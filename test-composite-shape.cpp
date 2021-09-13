#include <cmath>
#include <memory>
#include <stdexcept>
#include <boost/test/unit_test.hpp>
#include "base-types.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "rectangle.hpp"

BOOST_AUTO_TEST_SUITE(composite_shape_test)

struct CompositeFixture
{
  const double EPSILON = 0.00001;
  const double RADIUS = 6.8;
  const double WIDTH = 7;
  const double HEIGHT = 4;
  const double DX = 33;
  const double DY = 15;
  const double COEFFICIENT = 17;
  const int SIZE = 3;
  const int INDEX = 10;
  const doguhan::point_t NEW_POINT = {52, 81};
  const doguhan::point_t CIRCLE_CENTRE = {6.1, 7.3};
  const doguhan::point_t RECTANGLE_CENTRE = {1.4, 3.5};

  CompositeFixture()
  {
    compositeShape.add(firstShape);
    compositeShape.add(secondShape);
  }

  std::shared_ptr<doguhan::Shape> firstShape = std::make_shared<doguhan::Rectangle>(WIDTH, HEIGHT, RECTANGLE_CENTRE);
  std::shared_ptr<doguhan::Shape> secondShape = std::make_shared<doguhan::Circle>(RADIUS, CIRCLE_CENTRE);
  doguhan::CompositeShape compositeShape;
};

BOOST_FIXTURE_TEST_CASE(CompositeShapeCopyConstructor, CompositeFixture)
{
  doguhan::CompositeShape otherCompShape(compositeShape);
  BOOST_CHECK(compositeShape[0]->getFrameRect().height == otherCompShape[0]->getFrameRect().height);
  BOOST_CHECK(compositeShape[0]->getFrameRect().width == otherCompShape[0]->getFrameRect().width);
  BOOST_CHECK(compositeShape[0]->getFrameRect().pos.x == otherCompShape[0]->getFrameRect().pos.x);
  BOOST_CHECK(compositeShape[0]->getFrameRect().pos.y == otherCompShape[0]->getFrameRect().pos.y);

  BOOST_CHECK(compositeShape[1]->getFrameRect().height == otherCompShape[1]->getFrameRect().height);
  BOOST_CHECK(compositeShape[1]->getFrameRect().width == otherCompShape[1]->getFrameRect().width);
  BOOST_CHECK(compositeShape[1]->getFrameRect().pos.x == otherCompShape[1]->getFrameRect().pos.x);
  BOOST_CHECK(compositeShape[1]->getFrameRect().pos.y == otherCompShape[1]->getFrameRect().pos.y);
}

BOOST_FIXTURE_TEST_CASE(CompositeShapeMoveConstructor, CompositeFixture)
{
  doguhan::CompositeShape otherCompShape(std::move(compositeShape));
  BOOST_CHECK_CLOSE(otherCompShape[1]->getFrameRect().height, 2*RADIUS, EPSILON);
  BOOST_CHECK(otherCompShape[1]->getFrameRect().pos.x == CIRCLE_CENTRE.x);
  BOOST_CHECK(otherCompShape[1]->getFrameRect().pos.y == CIRCLE_CENTRE.y);
  BOOST_CHECK_THROW(compositeShape[1], std::out_of_range);

}

BOOST_FIXTURE_TEST_CASE(getAreaTest, CompositeFixture)
{
  double expectedArea = compositeShape[0]->getArea() + compositeShape[1]->getArea();
  BOOST_CHECK(compositeShape.getArea() == expectedArea);
}

BOOST_FIXTURE_TEST_CASE(CompositeShapeGetFrame, CompositeFixture)
{
  double maxX = std::max(RECTANGLE_CENTRE.x + WIDTH / 2, CIRCLE_CENTRE.x + RADIUS);
  double minX = std::min(RECTANGLE_CENTRE.x - WIDTH / 2, CIRCLE_CENTRE.x - RADIUS);
  double maxY = std::max(RECTANGLE_CENTRE.y + HEIGHT / 2, CIRCLE_CENTRE.y + RADIUS);
  double minY = std::min(RECTANGLE_CENTRE.y - HEIGHT / 2, CIRCLE_CENTRE.y - RADIUS);

  double frameWidth = maxX - minX;
  double frameHeight = maxY - minY;

  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().height, frameHeight, EPSILON);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().width, frameWidth, EPSILON);
}

BOOST_FIXTURE_TEST_CASE(CompositeShapeConstantAreaAndFrameMovingDxDy, CompositeFixture)
{
  const doguhan::rectangle_t tempRectangle = compositeShape.getFrameRect();
  double area = compositeShape.getArea();
  compositeShape.move(DX, DY);
  const doguhan::rectangle_t tempRectangleAfter = compositeShape.getFrameRect();
  BOOST_CHECK_CLOSE(tempRectangle.width, tempRectangleAfter.width, EPSILON);
  BOOST_CHECK_CLOSE(tempRectangle.height, tempRectangleAfter.height, EPSILON);
  BOOST_CHECK_CLOSE(compositeShape.getArea(), area, EPSILON);
}

BOOST_FIXTURE_TEST_CASE(CompositeShapeConstantAreaAndFrameMovingNewPoint, CompositeFixture)
{
  const doguhan::rectangle_t tempRectangle = compositeShape.getFrameRect();
  double area = compositeShape.getArea();
  compositeShape.move(NEW_POINT);
  const doguhan::rectangle_t tempRectangleAfter = compositeShape.getFrameRect();
  BOOST_CHECK_CLOSE(tempRectangle.width, tempRectangleAfter.width, EPSILON);
  BOOST_CHECK_CLOSE(tempRectangle.height, tempRectangleAfter.height, EPSILON);
  BOOST_CHECK_CLOSE(compositeShape.getArea(), area, EPSILON);
}

BOOST_FIXTURE_TEST_CASE(CompositeShapeAreaQuadraticScale, CompositeFixture)
{
  const doguhan::rectangle_t rectCompositeShape = compositeShape.getFrameRect();
  const double areaCompositeShape = compositeShape.getArea();
  double rectangleX = compositeShape[0]->getFrameRect().pos.x;
  double rectangleY = compositeShape[0]->getFrameRect().pos.y;
  double circleX = compositeShape[1]->getFrameRect().pos.x;
  double circleY = compositeShape[1]->getFrameRect().pos.y;

  const double rectangleDistanceToCSCenterOld = sqrt(std::pow((compositeShape.getFrameRect().pos.x - rectangleX), 2)
      + std::pow((compositeShape.getFrameRect().pos.y - rectangleY), 2));
  const double circleDistanceToCSCenterOld = sqrt(std::pow((compositeShape.getFrameRect().pos.x - circleX), 2)
      + std::pow((compositeShape.getFrameRect().pos.y - circleY), 2));
  compositeShape.scale(COEFFICIENT);
  BOOST_CHECK_CLOSE(compositeShape.getArea(), areaCompositeShape * COEFFICIENT * COEFFICIENT, EPSILON);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().width, rectCompositeShape.width * COEFFICIENT, EPSILON);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().height, rectCompositeShape.height * COEFFICIENT, EPSILON);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().pos.x, rectCompositeShape.pos.x, EPSILON);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().pos.y, rectCompositeShape.pos.y, EPSILON);
  rectangleX = compositeShape[0]->getFrameRect().pos.x;
  rectangleY = compositeShape[0]->getFrameRect().pos.y;
  circleX = compositeShape[1]->getFrameRect().pos.x;
  circleY = compositeShape[1]->getFrameRect().pos.y;

  const double rectangleDistanceToCSCenterNew = sqrt(pow((compositeShape.getFrameRect().pos.x - rectangleX), 2)
      + std::pow((compositeShape.getFrameRect().pos.y - rectangleY), 2));
  const double circleDistanceToCSCenterNew = sqrt(pow((compositeShape.getFrameRect().pos.x - circleX), 2)
      + std::pow((compositeShape.getFrameRect().pos.y - circleY), 2));
  BOOST_CHECK_CLOSE(rectangleDistanceToCSCenterOld * COEFFICIENT, rectangleDistanceToCSCenterNew, EPSILON);
  BOOST_CHECK_CLOSE(circleDistanceToCSCenterOld * COEFFICIENT, circleDistanceToCSCenterNew, EPSILON);
}

BOOST_FIXTURE_TEST_CASE(CompositeShapeInvalidParameters, CompositeFixture)
{
  BOOST_CHECK_THROW(compositeShape.scale(-COEFFICIENT), std::invalid_argument);
  BOOST_CHECK_THROW(compositeShape.scale(0.0), std::invalid_argument);
  BOOST_CHECK_THROW(compositeShape[INDEX], std::out_of_range);
  BOOST_CHECK_THROW(compositeShape.remove(INDEX), std::out_of_range);
  BOOST_CHECK_THROW(compositeShape.remove(INDEX), std::out_of_range);
}

BOOST_FIXTURE_TEST_CASE(CompositeShapeAddNullShape, CompositeFixture)
{
  BOOST_CHECK_THROW(compositeShape.add(nullptr), std::invalid_argument);
}

BOOST_FIXTURE_TEST_CASE(CompositeShapeToItSelf, CompositeFixture)
{
  std::shared_ptr<doguhan::CompositeShape> testShape(std::make_shared<doguhan::CompositeShape>(compositeShape));
  BOOST_CHECK_THROW(testShape->add(testShape), std::invalid_argument);
}

BOOST_FIXTURE_TEST_CASE(CompositeShapeAddingSameShape, CompositeFixture)
{

  BOOST_CHECK_THROW(compositeShape.add(secondShape), std::invalid_argument);
}

BOOST_FIXTURE_TEST_CASE(CompositeShapeRemoveShape, CompositeFixture)
{
  doguhan::CompositeShape removeShape = compositeShape;
  compositeShape.remove(0);
  BOOST_CHECK(removeShape[1] == compositeShape[0]);
  BOOST_CHECK(removeShape.size() - 1 == compositeShape.size());
  BOOST_CHECK_NO_THROW(removeShape.remove(1));
  BOOST_CHECK_NO_THROW(removeShape.remove(0));
  BOOST_CHECK_EQUAL(removeShape.size(), 0);
}

BOOST_AUTO_TEST_SUITE_END()
