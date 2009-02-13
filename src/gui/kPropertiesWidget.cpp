#include "kPropertiesWidget.h"

kPropertiesWidget::kPropertiesWidget()
	: kEmbeddedWidget()
{
	setupUi( this );
}

kPropertiesWidget::~kPropertiesWidget()
{
}

void kPropertiesWidget::loadDatas()
{
	qWarning( "kPropertiesWidget::loadDatas()" );
}

void kPropertiesWidget::saveDatas()
{
	qWarning( "kPropertiesWidget::saveDatas()" );
}

void kPropertiesWidget::reject()
{
	qWarning( "kPropertiesWidget::reject()" );
}

void kPropertiesWidget::accept()
{
	saveDatas();
	qWarning( "kPropertiesWidget::accept()" );
}
