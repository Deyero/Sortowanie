#include "sortwidget.h"
#include "SortingClasses.h"
#include <QPainter>
#include <QList>

const QString SortWidget::strAlgorithm[A] = {
    "SelectionSort",
    "InsertionSort",
    "BubbleSort",
    "HeapSort",
    "MergeSort",
    "QuickSort",
    "BogoSort",
    "Nic"};

SortWidget::SortWidget(QWidget *parent) :
    QWidget(parent)
{
    sort = NULL;
    algorithm = None;
    currentStep = Sort::Step(-1, -1, Sort::Comparision);
}

int SortWidget::getAlgorithm()
{
    return static_cast<int>(algorithm);
}

void SortWidget::start(Algorithm a, int n, int delay)
{
    if (sort == NULL || a != algorithm)
    {
        algorithm = a;
        if (sort != NULL)
        {
            delete sort;
            delete []values;
        }
        switch (algorithm)
        {
        case Selection:
            sort = new SelectionSort(n);
            break;

        case Insertion:
            sort = new InsertionSort(n);
            break;

        case Bubble:
            sort = new BubbleSort(n);
            break;

        case Heap:
            sort = new HeapSort(n);
            break;

        case Merge:
            sort = new MergeSort(n);
            break;

        case Quick:
            sort = new QuickSort(n);
            break;

        case Bogo:
            sort = new BogoSort(n);
            break;

        default:
            sort = NULL;
            algorithm = None;
            timer.stop();
            break;
        }
        if (algorithm != None)
        {
            accesses = 0;
            comparisions = 0;
            emit labelInfoStarted(strAlgorithm[static_cast<int>(algorithm)]);

            currentStep = Sort::Step(-1, -1, Sort::Comparision);
            timer.start(delay, this);
            values = new int[n];
            if (algorithm == Heap)
            {
                for (int i = 0; i < n; i++)
                    values[i] = sort->values[i+1];
            }
            else
            {
                for (int i = 0; i < n; i++)
                    values[i] = sort->values[i];
            }
        }
    }
    else
    {
        timer.start(delay, this);
    }
}

void SortWidget::pause()
{
    timer.stop();
}

void SortWidget::stop()
{
    if (sort != NULL)
    {
        delete sort;
        delete []values;
    }
    sort = NULL;
    algorithm = None;
    timer.stop();
}

void SortWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.save();
    if (sort != NULL)
    {
        painter.setPen(Qt::NoPen);
        painter.setBrush(Qt::blue);
        //painter.setRenderHint(QPainter::Antialiasing);
        double scale = height() / (double)(sort->getSize());
        double step = width() / (double)(sort->getSize());
        double spacer = 1;
        if (width() < sort->getSize() * 2)
            spacer = 0;
        painter.translate(0, height() - 1);
        painter.scale(1, scale);
        for (int i = 0; i < sort->getSize(); i++)
        {
            if (i == currentStep.a || (i == currentStep.b && currentStep.operation != Sort::Set))
                painter.setBrush(Qt::red);
            painter.drawRect(QRectF(0, 0, step - spacer, -values[i]));
            painter.translate(step, 0);
            painter.setBrush(Qt::blue);
        }
    }
    else
    {
        painter.fillRect(0, 0, width(), height(), Qt::white);
    }
    painter.restore();
    painter.setPen(palette().dark().color());
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(0, 0, width() - 1, height() - 1);
}

void SortWidget::timerEvent(QTimerEvent *)
{
    //pierwszy krok domyślnie (-1, -1, Comp)
    if (sort->list.isEmpty())
        sort->nextStep(N);
    if (!sort->list.isEmpty())
    {
        if (currentStep.operation == Sort::Swap)
        {
            int tmp = values[currentStep.a];
            values[currentStep.a] = values[currentStep.b];
            values[currentStep.b] = tmp;
            accesses++;
            currentStep.operation = Sort::Comparision;
        }
        else
        {
            if (currentStep.operation == Sort::Set)
            {
                values[currentStep.a] = currentStep.b;
                accesses++;
            }
            else
            {
                accesses += 2;
                comparisions++;
            }
            currentStep = sort->list.front();
            sort->list.pop_front();
        }
    }
    else
    {
        timer.stop();
        if (currentStep.operation == Sort::Set)
            values[currentStep.a] = currentStep.b;
        currentStep = Sort::Step(-1, -1, Sort::Comparision);
    }

    emit labelInfoTick(QString::number(comparisions), QString::number(accesses));

    update();
}
