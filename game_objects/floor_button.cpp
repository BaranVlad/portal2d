#include "floor_button.h"

#include <QtGlobal>
#include <QDebug>

#include "player.h"
#include "../game_core/scene.h"

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
		if (dynamic_cast<Player*>(area->GetAreaObject())) {
			qDebug() << "pressed!";
			if (!is_pressed_) {
				SendButtonAction();
			}
			pressed_now = true;
		}
	}
	is_pressed_ = pressed_now;
}

void FloorButton::Draw(QPainter* painter) const {
	painter->setBrush(Qt::red);
	painter->drawRect(GetAreasViaGroupName("Target")[0]->GetGlobalRect());
}

