#ifndef PORTAL2D_WALL_MAP_MESSAGE_H_
#define PORTAL2D_WALL_MAP_MESSAGE_H_

#include "../game_core/common_message.h"

/* This mesasge contain information about name of wall_map group
 * that must be changed */
class WallMapMessage : public Message {
private:
	QString group_name_;
public:
	WallMapMessage(const QString& dest, const QString& group_name);
	WallMapMessage(const QString& dest, const QVector<void*>& params);

	const QString& GetGroupName() const;
};

#endif

