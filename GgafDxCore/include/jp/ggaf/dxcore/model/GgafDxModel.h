#ifndef GGAFDXCORE_GGAFDXMODEL_H_
#define GGAFDXCORE_GGAFDXMODEL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/GgafObject.h"

#include <d3d9.h>
#include <d3dx9.h>

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
    /** [r]モデルインスタンス種類 */
    uint32_t _obj_model;
    /** [r]マテリアル配列 */
    D3DMATERIAL9* _paMaterial_default;
    /** [r]マテリアル数 */
    DWORD _num_materials;

    /** [rw]モデルの境界球半径。画面外判定に利用される */
    FLOAT _bounding_sphere_radius;
    /** [r]点滅強度 (0.0 <= _power_blink <= 1.0)。GgafDxTextureBlinkerにより操作すること */
    FLOAT _power_blink;
    /** [r]点滅対象RGB値(0.0 <= tex2D()のrgbの何れか <= 1.0)。GgafDxTextureBlinkerにより操作すること */
    FLOAT _blink_threshold;
    //_blink_threshold = 1.0 と指定した場合、PSでtex2D()のサンプリングカラーの
    //r,g,b 何れか >= 1.0 の の場合、_power_blink倍数の色(rgb)を加算
    //ゼビウスのキャラの赤い点滅のようなことをしたかったため作成。

    /** [r]テクスチャ資源コネクション配列 */
    GgafDxTextureConnection** _papTextureConnection;
    /** [r]点滅操作支援オブジェクト */
    GgafDxTextureBlinker* const _pTexBlinker;
    /** [r]GgafDxTextureBlinker専用カウンター */
    frame _blinker_frames;

    /** [r/w]モデルのスペキュラーの範囲（ハーフベクトル・法線内積のg_specular乗） */
    float _specular;
    /** [r/w]モデルのスペキュラーの強度（全体の倍率、0.0以外を設定するとスペキュラが有効になる） */
    float _specular_power;

    /** [r]モデル単位の初期処理が実行済みかどうか(draw時チェック＆変更) */
    bool _is_init_model;

    UINT _num_pass;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_model_name モデル定義の識別名。".x"を追加すると定義Xファイル名になる。
     */
    explicit GgafDxModel(const char* prm_model_name);

    char* getName(){
        return _model_name;
    }

    /**
     * 色強度と、対象色しきい値を設定 .
     * 対象色しきい値とは、色強度が影響を与える対象のテクスチャの色の強さ具合です。<BR>
     * ピクセルシェーダーにおいて、<BR>
     * ・ここまでの計算した色（テクスチャやライト考慮済み）・・・ colOut.rgba<BR>
     * ・テクスチャの色 ・・・ colTex.rgba<BR>
     * ・対象色しきい値 ・・・ g_tex_blink_threshold<BR>
     * ・現在の色強度値 ・・・ g_tex_blink_power<BR>
     * とした場合、以下の様な処理を行なっています。<BR>
     * <code><pre>
     * <BR>
     * if (colTex.r >= g_tex_blink_threshold || colTex.g >= g_tex_blink_threshold || colTex.b >= g_tex_blink_threshold) {
     *     colOut *= g_tex_blink_power; //あえてαも倍率を掛ける。点滅を目立たせる。
     * }
     * </pre></code>
     * ゼビウスの地上物の赤い点滅のようなエフェクトを簡単に実現するために実装・・(ﾅﾝﾉｺｺｯﾁｬ
     * @param prm_power_blink 色強度値1 (負の数 ～ 0:黒 ～ 1.0:等倍強度 ～ )
     * @param prm_blink_threshold 色強度値が影響する対象色しきい値 (0.0 ～ 1.0)
     */
    void setBlinkPower(float prm_power_blink, float prm_blink_threshold) {
        _power_blink = prm_power_blink;
        _blink_threshold = prm_blink_threshold;
    }

    /**
     * 色強度値のみを設定 .
     * @param prm_power_blink 色強度値1 (負の数 ～ 0:黒 ～ 1.0:等倍強度 ～ )
     */
    void setBlinkPower(float prm_power_blink) {
        _power_blink = prm_power_blink;
    }
    /**
     * 色強度反映対象の色しきい値を設定 .
     * @param prm_blink_threshold 色強度値が影響する対象色しきい値 (0.0 ～ 1.0)
     */
    void setBlinkThreshold(float prm_blink_threshold) {
        _blink_threshold = prm_blink_threshold;
    }
    /**
     * 色強度値を取得 .
     * @return 色強度値
     */
    float getBlinkPower() {
        return _power_blink;
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


    inline GgafDxTextureBlinker* getTexBlinker() {
        return _pTexBlinker;
    }

    /**
     * モデルを描画 .
     * 下位クラスでモデル描画ロジックを実装して下さい。
     * @param prm_pActor_target 描画するモデルのアクター
     * @param prm_draw_set_num 描画するモデルのセット数
     * @return
     */
    virtual HRESULT draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num = 1) = 0;

    /**
     * マテリアルのテクスチャを入れ替えて切り替える。 .
     * 予めモデルに複数のテクスチャ(マテリアル)を登録して置く必要がある。<BR>
     * 具体的には X ファイルで予め複数マテリアルエントリ（テクスチャ）を書いておく。<BR>
     * @param prm_texture0 予めモデルに複数のテクスチャの切り替える先のテクスチャID
     *                    （＝GgafDxTextureManager にエントリされている識別文字列）
     */
    virtual void swapTopTextureOrder(const char* prm_texture0);

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
#endif /*GGAFDXCORE_GGAFDXMODEL_H_*/
