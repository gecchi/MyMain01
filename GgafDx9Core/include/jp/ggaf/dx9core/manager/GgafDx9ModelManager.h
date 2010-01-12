#ifndef GGAFDX9MODELMANAGER_H_
#define GGAFDX9MODELMANAGER_H_
namespace GgafDx9Core {

/**
 * モデルインスタンス管理.
 * 主に、モデルをリストにより保持し、モデルを要求された時に<BR>
 * 生成するか、あるいは生成済を返すかを判断します。<BR>
 * TODO:中核とも言えるクラスで肥大化はしかたないが、分割したなぁ。
 * @version 1.00
 * @since 2009/02/01
 * @author Masatoshi Tsuge
 */
class GgafDx9ModelManager : public GgafCore::GgafResourceManager<GgafDx9Model> {

private:
    /** カスタムテンプレートXファイル読み込み用の IDirectXFile のポインタ */
    IDirectXFile* _pIDirectXFile;
    GgafDx9TextureManager* _pTextureManager;

    /**
     * GgafDx9D3DXMeshModel オブジェクトを生成。 .
     * @param prm_model_name モデル定義の識別名。".x"を追加するとメッシュ定義のXファイル名になる。
     * @param prm_dwOptions オプション（D3DXLoadMeshFromXの引数になる）
     */
    GgafDx9D3DXMeshModel* createD3DXMeshModel(char* prm_model_name, DWORD prm_dwOptions);

    GgafDx9D3DXAniMeshModel* createD3DXAniMeshModel(char* prm_model_name);

    /**
     * GgafDx9D3DXMeshModel オブジェクトを生成。 .
     * @param prm_model_name モデル定義の識別名。".x"を追加するとメッシュ定義のXファイル名になる。
     * @param prm_dwOptions オプション（D3DXLoadMeshFromXの引数になる）
     */
    GgafDx9D3DXMeshModel* createDynaMeshModel(char* prm_model_name);

    /**
     * GgafDx9SpriteModel オブジェクトを生成。 .
     * Xファイルのフォーマットは、カスタムテンプレートXファイルの ggaf_spritemodel_define.x の内容がが使用される<BR>
     * @param prm_model_name モデル定義の識別名。".sprx"を追加するとスプライト定義のXファイル名になる。
     */
    GgafDx9SpriteModel* createSpriteModel(char* prm_model_name);

    GgafDx9SpriteSetModel* createSpriteSetModel(char* prm_model_name);


    /**
     * GgafDx9BoardModel オブジェクトを生成。 .
     * Xファイルのフォーマットは、カスタムテンプレートXファイルの ggaf_spritemodel_define.x の内容がが使用される<BR>
     * @param prm_model_name モデル定義の識別名。".sprx"を追加するとスプライト定義のXファイル名になる。
     */
    GgafDx9BoardModel* createBoardModel(char* prm_model_name);
    GgafDx9BoardSetModel* createBoardSetModel(char* prm_model_name);

    GgafDx9MeshModel* createMeshModel(char* prm_model_name);
    GgafDx9MeshSetModel* createMeshSetModel(char* prm_model_name);

    GgafDx9MorphMeshModel* createMorphMeshModel(char* prm_model_name);

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
     *  "D/MyShip"   --> D3DXMeshModel の モデル。読み込むファイルは "MyShip.x"
     *  "d/MyShip"   --> D3DXMeshModel の モデル。読み込むファイルは "MyShip.x"（D3DXMESH_DYNAMIC オプションだけ異なる）
     *  "A/MyShip"   --> D3DXAniMeshModel の モデル。読み込むファイルは "MyShip.x"
     *  "X/MyShip"   --> MeshModel の モデル。読み込むファイルは "MyShip.x"
     *  "x/MyShip"   --> MeshSetModel の モデル。読み込むファイルは "MyShip.x"。同時描画セット数は8
     *  "x/12/MyShip"--> MeshSetModel の モデル。読み込むファイルは "MyShip.x"。同時描画セット数は12
     *  "M/3/MyShip" --> MorphMeshModel の モデル。読み込むファイルは "MyShip_0.x", "MyShip_1.x", "MyShip_2.x", "MyShip_3.x"。数値部分省略不可。
     *                   プライマリモデルは"MyShip_0.x"、モーフターゲット1～3が"MyShip_1.x", "MyShip_2.x", "MyShip_3.x"
     *  "S/Bomb"     --> SpriteModel の モデル。読み込むファイルは "Bomb.sprx"。
     *  "s/Bomb"     --> SpriteSetModelの モデル。読み込むファイルは "Bomb.sprx"。同時描画セット数は8
     *  "s/16/Bomb"  --> SpriteSetModelの モデル。読み込むファイルは "Bomb.sprx"。同時描画セット数は16
     *  "B/Font"     --> BoardModelの モデル。読み込むファイルは "Font.sprx"。
     *  "b/Font"     --> BoardSetModelの モデル。読み込むファイルは "Font.sprx"。同時描画セット数は8
     *  "C"          --> D3DXMeshModel の モデル。読み込むファイルは "cube.x"
     *  </pre>
     * @param prm_idstr モデル識別ID
     * @return モデルオブジェクト
     */
    GgafDx9Model* processCreateResource(char* prm_idstr);

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
    /**
     * オーバーライド
     */
    GgafCore::GgafResourceConnection<GgafDx9Model>* processCreateConnection(char* prm_idstr, GgafDx9Model* prm_pResource);

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
     * 空間の3点v0 v1 v2 より、直線 v0v1 と v1v2 の成す角(角v1)を求める
     * @param v0
     * @param v1
     * @param v2
     * @return 成す角(ラディアン)
     */
    float getRadv1_v0v1v2(Frm::Vertex& v0, Frm::Vertex& v1, Frm::Vertex& v2);

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
