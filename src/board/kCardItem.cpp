#include "kCardItem.h"

#include "math.h"

#include <QGraphicsProxyWidget>
#include <QPainter>
#include <QDebug>

kCardItem::kCardItem( const QRectF& rect, const QBrush& brush)
    : QObject( 0 ), QGraphicsRectItem( rect ),
    _mBrush( brush ),
    _mCardState(FALSE),
    _mFlipTimeLine( 500, this ),
    _mIsSelected(FALSE),
    _mLastVal( 0 ),
    _mOpacity( 1 ),
    _mPixmapBorder(3),
    _mSourcePixmap(QPixmap()), //source pixmap
    _mViewMode(ViewMode::VIEW2D)
{
    _mFlipTimeLine.setDirection( QTimeLine::Forward );

    connect( &_mFlipTimeLine, SIGNAL( valueChanged( qreal ) ), this, SLOT( updateValue( qreal ) ) );
    connect( &_mFlipTimeLine, SIGNAL( finished() ), this, SLOT( finishedRotation( ) ) );
}

kCardItem::~kCardItem()
{
}

QRectF kCardItem::boundingRect() const
{
    qreal penW = 0.5;
    qreal shadowW = 2.0;
    return rect().adjusted(-penW, -penW, penW + shadowW, penW + shadowW);
}

void kCardItem::paint( QPainter* painter, const QStyleOptionGraphicsItem* options, QWidget* widget )
{
    Q_UNUSED(widget);
    Q_UNUSED(options);
    painter->setOpacity(opacity());
    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor(0, 0, 0, 64));

    painter->drawRoundRect(rect().translated(2, 2), 10, 10);

    QLinearGradient gradient(rect().topLeft(), rect().bottomRight());
    const QColor col = _mBrush.color();
    gradient.setColorAt(0, col);
    gradient.setColorAt(1, col.dark(int(200 + _mLastVal * 50)));
    painter->setBrush(gradient);

    if (_mViewMode == ViewMode::VIEW3D)
        painter->translate(0, -rect().height());

    painter->setPen(QPen(Qt::black, 1));
    painter->drawRoundRect(rect(), 10, 10);
    QRectF source(0.0, 0.0, _mPixmap.width(), _mPixmap.height());
    QRectF target(- rect().width() / 4 + _mPixmapBorder, -rect().height() / 4 + _mPixmapBorder, rect().width() / 2 - _mPixmapBorder * 2, rect().height() / 2 - _mPixmapBorder * 2);
    if (!_mPixmap.isNull()) {
        painter->scale(1.95, 1.95);
        painter->drawPixmap(target, _mPixmap, source);
    }

}

//________________________________________________________________________________________________________________________________________
//METHOD
//________________________________________________________________________________________________________________________________________

qreal kCardItem::opacity() const
{
    kCardItem *parent = parentItem() ? (kCardItem *)parentItem() : 0;
    return _mOpacity + (parent ? parent->opacity() : 0);
}

void kCardItem::setOpacity(qreal opacity)
{
    _mOpacity = opacity;
    update();
}

/*!
 * \brief
 * Set the cardItem pixmap
 * 
 * \param pixmap
 * Pixmap to give
 * 
 * Permutes between null pixmap and source pixmap when card is folded
 */
void kCardItem::setPixmap(const QPixmap &pixmap)
{
    if (_mSourcePixmap.isNull()) {
        //store first assignment
        _mSourcePixmap = pixmap;
        //store current pixmap
        _mPixmap = pixmap;
        //card is front
        _mCardState = TRUE;
        return;
    }

    if (_mCardState == TRUE) { //card is front
        _mCardState = FALSE;
        _mPixmap = QPixmap( ":/board/blueBack.png" );
    }
    else { //card is back
        _mCardState = TRUE;
        _mPixmap = _mSourcePixmap;
    }
    if (scene() && isVisible())
        update();
}

//________________________________________________________________________________________________________________________________________
// EVENT
//________________________________________________________________________________________________________________________________________

void kCardItem::keyPressEvent(QKeyEvent *event)
{
    if (event->key() != Qt::Key_Return) {
        QGraphicsRectItem::keyPressEvent(event);
        return;
    }
    //animation
    _mChangePicture = FALSE;
    _mFlipTimeLine.start();
}

void kCardItem::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() != Qt::Key_Return) {
        QGraphicsRectItem::keyReleaseEvent(event);
        return;
    }
}

void kCardItem::mousePressEvent( QGraphicsSceneMouseEvent * event )
{
    Q_UNUSED(event);
    if (_mIsSelected == TRUE) {
        //animation
        _mChangePicture = FALSE;
        _mFlipTimeLine.start();
        emit returnCardItem(this);
    }

    else {
        _mIsSelected = TRUE;
        emit returnCardItem(this);
    }
}
//________________________________________________________________________________________________________________________________________
// ANIMATION
//________________________________________________________________________________________________________________________________________

/*!
* \brief
* Card Item Rotation.
*/
void kCardItem::updateValue( qreal value )
{
    //rotate card
    if (_mViewMode == ViewMode::VIEW3D) {
        QTransform transform;
        transform.rotate(-60, Qt::XAxis); //perspective view
        transform.translate(0, -rect().height());
        transform.rotate((value * -130), Qt::XAxis  );
        setTransform(transform);
    }
    else
        setTransform( QTransform().rotate((value * 180), Qt::YAxis  )); //rotate by 180� the card item
    if (value >= .5 && _mChangePicture == FALSE &&  _mFlipTimeLine.direction() == QTimeLine::Forward) { //when the rotation is at 90�, change the  card picture (front / back)
        _mChangePicture = TRUE; //change flag
        setPixmap(QPixmap()); //flip picture
    }
    if (value <= .5 && _mChangePicture == FALSE &&  _mFlipTimeLine.direction() == QTimeLine::Backward) { //when the rotation is at 90�, change the  card picture (front / back)
        _mChangePicture = TRUE; //change flag
        setPixmap(QPixmap()); //flip picture
    }
}

/*!
 * \brief
 * Stop timeline.
  */
void kCardItem::finishedRotation()
{
    //animation

    //reverse timeline
    if ( _mFlipTimeLine.direction() == QTimeLine::Forward)
        _mFlipTimeLine.setDirection( QTimeLine::Backward );
    else
        _mFlipTimeLine.setDirection( QTimeLine::Forward );

    //stop timeline
    _mFlipTimeLine.stop();

    //change flag
    _mChangePicture = FALSE;
}

void kCardItem::setViewMode( const ViewMode::BoardViewMode& mode )
{
    _mViewMode = mode;
    if (_mViewMode == ViewMode::VIEW3D) {
        QTransform transform;
        transform.rotate(-60, Qt::XAxis); //perspective view
        setTransform(transform);
    }
}
