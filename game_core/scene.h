#ifndef PORTAL2D_SCENE_H_
#define PORTAL2D_SCENE_H_

#include <QObject>
#include <QWidget>
#include <QMap>
#include <QPainter>
#include <QDebug>

#include "game_object.h"
#include "area_object.h"
#include "view.h"
#include "area.h"

#include <QList>

/* This class contains all objects in game,
 * and provide their updating and drawing */
class Scene : public QObject {
	Q_OBJECT
private:
	/* Every object has own string id. This is need to 
	 * send messages between objects */
	QMap<QString, GameObject*> objects;
public:
	Scene(QObject* parent = nullptr);
	~Scene();

	void Draw(QPainter* painter) const;
	void Update();
	void SendTo(const QString& name, Message* message);
	void AddGameObject(const QString& name, GameObject* game_object);

	/* Fill area_obj's areas by only those which intersects */
	QList<Area*> GetIntersected(Area* area);
	
};

#endif


