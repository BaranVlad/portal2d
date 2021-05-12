#ifndef PORTAL2D_BOX_H_
#define PORTAL2D_BOX_H_

#include "../game_core/kinematic_body.h"

class Player;

class Box : public KinematicBody {
private:
	QRectF box_rect;

	Player* player_taked = nullptr;
public:
	Box() = delete;
	Box(Scene* scene);
	virtual ~Box();

	virtual void Update();
	virtual void Draw(QPainter* painter) const;
	virtual qreal GetWidth() const;
	virtual qreal GetHeight() const;

	void CollisionUpdate(const QList<Area*>& list);
	void PlayerTake(Player* player);
	void PlayerRelease();
	void BoxTakedUpdate();	
	Player* GetPlayer();
	bool PlayerReachable(Player* player) const;

	virtual void ToJsonObject(QJsonObject& js) const;
	virtual void FromJsonObject(const QJsonObject& js);
};


#endif

