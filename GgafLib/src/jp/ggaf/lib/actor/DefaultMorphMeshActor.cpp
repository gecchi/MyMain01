#include "stdafx.h"
#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"

#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/lib/actor/ColliAABActor.h"
#include "jp/ggaf/lib/actor/ColliAAPrismActor.h"
#include "jp/ggaf/lib/actor/ColliSphereActor.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

DefaultMorphMeshActor::DefaultMorphMeshActor(const char* prm_name, const char* prm_model_id, GgafStatus* prm_pStat) :
    GgafDxMorphMeshActor(prm_name,
                         prm_model_id,
                         "DefaultMorphMeshEffect",
                         "DefaultMorphMeshTechnique",
                         prm_pStat,
                         NEW CollisionChecker3D(this) ),
_pScaler(new GgafDxScaler(this)) {

    _class_name = "DefaultMorphMeshActor";
    _pColliChecker = (CollisionChecker3D*)_pChecker;
}

void DefaultMorphMeshActor::drawHitArea() {
    ColliAABActor::get()->drawHitarea(_pColliChecker); ColliAAPrismActor::get()->drawHitarea(_pColliChecker); ColliSphereActor::get()->drawHitarea(_pColliChecker);
}


DefaultMorphMeshActor::~DefaultMorphMeshActor() {
    GGAF_DELETE(_pColliChecker);
    delete _pScaler;
}
