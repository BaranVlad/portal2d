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

QList<Area*> Scene::GetIntersected(Area* area) {
	QList<Area*> result;
	for (GameObject* object : objects.values()) {
		AreaObject* area_object = dynamic_cast<AreaObject*>(object);	
		if (!area_object) {
			continue;
		}
		for (Area* game_area : area_object->GetAreas()) {
			if (game_area->IsIntersects(*area)) {
				result.push_back(game_area);
			}
		}	
	}
	return result;
}

void Scene::SendTo(const QString& name, Message* message) {
	objects[name]->TakeMessage(message);
}

void Scene::AddGameObject(const QString& name, GameObject* game_object) {
	if (objects.contains(name)) {
		qDebug() << "Scene::AddGameObject(...) error: object with name " 
				<< name << " already exist";
	}
	objects[name] = game_object;	
}

