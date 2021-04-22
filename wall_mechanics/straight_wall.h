#ifndef STRAIGHT_WALL_H_
#define STRAIGHT_WALL_H_

#include <QtGlobal>
#include <QVector2D>

#include "wall.h"
#include "../game_core/common_message.h"

#define WALL_LINE_WIDTH 6
#define WALL_PORTABLE_AREA_SIZE 20
   
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
	virtual void Update();

	virtual void SetPosition(qreal x, qreal y);
	virtual void SetPosition(const QVector2D& position);

	void DrawPortablePart(QPainter* painter) const;

};

#endif

