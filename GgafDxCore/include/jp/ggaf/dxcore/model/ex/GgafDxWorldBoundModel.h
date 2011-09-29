#ifndef GGAFDXWORLDMODEL_H_
#define GGAFDXWORLDMODEL_H_
namespace GgafDxCore {

/**
 * ���E���E���f�� .
 * @version 1.00
 * @since 2011/05/20
 * @author Masatoshi Tsuge
 */
class GgafDxWorldBoundModel : public GgafDxMorphMeshModel {
    friend class GgafDxModelManager;

public:

    /**
     * �R���X�g���N�^<BR>
     * @param prm_model_name �X�v���C�g��`�̎��ʖ��B".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
     */
    GgafDxWorldBoundModel(char* prm_model_name);

    virtual HRESULT draw(GgafDxDrawableActor* prm_pActor_Target, int prm_draw_set_num = 1) override;

    virtual ~GgafDxWorldBoundModel(); //�f�X�g���N�^
};

}
#endif /*GGAFDXWORLDMODEL_H_*/

