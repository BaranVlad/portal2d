#ifndef PORTAL2D_PLAYER_2D
#define PORTAL2D_PLAYER_2D

#define PLAYER_W 20
#define PLAYER_H 40

#include <QPainter>

#include "../game_core/kinematic_body.h"

class Scene;
class Message;

class Player : public KinematicBody {
private:

public:
	Player(Scene* scene);
	
	virtual void Update();	
	virtual void Draw(QPainter* painter) const;
	virtual void TakeMessage(Message* msg);
	void FirePortalBullet() const;

	void KeyUpdate();
};

#endif

