#ifndef PORTAL2D_SPAWN_BOX_MESSAGE_H_
#define PORTAL2D_SPAWN_BOX_MESSAGE_H_

#include "../game_core/common_message.h"

class SpawnBoxMessage : public Message {
public:
	SpawnBoxMessage(const QString& name);
};


#endif

