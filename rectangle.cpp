#include "rectangle.hpp"
#include <iostream>
#include <stdexcept>
#include "base-types.hpp"

doguhan::Rectangle::Rectangle(double width, double height, const point_t &point) :
  width_(width),
  height_(height),
  position_(point)
{
  if (width <= 0.0)
  {
    throw std::invalid_argument("Invalid width");
  }
  if (height <= 0.0)
  {
    throw std::invalid_argument("Invalid height");
  }
}

double doguhan::Rectangle::getArea() const
{
  return width_ * height_;
}

void doguhan::Rectangle::move(const point_t &point)
{
  position_ = point;
}

void doguhan::Rectangle::move(double dx, double dy)
{
  position_.x += dx;
  position_.y += dy;
}

doguhan::rectangle_t doguhan::Rectangle::getFrameRect() const
{
  return rectangle_t{width_, height_, position_};
}

void doguhan::Rectangle::print(std::ostream &ostream) const
{
  ostream << "Area: " << getArea()
          << "Height: " << height_
          << "Width: " << width_
          << "Center is: "
          << "(" << position_.x
          << ", " << position_.y << ")" << std::endl;
}

void doguhan::Rectangle::scale(double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("Incorrect coefficient.");
  }
  height_ *= coefficient;
  width_ *= coefficient;
}
