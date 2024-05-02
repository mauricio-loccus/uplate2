QT += quick
QT += serialport
QT += svg
RC_ICONS = Elisa.ico
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
SOURCES += \
        calculobranco.cpp \
        calculocq.cpp \
        calculocutoff.cpp \
        configfiltros.cpp \
        configpath.cpp \
        dadosbrutos.cpp \
        exportararquivos.cpp \
        importararquivos.cpp \
        layoutpocos.cpp \
        main.cpp \
        protocoloserial.cpp \
        salvarprotocolo.cpp
RESOURCES += qml.qrc
# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = 

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH = 

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    calculobranco.h \
    calculocq.h \
    calculocutoff.h \
    configfiltros.h \
    configpath.h \
    dadosbrutos.h \
    exportararquivos.h \
    importararquivos.h \
    layoutpocos.h \
    protocoloserial.h \
    salvarprotocolo.h


# QXlsx code for Application Qt project
QXLSX_PARENTPATH=./         # current QXlsx path is . (. means curret directory)
QXLSX_HEADERPATH=./header/  # current QXlsx header path is ./header/
QXLSX_SOURCEPATH=./source/  # current QXlsx source path is ./source/
include(./QXlsx.pri)

DISTFILES += \
    Elisa.ico
