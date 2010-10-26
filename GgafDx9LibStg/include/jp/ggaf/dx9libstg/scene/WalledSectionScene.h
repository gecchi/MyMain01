#ifndef WALLEDSCENE_H_
#define WALLEDSCENE_H_

#define FULL_VAL (-2)
#define KARA_VAL (-2)

namespace GgafDx9LibStg {

/**
 * 外壁シーン .
 * @version 1.00
 * @since 2010/10/18
 * @author Masatoshi Tsuge
 */
class WalledSectionScene : public DefaultScene {

    /**
     * 壁ブロック(WallActor)の配置情報構造体
     */
    struct WallInfo {
        /** 表示時のY座標 */
        int _Y;
        /** 表示時のZ座標 */
        int _Z;
        /** 可視表示面情報 */
        int _wall_draw_face;
        /** 当たり判定領域AAB情報         */
        int _aColliBoxStretch[6];
    };
public:
    /** [r]外壁シーンの長さ（X座標軸の壁ブロック数） */
    int _area_len;
    /** [r]外壁シーンの高さ（Y座標軸の壁ブロック数） */
    int _area_height;
    /** [r]外壁シーンの幅（Z座標軸の壁ブロック数） */
    int _area_width;
    /** [r]壁ブロックの長さ（１つのWallActorオブジェクトのX座標軸長さ）*/
    int _wall_dep;
    /** [r]壁ブロックの高さ（１つのWallActorオブジェクトのY座標軸長さ）*/
    int _wall_height;
    /** [r]壁ブロックの幅（１つのWallActorオブジェクトのZ座標軸長さ）*/
    int _wall_width;
    /** [r]外壁表示X座標位置 */
    int _wall_start_X;
    /** [r]外壁移動スピード(値は正、但し移動方向はX軸負の方向) */
    int _ground_speed;
    /** [r]繰り返し回数 */
    int _loop_num;
    /** [r]繰り返しカウンタ */
    int _cnt_loop;
    /** [r]外壁表示間隔時間 */
    frame _frame_of_launch_interval;
    /** [r]表示済み外壁シーンの長さ */
    int _cnt_area_len;
    /** [r]全壁ブロック(WallActor)の配置情報 */
    WallInfo** _papaWallInfo;
    /** [r]全壁ブロック(WallActor)の配置情報の、外壁シーンの長さ別個数 */
    int* _paWallInfoLen;
    /** [r]壁ブロック(WallActor)ディスパッチャー */
    GgafCore::GgafActorDispatcher* _pDispatcher_Wall;
    /** [r]手前ブロックの透過機能有効時の基準となるアクター */
    GgafDx9Core::GgafDx9GeometricActor* _pTarget_FrontAlpha;
    /** [r/w]毎フレームprocessSettlementBehavior()で、配下アクター全てに実行される関数。*/
    void (*_pFuncWallMove)(GgafCore::GgafObject*, void*, void*);

    WallActor* _pWallLast;


    /**
     * コンストラクタ .
     * 壁ブロック情報ファイルを読み込み、オブジェクトに展開します。
     * 【使用上注意】
     * コンストラクタ実行後、initialize() までの間に、壁ブロック(WallActor)ディスパッチャー(_pDispatcher_Wall)に
     * お好きな壁ブロック（WallActor実装クラスのオブジェクト）を登録し下さい。
     * @param prm_name シーン名
     * @param prm_data_filename 壁ブロック情報ファイル
     * @param prm_wall_dep 壁ブロックの長さ（１つのWallActorオブジェクトのX座標軸長さ）
     * @param prm_wall_width 壁ブロックの高さ（１つのWallActorオブジェクトのY座標軸長さ）
     * @param prm_wall_height 壁ブロックの高さ（１つのWallActorオブジェクトのZ座標軸長さ）
     * @param prm_ground_speed 外壁移動スピード(値は正、但し移動方向はX軸負の方向)
     * @return
     */
    WalledSectionScene(const char* prm_name,
                const char* prm_data_filename,
                int prm_wall_dep, int prm_wall_width, int prm_wall_height,
                int prm_ground_speed, int prm_loop_num = 1);
    /**
     * 初期処理 .
     * ディスパッチャー(_pDispatcher_Wall)のチェックを行っているのみ .
     */
    virtual void initialize() override;

    /**
     * 外壁表示間隔時間等を計算し設定 .
     * オーバーライドする場合、その処理の中で WalledSectionScene::onActive() も呼び出して下さい。
     */
    virtual void onActive() override;

    /**
     * 配下アクター全てに_pFuncWallMove を実行。
     * オーバーライドする場合、DefaultScene::processSettlementBehavior(); を呼び出すことを忘れずに。
     */
    virtual void processSettlementBehavior() override;


    /**
     * 外壁を出現させ、移動させる.
     * オーバーライドする場合、その処理の中で WalledSectionScene::processBehavior() も呼び出して下さい。
     */
    virtual void processBehavior() override;

    virtual void processFinal() override;

    /**
     * 手前ブロックの透過機能を有効にする。
     * 無効にしたい場合は NULL を設定する
     * @param prm_pTarget_FrontAlpha 手前の基準になるアクター
     */
    void enableFrontAlpha(GgafDx9Core::GgafDx9GeometricActor* prm_pTarget_FrontAlpha) {
        _pTarget_FrontAlpha = prm_pTarget_FrontAlpha;
    }

    /**
     * _pFuncWallMove にデフォルトで設定されている関数 .
     * アクターをX軸の負の方向に_ground_speedスクロールさせる
     * @param pThat アクターのポインタ
     * @param p1 _ground_speedのポインタ
     * @param p2 NULL（未使用）
     */
    static void moveX(GgafCore::GgafObject* pThat, void* p1, void* p2);

    virtual ~WalledSectionScene();
};

}
#endif /*WALLEDSCENE_H_*/
