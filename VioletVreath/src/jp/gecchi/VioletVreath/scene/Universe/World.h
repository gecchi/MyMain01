#ifndef WORLD_H_
#define WORLD_H_
namespace VioletVreath {


#ifdef P_UNIVERSE
    #define P_WORLD ((VioletVreath::World*)(P_UNIVERSE->_pWorld))
#else
    #error P_UNIVERSE isnt define
#endif


/**
 * 世界シーンクラス .
 * アプリ上の「この世(Universe)」の一つ下の階層に位置します。<BR>
 */
class World : public GgafLib::DefaultScene {

public:
    bool _is_create_GameScene;
    char _aBufDebug[80];
    LabelGecchi16Font* _pLabel_Title;
    LabelGecchi16Font* _pLabel_Aster;
    LabelGecchi16Font* _pLabel_Debug;
    LabelGecchi16Font* _pLabel_Wait;
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
