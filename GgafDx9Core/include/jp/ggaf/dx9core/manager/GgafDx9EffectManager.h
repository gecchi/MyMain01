#ifndef GGAFDX9EFFECTMANAGER_H_
#define GGAFDX9EFFECTMANAGER_H_
namespace GgafDx9Core {

/**
 * GgafDx9EffectConnection �Ǘ��N���X .
 * �����ς� GgafDx9EffectConnection �I�u�W�F�N�g��o�^���Ă����A�g���܂킵�܂��B
 * @version 1.00
 * @since 2009/02/09
 * @author Masatoshi Tsuge
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
     * �G�t�F�N�g����ID�ɂ��A�G�t�F�N�g�u�W�F�N�g�𐶐����� .
     * <pre>
     * ��prm_idstr�̌`��������
     * prm_idstr�́A
     * �w�G�t�F�N�g�^�C�v  + "/" + fx�t�@�C����(�g���q .fx ������������)�x
     * �Ƃ���������ɂȂ��Ă���B�G�t�F�N�g�^�C�v�͈ȉ��̒ʂ�
     * 'D': GgafDx9MeshEffect �I�u�W�F�N�g
     * 'd': GgafDx9MeshEffect �I�u�W�F�N�g
     * 'X': GgafDx9MeshEffect �I�u�W�F�N�g
     * 'x': GgafDx9MeshSetEffect �I�u�W�F�N�g
     * 'A': GgafDx9D3DXAniMeshEffect �I�u�W�F�N�g
     * 'M': GgafDx9MorphMeshEffect �I�u�W�F�N�g
     * 'S': GgafDx9SpriteEffect �I�u�W�F�N�g
     * 's': GgafDx9SpriteSetEffect �I�u�W�F�N�g
     * 'B': GgafDx9BoardEffect �I�u�W�F�N�g
     * 'b': GgafDx9BoardSetEffect �I�u�W�F�N�g
     *
     * ��F"x/LaserChipEffect" �̏ꍇ�B
     * "LaserChipEffect.fx"��ǂݍ��� GgafDx9MeshSetEffect�C���X�^���X ��Ԃ��B
     * </pre>
     * @param prm_idstr �G�t�F�N�g����ID
     * @return �G�t�F�N�g�I�u�W�F�N�g
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
