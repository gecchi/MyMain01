#ifndef VVSCENE_H_
#define VVSCENE_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"

#include "jp/ggaf/lib/actor/DefaultSceneChief.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"

namespace VioletVreath {

template<class T>
class VvScene : public T {
public:
    /** [r]シーンイベント用のフレーム値の配列(※「シーンCreater.xls」マクロの生成PGに組み込まれる） */
    frame* _paFrame_NextEvent;
    /** [r]シーンのイベント数（_paFrame_NextEventの要素数）(※「シーンCreater.xls」マクロの生成PGに組み込まれる） */
    int _event_num;
    /** シーンの現在イベント(※「シーンCreater.xls」マクロの生成PGに組み込まれる） */
    int _cnt_event;

    /** 何フレームに１回動作するか */
    frame _once_in_n_time;
    bool _is_next_frame;

public:
    VvScene(const char* prm_name, GgafCore::SceneChief* prm_pSceneChief = nullptr) : T(prm_name, prm_pSceneChief) {

        _paFrame_NextEvent = nullptr;
        _cnt_event = 0;
        _event_num = 0;

        _once_in_n_time = 1;
        _is_next_frame = true;
    }
    void nextFrame() override {
        _is_next_frame = (_once_in_n_time == 1 || pCARETAKER->_frame_of_Caretaker % _once_in_n_time == 0);
        if (_is_next_frame) {
            T::nextFrame();
        }
    }

    void behave() override {
        if (_is_next_frame) {
            T::behave();
        }
    }

    void settleBehavior() override {
        if (_is_next_frame) {
            T::settleBehavior();
        }
    }

    void resetTree() override {
        _once_in_n_time = 1;
        T::resetTree();
    }

    void reset() override {
        _once_in_n_time = 1;
        T::reset();
    }

    /**
     * 何フレームに１回実行するかを指定 .
     * スローにしたい時に使用することを想定。<BR>
     * 規定は1。等倍進行。上位シーンの1フレームで、自身が1フレーム進む。<BR>
     * 2 を設定すると 1/2倍速進行。上位シーンの2フレームで1フレーム進む。<BR>
     * 3 を設定すると 1/3倍速進行。上位シーンの3フレームで1フレーム進む。<BR>
     * 4 を設定すると 1/4倍速進行。上位シーンの4フレームで1フレーム進む。<BR>
     * @param prm_once_in_n_time 何フレームに１回実行するか
     */
    void setRunFrameOnce(int prm_once_in_n_time) {
        if (prm_once_in_n_time <= 1) {
            _once_in_n_time = 1;
        } else {
            _once_in_n_time = prm_once_in_n_time;
        }
    }
    void addRunFrameOnce(int prm_once_in_n_time) {
        if ((int)_once_in_n_time + prm_once_in_n_time <= 1) {
            _once_in_n_time = 1;
        } else {
            _once_in_n_time += prm_once_in_n_time;
        }
    }

    /**
     * 最後のシーンイベントフレームを返します。
     * シーンイベントがない場合は 0 を返す。
     * @return 最後のシーンイベントフレーム
     */
    frame getLastEventFrame() {
        if (_paFrame_NextEvent) {
            return _paFrame_NextEvent[_event_num-1];
        } else {
            return 0;
        }
    }

    virtual ~VvScene() {
        //シーンにイベントが無いかもしれない
        GGAF_DELETEARR_NULLABLE(_paFrame_NextEvent);
    }
};

}

#endif /* VVSCENE_H_ */
