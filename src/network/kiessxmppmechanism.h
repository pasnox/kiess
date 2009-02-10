#ifndef KIESS_XMPP_MECHANISM_H
#define KIESS_XMPP_MECHANISM_H

#include <QString>
#include <QMap>

class KiessXmppMechanism {
public:
	static KiessXmppMechanism * factory(const QString& mechanism);
	virtual QByteArray response(const QString& challenge) = 0;
};

class KiessXmppDigestMd5Mechanism : public KiessXmppMechanism {
private:
	QString cnonce;
	QMap<QString, QString> parts;

	QByteArray authResponse(void);
public:
	KiessXmppDigestMd5Mechanism();
	QByteArray response(const QString& challenge);
};

#endif
