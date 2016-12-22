QT += network widgets

HEADERS       = blockingclient.h \
                fortunethread.h \
                 dataget.h \
    datastruct.h
SOURCES       = blockingclient.cpp \
                main.cpp \
                fortunethread.cpp \
                dataget.cpp \
    datastruct.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/network/blockingfortuneclient
INSTALLS += target

