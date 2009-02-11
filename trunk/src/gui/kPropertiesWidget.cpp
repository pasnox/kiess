#include "kPropertiesWidget.h"

kPropertiesWidget::kPropertiesWidget()
	: kEmbeddedWidget()
{
	setupUi( this );
}

kPropertiesWidget::~kPropertiesWidget()
{
}

void kPropertiesWidget::reject()
{
	qWarning( "kPropertiesWidget::reject()" );
	emit rejected();
}

void kPropertiesWidget::accept()
{
	qWarning( "kPropertiesWidget::accept()" );
	emit accepted();
}
