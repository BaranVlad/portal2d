#ifndef PORTAL2D_SCENE_H_
#define PORTAL2D_SCENE_H_

#include <QObject>
#include <QWidget>
#include <QMap>
#include <QPainter>
#include <QDebug>
#include <QPixmap>

#include <QList>

class Area;
class GameObject;
class Message;
enum class Direction;
class Camera;

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

	QPixmap background;
public:
	Scene(QObject* parent = nullptr);
	~Scene();

	void Draw(QPainter* painter) const;
	void Update(qreal delta_time);
	void SendTo(Message* message);
	void AddGameObject(const QString& name, GameObject* game_object);
	QList<Area*> GetAllAreas();

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
	bool GetMovableIntersects(Area* move_area, const QVector2D& velocity,
		   	QVector2D* offset, QList<Area*>& areas, Direction& direction);
	qreal GetDeltaTime() const;
	Camera* GetCamera();

	void SetGameObjectPosition(const QString& name, const QVector2D& pos);
	bool IsOnScene(const QString& name) const;
	void SetCamera(Camera* camera);
	void DrawBackground(QPainter* painter) const;
	void DeleteObject(const QString& name);
	const QPointF& GetMousePosition() const;
	QRect GetRect() const;
	
};

#endif

