#ifndef GGAFDX9MODEL_H_
#define GGAFDX9MODEL_H_
namespace GgafDx9Core {

/**
 * モデル基底クラス.
 * キャラ(アクター)の形状や色などを保持するクラスです。<BR>
 * @version 1.00
 * @since 2008/02/21
 * @author Masatoshi Tsuge
 */
class GgafDx9Model : public GgafCore::GgafObject {
    friend class GgafDx9ModelManager;

protected:
public:
    /** [r]ID */
    int _id;

    /** [r]モデル定義の識別名。(50文字まで) */
    char* _model_name;

    /** [r]マテリアル配列 */
    D3DMATERIAL9* _paD3DMaterial9_default;
    /** [r]マテリアル数 */
    DWORD _dwNumMaterials;

    /** [rw]モデルの境界球半径。画面外判定に利用される */
    FLOAT _fBoundingSphereRadius;
    /** [r]点滅強度 (0.0 <= _fblink <= 1.0)。GgafDx9TextureBlinkerにより操作すること */
    FLOAT _fPowerBlink;
    /** [r]点滅対象RGB値(0.0 <= tex2D()のrgbの何れか <= 1.0)。GgafDx9TextureBlinkerにより操作すること */
    FLOAT _fBlinkThreshold;
    //_fBlinkThreshold = 1.0 と指定した場合、PSでtex2D()のサンプリングカラーの
    //r,g,b 何れか >= 1.0 の の場合、_fPowerBlink倍数の色(rgb)を加算
    //ゼビウスの地上物破壊後の赤い点滅のようなことをしたかった。

    /** [r]テクスチャ資源コネクション配列 */
    GgafDx9TextureConnection** _papTextureCon;
    /** [r]点滅操作支援オブジェクト */
    GgafDx9TextureBlinker* _pTextureBlinker;
    DWORD _frame_blinker;
    /** [r]モデル単位の初期処理が実行済みかどうか(draw時チェック＆変更) */
    bool _is_init_model;
    /**
     * コンストラクタ<BR>
     * @param prm_model_name モデル定義の識別名。".x"を追加すると定義Xファイル名になる。
     */
    GgafDx9Model(char* prm_model_name);

    char* getName(){
        return _model_name;
    }

    /**
     * モデルの境界球半径の倍率設定。
     * 境界球半径とは、ローカル座標の原点から全頂点の距離で最大の長さで、
     * この値は、画面外判定に利用されてるため、モデル表示時に独自に拡大を行った場合。
     * この値を更新しないと画面外判定が正しく行われない。<BR>
     * 例えば、表示時に５倍の拡大で表示した場合、本メソッドで<BR>
     * <BR>
     * setBoundingSphereRadiusRate(5.0)<BR>
     * <BR>
     * とすると、画面外判定が正しくなる。<BR>
     * 注意は、モデル１に対して１つしか設定出来無いということ。<BR>
     * 複数のアクターでバラバラの拡大表示をする場合は、最大の拡大のものを採用するしか無い。<BR>
     * @param prm_rate 拡大率
     */
    virtual void setBoundingSphereRadiusRate(FLOAT prm_rate) {
        _fBoundingSphereRadius *= prm_rate;
    }

    /**
     * モデルを描画します.
     * @param prm_pActor_Target 描画するモデルのアクター
     * @return HRESULT
     */
    virtual HRESULT draw(GgafDx9DrawableActor* prm_pActor_Target) = 0;

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
