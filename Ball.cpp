#include "Ball.hpp"
#include <cmath>
#include "Point.h"
#include "Velocity.h"
#include "Color.h"



Ball::Ball(Point center, Velocity velocity, double radius, Color color, bool collision) {
        ballCenter = center;
        ballVelo = velocity;
        ballRad = radius;
        ballColor = color;
        isCollidable = collision;
    }

/**
 * Задает скорость объекта
 * @param velocity новое значение скорости
 */
void Ball::setVelocity(const Velocity& velocity) {
    ballVelo = velocity;
}

/**
 * @return скорость объекта
 */
Velocity Ball::getVelocity() const {
    return ballVelo;
}

/**
 * @brief Выполняет отрисовку объекта
 * @details объект Ball абстрагирован от конкретного
 * способа отображения пикселей на экране. Он "знаком"
 * лишь с интерфейсом, который предоставляет Painter
 * Рисование выполняется путем вызова painter.draw(...)
 * @param painter контекст отрисовки
 */
void Ball::draw(Painter& painter) const {
    painter.draw(ballCenter, ballRad, ballColor);
}

/**
 * Задает координаты центра объекта
 * @param center новый центр объекта
 */
void Ball::setCenter(const Point& center) {
    ballCenter = center;
}

/**
 * @return центр объекта
 */
Point Ball::getCenter() const {
    // TODO: место для доработки
    return ballCenter;
}

/**
 * @brief Возвращает радиус объекта
 * @details обратите внимание, что метод setRadius()
 * не требуется
 */
double Ball::getRadius() const {
    return ballRad;
}

/**
 * @brief Возвращает массу объекта
 * @details В нашем приложении считаем, что все шары
 * состоят из одинакового материала с фиксированной
 * плотностью. В этом случае масса в условных единицах
 * эквивалентна объему: PI * radius^3 * 4. / 3.
 */
double Ball::getMass() const {
    return M_PI*pow(ballRad, 3) *4.0/3.0;
}

Color Ball::getColor() const {
    return ballColor;
}

bool Ball::getCollision() const {
    return isCollidable;
}