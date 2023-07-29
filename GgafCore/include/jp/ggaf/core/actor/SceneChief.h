#ifndef GGAF_CORE_SCENECHIEF_H_
#define GGAF_CORE_SCENECHIEF_H_
#include "jp/ggaf/GgafCommonHeader.h"
#include "jp/ggaf/core/actor/Actor.h"

namespace GgafCore {

/**
 * �V�[���̃`�[�t�N���X .
 * �V�[���N���X�ƃA�N�^�[�̋��n�����s�����ʂȃA�N�^�[�B<BR>
 * �V�[���N���X�ƃV�[���`�[�t�͕��ʂ�hasA�̊֌W�ł��B�i�`�[�t�ƒc���͊K�w�֌W�ɂȂ��Ă��܂��j<BR>
 * �S�ẴV�[��(Sceane�I�u�W�F�N�g)�ɕK���P�l�V�[���`�[�t�����܂��B<BR>
 * �`�[�t�́A�A�N�^�[�B�c���[�̍ł����_�Ɉʒu���܂��B<BR>
 * �`�[�t(SceneChief)�̎q�A�N�^�[�͕K���c��(GroupHead)�ɂȂ��Ă��܂��B<BR>
 * ����ɒc���̉��ɕ��ʂ̃A�N�^�[�����܂��B<BR>
 * �`�[�t�ւ̃��\�b�h���s�́A���̔z���S�Ă̒c���{�A�N�^�[�ւ̎w���ƂȂ�܂��B<BR>
 * �c��(GroupHead)�̉�������킹�ĎQ�Ƃ��ĉ������B
 * @version 1.00
 * @since 2007/11/29
 * @author Masatoshi Tsuge
 */
class SceneChief : public Actor {

private:
    /** ���݂̏����V�[�� */
    Scene* _pScene_platform;

private:
    /**
     * �g�p�s�� .
     */
    SceneChief* extract() override {
        throwCriticalException("SceneChief �� extract() �͎��s�ł��܂���Bname="<<getName());
        return (SceneChief*)nullptr;
    }

    /**
     * �����V�[����ݒ肷��B.
     */
    void setPlatformScene(Scene* prm_pScene_platform) {
        _pScene_platform = prm_pScene_platform;
    }

public:
    SceneChief(Scene* prm_pScene_platform);

    /**
     * ��������<BR>
     */
    void initialize() override {
    }

    void processBehavior() override {
    }

    void processSettlementBehavior() override {
    }

    void processJudgement() override {
    }
    bool processHitChkLogic(Actor* prm_pOtherActor) override {
        return false;
    }
    void processPreDraw() override {
    }

    void processDraw() override {
    }

    void processAfterDraw() override {
    }


    void processFinal() override {
    }


    void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {
    }

    void throwEventUpperTree(eventval prm_event_val, void* prm_pSource) override;
    void throwEventUpperTree(eventval prm_event_val) override {
        throwEventUpperTree(prm_event_val, this);
    }
    void onHit(const Actor* prm_pOtherActor) override {
    }

    void remove();

    /**
     * �������Ă���V�[�����擾�B .
     * @return	Scene*	�������Ă���V�[��
     */
    virtual Scene* getPlatformScene() {
        return _pScene_platform;
    }

    /**
     * �O���[�v�Ƃ��Ĉ����̃A�N�^�[���q�A�N�^�[�ɒǉ����܂� .
     * ����͎�����GroupHead�I�u�W�F�N�g���Ԃɑ}������܂��B<BR>
     * ���������ăO���[�v��ʂƋ��ɓo�^���K�v�ł��B<BR>
     * ��ʂƂ́A�����Ő�������� GroupHead�� �ɂ��g�p����܂��B<BR>
     * GroupHead�I�u�W�F�N�g �͏����ʓo�^��������������A�Q��ڈȍ~�̓����ʓo�^�́A<BR>
     * ������ GroupHead�I�u�W�F�N�g�̎q�ɒǉ�����܂��B<BR>
     * <pre>
     * ���g�p��P��
     *
     *  appendGroupChild(KIND_XXX, pActor);
     *
     *  �Ƃ����ꍇ�A�K�w�\���͎��̂悤�ɂȂ�B
     *
     *  this
     *    |
     *    +- pObject(GroupHead[KIND_XXX])
     *         |
     *         +- pActor
     *
     *
     * ���g�p��Q��
     *
     * appendGroupChild(KIND_AAA, pActor01);
     * appendGroupChild(KIND_BBB, pActor02);
     * appendGroupChild(KIND_AAA, pActor03);
     *
     * �Ƃ����ꍇ�A�K�w�\���͎��̂悤�ɂȂ�B
     *
     *  this
     *    |
     *    +- pObject(GroupHead[KIND_AAA]) -- pObject(GroupHead[KIND_BBB])
     *         |                                    |
     *         +- pActor01 -- pActor03              + pActor02
     * </pre>
     * �⑫�F������ prm_pMainActor �ȉ��S�ẴA�N�^�[�Ɋւ��āA
     *       �E�����V�[�������o (_pScene_platform)
     *       �E�`�[�t�A�N�^�[�����o(_pSceneChief)
     *       �E�c���A�N�^�[�����o(_pGroupHead) ���A�����ʂɑ��̒c���������ꍇ�͂����܂�
     *       �̍X�V���s���܂��B
     * @param   prm_kind    ��ʖ��i��GroupHead���j
     * @param   prm_pMainActor   �o�^����A�N�^�[
     */
    GroupHead* appendGroupChild(kind_t prm_kind, MainActor* prm_pMainActor);

    /**
     * �P��Actor�A������DestructActor���P�Ɛe�ƂȂ�Actor�A���̂�<BR>
     * ��ʂ͈����q�A�N�^�[�̃X�e�[�^�X(getStatus())�̍��� 'STAT_DEFAULT_ACTOR_KIND' �̒l���A��ʂƂ���
     * �㏑���R�s�[�����B
     * �{�֐��͂̕��I������ prm_pActor �� GroupHead �̎q�A�N�^�[�Ƃ��Ă��邾���ł���B<BR>
     * @param   prm_pMainActor   �o�^����A�N�^�[
     */
    GroupHead* appendGroupChild(MainActor* prm_pMainActor);

    /**
     * �q�̒c���A�N�^�[���擾�A�������nullptr���A��
     * @param prm_kind
     * @return
     */
    GroupHead* searchChildGroupHead(kind_t prm_kind);

    void updateActiveInTheTree() override;

    /**
     * �Ǘ��҂ɉy�� .
     * @return    �Ă΂�ďo�Ă����Ǘ���
     */
    Caretaker* askCaretaker();

    /**
     * �z���c���[�A�N�^�[����A�����̖��O�����A�N�^�[��T�� .
     * �����́A�A�N�^�[���� Util::easy_hash(const char* str) ��HASH�l�ɕϊ������l��n���B
     * @param prm_name_hash �A�N�^�[��HASH�l
     * @return �ŏ��ɔ��������A�N�^�[�^�����ł��Ȃ��ꍇ�� nullptr
     */
    Actor* search(hashval prm_name_hash);

    virtual ~SceneChief();
};

}
#endif /**GGAF_CORE_SCENECHIEF_H_*/
