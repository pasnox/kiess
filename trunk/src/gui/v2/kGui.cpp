#include "kGui.h"
#include "kGuiScene.h"

const int mFactor = 150;

kGui::kGui( QWidget* parent )
	: QGraphicsView( parent )
{
	mScene = new kGuiScene( this );
	mScene->initialize( QSize( 2, 2 ) );
}

kGui::~kGui()
{
}

QSize kGui::sizeHint() const
{
	return QSize( 800, 600 );
}

void kGui::resizeEvent( QResizeEvent* event )
{
	QGraphicsView::resizeEvent( event );
	fitInView( mScene->sceneRect(), Qt::KeepAspectRatio );
}

kGuiScene* kGui::scene() const
{
	return mScene;
}
