#ifndef WALLEDSCENE_H_
#define WALLEDSCENE_H_
namespace GgafLib {

/**
 * 壁ブロックシーン .
 * 一つの WalledScene は、複数個の WalledSectionScene を繋ぎあわせたものです。
 * @version 1.00
 * @since 2010/11/05
 * @author Masatoshi Tsuge
 */
class WalledScene : public DefaultScene {

public:
    /** セクションシーンの保持リスト */
    GgafCore::GgafLinkedListRing<GgafLib::WalledSectionScene> _ringHoldSection;
    /** 完了したセクションシーンの保持リスト */
    GgafCore::GgafLinkedListRing<GgafLib::WalledSectionScene> _ringLoopEndSection;
    /** 壁ブロックを供給するデポジトリ(buildWalledScene()で設定される) */
    GgafCore::GgafActorDepository* _pDepo_WallAAB;
    GgafCore::GgafActorDepository* _pDepo_WallAAPrism;
    WalledSectionScene* _pLastSectionScene;
    bool _is_all_active_section_scenes;
    bool _is_finished;

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    WalledScene(const char* prm_name);

    /**
     * WalledSceneを構築する。
     * 本クラス new 後 initialize() までに、必ず１回実行する必要があります。
     * 【注意】
     * prm_pDepo_WallAABox 及び prm_pDepo_WallAAPrism は処理内で本シーンのinitialize() で
     * 配下に強制移動されます。したがって、マネージャ管理の共通デポジトリの場合は、
     * マネージャ側の不正ポインタの原因になります。
     * @param prm_wall_dep      壁ブロック１個のX軸方向の幅
     * @param prm_wall_width    壁ブロック１個のZ軸方向の幅
     * @param prm_wall_height   壁ブロック１個のY軸方向の幅
     * @param prm_wall_start_X  外壁出現のX座標位置
     * @param prm_papSection    セクションシーン配列へのポインタ
     * @param prm_section_num   セクションシーン数
     * @param prm_pDepo_WallAABox 壁ブロック(WallAABActor)を供給するデポジトリ（※initialize()時、配下に強制移動）
     * @param prm_pDepo_WallAAPrism 壁プリズム(WallAAPrismActor)を供給するデポジトリ（※initialize()時、配下に強制移。プリズムが無い時は省略可）
     */
    void buildWalledScene(
            coord prm_wall_dep, coord prm_wall_width, coord prm_wall_height,
            coord prm_wall_start_X,
            WalledSectionScene** prm_papSection, int prm_section_num,
            GgafCore::GgafActorDepository* prm_pDepo_WallAABox,
            GgafCore::GgafActorDepository* prm_pDepo_WallAAPrism = nullptr
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
     * 最後のセクションシーンの最後の壁ブロックが非活動に鳴った場合、
     * コールバックされる。
     * sayonara() などを実装して下さい。
     */
    virtual void onFinishedSection() = 0;

    /**
     * 処理実装済み。下位でオーバーライドする場合は、上位processBehavior()を呼び出して下さい。
     */
    virtual void processBehavior() override;

    virtual void processFinal() override;

    /**
     * X軸の負の方向にスクロールさせる関数 .
     * @param pThat アクター
     * @param p1 スクロールスピード(_scroll_speedへのポインタ)
     * @param p2 任意（引数は特に無し）
     */
    static void scrollX(GgafObject* pThat, void* p1, void* p2);


    virtual ~WalledScene();
};

}
#endif /*WALLEDSCENE_H_*/
