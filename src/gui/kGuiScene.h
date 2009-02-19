#ifndef KGUISCENE_H
#define KGUISCENE_H

#include <QGraphicsScene>

class kGui;

class kGuiScene : public QGraphicsScene
{
	Q_OBJECT
	
public:
	kGuiScene( kGui* gui );
	virtual ~kGuiScene();

protected:
	kGui* mGui;
};

#endif // KGUISCENE_H
