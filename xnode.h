#ifndef XNODE_H
#define XNODE_H
#include <vector>
#include <random>
#include <QDebug>

template <class T>
class XNode
{
public:
    XNode();
    XNode(unsigned int nWeight) : weights(nWeight)
    {
        std::mt19937 gen;
        gen.seed(std::random_device()());
        std::uniform_real_distribution<> dist(-1, 1);
        for (double &w : weights) {
            w = dist(gen);
        }
    }

    void init(unsigned int nWeight)
    {
        *this = XNode(nWeight);
    }

    double getDistance(const std::vector<T> &inputVec)
    {
        double res = 0;
        for (unsigned int i = 0; i < weights.size(); ++i) {
            res += (weights[i] - inputVec[i]) * (weights[i] - inputVec[i]);
        }
        return sqrt(res);
    }

    std::vector<double> getWeight() const { return weights; }
    void setWeight(const std::vector<double> &w) { weights = w; }
    void addWeight(const std::vector<double> &w)
    {
        std::transform(weights.begin(), weights.end(), w.begin(), weights.begin(), std::plus<double>());
    }

private:
    std::vector<double> weights;
};

#endif // XNODE_H
