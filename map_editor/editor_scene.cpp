#include "editor_scene.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QFile>

#include "../game_core/game_object.h"

EditorScene::EditorScene(QObject* parent) :
	Scene(parent)
{}

void EditorScene::Update(qreal delta_time) {}

void EditorScene::SaveMapToJson(const QString& file_name) const {
	QJsonObject json_object;
	for (auto& object_str : objects.keys()) {
		json_object[object_str] = objects[object_str]->ToJsonObject();
	}
	QJsonDocument document(json_object);	
	QFile file(file_name);
	file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
	file.write(document.toJson());
	file.close();
}

