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

void StraightWall::Update() 
{}

void StraightWall::DrawActive(QPainter* painter) const {
	DrawPortablePart(painter);

	QPen pen;
	pen.setWidth(WALL_LINE_WIDTH);
	pen.setColor(Qt::black);
	painter->setPen(pen);
	painter->setBrush(Qt::black);

	painter->drawLine(GetLine());
}

void StraightWall::DrawInactive(QPainter* painter) const {
	QPen pen = painter->pen();
	pen.setWidth(WALL_LINE_WIDTH);
	pen.setColor(QColor(0, 0, 0, 100));	
	pen.setStyle(Qt::DashLine);
	painter->setPen(pen);

	painter->drawLine(GetLine());
}

void StraightWall::DrawPortablePart(QPainter* painter) const {
	if (!is_portable_) {
		int offset = 3;
 		painter->setBrush(Qt::gray);
		painter->setPen(Qt::NoPen);
		QRect paint_rect;
		switch (direction_) {
			case (Direction::Down):
				paint_rect.setRect(offset, 0, 
						len_ - 2*offset, WALL_PORTABLE_AREA_SIZE);
				break;
			case (Direction::Up):
				paint_rect.setRect(offset, -WALL_PORTABLE_AREA_SIZE, 
								len_ - 2*offset, WALL_PORTABLE_AREA_SIZE);
				break;
			case (Direction::Right):
				paint_rect.setRect(0, offset,
					   	WALL_PORTABLE_AREA_SIZE, len_ - 2*offset);
				break;
			case (Direction::Left):
				paint_rect.setRect(-WALL_PORTABLE_AREA_SIZE, offset,
					   			WALL_PORTABLE_AREA_SIZE, len_ - 2*offset);
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
	return line_.translated(GetPosition().x(),
			GetPosition().y());
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
	
	js["class"] = "StraightWall";
}

void StraightWall::FromJsonObject(const QJsonObject& js) {
	Wall::FromJsonObject(js);

	Direction direction = static_cast<Direction>(js["direction"].toInt());
	qreal len = js["len"].toDouble();

	SetDirectionAndLen(direction, len);
}

StraightWall::StraightWall(Scene* scene) :
	Wall(scene)
{
	z_index = -1;
	SetDirectionAndLen(Direction::Up, 100);
}

void StraightWall::SetDirectionAndLen(Direction dir, qreal len) {
	QRectF collide_rect;
	direction_ = dir;
	len_ = len;
	if (dir == Direction::Down) {
		collide_rect = QRectF(0, 0, len, WALL_LINE_WIDTH);	
		collide_rect.moveTop(-WALL_LINE_WIDTH / 2.);
		line_ = QLineF(0, 0, len_, 0);
	} else if (dir == Direction::Up) {
		collide_rect = QRectF(0, -WALL_LINE_WIDTH, len, WALL_LINE_WIDTH);
		collide_rect.moveBottom(WALL_LINE_WIDTH / 2.);
		line_ = QLineF(0, 0, len_, 0);
	} else if (dir == Direction::Right) {
		collide_rect = QRectF(0, 0, WALL_LINE_WIDTH, len);
		collide_rect.moveLeft(-WALL_LINE_WIDTH / 2.);
		line_ = QLineF(0, 0, 0, len_);
	} else if (dir == Direction::Left) {
		collide_rect = QRectF(-WALL_LINE_WIDTH, 0, WALL_LINE_WIDTH, len);
		collide_rect.moveRight(WALL_LINE_WIDTH / 2.);
		line_ = QLineF(0, 0, 0, len_);
	}
	ClearAll();
	SetNormalVector(NormVectorFromDirection(dir));
	AddAreaToGroup("Collider", collide_rect);
	SetAreasActive(IsActive());
}

Direction StraightWall::GetDirection() const {
	return direction_;
}

qreal StraightWall::GetLen() const {
	return len_;
}

