#include "jp/ggaf/dx/actor/debug/AAPrismActor.h"

#include "jp/ggaf/dx/Config.h"
#include "jp/ggaf/dx/util/Util.h"


using namespace GgafDx;

std::map<int, AAPrismActor::RotPosPrism> AAPrismActor::pos2r;

AAPrismActor::AAPrismActor(const char* prm_name,
                           CollisionChecker* prm_pChecker) :
                               MeshActor(prm_name,
                                         CONFIG::COLI_AAPRISM_MODEL.c_str(),
                                         "DefaultMeshEffect",
                                         "DefaultMeshTechnique",
                                         prm_pChecker) {
    _class_name = "AAPrismActor";
    static volatile bool is_init = AAPrismActor::initStatic(); //ê√ìIÉÅÉìÉoèâä˙âª
}

bool AAPrismActor::initStatic() {
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
    //è„ê}Ç©ÇÁÇ«ÇÃÇÊÇ§Ç…âÒì]Ç∑ÇÈÇ©Çï\Ç∑
    //                                                rx        rz       ry
    AAPrismActor::pos2r[POS_PRISM_XY_NN] = RotPosPrism(D0ANG  , D0ANG  , D0ANG  );
    AAPrismActor::pos2r[POS_PRISM_XY_NP] = RotPosPrism(D0ANG  , D270ANG, D0ANG  );
    AAPrismActor::pos2r[POS_PRISM_XY_PN] = RotPosPrism(D0ANG  , D90ANG , D0ANG  );
    AAPrismActor::pos2r[POS_PRISM_XY_PP] = RotPosPrism(D0ANG  , D180ANG, D0ANG  );

    AAPrismActor::pos2r[POS_PRISM_YZ_NN] = RotPosPrism(D0ANG  , D90ANG , D90ANG );
    AAPrismActor::pos2r[POS_PRISM_YZ_NP] = RotPosPrism(D0ANG  , D0ANG  , D90ANG );
    AAPrismActor::pos2r[POS_PRISM_YZ_PN] = RotPosPrism(D0ANG  , D180ANG, D90ANG );
    AAPrismActor::pos2r[POS_PRISM_YZ_PP] = RotPosPrism(D0ANG  , D270ANG, D90ANG );

    AAPrismActor::pos2r[POS_PRISM_ZX_NN] = RotPosPrism(D90ANG , D0ANG  , D0ANG  );
    AAPrismActor::pos2r[POS_PRISM_ZX_NP] = RotPosPrism(D90ANG , D0ANG  , D270ANG);
    AAPrismActor::pos2r[POS_PRISM_ZX_PN] = RotPosPrism(D90ANG , D0ANG  , D90ANG );
    AAPrismActor::pos2r[POS_PRISM_ZX_PP] = RotPosPrism(D90ANG , D0ANG  , D180ANG);

    AAPrismActor::pos2r[0] = RotPosPrism(D0ANG  , D0ANG  , D0ANG  );
    return true;
}

void AAPrismActor::drawPrism(coord prm_x1, coord prm_y1, coord prm_z1,
                             coord prm_x2, coord prm_y2, coord prm_z2, pos_t pos_info) {
    _rx = AAPrismActor::pos2r[pos_info]._rx;
    _rz = AAPrismActor::pos2r[pos_info]._rz;
    _ry = AAPrismActor::pos2r[pos_info]._ry;
    _sx = (prm_x2 - prm_x1);
    _sy = (prm_y2 - prm_y1);
    _sz = (prm_z2 - prm_z1);
    _x = prm_x1 + (prm_x2 - prm_x1) / 2;
    _y = prm_y1 + (prm_y2 - prm_y1) / 2;
    _z = prm_z1 + (prm_z2 - prm_z1) / 2;
    _fX = C_DX(_x);
    _fY = C_DX(_y);
    _fZ = C_DX(_z);
    UTIL::setWorldMatrix_RxRzRyScMv(this, _matWorld); //âÒì]å„Ç…ÉXÉPÅ[ÉãÇ™É|ÉCÉìÉg
    processDraw();
}

AAPrismActor::~AAPrismActor() {
}
