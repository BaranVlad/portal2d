#include "collide_object.h"

CollideObject::CollideObject(Scene* scene) :
	AreaObject(scene)
{
	AddGroup("Collider");
}

