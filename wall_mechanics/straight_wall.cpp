#include "straight_wall.h"

#include "../game_core/consts.h"
#include "../game_core/scene.h"
#include "../game_objects/portal.h"

#include <QPen>

QVector2D NormVectorFromDirection(Direction dir) {
	switch (dir) {
		case (Direction::Up):
			return QVector2D(0, 1);
		case (Direction::Down):
			return QVector2D(0, -1);
		case (Direction::Left):
			return QVector2D(1, 0);
		case (Direction::Right):
			return QVector2D(-1, 0);
	}
	return QVector2D(0, 0);
}

StraightWall::StraightWall(Scene* scene, Direction dir, qreal len) :
	Wall(scene, NormVectorFromDirection(dir)),
	direction_(dir),
	len_(len)
{
	QRectF collide_rect;
	if (dir == Direction::Down) {
		collide_rect = QRectF(0, 0, len, WALL_LINE_WIDTH);	
		collide_rect.moveTop(-WALL_LINE_WIDTH / 2);
		line_ = QLineF(0, 0, len_, 0);
	} else if (dir == Direction::Up) {
		collide_rect = QRectF(0, -WALL_LINE_WIDTH, len, WALL_LINE_WIDTH);
		collide_rect.moveBottom(WALL_LINE_WIDTH / 2);
		line_ = QLineF(0, 0, len_, 0);
	} else if (dir == Direction::Right) {
		collide_rect = QRectF(0, 0, WALL_LINE_WIDTH, len);
		collide_rect.moveLeft(-WALL_LINE_WIDTH / 2);
		line_ = QLineF(0, 0, 0, len_);
	} else if (dir == Direction::Left) {
		collide_rect.moveRight(WALL_LINE_WIDTH / 2);
		collide_rect = QRectF(-WALL_LINE_WIDTH, 0, WALL_LINE_WIDTH, len);
		line_ = QLineF(0, 0, 0, len_);
	}
	AddAreaToGroup("Collider", collide_rect);
}

void StraightWall::Update() 
{}

void StraightWall::DrawActive(QPainter* painter) const {
	DrawPortablePart(painter);

	QPen pen;
	pen.setWidth(WALL_LINE_WIDTH);
	pen.setColor(Qt::black);
	painter->setPen(pen);
	painter->setBrush(Qt::black);

	painter->drawLine(line_);
}

void StraightWall::DrawInactive(QPainter* painter) const {
	QPen pen = painter->pen();
	pen.setWidth(WALL_LINE_WIDTH);
	pen.setColor(QColor(0, 0, 0, 100));	
	pen.setStyle(Qt::DashLine);
	painter->setPen(pen);

	painter->drawLine(line_);
}

void StraightWall::SetPosition(qreal x, qreal y) {
	line_.translate(x - GetPosition().x(), y - GetPosition().y());
	View::SetPosition(x, y);	
}

void StraightWall::SetPosition(const QVector2D& position) {
	line_.translate((position - GetPosition()).toPointF());
	View::SetPosition(position);	
}

void StraightWall::DrawPortablePart(QPainter* painter) const {
	if (!is_portable_) {
 		painter->setBrush(Qt::gray);
		painter->setPen(Qt::NoPen);
		QRect paint_rect;
		switch (direction_) {
			case (Direction::Down):
				paint_rect.setRect(0, 0, len_, WALL_PORTABLE_AREA_SIZE);
				break;
			case (Direction::Up):
				paint_rect.setRect(0, -WALL_PORTABLE_AREA_SIZE, 
									len_, WALL_PORTABLE_AREA_SIZE);
				break;
			case (Direction::Right):
				paint_rect.setRect(0, 0, WALL_PORTABLE_AREA_SIZE, len_);
				break;
			case (Direction::Left):
				paint_rect.setRect(-WALL_PORTABLE_AREA_SIZE, 0,
					   				WALL_PORTABLE_AREA_SIZE, len_);
				break;
		}
		paint_rect.translate(GetPosition().toPoint());
		painter->drawRect(paint_rect);
	}	
}

void StraightWall::OpenPortal(const QPointF& point, 
									const QString& portal_name) const 
{
	if (IsPortable() == false) {
		return;
	}	

	if (scene_->IsOnScene(portal_name)) {
		scene_->DeleteObject(portal_name);
	}
	
	Portal* portal = new Portal(scene_);
	portal->SetPosition(QVector2D(point));
	portal->SetDirection(direction_);
	portal->SetNormalVector(normal_vector_);
	portal->SetWall(this);
	scene_->AddGameObject(portal_name, portal);
}

QLineF StraightWall::GetLine() const {
	return line_;
}

qreal StraightWall::GetWidth() const {
	if (direction_ == Direction::Up ||
		direction_ == Direction::Down) 
	{
		return len_;
	} else {
		return WALL_LINE_WIDTH;
	}
}

qreal StraightWall::GetHeight() const {
	if (direction_ == Direction::Up ||
		direction_ == Direction::Down) 
	{
		return WALL_LINE_WIDTH;
	} else {
		return len_;
	}
}

void StraightWall::ToJsonObject(QJsonObject& js) const {
	Wall::ToJsonObject(js);

	js["direction"] = static_cast<int>(direction_);
	js["len"] = len_;
	
	js["line.p1.x"] = line_.p1().x();
	js["line.p1.y"] = line_.p1().y();

	js["line.p2.x"] = line_.p2().x();
	js["line.p2.y"] = line_.p2().y();

}

void StraightWall::FromJsonObject(const QJsonObject& js) {
	Wall::FromJsonObject(js);

	direction_ = static_cast<Direction>(js["direction"].toInt());
	len_ = js["len"].toDouble();
	line_.setP1(QPointF(js["line.p1.x"].toDouble(), 
						js["line.p1.y"].toDouble()));
	line_.setP2(QPointF(js["line.p2.x"].toDouble(), 
						js["line.p2.y"].toDouble()));
}

StraightWall::StraightWall(Scene* scene) :
	Wall(scene)
{}

