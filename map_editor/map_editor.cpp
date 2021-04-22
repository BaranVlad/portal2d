#include "map_editor.h"

#include "item_button.h"
#include "editor_scene.h"
#include "strategies/player_strategy.h"
#include "strategies/walls_strategy.h"
#include "../game_core/camera.h"

MapEditor::MapEditor(QWidget* parent) :
	QWidget(parent),
	mouse_pos_(0, 0),
	scene_(new EditorScene(this))
{
	setMouseTracking(true);

	strategy_ = nullptr;
	setGeometry(50, 50, EDITOR_WIDTH, EDITOR_HEIGHT);

	QTimer* timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &MapEditor::Update);
	timer->start(1000 / EDITOR_FPS);

	ItemButton* player_button = new ItemButton(this);
	PlayerStrategy* strategy = new PlayerStrategy(this, scene_);
	player_button->SetStrategy(strategy);
	player_button->move(100, 100);

	ItemButton* wall_button = new ItemButton(this);
	WallsStrategy* wall_strategy = new WallsStrategy(this, scene_);
	wall_button->SetStrategy(wall_strategy);
	wall_button->move(200, 100);
}

EditorStrategy* MapEditor::GetStrategy() const {
	return strategy_;
}

void MapEditor::SetStrategy(EditorStrategy* strategy) {
	strategy_ = strategy;
}

void MapEditor::Update() {
	if (strategy_) {
		strategy_->Execute();
	}
	update();
}


void MapEditor::mousePressEvent(QMouseEvent* event) {
	if (event->button() == Qt::LeftButton) {
		is_lkm_pressed = true;
	} else if (event->button() == Qt::RightButton) {
		is_pkm_pressed = true;
	}
}

void MapEditor::mouseReleaseEvent(QMouseEvent* event) {
	if (event->button() == Qt::LeftButton) {
		is_lkm_pressed = false;
	} else if (event->button() == Qt::RightButton) {
		is_pkm_pressed = false;
	}
}

bool MapEditor::IsLkmPressed() const {
	return is_lkm_pressed;
}

bool MapEditor::IsPkmPressed() const {
	return is_pkm_pressed;
}

void MapEditor::mouseMoveEvent(QMouseEvent* event) {
	QRectF camera_rect = scene_->GetCamera()->GetCurrentRect();
	
	mouse_pos_ = event->localPos().toPoint();
	mouse_pos_ -= camera_rect.topLeft().toPoint();	
	mouse_pos_ *= (double)EDITOR_HEIGHT / (double)height();
	mouse_pos_ *= (double)EDITOR_HEIGHT / (double)camera_rect.height();

	QWidget::mouseMoveEvent(event);
}

QPoint MapEditor::GetMousePosition() const {
	return mouse_pos_;
}

void MapEditor::Draw() {
	QPainter painter(this);

	painter.setRenderHint(QPainter::Antialiasing);

	scene_->Draw(&painter);
}

MapEditor::~MapEditor() {
	delete scene_;
}

void MapEditor::paintEvent(QPaintEvent*) {
	Draw();
}

void MapEditor::wheelEvent(QWheelEvent* event) {
	scene_->wheelEvent(event);
}

