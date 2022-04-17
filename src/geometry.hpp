#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <iostream>
#include <numeric>
/*
struct Point2D
{
    float values[2] {};

    Point2D() {}
    Point2D(float x, float y) : values { x, y } {}

    float& x() { return values[0]; }
    float x() const { return values[0]; }

    float& y() { return values[1]; }
    float y() const { return values[1]; }

    Point2D& operator+=(const Point2D& other)
    {
        x() += other.x();
        y() += other.y();
        return *this;
    }

    Point2D& operator*=(const Point2D& other)
    {
        x() *= other.x();
        y() *= other.y();
        return *this;
    }

    Point2D& operator*=(const float scalar)
    {
        x() *= scalar;
        y() *= scalar;
        return *this;
    }

    Point2D operator+(const Point2D& other) const
    {
        Point2D result = *this;
        result += other;
        return result;
    }

    Point2D operator*(const Point2D& other) const
    {
        Point2D result = *this;
        result *= other;
        return result;
    }

    Point2D operator*(const float scalar) const
    {
        Point2D result = *this;
        result *= scalar;
        return result;
    }
};

struct Point3D
{
    std::array<float,3> values {};

    Point3D() {}
    Point3D(float x, float y, float z) : values { x, y, z } {}

    float& x() { return values[0]; }
    float x() const { return values[0]; }

    float& y() { return values[1]; }
    float y() const { return values[1]; }

    float& z() { return values[2]; }
    float z() const { return values[2]; }

    Point3D& operator+=(const Point3D& other)
    {
        std::transform(values.begin(), values.end(),
                       other.values.begin(),values.begin(),
                       std::plus<float>()
                       );
        //x() += other.x();
        //y() += other.y();
        //z() += other.z();
        return *this;
    }

    Point3D& operator-=(const Point3D& other)
    {
        std::transform(values.begin(), values.end(),
                       other.values.begin(),values.begin(),
                       std::minus<float>()
                       );
        //x() -= other.x();
        //y() -= other.y();
        //z() -= other.z();
        return *this;
    }

    Point3D& operator*=(const float scalar)
    {
        std::transform(values.begin(), values.end(),
                       values.begin(),
                       [scalar](float coord){return coord * scalar;}
                       );
        //x() *= scalar;
        //y() *= scalar;
        //z() *= scalar;
        return *this;
    }

    Point3D operator+(const Point3D& other) const
    {
        Point3D result = *this;
        result += other;
        return result;
    }

    Point3D operator-(const Point3D& other) const
    {
        Point3D result = *this;
        result -= other;
        return result;
    }

    Point3D operator*(const float scalar) const
    {
        Point3D result = *this;
        result *= scalar;
        return result;
    }

    Point3D operator-() const { return Point3D { -x(), -y(), -z() }; }

    float length() const {
        return std::sqrt(
            std::reduce(values.begin(), values.end(), 0.,
            [](float f1, float f2)
                        {return f1 + f2*f2;}) );
        //return std::sqrt(x() * x() + y() * y() + z() * z());
    }

    float distance_to(const Point3D& other) const { return (*this - other).length(); }

    Point3D& normalize(const float target_len = 1.0f)
    {
        const float current_len = length();
        if (current_len == 0)
        {
            throw std::logic_error("cannot normalize vector of length 0");
        }

        *this *= (target_len / current_len);
        return *this;
    }

    Point3D& cap_length(const float max_len)
    {
        assert(max_len > 0);

        const float current_len = length();
        if (current_len > max_len)
        {
            *this *= (max_len / current_len);
        }
        return *this;
    }
};
*/

template <int dimension, typename TypeElement>
class Point
{
    
public:
    std::array<TypeElement,dimension> values {};
    
    Point() = default;
    // Constructeur Point 2D
    Point(TypeElement x, TypeElement y) : values { x, y }
    {
        static_assert(dimension==2, "Not the good number of parameters");
    }
    // Constructeur Point 3D
    Point(TypeElement x, TypeElement y, TypeElement z) : values { x, y, z } 
    {
        static_assert(dimension==3, "Not the good number of parameters");
    }

    template <typename... E>
    Point(TypeElement type, E&&... elem) : values { type, static_cast<TypeElement>(std::forward<E>(elem))... }
    {
        static_assert(sizeof...(E)==dimension-1, "Not the good number of parameters");
    }

    TypeElement& x()
    {
        return values[0];
    }
    TypeElement x() const
    {
        return values[0];
    }

    TypeElement& y()
    {
        static_assert(dimension>=2, "Dimension is lower than 2");
        return values[1];
    }

    TypeElement y() const
    {
        static_assert(dimension>=2, "Dimension is lower than 2");
        return values[1];
    }

    TypeElement& z()
    {
        static_assert(dimension>=3, "Dimension is lower than 3");
        return values[2];
    }

    TypeElement z() const
    {
        static_assert(dimension>=3, "Dimension is lower than 3");
        return values[2];
    }

    Point<dimension, TypeElement>& operator+=(const Point<dimension, TypeElement>& other)
    {
        std::transform(
            values.begin(), values.end(), other.values.begin(),
            values.begin(),
            std::plus<TypeElement>()
        );
        return *this;
    }

    Point<dimension, TypeElement>& operator-=(const Point<dimension, TypeElement>& other)
    {
        std::transform(
            values.begin(), values.end(), other.values.begin(),
            values.begin(),
            std::minus<TypeElement>()
        );
        return *this;
    }

    Point<dimension, TypeElement>& operator*=(const TypeElement scalar)
    {
        std::transform(
            values.begin(), values.end(), values.begin(),
            [scalar](TypeElement coord){return coord * scalar;}
        );
        return *this;
    }

    Point<dimension, TypeElement> operator+(const Point<dimension, TypeElement>& other) const
    {
        Point<dimension, TypeElement> result = *this;
        result += other;
        return result;
    }

    Point<dimension, TypeElement> operator-(const Point<dimension, TypeElement>& other) const
    {
        Point<dimension, TypeElement> result = *this;
        result -= other;
        return result;
    }

    Point<dimension, TypeElement> operator*(const float scalar) const
    {
        Point<dimension, TypeElement> result = *this;
        result *= scalar;
        return result;
    }

    Point<dimension, TypeElement>& operator*=(const Point<dimension, TypeElement>& other)
    {
        x() *= other.x();
        y() *= other.y();
        if constexpr(dimension > 2)
        {
            z() *= other.z();
        }
        return *this;
    }

    Point<dimension, TypeElement> operator*(const Point<dimension, TypeElement>& other) const
    {
        Point<dimension, TypeElement> result = *this;
        result *= other;
        return result;
    }

    Point<dimension, TypeElement> operator-() const { 
        if constexpr(dimension == 2)
            return Point<dimension, TypeElement> { -x(), -y() }; 
        return Point<dimension, TypeElement> { -x(), -y(), -z() }; 
    }

    TypeElement length() const { 
        return std::sqrt(
            std::reduce(values.begin(), values.end(), 0.,   
                        [](TypeElement f1, TypeElement f2) {return f1 + f2*f2;})
        );
    }

    float distance_to(const Point<dimension, TypeElement>& other) const { 
        return (*this - other).length(); 
    }

    Point<dimension, TypeElement>& normalize(const TypeElement target_len = 1.0f)
    {
        const float current_len = length();
        if (current_len == 0)
        {
            throw std::logic_error("cannot normalize vector of length 0");
        }

        *this *= (target_len / current_len);
        return *this;
    }

    Point<dimension, TypeElement>& cap_length(const TypeElement max_len)
    {
        assert(max_len > 0);

        const float current_len = length();
        if (current_len > max_len)
        {
            *this *= (max_len / current_len);
        }

        return *this;
    }
};

using Point2D = Point<2, float>;
using Point3D = Point<3, float>;

// our 3D-coordinate system will be tied to the airport: the runway is parallel to the x-axis, the z-axis
// points towards the sky, and y is perpendicular to both thus,
// {1,0,0} --> {.5,.5}   {0,1,0} --> {-.5,.5}   {0,0,1} --> {0,1}
inline Point2D project_2D(const Point3D& p)
{
    return { .5f * p.x() - .5f * p.y(), .5f * p.x() + .5f * p.y() + p.z() };
}
