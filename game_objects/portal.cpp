#include "portal.h"

#include "../game_core/consts.h"
#include "../game_core/scene.h"
#include <QColor>


Portal::Portal(Scene* scene) :
	AreaObject(scene)	
{}

void Portal::Update() {
	if (!wall_->IsActive() || !wall_->IsPortable()) {
		scene_->DeleteObject(GetName());
	}
}

void Portal::Draw(QPainter* painter) const
{
	QBrush brush(Qt::SolidPattern);
	if (name_ == "portal_blue") {
		brush.setColor(QColor(40, 80, 200));
	} else if (name_ == "portal_orange") {
		brush.setColor(QColor(255, 165, 0));
	} else {
		brush.setColor(QColor(0, 0, 0));
	}
	painter->setBrush(brush);
	painter->setPen(QPen(Qt::black, 2));
	
	QRectF global_rect = portal_rect_;
	global_rect.moveTo(portal_rect_.topLeft() + GetPosition().toPointF());
	painter->drawRect(global_rect);
}

void Portal::SetDirection(Direction direction) {
	if (direction == Direction::Up || direction == Direction::Down) {
		portal_rect_.setRect(-PORTAL_FLOOR_LONG/2., -PORTAL_WIDE/2.,
										PORTAL_FLOOR_LONG, PORTAL_WIDE);
	} else {
		portal_rect_.setRect(-PORTAL_WIDE/2., -PORTAL_LONG/2.,
											PORTAL_WIDE, PORTAL_LONG);
	}

	direction_ = direction;
	ClearGroup("trigger");
	AddAreaToGroup("trigger", portal_rect_); 
}

void Portal::SetNormalVector(const QVector2D& vec) {
	normal_vector_ = vec;
}

QVector2D Portal::GetNormalVector() const {
	return normal_vector_;
}

qreal Portal::GetWidth() const {
	if (direction_ == Direction::Up || 
		direction_ == Direction::Down) 
	{
		return PORTAL_FLOOR_LONG;
	} else {
		return PORTAL_WIDE;
	}
}

qreal Portal::GetHeight() const {
	if (direction_ == Direction::Up || 
		direction_ == Direction::Down) 
	{
		return PORTAL_WIDE;
	} else {
		return PORTAL_LONG;
	}
}

void Portal::SetWall(const StraightWall* wall) {
	wall_ = wall;
}

bool Portal::IsInPair() {
	if (GetName() == "portal_blue") {
		return scene_->IsOnScene("portal_orange");
	} else if (GetName() == "portal_orange") {
		return scene_->IsOnScene("portal_blue");
	}
}

