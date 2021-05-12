#ifndef PORTAL2D_PORTAL_H_
#define PORTAL2D_PORTAL_H_

#include "../game_core/area_object.h"
#include "../wall_mechanics/straight_wall.h"
#include "../game_objects/player.h"

class Portal : public AreaObject {
private:
	const StraightWall* wall_;	
	QRectF portal_rect_;
	
	Direction direction_;
	QVector2D normal_vector_;
public:
	Portal() = delete;
	Portal(Scene* scene);

	virtual void Update();
	virtual void Draw(QPainter* painter) const;

	virtual qreal GetWidth() const;
	virtual qreal GetHeight() const;
	
	void PlayerCollision(Player* player);
	void SetDirection(Direction direction);

	bool IsInPair();

	void SetNormalVector(const QVector2D& vec);
	QVector2D GetNormalVector() const;
	void SetWall(const StraightWall* wall);
};

#endif
