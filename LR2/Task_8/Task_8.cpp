#include <iostream>
#include <cmath>

double findSideOfTriangle(double x1, double y1, double x2, double y2) {
    double side = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    return side;
}

double findPerimeter(double a, double b, double c) {
    double perimeter = a + b + c;
    return perimeter;
}

double findAreaByHeron(double a, double b, double c, double perimeter) {
    double semiperimeter = perimeter / 2;
    double area = sqrt(semiperimeter * (semiperimeter - a) * (semiperimeter - b) * (semiperimeter - c));
    return area;
}

double findAreaByHeight(double side, double height) {
    double area = side * height / 2;
    return area;
}

double findAreaByLittleRadius(double littleRadius, double perimeter) {
    double area = littleRadius * perimeter / 2;
    return area;
}

double findHeightOfTriangle(double side, double area) {
    double height = 2 * area / side;
    return height;
}

double findMedianOfTrinagle(double side1, double side2, double side3) {
    double median = 0.5 * sqrt(2 * pow(side2, 2) + 2 * pow(side3, 2) - pow(side1, 2));
    return median;
}

double findAngle(double side, double bigRadius) {
    double angle = asin(side / (2 * bigRadius));
    return angle;
}

double convertToDegrees(double angle) {
    double angleInDegrees = angle * 180 / 3.14;
    return angleInDegrees;
}

double findBisector(double height, double angle1, double angle2) {
    double bisector = height / (cos((angle2 - angle1) / 2));
    return bisector;
}

double findLittleRadius(double area, double perimeter) {
    double littleRadius = 2 * area / perimeter;
    return littleRadius;
}

double findBigRadius(double area, double a, double b, double c) {
    double bigRadius = a * b * c / (4 * area);
    return bigRadius;
}

double findAreaOfCircle(double radius) {
    double areaOfCircle = M_PI * pow(radius, 2);
    return areaOfCircle;
}

double findLengthOfCircle(double radius) {
    double lengthOfCircle = 2 * M_PI * radius;
    return lengthOfCircle;
}

int main() {
    double x1, x2, x3, y1, y2, y3;

    std::cout << "Введите x1, x2, x3: ";
    std::cin >> x1 >> x2 >> x3;
    std::cout << "Введите y1, y2, y3: ";
    std::cin >> y1 >> y2 >> y3;

    double a = findSideOfTriangle(x1, y1, x2, y2);
    double b = findSideOfTriangle(x1, y1, x3, y3);
    double c = findSideOfTriangle(x2, y2, x3, y3);

    double perimeter = findPerimeter(a, b, c);
    double areaByHeron = findAreaByHeron(a, b, c, perimeter);

    double height_a = findHeightOfTriangle(a, areaByHeron);
    double height_b = findHeightOfTriangle(b, areaByHeron);
    double height_c = findHeightOfTriangle(c, areaByHeron);

    double areaByHeight = findAreaByHeight(a, height_a);

    double median_a = findMedianOfTrinagle(a, b, c);
    double median_b = findMedianOfTrinagle(b, a, c);
    double median_c = findMedianOfTrinagle(c, a, b);

    double littleRadius = findLittleRadius(areaByHeight, perimeter);
    double bigRadius = findBigRadius(areaByHeight, a, b, c);

    double alpha = findAngle(a, bigRadius);
    double beta = findAngle(b, bigRadius);
    double gamma = findAngle(c, bigRadius);

    double bisector_a = findBisector(height_a, beta, gamma);
    double bisector_b = findBisector(height_b, alpha, gamma);
    double bisector_c = findBisector(height_c, beta, alpha);

    double areaOfLittleCircle = findAreaOfCircle(littleRadius);
    double areaOfBigCircle = findAreaOfCircle(bigRadius);
    double lengthOfLittleCircle = findLengthOfCircle(littleRadius);
    double lengthOfBigCircle = findLengthOfCircle(bigRadius);

    double areaByLittleRadius = findAreaByLittleRadius(littleRadius, perimeter);

    std::cout << "1. Стороны треугольника:\nA = " << a << " B = " << b << " C = " << c << std::endl;
    std::cout << "2. Длины высот треугольника:\nH_a = " << height_a << " H_b = " << height_b << " H_c = " << height_c << std::endl;
    std::cout << "3. Длины медиан треугольника:\nm_a = " << median_a << " m_b = " << median_b << " m_c = " << median_c << std::endl;
    std::cout << "4. Длины биссектрис треугольника:\nb_a = " << bisector_a << " b_b = " << bisector_b << " b_c = " << bisector_c << std::endl;
    std::cout << "5. Значения углов треугольника:" << std::endl;
    std::cout << "\tЗначения углов в радианах: alpha = " << alpha << " beta = " << beta << " gamma = " << gamma << std::endl;
    std::cout << "\tЗначения углов в градусах: alpha = " << convertToDegrees(alpha) << " градусов beta = " << convertToDegrees(beta);
    std::cout << " градусов gamma = " << convertToDegrees(gamma) << std::endl;
    std::cout << "6. Радиусы вписанной и описанной окружностей: \nr = " << littleRadius << " R = " << bigRadius << std::endl;
    std::cout << "7. Площади и длины вписанной и описанной окружностей: " << std::endl;
    std::cout << "\tПлощадь вписанной окружности = " << areaOfLittleCircle << " длина вписанной окружности = " << lengthOfLittleCircle << std::endl;
    std::cout << "\tПлощадь описанной окружности = " << areaOfBigCircle << " длина описанной окружности = " << lengthOfBigCircle << std::endl;
    std::cout << "8. Площадь и периметр треугольника:\n" << "\tP = " << perimeter << std::endl;
    std::cout << "\tПлощадь через формулу Герона = " << areaByHeron << std::endl;
    std::cout << "\tПлощадь через высоту треугольника = " << areaByHeight << std::endl;
    std::cout << "\tПлощадь через радиус вписанной окружности = " << areaByLittleRadius << std::endl;
}