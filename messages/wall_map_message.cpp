#include "wall_map_message.h"

WallMapMessage::WallMapMessage(const QString& dest, 
								const QString& group_name) :
	Message(dest),
	group_name_(group_name)
{}

WallMapMessage::WallMapMessage(const QString& dest,
	   							const QVector<void*>& params) :
	Message(dest),
	group_name_(*(QString*)params[0])
{}

const QString& WallMapMessage::GetGroupName() const {
	return group_name_;
}

