#ifndef XSOM_H
#define XSOM_H
#include "xnode.h"
#include <vector>
#include <utility>
#include <algorithm>
#include <functional>
#include "xscatterchart.h"

template <class T>
class XSOM
{
public:
    friend class XScatterChart;
    XSOM() {}
    XSOM(unsigned int r, unsigned int c, unsigned int nWeight)
        : r(r), c(c), nW(nWeight),
          nodes(r, std::vector<XNode<T>>(c, XNode<T>(nWeight))), radius(std::max(r, c) / 2.0)
    {}

    void init(unsigned int r, unsigned int c, unsigned int nWeight)
    {
        *this = XSOM(r, c, nWeight);
    }

    void train(const std::vector<std::vector<T>> &samples, unsigned int iter = 1000)
    {
        iterTimes = 1;
        while (iterTimes < iter) {
            for (auto &sample : samples) {
                iterate(sample);
                if (iterTimes >= iter) {
                    break;
                }
            }
        }
    }

    std::pair<unsigned int, unsigned int> classify(const std::vector<T> &data)
    {
        std::vector<std::vector<double>> d(r, std::vector<double>(c, 0)); // Distances
        double minDist; // Minimum distance
        unsigned int u = -1, v; // Index of the nearest node

        for (unsigned int i = 0; i < r; ++i) {
            for (unsigned int j = 0; j < c; ++j) {
                d[i][j] = nodes[i][j].getDistance(data);

                // Update the nearest node
                if (u == -1 || d[i][j] < minDist) {
                    u = i; v = j;
                    minDist = d[i][j];
                }
            }
        }

        return std::make_pair(u, v);
    }
private:
    unsigned int r, c, nW;
    double radius;
    std::vector<std::vector<XNode<T>>> nodes;
    unsigned int iterTimes;

    void iterate(const std::vector<T> sample)
    {

        std::vector<std::vector<double>> d(r, std::vector<double>(c, 0)); // Distances

        double minDist; // Minimum distance
        unsigned int u = -1, v; // Index of the nearest node

        // Update the parameters
        double sigma = radius * exp(-(double)(iterTimes) / (iterTimes / log(radius)));
        double alpha = 100.0 / (200.0 + iterTimes);

        for (unsigned int i = 0; i < r; ++i) {
            for (unsigned int j = 0; j < c; ++j) {
                d[i][j] = nodes[i][j].getDistance(sample);

                // Update the nearest node
                if (u == -1 || d[i][j] < minDist) {
                    u = i; v = j;
                    minDist = d[i][j];
                }
            }
        }

        // Update the weights
        for (unsigned int i = 0; i < r; ++i) {
            for (unsigned int j = 0; j < c; ++j) {
                double f = alpha * neighborhood(i, j, u, v, sigma);
                std::vector<double> diff(nW);
                std::transform(sample.begin(), sample.end(), nodes[i][j].getWeight().begin(), diff.begin(), [f](T a, T b) {
                    return f * (a - b);
                });
                nodes[i][j].addWeight(diff);
            }
        }

        iterTimes++;
    }

    double neighborhood(unsigned int i, unsigned int j, unsigned int u, unsigned int v, double sigma)
    {
        return exp(-(double)((i - u) * (i - u) + (j - v) * (j - v)) / (2 * sigma * sigma));
    }
};

#endif // XSOM_H
