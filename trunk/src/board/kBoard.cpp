#include "kBoard.h"
#include "kCardItem.h"

#ifndef QT_NO_OPENGL
#include <QtOpenGL>
#endif

kBoard::kBoard(const int& gridX, const int& gridY, QWidget* parent )
	: QGraphicsView( parent ),
	_mGridSize( gridX, gridY),
	_mSelectedX(0),
	_mSelectedY(0)
{
	//initialization
	initBoardParameters();

	createScene();

	createItems();

    _mSelectionTimeLine = new QTimeLine(150, this);
    _mFlipTimeLine = new QTimeLine(500, this);

    connect(_mSelectionTimeLine, SIGNAL(valueChanged(qreal)), this, SLOT(updateSelectionStep(qreal)));
	updateSelectionStep(0);
}

kBoard::~kBoard()
{
	foreach ( const int& x, _mItems.keys() )
	{
		foreach ( const int& y, _mItems[ x ].keys() )
		{
			delete _mItems[ x ][ y ];
		}
	}
	_mItems.clear();

	delete _mContainerItem;
}

QSize kBoard::sizeHint() const
{
	return QSize( 640, 480 );
}

//_________________________________________________________________________
//METHOD

/*!
 * \brief
 * Create all items (Board and cards
 */
void kBoard::createItems()
{	
	// selection item
	_mSelectionItem = new kCardItem( QRectF( -60, -60, 120, 120 ), Qt::gray );
	_mSelectionItem->setParentItem( _mContainerItem );
	_mSelectionItem->setZValue( -1 );


	//Create cards
	for (int i = 0; i < _mGridSize.width(); i++) {
		for (int j = 0; j < _mGridSize.height(); j++) {
			kCardItem* cardItem = new kCardItem( QRectF( -54, -54, 108, 108 ), QColor( 214, 240, 110, 128 ) );
			connect(cardItem, SIGNAL(returnCardItem(kCardItem*)), this, SLOT(selectedCardItem(kCardItem*)));
			cardItem->setFlag(QGraphicsItem::ItemIsSelectable);
			cardItem->setPos( posForLocation( i, j ) );
			cardItem->setParentItem( _mContainerItem );
			cardItem->setFlag( QGraphicsItem::ItemIsFocusable );
			cardItem->setPixmap( QPixmap( ":/board/single.png" ) );
			_mItems[ i ][ j ] = cardItem;
		}
	}

	// default item and selection
	setCurrentItem( 0, 0, false );
}

/*!
* \brief
* Create environment
*/
void kBoard::createScene()
{
	// area bound
	QRectF bounds( ( -_mGridSize.width() /2.0 ) *150, ( -_mGridSize.height() /2.0 ) *150, _mGridSize.width() *150, _mGridSize.height() *150 );

	// scene
	_mScene = new QGraphicsScene( bounds, this );
	setScene( _mScene );

	// container item
	_mContainerItem = new kCardItem( bounds, QColor( 226, 255, 92, 64 ) );
	_mScene->addItem( _mContainerItem );
}

/*!
* \brief
* Initailization of the board
*/
void kBoard::initBoardParameters()
{
	//GraphicView Properties
	setFrameStyle( QFrame::NoFrame );
	setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	setCacheMode( CacheBackground );
	setViewportUpdateMode( FullViewportUpdate );
	setRenderHints( QPainter::Antialiasing | QPainter::SmoothPixmapTransform );
	setBackgroundBrush( QPixmap( ":/board/background.jpg" ) );

#ifndef QT_NO_OPENGL
	setViewport( new QGLWidget( QGLFormat( QGL::SampleBuffers ) ) );
#endif
}


QPointF kBoard::posForLocation(int x, int y) const
{
	return QPointF(x * 150, y * 150)
		- QPointF((_mGridSize.width() - 1) * 75, (_mGridSize.height() - 1) * 75);
}

/*!
 * \brief
 * Move the _mSelectionItem to the selected cardItem
 * 
 * \param x
 * x coordinate (in the grid).
 * 
 * \param y
 * y coordinate (in the grid).
 * 
 * \param animate
 * Animation
 * 
 * The real x,y coordinate are computed from the following x,y coordinate in the grid referential.
 */
void kBoard::setCurrentItem( int x, int y, bool animate )
{
	if (!_mItems[ x ][ y ]) return;

	_mItems[ x ][ y ]->setFocus();

	if ( animate )
	{
		_mSelectionTimeLine->stop();
		_mStartPos = _mSelectionItem->pos();
		_mEndPos = posForLocation( x, y );
		_mSelectionTimeLine->start();
	}
	else
	{
		_mSelectionItem->setPos( posForLocation( x, y ) );
		_mStartPos = _mSelectionItem->pos();
	}
}

/*!
 * \brief
 * Selected the cardItem after mousePressEvent received by teh cardItem
 * 
 * \param kCardItem* item
 * Item selected by mousePressEvent
 *
 * The method iterates in all items in _mItems.
 * if item found, item is selected.
 */
void kBoard::selectedCardItem( kCardItem* item)
{
	kCardItem* itemInList = 0;
	_mSelectedX = _mSelectedY = 0;
	item->setFocus();
	//iteration
	for (int i = 0; i < _mGridSize.width(); i++) {
		for (int j = 0; j < _mGridSize.height(); j++) {
			itemInList = _mItems[i][j];
			if (itemInList)
				if (itemInList == item) { //if item is found in the list of cardItems
					_mSelectedX = i;
					_mSelectedY = j;
				}
		}
	}
	setCurrentItem(_mSelectedX, _mSelectedY, true);
}

void kBoard::updateSelectionStep(qreal val)
{
	//Animation with timeline
	QPointF newPos(_mStartPos.x() + (_mEndPos - _mStartPos).x() * val,
		_mStartPos.y() + (_mEndPos - _mStartPos).y() * val);
	_mSelectionItem->setPos(newPos);
}

void kBoard::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    fitInView(_mScene->sceneRect(), Qt::KeepAspectRatio);
}

