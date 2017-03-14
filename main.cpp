#include <QApplication>
#include <QGraphicsView>
#include <QFile>
#include <QString>
#include <QLatin1String>

#include "gui/mainwidget.h"
#include "gui/gameselection.h"
#include "myaccount.h"
#include "gui/gamemainmenu.h"
#include "game1/game1.h"

/**
* \mainpage EECE 435L Games Project
* \author Rita Aoun
* \author Rawan Moukalled
* \date 28-2-2017
*
* Runs the application.
*/
int main(int argc, char **argv) {
    QApplication app(argc, argv);

    //MainWidget *mainWidget = new MainWidget;
    //mainWidget->show();

    Game1 *g = new Game1(24);
    g->show();

    return app.exec();
}

