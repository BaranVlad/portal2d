#include "item_button.h"

#include "map_editor.h"
#include <QPainter>

ItemButton::ItemButton(QWidget* parent) :
	QAbstractButton(parent)
{
	setGeometry(100, 100, 50, 50);
	setFocusPolicy(Qt::ClickFocus);
	connect(this, &QAbstractButton::pressed, this, &ItemButton::Pressed);
}

EditorStrategy* ItemButton::GetStrategy() const {
	return strategy_;
}

void ItemButton::SetStrategy(EditorStrategy* strategy) {
	strategy_ = strategy;	
}

ItemButton::~ItemButton() {
	delete strategy_;	
}

void ItemButton::Pressed() {
	strategy_->GetEditor()->SetStrategy(strategy_);
	strategy_->OnStart();
	strategy_->GetEditor()->setFocus();
}

void ItemButton::paintEvent(QPaintEvent* event) {
	QPainter painter(this);
	painter.setPen(Qt::black);
	painter.setBrush(Qt::white);

	painter.drawRect(0, 0, width(), height());
}

