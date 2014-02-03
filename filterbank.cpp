
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

void FilterBank::showImage2(const IplImage *image)
{
    // Inorder to display the img in QT, converting back to QImage.
    QImage qimg = IplImageToQImage(image);

    // Showing the img via QLabel
    imageLabel2->setPixmap(QPixmap::fromImage(qimg));

    imageLabel2->adjustSize();
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

    imageLabel2 = new QLabel;
    imageLabel2->setBackgroundRole(QPalette::Base);
    imageLabel2->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel2->setScaledContents(true);

    scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);

    scrollArea2= new QScrollArea;
    scrollArea2->setBackgroundRole(QPalette::Dark);
    scrollArea2->setWidget(imageLabel2);

    // Do the layout
    QWidget *centralWidget = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout(centralWidget);
    layout->addWidget(scrollArea);
    layout->addWidget(scrollArea2);

    setCentralWidget(centralWidget);

    createActions();
    createMenus();

    setWindowTitle(tr("Filter Bank"));
    resize(635, 330);
}

void FilterBank::open()
{
    // It opens a dialog box, where we can select a file.
    fileName = QFileDialog::getOpenFileName(this,
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
    showImage2(img2);
}

void FilterBank::gaussian()
{
    cvSmooth(img, img2, CV_GAUSSIAN, 11, 11);

    showImage2(img2);
}

void FilterBank::median()
{
    cvSmooth(img, img2, CV_MEDIAN, 11, 11);
    
    showImage2(img2);
}

void FilterBank::bilateral()
{ 
    try {
        cvSmooth(img, img2, CV_BILATERAL, 21, 21, 150.0f, 150.0f);
    }
    catch (cv::Exception e)
    {
        std::cout << e.what();
    }
 
    showImage2(img2);
}

void FilterBank::cannyEdge()
{
    IplImage* img3 = cvCreateImage(cvSize(img->width, img->height), img->depth, 1);
    cvCvtColor(img, img3, CV_RGB2GRAY);
    cvCanny( img3, img3, 10, 100, 3 );
    cvCvtColor(img3, img2, CV_GRAY2RGB);

    showImage2(img2);

    cvReleaseImage(&img3);
}

void FilterBank::nonLocalMeans()
{
    cv::Mat mat = cv::Mat(img, false);
    cv::fastNlMeansDenoisingColored(mat, mat,5, 5, 7, 21);
    *img2 = mat;

    showImage2(img2);
}

void FilterBank::dctDenoising()
{
    // DCT Image Denoising
    // http://www.ipol.im/pub/art/2011/ys-dct/

    float * iarr1;
    size_t w1, h1, c1;
    if (NULL == (iarr1 = io_png_read_f32(fileName.toStdString().c_str(), &w1, &h1, &c1))) {
        std::cerr << "Unable to load image file " << "input.png" << std::endl;
        return;
    }
    std::vector<float> npixels(iarr1, iarr1 + w1 * h1 * c1);
    free(iarr1);

    float sigma = 15;

    int flag_dct16x16 = 1;

    std::vector<float> opixels;
    opixels.resize(w1*h1*c1);

    DCTdenoising(npixels, opixels, w1, h1, c1, sigma, flag_dct16x16);

    // Converting png ordering to IplImage ordering
    for (size_t i = 0; i < w1; i++)
        for (size_t j = 0; j < h1; j++)
            for(size_t k = 0; k < c1; k++)
            {
                float pixel = opixels[(2-k)*w1*h1 + (j*w1 + i)];
                pixel = pixel > 255 ? 255 : pixel;
                pixel = pixel < 0 ? 0 : pixel;
                img2->imageData[ (j*w1 + i)*c1 + k] = (unsigned char) pixel;
            }

    showImage2(img2);

    /*
    float *out = new float[w1*h1*c1];
    // Save output denoised image
    for (size_t i = 0; i < w1*h1*c1; i++)
        out[i] = opixels[i];
    io_png_write_f32("output.png", out, w1, h1, c1);
    */
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

    dctDenoisingAct = new QAction(tr("&DCT denoising"), this);
    dctDenoisingAct->setShortcut(tr("Ctrl+D1"));
    connect(dctDenoisingAct, SIGNAL(triggered()), this, SLOT(dctDenoising()));

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
    filterMenu->addAction(dctDenoisingAct);
    filterMenu->addAction(denoising2Act);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(filterMenu);
}

void FilterBank::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value()
                            + ((factor - 1) * scrollBar->pageStep()/2)));
}
