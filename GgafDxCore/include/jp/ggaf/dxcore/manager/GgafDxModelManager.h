#ifndef GGAFDXCORE_GGAFDXMODELMANAGER_H_
#define GGAFDXCORE_GGAFDXMODELMANAGER_H_
#include "GgafDxCommonHeader.h"

#include "jp/ggaf/core/util/GgafResourceManager.hpp"

#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/util/XFile/framework/Frm_Mesh.h"
#include "jp/ggaf/dxcore/util/XFile/ToolBox/IOModel_X.h"

#define connectToModelTextureManager(X) ((GgafDxCore::GgafDxTextureConnection*)P_GOD->_pModelManager->_pModelTextureManager->connect((X), this))

namespace GgafDxCore {

/**
 * モデルインスタンス管理.
 * 主に、モデルをリストにより保持し、モデルが要求された時に<BR>
 * 生成するか、あるいは生成済を返すかを判断します。<BR>
 * TODO:中核とも言えるクラスで肥大化はしかたないが、分割したなぁ。
 * @version 1.00
 * @since 2009/02/01
 * @author Masatoshi Tsuge
 */
class GgafDxModelManager : public GgafCore::GgafResourceManager<GgafDxModel> {



private:
    GgafDxD3DXMeshModel*         createD3DXMeshModel(const char* prm_model_name, DWORD prm_dwOptions);
    GgafDxD3DXAniMeshModel*      createD3DXAniMeshModel(const char* prm_model_name);
    GgafDxD3DXMeshModel*         createDynaMeshModel(const char* prm_model_name);
    GgafDxSpriteModel*           createSpriteModel(const char* prm_model_name);
    GgafDxSpriteSetModel*        createSpriteSetModel(const char* prm_model_name);
    GgafDxBoardModel*            createBoardModel(const char* prm_model_name);
    GgafDxBoardSetModel*         createBoardSetModel(const char* prm_model_name);
    GgafDxMeshModel*             createMeshModel(const char* prm_model_name);
    GgafDxMeshSetModel*          createMeshSetModel(const char* prm_model_name);
    GgafDxMassMeshModel*         createMassMeshModel(const char* prm_model_name);
    GgafDxCubeMapMeshModel*      createCubeMapMeshModel(const char* prm_model_name);
    GgafDxCubeMapMeshSetModel*   createCubeMapMeshSetModel(const char* prm_model_name);
    GgafDxMorphMeshModel*        createMorphMeshModel(const char* prm_model_name);
    GgafDxCubeMapMorphMeshModel* createCubeMapMorphMeshModel(const char* prm_model_name);
    GgafDxWorldBoundModel*       createWorldBoundModel(const char* prm_model_name);
    GgafDxPointSpriteModel*      createPointSpriteModel(const char* prm_model_name);

public:

    /** カスタムテンプレートXファイル読み込み用の ID3DXFile のポインタ */
    ID3DXFile* _pID3DXFile_sprx;
    ID3DXFile* _pID3DXFile_psprx;
    struct XFILE_SPRITE_FMT {
        float width;
        float height;
        char texture_file[256];
        int row_texture_split;
        int col_texture_split;
    };


    void setMaterial(Frm::Mesh* in_pMeshesFront,
                     int* pOut_material_num,
                     D3DMATERIAL9**                pOut_paMaterial,
                     GgafDxTextureConnection***    pOut_papTextureConnection);
    void setDefaultMaterial(D3DMATERIAL9* out_pD3DMATERIAL9);

    /**
     * 空間の3点v0 v1 v2 より、直線 v0v1 と v1v2 の成す角(角v1)を求める
     * @param v0
     * @param v1
     * @param v2
     * @return 成す角(ラディアン)
     */
    float getRadv1_v0v1v2(Frm::Vertex& v0, Frm::Vertex& v1, Frm::Vertex& v2);

    /**
     * 3D頂点バッファにFrameTransformMatrix変換と法線を設定。
     * @param prm_paVtxBuffer
     * @param prm_size_of_vtx_unit
     * @param model_pModel3D
     * @param paNumVertices 頂点連結前の頂点サブセット数の配列
     *        （モデルがサブセット単位で個別基準（位置、回転、拡大）を保持してる場合）
     */
    void prepareVtx(void* prm_paVtxBuffer, UINT prm_size_of_vtx_unit,
                    Frm::Model3D* model_pModel3D,
                    uint16_t* paNumVertices,
                    GgafDxModel* prm_pModel = nullptr);

    /**
     * ID3DXFileDataのデータポインタから、（Xファイルフォーマット通りに）スプライト情報を取り出す。
     * @param pSpriteFmt_out
     * @param pLockedData ID3DXFileData->lock() のデータポインタ
     * @return
     */
    char* obtainSpriteFmtX(XFILE_SPRITE_FMT* pSpriteFmt_out, char* pLockedData);

    static std::string getMeshFileName(std::string prm_model_name);
    static std::string getSpriteFileName(std::string prm_model_name);
    static std::string getPointSpriteFileName(std::string prm_model_name);

    static void calcTangentAndBinormal(
            D3DXVECTOR3* p0, D3DXVECTOR2* uv0,
            D3DXVECTOR3* p1, D3DXVECTOR2* uv1,
            D3DXVECTOR3* p2, D3DXVECTOR2* uv2,
            D3DXVECTOR3* outTangent, D3DXVECTOR3* outBinormal);

    GgafDxTextureManager* _pModelTextureManager;

public:
    /**
     * コンストラクタ
     * @param prm_manager_name マネージャ名称(リテラル必須)
     */
    GgafDxModelManager(const char* prm_manager_name);

    /**
     * モデル識別IDにより、モデルオブジェクトを生成する .
     * <pre>
     * ＜モデル識別IDの形式＞メモ
     * 『モデルタイプ  + "/" + モデル定義名』となっている。
     *  "D/MyShip"   --> GgafDxD3DXMeshModel のモデル。読み込むファイルは "MyShip.x"
     *  "d/MyShip"   --> GgafDxD3DXMeshModel のモデル。読み込むファイルは "MyShip.x"（D3DXMESH_DYNAMIC オプションだけ異なる）
     *  "A/Hone"     --> GgafDxD3DXAniMeshModel のモデル。読み込むファイルは "Hone.x"
     *  "X/Enemy"    --> GgafDxMeshModel のモデル。読み込むファイルは "Enemy.x"
     *  "x/12/Enemy"- -> GgafDxMeshSetModel のモデル。読み込むファイルは "Enemy.x"。同時描画オブジェクト数は 12 セット
     *  "x/Enemy"    --> GgafDxMeshSetModel のモデル(セット数省略表記)。読み込むファイルは "Enemy.x"。セット数省略時は最大の 15 セット
     *  "t/12/Enemy"- -> GgafDxMassMeshModel のモデル。読み込むファイルは "Enemy.x"。同時描画オブジェクト数は 12 セット
     *  "t/Enemy"    --> GgafDxMassMeshModel のモデル(セット数省略表記)。読み込むファイルは "Enemy.x"。セット数省略時は最大の 15 セット
     *  "M/3/MyShip" --> GgafDxMorphMeshModel のモデル。読み込むファイルは "MyShip_0.x", "MyShip_1.x", "MyShip_2.x", "MyShip_3.x"。数値部分省略不可。
     *                   プライマリモデルは"MyShip_0.x"、モーフターゲット1～3が"MyShip_1.x", "MyShip_2.x", "MyShip_3.x"
     *  "S/Bomb"     --> GgafDxSpriteModel のモデル。読み込むファイルは "Bomb.sprx"。
     *  "s/5/Bomb"   --> GgafDxSpriteSetModel のモデル。読み込むファイルは "Bomb.sprx"。同時描画オブジェクト数は 5 セット
     *  "s/Bomb"     --> GgafDxSpriteSetModel のモデル(セット数省略表記)。読み込むファイルは "Bomb.sprx"。セット数省略時は最大の 18 セット
     *  "B/Font"     --> GgafDxBoardModel のモデル。読み込むファイルは "Font.sprx"。
     *  "b/10/Font"  --> GgafDxBoardSetModel のモデル。読み込むファイルは "Font.sprx"。同時描画オブジェクト数は 10 セット
     *  "b/Font"     --> GgafDxBoardSetModel のモデル。読み込むファイルは "Font.sprx"。セット数省略時は最大の 28 セット
     *  "P/Star"     --> GgafDxPointSpriteModel のモデル。読み込むファイルは "Star.psprx"。同時描画セット数は8
     *  "C"          --> GgafDxD3DXMeshModel のモデル。読み込むファイルは "cube.x"
     *  </pre>
     * @param prm_idstr モデル識別ID
     * @param prm_p 自由パラメータ、現在未使用
     * @return モデルオブジェクト
     */
    GgafDxModel* processCreateResource(const char* prm_idstr, void* prm_pConnector) override;

    /**
     * GgafDxD3DXMeshModel オブジェクトを再構築する。 .
     * @param prm_pD3DXMeshModel 再構築するGgafDxD3DXMeshModel
     */
    void restoreD3DXMeshModel(GgafDxD3DXMeshModel* prm_pD3DXMeshModel);

    void restoreD3DXAniMeshModel(GgafDxD3DXAniMeshModel* prm_pD3DXAniMeshModel);
    void getDrawFrameList(std::list<D3DXFRAME_WORLD*>* pList, D3DXFRAME_WORLD* frame);
    /**
     * GgafDxSpriteModel オブジェクトを再構築する。 .
     * @param prm_pSpriteModel 再構築するGgafDxSpriteModel
     */
//    void restoreSpriteModel(GgafDxSpriteModel* prm_pSpriteModel);

//    void restoreSpriteSetModel(GgafDxSpriteSetModel* prm_pSpriteSetModel);


    /**
     * GgafDxBoardModel オブジェクトを再構築する。 .
     * @param prm_pBoardModel 再構築するGgafDxBoardModel
     */
//    void restoreBoardModel(GgafDxBoardModel* prm_pBoardModel);

//    void restoreBoardSetModel(GgafDxBoardSetModel* prm_pBoardSetModel);

//    void restoreMeshModel(GgafDxMeshModel* prm_pD3DXMeshModel);

    void restoreMeshSetModel(GgafDxMeshSetModel* prm_pD3DXMeshSetModel);

//    void restoreMassMeshModel(GgafDxMassMeshModel* prm_pD3DXMassMeshModel);

    void restoreMorphMeshModel(GgafDxMorphMeshModel* prm_pModel);

//    void restorePointSpriteModel(GgafDxPointSpriteModel* prm_pPointSpriteModel);

    /**
     * オーバーライド
     */
    GgafCore::GgafResourceConnection<GgafDxModel>* processCreateConnection(const char* prm_idstr, GgafDxModel* prm_pResource) override;

    /**
     * モデルオブジェクトリストの各インスタンスの内容を再構築。 .
     * デバイスロスト後の復帰時に呼び出される<BR>
     */
    void restoreAll();

    void onDeviceLostAll();

    void releaseAll();


    /** 前回描画Model */
    static GgafDxModel* _pModelLastDraw;

    /**
     * モデルマネージャーが管理するモデルリストの先頭を取得
     * @return 先頭のモデル
     */
    GgafDxModelConnection* getFirstConnection() const {
        return (GgafDxModelConnection*)_pConn_first;
    }

    virtual ~GgafDxModelManager();
};

}
#endif /*GGAFDXCORE_GGAFDXMODELMANAGER_H_*/
