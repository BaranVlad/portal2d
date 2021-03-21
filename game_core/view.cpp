#include "view.h"

View::View(Scene* scene) :
	GameObject(scene) 
{}

void View::SetPosition(const QVector2D& position) {
	position_ = position;
}

void View::SetPosition(qreal x, qreal y) {
	position_ = QVector2D(x, y);
}

QVector2D View::GetPosition() const {
	return position_;
}

void View::Move(const QVector2D& offset) {
	position_ += offset;
}

