#include "EnemyGeria.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/CommonScene.h"

#include "jp/gecchi/VioletVreath/actor/effect/Blink/EffectBlink.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyGeria::EnemyGeria(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Geria", STATUS(EnemyGeria)) {
    _class_name = "EnemyGeria";
    pAxsMver_ = NEW GgafDxAxesMover(this);
    iMovePatternNo_ = 0;
    max_shots_ = 1;
    shot_num_ = 0;
    can_Shot_ = false;
    will_shot_ = false;
    velo_mv_begin_ = 0;
    frame_when_shot_ = 0;
    GgafDxSeTransmitterForActor* pSe = getSeTransmitter();
    pSe->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");     //����
    pSe->set(SE_FIRE     , "WAVE_ENEMY_FIRE_SHOT_001");     //����
    pAFader_ = NEW GgafDxAlphaFader(this);
    useProgress(PROG_BANPEI);
    migration_length_ = PX_C(10000);
    mvd_ = 0;
}

void EnemyGeria::onCreateModel() {
}

void EnemyGeria::initialize() {
    setHitAble(false);
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAABox_Cube(0, 45000);
    GgafDxKuroko* const pKuroko = getKuroko();
    pKuroko->setFaceAngVelo(AXIS_Z, -7000);
}

void EnemyGeria::onActive() {
    getStatus()->reset();
    setHitAble(true);
    will_shot_ = false;
    can_Shot_ = true;
    shot_num_ = 0;
    frame_when_shot_ = 0;
    GgafDxKuroko* const pKuroko = getKuroko();
    velo_mv_begin_ = pKuroko->getMvVelo(); //�����ړ����x��ۑ�
    pKuroko->setMvVelo(0);
    setRzFaceAng(0);
    setRxFaceAng(0);
    mvd_ = 0;
    getProgress()->reset(PROG_INIT);
}

void EnemyGeria::processBehavior() {
    GgafDxKuroko* const pKuroko = getKuroko();
    GgafProgress* const pProg = getProgress();

    switch (pProg->get()) {
        case PROG_INIT: {
            max_shots_ = 1; //�ړ����Ɍ������ł���V���b�g�̍ő��
            shot_num_ = 0;  //�������V���b�g��
            setHitAble(false);
            setAlpha(0);
            pProg->changeNext();
            break;
        }
        case PROG_ENTRY: {  //�o��
            EffectBlink* pEffectEntry = nullptr;
            if (pProg->hasJustChanged()) {
                pEffectEntry = UTIL::activateEntryEffectOf(this);
            }
            static const frame frame_of_summons = pEffectEntry->getFrameOfSummonsBegin();
            static const frame summoning_frames = pEffectEntry->getSummoningFrames();
            if (pProg->hasArrivedAt(frame_of_summons)) {
                pAFader_->transitionLinerUntil(1.0, summoning_frames);
            }
            if (pProg->hasArrivedAt(frame_of_summons + summoning_frames)) {
                setHitAble(true);
                pProg->changeNext();
            }
            break;
        }
        case PROG_MOVE: {  //�ړ�
            if (pProg->hasJustChanged()) {
                pKuroko->setMvVelo(velo_mv_begin_);
                will_shot_ = false;
            }
            if (will_shot_) {
                if (pProg->hasArrivedAt(frame_when_shot_)) {
                    pProg->change(PROG_FIRE);
                }
            } else {
                if (max_shots_ > shot_num_) {
                    MyShip* pM = P_MYSHIP;
                    if (pM->_z - 500000 < _z && _z < pM->_z + 500000 &&
                        pM->_y - 500000 < _y && _y < pM->_y + 500000 )
                    {
                        frame_when_shot_ = pProg->getFrame() + RND(1, 20); //�V���b�g�������߂܂ł̃��O��݂��ĎU��΂点��
                        will_shot_ = true;
                    }
                }
            }
            break;
        }
        case PROG_FIRE: {  //����
            if (pProg->hasJustChanged()) {
                pKuroko->setMvVelo(PX_C(3)); //����
                pKuroko->rollFaceAngTo(D180ANG, D_ANG(3), 0, TURN_CLOCKWISE); //�\������̂�����Ɖ�]
            }

            if (!pKuroko->isTurningFaceAng()) {
                MyShip* pM = P_MYSHIP;
                GgafDxGeometricActor* pLast =
                      UTIL::shotWay001(_x, _y, _z,
                                       pM->_x, pM->_y, pM->_z,
                                       getCommonDepository(Shot004),
                                       PX_C(10),
                                       10000, 100,
                                       3, 5, 0.9,
                                       EnemyGeria::callbackDispatched);
                if (pLast) {
                    shot_num_++;
                    will_shot_ = false;
                    effectFlush(3); //�t���b�V��
                    getSeTransmitter()->play3D(SE_FIRE);
                }
                pProg->change(PROG_MOVE);
            }
            break;
        }
        case PROG_LEAVE: {
            if (pProg->hasJustChanged()) {
                setHitAble(false);
                pKuroko->setMvVelo(0);
                UTIL::activateLeaveEffectOf(this);
                pAFader_->transitionLinerUntil(0.0, 30);
            }
            if (pProg->hasArrivedAt(60)) {
                sayonara();
                pProg->changeNothing(); //�����܂��I
            }
            break;
        }
        default :
            break;
    }
    pAxsMver_->behave();
    pKuroko->behave();
    pAFader_->behave();
    mvd_ += pKuroko->getMvVelo();
}

void EnemyGeria::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
    if (mvd_ > migration_length_) {
        getProgress()->change(PROG_LEAVE);
    }
}

void EnemyGeria::onInactive() {
    setHitAble(false);
}

void EnemyGeria::onHit(const GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //�j�󂳂ꂽ��(�X�^�~�i <= 0)
        getSeTransmitter()->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //�j�󂳂�Ȃ�������(�X�^�~�i > 0)
    }
}

EnemyGeria::~EnemyGeria() {
    GGAF_DELETE(pAFader_);
    GGAF_DELETE(pAxsMver_);
}

void EnemyGeria::callbackDispatched(GgafDxFigureActor* prm_pDispatched, int prm_dispatched_seq, int prm_set_seq) {
}

