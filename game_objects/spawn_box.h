#ifndef PORTAL2D_SPAWN_BOX_H_
#define PORTAL2D_SPAWN_BOX_H_

#include "../game_core/view.h"

class Box;

class SpawnBox : public View {
private:
	QRectF box_rect;
	Box* box_ = nullptr;
	
public:
	SpawnBox() = delete;	
	SpawnBox(Scene* scene);

	virtual void Update();
	virtual void Draw(QPainter* painter) const;
	virtual void TakeMessage(Message* message);
	virtual qreal GetWidth() const;
	virtual qreal GetHeight() const;

	void SetBoxName() const;

	virtual void ToJsonObject(QJsonObject& js) const;
	virtual void FromJsonObject(const QJsonObject& js);
	
	void CreateBox();
};

#endif

