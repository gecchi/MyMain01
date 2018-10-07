#ifndef GGAFLIB_WMKEYINPUT_H_
#define GGAFLIB_WMKEYINPUT_H_
#include "GgafLibCommonHeader.h"

#include <windows.h>

namespace GgafLib {


/**
 * �L�[���͎�t .
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

    /**
     * ������ .
     */
    static void init();

    /**
     * WM_CHAR�C�x���g���̏��� .
     * WINDOW�v���V�[�W�� �� WM_CHAR�C�x���g���L���b�`������
     * �{���\�b�h�����s���Ă��������B
     * @param wParam WINDOW�v���V�[�W�������� WPARAM wParam
     */
    static void catchWmChar(WPARAM wParam);

    /**
     * �L�[���͏�Ԃ̍X�V .
     * �A�v���P�[�V�������ŁA���t���[���Ăяo���Ă��������B
     */
    static void updateState();

    /**
     * �������̓L�[��������Ă��邩�𔻒� .
     * @param prm_c ���肷����͕����iASCII�R�[�h�j
     * @return true:�����̕������̓L�[��������Ă���^false:�����ł͂Ȃ��B
     */
    static inline bool isPressedKey(int prm_c) {
        return (_input_char_state[_flip][prm_c] == 1) ? true : false;
    }

    /**
     * �������̓L�[���������ꂽ���𔻒� .
     * @param prm_c ���肷����͕����iASCII�R�[�h�j
     * @return true:�����̕������̓L�[���������ꂽ�^false:�����ł͂Ȃ��B
     * @return
     */
    static bool isPushedDownKey(int prm_c);

    /**
     * ���݉�����Ă��镶�����̓L�[���擾 .
     * @param prm_num �����Ɏ擾����ő吔
     * @param prm_pa_char ���ʂ��i�[����z��Bprm_num�̗v�f���̔z���n�����ƁB
     * @return ���݉�����Ă��镶�����̓L�[�̐�
     */
    static inline int getPressedKey(int prm_num, int* prm_pa_char) {
        int n = 0;
        for (int i = 0; i < 256; i ++) {
            if (_input_char_state[_flip][i] == 1) {
                if (n < prm_num) {
                    prm_pa_char[n] = i;
                    n++;
                    continue;
                } else {
                    break;
                }
            }
        }
        return n;
    }

    /**
     * �������ꂽ�������̓L�[���擾 .
     * @param prm_num �����Ɏ擾����ő吔
     * @param prm_pa_char ���ʂ��i�[����z��Bprm_num�̗v�f���̔z���n�����ƁB
     * @return �������ꂽ�������̓L�[�̐�
     */
    static int getPushedDownKey(int prm_num, int* prm_pa_char);


};

}
#endif /*GGAFLIB_WMKEYINPUT_H_*/
