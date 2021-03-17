#include "kinematic_body.h"

KinematicBody::KinematicBody(const QRectF& rect_area, Scene* scene) :
	CollideObject(rect_area, scene)	
{}

void KinematicBody::SetVelocity(qreal x, qreal y) {
	velocity_.setX(x);
	velocity_.setY(y);
}

void KinematicBody::SetVelocity(const QVector2D& velocity) {
	velocity_ = veclocity;
}

bool KinematicBody::IsOnFloor() const {
	for (CollideObject* collider : collided) {
		if (collider->IsFloor()) {
			return true;
		}
	}
}

