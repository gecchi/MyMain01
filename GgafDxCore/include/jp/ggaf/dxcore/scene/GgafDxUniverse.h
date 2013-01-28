#ifndef GGAFDXUNIVERSE_H_
#define GGAFDXUNIVERSE_H_

namespace GgafDxCore {

#ifdef P_UNIVERSE
    #define P_CAM (P_UNIVERSE->_pCamera)
#else
    #error P_UNIVERSE isnt define
#endif

/**
 * GgafDxCore名前空間のこの世クラス.
 * GgafDxCore名前空間内では、このクラスを基底のこの世クラスとします。<BR>
 * (旧GgafDxWorldBound)
 * @version 1.00
 * @since 2008/07/30
 * @author Masatoshi Tsuge
 */
class GgafDxUniverse : public GgafCore::GgafUniverse {

private:
    /**
     * フレーム毎の描画処理 .
     * 段階レンダリングを行なうため void GgafElement<T>::draw() をオーバーライド。<BR>
     * 本クラス(GgafUniverse)は頂点のシーンであるため、その他のアクターやシーンの全ての、<BR>
     * void GgafElement<T>::draw() が呼ばれることも無いでしょう。<BR>
     */
    virtual void draw() override;

public:
    class SeArray {
    public:
        int _p;
        GgafDxSe* _apSe[MAX_SE_AT_ONCE];
        int _volume[MAX_SE_AT_ONCE];
        float _pan[MAX_SE_AT_ONCE];
        float _rate_frequency[MAX_SE_AT_ONCE];
        GgafDxGeometricActor* _apActor[MAX_SE_AT_ONCE];
        SeArray();

        void add(GgafDxSe* prm_pSe, int prm_volume, float prm_pan, float prm_rate_frequency, GgafDxGeometricActor* prm_pActor);

        void play(int index);
    };
    GgafCore::GgafLinkedListRing<SeArray>* _pRing_pSeArray;

public:
    /** カメラ */
    GgafDxCamera* _pCamera;

    /** レンダリング順序配列に登録されている各アクターリストの先頭のアクターの配列 */
    static GgafDxDrawableActor* _apAlphaActorFirstList_DrawDepthLevel[];
    /** レンダリング順序配列に登録されている各アクターリストの末尾のアクターの配列 */
    static GgafDxDrawableActor* _apAlphaActorLastList_DrawDepthLevel[];

    /** 描画アクターのカーソル */
    static GgafDxDrawableActor* _pActor_DrawActive;

    /** [r]アプリケーション領域、X座標の最小値 */
    static coord _X_goneLeft;
    /** [r]アプリケーション領域、X座標の最大値 */
    static coord _X_goneRight;
    /** [r]アプリケーション領域、Y座標の最大値 */
    static coord _Y_goneTop;
    /** [r]アプリケーション領域、Y座標の最小値 */
    static coord _Y_goneBottom;
    /** [r]アプリケーション領域、Z座標の最大値 */
    static coord _Z_goneFar;
    /** [r]アプリケーション領域、Z座標の最小値 */
    static coord _Z_goneNear;
    static std::string _seqkey_se_delay;

public:
    GgafDxUniverse(const char* prm_name, GgafDxCamera* prm_pCamera);

    virtual void processSettlementBehavior() override;

    virtual ~GgafDxUniverse();


    /**
     * 描画レベル（順序）を登録 .
     * αなど半透明はこちらに登録した方が、ある程度前後関係が正しく表示される。
     * @param prm_draw_depth_level レベル
     * @param prm_pActor アクター
     */
    static int setDrawDepthLevel(int prm_draw_depth_level, GgafDxDrawableActor* prm_pActor);

    void registSe(GgafDxSe* prm_pSe,
                  int prm_volume,
                  float prm_pan,
                  float prm_rate_frequency,
                  int prm_delay,
                  GgafDxGeometricActor* prm_pActor);

};

}
#endif /*GGAFDXUNIVERSE_H_*/
