#ifndef PORTAL2D_WALL_MAP_H_
#define PORTAL2D_WALL_MAP_H_

#include "../game_core/collide_object.h"
#include "wall.h"

#include <QVector>
#include <QMap>

class WallMap : public CollideObject {
private:
	QMap<QString, QVector<Wall*>> groups_;
public:
	WallMap(Scene* scene);
	virtual ~WallMap();

	virtual void Update();
	virtual void Draw(QPainter* painter) const;

	void AddWall(Wall* wall);
	void AddWallGroup(const QString& name);
	void AddWallToGroup(const QString& name, Wall* wall);
	bool IsGroupExist(const QString& name);

	QList<Wall*> GetWalls() const;

	void SwitchGroup(const QString& name);

	virtual void TakeMessage(Message* msg);
};

#endif

