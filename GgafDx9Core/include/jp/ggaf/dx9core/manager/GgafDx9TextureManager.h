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
class GgafDx9TextureManager : public GgafCore::GgafResourceManager<GgafDx9Texture> {

public:

    /**
     * �R���X�g���N�^
     * @param prm_manager_name �}�l�[�W������(���e�����K�{)
     */
    GgafDx9TextureManager(const char* prm_manager_name);

    /**
     * �I�[�o�[���C�h
     */
    GgafDx9Texture* processCreateResource(char* prm_idstr, void* prm_p);

    /**
     * �I�[�o�[���C�h
     */
    GgafCore::GgafResourceConnection<GgafDx9Texture>* processCreateConnection(char* prm_idstr, GgafDx9Texture* prm_pResource);

    virtual ~GgafDx9TextureManager() {
    }
};

}
#endif /*GGAFDX9TEXTUREMANAGER_H_*/
