#ifndef KIESS_XMPP_MECHANISM_H
#define KIESS_XMPP_MECHANISM_H

#include <QString>

class KiessXmppMechanism {
public:
	static KiessXmppMechanism * factory(const QString& mechanism);
	virtual QString response(const QString& challenge) = 0;
};

class KiessXmppDigestMd5Mechanism : public KiessXmppMechanism {
private:
	QString cnonce;
public:
	KiessXmppDigestMd5Mechanism();
	QString response(const QString& challenge);
};

#endif
