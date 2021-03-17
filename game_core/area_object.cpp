#include "area_object.h"
#include "scene.h"

AreaObject::AreaObject(Scene* scene) :
	View(scene),
{}

void AreaObject::Update() {
	scene->GetIntersected(this);
}

void AreaObject::AddArea(const QString& name, const QRectF rect_area) {
	Area* area = new Area(rect_area, this);
	areas_[name] = area;
}

Area* AreaObject::GetArea(const QString& name) const {
	return areas_[name];
}

virtual AreaObject::~AreaObject() {
	for (auto& elem : areas_) {
		delete elem.value();
	}
}

bool AreaObject::IsAreaActive(const QString& area_name) const {
	return areas_[area_name]->IsActive();
}

void AreaObject::SetAreaActive(const QString& area_name, bool value) {
	map[area_name]->SetActive(value);
}

QMap::iterator AreaObject::AreasBegin() {
	return areas_.begin();	
}

QMap::iterator AreaObject::AreasEnd() {
	return areas_.end();
}

QPointF AreaObject::GetPosition() const {
	return position_;
}

