#ifndef GGAFDX9UNIVERSE_H_
#define GGAFDX9UNIVERSE_H_

namespace GgafDx9Core {

#ifdef P_UNIVERSE
    #define P_CAM (P_UNIVERSE->_pCamera)
#else
    #error P_UNIVERSE isnt define
#endif

/**
 * GgafDx9Core名前空間のこの世クラス.
 * GgafDx9Core名前空間内では、このクラスを基底のこの世クラスとします。<BR>
 * (旧GgafDx9WorldBound)
 * @version 1.00
 * @since 2008/07/30
 * @author Masatoshi Tsuge
 */
class GgafDx9Universe : public GgafCore::GgafUniverse {

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
        GgafDx9Se* _apSe[MAX_SE_AT_ONCE];
        LONG _volume[MAX_SE_AT_ONCE];
        float _pan[MAX_SE_AT_ONCE];
        float _rate_frequency[MAX_SE_AT_ONCE];

        SeArray();

        void add(GgafDx9Se* prm_pSe, LONG prm_volume, float prm_pan, float prm_rate_frequency);

        void play(int index);
    };
    GgafCore::GgafLinkedListRing<SeArray>* _pRing_pSeArray;

public:

    /** カメラ */
    GgafDx9Camera* _pCamera;

    /** アクター順序レンダリングのための遠さ別のグループ */
    static GgafDx9DrawableActor* _apAlphaActorList_DrawDepthLevel[];
    /** アクター順序レンダリング最遠グループ(一番最初にレンダリング) */
    static GgafDx9DrawableActor* _pActors_DrawMaxDrawDepth;
    static GgafDx9DrawableActor* _pActor_DrawActive;


    static int _X_goneLeft;
    static int _X_goneRight;
    static int _Y_goneTop;
    static int _Y_goneBottom;
    static int _Z_goneFar;
    static int _Z_goneNear;

//    GgafDx9TextureManager* _pCubeMapTextureManager;


    GgafDx9Universe(const char* prm_name, GgafDx9Camera* prm_pCamera);

    virtual void processSettlementBehavior() override;

    virtual ~GgafDx9Universe();



    /**
     * 描画レベル（順序）を登録 .
     * αなど半透明はこちらに登録した方が、ある程度前後関係が正しく表示される。
     * @param prm_draw_depth_level レベル
     * @param prm_pActor アクター
     */
    static int setDrawDepthLevel(int prm_draw_depth_level, GgafDx9DrawableActor* prm_pActor);


    void registSe(GgafDx9Se* prm_pSe, LONG prm_volume, float prm_pan, float prm_rate_frequency, int prm_delay );

//    /**
//     * 描画レベル（順序）を最遠で登録.
//     * 不透明なオブジェクトは極力こちらで登録する
//     * @param prm_pActor アクター
//     */
//    static void setDrawDepthMaxLevel(GgafDx9DrawableActor* prm_pActor);
};

}
#endif /*GGAFDX9UNIVERSE_H_*/
