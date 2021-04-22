#ifndef PORTAL2D_EDITOR_STRATEGY_H_
#define PORTAL2D_EDITOR_STRATEGY_H_

class MapEditor;
class EditorScene;

class EditorStrategy {
protected:
	MapEditor* map_editor_;
	EditorScene* scene_;
public:
	EditorStrategy(MapEditor* map_editor, EditorScene* scene);
	virtual ~EditorStrategy() = default;

	virtual void Execute() = 0;
	virtual void OnStart() = 0;

	MapEditor* GetEditor() const;
	EditorScene* GetScene() const;
};

#endif

