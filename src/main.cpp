#include <QApplication>
#include <QDesktopWidget>

#include "gui/kGui.h"
#include "gui/kGuiScene.h"
#include "gui/kGuiScenePanel.h"
#include "board/kBoard.h"
#include "network/kiessxmpp.h"

int main(int argc, char ** argv)
{
	QApplication qa( argc, argv );
	
	// create game panel
	kGui gui;
	gui.setWindowTitle( "Kiess v0 - Kiess Team" );
	
	// center window
	QRect rect = gui.frameGeometry();
	rect.moveCenter( qa.desktop()->availableGeometry( &gui ).center() );
	gui.move( rect.topLeft() );
	
	// show game panel
	gui.show();
	//gui.scene()->panel()->setCurrentItem( QPoint(), false );
	
	/*
	kBoard board;
	board.show();
	*/
	/*
	kXmppSettings settings("localhost", "guillaume", "localhost", "Home", "pouet");
	KiessXmpp xmpp(settings);
	xmpp.process();
	*/

	return qa.exec();
}
