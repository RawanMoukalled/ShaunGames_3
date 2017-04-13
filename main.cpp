#include <QApplication>
#include "gui/mainwidget.h"

/**
* \mainpage EECE 435L Games Project
* \author Rita Aoun
* \author Rawan Moukalled
* \date 13-04-2017
*
* Runs the application.
*/
int main(int argc, char **argv) {
    QApplication app(argc, argv);

    MainWidget *mainWidget = new MainWidget;
    mainWidget->show();

    return app.exec();
}

