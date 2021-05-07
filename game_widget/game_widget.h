#ifndef PORTAL2D_GAME_WIDGET_H_
#define PORTAL2D_GAME_WIDGET_H_

#include <QWidget>
#include <QTimer>
#include <QElapsedTimer>
#include <QKeyEvent>

#define FPS 60

class Scene;

class GameWidget : public QWidget {
	Q_OBJECT
protected:
	Scene* scene_;
	QElapsedTimer clock_;

	void Update();

	void keyPressEvent(QKeyEvent*);
	void keyReleaseEvent(QKeyEvent*);
	void paintEvent(QPaintEvent*);
	void wheelEvent(QWheelEvent*);
	void mouseMoveEvent(QMouseEvent*);
	void mousePressEvent(QMouseEvent*);
	void mouseReleaseEvent(QMouseEvent*);
	void resizeEvent(QResizeEvent*);
public:
	GameWidget(QWidget* parent = nullptr);
	~GameWidget();
};

#endif

