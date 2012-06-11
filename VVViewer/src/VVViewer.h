#ifndef VVVIEWER_H_
#define VVVIEWER_H_

#include "GgafLibHeader.h"

#undef P_GOD
#define P_GOD ((VVViewer::VvvGod*)VVViewer::VvvGod::_pGod)
#undef P_UNIVERSE
#define P_UNIVERSE ((VVViewer::VvvUniverse*)(P_GOD->_pUniverse))

namespace VVViewer {
class VvvGod;
class VvvUniverse;
class VvvWorld;
class VvvCamera;
class VvvActor;
class VvvCamWorker;
}

#include "VvvGod.h"
#include "scene/VvvUniverse.h"
#include "scene/VvvUniverse/VvvWorld.h"
#include "actor/VvvCamera.h"
#include "actor/VvvActor.h"
#include "actor/CamWorker/VvvCamWorker.h"

#endif /*VVVIEWER_H_*/
