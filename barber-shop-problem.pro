TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -pthread

# Even better we can enable this when we cleanup all warnings
# QMAKE_CXXFLAGS +=  -Wall

SOURCES += \
        main.cpp \
    barber.cpp \
    customer.cpp \
    shop.cpp \
    semaphore.cpp

HEADERS += \
    barber.h \
    customer.h \
    shop.h \
    semaphore.h
