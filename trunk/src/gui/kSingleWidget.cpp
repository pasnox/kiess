#include "kSingleWidget.h"

kSingleWidget::kSingleWidget()
	: kEmbeddedWidget()
{
	setupUi( this );
}

kSingleWidget::~kSingleWidget()
{
}

void kSingleWidget::reject()
{
	qWarning( "kSingleWidget::reject()" );
}

void kSingleWidget::accept()
{
	qWarning( "kSingleWidget::accept()" );
}
