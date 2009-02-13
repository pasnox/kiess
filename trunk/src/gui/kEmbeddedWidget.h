#ifndef KEMBEDDEDWIDGET_H
#define KEMBEDDEDWIDGET_H

#include <QWidget>

class kEmbeddedWidget : public QWidget
{
	Q_OBJECT

public slots:
	virtual void loadDatas() = 0;
	virtual void saveDatas() = 0;
	virtual void reject() = 0;
	virtual void accept() = 0;
};

#endif // KEMBEDDEDWIDGET_H
