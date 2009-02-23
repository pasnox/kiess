#ifndef KSINGLEWIDGET_H
#define KSINGLEWIDGET_H

#include "ui_kSingleWidget.h"
#include "kClient.h"

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
	kClient* mClient;
	
	kClient* newClient();

protected slots:
	void connected( bool success );
};

#endif // KSINGLEWIDGET_H
