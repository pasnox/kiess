#include "kClient.h"

kClient::kClient()
	: JabberClient()
{
	DiscoItem::Identity identity;
	identity.category = "client";
	identity.type = ARCH_NAME;
	identity.name = APP_NAME;
	
	setClientName( APP_NAME );
	setClientVersion( APP_VERSION );
	setOSName( OS_NAME );
	setDiscoIdentity( identity );
	
	QObject::connect( this, SIGNAL( connected() ), this, SLOT( _q_connected() ) );
	QObject::connect( this, SIGNAL( csAuthenticated() ), this, SLOT( _q_csAuthenticated() ) );
	QObject::connect( this, SIGNAL( csError( int ) ), this, SLOT( _q_csError( int ) ) );
	QObject::connect( this, SIGNAL( csDisconnected() ), this, SLOT( _q_csDisconnected() ) );
	QObject::connect( this, SIGNAL( tlsWarning( QCA::TLS::IdentityResult, QCA::Validity ) ), this, SLOT( _q_tlsWarning( QCA::TLS::IdentityResult, QCA::Validity ) ) );
	QObject::connect( this, SIGNAL( incomingFileTransfer() ), this, SLOT( _q_incomingFileTransfer() ) );
	QObject::connect( this, SIGNAL( error( JabberClient::ErrorCode ) ), this, SLOT( _q_error( JabberClient::ErrorCode ) ) );
	QObject::connect( this, SIGNAL( rosterRequestFinished( bool ) ), this, SLOT( _q_rosterRequestFinished( bool ) ) );
	QObject::connect( this, SIGNAL( newContact( const XMPP::RosterItem& ) ), this, SLOT( _q_newContact( const XMPP::RosterItem& ) ) );
	QObject::connect( this, SIGNAL( contactDeleted( const XMPP::RosterItem& ) ), this, SLOT( _q_contactDeleted( const XMPP::RosterItem& ) ) );
	QObject::connect( this, SIGNAL( contactUpdated( const XMPP::RosterItem& ) ), this, SLOT( _q_contactUpdated( const XMPP::RosterItem& ) ) );
	QObject::connect( this, SIGNAL( resourceAvailable( const XMPP::Jid&, const XMPP::Resource& ) ), this, SLOT( _q_resourceAvailable( const XMPP::Jid&, const XMPP::Resource& ) ) );
	QObject::connect( this, SIGNAL( resourceUnavailable( const XMPP::Jid&, const XMPP::Resource& ) ), this, SLOT( _q_resourceUnavailable( const XMPP::Jid&, const XMPP::Resource& ) ) );
	QObject::connect( this, SIGNAL( messageReceived( const XMPP::Message& ) ), this, SLOT( _q_messageReceived( const XMPP::Message& ) ) );
	QObject::connect( this, SIGNAL( groupChatJoined( const XMPP::Jid& ) ), this, SLOT( _q_groupChatJoined( const XMPP::Jid& ) ) );
	QObject::connect( this, SIGNAL( groupChatLeft( const XMPP::Jid& ) ), this, SLOT( _q_groupChatLeft( const XMPP::Jid& ) ) );
	QObject::connect( this, SIGNAL( groupChatPresence( const XMPP::Jid&, const XMPP::Status& ) ), this, SLOT( _q_groupChatPresence( const XMPP::Jid&, const XMPP::Status& ) ) );
	QObject::connect( this, SIGNAL( groupChatError( const XMPP::Jid&, int, const QString& ) ), this, SLOT( _q_groupChatError( const XMPP::Jid&, int, const QString& ) ) );
	QObject::connect( this, SIGNAL( subscription( const XMPP::Jid&, const QString& ) ), this, SLOT( _q_subscription( const XMPP::Jid&, const QString& ) ) );
	QObject::connect( this, SIGNAL( debugMessage( const QString& ) ), this, SLOT( _q_debugMessage( const QString& ) ) );
	QObject::connect( this, SIGNAL( incomingXML( const QString& ) ), this, SLOT( _q_incomingXML( const QString& ) ) );
	QObject::connect( this, SIGNAL( outgoingXML( const QString& ) ), this, SLOT( _q_outgoingXML( const QString& ) ) );
}

kClient::~kClient()
{
}

void kClient::setPresence( const Status& status )
{
	client()->setPresence( status );
}

void kClient::_q_connected()
{
	emit connected( true );
	//return;
	
	Status status( Status::Online, tr( "Playing Kiess Game" ), 0 );
	//setPresence( status );
	
	joinGroupChat( "conference.jabber.org", "Kiess", "Monkey IDE" );
	
	//requestRoster();
}

void kClient::_q_csAuthenticated()
{
	qWarning() << "csAuthenticated";
}

void kClient::_q_csError( int error )
{
	qWarning() << "csError" << error;
	emit connected( false );
}

void kClient::_q_csDisconnected()
{
	qWarning() << "csDisconnected";
	emit connected( false );
}

void kClient::_q_tlsWarning( QCA::TLS::IdentityResult, QCA::Validity )
{
	qWarning() << "tlsWarning";
}

void kClient::_q_incomingFileTransfer()
{
	qWarning() << "incomingFileTransfer";
}

void kClient::_q_error( JabberClient::ErrorCode code )
{
	qWarning() << "error" << code;
	emit connected( false );
}

void kClient::_q_rosterRequestFinished( bool success )
{
	qWarning() << "rosterRequestFinished" << success;
	
	if ( success )
	{
		Message msg( Jid( "pasnox@gmail.com" ) );
		msg.setFrom( jid() );
		msg.setType( "chat" );
		msg.setBody( "mon message depuis kiess", "fr" );
		msg.addEvent( OfflineEvent );
		msg.addEvent( ComposingEvent );
		msg.addEvent( DeliveredEvent );
		msg.addEvent( DisplayedEvent );
		
		sendMessage( msg );
	}
}

void kClient::_q_newContact( const XMPP::RosterItem& item )
{
	qWarning() << "newContact";
}

void kClient::_q_contactDeleted( const XMPP::RosterItem& item )
{
	qWarning() << "contactDeleted";
}

void kClient::_q_contactUpdated( const XMPP::RosterItem& item )
{
	qWarning() << "contactUpdated";
}

void kClient::_q_resourceAvailable( const XMPP::Jid& jid, const XMPP::Resource& resource )
{
	qWarning() << "resourceAvailable" << jid.full() << resource.name() << resource.status().show() << resource.status().status();
}

void kClient::_q_resourceUnavailable( const XMPP::Jid& jid, const XMPP::Resource& resource )
{
	qWarning() << "resourceUnavailable" << jid.full() << resource.name() << resource.status().show() << resource.status().status();
}

void kClient::_q_messageReceived( const XMPP::Message& message )
{
	qWarning() << "messageReceived";
}

void kClient::_q_groupChatJoined( const XMPP::Jid& jid )
{
	qWarning() << "groupChatJoined";
}

void kClient::_q_groupChatLeft( const XMPP::Jid& jid )
{
	qWarning() << "groupChatLeft";
}

void kClient::_q_groupChatPresence( const XMPP::Jid& jid, const XMPP::Status& status )
{
	qWarning() << "groupChatPresence";
}

void kClient::_q_groupChatError( const XMPP::Jid& jid, int error, const QString& reason )
{
	qWarning() << "groupChatError";
}

void kClient::_q_subscription( const XMPP::Jid& jid, const QString& type )
{
	qWarning() << "subscription" << type;
}

void kClient::_q_debugMessage( const QString& message )
{
	//qWarning() << "debugMessage" << message;
}

void kClient::_q_incomingXML( const QString& msg )
{
	//qWarning() << "incomingXML" << msg;
}

void kClient::_q_outgoingXML( const QString& msg )
{
	//qWarning() << "outgoingXML" << msg;
}
