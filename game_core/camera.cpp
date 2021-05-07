#include "camera.h"

Camera::Camera(Scene* scene) : 
	GameObject(scene),
	camera_point_(0, 0),
	camera_scale_(1)
{}

void Camera::SetPainter(QPainter* painter) {
	painter_ = painter;
	SetWindowRect(painter_->viewport());
}

void Camera::Update() {
	painter_->translate(-1 * camera_point_);
	painter_->scale(camera_scale_, camera_scale_);

	SetWindowRect(painter_->viewport());
}

void Camera::MoveBy(qreal dx, qreal dy) {
	camera_point_ += QPointF(dx, dy);
}

void Camera::MoveTo(qreal x, qreal y) {
	camera_point_ = QPointF(x, y);
}

void Camera::ResizeBy(qreal d) {
	double w_height = window_rect_.height();
	MoveBy(d * camera_scale_, d);
	camera_scale_ = 
		(w_height * camera_scale_) / (w_height - 2 * d * camera_scale_);
}

QPointF Camera::PointToCurrent(const QPointF& point) {
	QPointF new_point = point;

	new_point /= camera_scale_;
	new_point += camera_point_;

	return new_point;
}

// TODO
QPointF Camera::PointFromCurrent(const QPointF& point) {
	return point;	
}

void Camera::SetWindowRect(const QRect& window_rect) {
	window_rect_ = window_rect;
}

const QRect& Camera::GetWindowRect() {
	return window_rect_;
}

void Camera::resizeEvent(QResizeEvent* event) {
	qreal new_height = (double)event->size().height();
	qreal old_height = (double)window_rect_.height();
	if (old_height <= 0) {
		return;
	}
	camera_scale_ = new_height * camera_scale_ / old_height;
	window_rect_.setHeight(new_height);
	window_rect_.setWidth(event->size().width());
}

