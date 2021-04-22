#include "wall_map_add_message.h"

WallMapAddMessage::WallMapAddMessage(const QString dest, Wall* wall) :
	Message(dest),
	wall_(wall)
{}

WallMapAddMessage::WallMapAddMessage(const QString dest,
	   									const QVector<void*>& params) :
	Message(dest),
	wall_((Wall*)params[0])
{}

Wall* WallMapAddMessage::GetWall() const {
	return wall_;
}
