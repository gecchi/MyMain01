#ifndef MYSHIP_H_
#define MYSHIP_H_

#define SH_NOMAL 0;
#define SH_LASER 1;

#define MAX_LEVEL_MOVE_SPEED 5
#define MIN_LEVEL_MOVE_SPEED 0

#define EQ_OPTION 1
#define EQ_MAX_OPTION 8

enum MoveWay {
	NONE,
	UP,
	UP_FRONT,
	UP_BEHIND,
	DOWN,
	DOWN_FRONT,
	DOWN_BEHIND,
	FRONT,
	BEHIND,
	ZLEFT,
	ZLEFT_FRONT,
	ZLEFT_BEHIND,
	ZRIGHT,
	ZRIGHT_FRONT,
	ZRIGHT_BEHIND
};

class MyShip : public DefaultMeshActor {

	class State {
 	public:
 		int eq_option;
 		int eq_speed;
 		State() {
 			eq_option = 0;
 			eq_speed = 1;
 		};

 	};


	struct VERTEX{
		float x, y, z;    // ���_���W
		float nx, ny, nz; // �@��
		DWORD color;      // ���_�̐F
		float tu, tv;     // �e�N�X�`�����W
	};

public:
	int _tmpX;
	int _tmpY;
	int _tmpZ;

	/** XY�^�[�{�I������(Frame) */
	DWORD _dwFrameNextXYTurboOut;

	/** XY�^�[�{����(Frame) */
	DWORD _dwIntervalXYTurbo;

	/** ZX�^�[�{�I������(Frame) */
	DWORD _dwFrameNextZXTurboOut;

	/** ZX�^�[�{����(Frame) */
	DWORD _dwIntervalZXTurbo;

	/** �^�[�{���A�ړ����p */
	MoveWay _wayTurbo;

	/** �ړ��X�s�[�h���x�� */
	int _lv_MoveSpeed;
	/** �ړ��X�s�[�h���x���ɑ�������ړ��X�s�[�h */
	int _iMoveSpeed;

	bool _isMoveZX;


	/** TURBO�ړ��J�n���̈ړ����x�̏����x */
	int _iMvVelo_BeginMT;		//Move Velocity when I Begin To Move with Turbo
								//Z�������ޏꍇ�A���܂����̒l����v�Z���悤�iZ���̈ړ����x�͐����ŊǗ����Ă邽�߁j

	/** TURBO�ړ����̈ړ����x�̉����x */
	int _iMvAcce_MT;			//Move Acceleration while I Move with Turbo
								//�A�� �l < 0 �ł��邱�ƁB �悾�񂾂�x���Ȃ�悤�ɂ���������
								//�����Z�������ޏꍇ�A���܂����̒l����v�Z���悤

	/** TURBO�ړ����̈ړ����x�̍Œᑬ�x */
	int _iMvBtmVelo_MT;			//Move Bottom Velocity while I Move with Turbo
								//�A�� �l < 0 �ł��邱�ƁB
								//�����Z�������ޏꍇ�A���܂����̒l����v�Z���悤

	/** TURBO�ړ����I���Ɣ��f�����ړ����x */
	int _iMvVelo_FMT;			//Rotation axisX angle Velocity when I Finish Moveing with Turbo
								//�A�� �l < 0 �ł��邱�ƁB
								//�����Z�������ޏꍇ�A���܂����̒l����v�Z���悤

	/** TURBO���ɋt�����ɓ��͂���鎖�ɂ�茸�����鑬�x */
	int _iMvAcce_EOD_MT;		//Move Acceleration when I enter opposite direction while I Move with Turbo

	/** �����͎�O�֒ʏ�ړ��J�n����X����]�p���x�̏����x */
	angle _angRXVelo_BeginMZ;	//Rotation axisX angle Velocity when I Begin To Move Z
								//���̏ꍇ�͐��A��O�̏ꍇ�͂���� -1 ���悸��

	/** �����͎�O�֒ʏ�ړ�����X����]�p���x�̊p�����x */
	angle _angRXAcce_MZ;		//Rotation axisX angle Acceleration while I Move Z
								//���̏ꍇ�͐��A��O�̏ꍇ�͂���� -1 ���悸��

	/** �����͎�O�ֈړ�����X����]�p���x�̏���p���x */
	angle _angRXTopVelo_MZ;		//Rotation axisX Top angle Velocity while I Move Z
								//�����p���x�͂���� -1 ���悸��

	/** �����͎�O�֒ʏ�Z�ړ�����X����]�p�̒�~�p�x */
	angle _angRXStop_MZ;		//Rotation axisX Stop angle while I Move Z


	/** �����͎�O��TURBO�ړ��J�n����X����]�p���x�̏����x */
	angle _angRXVelo_BeginMZT;	//Rotation axisX angle Velocity when I Begin To Move Z with Turbo
								//���̏ꍇ�͐��A��O�̏ꍇ�͂���� -1 ���悸��

	/** �����͎�O��TURBO�ړ�����X����]�p���x�̊p�����x */
	angle _angRXAcce_MZT;		//Rotation axisX angle Acceleration while I Move Z with Turbo
								//���̏ꍇ�͐��A��O�̏ꍇ�͂���� -1 ���悸��B�A�� �l < 0 �ł��邱�ƁB �悾�񂾂�x���Ȃ�悤�ɂ���������

	/** �����͎�O��TURBO�ړ�����X����]�p���x�̍Œᑬ�x */
	angle _angRXBtmVelo_MZT;	//Rotation axisX Bottom angle Velocity while I Move Z with Turbo
								//���̏ꍇ�͔͈͂� _angRXBtmVelo_MZT < X����]�p���x�� < 360,000
								//��O�̏ꍇ��     -360,000 < X����]�p���x�� < -1*_angRXBtmVelo_MZT
								//�Ƃ��āATURBO�ړ����Œ���̉�]�͂�ۏ؂���B


	/** �����͎�O�ȊO�̒ʏ�ړ����A�����I��Angle0�ɖ߂낤�Ƃ���X����]�p���x�̏���p���x */
	angle _angRXTopVelo_MNZ;	//Rotation X Top angle Velocity while I Move Not Z
								//�����p���x�͂���� -1 ���悸��

	/** �����͎�O�ȊO�̒ʏ�ړ����A�����I��Angle0�ɖ߂낤�Ƃ��鎞��X����]�p�����x(��������) */
	angle _angRXAcce_MNZ;		//Rotation X angle Acceleration while I Not Move Not Z


	/** �㖔�͉��֒ʏ�ړ��J�n����X����]�p���x�̏����x */
	angle _angRZVelo_BeginMY;	//Rotation axisX angle Velocity when I Begin To Move Y
								//���̏ꍇ�͐��A��O�̏ꍇ�͂���� -1 ���悸��

	/** �㖔�͉��֒ʏ�ړ�����Z����]�p���x�̊p�����x */
	angle _angRZAcce_MY;		//Rotation axisX angle Acceleration while I Move Y
								//���̏ꍇ�͐��A��O�̏ꍇ�͂���� -1 ���悸��

	/** �㖔�͉��ֈړ�����Z����]�p���x�̏���p���x */
	angle _angRZTopVelo_MY;		//Rotation axisX Top angle Velocity while I Move Y
								//�����p���x�͂���� -1 ���悸��

	/** �㖔�͉��֒ʏ�Z�ړ�����Z����]�p�̒�~�p�x */
	angle _angRZStop_MY;		//Rotation axisX Stop angle while I Move Z


	/** �㖔�͉���TURBO�ړ��J�n����Z����]�p���x�̏����x */
	angle _angRZVelo_BeginMYT;	//Rotation axisZ angle Velocity when I Begin To Move Y with Turbo
								//��̏ꍇ�͐��A���̏ꍇ�͂���� -1 ���悸��

	/** �㖔�͉���TURBO�ړ�����Z����]�p���x�̊p�����x */
	angle _angRZAcce_MYT;		//Rotation axisZ angle Acceleration while I Move Y with Turbo
								//��̏ꍇ�͐��A���̏ꍇ�͂���� -1 ���悸��B�A�� �l < 0 �ł��邱�ƁB �悾�񂾂�x���Ȃ�悤�ɂ���������

	/** �㖔�͉���TURBO�ړ�����Z����]�p���x�̍Œᑬ�x */
	angle _angRZBtmVelo_MYT;	//Rotation axisZ Bottom angle Velocity while I Move Y with Turbo
								//��̏ꍇ�͔͈͂� _angRZBtmVelo_MYT < Z����]�p���x�� < 360,000
								//��̏ꍇ��       -360,000 < X����]�p���x�� < -1*_angRZBtmVelo_MYT
								//�Ƃ��āATURBO�ړ����Œ���̉�]�͂�ۏ؂���B


	/** �㖔�͉��֒ʏ�ړ����A�����I��Angle0�ɖ߂낤�Ƃ���Z����]�p���x�̏���p���x */
	angle _angRZTopVelo_MNY;	//Rotation Z Top angle Velocity while I Move Not Y
								//�����p���x�͂���� -1 ���悸��


	/** �㖔�͉��֒ʏ�ړ����A�����I��Angle0�ɖ߂낤�Ƃ��鎞��Y����]�p�����x(��������) */
	angle _angRZAcce_MNY;		//Rotation X angle Acceleration while I Not Move Not Y

	/** TURBO�ړ����ړ�����ł��銄�� */
	double _dRate_TurboControl;
	/** TURBO�ړ����ړ����䑝�� */
	int _iTurboControl;

	/** �^�[�{�o�߃t���[�� */
	DWORD _dwFrameTurboMove;
	/** �ʏ�ړ��o�߃t���[�� */
	DWORD _dwFrameNomalMove;

	int _iShotKind01;
	int _iShotKind02;
	int _iShotKind03;



	State _state;



	RotationActor* _pMyWaves001Rotation;
	RotationActor* _pMyShots001Rotation;
	RotationActor* _pMyLaserChipRotation;
	RotationActor* _pEnemyShots001Rotation;
	RotationActor* _pEffectExplosion001Rotation;


	MyShip(string prm_name, string prm_model);

	/**
	 * ��OverRide �ł���
	 */
	virtual void initialize();

	/**
	 * ��OverRide �ł���
	 */
	virtual void processBehavior();

 	/**
	 * ��OverRide �ł���
	 */
	virtual void processJudgement();

	/**
	 * ��OverRide �ł���
	 */
	virtual void processOnHit(GgafActor* prm_pActor_Opponent);


	virtual void setMoveSpeedLv(int lv) {
 		_lv_MoveSpeed = lv;
 		_iMoveSpeed = _lv_MoveSpeed*1000;
 	}
 	//��ʉ��ֈړ�����X����]����
	virtual void beginTurboZX(int prm_VB);

 	//��ʎ�O�ֈړ�����X����]����
	virtual void beginTurboXY(int prm_VB);


	virtual void beginMoveZX(int prm_VB);

	virtual void beginMoveXY(int prm_VB);

 	static void transactShot(GgafDx9UntransformedActor* prm_pActor);


 	/**�I�v�V�����ǉ�*/
 	void equipOption();


 	virtual ~MyShip();





};


#endif /*MYSHIP_H_*/

