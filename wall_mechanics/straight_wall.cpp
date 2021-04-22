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
{
	QRectF collide_rect;
	if (dir == Direction::Down) {
		collide_rect = QRectF(0, 0, len, WALL_LINE_WIDTH);	
	} else if (dir == Direction::Up) {
		collide_rect = QRectF(0, -WALL_LINE_WIDTH, len, WALL_LINE_WIDTH);
	} else if (dir == Direction::Left) {
		collide_rect = QRectF(0, 0, WALL_LINE_WIDTH, len);
	} else if (dir == Direction::Right) {
		collide_rect = QRectF(-WALL_LINE_WIDTH, 0, WALL_LINE_WIDTH, len);
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

	painter->drawLine(position_.toPointF(),
		   				end_point_.toPointF());
}

void StraightWall::DrawInactive(QPainter* painter) const {
	QPen pen = painter->pen();
	pen.setWidth(8);
	pen.setColor(QColor(0, 0, 0, 100));	
	pen.setStyle(Qt::DashLine);
	painter->setPen(pen);

	painter->drawLine(position_.toPointF(),
		   				end_point_.toPointF());
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
			case (Direction::Left):
				paint_rect.setRect(0, 0, WALL_PORTABLE_AREA_SIZE, len_);
				break;
			case (Direction::Right):
				paint_rect.setRect(-WALL_PORTABLE_AREA_SIZE, 0,
					   				WALL_PORTABLE_AREA_SIZE, len_);
				break;
		}
		paint_rect.translate(GetPosition().toPoint());
		painter->drawRect(paint_rect);
	}	
}

