#include "wall_map_message.h"

WallMapMessage::WallMapMessage(const QString& dest_, 
								const QString& group_name) :
	Message(dest),
	group_name_(group_name_)	
{}

const QString& WallMapMessage::GetGroupName() const {
	return group_name_;
}

