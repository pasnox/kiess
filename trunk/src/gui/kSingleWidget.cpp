#include "kSingleWidget.h"

kSingleWidget::kSingleWidget( kGuiScenePanel* panel )
	: kEmbeddedWidget( panel )
{
	setupUi( this );
}

kSingleWidget::~kSingleWidget()
{
}

void kSingleWidget::loadDatas()
{
}

void kSingleWidget::saveDatas()
{
}

void kSingleWidget::reject()
{
}

void kSingleWidget::accept()
{
	saveDatas();
}