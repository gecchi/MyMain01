#ifndef GGAFDX9TEXTUREMANAGER_H_
#define GGAFDX9TEXTUREMANAGER_H_
namespace GgafDx9Core {


/**
 * GgafDx9TextureLead 管理クラス .
 * 生成済み GgafDx9TextureLead オブジェクトを登録しておき、使いまわします。
 */
class GgafDx9TextureManager : public GgafCore::GgafResourceManager<IDirect3DTexture9> {

public:

	/**
	 * コンストラクタ
	 * @param prm_manager_name マネージャ名称(リテラル必須)
	 */
	GgafDx9TextureManager(const char* prm_manager_name);

	/**
	 * オーバーライド
	 */
	IDirect3DTexture9* processCreateResource(char* prm_idstr);

	/**
	 * オーバーライド
	 */
	GgafCore::GgafResourceLead<IDirect3DTexture9>* processCreateLead(char* prm_idstr, IDirect3DTexture9* prm_pResource);


	virtual ~GgafDx9TextureManager() {};
};


}
#endif /*GGAFDX9TEXTUREMANAGER_H_*/
