
#include <QApplication>

#include "filterbank.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    FilterBank fb;
    fb.show();
    return app.exec();
}
