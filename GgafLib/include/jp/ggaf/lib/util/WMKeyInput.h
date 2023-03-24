#ifndef GGAF_LIB_WMKEYINPUT_H_
#define GGAF_LIB_WMKEYINPUT_H_
#include "jp/ggaf/GgafLibCommonHeader.h"

#include <windows.h>

namespace GgafLib {


/**
 * キー入力受付 .
 * @version 1.00
 * @since 2018/09/28
 * @author Masatoshi Tsuge
 */
class WMKeyInput {

    /** 現在アクティブな入力状態の表裏(0:表／1:裏) */
    static int _flip;
    /** 入力状態（表、裏） */
    static int _input_char_state[2][256];
    static int _wm_char_state[256];
public:

    /**
     * 初期化 .
     */
    static void init();

    /**
     * WM_CHARイベント時の処理 .
     * WINDOWプロシージャ の WM_CHARイベントをキャッチした際
     * 本メソッドを実行してください。
     * @param wParam WINDOWプロシージャ引数の WPARAM wParam
     */
    static void catchWmChar(WPARAM wParam);

    /**
     * キー入力状態の更新 .
     * アプリケーション側で、毎フレーム呼び出してください。
     */
    static void updateState();

    /**
     * 文字入力キーが押されているかを判定 .
     * @param prm_c 判定する入力文字（ASCIIコード）
     * @return true:引数の文字入力キーが押されている／false:そうではない。
     */
    static inline bool isPressedKey(int prm_c) {
        return (_input_char_state[_flip][prm_c] == 1) ? true : false;
    }

    /**
     * 文字入力キーが押下されたかを判定 .
     * @param prm_c 判定する入力文字（ASCIIコード）
     * @return true:引数の文字入力キーが押下された／false:そうではない。
     * @return
     */
    static bool isPushedDownKey(int prm_c);

    /**
     * 現在押されている文字入力キーを取得 .
     * @param prm_num 同時に取得する最大数
     * @param prm_pa_char 結果を格納する配列。prm_numの要素数の配列を渡すこと。
     * @return 現在押されている文字入力キーの数
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
     * 押下された文字入力キーを取得 .
     * @param prm_num 同時に取得する最大数
     * @param prm_pa_char 結果を格納する配列。prm_numの要素数の配列を渡すこと。
     * @return 押下された文字入力キーの数
     */
    static int getPushedDownKey(int prm_num, int* prm_pa_char);


};

}
#endif /*GGAF_LIB_WMKEYINPUT_H_*/
