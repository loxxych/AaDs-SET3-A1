#include <iostream>
#include <random>
#include <vector>
#include <fstream>

using namespace std;

bool isInArea(double x, double y,
              double x1, double y1, double r1,
              double x2, double y2, double r2,
              double x3, double y3, double r3)
{
    auto inside = [&](double xc, double yc, double rc){
        return (x - xc)*(x - xc) + (y - yc)*(y - yc) <= rc*rc;
    };
    return inside(x1,y1,r1) && inside(x2,y2,r2) && inside(x3,y3,r3);
}

double monteCarlo(double x1,double y1,double r1,
                  double x2,double y2,double r2,
                  double x3,double y3,double r3,
                  long long N,
                  double minX,double maxX,
                  double minY,double maxY)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<> dx(minX,maxX);
    std::uniform_real_distribution<> dy(minY,maxY);

    long long M = 0;

    for (long long i=0; i<N; i++) {
        double x = dx(mt);
        double y = dy(mt);

        if (isInArea(x,y,x1,y1,r1,x2,y2,r2,x3,y3,r3))
            M++;
    }

    return double(M)/N * (maxX - minX) * (maxY - minY);
}

int main(int argc,char** argv)
{
    long long N = 10000;

    if (argc > 1)
        N = atoll(argv[1]);

    double x1,y1,r1;
    double x2,y2,r2;
    double x3,y3,r3;

    cin >> x1 >> y1 >> r1;
    cin >> x2 >> y2 >> r2;
    cin >> x3 >> y3 >> r3;

    // Узкий прямоугольник
    double s_minX = 0.85, s_maxX = 2.10;
    double s_minY = 0.85, s_maxY = 2.10;

    // Широкий прямоугольник
    double b_minX = 0.0,  b_maxX = 3.15;
    double b_minY = 0.0,  b_maxY = 3.15;

    double area_small = monteCarlo(
        x1,y1,r1,
        x2,y2,r2,
        x3,y3,r3,
        N,
        s_minX,s_maxX,
        s_minY,s_maxY
    );

    double area_big = monteCarlo(
        x1,y1,r1,
        x2,y2,r2,
        x3,y3,r3,
        N,
        b_minX,b_maxX,
        b_minY,b_maxY
    );

    cout << N << "," << area_small << "," << area_big;
}
