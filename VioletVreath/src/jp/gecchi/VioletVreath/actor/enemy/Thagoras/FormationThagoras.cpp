#include "stdafx.h"
#include "FormationThagoras.h"

#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Thagoras/EnemyThagoras.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationThagoras::FormationThagoras(const char* prm_name) :
        TreeFormation(prm_name) {
    _class_name = "FormationThagoras";
    num_Thagoras_    = 30;  //�ґ���
    interval_frames_ = 10;  //�o���Ԋu(frame)
    for (int i = 0; i < num_Thagoras_; i++) {
        std::string name = "Thagoras("+XTOS(i)+")";
        addFormationMember(NEW EnemyThagoras(name.c_str()));
    }
    cnt_call_up_ = 0;
}
void FormationThagoras::initialize() {
}

void FormationThagoras::onActive() {
}

void FormationThagoras::processBehavior() {
    if (canCallUp() && getActiveFrame() % interval_frames_ == 0) {
        EnemyThagoras* pThagoras = (EnemyThagoras*)callUpMember();
        if (pThagoras) {
            onCallUpThagoras(pThagoras, cnt_call_up_);  //�R�[���o�b�N
            cnt_call_up_++;
        }
    }
}

void FormationThagoras::onDestroyAll(GgafActor* prm_pActor_last_destroyed) {
    UTIL::proceedFormationDestroyAll((GgafDxDrawableActor*)prm_pActor_last_destroyed);
}

FormationThagoras::~FormationThagoras() {
}
