#include "library.h"

#include <iostream>
#include <vector>
#include <algorithm>

class KNN {
    std::vector<int> centroids;
    std::vector<float> list;
    int n;

public:
    // constructor
    KNN(std::vector<float> list, int neighbours) {
        this->list = list;
        std::sort(this->list.begin(), this->list.end());
        this->n = neighbours;
        this->centroids = create_centroids();
        predict();
    }

private:
    // create random centroids
    std::vector<int> create_centroids() {
        for (int i = 0; i < n; i++) {
            int random = rand() % 100;
            centroids.push_back(random);
        }
        return centroids;
    }

    // calculated closesd centroid to the given number
    int closest_centroid(int number) {
        int closest = 0;
        int distance = 0;
        for (int i = 0; i < centroids.size(); i++) {
            int temp = abs(centroids[i] - number);
            if (distance == 0) {
                distance = temp;
                closest = i;
            }
            else if (temp < distance) {
                distance = temp;
                closest = i;
            }
        }
        return closest;
    }

    // find closest centroid to each number in the list
    std::vector<int> find_closest_centroids() {
        std::vector<int> closest_centroids;
        for (int i = 0; i < this->list.size(); i++) {
            closest_centroids.push_back(closest_centroid(this->list[i]));
        }
        return closest_centroids;
    }

    // calculate mean of each centroid
    void calculate_mean(std::vector<int> closest_centroids) {
        std::vector<int> means;
        for (int i = 0; i < centroids.size(); i++) {
            int sum = 0;
            int count = 0;
            for (int j = 0; j < closest_centroids.size(); j++) {
                if (closest_centroids[j] == i) {
                    sum += this->list[j];
                    count++;
                }
            }
            if (count != 0) {
                means.push_back(sum/count);
            } else {
                means.push_back(0);
            }
        }
        this->centroids = means;
    }

    // predict centroids until they stop changing
    void predict() {
        std::vector<int> closest_centroids = find_closest_centroids();
        calculate_mean(closest_centroids);
        std::vector<int> new_closest_centroids = find_closest_centroids();
        while (closest_centroids != new_closest_centroids) {
            closest_centroids = new_closest_centroids;
            calculate_mean(closest_centroids);
            new_closest_centroids = find_closest_centroids();
        }
    }
};