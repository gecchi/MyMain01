#include "stdafx.h"
#include "jp/ggaf/lib/actor/SpriteMeshSetActor.h"

#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/lib/actor/ColliAABActor.h"
#include "jp/ggaf/lib/actor/ColliAAPrismActor.h"
#include "jp/ggaf/lib/actor/ColliSphereActor.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

SpriteMeshSetActor::SpriteMeshSetActor(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
    GgafDxSpriteMeshSetActor(prm_name,
                             prm_model,
                             prm_pStat,
                             NEW CollisionChecker3D(this) ) {

    _class_name = "SpriteMeshSetActor";
    _pColliChecker = (CollisionChecker3D*)_pChecker;
}

void SpriteMeshSetActor::drawHitArea() {
    ColliAABActor::get()->drawHitarea(_pColliChecker); ColliAAPrismActor::get()->drawHitarea(_pColliChecker); ColliSphereActor::get()->drawHitarea(_pColliChecker);
}

SpriteMeshSetActor::~SpriteMeshSetActor() {
    GGAF_DELETE(_pColliChecker);
}

