#ifndef PORTAL2D_KINEMATIC_BODY_H_
#define PORTAL2D_KINEMATIC_BODY_H_

#include <QVector2D>
#include <QtGlobal>

#include "collide_object.h"

class Portal;

/* Abstract class that can move and collide */
class KinematicBody : public CollideObject {
protected:
	QVector2D velocity_ = QVector2D(0, 0);	
	bool is_on_floor_ = false;
public:
	KinematicBody() = delete;	
	KinematicBody(Scene* scene);

	/* Move kinamatic body and collide it with colliders
	 * returns list of colliding areas and side of colliding rect */
	bool MoveAndCollide(QList<Area*>& areas);
	void Teleport(Portal* collided_portal);

	qreal GetFriction(int x_speed);
	qreal GetAirFriction(int x_speed);

	void FrictionUpdate(qreal friction);

	void SetVelocity(qreal x, qreal y);
	void SetVelocity(const QVector2D& velocity);

	bool IsOnFloor() const;

	static QVector2D gravity;
};

#endif

