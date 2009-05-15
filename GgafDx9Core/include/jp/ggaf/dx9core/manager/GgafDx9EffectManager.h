#ifndef GGAFDX9EFFECTMANAGER_H_
#define GGAFDX9EFFECTMANAGER_H_
namespace GgafDx9Core {

/**
 * GgafDx9EffectConnection �Ǘ��N���X .
 * �����ς� GgafDx9EffectConnection �I�u�W�F�N�g��o�^���Ă����A�g���܂킵�܂��B
 */
class GgafDx9EffectManager : public GgafCore::GgafResourceManager<GgafDx9Effect> {

public:

    static GgafDx9Effect* _pEffect_Active;

    /**
     * �R���X�g���N�^
     * @param prm_manager_name �}�l�[�W������(���e�����K�{)
     */
    GgafDx9EffectManager(const char* prm_manager_name);

    /**
     * �I�[�o�[���C�h
     */
    GgafDx9Effect* processCreateResource(char* prm_idstr);

    /**
     * �I�[�o�[���C�h
     */
    GgafCore::GgafResourceConnection<GgafDx9Effect>* processCreateConnection(char* prm_idstr, GgafDx9Effect* prm_pResource);


    void restoreAll();

    void onDeviceLostAll();

    virtual ~GgafDx9EffectManager() {
    }
};

}
#endif /*GGAFDX9EFFECTMANAGER_H_*/
