#ifndef GGAFDXTEXTUREMANAGER_H_
#define GGAFDXTEXTUREMANAGER_H_
namespace GgafDxCore {

/**
 * GgafDxTextureConnection �Ǘ��N���X .
 * �����ς� GgafDxTextureConnection �I�u�W�F�N�g��o�^���Ă����A�g���܂킵�܂��B
 * @version 1.00
 * @since 2009/01/26
 * @author Masatoshi Tsuge
 */
class GgafDxTextureManager : public GgafCore::GgafResourceManager<GgafDxTexture> {

public:

    /**
     * �R���X�g���N�^
     * @param prm_manager_name �}�l�[�W������(���e�����K�{)
     */
    GgafDxTextureManager(const char* prm_manager_name);

    /**
     * �I�[�o�[���C�h
     */
    GgafDxTexture* processCreateResource(char* prm_idstr, void* prm_p);

    void releaseAll();

    void restoreAll();



    /**
     * �I�[�o�[���C�h
     */
    GgafCore::GgafResourceConnection<GgafDxTexture>* processCreateConnection(char* prm_idstr, GgafDxTexture* prm_pResource);

    virtual ~GgafDxTextureManager() {
    }
};

}
#endif /*GGAFDXTEXTUREMANAGER_H_*/
