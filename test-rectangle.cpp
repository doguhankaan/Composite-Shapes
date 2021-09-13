#include <stdexcept>
#include <boost/test/unit_test.hpp>

#include "base-types.hpp"
#include "rectangle.hpp"

BOOST_AUTO_TEST_SUITE(rectangle_test)

const double EPSILON = 0.00001;
const double WIDTH = 4.3;
const double HEIGHT = 5.7;
const double X = 3.4;
const double Y = 5.3;
const double DX = 33;
const double DY = 15;
const double COEFFICIENT = 17;
const doguhan::point_t NEWPOINT{ 52, 81 };

BOOST_AUTO_TEST_CASE(rectangleCorrectMoveDxDy)
{
  doguhan::Rectangle rectangle{WIDTH, HEIGHT, {X, Y}};

  double rectangleArea = rectangle.getArea();
  rectangle.move(DX, DY);
  BOOST_CHECK_CLOSE(rectangle.getArea(), rectangleArea, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, WIDTH, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, HEIGHT, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, X + DX, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, Y + DY, EPSILON);
}

BOOST_AUTO_TEST_CASE(circleCorrectMoveNewPoint)
{
  doguhan::Rectangle rectangle{WIDTH, HEIGHT, {X, Y}};

  double rectangleArea = rectangle.getArea();
  rectangle.move(NEWPOINT);
  BOOST_CHECK_CLOSE(rectangle.getArea(), rectangleArea, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, WIDTH, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, HEIGHT, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, NEWPOINT.x, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, NEWPOINT.y, EPSILON);
}

BOOST_AUTO_TEST_CASE(rectangleQuadraticAreaScale)
{
  doguhan::Rectangle rectangle{WIDTH, HEIGHT, {X, Y}};

  double areaOld = rectangle.getArea();
  rectangle.scale(COEFFICIENT);
  double areaNew = rectangle.getArea();
  BOOST_CHECK_CLOSE(areaOld * COEFFICIENT * COEFFICIENT, areaNew, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, WIDTH * COEFFICIENT,
                    EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, HEIGHT * COEFFICIENT,
                    EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, X, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, Y, EPSILON);
}

BOOST_AUTO_TEST_CASE(circleIncorrectParameters)
{
  doguhan::Rectangle rectangle{WIDTH, HEIGHT, {X, Y}};

  BOOST_CHECK_THROW(doguhan::Rectangle rectangle1(0, 0, {X, Y}),
                    std::invalid_argument);
  BOOST_CHECK_THROW(doguhan::Rectangle rectangle1(-WIDTH, -HEIGHT, {X, Y}),
                    std::invalid_argument);
  BOOST_CHECK_THROW(rectangle.scale(-COEFFICIENT), std::invalid_argument);
  BOOST_CHECK_THROW(rectangle.scale(0), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()
