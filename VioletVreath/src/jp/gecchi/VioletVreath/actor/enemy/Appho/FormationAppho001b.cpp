#include "stdafx.h"
#include "FormationAppho001b.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Appho/EnemyAppho.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/God.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationAppho001b::FormationAppho001b(const char* prm_name) : FormationAppho001(prm_name) {
    _class_name = "FormationAppho001b";
}

void FormationAppho001b::onCallUpAppho(EnemyAppho* prm_pAppho, int prm_index) {
    int d = 130;
    prm_pAppho->entry_pos_.set( P_MYSHIP->_X + RND(-PX_C(d),PX_C(d)),
                                 P_MYSHIP->_Y + RND(-PX_C(d),PX_C(d)),
                                 MyShip::lim_Z_left_ + RND(-PX_C(d),PX_C(d)));
    coord R = PX_C(400);
    angle pos_ang = D_ANG((prm_index+1)*8);
    coord X = ANG_COS(pos_ang) * R;
    coord Y = ANG_SIN(pos_ang) * R;
    prm_pAppho->hanging_pos_.set( P_MYSHIP->_X + X,
                                   P_MYSHIP->_Y - Y,
                                   P_MYSHIP->_Z );

    prm_pAppho->leave_pos_.set( (Universe::_X_gone_right/2) + RND(-PX_C(d),PX_C(d)),
                                 (Universe::_Y_gone_bottom/2)+ RND(-PX_C(d),PX_C(d)),
                                 P_MYSHIP->_Z);
}

FormationAppho001b::~FormationAppho001b() {
}
