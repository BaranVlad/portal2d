#include "view.h"

View::View(Scene* scene) :
	GameObject(scene) 
{}

void View::SetPosition(const QPointF& position) {
	position_ = position;
}

void View::SetPosition(qreal x, qreal y) {
	position_ = QPointF(x, y);
}

