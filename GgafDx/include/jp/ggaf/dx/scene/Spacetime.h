#ifndef GGAF_DX_SPACETIME_H_
#define GGAF_DX_SPACETIME_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/scene/Spacetime.h"

#include "jp/ggaf/dx/Config.h"
#include "jp/ggaf/dx/actor/camera/Camera.h"


#define EX_RENDER_DEPTH_INDEXS_FRONT_NUM   (5)
#define REGULAR_RENDER_DEPTH_INDEXS_NUM    (CONFIG::RENDER_DEPTH_INDEXS_NUM)  //段階レンダー分解能
#define EX_RENDER_DEPTH_INDEXS_BACK_NUM    (5)
#define ALL_RENDER_DEPTH_INDEXS_NUM        (EX_RENDER_DEPTH_INDEXS_FRONT_NUM+REGULAR_RENDER_DEPTH_INDEXS_NUM+EX_RENDER_DEPTH_INDEXS_BACK_NUM)

#define RENDER_DEPTH_INDEX_FRONT      (EX_RENDER_DEPTH_INDEXS_FRONT_NUM)  //通常の最前面
#define RENDER_DEPTH_INDEX_BACK       (EX_RENDER_DEPTH_INDEXS_FRONT_NUM + REGULAR_RENDER_DEPTH_INDEXS_NUM - 1) //通常の最背面

 /** 最前面より手前の特別な表示深度レベル(0～5  0:RENDER_DEPTH_INDEX_FRONTと同じ、5:最前面) */
#define RENDER_DEPTH_INDEX_SP_FRONT(X)  (RENDER_DEPTH_INDEX_FRONT - (X))

 /** 最前面より奥の特別な表示深度レベル(0～5  0:RENDER_DEPTH_INDEX_BACKと同じ、5:最背面) */
#define RENDER_DEPTH_INDEX_SP_BACK(X)  (RENDER_DEPTH_INDEX_BACK + (X))

namespace GgafDx {

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
    FigureActor** _papFirstActor_in_render_depth;
    /** レンダリング順序配列に登録されている各アクターリストの末尾のアクターの配列 */
    FigureActor** _papLastActor_in_render_depth;

    /** 描画アクターのカーソル */
    static FigureActor* _pActor_draw_active;
    static int render_depth_index_active;
    /** [r]アプリケーション領域、X座標の最小値 */
    const coord _x_bound_left;
    /** [r]アプリケーション領域、X座標の最大値 */
    const coord _x_bound_right;
    /** [r]アプリケーション領域、Y座標の最小値 */
    const coord _y_bound_bottom;
    /** [r]アプリケーション領域、Y座標の最大値 */
    const coord _y_bound_top;
    /** [r]アプリケーション領域、Z座標の最小値 */
    const coord _z_bound_near;
    /** [r]アプリケーション領域、Z座標の最大値 */
    const coord _z_bound_far;

    /** [r]アプリケーション領域(Board用)、X座標の最小値 */
    const coord _x_bound_left_b;
    /** [r]アプリケーション領域(Board用)、X座標の最大値 */
    const coord _x_bound_right_b;
    /** [r]アプリケーション領域(Board用)、Y座標の最小値 */
    const coord _y_bound_bottom_b;
    /** [r]アプリケーション領域(Board用)、Y座標の最大値 */
    const coord _y_bound_top_b;


    static std::string _seqkey_se_delay;

    /** オブジェクトのカメラからの遠さ(pixcoord)に対する、段階レンダリングインデックスの配列 */
    int* _paDep2Lv;
    /** 段階レンダリングが有効なカメラ（始点から）から奥への距離 */
    dxcoord _dep_resolution;


public:
    Spacetime(const char* prm_name, Camera* prm_pCamera);

    virtual void processSettlementBehavior() override;

    virtual ~Spacetime();

    virtual Camera* getCamera() {
        return _pCamera;
    }

    /**
     * この世にアクターを登録(2Dオブジェクト用) .
     * 登録すると、この世に描画されることとなる。
     * @param prm_pActor 対象アクター
     * @return 登録された描画順序深度レベル
     */
    int registerFigureActor2D(FigureActor* prm_pActor);

    /**
     * この世にアクターを登録(3Dオブジェクト用) .
     * 登録すると、この世に描画されることとなる。
     * αなど半透明はこちらに登録した方が、ある程度前後関係が正しく表示される。
     * @param prm_pActor 対象アクター
     * @return 登録された描画順序深度レベル
     */
    int registerFigureActor3D(FigureActor* prm_pActor);

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
};

}
#endif /*GGAF_DX_SPACETIME_H_*/
