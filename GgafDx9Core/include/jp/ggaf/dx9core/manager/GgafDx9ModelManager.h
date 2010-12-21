#ifndef GGAFDX9MODELMANAGER_H_
#define GGAFDX9MODELMANAGER_H_


namespace GgafDx9Core {

/**
 * モデルインスタンス管理.
 * 主に、モデルをリストにより保持し、モデルが要求された時に<BR>
 * 生成するか、あるいは生成済を返すかを判断します。<BR>
 * TODO:中核とも言えるクラスで肥大化はしかたないが、分割したなぁ。
 * @version 1.00
 * @since 2009/02/01
 * @author Masatoshi Tsuge
 */
class GgafDx9ModelManager : public GgafCore::GgafResourceManager<GgafDx9Model> {

private:
    /** カスタムテンプレートXファイル読み込み用の IDirectXFile のポインタ */
    IDirectXFile* _pIDirectXFile_sprx;
    IDirectXFile* _pIDirectXFile_psprx;
    GgafDx9TextureManager* _pTextureManager;

    GgafDx9D3DXMeshModel*    createD3DXMeshModel(char* prm_model_name, DWORD prm_dwOptions);
    GgafDx9D3DXAniMeshModel* createD3DXAniMeshModel(char* prm_model_name);
    GgafDx9D3DXMeshModel*    createDynaMeshModel(char* prm_model_name);
    GgafDx9SpriteModel*      createSpriteModel(char* prm_model_name);
    GgafDx9SpriteSetModel*   createSpriteSetModel(char* prm_model_name);
    GgafDx9BoardModel*       createBoardModel(char* prm_model_name);
    GgafDx9BoardSetModel*    createBoardSetModel(char* prm_model_name);
    GgafDx9MeshModel*        createMeshModel(char* prm_model_name);
    GgafDx9MeshSetModel*     createMeshSetModel(char* prm_model_name);
    GgafDx9CubeMapMeshModel* createCubeMapMeshModel(char* prm_model_name);
    GgafDx9MorphMeshModel*   createMorphMeshModel(char* prm_model_name);
    GgafDx9PointSpriteModel* createPointSpriteModel(char* prm_model_name);

    /**
     * 空間の3点v0 v1 v2 より、直線 v0v1 と v1v2 の成す角(角v1)を求める
     * @param v0
     * @param v1
     * @param v2
     * @return 成す角(ラディアン)
     */
    float getRadv1_v0v1v2(Frm::Vertex& v0, Frm::Vertex& v1, Frm::Vertex& v2);
public:

    /**
     * コンストラクタ
     * @param prm_manager_name マネージャ名称(リテラル必須)
     */
    GgafDx9ModelManager(const char* prm_manager_name);

    /**
     * モデル識別IDにより、モデルオブジェクトを生成する .
     * <pre>
     * ＜モデル識別IDの形式＞メモ
     * 『モデルタイプ  + "/" + モデル定義名』となっている。
     *  "D/MyShip"   --> GgafDx9D3DXMeshModel のモデル。読み込むファイルは "MyShip.x"
     *  "d/MyShip"   --> GgafDx9D3DXMeshModel のモデル。読み込むファイルは "MyShip.x"（D3DXMESH_DYNAMIC オプションだけ異なる）
     *  "A/Hone"     --> GgafDx9D3DXAniMeshModel のモデル。読み込むファイルは "Hone.x"
     *  "X/Enemy"    --> GgafDx9MeshModel のモデル。読み込むファイルは "Enemy.x"
     *  "x/12/Enemy"- -> GgafDx9MeshSetModel のモデル。読み込むファイルは "Enemy.x"。同時描画オブジェクト数は 12 セット
     *  "x/Enemy"    --> GgafDx9MeshSetModel のモデル(セット数省略表記)。読み込むファイルは "Enemy.x"。セット数省略時は最大の 15 セット
     *  "M/3/MyShip" --> GgafDx9MorphMeshModel のモデル。読み込むファイルは "MyShip_0.x", "MyShip_1.x", "MyShip_2.x", "MyShip_3.x"。数値部分省略不可。
     *                   プライマリモデルは"MyShip_0.x"、モーフターゲット1～3が"MyShip_1.x", "MyShip_2.x", "MyShip_3.x"
     *  "S/Bomb"     --> GgafDx9SpriteModel のモデル。読み込むファイルは "Bomb.sprx"。
     *  "s/5/Bomb"   --> GgafDx9SpriteSetModel のモデル。読み込むファイルは "Bomb.sprx"。同時描画オブジェクト数は 5 セット
     *  "s/Bomb"     --> GgafDx9SpriteSetModel のモデル(セット数省略表記)。読み込むファイルは "Bomb.sprx"。セット数省略時は最大の 18 セット
     *  "B/Font"     --> GgafDx9BoardModel のモデル。読み込むファイルは "Font.sprx"。
     *  "b/10/Font"  --> GgafDx9BoardSetModel のモデル。読み込むファイルは "Font.sprx"。同時描画オブジェクト数は 10 セット
     *  "b/Font"     --> GgafDx9BoardSetModel のモデル。読み込むファイルは "Font.sprx"。セット数省略時は最大の 28 セット
     *  "P/Star"     --> GgafDx9PointSpriteModel のモデル。読み込むファイルは "Star.psprx"。同時描画セット数は8
     *  "C"          --> GgafDx9D3DXMeshModel のモデル。読み込むファイルは "cube.x"
     *  </pre>
     * @param prm_idstr モデル識別ID
     * @return モデルオブジェクト
     */
    GgafDx9Model* processCreateResource(char* prm_idstr, void* prm_p) override;

    /**
     * GgafDx9D3DXMeshModel オブジェクトを再構築する。 .
     * @param prm_pD3DXMeshModel 再構築するGgafDx9D3DXMeshModel
     */
    void restoreD3DXMeshModel(GgafDx9D3DXMeshModel* prm_pD3DXMeshModel);

    void restoreD3DXAniMeshModel(GgafDx9D3DXAniMeshModel* prm_pD3DXAniMeshModel);

    /**
     * GgafDx9SpriteModel オブジェクトを再構築する。 .
     * @param prm_pSpriteModel 再構築するGgafDx9SpriteModel
     */
    void restoreSpriteModel(GgafDx9SpriteModel* prm_pSpriteModel);

    void restoreSpriteSetModel(GgafDx9SpriteSetModel* prm_pSpriteSetModel);


    /**
     * GgafDx9BoardModel オブジェクトを再構築する。 .
     * @param prm_pBoardModel 再構築するGgafDx9BoardModel
     */
    void restoreBoardModel(GgafDx9BoardModel* prm_pBoardModel);

    void restoreBoardSetModel(GgafDx9BoardSetModel* prm_pBoardSetModel);

    void restoreMeshModel(GgafDx9MeshModel* prm_pD3DXMeshModel);

    void restoreMeshSetModel(GgafDx9MeshSetModel* prm_pD3DXMeshSetModel);

    void restoreMorphMeshModel(GgafDx9MorphMeshModel* prm_pModel);

    void restorePointSpriteModel(GgafDx9PointSpriteModel* prm_pPointSpriteModel);

    /**
     * オーバーライド
     */
    GgafCore::GgafResourceConnection<GgafDx9Model>* processCreateConnection(char* prm_idstr, GgafDx9Model* prm_pResource) override;

    /**
     * モデルオブジェクトリストの各インスタンスの内容を再構築。 .
     * デバイスロスト後の復帰時に呼び出される<BR>
     */
    void restoreAll();

    void onDeviceLostAll();

    void releaseAll();


    /** 現在モデルID */
    static int _id_max;

    /** モデルID取得 */
    static int getNextId() {
        _id_max++;
        return _id_max;
    }
    /** 前回描画Model */
    static GgafDx9Model* _pModelLastDraw;

    /**
     * モデルマネージャーが管理するモデルリストの先頭を取得
     * @return 先頭のモデル
     */
    GgafDx9ModelConnection* getFirstConnection() {
        return (GgafDx9ModelConnection*)_pFirstConnection;
    }

    virtual ~GgafDx9ModelManager();


    //
    //	/**
    //	 * GgafDx9Modelオブジェクトのリストをすべて delete を行う。<BR>
    //	 */
    //	static void release();
    //
};

}
#endif /*GGAFDX9MODELMANAGER_H_*/
