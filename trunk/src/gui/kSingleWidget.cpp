#include "kSingleWidget.h"

kSingleWidget::kSingleWidget( kGuiScenePanel* panel )
	: kEmbeddedWidget( panel )
{
	mClient = 0;
	setupUi( this );
}

kSingleWidget::~kSingleWidget()
{
	delete mClient;
}

JabberClient* kSingleWidget::newClient()
{
	delete mClient;
	
	mClient = new JabberClient();
	
	connect( mClient, SIGNAL( connected() ), this, SLOT( connected() ) );
	connect( mClient, SIGNAL( csAuthenticated() ), this, SLOT( csAuthenticated() ) );
	connect( mClient, SIGNAL( csError( int ) ), this, SLOT( csError( int ) ) );
	connect( mClient, SIGNAL( csDisconnected() ), this, SLOT( csDisconnected() ) );
	connect( mClient, SIGNAL( tlsWarning( QCA::TLS::IdentityResult, QCA::Validity ) ), this, SLOT( tlsWarning( QCA::TLS::IdentityResult, QCA::Validity ) ) );
	connect( mClient, SIGNAL( incomingFileTransfer() ), this, SLOT( incomingFileTransfer() ) );
	connect( mClient, SIGNAL( error( JabberClient::ErrorCode ) ), this, SLOT( error( JabberClient::ErrorCode ) ) );
	connect( mClient, SIGNAL( rosterRequestFinished( bool ) ), this, SLOT( rosterRequestFinished( bool ) ) );
	connect( mClient, SIGNAL( newContact( const XMPP::RosterItem& ) ), this, SLOT( newContact( const XMPP::RosterItem& ) ) );
	connect( mClient, SIGNAL( contactDeleted( const XMPP::RosterItem& ) ), this, SLOT( contactDeleted( const XMPP::RosterItem& ) ) );
	connect( mClient, SIGNAL( contactUpdated( const XMPP::RosterItem& ) ), this, SLOT( contactUpdated( const XMPP::RosterItem& ) ) );
	connect( mClient, SIGNAL( resourceAvailable( const XMPP::Jid&, const XMPP::Resource& ) ), this, SLOT( resourceAvailable( const XMPP::Jid&, const XMPP::Resource& ) ) );
	connect( mClient, SIGNAL( resourceUnavailable( const XMPP::Jid&, const XMPP::Resource& ) ), this, SLOT( resourceUnavailable( const XMPP::Jid&, const XMPP::Resource& ) ) );
	connect( mClient, SIGNAL( messageReceived( const XMPP::Message& ) ), this, SLOT( messageReceived( const XMPP::Message& ) ) );
	connect( mClient, SIGNAL( groupChatJoined( const XMPP::Jid& ) ), this, SLOT( groupChatJoined( const XMPP::Jid& ) ) );
	connect( mClient, SIGNAL( groupChatLeft( const XMPP::Jid& ) ), this, SLOT( groupChatLeft( const XMPP::Jid& ) ) );
	connect( mClient, SIGNAL( groupChatPresence( const XMPP::Jid&, const XMPP::Status& ) ), this, SLOT( groupChatPresence( const XMPP::Jid&, const XMPP::Status& ) ) );
	connect( mClient, SIGNAL( groupChatError( const XMPP::Jid&, int, const QString& ) ), this, SLOT( groupChatError( const XMPP::Jid&, int, const QString& ) ) );
	connect( mClient, SIGNAL( subscription( const XMPP::Jid&, const QString& ) ), this, SLOT( subscription( const XMPP::Jid&, const QString& ) ) );
	connect( mClient, SIGNAL( debugMessage( const QString& ) ), this, SLOT( debugMessage( const QString& ) ) );
	connect( mClient, SIGNAL( incomingXML( const QString& ) ), this, SLOT( incomingXML( const QString& ) ) );
	connect( mClient, SIGNAL( outgoingXML( const QString& ) ), this, SLOT( outgoingXML( const QString& ) ) );
	
	return mClient;
}

// client signals

void kSingleWidget::connected()
{
	qWarning() << "connected";
	
	mClient->requestRoster();
}

void kSingleWidget::csAuthenticated()
{
	qWarning() << "csAuthenticated";
}

void kSingleWidget::csError( int error )
{
	qWarning() << "csError" << error;
}

void kSingleWidget::csDisconnected()
{
	qWarning() << "csDisconnected";
}

void kSingleWidget::tlsWarning( QCA::TLS::IdentityResult, QCA::Validity )
{
	qWarning() << "tlsWarning";
}

void kSingleWidget::incomingFileTransfer()
{
	qWarning() << "incomingFileTransfer";
}

void kSingleWidget::error( JabberClient::ErrorCode code )
{
	qWarning() << "error" << code;
}

void kSingleWidget::rosterRequestFinished( bool success )
{
	qWarning() << "rosterRequestFinished" << success;
	
	if ( success )
	{
		//ogoffart@bepointbe.be
		Message msg( Jid( "richard.groult@gmail.com" ) );
		msg.setFrom( mClient->jid() );
		msg.setType( "chat" );
		msg.setBody( "mon message depuis kiess", "fr" );
		msg.addEvent( OfflineEvent );
		msg.addEvent( ComposingEvent );
		msg.addEvent( DeliveredEvent );
		msg.addEvent( DisplayedEvent );
		
		mClient->sendMessage( msg );
	}
}

void kSingleWidget::newContact( const XMPP::RosterItem& item )
{
	qWarning() << "newContact";
}

void kSingleWidget::contactDeleted( const XMPP::RosterItem& item )
{
	qWarning() << "contactDeleted";
}

void kSingleWidget::contactUpdated( const XMPP::RosterItem& item )
{
	qWarning() << "contactUpdated";
}

void kSingleWidget::resourceAvailable( const XMPP::Jid& jid, const XMPP::Resource& resource )
{
	qWarning() << "resourceAvailable";
}

void kSingleWidget::resourceUnavailable( const XMPP::Jid& jid, const XMPP::Resource& resource )
{
	qWarning() << "resourceUnavailable";
}

void kSingleWidget::messageReceived( const XMPP::Message& message )
{
	qWarning() << "messageReceived";
}

void kSingleWidget::groupChatJoined( const XMPP::Jid& jid )
{
	qWarning() << "groupChatJoined";
}

void kSingleWidget::groupChatLeft( const XMPP::Jid& jid )
{
	qWarning() << "groupChatLeft";
}

void kSingleWidget::groupChatPresence( const XMPP::Jid& jid, const XMPP::Status& status )
{
	qWarning() << "groupChatPresence";
}

void kSingleWidget::groupChatError( const XMPP::Jid& jid, int error, const QString& reason )
{
	qWarning() << "groupChatError";
}

void kSingleWidget::subscription( const XMPP::Jid& jid, const QString& type )
{
	qWarning() << "subscription" << type;
}

void kSingleWidget::debugMessage( const QString& message )
{
	//qWarning() << "debugMessage" << message;
}

void kSingleWidget::incomingXML( const QString& msg )
{
	qWarning() << "incomingXML" << msg;
}

void kSingleWidget::outgoingXML( const QString& msg )
{
	qWarning() << "outgoingXML" << msg;
}

// end client signals

void kSingleWidget::loadDatas()
{
}

void kSingleWidget::saveDatas()
{
	const QStringList gmail = QStringList( "google" ) << "gmail";
	const QString jid = leJID->text().append( "/Kiess" );
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
	qWarning() << error << ( error != JabberClient::Ok ? "Error" : "No Error" );
}

void kSingleWidget::reject()
{
	emit rejected();
}

void kSingleWidget::accept()
{
	saveDatas();
	//emit accepted();
}
