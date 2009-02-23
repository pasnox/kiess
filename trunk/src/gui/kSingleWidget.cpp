#include "kSingleWidget.h"

#include <QMessageBox>

kSingleWidget::kSingleWidget( kGuiScenePanel* panel )
	: kEmbeddedWidget( panel ),
	mClient( 0 )
{
	setupUi( this );
}

kSingleWidget::~kSingleWidget()
{
	delete mClient;
}

kClient* kSingleWidget::client() const
{
	return mClient;
}

kClient* kSingleWidget::newClient()
{
	delete mClient;
	
	mClient = new kClient();
	
	connect( mClient, SIGNAL( connected( bool ) ), this, SLOT( connected( bool ) ) );
	
	return mClient;
}

void kSingleWidget::connected( bool success )
{
	setEnabled( true );
	
	if ( success )
	{
		emit accepted();
	}
	else
	{
		QMessageBox::information( 0, tr( "Information..." ), tr( "Connexion failed" ) );
	}
}

void kSingleWidget::loadDatas()
{
}

void kSingleWidget::saveDatas()
{
	const QStringList gmail = QStringList( "google" ) << "gmail";
	const QString jid = QString( "%1/%2" ).arg( leJID->text() ).arg( APP_NAME );
	bool isGmail = false;
	
	foreach ( const QString& host, gmail )
	{
		if ( jid.contains( host ) )
		{
			isGmail = true;
			break;
		}
	}
	
	mClient = newClient();
	
	if ( isGmail )
	{
		mClient->setUseXMPP09( true );
		mClient->setUseSSL( true );
		mClient->setOverrideHost( true, "talk.google.com", 5223 );
	}
	
	JabberClient::ErrorCode error = mClient->connect( Jid( jid ), lePassword->text(), true );
	
	if ( error == kClient::Ok )
	{
		setEnabled( false );
	}
	else
	{
		QMessageBox::warning( 0, tr( "Warning..." ), tr( "An error occur while connecting: %1" ).arg( error ) );
	}
}

void kSingleWidget::reject()
{
	emit rejected();
}

void kSingleWidget::accept()
{
	saveDatas();
}
