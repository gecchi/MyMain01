#include "EnemyWateringLaserChip001.h"
#include "jp/ggaf/lib/actor/laserchip/WateringLaserChip.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyWateringLaserChip001::EnemyWateringLaserChip001(const char* prm_name) :
        WateringLaserChip(prm_name, "EnemyWateringLaserChip001", STATUS(EnemyWateringLaserChip001)) {
    _class_name = "EnemyWateringLaserChip001";
    tmp_x_ = _x;
    tmp_y_ = _y;
    tmp_z_ = _z;
}

void EnemyWateringLaserChip001::initialize() {
    getKuroko()->linkFaceAngByMvAng(true);
    registerHitAreaCube_AutoGenMidColli(50000);
    setHitAble(true);
    setScaleR(6.0);
    setAlpha(0.99);
}

void EnemyWateringLaserChip001::onCreateModel() {

}

void EnemyWateringLaserChip001::onActive() {
    WateringLaserChip::onActive();
    getKuroko()->setMvVelo(PX_C(100));
    getKuroko()->setMvAcce(PX_C(5));
    getStatus()->reset();
}

void EnemyWateringLaserChip001::processBehavior() {
    if (hasJustChangedToActive()) {
        //�A�N�e�B�u�ɂȂ����u�Ԃ́A
        //���p���A�N�^�[���w�肵���ŏ��̍��W�ŕ\���������B
        //���߂̊������s���ƁA�����̂ŁA�ŏ������͂��̂܂܂̍��W�ŕ\���B
        //�Ƃ͂������̂́A���ˌ��͂P�t���[�����ړ����Ă�̂ŁA�s�b�^���ɂ͌����Ȃ���������Ȃ��B
    } else {
        GgafDxKuroko* const pKuroko = getKuroko();
        pKuroko->behave();
    }
    WateringLaserChip::processBehavior();//���W���ړ������Ă���Ăяo������

    tmp_x_ = _x;
    tmp_y_ = _y;
    tmp_z_ = _z;
}

void EnemyWateringLaserChip001::processSettlementBehavior() {
    //���ϋȐ����W�ݒ�B(���[�U�[�����炩�ɂ���m�[�}���C�Y�j
    //processSettlementBehavior() �̃��\�b�h�̈Ӌ`�Ƃ͗���č��W��������ړ����Ă���B
    //�{���� processBehaviorAfter() �I�ȈӖ��̏����ł��邪�A�S���[�U�[�`�b�v���ړ���łȂ��ƈӖ����Ȃ��̂�
    //�d���Ȃ��̂�processSettlementBehavior()�ɐH������ł��܂��B
    if (getActiveFrame() > 3) {
        EnemyWateringLaserChip001* pF = (EnemyWateringLaserChip001*)getInfrontChip();
        EnemyWateringLaserChip001* pB = (EnemyWateringLaserChip001*)getBehindChip();
        if (pF && pB && pF->isActive() && pB->isActive()) {
            //_pChip_behind == nullptr �̔��肾���ł͂��߁B_pChip_behind->_is_active_flg �Ɣ��肷�邱��
            //�Ȃ��Ȃ� dispatch �̏u�Ԃ�_pChip_behind != nullptr �ƂȂ邪�Aactive()�ɂ��L���ɂȂ�͎̂��t���[��������
            //_x,_y,_z �ɂ͂܂��ςȒl�������Ă���B
            //���ԍ��W�ɍĐݒ�
            _x = ((pF->tmp_x_ + pB->tmp_x_)/2 + tmp_x_)/2;
            _y = ((pF->tmp_y_ + pB->tmp_y_)/2 + tmp_y_)/2;
            _z = ((pF->tmp_z_ + pB->tmp_z_)/2 + tmp_z_)/2;
        }
    }
    WateringLaserChip::processSettlementBehavior();
}

void EnemyWateringLaserChip001::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyWateringLaserChip001::onHit(const GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    if (getActiveFrame() <= 2 && (pOther->getKind() & KIND_CHIKEI)) {
        //�o��2�t���[���ȓ��Ńq�b�g���肪�n�`�Ȃ�Ζ����i�o�����n�`�ɂ��j�󂳂������j
        return;
    }

    bool was_destroyed = UTIL::transactEnemyHit(this, pOther);
    if (was_destroyed) {
        //�j�󂳂ꂽ��(�X�^�~�i <= 0)
        sayonara();
    } else {
        //�j�󂳂�Ȃ�������(�X�^�~�i > 0)
    }
}

void EnemyWateringLaserChip001::onInactive() {
    WateringLaserChip::onInactive();
}


EnemyWateringLaserChip001::~EnemyWateringLaserChip001() {
}

