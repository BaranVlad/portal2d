#ifndef PORTAL2D_GAME_WIDGET_H_
#define PORTAL2D_GAME_WIDGET_H_

#include <QWidget>
#include <QTimer>

#include "../game_core/scene.h"

#define FPS 2

class GameWidget : public QWidget {
	Q_OBJECT
protected:
	Scene* scene_;
	void Update();

	void paintEvent(QPaintEvent*);
public:
	GameWidget(QWidget* parent = nullptr);
};

#endif

