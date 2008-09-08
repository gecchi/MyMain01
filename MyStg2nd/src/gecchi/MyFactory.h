#ifndef MYFACTORY_H_
#define MYFACTORY_H_

class MyFactory : public GgafSubcontractor {

public:
//	static GgafMainScene* createGameScene(void* x);
//	static GgafMainScene* createGameDemoScene(void* x);
//	static GgafMainScene* createGameMainScene(void* x);
//	static GgafMainScene* createMyShipScene(void* x);
	static GgafMainScene* createStage01Scene(void* x);
	static GgafMainScene* createStage02Scene(void* x);
	static GgafMainScene* createStage03Scene(void* x);
	static GgafMainScene* createStage04Scene(void* x);
	static GgafMainScene* createStage05Scene(void* x);


//	static GgafMainActor* createDispFpsActor(void* x);
	static GgafMainActor* createDebugDelineateActor(void* x);
//	static GgafMainActor* createMyShip(void* x);
//	static GgafMainActor* createMyShipShot(void* x);
	static GgafMainActor* createTamagoSet01(void* x);


	static GgafMainActor* createEnemyCeres(void* x);
	static GgafMainActor* createEnemyFormation001(void* x);
};

#endif /*MYFACTORY_H_*/

