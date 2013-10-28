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
    static coord R1 = PX_C(50); //初期配置の半径
    coord X = pos_.x;
    coord Y = pos_.y;
    coord Z = pos_.z;
    prm_pOrtuna->entry_pos_.set(X,
                                Y + (ANG_SIN(ang) * R1),
                                Z + (ANG_COS(ang) * R1));
    static coord R2 = PX_C(200); //折り返し地点半径
    prm_pOrtuna->hanging_pos_.set( X,
                                   Y + (ANG_SIN(ang) * R2),
                                   Z + (ANG_COS(ang) * R2));
}

FormationOrtuna001b::~FormationOrtuna001b() {
}
