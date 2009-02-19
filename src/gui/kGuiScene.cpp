#include "kGuiScene.h"
#include "kGui.h"

kGuiScene::kGuiScene( kGui* gui )
	: QGraphicsScene( gui )
{
	Q_ASSERT( gui );
	
	mGui = gui;
}

kGuiScene::~kGuiScene()
{
}
