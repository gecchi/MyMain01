#include "stdafx.h"
#include "FormationHalia.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Halia/EnemyHalia.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/CommonScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationHalia::FormationHalia(const char* prm_name) :
        TreeFormation(prm_name) {
    _class_name = "FormationHalia";
    num_Halia_      = RF_FormationHalia_Num(G_RANK);         //�ґ��̃n���A�̐�
    interval_frames_ = RF_FormationHalia_LaunchInterval(G_RANK);    //�e�n���A�̏o���Ԋu(frame)
    velo_mv_         = RF_FormationHalia_MvVelo(G_RANK); //�e�n���A�̈ړ����x

    //�ґ��쐬
    papHalia_ = NEW EnemyHalia*[num_Halia_];
    for (int i = 0; i < num_Halia_; i++) {
        papHalia_[i] = NEW EnemyHalia("Halia01");
        //�X�v���C���ړ��v���O�����ݒ�
        papHalia_[i]->setSplineKurokoLeader(nullptr);
        addFormationMember(papHalia_[i]);
    }
}

void FormationHalia::initialize() {

}

void FormationHalia::onActive() {
    for (int i = 0; i < num_Halia_; i++) {
        papHalia_[i]->position(MyShip::lim_x_behaind_, -2000000 + (i * 400000), 0);
        papHalia_[i]->_pKuroko->setRzRyMvAng(0,0);
        papHalia_[i]->_pKuroko->setMvVelo(80000);
        papHalia_[i]->activateDelay(i*interval_frames_ + 1);//interval_frames_�Ԋu��Active�ɂ���B
    }
}

void FormationHalia::onDestroyAll(GgafActor* prm_pActor_last_destroyed) {
    UTIL::proceedFormationDestroyAll((GgafDxDrawableActor*)prm_pActor_last_destroyed);
}


FormationHalia::~FormationHalia() {
    GGAF_DELETEARR(papHalia_);
}
