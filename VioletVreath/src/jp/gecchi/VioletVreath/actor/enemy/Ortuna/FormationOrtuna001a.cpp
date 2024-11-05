#include "FormationOrtuna001a.h"

#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ortuna/EnemyOrtuna.h"



using namespace GgafLib;
using namespace VioletVreath;

FormationOrtuna001a::FormationOrtuna001a(const char* prm_name) : FormationOrtuna001(prm_name) {
    _class_name = "FormationOrtuna001a";
}

void FormationOrtuna001a::onSummonOrtuna(EnemyOrtuna* prm_pOrtuna, int prm_index) {
    int d = 300;
    MyShip* pMyShip = pMYSHIP;

    coord x = RND(pMyShip->_x+PX_C(d), pMyShip->_x + (PX_C(d)*3));
    coord y = pMyShip->_y + RND(-PX_C(d),PX_C(d));
    coord z = pMyShip->_z + RND(-PX_C(d),PX_C(d));
    prm_pOrtuna->entry_pos_.set( x, y, z);

    static coord r = PX_C(200);
    coord ang = UTIL::getAngle2D(z - pMyShip->_z, y - pMyShip->_y);
    prm_pOrtuna->stagnating_pos_.set( x,
                                   y + (ANG_SIN(ang) * r),
                                   z + (ANG_COS(ang) * r));

}

FormationOrtuna001a::~FormationOrtuna001a() {
}
