#include "editor_widget.h"
#include "qnamespace.h"

#include "../game_core/scene.h"

#include "../game_objects/player.h"
#include "../game_objects/box.h"
#include "../game_objects/floor_button.h"
#include "../game_objects/press_button.h"
#include "../game_objects/spawn_box.h"
#include "../game_objects/finish_area.h"
#include "../wall_mechanics/straight_wall.h"

#include <QDebug>
#include <QPainter>
#include <Qt>
#include <QString>

EditorWidget::EditorWidget(QWidget* parent) :
	GameWidget(parent)
{
	scene_->SetPause(true);
	scene_->SetDebugInfo(true);
}

void EditorWidget::keyPressEvent(QKeyEvent* event) {
	if (!scene_->IsPaused()) {
		if (event->key() == Qt::Key_R) {
			scene_->SetPause(true);
			EditLevel(level_);
		}
		if (event->key() == Qt::Key_Q) {
			StartLevel(level_);
		}
		GameWidget::keyPressEvent(event);
		return;
	}

	if (event->key() == Qt::Key_Return) {
		CommandUpdate();
	} else if (event->key() == Qt::Key_Backspace) {
		command.chop(1);
	} else if (event->key() == Qt::Key_Up) {
		command = last_command;
	} else {
		command += event->text();
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

	if (list.size() == 0) {
		return;
	}

	error = "";

	if (list[0] == "add") {
		AddCommand(list);
	} else if (list[0] == "move") {
		MoveCommand(list);	
	} else if (list[0] == "setpos") {
		SetposCommand(list);
	} else if (list[0] == "rename") {
		RenameCommand(list);
	} else if (list[0] == "remove") {
		RemoveCommand(list);
	} else if (list[0] == "setdir") {
		SetWallDirection(list);
	} else if (list[0] == "setlen") {
		SetWallLen(list);
	} else if (list[0] == "setactive") {
		SwitchWallActive(list);
	} else if (list[0] == "setportable") {
		SwitchWallPortable(list);
	} else if (list[0] == "settimer") {
		SetPressButtonTimer(list);
	} else if (list[0] == "setdebug") {
		SetDebugInfo(list);
	} else if (list[0] == "message") {
		ConnectMessage(list);
	} else if (list[0] == "start") {
		SaveLevel();
		StartLevel(level_);
	} else if (list[0] == ":wall" || list[0] == ":w") {
		SaveLevel();
	} else if (list[0] == ":e") {
		if (list.size() >= 2) {
			EditLevel(list[1].toInt());
		}
	}

	last_command = command;
	command = "";
}


void EditorWidget::AddCommand(const QStringList& list) {
	if (list.size() < 3) {
		error = "Not enough args for add command";
		return;
	}
	ADD_COMMAND(Player);
	ADD_COMMAND(FloorButton);
	ADD_COMMAND(PressButton);
	ADD_COMMAND(SpawnBox);
	ADD_COMMAND(Box);
	ADD_COMMAND(FinishArea);
	ADD_COMMAND(StraightWall);

	scene_->PostUpdate();
	if (list[1] == "StraightWall" && list.size() == 4) {
		QStringList new_list;
		new_list.push_back("setdir");
		new_list.push_back(list[2]);
		new_list.push_back(list[3]);
		SetWallDirection(new_list);
	}
}


void EditorWidget::MoveCommand(const QStringList& list) {
	if (list.size() < 4) {
		error = "Not enough args for move command";
		return;
	}
	if (!scene_->IsOnScene(list[1])) {
		error = "Object with this name don't exist";
		return;
	}

	GameObject* object = scene_->GetObject(list[1]);
	View* view = dynamic_cast<View*>(object);
	if (!view) {
		error = "Not movable";
		return;
	}

	bool ok;
	int x = list[2].toInt(&ok) + view->GetPosition().x();
	if (!ok) {
		error = "Bad coordinates";
		return;
	}
	int y = list[3].toInt(&ok) + view->GetPosition().y();
	if (!ok) {
		error = "Bad coordinates";
		return;
	}
	view->SetPosition(x, y);
}

void EditorWidget::SetposCommand(const QStringList& list) {
	if (list.size() < 4) {
		error = "Not enough args for move command";
		return;
	}
	if (!scene_->IsOnScene(list[1])) {
		error = "Object with this name don't exist";
		return;
	}

	GameObject* object = scene_->GetObject(list[1]);
	View* view = dynamic_cast<View*>(object);
	if (!view) {
		error = "Not movable";
		return;
	}

	bool ok;
	int x = list[2].toInt(&ok);
	if (!ok) {
		error = "Bad coordinates";
		return;
	}
	int y = list[3].toInt(&ok);
	if (!ok) {
		error = "Bad coordinates";
		return;
	}
	view->SetPosition(x, y);
}

void EditorWidget::RenameCommand(const QStringList& list) {
	if (list.size() < 3) {
		error = "Not enough args for rename command";
		return;
	}
	if (!scene_->IsOnScene(list[1])) {
		error = "Object with this name don't exist";
		return;
	}

	scene_->RenameObject(list[1], list[2]);
}

void EditorWidget::RemoveCommand(const QStringList& list) {
	if (list.size() < 2) {
		error = "Not enough args for remove command";
	}
	
	scene_->DeleteObject(list[1]);
}

void EditorWidget::SetWallDirection(const QStringList& list) {
	if (list.size() < 3) {
		error = "Not enough args for setdir command";
	}
	if (!scene_->IsOnScene(list[1])) {
		error = "Object with this name don't exist";
		return;
	}

	GameObject* object = scene_->GetObject(list[1]);
	StraightWall* wall = dynamic_cast<StraightWall*>(object);
	if (!wall) {
		error = "Not wall";
		return;
	}

	Direction dir;
	if (list[2] == "up") {
		dir = Direction::Up;
	} else if (list[2] == "down") {
		dir = Direction::Down;
	} else if (list[2] == "left") {
		dir = Direction::Left;
	} else if (list[2] == "right") {
		dir = Direction::Right;
	} else {
		error = "Wrong direction";
		return;
	}

	wall->SetDirectionAndLen(dir, wall->GetLen());
}

void EditorWidget::SetWallLen(const QStringList& list) {
	if (list.size() < 3) {
		error = "Not enough args for setdir command";
	}
	if (!scene_->IsOnScene(list[1])) {
		error = "Object with this name don't exist";
		return;
	}

	GameObject* object = scene_->GetObject(list[1]);
	StraightWall* wall = dynamic_cast<StraightWall*>(object);
	if (!wall) {
		error = "Not wall";
		return;
	}

	bool ok;
	int len = list[2].toInt(&ok);

	if (!ok) {
		error = "Bad len";
		return;
	}
	wall->SetDirectionAndLen(wall->GetDirection(), len);
}

void EditorWidget::SwitchWallActive(const QStringList& list) {
	if (list.size() < 2) {
		error = "not enough args";
		return;
	}

	GameObject* object = scene_->GetObject(list[1]);
	StraightWall* wall = dynamic_cast<StraightWall*>(object);
	if (!wall) {
		error = "Not wall";
		return;
	}
	
	wall->ChangeActive();
}

void EditorWidget::SwitchWallPortable(const QStringList& list) {
	if (list.size() < 2) {
		error = "not enough args";
		return;
	}

	GameObject* object = scene_->GetObject(list[1]);
	StraightWall* wall = dynamic_cast<StraightWall*>(object);
	if (!wall) {
		error = "Not wall";
		return;
	}
	
	wall->SetPortable(!wall->IsPortable());
}

void EditorWidget::EditLevel(int level) {
	scene_->SetPause(true);
	scene_->ReadFromJson(QString("level%1.json").arg(level));
	level_ = level;
}

void EditorWidget::SaveLevel() {
	scene_->WriteToJson(QString("level%1.json").arg(level_));
}

void EditorWidget::SetPressButtonTimer(const QStringList& list) {
	if (list.size() < 3) {
		error = "not enough args";
		return;
	}

	GameObject* object = scene_->GetObject(list[1]);
	PressButton* button = dynamic_cast<PressButton*>(object);
	if (!button) {
		error = "Not button";
		return;
	}
	
	bool ok;
	int time = list[2].toInt(&ok);
	if (!ok) {
		error = "Bad value";
		return;
	}

	button->SetTimer(time);
}

void EditorWidget::ConnectMessage(const QStringList& list) {
	if (list.size() < 5) {
		error = "not enough args";
		return;
	}
	if (!scene_->IsOnScene(list[3])) {
		error = "object don't exist";
		return;
	}

	Button* button = dynamic_cast<Button*>(scene_->GetObject(list[3]));
	if (!button) {
		error = "It is not button";
		return;
	}
	MessageType m_type;
	QString dest;
	QList<QVariant> params;
	if (list[2] == "SpawnBox") {
		SpawnBox* spawn =
		   	dynamic_cast<SpawnBox*>(scene_->GetObject(list[4]));
		m_type = MessageType::SpawnBox;
		dest = list[4];
		if (!spawn) {
			error = "It is not SpawnBox object";
			return;
		}
	} else if (list[2] == "WallSwitch") {
		for (int i = 4; i < list.size(); i++) {
			Wall* wall = dynamic_cast<Wall*>(scene_->GetObject(list[i]));
			if (!wall) {
				error = "Bad wall";
				return;
			}
			params.push_back(list[i]);
		}
		dest = "Scene";
		m_type = MessageType::WallSwitch;
	} else if (list[2] == "WallPortable") {
		for (int i = 4; i < list.size(); i++) {
			Wall* wall = dynamic_cast<Wall*>(scene_->GetObject(list[i]));
			if (!wall) {
				error = "Bad wall";
				return;
			}
			params.push_back(list[i]);
		}
		dest = "Scene";
		m_type = MessageType::WallPortable;
	} else {
		error = "Bad message type";
		return;
	}

	if (list[1] == "press") {
		button->SetPressMessage(new Message(dest, m_type, params));
	} else if (list[1] == "release") {
		button->SetReleaseMessage(new Message(dest, m_type, params));
	} else {
		error = "press/release only";
		return;
	}
}

void EditorWidget::SetDebugInfo(const QStringList& list) {
	if (list.size() < 2) {
		error = "not enough args";
		return;
	}
	scene_->SetDebugInfo(list[1].toInt());
}

