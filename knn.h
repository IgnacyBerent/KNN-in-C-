#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>

class KNN {
public:
    KNN(std::vector<float> data, int neighbours);
    int predict(float number);

private:
    void create_centroids();
    int closest_centroid(int number);
    std::vector<int> find_closest_centroids();
    void calculate_mean(std::vector<int>& closest_centroids);
    void train();

    std::vector<int> centroids;
    std::vector<float> data;
    int n;
};

#endif // LIBRARY_H