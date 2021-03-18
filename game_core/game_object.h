#ifndef PORTAL2D_GAME_OBJECT_H_
#define PORTAL2D_GAME_OBJECT_H_

#include "message.h"

class Scene;
/* It is the base class for all updateble classes that scene class contains */
class GameObject {
protected:
	Scene* scene_;
public:
	GameObject() = delete;
	GameObject(Scene* scene);

	virtual void Update() = 0;

	/* Message object delete hear */
	virtual void TakeMessage(Message* msg) = 0;
	virtual ~GameObject() = default;
};

#endif

