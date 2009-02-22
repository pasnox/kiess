#ifndef KSINGLEWIDGET_H
#define KSINGLEWIDGET_H

#include "ui_kSingleWidget.h"
#include "JabberClient.h"

class kSingleWidget : public kEmbeddedWidget, public Ui::kSingleWidget
{
	Q_OBJECT

public:
	kSingleWidget( kGuiScenePanel* panel );
	virtual ~kSingleWidget();

public slots:
	virtual void loadDatas();
	virtual void saveDatas();
	virtual void reject();
	virtual void accept();

protected slots:
	void connected();
	void csAuthenticated();
	void csError( int error );
	void csDisconnected();
	void tlsWarning( QCA::TLS::IdentityResult, QCA::Validity );
	void incomingFileTransfer();
	void error( JabberClient::ErrorCode code );
	void rosterRequestFinished( bool success );
	void newContact( const XMPP::RosterItem& item );
	void contactDeleted( const XMPP::RosterItem& item );
	void contactUpdated( const XMPP::RosterItem& item );
	void resourceAvailable( const XMPP::Jid& jid, const XMPP::Resource& resource );
	void resourceUnavailable( const XMPP::Jid& jid, const XMPP::Resource& resource );
	void messageReceived( const XMPP::Message& message );
	void groupChatJoined( const XMPP::Jid& jid );
	void groupChatLeft( const XMPP::Jid& jid );
	void groupChatPresence( const XMPP::Jid& jid, const XMPP::Status& status );
	void groupChatError( const XMPP::Jid& jid, int error, const QString& reason );
	void subscription( const XMPP::Jid& jid, const QString& type );
	void debugMessage( const QString& message );
	void incomingXML( const QString& msg );
	void outgoingXML( const QString& msg );

protected:
	JabberClient* mClient;
	
	JabberClient* newClient();
};

#endif // KSINGLEWIDGET_H
