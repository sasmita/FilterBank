
#include <QtWidgets>

#include "filterbank.h"

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
    resize(500, 500);
}
void FilterBank::open()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                    tr("Open File"), QDir::currentPath());
    if (!fileName.isEmpty()) {
        QImage image(fileName);
        if (image.isNull()) {
            QMessageBox::information(this, tr("Filter Bank"),
                                     tr("Cannot load %1.").arg(fileName));
            return;
        }

        img = cvLoadImage("test.jpg", 1);

        imageLabel->setPixmap(QPixmap::fromImage(image));
    }
}

void FilterBank::box()
{
}

void FilterBank::gaussian()
{
}

void FilterBank::median()
{
}

void FilterBank::bilateral()
{
}

void FilterBank::cannyEdge()
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

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(filterMenu);
}

void FilterBank::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value()
                            + ((factor - 1) * scrollBar->pageStep()/2)));
}
