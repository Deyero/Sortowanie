#include "SortingClasses.h"
#include <QtGlobal>
#include <QtWidgets>
#include <QList>

Sort::Sort()
{
    //tu nic nie ma
}

Sort::Sort(int n)
{
    values = new int[n];
    for (int k = 0; k < n; k++)
    {
        values[k] = n - k;
    }

    qsrand(QTime::currentTime().second());
    for (int i = n-1; i >= 0; i--)
    {
        int j = qrand() % (i+1);
        int tmp = values[i];
        values[i] = values[j];
        values[j] = tmp;
    }

    size = n;
}

Sort::Step::Step(int val1, int val2, Operation op)
{
    a = val1;
    b = val2;
    operation = op;
}
Sort::Step::Step()
{

}

Sort::~Sort()
{
    delete []values;
}

int Sort::getSize()
{
    return size;
}

SelectionSort::SelectionSort(int n): Sort(n)
{
    i = 0;
}

void SelectionSort::nextStep(int n)
{
    int k = 0;
    while (i < size && k < n)
    {
        int min = i;
        int j = i + 1;
        while (j < size)
        {
            list.append(Step(min, j, Sort::Comparision));
            if (values[j] < values[min])
                min = j;
            j++;
            k++;
        }
        int tmp = values[i];
        values[i] = values[min];
        values[min] = tmp;
        list.append(Step(i, min, Sort::Swap));
        i++;
    }
}

InsertionSort::InsertionSort(int n): Sort(n)
{
    i = 0;
}

void InsertionSort::nextStep(int n)
{
    int k = 0;
    while (i < size && k < n)
    {
        int j = i - 1;
        int tmp = values[i];
        while (j >= 0 && values[j] > tmp)
        {
            list.append(Step(j, j+1, Sort::Swap));
            //list.append(Step(j+1, values[j], Sort::Set));
            values[j+1] = values[j];
            j--;
            k++;
        }
        values[j+1] = tmp;
        list.append(Step(j+1, tmp, Sort::Set));
        i++;
    }
}

BubbleSort::BubbleSort(int n): Sort(n)
{
    i = size - 1;
}

void BubbleSort::nextStep(int n)
{
    int k = 0;
    while (i >= 1 && k < n)
    {
        for (int j = 1; j <= i; j++)
        {
            list.append(Step(j-1, j, Sort::Comparision));
            if (values[j-1] > values[j])
            {
                int tmp = values[j-1];
                values[j-1] = values[j];
                values[j] = tmp;
                list.append(Step(j-1, j, Sort::Swap));
            }
        }
        i--;
        k++;
    }
}

HeapSort::HeapSort(int n)
{
    values = new int[n + 1];
    for (int k = 1; k <= n; k++)
    {
        values[k] = n - k + 1;
    }

    qsrand(QTime::currentTime().second());
    for (int i = n; i > 0; i--)
    {
        int j = qrand() % i + 1;
        int tmp = values[i];
        values[i] = values[j];
        values[j] = tmp;
    }

    size = n + 1;
    heapSize = size - 1;
    ukopcowawszy = false;
}

void HeapSort::heapify(int index)
{
    int largest = index;
    int l = 2 * index;
    int r = l + 1;

    if (l <= heapSize)
    {
        list.append(Step(index - 1, l - 1, Sort::Comparision));
        if (values[l] > values[largest])
        {
            largest = l;
        }
    }

    if (r <= heapSize)
    {
        list.append(Step(largest - 1, r - 1, Sort::Comparision));
        if (values[r] > values[largest])
        {
            largest = r;
        }
    }

    if (largest != index)
    {
        int tmp = values[index];
        values[index] = values[largest];
        values[largest] = tmp;
        list.append(Step(index - 1, largest - 1, Sort::Swap));
        heapify(largest);
    }
}

void HeapSort::buildHeap()
{
    ukopcowawszy = true;

    for (int i = heapSize / 2; i > 0; i--)
    {
        heapify(i);
    }
}

void HeapSort::nextStep(int n)
{
    if (ukopcowawszy)
        while (heapSize > 0 && n > 0)
        {
            //swap
            int tmp = values[1];
            values[1] = values[heapSize];
            values[heapSize] = tmp;
            list.append(Step(0, heapSize - 1, Sort::Swap));
            heapSize--;
            heapify(1);
            n -= 4;
        }
    else
        buildHeap();
}

MergeSort::MergeSort(int n): Sort(n)
{
    stack.append(mergeNode(0, n-1));

}

MergeSort::mergeNode::mergeNode(int a, int b)
{
    l = a;
    r = b;
    leftDone = false;
    rightDone = false;
}

void MergeSort::run(int &n)
{
    while(!stack.empty() && n > 0)
    {
        mergeNode *v = &stack.back();
        if (!v->leftDone)
        {
            v->q = (v->r + v->l) / 2;
            if (v->q > v->l)
                stack.append(mergeNode(v->l, v->q));
            v->leftDone = true;
        }
        else if (!v->rightDone)
        {
            if (v->q + 1 < v->r)
                stack.append(mergeNode(v->q + 1, v->r));
            v->rightDone = true;
        }
        else
        {
            n -= (v->r - v->l + 1);
            merge(v->l, v->q, v->r);
            stack.pop_back();
        }

    }

}


void MergeSort::merge(int l, int q, int r)
{
    int *tempArray = new int[r-l+1];
    int i = l;
    int j = q + 1;
    int k = 0;

    while (i <= q && j <= r)
    {
        list.append(Step(i, j, Sort::Comparision));
        if (values[i] < values[j])
        {
            tempArray[k] = values[i];
            i++;
        }
        else
        {
            tempArray[k] = values[j];
            j++;
        }
        k++;
    }

    while (i <= q)
    {
        tempArray[k] = values[i];
        i++;
        k++;
    }
    while (j <= r)
    {
        tempArray[k] = values[j];
        j++;
        k++;
    }

    k = 0;
    i = l;
    while (k < r-l+1)
    {
        list.append(Step(i, tempArray[k], Sort::Set));
        values[i] = tempArray[k];
        i++;
        k++;
    }
    delete []tempArray;
}

void MergeSort::nextStep(int n)
{
    run(n);
}

QuickSort::QuickSort(int n): Sort(n)
{
    stack.append(QSNode(0, n - 1));
}

QuickSort::QSNode::QSNode(int a, int b)
{
    l = a;
    r = b;
}

int QuickSort::partition(int l, int r)
{
    int q = qrand() % (r - l + 1) + l;
    int x = values[q];
    int i = l - 1;
    int j = r + 1;

    while(true)
    {
        do
        {
            j--;
            list.append(Step(j, j, Sort::Comparision));
        }while(values[j] > x);

        do
        {
            i++;
            list.append(Step(i, i, Sort::Comparision));
        }while(values[i] < x);

        if (i < j)
        {
            int tmp = values[i];
            values[i] = values[j];
            values[j] = tmp;
            list.append(Step(i, j, Sort::Swap));
        }
        else
            return j;
    }
}

void QuickSort::run(int n)
{
    while (!stack.empty() && n > 0)
    {
        QSNode v = stack.back();
        stack.pop_back();
        int p = partition(v.l, v.r);
        if (p > v.l)
            stack.append(QSNode(v.l, p));
        if (v.r > p + 1)
            stack.append(QSNode(p + 1, v.r));
        n -= (v.r - v.l);
    }
}

void QuickSort::nextStep(int n)
{
    run(n);
}

BogoSort::BogoSort(int n): Sort(n)
{
    sorted = false;
}

void BogoSort::nextStep(int n)
{
    while(n > 0 && sorted == false)
    {
        int i = 1;
        while (i < size && values[i] >= values[i-1])
        {
            list.append(Step(i, i-1, Sort::Comparision));
            i++;
            n--;
        }
        if (i < size)
        {
            randomize();
            n -= size;
        }
        else
            sorted = true;
    }

}

void BogoSort::randomize()
{
    //qsrand(QTime::currentTime().second());
    for (int i = size-1; i >= 0; i--)
    {
        int j = qrand() % (i+1);
        int tmp = values[i];
        values[i] = values[j];
        values[j] = tmp;
        list.append(Step(i, j, Sort::Swap));
    }
}






