#include "stdafx.h"
#include "FormationSappho001b.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Sappho/EnemySappho.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/God.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationSappho001b::FormationSappho001b(const char* prm_name) : FormationSappho001(prm_name) {
    _class_name = "FormationSappho001b";
}

void FormationSappho001b::onCallUpSappho(EnemySappho* prm_pSappho, int prm_index) {
    int d = 130;
    prm_pSappho->entry_pos_.set( P_MYSHIP->_X + RND(-PX_C(d),PX_C(d)),
                                 P_MYSHIP->_Y + RND(-PX_C(d),PX_C(d)),
                                 MyShip::lim_Z_left_ + RND(-PX_C(d),PX_C(d)));
    coord R = PX_C(400);
    angle pos_ang = D_ANG((prm_index+1)*8);
    coord X = ANG_COS(pos_ang) * R;
    coord Y = ANG_SIN(pos_ang) * R;
    prm_pSappho->hanging_pos_.set( P_MYSHIP->_X + X,
                                   P_MYSHIP->_Y - Y,
                                   P_MYSHIP->_Z );

    prm_pSappho->leave_pos_.set( (Universe::_X_gone_right/2) + RND(-PX_C(d),PX_C(d)),
                                 (Universe::_Y_gone_bottom/2)+ RND(-PX_C(d),PX_C(d)),
                                 P_MYSHIP->_Z);
}

FormationSappho001b::~FormationSappho001b() {
}
