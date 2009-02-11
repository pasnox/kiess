#include "kXmppSettings.h"

kXmppSettings::kXmppSettings() {
}

kXmppSettings::kXmppSettings(const QString& host, const QString& user, const QString& resource, const QString& pass) :
		mHost(host),
		mUser(user),
		mResource(resource),
		mPassword(pass) {
}

void kXmppSettings::setHost(const QString& host) {
	mHost = host;
}

void kXmppSettings::setUser(const QString& user) {
	mUser = user;
}

void kXmppSettings::setResource(const QString& resource) {
	mResource = resource;
}

void kXmppSettings::setPassword(const QString& pass) {
	mPassword = pass;
}

const QString kXmppSettings::getHost() const {
	return mHost;
}

const QByteArray kXmppSettings::getAsciiHost() const {
	return mHost.toAscii();
}

const QString kXmppSettings::getUser() const {
	return mUser;
}

const QString kXmppSettings::getResource() const {
	return mResource;
}

const QString kXmppSettings::getPassword() const {
	return mPassword;
}

const QString kXmppSettings::getAuthzid() const {
	QString authzid;
	authzid.append(mUser).append('@').append(mHost).append('/').append(mResource);
	return authzid;
}
