#include "game_object.h"

GameObject::GameObject(Scene* scene) : scene_(scene) {}

void GameObject::TakeMessage(Message* msg) 
{}

QJsonValue GameObject::ToJsonValue() const 
{}

void GameObject::FromJsonObject(const QJsonObject& js) 
{}

Scene* GameObject::GetScene() const {
	return scene_;
}

void GameObject::SetName(const QString& name) {
	name_ = name;
}

const QString& GameObject::GetName() const {
	return name_;
}

