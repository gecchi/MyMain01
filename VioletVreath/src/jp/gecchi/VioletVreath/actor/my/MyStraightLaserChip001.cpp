#include "MyStraightLaserChip001.h"

#include "jp/ggaf/core/util/LinkedListRing.hpp"
#include "jp/ggaf/dx/actor/supporter/Kuroko.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/gecchi/VioletVreath/actor/my/MyLockonController.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/LaserMagic.h"


using namespace GgafLib;
using namespace VioletVreath;


GgafDx::Model* MyStraightLaserChip001::pModel_  = nullptr;
int MyStraightLaserChip001::tex_no_ = 0;


MyStraightLaserChip001::MyStraightLaserChip001(const char* prm_name) :
        StraightLaserChip(prm_name, "MyLaserChip001", STATUS(MyStraightLaserChip001)) {
    _class_name = "MyStraightLaserChip001";
    default_stamina_ = getStatus()->get(STAT_Stamina);
    setMvVelo(PX_C(300));
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
    getKuroko()->setRzRyMvAng(0,0);
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAABox_WHD(0,PX_C(300),PX_C(80),PX_C(80));

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

    getKuroko()->setMvVelo(100000);
    getKuroko()->setMvAcce(1000);
}

void MyStraightLaserChip001::processBehavior() {
    frame active_frames = getActiveFrame();
    double power = active_frames <= 300 ? UTIL::SHOT_POWER[active_frames] : UTIL::SHOT_POWER[300];
    getStatus()->set(STAT_AttackPowerRate, power);
    _power = power;

    if (getInfrontChip() == nullptr) {
        getSeTransmitter()->behave();
    }
    StraightLaserChip::processBehavior();//���W���ړ������Ă���Ăяo������
    //�������烌�[�U�[�\���̂��ߋ����I�ɍ��W�␳
    if (hasJustChangedToActive()) {
        setPositionAt(pOrg_);
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

        const int stamina = UTIL::calcMyStamina(this, pOther);
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


