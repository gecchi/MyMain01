#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EnemyMeshShot001::EnemyMeshShot001(string prm_name, string prm_model) : DefaultMeshEnemyActor(prm_name, prm_model) {
	_class_name = "EnemyMeshShot001";

	declareStop();

	/** �o�����̏��� */
	_iMoveVelocity_1st = 10000;
	/** �o�����̉����x�i���Œx���Ȃ�j */
	_iMoveAcceleration_1st = -150;
	/** ���g���o�����Ă���A���@�̕����ɕ����]�����J�n����t���[�� */
	_dwFrame_TurnBegin = 50;
	/** �ړ����x��� */
	_iMoveVelocity_Top = 30000;
	/** �Œ�ۏ؈ړ����x */
	_iMoveVelocity_Bottom = 0;
	/** �����]���ɔ�₷���Ƃ��ł���t���[���� */
	_dwFrameInterval_Turn = 100;
	/** �����]�����̊p���x�A���O���l */
	_angVelocity_Turn = 5000;
	/** �����]�����J�n�i_dwFrame_TurnBegin�j����Đݒ肳�������x */
	_iMoveAcceleration_2nd = 300;

	_dwFrame_switchedToPlay = 0;
}

void EnemyMeshShot001::initialize() {
	_pGeoMover -> setXMoveVelocityRenge(_iMoveVelocity_Top, _iMoveVelocity_Bottom);
	_pGeoMover -> _synchronize_ZAxisRotAngle_to_MoveAngleRz_Flg = true;
	_pGeoMover -> _synchronize_YAxisRotAngle_to_MoveAngleRy_Flg = true;


	_pChecker -> useHitAreaBoxNum(1);
	_pChecker -> setHitAreaBox(0, -10000, -10000, 10000, 10000);
	setBumpableAlone(true);
}



void EnemyMeshShot001::processBehavior() {
	if (switchedToPlay()) {
		//�o����
		_pGeoMover -> setMoveVelocity(_iMoveVelocity_1st);
		_pGeoMover -> setMoveAcceleration(_iMoveAcceleration_1st);

		_dwFrame_switchedToPlay = 0;
		setBumpableAlone(true);
	} else {

//		_pGeoMover->setMoveAngle(
//				GameGlobal::_pMyShip->_X,
//				GameGlobal::_pMyShip->_Y,
//				GameGlobal::_pMyShip->_Z
//				);

//		angle angRz_Target;
//		angle angRy_Target;
//		double dummy1,dummy2,dummy3;
//		GgafDx9Util::getRotAngleZY(
//				GameGlobal::_pMyShip->_X - _X,
//				GameGlobal::_pMyShip->_Y - _Y,
//				GameGlobal::_pMyShip->_Z - _Z,
//				angRz_Target,
//				angRy_Target
//				);
//		_pGeoMover -> setMoveAngleRz(angRz_Target);
//		_pGeoMover -> setMoveAngleRy(angRy_Target);

		_dwFrame_switchedToPlay++;
		//�����]���J�n
		if (_dwFrame_switchedToPlay == _dwFrame_TurnBegin) {
			angle angRz_Target;
			angle angRy_Target;
			GgafDx9Util::getRotAngleZY(
					GameGlobal::_pMyShip->_X - _X,
					GameGlobal::_pMyShip->_Y - _Y,
					GameGlobal::_pMyShip->_Z - _Z,
					angRz_Target,
					angRy_Target
				);
			if (_pGeoMover->getDistanceFromMoveAngleRzTo(angRz_Target, TURN_CLOSE_TO) > 0) {
				_pGeoMover -> setMoveAngleRzVelocity(_angVelocity_Turn);
			} else {
				_pGeoMover -> setMoveAngleRzVelocity(-1 * _angVelocity_Turn);
			}
			if (_pGeoMover->getDistanceFromMoveAngleRyTo(angRy_Target, TURN_CLOSE_TO) > 0) {
				_pGeoMover -> setMoveAngleRyVelocity(_angVelocity_Turn);
			} else {
				_pGeoMover -> setMoveAngleRyVelocity(-1 * _angVelocity_Turn);
			}
			_pGeoMover -> setTargetMoveAngleRy(angRy_Target);
			_pGeoMover -> setTargetMoveAngleRz(angRz_Target);

			_pGeoMover -> setMoveAcceleration(_iMoveAcceleration_2nd);
		}


		//�����]���I��
		if (_dwFrame_switchedToPlay == _dwFrame_TurnBegin+_dwFrameInterval_Turn) {
			_pGeoMover -> setMoveAngleRzVelocity(0);
			_pGeoMover -> setMoveAngleRyVelocity(0);
			_pGeoMover -> _auto_move_angle_ry_target_Flg = false;
			_pGeoMover -> _auto_move_angle_rz_target_Flg = false;
		}


	}



	//nextAnimationFrame();
	//���W�ɔ��f
	_pGeoMover -> behave();

}

void EnemyMeshShot001::processJudgement() {
	if (isOffScreen()) {
		declareStop();
		//declareFinishLife();
	}
}

bool EnemyMeshShot001::isOffScreen() {
	if (_X < _X_OffScreenLeft) {
		return true;
	} else {
		if (_X > _X_OffScreenRight) {
			return true;
		} else {
			if (_Y > _Y_OffScreenTop) {
				return true;
			} else {
				if (_Y < _Y_OffScreenBottom) {
					return true;
				} else {
					if (_Z < GgafDx9God::_dCamZ*LEN_UNIT*10) {
						return true;
					} else {
						if (_Z > -1* GgafDx9God::_dCamZ*LEN_UNIT*10) {
							return true;
						} else {
							return false;
						}
					}
				}
			}
		}
	}
}

void EnemyMeshShot001::processOnHit(GgafActor* prm_pActor_Opponent) {
	//_TRACE_("EnemyMeshShot001�q�b�g���܂����B("<<_X<<","<<_Y<<")");
	//declareFinishLife();
	setBumpableAlone(false);
	declareStop();
	EffectExplosion001* pExplo001 = (EffectExplosion001*)GameGlobal::_pSceneCommon->_pEffectExplosion001Rotation->obtain();
	if (pExplo001 != NULL) {
		pExplo001->setGeometry(this);
		pExplo001->declarePlay();
	}
}


EnemyMeshShot001::~EnemyMeshShot001() {
}
