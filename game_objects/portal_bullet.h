#ifndef PORTAL_BULLET_H_
#define PORTAL_BULLET_H_

#include "../game_core/kinematic_body.h"

#include <QVector2D>

#define BULLET_RADIUS 5
#define BULLET_SPEED 20

class PortalBullet : public KinematicBody {
private:
public:
	PortalBullet() = delete;
	PortalBullet(Scene* scene);

	virtual void Update();
	virtual void Draw(QPainter* painter) const;
	void SetVelocity(const QVector2D& velocity);
};

#endif

