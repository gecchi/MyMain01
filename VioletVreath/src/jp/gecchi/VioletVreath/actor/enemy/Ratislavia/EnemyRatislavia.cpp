#include "EnemyRatislavia.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/util/GgafDxCollisionArea.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectExplosion004.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/CommonScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyRatislavia::EnemyRatislavia(const char* prm_name, const char* prm_model, coord prm_r1, coord prm_r2) :
        CubeMapMeshActor(prm_name, prm_model, STATUS(EnemyRatislavia)) {
    _class_name = "EnemyRatislavia";
    setCubeMap("BkSky_cubemap.dds", 0.4);
    r1_ = prm_r1;
    r2_ = prm_r2;
    colli_part_num_ = 16; //�����蔻�苅�̐�
    useProgress(PROG_BANPEI);
}

void EnemyRatislavia::addSubGroupAsFkOnSurface(GgafDxGeometricActor* prm_pGeoActor, angle prm_angPos1, angle prm_angPos2) {
    //�g�[���X���f����ZY���ʂɉ~
    //�ʒu�����߂�
    //���s�ړ�( +r2_, +0, +0) > angPos2��Y����] > ���s�ړ�( +0, +0, -r1_) > angPos1��X����] �ϊ��s��� dx, dy, dz ���~����
    //
    //    | COS[angPos2]    , -SIN[angPos2]*-SIN[angPos1]             , -SIN[angPos2]*COS[angPos1]             , 0 |
    //    | 0               ,  COS[angPos1]                           ,  SIN[angPos1]                          , 0 |
    //    | SIN[angPos2]    ,  COS[angPos2]*-SIN[angPos1]             ,  COS[angPos2]*COS[angPos]              , 0 |
    //    | r2_*COS[angPos2], (r2_*-SIN[angPos2] + -r1_)*-SIN[angPos1], (r2_*-SIN[angPos2] + -r1_)*COS[angPos1], 1 |
    //���
    double X = r2_*ANG_COS(prm_angPos2);
    double Y = (r2_*-ANG_SIN(prm_angPos2) - r1_) * -ANG_SIN(prm_angPos1);
    double Z = (r2_*-ANG_SIN(prm_angPos2) - r1_) *  ANG_COS(prm_angPos1);

    //���������߂�
    //���s�ړ�( +0, +0, -r1_) > angPos1��X����] �ϊ��s��� dx, dy, dz ���g�p
    //    | 1, 0                 , 0                , 0 |
    //    | 0, COS[angPos1]      , SIN[angPos1]     , 0 |
    //    | 0, -SIN[angPos1]     , COS[angPos1]     , 0 |
    //    | 0, -r1_*-SIN[angPos1], -r1_*COS[angPos1], 1 |
    //���
    double X2 = 0;
    double Y2 = -r1_*-ANG_SIN(prm_angPos1);
    double Z2 = -r1_*ANG_COS(prm_angPos1);
    angle angRz, angRy;
    UTIL::convVectorToRzRy((int)(X - X2), (int)(Y - Y2), (int)(Z - Z2),
                           angRz, angRy);
    //�{�[���Ƃ��Ēǉ�
    this->addSubGroupAsFk(prm_pGeoActor, X, Y, Z, D0ANG, angRy, angRz);
}

void EnemyRatislavia::makeCollisionArea(int prm_nSphere){
    angle* paAngRadial = NEW angle[prm_nSphere];
    UTIL::getRadialAngle2D(0, prm_nSphere, paAngRadial);
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->makeCollision(prm_nSphere);
    for (int i = 0; i < prm_nSphere; i++) {
        pChecker->setColliSphere(
                i,
                0 , ANG_SIN(paAngRadial[i]) * r1_, ANG_COS(paAngRadial[i]) * r1_,
                r2_,
                false, true, true
                );
    }
    setSpecialDrawDepth(DRAW_DEPTH_LEVEL_BIGOBJ-2);
    GGAF_DELETE(paAngRadial);
}

void EnemyRatislavia::onCreateModel() {
}

void EnemyRatislavia::initialize() {
    makeCollisionArea(colli_part_num_);
    setHitAble(true);
    setAlpha(1.00);
}

void EnemyRatislavia::onActive() {
    getStatus()->reset();
    getProgress()->reset(PROG_INIT);
}

void EnemyRatislavia::processBehavior() {
    GgafDxKuroko* pKuroko = getKuroko();
    GgafProgress* pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            pProg->change(PROG_FLOAT_MOVE);
            break;
        }

        case PROG_FLOAT_MOVE: {
            //�C�x���g�҂�
            break;
        }

        case PROG_EXPLOSION: {
            if (pProg->isJustChanged()) {
                _DTRACE_("EnemyRatislavia::processBehavior() _pProg=PROG_EXPLOSION ������`");
            }
            if (pProg->getFrameInProgress() % 16U == 0) {
                //���X����
                //�����蔻�苅�t�߂ɔ����G�t�F�N�g���U��������
                GgafDxCollisionPart* pPart;
                GgafDxDrawableActor* pE;
                CollisionChecker3D* pChecker = getCollisionChecker();
                for (int j = 0; j < colli_part_num_; j++) {
                    pPart = pChecker->getArea()->getPart(j);
                    pE = dispatchDelayFromCommon(EffectExplosion004, RND(1,10));
                    if (pE) {
                        pE->position(_x + pPart->_cx + RND(-r2_, +r2_),
                                     _y + pPart->_cy + RND(-r2_, +r2_),
                                     _z + pPart->_cz + RND(-r2_, +r2_));
                    }
                }
            }


            if (pProg->getFrameInProgress() == 480) {
                //�����ő傫������
                //�����蔻�苅�t�߂ɔ����G�t�F�N�g���U��������
                GgafDxCollisionPart* pPart;
                GgafDxDrawableActor* pE;
                CollisionChecker3D* pChecker = getCollisionChecker();
                for (int j = 0; j < colli_part_num_; j++) {
                    pPart = pChecker->getArea()->getPart(j);
                    pE = dispatchFromCommon(EffectExplosion004);
                    if (pE) {
                        pE->position(_x + pPart->_cx,
                                     _y + pPart->_cy,
                                     _z + pPart->_cz);
                    }
                }
                sayonara();
                pProg->change(PROG_NOTHING);
            }
            break;
        }
        case PROG_NOTHING: {
            //�������̎�
            break;
        }
    }

    pKuroko->behave();
}

void EnemyRatislavia::processJudgement() {
    if (wasDeclaredEnd() == false && isOutOfUniverse()) {
        sayonara(600);
    }
}

void EnemyRatislavia::onHit(GgafActor* prm_pOtherActor) {

}

void EnemyRatislavia::onCatchEvent(hashval prm_no, void* prm_pSource) {
    if (prm_no == RATISLAVIA_EXPLOSION) {
        _DTRACE_("EnemyRatislavia::onCatchEvent RATISLAVIA_EXPLOSION �L���b�`");
        setHitAble(false);
        getProgress()->change(PROG_EXPLOSION);
    }
}

int EnemyRatislavia::isOutOfView() {
    //����O���薳��
    return 0;
}

bool EnemyRatislavia::isOutOfUniverse() {
    if (GgafDxCore::GgafDxUniverse::_x_gone_left < _x) {
        return false;
    } else {
        return true;
    }
}

EnemyRatislavia::~EnemyRatislavia() {
}
