#ifndef KPROPERTIESWIDGET_H
#define KPROPERTIESWIDGET_H

#include "ui_kPropertiesWidget.h"

class kPropertiesWidget : public kEmbeddedWidget, public Ui::kPropertiesWidget
{
	Q_OBJECT

public:
	kPropertiesWidget();
	virtual ~kPropertiesWidget();

public slots:
	virtual void reject();
	virtual void accept();
};

#endif // KPROPERTIESWIDGET_H
