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


#define CAM_POS_RIGHT 1
#define CAM_POS_LEFT 2
#define CAM_POS_TOP 3
#define CAM_POS_BOTTOM 4
#define CAM_POS_TO_BEHIND 10
#define CAM_POS_BEHIND_RIGHT 11
#define CAM_POS_BEHIND_LEFT 12
#define CAM_POS_BEHIND_TOP 13
#define CAM_POS_BEHIND_BOTTOM 14

/**
 * 世界シーンクラス .
 * この世に、とある世界がありました。<BR>
 * 本クラスは、世界の振る舞い等を実装しています。<BR>
 */
class World : public GgafDx9LibStg::DefaultScene {

public:
    bool _is_create_GameScene;
    char _aBufDebug[80];
    LabelGecchi16Font* _pFont16_Debug;

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
