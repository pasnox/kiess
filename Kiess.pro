###########################################################################################
##		Created using Monkey Studio v1.8.3.0
##
##	Author    : You Name <your@email.org>
##	Project   : Kiess
##	FileName  : Kiess.pro
##	Date      : 2009-02-10T18:08:49
##	License   : GPL
##	Comment   : Creating using Monkey Studio RAD
##	Home Page   : http://googlecode.com/p/kiess
##
##	This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
##	WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
##
###########################################################################################

XUPProjectSettings {
	EDITOR	= QMake
	QT_VERSION	= Qt System (4.4.3)
	EXECUTE_DEBUG	= bin/Kiess_debug
	EXECUTE_RELEASE	= bin/Kiess
}

TEMPLATE	= app
LANGUAGE	= C++/Qt4
TARGET	= $$quote(Kiess)
DESTDIR	= bin
CONFIG	+= qt resources debug_and_release warn_on thread x11 windows console embed_manifest_exe x86 ppc app_bundle
QT	= core gui network opengl
BUILD_PATH	= ./build

CONFIG(debug, debug|release) {
	#Debug
	CONFIG	*= console
	unix:TARGET	= $$join(TARGET,,,_debug)
	else:TARGET	= $$join(TARGET,,,d)
	unix:OBJECTS_DIR	= $${BUILD_PATH}/debug/.obj/unix
	win32:OBJECTS_DIR	= $${BUILD_PATH}/debug/.obj/win32
	mac:OBJECTS_DIR	= $${BUILD_PATH}/debug/.obj/mac
	UI_DIR	= $${BUILD_PATH}/debug/.ui
	MOC_DIR	= $${BUILD_PATH}/debug/.moc
	RCC_DIR	= $${BUILD_PATH}/debug/.rcc
	unix:LIBS	*= -liris_kiess_debug
	else:LIBS	*= -liris_kiessd
} else {
	#Release
	unix:OBJECTS_DIR	= $${BUILD_PATH}/release/.obj/unix
	win32:OBJECTS_DIR	= $${BUILD_PATH}/release/.obj/win32
	mac:OBJECTS_DIR	= $${BUILD_PATH}/release/.obj/mac
	UI_DIR	= $${BUILD_PATH}/release/.ui
	MOC_DIR	= $${BUILD_PATH}/release/.moc
	RCC_DIR	= $${BUILD_PATH}/release/.rcc
	LIBS	*= -liris_kiess
}

win32-msvc*:DEFINES	+= _USE_MATH_DEFINES

INCLUDEPATH	= src/gui \
	src/network \
	src/board \
	src \
	src/network/jabber

include( src/3rdparty/libiris/libiris.pri )

RESOURCES	= src/resources/resources.qrc

FORMS	= src/gui/kPropertiesWidget.ui \
	src/gui/kSingleWidget.ui \
	src/gui/kAboutWidget.ui

HEADERS	= src/network/kiessxmpp.h \
	src/network/kiessxmppmechanism.h \
	src/network/kXmppSettings.h \
	src/gui/kPropertiesWidget.h \
	src/gui/kEmbeddedWidget.h \
	src/board/kBoardDef.h \
	src/board/kBoard.h \
	src/board/kCardItem.h \
	src/gui/kSingleWidget.h \
	src/gui/kAboutWidget.h \
	src/gui/kGui.h \
	src/gui/kGuiScene.h \
	src/gui/kGuiScenePanel.h \
	src/gui/kGuiScenePanelItem.h \
	src/kHelper.h \
	src/network/jabber/JabberClient.h \
	src/network/jabber/PrivacyList.h \
	src/network/jabber/PrivacyListItem.h \
	src/network/jabber/PrivacyManager.h \
	src/network/kClient.h

SOURCES	= src/main.cpp \
	src/network/kiessxmpp.cpp \
	src/network/kiessxmppmechanism.cpp \
	src/network/kXmppSettings.cpp \
	src/gui/kPropertiesWidget.cpp \
	src/board/kBoard.cpp \
	src/board/kCardItem.cpp \
	src/gui/kSingleWidget.cpp \
	src/gui/kAboutWidget.cpp \
	src/gui/kGui.cpp \
	src/gui/kGuiScene.cpp \
	src/gui/kGuiScenePanel.cpp \
	src/gui/kGuiScenePanelItem.cpp \
	src/kHelper.cpp \
	src/network/jabber/JabberClient.cpp \
	src/network/jabber/PrivacyListItem.cpp \
	src/network/jabber/PrivacyManager.cpp \
	src/network/jabber/PrivacyList.cpp \
	src/network/kClient.cpp