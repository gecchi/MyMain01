#ifndef GGAFDX9TEXTUREMANAGER_H_
#define GGAFDX9TEXTUREMANAGER_H_
namespace GgafDx9Core {


/**
 * GgafDx9TextureConnection 管理クラス .
 * 生成済み GgafDx9TextureConnection オブジェクトを登録しておき、使いまわします。
 */
class GgafDx9TextureManager : public GgafCore::GgafResourceManager<IDirect3DTexture9> {

public:

	GgafDx9TextureManager(std::string prm_name);
	/**
	 * オーバーライド
	 */
	IDirect3DTexture9* processCreateResource(std::string prm_resource_idstr);

	/**
	 * オーバーライド
	 */
	GgafCore::GgafResourceConnection<IDirect3DTexture9>* processCreateConnection(std::string prm_resource_idstr, IDirect3DTexture9* prm_pResource);


	virtual ~GgafDx9TextureManager();
};


}
#endif /*GGAFDX9TEXTUREMANAGER_H_*/
