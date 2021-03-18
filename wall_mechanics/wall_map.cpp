#include "wall_map.h"

#include <QPointF>
#include <QDebug>

#include "../game_core/area.h"
#include "../game_core/message.h"
#include "../messages/wall_map_message.h"

WallMap::WallMap(Scene* scene) :
	CollideObject(scene)
{
	position_ = QPointF(0, 0);
	AddGroup("Common");
}

void WallMap::TakeMessage(Message* msg) {
	WallMapMessage* wall_msg = dynamic_cast<WallMapMessage*>(msg);
	if (!wall_msg) {
		qDebug() << "WallMap::TakeMessage(...) error: bad type of message";
	}

	SwitchGroup(wall_msg->GetGroupName());
	
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

QList<Walls*> WallMap::GetWalls() const {
			
}

void WallMap::AddWall(Wall* wall) {
	AddWallToGroup("Common", wall);
}

void WallMap::AddWallGroup(const QString& name) {
	groups_[name];
}

WallMap::~WallMap() {
	for (Wall* wall : groups_.values()) {
		delete wall;
	}
}

void WallMap::SwitchGroup(const QString& name) {
	for (Wall* wall : groups_[name]) {
		wall->ChangeState();
	}	
}

