#include "camera.h"

Camera::Camera(Scene* scene) : 
	GameObject(scene),
	current_rect_(0, 0, source_size_.width(), source_size_.height())
{}

void Camera::SetPainter(QPainter* painter) {
	painter_ = painter;
	SetWindowRect(painter_->viewport());
}

void Camera::Update() {
	painter_->scale(GetScale(), GetScale());
	painter_->translate(-1 * current_rect_.topLeft());

	SetWindowRect(painter_->viewport());
}

void Camera::MoveBy(qreal dx, qreal dy) {
	current_rect_.moveTo(current_rect_.topLeft() + QPointF(dx, dy));
}

void Camera::MoveTo(qreal x, qreal y) {
	current_rect_.moveTo(QPointF(x, y));
}

void Camera::ResizeBy(qreal d) {
	current_rect_.adjust(d, d, -d, -d);
}

QPointF Camera::PointToCurrent(const QPointF& point) {
	QPointF new_point = point;

	new_point /= GetScale();
	new_point += current_rect_.topLeft();

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
	window_rect_.setHeight(event->size().height());
	window_rect_.setWidth(event->size().width());
}

qreal Camera::GetScale() {
	return window_rect_.height() / current_rect_.height();
}

