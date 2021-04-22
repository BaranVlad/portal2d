#ifndef PORTAL2D_WALLS_STRATEGY_H_
#define PORTAL2D_WALLS_STRATEGY_H_

#include "../editor_strategy.h"

class WallsStrategy : public EditorStrategy {
private:
public:
	WallsStrategy(MapEditor* map_editor, EditorScene* scene);
	virtual ~WallsStrategy() = default;

	virtual void Execute();
	virtual void OnStart();

};

#endif

