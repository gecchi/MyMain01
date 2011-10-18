#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

EnemyCeres::EnemyCeres(const char* prm_name, GgafActorDepository* prm_pDepo_EnemyCeresShots001) :
        DefaultMeshSetActor(prm_name, "Ceres", STATUS(EnemyCeres)) {
    _class_name = "EnemyCeres";
    _iMovePatternNo = 0;
    _X = -356000; //�J�n���W
    _Y = 0;
    _Z = -680000;
    _X_turn = GgafDxCamera::_X_ScreenRight - 30000;
    _Y_turn = -10000;
    _Z_turn = 0;
    _veloBegin = 5000;



    if (prm_pDepo_EnemyCeresShots001 == NULL) {
        //���L�̒e�������ɖ��w��̏ꍇ
        //�e�X�g�b�N�쐬
        _pDepo_EnemyCeresShots001 = NEW GgafActorDepository("RotEnemyMeshS001");
        EnemyCeresShot001* pCeresShot001;
        for (int i = 0; i < 32; i++) {
            pCeresShot001 = NEW EnemyCeresShot001("EnemyMeshShot");
            pCeresShot001->inactivateTreeImmediately(); //�ŏ���\��
            _pDepo_EnemyCeresShots001->addSubLast(pCeresShot001);
        }
        addSubGroup(_pDepo_EnemyCeresShots001);
        _createGgafActorDepository = true;
    } else {
        //���L�̒e���w�肳��Ă�̏ꍇ
        _pDepo_EnemyCeresShots001 = prm_pDepo_EnemyCeresShots001;
        _createGgafActorDepository = false;
    }

    _pSplLineCon = connectSplineLineManager("SpCon_001");
    _pProgram_CeresMove = NEW FixedVelocitySplineSequence(_pKurokoA, _pSplLineCon->use(), 5000); //�ړ����x�Œ�

//    _pProgram_CeresMove = NEW FixedFrameSplineSequence(_pKurokoA, _pSplLineCon->use(), 600, 5000); //�ړ��t���[�����Œ�
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
    _iMovePatternNo = 0;
    _frame_Active = 0;
    _pKurokoA->relateFaceAngWithMvAng(true);
    _pKurokoA->setFaceAngVelo(AXIS_X, 6000);
    _pKurokoA->setFaceAngVelo(AXIS_X, 6000);
    _pKurokoA->setMvVelo(8000);
    _pProgram_CeresMove->exec(ABSOLUTE_COORD); //�X�v���C���ړ����J�n
    _frame_Active = 0;
}

void EnemyCeres::processBehavior() {
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    //�����]��
    if (_iMovePatternNo == 0 && _X > 400000) {

        angle way[32];
        //GgafDxUtil::getWayAngle2D(180000, 8, 10000, way);
        GgafDxUtil::getRadialAngle2D(0, 32, way);
        GgafDxDrawableActor* pTama;
        for (int i = 0; i < 16; i++) {
            pTama = (GgafDxDrawableActor*)_pDepo_EnemyCeresShots001->dispatch();
            if (pTama) {
                pTama->locate(_X, _Y, _Z);
                pTama->_pKurokoA->setRzRyMvAng(-D90ANG + way[i], D90ANG);
            }
        }
        for (int i = 16; i < 32; i++) {
            pTama = (GgafDxDrawableActor*)_pDepo_EnemyCeresShots001->dispatch();
            if (pTama) {
                pTama->locate(_X, _Y, _Z);
                pTama->_pKurokoA->setRzRyMvAng(-D90ANG - way[i], -D90ANG);
            }
        }

        _iMovePatternNo++;
    }
    _pProgram_CeresMove->behave(); //�X�v���C���ړ���i�߂�
    _pKurokoA->behave(); //���̍��W�ֈړ�
    //_pSeTransmitter->behave();
    _frame_Active++;
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
        GgafDxDrawableActor* pExplo001 = (GgafDxDrawableActor*)P_COMMON_SCENE->_pDP_EffectExplosion001->dispatch();
        if (pExplo001) {
            pExplo001->locateAs(this);
        }
        sayonara();
    }
}

void EnemyCeres::onInactive() {
    if (_createGgafActorDepository) {
        //�e�͒x��ĊJ��������悤�ɁA�������p�������邽�߈ړ�
        getSceneDirector()->addSubLast(_pDepo_EnemyCeresShots001->getMyGroupHead()->extract());
       _pDepo_EnemyCeresShots001->sayonara(60 * 5);//����\��
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
    _pSplLineCon->close();
    DELETE_POSSIBLE_NULL(_pProgram_CeresMove);
}
