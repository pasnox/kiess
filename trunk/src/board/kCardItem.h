#ifndef KCARDITEM_H
#define KCARDITEM_H

#include "kBoardDef.h"

#include <QGraphicsRectItem>
#include <QBrush>
#include <QTimeLine>

class QGraphicsProxyWidget;

class kCardItem : public QObject, public QGraphicsRectItem
{
	Q_OBJECT
	
public:
										kCardItem( const QRectF& rect, const QBrush& brush);
	virtual								~kCardItem();
	virtual QRectF						boundingRect() const;
	virtual void						paint( QPainter* painter, const QStyleOptionGraphicsItem* options, QWidget* widget );
    
//_________________________________________________________________________
//METHOD
public:
	/*!
	* \brief
	* Set the carItem background color.
	* 
	* \param const QColor& Color
	* Color to give.
	* 
	* \see
	* backgroundColor().
	*/
	inline void							setBackgroundColor(const QColor& Color) {_mBrush.setColor(Color);}

	/*!
	 * \brief
	 * Return cardItem background color
	 * 
	 * \returns
	 * cardItem background color
	 * 
	 * \see
	 * setBackgroundColor(const QColor& Color).
	 */
	inline QColor						backgroundColor() const {return _mBrush.color();}
	/*!
	* \brief
	* Set the carItem opacity.
	* 
	* \param qreal opacity
	* Opacity to give.
	* 
	* \see
	* opacity().
	*/
	void								setOpacity( qreal opacity );
	/*!
	* \brief
	* Return cardItem opacity parameter
	* 
	* \returns
	* value of opacity parameter
	* 
	* \see
	* setOpacity( qreal opacity ).
	*/
	qreal								opacity() const;
	/*!
	* \brief
	* Set the carItem pixmap border.
	* 
	* \param int Border
	* Border to give.
	* 
	* \see
	* pixmapBorder().
	*/
	inline void							setPixmapBorder(const int& Border) {_mPixmapBorder = Border;}
	/*!
	* \brief
	* Return cardItem pixmap border
	* 
	* \returns
	* int : pixmap border value
	* 
	* \see
	* setPixmapBorder(const int& Border)
	*/
	inline int							pixmapBorder() const {return _mPixmapBorder;}
	/*!
	* \brief
	* Set the carItem selected.
	* 
	* \see
	* selected().
	*/
	inline void							setSelected(const bool& Selected) {_mIsSelected = Selected;}
	/*!
	* \brief
	* Return cardItem selected state
	* 
	* \returns
	* true : if item is selected
	* 
	* \see
	* setSelected(const bool& Selected) 
	*/
	inline bool							selected() const {return _mIsSelected;}

    void								setPixmap( const QPixmap& pixmap );

	/*!
	 * \brief
	 * Set the view mode 2D ou 3D.
	 * 
	 * \param mode
	 * values possible : ViewMode::VIEW2D, ViewMode::VIEW3D
	 * \see
	 * viewMode()
	 */
	void							setViewMode(const ViewMode::BoardViewMode& mode);
	/*!
	 * \brief
	 * Return the view mode
	 * 
	 * \returns
	 * values possible : ViewMode::VIEW2D, ViewMode::VIEW3D
	 * \see
	 * setViewMode(const ViewMode::BoardViewMode& mode)
	 */
	inline ViewMode::BoardViewMode		viewMode() const {return _mViewMode;}

private slots:
	void								updateValue( qreal value );
	void								finishedRotation(); //slot launch when the card rotation is finished

//_________________________________________________________________________
//MEMBERS
private:
	QBrush								_mBrush; //card brush
	bool								_mCardState; // true if front, false if back
	bool								_mChangePicture; //Flag, change picture when card rotate by 90°
	QTimeLine							_mFlipTimeLine; //Rotation time line
	bool								_mIsSelected; //True if card is selected
    qreal								_mLastVal; //gradient parameter
    qreal								_mOpacity; //opacity parameter
    QPixmap								_mPixmap; //current pixmap
	int									_mPixmapBorder; //space between the picture border and the item border
	QPixmap								_mSourcePixmap; //first pixmap assignmen
	ViewMode::BoardViewMode				_mViewMode;

//EVENT
protected:
	void								keyPressEvent( QKeyEvent* event );
    void								keyReleaseEvent( QKeyEvent* event );
	void								mousePressEvent(QGraphicsSceneMouseEvent *event);

signals:
	void								returnCardItem(kCardItem*); //return cardItem to the view
};

#endif // KCARDITEM_H
