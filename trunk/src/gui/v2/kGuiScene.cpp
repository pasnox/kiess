#include "kGuiScene.h"
#include "kGui.h"
#include "kGuiScenePanel.h"

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
	qreal min = qMin( mGui->sizeHint().width(), mGui->sizeHint().height() ) *0.85;
	qreal x = ( mGui->sizeHint().width() -min ) /2;
	qreal y = ( mGui->sizeHint().height() -min ) /2;
	QRectF bounds = QRectF( QPointF( x, y ), QSizeF( min, min ) );
	
	setSceneRect( QRect( QPoint( 0, 0 ), mGui->sizeHint() ) );
	
	mPanel = new kGuiScenePanel( bounds, gridSize, this );
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
