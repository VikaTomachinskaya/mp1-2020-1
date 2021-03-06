#pragma once
#include "Matrix.h"
#include <iostream>

using namespace std;

template<class T>
class SLAU : public Matrix<T>
{
public:
	SLAU(int n) : Matrix<T>::Matrix(n) {}

	Vector<double>* Gausse(Vector<T> y);

};

template<class T>
inline Vector<double>* SLAU<T>::Gausse(Vector<T> y)
{
	Vector< Vector<T> > b = this[0];
    Vector< Vector<T> > a;// = b;
    for (int i = 0; i < b.Size(); ++i)
    {
        Vector<T> tmp;
        for (int j = 0; j < b.Size(); ++j)
        {
            tmp.push_back(b[i][j]);
        }
        a.push_back(tmp);
    }

    Vector<double>* x = new Vector<double>(a.Size() , 0);
    int k, index;
    const double eps = 0.00001;  // ��������
    int n = a.Size();
    double max;
    k = 0;
    while (k < n)
    {
        // ����� ������ � ������������ a[i][k]
        max = abs(a[k][k]);
        index = k;
        for (int i = k + 1; i < n; i++)
        {
            if (abs(a[i][k]) > max)
            {
                max = abs(a[i][k]);
                index = i;
            }
        }
        // ������������ �����
        if (max < eps)
        {
            // ��� ��������� ������������ ���������
            cout << "������� �������� ���������� ��-�� �������� ������� ";
            cout << index << " ������� A" << endl;
            return 0;
        }

        for (int j = 0; j < n; j++)
        {
            T temp = a[k][j];
            a[k][j] = a[index][j];
            a[index][j] = temp;
        }

       // SwapRow(index, k, &a);

        double temp = y[k];
        y[k] = y[index];
        y[index] = temp;
        

        // ������������ ���������
        for (int i = k; i < n; i++)
        {
            double temp = a[i][k];
            if (abs(temp) < eps) continue; // ��� �������� ������������ ����������
            for (int j = 0; j < n; j++)
                a[i][j] = a[i][j] / temp;
            y[i] = y[i] / temp;
            if (i == k)  continue; // ��������� �� �������� ���� �� ����
            for (int j = 0; j < n; j++)
                a[i][j] = a[i][j] - a[k][j];
            y[i] = y[i] - y[k];
        }

        k++;
    }
    // �������� �����������
    for (k = n - 1; k >= 0; k--)
    {
        (*x)[k] = y[k];
        for (int i = 0; i < k; i++)
            y[i] = y[i] - a[i][k] * (*x)[k];
    }
    return x;

}
