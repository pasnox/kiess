#include "kiessxmpp.h"

KiessXmpp::KiessXmpp(const kXmppSettings& settings) : mSettings(settings) {
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
		mechanism = KiessXmppMechanism::factory(mechanisms.at(i), mSettings);
		i++;
	}

	if (mechanism != NULL) {
		socket->write("<auth xmlns='urn:ietf:params:xml:ns:xmpp-sasl' mechanism='");
		socket->write(mechanisms.at(i - 1).toAscii());
		socket->write("'/>");
	}
}

void KiessXmpp::startStream(void) {
	reader->setDevice(socket);
	socket->write("<stream:stream to='");
	socket->write(mSettings.getAsciiHost());
	socket->write("' version='1.0' xmlns:stream='http://etherx.jabber.org/streams'>");
}

void KiessXmpp::resourceBinding(void) {
	if (! jid.isEmpty()) return;

	socket->write("<iq type='set' id='bind_1'>");
	socket->write("<bind xmlns='urn:ietf:params:xml:ns:xmpp-bind'/>");
	socket->write("</iq>");
}

void KiessXmpp::startSession(void) {
	socket->write("<iq to='");
	socket->write(mSettings.getAsciiHost());
	socket->write("' type='set' id='sess_1'>");
	socket->write("<session xmlns='urn:ietf:params:xml:ns:xmpp-session'/>");
	socket->write("</iq>");
	socket->write("<presence/>");
}

void KiessXmpp::process(void) {
	socket->connectToHost(mSettings.getAsciiHost(), 5222);
}

void KiessXmpp::onConnected(void) {
	socket->write("<stream:stream to='");
	socket->write(mSettings.getAsciiHost());
	socket->write("' version='1.0' xmlns:stream='http://etherx.jabber.org/streams'>");
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
						socket->write(response.toAscii());
					} else if (elem == "success") {
						startStream();
					} else if (elem == "jid") {
						jid = reader->readElementText();
						if (sessionPending) startSession();
					} else if (elem == "session") {
						sessionPending = true;
					} else if (elem == "body") {
						body = reader->readElementText();
					}
				}
				break;
			case QXmlStreamReader::EndElement:
				{
					QStringRef elem = reader->name();
					if (elem == "mechanisms") {
						sendAuth();
					} else if (elem == "bind") {
						resourceBinding();
					} else if (elem == "message") {
						emit message(body);
					}
				}
			default:
				break;
		}
	}
}
