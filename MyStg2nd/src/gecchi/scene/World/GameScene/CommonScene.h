#ifndef MYSHIPSCENE_H_
#define MYSHIPSCENE_H_

class CommonScene : public DefaultScene {

public:
	MyShip* _pMyShip;


	RotationActor* _pEnemyShots001Rotation;
	RotationActor* _pEffectExplosion001Rotation;

	CommonScene(string prm_name);
	/**
	 * ��������
	 */
	void initialize();

	virtual void processBehavior();

	virtual ~CommonScene();
};

#endif /*MYSHIPSCENE_H_*/
