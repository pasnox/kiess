#ifndef KXMPP_SETTINGS_H
#define KXMPP_SETTINGS_H

#include <QString>

class kXmppSettings {
private:
	QString mHost;
	QString mUser;
	QString mRealm;
	QString mResource;
	QString mPassword;
public:
	kXmppSettings();
	kXmppSettings(const QString& host, const QString& user, const QString& realm, const QString& resource, const QString& pass);

	void setHost(const QString& host);
	void setUser(const QString& user);
	void setRealm(const QString& realm);
	void setResource(const QString& resource);
	void setPassword(const QString& pass);

	const QString getHost() const;
	const QByteArray getAsciiHost() const;
	const QString getUser() const;
	const QString getRealm() const;
	const QByteArray getAsciiRealm() const;
	const QString getResource() const;
	const QString getPassword() const;

	const QString getAuthzid() const;
};

#endif
