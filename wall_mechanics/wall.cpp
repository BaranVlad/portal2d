#include "wall.h"

#include "../game_core/area.h"

Wall::Wall(Scene* scene, const QVector2D& normal_vector) :
	CollideObject(scene),
	normal_vector_(normal_vector),
	is_active_(true),
	is_portable_(false)
{}

bool Wall::IsActive() const {
	return is_active_;
}

void Wall::SetActive(bool value) {
	is_active_ = value;
	for (Area* area : GetAreas()) {
		area->SetActive(value);
	}
}

void Wall::Draw(QPainter* painter) const {
	if (is_active_)	{
		DrawActive(painter);
	} else {
		DrawInactive(painter);
	}
}

void Wall::ChangeState() {
	if (is_active_) {
		SetActive(false);
	} else {
		SetActive(true);
	}
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
	is_active_ = js["is_active"].toBool();
	is_portable_ = js["is_portable"].toBool();
}

Wall::Wall(Scene* scene) :
	CollideObject(scene)
{}

