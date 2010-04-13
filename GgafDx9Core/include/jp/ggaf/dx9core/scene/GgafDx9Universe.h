#ifndef GGAFDX9UNIVERSE_H_
#define GGAFDX9UNIVERSE_H_

#define pCAM (GgafDx9Universe::_pCamera)

namespace GgafDx9Core {

//#define MAX_DRAW_DEPTH_LEVEL 1000
#define MAX_DRAW_DEPTH_LEVEL 500
#define MAX_SE_AT_ONCE 10
/**
 * GgafDx9Core名前空間のこの世クラス.
 * GgafDx9Core名前空間内では、このクラスを基底のこの世クラスとします。<BR>
 * (旧GgafDx9World)
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

        SeArray() {
            _p = 0;
            for (int i = 0; i < MAX_SE_AT_ONCE; i++) {
                _apSe[i] = NULL;
            }
        }

        void add(GgafDx9Se* prm_pSe) {
            if (_p < MAX_SE_AT_ONCE) {
                _apSe[_p] = prm_pSe;
                _p++;
            }
        }
    };
    GgafCore::GgafLinkedListRing<SeArray>* _pRing_pSeArray;

public:

    /** カメラ */
    static GgafDx9Camera* _pCamera;

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



    GgafDx9Universe(const char* prm_name);

    virtual void processPreJudgement() override;

    virtual ~GgafDx9Universe();



    /**
     * 描画レベル（順序）を登録 .
     * αなど半透明はこちらに登録した方が、ある程度前後関係が正しく表示される。
     * @param prm_draw_depth_level レベル
     * @param prm_pActor アクター
     */
    static int setDrawDepthLevel(int prm_draw_depth_level, GgafDx9DrawableActor* prm_pActor);


    void registSe(GgafDx9Se* prm_pSe, DWORD prm_delay = 0);

//    /**
//     * 描画レベル（順序）を最遠で登録.
//     * 不透明なオブジェクトは極力こちらで登録する
//     * @param prm_pActor アクター
//     */
//    static void setDrawDepthMaxLevel(GgafDx9DrawableActor* prm_pActor);
};

}
#endif /*GGAFDX9UNIVERSE_H_*/
