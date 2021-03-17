#ifndef PROTAL2D_AREA_H_
#define PROTAL2D_AREA_H_

#include <QRectF>
#include <QVector>

class AreaObject;

/* This class are used by AreaObject to manage intersections */
class Area {
private:
	AreaObject* area_object_;
	QRectF rect_area_;	
	QVector<Area*> intersects_with_;
	
	QString name_;
	bool is_active_;
public:
	Area() = delete;
	Area(const QString& name,
		   	const QRectF& rect_area, AreaObject* area_object);

	void ClearIntersects();
	void AddIntersect(Area* area);
	int IntersectsSize() const;

	bool IsActive() const;
	void SetActive(bool value);

	void SetRect(const QRectF& rect_area);
	
	AreaObject* GetAreaObject() const;

	bool IsIntersects(const Area& area) const;

	Area* operator[](int index);
};

#endif

