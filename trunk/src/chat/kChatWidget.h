#ifndef KCHATWIDGET_H
#define KCHATWIDGET_H

#include "ui_kChatWidget.h"
#include "kClient.h"

class kChatWidget : public QFrame, public Ui::kChatWidget
{
	Q_OBJECT

public:
	kChatWidget();
	virtual ~kChatWidget();
	
	kClient* client() const;
	void setClient( kClient* client );

public slots:

protected:
	kClient* mClient;

protected slots:
};

#endif // KCHATWIDGET_H
