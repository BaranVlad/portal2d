#ifndef STRAIGHT_WALL_H_
#define STRAIGHT_WALL_H_

#include <QtGlobal>
#include <QVector2D>

#include "wall.h"
#include "../game_core/common_message.h"
   
class StraightWall : public Wall {
private:
	Direction direction_;
	qreal len_;
	QVector2D end_point_;

	void UpdateEndPoint();
public:
	StraightWall() = delete;
	StraightWall(Scene* scene, Direction dir, qreal len);

	virtual void DrawActive(QPainter* painter) const;
	virtual void DrawInactive(QPainter* painter) const;
	virtual void TakeMessage(Message* message);

	virtual void SetPosition(qreal x, qreal y);
	virtual void SetPosition(const QVector2D& position);

};

#endif

