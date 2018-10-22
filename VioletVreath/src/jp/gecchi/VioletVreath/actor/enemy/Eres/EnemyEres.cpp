#include "EnemyEres.h"

#include "jp/ggaf/core/actor/GgafSceneMediator.h"
#include "jp/ggaf/core/actor/GgafGroupHead.h"
#include "jp/ggaf/core/actor/ex/GgafActorDepository.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxTrucker.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/ggaf/lib/util/spline/FixedFrameSplineTruckerLeader.h"
#include "jp/ggaf/lib/util/spline/FixedFrameSplineKurokoLeader.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Eres/EnemyEresShot001.h"
#include "jp/ggaf/lib/util/spline/FixedFrameSplineManufacture.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/Config.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

enum {
    SE_EXPLOSION ,
};

EnemyEres::EnemyEres(const char* prm_name, GgafActorDepository* prm_pDepo_EnemyEresShots001) :
        DefaultMeshSetActor(prm_name, "Eres", STATUS(EnemyEres)) {
    _class_name = "EnemyEres";
    iMovePatternNo_ = 0;
    _x = PX_C(-100); //�J�n���W
    _y = 0;
    _z = 0;
    if (prm_pDepo_EnemyEresShots001 == nullptr) {
        //���L�̒e�������ɖ��w��̏ꍇ
        //�e�X�g�b�N�쐬
        pDepo_shot001_ = NEW GgafActorDepository("Depo_EnemyEresShots");
        for (int i = 0; i < 32; i++) {
            pDepo_shot001_->put(NEW EnemyEresShot001("EnemyEresShot"));
        }
        appendGroupChild(pDepo_shot001_);
        createGgafActorDepository_ = true;
    } else {
        //���L�̒e���w�肳��Ă�̏ꍇ
        pDepo_shot001_ = prm_pDepo_EnemyEresShots001;
        createGgafActorDepository_ = false;
    }

    pSplManufConn_ = connectToSplineManufactureManager("EnemyEres_spline");
    SplineManufacture* pSplManuf = pSplManufConn_->peek();
    pSplineLeader_ = pSplManuf->createTruckerLeader(getTrucker());
//    ((FixedFrameSplineTruckerLeader*)pSplineLeader_)->setGravitationParam(200, PX_C(100));

    GgafDxSeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    getModel()->setSpecular(8.0, 2.0);
}

void EnemyEres::initialize() {
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAACube(0, PX_C(60));
}

void EnemyEres::onActive() {
    setHitAble(true);
    getStatus()->reset();
    iMovePatternNo_ = 0;
    GgafDxKuroko* const pKuroko = getKuroko();
    pKuroko->linkFaceAngByMvAng(true);
    pKuroko->setRollFaceAngVelo(2000);
//    pKuroko->setMvVelo(3000);
    pSplineLeader_->start(RELATIVE_COORD); //�X�v���C���ړ����J�n
}

void EnemyEres::processBehavior() {
    //�����]��
    if (iMovePatternNo_ == 0 && getActiveFrame() == 60*30) {

        angle way[32];
        //UTIL::getWayAngle2D(180000, 8, 10000, way);
        UTIL::getRadialAngle2D(0, 32, way); //TODO:���񋁂߂�͖̂���
        GgafDxFigureActor* pTama;
        for (int i = 0; i < 16; i++) {
            pTama = (GgafDxFigureActor*)pDepo_shot001_->dispatch();
            if (pTama) {
                pTama->setPositionAt(this);
                pTama->getKuroko()->setRzRyMvAng(-D90ANG + way[i], D90ANG);
            }
        }
        for (int i = 16; i < 32; i++) {
            pTama = (GgafDxFigureActor*)pDepo_shot001_->dispatch();
            if (pTama) {
                pTama->setPositionAt(this);
                pTama->getKuroko()->setRzRyMvAng(-D90ANG - way[i], -D90ANG);
            }
        }

        iMovePatternNo_++;
    }
    pSplineLeader_->behave(); //�X�v���C���ړ���i�߂�
    getTrucker()->behave();
    getKuroko()->behave(); //���̍��W�ֈړ�
    //getSeTransmitter()->behave();
}

void EnemyEres::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyEres::onHit(const GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //�j�󂳂ꂽ��(�X�^�~�i <= 0)
        getSeTransmitter()->play3D(SE_EXPLOSION);
        //sayonara();
    } else {
        //�j�󂳂�Ȃ�������(�X�^�~�i > 0)
    }
}

void EnemyEres::onInactive() {
    if (createGgafActorDepository_) {
        //�e�͒x��ĊJ��������悤�ɁA�������p�������邽�߈ړ�
        getMySceneMediator()->appendChild(pDepo_shot001_->getMyGroupHead()->extract());
        pDepo_shot001_->sayonara(60 * 5);//����\��
    }
    sayonara();
}

bool EnemyEres::isOutOfSpacetime() const {
    if (_x < (PX_C(CONFIG::GAME_BUFFER_WIDTH) / -2) - 20000000) {
        return true;
    } else {
        return false;
    }
}

EnemyEres::~EnemyEres() {
    //static�Ȃ̂ōŏ��̂P�񂾂����������
    pSplManufConn_->close();
    GGAF_DELETE_NULLABLE(pSplineLeader_);
}

