#include "kinematic_body.h"
#include "scene.h"

#include "consts.h"
#include "../game_objects/portal.h"

QVector2D KinematicBody::gravity = QVector2D(0, GRAVITY);

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
		if (is_collide) {
			if (direction == Direction::Up) {
				is_on_floor_ = true;
			}
		}
		if (direction == Direction::Up || direction == Direction::Down) {
			suspend.setY(0);	
		} else {
			suspend.setX(0);
		}
		
		Move(offset);
	} else {
		is_on_floor_ = false;
		Move(velocity_);
	}
	return is_collide;	
}

qreal KinematicBody::GetFriction(int x_speed) {
	return x_speed > 0 ? FRICTION : -FRICTION;
}

qreal KinematicBody::GetAirFriction(int x_speed) {
	return x_speed > 0 ? AIR_FRICTION : -AIR_FRICTION;
}

void KinematicBody::Teleport(Portal* portal) {
	Portal* another_portal = nullptr;
	if (portal->GetName() == "portal_blue")	{
		if (!scene_->IsOnScene("portal_orange")) {
			return;
		}
		another_portal = dynamic_cast<Portal*>(
								scene_->GetObject("portal_orange"));
	} else if (portal->GetName() == "portal_orange") {
		if (!scene_->IsOnScene("portal_blue")) {
			return;
		}
		another_portal = dynamic_cast<Portal*>(
								scene_->GetObject("portal_blue"));
	}
	
	qreal velocity_len = qMax(
		(qreal)QVector2D::dotProduct(-portal->GetNormalVector(),
			   				velocity_), (qreal)MIN_TELEPORT_SPEED);

	QVector2D norm_vec = another_portal->GetNormalVector();

	SetCenter(another_portal->GetPosition());

	Move(norm_vec.x() * (GetWidth() / 2 + PORTAL_WIDE / 2),
		 norm_vec.y() * (GetHeight() / 2 + PORTAL_WIDE / 2));

	SetVelocity(norm_vec * velocity_len);
}

void KinematicBody::FrictionUpdate(qreal friction) {
	if (velocity_.x() > 0) {
		velocity_.setX(qMax(velocity_.x() - friction, 0.));
	} else if (velocity_.x() < 0) {
		velocity_.setX(qMin(velocity_.x() + friction, 0.));
	}
}


