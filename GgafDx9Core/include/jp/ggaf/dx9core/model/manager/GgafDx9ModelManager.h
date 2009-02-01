#ifndef GGAFDX9MODELMANAGER_H_
#define GGAFDX9MODELMANAGER_H_
namespace GgafDx9Core {






//文字列の分割
//さて，文字列の実態はchar型の配列で終端が'\0'であるということが分かると，文字列を分割するということが簡単にできることに気がつくでしょう．
//そう，途中で'\0'を挿入してやればいいのです．そうすると，それまでの文字列が'\0'までになり，その次を指すポインタが途中から終端までの文字列を表現することになります．
//以下に簡単な例を示します．

char str[] = "hogehoge fugafuga";
char *next;
for( i = 0; str[i] != '\0'; i++ ){
  if(str[i] == ' '){
    str[i] = '\0';
    next = str + i + 1;
  }
}








/**
 * モデルインスタンス管理.
 * 主に、モデルをリストにより保持し、モデルを要求された時に<BR>
 * 生成するか、あるいは生成済を返すかを判断します。<BR>
 */
class GgafDx9ModelManager : public GgafCore::GgafResourceManager<GgafDx9Model> {

private:
	/** カスタムテンプレートXファイル読み込み用の IDirectXFile のポインタ */
	static IDirectXFile* _s_pIDirectXFile;

	/**
	 * GgafDx9MeshModel オブジェクトを生成。 .
	 * @param prm_model_name モデル定義の識別名。".x"を追加するとメッシュ定義のXファイル名になる。
	 * @param prm_dwOptions オプション（D3DXLoadMeshFromXの引数になる）
	 */
	GgafDx9MeshModel* createMeshModel(std::string prm_model_name);

	/**
	 * GgafDx9MeshModel オブジェクトを生成。 .
	 * @param prm_model_name モデル定義の識別名。".x"を追加するとメッシュ定義のXファイル名になる。
	 * @param prm_dwOptions オプション（D3DXLoadMeshFromXの引数になる）
	 */
	GgafDx9MeshModel* createDynaMeshModel(std::string prm_model_name);

	/**
	 * GgafDx9SpriteModel オブジェクトを生成。 .
	 * Xファイルのフォーマットは、カスタムテンプレートXファイルの ggaf_spritemodel_define.x の内容がが使用される<BR>
	 * @param prm_model_name モデル定義の識別名。".x"を追加するとスプライト定義のXファイル名になる。
	 */
	GgafDx9SpriteModel* createSpriteModel(std::string prm_model_name);

	/**
	 * GgafDx9SquareModel オブジェクトを生成。 .
	 * 1*1*1 立方体のモデル<BR>
	 * @param prm_model_name モデル定義の識別名。
	 */
	GgafDx9SquareModel* createSquareModel(std::string prm_model_name);

	/**
	 * GgafDx9PlateModel オブジェクトを生成。 .
	 * Xファイルのフォーマットは、カスタムテンプレートXファイルの ggaf_spritemodel_define.x の内容がが使用される<BR>
	 * @param prm_model_name モデル定義の識別名。".x"を追加すると定義のXファイル名になる。
	 */
	GgafDx9PlateModel* createPlateModel(std::string prm_model_name);

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
	 * オーバーライド
	 */
	GgafCore::GgafResourceLead<GgafDx9Model>* processCreateLead(char* prm_idstr, GgafDx9Model* prm_pResource);


	virtual ~GgafDx9ModellManager() {};

//
//
//
//	static GgafDx9TextureManager* _pTextureManager;
//
//	/**
//	 * GgafDx9Modelオブジェクトをリストの各インスタンスの内容を再構築。 .
//	 * デバイスロスト後の復帰時に呼び出される<BR>
//	 */
//	void restoreAll();
//
//	void onDeviceLostAll();
//
//	/**
//	 * GgafDx9MeshModelオブジェクトを取得。 .
//	 * GgafDx9Model オブジェクトリスト（先頭は_s_pModel_First）<BR>
//	 * から検索し、ヒットした（生成済みGgafDx9MeshModelがある）場合、 GgafDx9MeshModel にキャストしてそれを返す。<BR>
//	 * ヒットしない場合は create を行いインスタンス生成後リストに追加しそれを返す。<BR>
//	 * 内部で std::string の比較を見つかるまで行うため、重いです。<BR>
//	 * 毎フレーム実行されるような使用は避けるべきです。<BR>
//	 * 初期化関数等で１回使用し、ポインタを保持するという使用方法を想定。<BR>
//	 * @param prm_model_name スプライト定義の識別名。".x"を追加すると定義Xファイル名になる。
//	 * @param prm_dwOptions オプション（D3DXLoadMeshFromXの引数になる）
//	 */
//	GgafDx9MeshModel* obtainMeshModel(std::string prm_model_name, DWORD prm_dwOptions);
//
//	/**
//	 * GgafDx9SpriteModelオブジェクトを取得。 .
//	 * 生成済み GgafDx9Model オブジェクトリスト（先頭は_s_pModel_First）<BR>
//	 * から検索し、ヒットした（生成済みGgafDx9SpriteModelがある）場合、 GgafDx9SpriteModel にキャストしてそれを返す。<BR>
//	 * ヒットしない場合は create を行いインスタンス生成後リストに追加しそれを返す。<BR>
//	 * 内部で std::string の比較を見つかるまで行うため、重いです。<BR>
//	 * 毎フレーム実行されるような使用は避けるべきです。<BR>
//	 * 初期化関数等で１回使用し、ポインタを保持するという使用方法を想定。<BR>
//	 * @param prm_model_name モデル定義の識別名。（".x"を追加すると定義Xファイル名になる）
//	 */
//	GgafDx9SpriteModel* obtainSpriteModel(std::string prm_model_name);
//
//	/**
//	 * GgafDx9SquareModelオブジェクトを取得。 .
//	 * 生成済み GgafDx9Model オブジェクトリスト（先頭は_s_pModel_First）<BR>
//	 * から検索し、ヒットした（生成済みGgafDx9SquareModelがある）場合、 GgafDx9SquareModel にキャストしてそれを返す。<BR>
//	 * ヒットしない場合は create を行いインスタンス生成後リストに追加しそれを返す。<BR>
//	 * 内部で std::string の比較を見つかるまで行うため、重いです。<BR>
//	 * 毎フレーム実行されるような使用は避けるべきです。<BR>
//	 * 初期化関数等で１回使用し、ポインタを保持するという使用方法を想定。<BR>
//	 * @param prm_model_name モデル定義の識別名。（".x"を追加すると定義Xファイル名になる）
//	 */
//	GgafDx9SquareModel* obtainSquareModel(std::string prm_model_name);
//
//	/**
//	 * GgafDx9PlateModelオブジェクトを取得。<BR>
//	 * 生成済み GgafDx9Model オブジェクトリスト（先頭は_s_pModel_First）<BR>
//	 * から検索し、ヒットした（生成済みGgafDx9PlateModelがある）場合、 GgafDx9PlateModel にキャストしてそれを返す。<BR>
//	 * ヒットしない場合は create を行いインスタンス生成後リストに追加しそれを返す。<BR>
//	 * 内部で std::string の比較を見つかるまで行うため、重いです。<BR>
//	 * 毎フレーム実行されるような使用は避けるべきです。<BR>
//	 * 初期化関数等で１回使用し、ポインタを保持するという使用方法を想定。<BR>
//	 * @param prm_model_name モデル定義の識別名。（".x"を追加すると定義Xファイル名になる）
//	 */
//	static GgafDx9PlateModel* obtainPlateModel(std::string prm_model_name);
//
//	/**
//	 * GgafDx9Modelオブジェクトのリストをすべて delete を行う。<BR>
//	 */
//	static void release();
//
//	/**
//	 * GgafDx9MeshModel オブジェクトを再構築する。 .
//	 * @param prm_pMeshModel 再構築するGgafDx9MeshModel
//	 */
//	static void restoreMeshModel(GgafDx9MeshModel* prm_pMeshModel);
//
//	/**
//	 * GgafDx9SpriteModel オブジェクトを再構築する。 .
//	 * @param prm_pSpriteModel 再構築するGgafDx9SpriteModel
//	 */
//	static void restoreSpriteModel(GgafDx9SpriteModel* prm_pSpriteModel);
//
//	/**
//	 * GgafDx9SquareModel オブジェクトを再構築する。 .
//	 * @param prm_pSquareModel 再構築するGgafDx9SquareModel
//	 */
//	static void restoreSquareModel(GgafDx9SquareModel* prm_pSquareModel);
//
//
//	/**
//	 * GgafDx9PlateModel オブジェクトを再構築する。 .
//	 * @param prm_pPlateModel 再構築するGgafDx9PlateModel
//	 */
//	static void restorePlateModel(GgafDx9PlateModel* prm_pPlateModel);
//
};


}
#endif /*GGAFDX9MODELMANAGER_H_*/
