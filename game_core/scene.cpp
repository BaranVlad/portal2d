#include "scene.h"

#include <QMap>

Scene::Scene(QObject* parent) :
	QObject(parent)
{}

Scene::~Scene() {
	for (GameObject* object : objects) {
		delete object;
	}	
}

void Scene::Draw(QPainter* painter) const {
	for (GameObject* object : objects) {
		View* object_to_draw = dynamic_cast<View*>(object);
		if (object_to_draw) {
			object_to_draw->Draw(painter);
		}
	}	
}

void Scene::Update() {
	for (GameObject* object : objects) {
		object->Update();
	}
}

void Scene::GetIntersected(AreaObject* area) {
	QMap::iterator area_begin = area.AreasBegin();	
	QMap::iterator area_end = area.AreasEnd();	
	for (QMap::iterator area_it = area_begin; it != area_end; it++) {
		Area* main_area = area_it.value();
		if (!main_area->IsActive()) {
			continue;
		}
		main_area.ClearIntersects();
		for (GameObject* object : objects) {
			AreaObject* area_obj = dynamic_cast<AreaObject*>(object);
			if (area_obj && area_obj != area) {
				QMap::iterator begin = area_obj.AreasBegin();
				QMap::iterator end = area_obj.AreasEnd();
				for (QMap::iterator it = begin; it != end; it++) {
					Area* spinoff_area = it.value();	
					if (main_area.IsIntersects(spinoff_area)) {
						main_area.AddIntersect(spinoff_area);
					}
				}
			}
		}
	}
}



