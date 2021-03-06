SOURCES += \
    main.cpp \
    helper.cpp \
    game2/game2.cpp \
    game1/game1options.cpp \
    game1/game1.cpp \
    game3/game3.cpp \
    gui/mainwidget.cpp \
    gui/gameselection.cpp \
    gui/gamemainmenu.cpp \
    game1/cannon.cpp \
    game1/game1scene.cpp \
    game1/sheep1.cpp \
    game1/barn.cpp \
    game2/game2options.cpp \
    game3/game3options.cpp \
    game2/game2scene.cpp \
    game3/game3scene.cpp \
    game3/dot.cpp \
    game2/tile.cpp \
    game2/sheep2.cpp \
    game3/horizontalline.cpp \
    game3/verticalline.cpp \
    game3/box.cpp \
    game3/line.cpp \
    gameover.cpp \
    account/myaccount.cpp \
    account/qcustomplot.cpp

HEADERS += \
    helper.h \
    game2/game2.h \
    game1/game1options.h \
    game1/game1.h \
    game3/game3.h \
    gui/mainwidget.h \
    gui/gameselection.h \
    gui/gamemainmenu.h \
    game1/cannon.h \
    game1/game1scene.h \
    game1/sheep1.h \
    game1/barn.h \
    game2/game2options.h \
    game3/game3options.h \
    game2/game2scene.h \
    difficulty.h \
    game3/size.h \
    game3/game3scene.h \
    game3/dot.h \
    game2/tile.h \
    game2/sheep2.h \
    game3/horizontalline.h \
    game3/verticalline.h \
    game3/box.h \
    game3/line.h \
    gameover.h \
    account/myaccount.h \
    account/qcustomplot.h

OTHER_FILES +=

QT += sql

DESTDIR=bin #Target file directory
OBJECTS_DIR=bin #Intermediate object files directory
MOC_DIR=bin #Intermediate moc files directory
