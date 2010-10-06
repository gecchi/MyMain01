#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EnemyCeres::EnemyCeres(const char* prm_name, GgafActorDispatcher* prm_pDispatcher_EnemyCeresShots001) :
        DefaultMeshSetActor(prm_name, "Ceres") {
    _class_name = "EnemyCeres";
    MyStgUtil::resetEnemyCeresStatus(_pStatus);
    _iMovePatternNo = 0;
    _X = -356000; //�J�n���W
    _Y = 0;
    _Z = -680000;
    _X_turn = GgafDx9Camera::_X_ScreenRight - 30000;
    _Y_turn = -10000;
    _Z_turn = 0;
    _veloBegin = 5000;



    if (prm_pDispatcher_EnemyCeresShots001 == NULL) {
        //���L�̒e�������ɖ��w��̏ꍇ
        //�e�X�g�b�N�쐬
        _pDispatcher_EnemyCeresShots001 = NEW GgafActorDispatcher("RotEnemyMeshS001");
        EnemyCeresShot001* pCeresShot001;
        for (int i = 0; i < 32; i++) {
            pCeresShot001 = NEW EnemyCeresShot001("EnemyMeshShot");
            pCeresShot001->inactivateTreeImmediately(); //�ŏ���\��
            _pDispatcher_EnemyCeresShots001->addSubLast(pCeresShot001);
        }
        addSubGroup(_pDispatcher_EnemyCeresShots001);
        _createGgafActorDispatcher = true;
    } else {
        //���L�̒e���w�肳��Ă�̏ꍇ
        _pDispatcher_EnemyCeresShots001 = prm_pDispatcher_EnemyCeresShots001;
        _createGgafActorDispatcher = false;
    }

    _pSplineCon = (Spline3DConnection*)(pGOD->_pSpline3DManager->getConnection("SpCon_001"));
    //_pProgram_CeresMove = NEW GgafDx9FixedVelocitySplineProgram(&EnemyCeres::_spline, 5000); //�ړ����x�Œ�
    _pProgram_CeresMove = NEW GgafDx9FixedFrameSplineProgram(this, _pSplineCon->refer(), 600, 5000); //�ړ��t���[�����Œ�

    _pSeTransmitter->useSe(1);
    _pSeTransmitter->set(0, "a_shot", GgafRepeatSeq::nextVal("CH_a_shot"));
}

void EnemyCeres::initialize() {
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliAAB(0, -30000, -30000, 30000, 30000);
}

void EnemyCeres::onActive() {
    setHitAble(true);
    MyStgUtil::resetEnemyCeresStatus(_pStatus);
    _iMovePatternNo = 0;
    _frame_Active = 0;
    _pMover->relateRzRyFaceAngToMvAng(true);
    _pMover->setFaceAngVelo(AXIS_X, 6000);
    _pMover->setFaceAngVelo(AXIS_X, 6000);
    _pMover->setMvVelo(8000);
    _pProgram_CeresMove->begin(0); //�X�v���C���ړ����J�n
    _frame_Active = 0;
}

void EnemyCeres::processBehavior() {
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    //�����]��
    if (_iMovePatternNo == 0 && _X > 400000) {

        angle way[32];
        //GgafDx9Util::getWayAngle2D(180000, 8, 10000, way);
        GgafDx9Util::getRadialAngle2D(0, 32, way);
        GgafDx9DrawableActor* pTama;
        for (int i = 0; i < 16; i++) {
            pTama = (GgafDx9DrawableActor*)_pDispatcher_EnemyCeresShots001->employ();
            if (pTama != NULL) {
                pTama->setGeometry(_X, _Y, _Z);
                pTama->_pMover->setRzRyMvAng(-ANGLE90 + way[i], ANGLE90);
                pTama->activate();
            }
        }
        for (int i = 16; i < 32; i++) {
            pTama = (GgafDx9DrawableActor*)_pDispatcher_EnemyCeresShots001->employ();
            if (pTama != NULL) {
                pTama->setGeometry(_X, _Y, _Z);
                pTama->_pMover->setRzRyMvAng(-ANGLE90 - way[i], -ANGLE90);
                pTama->activate();
            }
        }

        _iMovePatternNo++;
    }
    _pProgram_CeresMove->behave(); //�X�v���C���ړ���i�߂�
    _pMover->behave(); //���̍��W�ֈړ�
    //_pSeTransmitter->behave();
    _frame_Active++;
}

void EnemyCeres::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}


void EnemyCeres::onHit(GgafActor* prm_pOtherActor) {
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
    //�E�E�E�R�R�Ƀq�b�g���ꂽ�G�t�F�N�g
    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        //�j�󂳂ꂽ�ꍇ
        setHitAble(false);
        _pSeTransmitter->play3D(0);
        GgafDx9DrawableActor* pExplo001 = (GgafDx9DrawableActor*)pCOMMONSCENE->_pDispatcher_EffectExplosion001->employ();
        if (pExplo001 != NULL) {
            pExplo001->setGeometry(this);
            pExplo001->activate();
        }
        sayonara();
    }
}

void EnemyCeres::onInactive() {
    if (_createGgafActorDispatcher) {
        //�e�͒x��ĊJ��������悤�ɁA�������p�������邽�߈ړ�
        getLordActor()->addSubLast(_pDispatcher_EnemyCeresShots001->getGroupActor()->extract());
       _pDispatcher_EnemyCeresShots001->sayonara(60 * 5);//����\��
    }
    sayonara();
}

bool EnemyCeres::isOutOfUniverse() {
    if (_X < GgafDx9Camera::_X_ScreenLeft - 20000000) {
        return true;
    } else {
        return false;
    }
}

EnemyCeres::~EnemyCeres() {
    //static�Ȃ̂ōŏ��̂P�񂾂����������
    DELETE_POSSIBLE_NULL(_pProgram_CeresMove);
}
