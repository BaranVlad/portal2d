#include "editor_widget.h"
#include "qnamespace.h"

#include "../game_core/scene.h"

#include "../game_objects/player.h"
#include "../game_objects/box.h"
#include "../game_objects/floor_button.h"
#include "../game_objects/press_button.h"
#include "../game_objects/spawn_box.h"
#include "../game_objects/finish_area.h"
#include "../wall_mechanics/wall_map.h"
#include "../wall_mechanics/straight_wall.h"

#include <QDebug>
#include <QPainter>
#include <Qt>
#include <QString>

EditorWidget::EditorWidget(QWidget* parent) :
	GameWidget(parent)
{
	scene_->SetDebugInfo(true);
}

void EditorWidget::keyPressEvent(QKeyEvent* event) {
	if (event->key() == Qt::Key_Return) {
		CommandUpdate();
	} else if (event->key() == Qt::Key_Backspace) {
		command.chop(1);
	} else if (event->key() == Qt::Key_Up) {
		command = last_command;
	} else {
		command += event->text();
	}

	if (!scene_->IsPaused()) {
		GameWidget::keyPressEvent(event);
	}
}

void EditorWidget::Update() {
	GameWidget::Update();
}

void EditorWidget::paintEvent(QPaintEvent* event) {
	QPainter painter(this);
	painter.drawText(10, 10, command);
	painter.drawText(20, 20, error);
	painter.end();

	GameWidget::paintEvent(event);
}

#define ADD_COMMAND(class_t) 		\
if (list[1] == #class_t) {			\
	class_t* obj = new class_t(scene_);	\
	scene_->AddGameObject(list[2], obj);		\
}

void EditorWidget::CommandUpdate() {
	QStringList list = command.split(' ');
	list.removeAll("");

	if (list[0] == "add") {
		if (list.size() < 3) {
			error = "Not enough args for add command";
			goto comm_q;
		}
		ADD_COMMAND(Player);
		ADD_COMMAND(FloorButton);
		ADD_COMMAND(PressButton);
		ADD_COMMAND(SpawnBox);
		ADD_COMMAND(Box);
		ADD_COMMAND(FinishArea);
	} else if (list[0] == "move") {
		if (list.size() < 4) {
			error = "Not enough args for move command";
			goto comm_q;
		}
		if (!scene_->IsOnScene(list[1])) {
			error = "Object with this name don't exist";
			goto comm_q;
		}

		GameObject* object = scene_->GetObject(list[1]);
		View* view = dynamic_cast<View*>(object);
		if (!view) {
			error = "Not movable";
			goto comm_q;
		}

		bool ok;
		int x = list[2].toInt(&ok) + view->GetPosition().x();
		if (!ok) {
			error = "Bad coordinates";
			goto comm_q;
		}
		int y = list[3].toInt(&ok) + view->GetPosition().y();
		if (!ok) {
			error = "Bad coordinates";
			goto comm_q;
		}
		view->SetPosition(x, y);
	}

comm_q:
	last_command = command;
	command = "";
}

