#ifndef KPANEL_H
#define KPANEL_H

#include <QGraphicsView>
#include <QTimeLine>
#include <QMap>

class kPanelItem;

class kPanel : public QGraphicsView
{
	Q_OBJECT
	
public:
	kPanel( QWidget* parent = 0 );
	virtual ~kPanel();
	
	virtual QSize sizeHint() const;

protected:
    void keyPressEvent( QKeyEvent* event );
    void resizeEvent( QResizeEvent* event );

private:
    QGraphicsScene* mScene;
	kPanelItem* mContainerItem;
	kPanelItem* mBackItem;
	kPanelItem* mSelectionItem;
	QSize mGridSize;
	QMap<int, QMap<int, kPanelItem*> > mItems;
	
    
    QGraphicsWidget *splash;
    QTimeLine *selectionTimeLine;
    QTimeLine *flipTimeLine;
    int selectedX, selectedY;
    
    QPointF startPos;
    QPointF endPos;
    qreal xrot, yrot;
    qreal xrot2, yrot2;

    bool flipped;
    bool flipLeft;
	
	QPointF posForLocation( int x, int y ) const;
	void setCurrentItem( int x, int y, bool animate );

private slots:
    void updateSelectionStep(qreal val);
    void updateFlipStep(qreal val);
    void flip();
};

#endif // KPANEL_H
