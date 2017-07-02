TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp \
    insinput.cpp \
    cpu.cpp \
    instruction.cpp \
    insfetch.cpp \
    insdecode.cpp \
    memaccess.cpp \
    writeback.cpp \
    execute.cpp \
    mips.cpp \
    stage.cpp \
    msg.cpp \
    debug.cpp \
    error.cpp

HEADERS += \
    mips.h \
    insinput.h \
    cpu.h \
    instruction.h \
    insfetch.h \
    insdecode.h \
    memaccess.h \
    writeback.h \
    execute.h \
    stage.h \
    msg.h \
    debug.h \
    error.h
