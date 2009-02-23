#ifndef KGUI_H
#define KGUI_H

#include <QGraphicsView>
#include <QMap>

class kGuiScene;
class kGuiScenePanel;
class kChatItem;

class kGui : public QGraphicsView
{
	Q_OBJECT
	
public:
	enum Widget
	{
		Single,
		Team,
		Properties,
		About,
		Chat
	};
	
	kGui( QWidget* parent = 0 );
	virtual ~kGui();
	
	virtual QSize sizeHint() const;
	
	kGuiScene* scene() const;

protected:
	QMap<Widget, QWidget*> mWidgets;
	kGuiScene* mScene;
	kGuiScenePanel* mPanel;
	kChatItem* mChatItem;
	
	void resizeEvent( QResizeEvent* event );

protected slots:
	void itemRejected( QWidget* widget );
	void itemAccepted( QWidget* widget );
};

#endif // KGUI_H
