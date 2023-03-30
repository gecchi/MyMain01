#include "jp/ggaf/dx/actor/debug/AAPyramidActor.h"

#include "jp/ggaf/dx/Config.h"
#include "jp/ggaf/dx/util/Util.h"


using namespace GgafDx;

std::map<int, AAPyramidActor::RotPosPyramid> AAPyramidActor::pos2r;

AAPyramidActor::AAPyramidActor(const char* prm_name,
                               CollisionChecker* prm_pChecker) :
                                   MeshActor(prm_name,
                                             CONFIG::COLI_AAPYRAMID_MODEL.c_str(),
                                             "DefaultMeshEffect",
                                             "DefaultMeshTechnique",
                                             prm_pChecker) {
    _class_name = "AAPyramidActor";
    static volatile bool is_init = AAPyramidActor::initStatic(); //静的メンバ初期化
}

bool AAPyramidActor::initStatic() {
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
    AAPyramidActor::pos2r[POS_PYRAMID_NNN] = RotPosPyramid(D0ANG , D0ANG  , D0ANG   );
    AAPyramidActor::pos2r[POS_PYRAMID_NNP] = RotPosPyramid(D0ANG , D0ANG  , D90ANG  );
    AAPyramidActor::pos2r[POS_PYRAMID_NPN] = RotPosPyramid(D0ANG , D180ANG, D90ANG  );
    AAPyramidActor::pos2r[POS_PYRAMID_NPP] = RotPosPyramid(D0ANG , D180ANG, D180ANG );
    AAPyramidActor::pos2r[POS_PYRAMID_PNN] = RotPosPyramid(D0ANG , D0ANG  , D270ANG );
    AAPyramidActor::pos2r[POS_PYRAMID_PNP] = RotPosPyramid(D0ANG , D0ANG  , D180ANG );
    AAPyramidActor::pos2r[POS_PYRAMID_PPN] = RotPosPyramid(D0ANG , D180ANG, D0ANG   );
    AAPyramidActor::pos2r[POS_PYRAMID_PPP] = RotPosPyramid(D0ANG , D180ANG, D270ANG );
    return true;
}

void AAPyramidActor::drawPyramid(coord prm_x1, coord prm_y1, coord prm_z1,
                                       coord prm_x2, coord prm_y2, coord prm_z2, pos_t pos_info) {
    _rx = AAPyramidActor::pos2r[pos_info]._rx;
    _rz = AAPyramidActor::pos2r[pos_info]._rz;
    _ry = AAPyramidActor::pos2r[pos_info]._ry;
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

AAPyramidActor::~AAPyramidActor() {
}
