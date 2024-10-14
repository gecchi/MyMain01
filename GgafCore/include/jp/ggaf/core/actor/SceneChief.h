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
    void onHit(const Checker* prm_pOtherChecker, const Actor* prm_pOtherActor) override {
    }

    void remove();

    /**
     * �������Ă���V�[�����擾�B .
     * @return	Scene*	�������Ă���V�[��
     */
    virtual Scene* getPlatformScene() {
        return _pScene_platform;
    }


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
