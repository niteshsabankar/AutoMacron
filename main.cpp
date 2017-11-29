#include "automacronui.h"
#include <QApplication>
#include <windows.h>
#include <direct.h>

int main(int argc, char *argv[])
{
    _mkdir("/Macros");
    QApplication a(argc, argv);
    AutoMacronUI w;
    w.show();

    return a.exec();
}
