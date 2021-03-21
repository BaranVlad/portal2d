#include "area.h"

#include "area_object.h"

Area::Area(const QString& name, 
			const QRectF& rect_area, 
			AreaObject* area_object) : 
	area_object_(area_object),
	rect_area_(rect_area),
	name_(name)
{}

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
	rect_area_.translate(GameObject::VectorToPoint(vec));	
}

bool Area::MovableIntersect(Area* move_area, const QVector2D& velocity,
		   						QVector2D* offset, Direction& direction)
{
	bool is_collide;
	QRectF global_move = move_area->GetGlobalRect();
	QRectF global_area = GetGlobalRect();
	if (velocity.x() >= 0 && velocity.y() <= 0) {
		is_collide = Sweeping(global_move.topLeft(), global_move.bottomRight(),
					global_move.topRight(), velocity, 
					QLineF(global_area.bottomLeft(), global_area.bottomRight()),
					Direction::Down,
					QLineF(global_area.bottomLeft(), global_area.topLeft()),
					Direction::Left,
					offset, direction);	
	} else if (velocity.x() >= 0 && velocity.y() >= 0) {
		is_collide = Sweeping(global_move.topRight(), global_move.bottomLeft(),
					global_move.bottomRight(), velocity, 
					QLineF(global_area.topLeft(), global_area.bottomLeft()),
					Direction::Left,
					QLineF(global_area.topLeft(), global_area.topRight()),
					Direction::Up,
					offset, direction);	
	} else if (velocity.x() <= 0 && velocity.y() <= 0) {
		is_collide = Sweeping(global_move.bottomLeft(), global_move.topRight(),
					global_move.topLeft(), velocity, 
					QLineF(global_area.bottomRight(), global_area.topRight()),
					Direction::Right,
					QLineF(global_area.bottomRight(), global_area.bottomLeft()),
					Direction::Down,
					offset, direction);	
	} else if (velocity.x() <= 0 && velocity.y() >= 0) {
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
				   	const QLineF second_side, Direction second_dir,
					QVector2D* offset, Direction& direction)
{
	QPointF vel_point = GameObject::VectorToPoint(velocity);
	QLineF center_line(center, center + vel_point);	
	QLineF::IntersectType intersection;
	QPointF i_point;
	
	intersection = center_line.intersect(first_side, &i_point);
	if (intersection == QLineF::BoundedIntersection) {
		direction = first_dir;
		*offset = QVector2D(i_point - center);
		return true;
	}

	intersection = center_line.intersect(second_side, &i_point);
	if (intersection == QLineF::BoundedIntersection) {
		direction = second_dir;
		*offset = QVector2D(i_point - center);
		return true;
	}

	QLineF first_line(first, first + vel_point);
	intersection = first_line.intersect(first_side, &i_point);
	if (intersection == QLineF::BoundedIntersection) {
		direction = first_dir;
		*offset = QVector2D(i_point - first);
		return true;
	}

	intersection = center_line.intersect(second_side, &i_point);
	if (intersection == QLineF::BoundedIntersection) {
		direction = first_dir;
		*offset = QVector2D(i_point - first);
		return true;
	}

	QLineF second_line(second, second + vel_point);
	intersection = second_line.intersect(first_side, &i_point);
	if (intersection == QLineF::BoundedIntersection) {
		direction = second_dir;
		*offset = QVector2D(i_point - second);
		return true;
	}

	intersection = second_line.intersect(second_side, &i_point);
	if (intersection == QLineF::BoundedIntersection) {
		direction = second_dir;
		*offset = QVector2D(i_point - second);
		return true;
	}

	return false;
}

