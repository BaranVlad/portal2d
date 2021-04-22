#include "player.h"

#include <QList>
#include <QDebug>

#include "../game_core/scene.h"
#include "../game_core/area.h"
#include "portal_bullet.h"

Player::Player(Scene* scene) :
	KinematicBody(scene)
{
	AddAreaToGroup("Collider",
		 new Area("Collider", QRectF(0, 0, PLAYER_W, PLAYER_H), this));
	velocity_ = QVector2D(0, 0);
}

void Player::Update() {
	if (!is_on_floor_) {
		velocity_ += KinematicBody::gravity;	
	} else {
		velocity_.setY(1);
	}
	KeyUpdate();
	if (scene_->IsMouseKeyJustPressed(Qt::LeftButton)) {
		FirePortalBullet();
	}

	QList<Area*> areas;
	MoveAndCollide(areas);
}

void Player::Draw(QPainter* painter) const {
	painter->drawRect(GetAreasViaGroupName("Collider")[0]->GetGlobalRect());
}

void Player::TakeMessage(Message* msg)
{}

void Player::KeyUpdate() {
	if (scene_->IsKeyPressed(Qt::Key_A)) {
		velocity_.setX(-2);
	} else if (scene_->IsKeyPressed(Qt::Key_D)) {
		velocity_.setX(2);	
	} else {
		velocity_.setX(0);
	}
	
	if (scene_->IsKeyJustPressed(Qt::Key_Space) && is_on_floor_) {
		velocity_ += QVector2D(0, -10);
	}
}

void Player::FirePortalBullet() const {
	QVector2D mouse_position = QVector2D(scene_->GetMousePosition());
	QVector2D bullet_velocity = mouse_position - GetPosition();
	bullet_velocity.normalize();

	PortalBullet* portal_bullet = new PortalBullet(scene_);
	portal_bullet->SetPosition(GetPosition() + bullet_velocity * 20);
	portal_bullet->SetVelocity(bullet_velocity);
	scene_->AddGameObject("bullet", portal_bullet);
}

