#ifndef PORTAL2D_SCENE_H_
#define PORTAL2D_SCENE_H_

#include <QObject>
#include <QWidget>
#include <QVector>
#include <QPainter>

#include "game_object.h"
#include "area_object.h"
#include "view.h"
#include "area.h"

/* This class contains all objects in game,
 * and provide their updating and drawing */
class Scene : public QObject {
	Q_OBJECT
private:
	QVector<GameObject*> objects;
public:
	Scene(QObject* parent = nullptr);
	~Scene();

	void Draw(QPainter* painter) const;
	void Update();

	/* Fill area_obj's areas by obly those which intersects */
	void GetIntersected(AreaObject* area);
	
};

#endif


