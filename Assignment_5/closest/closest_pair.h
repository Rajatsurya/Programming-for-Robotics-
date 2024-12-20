#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>

struct Point {
    int id;
    double x, y;
};

double dist(const Point& p1, const Point& p2) {
    auto dx = p1.x - p2.x;
    auto dy = p1.y - p2.y;
    return std::sqrt(dx * dx + dy * dy);
}

// Naive closest pair for small sets
std::pair<Point, Point> closest_pair_brute(const std::vector<Point>& points) {
    double min_dist = std::numeric_limits<double>::infinity();
    std::pair<Point, Point> min_pair = {points[0], points[1]};

    for (size_t i = 0; i < points.size(); ++i) {
        for (size_t j = i + 1; j < points.size(); ++j) {
            double d = dist(points[i], points[j]);
            if (d < min_dist) {
                min_dist = d;
                min_pair = {points[i], points[j]};
            }
        }
    }
    return min_pair;
}

// Helper function for recursive closest pair search
std::pair<Point, Point> closest_pair_recursive(std::vector<Point>& points_sorted_x, 
                                               std::vector<Point>& points_sorted_y) {
    // Base case: use brute force if the problem size is small
    if (points_sorted_x.size() <= 3) {
        return closest_pair_brute(points_sorted_x);
    }

    // Split points into left and right halves
    size_t mid = points_sorted_x.size() / 2;
    double mid_x = points_sorted_x[mid].x;

    std::vector<Point> left_x(points_sorted_x.begin(), points_sorted_x.begin() + mid);
    std::vector<Point> right_x(points_sorted_x.begin() + mid, points_sorted_x.end());

    std::vector<Point> left_y, right_y;
    for (const auto& point : points_sorted_y) {
        if (point.x <= mid_x) left_y.push_back(point);
        else right_y.push_back(point);
    }

    // Recursive calls
    auto left_pair = closest_pair_recursive(left_x, left_y);
    auto right_pair = closest_pair_recursive(right_x, right_y);

    // Find the minimum distance from the left and right halves
    double min_dist = std::min(dist(left_pair.first, left_pair.second), dist(right_pair.first, right_pair.second));
    std::pair<Point, Point> min_pair = dist(left_pair.first, left_pair.second) < dist(right_pair.first, right_pair.second) ? left_pair : right_pair;

    // Check the strip within min_dist of the dividing line
    std::vector<Point> strip;
    for (const auto& point : points_sorted_y) {
        if (std::abs(point.x - mid_x) < min_dist) {
            strip.push_back(point);
        }
    }

    // Find the closest pair in the strip
    for (size_t i = 0; i < strip.size(); ++i) {
        for (size_t j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < min_dist; ++j) {
            double d = dist(strip[i], strip[j]);
            if (d < min_dist) {
                min_dist = d;
                min_pair = {strip[i], strip[j]};
            }
        }
    }

    // Ensure the point with the lower ID is first in the pair
    if (min_pair.first.id > min_pair.second.id) {
        std::swap(min_pair.first, min_pair.second);
    }

    return min_pair;
}

std::pair<Point, Point> closest_pair(const std::vector<Point>& points) {
    std::vector<Point> points_sorted_x = points;
    std::vector<Point> points_sorted_y = points;

    // Sort by x and y coordinates
    std::sort(points_sorted_x.begin(), points_sorted_x.end(), [](const Point& p1, const Point& p2) {
        return p1.x < p2.x;
    });
    std::sort(points_sorted_y.begin(), points_sorted_y.end(), [](const Point& p1, const Point& p2) {
        return p1.y < p2.y;
    });

    // Use recursive divide and conquer method
    return closest_pair_recursive(points_sorted_x, points_sorted_y);
}
