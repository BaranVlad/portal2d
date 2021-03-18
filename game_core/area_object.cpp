#include "area_object.h"
#include "scene.h"

AreaObject::AreaObject(Scene* scene) :
	View(scene)
{}

void AreaObject::Update() {
	scene_->GetIntersected(this);
}

AreaObject::~AreaObject() {
	for (Area* elem : GetAreas()) {
		delete elem;
	}
}

QPointF AreaObject::GetPosition() const {
	return position_;
}

bool AreaObject::IsGroupExist(const QString& name) const {
	return areas_.contains(name);
}

void AreaObject::AddGroup(const QString& name) {
	areas_[name];
}

QList<Area*> AreaObject::GetAreas() const {
	QList<Area*> result_list;
	for (auto& vec : areas_.values()) {
		for (Area* area : vec) {
			result_list.push_back(area);
		}
	}
	return result_list;
}

QList<QString> AreaObject::GetGroups() const {
	return areas_.keys();
}

QVector<Area*>& AreaObject::GetAreasViaGroupName(const QString& name) const {
	return areas_[name];
}

void AreaObject::AddAreaToGroup(const QString& name, Area* area) {
	areas_[name].push_back(area);
}



