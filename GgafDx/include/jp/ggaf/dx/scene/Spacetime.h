#ifndef GGAF_DX_SPACETIME_H_
#define GGAF_DX_SPACETIME_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/core/scene/Spacetime.h"

#include "jp/ggaf/dx/Config.h"
#include "jp/ggaf/dx/actor/camera/Camera.h"

/** 段階レンダリングの段階総数 */
#define ALL_RENDER_DEPTH_INDEXS_NUM  (CONFIG::RENDER_DEPTH_INDEXS_NUM_EX_NEAR + CONFIG::RENDER_DEPTH_INDEXS_NUM + CONFIG::RENDER_DEPTH_INDEXS_NUM_EX_FAR)

#define RENDER_DEPTH_NEAR_INDEX      (CONFIG::RENDER_DEPTH_INDEXS_NUM_EX_NEAR)  //通常の最前面
#define RENDER_DEPTH_FAR_INDEX       (CONFIG::RENDER_DEPTH_INDEXS_NUM_EX_FAR + CONFIG::RENDER_DEPTH_INDEXS_NUM - 1) //通常の最背面

 /** 最前面より手前の特別な表示深度レベル(0～5  0:RENDER_DEPTH_NEAR_INDEXと同じ、5:最前面) */
#define RENDER_DEPTH_INDEX_SP_FRONT(X)  (RENDER_DEPTH_NEAR_INDEX - (X))

 /** 最前面より奥の特別な表示深度レベル(0～5  0:RENDER_DEPTH_FAR_INDEXと同じ、5:最背面) */
#define RENDER_DEPTH_INDEX_SP_BACK(X)  (RENDER_DEPTH_FAR_INDEX + (X))

namespace GgafDx {

typedef GgafCore::LinearOctree<GgafCore::Actor> WorldOctree;
typedef GgafCore::LinearOctreeRounder<GgafCore::Actor> WorldOctreeRounder;
typedef GgafCore::LinearQuadtree<GgafCore::Actor> WorldQuadtree;
typedef GgafCore::LinearQuadtreeRounder<GgafCore::Actor> WorldQuadtreeRounder;

typedef GgafCore::LinearQuadtree<GgafCore::Actor> ViewQuadtree;
typedef GgafCore::LinearQuadtreeRounder<GgafCore::Actor> ViewQuadtreeRounder;

/**
 * Core名前空間のこの世クラス.
 * Core名前空間内では、このクラスを基底のこの世クラスとします。<BR>
 * (旧WorldBound)
 * @version 1.00
 * @since 2008/07/30
 * @author Masatoshi Tsuge
 */
class Spacetime : public GgafCore::Spacetime {

private:
    /**
     * フレーム毎の描画処理 .
     * 段階レンダリングを行なうため void GgafCore::Element<T>::draw() をオーバーライド。<BR>
     * 本クラス(GgafCore::Spacetime)は頂点のシーンであるため、その他のアクターやシーンの全ての、<BR>
     * void GgafCore::Element<T>::draw() が呼ばれることも無いでしょう。<BR>
     */
    virtual void draw() override;

public:
    class SeArray {
    public:
        int _p;
        Se* _apSe[64];
        int _volume[64];
        float _pan[64];
        float _frequency_rate[64];
        bool _can_looping[64];
        GeometricActor* _apActor[64];
        SeArray();

        void add(Se* prm_pSe, int prm_volume, float prm_pan, float prm_frequency_rate, bool prm_can_looping, GeometricActor* prm_pActor);

        void play(int index);
    };
    GgafCore::RingLinkedList<SeArray>* _pRing_pSeArray;

public:
    /** カメラ */
    Camera* _pCamera;

    /** レンダリング順序配列に登録されている各アクターリストの先頭のアクターの配列 */
    FigureActor** _papFirstRenderActor;
    /** レンダリング順序配列に登録されている各アクターリストの末尾のアクターの配列 */
    FigureActor** _papLastRenderActor;

    static int render_depth_index_active;
    /** [r]アプリケーション領域(ヒットチェック可能座標領域)、X座標の最小値 */
    const coord _x_bound_left;
    /** [r]アプリケーション領域(ヒットチェック可能座標領域)、X座標の最大値 */
    const coord _x_bound_right;
    /** [r]アプリケーション領域(ヒットチェック可能座標領域)、Y座標の最小値 */
    const coord _y_bound_bottom;
    /** [r]アプリケーション領域(ヒットチェック可能座標領域)、Y座標の最大値 */
    const coord _y_bound_top;
    /** [r]アプリケーション領域(ヒットチェック可能座標領域)、Z座標の最小値 */
    const coord _z_bound_near;
    /** [r]アプリケーション領域(ヒットチェック可能座標領域)、Z座標の最大値 */
    const coord _z_bound_far;

    /** [r]アプリケーション領域(ヒットチェック可能座標領域)(Board用)、X座標の最小値 */
    const coord _x_bound_left_b;
    /** [r]アプリケーション領域(ヒットチェック可能座標領域)(Board用)、X座標の最大値 */
    const coord _x_bound_right_b;
    /** [r]アプリケーション領域(ヒットチェック可能座標領域)(Board用)、Y座標の最小値 */
    const coord _y_bound_bottom_b;
    /** [r]アプリケーション領域(ヒットチェック可能座標領域)(Board用)、Y座標の最大値 */
    const coord _y_bound_top_b;


    static std::string _seqkey_se_delay;

    /** オブジェクトのカメラからの遠さ(pixcoord)に対する、段階レンダリングインデックスの配列 */
    int* _paDep2Lv;
    /** 段階レンダリングが有効なカメラ（始点から）から奥への距離 */
    dxcoord _dep_resolution;


    double _w_r;
    double _h_r;

    /** [r] 描画用バックバッファ矩形領域の内、ゲームに表示する矩形の左上座標のX座標(主画面) */
    pixcoord _primary_buffer_source_left;
    /** [r] 描画用バックバッファ矩形領域の内、ゲームに表示する矩形の左上座標のY座標(主画面) */
    pixcoord _primary_buffer_source_top;
    /** [r] 描画用バックバッファ矩形領域の内、ゲームに表示する矩形の左上座標空の幅(主画面) */
    pixcoord _primary_buffer_source_width;
    /** [r] 描画用バックバッファ矩形領域の内、ゲームに表示する矩形の左上座標空の高さ(主画面) */
    pixcoord _primary_buffer_source_height;

    /** [r] 描画用バックバッファ矩形領域の内、ゲームに表示する矩形の左上座標のX座標(副画面) */
    pixcoord _secondary_buffer_source_left;
    /** [r] 描画用バックバッファ矩形領域の内、ゲームに表示する矩形の左上座標のY座標(副画面) */
    pixcoord _secondary_buffer_source_top;
    /** [r] 描画用バックバッファ矩形領域の内、ゲームに表示する矩形の左上座標空の幅(副画面) */
    pixcoord _secondary_buffer_source_width;
    /** [r] 描画用バックバッファ矩形領域の内、ゲームに表示する矩形の左上座標空の高さ(副画面) */
    pixcoord _secondary_buffer_source_height;

    static WorldOctree* _pWorldOctree;
    static WorldOctreeRounder* _pWorldOctreeRounder;
    static WorldQuadtree* _pWorldQuadtree;
    static WorldQuadtreeRounder* _pWorldQuadtreeRounder;

    static ViewQuadtree* _pViewQuadtree;
    static ViewQuadtreeRounder* _pViewQuadtreeRounder;

public:
    Spacetime(const char* prm_name, Camera* prm_pCamera);

    virtual void processSettlementBehavior() override;

    virtual ~Spacetime();

    virtual Camera* getCamera() {
        return _pCamera;
    }

    /**
     * この世にアクターを登録 .
     * 登録すると、この世に描画されることとなる。
     * @param prm_pActor 対象アクター
     * @return 登録された描画順序深度レベル
     */
    int registerDrawActor(FigureActor* prm_pActor);

    /**
     * この世に効果音オブジェクトを登録する .
     * 登録すると、この世に効果音が発声される。
     * 同時期に同じ効果音を何度も登録すると、音量跳ね上がり防止の為
     * 勝手にばらつかせて発声させる。
     * @param prm_pSe 効果音オブジェクト
     * @param prm_volume ボリューム(0 ～ 1000)
     * @param prm_pan    パン(left:-1.0 ～ center:0 ～ right:1.0)
     * @param prm_frequency_rate 元の周波数に乗ずる率
     * @param prm_delay  遅延フレーム
     * @param prm_pActor 効果音発声元アクター
     */
    void registerSe(Se* prm_pSe,
                    int prm_volume,
                    float prm_pan,
                    float prm_frequency_rate,
                    int prm_delay,
                    bool prm_can_looping,
                    GeometricActor* prm_pActor);

    /**
     * ビュー座標をワールド座標に変換する .
     * @param prm_view_x ビュー座標X軸要素
     * @param prm_view_y ビュー座標Y軸要素
     * @param prm_depth カメラ視点からの距離
     * @param out_world_x 対応するワールド座標X軸要素
     * @param out_world_y 対応するワールド座標Y軸要素
     * @param out_world_z 対応するワールド座標Z軸要素
     */
    void cnvViewCoordToWorld(coord prm_view_x, coord prm_view_y, coord prm_depth,
                             coord& out_world_x, coord& out_world_y, coord& out_world_z);

    /**
     * ワールド座標をビュー座標変換する .
     * @param prm_world_x ワールド座標X軸要素
     * @param prm_world_y ワールド座標Y軸要素
     * @param prm_world_z ワールド座標Z軸要素
     * @param out_view_x 対応するビュー座標X軸要素
     * @param out_view_y 対応するビュー座標Y軸要素
     */
    void cnvWorldCoordToView(coord prm_world_x, coord prm_world_y, coord prm_world_z,
                             coord& out_view_x, coord& out_view_y);


    /**
      * ワールド座標上のアクターの「種別Aグループ 対 種別Bグループ」の ヒットチェック を行う  .
      * ３次元（８分木） or ２次元（４分木）
      * processJudgement() で呼ぶ必要あり。（processSettlementBehavior() で ツリーに登録している為）<BR>
      * @param prm_kind_groupA アクター種別Aグループ
      * @param prm_kind_groupB アクター種別Bグループ
      */
     virtual void executeWorldHitCheck(kind_t prm_kind_groupA, kind_t prm_kind_groupB);

     /**
      * ビュー座標上のアクターの「種別Aグループ 対 種別Bグループ」の ヒットチェック を行う  .
      * processJudgement() で呼ぶ必要あり。（processSettlementBehavior() で ツリーに登録している為）<BR>
      * @param prm_kind_groupA アクター種別Aグループ
      * @param prm_kind_groupB アクター種別Bグループ
      */
     virtual void executeViewHitCheck(kind_t prm_kind_groupA, kind_t prm_kind_groupB);

     virtual void processFinal() override;

    /**
     * デバッグ：描画順表示
     */
    void dumpRenderDepthOrder();


};

}
#endif /*GGAF_DX_SPACETIME_H_*/
