#include "jp/ggaf/lib/actor/CubeMapMeshActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#ifdef MY_DEBUG
#include "jp/ggaf/lib/actor/ColliAABoxActor.h"
#include "jp/ggaf/lib/actor/ColliAAPrismActor.h"
#include "jp/ggaf/lib/actor/ColliAAPyramidActor.h"
#include "jp/ggaf/lib/actor/ColliSphereActor.h"
#endif


using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

CubeMapMeshActor::CubeMapMeshActor(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
    GgafDxCubeMapMeshActor(prm_name,
                           prm_model,
                           "CubeMapMeshEffect",
                           "CubeMapMeshTechnique",
                           prm_pStat,
                           UTIL::createChecker(this) ) {
    _class_name = "CubeMapMeshActor";
    _pColliChecker = (CollisionChecker3D*)_pChecker;
}

void CubeMapMeshActor::drawHitArea() {
#ifdef MY_DEBUG
    ColliAABoxActor::get()->drawHitarea(_pColliChecker); ColliAAPrismActor::get()->drawHitarea(_pColliChecker); ColliAAPyramidActor::get()->drawHitarea(_pColliChecker); ColliSphereActor::get()->drawHitarea(_pColliChecker);
#endif
}

CubeMapMeshActor::~CubeMapMeshActor() {
    GGAF_DELETE(_pColliChecker);
}
