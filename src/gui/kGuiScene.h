#ifndef KGUISCENE_H
#define KGUISCENE_H

#include <QGraphicsScene>

class kGui;
class kGuiScenePanel;

class kGuiScene : public QGraphicsScene
{
	Q_OBJECT
	friend class kGui;
	
public:
	kGuiScene( kGui* gui );
	virtual ~kGuiScene();

protected:
	kGui* mGui;
	kGuiScenePanel* mPanel;
	
	void initialize( const QSize& gridSize );
};

#endif // KGUISCENE_H
