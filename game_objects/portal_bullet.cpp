#include "portal_bullet.h"

#include "../game_core/area.h"
#include "../wall_mechanics/straight_wall.h"
#include "../game_core/scene.h"

PortalBullet::PortalBullet(Scene* scene) :
	KinematicBody(scene)
{
	AddAreaToGroup("Collider", QRectF(GetPosition().x(), GetPosition().y(),
									2 * BULLET_RADIUS, 2 * BULLET_RADIUS));
}

void PortalBullet::Update() {
	QList<Area*> areas;
	MoveAndCollide(areas);
	if (!scene_->GetRect().contains(GetPosition().toPoint())) {
		scene_->DeleteObject(name_);
	}
	if (areas.empty()) {
		return;
	}
	StraightWall* wall = 
		dynamic_cast<StraightWall*>(areas[0]->GetAreaObject());
	if (!wall) {
		return;
	}
	scene_->DeleteObject(name_);
}

void PortalBullet::Draw(QPainter* painter) const {
	painter->setPen(Qt::blue); 
	painter->setBrush(Qt::black);
	painter->drawEllipse(GetPosition().x() + BULLET_RADIUS,
		   				 GetPosition().y() + BULLET_RADIUS,
							BULLET_RADIUS, BULLET_RADIUS);	
}

void PortalBullet::SetVelocity(const QVector2D& velocity) {
	velocity_ = velocity.normalized() * BULLET_SPEED;
}

