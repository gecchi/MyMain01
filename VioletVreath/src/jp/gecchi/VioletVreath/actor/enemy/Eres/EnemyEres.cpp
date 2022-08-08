#include "EnemyEres.h"

#include "jp/ggaf/core/actor/SceneMediator.h"
#include "jp/ggaf/core/actor/GroupHead.h"
#include "jp/ggaf/core/actor/ex/ActorDepository.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/ggaf/dx/actor/supporter/AxisVehicle.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/ggaf/dx/util/curve/FixedFrameCurveAxisVehicleLeader.h"
#include "jp/ggaf/dx/util/curve/FixedFrameCurveVecVehicleLeader.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Eres/EnemyEresShot001.h"
#include "jp/ggaf/dx/util/curve/FixedFrameCurveManufacture.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/Config.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

enum {
    SE_EXPLOSION ,
};

EnemyEres::EnemyEres(const char* prm_name, GgafCore::ActorDepository* prm_pDepo_EnemyEresShots001) :
        VvEnemyActor<DefaultMeshSetActor>(prm_name, "Eres", StatusReset(EnemyEres)) {
    _class_name = "EnemyEres";
    iMovePatternNo_ = 0;
    _x = PX_C(-100); //�J�n���W
    _y = 0;
    _z = 0;
    if (prm_pDepo_EnemyEresShots001 == nullptr) {
        //���L�̒e�������ɖ��w��̏ꍇ
        //�e�X�g�b�N�쐬
        pDepo_shot001_ = NEW GgafCore::ActorDepository("Depo_EnemyEresShots");
        for (int i = 0; i < 32; i++) {
            pDepo_shot001_->put(NEW EnemyEresShot001("EnemyEresShot"));
        }
        appendGroupChild(pDepo_shot001_);
        createActorDepository_ = true;
    } else {
        //���L�̒e���w�肳��Ă�̏ꍇ
        pDepo_shot001_ = prm_pDepo_EnemyEresShots001;
        createActorDepository_ = false;
    }

    pCurveManufConn_ = connectToCurveManufactureManager("EnemyEres_curve");
    pVehicleLeader_ = createCurveVehicleLeader(pCurveManufConn_->peek());
//    ((FixedFrameCurveAxisVehicleLeader*)pVehicleLeader_)->setGravitationParam(200, PX_C(100));

    GgafDx::SeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_EXPLOSION, "SE_EXPLOSION_001");
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
    GgafDx::VecVehicle* pVecVehicle = getVecVehicle();
    pVecVehicle->linkFaceAngByMvAng(true);
    pVecVehicle->setRollFaceAngVelo(2000);
//    pVecVehicle->setMvVelo(3000);
    pVehicleLeader_->start(RELATIVE_COORD); //�J�[�u�ړ����J�n
}

void EnemyEres::processBehavior() {
    //�����]��
    if (iMovePatternNo_ == 0 && getActiveFrame() == 60*30) {

        angle way[32];
        //UTIL::getWayAngle2D(180000, 8, 10000, way);
        UTIL::getRadialAngle2D(0, 32, way); //TODO:���񋁂߂�͖̂���
        GgafDx::FigureActor* pTama;
        for (int i = 0; i < 16; i++) {
            pTama = (GgafDx::FigureActor*)pDepo_shot001_->dispatch();
            if (pTama) {
                pTama->setPositionAt(this);
                pTama->getVecVehicle()->setRzRyMvAng(-D90ANG + way[i], D90ANG);
            }
        }
        for (int i = 16; i < 32; i++) {
            pTama = (GgafDx::FigureActor*)pDepo_shot001_->dispatch();
            if (pTama) {
                pTama->setPositionAt(this);
                pTama->getVecVehicle()->setRzRyMvAng(-D90ANG - way[i], -D90ANG);
            }
        }

        iMovePatternNo_++;
    }
    pVehicleLeader_->behave(); //�J�[�u�ړ���i�߂�
    getAxisVehicle()->behave();
    getVecVehicle()->behave(); //���̍��W�ֈړ�
    //getSeTransmitter()->behave();
}

void EnemyEres::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyEres::onHit(const GgafCore::Actor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDx::GeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //�j�󂳂ꂽ��(�X�^�~�i <= 0)
        getSeTransmitter()->play3D(SE_EXPLOSION);
        //sayonara();
    } else {
        //�j�󂳂�Ȃ�������(�X�^�~�i > 0)
    }
}

void EnemyEres::onInactive() {
    if (createActorDepository_) {
        //�e�͒x��ĊJ��������悤�ɁA�������p�������邽�߈ړ�
        getSceneMediator()->appendChild(pDepo_shot001_->getGroupHead()->extract());
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
    pCurveManufConn_->close();
    GGAF_DELETE_NULLABLE(pVehicleLeader_);
}

