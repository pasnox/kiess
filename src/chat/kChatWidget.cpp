#include "kChatWidget.h"

#include <QMessageBox>

const QString mKiessHost = "conference.jabber.org";
const QString mKiessRoom = "kiess";
const QString mKiessFull = "kiess@conference.jabber.org";

kChatWidget::kChatWidget()
	: QFrame( 0 ),
	mClient( 0 )
{
	setupUi( this );
}

kChatWidget::~kChatWidget()
{
}

kClient* kChatWidget::client() const
{
	return mClient;
}

void kChatWidget::setClient( kClient* client, const QString& nick )
{
	if ( mClient != client )
	{
		if ( mClient )
		{
			disconnect( mClient, SIGNAL( incomingFileTransfer() ), this, SLOT( _q_incomingFileTransfer() ) );
			disconnect( mClient, SIGNAL( rosterRequestFinished( bool ) ), this, SLOT( _q_rosterRequestFinished( bool ) ) );
			disconnect( mClient, SIGNAL( newContact( const XMPP::RosterItem& ) ), this, SLOT( _q_newContact( const XMPP::RosterItem& ) ) );
			disconnect( mClient, SIGNAL( contactDeleted( const XMPP::RosterItem& ) ), this, SLOT( _q_contactDeleted( const XMPP::RosterItem& ) ) );
			disconnect( mClient, SIGNAL( contactUpdated( const XMPP::RosterItem& ) ), this, SLOT( _q_contactUpdated( const XMPP::RosterItem& ) ) );
			disconnect( mClient, SIGNAL( resourceAvailable( const XMPP::Jid&, const XMPP::Resource& ) ), this, SLOT( _q_resourceAvailable( const XMPP::Jid&, const XMPP::Resource& ) ) );
			disconnect( mClient, SIGNAL( resourceUnavailable( const XMPP::Jid&, const XMPP::Resource& ) ), this, SLOT( _q_resourceUnavailable( const XMPP::Jid&, const XMPP::Resource& ) ) );
			disconnect( mClient, SIGNAL( messageReceived( const XMPP::Message& ) ), this, SLOT( _q_messageReceived( const XMPP::Message& ) ) );
			disconnect( mClient, SIGNAL( groupChatJoined( const XMPP::Jid& ) ), this, SLOT( _q_groupChatJoined( const XMPP::Jid& ) ) );
			disconnect( mClient, SIGNAL( groupChatLeft( const XMPP::Jid& ) ), this, SLOT( _q_groupChatLeft( const XMPP::Jid& ) ) );
			disconnect( mClient, SIGNAL( groupChatPresence( const XMPP::Jid&, const XMPP::Status& ) ), this, SLOT( _q_groupChatPresence( const XMPP::Jid&, const XMPP::Status& ) ) );
			disconnect( mClient, SIGNAL( groupChatError( const XMPP::Jid&, int, const QString& ) ), this, SLOT( _q_groupChatError( const XMPP::Jid&, int, const QString& ) ) );
			disconnect( mClient, SIGNAL( subscription( const XMPP::Jid&, const QString& ) ), this, SLOT( _q_subscription( const XMPP::Jid&, const QString& ) ) );
		}
		
		mClient = client;
		
		if ( mClient )
		{
			connect( mClient, SIGNAL( incomingFileTransfer() ), this, SLOT( _q_incomingFileTransfer() ) );
			connect( mClient, SIGNAL( rosterRequestFinished( bool ) ), this, SLOT( _q_rosterRequestFinished( bool ) ) );
			connect( mClient, SIGNAL( newContact( const XMPP::RosterItem& ) ), this, SLOT( _q_newContact( const XMPP::RosterItem& ) ) );
			connect( mClient, SIGNAL( contactDeleted( const XMPP::RosterItem& ) ), this, SLOT( _q_contactDeleted( const XMPP::RosterItem& ) ) );
			connect( mClient, SIGNAL( contactUpdated( const XMPP::RosterItem& ) ), this, SLOT( _q_contactUpdated( const XMPP::RosterItem& ) ) );
			connect( mClient, SIGNAL( resourceAvailable( const XMPP::Jid&, const XMPP::Resource& ) ), this, SLOT( _q_resourceAvailable( const XMPP::Jid&, const XMPP::Resource& ) ) );
			connect( mClient, SIGNAL( resourceUnavailable( const XMPP::Jid&, const XMPP::Resource& ) ), this, SLOT( _q_resourceUnavailable( const XMPP::Jid&, const XMPP::Resource& ) ) );
			connect( mClient, SIGNAL( messageReceived( const XMPP::Message& ) ), this, SLOT( _q_messageReceived( const XMPP::Message& ) ) );
			connect( mClient, SIGNAL( groupChatJoined( const XMPP::Jid& ) ), this, SLOT( _q_groupChatJoined( const XMPP::Jid& ) ) );
			connect( mClient, SIGNAL( groupChatLeft( const XMPP::Jid& ) ), this, SLOT( _q_groupChatLeft( const XMPP::Jid& ) ) );
			connect( mClient, SIGNAL( groupChatPresence( const XMPP::Jid&, const XMPP::Status& ) ), this, SLOT( _q_groupChatPresence( const XMPP::Jid&, const XMPP::Status& ) ) );
			connect( mClient, SIGNAL( groupChatError( const XMPP::Jid&, int, const QString& ) ), this, SLOT( _q_groupChatError( const XMPP::Jid&, int, const QString& ) ) );
			connect( mClient, SIGNAL( subscription( const XMPP::Jid&, const QString& ) ), this, SLOT( _q_subscription( const XMPP::Jid&, const QString& ) ) );
			
			Status status( Status::Online, tr( "Playing Kiess Game" ), 0 );
			mClient->setPresence( status );
			
			mClient->joinGroupChat( mKiessHost, mKiessRoom, nick );
	
			//requestRoster();
		}
	}
}

void kChatWidget::_q_incomingFileTransfer()
{
	qWarning() << "incomingFileTransfer";
}

void kChatWidget::_q_rosterRequestFinished( bool success )
{
	qWarning() << "rosterRequestFinished" << success;
}

void kChatWidget::_q_newContact( const XMPP::RosterItem& item )
{
	qWarning() << "newContact";
}

void kChatWidget::_q_contactDeleted( const XMPP::RosterItem& item )
{
	qWarning() << "contactDeleted";
}

void kChatWidget::_q_contactUpdated( const XMPP::RosterItem& item )
{
	qWarning() << "contactUpdated";
}

void kChatWidget::_q_resourceAvailable( const XMPP::Jid& jid, const XMPP::Resource& resource )
{
	qWarning() << "resourceAvailable" << jid.full() << resource.name() << resource.status().show() << resource.status().status();
}

void kChatWidget::_q_resourceUnavailable( const XMPP::Jid& jid, const XMPP::Resource& resource )
{
	qWarning() << "resourceUnavailable" << jid.full() << resource.name() << resource.status().show() << resource.status().status();
}

void kChatWidget::_q_messageReceived( const XMPP::Message& message )
{
	QString text = QString( "[%1] %2: %3" )// (%4)" )
		.arg( QTime::currentTime().toString( "hh:mm" ) )
		.arg( message.from().resource() )
		.arg( message.body() );
		//.arg( message.subject() );
	
	pteChat->appendPlainText( text );
}

void kChatWidget::_q_groupChatJoined( const XMPP::Jid& jid )
{
	qWarning() << "groupChatJoined" << jid.full();
}

void kChatWidget::_q_groupChatLeft( const XMPP::Jid& jid )
{
	qWarning() << "groupChatLeft" << jid.full();
}

void kChatWidget::_q_groupChatPresence( const XMPP::Jid& jid, const XMPP::Status& status )
{
	qWarning() << "groupChatPresence" << jid.full() << status.show() << status.status();
}

void kChatWidget::_q_groupChatError( const XMPP::Jid& jid, int error, const QString& reason )
{
	qWarning() << "groupChatError" << jid.full() << error << reason;
}

void kChatWidget::_q_subscription( const XMPP::Jid& jid, const QString& type )
{
	qWarning() << "subscription" << jid.full() << type;
}

void kChatWidget::on_leChat_returnPressed()
{
	Jid jid( mKiessFull );
	Message msg( jid );
	msg.setFrom( mClient->jid() );
	msg.setType( "groupchat" );
	msg.setBody( leChat->text(), "fr" );
	msg.addEvent( OfflineEvent );
	msg.addEvent( ComposingEvent );
	msg.addEvent( DeliveredEvent );
	msg.addEvent( DisplayedEvent );
	
	mClient->sendMessage( msg );
	
	leChat->clear();
}

void kChatWidget::reject()
{
	mClient->leaveGroupChat( mKiessHost, mKiessRoom );
	//setClient( 0 );
}
