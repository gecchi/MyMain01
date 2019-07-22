#ifndef VVSCENE_H_
#define VVSCENE_H_
#include "VioletVreath.h"

#include "jp/ggaf/lib/actor/DefaultSceneMediator.h"
#include "jp/gecchi/VioletVreath/God.h"

namespace VioletVreath {

template<class T>
class VvScene : public T {

    /** 何フレームに１回動作するか */
    frame _once_in_n_time;
    bool _is_next_frame;

public:
    VvScene(const char* prm_name, GgafCore::SceneMediator* prm_pSceneMediator = nullptr) : T(prm_name, prm_pSceneMediator) {
        _once_in_n_time = 1;
        _is_next_frame = true;
    }
    void nextFrame() {
        _is_next_frame = (_once_in_n_time == 1 || pGOD->_frame_of_God % _once_in_n_time == 0);
        if (_is_next_frame) {
            T::nextFrame();
        }
    }
    void behave() {
        if (_is_next_frame) {
            T::behave();
        }
    }

    void settleBehavior() {
        if (_is_next_frame) {
            T::settleBehavior();
        }
    }
    void resetTree() {
        _once_in_n_time = 1;
        T::resetTree();
    }

    void reset() {
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
    virtual ~VvScene() {
    }
};

}

#endif /* VVSCENE_H_ */
