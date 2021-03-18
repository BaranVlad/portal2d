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

bool KinematicBody::IsOnFloor() const {
	bool with_collider = false;
	bool with_floor = false;

	for (Area* collider : GetAreasViaGroupName("Collider")) {
		for (int i = 0; i < collider->IntersectsSize(); i++) {
			if (collider[i].GetName() == "Floor") {
				with_floor = true;
			} else if (collider[i].GetName() == "Collider") {
				with_collider = true;
			}
		}
	}

	if (with_collider && with_floor) {
		return true;
	}
	return false;
}

