#ifndef STRAIGHT_WALL_H_
#define STRAIGHT_WALL_H_

enum class Direction { Up, Down, Left, Right };

#include "wall.h"
#include <QtGlobal>
#include <QPointF>
   
class StraightWall : public Wall {
private:
	Direction direction_;
	QPointF end_point_;
public:
	StraightWall() = delete;
	StraightWall(Scene* scene, Direction dir, qreal len);

	virtual void DrawActive(QPainter* painter) const;
	virtual void DrawInactive(QPainter* painter) const;

};

#endif

