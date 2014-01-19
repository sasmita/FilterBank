
#ifndef FILTERBANK_H
#define FILTERBANK_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QAction;
class QLabel;
class QMenu;
class QScrollArea;
class QScrollBar;
QT_END_NAMESPACE

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
