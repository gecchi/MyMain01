#ifndef MYSHIP_H_
#define MYSHIP_H_

#define SH_NOMAL 0;
#define SH_LASER 1;

#define MAX_LEVEL_MOVE_SPEED 5
#define MIN_LEVEL_MOVE_SPEED 0


class MyShip : public DefaultMeshActor {

public:

	/** �^�[�{�����ǂ��� */
	bool _isTurbo;

	/** ����O�^�[�{�����ǂ��� */
	bool _isZTurbo;

	int _iVB_turbo;
	/** �ړ��X�s�[�h���x�� */
	int _lv_MoveSpeed;
	/** �ړ��X�s�[�h���x���ɑ�������ړ��X�s�[�h */
	int _iMoveSpeed;

	bool _isMoveZX;


	//�����͎�O�֒ʏ�ړ��J�n����X����]�p���x�̏����x
	//���̏ꍇ�͐��A��O�̏ꍇ�͂���� -1 ���悸��
	//Rotation axisX Velocity when I Begin To Move Z
	int _iRXVelo_BMZ;
	//�����͎�O�֒ʏ�ړ�����X����]�p���x�̊p�����x
	//���̏ꍇ�͐��A��O�̏ꍇ�͂���� -1 ���悸��
	//Rotation axisX Acceleration while I Move Z
	int _iRXAcce_MZ;
	//�����͎�O�ֈړ�����X����]�p���x�̏���p���x
	//�����p���x�͂���� -1 ���悸��
	//Rotation axisX Top Velocity while I Move Z
	int _iRXTopVelo_MZ;
	//�����͎�O�֒ʏ�Z�ړ�����X����]�p�̒�~�p�x�ʒu
	//Rotation axisX Stop Angle while I Move Z
	angle _iRXStopAng_MZ;

	//TURBO�ړ��J�n���̈ړ����x�̏����x
	//Move Velocity when I Begin To Move with Turbo
	int _iMVelo_BMT;
	//TURBO�ړ����̈ړ����x�̉����x(<0 �悾�񂾂�x���Ȃ�悤�ɂ��邽��)
	//Move Acceleration while I Move with Turbo
	int _iMAcce_MT;
	//TURBO�ړ����̈ړ����x�̍Œᑬ�x
	//Move Bottom Velocity while I Move with Turbo
	int _iMBtmVelo_MT;


	//�����͎�O��TURBO�ړ��J�n����X����]�p���x�̏����x
	//���̏ꍇ�͐��A��O�̏ꍇ�͂���� -1 ���悸��
	//Rotation axisX Velocity when I Begin To Move Z with Turbo
	int _iRXVelo_BMZT;
	//�����͎�O��TURBO�ړ�����X����]�p���x�̊p�����x(<0 �悾�񂾂��]�͂����Ȃ��Ȃ�悤�ɂ��邽��)
	//���̏ꍇ�͐��A��O�̏ꍇ�͂���� -1 ���悸��
	//Rotation axisX Acceleration while I Move Z with Turbo
	int _iRXAcce_MZT;
	//�����͎�O��TURBO�ړ�����X����]�p���x�̍Œᑬ�x
	//���̏ꍇ�͔͈͂� _iRXBtmVelo_MZT < X����]�p���x�� < 360,000
	//��O�̏ꍇ��     -360,000 < X����]�p���x�� < -1*_iRXBtmVelo_MZT
	//�Ƃ��āATURBO�ړ����Œ���̉�]�͂�ۏ؂���B
	//Rotation axisX Bottom Angle Velocity while I Move Z with Turbo
	int _iRXBtmVelo_MZT;
	//�����͎�O��TURBO�ړ�����TURBO�ړ����I���Ɣ��f�����X����]�p���x
	//���̏ꍇ�͐��A��O�̏ꍇ�͂���� -1 ���悸��
	//Rotation axisX Velocity when I Finish Moveing Z with Turbo
	int _iRXVelo_FMZT;









	//�����͎�O�ȊO�̒ʏ�ړ����A�����I��Angle0�ɖ߂낤�Ƃ���X����]�p���x�̏���p���x
	//�����p���x�͂���� -1 ���悸��
	//Rotation X Top Velocity while I do Not Move Z
	int _iRXTopVelo_NMZ;
	//�����͎�O�ȊO�̒ʏ�ړ����A�����I��Angle0�ɖ߂낤�Ƃ��鎞��X����]�p�����x(��������)
	//Rotation X Acceleration while I do Not Move Z
	int _iRXAcce_NMZ;


	int _iShotKind01;
	int _iShotKind02;
	int _iShotKind03;

	MyShip(string prm_name, string prm_xname);

	/**
	 * ��OverRide �ł���
	 */
	void initialize();

	/**
	 * ��OverRide �ł���
	 */
	void processBehavior();

 	/**
	 * ��OverRide �ł���
	 */
	void processJudgement();

	/**
	 * ��OverRide �ł���
	 */
 	void processOnHit(GgafActor* prm_pActor_Opponent);


 	void setMoveSpeedLv(int lv) {
 		_lv_MoveSpeed = lv;
 		_iMoveSpeed = _lv_MoveSpeed*1000;
 	}
 	//��ʉ��ֈړ�����X����]����
 	void beginTurboZX(int prm_VB);

 	//��ʎ�O�ֈړ�����X����]����
 	void beginTurboXY(int prm_VB);


 	void beginMoveZX(int prm_VB);

 	void beginMoveXY(int prm_VB);

 	//��ʉ��ֈړ��I��X����]����
 	void onMoveZFinish();
 	virtual ~MyShip();
};


#endif /*MYSHIP_H_*/

