QT += network widgets

HEADERS       = blockingclient.h \
                fortunethread.h \
                 dataget.h \
    datastruct.h \
    defines.h \
    avgline.h
SOURCES       = blockingclient.cpp \
                main.cpp \
                fortunethread.cpp \
                dataget.cpp \
    datastruct.cpp \
    avgline.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/network/blockingfortuneclient
INSTALLS += target

