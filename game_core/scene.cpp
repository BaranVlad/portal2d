#include "scene.h"

#include "area.h"
#include "common_message.h"
#include "collide_object.h"
#include "camera.h"
#include "view.h"

Scene::Scene(QObject* parent) :
	QObject(parent),
	camera_(new Camera(this)),
	background(":background.png")
{
	camera_->SetSourceSize(800, 600);
	camera_->SetCurrentRect(0, 0, 800, 600);
}

Scene::~Scene() {
	for (GameObject* object : objects.values()) {
		delete object;
	}
	delete camera_;
}

void Scene::Draw(QPainter* painter) const {
	camera_->SetPainter(painter);
	camera_->Update();

	DrawBackground(painter);
	for (GameObject* object : objects.values()) {
		View* object_to_draw = dynamic_cast<View*>(object);
		if (object_to_draw) {
			object_to_draw->Draw(painter);
		}
	}	
}

void Scene::Update(qreal delta_time) {
	delta_time_ = delta_time;
	for (GameObject* object : objects.values()) {
		object->Update();
	}
	KeysUpdate();
}

QList<Area*> Scene::GetIntersected(Area* area) {
	QList<Area*> result;
	for (GameObject* object : objects.values()) {
		AreaObject* area_object = dynamic_cast<AreaObject*>(object);	
		if (!area_object || area_object == area->GetAreaObject()) {
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

void Scene::SendTo(Message* message) {
	objects[message->GetDest()]->TakeMessage(message);
}

void Scene::AddGameObject(const QString& name, GameObject* game_object) {
	if (objects.contains(name)) {
		qDebug() << "Scene::AddGameObject(...) error: object with name " 
				<< name << " already exist";
		return;
	}
	game_object->SetName(name);
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
				   				&temp_offset, temp_direction)) 
		{
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
	if (IsKeyPressed(event->key())) {
		return;
	}
	keyboard[event->key()] = KeyState::JustPressed;	
}

void Scene::keyReleaseEvent(QKeyEvent* event) {
	keyboard[event->key()] = KeyState::JustReleased;
}

void Scene::KeysUpdate() {
	for (int key : keyboard.keys()) {
		if (keyboard[key] == KeyState::JustPressed) {
			keyboard[key] = KeyState::Pressed;
		} else if (keyboard[key] == KeyState::JustReleased) {
			keyboard[key] = KeyState::Released;
		}
	}
	for (int key : mouse_keys.keys()) {
		if (mouse_keys[key] == KeyState::JustPressed) {
			mouse_keys[key] = KeyState::Pressed;
		} else if (mouse_keys[key] == KeyState::JustReleased) {
			mouse_keys[key] = KeyState::Released;
		}
	}
}

bool Scene::IsKeyJustPressed(int key) {
	if (!keyboard.contains(key)) {
		return false;
	}
	return keyboard[key] == KeyState::JustPressed;
}

bool Scene::IsKeyJustReleased(int key) {
	if (!keyboard.contains(key)) {
		return false;
	}
	return keyboard[key] == KeyState::JustReleased;
}

bool Scene::IsKeyPressed(int key) {
	if (!keyboard.contains(key)) {
		return false;
	}
	return 	keyboard[key] == KeyState::JustPressed ||
			keyboard[key] == KeyState::Pressed;	
}

qreal Scene::GetDeltaTime() const {
	return delta_time_;
}

Camera* Scene::GetCamera() {
	return camera_;	
}

void Scene::wheelEvent(QWheelEvent* event) {
	int angle = event->angleDelta().y();
	angle /= 8 * 15;
	camera_->ResizeBy(-angle * 5/*const*/);
}

void Scene::SetGameObjectPosition(const QString& name,
	   										const QVector2D& pos)
{
	if (!objects.contains(name)) {
		qDebug() << "Scene::SetGameObjectPosition(...) name doesn't exist";
		return;
	}
	View* view = dynamic_cast<View*>(objects[name]);
	if (!view) {
		qDebug() << "Scene::SetGameObjectPosition(...) object is not View";
		return;
	}
	view->SetPosition(pos);
}

bool Scene::IsOnScene(const QString& name) const {
	return objects.contains(name);
}

void Scene::SetCamera(Camera* camera) {
	delete camera_;
	camera_ = camera;
}

void Scene::DrawBackground(QPainter* painter) const {
	painter->drawPixmap(0, 0, background);
}

void Scene::DeleteObject(const QString& name) {
	if (!IsOnScene(name)) {
		return;
	}
	delete objects[name];
	objects.remove(name);
}

void Scene::mouseMoveEvent(QMouseEvent* event) {
	mouse_position_ = event->localPos();
}

void Scene::mousePressEvent(QMouseEvent* event) {
	if (IsMouseKeyPressed(event->button())) {
		return;
	}
	mouse_keys[event->button()] = KeyState::JustPressed;	
}

void Scene::mouseReleaseEvent(QMouseEvent* event) {
	mouse_keys[event->button()] = KeyState::JustReleased;
}

bool Scene::IsMouseKeyPressed(int key) {
	if (!mouse_keys.contains(key)) {
		return false;
	}
	return  mouse_keys[key] == KeyState::JustPressed ||
			mouse_keys[key] == KeyState::Pressed;	
}

const QPointF& Scene::GetMousePosition() const {
	return mouse_position_;
}

bool Scene::IsMouseKeyJustPressed(int key) {
	if (!mouse_keys.contains(key)) {
		return false;
	}
	return mouse_keys[key] == KeyState::JustPressed;
}

QRect Scene::GetRect() const {
	return QRect(0, 0, window_size_.width(), window_size_.height());
}

void Scene::resizeEvent(QResizeEvent* event) {
	window_size_ = event->size();
}

