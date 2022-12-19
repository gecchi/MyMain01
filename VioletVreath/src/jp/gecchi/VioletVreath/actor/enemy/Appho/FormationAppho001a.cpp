#include "FormationAppho001a.h"

#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Appho/EnemyAppho.h"



using namespace GgafLib;
using namespace VioletVreath;

FormationAppho001a::FormationAppho001a(const char* prm_name) : FormationAppho001(prm_name) {
    _class_name = "FormationAppho001a";
}

void FormationAppho001a::onCalledUpAppho(EnemyAppho* prm_pAppho, int prm_index) {
    int d = 200;
    prm_pAppho->entry_pos_.set( pMYSHIP->_x + PX_C(200) + RND(-PX_C(d),PX_C(d)),
                                pMYSHIP->_y + RND(-PX_C(d),PX_C(d)),
                                MyShip::lim_z_right_ + RND(-PX_C(d),PX_C(d)));
    coord r = PX_C(400);
    angle pos_ang = D_ANG((prm_index+1)*8);
    coord x = ANG_COS(pos_ang) * r;
    coord y = ANG_SIN(pos_ang) * r;
    prm_pAppho->stagnating_pos_.set( pMYSHIP->_x + x,
                                     pMYSHIP->_y + y,
                                     pMYSHIP->_z      );
    Spacetime* pSpacetime =  pCARETAKER->getSpacetime();
    prm_pAppho->leave_pos_.set( (pSpacetime->_x_bound_right/2) + PX_C(200) + RND(-PX_C(d),PX_C(d)),
                                (pSpacetime->_y_bound_top/2)   + RND(-PX_C(d),PX_C(d)),
                                pMYSHIP->_z                                         );

}

FormationAppho001a::~FormationAppho001a() {
}
