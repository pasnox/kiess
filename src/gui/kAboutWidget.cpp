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
	QString html;
	
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
	
	lInformations->setText( html );
}

void kAboutWidget::saveDatas()
{
}

void kAboutWidget::reject()
{
	emit rejected();
}

void kAboutWidget::accept()
{
	emit accepted();
}
