#ifndef WALLEDSCENE_H_
#define WALLEDSCENE_H_
namespace GgafLib {

/**
 * �ǃu���b�N�V�[�� .
 * ��� WalledScene �́A������ WalledSectionScene ���q�����킹�����̂ł��B
 * @version 1.00
 * @since 2010/11/05
 * @author Masatoshi Tsuge
 */
class WalledScene : public DefaultScene {

public:
    /** �Z�N�V�����V�[���̕ێ����X�g */
    GgafCore::GgafLinkedListRing<GgafLib::WalledSectionScene> _ringHoldSection;
    /** ���������Z�N�V�����V�[���̕ێ����X�g */
    GgafCore::GgafLinkedListRing<GgafLib::WalledSectionScene> _ringLoopEndSection;
    /** �ǃu���b�N����������f�|�W�g��(buildWalledScene()�Őݒ肳���) */
    GgafCore::GgafActorDepository* _pDepo_WallAAB;
    GgafCore::GgafActorDepository* _pDepo_WallAAPrism;
    WalledSectionScene* _pLastSectionScene;
    bool _is_all_active_section_scenes;
    bool _is_finished;

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    WalledScene(const char* prm_name);

    /**
     * WalledScene���\�z����B
     * �{�N���X new �� initialize() �܂łɁA�K���P����s����K�v������܂��B
     * �y���Ӂz
     * prm_pDepo_WallAABox �y�� prm_pDepo_WallAAPrism �͏������Ŗ{�V�[����initialize() ��
     * �z���ɋ����ړ�����܂��B���������āA�}�l�[�W���Ǘ��̋��ʃf�|�W�g���̏ꍇ�́A
     * �}�l�[�W�����̕s���|�C���^�̌����ɂȂ�܂��B
     * @param prm_wall_dep      �ǃu���b�N�P��X�������̕�
     * @param prm_wall_width    �ǃu���b�N�P��Z�������̕�
     * @param prm_wall_height   �ǃu���b�N�P��Y�������̕�
     * @param prm_wall_start_X  �O�Ǐo����X���W�ʒu
     * @param prm_papSection    �Z�N�V�����V�[���z��ւ̃|�C���^
     * @param prm_section_num   �Z�N�V�����V�[����
     * @param prm_pDepo_WallAABox �ǃu���b�N(WallAABActor)����������f�|�W�g���i��initialize()���A�z���ɋ����ړ��j
     * @param prm_pDepo_WallAAPrism �ǃv���Y��(WallAAPrismActor)����������f�|�W�g���i��initialize()���A�z���ɋ����ځB�v���Y�����������͏ȗ��j
     */
    void buildWalledScene(
            coord prm_wall_dep, coord prm_wall_width, coord prm_wall_height,
            coord prm_wall_start_X,
            WalledSectionScene** prm_papSection, int prm_section_num,
            GgafCore::GgafActorDepository* prm_pDepo_WallAABox,
            GgafCore::GgafActorDepository* prm_pDepo_WallAAPrism = nullptr
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
     * �Ō�̃Z�N�V�����V�[���̍Ō�̕ǃu���b�N���񊈓��ɖ����ꍇ�A
     * �R�[���o�b�N�����B
     * sayonara() �Ȃǂ��������ĉ������B
     */
    virtual void onFinishedSection() = 0;

    /**
     * ���������ς݁B���ʂŃI�[�o�[���C�h����ꍇ�́A���processBehavior()���Ăяo���ĉ������B
     */
    virtual void processBehavior() override;

    virtual void processFinal() override;

    /**
     * X���̕��̕����ɃX�N���[��������֐� .
     * @param pThat �A�N�^�[
     * @param p1 �X�N���[���X�s�[�h(_scroll_speed�ւ̃|�C���^)
     * @param p2 �C�Ӂi�����͓��ɖ����j
     */
    static void scrollX(GgafObject* pThat, void* p1, void* p2);


    virtual ~WalledScene();
};

}
#endif /*WALLEDSCENE_H_*/
