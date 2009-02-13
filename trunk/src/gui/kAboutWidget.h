#ifndef KABOUTWIDGET_H
#define KABOUTWIDGET_H

#include "ui_kAboutWidget.h"

struct AboutIdentity
{
	AboutIdentity( const QString& name, const QString& email, const QString& job )
	{
		mName = name;
		mEmail = email;
		mJob = job;
	}
	
	bool operator==( const AboutIdentity& other ) const
	{
		return mName == other.mName && mEmail == other.mEmail && mJob == other.mJob;
	}
	
	bool operator!=( const AboutIdentity& other ) const
	{
		return !operator==( other );
	}
	
	QString mName;
	QString mEmail;
	QString mJob;
};

typedef QList<AboutIdentity> AboutIdentities;

class kAboutWidget : public kEmbeddedWidget, public Ui::kAboutWidget
{
	Q_OBJECT

public:
	kAboutWidget( kPanel* panel );
	virtual ~kAboutWidget();

public slots:
	virtual void loadDatas();
	virtual void saveDatas();
	virtual void reject();
	virtual void accept();

protected:
	AboutIdentities mAboutIdentities;
};

#endif // KABOUTWIDGET_H
