#ifndef GGAFDX9TEXTUREMANAGER_H_
#define GGAFDX9TEXTUREMANAGER_H_
namespace GgafDx9Core {

/**
 * GgafDx9TextureConnection �Ǘ��N���X .
 * �����ς� GgafDx9TextureConnection �I�u�W�F�N�g��o�^���Ă����A�g���܂킵�܂��B
 * @version 1.00
 * @since 2009/01/26
 * @author Masatoshi Tsuge
 */
class GgafDx9TextureManager : public GgafCore::GgafResourceManager<IDirect3DTexture9> {

public:

    /**
     * �R���X�g���N�^
     * @param prm_manager_name �}�l�[�W������(���e�����K�{)
     */
    GgafDx9TextureManager(const char* prm_manager_name);

    /**
     * �I�[�o�[���C�h
     */
    IDirect3DTexture9* processCreateResource(char* prm_idstr);

    /**
     * �I�[�o�[���C�h
     */
    GgafCore::GgafResourceConnection<IDirect3DTexture9>* processCreateConnection(char* prm_idstr, IDirect3DTexture9* prm_pResource);

    virtual ~GgafDx9TextureManager() {
    }
};

}
#endif /*GGAFDX9TEXTUREMANAGER_H_*/
