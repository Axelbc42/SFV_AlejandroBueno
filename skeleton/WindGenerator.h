#pragma once
#include <cmath>
#include "ForceGenerator.h"

class WindGenerator : public ForceGenerator {
public:
    WindGenerator(const Vector3D& windVel, const Vector3D& center, float radius, float k1, float k2 = 0.0f);

    void updateForce(Particle* p, double dt) override;

protected:
    virtual Vector3D windAt(const Vector3D& pos) const { return wind; }   // para el tornado

    bool inside(const Vector3D& pos) const;

    Vector3D wind;      // velocidad del viento
    Vector3D pos;       // posiciond e la fuerza
    float dist;         // distancia de la fuerza
    float k1, k2;       // Componente de rozamiento de las particulas
    bool active = true;
};