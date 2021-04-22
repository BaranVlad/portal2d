#ifndef PORTAL2D_AREA_H_
#define PORTAL2D_AREA_H_

#include <QRectF>
#include <QVector2D>
#include <QString>

#include "game_object.h"

class AreaObject;
enum class Direction;

/* This class are used by AreaObject to manage intersections */
class Area : public GameObject {
private:
	AreaObject* area_object_;
	QRectF rect_area_;	
	
	QString name_;
	bool is_active_;
public:
	Area() = delete;
	Area(const QString& name,
		   	const QRectF& rect_area, AreaObject* area_object);

	virtual void Update();

	bool IsActive() const;
	void SetActive(bool value);

	void SetRect(const QRectF& rect_area);
	void MoveRect(const QVector2D& vec);
	
	AreaObject* GetAreaObject() const;
	const QString& GetName() const;

	bool IsIntersects(const Area& area) const;

	// scene use this function to know when movable object intersects 
	// with other area. Return true if objects collides
	bool MovableIntersect(Area* move_area, const QVector2D& velocity,
		   						QVector2D* offset, Direction& direction);
	// This function is used for colliding movable object
	bool Sweeping(const QPointF& first, const QPointF& second,
					const QPointF& center, const QVector2D& velocity,
					const QLineF& first_side, Direction first_dir,
				   	const QLineF& second_side, Direction second_dir,
					QVector2D* offset, Direction& direction);
	bool IsPointBetweenTwoLines(const QLineF& first,
								const QLineF& second, 
								const QPointF& i_point);
	//This functions is used for only straight move intersection
	bool StraightMoveIntersect(const QPointF& first, const QPointF& second,
								const QLineF& side, Direction side_dir,
								const QVector2D& velocity, 
								QVector2D* offset, Direction& direction);
	qreal GetPointSign(const QLineF& line, const QPointF& point) const;
	bool IsLinesEqual(const QLineF& first, const QLineF& second);
		

	QRectF GetGlobalRect() const;
	
};

#endif

