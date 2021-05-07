#ifndef PORTAL2D_SCENE_H_
#define PORTAL2D_SCENE_H_

#include <QObject>
#include <QWidget>
#include <QMap>
#include <QPainter>
#include <QDebug>
#include <QPixmap>
#include <QList>
#include <QQueue>

#include "../wall_mechanics/straight_wall.h"

class Area;
class GameObject;
class Message;
enum class Direction;
class Camera;
class Box;

/* This class contains all objects in game,
 * and provide their updating and drawing */
class Scene : public QObject {
	Q_OBJECT
protected:
	/* Every object has own string id. This is need to 
	 * send messages between objects */
	enum class KeyState { JustPressed, Pressed, JustReleased, Released };
	
	Camera* camera_;
	qreal delta_time_;
	QMap<QString, GameObject*> objects;

	QMap<int, KeyState> keyboard;
	QMap<int, KeyState> mouse_keys;
	QPointF mouse_position_;
	QSize window_size_;

	QQueue<GameObject*> to_delete;	
	QQueue<GameObject*> to_add;
	QQueue<Message*> to_send;

	QPixmap background;

	void ForceDelete(const QString& name);
	void ForceAdd(GameObject* game_object);
	void ForceSend(Message* message);
public:
	Scene(QObject* parent = nullptr);
	~Scene();

	void PostUpdate();

	void DeleteUpdate();
	void AddUpdate();
	void MessageUpdate();

	void Draw(QPainter* painter) const;
	void Update(qreal delta_time);
	void SendTo(Message* message);
	void AddGameObject(const QString& name, GameObject* game_object);
	void DeleteObject(const QString& name);
	GameObject* GetObject(const QString& str) const;
	QList<Area*> GetAllAreas();
	QList<Wall*> GetAllWalls();
	QList<Box*> GetBoxes();

	void resizeEvent(QResizeEvent* event);
	void wheelEvent(QWheelEvent* event);
	void keyPressEvent(QKeyEvent* event);
	void keyReleaseEvent(QKeyEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void mousePressEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);

	void KeysUpdate();
	bool IsKeyJustPressed(int key);
	bool IsKeyJustReleased(int key);
	bool IsKeyPressed(int key);
	bool IsMouseKeyPressed(int key);
	bool IsMouseKeyJustPressed(int key);

	QList<Area*> GetIntersected(Area* area);
	bool GetWallLineIntersect(const QLineF& line,
		QVector2D* intersect_point, StraightWall** res_wall);
	bool GetMovableIntersects(Area* move_area, const QVector2D& velocity,
		QVector2D* offset, QList<Area*>& areas, Direction& direction);

	qreal GetDeltaTime() const;
	Camera* GetCamera();

	void SetGameObjectPosition(const QString& name, const QVector2D& pos);
	bool IsOnScene(const QString& name) const;
	void SetCamera(Camera* camera);
	void DrawBackground(QPainter* painter) const;
	const QPointF& GetMousePosition() const;
	QRect GetRect() const;

	void WriteToJson(const QString& file_name) const;
	void ReadFromJson(const QString& file_name);
};

#endif

