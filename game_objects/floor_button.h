#ifndef PORTAL2D_FLOOR_BUTTON_H_
#define PORTAL2D_FLOOR_BUTTON_H_

#include "../game_core/button.h"

#define BUTTON_WIDTH 50
#define BUTTON_HEIGHT 10

class FloorButton : public Button {
private:
public:
	FloorButton() = delete;
	FloorButton(Scene* scene);

	virtual void Update();
	virtual void Draw(QPainter* painter) const;
};

#endif

