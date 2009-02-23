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
	QObject::connect( this, SIGNAL( error( JabberClient::ErrorCode ) ), this, SLOT( _q_error( JabberClient::ErrorCode ) ) );
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
	qWarning() << "connected";
	emit connected( true );
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

void kClient::_q_error( JabberClient::ErrorCode code )
{
	qWarning() << "error" << code;
	emit connected( false );
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
