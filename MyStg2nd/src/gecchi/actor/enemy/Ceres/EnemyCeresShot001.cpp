#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EnemyCeresShot001::EnemyCeresShot001(const char* prm_name) : DefaultMeshEnemyActor(prm_name, "myvic") {
    _class_name = "EnemyCeresShot001";
    MyStgUtil::resetEnemyCeresShot001Status(_pStatus);
    inactivateTree();

    /** �o�����̏��� */
    _iMvVelo_1st = 13000;
    /** �o�����̉����x�i���Œx���Ȃ�j */
    _iMoveAcce_1st = -150;
    /** ���g���o�����Ă���A���@�̕����ɕ����]�����J�n����t���[�� */
    _dwFrame_TurnBegin = 60;
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
    useSe1("break_glass01");
}

void EnemyCeresShot001::initialize() {
    _pMover->setVxMvVeloRenge(_iMvVelo_Top, _iMvVelo_Bottom);
    _pMover->relateRzRyFaceAngToMvAng(true);

    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliBox(0, -30000, -30000, 30000, 30000);
    setHitAble(true);
}

void EnemyCeresShot001::onActive() {
    MyStgUtil::resetEnemyCeresShot001Status(_pStatus);

    //�o����
    _pMover->setMvVelo(_iMvVelo_1st);
    _pMover->setMvAcce(_iMoveAcce_1st);

    _frame_on_change_to_active_flg = 0;
    setHitAble(true);
}

void EnemyCeresShot001::processBehavior() {
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

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

    //addNextAnimationFrame();
    //���W�ɔ��f
    _pMover->behave();

}

void EnemyCeresShot001::processJudgement() {
    if (isOutOfGameSpace()) {
        inactivate();
    }
}

void EnemyCeresShot001::onHit(GgafActor* prm_pOtherActor) {
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
    //�����Ƀq�b�g�G�t�F�N�g
    if (MyStgUtil::calcEnemyStamina(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        //�����ɏ��ŃG�t�F�N�g
        playSe1();
        setHitAble(false);
        inactivate();
        EffectExplosion001* pExplo001 =
                (EffectExplosion001*)GameGlobal::_pSceneCommon->_pDispatcher_EffectExplosion001->employ();
        if (pExplo001 != NULL) {
            pExplo001->setGeometry(this);
            pExplo001->activate();
        }
    }
}

void EnemyCeresShot001::onInactive() {
    //�f�B�X�p�b�`���ɖ߂邾���Ȃ̂�adios�s�v�H
    //adios();
}

EnemyCeresShot001::~EnemyCeresShot001() {
}
