
#ifndef FILTERBANK_H
#define FILTERBANK_H

#include <QMainWindow>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include <opencv2/gpu/gpu.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/photo/photo.hpp>
#include <vector>

#include "DCTdenoising.h"
#include "io_png.h"

#include "LibMatrix.h"
#include "NlBayes.h"

QT_BEGIN_NAMESPACE
class QAction;
class QLabel;
class QMenu;
class QScrollArea;
class QScrollBar;
QT_END_NAMESPACE

QImage IplImageToQImage(const IplImage *img);

class FilterBank : public QMainWindow
{
    Q_OBJECT

public:
    FilterBank();

private slots:
    void open();

    void box();
    void gaussian();
    void median();
    void bilateral();
    void cannyEdge();
    void nonLocalMeans();
    void dctDenoising();
    void nlBayesDenoising();


private:

    IplImage* img;
    IplImage* img2;

    void showImage(const IplImage *image);
    void showImage2(const IplImage *image);

    void createActions();
    void createMenus();
    void adjustScrollBar(QScrollBar *scrollBar, double factor);

    QString fileName;

    QLabel *imageLabel;
    QLabel *imageLabel2; // To diaplay output image

    QScrollArea *scrollArea;
    QScrollArea *scrollArea2;

    QAction *openAct;
    QAction *exitAct;

    QAction *boxAct;
    QAction *gaussianAct;
    QAction *medianAct;
    QAction *bilateralAct;
    QAction *cannyEdgeAct;
    QAction *nonLocalMeansAct;
    QAction *dctDenoisingAct;
    QAction *nlBayesDenoisingAct;

    QMenu *fileMenu;
    QMenu *filterMenu;
};

#endif
