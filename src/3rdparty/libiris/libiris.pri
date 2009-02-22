CONFIG	*= staticlib qt debug_and_release warn_on thread x11 windows embed_manifest_lib x86 ppc lib_bundle
DEFINES	-= QT_NO_HTTP
QT	*= core gui network xml
LIBS	*= -lqca -lidn
win32:LIBS	*= -lws2_32

contains( DEFINES, HAVE_NSL_LIBRARY ) {
	LIBS	*= -lnsl
}

CONFIG(debug, debug|release) {
	#Debug
} else {
	#Release
}

LIBIRIS_SOURCE_DIR	= $$PWD
LIBS	*= -L$${LIBIRIS_SOURCE_DIR}

unix:QCA2_INCLUDE_DIR	= /usr/include/QtCrypto

INCLUDEPATH	*= $${LIBIRIS_SOURCE_DIR}/iris \
	$${LIBIRIS_SOURCE_DIR}/iris/xmpp/base \
	# $${LIBIRIS_SOURCE_DIR}/iris/xmpp/base/unittest \
	$${LIBIRIS_SOURCE_DIR}/iris/xmpp/base \
	# $${LIBIRIS_SOURCE_DIR}/iris/xmpp/qa/qttestutil \
	$${LIBIRIS_SOURCE_DIR}/iris/xmpp/jid \
	$${LIBIRIS_SOURCE_DIR}/iris/xmpp/cutestuff \
	$${LIBIRIS_SOURCE_DIR}/iris/xmpp/xmpp-im \
	$${LIBIRIS_SOURCE_DIR}/iris/xmpp/sasl \
	$${LIBIRIS_SOURCE_DIR}/iris/xmpp/zlib \
	$${LIBIRIS_SOURCE_DIR}/iris/xmpp/base64 \
	$${LIBIRIS_SOURCE_DIR}/iris/xmpp/xmpp-core \
	$${LIBIRIS_SOURCE_DIR}/iris/xmpp/jingle \
	#$${LIBIRIS_SOURCE_DIR}/iris/libidn \
	$${LIBIRIS_SOURCE_DIR}/iris/jdns \
	$${LIBIRIS_SOURCE_DIR}/iris/irisnet/noncore \
	$${LIBIRIS_SOURCE_DIR}/iris/irisnet/noncore/legacy \
	$${LIBIRIS_SOURCE_DIR}/iris/irisnet/corelib \
	$${LIBIRIS_SOURCE_DIR}/iris/irisnet/appledns \
	$${LIBIRIS_SOURCE_DIR}/include \
	$${QCA2_INCLUDE_DIR} \
	$${IDN_INCLUDE_DIR} \
	$${ZLIB_INCLUDE_DIR} \
	$${DNSSD_INCLUDE_DIR}