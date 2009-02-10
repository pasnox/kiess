#ifndef KIESS_XMPP_H
#define KIESS_XMPP_H

#include <qtcpsocket.h>
#include <QXmlStreamReader>

#include "kiessxmppmechanism.h"

class KiessXmpp : public QObject {
	Q_OBJECT
private:
	QXmlStreamReader * reader;
	QVector<QString> mechanisms;
	QTcpSocket * socket;
	KiessXmppMechanism * mechanism;

	void sendAuth(void);
public:
	KiessXmpp();
	void process(void);

protected slots:
	void onConnected(void);
	void onError(QAbstractSocket::SocketError socketError);
	void onReadyRead(void);
};

#endif
