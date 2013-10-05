#include "stdafx.h"
#include "EnemyEres.h"

#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/core/actor/GgafGroupHead.h"
#include "jp/ggaf/core/actor/ex/GgafActorDepository.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/lib/util/spline/FixedVelocitySplineKurokoLeader.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Eres/EnemyEresShot001.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/scene/Universe.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyEres::EnemyEres(const char* prm_name, GgafActorDepository* prm_pDepo_EnemyEresShots001) :
        DefaultMeshSetActor(prm_name, "Eres", STATUS(EnemyEres)) {
    _class_name = "EnemyEres";
    iMovePatternNo_ = 0;
    _X = -356000; //�J�n���W
    _Y = 0;
    _Z = -680000;
    X_turn_ = P_CAM->_X_buffer_right - 30000;
    Y_turn_ = -10000;
    Z_turn_ = 0;

    if (prm_pDepo_EnemyEresShots001 == nullptr) {
        //���L�̒e�������ɖ��w��̏ꍇ
        //�e�X�g�b�N�쐬
        pDepo_EnemyEresShots001_ = NEW GgafActorDepository("RotEnemyMeshS001");
        EnemyEresShot001* pEresShot001;
        for (int i = 0; i < 32; i++) {
            pDepo_EnemyEresShots001_->put(NEW EnemyEresShot001("EnemyMeshShot"));
        }
        addSubGroup(pDepo_EnemyEresShots001_);
        createGgafActorDepository_ = true;
    } else {
        //���L�̒e���w�肳��Ă�̏ꍇ
        pDepo_EnemyEresShots001_ = prm_pDepo_EnemyEresShots001;
        createGgafActorDepository_ = false;
    }

    pSplLineConnection_ = connect_SplineLineManager("Spl_001");
    pProgram_EresMove_ = NEW FixedVelocitySplineKurokoLeader(_pKurokoA, pSplLineConnection_->peek(), 5000); //�ړ����x�Œ�

//    pProgram_EresMove_ = NEW FixedFrameSplineKurokoLeader(_pKurokoA, pSplLineConnection_->peek(), 600, 5000); //�ړ��t���[�����Œ�
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
}

void EnemyEres::initialize() {
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB(0, -30000, -30000, 30000, 30000);
}

void EnemyEres::onActive() {
    setHitAble(true);
    _pStatus->reset();
    iMovePatternNo_ = 0;
    frame_Active_ = 0;
    _pKurokoA->relateMvFaceAng(true);
    _pKurokoA->setFaceAngVelo(AXIS_X, 6000);
    _pKurokoA->setMvVelo(8000);
    pProgram_EresMove_->start(SplineKurokoLeader::ABSOLUTE_COORD); //�X�v���C���ړ����J�n
    frame_Active_ = 0;
}

void EnemyEres::processBehavior() {
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    //�����]��
    if (iMovePatternNo_ == 0 && _X > 400000) {

        angle way[32];
        //UTIL::getWayAngle2D(180000, 8, 10000, way);
        UTIL::getRadialAngle2D(0, 32, way); //TODO:���񋁂߂�͖̂���
        GgafDxDrawableActor* pTama;
        for (int i = 0; i < 16; i++) {
            pTama = (GgafDxDrawableActor*)pDepo_EnemyEresShots001_->dispatch();
            if (pTama) {
                pTama->position(_X, _Y, _Z);
                pTama->_pKurokoA->setRzRyMvAng(-D90ANG + way[i], D90ANG);
            }
        }
        for (int i = 16; i < 32; i++) {
            pTama = (GgafDxDrawableActor*)pDepo_EnemyEresShots001_->dispatch();
            if (pTama) {
                pTama->position(_X, _Y, _Z);
                pTama->_pKurokoA->setRzRyMvAng(-D90ANG - way[i], -D90ANG);
            }
        }

        iMovePatternNo_++;
    }
    pProgram_EresMove_->behave(); //�X�v���C���ړ���i�߂�
    _pKurokoA->behave(); //���̍��W�ֈړ�
    //_pSeTx->behave();
    frame_Active_++;
}

void EnemyEres::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}


void EnemyEres::onHit(GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::proceedEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //�j��
        _pSeTx->play3D(SE_EXPLOSION);
    } else {
        //��j��
    }
}

void EnemyEres::onInactive() {
    if (createGgafActorDepository_) {
        //�e�͒x��ĊJ��������悤�ɁA�������p�������邽�߈ړ�
        getSceneDirector()->addSubLast(pDepo_EnemyEresShots001_->getMyGroupHead()->extract());
        pDepo_EnemyEresShots001_->sayonara(60 * 5);//����\��
    }
    sayonara();
}

bool EnemyEres::isOutOfUniverse() {
    if (_X < P_CAM->_X_buffer_left - 20000000) {
        return true;
    } else {
        return false;
    }
}

EnemyEres::~EnemyEres() {
    //static�Ȃ̂ōŏ��̂P�񂾂����������
    pSplLineConnection_->close();
    GGAF_DELETE_NULLABLE(pProgram_EresMove_);
}
