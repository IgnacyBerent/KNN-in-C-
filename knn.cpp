#include "knn.h"

#include <iostream>
#include <vector>
#include <algorithm>

// constructor
KNN::KNN(std::vector<float> data, int neighbours) {
    this->data = data;
    std::sort(this->data.begin(), this->data.end());
    this->n = neighbours;
    create_centroids();
    train();
}

// predict the closest centroid to the given number
int KNN::predict(float number) {
    int closest = closest_centroid(number);
    return centroids[closest];
}

// create random centroids
void KNN::create_centroids() {
    for (int i = 0; i < n; i++) {
        int random = rand() % 100;
        centroids.push_back(random);
    }
}

// calculated closest centroid to the given number
int KNN::closest_centroid(int number) {
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

// find a closest centroid to each number in the list
std::vector<int> KNN::find_closest_centroids() {
    std::vector<int> closest_centroids;
    for (int i = 0; i < this->data.size(); i++) {
        closest_centroids.push_back(closest_centroid(this->data[i]));
    }
    return closest_centroids;
}

// calculate mean of each centroid
void KNN::calculate_mean(std::vector<int>& closest_centroids) {
    std::vector<int> means;
    for (int i = 0; i < centroids.size(); i++) {
        int sum = 0;
        int count = 0;
        for (int j = 0; j < closest_centroids.size(); j++) {
            if (closest_centroids[j] == i) {
                sum += this->data[j];
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

// train model until centroids stop changing
void KNN::train() {
    std::vector<int> closest_centroids = find_closest_centroids();
    calculate_mean(closest_centroids);
    while (true) {
        std::vector<int> old_centroids = closest_centroids;
        closest_centroids = find_closest_centroids();
        if (old_centroids == closest_centroids) {
            break;
        }
        calculate_mean(closest_centroids);
    }

    // Clear and shrink the data vector after training
    data.clear();
    data.shrink_to_fit();
}