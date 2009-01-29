#ifndef GGAFDX9TEXTUREMANAGER_H_
#define GGAFDX9TEXTUREMANAGER_H_
namespace GgafDx9Core {


/**
 * GgafDx9TextureConnection �Ǘ��N���X .
 * �����ς� GgafDx9TextureConnection �I�u�W�F�N�g��o�^���Ă����A�g���܂킵�܂��B
 */
class GgafDx9TextureManager : public GgafCore::GgafResourceManager<IDirect3DTexture9> {

public:

	GgafDx9TextureManager(std::string prm_name);
	/**
	 * �I�[�o�[���C�h
	 */
	IDirect3DTexture9* processCreateResource(std::string prm_resource_idstr);

	/**
	 * �I�[�o�[���C�h
	 */
	GgafCore::GgafResourceConnection<IDirect3DTexture9>* processCreateConnection(std::string prm_resource_idstr, IDirect3DTexture9* prm_pResource);


	virtual ~GgafDx9TextureManager();
};


}
#endif /*GGAFDX9TEXTUREMANAGER_H_*/
