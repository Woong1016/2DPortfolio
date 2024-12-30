#pragma once

struct Vector2
{
    float x = 0.0f;
    float y = 0.0f;

    Vector2() = default;
    Vector2(float x, float y) : x(x), y(y) {};
    Vector2(POINT point) : x(point.x), y(point.y) {};
    Vector2(Float2 point) : x(point.x), y(point.y) {};

    Vector2 operator+(const Vector2& value) const
    {
        return Vector2(x + value.x, y + value.y);
    }
    Vector2 operator-(const Vector2& value) const
    {
        return Vector2(x - value.x, y - value.y);
    }
    Vector2 operator*(const Vector2& value) const
    {
        return Vector2(x * value.x, y * value.y);
    }
    Vector2 operator/(const Vector2& value) const
    {
        return Vector2(x / value.x, y / value.y);
    }
    Vector2 operator*(const float& value) const
    {
        return Vector2(x * value, y * value);
    }
    Vector2 operator/(const float& value) const
    {
        return Vector2(x / value, y / value);
    }

    void operator+=(const Vector2& value)
    {
        x += value.x;
        y += value.y;
    }
    void operator-=(const Vector2& value)
    {
        x -= value.x;
        y -= value.y;
    }
    void operator*=(const float& value)
    {
        x *= value;
        y *= value;
    }
    void operator/=(const float& value)
    {
        x /= value;
        y /= value;
    }

    Vector2 operator* (const Matrix& value) const
    {
        Float2 coord(x, y);
        XMVECTOR temp = XMLoadFloat2(&coord);

        //XMVector2TransformNormal : w-> 0
        //XMVector2TransformCoord : w-> 1
        temp = XMVector2TransformCoord(temp, value);
        
        XMStoreFloat2(&coord, temp);

        return coord;
    }

    void operator*= (const Matrix& value)
    {
        Float2 coord(x, y);
        XMVECTOR temp = XMLoadFloat2(&coord);
                
        temp = XMVector2TransformCoord(temp, value);

        XMStoreFloat2(&coord, temp);

        x = coord.x;
        y = coord.y;
    }

    float Length() const
    {
        return sqrt(x * x + y * y);
    }

    void Normalize()
    {
        float length = Length();

        x /= length;
        y /= length;
    }

    Vector2 GetNormalized() const
    {
        float length = Length();

        return Vector2(x / length, y / length);        
    }

    float Angle() const
    {
        return atan2(y, x);
    }

    // 2차원 수직선 얻기 함수
    Vector2 Normal()
    {
        return Vector2(-y, x); // x의 좌표는 y로 가고, y는 x로 가고, 둘 중 하나는 음수가 되어 방향을 꺾는다
    }

    //벡터에서 바로 호출하는 점곱
    float Dot(Vector2 input) const // 함수 결과를 마음대로 입력 못 하게
    {
        return (x * input.x) + (y * input.y); // x끼리, y끼리 곱하면 2차원 벡터는 점곱이 이루어진다 (공식)
    }
};