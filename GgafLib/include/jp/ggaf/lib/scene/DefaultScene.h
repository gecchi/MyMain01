#ifndef GGAFLIB_DEFAULTSCENE_H_
#define GGAFLIB_DEFAULTSCENE_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dxcore/scene/GgafDxScene.h"

#include "jp/ggaf/lib/util/SceneProgress.h"

namespace GgafLib {

/**
 * �V�[���̋�ۃN���X .
 * GgafDxCore::GgafDxScene ���p�����A�����������ۃV�[���ł��B
 * @version 1.00
 * @since 2007/12/06
 * @author Masatoshi Tsuge
 */
class DefaultScene : public GgafDxCore::GgafDxScene {

public:
    /** [r]�V�[���C�x���g�p�̃t���[���l�̔z��(���u�V�[��Creater.xls�v�}�N���̐���PG�ɑg�ݍ��܂��j */
    frame* _paFrame_NextEvent;
    /** [r]�V�[���̃C�x���g���i_paFrame_NextEvent�̗v�f���j(���u�V�[��Creater.xls�v�}�N���̐���PG�ɑg�ݍ��܂��j */
    int _event_num;
    /** �V�[���̌��݃C�x���g(���u�V�[��Creater.xls�v�}�N���̐���PG�ɑg�ݍ��܂��j */
    int _cnt_event;

    /** �X�N���[�����x */
    velo _scroll_speed;
    /** [r/w]�X�N���[���֐��ւ̃|�C���^ */
    void (*_pFuncScrolling)(GgafCore::GgafObject*, void*, void*);

public:
    DefaultScene(const char* prm_name, GgafCore::GgafSceneMediator* prm_pSceneMediator = nullptr);

    virtual void useProgress(int prm_num = 10) override;

    virtual SceneProgress* createProgress(int prm_num = 10) override; //���ϖ߂�l

    virtual SceneProgress* getProgress() const override; //���ϖ߂�l

    virtual void initialize() override {
    }

    /**
     * �V�[�������Z�b�g���A�ė��p�\�ɂ��� .
     * ���ʂŎ������Ă��������B
     */
    virtual void onReset() override {
    }

    virtual void processBehavior() override {
    }
    /**
     * �X�N���[�������̒ǉ� .
     */
    virtual void processSettlementBehavior() override;

    virtual void processJudgement() override {
    }

    virtual void processDraw() override {
    }

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }


public:

    /**
     * �X�N���[���֐���ݒ肷��B
     * �ݒ肳�ꂽ�X�N���[���֐���z���c���[�V�[���̑S�A�N�^�[�Ɏ��s���s���B<BR>
     * ��P�����ɂ́A�ΏۃA�N�^�[�A��Q�����ɂ́A�X�N���[���X�s�[�h(_scroll_speed�ւ̃|�C���^)���n�����B<BR>
     * �V�[���� WalledScene�̏ꍇ�Ɍ���A�W���� WalledScene::scrollX(GgafObject*, void*, void*) ���ݒ肳��Ă���B<BR>
     * @param prm_pFuncScrolling ������(GgafObject*, void*, void*) �ƂȂ�֐��|�C���^
     */
    void setScrollingFunction(void (*prm_pFuncScrolling)(GgafCore::GgafObject*, void*, void*)) {
        _pFuncScrolling = prm_pFuncScrolling;
    }

    void setScrollSpeed(velo prm_scroll_speed) {
        _scroll_speed = prm_scroll_speed;
    }

    velo getScrollSpeed() const {
        return _scroll_speed;
    }

    void addScrollSpeed(acce prm_acce) {
        _scroll_speed += prm_acce;
    }
    /**
     * �ł����߂̃X�N���[�����Ă���V�[����T���Ď擾�B .
     * �����͈͂� ���V�[���{�e�V�[���B
     * �X�N���[���֐��|�C���^ _pFuncScrolling �� nullptr �łȂ���΁A�X�N���[�����Ă���Ɣ��f�B
     * @return ���߂̃X�N���[�����Ă���V�[���A������� nullptr
     */
    DefaultScene* getNearestScrollingScene();

    /**
     * �ł����߂� WallScene ��T���Ď擾�B .
     * �����͈͂� ���V�[���{�e�V�[���B
     * WallScene ��X���̕��̕����X�N���[�����Ă��邱�Ƃ������ۏ؂���Ă���B
     * _pFuncScrolling �� nullptr �ł��낤�ƂȂ��낤�ƁA�֌W�͂Ȃ��AWallScene �Ȃ�΂����Ԃ��B
     * @return ���߂�WallScene
     */
    WallScene* getNearestWallScene();

    virtual ~DefaultScene();
};

}
#endif /*GGAFLIB_DEFAULTSCENE_H_*/
