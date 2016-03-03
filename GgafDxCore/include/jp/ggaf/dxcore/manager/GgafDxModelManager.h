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
    GgafDxMassSpriteModel*       createMassSpriteModel(const char* prm_model_name);
    GgafDxBoardModel*            createBoardModel(const char* prm_model_name);
    GgafDxBoardSetModel*         createBoardSetModel(const char* prm_model_name);
    GgafDxMassBoardModel*        createMassBoardModel(const char* prm_model_name);
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

    struct SpriteXFileFmt {
        float width;
        float height;
        char texture_file[256];
        int row_texture_split;
        int col_texture_split;
    };

    class PointSpriteXFileFmt {
    public:
        float SquareSize;
        char TextureFile[256];
        int TextureSplitRowCol;
        int VerticesNum;
        D3DVECTOR* paD3DVECTOR_Vertices;
        D3DCOLORVALUE* paD3DVECTOR_VertexColors;
        int* paInt_InitUvPtnNo;
        float* paFLOAT_InitScale;
        PointSpriteXFileFmt() {
            paD3DVECTOR_Vertices = nullptr;
            paD3DVECTOR_VertexColors = nullptr;
            paInt_InitUvPtnNo = nullptr;
            paFLOAT_InitScale = nullptr;
        }
        ~PointSpriteXFileFmt() {
            GGAF_DELETE_NULLABLE(paD3DVECTOR_Vertices);
            GGAF_DELETE_NULLABLE(paD3DVECTOR_VertexColors);
            GGAF_DELETE_NULLABLE(paInt_InitUvPtnNo);
            GGAF_DELETE_NULLABLE(paFLOAT_InitScale);
        }
    };

    static GgafDxTextureManager* _pModelTextureManager;
    /** カスタムテンプレートXファイル読み込み用の ID3DXFile のポインタ */
    static ID3DXFile* _pID3DXFile_sprx;
    static ID3DXFile* _pID3DXFile_psprx;
    static std::string getMeshFileName(std::string prm_model_name);
    static std::string getSpriteFileName(std::string prm_model_name);
    static std::string getPointSpriteFileName(std::string prm_model_name);

    static void obtainSpriteInfo(SpriteXFileFmt* pSpriteFmt_out, std::string prm_sprite_x_filename);
    static void obtainPointSpriteInfo(PointSpriteXFileFmt* pPointSpriteFmt_out, std::string prm_point_sprite_x_filename);
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
