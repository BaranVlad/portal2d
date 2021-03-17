#ifndef PORTAL2D_WALL_H_
#define PORTAL2D_WALL_H_

#include "../game_core/collide_object.h"

/* Abstract class for all walls (include ground) */
class Wall : public CollideObject {
private:
	bool is_floor;
public:
	Wall() = delete;
	Wall(const QRectF& rect_area, Scene* scene);

	virtual void Update();
}

#endif

