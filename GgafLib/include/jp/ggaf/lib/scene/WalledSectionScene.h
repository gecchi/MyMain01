#ifndef WALLEDSECTIONSCENE_H_
#define WALLEDSECTIONSCENE_H_

#define FULL_VAL (-2)
#define KARA_VAL (-2)

namespace GgafLib {

/**
 * 外壁セクションシーン .
 * 「外壁シーン」を構成するシーンであり、
 * 外壁セクションシーンが連って一つの「外壁シーン」を構成します。
 * @version 1.00
 * @since 2010/10/18
 * @author Masatoshi Tsuge
 */
class WalledSectionScene : public DefaultScene {

    /**
     * 壁ブロック(WallPartsActor)の配置情報構造体
     */
    struct WallInfo {
        /** プリズム位置情報(> 0の場合はプリズム、0の場合はBOX) */
        int _pos_prism;
        /** 表示時のY座標 */
        int _Y;
        /** 表示時のZ座標 */
        int _Z;
        /** 可視表示面情報 */
        int _wall_draw_face;
        /** 当たり判定領域AAB情報 */
        int _aColliBoxStretch[6];
    };
public:
    /** [r]外壁シーンの長さ（X座標軸の壁ブロック数） */
    int _area_len;
    /** [r]外壁シーンの高さ（Y座標軸の壁ブロック数） */
    int _area_height;
    /** [r]外壁シーンの幅（Z座標軸の壁ブロック数） */
    int _area_width;
    /** [r]壁ブロックの長さ（１つのWallPartsActorオブジェクトのX座標軸長さ）*/
    int _wall_dep;
    /** [r]壁ブロックの高さ（１つのWallPartsActorオブジェクトのY座標軸長さ）*/
    int _wall_height;
    /** [r]壁ブロックの幅（１つのWallPartsActorオブジェクトのZ座標軸長さ）*/
    int _wall_width;
    /** [r]外壁表示X座標位置 */
    int _wall_start_X;
    /** [r]繰り返し回数 */
    int _loop_num;
    /** [r]繰り返しカウンタ */
    int _cnt_loop;
    /** [r]外壁表示間隔時間 */
    frame _frame_of_launch_next;
    /** [r]表示済み外壁シーンの長さ */
    int _cnt_area_len;
    /** [r]全壁ブロック(WallPartsActor)の配置情報 */
    WallInfo** _papaWallInfo;
    /** [r]全壁ブロック(WallPartsActor)の配置情報の、外壁シーンの長さ別個数 */
    int* _paWallInfoLen;
    /** [r]壁ブロック(WallPartsActor)デポジトリ */
    GgafCore::GgafActorDepository* _pDepo_WallAAB;
    GgafCore::GgafActorDepository* _pDepo_WallAAPrism;
    /** [r]手前ブロックの透過機能有効時の基準となるアクター */
    GgafDxCore::GgafDxGeometricActor* _pTarget_FrontAlpha;

    bool _is_loop_end;
    WallPartsActor* _pWallPartsLast;

    ScrolledScene*  _pScrolledScene;

    /**
     * コンストラクタ .
     * 壁ブロック情報ファイルを読み込み、オブジェクトに展開します。
     * @param prm_name シーン名
     * @param prm_data_filename 壁ブロック情報ファイル
     * @return
     */
    WalledSectionScene(const char* prm_name, const char* prm_data_filename, ScrolledScene* prm_pScrolledScene);



    /**
     * 外壁シーンを設定.
     * new した後、initialize() が実行されるまでに config して下さい。
     * @param prm_pDepo_WallAAB 壁ブロック（WallAABActorオブジェクト）が登録されているデポジトリ
     * @param prm_pDepo_WallAAPrism 壁プリズムブロック（WallAAPrismActorオブジェクト）が登録されているデポジトリ
     * @param prm_wall_dep 壁ブロックの長さ（１つのWallPartsActorオブジェクトのX座標軸長さ）
     * @param prm_wall_width 壁ブロックの高さ（１つのWallPartsActorオブジェクトのY座標軸長さ）
     * @param prm_wall_height 壁ブロックの高さ（１つのWallPartsActorオブジェクトのZ座標軸長さ）
     */
    virtual void config(
            GgafCore::GgafActorDepository* prm_pDepo_WallAAB,
            GgafCore::GgafActorDepository* prm_pDepo_WallAAPrism,
            int prm_wall_dep, int prm_wall_width, int prm_wall_height);
    /**
     * 初期処理 .
     * デポジトリ(_pDepo_Wall)のチェックを行っているのみ .
     */
    virtual void initialize() override;

    /**
     * 外壁表示間隔時間等を計算し設定 .
     * オーバーライドする場合、その処理の中で WalledSectionScene::onActive() も呼び出して下さい。
     */
    virtual void onActive() override;


    /**
     * 外壁を出現させ、移動させる.
     * オーバーライドする場合、その処理の中で WalledSectionScene::processBehavior() も呼び出して下さい。
     */
    virtual void processBehavior() override;

    virtual void processFinal() override;

    WallPartsActor* getLastWallParts();



    /**
     * 手前ブロックの透過機能を有効にする。
     * 無効にしたい場合は NULL を設定する
     * @param prm_pTarget_FrontAlpha 手前の基準になるアクター
     */
    void enableFrontAlpha(GgafDxCore::GgafDxGeometricActor* prm_pTarget_FrontAlpha) {
        _pTarget_FrontAlpha = prm_pTarget_FrontAlpha;
    }


    virtual ~WalledSectionScene();
};

}
#endif /*WALLEDSECTIONSCENE_H_*/
