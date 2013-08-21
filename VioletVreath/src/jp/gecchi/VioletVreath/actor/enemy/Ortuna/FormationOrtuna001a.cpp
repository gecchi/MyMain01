#include "stdafx.h"
#include "FormationOrtuna001a.h"

#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ortuna/EnemyOrtuna.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationOrtuna001a::FormationOrtuna001a(const char* prm_name) : FormationOrtuna001(prm_name) {
    _class_name = "FormationOrtuna001a";
}

void FormationOrtuna001a::onCallUpOrtuna(EnemyOrtuna* prm_pOrtuna, int prm_index) {
    int d = 300;
    MyShip* pMyShip = P_MYSHIP;

    coord X = RND(pMyShip->_X+PX_C(d), pMyShip->_X + (PX_C(d)*3));
    coord Y = pMyShip->_Y + RND(-PX_C(d),PX_C(d));
    coord Z = pMyShip->_Z + RND(-PX_C(d),PX_C(d));
    prm_pOrtuna->entry_pos_.set( X, Y, Z);

    static coord R = PX_C(200);
    coord ang = UTIL::getAngle2D(Z - pMyShip->_Z, Y - pMyShip->_Y);
    prm_pOrtuna->hanging_pos_.set( X,
                                   Y + (ANG_SIN(ang) * R),
                                   Z + (ANG_COS(ang) * R));

}

FormationOrtuna001a::~FormationOrtuna001a() {
}
