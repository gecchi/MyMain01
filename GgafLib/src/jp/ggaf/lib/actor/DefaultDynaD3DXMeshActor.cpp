#include "jp/ggaf/lib/actor/DefaultDynaD3DXMeshActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"



using namespace GgafLib;

DefaultDynaD3DXMeshActor::DefaultDynaD3DXMeshActor(const char* prm_name, const char* prm_model) :
    GgafDx::DynaD3DXMeshActor(prm_name,
                             prm_model,
                             "DefaultMeshEffect",
                             "DefaultMeshTechnique",
                             UTIL::createChecker(this) ) {
    _class_name = "DefaultDynaD3DXMeshActor";
    _pColliChecker = (CollisionChecker*)_pChecker;
}

void DefaultDynaD3DXMeshActor::drawHitArea() {
#ifdef MY_DEBUG
    CollisionChecker::drawHitArea(_pColliChecker);
#endif
}


DefaultDynaD3DXMeshActor::~DefaultDynaD3DXMeshActor() {
    GGAF_DELETE(_pColliChecker);
}
