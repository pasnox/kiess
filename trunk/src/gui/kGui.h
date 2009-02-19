#ifndef KGUI_H
#define KGUI_H

#include <QGraphicsView>

class kGuiScene;

class kGui : public QGraphicsView
{
	Q_OBJECT
	
public:
	kGui( QWidget* parent = 0 );
	virtual ~kGui();
	
	virtual QSize sizeHint() const;
	
	kGuiScene* scene() const;

protected:
	kGuiScene* mScene;
	
	void resizeEvent( QResizeEvent* event );
};

#endif // KGUI_H
