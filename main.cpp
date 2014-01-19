
#include <QApplication>

#include "filterbank.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    FilterBank filterBank;
    filterBank.show();
    return app.exec();
}
