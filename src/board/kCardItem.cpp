#include "kCardItem.h"

#include "math.h"

#include <QGraphicsProxyWidget>
#include <QPainter>

kCardItem::kCardItem( const QRectF& rect, const QBrush& brush)
	: QObject( 0 ), QGraphicsRectItem( rect ),
	_mBrush( brush ),
	_mLastVal( 0 ),
	_mOpacity( 1 ),
	_mFlipTimeLine( 500, this ),
	_mSourcePixmap(QPixmap()) //source pixmap
{
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
    painter->drawRoundRect(rect().translated(2, 2));

    QLinearGradient gradient(rect().topLeft(), rect().bottomRight());
    const QColor col = _mBrush.color();
    gradient.setColorAt(0, col);
    gradient.setColorAt(1, col.dark(int(200 + _mLastVal * 50)));
    painter->setBrush(gradient);


    painter->setPen(QPen(Qt::black, 1));
    painter->drawRoundRect(rect());
    if (!_mPixmap.isNull()) {
        painter->scale(1.95, 1.95);
        painter->drawPixmap(-_mPixmap.width() / 2, -_mPixmap.height() / 2, _mPixmap);
    }
}

//__________________________________________________________________________________________________________________________________________________
//METHOD
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
 * Permuts between null pixmap and source pixmap when card is folded
 */
void kCardItem::setPixmap(const QPixmap &pixmap)
{
	//store the first QPixmap assignment
	if (_mSourcePixmap.isNull())
		_mSourcePixmap = pixmap;
	//set a null pixmap (card)
	if (!_mPixmap.isNull())
		_mPixmap = pixmap;
	else
		_mPixmap = _mSourcePixmap; //restore the source pixmap
    if (scene() && isVisible())
        update();
}

//____________________________________________________________________________________________________________
//Event (Keyboard and Mouse)
void kCardItem::keyPressEvent(QKeyEvent *event)
{
	if (event->key() != Qt::Key_Return) {
        QGraphicsRectItem::keyPressEvent(event);
        return;
    }
	//animation
	_mChangePicture = FALSE;
	_mFlipTimeLine.setDirection( QTimeLine::Forward );
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
	emit returnCardItem(this);
}

void kCardItem::updateValue( qreal value )
{
	setTransform( QTransform().rotate((value * 180), Qt::YAxis  ));
	if (value >= .5 && _mChangePicture == FALSE) {
		_mChangePicture = TRUE;
		setPixmap(QPixmap());
	}
}

void kCardItem::finishedRotation()
{
	//animation
	if ( _mFlipTimeLine.direction() != QTimeLine::Backward )
	{
		_mFlipTimeLine.stop();
		_mFlipTimeLine.setDirection( QTimeLine::Backward );
		_mChangePicture = FALSE;
	}
}