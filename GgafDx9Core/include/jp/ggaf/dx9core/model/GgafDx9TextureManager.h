#ifndef GGAFDX9TEXTUREMANAGER_H_
#define GGAFDX9TEXTUREMANAGER_H_
namespace GgafDx9Core {


/**
 * GgafDx9Texture 管理クラス .
 * 生成済み GgafDx9Texture オブジェクトを登録しておき、使いまわします。
 */
class GgafDx9TextureManager : public GgafCore::GgafResourceManager<IDirect3DTexture9> {

public:

	GgafDx9TextureManager(std::string prm_name);
	/**
	 */
	GgafCore::GgafResource<IDirect3DTexture9>* createResource(std::string prm_texture_file_name);

	virtual ~GgafDx9TextureManager();
};


}
#endif /*GGAFDX9TEXTUREMANAGER_H_*/
