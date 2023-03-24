#ifndef GGAF_LIB_WALLSECTIONSCENE_H_
#define GGAF_LIB_WALLSECTIONSCENE_H_
#include "jp/ggaf/GgafLibCommonHeader.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"

#define FULL_VAL (-2)
#define KARA_VAL (-2)

namespace GgafLib {

/**
 * X軸方向スクロールの壁ブロックセクションシーン .
 * WallScene を構成するシーンの１つであり、
 * WallSectionScene が連って一つの WallScene を構成します。<BR>
 * WallSectionScene は壁ブロック情報ファイルから壁情報を読み込み、
 * タイミング（スクロールスピード）を計りながら、自動で壁を出現させます。<BR>
 * @version 1.00
 * @since 2010/10/18
 * @author Masatoshi Tsuge
 */
class WallSectionScene : public DefaultScene {

    /**
     * 壁ブロック(MassWallActor)の配置情報構造体
     */
    struct WallInfo {
        /** プリズム位置情報(> 0の場合はプリズム、0の場合はBOX) */
        pos_t _pos_info;
        /** 表示時のY座標 */
        int _y;
        /** 表示時のZ座標 */
        int _z;
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
    /** [r]壁ブロックの長さ（１つのMassWallActorオブジェクトのX座標軸長さ）*/
    coord _wall_dep;
    /** [r]壁ブロックの高さ（１つのMassWallActorオブジェクトのY座標軸長さ）*/
    coord _wall_height;
    /** [r]壁ブロックの幅（１つのMassWallActorオブジェクトのZ座標軸長さ）*/
    coord _wall_width;
    /** [r]外壁表示X座標位置 */
    coord _wall_start_x;
    /** [r]繰り返し回数 */
    int _loop_num;
    /** [r]繰り返しカウンタ */
    int _cnt_loop;
    /** [r]外壁表示間隔時間 */
    frame _frame_of_launch_next;
    /** [r]表示済み外壁シーンの長さ(壁ブロック数) */
    int _cnt_area_len;
    /** [r]全壁ブロック(MassWallActor)の配置情報 */
    WallInfo** _papaWallInfo;
    /** [r]全壁ブロック(MassWallActor)の配置情報の、外壁の壁ブロック数。要素＝何ブロック目か(_area_lenインデックス) */
    int* _paWallNum;
    /** [r]壁ブロック(MassWallActor)デポジトリ */
    GgafCore::ActorDepository* _pDepo_wall;
    /** [r]手前ブロックの透過機能有効時の基準となるアクター */
    GgafDx::GeometricActor* _pActor_infront_alpha_target;
    /** セクションシーン繰り返しフラグ */
    bool _is_loop_end;
    MassWallActor* _pWallLast;

    WallScene*  _pWallScene;

public:
    /**
     * コンストラクタ .
     * 壁ブロック情報ファイルを読み込み、オブジェクトに展開します。
     * @param prm_name シーン名
     * @param prm_data_filename 壁ブロック情報ファイル
     * @param prm_pWallScene 親の壁シーンオブジェクト
     */
    WallSectionScene(const char* prm_name, const char* prm_data_filename, WallScene* prm_pWallScene);

    /**
     * 外壁シーンを設定.
     * new した後、initialize() が実行されるまでに config して下さい。
     * @param prm_pDepo_wall 壁ブロック（WallAABActorオブジェクト）が登録されているデポジトリ
     * @param prm_wall_start_x 外壁出現X座標位置
     * @param prm_wall_dep 壁ブロックの長さ（１つのMassWallActorオブジェクトのX座標軸長さ）
     * @param prm_wall_width 壁ブロックの高さ（１つのMassWallActorオブジェクトのY座標軸長さ）
     * @param prm_wall_height 壁ブロックの高さ（１つのMassWallActorオブジェクトのZ座標軸長さ）
     */
    virtual void config(
            GgafCore::ActorDepository* prm_pDepo_wall,
            coord prm_wall_start_x,
            coord prm_wall_dep, coord prm_wall_width, coord prm_wall_height);

    /**
     * 初期処理 .
     * デポジトリ(_pDepo_wall)のチェックを行っているのみ .
     */
    virtual void initialize() override;

    /**
     * 外壁表示間隔時間等を計算し設定 .
     * オーバーライドする場合、その処理の中で WallSectionScene::onActive() も呼び出して下さい。
     */
    virtual void onActive() override;

    /**
     * 外壁を出現させ、移動させる.
     * オーバーライドする場合、その処理の中で WallSectionScene::processBehavior() も呼び出して下さい。
     */
    virtual void processBehavior() override;

    MassWallActor* getLastWallParts() const;

    /**
     * 手前ブロックの透過機能を有効にする。
     * 無効にしたい場合は nullptr を設定する
     * @param prm_pActor_infront_alpha_target 手前の基準になるアクター
     */
    void enableInfrontAlpha(GgafDx::GeometricActor* prm_pActor_infront_alpha_target) {
        _pActor_infront_alpha_target = prm_pActor_infront_alpha_target;
    }

    /**
     * YZ面に、ブロックのセットが出現完了時に呼び出されるコールバック。 .
     * オーバーライドしてもいいのよ。
     * @param prm_loop_count セクションのループ数カウント(0～)
     * @param prm_wall_count セクションのYZ面ブロックセット数カウント(0～)
     * @param prm_wall_x 出現したYZ面のブロックのX座標
     */
    virtual void onBlockLaunch(int prm_loop_count, int prm_wall_count, coord prm_wall_x) {};

    virtual ~WallSectionScene();
};

}
#endif /*GGAF_LIB_WALLSECTIONSCENE_H_*/
