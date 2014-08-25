#include "DefaultSpriteSetTestActor.h"

#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/model/supporter/GgafDxTextureBlinker.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

DefaultSpriteSetTestActor::DefaultSpriteSetTestActor(const char* prm_name) :
        DefaultSpriteSetActor(prm_name, "_chk_DefaultSpriteSetTestModel", nullptr) {
    _class_name = "DefaultSpriteSetTestActor";
    setHitAble(false);
}

DefaultSpriteSetTestActor::~DefaultSpriteSetTestActor() {
}

