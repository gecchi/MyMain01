#ifndef GGAF_CORE_MAINACTOR_H_
#define GGAF_CORE_MAINACTOR_H_
#include "jp/ggaf/GgafCommonHeader.h"
#include "jp/ggaf/core/actor/Actor.h"

namespace GgafCore {

/**
 * ���ʂ̃A�N�^�[(����) .
 * ���ʃA�N�^�[�N���X�ւ̃C���^�[�t�F�C�X�ł���A<BR>
 * �V���ɃA�N�^�[�N���X�����ꍇ�{�N���X���p�����ăA�N�^�[�N���X����邱�ƂƂ���B<BR>
 * @version 1.00
 * @since 2008/03/24
 * @author Masatoshi Tsuge
 */
class MainActor : public Actor {

public:
    /** [r]���g����������O���[�v�̒c���̃V�[���`�[�t */
    SceneChief* _pSceneChief;

public:
    MainActor(const char* prm_name);

    virtual MainActor* getNext() const override { //���ϖ߂�l
        return (MainActor*)Actor::getNext();
    }

    virtual MainActor* getPrev() const override { //���ϖ߂�l
        return (MainActor*)Actor::getPrev();
    }

    void updateActiveInTheTree() override;

    /**
     * ���c���[�m�[�h��A�����X�g����؂藣���A�Ɨ�����B .
     * �؂藣���ꌊ���J���������́A����̃m�[�h�����𖄂߂܂��i�ĘA�����܂��j<BR>
     * ���m�[�h�Ɏq���Ԃ牺�����Ă����ꍇ�A�������؂藣���ꂽ���ƂɂȂ�܂��B<BR>
     * �z���� _pSceneChief �� nullptr ���Z�b�g�����B<BR>
     * @return  ���m�[�h�̃|�C���^
     */
    virtual MainActor* extract() override;

    /**
     * �V�[���`�[�t��ݒ肷��B .
     */
    virtual void setSceneChief(SceneChief* prm_pSceneChief);

    /**
     * �����V�[���̃V�[���`�[�t�擾�B�A���V�[���ɏ������Ă��Ȃ��ꍇ�́A���̐�(Spacetime)�̃V�[���`�[�t��Ԃ� .
     * @return �����V�[���`�[�t�̃`�[�t�B(���Ȃ��ꍇ ���̐�(Spacetime)�̃`�[�t)
     */
    SceneChief* getSceneChief();

    /**
     * �Ǘ��҂ɉy�� .
     * @return  �Ă΂�ďo�Ă����Ǘ���
     */
    virtual Caretaker* askCaretaker() override;

    /**
     * �j�󂳂ꂽ���Ƃ�ʒm .
     * �����V�[���ɂ��ʒm���� Scene::onDestroyedActor(Actor*) ���R�[���o�b�N���܂�
     */
    virtual void notifyDestroyed() override;

    virtual ~MainActor();
};

}
#endif /*GGAF_CORE_MAINACTOR_H_*/
