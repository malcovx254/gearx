#include "vec2.hpp"

// コンストラクタ
Vec2::Vec2() :x(0.0), y(0.0) {}
Vec2::Vec2(float x, float y)
    : x(x), y(y) {}

// 単項演算子
Vec2 Vec2::operator+() const {
    return *this;
}

Vec2 Vec2::operator-() const {
    return Vec2(-x, -y);
}

// 比較
bool Vec2::operator==(const Vec2& v) const {
    return (x == v.x && y == v.y);
}

// ベクトル同士
Vec2 Vec2::operator+(const Vec2& v) const {
    return Vec2(x + v.x, y + v.y);
}

Vec2 Vec2::operator-(const Vec2& v) const {
    return Vec2(x - v.x, y - v.y);
}

Vec2 Vec2::operator*(const Vec2& v) const {
    return Vec2(x * v.x, y * v.y);
}

Vec2 Vec2::operator/(const Vec2& v) const {
    return Vec2(x / v.x, y / v.y);
}

// スカラー演算
Vec2 Vec2::operator+(float s) const {
    return Vec2(x + s, y + s);
}

Vec2 Vec2::operator-(float s) const {
    return Vec2(x - s, y - s);
}

Vec2 Vec2::operator*(float s) const {
    return Vec2(x * s, y * s);
}

Vec2 Vec2::operator/(float s) const {
    return Vec2(x / s, y / s);
}