#ifndef ORBITTRANSFORMCONTROLLER_H
#define ORBITTRANSFORMCONTROLLER_H

#include <QObject>
#include <QMatrix4x4>

#include <Qt3DCore/qtransform.h>

QT_BEGIN_NAMESPACE

class OrbitTransformController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Qt3DCore::QTransform* target READ target WRITE setTarget NOTIFY targetChanged)
    Q_PROPERTY(float radius READ radius WRITE setRadius NOTIFY radiusChanged)
    Q_PROPERTY(float angle READ angle WRITE setAngle NOTIFY angleChanged)
    Q_PROPERTY(QVector3D position READ getPosition WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(QVector3D scale READ getScale WRITE setScale NOTIFY scaleChanged)


public:
    OrbitTransformController(QObject *parent = 0);

    void setTarget(Qt3DCore::QTransform *target);
    Qt3DCore::QTransform *target() const;

    void setRadius(float radius);
    float radius() const;

    void setAngle(float angle);
    float angle() const;

    void setPosition(const QVector3D position);
    QVector3D getPosition() const;

    void setScale(const QVector3D scale);
    QVector3D getScale() const;

signals:
    void targetChanged();
    void radiusChanged();
    void angleChanged();
    void positionChanged();
    void scaleChanged();

protected:
    void updateMatrix();

private:
    Qt3DCore::QTransform *m_target;
    QMatrix4x4 m_matrix;
    float m_radius;
    float m_angle;
    QVector3D m_position;
    QVector3D m_scale;
};

QT_END_NAMESPACE

#endif // ORBITTRANSFORMCONTROLLER_H
