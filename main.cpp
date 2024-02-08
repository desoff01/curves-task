#include "curves.h"
#include <vector>
#include <random>
#include <memory>
#include <algorithm>
#include <future>

inline constexpr double t {M_PI / 4};
inline constexpr size_t SIZE_CURVES {20};
inline constexpr size_t NUM_THREADS {3};

double sumOfRadii(const std::vector<std::shared_ptr<Circle>> &c, const size_t &start, const size_t &end) {
    double sum {0};
    for (size_t i {start}; i <= end; i++) {
        sum += c[i]->getRadius();
    }
    return sum;
}

int main() {
    std::vector<std::shared_ptr<Curve>> curves;
    curves.reserve(SIZE_CURVES);

    std::vector<std::shared_ptr<Circle>> circles;

    std::random_device r;
    std::default_random_engine dre(r());
    std::uniform_real_distribution<double> pointDist(-10, 10);
    std::uniform_real_distribution<double> radiusDist(0, 10);
    std::uniform_int_distribution<uint8_t> curveDist(0, 2);

    // populate the container
    for (size_t i {0}; i < SIZE_CURVES; i++) {
        switch (curveDist(dre)) {
        case 0:
            curves.emplace_back(std::make_shared<Circle>(radiusDist(dre)));

            circles.emplace_back(std::dynamic_pointer_cast<Circle>(curves.back()));
            break;
        case 1:
            curves.emplace_back(std::make_shared<Ellipse>(radiusDist(dre), radiusDist(dre)));
            break;
        case 2:
            curves.emplace_back(std::make_shared<Helix>(radiusDist(dre), radiusDist(dre)));
            break;
        }
    }

    // Print coordinates of points and derivatives
    for (auto& c : curves) {
        std::cout << "Point:      " << c->getPoint(t) << std::endl;
        std::cout << "Derivative: " << c->getDerivative(t) << std::endl;
    }
    
    // sort the container of circles
    sort(circles.begin(), circles.end(), [](std::shared_ptr<Circle> a,
            std::shared_ptr<Circle> b) {
        return a->getRadius() < b->getRadius();
    });

    // compute the total sum of radii in the second container
    std::future<double> ret2;
    std::future<double> ret3;
    size_t start{0}, end {circles.size() / 3};

    std::future<double> ret1 {std::async(&sumOfRadii, circles, start, end)};
    start = end + 1;
    end = (circles.size() % 3 == 2) ? (circles.size() / 3) * 2 + 1 : (circles.size() / 3) * 2;

    ret2 = std::async(&sumOfRadii, circles, start, end);
    start = end + 1;
    ret3 = std::async(&sumOfRadii, circles, start, circles.size()-1);

    double totalSum {ret1.get() + ret2.get() + ret3.get()};

    std::cout << "Sum: " << totalSum << std:: endl;

    return 0;
}