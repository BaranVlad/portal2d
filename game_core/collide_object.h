#ifndef PROTAL2D_COLLIDE_OBJECT_H_
#define PROTAL2D_COLLIDE_OBJECT_H_

#include "area_object.h"

/* Class that use rect_area_ for colliding with other CollideObject */
class CollideObject : public AreaObject {
public:
	CollideObject() = delete;
	CollideObject(Scene* scene);
};

#endif

