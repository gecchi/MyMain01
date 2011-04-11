#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

bool GgafDx9AAPrismActor::init = false;
_MAP_<int, GgafDx9AAPrismActor::RotPosPrism> GgafDx9AAPrismActor::pos2r;


GgafDx9AAPrismActor::GgafDx9AAPrismActor(const char* prm_name,
                                   GgafDx9Checker* prm_pChecker) :

                                   GgafDx9MeshActor(prm_name,
                                                    "prism",
                                                    "DefaultMeshEffect",
                                                    "DefaultMeshTechnique",
                                                    prm_pChecker) {
    //_obj_class |= Obj_GgafDx9AAPrismActor;
    _class_name = "GgafDx9AAPrismActor";
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
        pos2r[POS_PRISM_XY_nn] = RotPosPrism(ANGLE0  , ANGLE0  , ANGLE0  );
        pos2r[POS_PRISM_XY_np] = RotPosPrism(ANGLE0  , ANGLE270, ANGLE0  );
        pos2r[POS_PRISM_XY_pn] = RotPosPrism(ANGLE0  , ANGLE90 , ANGLE0  );
        pos2r[POS_PRISM_XY_pp] = RotPosPrism(ANGLE0  , ANGLE180, ANGLE0  );

        pos2r[POS_PRISM_YZ_nn] = RotPosPrism(ANGLE0  , ANGLE90 , ANGLE90 );
        pos2r[POS_PRISM_YZ_np] = RotPosPrism(ANGLE0  , ANGLE0  , ANGLE90 );
        pos2r[POS_PRISM_YZ_pn] = RotPosPrism(ANGLE0  , ANGLE180, ANGLE90 );
        pos2r[POS_PRISM_YZ_pp] = RotPosPrism(ANGLE0  , ANGLE270, ANGLE90 );

        pos2r[POS_PRISM_ZX_nn] = RotPosPrism(ANGLE90 , ANGLE0  , ANGLE0  );
        pos2r[POS_PRISM_ZX_np] = RotPosPrism(ANGLE90 , ANGLE0  , ANGLE270);
        pos2r[POS_PRISM_ZX_pn] = RotPosPrism(ANGLE90 , ANGLE0  , ANGLE90 );
        pos2r[POS_PRISM_ZX_pp] = RotPosPrism(ANGLE90 , ANGLE0  , ANGLE180);
        init = true;
    }
}

//void GgafDx9AAPrismActor::processDraw() {
//    GgafDx9GeometricActor::setWorldTransformScRzMxyz(this);
//    _pD3DXMeshModel->draw(this);
//}

void GgafDx9AAPrismActor::drawPrism(int prm_x1, int prm_y1, int prm_z1, int prm_x2, int prm_y2, int prm_z2,int pos_prism) {
    _RX = pos2r[pos_prism]._rx;
    _RZ = pos2r[pos_prism]._rz;
    _RY = pos2r[pos_prism]._ry;
    _SX = (prm_x2 - prm_x1);
    _SY = (prm_y2 - prm_y1);
    _SZ = (prm_z2 - prm_z1);
    _X = prm_x1 + (prm_x2 - prm_x1) / 2;
    _Y = prm_y1 + (prm_y2 - prm_y1) / 2;
    _Z = prm_z1 + (prm_z2 - prm_z1) / 2;
    _fX = (FLOAT)(1.0f * _X / LEN_UNIT / PX_UNIT);
    _fY = (FLOAT)(1.0f * _Y / LEN_UNIT / PX_UNIT);
    _fZ = (FLOAT)(1.0f * _Z / LEN_UNIT / PX_UNIT);

    //GgafDx9Util::setWorldMatrix_ScRzMv(this, _matWorld);
    GgafDx9Util::setWorldMatrix_RxRzRyScMv(this, _matWorld); //âÒì]å„Ç…ÉXÉPÅ[ÉãÇ™É|ÉCÉìÉg
    processDraw();
}

GgafDx9AAPrismActor::~GgafDx9AAPrismActor() {
}
