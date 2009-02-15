#include "kGuiScenePanel.h"
#include "kGuiScenePanelItem.h"

#include <QPainter>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>

kGuiScenePanel::kGuiScenePanel( const QRectF& rect, const QSize& gridSize, QObject* parent )
	: QObject( parent ), QGraphicsRectItem( rect ),
	mBrush( QColor( 226, 255, 92, 64 ) ),
	mGridSize( gridSize ),
	mSelectionItemFactor( 0.1 ),
	mItemFactor( 0.15 ),
	mSelectionTimeLine( 250, this )
{	
	qreal width = ( rect.width() /(qreal)mGridSize.width() );
	qreal height = ( rect.height() /(qreal)mGridSize.height() );
	qreal left = ( rect.width() /(qreal)mGridSize.width() );
	qreal top = ( rect.height() /(qreal)mGridSize.height() );
	
	mSelectionItem = new kGuiScenePanelItem( QRectF( 0, 0, width *0.8, height *0.8 ), Qt::gray );
	mSelectionItem->setParentItem( this );
	mSelectionItem->setZValue( -1 );
	
	for ( int x = 0; x < mGridSize.width(); x++ )
	{
		for ( int y = 0; y < mGridSize.height(); y++ )
		{
			kGuiScenePanelItem* item = new kGuiScenePanelItem( QRectF( 0, 0, width *0.7, height *0.7 ), QColor( 214, 240, 110, 128 ) );
			item->setParentItem( this );
			item->setFlag( QGraphicsItem::ItemIsFocusable );
			item->setPixmap( QPixmap( ":/gui/single.png" ) );
			item->setPos( gridPosition( QPoint( x, y ), mItemFactor ) );
			item->setZValue( 10 );
			
			mItems[ x ][ y ] = item;
		}
	}
	
	connect( &mSelectionTimeLine, SIGNAL( valueChanged( qreal ) ), this, SLOT( selectionTimeLineChanged( qreal ) ) );
}

kGuiScenePanel::~kGuiScenePanel()
{
}

void kGuiScenePanel::paint( QPainter* painter, const QStyleOptionGraphicsItem* options, QWidget* widget )
{
	Q_UNUSED( options );
	Q_UNUSED( widget );

	painter->setOpacity( 1 );
	
	painter->setPen( Qt::NoPen );
	painter->setBrush( QColor( 0, 0, 0, 64 ) );
	painter->drawRoundRect( rect().translated( 2, 2 ) );
	
	painter->setPen( QPen( Qt::black, 1 ) );
	painter->setBrush( mBrush );
	painter->drawRoundRect( rect() );
}

QRectF kGuiScenePanel::boundingRect() const
{
	qreal penW = 0.5;
	qreal shadowW = 2.0;
	return rect().adjusted( -penW, -penW, penW +shadowW, penW +shadowW );
}

kGuiScenePanelItem* kGuiScenePanel::item( const QPoint& pos ) const
{
	return mItems.value( pos.x() ).value( pos.y() );
}

void kGuiScenePanel::setCurrentItem( const QPoint& pos, bool animate )
{
	item( pos )->setFocus();
	
	if ( animate )
	{
		mSelectionTimeLine.stop();
		mSelectionStart = mSelectionItem->pos();
		mSelectionEnd = gridPosition( pos, mSelectionItemFactor );
		mSelectionTimeLine.start();
	}
	else
	{
		mSelectionTimeLine.stop();
		mSelectionItem->setPos( gridPosition( pos, mSelectionItemFactor ) );
		mSelectionStart = mSelectionItem->pos();
		
		emit selectionMoved( mSelectionStart );
	}
}

bool kGuiScenePanel::isSelectionMoving() const
{
	return mSelectionTimeLine.state() == QTimeLine::Running;
}

QPointF kGuiScenePanel::gridPosition( const QPoint& pos, qreal factor ) const
{
	qreal width = ( rect().width() /(qreal)mGridSize.width() );
	qreal height = ( rect().height() /(qreal)mGridSize.height() );
	
	qreal x = width *pos.x();
	qreal y = height *pos.y();
	
	x += width *factor;
	y += height *factor;
	
	return QPointF( x, y );
}

bool kGuiScenePanel::isKeyPad( QKeyEvent* event ) const
{
	return event->key() == Qt::Key_Right || event->key() == Qt::Key_Left || event->key() == Qt::Key_Up || event->key() == Qt::Key_Down;
}

void kGuiScenePanel::keyPressEvent( QKeyEvent* event )
{
	if ( ( event->isAutoRepeat() && isSelectionMoving() ) || !isKeyPad( event ) )
	{
		QGraphicsRectItem::keyPressEvent( event );
		return;
	}
	
	mSelectedPos.rx() = ( mSelectedPos.x() +mGridSize.width() +( event->key() == Qt::Key_Right ) -( event->key() == Qt::Key_Left ) ) %mGridSize.width();
	mSelectedPos.ry() = ( mSelectedPos.y() +mGridSize.height() +( event->key() == Qt::Key_Down ) -( event->key() == Qt::Key_Up ) ) %mGridSize.height();
	
	setCurrentItem( mSelectedPos, true );
}

void kGuiScenePanel::mousePressEvent( QGraphicsSceneMouseEvent* event )
{
	if ( event->modifiers() == Qt::NoModifier && event->button() == Qt::LeftButton )
	{
		QPoint newPos = mSelectedPos;
		
		foreach ( const int& x, mItems.keys() )
		{
			foreach ( const int& y, mItems[ x ].keys() )
			{
				kGuiScenePanelItem* item = mItems[ x ][ y ];
				
				if ( item->contains( item->mapFromScene( event->scenePos() ) ) )
				{
					newPos = QPoint( x, y );
					break;
				}
			}
		}
		
		if ( newPos != mSelectedPos )
		{
			mSelectedPos = newPos;
			setCurrentItem( mSelectedPos, true );
			return;
		}
	}
	
	QGraphicsRectItem::mousePressEvent( event );
}

void kGuiScenePanel::selectionTimeLineChanged( qreal val )
{
	QPointF newPos( mSelectionStart.x() +( mSelectionEnd -mSelectionStart ).x() *val, mSelectionStart.y() +( mSelectionEnd -mSelectionStart ).y() *val );
	mSelectionItem->setPos( newPos );
	
	emit selectionMoved( newPos );
}
