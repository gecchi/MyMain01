#ifndef GGAFLIB_WMKEYINPUT_H_
#define GGAFLIB_WMKEYINPUT_H_
#include "GgafLibCommonHeader.h"

#include <windows.h>

namespace GgafLib {


/**
 * ���z�{�^�� .
 * @version 1.00
 * @since 2018/09/28
 * @author Masatoshi Tsuge
 */
class WMKeyInput {

    /** ���݃A�N�e�B�u�ȓ��͏�Ԃ̕\��(0:�\�^1:��) */
    static int _flip;
    /** ���͏�ԁi�\�A���j */
    static int _input_char_state[2][256];
    static int _wm_char_state[256];
public:
    static void init();
    static void catchWmChar(WPARAM wParam);
    static void updateState();

    static inline bool isPressedKey(int prm_c) {
        return (_input_char_state[_flip][prm_c] == 1) ? true : false;
    }

    static inline int getPressedKey() {
        for (int i = 0; i < 256; i ++) {
            if (_input_char_state[_flip][i] == 1) {
                return i;
            }
        }
        return -1;
    }

    static bool isPushedDownKey(int prm_c);

    static int getPushedDownKey();
};

}
#endif /*GGAFLIB_WMKEYINPUT_H_*/
