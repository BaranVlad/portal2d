#ifndef PORTAL2D_EDITOR_WIDGET_H_
#define PORTAL2D_EDITOR_WIDGET_H_

#include "../game_widget/game_widget.h"

/* :e - open new level
 * :wall - save level
 * start - start current level
 * add [class] [name] - add new object [class] type with name [name]
 * set[command] [name] [args..] - set some field [name] object with [argc]
 * message [press/release] [message_type] [reciever] [message_args]
*/

class EditorWidget : public GameWidget {
private:
	QString command = "";
	QString last_command = "";
	QString error = "";

	int level_ = 0;
protected:
	void keyPressEvent(QKeyEvent* event);
	void paintEvent(QPaintEvent* event);
public:
	EditorWidget(QWidget* parent = nullptr);	
	void Update();

	void CommandUpdate();
	void AddCommand(const QStringList& list);
	void MoveCommand(const QStringList& list);
	void RemoveCommand(const QStringList& list);
	void RenameCommand(const QStringList& list);
	void SetposCommand(const QStringList& list);

	void SetPressButtonTimer(const QStringList& list);
	void SetWallDirection(const QStringList& list);
	void SetWallLen(const QStringList& list);
	void SwitchWallActive(const QStringList& list);
	void SwitchWallPortable(const QStringList& list);
	void SetDebugInfo(const QStringList& list);

	void ConnectMessage(const QStringList& list);

	void EditLevel(int level);
	void SaveLevel();
};

#endif

