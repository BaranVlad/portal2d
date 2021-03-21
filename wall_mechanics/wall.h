#ifndef PORTAL2D_WALL_H_
#define PORTAL2D_WALL_H_

#include "../game_core/collide_object.h"
#include <QVector2D>

/* Abstract class for all walls (include ground) */
class Wall : public CollideObject {
protected:
	QVector2D normal_vector_;
	bool is_active_;
public:
	Wall() = delete;
	Wall(Scene* scene,
		   	const QVector2D& normal_vector);

	virtual void Update(qreal delta_time);
	virtual void Draw(QPainter* painter) const;

	bool IsActive() const;
	void SetActive(bool value);
	void ChangeState();

	virtual void DrawActive(QPainter* painter) const = 0;
	virtual void DrawInactive(QPainter* painter) const = 0;
};

#endif

