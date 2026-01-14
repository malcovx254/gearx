#ifndef GEARX_MATH_VEC3_HPP
#define GEARX_MATH_VEC3_HPP

struct Vec3 {
    float x, y, z;

    // コンストラクタ
    Vec3();
    Vec3(float x = 0, float y = 0, float z = 0);

    // 単項演算子
    Vec3 operator+() const;
    Vec3 operator-() const;

    // 比較
    bool operator==(const Vec3& vec3) const;

    // ベクトル同士
    Vec3 operator+(const Vec3& vec3) const;
    Vec3 operator-(const Vec3& vec3) const;
    Vec3 operator*(const Vec3& vec3) const;
    Vec3 operator/(const Vec3& vec3) const;

    // スカラー演算
    Vec3 operator+(float operand) const;
    Vec3 operator-(float operand) const;
    Vec3 operator*(float operand) const;
    Vec3 operator/(float operand) const;
};

#endif

/*
struct Vec3 { 
float x; float y; float z; 
Vec3() :x(0.0), y(0.0), z(0.0) {}
Vec3(float x=0, float y=0, float z=0) :x(x), y(y), z(z) { } 
bool operator==(const Vec3& vec3) const { return ((x == vec3.x) && (y == vec3.y) && (z == vec3.z)); } 

Vec3 operator+() const { // 何も変更せず、現在のオブジェクトのコピーを返す return this; } 
Vec3 operator-() const { return Vec3(-x, -y, -z); }
Vec3 operator+(const Vec3& vec3) { return Vec3((x + vec3.x), (y + vec3.y), (z + vec3.z)); } 
Vec3 operator-(const Vec3& vec3) { return Vec3((x - vec3.x), (y - vec3.y), (z - vec3.z)); }
Vec3 operator*(const Vec3& vec3) { return Vec3((x * vec3.x), (y * vec3.y), (z * vec3.z)); }
Vec3 operator/(const Vec3& vec3) { return Vec3((x / vec3.x), (y / vec3.y), (z / vec3.z)); } 
Vec3 operator+(const float operand) { return Vec3((x + operand ), (y + operand), (z + operand)); } 
Vec3 operator-(const float operand) { return Vec3((x - operand ), (y - operand), (z - operand)); }
Vec3 operator*(const float operand) { return Vec3((x * operand ), (y * operand), (z * operand)); }
Vec3 operator/(const float operand) { return Vec3((x / operand ), (y / operand), (z / operand)); }
};

*/