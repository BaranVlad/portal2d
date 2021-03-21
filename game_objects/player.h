#ifndef PORTAL2D_PLAYER_2D
#define PORTAL2D_PLAYER_2D

#include "../game_core/kinematic_body.h"

#define PLAYER_W 20
#define PLAYER_H 40

class Player : public KinematicBody {
private:

public:
	Player(Scene* scene);
	
	virtual void Update(qreal delta_);	
	virtual void Draw(QPainter* painter) const;
	virtual void TakeMessage(Message* msg);

	void KeyUpdate();
};

#endif

