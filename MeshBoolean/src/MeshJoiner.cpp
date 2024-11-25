#include "MeshJoiner.h"
#include "Triangulation.h"
using namespace Geometry;

MeshJoiner::MeshJoiner()
{

}

MeshJoiner::~MeshJoiner()
{

}

std::vector<Triangulation> MeshJoiner::performTransformations(std::vector<Triangulation>& triangulations)
{
    Triangulation translationTriangulation;
    Triangulation rotationTriangulation;
    Triangulation reverseRotationTriangulation;
    Triangulation reverseTranslationTriangulation;

    Triangulation translationTriangulation2;
    Triangulation rotationTriangulation2;
    Triangulation reverseRotationTriangulation2;
    Triangulation reverseTranslationTriangulation2;

    Triangle triangle1 = triangulations[0].Triangles[0];
    Triangle triangle2 = triangulations[1].Triangles[0];

    Point firstNormalPoint = triangle1.Normal();
    RealPoint firstNormal = triangulations[0].getRealPoint(firstNormalPoint);

    Point secondNormalPoint = triangle2.Normal();
    RealPoint secondNormal = triangulations[1].getRealPoint(secondNormalPoint);


    double angle1 = firstNormal.getAngleBetweenNormalAndXAxis();
    double angle2 = secondNormal.getAngleBetweenNormalAndXAxis();

    // First Triangle avg
    Point firstTriangleP1 = triangle1.P1();
    Point firstTriangleP2 = triangle1.P2();
    Point firstTriangleP3 = triangle1.P3();
    //RealPoint of First Triangle avg
    RealPoint firstRealPoint1 = triangulations[0].getRealPoint(firstTriangleP1);
    RealPoint firstRealPoint2 = triangulations[0].getRealPoint(firstTriangleP2);
    RealPoint firstRealPoint3 = triangulations[0].getRealPoint(firstTriangleP3);
    Geometry::RealPoint avgFirstTriangle = triangle1.triangleCentroid(firstRealPoint1, firstRealPoint2, firstRealPoint3);

    translationTriangulation = transformer.translation(triangulations[0], -(avgFirstTriangle.X()), -(avgFirstTriangle.Y()), -(avgFirstTriangle.Z()));
    rotationTriangulation = transformer.rotationX(translationTriangulation, -angle1);

    // Second Triangle average
    Point secondTriangleP1 = triangle2.P1();
    Point secondTriangleP2 = triangle2.P2();
    Point secondTriangleP3 = triangle2.P3();
    //RealPoint of Second Triangle average
    RealPoint secondRealPoint1 = triangulations[1].getRealPoint(secondTriangleP1);
    RealPoint secondRealPoint2 = triangulations[1].getRealPoint(secondTriangleP2);
    RealPoint secondRealPoint3 = triangulations[1].getRealPoint(secondTriangleP3);
    Geometry::RealPoint avgSecondTriangle = triangle2.triangleCentroid(secondRealPoint1, secondRealPoint2, secondRealPoint3);


    translationTriangulation2 = transformer.translation(triangulations[1], -(avgSecondTriangle.X()), -(avgSecondTriangle.Y()), -(avgSecondTriangle.Z()));
    rotationTriangulation2 = transformer.rotationX(translationTriangulation2, -angle2);

    reverseRotationTriangulation = transformer.rotationX(translationTriangulation, angle1);
    reverseRotationTriangulation2 = transformer.rotationX(translationTriangulation2, angle1);

    reverseTranslationTriangulation = transformer.translation(reverseRotationTriangulation, (avgFirstTriangle.X()), (avgFirstTriangle.Y()), (avgFirstTriangle.Z()));
    reverseTranslationTriangulation2 = transformer.translation(reverseRotationTriangulation2, (avgFirstTriangle.X()), (avgFirstTriangle.Y()), (avgFirstTriangle.Z()));
    std::vector<Triangulation> resultTriangulation;
    resultTriangulation.push_back(reverseTranslationTriangulation);
    resultTriangulation.push_back(reverseTranslationTriangulation2);

    return resultTriangulation;
}
