QT += widgets

INCLUDEPATH += /usr/local/include/

LIBS += -L/usr/local/lib/ \
     -lopencv_core \
     -lopencv_imgproc \
     -lopencv_features2d \
     -lopencv_highgui \
     -lopencv_photo \
     -lopencv_gpu \
     -lpng

HEADERS       = filterbank.h \ 
                DCT2D.h DCT2D16x16.h DCTdenoising.h mt19937ar.h io_png.h \
                NlBayes.h LibMatrix.h LibImages.h Utilities.h io_png2.h
SOURCES       = filterbank.cpp \
                main.cpp \
                DCT2D.cpp DCT2D16x16.cpp DCTdenoising.cpp mt19937ar.c io_png.c \
                NlBayes.cpp LibMatrix.cpp LibImages.cpp Utilities.cpp io_png2.c

# install
target.path = ./filterbank
INSTALLS += target

