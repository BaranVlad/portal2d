#ifndef PORTAL2D_EDITOR_WIDGET_H_
#define PORTAL2D_EDITOR_WIDGET_H_

#include "../game_widget/game_widget.h"

class EditorWidget : public GameWidget {
private:
	QString command = "";
	QString last_command = "";
	QString error = "";
protected:
	void keyPressEvent(QKeyEvent* event);
	void paintEvent(QPaintEvent* event);
public:
	EditorWidget(QWidget* parent = nullptr);	
	void Update();

	void CommandUpdate();

};

#endif

