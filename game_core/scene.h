#ifndef PORTAL2D_SCENE_H_
#define PORTAL2D_SCENE_H_

#include <QObject>
#include <QWidget>
#include <QMap>
#include <QPainter>
#include <QDebug>

#include "collide_object.h"

#define KEYS_COUNT 255

#include <QList>

/* This class contains all objects in game,
 * and provide their updating and drawing */
class Scene : public QObject {
	Q_OBJECT
private:
	/* Every object has own string id. This is need to 
	 * send messages between objects */
	enum class KeyState { JustPressed, Pressed, JustReleased, Released };
	
	QMap<QString, GameObject*> objects;
	KeyState key_pressed_[KEYS_COUNT];
public:

	Scene(QObject* parent = nullptr);
	~Scene();

	void Draw(QPainter* painter) const;
	void Update(qreal delta_time);
	void SendTo(const QString& name, Message* message);
	void AddGameObject(const QString& name, GameObject* game_object);
	QList<Area*> GetAllAreas();

	void keyPressEvent(QKeyEvent* event);
	void keyReleaseEvent(QKeyEvent* event);

	void KeysUpdate();
	void KeysReset();
	bool IsKeyJustPressed(int key);
	bool IsKeyJustReleased(int key);
	bool IsKeyPressed(int key);

	/* Fill area_obj's areas by only those which intersects */
	QList<Area*> GetIntersected(Area* area);
	bool GetMovableIntersects(Area* move_area, const QVector2D& velocity,
		   		QVector2D* offset, QList<Area*>& areas, Direction& direction);
};

#endif


