#include "wall.h"

Wall::Wall(const QRectF& rect_area, Scene* scene) :
	CollideObject(rect_area, scene)
{}

virtual void Wall::Update() {
	CollideObject::Update();
}



