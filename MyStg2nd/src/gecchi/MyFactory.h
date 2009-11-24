#ifndef MYFACTORY_H_
#define MYFACTORY_H_
namespace MyStg2nd {

class MyFactory : public GgafCore::GgafFactory {

public:

    template<class X>
    static X* createActor(void* p1, void* p2, void* p3) {
        //p1 : 名称
        X* p = NEW X((char*)p1);
        return p;
    }

    template<class X>
    static X* createActorWithModel(void* p1, void* p2, void* p3) {
        //p1 : 識別名称
        //p2 : モデル識別文字列
        X* p = NEW X((char*)p1, (char*)p2);
        return p;
    }

    template<class X>
    static X* createActorWithDp(void* p1, void* p2, void* p3) {
        //p1 : 識別名称
        //p2 : アクター発送者
        X* p = NEW X((char*)p1, (GgafDx9LibStg::ActorDispatcher*)p2);
        return p;
    }

    template<class X>
    static X* createActorWithModelDp(void* p1, void* p2, void* p3) {
        //p1 : 識別名称
        //p2 : モデル識別文字列
        //p3 : アクター発送者
        X* p = NEW X((char*)p1, (char*)p2, (GgafDx9LibStg::ActorDispatcher*)p3);
        return p;
    }

    template<class X>
    static X* createScene(void* p1, void* p2, void* p3) {
        //Scene生成で一番多い形の引数。
        //p1 : 識別名称
        X* p = NEW X((char*)p1);
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

#define orderActorToFactory(ID, CLASS, NAME) MyFactory::orderActor<CLASS>(ID,MyFactory::createActor,(void*)(NAME),(void*)(NULL),(void*)(NULL))
#define orderActorWithModelToFactory(ID, CLASS, NAME, MODEL) MyFactory::orderActor<CLASS>(ID,MyFactory::createActorWithModel,(void*)(NAME),(void*)(MODEL),(void*)(NULL))
#define orderActorWithModelDpToFactory(ID, CLASS, NAME, MODEL, DISPATCHER) MyFactory::orderActor<CLASS>(ID,MyFactory::createActorWithModelDp,(void*)(NAME),(void*)(MODEL),(void*)(DISPATCHER))
#define orderActorWithDpToFactory(ID, CLASS, NAME, DISPATCHER) MyFactory::orderActor<CLASS>(ID,MyFactory::createActorWithDp,(void*)(NAME),(void*)(DISPATCHER), (void*)(NULL))

#define obtainActorFromFactory(ID) MyFactory::obtainActor(ID)
#define orderSceneToFactory(ID, CLASS, NAME) MyFactory::orderScene<CLASS>(ID,MyFactory::createScene,(void*)(NAME),(void*)(NULL),(void*)(NULL))
#define obtainSceneFromFactory(ID) MyFactory::obtainScene(ID)


}
#endif /*MYFACTORY_H_*/

