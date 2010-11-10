#ifndef WORLD_H_
#define WORLD_H_
namespace MyStg2nd {

//getParent getSub そして キャストマクロ。
//下記マクロ使用するには、オブジェクトの識別名が、
//クラス名の末尾の"...Scene"という文字列を取り去ったものであることが前提条件です
#define getParentScene(X) ((X##Scene*)getParent(#X))
#define getSubScene(X) ((X##Scene*)getSub(#X))
#define getParentActor(X) ((X##Actor*)getParent(#X))
#define getSubActor(X) ((X##Actor*)getSub(#X))




#ifdef pUNIVERSE
    #define pWORLD ((MyStg2nd::World*)(pUNIVERSE->_pWorld))
    #define pACTIVE_CAMWORKER (pUNIVERSE->_pActiveCameraWorker)
#else
    #error pUNIVERSE isnt define
#endif


/**
 * 世界シーンクラス .
 * 本クラスは、アプリ上の「この世」の振る舞い等を実装しています。<BR>
 */
class World : public GgafDx9LibStg::DefaultScene {

public:
    bool _is_create_GameScene;
    char _aBufDebug[80];
    LabelGecchi16Font* _pFont16_Debug;
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
