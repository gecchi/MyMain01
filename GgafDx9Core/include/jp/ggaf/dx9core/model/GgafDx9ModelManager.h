#ifndef GGAFDX9MODELMANAGER_H_
#define GGAFDX9MODELMANAGER_H_

class GgafDx9ModelManager {

protected:
	/** GgafDx9Modelオブジェクトのリストの先頭のポインタ。終端はNULL */
	static GgafDx9Model* _pModel_First;
	/** カスタムテンプレートXファイル読み込み用の IDirectXFile のポインタ */
	static IDirectXFile* _pIDirectXFile;

public:
	/**
	 * GgafDx9Modelオブジェクトをリストに追加。<BR>
	 * @param 追加するGgafDx9Modelオブジェクトのポインタ
	 */
	static void add(GgafDx9Model* prm_pSpriteModel_New);

	/**
	 * GgafDx9Modelオブジェクトをリストから検索。<BR>
	 * @param	検索するスプライト定義の識別名。".x"を追加すると定義Xファイル名になる。
	 * @return	所望のGgafDx9Modelオブジェクトのポインタ。リストに存在しなかった場合 NULL
	 */
	static GgafDx9Model* find(string prm_model_name);

	/**
	 * GgafDx9Modelオブジェクトをリストの各インスタンスの内容を再構築。<BR>
	 * デバイスロスト後の復帰時に呼び出される<BR>
	 */
	static void restoreAll();
	static void onDeviceLostAll();

	/**
	 * GgafDx9MeshModelオブジェクトを取得。<BR>
	 * GgafDx9Model オブジェクトリスト（先頭は_pModel_First）<BR>
	 * から検索し、ヒットした（生成済みGgafDx9MeshModelがある）場合、 GgafDx9MeshModel にキャストしてそれを返す。<BR>
	 * ヒットしない場合は create を行いインスタンス生成後リストに追加しそれを返す。<BR>
	 * @param スプライト定義の識別名。".x"を追加すると定義Xファイル名になる。
	 */
	static GgafDx9MeshModel* getMeshModel(string prm_model_name);


	/**
	 * GgafDx9SpriteModelオブジェクトを取得。<BR>
	 * 生成済み GgafDx9Model オブジェクトリスト（先頭は_pModel_First）<BR>
	 * から検索し、ヒットした（生成済みGgafDx9SpriteModelがある）場合、 GgafDx9SpriteModel にキャストしてそれを返す。<BR>
	 * ヒットしない場合は create を行いインスタンス生成後リストに追加しそれを返す。<BR>
	 * @param prm_model_name モデル定義の識別名。（".x"を追加すると定義Xファイル名になる）
	 */
	static GgafDx9SpriteModel* getSpriteModel(string prm_model_name);

	/**
	 * GgafDx9SquareModelオブジェクトを取得。<BR>
	 * 生成済み GgafDx9Model オブジェクトリスト（先頭は_pModel_First）<BR>
	 * から検索し、ヒットした（生成済みGgafDx9SquareModelがある）場合、 GgafDx9SquareModel にキャストしてそれを返す。<BR>
	 * ヒットしない場合は create を行いインスタンス生成後リストに追加しそれを返す。<BR>
	 * @param prm_model_name モデル定義の識別名。（".x"を追加すると定義Xファイル名になる）
	 */
	static GgafDx9SquareModel* getSquareModel(string prm_model_name);

	/**
	 * GgafDx9PlateModelオブジェクトを取得。<BR>
	 * 生成済み GgafDx9Model オブジェクトリスト（先頭は_pModel_First）<BR>
	 * から検索し、ヒットした（生成済みGgafDx9PlateModelがある）場合、 GgafDx9PlateModel にキャストしてそれを返す。<BR>
	 * ヒットしない場合は create を行いインスタンス生成後リストに追加しそれを返す。<BR>
	 * @param prm_model_name モデル定義の識別名。（".x"を追加すると定義Xファイル名になる）
	 */
	static GgafDx9PlateModel* getPlateModel(string prm_model_name);

	/**
	 * GgafDx9Modelオブジェクトのリストをすべて delete を行う。<BR>
	 */
	static void clear();


	/**
	 * GgafDx9MeshModel オブジェクトを生成。<BR>
	 * @param モデル定義の識別名。".x"を追加するとメッシュ定義のXファイル名になる。
	 */
	static GgafDx9MeshModel* createMeshModel(string prm_model_name);

	/**
	 * GgafDx9MeshModel オブジェクトを再構築する。<BR>
	 * @param 再構築するGgafDx9MeshModel
	 */
	static void restoreMeshModel(GgafDx9MeshModel* prm_pMeshModel);

	/**
	 * GgafDx9SpriteModel オブジェクトを生成。<BR>
	 * Xファイルのフォーマットは、カスタムテンプレートXファイルの ggaf_spritemodel_define.x の内容がが使用される<BR>
	 * @param モデル定義の識別名。".x"を追加するとスプライト定義のXファイル名になる。
	 */
	static GgafDx9SpriteModel* createSpriteModel(string prm_model_name);

	/**
	 * GgafDx9SpriteModel オブジェクトを再構築する。<BR>
	 * @param 再構築するGgafDx9SpriteModel
	 */
	static void restoreSpriteModel(GgafDx9SpriteModel* prm_pSpriteModel);

	/**
	 * GgafDx9SquareModel オブジェクトを生成。<BR>
	 * 1*1*1 立方体のモデル<BR>
	 * @param モデル定義の識別名。
	 */
	static GgafDx9SquareModel* createSquareModel(string prm_model_name);

	/**
	 * GgafDx9SquareModel オブジェクトを再構築する。<BR>
	 * @param 再構築するGgafDx9SquareModel
	 */
	static void restoreSquareModel(GgafDx9SquareModel* prm_pSquareModel);

	/**
	 * GgafDx9PlateModel オブジェクトを生成。<BR>
	 * Xファイルのフォーマットは、カスタムテンプレートXファイルの ggaf_spritemodel_define.x の内容がが使用される<BR>
	 * @param モデル定義の識別名。".x"を追加すると定義のXファイル名になる。
	 */
	static GgafDx9PlateModel* createPlateModel(string prm_model_name);

	/**
	 * GgafDx9PlateModel オブジェクトを再構築する。<BR>
	 * @param 再構築するGgafDx9PlateModel
	 */
	static void restorePlateModel(GgafDx9PlateModel* prm_pPlateModel);

};

#endif /*GGAFDX9MODELMANAGER_H_*/
