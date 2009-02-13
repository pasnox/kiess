#include "kSingleWidget.h"

kSingleWidget::kSingleWidget( kPanel* panel )
	: kEmbeddedWidget( panel )
{
	setupUi( this );
}

kSingleWidget::~kSingleWidget()
{
}

void kSingleWidget::loadDatas()
{
	qWarning( "kSingleWidget::loadDatas()" );
}

void kSingleWidget::saveDatas()
{
	qWarning( "kSingleWidget::saveDatas()" );
}

void kSingleWidget::reject()
{
	qWarning( "kSingleWidget::reject()" );
}

void kSingleWidget::accept()
{
	saveDatas();
	qWarning( "kSingleWidget::accept()" );
}
