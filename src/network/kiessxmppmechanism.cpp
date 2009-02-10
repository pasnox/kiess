#include "kiessxmppmechanism.h"

#include <QMap>
#include <QDebug>

KiessXmppMechanism * KiessXmppMechanism::factory(const QString& mechanism) {
	if (mechanism == "DIGEST-MD5") {
		return new KiessXmppDigestMd5Mechanism();
	}

	return NULL;
}

KiessXmppDigestMd5Mechanism::KiessXmppDigestMd5Mechanism() {
	cnonce = "OA6MHXh6VqTrRk";
}

QString KiessXmppDigestMd5Mechanism::response(const QString& challenge) {
	QMap<QString, QString> parts;
	QByteArray text = QByteArray::fromBase64(challenge.toAscii());
	QList<QByteArray> list = text.split(',');
	for(int i = 0;i < list.size();i++) {
		QList<QByteArray> part = list.at(i).split('=');
		parts.insert(part.at(0), part.at(1));
	}

#if 0
	QString resp;

	resp << "username=\"guillaume\",realm=\"localhost\"";
	resp << ",nonce=" << parts["nonce"];
	resp << ",cnonce=" << '"' << cnonce << '"';
	resp << ",nc=00000001,qop=auth,digest-uri=\"xmpp/localhost\"";

	QByteArray ha1s("guillaume:localhost:pouet");
	QByteArray ha1 = ha1s.toBase64();

	QByteArray ha2s("GET:xmpp/localhost");
	QByteArray ha2 = ha2s.toBase64();

	QByteArray fulls;
	fulls << ha1 << ":" << parts["nonce"] << ":" << "00000001" << ":" << cnonce << ":auth:" << ha2;

	QByteArray full = fulls.toBase64();

	resp << ",response=" << full;
	resp << ",charset=utf-8";

	return resp;
#endif
	return "";
}
