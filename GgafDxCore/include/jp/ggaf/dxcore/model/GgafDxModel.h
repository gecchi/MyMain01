#ifndef GGAFDXMODEL_H_
#define GGAFDXMODEL_H_
namespace GgafDxCore {

/**
 * モデル基底クラス.
 * キャラ(アクター)の形状や色などを保持するクラスです。<BR>
 * @version 1.00
 * @since 2008/02/21
 * @author Masatoshi Tsuge
 */
class GgafDxModel : public GgafCore::GgafObject {
    friend class GgafDxModelManager;

protected:
public:
    class VERTEX_3D_BASE {
    public:
        float x, y, z;    // 頂点座標
        float nx, ny, nz; // 法線
    };


    /** [r]ID */
    int _id;
    /** [r]最大可能同時描画セット数（キャラクタ数）*/
    int _set_num;
    /** [r]モデル定義の識別名。(50文字まで) */
    char* _model_name;

    /** [r]マテリアル配列 */
    D3DMATERIAL9* _paMaterial_default;
    /** [r]マテリアル数 */
    DWORD _num_materials;

    /** [rw]モデルの境界球半径。画面外判定に利用される */
    FLOAT _bounding_sphere_radius;
    /** [r]点滅強度 (0.0 <= _fblink <= 1.0)。GgafDxTextureBlinkerにより操作すること */
    FLOAT _power_blink;
    /** [r]点滅対象RGB値(0.0 <= tex2D()のrgbの何れか <= 1.0)。GgafDxTextureBlinkerにより操作すること */
    FLOAT _blink_threshold;
    //_blink_threshold = 1.0 と指定した場合、PSでtex2D()のサンプリングカラーの
    //r,g,b 何れか >= 1.0 の の場合、_power_blink倍数の色(rgb)を加算
    //ゼビウスのキャラの赤い点滅のようなことをしたかったため作成。

    /** [r]テクスチャ資源コネクション配列 */
    GgafDxTextureConnection** _papTextureCon;
    /** [r]点滅操作支援オブジェクト */
    GgafDxTextureBlinker* _pTextureBlinker;
    /** [r]GgafDxTextureBlinker専用カウンター */
    frame _blinker_frames;

    /** [r/w]モデルのスペキュラーの範囲（ハーフベクトル・法線内積のg_specular乗） */
    float _specular;
    /** [r/w]モデルのスペキュラーの強度（全体の倍率、0.0以外を設定するとスペキュラが有効になる） */
    float _specular_power;

    /** [r]モデル単位の初期処理が実行済みかどうか(draw時チェック＆変更) */
    bool _is_init_model;

    UINT _numPass;
    /**
     * コンストラクタ<BR>
     * @param prm_model_name モデル定義の識別名。".x"を追加すると定義Xファイル名になる。
     */
    GgafDxModel(char* prm_model_name);

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
     * モデルを描画 .
     * 下位クラスでモデル描画ロジックを実装して下さい。
     * @param prm_pActor_Target 描画するモデルのアクター
     * @param prm_draw_set_num 描画するモデルのセット数
     * @return
     */
    virtual HRESULT draw(GgafDxDrawableActor* prm_pActor_Target, int prm_draw_set_num = 1) = 0;

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
     * deleteするのはGgafDxModelManagerである<BR>
     */
    virtual ~GgafDxModel(); //デストラクタ
};

}
#endif /*GGAFDXMODEL_H_*/
