#include "DefaultSpriteTestActor.h"

#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/model/supporter/GgafDxTextureBlinker.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

DefaultSpriteTestActor::DefaultSpriteTestActor(const char* prm_name) :
        DefaultSpriteActor(prm_name, "_chk_DefaultSpriteTestModel", nullptr) {
    _class_name = "DefaultSpriteTestActor";
    setHitAble(false);
}

DefaultSpriteTestActor::~DefaultSpriteTestActor() {
}

