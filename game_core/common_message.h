#ifndef PORTAL2D_COMMON_MESSAGE_H_
#define PORTAL2D_COMMON_MESSAGE_H_

#include <QVariant>

enum class MessageType;

class Message {
private:
	QString dest_;
	MessageType type_;
	QVariantList params_;
public:
	Message();
	Message(const QJsonObject& js);
	Message(const QString& dest, MessageType type);
	Message(const QString& dest, MessageType type, 
											const QVariantList& params);

	const QString& GetDest() const;
	const MessageType& GetType() const;
	const QVariantList& GetParams() const;

	void AddParam(const QVariant& param);

	void ToJsonObject(QJsonObject& js) const;
	void FromJsonObject(const QJsonObject& js);
	
};

#endif

