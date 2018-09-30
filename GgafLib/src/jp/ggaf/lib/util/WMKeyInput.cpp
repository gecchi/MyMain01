#include "jp/ggaf/lib/util/WMKeyInput.h"

using namespace GgafCore;
using namespace GgafDxCore;
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
    WMKeyInput::_flip = !WMKeyInput::_flip;
    int* input_state = (int*)(&(WMKeyInput::_input_char_state[_flip]));
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
int WMKeyInput::getPushedDownKey() {
    int pressed = WMKeyInput::getPressedKey();
    if (pressed >= 0) { //���͉����Ă���
        if (WMKeyInput::_input_char_state[!WMKeyInput::_flip][pressed] == 1) {
            //�O��Z�b�g[!WMKeyInput::_flip]��������Ă���B�������ςȂ�
            return -1;
        } else {
            //�O��Z�b�g[!GgafDxInput::_flip_ks]�͉�����Ă��Ȃ��̂�OK
            return pressed;
        }
    } else {
        return -1;
    }
}

