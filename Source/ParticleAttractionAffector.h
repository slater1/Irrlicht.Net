#pragma once

#include "stdafx.h"
#include "ParticleAffector.h"

using namespace irr;
using namespace System;
using namespace Irrlicht::Core;

namespace Irrlicht {
namespace Scene {

public ref class ParticleAttractionAffector : ParticleAffector
{
public:

    property bool AffectX { bool get(); void set(bool value); }
    property bool AffectY { bool get(); void set(bool value); }
    property bool AffectZ { bool get(); void set(bool value); }
    property bool Attract { bool get(); void set(bool value); }
    property Vector3Df^ Point { Vector3Df^ get(); void set(Vector3Df^ value); }

internal:

    static ParticleAttractionAffector^ Wrap(scene::IParticleAttractionAffector* ref);
    ParticleAttractionAffector(scene::IParticleAttractionAffector* ref);

    scene::IParticleAttractionAffector* m_ParticleAttractionAffector;
};

} // end namespace Scene
} // end namespace Irrlicht
