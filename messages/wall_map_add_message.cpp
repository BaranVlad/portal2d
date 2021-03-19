#include "wall_map_add_message.h"

WallMapAddMessage::WallMapAddMessage(const QString dest, Wall* wall) :
	Message(dest),
	wall_(wall)
{}

Wall* WallMapAddMessage::GetWall() const {
	return wall_;
}
