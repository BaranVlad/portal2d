#include "message.h"

Message::Message(const QString& dest) :
	dest_(dest)	
{}

const QString& Message::GetDest() const {
	return dest_;	
}

