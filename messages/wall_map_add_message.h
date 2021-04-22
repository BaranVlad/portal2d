#ifndef PORTAL2D_WALL_MAP_ADD_MESSAGE_H_
#define PORTAL2D_WALL_MAP_ADD_MESSAGE_H_

#include "../game_core/common_message.h"
#include "../wall_mechanics/wall.h"

/* This mesasge contain information about name of wall_map group
 * that must be changed */
class WallMapAddMessage : public Message {
private:
	Wall* wall_;
public:
	WallMapAddMessage(const QString dest, Wall* wall);
	WallMapAddMessage(const QString dest, const QVector<void*>& params);
	Wall* GetWall() const;
};

#endif

