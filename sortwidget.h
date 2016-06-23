#ifndef SORTWIDGET_H
#define SORTWIDGET_H

#include <QWidget>
#include <QBasicTimer>
#include "SortingClasses.h"

class SortWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SortWidget(QWidget *parent = 0);
    enum Algorithm  {Selection, Insertion, Bubble, Heap, Merge, Quick, Bogo, None};
    //kolejnosc odpowiada stricte tej z comboboxa
    static const int A = 8;
    static const QString strAlgorithm[A];
    void start(Algorithm a, int n, int delay);
    void pause();
    void stop();
    int getAlgorithm();

protected:
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);

private:
    static const int N = 1000000;  //>luzny< limit operacji trzymanych w liscie
    QBasicTimer timer;
    Sort *sort;
    Sort::Step currentStep;
    int * values;
    int accesses;
    int comparisions;
    Algorithm algorithm;

signals:
    void labelInfoStarted(QString alg);
    void labelInfoTick(QString c, QString a);

public slots:

};


#endif // SORTWIDGET_H
