#include "wall_map_add_to_group_message.h"

WallMapAddToGroupMessage::WallMapAddToGroupMessage(const QString& dest,
		   							const QString& group_name, Wall* wall) :
	Message(dest),
	group_name_(group_name),
	wall_(wall)
{}

const QString& WallMapAddToGroupMessage::GetGroupName() const {
	return group_name_;	
}

Wall* WallMapAddToGroupMessage::GetWall() const {
	return wall_;
}


