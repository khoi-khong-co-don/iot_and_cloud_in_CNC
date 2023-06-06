QT       += core gui network charts quick 3dcore 3drender 3dinput 3dquick 3dlogic qml quick 3dquickextras 3dextras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
DEFINES +="_HAS_STD_BYTE=0"

SOURCES += \
    customtablemodel.cpp \
    data_process.cpp \
    led.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    orbittransformcontroller.cpp \
    thread_check_connect.cpp \
    thread_connect.cpp \
    thread_connect_post.cpp \
    thread_data_get.cpp \
    thread_data_post.cpp \
    thread_get_product.cpp

HEADERS += \
    customtablemodel.h \
    data_process.h \
    led.h \
    login.h \
    mainwindow.h \
    orbittransformcontroller.h \
    qmaterial.h \
    thread_check_connect.h \
    thread_connect.h \
    thread_connect_post.h \
    thread_data_get.h \
    thread_data_post.h \
    thread_get_product.h

FORMS += \
    data_process.ui \
    login.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    model.qrc \
    qml.qrc

DISTFILES += \
    model.qml

