QT += widgets

INCLUDEPATH += /usr/local/include/

LIBS += DCTdenoising.o DCT2D.o DCT2D16x16.o mt19937ar.o -lm \
     -L/usr/local/lib/ \
     -lopencv_core \
     -lopencv_imgproc \
     -lopencv_features2d \
     -lopencv_highgui \
     -lopencv_photo \
     -lopencv_gpu \

HEADERS       = filterbank.h
SOURCES       = filterbank.cpp \
                main.cpp

# install
target.path = ./filterbank
INSTALLS += target

