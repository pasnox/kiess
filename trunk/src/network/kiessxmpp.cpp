#include "kiessxmpp.h"

KiessXmpp::KiessXmpp() {
	socket = new QTcpSocket(this);
	reader = new QXmlStreamReader(socket);
	mechanism = NULL;

	QObject::connect(socket, SIGNAL(connected()),
			this, SLOT(onConnected()));
	QObject::connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),
			this, SLOT(onError(QAbstractSocket::SocketError)));
	QObject::connect(socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}

void KiessXmpp::sendAuth(void) {
	int i = 0;
	while((mechanism == NULL) && (i < mechanisms.size())) {
		mechanism = KiessXmppMechanism::factory(mechanisms.at(i));
		i++;
	}

	if (mechanism != NULL) {
		socket->write("<auth xmlns='urn:ietf:params:xml:ns:xmpp-sasl' mechanism='");
		socket->write(mechanisms.at(i - 1).toAscii());
		socket->write("'/>");
	}
}

void KiessXmpp::process(void) {
	socket->connectToHost("localhost", 5222);
}


void KiessXmpp::onConnected(void) {
	socket->write("<stream:stream to='localhost' version='1.0' xmlns:stream='http://etherx.jabber.org/streams'>");
}

void KiessXmpp::onError(QAbstractSocket::SocketError socketError) {
	qWarning("error");
}

void KiessXmpp::onReadyRead(void) {
	while(! reader->atEnd()) {
		QXmlStreamReader::TokenType tt = reader->readNext();

		switch(tt) {
			case QXmlStreamReader::StartElement:
				{
					QStringRef elem = reader->name();
					qWarning() << elem.toString();
					if (elem == "mechanism") {
						mechanisms.append(reader->readElementText());
					} else if (elem == "challenge") {
						QString response = mechanism->response(reader->readElementText());
					}
				}
				break;
			case QXmlStreamReader::EndElement:
				{
					QStringRef elem = reader->name();
					if (elem == "features") {
						sendAuth();
					}
				}
			default:
				break;
		}
	}
}
