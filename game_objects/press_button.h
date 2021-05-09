#ifndef PORTAL2D_PRESS_BUTTON_H_
#define PORTAL2D_PRESS_BUTTON_H_

#include "../game_core/button.h"
#include <QElapsedTimer>

class PressButton : public Button {
private:
	QElapsedTimer release_timer_;
	int release_time_ = -1;
public:
	PressButton() = delete;
	PressButton(Scene* scene);

	virtual void Update();
	virtual void Draw(QPainter* painter) const;

	virtual qreal GetWidth() const;
	virtual qreal GetHeight() const;

	virtual void ToJsonObject(QJsonObject& js) const;
	virtual void FromJsonObject(const QJsonObject& js);
	void SetTimer(int seconds);
};

#endif

