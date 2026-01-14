#include "vec3.hpp"


// コンストラクタ
Vec3::Vec3(): x(0.0), y(0.0), z(0.0) {}

Vec3::Vec3(float x, float y, float z)
    : x(x), y(y), z(z) {}

// 単項演算子
Vec3 Vec3::operator+() const {
    return *this;
}

Vec3 Vec3::operator-() const {
    return Vec3(-x, -y, -z);
}

// 比較
bool Vec3::operator==(const Vec3& v) const {
    return (x == v.x && y == v.y && z == v.z);
}

// ベクトル同士
Vec3 Vec3::operator+(const Vec3& v) const {
    return Vec3(x + v.x, y + v.y, z + v.z);
}

Vec3 Vec3::operator-(const Vec3& v) const {
    return Vec3(x - v.x, y - v.y, z - v.z);
}

Vec3 Vec3::operator*(const Vec3& v) const {
    return Vec3(x * v.x, y * v.y, z * v.z);
}

Vec3 Vec3::operator/(const Vec3& v) const {
    return Vec3(x / v.x, y / v.y, z / v.z);
}

// スカラー演算
Vec3 Vec3::operator+(float s) const {
    return Vec3(x + s, y + s, z + s);
}

Vec3 Vec3::operator-(float s) const {
    return Vec3(x - s, y - s, z - s);
}

Vec3 Vec3::operator*(float s) const {
    return Vec3(x * s, y * s, z * s);
}

Vec3 Vec3::operator/(float s) const {
    return Vec3(x / s, y / s, z / s);
}