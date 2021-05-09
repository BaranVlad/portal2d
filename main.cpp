#include <QApplication>
#include "map_editor/editor_widget.h"
#include "game_widget/game_widget.h"

int main(int argc, char** argv) {
	QApplication app(argc, argv);	

	EditorWidget widget;
	widget.show();

	return app.exec();
}
