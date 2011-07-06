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
    /** [r]最大可能同時描画セット数（キャラクタ数）*/
    int _set_num;
    /** [r]モデル定義の識別名。(50文字まで) */
    char* _model_name;

    /** [r]マテリアル配列 */
    D3DMATERIAL9* _paMaterial_default;
    /** [r]マテリアル数 */
    DWORD _dwNumMaterials;

    /** [rw]モデルの境界球半径。画面外判定に利用される */
    FLOAT _radius_bounding_sphere;
    /** [r]点滅強度 (0.0 <= _fblink <= 1.0)。GgafDx9TextureBlinkerにより操作すること */
    FLOAT _power_blink;
    /** [r]点滅対象RGB値(0.0 <= tex2D()のrgbの何れか <= 1.0)。GgafDx9TextureBlinkerにより操作すること */
    FLOAT _blink_threshold;
    //_blink_threshold = 1.0 と指定した場合、PSでtex2D()のサンプリングカラーの
    //r,g,b 何れか >= 1.0 の の場合、_power_blink倍数の色(rgb)を加算
    //ゼビウスの地上物破壊後の赤い点滅のようなことをしたかった。

    /** [r]テクスチャ資源コネクション配列 */
    GgafDx9TextureConnection** _papTextureCon;
    /** [r]点滅操作支援オブジェクト */
    GgafDx9TextureBlinker* _pTextureBlinker;
    /** [r]GgafDx9TextureBlinker専用カウンター */
    frame _blinker_frames;

    /** [r/w]モデルのスペキュラーの範囲（ハーフベクトル・法線内積のg_specular乗） */
    float _specular;
    /** [r/w]モデルのスペキュラーの強度（全体の倍率、0.0以外を設定するとスペキュラが有効になる） */
    float _specular_power;

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
     * モデルのスペキュラー強度を設定 .
     * 両方の引数に 0 以外の数値を設定すると、スペキュラーが有効になります。
     * 次のように設定するとスペキュラーを無効に出来ます。（デフォルトはスペキュラーを無効）
     * setSpecular(0, 0)
     * @param prm_specular モデルのスペキュラーの範囲（ハーフベクトル・法線内積のg_specular乗）
     * @param prm_specular_power モデルのスペキュラーの強度（全体の倍率、0.0以外を設定するとスペキュラが有効になる）
     */
    virtual void setSpecular(float prm_specular, float prm_specular_power) {
        _specular = prm_specular;
        _specular_power = prm_specular_power;
    }

    /**
     * モデルを描画します.
     * @param prm_pActor_Target 描画するモデルのアクター
     * @return HRESULT
     */
    virtual HRESULT draw(GgafDx9DrawableActor* prm_pActor_Target, int prm_draw_set_num = 1) = 0;

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
