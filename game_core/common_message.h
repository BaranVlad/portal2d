#ifndef PORTAL2D_MESSAGE_H_
#define PORTAL2D_MESSAGE_H_

#include <QString>

class Message {
protected:
	QString dest_;
public:
	Message(const QString& dest);
	const QString& GetDest() const;

	virtual ~Message() = default;
};

#endif

