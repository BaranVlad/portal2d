#include "box.h"
#include "../game_core/consts.h"
#include "../game_core/scene.h"
#include "portal.h"


Box::Box(Scene* scene) :
	KinematicBody(scene)
{
	box_rect.setRect(0, 0, BOX_SIZE, BOX_SIZE);
	AddAreaToGroup("Collider", box_rect);
}

void Box::Update() {
	if (player_taked) {
		BoxTakedUpdate();	
	} else {
		if (is_on_floor_) {
			FrictionUpdate(FRICTION);
		} else {
			FrictionUpdate(AIR_FRICTION);
		}

		if (velocity_.length() >= MAX_PLAYER_AIR_SPEED) {
			velocity_ = velocity_.normalized() * MAX_PLAYER_AIR_SPEED;
		}

		if (is_on_floor_) {
			velocity_.setY(0.1);
		} else {
			velocity_ += KinematicBody::gravity;
		}
	}

	QList<Area*> areas;
	MoveAndCollide(areas);
	CollisionUpdate(areas);
}

void Box::Draw(QPainter* painter) const {
	painter->setPen(QPen(Qt::black, 2));
	painter->setBrush(QColor(200, 200, 200));

	QRectF new_rect(box_rect);
	new_rect.moveTopLeft(new_rect.topLeft() + GetPosition().toPointF());
	painter->drawRect(new_rect);
}

qreal Box::GetWidth() const {
	return BOX_SIZE;
}

qreal Box::GetHeight() const {
	return BOX_SIZE;
}

void Box::CollisionUpdate(const QList<Area*>& list) {
	Portal* portal = nullptr;
	for (Area* area : list) {
		AreaObject* area_object = area->GetAreaObject();
		if (portal = dynamic_cast<Portal*>(area_object)) {
			Teleport(portal);
			is_on_floor_ = false;
		}
	}
}

void Box::PlayerTake(Player* player) {
	velocity_ = QVector2D(0, 0);
	player_taked = player;
}

void Box::PlayerRelease() {
	player_taked->ReleaseBox();
	player_taked = nullptr;
	velocity_ = QVector2D(0, 0);
}

bool Box::PlayerReachable(Player* player) const {
	QVector2D player_pos = player->GetCenter();
	QLineF connect_line(player_pos.x(), player_pos.y(),
						GetCenter().x(), GetCenter().y());
	QVector2D point;
	StraightWall* wall;
	if (scene_->GetWallLineIntersect(connect_line, &point, &wall)) {
		return false;
	}
	return true;
}

void Box::BoxTakedUpdate() {
	
	if (!PlayerReachable(player_taked)) {
		PlayerRelease();
		return;
	}

	if ((player_taked->GetCenter() - GetCenter()).length() >
		   												MAX_BOX_DISTANCE)
	{
		PlayerRelease();
		return;
	}

	QVector2D aim = (player_taked->GetMouseVec().normalized() *
		   			MAX_BOX_TAKE_DISTANCE + player_taked->GetCenter());
	QVector2D to_aim = aim - GetCenter();
	velocity_ = to_aim * BOX_TAKED_VELOCITY_COEF;
}

void Box::ToJsonObject(QJsonObject& js) const {
	KinematicBody::ToJsonObject(js);
	js["class"] = "Box";
}

void Box::FromJsonObject(const QJsonObject& js) {
	KinematicBody::FromJsonObject(js);
}

Box::~Box() {
	if (player_taked) {
		player_taked->ReleaseBox();
	}
}

