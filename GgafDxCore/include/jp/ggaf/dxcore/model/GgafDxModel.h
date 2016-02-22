#ifndef GGAFDXCORE_GGAFDXMODEL_H_
#define GGAFDXCORE_GGAFDXMODEL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/GgafObject.h"

#include "jp/ggaf/dxcore/util/XFile/framework/Frm_Mesh.h"
#include "jp/ggaf/dxcore/util/XFile/ToolBox/IOModel_X.h"

#include <d3d9.h>
#include <d3dx9.h>
#ifdef __GNUG__
    #undef __in
    #undef __out
#endif

//#define Obj_GgafDxDynaD3DXMeshModel      (0x1U)          //0b 00000000 00000000 00000000 00000001
#define Obj_GgafDxD3DXAniMeshModel       (0x2U)            //0b 00000000 00000000 00000000 00000010
#define Obj_GgafDxD3DXMeshModel          (0x4U)            //0b 00000000 00000000 00000000 00000100
#define Obj_GgafDxSpriteModel            (0x8U)            //0b 00000000 00000000 00000000 00001000
#define Obj_GgafDxSpriteSetModel         (0x10U)           //0b 00000000 00000000 00000000 00010000
#define Obj_GgafDxBoardModel             (0x20U)           //0b 00000000 00000000 00000000 00100000
#define Obj_GgafDxBoardSetModel          (0x40U)           //0b 00000000 00000000 00000000 01000000
#define Obj_GgafDxMeshModel              (0x80U)           //0b 00000000 00000000 00000000 10000000
#define Obj_GgafDxMeshSetModel           (0x100U)          //0b 00000000 00000000 00000001 00000000
#define Obj_GgafDxCubeMapMeshModel       (0x200U)          //0b 00000000 00000000 00000010 00000000
#define Obj_GgafDxCubeMapMeshSetModel    (0x400U)          //0b 00000000 00000000 00000100 00000000
#define Obj_GgafDxMorphMeshModel         (0x800U)          //0b 00000000 00000000 00001000 00000000
#define Obj_GgafDxCubeMapMorphMeshModel  (0x1000U)         //0b 00000000 00000000 00010000 00000000
#define Obj_GgafDxWorldBoundModel        (0x2000U)         //0b 00000000 00000000 00100000 00000000
#define Obj_GgafDxPointSpriteModel       (0x4000U)         //0b 00000000 00000000 01000000 00000000
#define Obj_GgafDxMassMeshModel          (0x8000U)         //0b 00000000 00000000 10000000 00000000

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
    /** [r]テクスチャ資源コネクション配列のデフォルトのインデックス。通常は0。 */
    int _default_texture_index;
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

    struct SpriteXFileFmt {
        float width;
        float height;
        char texture_file[256];
        int row_texture_split;
        int col_texture_split;
    };


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
     * 規定のテクスチャ（マテリアル番号0番のテクスチャ) を変更。
     * @param prm_material_no マテリアル番号（のテクスチャに置き換わる）
     */
    inline void setDefaultTextureMaterialNo(int prm_material_no) {
        _default_texture_index = prm_material_no;
    }

    /**
     * 規定のテクスチャ資源へのコネクションを取得 .
     * @return 規定のテクスチャ資源
     */
    inline GgafDxTextureConnection* getDefaultTextureConnection() {
        return _papTextureConnection[_default_texture_index];
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
    //virtual void swapTopTextureOrder(const char* prm_texture0);



    char* obtainSpriteFmtX(SpriteXFileFmt* pSpriteFmt_out, char* pLockedData);


    /**
     * 3D頂点バッファにFrameTransformMatrix変換と法線を設定。
     * @param prm_paVtxBuffer
     * @param prm_size_of_vtx_unit
     * @param model_pModel3D
     * @param paNumVertices 頂点連結前の頂点サブセット数の配列
     *        （モデルがサブセット単位で個別基準（位置、回転、拡大）を保持してる場合）
     */
//    void prepareVtx(void* prm_paVtxBuffer, UINT prm_size_of_vtx_unit,
//                    Frm::Model3D* model_pModel3D,
//                    uint16_t* paNumVertices,
//                    GgafDxModel* prm_pModel = nullptr);
    void prepareVtx(void* prm_paVtxBuffer, UINT prm_size_of_vtx_unit,
                    Frm::Model3D* model_pModel3D,
                    uint16_t* paNumVertices);

    static void calcTangentAndBinormal(
            D3DXVECTOR3* p0, D3DXVECTOR2* uv0,
            D3DXVECTOR3* p1, D3DXVECTOR2* uv1,
            D3DXVECTOR3* p2, D3DXVECTOR2* uv2,
            D3DXVECTOR3* outTangent, D3DXVECTOR3* outBinormal);


    /**
     * 空間の3点v0 v1 v2 より、直線 v0v1 と v1v2 の成す角(角v1)を求める
     * @param v0
     * @param v1
     * @param v2
     * @return 成す角(ラディアン)
     */
    static float getRadv1_v0v1v2(Frm::Vertex& v0, Frm::Vertex& v1, Frm::Vertex& v2);

    void setMaterial(Frm::Mesh* in_pMeshesFront,
                     int* pOut_material_num,
                     D3DMATERIAL9**                pOut_paMaterial,
                     GgafDxTextureConnection***    pOut_papTextureConnection);
    void setDefaultMaterial(D3DMATERIAL9* out_pD3DMATERIAL9);
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
