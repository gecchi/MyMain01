#ifndef GGAFDX9UNIVERSE_H_
#define GGAFDX9UNIVERSE_H_
namespace GgafDx9Core {

#define MAX_DRAW_DEPTH_LEVEL 1000

/**
 * GgafDx9Core名前空間のこの世クラス.
 * GgafDx9Core名前空間内では、このクラスを基底のこの世クラスとします。<BR>
 */
class GgafDx9Universe : public GgafCore::GgafUniverse {

public:

    /** カメラ */
    static GgafDx9Camera* _pCamera;

    /** アクター順序レンダリングのための遠さ別のグループ */
    static GgafCore::GgafActor* _apAlphaActorList_DrawDepthLevel[];
    /** アクター順序レンダリング最遠グループ(一番最初にレンダリング) */
    static GgafCore::GgafActor* _pActors_DrawMaxDrawDepth;
    static GgafCore::GgafActor* _pActor_DrawActive;
    GgafDx9Universe(const char* prm_name);

    virtual ~GgafDx9Universe();

    /**
     * フレーム毎の描画処理 .
     * 段階レンダリングを行なうため void GgafElement<T>::drawMain() をオーバーライド。<BR>
     * 本クラス(GgafUniverse)は頂点のシーンであるため、その他のアクターやシーンの全ての、<BR>
     * void GgafElement<T>::drawMain() が呼ばれることも無いでしょう。<BR>
     */
    virtual void drawMain();

    /**
     * 描画レベル（順序）を登録 .
     * αなど半透明はこちらに登録した方が、ある程度前後関係が正しく表示される。
     * @param prm_draw_depth_level レベル
     * @param prm_pActor アクター
     */
    static void setDrawDepthLevel(int prm_draw_depth_level, GgafCore::GgafActor* prm_pActor);

    /**
     * 描画レベル（順序）を最遠で登録.
     * 不透明なオブジェクトは極力こちらで登録する
     * @param prm_pActor アクター
     */
    static void setDrawDepthMaxLevel(GgafCore::GgafActor* prm_pActor);
};

}
#endif /*GGAFDX9UNIVERSE_H_*/
