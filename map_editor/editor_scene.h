#ifndef EDITOR_SCENE_H_
#define EDITOR_SCENE_H_

#include "../game_core/scene.h"

class EditorScene : public Scene {
private:
public:
	EditorScene(QObject* parent = nullptr);
	void SaveMapToJson(const QString& file_name) const;

	void Update(qreal delta_time);
};

#endif

