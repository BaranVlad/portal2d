#ifndef PORTAL2D_VIEW_OBJECT_H_
#define PORTAL2D_VIEW_OBJECT_H_

#include <QPainter>
#include <QVector2D>
#include <QtGlobal>

#include "game_object.h"

class Scene;

/* Base class for all classes to be drown */
class View : public GameObject {
protected:
	/* Every view has one point in global coordinates
	 * others points of a children will be a local coordinates 
	 * regarding to position */
	QVector2D position_;
public:
	View() = delete;
	View(Scene* scene);

	virtual void SetPosition(const QVector2D& position);
	virtual void SetPosition(qreal x, qreal y);
	void Move(const QVector2D& offset);
	QVector2D GetPosition() const;

	virtual void Draw(QPainter* painter) const = 0;
	virtual ~View() = default;
};

#endif

