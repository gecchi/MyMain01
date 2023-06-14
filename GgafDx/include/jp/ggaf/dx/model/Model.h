#ifndef GGAF_DX_MODEL_H_
#define GGAF_DX_MODEL_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/core/Object.h"

#include "jp/ggaf/dx/Config.h"
#include "jp/ggaf/dx/util/XFile/framework/Frm_Mesh.h"
#include "jp/ggaf/dx/util/XFile/ToolBox/IOModel_X.h"
#include "jp/ggaf/dx/manager/ModelManager.h"

#include <d3d9.h>
#include <d3dx9.h>
#ifdef __GNUG__
    #undef __in
    #undef __out
#endif
//#define Obj_GgafDx_DynaD3DXMeshModel      (0x1U)          //0b 00000000 00000000 00000000 00000001
#define Obj_GgafDx_D3DXAniMeshModel            (0x2U)            //0b 00000000 00000000 00000000 00000010
#define Obj_GgafDx_D3DXMeshModel               (0x4U)            //0b 00000000 00000000 00000000 00000100
#define Obj_GgafDx_IPlaneModel                 (0x8U)            //0b 00000000 00000000 00000000 00001000
#define Obj_GgafDx_SpriteModel                 (0x10U)           //0b 00000000 00000000 00000000 00010000
#define Obj_GgafDx_SpriteSetModel              (0x20U)           //0b 00000000 00000000 00000000 00100000
#define Obj_GgafDx_BoardModel                  (0x40U)           //0b 00000000 00000000 00000000 01000000
#define Obj_GgafDx_BoardSetModel               (0x80U)           //0b 00000000 00000000 00000000 10000000
#define Obj_GgafDx_MeshModel                   (0x100U)          //0b 00000000 00000000 00000001 00000000
#define Obj_GgafDx_MeshSetModel                (0x200U)          //0b 00000000 00000000 00000010 00000000
#define Obj_GgafDx_CubeMapMeshModel            (0x400U)          //0b 00000000 00000000 00000100 00000000
#define Obj_GgafDx_CubeMapMeshSetModel         (0x800U)          //0b 00000000 00000000 00001000 00000000
#define Obj_GgafDx_MorphMeshModel              (0x1000U)         //0b 00000000 00000000 00010000 00000000
#define Obj_GgafDx_CubeMapMorphMeshModel       (0x2000U)         //0b 00000000 00000000 00100000 00000000
#define Obj_GgafDx_WorldBoundModel             (0x4000U)         //0b 00000000 00000000 01000000 00000000
#define Obj_GgafDx_PointSpriteModel            (0x8000U)         //0b 00000000 00000000 10000000 00000000
#define Obj_GgafDx_MassModel                   (0x10000U)        //0b 00000000 00000001 00000000 00000000
#define Obj_GgafDx_MassMeshModel               (0x20000U)        //0b 00000000 00000010 00000000 00000000
#define Obj_GgafDx_MassBoardModel              (0x40000U)        //0b 00000000 00000100 00000000 00000000
#define Obj_GgafDx_MassSpriteModel             (0x80000U)        //0b 00000000 00001000 00000000 00000000
#define Obj_GgafDx_MassMorphMeshModel          (0x100000U)       //0b 00000000 00010000 00000000 00000000
#define Obj_GgafDx_MassPointSpriteModel        (0x200000U)       //0b 00000000 00100000 00000000 00000000
#define Obj_GgafDx_PointSpriteSetModel         (0x400000U)       //0b 00000000 01000000 00000000 00000000
#define Obj_GgafDx_FramedBoardModel            (0x800000U)       //0b 00000000 10000000 00000000 00000000
#define Obj_GgafDx_RegularPolygonSpriteModel   (0x1000000U)      //0b 00000001 00000000 00000000 00000000
#define Obj_GgafDx_RegularPolygonBoardModel    (0x2000000U)      //0b 00000010 00000000 00000000 00000000
#define Obj_GgafDx_BoneAniMeshModel            (0x4000000U)      //0b 00000100 00000000 00000000 00000000
#define Obj_GgafDx_SkinAniMeshModel            (0x8000000U)      //0b 00001000 00000000 00000000 00000000
#define Obj_GgafDx_FramedSpriteModel           (0x10000000U)     //0b 00010000 00000000 00000000 00000000

namespace GgafDx {

/**
 * モデル基底クラス.
 * キャラ(アクター)の形状や色などを保持するクラスです。<BR>
 * @version 1.00
 * @since 2008/02/21
 * @author Masatoshi Tsuge
 */
class Model : public GgafCore::Object {
    friend class ModelManager;

public:
    struct VERTEX_POS {
        float x, y, z;    // 頂点座標
    };

    struct VERTEX_POS_NOMAL : public VERTEX_POS {
        float nx, ny, nz; // 法線
    };

    /** [r]最大可能同時描画セット数（キャラクタ数）*/
    int _draw_set_num;
    int _max_draw_set_num;
    /** [r]モデル定義の識別名。(50文字まで) */
    char* _model_id;
    /** [r]モデルタイプ(TYPE_XXXX_MODEL) */
    char  _model_type;

    /** [r]マテリアル配列 */
    D3DMATERIAL9* _paMaterial_default;
    /** [r]マテリアル数 */
    DWORD _num_materials;
    /** [r]テクスチャファイル名の配列 */
    std::string* _pa_texture_filenames;
    /** [r]テクスチャ資源コネクション配列 */
    TextureConnection** _papTextureConnection;


    /** [rw]モデルの境界球半径。画面外判定に利用される */
    FLOAT _bounding_sphere_radius;
    /** [r]点滅強度 (0.0 <= _power_blink <= 1.0)。TextureBlinkerにより操作すること */
    FLOAT _power_blink;
    /** [r]点滅対象RGB値(0.0 <= tex2D()のrgbの何れか <= 1.0)。TextureBlinkerにより操作すること */
    FLOAT _blink_threshold;
    //_blink_threshold = 1.0 と指定した場合、PSでtex2D()のサンプリングカラーの
    //r,g,b 何れか >= 1.0 の の場合、_power_blink倍数の色(rgb)を加算
    //ゼビウスのキャラの赤い点滅のようなことをしたかったため作成。


    /** [r]テクスチャ資源コネクション配列のデフォルトのインデックス。通常は0。 */
    int _default_texture_index;
    /** [r]点滅操作支援オブジェクト */
    TextureBlinker* const _pTexBlinker;
    /** [r]TextureBlinker専用カウンター */
    frame _blinker_frames;

    /** [r/w]モデルのスペキュラーの範囲（ハーフベクトル・法線内積のg_specular乗） */
    float _specular;
    /** [r/w]モデルのスペキュラーの強度（全体の倍率、0.0以外を設定するとスペキュラが有効になる） */
    float _specular_power;

    float _fog_starts_far_rate;
    /** [r]モデル単位の初期処理が実行済みかどうか(draw時チェック＆変更) */
    bool _is_init_model;

    UINT _num_pass;
    /** [r]ベース変換行（メッシュ系のみ） */
    D3DXMATRIX _matBaseTransformMatrix;
public:
    /**
     * コンストラクタ<BR>
     * @param prm_model_type
     * @param prm_model_id
     */
    Model(const char* prm_model_id);

    char* getName() {
        return _model_id;
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


    inline TextureBlinker* getTexBlinker() {
        return _pTexBlinker;
    }


    virtual void setFogStartFarRate(float prm_fog_starts_far_rate) {
        _fog_starts_far_rate = prm_fog_starts_far_rate;
    }

    virtual void resetFogStartFarRate() {
        _fog_starts_far_rate = CONFIG::DEFAULT_DRAW_FAR_RATE;
    }

    virtual void drawAnyFar() {
        setFogStartFarRate(-1.0);
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
    inline TextureConnection* getDefaultTextureConnection() {
        return _papTextureConnection[_default_texture_index];
    }

    /**
     * モデルを描画 .
     * 下位クラスでモデル描画ロジックを実装して下さい。
     * @param prm_pActor_target 描画するモデルのアクター
     * @param prm_draw_set_num 描画するモデルのセット数
     * @param prm_pPrm 汎用パラメータ
     * @return
     */
    virtual HRESULT draw(FigureActor* prm_pActor_target, int prm_draw_set_num = 1, void* prm_pPrm = nullptr) = 0;

    /**
     * マテリアルのテクスチャを入れ替えて切り替える。 .
     * 予めモデルに複数のテクスチャ(マテリアル)を登録して置く必要がある。<BR>
     * 具体的には X ファイルで予め複数マテリアルエントリ（テクスチャ）を書いておく。<BR>
     * @param prm_texture0 予めモデルに複数のテクスチャの切り替える先のテクスチャID
     *                    （＝TextureManager にエントリされている識別文字列）
     */
    //virtual void swapTopTextureOrder(const char* prm_texture0);


    /**
     * 頂点バッファ情報に共通事前処理を施す。
     * ・Xファイルの法線情報を設定。（※法線情報無い場合は生成して設定）
     * ・法線情報から、接ベクトル（Tangent）及び従法線（Binormal）を計算して設定。
     * ・modelx ファイルの _matBaseTransformMatrix 変換を適用
     * @param prm_paVtxBuffer 更新したい頂点バッファデータ（x,y,z,tu,tv は設定済みの前提）
     * @param prm_size_of_vtx_unit モデルの１頂点データのサイズ
     * @param model_pModel3D
     * @param paNumVertices 頂点連結前の頂点サブセット数の配列
     *        （モデルがサブセット単位で個別基準（位置、回転、拡大）を保持してる場合）
     */
    void prepareVtx3D(void* prm_paVtxBuffer, UINT prm_size_of_vtx_unit,
                    Frm::Model3D* model_pModel3D,
                    uint32_t* paNumVertices);

    void transformPosNomalVtx(void* prm_paVtxBuffer, UINT prm_size_of_vtx_unit, int prm_vtx_num);

    void transformPosVtx(void* prm_paVtxBuffer, UINT prm_size_of_vtx_unit, int prm_vtx_num);

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

    void setMaterial(Frm::Mesh* in_pMeshesFront = nullptr);

    void setDefaultMaterial(D3DMATERIAL9* pMateria);

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


    static std::string getMeshXFilePath(std::string prm_xfile);
    static std::string getPointSpriteXFilePath(std::string prm_xfile);
    static std::string getSpriteXFilePath(std::string prm_sprxfile);

    static std::string getMetaModelInfoPath(std::string prm_modelfile);
    virtual bool obtainMetaModelInfo(ModelManager::ModelXFileFmt* prm_pModelDefineXFileFmt_out);


    /**
     * デストラクタ<BR>
     * deleteするのはModelManagerである<BR>
     */
    virtual ~Model();
};

}
#endif /*GGAF_DX_MODEL_H_*/
