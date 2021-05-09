#include "game_widget.h"

#include "../wall_mechanics/straight_wall.h"
#include "../wall_mechanics/wall_map.h"
#include "../game_objects/player.h"
#include "../game_objects/floor_button.h"
#include "../game_core/scene.h"
#include "../game_core/camera.h"
#include "../game_objects/box.h"
#include "../game_objects/spawn_box.h"
#include "../game_objects/finish_area.h"
#include "../game_objects/press_button.h"

#include <QVector>
#include <QPushButton>

GameWidget::GameWidget(QWidget* parent) : 
	QWidget(parent),
	scene_(new Scene(this))
{
	setMouseTracking(true);
	grabKeyboard();
	setGeometry(50, 50, 800, 600);
	QTimer* timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &GameWidget::Update);
	timer->start(1000 / FPS);

	clock_.start();
	scene_->SetPause(true);

	WallMap* wall_map = new WallMap(scene_);
	wall_map->SetPosition(0, 0);
	scene_->AddGameObject("WallMap", wall_map);
//	
	StraightWall* wall = new StraightWall(scene_, Direction::Down, 700);
	wall->SetPosition(200, 500);
	wall->SetPortable(true);

	StraightWall* wall1 = new StraightWall(scene_, Direction::Right, 100);
	wall1->SetPosition(600, 400);
	wall1->SetPortable(true);

	StraightWall* wall2 = new StraightWall(scene_, Direction::Up, 700);
	wall2->SetPosition(200, 200);
	wall2->SetPortable(true);

	wall_map->AddWall(wall);
	wall_map->AddWallToGroup("group1", wall1);
	wall_map->AddWallToGroup("group1", wall2);

	Player* player = new Player(scene_);
	player->SetPosition(250, 200);
	scene_->AddGameObject("Player", player);

	FloorButton* button = new FloorButton(scene_);	
	button->SetPosition(300, 500 - BUTTON_HEIGHT);

	Message* msg2 = 
		new Message("spawn", MessageType::SpawnBox);

	button->SetPressMessage(msg2);
	
	scene_->AddGameObject("Button", button);

	SpawnBox* spawn = new SpawnBox(scene_);
	scene_->AddGameObject("spawn", spawn);
	spawn->SetPosition(400, 400);

	FinishArea* finish = new FinishArea(scene_);
	finish->SetPosition(600, 300);
	scene_->AddGameObject("finish", finish);

	PressButton* press_button = new PressButton(scene_);
	press_button->SetCenter(700, 470);
	scene_->AddGameObject("press", press_button);
	press_button->SetPressMessage(
			new Message("WallMap", MessageType::WallSwitch, {"group1"}));
	press_button->SetTimer(3);

	scene_->PostUpdate();
	scene_->WriteToJson("level1.json");
	scene_->Restart();
}

void GameWidget::StartGame(int level) {
	scene_->SetPause(false);
	QString file_name = QString("level%1.json").arg(level);
	scene_->ReadFromJson(file_name);
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
	if (key_event->isAutoRepeat()) {
		key_event->ignore();
	} else {
		scene_->keyPressEvent(key_event);	
	}
	QWidget::keyPressEvent(key_event);
}

void GameWidget::keyReleaseEvent(QKeyEvent* key_event) {
	if (key_event->isAutoRepeat()) {
		key_event->ignore();
	} else {
		scene_->keyReleaseEvent(key_event);	
	}
	QWidget::keyPressEvent(key_event);
}

void GameWidget::wheelEvent(QWheelEvent* event) {
	scene_->wheelEvent(event);
}

void GameWidget::mouseMoveEvent(QMouseEvent* event) {
	scene_->mouseMoveEvent(event);
}

void GameWidget::mousePressEvent(QMouseEvent* event) {
	scene_->mousePressEvent(event);
}

void GameWidget::mouseReleaseEvent(QMouseEvent* event) {
	scene_->mouseReleaseEvent(event);
}

GameWidget::~GameWidget() {
	releaseKeyboard();
}

void GameWidget::resizeEvent(QResizeEvent* event) {
	scene_->resizeEvent(event);
}

