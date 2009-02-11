#ifndef KIESS_XMPP_MECHANISM_H
#define KIESS_XMPP_MECHANISM_H

#include <QString>
#include <QMap>

#include "kXmppSettings.h"

class KiessXmppMechanism {
protected:
	const kXmppSettings& mSettings;
public:
	KiessXmppMechanism(const kXmppSettings& settings);
	static KiessXmppMechanism * factory(const QString& mechanism, const kXmppSettings& settings);
	virtual QByteArray response(const QString& challenge) = 0;
};

class KiessXmppDigestMd5Mechanism : public KiessXmppMechanism {
private:
	QString cnonce;
	QMap<QString, QString> parts;

	QByteArray authResponse(void);
public:
	KiessXmppDigestMd5Mechanism(const kXmppSettings& settings);
	QByteArray response(const QString& challenge);
};

#endif
