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
	end_point_(QPointF(position_.x() + len, position_.y() + len))
{}

void StraightWall::DrawActive(QPainter* painter) const {
	QPen pen = painter->pen();
	pen.setWidth(3);
	pen.setColor(Qt::black);
	painter->setPen(pen);

	painter->drawLine(position_, end_point_);
}

void StraightWall::DrawInactive(QPainter* painter) const {
	QPen pen = painter->pen();
	pen.setWidth(3);
	pen.setColor(QColor(0, 0, 0, 100));	
	pen.setStyle(Qt::DashLine);
	painter->setPen(pen);

	painter->drawLine(position_, end_point_);
}

