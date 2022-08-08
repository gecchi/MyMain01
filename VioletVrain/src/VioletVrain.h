#ifndef VIOLETVRAIN_H_
#define VIOLETVRAIN_H_
#include "VioletVrain.h"
#include "GgafLibCommonHeader.h"

#undef P_CARETAKER
#define P_CARETAKER ((VioletVrain::VvCaretaker*)VioletVrain::VvCaretaker::_pCaretaker)

#define VV_MIKATA (0x01U)
#define VV_TEKI   (0x10U)


namespace VioletVrain {

//// forward declaration begin
class Jiki;
class Test01;
class Zako;
class TrialAndErrScene;
class VvCamera;
class VvCaretaker;
class VvSpacetime;
class VvUtil;
class World;
//// forward declaration end

}

#endif /*VIOLETVRAIN_H_*/
