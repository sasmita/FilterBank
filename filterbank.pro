QT += widgets

INCLUDEPATH += /opt/local/include/

LIBS += -L/opt/local/lib/ \
     -lopencv_core \
     -lopencv_imgproc \
     -lopencv_features2d \
     -lopencv_highgui

HEADERS       = filterbank.h
SOURCES       = filterbank.cpp \
                main.cpp

# install
target.path = ./filterbank
INSTALLS += target

