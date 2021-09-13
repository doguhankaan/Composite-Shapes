# Composite-Shapes

1. As an exception! All further work must follow the rules of work design and do not contain copied code, with the exception of a set of tests. Copy the source texts of task A1.

2. Move the shape classes to a separate namespace. The name of this space should be chosen to match the student's surname in lowercase (respectively, it coincides with the part of the name of the catalog with works up to a dot), for example, for Petrov Ivan, the catalog will be called petrov. ivan, respectively, the name of the namespace is petrov. This namespace should be maintained for all remaining papers in this semester.

3. Add the scale () method to the shape class, which performs isotropic scaling of the shape relative to its center with the specified coefficient.
If a triangle was implemented in the first work, scaling must be implemented for it as well.

4. Add the CompositeShape class, which should store a list of arbitrary shapes inside the array. In this work, the use of standard containers is not allowed, it is necessary to independently implement the storage of a set of shapes based on a dynamic array. The class must be placed in the files composite-shape.hpp and composite-shape.cpp.
For CompositeShape, scaling and moving work relative to the center of this object, which is taken as the center of the bounding rectangle.

5. Write tests that check:
* immutability of the width and height, as well as the area of the figure when moving;
* quadratic change in the area of the figure when zooming;
* presence and processing of incorrect parameters in functions;
* the correct operation of the composite figure, it must be remembered that it may be necessary to implement additional special methods in the class to ensure correct operation.
To write tests, you need to create a file test-main.cpp, in which to implement the tests.
The list above contains the absolute minimum of what needs to be tested. A well-executed work should check every non-trivial method or function added to the program. The ideal solution will contain 100% test coverage of the task implementation.
The demo program cre
