#ifndef WORLD_H_
#define WORLD_H_
namespace MyStg2nd {


#ifdef P_UNIVERSE
    #define P_WORLD ((MyStg2nd::World*)(P_UNIVERSE->_pWorld))
#else
    #error P_UNIVERSE isnt define
#endif


/**
 * 世界シーンクラス .
 * 本クラスは、アプリ上の「この世」の振る舞い等を実装しています。<BR>
 */
class World : public GgafDx9LibStg::DefaultScene {

public:
    bool _is_create_GameScene;
    char _aBufDebug[80];
    LabelGecchi16Font* _pFont16_Wait;
    LabelGecchi16Font* _pFont16_Debug;
    LabelGecchi16Font* _pStringBoard01;
    PreDrawScene* _pPreDrawScene;
    GameScene* _pGameScene;

    World(const char* prm_name);

    /**
     * 初期処理
     */
    void initialize() override;

     /**
     * ＜OverRide です＞
     */
    void processBehavior() override;

     /**
     * ＜OverRide です＞
     */
    void processJudgement() override;

    virtual ~World();
};

}
#endif /*WORLD_H_*/
