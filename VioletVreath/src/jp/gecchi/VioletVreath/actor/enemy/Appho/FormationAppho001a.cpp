#include "stdafx.h"
#include "FormationAppho001a.h"

#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Appho/EnemyAppho.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationAppho001a::FormationAppho001a(const char* prm_name) : FormationAppho001(prm_name) {
    _class_name = "FormationAppho001a";
}

void FormationAppho001a::onCallUpAppho(EnemyAppho* prm_pAppho, int prm_index) {
    int d = 130;
    prm_pAppho->entry_pos_.set( P_MYSHIP->_x + RND(-PX_C(d),PX_C(d)),
                                P_MYSHIP->_y + RND(-PX_C(d),PX_C(d)),
                                MyShip::lim_z_right_ + RND(-PX_C(d),PX_C(d)));
    coord R = PX_C(400);
    angle pos_ang = D_ANG((prm_index+1)*8);
    coord X = ANG_COS(pos_ang) * R;
    coord Y = ANG_SIN(pos_ang) * R;
    prm_pAppho->hanging_pos_.set( P_MYSHIP->_x + X,
                                  P_MYSHIP->_y + Y,
                                  P_MYSHIP->_z );

    prm_pAppho->leave_pos_.set( (Universe::_x_gone_right/2) + RND(-PX_C(d),PX_C(d)),
                                (Universe::_y_gone_top/2)   + RND(-PX_C(d),PX_C(d)),
                                P_MYSHIP->_z);

}

FormationAppho001a::~FormationAppho001a() {
}
