#include "button.h"

#include "scene.h"

Button::Button(Scene* scene) :
	AreaObject(scene)
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
	press_message_ = message;
}

void Button::SetReleaseMessage(Message* message) {
	release_message_ = message;
}

void Button::SendPressMessage() {
	if (!press_message_) {
		return;
	}
	scene_->SendTo(press_message_);	
}

void Button::SendReleaseMessage() {
	if (!release_message_) {
		return;
	}
	scene_->SendTo(release_message_);	
}

void Button::ToJsonObject(QJsonObject& js) const {
	AreaObject::ToJsonObject(js);
	
}

void Button::FromJsonObject(const QJsonObject& js) {
	AreaObject::FromJsonObject(js);
}


