#include "area.h"

#include "area_object.h"
#include <QDebug>

// debug
#include "../wall_mechanics/wall.h"

Area::Area(const QString& name, 
			const QRectF& rect_area, 
			AreaObject* area_object) : 
	GameObject(area_object->GetScene()),
	area_object_(area_object),
	rect_area_(rect_area),
	is_active_(true)
{
	SetName(name);
}

Area::Area(const QString& name, 
			const QJsonObject& js, 
			AreaObject* area_object) : 
	GameObject(area_object->GetScene()),
	area_object_(area_object),
	is_active_(true)
{
	SetName(name);
	FromJsonObject(js);
}


bool Area::IsActive() const {
	return is_active_;
}

void Area::SetActive(bool value) {
	is_active_ = value;
}

bool Area::IsIntersects(const Area& area) const {
	if (!is_active_ || !area.is_active_) {
		return false;
	}
	if (area_object_ == area.area_object_) {
		return false;
	}

	QRectF global_rect1 = GetGlobalRect();
	QRectF global_rect2 = area.GetGlobalRect();

	return global_rect1.intersects(global_rect2);
}

void Area::SetRect(const QRectF& rect_area) {
	rect_area_ = rect_area;	
}

AreaObject* Area::GetAreaObject() const {
	return area_object_;
}

const QString& Area::GetName() const {
	return name_;
}

QRectF Area::GetGlobalRect() const {
	QRectF global_rect = rect_area_;
	QVector2D position = area_object_->GetPosition();
	QPointF move_position(position.x(), position.y());
	global_rect.moveTo(rect_area_.topLeft() + move_position);

	return global_rect;
}

void Area::MoveRect(const QVector2D& vec) {
	rect_area_.translate(vec.toPointF());	
}

bool Area::MovableIntersect(Area* move_area, const QVector2D& velocity,
		   						QVector2D* offset, Direction& direction)
{
	bool is_collide = false;
	QRectF global_move = move_area->GetGlobalRect();
	QRectF global_area = GetGlobalRect();

	if (velocity.isNull()) {
		return false;
	}
	if (velocity.x() == 0) {
		if (velocity.y() > 0) {
			is_collide = StraightMoveIntersect(
				global_move.bottomLeft(), global_move.bottomRight(),
				QLineF(global_area.topLeft(), global_area.topRight()),
				Direction::Up, velocity,
				offset, direction
			);
		} else if (velocity.y() < 0) {
			is_collide = StraightMoveIntersect(
				global_move.topLeft(), global_move.topRight(),
				QLineF(global_area.bottomLeft(), global_area.bottomRight()),
				Direction::Down, velocity,
				offset, direction
			);
		}
	} else if (velocity.y() == 0) {
		if (velocity.x() > 0) {
			is_collide = StraightMoveIntersect(
				global_move.topRight(), global_move.bottomRight(),
				QLineF(global_area.topLeft(), global_area.bottomLeft()),
				Direction::Left, velocity,
				offset, direction
			);
		} else if (velocity.x() < 0) {
			is_collide = StraightMoveIntersect(
				global_move.topLeft(), global_move.bottomLeft(),
				QLineF(global_area.topRight(), global_area.bottomRight()),
				Direction::Right, velocity,
				offset, direction
			);
		}
	} else if (velocity.x() > 0 && velocity.y() < 0) {
		is_collide = Sweeping(global_move.topLeft(), global_move.bottomRight(),
					global_move.topRight(), velocity, 
					QLineF(global_area.bottomLeft(), global_area.bottomRight()),
					Direction::Down,
					QLineF(global_area.bottomLeft(), global_area.topLeft()),
					Direction::Left,
					offset, direction);	
	} else if (velocity.x() > 0 && velocity.y() > 0) {
		is_collide = Sweeping(global_move.topRight(), global_move.bottomLeft(),
					global_move.bottomRight(), velocity, 
					QLineF(global_area.topLeft(), global_area.bottomLeft()),
					Direction::Left,
					QLineF(global_area.topLeft(), global_area.topRight()),
					Direction::Up,
					offset, direction);	
	} else if (velocity.x() < 0 && velocity.y() < 0) {
		is_collide = Sweeping(global_move.bottomLeft(), global_move.topRight(),
					global_move.topLeft(), velocity, 
					QLineF(global_area.bottomRight(), global_area.topRight()),
					Direction::Right,
					QLineF(global_area.bottomRight(), global_area.bottomLeft()),
					Direction::Down,
					offset, direction);	
	} else if (velocity.x() < 0 && velocity.y() > 0) {
		is_collide = Sweeping(global_move.bottomRight(), global_move.topLeft(),
					global_move.bottomLeft(), velocity, 
					QLineF(global_area.topRight(), global_area.topLeft()),
					Direction::Up,
					QLineF(global_area.topRight(), global_area.bottomRight()),
					Direction::Right,
					offset, direction);	
	}
	return is_collide;
}

bool Area::Sweeping(const QPointF& first, const QPointF& second,
					const QPointF& center, const QVector2D& velocity,
					const QLineF& first_side, Direction first_dir,
				   	const QLineF& second_side, Direction second_dir,
					QVector2D* offset, Direction& direction)
{
	QPointF vel_point = velocity.toPointF();
	QLineF center_line(center, center + vel_point);	
	QLineF first_line(first, first + vel_point);
	QLineF second_line(second, second + vel_point);

	QLineF::IntersectType intersection;
	QPointF i_point;

	intersection = center_line.intersect(first_side, &i_point);
	if (intersection == QLineF::BoundedIntersection)
	{
		direction = first_dir;
		*offset = QVector2D(i_point - center);
		return true;
	}

	intersection = center_line.intersect(second_side, &i_point);
	if (intersection == QLineF::BoundedIntersection)
	{
		direction = second_dir;
		*offset = QVector2D(i_point - center);
		return true;
	}

	intersection = first_line.intersect(first_side, &i_point);
	if (intersection == QLineF::BoundedIntersection)
	{
		direction = first_dir;
		*offset = QVector2D(i_point - first);
		return true;
	}

	intersection = first_line.intersect(second_side, &i_point);
	if (intersection == QLineF::BoundedIntersection)
	{
		direction = first_dir;
		*offset = QVector2D(i_point - first);
		return true;
	}

	intersection = second_line.intersect(first_side, &i_point);
	if (intersection == QLineF::BoundedIntersection)
	{
		direction = second_dir;
		*offset = QVector2D(i_point - second);
		return true;
	}

	intersection = second_line.intersect(second_side, &i_point);
	if (intersection == QLineF::BoundedIntersection)
	{
		direction = second_dir;
		*offset = QVector2D(i_point - second);
		return true;
	}

	if (IsPointBetweenTwoLines(first_line, center_line, first_side.p1()) &&
	   (IsPointBetweenTwoLines(QLineF(first, center),
		QLineF(first + vel_point, center + vel_point), first_side.p1()) ||
		IsLinesEqual(QLineF(first, center), first_side)))
	{
		intersection = first_side.intersect(first_line, &i_point);
		direction = first_dir;
		if (intersection == QLineF::NoIntersection) {
			*offset = velocity;
		} else {
			*offset = QVector2D(i_point - first);
		}
		return true;
	}

	if (IsPointBetweenTwoLines(second_line, center_line, second_side.p1()) &&
	   (IsPointBetweenTwoLines(QLineF(second, center),
		QLineF(second + vel_point, center + vel_point), second_side.p1()) ||
		IsLinesEqual(QLineF(second, center), second_side)))
	{
		intersection = second_side.intersect(second_line, &i_point);
		direction = second_dir;
		if (intersection == QLineF::NoIntersection) {
			*offset = velocity;
		} else {
			*offset = QVector2D(i_point - second);
		}
		return true;
	}

	return false;
}

bool Area::IsLinesEqual(const QLineF& first, const QLineF& second) {
	QPointF point;
	return first.intersect(QLineF(first.p1(), second.p1()), &point) ==
											QLineF::NoIntersection;
}

bool Area::IsPointBetweenTwoLines(const QLineF& first,
								const QLineF& second, 
								const QPointF& i_point)
{
	return GetPointSign(first, i_point) * GetPointSign(second, i_point) < 0;
}


qreal Area::GetPointSign(const QLineF& line, const QPointF& point) const {
	QPointF d_point = line.p2() - line.p1();	
	return d_point.y() * point.x() - d_point.x() * point.y() -
		d_point.y() * line.p1().x() + d_point.x() * line.p1().y();
}

bool Area::StraightMoveIntersect(const QPointF& first, const QPointF& second,
							const QLineF& side, Direction side_dir, 
							const QVector2D& velocity, 
							QVector2D* offset, Direction& direction)
{
	QPointF vel_point = velocity.toPointF();
	QPointF i_point1;	
	QPointF i_point2;	

	QLineF first_line(first, first + vel_point);
	QLineF second_line(second, second + vel_point);
	
	auto intersect1 = first_line.intersect(side, &i_point1);
	auto intersect2 = second_line.intersect(side, &i_point2);
	if ((intersect1 == QLineF::BoundedIntersection &&
		intersect2 == QLineF::BoundedIntersection) ||
		IsPointBetweenTwoLines(first_line, second_line, side.p1()) || 
		IsPointBetweenTwoLines(first_line, second_line, side.p2())) 
	{
		QVector2D might_offset = QVector2D(i_point1 - first);
		if (might_offset.length() < velocity.length()) {
			*offset = might_offset;
			direction = side_dir;
			return true;
		} else {
			return false;
		}
	}
	return false;
}

void Area::Update() 
{}

void Area::ToJsonObject(QJsonObject& js) const {
	GameObject::ToJsonObject(js);
	js["rect_x"] = rect_area_.x();
	js["rect_y"] = rect_area_.y();
	js["rect_width"] = rect_area_.width();
	js["rect_height"] = rect_area_.height();
}
 
void Area::FromJsonObject(const QJsonObject& js) {
	GameObject::FromJsonObject(js);
	rect_area_.setX(js["rect_x"].toDouble());
	rect_area_.setY(js["rect_y"].toDouble());
	rect_area_.setWidth(js["rect_width"].toDouble());
	rect_area_.setHeight(js["rect_height"].toDouble());
}

