#ifndef GGAFDX9CUBEMAPMESHSETACTOR_H_
#define GGAFDX9CUBEMAPMESHSETACTOR_H_
namespace GgafDx9Core {

/**
 * ���}�b�v���b�V���Z�b�g�A�N�^�[.
 * GgafDx9MeshActor ���p�����A���}�b�v�e�N�X�`�������������A�N�^�[�ł��B<BR>
 * @version 1.00
 * @since 2010/12/24
 * @author Masatoshi Tsuge
 */
class GgafDx9CubeMapMeshSetActor : public GgafDx9MeshSetActor {

public:

    /** ���f������ */
    GgafDx9CubeMapMeshSetModel* _pCubeMapMeshSetModel;
    /** �G�t�F�N�g���� */
    GgafDx9CubeMapMeshSetEffect* _pCubeMapMeshSetEffect;

    /** �`�掞�̃I�u�W�F�N�g�� */
    //int _draw_set_num;
    //int _draw_object_num;

    /**
     * �R���X�g���N�^ .
     * @param prm_name �A�N�^�[���́i�f�o�b�O���O�ŕ\���A�Ȃ�ł��ǂ��j
     * @param prm_model_id ���f����`���A������ ".x" ������X�t�@�C�����ɂȂ邱�ƁB
     * @param prm_effect_id �G�t�F�N�g��`���B������ ".fx" �����ăG�t�F�N�g�t�@�C�����ɂȂ邱�ƁB
     * @param prm_technique �G�t�F�N�g�̃e�N�j�b�N��
     * @param prm_pChecker �g�p����`�F�b�J�[�I�u�W�F�N�g�i�`�F�b�J�[���g�p����NULL�ł悢�j
     * @return
     */
    GgafDx9CubeMapMeshSetActor(const char* prm_name,
                        const char* prm_model_id,
                        const char* prm_effect_id,
                        const char* prm_technique,
                        GgafDx9Checker* prm_pChecker );

    /**
     * ��OverRide �ł���<BR>
     */
    virtual void processDraw() override;

    virtual ~GgafDx9CubeMapMeshSetActor(); //�f�X�g���N�^
};

}
#endif /*GGAFDX9CUBEMAPMESHSETACTOR_H_*/
