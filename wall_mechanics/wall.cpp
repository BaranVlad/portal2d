#include "wall.h"

#include "../game_core/area.h"
#include <QDebug>

bool Wall::IsActive() const {
	return is_active_;
}

void Wall::SetActive(bool value) {
	is_active_ = value;
	SetAreasActive(value);
}

void Wall::Draw(QPainter* painter) const {
	if (is_active_)	{
		DrawActive(painter);
	} else {
		DrawInactive(painter);
	}
}

void Wall::ChangeActive() {
	SetActive(!IsActive());
}

bool Wall::IsPortable() const {
	return is_portable_;
}

void Wall::SetPortable(bool value) {
	is_portable_ = value;
}

void Wall::CreatePortal() 
{}

void Wall::ToJsonObject(QJsonObject& js) const {
	CollideObject::ToJsonObject(js);
	
	js["normal_vector_x"] = normal_vector_.x();
	js["normal_vector_y"] = normal_vector_.y();
	js["is_active"] = is_active_;
	js["is_portable"] = is_portable_;
}

void Wall::FromJsonObject(const QJsonObject& js) {
	CollideObject::FromJsonObject(js);

	normal_vector_.setX(js["normal_vector_x"].toDouble());
	normal_vector_.setY(js["normal_vector_y"].toDouble());
	setActive(js["is_active"].toBool());
	is_portable_ = js["is_portable"].toBool();
}

Wall::Wall(Scene* scene) :
	CollideObject(scene),
	is_portable_(false)
{
	SetActive(true);
}

void Wall::SetNormalVector(const QVector2D& normal_vec) {
	normal_vector_ = normal_vec;
}

