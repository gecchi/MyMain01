#ifndef GGAFDX9MESHSETACTOR_H_
#define GGAFDX9MESHSETACTOR_H_
namespace GgafDx9Core {

/**
 * メッシュアクター.
 * GgafDx9DrawableActor を継承し、Xファイル定義のメッシュ表示機能を<BR>
 * 追加したアクターです<BR>
 */
class GgafDx9MeshSetActor : public GgafDx9DrawableActor {
private:

public:

    /** モデル資源 */
    GgafDx9MeshSetModel* _pMeshSetModel;
    /** エフェクト資源 */
    GgafDx9MeshSetEffect* _pMeshSetEffect;

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
                     const char* prm_model,
                     const char* prm_effect,
                     const char* prm_technique,
                     GgafDx9Checker* prm_pChecker );

    /**
     * ＜OverRide です＞<BR>
     */
    virtual void processDrawMain();

    /**
     * α設定.
     * ＜オーバーライト＞
     * @param prm_fAlpha
     */
    void setAlpha(float prm_fAlpha);


//    int chkSequenceOfTheSameDrawDepth() {
//
//
//    }

    virtual ~GgafDx9MeshSetActor(); //デストラクタ
};

}
#endif /*GGAFDX9MESHSETACTOR_H_*/
