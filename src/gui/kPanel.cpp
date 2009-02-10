#include "kPanel.h"
#include "kPanelItem.h"

#ifndef QT_NO_OPENGL
#include <QtOpenGL>
#endif

kPanel::kPanel( QWidget* parent )
	: QGraphicsView( parent ),
	mGridSize( 2, 2 ),
	selectedX(0),
	selectedY(0),
	flipped(false),
	flipLeft(true)
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
	QRectF bounds( ( -mGridSize.width() /2.0 ) *150, ( -mGridSize.height() /2.0 ) *150, mGridSize.width() *150, mGridSize.height() *150 );

	// scene
	mScene = new QGraphicsScene( bounds, this );
	setScene( mScene );

	// container item
	mContainerItem = new kPanelItem( bounds, QColor( 226, 255, 92, 64 ) );
	mScene->addItem( mContainerItem );

	// widget to show on flip
	QWidget* embed = new QLabel( "koolio !" );
	mBackItem = new kPanelItem( bounds, embed->palette().window(), embed );
	mBackItem->setTransform( QTransform().rotate( 180, Qt::YAxis ) );
	mBackItem->setParentItem( mContainerItem );
	
	// selection item
	mSelectionItem = new kPanelItem( QRectF( -60, -60, 120, 120 ), Qt::gray );
	mSelectionItem->setParentItem( mContainerItem );
	mSelectionItem->setZValue( -1 );
	
	// items
	
	// single
	kPanelItem* singleItem = new kPanelItem( QRectF( -54, -54, 108, 108 ), QColor( 214, 240, 110, 128 ) );
	singleItem->setPos( posForLocation( 0, 0 ) );
	singleItem->setParentItem( mContainerItem );
	singleItem->setFlag( QGraphicsItem::ItemIsFocusable );
	singleItem->setPixmap( QPixmap( ":/gui/single.png" ) );
	mItems[ 0 ][ 0 ] = singleItem;
	connect( singleItem, SIGNAL( activated() ), this, SLOT( flip() ) );
	
	// team
	kPanelItem* teamItem = new kPanelItem( QRectF( -54, -54, 108, 108 ), QColor( 214, 240, 110, 128 ) );
	teamItem->setPos( posForLocation( 1, 0 ) );
	teamItem->setParentItem( mContainerItem );
	teamItem->setFlag( QGraphicsItem::ItemIsFocusable );
	teamItem->setPixmap( QPixmap( ":/gui/team.png" ) );
	mItems[ 1 ][ 0 ] = teamItem;
	connect( teamItem, SIGNAL( activated() ), this, SLOT( flip() ) );
	
	// properties
	kPanelItem* propertiesItem = new kPanelItem( QRectF( -54, -54, 108, 108 ), QColor( 214, 240, 110, 128 ) );
	propertiesItem->setPos( posForLocation( 0, 1 ) );
	propertiesItem->setParentItem( mContainerItem );
	propertiesItem->setFlag( QGraphicsItem::ItemIsFocusable );
	propertiesItem->setPixmap( QPixmap( ":/gui/properties.png" ) );
	mItems[ 0 ][ 1 ] = propertiesItem;
	connect( propertiesItem, SIGNAL( activated() ), this, SLOT( flip() ) );
	
	// about²
	kPanelItem* aboutItem = new kPanelItem( QRectF( -54, -54, 108, 108 ), QColor( 214, 240, 110, 128 ) );
	aboutItem->setPos( posForLocation( 1, 1 ) );
	aboutItem->setParentItem( mContainerItem );
	aboutItem->setFlag( QGraphicsItem::ItemIsFocusable );
	aboutItem->setPixmap( QPixmap( ":/gui/about.png" ) );
	mItems[ 1 ][ 1 ] = aboutItem;
	connect( aboutItem, SIGNAL( activated() ), this, SLOT( flip() ) );

	// default item and selection
	setCurrentItem( 0, 0, false );

	
	
	
	

    selectionTimeLine = new QTimeLine(150, this);
    flipTimeLine = new QTimeLine(500, this);

    connect(mBackItem, SIGNAL(activated()),
            this, SLOT(flip()));
    connect(selectionTimeLine, SIGNAL(valueChanged(qreal)),
            this, SLOT(updateSelectionStep(qreal)));
    connect(flipTimeLine, SIGNAL(valueChanged(qreal)),
            this, SLOT(updateFlipStep(qreal)));
	
	splash = 0;
/*
    splash = new SplashItem;
    splash->setZValue(5);
    splash->setPos(-splash->rect().width() / 2, mScene->sceneRect().top());
    mScene->addItem(splash);

    splash->grabKeyboard();
	*/
    
    updateSelectionStep(0);
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
    
void kPanel::keyPressEvent(QKeyEvent *event)
{
    if ( ( splash && splash->isVisible() ) || event->key() == Qt::Key_Return || flipped) {
        QGraphicsView::keyPressEvent(event);
        return;
    }

    selectedX = (selectedX + mGridSize.width() + (event->key() == Qt::Key_Right) - (event->key() == Qt::Key_Left)) % mGridSize.width();
    selectedY = (selectedY + mGridSize.height() + (event->key() == Qt::Key_Down) - (event->key() == Qt::Key_Up)) % mGridSize.height();
	
	setCurrentItem( selectedX, selectedY, true );
}

void kPanel::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    fitInView(mScene->sceneRect(), Qt::KeepAspectRatio);
}

void kPanel::updateSelectionStep(qreal val)
{
    QPointF newPos(startPos.x() + (endPos - startPos).x() * val,
                   startPos.y() + (endPos - startPos).y() * val);
    mSelectionItem->setPos(newPos);
    
    QTransform transform;
    yrot = newPos.x() / 6.0;
    xrot = newPos.y() / 6.0;
    transform.rotate(newPos.x() / 6.0, Qt::YAxis);
    transform.rotate(newPos.y() / 6.0, Qt::XAxis);
    mContainerItem->setTransform(transform);
}

void kPanel::updateFlipStep(qreal val)
{
    qreal finalxrot = xrot - xrot * val;
    qreal finalyrot;
    if (flipLeft)
        finalyrot = yrot - yrot * val - 180 * val;
    else
        finalyrot = yrot - yrot * val + 180 * val;
    QTransform transform;
    transform.rotate(finalyrot, Qt::YAxis);
    transform.rotate(finalxrot, Qt::XAxis);
    qreal scale = 1 - sin(3.14 * val) * 0.3;
    transform.scale(scale, scale);
    mContainerItem->setTransform(transform);
    if (val == 0)
		mItems[ selectedX ][ selectedY ]->setFocus();
}

void kPanel::flip()
{
    if (flipTimeLine->state() == QTimeLine::Running)
        return;

    if (flipTimeLine->currentValue() == 0) {
        flipTimeLine->setDirection(QTimeLine::Forward);
        flipTimeLine->start();
        flipped = true;
        flipLeft = mSelectionItem->pos().x() < 0;
    } else {
        flipTimeLine->setDirection(QTimeLine::Backward);
        flipTimeLine->start();
        flipped = false;
    }
}

QPointF kPanel::posForLocation(int x, int y) const
{
    return QPointF(x * 150, y * 150)
        - QPointF((mGridSize.width() - 1) * 75, (mGridSize.height() - 1) * 75);
}

void kPanel::setCurrentItem( int x, int y, bool animate )
{
	mItems[ x ][ y ]->setFocus();
	
	if ( animate )
	{
		selectionTimeLine->stop();
		startPos = mSelectionItem->pos();
		endPos = posForLocation( x, y );
		selectionTimeLine->start();
	}
	else
	{
		mSelectionItem->setPos( posForLocation( x, y ) );
		startPos = mSelectionItem->pos();
	}
}
