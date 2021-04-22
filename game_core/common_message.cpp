#include "common_message.h"

#include "../messages/wall_map_message.h"
#include "../messages/wall_map_add_message.h"
#include "../messages/wall_map_add_to_group_message.h"

Message::Message(const QString& dest) :
	dest_(dest)	
{}

const QString& Message::GetDest() const {
	return dest_;	
}

Message* Message::GetMessage(Type type, const QString& dest,
							const QVector<void*>& params)
{
	switch (type) {
		case wall_map_message:
			return new WallMapMessage(dest, params);
		case wall_map_add_message:
			return new WallMapAddMessage(dest, params);
		case wall_map_add_to_group_message:
			return new WallMapAddToGroupMessage(dest, params);
	}
	return nullptr;
}

