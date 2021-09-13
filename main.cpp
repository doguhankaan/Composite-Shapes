#include <iostream>
#include <memory>
#include <stdexcept>

#include "base-types.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "rectangle.hpp"

using namespace doguhan;

int main()
{
  const double COEFFICIENT = 22.2;
  const point_t NEWPOS{-9, 12};
  const double DX = 10.0, DY = 10.0;
  const point_t POINT_CIRCLE{3.4, 4.3};
  const double RADIUS = 3;
  std::shared_ptr<doguhan::Shape> circle_ptr(std::make_shared<doguhan::Circle>(RADIUS, POINT_CIRCLE));
  const point_t POINT_RECTANGLE{10, 11};
  const double WIDTH = 11.0, HEIGHT = 6.0;
  try
  {
    std::shared_ptr<doguhan::Shape> rectangle_ptr(std::make_shared<doguhan::Rectangle>(WIDTH, HEIGHT, POINT_RECTANGLE));
    doguhan::CompositeShape compositeShape;
    compositeShape.add(circle_ptr);
    compositeShape.add(rectangle_ptr);
    std::cout << "Composite Shape: ";
    compositeShape.print(std::cout);
    std::cout << "\nMoving the compositeShape to: "
              << "("
              << compositeShape.getFrameRect().pos.x + DX << ", " << NEWPOS.y + DY << ")";
    compositeShape.move(DX, DY);
    compositeShape.print(std::cout);
    std::cout << "\nMoving the rectangle (method two) to: "
              << "("
              << NEWPOS.x << ", " << NEWPOS.y << ")";
    compositeShape.move(NEWPOS);
    compositeShape.print(std::cout);
    std::cout << "Scaling compositeShape: ";
    compositeShape.scale(COEFFICIENT);
    compositeShape.print(std::cout);
  }
  catch (const std::invalid_argument &error)
  {
    std::cerr << error.what() << "\n";
    return 1;
  }
  catch (const std::out_of_range &error)
  {
    std::cerr << error.what() << "\n";
    return 1;
  }
  catch (const std::logic_error &error)
  {
    std::cerr << error.what() << "\n";
    return 1;
  }
  return 0;
}
