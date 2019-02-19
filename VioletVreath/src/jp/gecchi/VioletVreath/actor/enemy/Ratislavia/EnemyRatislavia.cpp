#include "EnemyRatislavia.h"

#include "jp/ggaf/dx/actor/supporter/Kuroko.h"
#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/util/CollisionArea.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectExplosion004.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/CommonScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafLib;
using namespace VioletVreath;

enum {
    PROG_INIT      ,
    PROG_FLOAT_MOVE,
    PROG_EXPLOSION ,
    PROG_NOTHING   ,
    PROG_BANPEI,
};

EnemyRatislavia::EnemyRatislavia(const char* prm_name, const char* prm_model, coord prm_r1, coord prm_r2) :
        VvChikeiActor<CubeMapMeshActor>(prm_name, prm_model, StatusReset(EnemyRatislavia)) {
    _class_name = "EnemyRatislavia";
    setCubeMap("BkSky_cubemap.dds", 0.4);
    r1_ = prm_r1;
    r2_ = prm_r2;
    colli_part_num_ = 16; //�����蔻�苅�̐�
    useProgress(PROG_BANPEI);
}

void EnemyRatislavia::appendGroupChildAsFkOnSurface(GgafDx::GeometricActor* prm_pGeoActor, angle prm_ang1, angle prm_ang2) {
    //�g�[���X���f����ZY���ʂɉ~
    //�ʒu�����߂�
    //���s�ړ�( +r2_, +0, +0) > ang2��Y����] > ���s�ړ�( +0, +0, -r1_) > ang1��X����] �ϊ��s��� dx, dy, dz ���~����
    //
    //    | COS[ang2]    , -SIN[ang2]*-SIN[ang1]             , -SIN[ang2]*COS[ang1]             , 0 |
    //    | 0            ,  COS[ang1]                        ,  SIN[ang1]                       , 0 |
    //    | SIN[ang2]    ,  COS[ang2]*-SIN[ang1]             ,  COS[ang2]*COS[ans]              , 0 |
    //    | r2_*COS[ang2], (r2_*-SIN[ang2] + -r1_)*-SIN[ang1], (r2_*-SIN[ang2] + -r1_)*COS[ang1], 1 |
    //���
    double X = r2_*ANG_COS(prm_ang2);
    double Y = (r2_*-ANG_SIN(prm_ang2) - r1_) * -ANG_SIN(prm_ang1);
    double Z = (r2_*-ANG_SIN(prm_ang2) - r1_) *  ANG_COS(prm_ang1);

    //���������߂�
    //���s�ړ�( +0, +0, -r1_) > ang1��X����] �ϊ��s��� dx, dy, dz ���g�p
    //    | 1, 0              , 0             , 0 |
    //    | 0, COS[ang1]      , SIN[ang1]     , 0 |
    //    | 0, -SIN[ang1]     , COS[ang1]     , 0 |
    //    | 0, -r1_*-SIN[ang1], -r1_*COS[ang1], 1 |
    //���
    double X2 = 0;
    double Y2 = -r1_*-ANG_SIN(prm_ang1);
    double Z2 = -r1_*ANG_COS(prm_ang1);
    angle rz, ry;
    UTIL::convVectorToRzRy((int)(X - X2), (int)(Y - Y2), (int)(Z - Z2),
                            rz, ry);
    //�{�[���Ƃ��Ēǉ�
    this->appendGroupChildAsFk(prm_pGeoActor, X, Y, Z, D0ANG, ry, rz);
}

void EnemyRatislavia::createCollisionAreaArea(int prm_nSphere) {
    angle* paAngRadial = NEW angle[prm_nSphere];
    UTIL::getRadialAngle2D(0, prm_nSphere, paAngRadial);
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(prm_nSphere);
    for (int i = 0; i < prm_nSphere; i++) {
        pChecker->setColliSphere(
                    i,
                    0 , ANG_SIN(paAngRadial[i]) * r1_, ANG_COS(paAngRadial[i]) * r1_,
                    r2_,
                    false, true, true
                    );
    }
    setSpecialRenderDepthIndex(RENDER_DEPTH_INDEX_BACK-2);
    GGAF_DELETE(paAngRadial);
}

void EnemyRatislavia::onCreateModel() {
}

void EnemyRatislavia::initialize() {
    createCollisionAreaArea(colli_part_num_);
    setHitAble(true);
}

void EnemyRatislavia::onActive() {
    getStatus()->reset();
    getProgress()->reset(PROG_INIT);
}

void EnemyRatislavia::processBehavior() {
    GgafDx::Kuroko* const pKuroko = getKuroko();
    GgafCore::Progress* const pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            setAlpha(0);
            getAlphaFader()->transitionLinearUntil(1.0, 30*60);
            pProg->change(PROG_FLOAT_MOVE);
            break;
        }

        case PROG_FLOAT_MOVE: {
            //�C�x���g�҂�
            break;
        }

        case PROG_EXPLOSION: {
            if (pProg->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" _pProg=PROG_EXPLOSION ������`");
            }
            if (pProg->getFrame() % 16U == 0) {
                //���X����
                //�����蔻�苅�t�߂ɔ����G�t�F�N�g���U��������
                GgafDx::CollisionPart* pPart;
                GgafDx::FigureActor* pE;
                CollisionChecker* pChecker = getCollisionChecker();
                for (int j = 0; j < colli_part_num_; j++) {
                    pPart = pChecker->getArea()->getPart(j);
                    pE = dispatchDelayFromCommon(EffectExplosion004, RND(1,10));
                    if (pE) {
                        pE->setPosition(_x + pPart->_cx + RND(-r2_, +r2_),
                                        _y + pPart->_cy + RND(-r2_, +r2_),
                                        _z + pPart->_cz + RND(-r2_, +r2_));
                    }
                }
            }


            if (pProg->hasArrivedAt(480)) {
                //�����ő傫������
                //�����蔻�苅�t�߂ɔ����G�t�F�N�g���U��������
                GgafDx::CollisionPart* pPart;
                GgafDx::FigureActor* pE;
                CollisionChecker* pChecker = getCollisionChecker();
                for (int j = 0; j < colli_part_num_; j++) {
                    pPart = pChecker->getArea()->getPart(j);
                    pE = dispatchFromCommon(EffectExplosion004);
                    if (pE) {
                        pE->setPosition(_x + pPart->_cx,
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
    getAlphaFader()->behave();
}

void EnemyRatislavia::processJudgement() {
    if (wasDeclaredEnd() == false && isOutOfSpacetime()) {
        sayonara(600);
    }
}

void EnemyRatislavia::onHit(const GgafCore::Actor* prm_pOtherActor) {

}

void EnemyRatislavia::onCatchEvent(hashval prm_no, void* prm_pSource) {
    if (prm_no == RATISLAVIA_EXPLOSION) {
        _TRACE_(FUNC_NAME<<" RATISLAVIA_EXPLOSION �L���b�`");
        setHitAble(false);
        getProgress()->change(PROG_EXPLOSION);
    }
}

int EnemyRatislavia::isOutOfView() {
    //����O���薳��
    return 0;
}

bool EnemyRatislavia::isOutOfSpacetime() const {
    Spacetime* pSpacetime =  pGOD->getSpacetime();
    if (pSpacetime->_x_bound_left <= _x) {
        return false;
    } else {
        return true;
    }
}

EnemyRatislavia::~EnemyRatislavia() {
}
