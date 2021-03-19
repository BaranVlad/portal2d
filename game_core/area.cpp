#include "area.h"

#include "area_object.h"

Area::Area(const QString& name, 
			const QRectF& rect_area, 
			AreaObject* area_object) : 
	area_object_(area_object),
	rect_area_(rect_area),
	name_(name)
{}

bool Area::IsActive() const {
	return is_active_;
}

void Area::SetActive(bool value) {
	is_active_ = value;
}

bool Area::IsIntersects(const Area& area) const {
	if (!is_active_ || !area.is_active_) {
		return false;
	}
	if (area_object_ == area.area_object_) {
		return false;
	}

	QRectF global_rect1 = GetGlobalRect();
	QRectF global_rect2 = area.GetGlobalRect();

	return global_rect1.intersects(global_rect2);
}

void Area::SetRect(const QRectF& rect_area) {
	rect_area_ = rect_area;	
}

AreaObject* Area::GetAreaObject() const {
	return area_object_;
}

const QString& Area::GetName() const {
	return name_;
}

Direction Area::IsIntersectsMovable(const Area& area_old,
		   							const Area& area_new) const
{}

QRectF Area::GetGlobalRect() const {
	QRectF global_rect = rect_area_;
	QVector2D position = area_object_->GetPosition();
	QPointF move_position(position.x(), position.y());
	global_rect.moveTo(rect_area_.topLeft() + move_position);

	return global_rect;
}
