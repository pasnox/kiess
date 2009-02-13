#ifndef KPROPERTIESWIDGET_H
#define KPROPERTIESWIDGET_H

#include "ui_kPropertiesWidget.h"

class kPropertiesWidget : public kEmbeddedWidget, public Ui::kPropertiesWidget
{
	Q_OBJECT

public:
	kPropertiesWidget( kPanel* panel );
	virtual ~kPropertiesWidget();

public slots:
	virtual void loadDatas();
	virtual void saveDatas();
	virtual void reject();
	virtual void accept();
};

#endif // KPROPERTIESWIDGET_H
