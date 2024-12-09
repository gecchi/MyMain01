#include "FormationOrtuna001b.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Ortuna/EnemyOrtuna.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"

using namespace GgafLib;
using namespace VioletVreath;

FormationOrtuna001b::FormationOrtuna001b(const char* prm_name) : FormationOrtuna001(prm_name) {
    _class_name = "FormationOrtuna001b";
}

void FormationOrtuna001b::onSummonOrtuna(EnemyOrtuna* prm_pOrtuna, int prm_index) {
    if (prm_index == 0) {
        //初Summon、基点をセット
        MyShip* pMyShip = pMYSHIP;
        setPosition(pMyShip->_x+PX_C(200), pMyShip->_y, pMyShip->_z);
    }
    angle ang = (prm_index * D360ANG) / num_Ortuna_;

    //メンバーは自機前方のYZ平面円周上に整列
    static coord r1 = PX_C(50); //初期配置の半径
    prm_pOrtuna->entry_pos_.set(_x,
                                _y + (ANG_SIN(ang) * r1),
                                _z + (ANG_COS(ang) * r1));
    static coord r2 = PX_C(200); //折り返し地点半径
    prm_pOrtuna->stagnating_pos_.set(_x,
                                     _y + (ANG_SIN(ang) * r2),
                                     _z + (ANG_COS(ang) * r2));
}

FormationOrtuna001b::~FormationOrtuna001b() {
}
