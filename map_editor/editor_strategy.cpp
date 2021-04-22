#include "editor_strategy.h"

EditorStrategy::EditorStrategy(MapEditor* map_editor, EditorScene* scene) :
	map_editor_(map_editor),
	scene_(scene)
{}

MapEditor* EditorStrategy::GetEditor() const {
	return map_editor_;
}

EditorScene* EditorStrategy::GetScene() const {
	return scene_;
}

