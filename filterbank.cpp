
#include <QtWidgets>

#include "filterbank.h"

void FilterBank::showImage(const IplImage *image)
{
    // Inorder to display the img in QT, converting back to QImage.
    QImage qimg = IplImageToQImage(image);

    // Showing the img via QLabel
    imageLabel->setPixmap(QPixmap::fromImage(qimg));

    imageLabel->adjustSize();
}

QImage IplImageToQImage(const IplImage *img)
{
    int height = img->height;
    int width = img->width;

    const uchar *qImageBuffer =(const uchar*)img->imageData;
    QImage qimg(qImageBuffer, width, height, QImage::Format_RGB888);
    return qimg.rgbSwapped();
}

FilterBank::FilterBank()
{
    imageLabel = new QLabel;
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);

    scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);
    setCentralWidget(scrollArea);

    createActions();
    createMenus();

    setWindowTitle(tr("Filter Bank"));
    resize(700, 700);
}

void FilterBank::open()
{
    // It opens a dialog box, where we can select a file.
    QString fileName = QFileDialog::getOpenFileName(this,
                                    tr("Open File"), QDir::currentPath());
    if (!fileName.isEmpty()) {

        //Loads the image at a given filename
        img = cvLoadImage(fileName.toStdString().c_str(), /* Converting to c string*/
                          1 /* color image */);

        // Creating memory for img2 of same dimensions of img to store the output image(img2)
        img2 = cvCreateImage(cvSize(img->width, img->height), img->depth, img->nChannels);

        showImage(img);
    }
}

void FilterBank::box()
{
    // applying box filter(11 x 11) Kernel to img and storing in img2
    cvSmooth(img, img2, CV_BLUR, 11, 11);

    // Showing img2 which is the output image
    showImage(img2);
}

void FilterBank::gaussian()
{
    cvSmooth(img, img2, CV_GAUSSIAN, 11, 11);

    showImage(img2);
}

void FilterBank::median()
{
    cvSmooth(img, img2, CV_MEDIAN, 11, 11);
    
    showImage(img2);
}

void FilterBank::bilateral()
{ 
    cvSmooth(img, img2, CV_BILATERAL, 21, 21, 150.0f, 150.0f);
 
    showImage(img2);
}

void FilterBank::cannyEdge()
{
}

void FilterBank::nonLocalMeans()
{
}

void FilterBank::denoising1()
{
}

void FilterBank::denoising2()
{
}

void FilterBank::createActions()
{
    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcut(tr("Ctrl+O"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcut(tr("Ctrl+Q"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    gaussianAct = new QAction(tr("&Gaussian"), this);
    gaussianAct->setShortcut(tr("Ctrl+G"));
    connect(gaussianAct, SIGNAL(triggered()), this, SLOT(gaussian()));

    boxAct = new QAction(tr("&Box"), this);
    boxAct->setShortcut(tr("Ctrl+B"));
    connect(boxAct, SIGNAL(triggered()), this, SLOT(box()));

    medianAct = new QAction(tr("&Median"), this);
    medianAct->setShortcut(tr("Ctrl+M"));
    connect(medianAct, SIGNAL(triggered()), this, SLOT(median()));

    bilateralAct = new QAction(tr("&Bilateral"), this);
    bilateralAct->setShortcut(tr("Ctrl+L"));
    connect(bilateralAct, SIGNAL(triggered()), this, SLOT(bilateral()));

    cannyEdgeAct = new QAction(tr("&Canny Edge"), this);
    cannyEdgeAct->setShortcut(tr("Ctrl+C"));
    connect(cannyEdgeAct, SIGNAL(triggered()), this, SLOT(cannyEdge()));

    nonLocalMeansAct = new QAction(tr("&Non-local means"), this);
    nonLocalMeansAct->setShortcut(tr("Ctrl+N"));
    connect(nonLocalMeansAct, SIGNAL(triggered()), this, SLOT(nonLocalMeans()));

    denoising1Act = new QAction(tr("&De-noising1"), this);
    denoising1Act->setShortcut(tr("Ctrl+D1"));
    connect(denoising1Act, SIGNAL(triggered()), this, SLOT(denoising1()));

    denoising2Act = new QAction(tr("&De-noising2"), this);
    denoising2Act->setShortcut(tr("Ctrl+D2"));
    connect(denoising2Act, SIGNAL(triggered()), this, SLOT(denoising2()));

}


void FilterBank::createMenus()
{
    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    filterMenu = new QMenu(tr("&Filters"), this);
    filterMenu->addAction(boxAct);
    filterMenu->addAction(gaussianAct);
    filterMenu->addAction(medianAct);
    filterMenu->addAction(bilateralAct);
    filterMenu->addAction(cannyEdgeAct);
    filterMenu->addAction(nonLocalMeansAct);
    filterMenu->addAction(denoising1Act);
    filterMenu->addAction(denoising2Act);


    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(filterMenu);
}

void FilterBank::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value()
                            + ((factor - 1) * scrollBar->pageStep()/2)));
}
