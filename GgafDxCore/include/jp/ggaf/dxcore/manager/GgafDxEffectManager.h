#ifndef GGAFDXEFFECTMANAGER_H_
#define GGAFDXEFFECTMANAGER_H_
namespace GgafDxCore {

/**
 * GgafDxEffectConnection �Ǘ��N���X .
 * �����ς� GgafDxEffectConnection �I�u�W�F�N�g��o�^���Ă����A�g���܂킵�܂��B
 * @version 1.00
 * @since 2009/02/09
 * @author Masatoshi Tsuge
 */
class GgafDxEffectManager : public GgafCore::GgafResourceManager<GgafDxEffect> {

public:

    static GgafDxEffect* _pEffect_Active;

    /**
     * �R���X�g���N�^
     * @param prm_manager_name �}�l�[�W������(���e�����K�{)
     */
    GgafDxEffectManager(const char* prm_manager_name);

    /**
     * �G�t�F�N�g����ID�ɂ��A�G�t�F�N�g�u�W�F�N�g�𐶐����� .
     * <pre>
     * ��prm_idstr�̌`��������
     * prm_idstr�́A
     * �w�G�t�F�N�g�^�C�v  + "/" + fx�t�@�C����(�g���q .fx ������������)�x
     * �Ƃ���������ɂȂ��Ă���B�G�t�F�N�g�^�C�v�͈ȉ��̒ʂ�
     * 'D': GgafDxMeshEffect �I�u�W�F�N�g
     * 'd': GgafDxMeshEffect �I�u�W�F�N�g
     * 'X': GgafDxMeshEffect �I�u�W�F�N�g
     * 'x': GgafDxMeshSetEffect �I�u�W�F�N�g
     * 'A': GgafDxD3DXAniMeshEffect �I�u�W�F�N�g
     * 'M': GgafDxMorphMeshEffect �I�u�W�F�N�g
     * 'S': GgafDxSpriteEffect �I�u�W�F�N�g
     * 's': GgafDxSpriteSetEffect �I�u�W�F�N�g
     * 'B': GgafDxBoardEffect �I�u�W�F�N�g
     * 'b': GgafDxBoardSetEffect �I�u�W�F�N�g
     *
     * ��F"x/LaserChipEffect" �̏ꍇ�B
     * "LaserChipEffect.fx"��ǂݍ��� GgafDxMeshSetEffect�C���X�^���X ��Ԃ��B
     * </pre>
     * @param prm_idstr �G�t�F�N�g����ID
     * @return �G�t�F�N�g�I�u�W�F�N�g
     */
    GgafDxEffect* processCreateResource(char* prm_idstr, void* prm_p);

    /**
     * �I�[�o�[���C�h
     */
    GgafCore::GgafResourceConnection<GgafDxEffect>* processCreateConnection(char* prm_idstr, GgafDxEffect* prm_pResource);

    void setParamPerFrameAll();

    void restoreAll();

    void onDeviceLostAll();




    virtual ~GgafDxEffectManager() {
    }
};

}
#endif /*GGAFDXEFFECTMANAGER_H_*/