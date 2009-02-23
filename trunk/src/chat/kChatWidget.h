#ifndef KCHATWIDGET_H
#define KCHATWIDGET_H

#include "ui_kChatWidget.h"
#include "kClient.h"

class kChatWidget : public QFrame, public Ui::kChatWidget
{
	Q_OBJECT

public:
	kChatWidget();
	virtual ~kChatWidget();
	
	kClient* client() const;
	void setClient( kClient* client, const QString& nick );

public slots:

protected:
	kClient* mClient;

protected slots:
	void _q_incomingFileTransfer();
	void _q_rosterRequestFinished( bool success );
	void _q_newContact( const XMPP::RosterItem& item );
	void _q_contactDeleted( const XMPP::RosterItem& item );
	void _q_contactUpdated( const XMPP::RosterItem& item );
	void _q_resourceAvailable( const XMPP::Jid& jid, const XMPP::Resource& resource );
	void _q_resourceUnavailable( const XMPP::Jid& jid, const XMPP::Resource& resource );
	void _q_messageReceived( const XMPP::Message& message );
	void _q_groupChatJoined( const XMPP::Jid& jid );
	void _q_groupChatLeft( const XMPP::Jid& jid );
	void _q_groupChatPresence( const XMPP::Jid& jid, const XMPP::Status& status );
	void _q_groupChatError( const XMPP::Jid& jid, int error, const QString& reason );
	void _q_subscription( const XMPP::Jid& jid, const QString& type );
};

#endif // KCHATWIDGET_H
