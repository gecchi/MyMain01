#ifndef WALLEDSCENE_H_
#define WALLEDSCENE_H_
namespace GgafLib {

/**
 * �ǃu���b�N�V�[�� .
 * @version 1.00
 * @since 2010/11/05
 * @author Masatoshi Tsuge
 */
class WalledScene : public GgafLib::ScrolledScene {

public:
    /** �Z�N�V�����V�[���̃��X�g */
    GgafCore::GgafLinkedListRing<GgafLib::WalledSectionScene>* _pRingSection;
    /** �ǃu���b�N����������f�|�W�g��(buildWalledScene()�Őݒ肳���) */
    GgafCore::GgafActorDepository* _pDepo_WallAAB;
    GgafCore::GgafActorDepository* _pDepo_WallAAPrism;

    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    WalledScene(const char* prm_name);

    /**
     * WalledScene���\�z����B
     * �{�N���X new �� initialize() �܂łɁA�K���P����s����K�v������܂��B
     * @param prm_wall_dep      �ǃu���b�N�P��X�������̕�
     * @param prm_wall_width    �ǃu���b�N�P��Z�������̕�
     * @param prm_wall_height   �ǃu���b�N�P��Y�������̕�
     * @param prm_papSection    �Z�N�V�����V�[���z��ւ̃|�C���^
     * @param prm_section_num   �Z�N�V�����V�[����
     * @param prm_pDepo_WallAABox �ǃu���b�N����������f�|�W�g��
     * @param prm_pDepo_WallAAPrism �ǃv���Y���u���b�N����������f�|�W�g���i�ȗ��j
     */
    void buildWalledScene(
            int prm_wall_dep, int prm_wall_width, int prm_wall_height,
            WalledSectionScene** prm_papSection, int prm_section_num,
            GgafCore::GgafActorDepository* prm_pDepo_WallAABox,
            GgafCore::GgafActorDepository* prm_pDepo_WallAAPrism = NULL
         );

    /**
     * ���������ς݁B���ʂŃI�[�o�[���C�h����ꍇ�́A���initialize()���Ăяo���ĉ������B
     */
    virtual void initialize() override;

    /**
     * ���������ς݁B���ʂŃI�[�o�[���C�h����ꍇ�́A���onActive()���Ăяo���ĉ������B
     */
    virtual void onActive() override;

    /**
     * ���������ς݁B���ʂŃI�[�o�[���C�h����ꍇ�́A���processBehavior()���Ăяo���ĉ������B
     */
    virtual void processBehavior() override;

    virtual void processFinal() override;

    virtual ~WalledScene();
};

}
#endif /*WALLEDSCENE_H_*/
