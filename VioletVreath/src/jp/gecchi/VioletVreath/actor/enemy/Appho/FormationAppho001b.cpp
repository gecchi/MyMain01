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
    prm_pAppho->entry_pos_.set( P_MYSHIP->_x + RND(-PX_C(d),PX_C(d)),
                                P_MYSHIP->_y + RND(-PX_C(d),PX_C(d)),
                                MyShip::lim_z_left_ + RND(-PX_C(d),PX_C(d)));
    coord r = PX_C(400);
    angle pos_ang = D_ANG((prm_index+1)*8);
    coord x = ANG_COS(pos_ang) * r;
    coord y = ANG_SIN(pos_ang) * r;
    prm_pAppho->hanging_pos_.set( P_MYSHIP->_x + x,
                                  P_MYSHIP->_y - y,
                                  P_MYSHIP->_z      );

    prm_pAppho->leave_pos_.set( (Universe::_x_gone_right/2) + RND(-PX_C(d),PX_C(d)),
                                (Universe::_y_gone_bottom/2)+ RND(-PX_C(d),PX_C(d)),
                                P_MYSHIP->_z                                         );
}

FormationAppho001b::~FormationAppho001b() {
}
