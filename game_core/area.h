#ifndef PROTAL2D_AREA_H_
#define PROTAL2D_AREA_H_

#include <QRectF>
#include <QVector>

class AreaObject;
enum class Direction;

/* This class are used by AreaObject to manage intersections */
class Area {
private:
	AreaObject* area_object_;
	QRectF rect_area_;	
	
	QString name_;
	bool is_active_;
public:
	Area() = delete;
	Area(const QString& name,
		   	const QRectF& rect_area, AreaObject* area_object);

	bool IsActive() const;
	void SetActive(bool value);

	void SetRect(const QRectF& rect_area);
	
	AreaObject* GetAreaObject() const;
	const QString& GetName() const;

	bool IsIntersects(const Area& area) const;
	Direction IsIntersectsMovable(const Area& area_old,
		   							const Area& area_new) const;

	QRectF GetGlobalRect() const;
};

#endif

