#include "kBoard.h"
#include "kCardItem.h"

#include <QTimeLine>

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

    //TEST directory to load pictures
    QDir pixmapDirectory("Z:/kiess/trunk/src/resources/board/front");
    createListPixmap(pixmapDirectory);

    createItems();

    _mSelectionTimeLine = new QTimeLine(150, this);

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
    return QSize( 800, 600 );
}

//_________________________________________________________________________
//METHOD

/*!
 * \brief
 * Create all items (Board and cards
 */
void kBoard::createItems()
{	
    _previousItem = 0;
    // selection item
    _mSelectionItem = new kCardItem( QRectF( -70, -70, 140, 140 ), Qt::gray );
    _mSelectionItem->setParentItem( _mContainerItem );
    _mSelectionItem->setViewMode(_mboardViewMode); // 2D or 3D mode
    _mSelectionItem->setZValue( -1 );


    //Create cards
    int cardCount = 0;
    for (int i = 0; i < _mGridSize.width(); i++) {
        for (int j = 0; j < _mGridSize.height(); j++) {
            kCardItem* cardItem = new kCardItem( QRectF( -60, -60, 120, 120 ), QColor(90, 170, 220, 128));
            //when user click on item, the item is sent ti the view in order to move selection
            connect(cardItem, SIGNAL(returnCardItem(kCardItem*)), this, SLOT(selectedCardItem(kCardItem*)));
            //item can be select
            cardItem->setFlag(QGraphicsItem::ItemIsSelectable);
            cardItem->setPos( posForLocation( i, j ) );
            cardItem->setParentItem( _mContainerItem );
            cardItem->setFlag( QGraphicsItem::ItemIsFocusable );
            if (_mListOfPixmap.count() > cardCount) cardItem->setPixmap( QPixmap(_mListOfPixmap[cardCount++]) );
            else cardItem->setPixmap( QPixmap( ":/board/single.png" ) );
            cardItem->setViewMode(_mboardViewMode);// 2D or 3D mode
            _mItems[ i ][ j ] = cardItem; //store item in a qmap
        }
    }

    // default item and selection
    setCurrentItem( 0, 0, false );
    if (_mItems[ 0 ][ 0 ]) {
        _mItems[ 0 ][ 0 ]->setSelected(TRUE);
        _previousItem = _mItems[ 0 ][ 0 ];
    }
}

/*!
* \brief
* List all pixmap in a specific directory
* Only in debug and local mode
* code will disappear
*/
QStringList kBoard::createListPixmap(const QDir& directory)
{
    QStringList filters;
    filters << "*.png";
    QStringList tmpListOfPixmap = directory.entryList(filters);
    foreach(QString file, tmpListOfPixmap) {
        _mListOfPixmap << directory.absolutePath() + "/" + file;
    }
    return _mListOfPixmap;
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
    _mContainerItem->setAcceptedMouseButtons(Qt::NoButton);

    _mScene->addItem( _mContainerItem );

    //In 3D Mode, the item container is rotate for a perspective view
    if (_mboardViewMode == ViewMode::VIEW3D) {
        QTransform transform;
        //perspective
        transform.rotate(70, Qt::XAxis);
        transform.scale(0.8, 1.5);
        //translate to render the item so far
        transform.translate(0, -100);
        _mContainerItem->setTransform(transform);
    }
}

/*!
* \brief
* Initialization of the board
*/
void kBoard::initBoardParameters()
{
    //GraphicView Properties
    setFrameStyle( QFrame::NoFrame );
    //deactivate scroolBar
    setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );

    setCacheMode( CacheBackground );
    //full update items
    setViewportUpdateMode( FullViewportUpdate );
    //graphical parameters
    setRenderHints( QPainter::Antialiasing | QPainter::SmoothPixmapTransform );
    //Pixmap view Background
    setBackgroundBrush( QPixmap( ":/board/background.jpg" ) );


#ifndef QT_NO_OPENGL
    setViewport( new QGLWidget( QGLFormat( QGL::SampleBuffers ) ) );
#endif

    //View mode (2D / 3D)
    _mboardViewMode = ViewMode::VIEW2D;
}


/*!
 * \brief
 * Compute coordinate
 * 
 * \param x
 * X coordinate in the grid referential.
 * 
 * \param y
 * Y coordinate in the grid referential.
 * 
 * \returns
 * QPointF with scene coordinate
 * 
 * \see
 * locationForPos( int x, int y )
 */
QPointF kBoard::posForLocation(int x, int y) const
{
    return QPointF(x * 150, y * 150)
            - QPointF((_mGridSize.width() - 1) * 75, (_mGridSize.height() - 1) * 75);
}

/*!
* \brief
* Compute coordinate
* 
* \param x
* X coordinate in the scene referential.
* 
* \param y
* Y coordinate in the scene referential.
* 
* \returns
* QPointF with grid coordinate
* 
* \see
* posForLocation( int x, int y )
*/
QPointF kBoard::locationForPos( int x, int y ) const
{
    return QPointF((x + (_mGridSize.width() - 1) * 75) / 150,(y + (_mGridSize.height() - 1) * 75) / 150);
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
    //Check if item exists
    if (!_mItems[ x ][ y ]) return;

    _mItems[ x ][ y ]->setFocus();

    if ( animate )
    {
        //stop the timeline
        _mSelectionTimeLine->stop();
        //store start position
        _mStartPos = _mSelectionItem->pos();
        //compute end position
        _mEndPos = posForLocation( x, y );
        //start the timeline connect to the updateSelectionStep(qreal) slot
        _mSelectionTimeLine->start(); //start animation
    }
    else
    {
        //animation flag not set
        //only move item at the position X, Y
        _mSelectionItem->setPos( posForLocation( x, y ) );
        //store the start position
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
    if (_previousItem != item && _previousItem) _previousItem->setSelected(FALSE);
    _previousItem = item;
    //compute grid position with item scene coordinate
    QPointF position = locationForPos(item->scenePos().x(), item->scenePos().y());
    //store in boadr parameters
    _mSelectedX = position.x();
    _mSelectedY = position.y();
    //start animation and selection
    setCurrentItem(_mSelectedX, _mSelectedY, true);
}

void kBoard::updateSelectionStep(qreal val)
{
    //Animation with timeline
    //move item selection from the start position to the end position
    QPointF newPos(_mStartPos.x() + (_mEndPos - _mStartPos).x() * val,
                   _mStartPos.y() + (_mEndPos - _mStartPos).y() * val);
    _mSelectionItem->setPos(newPos);
}

void kBoard::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    fitInView(_mScene->sceneRect(), Qt::KeepAspectRatio);
}
