#ifndef GGAFDX9EFFECTMANAGER_H_
#define GGAFDX9EFFECTMANAGER_H_
namespace GgafDx9Core {

/**
 * GgafDx9EffectLead �Ǘ��N���X .
 * �����ς� GgafDx9EffectLead �I�u�W�F�N�g��o�^���Ă����A�g���܂킵�܂��B
 */
class GgafDx9EffectManager : public GgafCore::GgafResourceManager<ID3DXEffect> {

public:

    /**
     * �R���X�g���N�^
     * @param prm_manager_name �}�l�[�W������(���e�����K�{)
     */
    GgafDx9EffectManager(const char* prm_manager_name);

    /**
     * �I�[�o�[���C�h
     */
    ID3DXEffect* processCreateResource(char* prm_idstr);

    /**
     * �I�[�o�[���C�h
     */
    GgafCore::GgafResourceLead<ID3DXEffect>* processCreateLead(char* prm_idstr, ID3DXEffect* prm_pResource);

    virtual ~GgafDx9EffectManager() {
    }
};

}
#endif /*GGAFDX9EFFECTMANAGER_H_*/
