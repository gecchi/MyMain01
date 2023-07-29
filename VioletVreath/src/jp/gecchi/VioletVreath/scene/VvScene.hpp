#ifndef VVSCENE_H_
#define VVSCENE_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"

#include "jp/ggaf/lib/actor/DefaultSceneChief.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"

namespace VioletVreath {

template<class T>
class VvScene : public T {
public:
    /** [r]�V�[���C�x���g�p�̃t���[���l�̔z��(���u�V�[��Creater.xls�v�}�N���̐���PG�ɑg�ݍ��܂��j */
    frame* _paFrame_NextEvent;
    /** [r]�V�[���̃C�x���g���i_paFrame_NextEvent�̗v�f���j(���u�V�[��Creater.xls�v�}�N���̐���PG�ɑg�ݍ��܂��j */
    int _event_num;
    /** �V�[���̌��݃C�x���g(���u�V�[��Creater.xls�v�}�N���̐���PG�ɑg�ݍ��܂��j */
    int _cnt_event;

    /** ���t���[���ɂP�񓮍삷�邩 */
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

    /**
     * �Ō�̃V�[���C�x���g�t���[����Ԃ��܂��B
     * �V�[���C�x���g���Ȃ��ꍇ�� 0 ��Ԃ��B
     * @return �Ō�̃V�[���C�x���g�t���[��
     */
    frame getLastEventFrame() {
        if (_paFrame_NextEvent) {
            return _paFrame_NextEvent[_event_num-1];
        } else {
            return 0;
        }
    }

    virtual ~VvScene() {
        //�V�[���ɃC�x���g��������������Ȃ�
        GGAF_DELETEARR_NULLABLE(_paFrame_NextEvent);
    }
};

}

#endif /* VVSCENE_H_ */
