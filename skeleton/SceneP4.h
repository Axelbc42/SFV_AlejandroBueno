#pragma once
#include "Scene.h"
#include "AnchoredSpringFG.h"
#include "BuoyancyForceGenerator.h"
#include "SpringForceGenerator.h"
#include "RubberBandFG.h"

#include "ParticleForceRegistry.h"
#include "GravityGenerator.h"

class SceneP4 : public Scene {
public:
    explicit SceneP4(std::string name) : Scene(std::move(name)) {}

    void init() override {
        _p1 = new Particle(Vector3D(-15, 5, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0));
        _anchored = new AnchoredSpringFG(0.1, 10, Vector3D(-15, 10, 0));
        _gravityG = new GravityGenerator(Vector3D(0, -9.8, 0));
        _registry.add(_p1, _anchored);

        _p2 = new Particle(Vector3D(50, 10, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0));
        _p3 = new Particle(Vector3D(20, 10, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0));
        _spring2 = new SpringForceGenerator(0.1, 20, _p2);
        _spring3 = new SpringForceGenerator(0.1, 20, _p3);

        _p4 = new Particle(Vector3D(50, -10, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0));
        _p5 = new Particle(Vector3D(20, -10, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0));
        _spring4 = new RubberBandFG(0.1, 20, _p4);
        _spring5 = new RubberBandFG(0.1, 20, _p5);

        _registry.add(_p3, _spring2);
        _registry.add(_p2, _spring3);
        _registry.add(_p5, _spring4);
        _registry.add(_p4, _spring5);

		_p6 = new Particle(Vector3D(0, -15, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0), 1, 1, 0.0, Vector4(1, 1, 0, 1), 0.99, SPHERE);
		_buoyancy = new BuoyancyForceGenerator(1, 1, 1000, new Particle(Vector3D(0, -20, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0), 1, 10, 0.0, Vector4(0, 0, 1, 1), 0.99, PLANE));
		_registry.add(_p6, _buoyancy);
		_registry.add(_p6, _gravityG);
    }

    void update(double dt) override {
        _registry.updateForces(dt);
        _p1->integrateEulerSI(dt);
        _p2->integrateEulerSI(dt);
        _p3->integrateEulerSI(dt);
        _p4->integrateEulerSI(dt);
        _p5->integrateEulerSI(dt);
		_p6->integrateEulerSI(dt);

    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {
        switch (key) {
			// Activar/desactivar gravedad
            case 'g':
                if (!gravityActive) {
                    _registry.add(_p1, _gravityG);
                    std::cout << "Gravedad activada" << std::endl;
                    gravityActive = true;
                }
                else {
                    _registry.remove(_p1, _gravityG);
                    std::cout << "Gravedad desactivada" << std::endl;
                    gravityActive = false;
                }

			    break;
                // Subir la contante del muelle
            case '+':
                _K = _K * 2;
			    _anchored->setK(_K);
                std::cout << "Nueva constante del muelle = " << _K << std::endl;
                break;

                // Bajar la contante del muelle
            case '-':
			    _K = _K / 2;
			    _anchored->setK(_K);
                std::cout << "Nueva constante del muelle = " << _K << std::endl;
                break;
        default:
            break;
        }
    }

    void cleanup() override {
    }

private:
    Particle* _p1 = nullptr;
    AnchoredSpringFG* _anchored = nullptr;
    GravityGenerator* _gravityG;
    bool gravityActive = false;
	double _K = 0.1;

    Particle* _p2 = nullptr;
    Particle* _p3 = nullptr;
    SpringForceGenerator* _spring2 = nullptr;
    SpringForceGenerator* _spring3 = nullptr;

    Particle* _p4 = nullptr;
    Particle* _p5 = nullptr;
    RubberBandFG* _spring4 = nullptr;
    RubberBandFG* _spring5 = nullptr;

	BuoyancyForceGenerator* _buoyancy = nullptr;
    Particle* _p6 = nullptr;

    ParticleForceRegistry _registry;
};
