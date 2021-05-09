#include "finish_area.h"

#include "../game_core/consts.h"
#include "qnamespace.h"

FinishArea::FinishArea(Scene* scene) :
	AreaObject(scene)
{
	finish_rect_ = QRectF(0, 0, FINISH_AREA_SIZE, FINISH_AREA_SIZE);
	AddAreaToGroup("Trigger", finish_rect_);
}

void FinishArea::Draw(QPainter* painter) const {
	painter->setPen(QPen(Qt::darkGreen, 3));
	painter->setBrush(Qt::green);
	
	painter->drawRect(finish_rect_.translated(GetPosition().toPointF()));
}


void FinishArea::ToJsonObject(QJsonObject& js) const {
	AreaObject::ToJsonObject(js);
	js["class"] = "FinishArea";
}

void FinishArea::FromJsonObject(const QJsonObject& js) {
	AreaObject::FromJsonObject(js);
	finish_rect_ = GetAreasViaGroupName("Trigger")[0]->GetRect();
}

void FinishArea::Update() {}

qreal FinishArea::GetWidth() const {
	return FINISH_AREA_SIZE;
}

qreal FinishArea::GetHeight() const {
	return FINISH_AREA_SIZE;
}

FinishArea::~FinishArea() {}

