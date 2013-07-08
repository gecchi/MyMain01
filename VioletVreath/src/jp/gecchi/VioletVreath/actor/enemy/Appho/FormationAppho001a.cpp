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
    prm_pAppho->entry_pos_.set( P_MYSHIP->_X + RND(-PX_C(d),PX_C(d)),
                                 P_MYSHIP->_Y + RND(-PX_C(d),PX_C(d)),
                                 MyShip::lim_Z_right_ + RND(-PX_C(d),PX_C(d)));
    coord R = PX_C(400);
    angle pos_ang = D_ANG((prm_index+1)*8);
    coord X = ANG_COS(pos_ang) * R;
    coord Y = ANG_SIN(pos_ang) * R;
    prm_pAppho->hanging_pos_.set( P_MYSHIP->_X + X,
                                   P_MYSHIP->_Y + Y,
                                   P_MYSHIP->_Z );

    prm_pAppho->leave_pos_.set( (Universe::_X_gone_right/2) + RND(-PX_C(d),PX_C(d)),
                                 (Universe::_Y_gone_top/2)   + RND(-PX_C(d),PX_C(d)),
                                 P_MYSHIP->_Z);

}

FormationAppho001a::~FormationAppho001a() {
}
