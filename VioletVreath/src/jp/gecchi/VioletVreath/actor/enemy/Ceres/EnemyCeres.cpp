#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyCeres::EnemyCeres(const char* prm_name, GgafActorDepository* prm_pDepo_EnemyCeresShots001) :
        DefaultMeshSetActor(prm_name, "Ceres", STATUS(EnemyCeres)) {
    _class_name = "EnemyCeres";
    iMovePatternNo_ = 0;
    _X = -356000; //�J�n���W
    _Y = 0;
    _Z = -680000;
    X_turn_ = GgafDxCamera::_X_ScreenRight - 30000;
    Y_turn_ = -10000;
    Z_turn_ = 0;

    if (prm_pDepo_EnemyCeresShots001 == NULL) {
        //���L�̒e�������ɖ��w��̏ꍇ
        //�e�X�g�b�N�쐬
        pDepo_EnemyCeresShots001_ = NEW GgafActorDepository("RotEnemyMeshS001");
        EnemyCeresShot001* pCeresShot001;
        for (int i = 0; i < 32; i++) {
            pCeresShot001 = NEW EnemyCeresShot001("EnemyMeshShot");
            pCeresShot001->inactivateTreeImmed(); //�ŏ���\��
            pDepo_EnemyCeresShots001_->addSubLast(pCeresShot001);
        }
        addSubGroup(pDepo_EnemyCeresShots001_);
        createGgafActorDepository_ = true;
    } else {
        //���L�̒e���w�肳��Ă�̏ꍇ
        pDepo_EnemyCeresShots001_ = prm_pDepo_EnemyCeresShots001;
        createGgafActorDepository_ = false;
    }

    pSplLineCon_ = connectToSplineLineManager("SpCon_001");
    pProgram_CeresMove_ = NEW FixedVelocitySplineSequence(_pKurokoA, pSplLineCon_->use(), 5000); //�ړ����x�Œ�

//    pProgram_CeresMove_ = NEW FixedFrameSplineSequence(_pKurokoA, pSplLineCon_->use(), 600, 5000); //�ړ��t���[�����Œ�
    _pSeTransmitter->useSe(1);
    _pSeTransmitter->set(0, "a_shot", GgafRepeatSeq::nextVal("CH_a_shot"));
}

void EnemyCeres::initialize() {
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliAAB(0, -30000, -30000, 30000, 30000);
}

void EnemyCeres::onActive() {
    setHitAble(true);
    _pStatus->reset();
    iMovePatternNo_ = 0;
    frame_Active_ = 0;
    _pKurokoA->relateFaceAngWithMvAng(true);
    _pKurokoA->setFaceAngVelo(AXIS_X, 6000);
    _pKurokoA->setFaceAngVelo(AXIS_X, 6000);
    _pKurokoA->setMvVelo(8000);
    pProgram_CeresMove_->exec(ABSOLUTE_COORD); //�X�v���C���ړ����J�n
    frame_Active_ = 0;
}

void EnemyCeres::processBehavior() {
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    //�����]��
    if (iMovePatternNo_ == 0 && _X > 400000) {

        angle way[32];
        //GgafDxUtil::getWayAngle2D(180000, 8, 10000, way);
        GgafDxUtil::getRadialAngle2D(0, 32, way);
        GgafDxDrawableActor* pTama;
        for (int i = 0; i < 16; i++) {
            pTama = (GgafDxDrawableActor*)pDepo_EnemyCeresShots001_->dispatch();
            if (pTama) {
                pTama->locate(_X, _Y, _Z);
                pTama->_pKurokoA->setRzRyMvAng(-D90ANG + way[i], D90ANG);
            }
        }
        for (int i = 16; i < 32; i++) {
            pTama = (GgafDxDrawableActor*)pDepo_EnemyCeresShots001_->dispatch();
            if (pTama) {
                pTama->locate(_X, _Y, _Z);
                pTama->_pKurokoA->setRzRyMvAng(-D90ANG - way[i], -D90ANG);
            }
        }

        iMovePatternNo_++;
    }
    pProgram_CeresMove_->behave(); //�X�v���C���ړ���i�߂�
    _pKurokoA->behave(); //���̍��W�ֈړ�
    //_pSeTransmitter->behave();
    frame_Active_++;
}

void EnemyCeres::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}


void EnemyCeres::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    //�E�E�E�R�R�Ƀq�b�g���ꂽ�G�t�F�N�g
    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        //�j�󂳂ꂽ�ꍇ
        setHitAble(false);
        _pSeTransmitter->play3D(0);
        GgafDxDrawableActor* pExplo001 = (GgafDxDrawableActor*)P_COMMON_SCENE->pDP_EffectExplosion001_->dispatch();
        if (pExplo001) {
            pExplo001->locateAs(this);
        }
        sayonara();
    }
}

void EnemyCeres::onInactive() {
    if (createGgafActorDepository_) {
        //�e�͒x��ĊJ��������悤�ɁA�������p�������邽�߈ړ�
        getSceneDirector()->addSubLast(pDepo_EnemyCeresShots001_->getMyGroupHead()->extract());
       pDepo_EnemyCeresShots001_->sayonara(60 * 5);//����\��
    }
    sayonara();
}

bool EnemyCeres::isOutOfUniverse() {
    if (_X < GgafDxCamera::_X_ScreenLeft - 20000000) {
        return true;
    } else {
        return false;
    }
}

EnemyCeres::~EnemyCeres() {
    //static�Ȃ̂ōŏ��̂P�񂾂����������
    pSplLineCon_->close();
    DELETE_POSSIBLE_NULL(pProgram_CeresMove_);
}
