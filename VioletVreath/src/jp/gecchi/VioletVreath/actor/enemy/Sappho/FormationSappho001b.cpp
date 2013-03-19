#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationSappho001b::FormationSappho001b(const char* prm_name) : FormationSappho001(prm_name) {
    _class_name = "FormationSappho001b";
}

void FormationSappho001b::onActiveSappho(EnemySappho* prm_pSappho) {
    int d = 130;
    prm_pSappho->entry_pos_.set( P_MYSHIP->_X + RND(-PX_C(d),PX_C(d)),
                                 (Universe::_Y_gone_top/4) + RND(-PX_C(d),PX_C(d)),
                                 P_MYSHIP->_Z );

    prm_pSappho->hanging_pos_.set( P_MYSHIP->_X + PX_C(400) + RND(-PX_C(d),PX_C(d)),
                                   (+PX_C(d)) + RND(-PX_C(d),PX_C(d)),
                                   P_MYSHIP->_Z );

    prm_pSappho->leave_pos_.set( (Universe::_X_gone_right/2) + RND(-PX_C(d),PX_C(d)),
                                 (Universe::_Y_gone_bottom/2)+ RND(-PX_C(d),PX_C(d)),
                                 P_MYSHIP->_Z);
}

FormationSappho001b::~FormationSappho001b() {
}
