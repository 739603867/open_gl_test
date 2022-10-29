//
// Created by 刘小备 on 2019/4/6.
//

#ifndef TEST_COLLIDER_H
#define TEST_COLLIDER_H

#include <glm.hpp>
#include <algorithm>
class Collider {
public:
    Collider();

    Collider(const glm::vec3 min, const glm::vec3 max);

    Collider(const Collider& x);

    glm::vec3 getCenter();

    void getCorners(glm::vec3& dst) const;

    bool intersects(const Collider& target) const;

    bool intersects(const glm::vec3 min, const glm::vec3 max) const;

    bool containPoint(const glm::vec3& point) const;

    void merge(const Collider& box);

    void set(const glm::vec3& min, const glm::vec3& max);

    void reset();

    bool isEmpty() const;

    void updateMinMax(const glm::vec3 point[], size_t num);

    void transform(const glm::mat4& mat);

    void transformPoint(const glm::mat4& model, glm::vec3& point);
public:
    glm::vec3 _min;
    glm::vec3 _max;
};


#endif //TEST_COLLIDER_H
