#include "kinematic_body.h"

KinematicBody::KinematicBody(Scene* scene) :
	CollideObject(scene)	
{}

void KinematicBody::SetVelocity(qreal x, qreal y) {
	velocity_.setX(x);
	velocity_.setY(y);
}

void KinematicBody::SetVelocity(const QVector2D& velocity) {
	velocity_ = velocity;
}

bool KinematicBody::IsOnFloor() const 
{}

