#ifndef PORTAL2D_CAMERA_H_
#define PORTAL2D_CAMERA_H_

#include <QPainter>
#include <QDebug>

#include "game_object.h"

class Camera : public GameObject {
private:
	QPainter* painter_;	
	QSizeF source_size_;

	// It is camera rect. This image will show on the screen. x and y
	// is coords before scaling
	QRectF current_rect_;
	
public:
	Camera() = delete;
	Camera(Scene* scene);

	void SetPainter(QPainter* painter);
	void SetSourceSize(qreal width, qreal height);
	void SetSourceSize(const QSizeF& size);

	void SetCurrentRect(const QRectF& current_rect);
	void SetCurrentRect(qreal x, qreal y, qreal w, qreal h);
	const QRectF& GetCurrentRect() const;

	QPointF PointToCurrent(const QPoint& point);
	QPointF PointFromCurrent(const QPoint& point);

	virtual void Update();

	void MoveBy(qreal dx, qreal dy);
	void MoveTo(qreal x, qreal y);
	void ResizeBy(qreal d);
};

#endif

