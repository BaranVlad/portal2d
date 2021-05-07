#include "scene.h"

#include "area.h"
#include "common_message.h"
#include "collide_object.h"
#include "camera.h"
#include "view.h"
#include "../wall_mechanics/straight_wall.h"
#include "../wall_mechanics/wall_map.h"
#include "../game_objects/box.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

Scene::Scene(QObject* parent) :
	QObject(parent),
	camera_(new Camera(this)),
	background(":background.png")
{}

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
	PostUpdate();
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

void Scene::ForceSend(Message* message) {
	objects[message->GetDest()]->TakeMessage(message);
}

void Scene::ForceAdd(GameObject* game_object) {
	QString name = game_object->GetName();
	if (objects.contains(name)) {
		qDebug() << "Scene::AddGameObject(...) error: object with name " 
				<< name << " already exist";
		return;
	}
	game_object->SetName(name);
	objects[name] = game_object;	
}

bool Scene::GetMovableIntersects(Area* move_area, 
		const QVector2D& velocity, QVector2D* offset, 
							QList<Area*>& areas, Direction& direction) 
{
	areas = GetIntersected(move_area);
	QVector2D temp_offset;
	Direction temp_direction;
	bool has_offset = false;
	bool is_collide = false;
	for (Area* area : GetAllAreas()) {
		if (area == move_area || !area->IsActive()) {
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
		if (!area_object) {
			continue;
		}
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

void Scene::ForceDelete(const QString& name) {
	if (!IsOnScene(name)) {
		return;
	}
	delete objects[name];
	objects.remove(name);
}

void Scene::mouseMoveEvent(QMouseEvent* event) {
	mouse_position_ = event->localPos();
	mouse_position_ = camera_->PointToCurrent(mouse_position_);
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
	camera_->resizeEvent(event);
}

bool Scene::GetWallLineIntersect(const QLineF& line,
				QVector2D* intersect_point, StraightWall** res_wall)
{
	QVector2D res_point(line.p2());
	QPointF temp_point;
	StraightWall* s_wall;
	bool is_intersection = false;
	for (Wall* wall : GetAllWalls()) {
		s_wall = dynamic_cast<StraightWall*>(wall);
		if (!s_wall) {
			continue;
		}
		if (!s_wall->IsActive()) {
			continue;
		}
		if (line.intersect(s_wall->GetLine(), &temp_point) == 
					QLineF::BoundedIntersection) 
		{
			if ((res_point - QVector2D(line.p1())).length() >
			   (QVector2D(temp_point) - QVector2D(line.p1())).length()) 
			{	
				res_point = QVector2D(temp_point);
				*res_wall = s_wall;
			}
			is_intersection = true;
		}
	}
	*intersect_point = res_point;
	return is_intersection;
}

QList<Wall*> Scene::GetAllWalls() {
	WallMap* wall_map = dynamic_cast<WallMap*>(objects["WallMap"]);
	return wall_map->GetWalls();
}

void Scene::DeleteUpdate() {
	while (!to_delete.empty()) {
		ForceDelete(to_delete.back()->GetName());		
		to_delete.pop_back();
	}
}

void Scene::AddUpdate() {
	while (!to_add.empty()) {
		ForceAdd(to_add.back());		
		to_add.pop_back();
	}
}

void Scene::MessageUpdate() {
	while (!to_send.empty()) {
		ForceSend(to_send.back());		
		to_send.pop_back();
	}
}

void Scene::DeleteObject(const QString& name) {
	to_delete.push_back(objects[name]);
}

void Scene::AddGameObject(const QString& name, GameObject* game_object) {
	game_object->SetName(name);
	to_add.push_back(game_object);
}

void Scene::PostUpdate() {
	DeleteUpdate();	
	AddUpdate();
	MessageUpdate();
	KeysUpdate();
}

void Scene::SendTo(Message* message) {
	to_send.push_back(message);
}

GameObject* Scene::GetObject(const QString& str) const {
	return objects[str];
}

void Scene::WriteToJson(const QString& file_name) const {
	QFile json_file("levels/" +  file_name);
	json_file.open(QIODevice::WriteOnly | QIODevice::Text);

	QJsonArray scene_array;
	for (GameObject* object : objects.values()) {
		QJsonObject json_object;
		object->ToJsonObject(json_object);
		scene_array.push_back(QJsonValue(json_object));
	}

	QJsonDocument document;
	document.setArray(scene_array);
	json_file.write(document.toJson());
	json_file.close();
}

void Scene::ReadFromJson(const QString& file_name) {

}

QList<Box*> Scene::GetBoxes() {
	QList<Box*> boxes;
	for (QString& key : objects.keys()) {
		Box* box = dynamic_cast<Box*>(objects[key]);
		if (box) {
			boxes.push_back(box);
		}
	}
	return boxes;
}

