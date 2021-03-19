#include "straight_wall.h"

#include <QPen>

QVector2D NormVectorFromDirection(Direction dir) {
	switch (dir) {
		case (Direction::Up):
			return QVector2D(0, -1);
		case (Direction::Down):
			return QVector2D(0, 1);
		case (Direction::Left):
			return QVector2D(-1, 0);
		case (Direction::Right):
			return QVector2D(1, 0);
	}
	return QVector2D(0, 0);
}

StraightWall::StraightWall(Scene* scene, Direction dir, qreal len) :
	Wall(scene, NormVectorFromDirection(dir)),
	direction_(dir),
	len_(len)
{}

void StraightWall::DrawActive(QPainter* painter) const {
	QPen pen = painter->pen();
	pen.setWidth(3);
	pen.setColor(Qt::black);
	painter->setPen(pen);

	painter->drawLine(GameObject::VectorToPoint(position_),
		   				GameObject::VectorToPoint(end_point_));
}

void StraightWall::DrawInactive(QPainter* painter) const {
	QPen pen = painter->pen();
	pen.setWidth(3);
	pen.setColor(QColor(0, 0, 0, 100));	
	pen.setStyle(Qt::DashLine);
	painter->setPen(pen);

	painter->drawLine(GameObject::VectorToPoint(position_),
		   				GameObject::VectorToPoint(end_point_));
}

void StraightWall::TakeMessage(Message* message) {}

void StraightWall::UpdateEndPoint() {
	if (direction_ == Direction::Up || direction_ == Direction::Down) {
		end_point_.setX(position_.x() + len_);
		end_point_.setY(position_.y());
	} else {
		end_point_.setX(position_.x());
		end_point_.setY(position_.y() + len_);
	}
}

void StraightWall::SetPosition(qreal x, qreal y) {
	View::SetPosition(x, y);	
	UpdateEndPoint();
}

void StraightWall::SetPosition(const QVector2D& position) {
	View::SetPosition(position);	
	UpdateEndPoint();
}
