#ifndef SORTINGCLASSES_H
#define SORTINGCLASSES_H
#include <QList>

class Sort
{
public:
    Sort();
    Sort(int n);
    virtual ~Sort();
    virtual void nextStep(int n)=0;
    int *values;
    int getSize();
    enum Operation{Comparision, Swap, Set};
    struct Step
    {
        int a;
        int b;
        Operation operation;
        Step(int val1, int val2, Operation op);
        Step();
    };
    QList<Step> list;

protected:
    int size;
};

class SelectionSort : public Sort
{
public:
    SelectionSort(int n);
    void nextStep(int n);

private:
    int i;
};

class InsertionSort : public Sort
{
public:
    InsertionSort(int n);
    void nextStep(int n);

private:
    int i;
};

class BubbleSort : public Sort
{
public:
    BubbleSort(int n);
    void nextStep(int n);

private:
    int i;
};

class HeapSort : public Sort
{
public:
    HeapSort(int n);
    void nextStep(int n);

private:
    void heapify(int index);
    void buildHeap();
    int heapSize;
    bool ukopcowawszy;
};

class MergeSort : public Sort
{
public:
    MergeSort(int n);
    void nextStep(int n);

private:
    struct mergeNode
    {
        int l;
        int q;
        int r;
        bool leftDone;
        bool rightDone;
        mergeNode(int a, int b);
    };

    QList<mergeNode> stack;
    void run(int &n);
    void merge(int l, int q, int r);
};

class QuickSort : public Sort
{
public:
    QuickSort(int n);
    void nextStep(int n);

private:
    struct QSNode
    {
        int l;
        int r;
        QSNode(int a, int b);
    };

    QList<QSNode> stack;
    void run(int n);
    int partition(int l, int p);
};

class BogoSort : public Sort
{
public:
    BogoSort(int n);
    void nextStep(int n);

private:
    void randomize();
    bool sorted;
};









#endif // SORTINGCLASSES_H
