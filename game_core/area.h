#ifndef PROTAL2D_AREA_H_
#define PROTAL2D_AREA_H_

#include <QRectF>
#include <QVector2D>
#include <QString>

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
	void MoveRect(const QVector2D& vec);
	
	AreaObject* GetAreaObject() const;
	const QString& GetName() const;

	bool IsIntersects(const Area& area) const;



	bool MovableIntersect(Area* move_area, const QVector2D& velocity,
		   						QVector2D* offset, Direction& direction);
	bool Sweeping(const QPointF& first, const QPointF& second,
					const QPointF& center, const QVector2D& velocity,
					const QLineF& first_side, Direction first_dir,
				   	const QLineF second_side, Direction second_dir,
					QVector2D* offset, Direction& direction);
		

	QRectF GetGlobalRect() const;
};

#endif

