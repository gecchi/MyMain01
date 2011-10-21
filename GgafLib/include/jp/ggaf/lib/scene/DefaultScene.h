#ifndef DEFAULTSCENE_H_
#define DEFAULTSCENE_H_
namespace GgafLib {

/**
 * シーンの具象クラス .
 * GgafDxCore::GgafDxScene を継承し、空実装した具象シーンです。
 * @version 1.00
 * @since 2007/12/06
 * @author Masatoshi Tsuge
 */
class DefaultScene : public GgafDxCore::GgafDxScene {
public:

    /** シーンイベント用のフレーム値の配列(※「シーンCreater.xls」マクロの生成PGに組み込まれる） */
    UINT32* _paFrame_NextEvent;
    /** シーンのイベント数（_paFrame_NextEventの要素数）(※「シーンCreater.xls」マクロの生成PGに組み込まれる） */
    int _event_num;
    /** シーンの現在イベント(※「シーンCreater.xls」マクロの生成PGに組み込まれる） */
    int _iCnt_Event;
    /** シーン進捗管理(GgafElement<GgafScene>::GgafProgress* _pProg; をシャドー) */
    SceneProgress* _pProg;

    DefaultScene(const char* prm_name);

    void useProgress(int prm_num = 10) override;

    virtual void initialize() override {
    }

    /**
     * シーンをリセットし、再利用可能にする .
     * 下位で実装してください。
     */
    virtual void onReset() override {
    }

    virtual void processBehavior() override {
        TRACE("DefaultScene::processBehavior " << getName() << "frame:" << _frame_of_behaving);
    }

    virtual void processJudgement() override {
        TRACE("DefaultScene::processJudgement " << getName() << "frame:" << _frame_of_behaving);
    }

    virtual void processDraw() override {
        TRACE("DefaultScene::processJudgement " << getName() << "frame:" << _frame_of_behaving);
    }

    virtual void onCatchEvent(UINT32 prm_no, void* prm_pSource) override {
        TRACE("DefaultScene::catchEvent " << getName() << "no:" << prm_no);
    }

    virtual void processFinal() override {
        TRACE("DefaultScene::processFinally " << getName() << "frame:" << _frame_of_behaving);
    }

    virtual ~DefaultScene();
};

}
#endif /*DEFAULTSCENE_H_*/
