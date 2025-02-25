#include "LineSegment.hpp"

bool LineSegment::intersect(const Ray& ray, float& t) const {
    Vec2 v1 = ray.origin - p1;
    Vec2 v2 = p2 - p1;
    Vec2 v3(-ray.direction.y, ray.direction.x);

    float dot = v2.dot(v3);
    if (std::abs(dot) < 0.0001f) return false;

    float t1 = v2.cross(v1) / dot;
    float t2 = v1.dot(v3) / dot;

    if (t1 >= 0.0f && t2 >= 0.0f && t2 <= 1.0f) {
        t = t1;
        return true;
    }
    return false;
}
