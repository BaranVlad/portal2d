#ifndef PORTAL2D_FINISH_AREA_H_
#define PORTAL2D_FINISH_AREA_H_

#include <QPainter>

#include "../game_core/area_object.h"

class FinishArea : public AreaObject {
private:
	QRectF finish_rect_;
public:
	FinishArea() = delete;
	FinishArea(Scene* scene);
	virtual ~FinishArea();
	
	virtual void Draw(QPainter* painter) const;
	virtual void Update();

	virtual qreal GetWidth() const;
	virtual qreal GetHeight() const;

	virtual void ToJsonObject(QJsonObject& js) const;
	virtual void FromJsonObject(const QJsonObject& js);
};

#endif

