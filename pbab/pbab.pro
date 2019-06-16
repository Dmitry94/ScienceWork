QT -= gui core

TARGET = pbab
DEFINES += PBAB_LIB
requires(false) # disable building because header-only library

CONFIG += c++17
HEADERS += \
    pbab_solnode.hpp \
    pbab_solgenerator.h \
    pbab_solver.h \
    pbab_solanalyzer.h
