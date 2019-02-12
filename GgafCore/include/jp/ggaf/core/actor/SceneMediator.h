#ifndef GGAF_CORE_SCENEMEDIATOR_H_
#define GGAF_CORE_SCENEMEDIATOR_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/actor/Actor.h"

namespace GgafCore {

/**
 * �V�[���̒���҃N���X .
 * �c��(GroupHead)�̐e�K�w�̃A�N�^�[�ŁA�c���B���Ǘ����܂��B<BR>
 * �܂��A�V�[���N���X�Ƃ̋��n�����s�����ʂȃA�N�^�[�ł�����܂��B<BR>
 * �V�[���N���X�ƃV�[������҂͕��ʂ�hasA�̊֌W�ł��B�i����҂ƒc���͊K�w�֌W�ɂȂ��Ă��܂��j<BR>
 * �S�ẴV�[��(Sceane�I�u�W�F�N�g)�ɕK���P�l�V�[������҂����܂��B<BR>
 * ����҂́A�A�N�^�[�B�c���[�̍ł����_�Ɉʒu���܂��B<BR>
 * �����(SceneMediator)�̎q�A�N�^�[�͕K���c��(GroupHead)�ɂȂ��Ă��܂��B<BR>
 * ����ɒc���̉��ɕ��ʂ̃A�N�^�[�����܂��B<BR>
 * ����҂ւ̃��\�b�h���s�́A���̔z���S�Ă̒c���{�A�N�^�[�ւ̎w���ƂȂ�܂��B<BR>
 * �c��(GroupHead)�̉�������킹�ĎQ�Ƃ��ĉ������B
 * @version 1.00
 * @since 2007/11/29
 * @author Masatoshi Tsuge
 */
class SceneMediator : public Actor {

private:
    /** ���݂̏����V�[�� */
    Scene* _pScene_platform;

private:
    /**
     * �g�p�s�� .
     */
    SceneMediator* extract() override {
        throwCriticalException("SceneMediator �� extract() �͎��s�ł��܂���Bname="<<getName());
        return (SceneMediator*)nullptr;
    }

    /**
     * �����V�[����ݒ肷��B.
     */
    void setPlatformScene(Scene* prm_pScene_platform) {
        _pScene_platform = prm_pScene_platform;
    }

public:
    SceneMediator(Scene* prm_pScene_platform);

    /**
     * ��������<BR>
     */
    void initialize() override {
    }

    void processBehavior() override {
    }

    void processSettlementBehavior() override {
    }

    void processPreJudgement() override {
    }

    void processJudgement() override {
    }

    void processPreDraw() override {
    }

    void processDraw() override {
    }

    void processAfterDraw() override {
    }


    void processFinal() override {
    }


    void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    void throwEventUpperTree(hashval prm_no, void* prm_pSource) override;
    void throwEventUpperTree(hashval prm_no) override {
        throwEventUpperTree(prm_no, this);
    }
    /**
     * �����蔻��s�v�̂��ߏ��false��Ԃ� .
     * @param prm_pOtherActor
     * @return false
     */
    bool processHitChkLogic(Actor* prm_pOtherActor) override {
        return false;
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
     *       �E����҃A�N�^�[�����o(_pSceneMediator)
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
     * �_�ɉy�� .
     * @return    �Ă΂�ďo�Ă����_
     */
    God* askGod();

    /**
     * �z���c���[�A�N�^�[����A�����̖��O�����A�N�^�[��T�� .
     * �����́A�A�N�^�[���� Util::easy_hash(const char* str) ��HASH�l�ɕϊ������l��n���B
     * @param prm_name_hash �A�N�^�[��HASH�l
     * @return �ŏ��ɔ��������A�N�^�[�^�����ł��Ȃ��ꍇ�� nullptr
     */
    Actor* search(hashval prm_name_hash);

    virtual ~SceneMediator();
};

}
#endif /**GGAFSCENEMEDIATOR_H_*/
