#ifndef GGAFDXCORE_GGAFDXSPACETIME_H_
#define GGAFDXCORE_GGAFDXSPACETIME_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/scene/GgafSpacetime.h"

#include "jp/ggaf/dxcore/GgafDxProperties.h"
#include "jp/ggaf/dxcore/actor/camera/GgafDxCamera.h"


#define EX_RENDER_DEPTH_LEVELS_FRONT_NUM   (5)
#define REGULAR_RENDER_DEPTH_LEVELS_NUM    (PROPERTY::RENDER_DEPTH_LEVELS_NUM)  //段階レンダー分解能
#define EX_RENDER_DEPTH_LEVELS_BACK_NUM    (5)
#define ALL_RENDER_DEPTH_LEVELS_NUM        (EX_RENDER_DEPTH_LEVELS_FRONT_NUM+REGULAR_RENDER_DEPTH_LEVELS_NUM+EX_RENDER_DEPTH_LEVELS_BACK_NUM)

#define RENDER_DEPTH_LEVEL_FRONT      (EX_RENDER_DEPTH_LEVELS_FRONT_NUM)  //通常の最前面
#define RENDER_DEPTH_LEVEL_BACK       (EX_RENDER_DEPTH_LEVELS_FRONT_NUM + REGULAR_RENDER_DEPTH_LEVELS_NUM - 1) //通常の最背面

 //最前面より手前の特別な表示深度レベル
#define RENDER_DEPTH_LEVEL_SP_FRONT1  (RENDER_DEPTH_LEVEL_FRONT - 1)
#define RENDER_DEPTH_LEVEL_SP_FRONT2  (RENDER_DEPTH_LEVEL_SP_FRONT1 - 1)
#define RENDER_DEPTH_LEVEL_SP_FRONT3  (RENDER_DEPTH_LEVEL_SP_FRONT2 - 1)
#define RENDER_DEPTH_LEVEL_SP_FRONT4  (RENDER_DEPTH_LEVEL_SP_FRONT3 - 1)
#define RENDER_DEPTH_LEVEL_SP_FRONT5  (RENDER_DEPTH_LEVEL_SP_FRONT4 - 1) //最前面の手前の中でも最も最前面

 //最前面より奥の特別な表示深度レベル
#define RENDER_DEPTH_LEVEL_SP_BACK1  (RENDER_DEPTH_LEVEL_BACK + 1)
#define RENDER_DEPTH_LEVEL_SP_BACK2  (RENDER_DEPTH_LEVEL_SP_BACK1 + 1)
#define RENDER_DEPTH_LEVEL_SP_BACK3  (RENDER_DEPTH_LEVEL_SP_BACK2 + 1)
#define RENDER_DEPTH_LEVEL_SP_BACK4  (RENDER_DEPTH_LEVEL_SP_BACK3 + 1)
#define RENDER_DEPTH_LEVEL_SP_BACK5  (RENDER_DEPTH_LEVEL_SP_BACK4 + 1)  //最背面の奥の中でも最も奥

namespace GgafDxCore {

/**
 * GgafDxCore名前空間のこの世クラス.
 * GgafDxCore名前空間内では、このクラスを基底のこの世クラスとします。<BR>
 * (旧GgafDxWorldBound)
 * @version 1.00
 * @since 2008/07/30
 * @author Masatoshi Tsuge
 */
class GgafDxSpacetime : public GgafCore::GgafSpacetime {

private:
    /**
     * フレーム毎の描画処理 .
     * 段階レンダリングを行なうため void GgafElement<T>::draw() をオーバーライド。<BR>
     * 本クラス(GgafSpacetime)は頂点のシーンであるため、その他のアクターやシーンの全ての、<BR>
     * void GgafElement<T>::draw() が呼ばれることも無いでしょう。<BR>
     */
    virtual void draw() override;

public:
    class SeArray {
    public:
        int _p;
        GgafDxSe* _apSe[64];
        int _volume[64];
        float _pan[64];
        float _rate_frequency[64];
        GgafDxGeometricActor* _apActor[64];
        SeArray();

        void add(GgafDxSe* prm_pSe, int prm_volume, float prm_pan, float prm_rate_frequency, GgafDxGeometricActor* prm_pActor);

        void play(int index);
    };
    GgafCore::GgafLinkedListRing<SeArray>* _pRing_pSeArray;

public:
    /** カメラ */
    GgafDxCamera* _pCamera;

    /** レンダリング順序配列に登録されている各アクターリストの先頭のアクターの配列 */
    GgafDxFigureActor** _papFirstActor_in_render_depth;
    /** レンダリング順序配列に登録されている各アクターリストの末尾のアクターの配列 */
    GgafDxFigureActor** _papLastActor_in_render_depth;

    /** 描画アクターのカーソル */
    static GgafDxFigureActor* _pActor_draw_active;

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

    static std::string _seqkey_se_delay;

    /** オブジェクトのカメラからの遠さに対する、段階レンダリングインデックス */
    int* _paDep2Lv;
    /** 段階レンダリングが有効なカメラ（始点から）から奥への距離 */
    dxcoord _dep_resolution;


public:
    GgafDxSpacetime(const char* prm_name, GgafDxCamera* prm_pCamera);

    virtual void processSettlementBehavior() override;

    virtual ~GgafDxSpacetime();

    virtual GgafDxCamera* getCamera() {
        return _pCamera;
    }

    /**
     * 描画レベル（順序）を登録 .
     * αなど半透明はこちらに登録した方が、ある程度前後関係が正しく表示される。
     * @param prm_render_depth_level レベル
     * @param prm_pActor アクター
     */
    int setDrawDepthLevel2D(GgafDxFigureActor* prm_pActor);
    int setDrawDepthLevel3D(GgafDxFigureActor* prm_pActor);

    void registerSe(GgafDxSe* prm_pSe,
                    int prm_volume,
                    float prm_pan,
                    float prm_rate_frequency,
                    int prm_delay,
                    GgafDxGeometricActor* prm_pActor);

};

}
#endif /*GGAFDXCORE_GGAFDXSPACETIME_H_*/
