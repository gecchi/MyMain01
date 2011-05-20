#ifndef GGAFDX9WORLDMODEL_H_
#define GGAFDX9WORLDMODEL_H_
namespace GgafDx9Core {

/**
 * ���E���E���f�� .
 * @version 1.00
 * @since 2011/05/20
 * @author Masatoshi Tsuge
 */
class GgafDx9WorldBoundModel : public GgafDx9MorphMeshModel {
    friend class GgafDx9ModelManager;

public:

    /**
     * �R���X�g���N�^<BR>
     * @param prm_model_name �X�v���C�g��`�̎��ʖ��B".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
     */
    GgafDx9WorldBoundModel(char* prm_model_name);

    virtual HRESULT draw(GgafDx9DrawableActor* prm_pActor_Target, int prm_draw_set_num = 1) override;

    virtual ~GgafDx9WorldBoundModel(); //�f�X�g���N�^
};

}
#endif /*GGAFDX9CUBEMAPMORPHMESHMODEL_H_*/

