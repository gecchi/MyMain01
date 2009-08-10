#ifndef GGAFDX9MODEL_H_
#define GGAFDX9MODEL_H_
namespace GgafDx9Core {

/**
 * モデル基底クラス.
 * キャラ(アクター)の形状や色などを保持するクラスです。<BR>
 */
class GgafDx9Model : public GgafCore::GgafObject {
    friend class GgafDx9ModelManager;

protected:
public:
    /** ID */
    int _id;

    /** モデル定義の識別名。(50文字まで) */
    char* _model_name;
    /** 次のGgafDx9Modelへのポインタ。終端はNULL */
    //GgafDx9Model*	_pModel_Next;

    /** マテリアル配列 */
    D3DMATERIAL9* _paD3DMaterial9_default;
    /** マテリアル数 */
    DWORD _dwNumMaterials;

    /** このモデルのローカル座標の原点から全頂点の距離で最大の長さ */
    FLOAT _max_radius;

    /** テクスチャ資源コネクション配列 */
    GgafDx9TextureConnection** _papTextureCon;

    /**
     * コンストラクタ<BR>
     * @param prm_model_name モデル定義の識別名。".x"を追加すると定義Xファイル名になる。
     */
    GgafDx9Model(char* prm_model_name);

    virtual char* getName(){
        return _model_name;
    }

    /**
     * モデルを描画します.
     * @param prm_pActor_Target 描画するモデルのアクター
     * @return HRESULT
     */
    virtual HRESULT draw(GgafDx9BaseActor* prm_pActor_Target) = 0;

    /**
     * モデルを再構築します.
     */
    virtual void restore() = 0;

    /**
     * モデルを解放します.
     */
    virtual void release() = 0;

    /**
     * デバイスロスト時コールバック
     */
    virtual void onDeviceLost() = 0;

    /**
     * デストラクタ<BR>
     * deleteするのはGgafDx9ModelManagerである<BR>
     */
    virtual ~GgafDx9Model(); //デストラクタ
};

}
#endif /*GGAFDX9MODEL_H_*/
