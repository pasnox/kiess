#ifndef KEMBEDDEDWIDGET_H
#define KEMBEDDEDWIDGET_H

#include <QFrame>

class kGuiScenePanel;

class kEmbeddedWidget : public QFrame
{
	Q_OBJECT

public:
	kEmbeddedWidget( kGuiScenePanel* panel )
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
	kGuiScenePanel* mPanel;
};

#endif // KEMBEDDEDWIDGET_H
