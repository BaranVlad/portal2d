#ifndef PORTAL2D_GAME_OBJECT_H_
#define PORTAL2D_GAME_OBJECT_H_

#include <QVector2D>
#include <QPoint>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

enum class Direction { Up, Down, Left, Right };

class Scene;
class Message;
/* It is the base class for all updateble classes that scene class contains */
class GameObject {
protected:
	Scene* scene_;
	QString name_;
public:
	GameObject() = delete;
	GameObject(Scene* scene);

	virtual void Update() = 0;
	virtual void ToJsonObject(QJsonObject& js) const;
	virtual void FromJsonObject(const QJsonObject& js);

	Scene* GetScene() const;
	void SetName(const QString& name);
	const QString& GetName() const;

	/* Message object delete here */
	virtual void TakeMessage(Message* msg);
	virtual ~GameObject() = default;
};

#endif

