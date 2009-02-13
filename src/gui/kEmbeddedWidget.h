#ifndef KEMBEDDEDWIDGET_H
#define KEMBEDDEDWIDGET_H

#include <QFrame>

class kPanel;

class kEmbeddedWidget : public QFrame
{
	Q_OBJECT

public:
	kEmbeddedWidget( kPanel* panel )
	{
		Q_ASSERT( panel );
		mPanel = panel;
	}

public slots:
	virtual void loadDatas() = 0;
	virtual void saveDatas() = 0;
	virtual void reject() = 0;
	virtual void accept() = 0;

protected:
	kPanel* mPanel;
};

#endif // KEMBEDDEDWIDGET_H
