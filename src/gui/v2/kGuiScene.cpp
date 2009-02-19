#include "kGuiScene.h"
#include "kGui.h"
#include "kGuiScenePanel.h"
#include "kGuiScenePanelItem.h"
#include "kSingleWidget.h"
#include "kPropertiesWidget.h"
#include "kAboutWidget.h"
#include "kHelper.h"

#ifndef QT_NO_OPENGL
#include <QtOpenGL>
#endif

kGuiScene::kGuiScene( kGui* gui )
	: QGraphicsScene( gui ),
	mGui( gui ),
	mPanel( 0 )
{
	Q_ASSERT( mGui );
}

kGuiScene::~kGuiScene()
{
}

void kGuiScene::initialize( const QSize& gridSize )
{
	setSceneRect( QRect( QPoint( 0, 0 ), mGui->sizeHint() ) );
	
	qreal min = qMin( mGui->sizeHint().width(), mGui->sizeHint().height() ) *0.85;
	qreal x = ( mGui->sizeHint().width() -min ) /2;
	qreal y = ( mGui->sizeHint().height() -min ) /2;
	QRectF bounds = kHelper::translatedRectXY( QRectF( QPointF( 0, 0 ), QSizeF( min, min ) ), x, y );
	
	mPanel = new kGuiScenePanel( bounds, gridSize, this );
	mPanel->setPos( x, y );
	
	mPanel->item( QPoint( 0, 0 ) )->setWidget( new kSingleWidget( mPanel ) );
	mPanel->item( QPoint( 0, 1 ) )->setWidget( new kPropertiesWidget( mPanel ) );
	mPanel->item( QPoint( 1, 1 ) )->setWidget( new kAboutWidget( mPanel ) );
	
	addItem( mPanel );
	
	mGui->setFrameStyle( QFrame::NoFrame );
	mGui->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	mGui->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	mGui->setCacheMode( QGraphicsView::CacheBackground );
	mGui->setViewportUpdateMode( QGraphicsView::FullViewportUpdate );
	mGui->setRenderHints( QPainter::Antialiasing | QPainter::SmoothPixmapTransform );
	mGui->setBackgroundBrush( QPixmap( ":/gui/background.jpg" ) );
#ifndef QT_NO_OPENGL
	mGui->setViewport( new QGLWidget( QGLFormat( QGL::SampleBuffers ) ) );
#endif

	mGui->setScene( this );
	mPanel->setCurrentItem( QPoint(), false );
}
