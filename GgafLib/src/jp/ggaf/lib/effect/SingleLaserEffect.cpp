#include "jp/ggaf/lib/effect/SingleLaserEffect.h"

#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/lib/scene/DefaultSpacetime.h"
#include "jp/ggaf/lib/DefaultGod.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

SingleLaserEffect::SingleLaserEffect(const char* prm_effect_name) : GgafDxMeshSetEffect(prm_effect_name) {
}

SingleLaserEffect::~SingleLaserEffect() {
}

