#ifndef PORTAL2D_MESSAGE_H_
#define PORTAL2D_MESSAGE_H_

#include <QString>
#include <QVector>

class Message {
protected:
	QString dest_;
public:
	enum Type { wall_map_message,
	   			wall_map_add_message, 
				wall_map_add_to_group_message };

	Message(const QString& dest);
	const QString& GetDest() const;

	static Message* GetMessage(Type type, const QString& dest,
							const QVector<void*>& params);

	virtual ~Message() = default;
};

#endif

