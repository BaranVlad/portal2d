#ifndef PORTAL2D_MAP_EDITOR_H_
#define PORTAL2D_MAP_EDITOR_H_

#include <QWidget>
#include <QPoint>
#include <QTimer>

#include "editor_strategy.h"

#define EDITOR_FPS 60
#define EDITOR_WIDTH 800
#define EDITOR_HEIGHT 600

class GameObject;
class EditorScene;

class MapEditor : public QWidget {
	Q_OBJECT
private:
	EditorStrategy* strategy_;

	bool is_lkm_pressed = false;
	bool is_pkm_pressed = false;
	QPoint mouse_pos_;
	EditorScene* scene_;
protected:
	void wheelEvent(QWheelEvent*);
	void mousePressEvent(QMouseEvent*);
	void mouseReleaseEvent(QMouseEvent*);
	void mouseMoveEvent(QMouseEvent*);
	void paintEvent(QPaintEvent*);
public:
	MapEditor(QWidget* parent = nullptr);
	~MapEditor();

	EditorStrategy* GetStrategy() const;
	void SetStrategy(EditorStrategy* strategy);

	bool IsLkmPressed() const;
	bool IsPkmPressed() const;
	QPoint GetMousePosition() const;
	
	void Update();
	void Draw();

	void SaveMapToJson() const;
};

#endif

