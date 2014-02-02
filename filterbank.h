
#ifndef FILTERBANK_H
#define FILTERBANK_H

#include <QMainWindow>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include <opencv2/gpu/gpu.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/photo/photo.hpp>


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


private:

    IplImage* img;
    IplImage* img2;

    void showImage(const IplImage *img);

    void createActions();
    void createMenus();
    void adjustScrollBar(QScrollBar *scrollBar, double factor);

    QLabel *imageLabel;
    QScrollArea *scrollArea;

    QAction *openAct;
    QAction *exitAct;

    QAction *boxAct;
    QAction *gaussianAct;
    QAction *medianAct;
    QAction *bilateralAct;
    QAction *cannyEdgeAct;

    QMenu *fileMenu;
    QMenu *filterMenu;
};

#endif
