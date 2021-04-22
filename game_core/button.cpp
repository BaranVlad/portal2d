#include "button.h"

#include "scene.h"

Button::Button(Scene* scene) :
	AreaObject(scene)
{
	AddGroup("Target");
}

void Button::SetAction(Message::Type message_type, const QString& dest,
		   								const QVector<void*>& params)
{
	message_type_ = message_type;
	dest_ = dest;
	params_ = params;
}

void Button::SendButtonAction() {
	Message* message = Message::GetMessage(message_type_, dest_, params_);
	scene_->SendTo(message);
}

