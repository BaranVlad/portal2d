#ifndef PORTAL2D_VIEW_OBJECT_H_
#define PORTAL2D_VIEW_OBJECT_H_

#include <QPainter>
#include <QPointF>

#include "game_object.h"

class Scene;

/* Base class for all classes to be drown */
class View : public GameObject {
protected:
	/* Every view has one point in global coordinates
	 * others points of a children will be a local coordinates 
	 * regarding to position */
	QPointF position_;
public:
	View() = delete;
	View(Scene* scene);

	virtual void Draw(QPainter* painter) const = 0;
	virtual ~View() = default;
};

#endif

