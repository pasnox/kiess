#include <QApplication>

#include "CardSet.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
	CardSet cl("test.xml");
	cl.print();
    return app.exec();
}
