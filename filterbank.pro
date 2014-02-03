QT += widgets

INCLUDEPATH += /opt/local/include/

LIBS += -L/opt/local/lib/ \
     -lopencv_core \
     -lopencv_imgproc \
     -lopencv_features2d \
     -lopencv_highgui \
     -lopencv_photo \
     -lopencv_gpu \

HEADERS       = filterbank.h DCT2D.h DCT2D16x16.h DCTdenoising.h mt19937ar.h
SOURCES       = filterbank.cpp \
                main.cpp \
                DCT2D.cpp DCT2D16x16.cpp DCTdenoising.cpp mt19937ar.c 

# install
target.path = ./filterbank
INSTALLS += target

