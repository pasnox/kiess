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
	QString jid;
	bool sessionPending;
	const kXmppSettings& mSettings;
	QString body;

	void sendAuth(void);
	void startStream(void);
	void resourceBinding(void);
	void startSession(void);

public:
	KiessXmpp(const kXmppSettings& settings);
	void process(void);

protected slots:
	void onConnected(void);
	void onError(QAbstractSocket::SocketError socketError);
	void onReadyRead(void);

signals:
	void message(const QString& body);
};

#endif
