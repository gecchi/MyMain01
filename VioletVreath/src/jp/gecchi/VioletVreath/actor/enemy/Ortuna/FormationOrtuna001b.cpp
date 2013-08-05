#include "stdafx.h"
#include "FormationOrtuna001b.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Ortuna/EnemyOrtuna.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/God.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationOrtuna001b::FormationOrtuna001b(const char* prm_name) : FormationOrtuna001(prm_name) {
    _class_name = "FormationOrtuna001b";
}

void FormationOrtuna001b::onCallUpOrtuna(EnemyOrtuna* prm_pOrtuna, int prm_index) {
    MyShip* pMyShip = P_MYSHIP;
    angle ang = (prm_index * D360ANG) / num_Ortuna_;

    coord R1 = PX_C(50);
    coord X = pMyShip->_X+PX_C(200);
    coord Y = pMyShip->_Y;
    coord Z = pMyShip->_Z;
    prm_pOrtuna->entry_pos_.set(X,
                                Y + (ANG_SIN(ang) * R1),
                                Z + (ANG_COS(ang) * R1));
    coord R2 = PX_C(200);
    prm_pOrtuna->hanging_pos_.set( X,
                                   Y + (ANG_SIN(ang) * R2),
                                   Z + (ANG_COS(ang) * R2));
}

FormationOrtuna001b::~FormationOrtuna001b() {
}
