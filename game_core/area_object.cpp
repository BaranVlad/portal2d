#include "area_object.h"

#include "scene.h"

#include <QJsonArray>

AreaObject::AreaObject(Scene* scene) :
	View(scene)
{}

AreaObject::~AreaObject() {
	for (Area* elem : GetAreas()) {
		delete elem;
	}
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

void AreaObject::AddAreaToGroup(const QString& name, const QRectF& area_rect) {
	areas_[name].push_back(new Area(name, area_rect, this));
}

void AreaObject::AddAreaToGroup(const QString& name, Area* area) {
	areas_[name].push_back(area);
}

void AreaObject::ClearGroup(const QString& name) {
	areas_[name].clear();
}

void AreaObject::ToJsonObject(QJsonObject& js) const {
	View::ToJsonObject(js);	

	QJsonObject areas_map;
	QJsonArray vec_obj;
	for (QString& key : areas_.keys()) {
		QJsonObject area_obj;
		for (Area* area : areas_[key]) {
			area->ToJsonObject(area_obj);
			vec_obj.push_back(QJsonValue(area_obj));
		}
		areas_map[key] = vec_obj;
	}
	js["Areas"] = QJsonValue(areas_map);
}

void AreaObject::FromJsonObject(const QJsonObject& js) {
	View::FromJsonObject(js);
	QJsonObject areas_map = js["Areas"].toObject();

	QJsonArray vec_obj;
	Area* area;
	for (QString& key : areas_map.keys()) {
		QJsonArray area_vec = areas_map[key].toArray();
		for (QJsonValueRef area_obj : area_vec) {
			area = new Area(key, area_obj.toObject(), this);
			AddAreaToGroup(key, area);
		}
	}
}

