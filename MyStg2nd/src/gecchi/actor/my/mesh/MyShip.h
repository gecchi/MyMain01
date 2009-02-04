#ifndef MYSHIP_H_
#define MYSHIP_H_
namespace MyStg2nd {

#define SH_NOMAL 0;
#define SH_LASER 1;

#define MAX_LEVEL_MOVE_SPEED 5
#define MIN_LEVEL_MOVE_SPEED 0

#define EQ_OPTION 1
#define EQ_MAX_OPTION 0

enum MoveWay {
	WAY_NONE,
	WAY_UP,
	WAY_UP_FRONT,
	WAY_UP_BEHIND,
	WAY_DOWN,
	WAY_DOWN_FRONT,
	WAY_DOWN_BEHIND,
	WAY_FRONT,
	WAY_BEHIND,
	WAY_ZLEFT,
	WAY_ZLEFT_FRONT,
	WAY_ZLEFT_BEHIND,
	WAY_ZRIGHT,
	WAY_ZRIGHT_FRONT,
	WAY_ZRIGHT_BEHIND
};

class MyShip : public GgafDx9LibStg::DefaultMeshActor {

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

	/** �^�[�{���A�ړ����p */
	MoveWay _wayTurbo;

	/** �ړ��X�s�[�h���x�� */
	int _lv_MoveSpeed;
	/** �ړ��X�s�[�h���x���ɑ�������ړ��X�s�[�h */
	int _iMoveSpeed;

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




	/** �㖔�͉��֒ʏ�ړ��J�n����X����]�p���x�̏����x */
	GgafDx9Core::angle _angRZVelo_BeginMY;	//Rotation axisX angle Velocity when I Begin To Move Y
								//���̏ꍇ�͐��A��O�̏ꍇ�͂���� -1 ���悸��

	/** �㖔�͉��֒ʏ�ړ�����Z����]�p���x�̊p�����x */
	GgafDx9Core::angle _angRZAcce_MY;		//Rotation axisX angle Acceleration while I Move Y
								//���̏ꍇ�͐��A��O�̏ꍇ�͂���� -1 ���悸��

	/** �㖔�͉��ֈړ�����Z����]�p���x�̏���p���x */
	GgafDx9Core::angle _angRZTopVelo_MY;		//Rotation axisX Top angle Velocity while I Move Y
								//�����p���x�͂���� -1 ���悸��

	/** �㖔�͉��֒ʏ�Z�ړ�����Z����]�p�̒�~�p�x */
	GgafDx9Core::angle _angRZStop_MY;		//Rotation axisX Stop angle while I Move Z


	/** �㖔�͉���TURBO�ړ��J�n����Z����]�p���x�̏����x */
	GgafDx9Core::angle _angRZVelo_BeginMYT;	//Rotation axisZ angle Velocity when I Begin To Move Y with Turbo
								//��̏ꍇ�͐��A���̏ꍇ�͂���� -1 ���悸��

	/** �㖔�͉���TURBO�ړ�����Z����]�p���x�̊p�����x */
	GgafDx9Core::angle _angRZAcce_MYT;		//Rotation axisZ angle Acceleration while I Move Y with Turbo
								//��̏ꍇ�͐��A���̏ꍇ�͂���� -1 ���悸��B�A�� �l < 0 �ł��邱�ƁB �悾�񂾂�x���Ȃ�悤�ɂ���������

	/** �㖔�͉���TURBO�ړ�����Z����]�p���x�̍Œᑬ�x */
	GgafDx9Core::angle _angRZBtmVelo_MYT;	//Rotation axisZ Bottom angle Velocity while I Move Y with Turbo
								//��̏ꍇ�͔͈͂� _angRZBtmVelo_MYT < Z����]�p���x�� < 360,000
								//��̏ꍇ��       -360,000 < X����]�p���x�� < -1*_angRZBtmVelo_MYT
								//�Ƃ��āATURBO�ړ����Œ���̉�]�͂�ۏ؂���B


	/** �㖔�͉��֒ʏ�ړ����A�����I��Angle0�ɖ߂낤�Ƃ���Z����]�p���x�̏���p���x */
	GgafDx9Core::angle _angRZTopVelo_MNY;	//Rotation Z Top angle Velocity while I Move Not Y
								//�����p���x�͂���� -1 ���悸��


	/** �㖔�͉��֒ʏ�ړ����A�����I��Angle0�ɖ߂낤�Ƃ��鎞��Y����]�p�����x(��������) */
	GgafDx9Core::angle _angRZAcce_MNY;		//Rotation X angle Acceleration while I Not Move Not Y

	/** TURBO�ړ����ړ�����ł��銄�� */
	double _dRate_TurboControl;
	/** TURBO�ړ����ړ����䑝�� */
	int _iTurboControl;

	/** �^�[�{�o�߃t���[�� */
	DWORD _dwFrameTurboMove;
	DWORD _dwFrameXYTurboMove;


	GgafDx9Core::angle _angFaceTurnRange;
	GgafDx9Core::angle _angRotVelo_FaceTurn;

	/** �^�[�{��������(Frame) */
	DWORD _dwIntervalFinshTurbo;


	bool _needTurnFaceNeutralXY;
	bool _needTurnFaceXYMove;



	/** �ʏ�ړ��o�߃t���[�� */
	DWORD _dwFrameNomalMove;

	int _iShotKind01;
	int _iShotKind02;
	int _iShotKind03;



	State _state;

	GgafCore::GgafLinkedListRing<GgafDx9LibStg::GeoElement>* _pRing_GeoHistory;

	GgafDx9LibStg::RotationActor* _pMyWaves001Rotation;
	GgafDx9LibStg::RotationActor* _pMyShots001Rotation;
	GgafDx9LibStg::RotationActor* _pMyLaserChipRotation;
	GgafDx9LibStg::RotationActor* _pEnemyShots001Rotation;
	GgafDx9LibStg::RotationActor* _pEffectExplosion001Rotation;


	MyShip(char* prm_name, char* prm_model);

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
	virtual void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent);


	virtual void setMoveSpeedLv(int lv) {
 		_lv_MoveSpeed = lv;
 		_iMoveSpeed = _lv_MoveSpeed*1000;
 	}

	//��ʎ�O�ֈړ�����X����]����
	virtual void beginTurboXY(int prm_VB);

	virtual void moveXY(int prm_VB);

	virtual void controlTurboXY(int prm_VB);

	virtual void turnFaceXYMove(int prm_VB);

	virtual void doNotingMoveInput();

	virtual void turnFaceNeutralXY();


	//virtual void beginMoveZX(int prm_VB);

	//virtual void beginMoveXY(int prm_VB);

 	static void transactShot(GgafDx9Core::GgafDx9UntransformedActor* prm_pActor);


 	/**�I�v�V�����ǉ�*/
 	void equipOption();


 	virtual ~MyShip();





};


}
#endif /*MYSHIP_H_*/

