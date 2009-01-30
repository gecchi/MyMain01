#ifndef GGAFDX9SEMANAGER_H_
#define GGAFDX9SEMANAGER_H_
namespace GgafDx9Core {


/**
 * GgafDx9Se 管理クラス .
 * 生成済み GgafDx9Se オブジェクトを登録しておき、使いまわします。
 */
class GgafDx9SeManager : public GgafCore::GgafResourceManager<GgafDx9Se> {

public:

	/**
	 * コンストラクタ
	 * @param prm_manager_name マネージャ名称(リテラル必須)
	 */
	GgafDx9SeManager(const char* prm_manager_name);

	/**
	 * オーバーライド
	 */
	GgafDx9Se* processCreateResource(char* prm_idstr);

	/**
	 * オーバーライド
	 */
	GgafCore::GgafResourceConnection<GgafDx9Se>* processCreateConnection(char* prm_idstr, GgafDx9Se* prm_pResource);


	virtual ~GgafDx9SeManager() {};
};


}
#endif /*GGAFDX9SEMANAGER_H_*/
