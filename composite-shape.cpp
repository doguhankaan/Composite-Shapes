#include "composite-shape.hpp"

#include <iostream>
#include <memory>
#include <stdexcept>
#include <cmath>

#include "base-types.hpp"

doguhan::CompositeShape::CompositeShape() :
  size_(0)
{}

doguhan::CompositeShape::CompositeShape(const CompositeShape& shape):
  size_(shape.size_)
{
  if (shape.size_ > 0)
  {
    shapes_ = std::make_unique<std::shared_ptr<Shape>[]>(shape.size_);
    size_ = shape.size_;
    for (size_t i = 0; i < size_; ++i)
    {
      shapes_[i] = shape.shapes_[i];
    }
  }
}

doguhan::CompositeShape::CompositeShape(CompositeShape &&source) noexcept:
  shapes_(std::move(source.shapes_)),
  size_(source.size_)
{
  source.size_ = 0;
}

doguhan::CompositeShape &doguhan::CompositeShape::operator=(CompositeShape &&source) noexcept
{
  if (this != &source)
  {
    shapes_ = std::move(source.shapes_);
    size_ = source.size_;
    source.size_ = 0;
  }
  return *this;
}

doguhan::CompositeShape &doguhan::CompositeShape::operator=(const CompositeShape &source)
{
  if (this == &source)
  {
    return *this;
  }
  if (source.size_ != 0)
  {
    shapes_ = std::make_unique<pointer_t[]>(source.size_);
    size_ = source.size_;
    for (size_t i = 0; i < size_; ++i)
    {
      shapes_[i] = source.shapes_[i];
    }
  }
  else
  {
    shapes_ = nullptr;
    size_ = 0;
  }
  return *this;
}

void doguhan::CompositeShape::print(std::ostream &out) const
{
  std::cout << "CompositeShape: \n";
  for (size_t i = 0; i < size_; i++)
  {
    shapes_[i]->print(out);
  }
  std::cout << '\n';
}

void doguhan::CompositeShape::add(const pointer_t &shape)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Null Pointer shape added");
  }
  if (shape.get() == this)
  {
    throw std::invalid_argument("You can't add a shape to yourself");
  }
  for (size_t i = 0; i < size(); ++i)
  {
    if (shapes_[i] == shape)
    {
      throw std::invalid_argument("Already included");
    }
  }
  std::unique_ptr<pointer_t[]> temp = std::make_unique<pointer_t[]>(size_ + 1);
  for (size_t i = 0; i < size_; ++i)
  {
    temp[i] = shapes_[i];
  }
  shapes_ = std::move(temp);
  shapes_[size_] = shape;
  ++size_;
}

doguhan::rectangle_t doguhan::CompositeShape::getFrameRect() const
{
  if (size_ == 0)
  {
    return {0, 0, {0, 0}};
  }
  size_t i = 0;
  rectangle_t tmp{};

  for (; i < size_; i++)
  {
    if (shapes_[i]->getFrameRect().width != 0)
    {
      tmp = shapes_[i]->getFrameRect();
      break;
    }
  }

  if (i == size_)
  {
    return {0, 0, {0, 0}};
  }
  double minX = tmp.pos.x - (tmp.width / 2);
  double maxX = tmp.pos.x + (tmp.width / 2);
  double minY = tmp.pos.y - (tmp.height / 2);
  double maxY = tmp.pos.y + (tmp.height / 2);

  for (; i < size_; i++)
  {
    if (shapes_[i]->getFrameRect().width != 0)
    {
      tmp = shapes_[i]->getFrameRect();
      minX = std::min(minX, tmp.pos.x - (tmp.width / 2));
      maxX = std::max(maxX, tmp.pos.x + (tmp.width / 2));
      minY = std::min(minY, tmp.pos.y - (tmp.height / 2));
      maxY = std::max(maxY, tmp.pos.y + (tmp.height / 2));
    }
  }
  return {maxX - minX, maxY - minY, {minX + (maxX - minX) / 2, minY + (maxY - minY) / 2}};
}

void doguhan::CompositeShape::move(double dx, double dy)
{
  for (size_t i = 0; i < size_; i++)
  {
    shapes_[i]->move(dx, dy);
  }
}

double doguhan::CompositeShape::getArea() const
{
  double totalArea = 0;
  for (size_t i = 0; i < size_; i++)
  {
    totalArea += shapes_[i]->getArea();
  }
  return totalArea;
}

void doguhan::CompositeShape::move(const doguhan::point_t &point)
{
  const point_t compShapeCenter = getFrameRect().pos;
  move(point.x - compShapeCenter.x, point.y - compShapeCenter.y);
}

void doguhan::CompositeShape::scale(double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("Coefficient was non-positive");
  }
  const doguhan::rectangle_t frameRect = getFrameRect();
  for (size_t i = 0; i < size_; ++i)
  {
    shapes_[i]->scale(coefficient);
    const rectangle_t frameRectPos = shapes_[i]->getFrameRect();
    const double x = frameRect.pos.x + coefficient * (frameRectPos.pos.x - frameRect.pos.x);
    const double y = frameRect.pos.y + coefficient * (frameRectPos.pos.y - frameRect.pos.y);
    shapes_[i]->move({x, y});
  }
}

doguhan::CompositeShape::pointer_t &doguhan::CompositeShape::operator[](size_t index) const
{
  if (index >= size_)
  {
    throw std::out_of_range("Wrong index of shape!");
  }
  return shapes_[index];
}

size_t doguhan::CompositeShape::size() const
{
  return size_;
}

void doguhan::CompositeShape::remove(size_t index)
{
  if (size_ == 0)
  {
    throw std::underflow_error("Shape array is empty");
  }
  if (index >= size_)
  {
    throw std::out_of_range("Wrong index of shape!");
  }

  for (size_t i = index; i < size_ - 1; ++i)
  {
    shapes_[i] = std::move(shapes_[i + 1]);
  }
  size_--;
}
