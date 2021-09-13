#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include <iostream>
#include <memory>
#include "shape.hpp"

namespace doguhan
{
class CompositeShape : public Shape
{
public:
  using pointer_t = std::shared_ptr<Shape>;
  CompositeShape();
  CompositeShape(const CompositeShape &src);
  CompositeShape(CompositeShape &&src) noexcept;
  ~CompositeShape() override = default;
  CompositeShape &operator=(const CompositeShape &src);
  CompositeShape &operator=(CompositeShape &&src) noexcept;
  pointer_t &operator[](size_t index) const;
  void add(const pointer_t &shape);
  void remove(size_t index);
  void print(std::ostream &out) const override;
  double getArea() const override;
  void move(const point_t &point) override;
  void move(double dx, double dy) override;
  rectangle_t getFrameRect() const override;
  void scale(double coefficient) override;
  size_t size() const;

private:
  std::unique_ptr<pointer_t[]> shapes_;
  size_t size_;
};
}

#endif
