#-------------------------------------------------
#
# Project created by QtCreator 2017-01-19T17:03:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ARM
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    lamb.cpp \
    AND.cpp \
    ADD.cpp \
    SUB.cpp \
    start_cpu.cpp \
    ORR.cpp \
    MYTHREAD.cpp \
    MUL.cpp \
    MOV.cpp \
    LOAD.cpp \
    LDR_STR.cpp \
    CMP.cpp \
    BIC.cpp \
    B.cpp \
    mytest.cpp \
    timerclock.cpp \
    LDM_STM.cpp \
    MSR_RS.cpp \
    armintcontrol.cpp \
    TST.cpp \
    MVN.cpp \
    beep.cpp \
    beepthread.cpp \
    about.cpp \
    description.cpp \
    configpc.cpp \
    lcdnumber.cpp \
    configio.cpp \
    lcd.cpp \
    member.cpp

HEADERS  += mainwindow.h \
    lamb.h \
    start_cpu.h \
    mythread.h \
    FUNCMD.h \
    data.h \
    C_SPSR.h \
    mytest.h \
    s3c2410.h \
    timerclock.h \
    armintcontrol.h \
    beep.h \
    beepthread.h \
    about.h \
    description.h \
    configpc.h \
    lcdnumber.h \
    configio.h \
    lcd.h \
    member.h
FORMS    += mainwindow.ui \
    about.ui \
    description.ui \
    configpc.ui \
    configio.ui \
    lcd.ui \
    member.ui

RESOURCES += \
    resource.qrc
RC_FILE+=myico.rc

OTHER_FILES += \
    myico.rc \
    myico.ico \
    icon.png
