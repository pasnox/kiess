#include "kGui.h"
#include "kGuiScene.h"
#include "kGuiScenePanel.h"
#include "kGuiScenePanelItem.h"
#include "kChatItem.h"

#include "kSingleWidget.h"
#include "kPropertiesWidget.h"
#include "kAboutWidget.h"
#include "kChatWidget.h"

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
	
	mPanel = new kGuiScenePanel( bounds, QSize( 2, 2 ), mScene );
	mPanel->setCurrentItem( QPoint(), false );
	mPanel->setPos( x, y );
	
	// widgets
	mWidgets[ Single ] = new kSingleWidget( mPanel );
	//mWidgets[ Team ] = new ;
	mWidgets[ Properties ] = new kPropertiesWidget( mPanel );
	mWidgets[ About ] = new kAboutWidget( mPanel );
	mWidgets[ Chat ] = new kChatWidget();
	
	// init panel items widget
	// single player game
	mPanel->item( QPoint( 0, 0 ) )->setPixmap( QPixmap( ":/gui/single.png" ) );
	mPanel->item( QPoint( 0, 0 ) )->setWidget( qobject_cast<kEmbeddedWidget*>( mWidgets[ Single ] ) );
	// team player game
	mPanel->item( QPoint( 1, 0 ) )->setPixmap( QPixmap( ":/gui/team.png" ) );
	// properties
	mPanel->item( QPoint( 0, 1 ) )->setPixmap( QPixmap( ":/gui/properties.png" ) );
	mPanel->item( QPoint( 0, 1 ) )->setWidget( qobject_cast<kEmbeddedWidget*>( mWidgets[ Properties ] ) );
	// about
	mPanel->item( QPoint( 1, 1 ) )->setPixmap( QPixmap( ":/gui/about.png" ) );
	mPanel->item( QPoint( 1, 1 ) )->setWidget( qobject_cast<kEmbeddedWidget*>( mWidgets[ About ] ) );
	
	// chat item
	mChatItem = new kChatItem( mScene->sceneRect(), qobject_cast<kChatWidget*>( mWidgets[ Chat ] ) );
	mChatItem->setVisible( false );
	
	// set scene
	setScene( mScene );
	mScene->addItem( mPanel );
	mScene->addItem( mChatItem );
	
	// connections
	connect( mPanel, SIGNAL( itemRejected( QWidget* ) ), this, SLOT( itemRejected( QWidget* ) ) );
	connect( mPanel, SIGNAL( itemAccepted( QWidget* ) ), this, SLOT( itemAccepted( QWidget* ) ) );
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

void kGui::itemRejected( QWidget* widget )
{
	Q_UNUSED( widget );
}

void kGui::itemAccepted( QWidget* widget )
{
	switch ( mWidgets.key( widget ) )
	{
		case Single:
		{
			kSingleWidget* ks = qobject_cast<kSingleWidget*>( widget );
			kChatWidget* kc = qobject_cast<kChatWidget*>( mWidgets[ Chat ] );
			
			kc->setClient( ks->client(), ks->leNick->text() );
			mPanel->setVisible( false );
			mChatItem->setVisible( true );
			break;
		}
		case Team:
			break;
		case Properties:
			break;
		case About:
			break;
		case Chat:
		default:
			break;
	}
}
