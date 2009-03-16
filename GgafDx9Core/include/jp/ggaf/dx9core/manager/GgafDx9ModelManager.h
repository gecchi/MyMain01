#ifndef GGAFDX9MODELMANAGER_H_
#define GGAFDX9MODELMANAGER_H_
namespace GgafDx9Core {

/**
 * モデルインスタンス管理.
 * 主に、モデルをリストにより保持し、モデルを要求された時に<BR>
 * 生成するか、あるいは生成済を返すかを判断します。<BR>
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

    /**
     * GgafDx9D3DXMeshModel オブジェクトを生成。 .
     * @param prm_model_name モデル定義の識別名。".x"を追加するとメッシュ定義のXファイル名になる。
     * @param prm_dwOptions オプション（D3DXLoadMeshFromXの引数になる）
     */
    GgafDx9D3DXMeshModel* createDynaMeshModel(char* prm_model_name);

    /**
     * GgafDx9SpriteModel オブジェクトを生成。 .
     * Xファイルのフォーマットは、カスタムテンプレートXファイルの ggaf_spritemodel_define.x の内容がが使用される<BR>
     * @param prm_model_name モデル定義の識別名。".x"を追加するとスプライト定義のXファイル名になる。
     */
    GgafDx9SpriteModel* createSpriteModel(char* prm_model_name);

    /**
     * GgafDx9SquareModel オブジェクトを生成。 .
     * 1*1*1 立方体のモデル<BR>
     * @param prm_model_name モデル定義の識別名。
     */
    GgafDx9SquareModel* createSquareModel(char* prm_model_name);

    /**
     * GgafDx9PlateModel オブジェクトを生成。 .
     * Xファイルのフォーマットは、カスタムテンプレートXファイルの ggaf_spritemodel_define.x の内容がが使用される<BR>
     * @param prm_model_name モデル定義の識別名。".x"を追加すると定義のXファイル名になる。
     */
    GgafDx9BoardModel* createBoardModel(char* prm_model_name);

    GgafDx9MeshModel* createMeshModel(char* prm_model_name);


public:

    /**
     * コンストラクタ
     * @param prm_manager_name マネージャ名称(リテラル必須)
     */
    GgafDx9ModelManager(const char* prm_manager_name);

    /**
     * オーバーライド
     */
    GgafDx9Model* processCreateResource(char* prm_idstr);

    /**
     * GgafDx9D3DXMeshModel オブジェクトを再構築する。 .
     * @param prm_pD3DXMeshModel 再構築するGgafDx9D3DXMeshModel
     */
    void restoreD3DXMeshModel(GgafDx9D3DXMeshModel* prm_pD3DXMeshModel);

    /**
     * GgafDx9SpriteModel オブジェクトを再構築する。 .
     * @param prm_pSpriteModel 再構築するGgafDx9SpriteModel
     */
    void restoreSpriteModel(GgafDx9SpriteModel* prm_pSpriteModel);

    /**
     * GgafDx9SquareModel オブジェクトを再構築する。 .
     * @param prm_pSquareModel 再構築するGgafDx9SquareModel
     */
    void restoreSquareModel(GgafDx9SquareModel* prm_pSquareModel);

    /**
     * GgafDx9PlateModel オブジェクトを再構築する。 .
     * @param prm_pPlateModel 再構築するGgafDx9PlateModel
     */

    void restoreBoardModel(GgafDx9BoardModel* prm_pBoardModel);

    void restoreMeshModel(GgafDx9MeshModel* prm_pD3DXMeshModel);


    /**
     * オーバーライド
     */
    GgafCore::GgafResourceConnection<GgafDx9Model>* processCreateConnection(char* prm_idstr, GgafDx9Model* prm_pResource);

    /**
     * GgafDx9Modelオブジェクトをリストの各インスタンスの内容を再構築。 .
     * デバイスロスト後の復帰時に呼び出される<BR>
     */
    void restoreAll();

    void onDeviceLostAll();

    void releaseAll();

//    /**
//     * GgafDx9D3DXMeshModelオブジェクトを取得。 .
//     * GgafDx9Model オブジェクトリスト（先頭は_pModel_First）<BR>
//     * から検索し、ヒットした（生成済みGgafDx9D3DXMeshModelがある）場合、 GgafDx9D3DXMeshModel にキャストしてそれを返す。<BR>
//     * ヒットしない場合は create を行いインスタンス生成後リストに追加しそれを返す。<BR>
//     * 内部で std::string の比較を見つかるまで行うため、重いです。<BR>
//     * 毎フレーム実行されるような使用は避けるべきです。<BR>
//     * 初期化関数等で１回使用し、ポインタを保持するという使用方法を想定。<BR>
//     * @param prm_model_name スプライト定義の識別名。".x"を追加すると定義Xファイル名になる。
//     * @param prm_dwOptions オプション（D3DXLoadMeshFromXの引数になる）
//     */
//    GgafDx9D3DXMeshModel* restoreD3DXMeshModel(char* prm_model_name, DWORD prm_dwOptions);
//
//    /**
//     * GgafDx9SpriteModelオブジェクトを取得。 .
//     * 生成済み GgafDx9Model オブジェクトリスト（先頭は_pModel_First）<BR>
//     * から検索し、ヒットした（生成済みGgafDx9SpriteModelがある）場合、 GgafDx9SpriteModel にキャストしてそれを返す。<BR>
//     * ヒットしない場合は create を行いインスタンス生成後リストに追加しそれを返す。<BR>
//     * 内部で std::string の比較を見つかるまで行うため、重いです。<BR>
//     * 毎フレーム実行されるような使用は避けるべきです。<BR>
//     * 初期化関数等で１回使用し、ポインタを保持するという使用方法を想定。<BR>
//     * @param prm_model_name モデル定義の識別名。（".x"を追加すると定義Xファイル名になる）
//     */
//    GgafDx9SpriteModel* restoreSpriteModel(char* prm_model_name);
//
//    /**
//     * GgafDx9SquareModelオブジェクトを取得。 .
//     * 生成済み GgafDx9Model オブジェクトリスト（先頭は_pModel_First）<BR>
//     * から検索し、ヒットした（生成済みGgafDx9SquareModelがある）場合、 GgafDx9SquareModel にキャストしてそれを返す。<BR>
//     * ヒットしない場合は create を行いインスタンス生成後リストに追加しそれを返す。<BR>
//     * 内部で std::string の比較を見つかるまで行うため、重いです。<BR>
//     * 毎フレーム実行されるような使用は避けるべきです。<BR>
//     * 初期化関数等で１回使用し、ポインタを保持するという使用方法を想定。<BR>
//     * @param prm_model_name モデル定義の識別名。（".x"を追加すると定義Xファイル名になる）
//     */
//    GgafDx9SquareModel* restoreSquareModel(char* prm_model_name);


    /** 現在モデルID */
    static int _id_max;

    /** モデルID取得 */
    static int getNextId() {
        _id_max++;
        return _id_max;
    }
    /** 前回描画ModelのId */
    static int _id_lastdraw;


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
