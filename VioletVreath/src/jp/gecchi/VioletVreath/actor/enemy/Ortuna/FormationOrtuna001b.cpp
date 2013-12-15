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
    if (prm_index == 0) {
        //初CallUp、基点をセット
        MyShip* pMyShip = P_MYSHIP;
        position(pMyShip->_x+PX_C(200), pMyShip->_y, pMyShip->_z);
    }
    angle ang = (prm_index * D360ANG) / num_Ortuna_;

    //メンバーは自機前方のYZ平面円周上に整列
    static coord r1 = PX_C(50); //初期配置の半径
    coord x = pos_.x;
    coord y = pos_.y;
    coord z = pos_.z;
    prm_pOrtuna->entry_pos_.set(x,
                                y + (ANG_SIN(ang) * r1),
                                z + (ANG_COS(ang) * r1));
    static coord r2 = PX_C(200); //折り返し地点半径
    prm_pOrtuna->hanging_pos_.set( x,
                                   y + (ANG_SIN(ang) * r2),
                                   z + (ANG_COS(ang) * r2));
}

FormationOrtuna001b::~FormationOrtuna001b() {
}
