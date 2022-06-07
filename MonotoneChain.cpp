#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <string>

using namespace std;

struct Point
{
    double x, y;
};


bool binOps(Point a, Point b)
{
    return a.x < b. x || (a.x == b.x && a.y < b.y);
}

bool isUpper(Point a, Point b, Point c)
{
    return (b.x - a.x) * (b.y + a.y) + (c.x - b.x) * (c.y + b.y) + (a.x - c.x) * (a.y + c.y) > 0;
}

bool isLower(Point a, Point b, Point c)
{
    return (b.x - a.x) * (b.y + a.y) + (c.x - b.x) * (c.y + b.y) + (a.x - c.x) * (a.y + c.y) < 0;
}

void inpConvex(vector<Point> &arr, int nSize)
{
    ofstream outFile(to_string(nSize) + ".inp");

    srand(time(NULL));

    Point P;
    int rangeMax = 100000;

    for (int i = 0; i < nSize; i++)
    {
        P.x = rand() % rangeMax;
        P.y = rand() % rangeMax;
        
        arr.push_back(P);
        outFile << P.x << ' ' << P.y << endl;
    }

    outFile.close();
}

void outConvex(vector<Point> &arr, int nSize)
{
    ofstream outFile(to_string(nSize) + ".out");

    for (Point P : arr)
        outFile << P.x << ' ' << P.y << endl;

    outFile.close();
}


void monotoneChain(vector<Point> &arr, int &nAssign, int &nCompare)
{
    if (arr.size() == 1) return;

    sort(arr.begin(), arr.end(), &binOps);

    nAssign = 0;
    nCompare = 0;

    Point p1 = arr.front(); nAssign++;
    Point p2 = arr.back();  nAssign++;
    
    vector<Point> upper = {p1}; nAssign++;
    vector<Point> lower = {p1}; nAssign++;

    int i;

    for (i = 1, nAssign++; ++nCompare && (i < arr.size()); i++, nAssign++)
    {
        if (++nCompare && (i + 1 == arr.size() || isUpper(p1, arr[i], p2)))
        {
            while (++nCompare && upper.size() > 1 && !isUpper(upper[upper.size() - 2], upper[upper.size() - 1], arr[i]))
            {
                upper.pop_back(); nAssign++;
            }

            upper.push_back(arr[i]); nAssign++;
        }
        
        if (++nCompare && (i + 1 == arr.size() || isLower(p1, arr[i], p2)))
        {
            while (++nCompare && lower.size() > 1 && !isLower(lower[lower.size() - 2], lower[lower.size() - 1], arr[i]))
            {
                lower.pop_back(); nAssign++;
            }

            lower.push_back(arr[i]); nAssign++;
        }
    }

    arr.clear(); nAssign++;

    for (i = 0, nAssign++; ++nCompare && (i < upper.size() - 1); i++, nAssign++)
    {
        arr.push_back(upper[i]); nAssign++;
    }
    
    for (i = lower.size() - 1, nAssign++; ++nCompare && (i > 0); i--, nAssign++)
    {
        arr.push_back(lower[i]); nAssign++;
    }
}


int main()
{
    ofstream outFile("TestResult.txt");

    vector<Point> arr;

    int bstep = 25;
    int mstep = 10;
    int lstep = 100;

    for (int i = 5; i <= 1000000; i += bstep)
    {
        if (i > lstep)
        {
            bstep *= mstep;
            mstep -= 1;
            lstep *= 10;
        }

        cout << i << endl;

        int nAssign = 0;
        int nCompare = 0;

        arr.clear();

        inpConvex(arr, i);
        monotoneChain(arr, nAssign, nCompare);
        outConvex(arr, i);

        outFile << i << ' ' << nAssign << ' ' << nCompare << endl;
    }

    return 0;
}