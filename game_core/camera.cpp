#include "camera.h"

Camera::Camera(Scene* scene) : GameObject(scene)
{}

void Camera::SetPainter(QPainter* painter) {
	painter_ = painter;
}

void Camera::Update() {

	qreal scale_by = painter_->viewport().height() / source_size_.height();
	painter_->scale(scale_by, scale_by);

	scale_by = current_rect_.height() / source_size_.height();
	painter_->translate(current_rect_.topLeft());
	painter_->scale(scale_by, scale_by);

}

void Camera::SetSourceSize(qreal width, qreal height) {
	source_size_ = QSizeF(width, height);
}

void Camera::SetSourceSize(const QSizeF& size) {
	source_size_ = size;
}

void Camera::MoveBy(qreal dx, qreal dy) {
	current_rect_.adjust(dx, dy, 0, 0);
}

void Camera::MoveTo(qreal x, qreal y) {
	current_rect_.moveTo(x, y);
}

void Camera::ResizeBy(qreal d) {
	current_rect_.adjust(d, d, -d, -d);
}

void Camera::SetCurrentRect(const QRectF& current_rect) {
	current_rect_ = current_rect;
}

void Camera::SetCurrentRect(qreal x, qreal y, qreal w, qreal h) {
	current_rect_.setRect(x, y, w, h);
}

const QRectF& Camera::GetCurrentRect() const {
	return current_rect_;
}

QPointF Camera::PointToCurrent(const QPoint& point) {
	QPoint new_point = point;
	new_point -= current_rect_.topLeft().toPoint();	
	new_point *= source_size_.height() / 
									(double)painter_->viewport().height();
	new_point *= source_size_.height() / 
									(double)current_rect_.height();
	return new_point;
}

// TODO
QPointF PointFromCurrent(const QPoint& point) {
	return point;	
}
