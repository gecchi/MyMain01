#ifndef GGAF_DX_MODELMANAGER_H_
#define GGAF_DX_MODELMANAGER_H_
#include "GgafDxCommonHeader.h"

#include "jp/ggaf/core/util/ResourceManager.hpp"

#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/dx/util/XFile/framework/Frm_Mesh.h"
#include "jp/ggaf/dx/util/XFile/ToolBox/IOModel_X.h"

#define connectToModelTextureManager(X) ((GgafDx::TextureConnection*)pGOD->_pModelManager->_pModelTextureManager->connect((X), this))

#define TYPE_D3DXMESH_MODEL               'D'
#define TYPE_DYNAD3DXMESH_MODEL           'd'
#define TYPE_D3DXANIMESH_MODEL            'A'
#define TYPE_MESH_MODEL                   'X'
#define TYPE_MESHSET_MODEL                'x'
#define TYPE_MASSMESH_MODEL               't'
#define TYPE_CUBEMAPMESH_MODEL            'G'
#define TYPE_CUBEMAPMESHSET_MODEL         'g'
#define TYPE_MORPHMESH_MODEL              'M'
#define TYPE_MASSMORPHMESH_MODEL          'm'
#define TYPE_CUBEMAPMORPHMESH_MODEL       'H'
#define TYPE_WORLDBOUND_MODEL             'W'
#define TYPE_ACTOR_MODEL                  'S'
#define TYPE_SPRITESET_MODEL              's'
#define TYPE_MASSACTOR_MODEL              'z'
#define TYPE_BOARD_MODEL                  'B'
#define TYPE_BOARDSET_MODEL               'b'
#define TYPE_MASSBOARD_MODEL              'w'
#define TYPE_CUBE_MODEL                   'C'
#define TYPE_POINTSPRITE_MODEL            'P'
#define TYPE_MASSPOINTACTOR_MODEL         'p'
#define TYPE_POINTSPRITESET_MODEL         'o'
#define TYPE_FRAMEDBOARD_MODEL            'E'
#define TYPE_REGULARPOLYGONACTOR_MODEL    'R'
#define TYPE_REGULARPOLYGONBOARD_MODEL    'r'
#define TYPE_BONEANIMESH_MODEL            '1'
#define TYPE_SKINANIMESH_MODEL            '2'


namespace GgafDx {

/**
 * モデルインスタンス管理.
 * 主に、モデルをリストにより保持し、モデルが要求された時に<BR>
 * 生成するか、あるいは生成済を返すかを判断します。<BR>
 * TODO:中核とも言えるクラスで肥大化はしかたないが、分割したなぁ。
 * @version 1.00
 * @since 2009/02/01
 * @author Masatoshi Tsuge
 */
class ModelManager : public GgafCore::ResourceManager<Model> {

private:
    D3DXMeshModel*     createD3DXMeshModel(const char* prm_model_id, DWORD prm_dwOptions);

protected:
    template <typename T> T* createModel(const char* prm_model_id);

public:
    struct MeshXFileFmt {
        DWORD XFileNum;
        std::string* XFileNames;
        DWORD DrawSetNum; //0の場合は最大
        D3DXMATRIX BaseTransformMatrix;
        MeshXFileFmt() {
            XFileNum = 1;
            XFileNames = nullptr;
            DrawSetNum = 1;
        }
        ~MeshXFileFmt() {
            GGAF_DELETEARR_NULLABLE(XFileNames);
        }
    };

    struct SpriteXFileFmt {
        FLOAT Width;
        FLOAT Height;
        char TextureFile[256];
        DWORD TextureSplitRows;
        DWORD TextureSplitCols;
        DWORD DrawSetNum;
    };

    struct FramedSpriteXFileFmt {
        FLOAT Width;
        FLOAT Height;
        char TextureFile[256];
        DWORD TextureSplitRows;
        DWORD TextureSplitCols;

        FLOAT FrameWidth;
        FLOAT FrameHeight;
        char FrameTextureFile[256];
        DWORD FrameTextureSplitRows;
        DWORD FrameTextureSplitCols;
    };

    struct RegPolySpriteXFileFmt {
        FLOAT Width;
        FLOAT Height;
        char TextureFile[256];
        DWORD TextureSplitRows;
        DWORD TextureSplitCols;

        DWORD  FanNum;
        DWORD  IsCW; //1:時計回り / 0:反時計回り
        D3DXMATRIX BaseTransformMatrix;
    };




    class PointSpriteXFileFmt {
    public:
        FLOAT SquareSize;
        char TextureFile[256];
        DWORD TextureSplitRowCol;
        DWORD VerticesNum;
        D3DVECTOR* paD3DVECTOR_Vertices;
        D3DCOLORVALUE* paD3DVECTOR_VertexColors;
        DWORD* paInt_InitUvPtnNo;
        FLOAT* paFLOAT_InitScale;
        DWORD DrawSetNum;
        D3DXMATRIX BaseTransformMatrix;
        PointSpriteXFileFmt() {
            SquareSize = 1;
            TextureSplitRowCol = 1;
            VerticesNum = 1;
            paD3DVECTOR_Vertices = nullptr;
            paD3DVECTOR_VertexColors = nullptr;
            paInt_InitUvPtnNo = nullptr;
            paFLOAT_InitScale = nullptr;
            DrawSetNum = 1;
        }
        ~PointSpriteXFileFmt() {
            GGAF_DELETE_NULLABLE(paD3DVECTOR_Vertices);
            GGAF_DELETE_NULLABLE(paD3DVECTOR_VertexColors);
            GGAF_DELETE_NULLABLE(paInt_InitUvPtnNo);
            GGAF_DELETE_NULLABLE(paFLOAT_InitScale);
        }
    };

    TextureManager* _pModelTextureManager;
    /** Xファイル読み込み用の ID3DXFile のポインタ（meshx モデル定義読み込んだあと） */
    ID3DXFile* _pID3DXFile_meshx;
    ID3DXFile* _pID3DXFile_sprx;
    ID3DXFile* _pID3DXFile_fsprx;
    ID3DXFile* _pID3DXFile_rsprx;
    ID3DXFile* _pID3DXFile_psprx;
    static std::string getXFilePath(std::string prm_xfile);
//    static std::string getXFilePath2(std::string prm_model_id);
    static std::string getModelDefineFilePath(std::string prm_model_name);
    void obtainMeshModelInfo(MeshXFileFmt* prm_pMeshXFileFmt_out, std::string prm_meshx_filepath);
    void obtainSpriteModelInfo(SpriteXFileFmt* prm_pSpriteFmt_out, std::string prm_sprx_filepath);
    void obtainFramedSpriteModelInfo(FramedSpriteXFileFmt* prm_pFramedSpriteFmt_out, std::string prm_fsprx_filepath);
    void obtainRegPolySpriteModelInfo(RegPolySpriteXFileFmt* prm_pRegPolySpriteFmt_out, std::string prm_rsprx_filepath);
    void obtainPointSpriteModelInfo(PointSpriteXFileFmt* prm_pPointSpriteFmt_out, std::string prm_psprx_filepath);
public:
    /**
     * コンストラクタ
     * @param prm_manager_name マネージャ名称(リテラル必須)
     */
    ModelManager(const char* prm_manager_name);

    /**
     * モデル識別IDにより、モデルオブジェクトを生成する .
     * <pre>
     * ＜モデル識別IDの形式＞メモ
     * 『モデルタイプ  + "," + モデル定義名』となっている。
     *  "D,MyShip"   --> D3DXMeshModel のモデル。読み込むファイルは "MyShip.x"
     *  "d,MyShip"   --> D3DXMeshModel のモデル。読み込むファイルは "MyShip.x"（D3DXMESH_DYNAMIC オプションだけ異なる）
     *  "A,Hone"     --> D3DXAniMeshModel のモデル。読み込むファイルは "Hone.x"
     *  "X,Enemy"    --> MeshModel のモデル。読み込むファイルは "Enemy.x"
     *  "x,12,Enemy"- -> MeshSetModel のモデル。読み込むファイルは "Enemy.x"。同時描画オブジェクト数は 12 セット
     *  "x,Enemy"    --> MeshSetModel のモデル(セット数省略表記)。読み込むファイルは "Enemy.x"。セット数省略時は最大の 15 セット
     *  "t,12,Enemy"- -> MassMeshModel のモデル。読み込むファイルは "Enemy.x"。同時描画オブジェクト数は 12 セット
     *  "t,Enemy"    --> MassMeshModel のモデル(セット数省略表記)。読み込むファイルは "Enemy.x"。セット数省略時は最大の 15 セット
     *  "M,MyShip_3" --> MorphMeshModel のモデル。読み込むファイルは "MyShip_0.x", "MyShip_1.x", "MyShip_2.x", "MyShip_3.x"。数値部分省略不可。
     *                   プライマリモデルは"MyShip_0.x"、モーフターゲット1～3が"MyShip_1.x", "MyShip_2.x", "MyShip_3.x"
     *  "S,Bomb"     --> SpriteModel のモデル。読み込むファイルは "Bomb.sprx"。
     *  "s,5,Bomb"   --> SpriteSetModel のモデル。読み込むファイルは "Bomb.sprx"。同時描画オブジェクト数は 5 セット
     *  "s,Bomb"     --> SpriteSetModel のモデル(セット数省略表記)。読み込むファイルは "Bomb.sprx"。セット数省略時は最大の 18 セット
     *  "B,Font"     --> BoardModel のモデル。読み込むファイルは "Font.sprx"。
     *  "b,10,Font"  --> BoardSetModel のモデル。読み込むファイルは "Font.sprx"。同時描画オブジェクト数は 10 セット
     *  "b,Font"     --> BoardSetModel のモデル。読み込むファイルは "Font.sprx"。セット数省略時は最大の 28 セット
     *  "P,Star"     --> PointSpriteModel のモデル。読み込むファイルは "Star.psprx"。同時描画セット数は8
     *  "C"          --> D3DXMeshModel のモデル。読み込むファイルは "cube.x"
     *  </pre>
     * @param prm_idstr モデル識別ID
     * @param prm_p 自由パラメータ、現在未使用
     * @return モデルオブジェクト
     */
    Model* processCreateResource(const char* prm_idstr, void* prm_pConnector) override;

    /**
     * オーバーライド
     */
    GgafCore::ResourceConnection<Model>* processCreateConnection(const char* prm_idstr, Model* prm_pResource) override;

    /**
     * モデルオブジェクトリストの各インスタンスの内容を再構築。 .
     * デバイスロスト後の復帰時に呼び出される<BR>
     */
    void restoreAll();

    void onDeviceLostAll();

    void releaseAll();


    /** 前回描画Model */
    static Model* _pModelLastDraw;

    /**
     * モデルマネージャーが管理するモデルリストの先頭を取得
     * @return 先頭のモデル
     */
    ModelConnection* getFirstConnection() const {
        return (ModelConnection*)_pConn_first;
    }

    virtual ~ModelManager();
};


}
#endif /*GGAF_DX_MODELMANAGER_H_*/
