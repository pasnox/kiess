#include "kiessxmppmechanism.h"

#include <QCryptographicHash>

KiessXmppMechanism * KiessXmppMechanism::factory(const QString& mechanism) {
	if (mechanism == "DIGEST-MD5") {
		return new KiessXmppDigestMd5Mechanism();
	}

	return NULL;
}

KiessXmppDigestMd5Mechanism::KiessXmppDigestMd5Mechanism() {
	cnonce = "OA6MHXh6VqTrRk";
}

QByteArray KiessXmppDigestMd5Mechanism::authResponse(void) {
	QCryptographicHash md5(QCryptographicHash::Md5);

	QByteArray xs("guillaume:localhost:pouet");
	md5.addData(xs);
	QByteArray x = md5.result();
	md5.reset();

	QByteArray ha1s(x);
	ha1s.append(':').append(parts["nonce"]).append(':').append(cnonce).append(':').append("guillaume@localhost/Home");
	md5.addData(ha1s);
	QByteArray ha1 = md5.result().toHex();
	md5.reset();

	QByteArray ha2s("AUTHENTICATE:xmpp/localhost");
	md5.addData(ha2s);
	QByteArray ha2 = md5.result().toHex();
	md5.reset();

	QByteArray fulls;
	fulls.append(ha1).append(":").append(parts["nonce"]).append(":").append("00000001")
		.append(":").append(cnonce).append(':').append(parts["qop"]).append(':').append(ha2);
	md5.addData(fulls);
	QByteArray full = md5.result().toHex();
	md5.reset();

	QByteArray resp;
	resp.append("username=\"guillaume\",realm=\"localhost\"");
	resp.append(",nonce=\"").append(parts["nonce"]).append('"');
	resp.append(",cnonce=").append('"').append(cnonce).append('"');
	resp.append(",nc=00000001,qop=auth,digest-uri=\"xmpp/localhost\"");
	resp.append(",response=").append(full);
	resp.append(",charset=utf-8");
	resp.append(",authzid=\"guillaume@localhost/Home\"");

	QByteArray ret("<response xmlns='urn:ietf:params:xml:ns:xmpp-sasl'>");
	ret.append(resp.toBase64());
	ret.append("</response>");

	return ret;
}

QByteArray KiessXmppDigestMd5Mechanism::response(const QString& challenge) {
	QByteArray text = QByteArray::fromBase64(challenge.toAscii());
	QList<QByteArray> list = text.split(',');
	for(int i = 0;i < list.size();i++) {
		QList<QByteArray> part = list.at(i).split('=');
		QByteArray tmp = part.at(1);
		if ((tmp[0] == '"') && (tmp[tmp.size() -1] == '"')) tmp = tmp.mid(1, tmp.size() - 2);
		parts.insert(part.at(0), tmp);
	}

	if (parts.contains("rspauth")) {
		return "<response xmlns='urn:ietf:params:xml:ns:xmpp-sasl'/>";
	} else {
		return authResponse();
	}
}
