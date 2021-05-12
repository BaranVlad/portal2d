#ifndef PORTAL2D_WALL_H_
#define PORTAL2D_WALL_H_

#include "../game_core/collide_object.h"
#include <QVector2D>

/* Abstract class for all walls (include ground) */
class Wall : public CollideObject {
protected:
	QVector2D normal_vector_;
	bool is_active_ = true;
	bool is_portable_ = false;
public:
	Wall() = delete;
	Wall(Scene* scene);

	virtual void Draw(QPainter* painter) const;

	bool IsActive() const;
	void SetActive(bool value);
	void ChangeActive();

	bool IsPortable() const;
	void SetPortable(bool value);
	void SetNormalVector(const QVector2D& normal_vec);

	virtual void DrawActive(QPainter* painter) const = 0;
	virtual void DrawInactive(QPainter* painter) const = 0;
	virtual void CreatePortal();

	virtual void ToJsonObject(QJsonObject& js) const;
	virtual void FromJsonObject(const QJsonObject& js);
};

#endif

