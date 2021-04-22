#include "player_strategy.h"

#include "../editor_scene.h"
#include "../map_editor.h"

#include "../../game_objects/player.h"

PlayerStrategy::PlayerStrategy(MapEditor* editor, EditorScene* scene) :
	EditorStrategy(editor, scene)
{}

void PlayerStrategy::Execute() {
	QVector2D mouse_vec(map_editor_->GetMousePosition());
	qDebug() << mouse_vec;
	scene_->SetGameObjectPosition("Player", mouse_vec);
	if (map_editor_->IsLkmPressed()) {
		map_editor_->SetStrategy(nullptr);
	}
}
  
void PlayerStrategy::OnStart() {
	if (scene_->IsOnScene("Player")) {
		qDebug() << "Player alrady on scene\n";
		map_editor_->SetStrategy(nullptr);
		return;
	}
	QVector2D mouse_vec(map_editor_->GetMousePosition());
	Player* player = new Player(scene_);
	player->SetPosition(mouse_vec);
	scene_->AddGameObject("Player", player);
}

