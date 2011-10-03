#ifndef WALLEDSCENE_H_
#define WALLEDSCENE_H_
namespace GgafLib {

/**
 * 壁ブロックシーン .
 * @version 1.00
 * @since 2010/11/05
 * @author Masatoshi Tsuge
 */
class WalledScene : public GgafLib::ScrolledScene {

public:
    /** セクションシーンのリスト */
    GgafCore::GgafLinkedListRing<GgafLib::WalledSectionScene>* _pRingSection;
    /** 壁ブロックを供給するデポジトリ(buildWalledScene()で設定される) */
    GgafCore::GgafActorDepository* _pDepo_WallAAB;
    GgafCore::GgafActorDepository* _pDepo_WallAAPrism;

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
     * @param prm_pDepo_WallAABox 壁ブロックを供給するデポジトリ
     * @param prm_pDepo_WallAAPrism 壁プリズムブロックを供給するデポジトリ（省略可）
     */
    void buildWalledScene(
            int prm_wall_dep, int prm_wall_width, int prm_wall_height,
            WalledSectionScene** prm_papSection, int prm_section_num,
            GgafCore::GgafActorDepository* prm_pDepo_WallAABox,
            GgafCore::GgafActorDepository* prm_pDepo_WallAAPrism = NULL
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
