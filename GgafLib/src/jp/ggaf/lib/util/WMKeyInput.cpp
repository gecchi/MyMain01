#include "jp/ggaf/lib/util/WMKeyInput.h"

using namespace GgafLib;

int WMKeyInput::_input_char_state[2][256];
int WMKeyInput::_wm_char_state[256];
int WMKeyInput::_flip = 0;

void WMKeyInput::init() {
    for (int i = 0; i < 256; i++) {
        WMKeyInput::_input_char_state[0][i] = 0;
        WMKeyInput::_input_char_state[1][i] = 0;
        WMKeyInput::_wm_char_state[i] = 0;
    }
}

void WMKeyInput::catchWmChar(WPARAM wParam) {
    if (32 <= wParam && wParam <= 255) {
        WMKeyInput::_wm_char_state[wParam] = 1;
    }
}

void WMKeyInput::updateState() {
    WMKeyInput::_flip ^= 1;
    int* input_state = (int*)(&(WMKeyInput::_input_char_state[WMKeyInput::_flip]));
    int* wm_state = &WMKeyInput::_wm_char_state[0];
    for (int i = 0; i < 256; i++) {
        *input_state = *wm_state;
        *wm_state = 0;
        ++input_state;
        ++wm_state;
    }
}

bool WMKeyInput::isPushedDownKey(int prm_c) {
    if (WMKeyInput::isPressedKey(prm_c)) { //���͉����Ă���
        if (WMKeyInput::_input_char_state[!WMKeyInput::_flip][prm_c] == 1) {
            //�O��Z�b�g[!WMKeyInput::_flip]��������Ă���B�������ςȂ�
            return false;
        } else {
            //�O��Z�b�g[!WMKeyInput::_flip]�͉�����Ă��Ȃ��̂�OK
            return true;
        }
    } else {
        return false;
    }
}
int WMKeyInput::getPushedDownKey(int prm_num, int* prm_pa_char) {
    int pressed_num = WMKeyInput::getPressedKey(prm_num, prm_pa_char);
    int n = 0;
    for (int pressed_index = 0; pressed_index < pressed_num; pressed_index++) {
        if (WMKeyInput::_input_char_state[!WMKeyInput::_flip][prm_pa_char[pressed_index]] != 1) {
            //�O��Z�b�g[!GgafDx::Input::_flip_ks]�͉�����Ă��Ȃ��̂�OK
            if (n < prm_num) {
                prm_pa_char[n] = prm_pa_char[pressed_index];
                n++;
                continue;
            } else {
                break;
            }
        }
    }
    return n;
}

