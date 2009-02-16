#include "kAboutWidget.h"

kAboutWidget::kAboutWidget( kGuiScenePanel* panel )
	: kEmbeddedWidget( panel )
{
	setupUi( this );
	
	mAboutIdentities << AboutIdentity( "AZEVEDO Filipe", "pasnox@gmail.com", tr( "Gui developper" ) );
	mAboutIdentities << AboutIdentity( "DUHAMEL Guillaume", "guillaume.duhamel@gmail.com", tr( "Xmpp developper" ) );
	mAboutIdentities << AboutIdentity( "JOURDAN Romain", "jourdan.romain@gmail.com", tr( "Board developper" ) );
	mAboutIdentities << AboutIdentity( "GROULT Richard", "richard.groult@gmail.com", tr( "Cards developper" ) );
}

kAboutWidget::~kAboutWidget()
{
}

void kAboutWidget::loadDatas()
{
	QString html = "<p style=\"margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'DejaVu Sans'; font-size:8px; font-weight:440; font-style:normal;\">\n";
	
	foreach ( const AboutIdentity& identity, mAboutIdentities )
	{
		html += QString( "%1<br />\n" ).arg( identity.mName );
		html += QString( "&nbsp;&nbsp;&nbsp;&nbsp;<a href=\"mailto:%1\">%1</a><br />\n" ).arg( identity.mEmail );
		html += QString( "&nbsp;&nbsp;&nbsp;&nbsp;%1<br />\n" ).arg( identity.mJob );
		
		if ( mAboutIdentities.last() != identity )
		{
			html += "<br />\n";
		}
	}
	
	html += "</p>\n";
	
	lInformations->setText( html );
}

void kAboutWidget::saveDatas()
{
}

void kAboutWidget::reject()
{
}

void kAboutWidget::accept()
{
}
