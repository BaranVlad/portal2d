#include "button.h"

#include "scene.h"

Button::Button(Scene* scene) :
	AreaObject(scene),
	press_message_(new Message),
	release_message_(new Message)
{
	AddGroup("Target");
}

Button::~Button() {
	if (press_message_) {
		delete press_message_;
	}
	if (release_message_) {
		delete release_message_;
	}
}

void Button::SetPressMessage(Message* message) {
	if (press_message_) {
		delete press_message_;
	}
	press_message_ = message;
}

void Button::SetReleaseMessage(Message* message) {
	if (release_message_) {
		delete release_message_;
	}
	release_message_ = message;
}

void Button::SendPressMessage() {
	if (press_message_->GetType() != MessageType::Empty) {
		scene_->SendTo(press_message_);	
	}
}

void Button::SendReleaseMessage() {
	if (release_message_->GetType() != MessageType::Empty) {
		scene_->SendTo(release_message_);	
	}
}

void Button::ToJsonObject(QJsonObject& js) const {
	AreaObject::ToJsonObject(js);
	QJsonObject msg1;
	QJsonObject msg2;

	press_message_->ToJsonObject(msg1);
	release_message_->ToJsonObject(msg2);

	js["press_message"] = msg1;
	js["release_message"] = msg2;
}

void Button::FromJsonObject(const QJsonObject& js) {
	AreaObject::FromJsonObject(js);
	
	SetPressMessage(new Message(js["press_message"].toObject()));
	SetReleaseMessage(new Message(js["release_message"].toObject()));
}

