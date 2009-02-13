#ifndef KSINGLEWIDGET_H
#define KSINGLEWIDGET_H

#include "ui_kSingleWidget.h"

class kSingleWidget : public kEmbeddedWidget, public Ui::kSingleWidget
{
	Q_OBJECT

public:
	kSingleWidget();
	virtual ~kSingleWidget();

public slots:
	virtual void loadDatas();
	virtual void saveDatas();
	virtual void reject();
	virtual void accept();
};

#endif // KSINGLEWIDGET_H
