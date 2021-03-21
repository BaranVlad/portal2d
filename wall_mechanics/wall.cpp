#include "wall.h"

Wall::Wall(Scene* scene, const QVector2D& normal_vector) :
	CollideObject(scene),
	normal_vector_(normal_vector),
	is_active_(true)
{}

void Wall::Update(qreal delta_time) {}

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

