#ifndef WORLD_H_
#define WORLD_H_
namespace VioletVreath {


#ifdef P_UNIVERSE
    #define P_WORLD ((VioletVreath::World*)(P_UNIVERSE->pWorld_))
#else
    #error P_UNIVERSE isnt define
#endif


/**
 * 世界シーンクラス .
 * アプリ上の「この世(Universe)」の一つ下の階層に位置します。<BR>
 */
class World : public GgafLib::DefaultScene {

public:
    bool is_create_GameScene_;
    char aBufDebug_[80];
    LabelGecchi16Font* pLabel_Title_;
    LabelGecchi16Font* pLabel_Aster_;
    LabelGecchi16Font* pLabel_Debug_;
    LabelGecchi16Font* pLabel_Wait_;
    PreDrawScene* pPreDrawScene_;
    GameScene* pGameScene_;

    World(const char* prm_name);

    /**
     * 初期処理
     */
    void initialize() override;

    void processBehavior() override;

    void processJudgement() override;

    virtual ~World();
};

}
#endif /*WORLD_H_*/
