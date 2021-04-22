#ifndef WALL_MAPP_ADD_TO_GROUP_MESSAGE_H_
#define WALL_MAPP_ADD_TO_GROUP_MESSAGE_H_

#include "../game_core/common_message.h"
#include "../wall_mechanics/wall.h"

class WallMapAddToGroupMessage : public Message {
private:
	QString group_name_;
	Wall* wall_;
public:
	WallMapAddToGroupMessage(const QString& dest, 
			const QString& group_name, Wall* wall);
	WallMapAddToGroupMessage(const QString& dest,
		   									const QVector<void*> params);
	const QString& GetGroupName() const;
	Wall* GetWall() const;
};

#endif

