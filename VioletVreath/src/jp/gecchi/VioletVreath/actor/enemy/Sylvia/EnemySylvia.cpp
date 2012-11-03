#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemySylvia::EnemySylvia(const char* prm_name, const char* prm_model, coord prm_r1, coord prm_r2) :
        CubeMapMeshActor(prm_name, prm_model, STATUS(EnemySylvia)) {
    _class_name = "EnemySylvia";
    setCubeMap("BkSky_cubemap.dds", 0.4);
    r1_ = prm_r1;
    r2_ = prm_r2;
    colli_part_num_ = 16; //�����蔻�苅�̐�
    useProgress(PROG_NOTHING);
}

void EnemySylvia::addSubFkOnSurface(GgafDxGeometricActor* prm_pGeoActor, angle prm_angPos1, angle prm_angPos2) {
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
    double CX = 0;
    double CY = -r1_*-ANG_SIN(prm_angPos1);
    double CZ = -r1_*ANG_COS(prm_angPos1);
    angle angRz, angRy;
    UTIL::getRzRyAng((int)(X - CX), (int)(Y - CY), (int)(Z - CZ), angRz, angRy);
    //�{�[���Ƃ��Ēǉ�
    this->addSubFk(prm_pGeoActor, X, Y, Z, D0ANG, angRz, angRy);
}

void EnemySylvia::makeCollisionArea(int prm_nSphere){
    angle* paAngRadial = NEW angle[prm_nSphere];
    UTIL::getRadialAngle2D(0, prm_nSphere, paAngRadial);
    _pColliChecker->makeCollision(prm_nSphere);
    for (int i = 0; i < prm_nSphere; i++) {
        _pColliChecker->setColliSphere(
                i,
                0 , ANG_SIN(paAngRadial[i]) * r1_, ANG_COS(paAngRadial[i]) * r1_,
                r2_,
                false, true, true
                );
    }
    setSpecialDrawDepth(DRAW_DEPTH_LEVEL_BIGOBJ-2);
    DELETE_IMPOSSIBLE_NULL(paAngRadial);
}

void EnemySylvia::onCreateModel() {
//    _pModel->_pTextureBlinker->forceBlinkRange(0.7, 0.2, 3.0);
//    _pModel->_pTextureBlinker->setBlink(0.5);
//    _pModel->_pTextureBlinker->beat(60*20, 60*9, 60*3, -1);
}

void EnemySylvia::initialize() {
    makeCollisionArea(colli_part_num_);
    pColliArea_ = _pColliChecker->_pCollisionArea;
    setHitAble(true);
    setAlpha(1.00);
}

void EnemySylvia::onActive() {
    _pStatus->reset();
    _pProg->set(PROG_INIT);
}

void EnemySylvia::processBehavior() {
    switch (_pProg->get()) {
        case PROG_INIT: {
            _pProg->change(PROG_FLOAT_MOVE);
            break;
        }

        case PROG_FLOAT_MOVE: {
            //�C�x���g�҂�
            break;
        }

        case PROG_EXPLOSION: {
            if (_pProg->hasJustChanged()) {
                _TRACE_("EnemySylvia::processBehavior() _pProg=PROG_EXPLOSION ������`");
            }
            if (_pProg->getFrameInProgress() % 10 == 0) {
                //���X����
                //�����蔻�苅�t�߂ɔ����G�t�F�N�g���U��������
                GgafDxCollisionPart* pPart;
                GgafDxDrawableActor* pE;
                for (int j = 0; j < colli_part_num_; j++) {
                    pPart = pColliArea_->_papColliPart[j];
                    pE = employDelayFromCommon(EffectExplosion004, RND(1,10));
                    if (pE) {
                        pE->locate(_X + pPart->_cx + RND(-r2_, +r2_),
                                   _Y + pPart->_cy + RND(-r2_, +r2_),
                                   _Z + pPart->_cz + RND(-r2_, +r2_));
                    }
                }
            }


            if (_pProg->getFrameInProgress() == 480) {
                //�����ő傫������
                //�����蔻�苅�t�߂ɔ����G�t�F�N�g���U��������
                GgafDxCollisionPart* pPart;
                GgafDxDrawableActor* pE;
                for (int j = 0; j < colli_part_num_; j++) {
                    pPart = pColliArea_->_papColliPart[j];
                    pE = employFromCommon(EffectExplosion004);
                    if (pE) {
                        pE->locate(_X + pPart->_cx,
                                   _Y + pPart->_cy,
                                   _Z + pPart->_cz);
                    }
                }
                sayonara();
                _pProg->change(PROG_NOTHING);
            }
            break;
        }
        case PROG_NOTHING: {
            //�������̎�
            break;
        }
    }

    _pKurokoA->behave();
}

void EnemySylvia::processJudgement() {
    if (wasDeclaredEnd() == false && isOutOfUniverse()) {
        sayonara(600);
    }
}

void EnemySylvia::onHit(GgafActor* prm_pOtherActor) {

}
void EnemySylvia::onCatchEvent(hashval prm_no, void* prm_pSource) {
    if (prm_no == SYLVIA_EXPLOSION) {
        _TRACE_("EnemySylvia::onCatchEvent SYLVIA_EXPLOSION �L���b�`");
        setHitAble(false);
        _pProg->change(PROG_EXPLOSION);
    }

}
int EnemySylvia::isOutOfView() {
    //����O���薳��
    return 0;
}

EnemySylvia::~EnemySylvia() {
}