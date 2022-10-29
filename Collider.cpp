//
// Created by 刘小备 on 2019/4/6.
//

#include "Collider.h"

void Collider::set(const glm::vec3 &min, const glm::vec3 &max) {
    this->_min = min;
    this->_max = max;
}

void Collider::reset() {
    _min = glm::vec3(99999.0f, 99999.0f, 99999.0f);
    _max = glm::vec3(-99999.0f, -99999.0f, -99999.0f);
}

bool Collider::isEmpty() const {
    return _min.x>_max.x || _min.y>_max.y || _min.z>_max.z;
}

void Collider::merge(const Collider &box) {
        _min.x = std::min(this->_min.x, box._min.x);
        _min.y = std::min(this->_min.y, box._min.y);
        _min.z = std::min(this->_min.z, box._min.z);

        _max.x = std::max(this->_max.x, box._max.x);
        _max.y = std::max(this->_max.y, box._max.y);
        _max.z = std::max(this->_max.z, box._max.z);
}

bool Collider::containPoint(const glm::vec3 &point) const {
    if (point.x < _min.x) return false;
    if (point.y < _min.y) return false;
    if (point.z < _min.z) return false;
    if (point.x > _max.x) return false;
    if (point.y > _max.y) return false;
    if (point.z > _max.z) return false;
    return true;
}

bool Collider::intersects(const Collider &target) const {
    return ((_min.x >= target._min.x && _min.x <= target._max.x) || (target._min.x >= _min.x && target._min.x <= _max.x)) &&
           ((_min.y >= target._min.y && _min.y <= target._max.y) || (target._min.y >= _min.y && target._min.y <= _max.y)) &&
           ((_min.z >= target._min.z && _min.z <= target._max.z) || (target._min.z >= _min.z && target._min.z <= _max.z));
}

glm::vec3 Collider::getCenter() {
    glm::vec3 center;
    center.x = (_min.x + _max.x) * 0.5f;
    center.y = (_min.y + _max.y) * 0.5f;
    center.z = (_min.z + _max.z) * 0.5f;
    return center;
}

Collider::Collider() {
    reset();
}

Collider::Collider(const glm::vec3 min, const glm::vec3 max) {
    set(min, max);
}

Collider::Collider(const Collider &x) {
    set(x._min, x._max);
}

void Collider::getCorners(glm::vec3 &dst) const {

}

void Collider::updateMinMax(const glm::vec3 point[], size_t num) {
    for(size_t i = 0; i< num; ++i){
        if(point[i].x < _min.x)
            _min.x = point[i].x;
        if(point[i].y < _min.y)
            _min.y = point[i].y;
        if(point[i].z < _min.z)
            _min.z = point[i].z;

        if(point[i].x > _max.x)
            _max.x = point[i].x;
        if(point[i].y > _max.y)
            _max.y = point[i].y;
        if(point[i].z > _max.z)
            _max.z = point[i].z;
    }
}

void Collider::transform(const glm::mat4 &mat) {
    glm::vec3 corners[8];

    corners[0] = glm::vec3(_min.x, _max.y, _max.z);
    //左下顶点坐标
    corners[1] = glm::vec3(_min.x, _min.y, _max.z);
    //右下顶点坐标
    corners[2] = glm::vec3(_max.x, _min.y, _max.z);
    //右上顶点坐标
    corners[3] = glm::vec3(_max.x, _max.y, _max.z);

    //朝向z轴负方向的面
    //右上顶点坐标
    corners[4] = glm::vec3(_max.x, _max.y, _min.z);
    //右下顶点坐标
    corners[5] = glm::vec3(_max.x, _min.y, _min.z);
    //左下顶点坐标
    corners[6] = glm::vec3(_min.x, _min.y, _min.z);
    //左上顶点坐标
    corners[7] = glm::vec3(_min.x, _max.y, _min.z);

    for(int i=0; i < 8; ++i)
        transformPoint(mat,corners[i]);
    reset();
    updateMinMax(corners,8);
}

void Collider::transformPoint(const glm::mat4& model, glm::vec3 &point) {
    glm::vec4 translatePoint = glm::vec4(point,1.0f);
    translatePoint = model * translatePoint;
    point = glm::vec3(translatePoint.x, translatePoint.y, translatePoint.z);
}

bool Collider::intersects(const glm::vec3 min, const glm::vec3 max) const{
    return ((_min.x >= min.x && _min.x <= max.x) || (min.x >= _min.x && min.x <= _max.x)) &&
           ((_min.y >= min.y && _min.y <= max.y) || (min.y >= _min.y && min.y <= _max.y)) &&
           ((_min.z >= min.z && _min.z <= max.z) || (min.z >= _min.z && min.z <= _max.z));
}





