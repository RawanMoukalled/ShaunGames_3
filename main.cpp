#include <QApplication>
#include <QGraphicsView>
#include <QFile>
#include <QString>
#include <QLatin1String>

#include "mainwidget.h"
#include "gameselection.h"
#include "myaccount.h"
#include "gamemainmenu.h"
#include "game1.h"

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

    MainWidget *mainWidget = new MainWidget;
    mainWidget->show();

    return app.exec();
}

