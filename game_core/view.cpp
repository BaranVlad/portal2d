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

void View::Move(qreal x, qreal y) {
	Move(QVector2D(x, y));
}

void View::SetCenter(const QVector2D& point) {
	SetPosition(point.x() - GetWidth() / 2, point.y() - GetHeight() / 2);
}

QVector2D View::GetCenter() const {
	return GetPosition() + QVector2D(GetWidth() / 2, GetHeight() / 2);
}

void View::ToJsonObject(QJsonObject& js) const {
	GameObject::ToJsonObject(js);
	js["x"] = position_.x();
	js["y"] = position_.y();
}

void View::FromJsonObject(const QJsonObject& js) {
	GameObject::FromJsonObject(js);
	SetPosition(js["x"].toDouble(), js["y"].toDouble());
}

