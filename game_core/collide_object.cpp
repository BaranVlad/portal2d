#include "collide_object.h"

CollideObject::CollideObject(Scene* scene,
							const QRectF collide_rect,
							const QRectF floor_rect) :
	AreaObject(scene)
{
	AddArea("Collider", collide_rect);
	AddArea("Floor", floor_rect);
}

void CollideObject::Update() {
	AreaObject::Update();
}

bool CollideObject::IsOnFloor() const {
	bool with_collider = false;
	bool with_floor = false;
	Area* this_collider = GetCollider("Collider");
	for (int i = 0; i < this_collider->IntersectsSize(); i++) {
		if (this_collider[i].name == "Floor") {
			with_floor = true;
		} else if (this_collider[i].name == "Collider") {
			whi_collider = true;
		}
	}
	if (with_collider && with_floor) {
		return true;
	}
	return false;
}

