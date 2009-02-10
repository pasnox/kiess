#include "network/kiessxmpp.h"
#include <qapplication.h>

int main(int argc, char ** argv) {
	QApplication qa(argc, argv);

	KiessXmpp xmpp;
	xmpp.process();

	return qa.exec();
}
