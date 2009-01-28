#ifndef GGAFDX9TEXTUREMANAGER_H_
#define GGAFDX9TEXTUREMANAGER_H_
namespace GgafDx9Core {


/**
 * GgafDx9Texture �Ǘ��N���X .
 * �����ς� GgafDx9Texture �I�u�W�F�N�g��o�^���Ă����A�g���܂킵�܂��B
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
