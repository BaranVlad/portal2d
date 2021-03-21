#include "game_widget.h"

#include "../wall_mechanics/straight_wall.h"
#include "../wall_mechanics/wall_map.h"
#include "../messages/wall_map_add_to_group_message.h"
#include "../messages/wall_map_message.h"
#include "../game_objects/player.h"

GameWidget::GameWidget(QWidget* parent) : 
	QWidget(parent),
	scene_(new Scene(this))
{
	setGeometry(50, 50, 800, 600);
	QTimer* timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &GameWidget::Update);
	timer->start(1000 / FPS);

	clock_.start();
//	
	StraightWall* wall = new StraightWall(scene_, Direction::Down, 400);
	wall->SetPosition(200, 500);

	WallMap* wall_map = new WallMap(scene_);
	wall_map->SetPosition(0, 0);
	scene_->AddGameObject("WallMap", wall_map);

	WallMapAddToGroupMessage* msg = new WallMapAddToGroupMessage("WallMap", "group1", wall);
	scene_->SendTo("WallMap", msg);

	Player* player = new Player(scene_);
	player->SetPosition(300, 200);
	scene_->AddGameObject("Player", player);
}

void GameWidget::Update() {
	scene_->Update(clock_.elapsed());
	clock_.start();	
	update();
}

void GameWidget::paintEvent(QPaintEvent*) {
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	
	scene_->Draw(&painter);
}

void GameWidget::keyPressEvent(QKeyEvent* key_event) {
	scene_->keyPressEvent(key_event);	
}

void GameWidget::keyReleaseEvent(QKeyEvent* key_event) {
	scene_->keyReleaseEvent(key_event);	
}

