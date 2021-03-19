#include "game_object.h"

GameObject::GameObject(Scene* scene) : scene_(scene) {}

QPointF GameObject::VectorToPoint(const QVector2D& vec) {
	return QPointF(vec.x(), vec.y());
}

