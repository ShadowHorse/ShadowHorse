QT += core network gui widgets

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

HEADERS += \
    server.h \
    serverthread.h

SOURCES += \
    server.cpp \
    serverthread.cpp \
    main.cpp

include($$PWD/gui/gui.pri)

# Copy required DLLs to output directory
CONFIG(debug, debug|release) {
    DESTDIR = build/debug
} else {
    DESTDIR = build/release
}
