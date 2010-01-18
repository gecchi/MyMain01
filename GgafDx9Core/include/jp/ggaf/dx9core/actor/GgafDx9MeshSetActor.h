#ifndef GGAFDX9MESHSETACTOR_H_
#define GGAFDX9MESHSETACTOR_H_
namespace GgafDx9Core {

/**
 * メッシュアクター.
 * GgafDx9DrawableActor を継承し、Xファイル定義のメッシュ表示機能を<BR>
 * 追加、さらに同一モデル複数オブジェクトの頂点バッファを持ち、大量表示に最適化したアクターです<BR>
 * @version 1.00
 * @since 2009/06/16
 * @author Masatoshi Tsuge
 */
class GgafDx9MeshSetActor : public GgafDx9DrawableActor {
private:

public:

    /** モデル資源 */
    GgafDx9MeshSetModel* _pMeshSetModel;
    /** エフェクト資源 */
    GgafDx9MeshSetEffect* _pMeshSetEffect;

    /** 描画時のオブジェクト数 */
    int _draw_set_num;
    //int _draw_object_num;


    /**
     * コンストラクタ
     * @param prm_name  モデル名称（デバッグログで表示、なんでも良い）
     * @param prm_model モデル定義名、末尾に ".x" をつけてXファイル名になること。
     * @param prm_technique エフェクト(GgafDx9MeshSetEffect.fx) のテクニック。
     * @param prm_pChecker   様々な判定を行なうチェッカークラスのインスタンスを渡す
     */
    GgafDx9MeshSetActor(const char* prm_name,
                        const char* prm_model_id,
                        const char* prm_effect_id,
                        const char* prm_technique,
                        GgafDx9Checker* prm_pChecker );

    /**
     * ＜OverRide です＞<BR>
     */
    virtual void processDraw() override;

    /**
     * α設定.
     * ＜オーバーライト＞
     * @param prm_fAlpha
     */
    void setAlpha(float prm_fAlpha) override;


//    int chkSequenceOfTheSameDrawDepth() {
//
//
//    }

    virtual ~GgafDx9MeshSetActor(); //デストラクタ
};

}
#endif /*GGAFDX9MESHSETACTOR_H_*/
