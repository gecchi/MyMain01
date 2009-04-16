#ifndef GGAFDX9WORLD_H_
#define GGAFDX9WORLD_H_
namespace GgafDx9Core {

#define MAX_DRAW_DEPTH_LEVEL 10000

/**
 * GgafDx9Core名前空間の世界クラス.
 * GgafDx9Core名前空間内では、このクラスを基底の世界クラスとします。<BR>
 */
class GgafDx9World : public GgafCore::GgafWorld {

public:

    /** カメラ */
    static GgafDx9Camera* _pCamera;

    /** アクター順序レンダリングのための遠さ別のグループ */
    static GgafCore::GgafActor* _apAlphaActorList_DrawDepthLevel[];
    /** アクター順序レンダリング最遠グループ(一番最初にレンダリング) */
    static GgafCore::GgafActor* _pActors_DrawMaxDrawDepth;

    GgafDx9World(const char* prm_name);

    virtual ~GgafDx9World();

    /**
     * フレーム毎の描画処理<BR>
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
#endif /*GGAFDX9WORLD_H_*/
