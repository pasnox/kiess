#ifndef KCLIENT_H
#define KCLIENT_H

#define APP_NAME "Kiess"
#define APP_VERSION "0.1.0"
#define OS_NAME "Unix"
#define ARCH_NAME "x86"

#include "JabberClient.h"

class kClient : public JabberClient
{
	Q_OBJECT
	
public:
	kClient();
	virtual ~kClient();

	void setPresence( const Status& status );

protected slots:
	void _q_connected();
	void _q_csAuthenticated();
	void _q_csError( int error );
	void _q_csDisconnected();
	void _q_tlsWarning( QCA::TLS::IdentityResult, QCA::Validity );
	void _q_error( JabberClient::ErrorCode code );
	void _q_debugMessage( const QString& message );
	void _q_incomingXML( const QString& msg );
	void _q_outgoingXML( const QString& msg );

signals:
	void connected( bool success );
};

#endif // KCLIENT_H
