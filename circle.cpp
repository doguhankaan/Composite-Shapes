#define _USE_MATH_DEFINES

#include "circle.hpp"
#include <cmath>
#include <iostream>
#include <stdexcept>

doguhan::Circle::Circle(double radius, const point_t &point) :
  radius_(radius),
  position_(point)
{
  if (radius <= 0.0)
  {
    throw std::invalid_argument("Invalid radius");
  }
}

double doguhan::Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

void doguhan::Circle::move(const point_t &point)
{
  position_ = point;
}

void doguhan::Circle::move(double dx, double dy)
{
  position_.x += dx;
  position_.y += dy;
}

doguhan::rectangle_t doguhan::Circle::getFrameRect() const
{
  return rectangle_t{2*radius_, 2*radius_, position_};
}

void doguhan::Circle::print(std::ostream &ostream) const
{
  ostream << "Area: " << getArea()
          << "Radius: " << radius_
          << "Position: "
          << "(" << position_.x
          << ", " << position_.y << ")" << std::endl;
}

void doguhan::Circle::scale(const double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("Incorrect coefficient.");
  }
  radius_ *= coefficient;
}
