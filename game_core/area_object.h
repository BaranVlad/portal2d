#ifndef PORTAL2D_AREA_H_
#define PORTAL2D_AREA_H_

#include <QRectF>
#include <QMap>
#include <QString>

#include "view.h"
#include "area.h"

class Scene;

/* Abstract class for all classes that use some rect areas
 * and get signal when areas contact */
class AreaObject : public View {
private:
	QMap<QString, Area*> areas_;
public:
	AreaObject() = delete;
	AreaObject(Scene* scene);
	virtual ~AreaObject();

	virtual void Update();

	void AddArea(const QString& name, const QRectF rect_area);	
	Area* GetArea(const QString& name) const;
	
	QMap::iterator AreasBegin();
	QMap::iterator AreasEnd();

	bool IsAreaActive(const QString& area_name) const;
	void SetAreaActive(const QString& area_name, bool value);

	QPointF GetPosition() const;
};

#endif

