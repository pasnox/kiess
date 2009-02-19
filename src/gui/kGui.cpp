#include "kGui.h"
#include "kGuiScene.h"
#include "kGuiScenePanel.h"
#include "kGuiScenePanelItem.h"

#include "kSingleWidget.h"
#include "kPropertiesWidget.h"
#include "kAboutWidget.h"

#include "kHelper.h"

#ifndef QT_NO_OPENGL
#include <QtOpenGL>
#endif

kGui::kGui( QWidget* parent )
	: QGraphicsView( parent )
{
	// init view
	setFrameStyle( QFrame::NoFrame );
	setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	setCacheMode( QGraphicsView::CacheBackground );
	setViewportUpdateMode( QGraphicsView::FullViewportUpdate );
	setRenderHints( QPainter::Antialiasing | QPainter::SmoothPixmapTransform );
	setBackgroundBrush( QPixmap( ":/gui/background.jpg" ) );
#ifndef QT_NO_OPENGL
	setViewport( new QGLWidget( QGLFormat( QGL::SampleBuffers ) ) );
#endif

	// init scene
	mScene = new kGuiScene( this );
	mScene->setSceneRect( QRect( QPoint( 0, 0 ), sizeHint() ) );
	
	// init panel
	qreal min = qMin( sizeHint().width(), sizeHint().height() ) *0.85;
	qreal x = ( sizeHint().width() -min ) /2;
	qreal y = ( sizeHint().height() -min ) /2;
	QRectF bounds = kHelper::translatedRectXY( QRectF( QPointF( 0, 0 ), QSizeF( min, min ) ), x, y );
	
	kGuiScenePanel* mPanel = new kGuiScenePanel( bounds, QSize( 2, 2 ), mScene );
	mPanel->setPos( x, y );
	
	// init panel items widget
	mPanel->item( QPoint( 0, 0 ) )->setWidget( new kSingleWidget( mPanel ) );
	mPanel->item( QPoint( 0, 1 ) )->setWidget( new kPropertiesWidget( mPanel ) );
	mPanel->item( QPoint( 1, 1 ) )->setWidget( new kAboutWidget( mPanel ) );
	
	// set scene
	setScene( mScene );
	mScene->addItem( mPanel );
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
