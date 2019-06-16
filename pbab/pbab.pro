QT -= gui core

TARGET = pbab
DEFINES += PBAB_LIB
requires(false) # disable building because header-only library

CONFIG += c++17
HEADERS += \
    pbab_solnode.hpp \
    pbab_solgenerator.hpp \
    pbab_solanalyzer.hpp \
    pbab_solver.hpp \
    pbab_parsolver.hpp \
    pbab_babsolver.hpp
