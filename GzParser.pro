TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    GzParser.cpp 

HEADERS += GzParser.h 


INCLUDEPATH += zlib/include



LIBS += -L"$$PWD/zlib/lib" -lz




QMAKE_CXXFLAGS += -std=c++11