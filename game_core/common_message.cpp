#include "common_message.h"

#include <QJsonObject>
#include <QJsonArray>
#include "game_object.h"

Message::Message(const QJsonObject& js) {
	FromJsonObject(js);
}

Message::Message() {
	type_ = MessageType::Empty;
}

Message::Message(const QString& dest, MessageType type, 
											const QVariantList& params) :
	dest_(dest),
	type_(type),
	params_(params)
{}

Message::Message(const QString& dest, MessageType type) :
	dest_(dest),
	type_(type)
{}

void Message::ToJsonObject(QJsonObject& js) const {
	js["dest"] = dest_;
	js["type"] = static_cast<int>(type_);
	js["params"] = QJsonArray::fromVariantList(params_);
}

void Message::FromJsonObject(const QJsonObject& js) {
	dest_ = js["dest"].toString();	
	type_ = static_cast<MessageType>(js["type"].toInt());
	params_ = js["params"].toArray().toVariantList();
}

const QString& Message::GetDest() const {
	return dest_;
}

const MessageType& Message::GetType() const {
	return type_;
}

const QVariantList& Message::GetParams() const {
	return params_;
}

void Message::AddParam(const QVariant& param) {
	params_.push_back(param);
}

