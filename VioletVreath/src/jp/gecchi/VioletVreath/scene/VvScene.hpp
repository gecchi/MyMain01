#ifndef VVSCENE_H_
#define VVSCENE_H_
#include "VioletVreath.h"

#include "jp/ggaf/lib/actor/DefaultSceneMediator.h"
#include "jp/gecchi/VioletVreath/God.h"

namespace VioletVreath {

template<class T>
class VvScene : public T {

    /** ���t���[���ɂP�񓮍삷�邩 */
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
     * ���t���[���ɂP����s���邩���w�� .
     * �X���[�ɂ��������Ɏg�p���邱�Ƃ�z��B<BR>
     * �K���1�B���{�i�s�B��ʃV�[����1�t���[���ŁA���g��1�t���[���i�ށB<BR>
     * 2 ��ݒ肷��� 1/2�{���i�s�B��ʃV�[����2�t���[����1�t���[���i�ށB<BR>
     * 3 ��ݒ肷��� 1/3�{���i�s�B��ʃV�[����3�t���[����1�t���[���i�ށB<BR>
     * 4 ��ݒ肷��� 1/4�{���i�s�B��ʃV�[����4�t���[����1�t���[���i�ށB<BR>
     * @param prm_once_in_n_time ���t���[���ɂP����s���邩
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
