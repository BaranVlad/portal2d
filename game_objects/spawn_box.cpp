#include "spawn_box.h"

#include "../game_core/consts.h"
#include "../game_core/scene.h"
#include "box.h"

SpawnBox::SpawnBox(Scene* scene) :
	View(scene),
	box_rect(0, 0, BOX_SIZE, BOX_SIZE)
{}

void SpawnBox::Update() {}

void SpawnBox::Draw(QPainter* painter) const {
	painter->setPen(QPen(Qt::black, 2));
	painter->setBrush(QColor(200, 200, 200, 10));

	QRectF new_rect(box_rect);
	new_rect.moveTopLeft(new_rect.topLeft() + GetPosition().toPointF());
	painter->drawRect(new_rect);
}

qreal SpawnBox::GetWidth() const {
	return BOX_SIZE;
}

qreal SpawnBox::GetHeight() const {
	return BOX_SIZE;
}

void SpawnBox::TakeMessage(Message* message) {
	if (message->GetType() == MessageType::SpawnBox) {
		CreateBox();
	}
}

void SpawnBox::CreateBox() {
	if (box_) {
		scene_->DeleteObject(box_->GetName());
	}
	Box* box = new Box(scene_);
	box->SetPosition(GetPosition());
	scene_->AddGameObject(name_ + "_box", box);
	box_ = box;
}

void SpawnBox::ToJsonObject(QJsonObject& js) const {
	View::ToJsonObject(js);
	js["class"] = "SpawnBox";
}

void SpawnBox::FromJsonObject(const QJsonObject& js) {
	View::FromJsonObject(js);
}

