#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "base-types.hpp"
#include "shape.hpp"

namespace doguhan
{
class Circle : public Shape
{
public:
  Circle(double radius, const point_t &point);
  double getArea() const override;
  void move(const point_t &point) override;
  void move(double dx, double dy) override;
  rectangle_t getFrameRect() const override;
  void print(std::ostream &ostream) const override;
  void scale(double coefficient) override;

private:
  double radius_;
  point_t position_;
};
}

#endif
