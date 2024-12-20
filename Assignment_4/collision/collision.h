#include <eigen3/Eigen/Eigen>
#include <fstream>
#include <iostream>
#include <vector>

using Edge = std::pair<Eigen::Vector2d, Eigen::Vector2d>;

// returns true if the equation a*t^2+b*t+c=0 has a solution between 0 and 1 (inclusive)
// HINT: recall your solution to `quadratic` in HW1 
bool quadratic_has_valid_solution(double const a, double const b,  double const c) {
    // --- Your code here
    double x1 = (-b + std::sqrt(b*b -4*a*c))/(2*a);
    double x2 = (-b - std::sqrt(b*b -4*a*c))/(2*a);

    return (x1>=0 && x1 <=1) || (x2>=0 && x2<=1);

    // ---
}

class Disc; // forward-declare the type Disc, otherwise we can't use it in the Obstacle base class

class Obstacle
{
public:
    // returns true if the robot is collides with the obstacle
    virtual bool check_collision(Disc const &robot) const = 0;

    // returns true if whether the point p is within this disc
    virtual bool contains(Eigen::Vector2d const &p) const = 0;
};

class Disc : public Obstacle
{
public:
    Disc(double x, double y, double radius) : pos_(x, y), radius_(radius) {}

    // override check_collision (HINT: use the `norm` function!)
    bool check_collision(Disc const &robot) const override
    {
        // --- Your code here
       double dist = (robot.pos_ - pos_).norm();
        if ((dist< robot.radius_ + radius_)) {
            return true;
        }
        else {
            return false;
        }

        // ---
    }

    // returns true if the point p is within this disc
    bool contains(Eigen::Vector2d const &p) const override
    {
        // --- Your code here
        // check if points is within the disk
        // norm of the point and the x,y - radius of the disc
        if ((p - pos_).norm() < radius_) {
            return true;
        }
        else {
            return false;
        }

        // ---
    }


    Eigen::Vector2d pos_;
    double radius_;
};
class Rectangle : public Obstacle
{
public:
    Rectangle(double x1, double y1, double x2, double y2) : bottom_left_(x1, y1), top_right_(x2, y2),
                                                            edges_{{{x1, y1}, {x2, y1}}, {{x2, y1}, {x2, y2}}, {{x2, y2}, {x1, y2}}, {{x1, y2}, {x1, y1}}},
                                                            corners_{{x1, y1}, {x2, y1}, {x2,y2}, {x1,y2}}
    {
    }

    // override check_collision
    // HINT: use the `Rectangle::check_intersection_with_edge`, `Rectangle::contains`, and `Disc::contains` functions
    // --- Your code here
    bool check_collision(Disc const &robot) const override
    {
        if (contains(robot.pos_)) {
            return true;
        }
        for (const auto& corner : corners_) {
            if(robot.contains(corner)) {
                return true;
            }
        }
        for (const auto& edge : edges_) {
            if (check_intersection_with_edge(edge, robot)) {
                return true;
            }
        }
    return false;

    }


    // ---

    // Override the `contains` function
    // --- Your code here
    bool contains(Eigen::Vector2d const &p) const override
    {
        return (p.x() >= bottom_left_.x() && p.x() <=top_right_.x() && p.y() >= bottom_left_.y() && p.y() <= top_right_.y());
    }

    // ---

    // (HINT: use the `quadratic_has_valid_solution` function)
    bool check_intersection_with_edge(Edge const &e, Disc const& disc) const
    {
        // --- Your code here
        Eigen::Vector2d p1 = e.first - disc.pos_;
        Eigen::Vector2d p2 = e.second - disc.pos_;
        Eigen::Vector2d d = p2 - p1;

        double a = d.dot(d);
        double b = 2 * p1.dot(d);
        double c = p1.dot(p1) - disc.radius_ * disc.radius_;

        return quadratic_has_valid_solution(a,b,c);

        // ---
    }

    Eigen::Vector2d bottom_left_;
    Eigen::Vector2d top_right_;
    std::vector<Edge> edges_;
    std::vector<Eigen::Vector2d> corners_;
};

bool check_collisions(std::vector<Obstacle const *> const &obstacles, Disc const &robot)
{
    // --- Your code here
    for (const auto *obstacle : obstacles) {
        if (obstacle->check_collision(robot)) {
            return true;
        }
    }
    return false;

    // ---
}