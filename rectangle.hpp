#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "base-types.hpp"
#include "shape.hpp"

namespace doguhan
{
class Rectangle : public Shape
{
public:
  Rectangle(double width, double height, const point_t &position);
  double getArea() const override;
  void move(const point_t &point) override;
  void move(double dx, double dy) override;
  rectangle_t getFrameRect() const override;
  void print(std::ostream &ostream) const override;
  void scale(double coefficient) override;

private:
  double width_;
  double height_;
  point_t position_;
};
}

#endif
