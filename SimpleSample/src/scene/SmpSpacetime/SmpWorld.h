#ifndef SMPWORLD_H_
#define SMPWORLD_H_
#include "SimpleSample.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"
#include "jp/ggaf/lib/actor/DefaultSceneMediator.h"

#include "jp/ggaf/lib/util/VirtualButton.h"

namespace SimpleSample {

/**
 * ���E�V�[���̐��` .
 * GgafLib::DefaultScene ���p�����ăV�[���N���X���쐬���ĉ������B<BR>
 * �{�T���v���ł́u���E�v�V�[���Ɩ��Â��܂����B<BR>
 * processBehavior() ���I�[�o�[���C�h���A���t���[���̏������L�q���܂��B<BR>
 * @version 1.00
 * @since 2012/02/16
 * @author Masatoshi Tsuge
 */
class SmpWorld : public GgafLib::DefaultScene {

public:
    /**
     * �V�[���ƃA�N�^�[�̒���� .
     */
    class Mediator : public GgafLib::DefaultSceneMediator {
    public:
        /** ���z�{�^���I�u�W�F�N�g */
        GgafLib::VirtualButton vb_;

        /**
         * �R���X�g���N�^
         * @param prm_pSmpWorld
         * @return
         */
        Mediator(SmpWorld* prm_pSmpWorld) : GgafLib::DefaultSceneMediator(prm_pSmpWorld) {
            vb_.remap(VB_UP     , VBK_UP   , VBJ_Y_POS_MINUS);  //VB_UP      = �L�[�{�[�h�� �܂��́AY���| �Ƃ���B
            vb_.remap(VB_DOWN   , VBK_DOWN , VBJ_Y_POS_PLUS );  //VB_DOWN    = �L�[�{�[�h�� �܂��́AY���{ �Ƃ���B
            vb_.remap(VB_LEFT   , VBK_LEFT , VBJ_X_POS_MINUS);  //VB_LEFT    = �L�[�{�[�h�� �܂��́AX���| �Ƃ���B
            vb_.remap(VB_RIGHT  , VBK_RIGHT, VBJ_X_POS_PLUS );  //VB_RIGHT   = �L�[�{�[�h�� �܂��́AX���{ �Ƃ���B
            vb_.remap(VB_BUTTON1, VBK_SPACE, VBJ_BUTTON_01  );  //VB_BUTTON1 = �X�y�[�X�L�[ �܂��� �W���C�X�e�B�b�N�{�^���P �Ƃ���B
        }

        void initialize() override {
        }

        void processBehavior() override {
            vb_.update();
        }

        /**
         * ���z�{�^���I�u�W�F�N�g��Ԃ� .
         * @return ���z�{�^��
         */
        GgafLib::VirtualButton* getVB() {
            return &vb_;
        }

        virtual ~Mediator() {
        }
    };

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name ����
     */
    SmpWorld(const char* prm_name);

    /**
     * ���E�V�[���̏������� .
     */
    void initialize() override;

    /**
     * ���E�V�[���̐U�镑������ .
     */
    void processBehavior() override;

    virtual ~SmpWorld();
};

}
#endif /*SMPWORLD_H_*/
