TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

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
