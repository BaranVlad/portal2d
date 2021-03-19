#ifndef PORTAL2D_GAME_OBJECT_H_
#define PORTAL2D_GAME_OBJECT_H_

#include <QVector2D>
#include <QPoint>

#include "common_message.h"

enum class Direction { Up, Down, Left, Right };

class Scene;
/* It is the base class for all updateble classes that scene class contains */
class GameObject {
protected:
	Scene* scene_;
public:
	GameObject() = delete;
	GameObject(Scene* scene);

	static QPointF VectorToPoint(const QVector2D& vec);

	virtual void Update() = 0;

	/* Message object delete hear */
	virtual void TakeMessage(Message* msg) = 0;
	virtual ~GameObject() = default;
};

#endif

