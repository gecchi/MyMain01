#ifndef GGAF_LIB_DEFAULTSCENE_H_
#define GGAF_LIB_DEFAULTSCENE_H_
#include "jp/ggaf/GgafLibCommonHeader.h"
#include "jp/ggaf/dx/scene/Scene.h"

#include "jp/ggaf/lib/util/ScenePhase.h"

namespace GgafLib {

/**
 * �V�[���̋�ۃN���X .
 * GgafDx::Scene ���p�����A�����������ۃV�[���ł��B
 * @version 1.00
 * @since 2007/12/06
 * @author Masatoshi Tsuge
 */
class DefaultScene : public GgafDx::Scene {

public:
    /** ���F�֐��p����1 */
    velo _feature_p1;
    /** [r/w]���F�֐��ւ̃|�C���^ */
    void (*_pFuncFeature)(GgafCore::Object*, void*, void*, void*);

public:
    DefaultScene(const char* prm_name, GgafCore::SceneMediator* prm_pSceneMediator = nullptr);

    virtual ScenePhase* createAnotherPhase() override; //���ϖ߂�l

    virtual ScenePhase* getPhase() const override; //���ϖ߂�l

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
     * ���F�����̒ǉ� .
     */
    virtual void processSettlementBehavior() override;

    virtual void processJudgement() override {
    }
    virtual void processDraw() override {
    }
    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {
    }


public:
    /**
     * ���F�֐���ݒ肷��B
     * �ݒ肳�ꂽ���F�֐���z���c���[�V�[���̑S�A�N�^�[�Ɏ��s���s���B<BR>
     * ��P�����ɂ́A�ΏۃA�N�^�[�A��Q�����ɂ́A���F�֐��p�����P(_feature_p1�ւ̃|�C���^)���n�����B<BR>
     * �V�[���� WallScene�̏ꍇ�Ɍ���A�W���� WallScene::scrollX(GgafCore::Object*, void*, void*, void*) ���ݒ肳��Ă���B<BR>
     * @param prm_pFuncFeature ������(GgafCore::Object*, void*, void*, void*) �ƂȂ�֐��|�C���^
     */
    void setFeatureFunction(void (*prm_pFuncFeature)(GgafCore::Object*, void*, void*, void*)) {
        _pFuncFeature = prm_pFuncFeature;
    }

    void setFeatureParam1(velo prm_feature_p1) {
        _feature_p1 = prm_feature_p1;
    }

    velo getFeatureParam1() const {
        return _feature_p1;
    }

    void addFeatureParam1(acce prm_acce) {
        _feature_p1 += prm_acce;
    }
    /**
     * �ł����߂̓��F�V�[����T���Ď擾�B .
     * �����͈͂� ���V�[���{�e�V�[���B
     * ���F�֐��|�C���^ _pFuncFeature �� nullptr �łȂ���΁A���F�Ɣ��f�B
     * @return ���߂̓��F�V�[���A������� nullptr
     */
    DefaultScene* getNearestFeatureScene();

    /**
     * �ł����߂� WallScene ��T���Ď擾�B .
     * �����͈͂� ���V�[���{�e�V�[���B
     * WallScene ��X���̕��̕����ɃX�N���[��������F�������ۏ؂���Ă���B
     * _pFuncFeature �� nullptr �ł��낤�ƂȂ��낤�ƁA�֌W�͂Ȃ��AWallScene �Ȃ�΂����Ԃ��B
     * @return ���߂�WallScene
     */
    WallScene* getNearestWallScene();

    virtual ~DefaultScene();
};

}
#endif /*GGAF_LIB_DEFAULTSCENE_H_*/
