#include <QApplication>
#include <QDesktopWidget>

#include "gui/kPanel.h"
#include "board/kBoard.h"
#include "network/kiessxmpp.h"

#include "gui/v2/kGui.h"

int main(int argc, char ** argv)
{
	QApplication qa( argc, argv );
	
	/*
	// create game panel
	kPanel panel;
	panel.setWindowTitle( "Kiess v0 - Kiess Team" );
	
	// center window
	QRect rect = panel.frameGeometry();
	rect.moveCenter( qa.desktop()->availableGeometry( &panel ).center() );
	panel.move( rect.topLeft() );
	
	// show game panel
	panel.show();
	*/
	
	/*
	kBoard board;
	board.show();
	*/
	
	kGui gui;
	gui.show();
	
	kXmppSettings settings("localhost", "guillaume", "localhost", "Home", "pouet");
	KiessXmpp xmpp(settings);
	xmpp.process();

	return qa.exec();
}
