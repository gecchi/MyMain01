#ifndef GGAFLIB_WALLEDSCENE_H_
#define GGAFLIB_WALLEDSCENE_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"

#include "jp/ggaf/core/util/GgafLinkedListRing.hpp"
#include "jp/ggaf/lib/scene/WalledSectionScene.h"

namespace GgafLib {

/**
 * ���폜�\�聄
 * X�������X�N���[���̕ǃu���b�N�V�[�� .
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
    GgafCore::GgafActorDepository* _pDepo_wall;
    GgafCore::GgafActorDepository* _pDepo_prism;
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
     * X�������X�N���[�� WalledScene ��ݒ肷��B
     * �{�N���X new �� initialize() �܂łɁA�K���P����s����K�v������܂��B
     * �y���Ӂz
     * prm_pDepo_wallox �y�� prm_pDepo_prism �͏������Ŗ{�V�[����initialize() ��
     * �z���ɋ����ړ�����܂��B���������āA�}�l�[�W���Ǘ��̋��ʃf�|�W�g���̏ꍇ�́A
     * �}�l�[�W�����̕s���|�C���^�̌����ɂȂ�܂��B
     * @param prm_wall_dep      �ǃu���b�N�P��X�������̕�
     * @param prm_wall_width    �ǃu���b�N�P��Z�������̕�
     * @param prm_wall_height   �ǃu���b�N�P��Y�������̕�
     * @param prm_wall_start_x  �O�Ǐo����X���W�ʒu
     * @param prm_papSection    �Z�N�V�����V�[���z��ւ̃|�C���^
     * @param prm_section_num   �Z�N�V�����V�[����
     * @param prm_pDepo_wallox  �ǃu���b�N(WallAABActor)����������f�|�W�g���i��initialize()���A�z���ɋ����ړ��j
     * @param prm_pDepo_prism   �ǃv���Y��(WallAAPrismActor)����������f�|�W�g���i��initialize()���A�z���ɋ����ځB�v���Y�����������͏ȗ��j
     */
    void buildWalledScene(
            coord prm_wall_dep, coord prm_wall_width, coord prm_wall_height,
            coord prm_wall_start_x,
            WalledSectionScene** prm_papSection, int prm_section_num,
            GgafCore::GgafActorDepository* prm_pDepo_wallox,
            GgafCore::GgafActorDepository* prm_pDepo_prism = nullptr
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
    virtual void onFinishedAllSection() = 0;

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
#endif /*GGAFLIB_WALLEDSCENE_H_*/
