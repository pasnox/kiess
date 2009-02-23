#include "kChatWidget.h"

#include <QMessageBox>

kChatWidget::kChatWidget()
	: QFrame( 0 ),
	mClient( 0 )
{
	setupUi( this );
}

kChatWidget::~kChatWidget()
{
}

kClient* kChatWidget::client() const
{
	return mClient;
}

void kChatWidget::setClient( kClient* client )
{
	if ( mClient != client )
	{
		qWarning() << "client setted";
	}
}
