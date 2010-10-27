#ifndef WALLEDSCENE_H_
#define WALLEDSCENE_H_
namespace MyStg2nd {

/**
 * @version 1.00
 * @since 2010/08/23
 * @author Masatoshi Tsuge
 */
class WalledScene : public GgafDx9LibStg::DefaultScene {
//    class Section {
//    public :
//        GgafDx9LibStg::WalledSectionScene* _pScene;
//        int _repeat;
//        Section(GgafDx9LibStg::WalledSectionScene* prm_pScene, int prm_repeat) {
//            _pScene = prm_pScene;
//            _repeat = prm_repeat;
//        }
//    };

public:
    int _ground_speed;

    GgafCore::GgafLinkedListRing<GgafDx9LibStg::WalledSectionScene>* _pRingSection;

    WalledScene(const char* prm_name);
    /**
     * _pFuncWallMove にデフォルトで設定されている関数 .
     * アクターをX軸の負の方向に_ground_speedスクロールさせる
     * @param pThat アクターのポインタ
     * @param p1 _ground_speedのポインタ
     * @param p2 NULL（未使用）
     */
    static void moveX(GgafCore::GgafObject* pThat, void* p1, void* p2);

    /**
     * 初期処理
     */
    void initialize() override;

    virtual void onActive() override;
    /**
     * 配下アクター全てに_pFuncWallMove を実行。
     * オーバーライドする場合、DefaultScene::processSettlementBehavior(); を呼び出すことを忘れずに。
     */
    virtual void processSettlementBehavior() override;

    virtual void processBehavior() override;

    virtual void processFinal() override;

    virtual ~WalledScene();
};

}
#endif /*WALLEDSCENE_H_*/
