#ifndef PORTAL2D_AREA_H_
#define PORTAL2D_AREA_H_

#include <QRectF>
#include <QMap>
#include <QString>
#include <QVector>

#include "view.h"
#include "area.h"

class Scene;

/* Abstract class for all classes that use some rect areas
 * and get signal when areas contact */
class AreaObject : public View {
private:
	/* AreaObject provide groups of areas that united by string id */
	mutable QMap<QString, QVector<Area*>> areas_;
public:
	AreaObject() = delete;
	AreaObject(Scene* scene);
	virtual ~AreaObject();

	virtual void Update();

	bool IsGroupExist(const QString& name) const;
	void AddGroup(const QString& name);
	void AddAreaToGroup(const QString& name, Area* area);
	
	QVector<Area*>& GetAreasViaGroupName(const QString& name) const;

	QList<Area*> GetAreas() const;
	QList<QString> GetGroups() const;
	
	QPointF GetPosition() const;
};

#endif

