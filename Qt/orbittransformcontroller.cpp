#include "orbittransformcontroller.h"

#include <Qt3DCore/qtransform.h>

QT_BEGIN_NAMESPACE

OrbitTransformController::OrbitTransformController(QObject *parent)
    : QObject(parent)
    , m_target(nullptr)
    , m_matrix()
    , m_radius(1.0f)
    , m_angle(0.0f)
    , m_position(QVector3D(0.0f,0.0f,0.0f))
{
}

void OrbitTransformController::setTarget(Qt3DCore::QTransform *target)
{
    if (m_target != target) {
        m_target = target;
        emit targetChanged();
    }
}

Qt3DCore::QTransform *OrbitTransformController::target() const
{
    return m_target;
}

void OrbitTransformController::setRadius(float radius)
{
    if (!qFuzzyCompare(radius, m_radius)) {
        m_radius = radius;
        updateMatrix();
        emit radiusChanged();
    }
}

float OrbitTransformController::radius() const
{
    return m_radius;
}

void OrbitTransformController::setAngle(float angle)
{
    if (!qFuzzyCompare(angle, m_angle)) {
        m_angle = angle;
        updateMatrix();
        emit angleChanged();
    }
}

float OrbitTransformController::angle() const
{
    return m_angle;
}

void OrbitTransformController::setPosition(const QVector3D position)
{
    if (!qFuzzyCompare(position, m_position)) {
        m_position = position;
        updateMatrix();
        emit positionChanged();
    }
}
QVector3D OrbitTransformController::getPosition() const
{
    return m_position;
}

void OrbitTransformController::setScale(const QVector3D scale)
{
    if (!qFuzzyCompare(scale, m_scale)) {
        m_scale = scale;
        updateMatrix();
        emit scaleChanged();
    }
}
QVector3D OrbitTransformController::getScale() const
{
    return m_position;
}

void OrbitTransformController::updateMatrix()
{
    m_matrix.setToIdentity();
    m_matrix.rotate(m_angle, QVector3D(0.0f, 1.0f, 0.0f));
    m_matrix.translate(m_position);
    m_matrix.scale(m_scale);
    m_target->setMatrix(m_matrix);
}

QT_END_NAMESPACE
