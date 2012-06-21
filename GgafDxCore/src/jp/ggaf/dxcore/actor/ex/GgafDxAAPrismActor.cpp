#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;

bool GgafDxAAPrismActor::init = false;
__map__<int, GgafDxAAPrismActor::RotPosPrism> GgafDxAAPrismActor::pos2r;


GgafDxAAPrismActor::GgafDxAAPrismActor(const char* prm_name, GgafStatus* prm_pStat,
                                   GgafDxChecker* prm_pChecker) :

                                   GgafDxMeshActor(prm_name,
                                                   "GgafDxAAPrism",
                                                   "DefaultMeshEffect",
                                                   "DefaultMeshTechnique",
                                                   prm_pStat,
                                                   prm_pChecker) {
    //_obj_class |= Obj_GgafDxAAPrismActor;
    _class_name = "GgafDxAAPrismActor";
    if (init == false) {
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

 //                                             RX        RZ       RY
        pos2r[POS_PRISM_XY_nn] = RotPosPrism(D0ANG  , D0ANG  , D0ANG  );
        pos2r[POS_PRISM_XY_np] = RotPosPrism(D0ANG  , D270ANG, D0ANG  );
        pos2r[POS_PRISM_XY_pn] = RotPosPrism(D0ANG  , D90ANG , D0ANG  );
        pos2r[POS_PRISM_XY_pp] = RotPosPrism(D0ANG  , D180ANG, D0ANG  );

        pos2r[POS_PRISM_YZ_nn] = RotPosPrism(D0ANG  , D90ANG , D90ANG );
        pos2r[POS_PRISM_YZ_np] = RotPosPrism(D0ANG  , D0ANG  , D90ANG );
        pos2r[POS_PRISM_YZ_pn] = RotPosPrism(D0ANG  , D180ANG, D90ANG );
        pos2r[POS_PRISM_YZ_pp] = RotPosPrism(D0ANG  , D270ANG, D90ANG );

        pos2r[POS_PRISM_ZX_nn] = RotPosPrism(D90ANG , D0ANG  , D0ANG  );
        pos2r[POS_PRISM_ZX_np] = RotPosPrism(D90ANG , D0ANG  , D270ANG);
        pos2r[POS_PRISM_ZX_pn] = RotPosPrism(D90ANG , D0ANG  , D90ANG );
        pos2r[POS_PRISM_ZX_pp] = RotPosPrism(D90ANG , D0ANG  , D180ANG);

        pos2r[0] = RotPosPrism(D0ANG  , D0ANG  , D0ANG  );
        init = true;
    }
}

//void GgafDxAAPrismActor::processDraw() {
//    GgafDxGeometricActor::setWorldTransformScRzMxyz(this);
//    _pD3DXMeshModel->draw(this);
//}

void GgafDxAAPrismActor::drawPrism(coord prm_x1, coord prm_y1, coord prm_z1,
                                    coord prm_x2, coord prm_y2, coord prm_z2, int pos_prism) {
    _RX = pos2r[pos_prism]._rx;
    _RZ = pos2r[pos_prism]._rz;
    _RY = pos2r[pos_prism]._ry;
    _SX = (prm_x2 - prm_x1);
    _SY = (prm_y2 - prm_y1);
    _SZ = (prm_z2 - prm_z1);
    _X = prm_x1 + (prm_x2 - prm_x1) / 2;
    _Y = prm_y1 + (prm_y2 - prm_y1) / 2;
    _Z = prm_z1 + (prm_z2 - prm_z1) / 2;
    _fX = C_DX(_X);
    _fY = C_DX(_Y);
    _fZ = C_DX(_Z);

    //UTIL::setWorldMatrix_ScRzMv(this, _matWorld);
    UTIL::setWorldMatrix_RxRzRyScMv(this, _matWorld); //âÒì]å„Ç…ÉXÉPÅ[ÉãÇ™É|ÉCÉìÉg
    processDraw();
}

GgafDxAAPrismActor::~GgafDxAAPrismActor() {
}
