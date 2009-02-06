#ifndef MYFACTORY_H_
#define MYFACTORY_H_
namespace MyStg2nd {

class MyFactory : public GgafCore::GgafFactory {

public:

    template<class X>
    static X* createActor(void* p1, void* p2, void* p3) {
        //Actor�����ň�ԑ����`�̈����B
        //p1 : ���ʖ���
        //p2 : ���f�����ʕ�����
        X* p = NEW X((char*)p1, (char*)p2);
        return p;
    }

    template<class X>
    static X* createActorWithRot(void* p1, void* p2, void* p3) {
        //Actor�����œ�Ԗڑ����`�̈����B
        //p1 : ���ʖ���
        //p2 : ���f�����ʕ�����
        //p3 : ���[�e�[�V�����A�N�^�[
        X* p = NEW X((char*)p1, (char*)p2, (GgafDx9LibStg::RotationActor*)p3);
        return p;
    }

    template<class X>
    static X* createScene(void* p1, void* p2, void* p3) {
        //Scene�����ň�ԑ����`�̈����B
        //p1 : ���ʖ���
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

#define orderActorToFactory(ID, CLASS, NAME, MODEL) MyFactory::orderActor<CLASS>(ID,MyFactory::createActor,(void*)(NAME),(void*)(MODEL),(void*)(NULL))
#define orderActorWithRotToFactory(ID, CLASS, NAME, MODEL, ROT) MyFactory::orderActor<CLASS>(ID,MyFactory::createActorWithRot,(void*)(NAME),(void*)(MODEL),(void*)(ROT))

#define obtainActorFromFactory(ID) MyFactory::obtainActor(ID)
#define orderSceneToFactory(ID, CLASS, NAME) MyFactory::orderScene<CLASS>(ID,MyFactory::createScene,(void*)(NAME),(void*)(NULL),(void*)(NULL))
#define obtainSceneFromFactory(ID) MyFactory::obtainScene(ID)

}
#endif /*MYFACTORY_H_*/

