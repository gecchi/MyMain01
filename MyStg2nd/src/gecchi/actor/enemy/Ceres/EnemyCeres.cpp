#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

GgafDx9Spline3D EnemyCeres::_spline;

EnemyCeres::EnemyCeres(const char* prm_name, GgafActorDispatcher* prm_pDispatcher_EnemyCeresShots001) :
    DefaultMeshEnemyActor(prm_name, "Ceres") {
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

    //�P���X�p�X�v���C���ړ��̒�`
    if (EnemyCeres::_spline._num_basepoint == 0) { //�P���X�N���X�łP�񂾂��쐬
        double p[][3] = { //        X ,        Y ,       Z
                           { -1024000 ,  -300000 ,  680000 },
                           {  -800000 ,   300000 ,  480000 },
                           {  -200000 ,  -300000 ,  200000 },
                           {   200000 ,   300000 ,  100000 },
                           {   400000 ,        0 ,       0 },
                           {   300000 ,        0 ,       0 },
                           {   200000 ,   200000 ,       0 },
                           {   100000 ,        0 ,  200000 },
                           {        0 ,  -200000 ,       0 },
                           {  -100000 ,        0 , -200000 },
                           {   300000 ,        0 ,       0 },
                           {        0 ,   300000 ,       0 },
                           {        0 ,        0 ,  300000 },
                           {  -300000 ,        0 ,       0 },
                           {        0 ,  -300000 ,       0 },
                           {        0 ,        0 , -300000 },
                           {  -800000 ,        0 ,       0 }
                        };
        EnemyCeres::_spline.init(p, 17, 0.2);
    }

    //Mover �ɓn���v���O�����I�u�W�F�N�g�𐶐����Ă���
    //_pProgram_CeresMove = NEW GgafDx9FixedVelocitySplineProgram(&EnemyCeres::_spline, 5000); //�ړ����x�Œ�
    _pProgram_CeresMove = NEW GgafDx9FixedFrameSplineProgram(&EnemyCeres::_spline, 600, 5000); //�ړ��t���[�����Œ�

    useSe1("a_shot");
}

void EnemyCeres::initialize() {
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliBox(0, -30000, -30000, 30000, 30000);
}

void EnemyCeres::onActive() {
    setHitAble(true);
    MyStgUtil::resetEnemyCeresStatus(_pStatus);
    _iMovePatternNo = 0;
    _dwFrame_Active = 0;
    _pMover->relateRzRyFaceAngToMvAng(true);
    _pMover->setFaceAngVelo(AXIS_X, 6000);
    _pMover->setFaceAngVelo(AXIS_X, 6000);
    _pMover->setMvVelo(8000);
    _pMover->executeSplineMoveProgram(_pProgram_CeresMove, 0); //�X�v���C���ړ����v���O�������Ă���
    _dwFrame_Active = 0;
}

void EnemyCeres::processBehavior() {
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    //�����]��
    if (_iMovePatternNo == 0 && _X > 400000) {

        angle way[32];
        //GgafDx9Util::getWayAngle2D(180000, 8, 10000, way);
        GgafDx9Util::getRadiationAngle2D(0, 32, way);
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

    _pMover->behave(); //���̍��W�ֈړ�
    _dwFrame_Active++;
}

void EnemyCeres::processJudgement() {
    if (isOutOfGameSpace()) {
        inactivate();
    }
}


void EnemyCeres::onHit(GgafActor* prm_pOtherActor) {
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
    //�E�E�E�R�R�Ƀq�b�g���ꂽ�G�t�F�N�g
    if (MyStgUtil::calcEnemyStamina(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        //�j�󂳂ꂽ�ꍇ
        setHitAble(false);
        playSe1();
        inactivate(); //TODO:����Ȃ�
        GgafDx9DrawableActor* pExplo001 = (GgafDx9DrawableActor*)GameGlobal::_pSceneCommon->_pDispatcher_EffectExplosion001->employ();
        if (pExplo001 != NULL) {
            pExplo001->setGeometry(this);
            pExplo001->activate();
        }
    }
}

void EnemyCeres::onInactive() {
    if (_createGgafActorDispatcher) {
        //�e�͒x��ĊJ��������悤�ɁA�������p�������邽�߈ړ�
        getLordActor()->addSubLast(_pDispatcher_EnemyCeresShots001->getGroupActor()->becomeIndependent());
       _pDispatcher_EnemyCeresShots001->sayonara(60 * 5);//����\��
    }
    sayonara();
}

bool EnemyCeres::isOutOfGameSpace() {
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
