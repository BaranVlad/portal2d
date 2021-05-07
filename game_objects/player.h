#ifndef PORTAL2D_PLAYER_2D
#define PORTAL2D_PLAYER_2D

#include <QPainter>

#include "../game_core/kinematic_body.h"

class Scene;
class Message;
class Portal;
class StraightWall;
class Box;

class Player : public KinematicBody {
private:
	QVector2D key_vector;

	Box* box_taked = nullptr;
public:
	Player() = delete;
	Player(Scene* scene);
	
	virtual void Update();	
	virtual void Draw(QPainter* painter) const;
	virtual void TakeMessage(Message* msg);

	virtual qreal GetWidth() const;
	virtual qreal GetHeight() const;
		
	void ReleaseBox();
	QVector2D GetMouseVec() const;
	bool GetAimLine(QLineF* line, StraightWall** res_wall) const;
	void OpenPortal();

	void MotionControl();
	void SideMove();
	void AccelerateButBound(qreal acceleration, qreal min, qreal max_speed);

	void CollisionUpdate(const QList<Area*>& list);
	void KeyUpdate();
	void TakeBox();

	virtual void ToJsonObject(QJsonObject& js) const;
	virtual void FromJsonObject(const QJsonObject& js);
};

#endif

