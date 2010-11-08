#ifndef WALLEDSCENE_H_
#define WALLEDSCENE_H_
namespace GgafDx9LibStg {

/**
 * �ǃu���b�N�V�[�� .
 * @version 1.00
 * @since 2010/11/05
 * @author Masatoshi Tsuge
 */
class WalledScene : public GgafDx9LibStg::ScrolledScene {

public:
    /** �Z�N�V�����V�[���̃��X�g */
    GgafCore::GgafLinkedListRing<GgafDx9LibStg::WalledSectionScene>* _pRingSection;
    /** �ǃu���b�N����������f�B�X�p�b�`���[(buildWalledScene()�Őݒ肳���) */
    GgafCore::GgafActorDispatcher* _pDispatcher_Wall;

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
     * @param prm_pDispatcher_Wall �ǃu���b�N����������f�B�X�p�b�`���[
     */
    void buildWalledScene(
            int prm_wall_dep, int prm_wall_width, int prm_wall_height,
            WalledSectionScene** prm_papSection, int prm_section_num,
            GgafCore::GgafActorDispatcher* prm_pDispatcher_Wall
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
