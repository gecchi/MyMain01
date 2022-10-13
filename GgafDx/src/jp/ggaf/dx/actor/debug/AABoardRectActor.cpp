#include "jp/ggaf/dx/actor/debug/AABoardRectActor.h"

#include "jp/ggaf/dx/Config.h"
#include "jp/ggaf/dx/util/Util.h"


using namespace GgafDx;

AABoardRectActor::AABoardRectActor(const char* prm_name,
                                   Checker* prm_pChecker) :
                                BoardActor(prm_name,
                                     CONFIG::COLI_AABOARDRECT_MODEL.c_str(),
                                     "DefaultBoardEffect",
                                     "DefaultBoardTechnique",
                                     prm_pChecker) {
    _class_name = "AABoardRectActor";
    _align = ALIGN_LEFT;
    _valign = VALIGN_TOP;
}

//void AABoardRectActor::processDraw() {
//    GeometricActor::setWorldTransformScRzMxyz(this);
//    _pD3DXMeshModel->draw(this);
//}

void AABoardRectActor::drawRect(coord prm_x1, coord prm_y1, coord prm_x2, coord prm_y2) {
    //_TRACE_("drawBox ("<<prm_x1<<","<<prm_y1<<","<<prm_z1<<","<<prm_x2<<","<<prm_y2<<","<<prm_z2<<")");
    _sx = (prm_x2 - prm_x1);
    _sy = (prm_y2 - prm_y1);
    _x = prm_x1;
    _y = prm_y1;
    //UTIL::setWorldMatrix_ScRzMv(this, _matWorld);
    processDraw();
}

AABoardRectActor::~AABoardRectActor() {
}
