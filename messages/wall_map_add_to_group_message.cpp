#include "wall_map_add_to_group_message.h"

WallMapAddToGroupMessage::WallMapAddToGroupMessage(const QString& dest,
		   							const QString& group_name, Wall* wall) :
	Message(dest),
	group_name_(group_name),
	wall_(wall)
{}

WallMapAddToGroupMessage::WallMapAddToGroupMessage(const QString& dest,
		   									const QVector<void*> params) :
	Message(dest),
	group_name_(*(QString*)params[0]),
	wall_((Wall*)params[1])
{}

const QString& WallMapAddToGroupMessage::GetGroupName() const {
	return group_name_;	
}

Wall* WallMapAddToGroupMessage::GetWall() const {
	return wall_;
}

