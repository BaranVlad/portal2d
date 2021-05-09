#ifndef PORTAL2D_BUTTON_H_
#define PORTAL2D_BUTTON_H_

#include "common_message.h"
#include "area_object.h"
#include <QVector>

class Button : public AreaObject {
private:
	Message* press_message_;
	Message* release_message_;
protected:
	bool is_pressed_ = false;
public:
	Button() = delete;
	Button(Scene* scene);
	~Button();

	void SetPressMessage(Message* message);
	void SetReleaseMessage(Message* message);

	void SendPressMessage();
	void SendReleaseMessage();

	virtual void ToJsonObject(QJsonObject& js) const;
	virtual void FromJsonObject(const QJsonObject& js);
};

#endif

