#ifndef KSINGLEWIDGET_H
#define KSINGLEWIDGET_H

#include "ui_kSingleWidget.h"
#include "kXmppSettings.h"

class kSingleWidget : public kEmbeddedWidget, public Ui::kSingleWidget
{
	Q_OBJECT

public:
	kSingleWidget( kGuiScenePanel* panel );
	virtual ~kSingleWidget();

public slots:
	virtual void loadDatas();
	virtual void saveDatas();
	virtual void reject();
	virtual void accept();

protected:
	kXmppSettings mSettings;
};

#endif // KSINGLEWIDGET_H
