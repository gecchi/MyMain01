#include "jp/ggaf/dxcore/actor/ex/GgafDxAAPrismActor.h"

#include "jp/ggaf/dxcore/GgafDxConfig.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;

std::map<int, GgafDxAAPrismActor::RotPosPrism> GgafDxAAPrismActor::pos2r;

GgafDxAAPrismActor::GgafDxAAPrismActor(const char* prm_name, GgafStatus* prm_pStat,
                                   GgafDxChecker* prm_pChecker) :

                                   GgafDxMeshActor(prm_name,
                                                   CONFIG::COLI_AAPRISM_MODEL.c_str(),
                                                   "DefaultMeshEffect",
                                                   "DefaultMeshTechnique",
                                                   prm_pStat,
                                                   prm_pChecker) {
    //_obj_class |= Obj_GgafDxAAPrismActor;
    _class_name = "GgafDxAAPrismActor";
    static volatile bool is_init = GgafDxAAPrismActor::initStatic(); //ê√ìIÉÅÉìÉoèâä˙âª
}

bool GgafDxAAPrismActor::initStatic() {
    //äÓñ{Ç∆Ç»ÇÈÉvÉäÉYÉÄå^ÇÃépê®
    //
    //                 ^
    //              y+ |    Õ
    //                 |   / z+
    //              /Å_|  /
    //             / | |§/
    //            /  | |/Å_          x+
    //   ---------|Å_|_+--------------->
    //            | /`/     /
    //            |/ / Å_  /
    //            +-/-----/
    //             /   |
    //            /    |
    //           /     |
    //                 |
    //                 |

//                                                             rx        rz       ry
    GgafDxAAPrismActor::pos2r[POS_PRISM_XY_nn] = RotPosPrism(D0ANG  , D0ANG  , D0ANG  );
    GgafDxAAPrismActor::pos2r[POS_PRISM_XY_np] = RotPosPrism(D0ANG  , D270ANG, D0ANG  );
    GgafDxAAPrismActor::pos2r[POS_PRISM_XY_pn] = RotPosPrism(D0ANG  , D90ANG , D0ANG  );
    GgafDxAAPrismActor::pos2r[POS_PRISM_XY_pp] = RotPosPrism(D0ANG  , D180ANG, D0ANG  );

    GgafDxAAPrismActor::pos2r[POS_PRISM_YZ_nn] = RotPosPrism(D0ANG  , D90ANG , D90ANG );
    GgafDxAAPrismActor::pos2r[POS_PRISM_YZ_np] = RotPosPrism(D0ANG  , D0ANG  , D90ANG );
    GgafDxAAPrismActor::pos2r[POS_PRISM_YZ_pn] = RotPosPrism(D0ANG  , D180ANG, D90ANG );
    GgafDxAAPrismActor::pos2r[POS_PRISM_YZ_pp] = RotPosPrism(D0ANG  , D270ANG, D90ANG );

    GgafDxAAPrismActor::pos2r[POS_PRISM_ZX_nn] = RotPosPrism(D90ANG , D0ANG  , D0ANG  );
    GgafDxAAPrismActor::pos2r[POS_PRISM_ZX_np] = RotPosPrism(D90ANG , D0ANG  , D270ANG);
    GgafDxAAPrismActor::pos2r[POS_PRISM_ZX_pn] = RotPosPrism(D90ANG , D0ANG  , D90ANG );
    GgafDxAAPrismActor::pos2r[POS_PRISM_ZX_pp] = RotPosPrism(D90ANG , D0ANG  , D180ANG);

    GgafDxAAPrismActor::pos2r[0] = RotPosPrism(D0ANG  , D0ANG  , D0ANG  );
    return true;
}

//void GgafDxAAPrismActor::processDraw() {
//    GgafDxGeometricActor::setWorldTransformScRzMxyz(this);
//    _pD3DXMeshModel->draw(this);
//}

void GgafDxAAPrismActor::drawPrism(coord prm_x1, coord prm_y1, coord prm_z1,
                                   coord prm_x2, coord prm_y2, coord prm_z2, int pos_prism) {
    _rx = GgafDxAAPrismActor::pos2r[pos_prism]._rx;
    _rz = GgafDxAAPrismActor::pos2r[pos_prism]._rz;
    _ry = GgafDxAAPrismActor::pos2r[pos_prism]._ry;
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
    UTIL::setWorldMatrix_RxRzRyScMv(this, _matWorld); //âÒì]å„Ç…ÉXÉPÅ[ÉãÇ™É|ÉCÉìÉg
    processDraw();
}

GgafDxAAPrismActor::~GgafDxAAPrismActor() {
}
