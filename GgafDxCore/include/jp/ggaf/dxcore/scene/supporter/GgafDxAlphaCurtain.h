#ifndef GGAFDXALPHACURTAIN_H_
#define GGAFDXALPHACURTAIN_H_
namespace GgafDxCore {

/**
 * ���J�[�e�� .
 * @version 1.00
 * @since 2010/04/21
 * @author Masatoshi Tsuge
 */
class GgafDxAlphaCurtain : public GgafCore::GgafCurtain {
public:
    /** [r]���J�[�e�������t����V�[�� */
    GgafDxScene* _pDxScene;
    /** [r]�J�[�e���������Ƃ��̃� */
    float _min_alpha;
    /** [r]�J�[�e�����J�����Ƃ��̃� */
    float _max_alpha;
    /** [r]�J�[�e���̕��i�J�̒����j */
    float _range_alpha;
    /** [r]���݂̃V�[���̃� */
    float _alpha;

    /**
     * �R���X�g���N�^ .
     * @param prm_pScene ���J�[�e�������t����V�[��
     * @param prm_min_alpha �J�[�e���������Ƃ��̃�
     * @param prm_max_alpha �J�[�e�����J�����Ƃ��̃�
     */
    GgafDxAlphaCurtain(GgafDxScene* prm_pScene, float prm_min_alpha = 0.0f, float prm_max_alpha = 1.0f);

    void processOpenBegin() override;

    void processOpening() override;

    void processOpenDone() override;

    void processCloseBegin() override;

    void processClosing() override;

    void processCloseDone() override;

    void behave() override;

    virtual ~GgafDxAlphaCurtain();
};

}
#endif /*GGAFDXALPHACURTAIN_H_*/

