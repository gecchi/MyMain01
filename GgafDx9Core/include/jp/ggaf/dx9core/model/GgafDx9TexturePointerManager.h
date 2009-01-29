#ifndef GGAFDX9TEXTUREPOINTERMANAGER_H_
#define GGAFDX9TEXTUREPOINTERMANAGER_H_
namespace GgafDx9Core {


/**
 * GgafDx9TexturePointer �Ǘ��N���X .
 * �����ς� GgafDx9TexturePointer �I�u�W�F�N�g��o�^���Ă����A�g���܂킵�܂��B
 */
class GgafDx9TexturePointerManager : public GgafCore::GgafResourcePointerManager<IDirect3DTexture9> {

public:

	GgafDx9TexturePointerManager(std::string prm_name);
	/**
	 * �I�[�o�[���C�h
	 */
	IDirect3DTexture9* processCreateResource(std::string prm_resource_idstr);

	/**
	 * �I�[�o�[���C�h
	 */
	GgafCore::GgafResourcePointer<IDirect3DTexture9>* processCreateResourcePointer(std::string prm_resource_idstr, IDirect3DTexture9* prm_pResource);


	virtual ~GgafDx9TexturePointerManager();
};


}
#endif /*GGAFDX9TEXTUREPOINTERMANAGER_H_*/
