#include "MyStraightLaserChip001.h"

#include "jp/ggaf/core/util/RingLinkedList.hpp"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/gecchi/VioletVreath/actor/my/MyLockonController.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/LaserMagic.h"


using namespace GgafLib;
using namespace VioletVreath;


GgafDx::Model* MyStraightLaserChip001::pModel_  = nullptr;
int MyStraightLaserChip001::tex_no_ = 0;
const velo MyStraightLaserChip001::MAX_VELO = PX_C(512); //���̒l��傫������ƁA�ō����x�������Ȃ�B

MyStraightLaserChip001::MyStraightLaserChip001(const char* prm_name) :
        VvMyActor<StraightLaserChip>(prm_name, "MyLaserChip001", StatusReset(MyStraightLaserChip001)) {
    _class_name = "MyStraightLaserChip001";
    default_stamina_ = getStatus()->get(STAT_Stamina);
    setMvVelo(MAX_VELO*N_DISPATCH_AT_ONCE);
    pOrg_ = nullptr;
    GgafDx::Model* pModel = getModel();
    if (!MyStraightLaserChip001::pModel_) {
        if (pModel->_num_materials != MAX_LASER_LEVEL) {
            throwCriticalException("MyStraightLaserChip001���f���́A�e�N�X�`���i�}�e���A���j��"<<MAX_LASER_LEVEL<<"�K�v�ł��B");
        }
        MyStraightLaserChip001::pModel_ = pModel;
    }
}

void MyStraightLaserChip001::initialize() {
    pOrg_ = pMYSHIP;
    getLocusVehicle()->setRzRyMvAng(0,0);
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliAABox_WHD(0, MAX_VELO, MAX_VELO/4, MAX_VELO/4);
    setHitAble(true);
    setScaleR(5.0);
    setCullingDraw(false);
}

void MyStraightLaserChip001::onCreateModel() {
}


void MyStraightLaserChip001::onActive() {
    getStatus()->reset();
    default_stamina_ = getStatus()->get(STAT_Stamina);
    StraightLaserChip::onActive();
    getLocusVehicle()->setMvVelo(MAX_VELO*_n_dispatch_at_once);
//    getLocusVehicle()->setMvAcce(1000);
}

void MyStraightLaserChip001::processBehavior() {
    frame active_frames = getActiveFrame();
    double power = active_frames <= 300 ? UTIL::SHOT_POWER[active_frames] : UTIL::SHOT_POWER[300];
    getStatus()->set(STAT_AttackPowerRate, power);
    _power = power;

    if (getInfrontChip() == nullptr) {
        getSeXmtr()->behave();
    }
    StraightLaserChip::processBehavior();//���W���ړ������Ă���Ăяo������
    //�������烌�[�U�[�\���̂��ߋ����I�ɍ��W�␳
    if (hasJustChangedToActive()) {

        //�������烌�[�U�[�\���̂��ߋ����I�ɍ��W�␳
        int n = _n_dispatch_at_once-1 - _dispatch_index;
        if (n == 0) {
            setPositionAt(pOrg_);
        } else {
            coord velo_mv = getMvVelo();
            setPosition(pOrg_->_x + ( (velo_mv/_n_dispatch_at_once)*n) ,
                        pOrg_->_y ,
                        pOrg_->_z );
        }
    }
}

void MyStraightLaserChip001::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void MyStraightLaserChip001::onHit(const GgafCore::Actor* prm_pOtherActor) {
    GgafDx::GeometricActor* pOther = (GgafDx::GeometricActor*) prm_pOtherActor;
    //�q�b�g�G�t�F�N�g
    UTIL::activateExplosionEffectOf(this); //�����G�t�F�N�g�o��

    if ((pOther->lookUpKind() & KIND_ENEMY_BODY) ) {
        //���b�N�I���\�A�N�^�[�Ȃ烍�b�N�I�������݂�
        if (pOther->getStatus()->get(STAT_LockonAble) == 1) {
            pOrg_->pLockonCtrler_->lockon(pOther);
        }
        int stamina = calcStamina(pOther);
        if (stamina <= 0) {
            //�ꌂ�Ń`�b�v���ł̍U����
            getStatus()->set(STAT_Stamina, default_stamina_);
            sayonara();
        } else {
            //�ς����Ȃ�΁A�ʊт��A�X�^�~�i�񕜁i�U����100�̎G���Ȃ�Βʊсj
            getStatus()->set(STAT_Stamina, default_stamina_);
        }
    } else if (pOther->lookUpKind() & KIND_CHIKEI) {
        //�n�`����͖��������悤�Ȃ�
        sayonara();
    }
}

void MyStraightLaserChip001::onInactive() {
    StraightLaserChip::onInactive();
}

void MyStraightLaserChip001::chengeTex(int prm_tex_no) {
    if (MyStraightLaserChip001::pModel_) {
        MyStraightLaserChip001::tex_no_ = prm_tex_no;
        MyStraightLaserChip001::pModel_->setDefaultTextureMaterialNo(prm_tex_no);
    }
}

MyStraightLaserChip001::~MyStraightLaserChip001() {
    MyStraightLaserChip001::pModel_ = nullptr;
}


