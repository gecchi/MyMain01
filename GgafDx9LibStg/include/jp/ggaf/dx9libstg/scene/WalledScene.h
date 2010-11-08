#ifndef WALLEDSCENE_H_
#define WALLEDSCENE_H_
namespace GgafDx9LibStg {

/**
 * 壁ブロックシーン .
 * @version 1.00
 * @since 2010/11/05
 * @author Masatoshi Tsuge
 */
class WalledScene : public GgafDx9LibStg::ScrolledScene {

public:
    /** セクションシーンのリスト */
    GgafCore::GgafLinkedListRing<GgafDx9LibStg::WalledSectionScene>* _pRingSection;
    /** 壁ブロックを供給するディスパッチャー(buildWalledScene()で設定される) */
    GgafCore::GgafActorDispatcher* _pDispatcher_Wall;

    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    WalledScene(const char* prm_name);

    /**
     * WalledSceneを構築する。
     * 本クラス new 後 initialize() までに、必ず１回実行する必要があります。
     * @param prm_wall_dep      壁ブロック１個のX軸方向の幅
     * @param prm_wall_width    壁ブロック１個のZ軸方向の幅
     * @param prm_wall_height   壁ブロック１個のY軸方向の幅
     * @param prm_papSection    セクションシーン配列へのポインタ
     * @param prm_section_num   セクションシーン数
     * @param prm_pDispatcher_Wall 壁ブロックを供給するディスパッチャー
     */
    void buildWalledScene(
            int prm_wall_dep, int prm_wall_width, int prm_wall_height,
            WalledSectionScene** prm_papSection, int prm_section_num,
            GgafCore::GgafActorDispatcher* prm_pDispatcher_Wall
         );

    /**
     * 処理実装済み。下位でオーバーライドする場合は、上位initialize()を呼び出して下さい。
     */
    virtual void initialize() override;

    /**
     * 処理実装済み。下位でオーバーライドする場合は、上位onActive()を呼び出して下さい。
     */
    virtual void onActive() override;

    /**
     * 処理実装済み。下位でオーバーライドする場合は、上位processBehavior()を呼び出して下さい。
     */
    virtual void processBehavior() override;

    virtual void processFinal() override;

    virtual ~WalledScene();
};

}
#endif /*WALLEDSCENE_H_*/
