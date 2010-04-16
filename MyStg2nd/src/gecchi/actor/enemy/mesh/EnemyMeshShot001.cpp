#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EnemyMeshShot001::EnemyMeshShot001(const char* prm_name) : DefaultMeshSetActor(prm_name, "vic2") {
    _class_name = "EnemyMeshShot001";

    inactivateTree();

    /** �o�����̏��� */
    _iMvVelo_1st = 10000;
    /** �o�����̉����x�i���Œx���Ȃ�j */
    _iMoveAcce_1st = -150;
    /** ���g���o�����Ă���A���@�̕����ɕ����]�����J�n����t���[�� */
    _dwFrame_TurnBegin = 50;
    /** �ړ����x��� */
    _iMvVelo_Top = 30000;
    /** �Œ�ۏ؈ړ����x */
    _iMvVelo_Bottom = 0;
    /** �����]���ɔ�₷���Ƃ��ł���t���[���� */
    _dwFrameInterval_Turn = 400;
    /** �����]�����̊p���x�A���O���l(���̒l) */
    _angVelo_Turn = 7000;
    /** �����]�����J�n�i_dwFrame_TurnBegin�j����Đݒ肳�������x */
    _iMoveAcce_2nd = 100;

    _frame_on_change_to_active_flg = 0;
    prepareSe(0, "bomb1", GgafRepeatSeq::nextVal("CH_bomb1"));
}

void EnemyMeshShot001::initialize() {
    _pMover->forceVxMvVeloRange(_iMvVelo_Top, _iMvVelo_Bottom);
    _pMover->relateRzRyFaceAngToMvAng(true);

    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliBox(0, -30000, -30000, 30000, 30000);
    setHitAble(true);
}

void EnemyMeshShot001::processBehavior() {
    if (onChangeToActive()) {
        //�o����
        _pMover->setMvVelo(_iMvVelo_1st);
        _pMover->setMvAcce(_iMoveAcce_1st);

        _frame_on_change_to_active_flg = 0;
        setHitAble(true);
    } else {


        _frame_on_change_to_active_flg++;
        //�����]���J�n
        if (_frame_on_change_to_active_flg == _dwFrame_TurnBegin) {

            _pMover->execTagettingMvAngSequence(GameGlobal::_pMyShip,
                                                       _angVelo_Turn, 0,
                                                       TURN_CLOSE_TO);
            _pMover->setMvAcce(_iMoveAcce_2nd);
        }

        //�����]���I��
        if (_frame_on_change_to_active_flg == _dwFrame_TurnBegin + _dwFrameInterval_Turn) {
            _pMover->setRzMvAngVelo(0);
            _pMover->setRyMvAngVelo(0);
            _pMover->_mv_ang_ry_target_flg = false;
            _pMover->_mv_ang_rz_target_flg = false;
        }

    }

    //behaveUvFlip();
    //���W�ɔ��f
    _pMover->behave();

}

void EnemyMeshShot001::processJudgement() {
    if (isOutOfGameSpace()) {
        inactivateTree();
        //sayonara();
    }
}

void EnemyMeshShot001::onHit(GgafActor* prm_pOtherActor) {
    //_TRACE_("EnemyMeshShot001�q�b�g���܂����B("<<_X<<","<<_Y<<")");
    //sayonara();
    playSe3D(0);
    setHitAble(false);
    inactivateTree();
    EffectExplosion001* pExplo001 =
            (EffectExplosion001*)GameGlobal::_pSceneCommon->_pDispatcher_EffectExplosion001->employ();
    if (pExplo001 != NULL) {
        pExplo001->setGeometry(this);
        pExplo001->activate();
    }
}

EnemyMeshShot001::~EnemyMeshShot001() {
}
