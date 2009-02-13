#include "kSingleWidget.h"

kSingleWidget::kSingleWidget()
	: kEmbeddedWidget()
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
