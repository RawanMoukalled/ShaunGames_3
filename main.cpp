#include <QApplication>
#include "gui/mainwidget.h"

#include "game3/game3options.h"
#include "game2/game2options.h"

/**
* \mainpage EECE 435L Games Project
* \author Rita Aoun
* \author Rawan Moukalled
* \date 16-3-2017
*
* Runs the application.
*/
int main(int argc, char **argv) {
    QApplication app(argc, argv);

    //MainWidget *mainWidget = new MainWidget;
    //mainWidget->show();

    Game3Options *o = new Game3Options;
    o->show();

    return app.exec();
}

