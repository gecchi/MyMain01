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

        SeArray();

        void add(GgafDxSe* prm_pSe, int prm_volume, float prm_pan, float prm_rate_frequency);

        void play(int index);
    };
    GgafCore::GgafLinkedListRing<SeArray>* _pRing_pSeArray;

public:

    /** カメラ */
    GgafDxCamera* _pCamera;

    /** アクター順序レンダリングのための遠さ別のグループ */
    static GgafDxDrawableActor* _apAlphaActorFirstList_DrawDepthLevel[];
    static GgafDxDrawableActor* _apAlphaActorLastList_DrawDepthLevel[];
    /** アクター順序レンダリング最遠グループ(一番最初にレンダリング) */
    static GgafDxDrawableActor* _pActors_DrawMaxDrawDepth;
    static GgafDxDrawableActor* _pActor_DrawActive;


    static coord _X_goneLeft;
    static coord _X_goneRight;
    static coord _Y_goneTop;
    static coord _Y_goneBottom;
    static coord _Z_goneFar;
    static coord _Z_goneNear;

//    GgafDxTextureManager* _pCubeMapTextureManager;


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


    void registSe(GgafDxSe* prm_pSe, int prm_volume, float prm_pan, float prm_rate_frequency, int prm_delay );

//    /**
//     * 描画レベル（順序）を最遠で登録.
//     * 不透明なオブジェクトは極力こちらで登録する
//     * @param prm_pActor アクター
//     */
//    static void setDrawDepthMaxLevel(GgafDxDrawableActor* prm_pActor);
};

}
#endif /*GGAFDXUNIVERSE_H_*/
