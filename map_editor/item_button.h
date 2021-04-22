#ifndef PORTAL2D_ITEM_BUTTON_H_
#define PORTAL2D_ITEM_BUTTON_H_

#include <QAbstractButton>
#include "editor_strategy.h"

class ItemButton : public QAbstractButton {
	Q_OBJECT
private:
	EditorStrategy* strategy_;
protected:
	void Pressed();
	void paintEvent(QPaintEvent*);
public:
	ItemButton(QWidget* parent = nullptr);
	~ItemButton();

	EditorStrategy* GetStrategy() const;
	void SetStrategy(EditorStrategy* strategy);
};

#endif

