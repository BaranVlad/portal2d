#include "game_object.h"

#include "common_message.h"

GameObject::GameObject(Scene* scene) : scene_(scene) {}

void GameObject::TakeMessage(Message* msg) 
{}

void GameObject::ToJsonObject(QJsonObject& js) const 
{
	js["name"] = name_;
}

void GameObject::FromJsonObject(const QJsonObject& js) 
{
	name_ = js["name"].toString();
}

Scene* GameObject::GetScene() const {
	return scene_;
}

void GameObject::SetName(const QString& name) {
	name_ = name;
}

const QString& GameObject::GetName() const {
	return name_;
}

