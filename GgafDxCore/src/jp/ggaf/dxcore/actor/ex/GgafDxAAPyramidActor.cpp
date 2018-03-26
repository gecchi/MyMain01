#include "jp/ggaf/dxcore/actor/ex/GgafDxAAPyramidActor.h"

#include "jp/ggaf/dxcore/GgafDxConfig.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;

std::map<int, GgafDxAAPyramidActor::RotPosPyramid> GgafDxAAPyramidActor::pos2r;

GgafDxAAPyramidActor::GgafDxAAPyramidActor(const char* prm_name, GgafStatus* prm_pStat,
                                   GgafDxChecker* prm_pChecker) :

                                   GgafDxMeshActor(prm_name,
                                                   CONFIG::COLI_AAPYRAMID_MODEL.c_str(),
                                                   "DefaultMeshEffect",
                                                   "DefaultMeshTechnique",
                                                   prm_pStat,
                                                   prm_pChecker) {
    //_obj_class |= Obj_GgafDxAAPyramidActor;
    _class_name = "GgafDxAAPyramidActor";
    static volatile bool is_init = GgafDxAAPyramidActor::initStatic(); //静的メンバ初期化
}

bool GgafDxAAPyramidActor::initStatic() {
    //基本となるプリズム型の姿勢
    //                 ^
    //              y+ |    ﾍ
    //                 |   / z+
    //                 |  /
    //                 | /
    //            |-_  |/             x+
    //   ---------|＼--+--------------->
    //            | /`/
    //            |/ / ＼
    //            +-/-----`
    //             /   |
    //            /    |
    //           /     |
    //                 |
    //                 |
    //                                                              rx      rz       ry
    GgafDxAAPyramidActor::pos2r[POS_PYRAMID_NNN] = RotPosPyramid(D0ANG , D0ANG  , D0ANG   );
    GgafDxAAPyramidActor::pos2r[POS_PYRAMID_NNP] = RotPosPyramid(D0ANG , D0ANG  , D90ANG  );
    GgafDxAAPyramidActor::pos2r[POS_PYRAMID_NPN] = RotPosPyramid(D0ANG , D180ANG, D90ANG  );
    GgafDxAAPyramidActor::pos2r[POS_PYRAMID_NPP] = RotPosPyramid(D0ANG , D180ANG, D180ANG );
    GgafDxAAPyramidActor::pos2r[POS_PYRAMID_PNN] = RotPosPyramid(D0ANG , D0ANG  , D270ANG );
    GgafDxAAPyramidActor::pos2r[POS_PYRAMID_PNP] = RotPosPyramid(D0ANG , D0ANG  , D180ANG );
    GgafDxAAPyramidActor::pos2r[POS_PYRAMID_PPN] = RotPosPyramid(D0ANG , D180ANG, D0ANG   );
    GgafDxAAPyramidActor::pos2r[POS_PYRAMID_PPP] = RotPosPyramid(D0ANG , D180ANG, D270ANG );
    return true;
}

//void GgafDxAAPyramidActor::processDraw() {
//    GgafDxGeometricActor::setWorldTransformScRzMxyz(this);
//    _pD3DXMeshModel->draw(this);
//}

void GgafDxAAPyramidActor::drawPyramid(coord prm_x1, coord prm_y1, coord prm_z1,
                                       coord prm_x2, coord prm_y2, coord prm_z2, pos_t pos_info) {
    _rx = GgafDxAAPyramidActor::pos2r[pos_info]._rx;
    _rz = GgafDxAAPyramidActor::pos2r[pos_info]._rz;
    _ry = GgafDxAAPyramidActor::pos2r[pos_info]._ry;
    _sx = (prm_x2 - prm_x1);
    _sy = (prm_y2 - prm_y1);
    _sz = (prm_z2 - prm_z1);
    _x = prm_x1 + (prm_x2 - prm_x1) / 2;
    _y = prm_y1 + (prm_y2 - prm_y1) / 2;
    _z = prm_z1 + (prm_z2 - prm_z1) / 2;
    _fX = C_DX(_x);
    _fY = C_DX(_y);
    _fZ = C_DX(_z);

    //UTIL::setWorldMatrix_ScRzMv(this, _matWorld);
    UTIL::setWorldMatrix_RxRzRyScMv(this, _matWorld); //回転後にスケールがポイント
    processDraw();
}

GgafDxAAPyramidActor::~GgafDxAAPyramidActor() {
}
