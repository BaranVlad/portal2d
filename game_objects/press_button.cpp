#include "press_button.h"

#include "../game_core/consts.h"
#include "../game_core/scene.h"

#include "player.h"
#include "qglobal.h"
#include "qnamespace.h"

PressButton::PressButton(Scene* scene) :
	Button(scene) 
{
	QRectF press_rect(0, 0, 
						GetWidth(), GetHeight());
	AddAreaToGroup("Target", press_rect);
}

qreal PressButton::GetWidth() const {
	return PRESS_BUTTON_COLUMN_WIDTH;
}

qreal PressButton::GetHeight() const {
	return PRESS_BUTTON_HEIGHT + PRESS_BUTTON_COLUMN_HEIGHT;
}

void PressButton::Update() {
	QList<Area*> list =
	   		scene_->GetIntersected(GetAreasViaGroupName("Target")[0]);
	Player* player;
	if (release_timer_.isValid() &&
		   	release_timer_.hasExpired(release_time_)) 
	{
		is_pressed_ = false;
		release_timer_.invalidate();
		SendReleaseMessage();
	}
	for (Area* area : list) {
		player = dynamic_cast<Player*>(area->GetAreaObject());
		if (player && scene_->IsKeyJustPressed(Qt::Key_E) 
													&& !is_pressed_) 
		{
			SendPressMessage();
			is_pressed_ = true;
			if (release_time_ != 0) {
				release_timer_.start();
			}
		}
	}
}

void PressButton::Draw(QPainter* painter) const {
	QVector2D position = GetPosition();
	painter->setPen(QPen(Qt::darkRed, 2));
	painter->setBrush(Qt::red);
	if (!is_pressed_) {
		painter->drawRect(
				position.x() + 
				(PRESS_BUTTON_COLUMN_WIDTH - PRESS_BUTTON_WIDTH) / 2.,
				position.y(), PRESS_BUTTON_WIDTH, PRESS_BUTTON_HEIGHT
		);
	} else {
		painter->drawRect(
				position.x() + 
				(PRESS_BUTTON_COLUMN_WIDTH - PRESS_BUTTON_WIDTH) / 2.,
				position.y() + PRESS_BUTTON_HEIGHT - 3, 
				PRESS_BUTTON_WIDTH, PRESS_BUTTON_HEIGHT
		);
	}
	painter->setPen(QPen(Qt::black, 2));
	painter->setBrush(Qt::lightGray);

	painter->drawRect(position.x(), position.y() + PRESS_BUTTON_HEIGHT,
			PRESS_BUTTON_COLUMN_WIDTH, PRESS_BUTTON_COLUMN_HEIGHT);
}

void PressButton::ToJsonObject(QJsonObject& js) const {
	Button::ToJsonObject(js);
	js["class"] = "PressButton";
	js["release_time"] = release_time_;
}

void PressButton::FromJsonObject(const QJsonObject& js) {
	Button::FromJsonObject(js);
	release_time_ = js["release_time"].toInt(-1);
}

void PressButton::SetTimer(int seconds) {
	release_time_ = seconds * 1000;
}

