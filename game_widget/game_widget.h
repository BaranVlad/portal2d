#ifndef PORTAL2D_GAME_WIDGET_H_
#define PORTAL2D_GAME_WIDGET_H_

#include <QWidget>
#include <QTimer>
#include <QElapsedTimer>
#include <QKeyEvent>

#include "../game_core/scene.h"

#define FPS 30

class GameWidget : public QWidget {
	Q_OBJECT
protected:
	Scene* scene_;
	QElapsedTimer clock_;

	void Update();
	void keyPressEvent(QKeyEvent*);
	void keyReleaseEvent(QKeyEvent*);
	void paintEvent(QPaintEvent*);
public:
	GameWidget(QWidget* parent = nullptr);
};

#endif

