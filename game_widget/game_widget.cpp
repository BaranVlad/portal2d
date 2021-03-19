#include "game_widget.h"

#include "../wall_mechanics/straight_wall.h"
#include "../wall_mechanics/wall_map.h"
#include "../messages/wall_map_add_to_group_message.h"
#include "../messages/wall_map_message.h"

GameWidget::GameWidget(QWidget* parent) : 
	QWidget(parent),
	scene_(new Scene(this))
{
	setGeometry(50, 50, 800, 600);
	QTimer* timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &GameWidget::Update);
	timer->start(1000 / FPS);

//	
	StraightWall* wall = new StraightWall(scene_, Direction::Up, 50);
	wall->SetPosition(100, 100);

	WallMap* wall_map = new WallMap(scene_);
	wall_map->SetPosition(0, 0);
	scene_->AddGameObject("WallMap", wall_map);

	WallMapAddToGroupMessage* msg = new WallMapAddToGroupMessage("WallMap", "group1", wall);
	scene_->SendTo("WallMap", msg);
}

void GameWidget::Update() {

	WallMapMessage* msg = new WallMapMessage("WallMap", "group1");
	scene_->SendTo("WallMap", msg);

	scene_->Update();
	update();
}

void GameWidget::paintEvent(QPaintEvent*) {
	QPainter painter(this);
	scene_->Draw(&painter);
}

