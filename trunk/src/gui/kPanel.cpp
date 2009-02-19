#include "kPanel.h"
#include "kPanelItem.h"
#include "kSingleWidget.h"
#include "kPropertiesWidget.h"
#include "kAboutWidget.h"

#ifndef QT_NO_OPENGL
#include <QtOpenGL>
#endif

const int mFactor = 150;

kPanel::kPanel( QWidget* parent )
	: QGraphicsView( parent ),
	mGridSize( 2, 2 ),
	mSelectedX( 0 ),
	mSelectedY( 0 ),
	mFlipped( false ),
	mFlipLeft( true )
{
	setFrameStyle( QFrame::NoFrame );
	setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	setCacheMode( CacheBackground );
	setViewportUpdateMode( FullViewportUpdate );
	setRenderHints( QPainter::Antialiasing | QPainter::SmoothPixmapTransform );
	setBackgroundBrush( QPixmap( ":/gui/background.jpg" ) );
#ifndef QT_NO_OPENGL
	setViewport( new QGLWidget( QGLFormat( QGL::SampleBuffers ) ) );
#endif

	// area bound
	QRectF bounds( ( -mGridSize.width() /2.0 ) *mFactor, ( -mGridSize.height() /2.0 ) *mFactor, mGridSize.width() *mFactor, mGridSize.height() *mFactor );
	
	qWarning() << bounds;

	// scene
	mScene = new QGraphicsScene( bounds, this );
	setScene( mScene );

	// container item
	mContainerItem = new kPanelItem( bounds, QColor( 226, 255, 92, 64 ) );
	mContainerItem->setZValue( 10 );
	mScene->addItem( mContainerItem );

	// widget to show on flip
	mBackItem = new kPanelItem( bounds, QColor() );
	mBackItem->setTransform( QTransform().rotate( 180, Qt::YAxis ) );
	mBackItem->setParentItem( mContainerItem );
	mBackItem->setZValue( 30 );
	mBackItem->setVisible( false );
	
	// selection item
	mSelectionItem = new kPanelItem( QRectF( -60, -60, 120, 120 ), Qt::gray );
	mSelectionItem->setParentItem( mContainerItem );
	mSelectionItem->setZValue( -1 );
	
	// items
	
	// single
	kPanelItem* singleItem = new kPanelItem( QRectF( -54, -54, 108, 108 ), QColor( 214, 240, 110, 128 )/*, new kSingleWidget( this )*/ );
	singleItem->setPos( posForLocation( 0, 0 ) );
	singleItem->setParentItem( mContainerItem );
	singleItem->setFlag( QGraphicsItem::ItemIsFocusable );
	singleItem->setPixmap( QPixmap( ":/gui/single.png" ) );
	singleItem->setZValue( 20 );
	mItems[ 0 ][ 0 ] = singleItem;
	connect( singleItem, SIGNAL( activated() ), this, SLOT( flip() ) );
	
	// team
	kPanelItem* teamItem = new kPanelItem( QRectF( -54, -54, 108, 108 ), QColor( 214, 240, 110, 128 ) );
	teamItem->setPos( posForLocation( 1, 0 ) );
	teamItem->setParentItem( mContainerItem );
	teamItem->setFlag( QGraphicsItem::ItemIsFocusable );
	teamItem->setPixmap( QPixmap( ":/gui/team.png" ) );
	teamItem->setZValue( 20 );
	mItems[ 1 ][ 0 ] = teamItem;
	connect( teamItem, SIGNAL( activated() ), this, SLOT( flip() ) );
	
	// properties
	kPanelItem* propertiesItem = new kPanelItem( QRectF( -54, -54, 108, 108 ), QColor( 214, 240, 110, 128 )/*, new kPropertiesWidget( this )*/ );
	propertiesItem->setPos( posForLocation( 0, 1 ) );
	propertiesItem->setParentItem( mContainerItem );
	propertiesItem->setFlag( QGraphicsItem::ItemIsFocusable );
	propertiesItem->setPixmap( QPixmap( ":/gui/properties.png" ) );
	propertiesItem->setZValue( 20 );
	mItems[ 0 ][ 1 ] = propertiesItem;
	connect( propertiesItem, SIGNAL( activated() ), this, SLOT( flip() ) );
	
	// about
	kPanelItem* aboutItem = new kPanelItem( QRectF( -54, -54, 108, 108 ), QColor( 214, 240, 110, 128 )/*, new kAboutWidget( this )*/ );
	aboutItem->setPos( posForLocation( 1, 1 ) );
	aboutItem->setParentItem( mContainerItem );
	aboutItem->setFlag( QGraphicsItem::ItemIsFocusable );
	aboutItem->setPixmap( QPixmap( ":/gui/about.png" ) );
	aboutItem->setZValue( 20 );
	mItems[ 1 ][ 1 ] = aboutItem;
	connect( aboutItem, SIGNAL( activated() ), this, SLOT( flip() ) );
	
	// time lines animation
	mSelectionTimeLine = new QTimeLine( 250, this );
	mFlipTimeLine = new QTimeLine( 500, this );
	
	// connections
	connect( mBackItem, SIGNAL( activated() ), this, SLOT( flip() ) );
	connect( mSelectionTimeLine, SIGNAL( valueChanged( qreal ) ), this, SLOT( updateSelectionStep( qreal ) ) );
	connect( mFlipTimeLine, SIGNAL( valueChanged( qreal ) ), this, SLOT( updateFlipStep( qreal ) ) );

	// default item and selection
	setCurrentItem( 0, 0, false );
	
	splash = 0;
/*
	splash = new SplashItem;
	splash->setZValue(5);
	splash->setPos(-splash->rect().width() / 2, mScene->sceneRect().top());
	mScene->addItem(splash);

	splash->grabKeyboard();
	*/
	
	updateSelectionStep( 0 );
}

kPanel::~kPanel()
{
	foreach ( const int& x, mItems.keys() )
	{
		foreach ( const int& y, mItems[ x ].keys() )
		{
			delete mItems[ x ][ y ];
		}
	}
	
	mItems.clear();
}

QSize kPanel::sizeHint() const
{
	return QSize( 640, 480 );
}

bool kPanel::canFlip() const
{
	return mSelectionTimeLine->state() != QTimeLine::Running && mFlipTimeLine->state() != QTimeLine::Running;
}

bool kPanel::canMove() const
{
	return mSelectionTimeLine->state() != QTimeLine::Running;
}

bool kPanel::isKeyPad( QKeyEvent* event ) const
{
	return event->key() == Qt::Key_Right || event->key() == Qt::Key_Left || event->key() == Qt::Key_Up || event->key() == Qt::Key_Down;
}

bool kPanel::isFlipped() const
{
	return mFlipped;
}

void kPanel::switchFullScreen()
{
	if ( isFullScreen() )
	{
		showNormal();
	}
	else
	{
		showFullScreen();
	}
}
	
void kPanel::keyPressEvent( QKeyEvent* event )
{
	if ( event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_F )
	{
		switchFullScreen();
	}
	
	if ( !canMove() || !isKeyPad( event ) || mFlipped )
	{
		QGraphicsView::keyPressEvent( event );
		return;
	}
	
	mSelectedX = ( mSelectedX +mGridSize.width() +( event->key() == Qt::Key_Right ) -( event->key() == Qt::Key_Left ) ) %mGridSize.width();
	mSelectedY = ( mSelectedY +mGridSize.height() +( event->key() == Qt::Key_Down ) -( event->key() == Qt::Key_Up ) ) %mGridSize.height();
	
	setCurrentItem( mSelectedX, mSelectedY, true );
}

void kPanel::mousePressEvent( QMouseEvent* event )
{
	if ( event->modifiers() == Qt::NoModifier && event->button() == Qt::LeftButton && !mFlipped )
	{
		kPanelItem* item = static_cast<kPanelItem*>( itemAt( event->pos() ) );
		int newX = mSelectedX, newY = mSelectedY;
		
		foreach ( const int& x, mItems.keys() )
		{
			foreach ( const int& y, mItems[ x ].keys() )
			{
				if ( mItems[ x ][ y ] == item )
				{
					newX = x;
					newY = y;
					break;
				}
			}
		}
		
		if ( newX != mSelectedX || newY != mSelectedY )
		{
			mSelectedX = newX;
			mSelectedY = newY;
			setCurrentItem( mSelectedX, mSelectedY, true );
			return;
		}
	}
	
	QGraphicsView::mousePressEvent( event );
}

void kPanel::resizeEvent( QResizeEvent* event )
{
	QGraphicsView::resizeEvent( event );
	fitInView( mScene->sceneRect(), Qt::KeepAspectRatio );
}

QPointF kPanel::posForLocation(int x, int y) const
{
	return QPointF( x *mFactor, y *mFactor ) -QPointF( ( mGridSize.width() -1 ) *( mFactor /2 ), ( mGridSize.height() -1 ) *( mFactor /2 ) );
}

void kPanel::setCurrentItem( int x, int y, bool animate )
{
	if ( !canMove() )
	{
		return;
	}
	
	mItems[ x ][ y ]->setFocus();
	
	if ( animate )
	{
		mSelectionStart = mSelectionItem->pos();
		mSelectionEnd = posForLocation( x, y );
		mSelectionTimeLine->start();
	}
	else
	{
		mSelectionItem->setPos( posForLocation( x, y ) );
		mSelectionStart = mSelectionItem->pos();
	}
}

void kPanel::updateSelectionStep( qreal val )
{
	QPointF newPos( mSelectionStart.x() +( mSelectionEnd -mSelectionStart ).x() *val, mSelectionStart.y() +( mSelectionEnd -mSelectionStart ).y() *val );
	mSelectionItem->setPos( newPos );

	QTransform transform;
	mContainerRotationY = newPos.x() /6.0;
	mContainerRotationX = newPos.y() /6.0;
	transform.rotate( newPos.x() /6.0, Qt::YAxis );
	transform.rotate( newPos.y() /6.0, Qt::XAxis );
	mContainerItem->setTransform( transform );
}

void kPanel::updateFlipStep( qreal val )
{
	qreal finalxrot = mContainerRotationX -mContainerRotationX *val;
	qreal finalyrot;
	
	if ( mFlipLeft )
	{
		finalyrot = mContainerRotationY -mContainerRotationY *val -180 *val;
	}
	else
	{
		finalyrot = mContainerRotationY -mContainerRotationY *val +180 *val;
	}
	
	QTransform transform;
	transform.rotate( finalyrot, Qt::YAxis );
	transform.rotate( finalxrot, Qt::XAxis );
	qreal scale = 1 -sin( M_PI *val ) *0.6;
	transform.scale( scale, scale );
	mContainerItem->setTransform( transform );
	
	if ( val == 0 )
	{
		mBackItem->setVisible( false );
		mItems[ mSelectedX ][ mSelectedY ]->setFocus();
	}
}

void kPanel::flip()
{
	if ( !canFlip() )
	{
		return;
	}

	if ( mFlipTimeLine->currentValue() == 0 )
	{
		kPanelItem* item = qobject_cast<kPanelItem*>( sender() );
		kEmbeddedWidget* widget = item->widget();
		
		if ( widget )
		{
			widget->loadDatas();
			mBackItem->setWidget( widget );
			mBackItem->setVisible( true );
			
			mFlipped = true;
			mFlipLeft = mSelectionItem->pos().x() < 0;
			mFlipTimeLine->setDirection( QTimeLine::Forward );
			mFlipTimeLine->start();
		}
	}
	else
	{
		mBackItem->setVisible( true );
		
		mFlipped = false;
		mFlipTimeLine->setDirection( QTimeLine::Backward );
		mFlipTimeLine->start();
	}
}
