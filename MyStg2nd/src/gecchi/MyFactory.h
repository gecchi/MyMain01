#ifndef MYFACTORY_H_
#define MYFACTORY_H_

class MyFactory : public GgafCore::GgafFactory {

public:

	template <class X>
	static X* createActor(void* pArg1, void* pArg2) {
		string name = (char*)pArg1;
		string model = (char*)pArg2;
		X* p = NEW X(name, model);
		return p;
	}

	template <class X>
	static X* createScene(void* pArg1, void* pArg2) {
		string name = (char*)pArg1;
		X* p = NEW X(name);
		return p;
	}

//	static GgafMainScene* createGameScene(void* pArg1, void* pArg2);
//	static GgafMainScene* createGameDemoScene(void* pArg1, void* pArg2);
//	static GgafMainScene* createGameMainScene(void* pArg1, void* pArg2);
//	static GgafMainScene* createCommonScene(void* pArg1, void* pArg2);
//	static GgafMainScene* createStage01Scene(void* pArg1, void* pArg2);
//	static GgafMainScene* createStage02Scene(void* pArg1, void* pArg2);
//	static GgafMainScene* createStage03Scene(void* pArg1, void* pArg2);
//	static GgafMainScene* createStage04Scene(void* pArg1, void* pArg2);
//	static GgafMainScene* createStage05Scene(void* pArg1, void* pArg2);
//

//	static GgafMainActor* createDispFpsActor(void* pArg1, void* pArg2);
//	static GgafMainActor* createDebugDelineateActor(void* pArg1, void* pArg2);
//	static GgafMainActor* createMyShip(void* pArg1, void* pArg2);
//	static GgafMainActor* createMyShipShot(void* pArg1, void* pArg2);
	static GgafCore::GgafMainActor* createTamagoSet01(void* pArg1, void* pArg2);

//
//	static GgafMainActor* createEnemyCeres(void* pArg1, void* pArg2);
//	static GgafMainActor* createFormationCeres001(void* pArg1, void* pArg2);
//	static GgafMainActor* createFormationCeres002(void* pArg1, void* pArg2);
	static GgafCore::GgafMainActor* createFormationJuno001First(void* pArg1, void* pArg2);
//	static GgafMainActor* createFormationJuno001(void* pArg1, void* pArg2);




};

#define orderActorFactory(ID, CLASS, NAME, MODEL) MyFactory::orderActor<CLASS>(ID,MyFactory::createActor,(void*)(NAME),(void*)(MODEL))
#define obtainActorFactory(ID) MyFactory::obtainActor(ID)
#define orderSceneFactory(ID, CLASS, NAME) MyFactory::orderScene<CLASS>(ID,MyFactory::createScene,(void*)(NAME),(void*)(NULL))
#define obtainSceneFactory(ID) MyFactory::obtainScene(ID)


#endif /*MYFACTORY_H_*/

