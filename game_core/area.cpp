#include "area.h"

#include "area_object.h"

Area::Area(const QString& name, 
			const QRectF& rect_area, 
			AreaObject* area_object) : 
	rect_area_(rect_area),
	area_object_(area_object),
	name_(name)
{}

void Area::ClearIntersects() {
	intersects_with_.clear();
}

void Area::AddIntersect(Area* area) {
	intersects_with_.push_back(area);
}

bool Area::IsActive() const {
	return is_active_;
}

void Area::SetActive(bool value) {
	is_active_ = is_active;
}

Area* operator[](int index) {
	return intersects_with_[index];
}

int Area::IntersectsSize() const {
	return intersects_with_.size();	
}

bool Area::IsIntersects(const Area& area) const {
	if (!is_active || !area.is_active) {
		return false;
	}

	QRectF global_rect1 =
	   	rect_area_.moveTo(rect_area_.topLeft() + 
						area_object->GetPosition());
	QRectF global_rect2 =
	   	area.rect_area_.moveTo(area.rect_area_.topLeft() +
					area.area_object->GetPosition());

	return global_rect1.intersects(global_rect2);
}

void Area::SetRect(const QRectF& rect_area) {
	rect_area_ = rect_area;	
}

AreaObject* Area::GetAreaObject() const {
	return area_object_;
}

