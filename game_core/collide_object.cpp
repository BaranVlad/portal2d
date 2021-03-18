#include "collide_object.h"

CollideObject::CollideObject(Scene* scene) :
	AreaObject(scene)
{
	AddGroup("Floor");
	AddGroup("Collider");
}

void CollideObject::Update() {
	AreaObject::Update();
}

