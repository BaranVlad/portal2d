#include "wall_map.h"

#include <QPointF>
#include <QDebug>

#include "../game_core/area.h"
#include "../game_core/common_message.h"
#include "straight_wall.h"

WallMap::WallMap(Scene* scene) :
	CollideObject(scene)
{
	position_ = QVector2D(0, 0);
	AddGroup("Common");
}

void WallMap::TakeMessage(Message* msg) {
	if (msg->GetType() == MessageType::WallSwitch) {
		SwitchGroup(msg->GetParams()[0].toString());
	}
}

void WallMap::AddWallToGroup(const QString& name, Wall* wall) {
	if (!groups_.contains(name)) {
		qDebug() << "WallMap::AddWallToGroup(..) error: name doesn't exist";
	}
	groups_[name].push_back(wall);
	for (Area* area : wall->GetAreas()) {
		AddAreaToGroup(area->GetName(), area);
	}
}

QList<Wall*> WallMap::GetWalls() const {
	QList<Wall*> result;
	for (auto& vec : groups_.values()) {
		for (Wall* wall : vec) {
			result.push_back(wall);
		}	
	}
	return result;
}

void WallMap::AddWall(Wall* wall) {
	AddWallToGroup("Common", wall);
}

void WallMap::AddWallGroup(const QString& name) {
	groups_[name];
}

WallMap::~WallMap() {
	ClearAll();
	for (auto& vec : groups_.values()) {
		for (Wall* wall : vec) {
			delete wall;
		}
	}
}

void WallMap::SwitchGroup(const QString& name) {
	for (Wall* wall : groups_[name]) {
		wall->ChangeState();
	}	
}

bool WallMap::IsGroupExist(const QString& name) {
	return groups_.contains(name);
}

void WallMap::Update() {
	for (Wall* wall : GetWalls()) {
		wall->Update();	
	}
}

void WallMap::Draw(QPainter* painter) const {
	for (Wall* wall : GetWalls()) {
		wall->Draw(painter);
	}
}

qreal WallMap::GetWidth() const {
	return 0;
}

qreal WallMap::GetHeight() const {
	return 0;
}

void WallMap::ToJsonObject(QJsonObject& js) const {
	View::ToJsonObject(js);

	QJsonObject walls_obj;
	for (QString& key : groups_.keys()) {
		QJsonArray walls_array;
		for (Wall* wall : groups_[key])  {
			QJsonObject wall_obj;
			wall->ToJsonObject(wall_obj);
			walls_array.push_back(wall_obj);
		}
		walls_obj[key] = walls_array;
	}
	js["class"] = "WallMap";
	js["groups"] = walls_obj;
}

void WallMap::FromJsonObject(const QJsonObject& js) {
	View::FromJsonObject(js);

	StraightWall* wall;
	QJsonObject groups_obj = js["groups"].toObject();
	for (QString& group_key : groups_obj.keys()) {
		for (QJsonValueRef wall_val : groups_obj[group_key].toArray()) {
			wall = new StraightWall(scene_);
			wall->FromJsonObject(wall_val.toObject());
			AddWallToGroup(group_key, wall);
		}
	}
}


