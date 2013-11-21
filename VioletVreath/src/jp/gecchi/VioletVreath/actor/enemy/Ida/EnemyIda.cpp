#include "stdafx.h"
#include "EnemyIda.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyIda::EnemyIda(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Ida", STATUS(EnemyIda)) {
    _class_name = "EnemyIda";
    _pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");     //����
    useProgress(PROG_BANPEI-1);
}

void EnemyIda::onCreateModel() {
    _pModel->setSpecular(5.0, 1.0);
}

void EnemyIda::initialize() {
    _pKurokoA->relateFaceWithMvAng(true);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 40000);
}

void EnemyIda::onActive() {
    _pStatus->reset();
    _pProg->reset(PROG_INIT);
}

void EnemyIda::processBehavior() {
    changeGeoLocal(); //���[�J�����W�n��

    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    switch (_pProg->get()) {
        case PROG_INIT: {
            setHitAble(false);
            _pKurokoA->setFaceAngVelo(AXIS_X, D_ANG(4));
            _pAFader->setAlpha(0);
             UTIL::activateEntryEffectOf(this);
            _pProg->changeNext();
            break;
        }
        case PROG_ENTRY: {
            if (_pProg->isJustChanged()) {
                _pAFader->fadeLinerUntil(1.0, 30);
            }
            if (_pProg->getFrameInProgress() == 25) {
                setHitAble(true);
                _pProg->changeNext();
            }
            break;
        }
        case PROG_MOVE01: {
            if (_pProg->isJustChanged()) {
            }
            //���@�֌�����
            GgafDxGeometricActor* pTargetActor = P_MYSHIP;
            coord mvx = pTargetActor->_x - _x_final; //_x_final�͐�΍��W
            coord mvy = pTargetActor->_y - _y_final;
            coord mvz = pTargetActor->_z - _z_final;
            //�x�[�X�܂ł�(��]�~���s�ړ�)�s��̋t�s��擾
            D3DXMATRIX* pBaseInvMat = _pActor_Base->getInvMatWorldRotMv();
            //���[�J�����W�Ō����Ă����ׂ������x�N�g���v�Z
            coord tvx = mvx*pBaseInvMat->_11 + mvy*pBaseInvMat->_21 + mvz*pBaseInvMat->_31;
            coord tvy = mvx*pBaseInvMat->_12 + mvy*pBaseInvMat->_22 + mvz*pBaseInvMat->_32;
            coord tvz = mvx*pBaseInvMat->_13 + mvy*pBaseInvMat->_23 + mvz*pBaseInvMat->_33;

            angle angRz_Target, angRy_Target;
            UTIL::convVectorToRzRy(tvx, tvy, tvz, angRz_Target, angRy_Target); //RzRy�ɒu��������
            _pKurokoA->setRzRyMvAng(angRz_Target, angRy_Target);
            break;
        }
    }

    _pAFader->behave();
    _pKurokoA->behave();

    changeGeoFinal(); //��΍��W�n��
}

void EnemyIda::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyIda::onHit(GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::proceedEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //�j��
        _pSeTx->play3D(SE_EXPLOSION);
    } else {
        //��j��
        _pSeTx->play3D(SE_DAMAGED);
    }
}

void EnemyIda::onInactive() {
}

EnemyIda::~EnemyIda() {
}


