QT += core gui opengl

SOURCES += \
    main.cpp \
    scenewindow.cpp \
    sceneglwidget.cpp

HEADERS += \
    scenewindow.h \
    sceneglwidget.h

FORMS += \
    scenewindow.ui

LIBS += -lglut
