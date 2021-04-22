#include "kinematic_body.h"
#include "scene.h"

QVector2D KinematicBody::gravity = QVector2D(0, 1);

KinematicBody::KinematicBody(Scene* scene) :
	CollideObject(scene)	
{}

void KinematicBody::SetVelocity(qreal x, qreal y) {
	velocity_.setX(x);
	velocity_.setY(y);
}

void KinematicBody::SetVelocity(const QVector2D& velocity) {
	velocity_ = velocity;
}

bool KinematicBody::IsOnFloor() const {
	return is_on_floor_;
}

bool KinematicBody::MoveAndCollide(QList<Area*>& areas) 
{
	QVector2D offset;
	Direction direction;
	bool is_collide = 
		scene_->GetMovableIntersects(GetAreasViaGroupName("Collider")[0], 
									velocity_, &offset, areas, direction);
	if (is_collide) {
		if (direction == Direction::Up) {
			is_on_floor_ = true;
		} else {
			is_on_floor_ = false;
		}
		
		if (direction == Direction::Down) {
			if (velocity_.y() < 0) {
				velocity_.setY(0);
			}	
		}
		
		QVector2D suspend = velocity_ - offset;
		if (direction == Direction::Up || direction == Direction::Down) {
			suspend.setY(0);	
		} else {
			suspend.setX(0);
		}
		Move(offset);
		offset = suspend;

		is_collide = 
		scene_->GetMovableIntersects(GetAreasViaGroupName("Collider")[0],
				   					suspend, &offset, areas, direction);
		Move(offset);
	} else {
		is_on_floor_ = false;
		Move(velocity_);
	}
	return is_collide;	
}


