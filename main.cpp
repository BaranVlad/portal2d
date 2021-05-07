#include <QApplication>
#include "map_editor/map_editor.h"
#include "game_widget/game_widget.h"

int main(int argc, char** argv) {
	QApplication app(argc, argv);	

	GameWidget widget;
	widget.show();

	return app.exec();
}
