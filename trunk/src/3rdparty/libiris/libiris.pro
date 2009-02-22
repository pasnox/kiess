TEMPLATE	= lib
TARGET	= iris_kiess

BUILD_PATH	= ./build

CONFIG(debug, debug|release) {
	#Debug
	CONFIG	+= console
	unix:TARGET	= $$join(TARGET,,,_debug)
	else:TARGET	= $$join(TARGET,,,d)
	unix:OBJECTS_DIR	= $${BUILD_PATH}/debug/.obj/unix
	win32:OBJECTS_DIR	= $${BUILD_PATH}/debug/.obj/win32
	mac:OBJECTS_DIR	= $${BUILD_PATH}/debug/.obj/mac
	UI_DIR	= $${BUILD_PATH}/debug/.ui
	MOC_DIR	= $${BUILD_PATH}/debug/.moc
	RCC_DIR	= $${BUILD_PATH}/debug/.rcc
} else {
	#Release
	unix:OBJECTS_DIR	= $${BUILD_PATH}/release/.obj/unix
	win32:OBJECTS_DIR	= $${BUILD_PATH}/release/.obj/win32
	mac:OBJECTS_DIR	= $${BUILD_PATH}/release/.obj/mac
	UI_DIR	= $${BUILD_PATH}/release/.ui
	MOC_DIR	= $${BUILD_PATH}/release/.moc
	RCC_DIR	= $${BUILD_PATH}/release/.rcc
}

include(libiris.pri)

HEADERS	+= iris/xmpp/base/randrandomnumbergenerator.h \
	iris/xmpp/base/randomnumbergenerator.h \
	iris/xmpp/jid/jid.h \
	iris/xmpp/cutestuff/bytestream.h \
	iris/xmpp/cutestuff/socks.h \
	iris/xmpp/cutestuff/httpconnect.h \
	iris/xmpp/cutestuff/bsocket.h \
	iris/xmpp/cutestuff/httppoll.h \
	iris/xmpp/xmpp-im/xmpp_xdata.h \
	iris/xmpp/xmpp-im/xmpp_rosterx.h \
	iris/xmpp/xmpp-im/xmpp_tasks.h \
	iris/xmpp/xmpp-im/xmpp_discoitem.h \
	iris/xmpp/xmpp-im/xmpp_pubsubretraction.h \
	iris/xmpp/xmpp-im/xmpp_xmlcommon.h \
	iris/xmpp/xmpp-im/xmpp_roster.h \
	iris/xmpp/xmpp-im/xmpp_muc.h \
	iris/xmpp/xmpp-im/xmpp_htmlelement.h \
	iris/xmpp/xmpp-im/xmpp_receipts.h \
	iris/xmpp/xmpp-im/xmpp_message.h \
	iris/xmpp/xmpp-im/xmpp_discoinfotask.h \
	iris/xmpp/xmpp-im/xmpp_ibb.h \
	iris/xmpp/xmpp-im/xmpp_liverosteritem.h \
	iris/xmpp/xmpp-im/xmpp_httpauthrequest.h \
	iris/xmpp/xmpp-im/xmpp_pubsubitem.h \
	iris/xmpp/xmpp-im/xmpp_vcard.h \
	iris/xmpp/xmpp-im/xmpp_client.h \
	iris/xmpp/xmpp-im/s5b.h \
	iris/xmpp/xmpp-im/xmpp_url.h \
	iris/xmpp/xmpp-im/xmpp_chatstate.h \
	iris/xmpp/xmpp-im/xmpp_task.h \
	iris/xmpp/xmpp-im/xmpp_address.h \
	iris/xmpp/xmpp-im/xmpp_agentitem.h \
	iris/xmpp/xmpp-im/filetransfer.h \
	iris/xmpp/xmpp-im/xmpp_status.h \
	iris/xmpp/xmpp-im/xmpp_resourcelist.h \
	iris/xmpp/xmpp-im/xmpp_liveroster.h \
	iris/xmpp/xmpp-im/xmpp_resource.h \
	iris/xmpp/xmpp-im/xmpp_rosteritem.h \
	iris/xmpp/xmpp-im/xmpp_features.h \
	iris/xmpp/xmpp-im/im.h \
	iris/xmpp/sasl/digestmd5response.h \
	iris/xmpp/sasl/digestmd5proplist.h \
	iris/xmpp/sasl/plainmessage.h \
	iris/xmpp/zlib/common.h \
	iris/xmpp/zlib/zlibdecompressor.h \
	iris/xmpp/zlib/zlibcompressor.h \
	iris/xmpp/base64/base64.h \
	iris/xmpp/xmpp-core/xmpp_stanza.h \
	iris/xmpp/xmpp-core/simplesasl.h \
	iris/xmpp/xmpp-core/securestream.h \
	iris/xmpp/xmpp-core/protocol.h \
	iris/xmpp/xmpp-core/compressionhandler.h \
	iris/xmpp/xmpp-core/xmlprotocol.h \
	iris/xmpp/xmpp-core/xmpp.h \
	iris/xmpp/xmpp-core/xmpp_clientstream.h \
	iris/xmpp/xmpp-core/xmpp_stream.h \
	iris/xmpp/xmpp-core/td.h \
	iris/xmpp/xmpp-core/parser.h \
	iris/jdns/qjdns.h \
	iris/irisnet/noncore/stuntransaction.h \
	iris/irisnet/noncore/stunbinding.h \
	iris/irisnet/noncore/legacy/ndns.h \
	iris/irisnet/noncore/legacy/safedelete.h \
	iris/irisnet/noncore/legacy/servsock.h \
	iris/irisnet/noncore/legacy/srvresolver.h \
	iris/irisnet/noncore/stunallocate.h \
	iris/irisnet/noncore/ice176.h \
	iris/irisnet/noncore/processquit.h \
	iris/irisnet/noncore/icelocaltransport.h \
	iris/irisnet/corelib/irisnetglobal.h \
	iris/irisnet/corelib/objectsession.h \
	iris/irisnet/corelib/netavailability.h \
	iris/irisnet/corelib/netnames.h \
	iris/irisnet/corelib/irisnetplugin.h \
	iris/irisnet/corelib/netinterface.h \
	iris/irisnet/corelib/jdnsshared.h \
	#iris/irisnet/appledns/qdnssd.h \
	iris/xmpp/jingle/jinglecontent.h \
	iris/xmpp/jingle/jinglesession.h \
	iris/xmpp/jingle/jinglesessionmanager.h \
	iris/xmpp/jingle/jingletasks.h

SOURCES	+= iris/xmpp/base/randomnumbergenerator.cpp \
	# iris/xmpp/base/unittest/randomnumbergeneratortest.cpp \
	# iris/xmpp/base/unittest/randrandomnumbergeneratortest.cpp \
	# iris/xmpp/qa/qttestutil/testregistry.cpp \
	# iris/xmpp/qa/qttestutil/simplechecker.cpp \
	# iris/xmpp/qa/qttestutil/example/mysecondclasstest.cpp \
	# iris/xmpp/qa/qttestutil/example/myfirstclasstest.cpp \
	# iris/xmpp/qa/unittest.template/myclasstest.cpp \
	# iris/xmpp/jid/unittest/jidtest.cpp \
	iris/xmpp/jid/jid.cpp \
	iris/xmpp/cutestuff/httppoll.cpp \
	iris/xmpp/cutestuff/socks.cpp \
	iris/xmpp/cutestuff/bytestream.cpp \
	iris/xmpp/cutestuff/bsocket.cpp \
	iris/xmpp/cutestuff/httpconnect.cpp \
	iris/xmpp/xmpp-im/xmpp_discoitem.cpp \
	iris/xmpp/xmpp-im/client.cpp \
	iris/xmpp/xmpp-im/types.cpp \
	iris/xmpp/xmpp-im/xmpp_vcard.cpp \
	iris/xmpp/xmpp-im/xmpp_xmlcommon.cpp \
	iris/xmpp/xmpp-im/xmpp_ibb.cpp \
	iris/xmpp/xmpp-im/xmpp_xdata.cpp \
	iris/xmpp/xmpp-im/xmpp_task.cpp \
	iris/xmpp/xmpp-im/xmpp_features.cpp \
	iris/xmpp/xmpp-im/xmpp_discoinfotask.cpp \
	iris/xmpp/xmpp-im/s5b.cpp \
	iris/xmpp/xmpp-im/xmpp_tasks.cpp \
	iris/xmpp/xmpp-im/filetransfer.cpp \
	iris/xmpp/sasl/digestmd5proplist.cpp \
	# iris/xmpp/sasl/unittest/digestmd5responsetest.cpp \
	# iris/xmpp/sasl/unittest/plainmessagetest.cpp \
	iris/xmpp/sasl/digestmd5response.cpp \
	iris/xmpp/sasl/plainmessage.cpp \
	iris/xmpp/zlib/zlibcompressor.cpp \
	iris/xmpp/zlib/zlibdecompressor.cpp \
	# iris/xmpp/base64/unittest/base64test.cpp \
	iris/xmpp/base64/base64.cpp \
	iris/xmpp/xmpp-core/tlshandler.cpp \
	iris/xmpp/xmpp-core/xmpp_stanza.cpp \
	iris/xmpp/xmpp-core/stream.cpp \
	iris/xmpp/xmpp-core/securestream.cpp \
	iris/xmpp/xmpp-core/simplesasl.cpp \
	iris/xmpp/xmpp-core/xmlprotocol.cpp \
	iris/xmpp/xmpp-core/protocol.cpp \
	iris/xmpp/xmpp-core/compressionhandler.cpp \
	iris/xmpp/xmpp-core/parser.cpp \
	iris/xmpp/xmpp-core/connector.cpp \
	#iris/jdns/main.cpp \
	iris/jdns/qjdns.cpp \
	iris/jdns/qjdns_sock.cpp \
	iris/irisnet/noncore/ice176.cpp \
	iris/irisnet/noncore/stunallocate.cpp \
	iris/irisnet/noncore/legacy/ndns.cpp \
	iris/irisnet/noncore/legacy/srvresolver.cpp \
	iris/irisnet/noncore/legacy/safedelete.cpp \
	iris/irisnet/noncore/legacy/servsock.cpp \
	iris/irisnet/noncore/icelocaltransport.cpp \
	iris/irisnet/noncore/stunmessage.cpp \
	iris/irisnet/noncore/stunbinding.cpp \
	iris/irisnet/noncore/stuntransaction.cpp \
	iris/irisnet/noncore/processquit.cpp \
	iris/irisnet/corelib/netinterface_win.cpp \
	iris/irisnet/corelib/netavailability.cpp \
	iris/irisnet/corelib/netnames_jdns.cpp \
	iris/irisnet/corelib/netnames.cpp \
	iris/irisnet/corelib/irisnetplugin.cpp \
	iris/irisnet/corelib/netinterface_unix.cpp \
	iris/irisnet/corelib/netinterface.cpp \
	iris/irisnet/corelib/jdnsshared.cpp \
	iris/irisnet/corelib/objectsession.cpp \
	iris/irisnet/corelib/irisnetglobal.cpp \
	#iris/irisnet/appledns/appledns.cpp \
	#iris/irisnet/appledns/qdnssd.cpp \
	#iris/irisnet/appledns/sdtest.cpp \
	# iris/libidn/profiles.c \
	# iris/libidn/rfc3454.c \
	# iris/libidn/stringprep.c \
	# iris/libidn/nfkc.c \
	iris/jdns/jdns.c \
	iris/jdns/jdns_util.c \
	iris/jdns/jdns_sys.c \
	iris/jdns/jdns_mdnsd.c \
	iris/jdns/jdns_packet.c \
	iris/xmpp/jingle/jinglecontent.cpp \
	iris/xmpp/jingle/jinglesession.cpp \
	iris/xmpp/jingle/jinglesessionmanager.cpp \
	iris/xmpp/jingle/jingletasks.cpp
	