#ifndef PLAYER_STRATEGY_H_
#define PLAYER_STRATEGY_H_

#include <QVector>

#include "../editor_strategy.h"

class PlayerStrategy : public EditorStrategy {
private:
public:
	PlayerStrategy() = delete;
	PlayerStrategy(MapEditor* editor, EditorScene* scene);
	virtual void Execute();
	virtual void OnStart();
};

#endif

