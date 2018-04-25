#ifndef VIOLETVRAIN_H_
#define VIOLETVRAIN_H_
#include "VioletVrain.h"
#include "GgafLibCommonHeader.h"

#undef P_GOD
#define P_GOD ((VioletVrain::VvGod*)VioletVrain::VvGod::_pGod)

#define VV_MIKATA (0x01U)
#define VV_TEKI   (0x10U)


namespace VioletVrain {

//// forward declaration begin
class Jiki;
class Test01;
class TrialAndErrScene;
class VvCamera;
class VvGod;
class VvSpacetime;
class VvUtil;
class World;
//// forward declaration end

}

#endif /*VIOLETVRAIN_H_*/