#include "floor_button.h"

#include <QtGlobal>
#include <QDebug>

#include "player.h"
#include "../game_core/scene.h"
#include "box.h"

FloorButton::FloorButton(Scene* scene) :
	Button(scene)
{
	QRectF target_rect(0, 0, BUTTON_WIDTH, BUTTON_HEIGHT);
	AddAreaToGroup("Target", target_rect);
}

void FloorButton::Update() {
	bool pressed_now = false;
	for (Area* area :
	   		scene_->GetIntersected(GetAreasViaGroupName("Target")[0])) 
	{
		if (dynamic_cast<Player*>(area->GetAreaObject()) ||
			dynamic_cast<Box*>(area->GetAreaObject())) 
		{
			qDebug() << "pressed!";
			if (!is_pressed_) {
				SendPressMessage();
			}
			pressed_now = true;
		}
	}
	if (!pressed_now && is_pressed_) {
		SendReleaseMessage();
	}
	is_pressed_ = pressed_now;
}

void FloorButton::Draw(QPainter* painter) const {
	QRectF draw_rect = GetAreasViaGroupName("Target")[0]->GetGlobalRect();
	painter->setBrush(Qt::red);
	if (is_pressed_) {
		draw_rect.setY(draw_rect.y() +
							BUTTON_HEIGHT - BUTTON_PRESSED_HEIGHT);
	}
	painter->drawRect(draw_rect);
}

qreal FloorButton::GetWidth() const {
	return BUTTON_WIDTH;
}

qreal FloorButton::GetHeight() const {
	return BUTTON_HEIGHT;
}

void FloorButton::ToJsonObject(QJsonObject& js) const {
	Button::ToJsonObject(js);
	js["class"] = "FloorButton";
}

void FloorButton::FromJsonObject(const QJsonObject& js) {
	Button::FromJsonObject(js);
}

