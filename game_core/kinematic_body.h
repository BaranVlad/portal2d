#ifndef PORTAL2D_KINEMATIC_BODY_H_
#define PORTAL2D_KINEMATIC_BODY_H_

#include <QVector2D>
#include <QtGlobal>

#include "collide_object.h"

/* Abstract class that can move and collide */
class KinematicBody : public CollideObject {
protected:
	QVector2D velocity_(0, 0);	
public:
	KinematicBody() = delete;	
	KinematicBody(const QRectF& rect_area, Scene* scene);

	void SetVelocity(qreal x, qreal y);
	void SetVelocity(const QVector2D& velocity);

	bool IsOnFloor() const;
};

#endif
