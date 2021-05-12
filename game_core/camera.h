#ifndef PORTAL2D_CAMERA_H_
#define PORTAL2D_CAMERA_H_

#include <QPainter>
#include <QDebug>
#include <QResizeEvent>

#include "game_object.h"

class Camera : public GameObject {
private:
	QPainter* painter_;	
	
	QSizeF source_size_ = QSizeF(800, 500);
	QRectF current_rect_;
	QRect window_rect_;
public:
	Camera() = delete;
	Camera(Scene* scene);

	void SetPainter(QPainter* painter);

	void SetWindowRect(const QRect& window_rect);
	const QRect& GetWindowRect();

	QPointF PointToCurrent(const QPointF& point);
	QPointF PointFromCurrent(const QPointF& point);

	virtual void Update();

	void MoveBy(qreal dx, qreal dy);
	void MoveTo(qreal x, qreal y);
	void ResizeBy(qreal d);

	void resizeEvent(QResizeEvent* event);
	qreal GetScale();
};

#endif

