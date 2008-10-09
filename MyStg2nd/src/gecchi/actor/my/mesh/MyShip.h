#ifndef MYSHIP_H_
#define MYSHIP_H_

#define SH_NOMAL 0;
#define SH_LASER 1;

#define MAX_LEVEL_MOVE_SPEED 5
#define MIN_LEVEL_MOVE_SPEED 0


class MyShip : public DefaultMeshActor {

public:

	bool _turboFlg;

	/** �ړ��X�s�[�h���x�� */
	int _lv_MoveSpeed;
	/** �ړ��X�s�[�h���x���ɑ�������ړ��X�s�[�h */
	int _iMoveSpeed;

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
 	void onMoveZPlusBegin();

 	//��ʎ�O�ֈړ�����X����]����
 	void onMoveZMinusBegin();

 	//��ʉ��ֈړ��I��X����]����
 	void onMoveZFinish();
 	virtual ~MyShip();
};


#endif /*MYSHIP_H_*/

