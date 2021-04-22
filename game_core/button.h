#ifndef PORTAL2D_BUTTON_H_
#define PORTAL2D_BUTTON_H_

#include "common_message.h"
#include "area_object.h"
#include <QVector>

class Button : public AreaObject {
private:
	QVector<void*> params_;
	QString dest_;
	Message::Type message_type_;
protected:
	bool is_pressed_ = false;
public:
	Button() = delete;
	Button(Scene* scene);

	void SetAction(Message::Type message_type, const QString& dest_,
		   								const QVector<void*>& params);
	void SendButtonAction();
};

#endif

