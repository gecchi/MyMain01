#ifndef GGAFDX9MODELMANAGER_H_
#define GGAFDX9MODELMANAGER_H_
namespace GgafDx9Core {

/**
 * モデルインスタンス管理.
 * 主に、モデルをリストにより保持し、モデルを要求された時に<BR>
 * 生成するか、あるいは生成済を返すかを判断します。<BR>
 */
class GgafDx9ModelManager {

protected:
	/** GgafDx9Modelオブジェクトのリストの先頭のポインタ。終端はNULL */
	static GgafDx9Model* _s_pModel_First;
	/** カスタムテンプレートXファイル読み込み用の IDirectXFile のポインタ */
	static IDirectXFile* _s_pIDirectXFile;

	/**
	 * GgafDx9Modelオブジェクトをリストに追加。 .
	 * @param prm_pSpriteModel_New 追加するGgafDx9Modelオブジェクトのポインタ
	 */
	static void add(GgafDx9Model* prm_pSpriteModel_New);

	/**
	 * GgafDx9Modelオブジェクトをリストから検索。 .
	 * 内部で std::string の比較を見つかるまで行うため、重いです。<BR>
	 * 毎フレーム実行されるような使用は避けるべきです。<BR>
	 * @param	prm_model_name 検索するスプライト定義の識別名。".x"を追加すると定義Xファイル名になる。
	 * @return	所望のGgafDx9Modelオブジェクトのポインタ。リストに存在しなかった場合 NULL
	 */
	static GgafDx9Model* find(std::string prm_model_name);

	/**
	 * GgafDx9MeshModel オブジェクトを生成。 .
	 * @param prm_model_name モデル定義の識別名。".x"を追加するとメッシュ定義のXファイル名になる。
	 * @param prm_dwOptions オプション（D3DXLoadMeshFromXの引数になる）
	 */
	static GgafDx9MeshModel* createMeshModel(std::string prm_model_name, DWORD prm_dwOptions);

	/**
	 * GgafDx9SpriteModel オブジェクトを生成。 .
	 * Xファイルのフォーマットは、カスタムテンプレートXファイルの ggaf_spritemodel_define.x の内容がが使用される<BR>
	 * @param prm_model_name モデル定義の識別名。".x"を追加するとスプライト定義のXファイル名になる。
	 */
	static GgafDx9SpriteModel* createSpriteModel(std::string prm_model_name);

	/**
	 * GgafDx9SquareModel オブジェクトを生成。 .
	 * 1*1*1 立方体のモデル<BR>
	 * @param prm_model_name モデル定義の識別名。
	 */
	static GgafDx9SquareModel* createSquareModel(std::string prm_model_name);

	/**
	 * GgafDx9PlateModel オブジェクトを生成。 .
	 * Xファイルのフォーマットは、カスタムテンプレートXファイルの ggaf_spritemodel_define.x の内容がが使用される<BR>
	 * @param prm_model_name モデル定義の識別名。".x"を追加すると定義のXファイル名になる。
	 */
	static GgafDx9PlateModel* createPlateModel(std::string prm_model_name);

public:

	/**
	 * GgafDx9Modelオブジェクトをリストの各インスタンスの内容を再構築。 .
	 * デバイスロスト後の復帰時に呼び出される<BR>
	 */
	static void restoreAll();

	static void onDeviceLostAll();

	/**
	 * GgafDx9MeshModelオブジェクトを取得。 .
	 * GgafDx9Model オブジェクトリスト（先頭は_s_pModel_First）<BR>
	 * から検索し、ヒットした（生成済みGgafDx9MeshModelがある）場合、 GgafDx9MeshModel にキャストしてそれを返す。<BR>
	 * ヒットしない場合は create を行いインスタンス生成後リストに追加しそれを返す。<BR>
	 * 内部で std::string の比較を見つかるまで行うため、重いです。<BR>
	 * 毎フレーム実行されるような使用は避けるべきです。<BR>
	 * 初期化関数等で１回使用し、ポインタを保持するという使用方法を想定。<BR>
	 * @param prm_model_name スプライト定義の識別名。".x"を追加すると定義Xファイル名になる。
	 * @param prm_dwOptions オプション（D3DXLoadMeshFromXの引数になる）
	 */
	static GgafDx9MeshModel* getMeshModel(std::string prm_model_name, DWORD prm_dwOptions);

	/**
	 * GgafDx9SpriteModelオブジェクトを取得。 .
	 * 生成済み GgafDx9Model オブジェクトリスト（先頭は_s_pModel_First）<BR>
	 * から検索し、ヒットした（生成済みGgafDx9SpriteModelがある）場合、 GgafDx9SpriteModel にキャストしてそれを返す。<BR>
	 * ヒットしない場合は create を行いインスタンス生成後リストに追加しそれを返す。<BR>
	 * 内部で std::string の比較を見つかるまで行うため、重いです。<BR>
	 * 毎フレーム実行されるような使用は避けるべきです。<BR>
	 * 初期化関数等で１回使用し、ポインタを保持するという使用方法を想定。<BR>
	 * @param prm_model_name モデル定義の識別名。（".x"を追加すると定義Xファイル名になる）
	 */
	static GgafDx9SpriteModel* getSpriteModel(std::string prm_model_name);

	/**
	 * GgafDx9SquareModelオブジェクトを取得。 .
	 * 生成済み GgafDx9Model オブジェクトリスト（先頭は_s_pModel_First）<BR>
	 * から検索し、ヒットした（生成済みGgafDx9SquareModelがある）場合、 GgafDx9SquareModel にキャストしてそれを返す。<BR>
	 * ヒットしない場合は create を行いインスタンス生成後リストに追加しそれを返す。<BR>
	 * 内部で std::string の比較を見つかるまで行うため、重いです。<BR>
	 * 毎フレーム実行されるような使用は避けるべきです。<BR>
	 * 初期化関数等で１回使用し、ポインタを保持するという使用方法を想定。<BR>
	 * @param prm_model_name モデル定義の識別名。（".x"を追加すると定義Xファイル名になる）
	 */
	static GgafDx9SquareModel* getSquareModel(std::string prm_model_name);

	/**
	 * GgafDx9PlateModelオブジェクトを取得。<BR>
	 * 生成済み GgafDx9Model オブジェクトリスト（先頭は_s_pModel_First）<BR>
	 * から検索し、ヒットした（生成済みGgafDx9PlateModelがある）場合、 GgafDx9PlateModel にキャストしてそれを返す。<BR>
	 * ヒットしない場合は create を行いインスタンス生成後リストに追加しそれを返す。<BR>
	 * 内部で std::string の比較を見つかるまで行うため、重いです。<BR>
	 * 毎フレーム実行されるような使用は避けるべきです。<BR>
	 * 初期化関数等で１回使用し、ポインタを保持するという使用方法を想定。<BR>
	 * @param prm_model_name モデル定義の識別名。（".x"を追加すると定義Xファイル名になる）
	 */
	static GgafDx9PlateModel* getPlateModel(std::string prm_model_name);

	/**
	 * GgafDx9Modelオブジェクトのリストをすべて delete を行う。<BR>
	 */
	static void clear();

	/**
	 * GgafDx9MeshModel オブジェクトを再構築する。 .
	 * @param prm_pMeshModel 再構築するGgafDx9MeshModel
	 */
	static void restoreMeshModel(GgafDx9MeshModel* prm_pMeshModel);

	/**
	 * GgafDx9SpriteModel オブジェクトを再構築する。 .
	 * @param prm_pSpriteModel 再構築するGgafDx9SpriteModel
	 */
	static void restoreSpriteModel(GgafDx9SpriteModel* prm_pSpriteModel);

	/**
	 * GgafDx9SquareModel オブジェクトを再構築する。 .
	 * @param prm_pSquareModel 再構築するGgafDx9SquareModel
	 */
	static void restoreSquareModel(GgafDx9SquareModel* prm_pSquareModel);


	/**
	 * GgafDx9PlateModel オブジェクトを再構築する。 .
	 * @param prm_pPlateModel 再構築するGgafDx9PlateModel
	 */
	static void restorePlateModel(GgafDx9PlateModel* prm_pPlateModel);

};


}
#endif /*GGAFDX9MODELMANAGER_H_*/
