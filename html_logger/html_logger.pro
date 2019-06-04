QT -= core gui

TARGET = html_logger
DEFINES += HTML_LOGGER_LIB
TEMPLATE = lib

CONFIG += staticlib
CONFIG += c++11
CONFIG += optimization

SOURCES += \
    html_tag.cpp \
    html_table.cpp \
    html_body.cpp \
    html_head.cpp \
    html_doc.cpp \
    #html_logger.cpp

HEADERS +=  \
    html_tag.h \
    html_table.h \
    html_body.h \
    html_head.h \
    html_doc.h \
    #html_logger.h

optimization {
    QMAKE_CFLAGS_RELEASE += -O2
    QMAKE_CFLAGS_DEBUG += -g
}
