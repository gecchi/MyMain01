#include "FormationHalia.h"

#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Halia/EnemyHalia.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/CommonScene.h"



using namespace GgafLib;
using namespace VioletVreath;

FormationHalia::FormationHalia(const char* prm_name) :
        TreeFormation(prm_name) {
    _class_name = "FormationHalia";
    num_Halia_  = RF_FormationHalia_Num(G_RANK);         //�ґ��̃n���A�̐�
    interval_frames_ = RF_FormationHalia_LaunchInterval(G_RANK);    //�e�n���A�̏o���Ԋu(frame)
    velo_mv_         = RF_FormationHalia_MvVelo(G_RANK); //�e�n���A�̈ړ����x

    //�ґ��쐬
    papHalia_ = NEW EnemyHalia*[num_Halia_];
    for (int i = 0; i < num_Halia_; i++) {
        papHalia_[i] = NEW EnemyHalia("Halia01");
        //�X�v���C���ړ��v���O�����ݒ�
        papHalia_[i]->setSplineVecDriverLeader(nullptr);
        appendFormationMember(papHalia_[i]);
    }
}

void FormationHalia::initialize() {
}

void FormationHalia::onActive() {
    for (int i = 0; i < num_Halia_; i++) {
        papHalia_[i]->setPosition(1000000, -1000000 + (i * 200000), 0);
        papHalia_[i]->activateDelay(i*interval_frames_ + 1);//interval_frames_�Ԋu��Active�ɂ���B
    }
}

void FormationHalia::onDestroyAll(GgafCore::Actor* prm_pActor_last_destroyed) {
    UTIL::performFormationDestroyAll((GgafDx::FigureActor*)prm_pActor_last_destroyed);
}

FormationHalia::~FormationHalia() {
    GGAF_DELETEARR(papHalia_);
}
