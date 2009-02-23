#ifndef KGUISCENEPANELITEM_H
#define KGUISCENEPANELITEM_H

#include <QGraphicsRectItem>
#include <QBrush>
#include <QTimeLine>

class kEmbeddedWidget;
class kGuiScenePanel;
class QGraphicsProxyWidget;

class kGuiScenePanelItem : public QObject, public QGraphicsRectItem
{
	Q_OBJECT
	
public:
	kGuiScenePanelItem( const QRectF& rect, const QBrush& brush, kEmbeddedWidget* embeddedWidget = 0 );
	virtual ~kGuiScenePanelItem();
	
	virtual void paint( QPainter* painter, const QStyleOptionGraphicsItem* options, QWidget* widget );
	virtual QRectF boundingRect() const;

	void setPixmap( const QPixmap& pixmap );
	
	void setWidget( kEmbeddedWidget* widget );
	kEmbeddedWidget* widget() const;
	
	void loadWidget( kEmbeddedWidget* widget );
	QWidget* currentWidget() const;
	void unloadWidget();
	
	kGuiScenePanel* panel() const;
	bool isAnimate() const;
	
	void activate();

protected:
	QBrush mBrush;
	QPixmap mPixmap;
	QTimeLine mAnimationTimeLine;
	qreal mLastVal;
	kEmbeddedWidget* mEmbeddedWidget;
	QGraphicsProxyWidget* mProxyWidget;

private slots:
	void animationTimeLineChanged( qreal value );

signals:
	void activated();
};

#endif // KGUISCENEPANELITEM_H
