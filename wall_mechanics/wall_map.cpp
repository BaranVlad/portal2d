#include "wall_map.h"

#include <QPointF>
#include <QDebug>

#include "../game_core/area.h"
#include "../messages/wall_map_message.h"
#include "../messages/wall_map_add_message.h"
#include "../messages/wall_map_add_to_group_message.h"

WallMap::WallMap(Scene* scene) :
	CollideObject(scene)
{
	position_ = QVector2D(0, 0);
	AddGroup("Common");
}

void WallMap::TakeMessage(Message* msg) {
	WallMapMessage* wall_msg = dynamic_cast<WallMapMessage*>(msg);
	WallMapAddMessage* wall_add_msg = 
							dynamic_cast<WallMapAddMessage*>(msg);
	WallMapAddToGroupMessage* add_to_group_msg = 
					dynamic_cast<WallMapAddToGroupMessage*>(msg);

	if (wall_msg) {
		SwitchGroup(wall_msg->GetGroupName());
	} else if (wall_add_msg) {
		AddWall(wall_add_msg->GetWall());
	} else if (add_to_group_msg) {
		QString group_name = add_to_group_msg->GetGroupName();
		if (!IsGroupExist(group_name)) {
			AddGroup(group_name);	
		}
		AddWallToGroup(group_name, add_to_group_msg->GetWall());
	}
	delete msg;
}

void WallMap::AddWallToGroup(const QString& name, Wall* wall) {
	if (!groups_.contains(name)) {
		qDebug() << "WallMap::AddWallToGroup(...) error: name doesn't exist";
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

