#include "scene.h"

Scene::Scene(QObject* parent) :
	QObject(parent)
{}

Scene::~Scene() {
	for (GameObject* object : objects.values()) {
		delete object;
	}
}

void Scene::Draw(QPainter* painter) const {
	for (GameObject* object : objects.values()) {
		View* object_to_draw = dynamic_cast<View*>(object);
		if (object_to_draw) {
			object_to_draw->Draw(painter);
		}
	}	
}

void Scene::Update() {
	for (GameObject* object : objects.values()) {
		object->Update();
	}
}

void Scene::GetIntersected(AreaObject* area_object) {
	for (Area* main_area : area_object->GetAreas()) {
		if (!main_area->IsActive()) {
			continue;
		}
		main_area->ClearIntersects();
		for (GameObject* object : objects) {
			AreaObject* area_object_diff = dynamic_cast<AreaObject*>(object);
			for (Area* not_main_area : area_object_diff->GetAreas()) { 
				if (main_area->IsIntersects(*not_main_area)) {
					main_area->AddIntersect(not_main_area);
				}
			}
		}
	}
}

void Scene::SendTo(const QString& name, Message* message) {
	objects[name]->TakeMessage(message);
}


