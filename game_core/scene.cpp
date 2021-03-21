#include "scene.h"

Scene::Scene(QObject* parent) :
	QObject(parent)
{
	KeysReset();
}

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

void Scene::Update(qreal delta_time) {
	for (GameObject* object : objects.values()) {
		object->Update(delta_time);
	}
	KeysUpdate();
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

bool Scene::GetMovableIntersects(Area* move_area, const QVector2D& velocity,
						QVector2D* offset, QList<Area*>& areas, Direction& direction) 
{
	QVector2D temp_offset;
	Direction temp_direction;
	bool has_offset = false;
	bool is_collide = false;
	for (Area* area : GetAllAreas()) {
		if (area == move_area) {
			continue;
		}
		if (area->MovableIntersect(move_area, velocity,
				   				&temp_offset, temp_direction)) {
			areas.push_back(area);
			if (dynamic_cast<CollideObject*>(area->GetAreaObject())) {
				is_collide = true;
				if (!has_offset ||
					offset->lengthSquared() > temp_offset.lengthSquared()) 
				{
					*offset = temp_offset;
					direction = temp_direction;
					has_offset = true;
				}
			}	
		}
	}	
	return is_collide;
}

QList<Area*> Scene::GetAllAreas() {
	QList<Area*> result;	
	for (GameObject* object : objects.values()) {
		AreaObject* area_object = dynamic_cast<AreaObject*>(object);
		for (Area* area : area_object->GetAreas()) {
			result.push_back(area);
		}
	}
	return result;
}

void Scene::keyPressEvent(QKeyEvent* event) {
	key_pressed_[event->key()] = KeyState::JustPressed;	
}

void Scene::keyReleaseEvent(QKeyEvent* event) {
	key_pressed_[event->key()] = KeyState::JustReleased;	
}

void Scene::KeysUpdate() {
	for (int i = 0; i < KEYS_COUNT; i++) {
		if (key_pressed_[i] == KeyState::JustPressed) {
			key_pressed_[i] = KeyState::Pressed;
		} else if (key_pressed_[i] == KeyState::JustReleased) {
			key_pressed_[i] = KeyState::Released;
		}
	}
}

bool Scene::IsKeyJustPressed(int key) {
	return key_pressed_[key] == KeyState::JustPressed;
}

bool Scene::IsKeyJustReleased(int key) {
	return key_pressed_[key] == KeyState::JustReleased;
}

bool Scene::IsKeyPressed(int key) {
	return 	key_pressed_[key] == KeyState::JustPressed ||
			key_pressed_[key] == KeyState::Pressed;	
}

void Scene::KeysReset() {
	for (int i = 0; i < KEYS_COUNT; i++) {
		key_pressed_[i] = KeyState::Released;
	}
}

