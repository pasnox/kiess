#include "kPropertiesWidget.h"

kPropertiesWidget::kPropertiesWidget( kGuiScenePanel* panel )
	: kEmbeddedWidget( panel )
{
	setupUi( this );
}

kPropertiesWidget::~kPropertiesWidget()
{
}

void kPropertiesWidget::loadDatas()
{
	/*
	cbFullScreen->setChecked( mPanel->isFullScreen() );
	*/
}

void kPropertiesWidget::saveDatas()
{
	/*
	if ( cbFullScreen->isChecked() )
	{
		if ( !mPanel->isFullScreen() )
		{
			mPanel->showFullScreen();
		}
	}
	else
	{
		if ( mPanel->isFullScreen() )
		{
			mPanel->showNormal();
		}
	}
	*/
}

void kPropertiesWidget::reject()
{
	emit rejected();
}

void kPropertiesWidget::accept()
{
	saveDatas();
	emit accepted();
}
