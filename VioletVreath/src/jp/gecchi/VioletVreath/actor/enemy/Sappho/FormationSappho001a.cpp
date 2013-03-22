#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationSappho001a::FormationSappho001a(const char* prm_name) : FormationSappho001(prm_name) {
    _class_name = "FormationSappho001a";
}

void FormationSappho001a::onCallUpSappho(EnemySappho* prm_pSappho, int prm_index) {
    int d = 130;
    prm_pSappho->entry_pos_.set( P_MYSHIP->_X + RND(-PX_C(d),PX_C(d)),
                                 P_MYSHIP->_Y + RND(-PX_C(d),PX_C(d)),
                                 MyShip::lim_zright_ + RND(-PX_C(d),PX_C(d)));
    coord R = PX_C(400);
    angle pos_ang = D_ANG((prm_index+1)*8);
    coord X = ANG_COS(pos_ang) * R;
    coord Y = ANG_SIN(pos_ang) * R;
    prm_pSappho->hanging_pos_.set( P_MYSHIP->_X + X,
                                   P_MYSHIP->_Y + Y,
                                   P_MYSHIP->_Z );

    prm_pSappho->leave_pos_.set( (Universe::_X_gone_right/2) + RND(-PX_C(d),PX_C(d)),
                                 (Universe::_Y_gone_top/2)+ RND(-PX_C(d),PX_C(d)),
                                 P_MYSHIP->_Z);

}

FormationSappho001a::~FormationSappho001a() {
}
