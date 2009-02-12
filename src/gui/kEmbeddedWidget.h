#ifndef KEMBEDDEDWIDGET_H
#define KEMBEDDEDWIDGET_H

#include <QWidget>

class kEmbeddedWidget : public QWidget
{
	Q_OBJECT

public slots:
	virtual void reject() = 0;
	virtual void accept() = 0;

signals:
	void rejected();
	void accepted();
};

#endif // KEMBEDDEDWIDGET_H