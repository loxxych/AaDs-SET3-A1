#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <random>

using namespace std;

void generatePointInArea(vector<double>& point,
                         const double minX, const double maxX,
                         const double minY, const double maxY) {
    random_device rd;
    mt19937 mt(rd());
    uniform_real_distribution<> xDis(minX, maxX);
    uniform_real_distribution<> yDis(minY, maxY);

    point[0] = xDis(mt);
    point[1] = yDis(mt);
}

bool isInArea(const vector<double>& point, const double& x1, const double&  y1, const double&  r1,
                      const double&  x2, const double&  y2, const double&  r2,
                      const double&  x3, const double&  y3, const double&  r3) {
    const double x = point[0];
    const double y = point[1];

    const bool isInFirstCircle = (x - x1) * (x - x1) + (y - y1) * (y - y1) <= r1 * r1;
    const bool isInScndCircle = (x - x2) * (x - x2) + (y - y2) * (y - y2) <= r2 * r2;
    const bool isInThirdCircle = (x - x3) * (x - x3) + (y - y3) * (y - y3) <= r3 * r3;

    return isInFirstCircle && isInScndCircle && isInThirdCircle;
}

double monteCarloArea(const double& x1, const double&  y1, const double&  r1,
                      const double&  x2, const double&  y2, const double&  r2,
                      const double&  x3, const double&  y3, const double&  r3,
                      const long long N,
                      const double minX, const double maxX,
                      const double minY, const double maxY) {
    vector<double> point(2);

    long long M = 0;

    for (size_t i = 0; i < N; ++i) {
        generatePointInArea(point, minX, maxX, minY, maxY);
        if (isInArea(point, x1, y1, r1, x2, y2, r2, x3, y3, r3)) {
            ++M;
        }
    }

    return (double(M) / double(N)) * (maxX - minX) * (maxY - minY);
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false);

    long long N = 1000000;
    double minX = 0, maxX = 3.15, minY = 0, maxY = 3.15;

    if (argc > 1) {
        // Arg 1 - number of iterations
        N = atoll(argv[1]);
    }

    if (argc > 2) {
        // Arg 2 - sets the rectangle for point generation
        // s - small rectangle, b - big rectangle
        if (argv[2] == "s") { // small rectangle
            // Coordinates taken from the image in the task description
            minX = 0.85;
            maxX = 2.1;
            minY = 0.85;
            maxY = 2.1;
        } else {
            // Coordinates taken from the image in the task description
            minX = 0;
            maxX = 3.15;
            minY = 0;
            maxY = 3.15;
        }
    }

    double x1, y1, r1;
    double x2, y2, r2;
    double x3, y3, r3;

    cin >> x1 >> y1 >> r1;
    cin >> x2 >> y2 >> r2;
    cin >> x3 >> y3 >> r3;

    cout << monteCarloArea(x1, y1, r1, x2, y2, r2, x3, y3, r3, N, minX, maxX, minY, maxY);
    return 0;
}
