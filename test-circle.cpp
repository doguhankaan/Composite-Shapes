#define _USE_MATH_DEFINES

#include <cmath>
#include <stdexcept>

#include <boost/test/unit_test.hpp>

#include "base-types.hpp"
#include "circle.hpp"

BOOST_AUTO_TEST_SUITE(circle_test)

const double EPSILON = 0.0001;
const double RADIUS = 6.8;
const double X = 3.4;
const double Y = 5.3;
const double DX = 33;
const double DY = 15;
const double COEFFICIENT = 17;
const doguhan::point_t NEWPOINT{52, 81};

BOOST_AUTO_TEST_CASE(circleCorrectMoveDxDy)
{
  doguhan::Circle circle{RADIUS, {X, Y}};
  double circleArea = circle.getArea();
  circle.move(DX, DY);
  BOOST_CHECK_CLOSE(circle.getArea(), circleArea, EPSILON);
  BOOST_CHECK_CLOSE(circle.getFrameRect().width, 2*RADIUS, EPSILON);
  BOOST_CHECK_CLOSE(circle.getFrameRect().pos.x, X + DX, EPSILON);
  BOOST_CHECK_CLOSE(circle.getFrameRect().pos.y, Y + DY, EPSILON);
}

BOOST_AUTO_TEST_CASE(circleCorrectMoveNewPoint)
{
  doguhan::Circle circle{RADIUS, {X, Y}};
  double circleArea = circle.getArea();
  circle.move(NEWPOINT);
  BOOST_CHECK_CLOSE(circle.getArea(), circleArea, EPSILON);
  BOOST_CHECK_CLOSE(circle.getFrameRect().width, 2*RADIUS, EPSILON);
  BOOST_CHECK_CLOSE(circle.getFrameRect().pos.x, NEWPOINT.x, EPSILON);
  BOOST_CHECK_CLOSE(circle.getFrameRect().pos.y, NEWPOINT.y, EPSILON);
}

BOOST_AUTO_TEST_CASE(circleQuadraticAreaScale)
{
  doguhan::Circle circle{RADIUS, {X, Y}};
  double areaOld = circle.getArea();
  circle.scale(COEFFICIENT);
  double areaNew = circle.getArea();
  BOOST_CHECK_CLOSE(areaOld * COEFFICIENT * COEFFICIENT, areaNew, EPSILON);
  BOOST_CHECK_CLOSE(circle.getFrameRect().width, 2*RADIUS * COEFFICIENT, EPSILON);
  BOOST_CHECK_CLOSE(circle.getFrameRect().height, 2*RADIUS * COEFFICIENT, EPSILON);
  BOOST_CHECK_CLOSE(circle.getFrameRect().pos.x, X, EPSILON);
  BOOST_CHECK_CLOSE(circle.getFrameRect().pos.y, Y, EPSILON);
}

BOOST_AUTO_TEST_CASE(circleIncorrectParameters)
{
  doguhan::Circle circle{RADIUS, {X, Y}};
  BOOST_CHECK_THROW(doguhan::Circle circle1(-RADIUS, {X, Y}), std::invalid_argument);
  BOOST_CHECK_THROW(doguhan::Circle circle1(0, {X, Y}), std::invalid_argument);
  BOOST_CHECK_THROW(circle.scale(-COEFFICIENT), std::invalid_argument);
  BOOST_CHECK_THROW(circle.scale(0), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()
