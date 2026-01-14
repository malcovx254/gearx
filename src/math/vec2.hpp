#ifndef GEARX_MATH_VEC2_HPP
#define GEARX_MATH_VEC2_HPP


struct Vec2 {
    float x, y;

    // コンストラクタ
    Vec2();
    Vec2(float x = 0, float y = 0);

    // 単項演算子
    Vec2 operator+() const;
    Vec2 operator-() const;

    // 比較
    bool operator==(const Vec2& v) const;

    // ベクトル同士
    Vec2 operator+(const Vec2& v) const;
    Vec2 operator-(const Vec2& v) const;
    Vec2 operator*(const Vec2& v) const;
    Vec2 operator/(const Vec2& v) const;

    // スカラー演算
    Vec2 operator+(float s) const;
    Vec2 operator-(float s) const;
    Vec2 operator*(float s) const;
    Vec2 operator/(float s) const;
};


#endif 

/*
struct Vec2{
float x;
float y;
    Vec2() :x(0.0), y(0.0) {}
    Vec2(float x=0, float y=0) :x(x), y(y) {
    }

    Vec2 operator-() const {
        return Vec2(-x, -y);
    }
    Vec2 operator+() const {
        // 何も変更せず、現在のオブジェクトのコピーを返す
        return *this; 
    }
    bool operator==(const Vec2& vec2) const {
        return ((x == vec2.x) && (y == vec2.y));
    }
    Vec2 operator+(const Vec2& vec2) {
        return Vec2((x + vec2.x), (y + vec2.y));
    }
    Vec2 operator-(const Vec2& vec2) {
        return Vec2((x - vec2.x), (y - vec2.y));
    }
    Vec2 operator*(const Vec2& vec2) {
        return Vec2((x * vec2.x), (y * vec2.y));
    }
    Vec2 operator/(const Vec2& vec2) {
        return Vec2((x / vec2.x), (y / vec2.y));
    }
    Vec2 operator+(const float operand) {
        return Vec2((x + operand ), (y + operand));
    }
    Vec2 operator-(const float operand) {
        return Vec2((x - operand ), (y - operand));
    }    
    Vec2 operator*(const float operand) {
        return Vec2((x * operand ), (y * operand));
    }    
    Vec2 operator/(const float operand) {
        return Vec2((x / operand ), (y / operand));
    }
}


*/