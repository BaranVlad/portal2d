#include "player.h"

#include <QList>
#include <QDebug>
#include <QtGlobal>

#include "../game_core/scene.h"
#include "../game_core/area.h"
#include "portal_bullet.h"
#include "portal.h"
#include "box.h"
#include "finish_area.h"

#include "../game_core/consts.h"
#include "qnamespace.h"

Player::Player(Scene* scene) :
	KinematicBody(scene)
{
	AddAreaToGroup("Collider",
		 new Area("Collider", QRectF(0, 0, PLAYER_W, PLAYER_H), this));
	velocity_ = QVector2D(0, 0);
}

void Player::Update() {
	MotionControl();
	if (scene_->IsMouseKeyJustPressed(Qt::LeftButton) ||
		scene_->IsMouseKeyJustPressed(Qt::RightButton)) 
	{
		OpenPortal();
	}
	StraightWall* wall = nullptr;
	GetAimLine(&fire_line, &wall);

	QList<Area*> areas;
	MoveAndCollide(areas);
	CollisionUpdate(areas);
}

void Player::Draw(QPainter* painter) const {
	painter->setPen(QPen(Qt::black, 2));
	painter->setBrush(Qt::blue);

	painter->
		drawRect(GetAreasViaGroupName("Collider")[0]->GetGlobalRect());

	painter->setPen(QPen(Qt::gray, 4));
	painter->drawLine(fire_line);
}

void Player::TakeMessage([[maybe_unused]] Message* msg)
{}

void Player::KeyUpdate() {
	if (scene_->IsKeyPressed(Qt::Key_A)) {
		key_vector = QVector2D(-1, 0);
	} else if (scene_->IsKeyPressed(Qt::Key_D)) {
		key_vector = QVector2D(1, 0);
	} else {
		key_vector = QVector2D(0, 0);
	}

	if (is_on_floor_) {
		key_vector *= SIDE_ACCELERATION;
	} else {
		key_vector *= SIDE_AIR_ACCELERATION;
	}
	
	if (scene_->IsKeyJustPressed(Qt::Key_Space) && is_on_floor_) {
		velocity_ += QVector2D(0, JUMP_VEC);
	}

	if (scene_->IsKeyJustPressed(Qt::Key_E)) {
		if (!box_taked) {
			TakeBox();
		} else {
			box_taked->PlayerRelease();
			box_taked = nullptr;
		}
	}
}

QVector2D Player::GetMouseVec() const {
	QVector2D mouse_position = QVector2D(scene_->GetMousePosition());
	QVector2D mouse_vec = mouse_position - GetCenter();
	return mouse_vec;
}

bool Player::GetAimLine(QLineF* line, StraightWall** res_wall) const {
	QVector2D position = GetCenter();
	QVector2D mouse_vec = GetMouseVec();

	QLineF fire_line(position.toPointF(), 
			(position + mouse_vec.normalized() * 1000).toPointF());
	StraightWall* wall = nullptr;
	QVector2D i_point;

	bool is_intersection = 
		scene_->GetWallLineIntersect(fire_line, &i_point, &wall);
	*line = QLineF(position.toPointF(), i_point.toPointF());
	*res_wall = wall;
	return is_intersection;
}

void Player::OpenPortal() {
	StraightWall* i_wall = nullptr;
	QLineF line;
	bool is_intersection = GetAimLine(&line, &i_wall);
	if (!is_intersection) {
		return;
	}
	if (scene_->IsMouseKeyJustPressed(Qt::LeftButton)) {
		i_wall->OpenPortal(line.p2(), "portal_orange");
	} else if (scene_->IsMouseKeyJustPressed(Qt::RightButton)) {
		i_wall->OpenPortal(line.p2(), "portal_blue");
	}
}

void Player::CollisionUpdate(const QList<Area*>& list) {
	Portal* portal = nullptr;
	FinishArea* finish = nullptr;
	for (Area* area : list) {
		AreaObject* area_object = area->GetAreaObject();
		qDebug() << area->GetAreaObject()->GetName();
		if (portal = dynamic_cast<Portal*>(area_object)) {
			Teleport(portal);
			is_on_floor_ = false;
			if (box_taked) {
				box_taked->Teleport(portal);
			}
		}
		if (finish = dynamic_cast<FinishArea*>(area_object)) {
			scene_->Win();
		}
	}
}

void Player::MotionControl() {
	if (!is_on_floor_) {
		velocity_ += KinematicBody::gravity;	
	} else {
		if (velocity_.y() >= 0) {
			velocity_.setY(0.1);
		}
	}
	KeyUpdate();

	SideMove();
	if (is_on_floor_) {
		FrictionUpdate(FRICTION);
	} else {
		FrictionUpdate(AIR_FRICTION);
	}

	if (velocity_.length() >= MAX_PLAYER_AIR_SPEED) {
		velocity_ = velocity_.normalized() * MAX_PLAYER_AIR_SPEED;
	}
}

void Player::SideMove() {
	qreal new_x = velocity_.x() + key_vector.x();
	if (velocity_.x() <= MAX_PLAYER_FLOOR_SPEED &&
		velocity_.x() >= -MAX_PLAYER_FLOOR_SPEED) 
	{
		velocity_.setX(new_x);
	}
}

void Player::AccelerateButBound(qreal acceleration, 
									qreal min_speed, qreal max_speed) 
{
	if (velocity_.x() + acceleration <= min_speed) {
		velocity_.setX(min_speed);
	} else if (velocity_.x() + acceleration >= max_speed) {
		velocity_.setX(max_speed);
	} else {
		velocity_.setX(velocity_.x() + acceleration);
	}
}

qreal Player::GetWidth() const {
	return PLAYER_W;	
}

qreal Player::GetHeight() const {
	return PLAYER_H;
}

void Player::TakeBox() {
	for (Box* box : scene_->GetBoxes()) {
		QVector2D vec = box->GetCenter() - GetCenter();
		if (vec.length() <= MAX_BOX_TAKE_DISTANCE &&
			QVector2D::dotProduct(vec, GetMouseVec()) > 0) 
		{
			box->PlayerTake(this);
			box_taked = box;
		}
	}
}

void Player::ReleaseBox() {
	box_taked = nullptr;
}

void Player::ToJsonObject(QJsonObject& js) const {
	KinematicBody::ToJsonObject(js);
	js["class"] = "Player";
}

void Player::FromJsonObject(const QJsonObject& js) {
	KinematicBody::FromJsonObject(js);
}

