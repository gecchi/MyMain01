#ifndef GGAF_LIB_VIRTUALBUTTON_H_
#define GGAF_LIB_VIRTUALBUTTON_H_
#include "jp/ggaf/GgafLibCommonHeader.h"
#include "jp/ggaf/core/Object.h"

#include <string>
#include <map>
#include "jp/ggaf/dx/util/Input.h"

typedef int_fast32_t vbk;
typedef int_fast32_t vbj;
typedef int_fast32_t vbj_base;
typedef uint64_t vb_sta;

namespace GgafLib {

#define VBK_ESCAPE          DIK_ESCAPE
#define VBK_1               DIK_1
#define VBK_2               DIK_2
#define VBK_3               DIK_3
#define VBK_4               DIK_4
#define VBK_5               DIK_5
#define VBK_6               DIK_6
#define VBK_7               DIK_7
#define VBK_8               DIK_8
#define VBK_9               DIK_9
#define VBK_0               DIK_0
#define VBK_MINUS           DIK_MINUS
#define VBK_EQUALS          DIK_EQUALS
#define VBK_BACK            DIK_BACK
#define VBK_TAB             DIK_TAB
#define VBK_Q               DIK_Q
#define VBK_W               DIK_W
#define VBK_E               DIK_E
#define VBK_R               DIK_R
#define VBK_T               DIK_T
#define VBK_Y               DIK_Y
#define VBK_U               DIK_U
#define VBK_I               DIK_I
#define VBK_O               DIK_O
#define VBK_P               DIK_P
#define VBK_LBRACKET        DIK_LBRACKET
#define VBK_RBRACKET        DIK_RBRACKET
#define VBK_RETURN          DIK_RETURN
#define VBK_LCONTROL        DIK_LCONTROL
#define VBK_A               DIK_A
#define VBK_S               DIK_S
#define VBK_D               DIK_D
#define VBK_F               DIK_F
#define VBK_G               DIK_G
#define VBK_H               DIK_H
#define VBK_J               DIK_J
#define VBK_K               DIK_K
#define VBK_L               DIK_L
#define VBK_SEMICOLON       DIK_SEMICOLON
#define VBK_APOSTROPHE      DIK_APOSTROPHE
#define VBK_GRAVE           DIK_GRAVE
#define VBK_LSHIFT          DIK_LSHIFT
#define VBK_BACKSLASH       DIK_BACKSLASH
#define VBK_Z               DIK_Z
#define VBK_X               DIK_X
#define VBK_C               DIK_C
#define VBK_V               DIK_V
#define VBK_B               DIK_B
#define VBK_N               DIK_N
#define VBK_M               DIK_M
#define VBK_COMMA           DIK_COMMA
#define VBK_PERIOD          DIK_PERIOD
#define VBK_SLASH           DIK_SLASH
#define VBK_RSHIFT          DIK_RSHIFT
#define VBK_MULTIPLY        DIK_MULTIPLY
#define VBK_LMENU           DIK_LMENU
#define VBK_SPACE           DIK_SPACE
#define VBK_CAPITAL         DIK_CAPITAL
#define VBK_F1              DIK_F1
#define VBK_F2              DIK_F2
#define VBK_F3              DIK_F3
#define VBK_F4              DIK_F4
#define VBK_F5              DIK_F5
#define VBK_F6              DIK_F6
#define VBK_F7              DIK_F7
#define VBK_F8              DIK_F8
#define VBK_F9              DIK_F9
#define VBK_F10             DIK_F10
#define VBK_NUMLOCK         DIK_NUMLOCK
#define VBK_SCROLL          DIK_SCROLL
#define VBK_NUMPAD7         DIK_NUMPAD7
#define VBK_NUMPAD8         DIK_NUMPAD8
#define VBK_NUMPAD9         DIK_NUMPAD9
#define VBK_SUBTRACT        DIK_SUBTRACT
#define VBK_NUMPAD4         DIK_NUMPAD4
#define VBK_NUMPAD5         DIK_NUMPAD5
#define VBK_NUMPAD6         DIK_NUMPAD6
#define VBK_ADD             DIK_ADD
#define VBK_NUMPAD1         DIK_NUMPAD1
#define VBK_NUMPAD2         DIK_NUMPAD2
#define VBK_NUMPAD3         DIK_NUMPAD3
#define VBK_NUMPAD0         DIK_NUMPAD0
#define VBK_DECIMAL         DIK_DECIMAL
#define VBK_OEM_102         DIK_OEM_102
#define VBK_F11             DIK_F11
#define VBK_F12             DIK_F12
#define VBK_F13             DIK_F13
#define VBK_F14             DIK_F14
#define VBK_F15             DIK_F15
#define VBK_KANA            DIK_KANA
#define VBK_ABNT_C1         DIK_ABNT_C1
#define VBK_CONVERT         DIK_CONVERT
#define VBK_NOCONVERT       DIK_NOCONVERT
#define VBK_YEN             DIK_YEN
#define VBK_ABNT_C2         DIK_ABNT_C2
#define VBK_NUMPADEQUALS    DIK_NUMPADEQUALS
#define VBK_PREVTRACK       DIK_PREVTRACK
#define VBK_AT              DIK_AT
#define VBK_COLON           DIK_COLON
#define VBK_UNDERLINE       DIK_UNDERLINE
#define VBK_KANJI           DIK_KANJI
#define VBK_STOP            DIK_STOP
#define VBK_AX              DIK_AX
#define VBK_UNLABELED       DIK_UNLABELED
#define VBK_NEXTTRACK       DIK_NEXTTRACK
#define VBK_NUMPADENTER     DIK_NUMPADENTER
#define VBK_RCONTROL        DIK_RCONTROL
#define VBK_MUTE            DIK_MUTE
#define VBK_CALCULATOR      DIK_CALCULATOR
#define VBK_PLAYPAUSE       DIK_PLAYPAUSE
#define VBK_MEDIASTOP       DIK_MEDIASTOP
#define VBK_VOLUMEDOWN      DIK_VOLUMEDOWN
#define VBK_VOLUMEUP        DIK_VOLUMEUP
#define VBK_WEBHOME         DIK_WEBHOME
#define VBK_NUMPADCOMMA     DIK_NUMPADCOMMA
#define VBK_DIVIDE          DIK_DIVIDE
#define VBK_SYSRQ           DIK_SYSRQ
#define VBK_RMENU           DIK_RMENU
#define VBK_PAUSE           DIK_PAUSE
#define VBK_HOME            DIK_HOME
#define VBK_UP              DIK_UP
#define VBK_PRIOR           DIK_PRIOR
#define VBK_LEFT            DIK_LEFT
#define VBK_RIGHT           DIK_RIGHT
#define VBK_END             DIK_END
#define VBK_DOWN            DIK_DOWN
#define VBK_NEXT            DIK_NEXT
#define VBK_INSERT          DIK_INSERT
#define VBK_DELETE          DIK_DELETE
#define VBK_LWIN            DIK_LWIN
#define VBK_RWIN            DIK_RWIN
#define VBK_APPS            DIK_APPS
#define VBK_POWER           DIK_POWER
#define VBK_SLEEP           DIK_SLEEP
#define VBK_WAKE            DIK_WAKE
#define VBK_WEBSEARCH       DIK_WEBSEARCH
#define VBK_WEBFAVORITES    DIK_WEBFAVORITES
#define VBK_WEBREFRESH      DIK_WEBREFRESH
#define VBK_WEBSTOP         DIK_WEBSTOP
#define VBK_WEBFORWARD      DIK_WEBFORWARD
#define VBK_WEBBACK         DIK_WEBBACK
#define VBK_MYCOMPUTER      DIK_MYCOMPUTER
#define VBK_MAIL            DIK_MAIL
#define VBK_MEDIASELECT     DIK_MEDIASELECT

#define VBK_BACKSPACE       DIK_BACKSPACE
#define VBK_NUMPADSTAR      DIK_NUMPADSTAR
#define VBK_LALT            DIK_LALT
#define VBK_CAPSLOCK        DIK_CAPSLOCK
#define VBK_NUMPADMINUS     DIK_NUMPADMINUS
#define VBK_NUMPADPLUS      DIK_NUMPADPLUS
#define VBK_NUMPADPERIOD    DIK_NUMPADPERIOD
#define VBK_NUMPADSLASH     DIK_NUMPADSLASH
#define VBK_RALT            DIK_RALT
#define VBK_UPARROW         DIK_UPARROW
#define VBK_PGUP            DIK_PGUP
#define VBK_LEFTARROW       DIK_LEFTARROW
#define VBK_RIGHTARROW      DIK_RIGHTARROW
#define VBK_DOWNARROW       DIK_DOWNARROW
#define VBK_PGDN            DIK_PGDN



#define VBJ_BASE_BUTTON_01       (0x01)
#define VBJ_BASE_BUTTON_02       (0x02)
#define VBJ_BASE_BUTTON_03       (0x03)
#define VBJ_BASE_BUTTON_04       (0x04)
#define VBJ_BASE_BUTTON_05       (0x05)
#define VBJ_BASE_BUTTON_06       (0x06)
#define VBJ_BASE_BUTTON_07       (0x07)
#define VBJ_BASE_BUTTON_08       (0x08)
#define VBJ_BASE_BUTTON_09       (0x09)
#define VBJ_BASE_BUTTON_10       (0x0A)
#define VBJ_BASE_BUTTON_11       (0x0B)
#define VBJ_BASE_BUTTON_12       (0x0C)
#define VBJ_BASE_BUTTON_13       (0x0D)
#define VBJ_BASE_BUTTON_14       (0x0E)
#define VBJ_BASE_BUTTON_15       (0x0F)
#define VBJ_BASE_BUTTON_16       (0x10)
#define VBJ_BASE_BUTTON_MAX      (0x10) //rgbボタン番兵

#define VBJ_BASE_X_POS_MINUS     (0x80)
#define VBJ_BASE_X_POS_PLUS      (0x81)
#define VBJ_BASE_Y_POS_MINUS     (0x82)
#define VBJ_BASE_Y_POS_PLUS      (0x83)
#define VBJ_BASE_Z_POS_MINUS     (0x84)
#define VBJ_BASE_Z_POS_PLUS      (0x85)
#define VBJ_BASE_X_ROT_MINUS     (0x86)
#define VBJ_BASE_X_ROT_PLUS      (0x87)
#define VBJ_BASE_Y_ROT_MINUS     (0x88)
#define VBJ_BASE_Y_ROT_PLUS      (0x89)
#define VBJ_BASE_Z_ROT_MINUS     (0x8A)
#define VBJ_BASE_Z_ROT_PLUS      (0x8B)
#define VBJ_BASE_POV_UP          (0x8C)
#define VBJ_BASE_POV_DOWN        (0x8D)
#define VBJ_BASE_POV_LEFT        (0x8E)
#define VBJ_BASE_POV_RIGHT       (0x8F)

#define VBJ_P1                  (0x0000)
#define VBJ_P2                  (0x1000)

#define VBJ_P1_BUTTON_01       (VBJ_P1 | VBJ_BASE_BUTTON_01   )
#define VBJ_P1_BUTTON_02       (VBJ_P1 | VBJ_BASE_BUTTON_02   )
#define VBJ_P1_BUTTON_03       (VBJ_P1 | VBJ_BASE_BUTTON_03   )
#define VBJ_P1_BUTTON_04       (VBJ_P1 | VBJ_BASE_BUTTON_04   )
#define VBJ_P1_BUTTON_05       (VBJ_P1 | VBJ_BASE_BUTTON_05   )
#define VBJ_P1_BUTTON_06       (VBJ_P1 | VBJ_BASE_BUTTON_06   )
#define VBJ_P1_BUTTON_07       (VBJ_P1 | VBJ_BASE_BUTTON_07   )
#define VBJ_P1_BUTTON_08       (VBJ_P1 | VBJ_BASE_BUTTON_08   )
#define VBJ_P1_BUTTON_09       (VBJ_P1 | VBJ_BASE_BUTTON_09   )
#define VBJ_P1_BUTTON_10       (VBJ_P1 | VBJ_BASE_BUTTON_10   )
#define VBJ_P1_BUTTON_11       (VBJ_P1 | VBJ_BASE_BUTTON_11   )
#define VBJ_P1_BUTTON_12       (VBJ_P1 | VBJ_BASE_BUTTON_12   )
#define VBJ_P1_BUTTON_13       (VBJ_P1 | VBJ_BASE_BUTTON_13   )
#define VBJ_P1_BUTTON_14       (VBJ_P1 | VBJ_BASE_BUTTON_14   )
#define VBJ_P1_BUTTON_15       (VBJ_P1 | VBJ_BASE_BUTTON_15   )
#define VBJ_P1_BUTTON_16       (VBJ_P1 | VBJ_BASE_BUTTON_16   )
#define VBJ_P1_BUTTON_MAX      (VBJ_P1 | VBJ_BASE_BUTTON_MAX  )
#define VBJ_P1_X_POS_MINUS     (VBJ_P1 | VBJ_BASE_X_POS_MINUS )
#define VBJ_P1_X_POS_PLUS      (VBJ_P1 | VBJ_BASE_X_POS_PLUS  )
#define VBJ_P1_Y_POS_MINUS     (VBJ_P1 | VBJ_BASE_Y_POS_MINUS )
#define VBJ_P1_Y_POS_PLUS      (VBJ_P1 | VBJ_BASE_Y_POS_PLUS  )
#define VBJ_P1_Z_POS_MINUS     (VBJ_P1 | VBJ_BASE_Z_POS_MINUS )
#define VBJ_P1_Z_POS_PLUS      (VBJ_P1 | VBJ_BASE_Z_POS_PLUS  )
#define VBJ_P1_X_ROT_MINUS     (VBJ_P1 | VBJ_BASE_X_ROT_MINUS )
#define VBJ_P1_X_ROT_PLUS      (VBJ_P1 | VBJ_BASE_X_ROT_PLUS  )
#define VBJ_P1_Y_ROT_MINUS     (VBJ_P1 | VBJ_BASE_Y_ROT_MINUS )
#define VBJ_P1_Y_ROT_PLUS      (VBJ_P1 | VBJ_BASE_Y_ROT_PLUS  )
#define VBJ_P1_Z_ROT_MINUS     (VBJ_P1 | VBJ_BASE_Z_ROT_MINUS )
#define VBJ_P1_Z_ROT_PLUS      (VBJ_P1 | VBJ_BASE_Z_ROT_PLUS  )
#define VBJ_P1_POV_UP          (VBJ_P1 | VBJ_BASE_POV_UP      )
#define VBJ_P1_POV_DOWN        (VBJ_P1 | VBJ_BASE_POV_DOWN    )
#define VBJ_P1_POV_LEFT        (VBJ_P1 | VBJ_BASE_POV_LEFT    )
#define VBJ_P1_POV_RIGHT       (VBJ_P1 | VBJ_BASE_POV_RIGHT   )

#define VBJ_P2_BUTTON_01       (VBJ_P2 | VBJ_BASE_BUTTON_01   )
#define VBJ_P2_BUTTON_02       (VBJ_P2 | VBJ_BASE_BUTTON_02   )
#define VBJ_P2_BUTTON_03       (VBJ_P2 | VBJ_BASE_BUTTON_03   )
#define VBJ_P2_BUTTON_04       (VBJ_P2 | VBJ_BASE_BUTTON_04   )
#define VBJ_P2_BUTTON_05       (VBJ_P2 | VBJ_BASE_BUTTON_05   )
#define VBJ_P2_BUTTON_06       (VBJ_P2 | VBJ_BASE_BUTTON_06   )
#define VBJ_P2_BUTTON_07       (VBJ_P2 | VBJ_BASE_BUTTON_07   )
#define VBJ_P2_BUTTON_08       (VBJ_P2 | VBJ_BASE_BUTTON_08   )
#define VBJ_P2_BUTTON_09       (VBJ_P2 | VBJ_BASE_BUTTON_09   )
#define VBJ_P2_BUTTON_10       (VBJ_P2 | VBJ_BASE_BUTTON_10   )
#define VBJ_P2_BUTTON_11       (VBJ_P2 | VBJ_BASE_BUTTON_11   )
#define VBJ_P2_BUTTON_12       (VBJ_P2 | VBJ_BASE_BUTTON_12   )
#define VBJ_P2_BUTTON_13       (VBJ_P2 | VBJ_BASE_BUTTON_13   )
#define VBJ_P2_BUTTON_14       (VBJ_P2 | VBJ_BASE_BUTTON_14   )
#define VBJ_P2_BUTTON_15       (VBJ_P2 | VBJ_BASE_BUTTON_15   )
#define VBJ_P2_BUTTON_16       (VBJ_P2 | VBJ_BASE_BUTTON_16   )
#define VBJ_P2_BUTTON_MAX      (VBJ_P2 | VBJ_BASE_BUTTON_MAX  )
#define VBJ_P2_X_POS_MINUS     (VBJ_P2 | VBJ_BASE_X_POS_MINUS )
#define VBJ_P2_X_POS_PLUS      (VBJ_P2 | VBJ_BASE_X_POS_PLUS  )
#define VBJ_P2_Y_POS_MINUS     (VBJ_P2 | VBJ_BASE_Y_POS_MINUS )
#define VBJ_P2_Y_POS_PLUS      (VBJ_P2 | VBJ_BASE_Y_POS_PLUS  )
#define VBJ_P2_Z_POS_MINUS     (VBJ_P2 | VBJ_BASE_Z_POS_MINUS )
#define VBJ_P2_Z_POS_PLUS      (VBJ_P2 | VBJ_BASE_Z_POS_PLUS  )
#define VBJ_P2_X_ROT_MINUS     (VBJ_P2 | VBJ_BASE_X_ROT_MINUS )
#define VBJ_P2_X_ROT_PLUS      (VBJ_P2 | VBJ_BASE_X_ROT_PLUS  )
#define VBJ_P2_Y_ROT_MINUS     (VBJ_P2 | VBJ_BASE_Y_ROT_MINUS )
#define VBJ_P2_Y_ROT_PLUS      (VBJ_P2 | VBJ_BASE_Y_ROT_PLUS  )
#define VBJ_P2_Z_ROT_MINUS     (VBJ_P2 | VBJ_BASE_Z_ROT_MINUS )
#define VBJ_P2_Z_ROT_PLUS      (VBJ_P2 | VBJ_BASE_Z_ROT_PLUS  )
#define VBJ_P2_POV_UP          (VBJ_P2 | VBJ_BASE_POV_UP      )
#define VBJ_P2_POV_DOWN        (VBJ_P2 | VBJ_BASE_POV_DOWN    )
#define VBJ_P2_POV_LEFT        (VBJ_P2 | VBJ_BASE_POV_LEFT    )
#define VBJ_P2_POV_RIGHT       (VBJ_P2 | VBJ_BASE_POV_RIGHT   )


#define VBJ_P_MASK       (0xF000)
#define VBJ_BUTTON_MASK  (0x0FFF)

#define BASE_TO_VBJ(P_N, VBJ_BASE) ( (VBJ_BASE) | ((P_N) << 12 )  )
#define VBJ_TO_BASE(VBJ)         ( (VBJ) & (VBJ_BUTTON_MASK) )
/** P1/P2 を取得   1:P1 / 2:P2   */
#define VBJ_TO_P_N(VBJ)         ( ( (VBJ) & (VBJ_P_MASK) ) >> 12 )

#define RGB_BUTTON_TO_VBJ_BASE_BUTTON(RGB_B) ((RGB_B) + 1)

#define VB_BUTTON1                (0x1ULL) //&B 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000001
#define VB_BUTTON2                (0x2ULL) //&B 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000010
#define VB_BUTTON3                (0x4ULL) //&B 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000100
#define VB_BUTTON4                (0x8ULL) //&B 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00001000
#define VB_BUTTON5               (0x10ULL) //&B 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00010000
#define VB_BUTTON6               (0x20ULL) //&B 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00100000
#define VB_BUTTON7               (0x40ULL) //&B 00000000 00000000 00000000 00000000 00000000 00000000 00000000 01000000
#define VB_BUTTON8               (0x80ULL) //&B 00000000 00000000 00000000 00000000 00000000 00000000 00000000 10000000
#define VB_BUTTON9              (0x100ULL) //&B 00000000 00000000 00000000 00000000 00000000 00000000 00000001 00000000
#define VB_BUTTON10             (0x200ULL) //&B 00000000 00000000 00000000 00000000 00000000 00000000 00000010 00000000
#define VB_BUTTON11             (0x400ULL) //&B 00000000 00000000 00000000 00000000 00000000 00000000 00000100 00000000
#define VB_BUTTON12             (0x800ULL) //&B 00000000 00000000 00000000 00000000 00000000 00000000 00001000 00000000
#define VB_BUTTON13            (0x1000ULL) //&B 00000000 00000000 00000000 00000000 00000000 00000000 00010000 00000000
#define VB_BUTTON14            (0x2000ULL) //&B 00000000 00000000 00000000 00000000 00000000 00000000 00100000 00000000
#define VB_BUTTON15            (0x4000ULL) //&B 00000000 00000000 00000000 00000000 00000000 00000000 01000000 00000000
#define VB_BUTTON16            (0x8000ULL) //&B 00000000 00000000 00000000 00000000 00000000 00000000 10000000 00000000
#define VB_PAUSE              (0x10000ULL) //&B 00000000 00000000 00000000 00000000 00000000 00000001 00000000 00000000
#define VB_UP                 (0x20000ULL) //&B 00000000 00000000 00000000 00000000 00000000 00000010 00000000 00000000
#define VB_DOWN               (0x40000ULL) //&B 00000000 00000000 00000000 00000000 00000000 00000100 00000000 00000000
#define VB_LEFT               (0x80000ULL) //&B 00000000 00000000 00000000 00000000 00000000 00001000 00000000 00000000
#define VB_RIGHT             (0x100000ULL) //&B 00000000 00000000 00000000 00000000 00000000 00010000 00000000 00000000
#define VB_S1_UP             (0x200000ULL) //&B 00000000 00000000 00000000 00000000 00000000 00100000 00000000 00000000
#define VB_S1_DOWN           (0x400000ULL) //&B 00000000 00000000 00000000 00000000 00000000 01000000 00000000 00000000
#define VB_S1_LEFT           (0x800000ULL) //&B 00000000 00000000 00000000 00000000 00000000 10000000 00000000 00000000
#define VB_S1_RIGHT         (0x1000000ULL) //&B 00000000 00000000 00000000 00000000 00000001 00000000 00000000 00000000
#define VB_S2_UP            (0x2000000ULL) //&B 00000000 00000000 00000000 00000000 00000010 00000000 00000000 00000000
#define VB_S2_DOWN          (0x4000000ULL) //&B 00000000 00000000 00000000 00000000 00000100 00000000 00000000 00000000
#define VB_S2_LEFT          (0x8000000ULL) //&B 00000000 00000000 00000000 00000000 00001000 00000000 00000000 00000000
#define VB_S2_RIGHT        (0x10000000ULL) //&B 00000000 00000000 00000000 00000000 00010000 00000000 00000000 00000000

#define VB_UI_UP           (0x20000000ULL) //&B 00000000 00000000 00000000 00000000 00100000 00000000 00000000 00000000
#define VB_UI_DOWN         (0x40000000ULL) //&B 00000000 00000000 00000000 00000000 01000000 00000000 00000000 00000000
#define VB_UI_LEFT         (0x80000000ULL) //&B 00000000 00000000 00000000 00000000 10000000 00000000 00000000 00000000
#define VB_UI_RIGHT       (0x100000000ULL) //&B 00000000 00000000 00000000 00000001 00000000 00000000 00000000 00000000
#define VB_UI_EXECUTE     (0x200000000ULL) //&B 00000000 00000000 00000000 00000010 00000000 00000000 00000000 00000000
#define VB_UI_CANCEL      (0x400000000ULL) //&B 00000000 00000000 00000000 00000100 00000000 00000000 00000000 00000000
#define VB_UI_DEBUG       (0x800000000ULL) //&B 00000000 00000000 00000000 00001000 00000000 00000000 00000000 00000000

#define VB_UI_START      (0x1000000000ULL) //&B 00000000 00000000 00000000 00010000 00000000 00000000 00000000 00000000
#define VB_UI_COIN       (0x2000000000ULL) //&B 00000000 00000000 00000000 00100000 00000000 00000000 00000000 00000000
#define VB_UI_SERVICE    (0x4000000000ULL) //&B 00000000 00000000 00000000 01000000 00000000 00000000 00000000 00000000
#define VB_UI_TEST       (0x8000000000ULL) //&B 00000000 00000000 00000000 10000000 00000000 00000000 00000000 00000000


#define VB_MAP_BUFFER 120
#define VB_NUM 29

/**
 * 仮想ボタン .
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class VirtualButton : public GgafCore::Object {

public:
    /**
     * 仮想ボタンリスト .
     */
    class VBRecord {
    public :
        VBRecord* _next; //時系列で次のフレームの入力状態
        VBRecord* _prev; //時系列で前のフレームの入力状態
        vb_sta _vb_state[MAX_JOY_STICK_NUM];
//        vb_sta _p2_state;
    public:
        VBRecord() {
            _next = nullptr;
            _prev = nullptr;
            for (int p = 0; p < MAX_JOY_STICK_NUM; p++) {
                _vb_state[p] = (vb_sta)0;
            }
        }
        ~VBRecord() {
        }
    };


    struct VbkKeyboard {
        vbk P1_BUTTON1;
        vbk P1_BUTTON2;
        vbk P1_BUTTON3;
        vbk P1_BUTTON4;
        vbk P1_BUTTON5;
        vbk P1_BUTTON6;
        vbk P1_BUTTON7;
        vbk P1_BUTTON8;
        vbk P1_BUTTON9;
        vbk P1_BUTTON10;
        vbk P1_BUTTON11;
        vbk P1_BUTTON12;
        vbk P1_BUTTON13;
        vbk P1_BUTTON14;
        vbk P1_BUTTON15;
        vbk P1_BUTTON16;
        vbk P1_PAUSE;
        vbk P1_UP;
        vbk P1_DOWN;
        vbk P1_LEFT;
        vbk P1_RIGHT;
        vbk P1_S1_UP;
        vbk P1_S1_DOWN;
        vbk P1_S1_LEFT;
        vbk P1_S1_RIGHT;
        vbk P1_S2_UP;
        vbk P1_S2_DOWN;
        vbk P1_S2_LEFT;
        vbk P1_S2_RIGHT;
        vbk P1_UI_UP;
        vbk P1_UI_DOWN;
        vbk P1_UI_LEFT;
        vbk P1_UI_RIGHT;
        vbk P1_UI_EXECUTE;
        vbk P1_UI_CANCEL;
        vbk P1_UI_DEBUG;
        vbk P1_UI_START;
        vbk P1_UI_COIN;
        vbk P1_UI_SERVICE;
        vbk P1_UI_TEST;

        vbk P2_BUTTON1;
        vbk P2_BUTTON2;
        vbk P2_BUTTON3;
        vbk P2_BUTTON4;
        vbk P2_BUTTON5;
        vbk P2_BUTTON6;
        vbk P2_BUTTON7;
        vbk P2_BUTTON8;
        vbk P2_BUTTON9;
        vbk P2_BUTTON10;
        vbk P2_BUTTON11;
        vbk P2_BUTTON12;
        vbk P2_BUTTON13;
        vbk P2_BUTTON14;
        vbk P2_BUTTON15;
        vbk P2_BUTTON16;
        vbk P2_PAUSE;
        vbk P2_UP;
        vbk P2_DOWN;
        vbk P2_LEFT;
        vbk P2_RIGHT;
        vbk P2_S1_UP;
        vbk P2_S1_DOWN;
        vbk P2_S1_LEFT;
        vbk P2_S1_RIGHT;
        vbk P2_S2_UP;
        vbk P2_S2_DOWN;
        vbk P2_S2_LEFT;
        vbk P2_S2_RIGHT;
        vbk P2_UI_UP;
        vbk P2_UI_DOWN;
        vbk P2_UI_LEFT;
        vbk P2_UI_RIGHT;
        vbk P2_UI_EXECUTE;
        vbk P2_UI_CANCEL;
        vbk P2_UI_DEBUG;
        vbk P2_UI_START;
        vbk P2_UI_COIN;
        vbk P2_UI_SERVICE;
        vbk P2_UI_TEST;
    };

    struct VbjJoystick {
        vbj BUTTON1;
        vbj BUTTON2;
        vbj BUTTON3;
        vbj BUTTON4;
        vbj BUTTON5;
        vbj BUTTON6;
        vbj BUTTON7;
        vbj BUTTON8;
        vbj BUTTON9;
        vbj BUTTON10;
        vbj BUTTON11;
        vbj BUTTON12;
        vbj BUTTON13;
        vbj BUTTON14;
        vbj BUTTON15;
        vbj BUTTON16;
        vbj PAUSE;
        vbj UP;
        vbj DOWN;
        vbj LEFT;
        vbj RIGHT;
        vbj S1_UP;
        vbj S1_DOWN;
        vbj S1_LEFT;
        vbj S1_RIGHT;
        vbj S2_UP;
        vbj S2_DOWN;
        vbj S2_LEFT;
        vbj S2_RIGHT;
        vbj UI_UP;
        vbj UI_DOWN;
        vbj UI_LEFT;
        vbj UI_RIGHT;
        vbj UI_EXECUTE;
        vbj UI_CANCEL;
        vbj UI_DEBUG;
        vbj UI_START;
        vbj UI_COIN;
        vbj UI_SERVICE;
        vbj UI_TEST;
    };

public:
    static std::map<std::string, vbk> _mapStr2VBK;
    static std::map<std::string, vbj> _mapStr2VBJ;
    static std::map<vbk, std::string> _mapVBK2Str;
    static std::map<vbj, std::string> _mapVBJ2Str;



    typedef bool (*funcVJBtn)(int);
    static std::map<vbj_base, funcVJBtn> _mapVbjBase2PressedFunc;
    static std::map<vbj_base, funcVJBtn> _mapVbjBase2PushedDownFunc;
public:
    /** キーボード割り当て値 */
    VbkKeyboard _vbk_keyboardmap;
    /** ジョイスティック割り当て値 */
    VbjJoystick _vbj_joystickmap[MAX_JOY_STICK_NUM];

    std::map<vb_sta, vbk*> _mapVB2keyboardmap[MAX_JOY_STICK_NUM];
    std::map<vb_sta, vbj*> _mapVB2joystickmap[MAX_JOY_STICK_NUM];

    /** オートリピート判定用カウンター */
    std::map<vb_sta, frame> _auto_repeat_counter;
    /** オートリピート中ならば true */
    bool _is_auto_repeat;

    bool _with_pov;
    VBReplayRecorder* _pRpy;

    /** [r]リプレイモード時:true／ユーザー入力（リプレイモード記入）モード:false */
    bool _is_replaying;
    /** 現在フレームの入力状態 */
    VirtualButton::VBRecord* _pVBRecord_active;


public:
    /**
     * コンストラクタ .
     * 引数のリプレイファイルが存在する場合→リプレイーモード。
     * 引数のリプレイファイルが存在しない場合→ユーザー入力受付 ＆ リプレイファイル記入モード。
     * @param prm_replay_file リプレイファイル
     */
    VirtualButton(const char* prm_replay_file = "VirtualButton.rep");

    static bool initStatic();

    static bool isPressedVirtualJoyButton(vbj prm_VBJ);

    static bool isPushedDownVirtualJoyButton(vbj prm_VBJ);

    static vbj getFirstPushedDownVirtualJoyButton(int prm_player_no);

    /**
     * 仮想ボタンの割り当てを変更（キーボード＆ジョイスティック） .
     * @param prm_VB VB_... で始まる仮想ボタン、割り当て対象の仮想ボタンを指定
     * @param prm_VBK VBK_... で始まる仮想キー定数、仮想ボタンへ割り当てるキーボードを指定
     * @param prm_VBJ VBJ_... で始まる仮想JOYスティックボタン定数、仮想ボタンへ割り当てるJOYスティックボタンを指定
     */
    void remap(int prm_player_no, vb_sta prm_VB, vbk prm_VBK, vbj prm_VBJ);

    /**
     * 仮想ボタンの割り当てを変更（キーボードのみ） .
     * @param prm_VB VB_... で始まる仮想ボタン、割り当て対象の仮想ボタンを指定
     * @param prm_VBK VBK_... で始まる仮想キー定数、仮想ボタンへ割り当てるキーボードを指定
     */
    void remapK(int prm_player_no, vb_sta prm_VB, vbk prm_VBK);

    /**
     * 仮想ボタンの割り当てを変更（ジョイスティックのみ） .
     * @param prm_VB VB_... で始まる仮想ボタン、割り当て対象の仮想ボタンを指定
     * @param prm_VBJ VBJ_... で始まる仮想JOYスティックボタン定数、仮想ボタンへ割り当てるJOYスティックボタンを指定
     */
    void remapJ(int prm_player_no, vb_sta prm_VB, vbj prm_VBJ);

    /**
     * 過去の入力状態を取得 .
     * @param prm_frame_ago 現在より何フレーム過去かを指定
     * @return 過去の入力状態
     */
    VirtualButton::VBRecord* getPastVBRecord(frame prm_frame_ago) const;

    /**
     * 現在ボタンが押されているか判定(押されている間成立する) .
     * @param prm_VB 判定対象仮想ボタン定数。VB_ で始まる定数(の論理和)
     * @retval 0   引数のボタンはいずれも押されていない(=false)
     * @retval >0  引数のボタンの内、現在押されているボタンの VB_ で始まる定数(の論理和)
     * @code
     * VirtualButton vb_play = VirtualButton();
     * vb_play.update();
     *
     * if (vb_play.isPressed(0, VB_BUTTON1)) {
     *     //VB_BUTTON1 が押されている場合の処理
     * }
     *
     * if (vb_play.isPressed(0, VB_BUTTON1|VB_BUTTON3)) {
     *     //VB_BUTTON1 又は VB_BUTTON3 が押されている場合の処理
     * }
     *
     * if (vb_play.isPressed(0, VB_BUTTON1|VB_BUTTON3) == (VB_BUTTON1|VB_BUTTON3)) {
     *     //VB_BUTTON1 と VB_BUTTON3 が両方押されている場合の処理
     * }
     * @endcode
     */
    inline vb_sta isPressed(int prm_player_no, vb_sta prm_VB) const {
        return (_pVBRecord_active->_vb_state[prm_player_no] & prm_VB);
    }

    /**
     * 過去フレームでボタンが押されていたかどうか判定 .
     * @param prm_VB 判定対象仮想ボタン。VB_ で始まる定数(の論理和)
     * @param prm_frame_ago 何フレーム前(>0)を判定するのか指定。
     * 1 で 1フレーム前、2 で 2フレーム前、0 は isPressed(vb_sta) と同じ意味になる。
     * 最大 (VB_MAP_BUFFER-1) フレーム前まで可
     * @retval 0   isPressed() と同じ
     * @retval >0  引数のボタンの内、過去に押されていたボタンの VB_ で始まる定数(の論理和)
     */
    vb_sta wasPressed(int prm_player_no, vb_sta prm_VB, frame prm_frame_ago) const;

    /**
     * 現在と過去フレームの機関で、ずっとボタンが押されていたかどうか判定 .
     * @param prm_VB  prm_VB 判定対象仮想ボタン。VB_ で始まる定数(の論理和)
     * @param prm_frame_ago 何フレーム前までの期間を判定するのか指定。
     * 1 で 現在と1フレーム前、2 で 現在と2フレーム前、0 は isPressed(vb_sta) と同じ意味になる。
     * @return true：現在とprm_frame_agoの期間ずっと押しっぱなしだった／false：それ以外（少なくとも１フレーム押されていない瞬間あり）
     */
    vb_sta hasBeenPressed(int prm_player_no, vb_sta prm_VB, frame prm_frame_ago) const;


//    /**
//     * 過去フレーム範囲でボタンが少なくとも１回は押されていたかどうか判定 .
//     * @param prm_VB 判定対象仮想ボタン。VB_ で始まる定数(の論理和)
//     * @param prm_frame_ago 何フレーム前(>0)までの範囲を判定するのか指定。
//     * 1 で 1フレーム前、2 で 1～2フレーム前、3 で 1～3フレーム前 という範囲を調べる。
//     * 最大 (VB_MAP_BUFFER-1) フレーム前まで可
//     * @retval 0   isPressed() と同じ
//     * @retval >0  引数のボタンの内、過去フレーム範囲で最初に成立したボタンの VB_ で始まる定数(の論理和)
//     * @return
//     */
//    vb_sta wasPressedAtLeastOnce(vb_sta prm_VB, frame prm_frame_ago) const;
//
//
//    vb_sta wasReleasedUpAtLeastOnce(vb_sta prm_VB, frame prm_frame_ago) const;


    /**
     * 過去フレームで押されていなかったのかどうか判定 .
     * wasPressed(vb_sta, frame) の否定の結果が返る。
     * @param prm_VB 判定対象仮想ボタン。VB_ で始まる定数(の論理和)
     * @param prm_frame_ago 何フレーム前(>0)を判定するのか指定。
     *                      1 で 1フレーム前、2 で 2フレーム前、0 は isPressed(vb_sta) と同じ意味になる。
     *                      最大 (VB_MAP_BUFFER-1) フレーム前まで可
     * @return true / false
     */
    inline bool wasNotPressed(int prm_player_no, vb_sta prm_VB, frame prm_frame_ago) const {
        return wasPressed(prm_player_no, prm_VB, prm_frame_ago) ? false : true;
    }

    /**
     * 現在ボタンが押された瞬間なのかどうか判定 .
     * 現在は押されている、かつ、１フレーム前は押されていない場合に true
     * @param prm_VB 判定対象仮想ボタン。VB_ で始まる定数(の論理和)
     * @return true / false
     */
    inline bool isPushedDown(int prm_player_no, vb_sta prm_VB) const {
        return (!(_pVBRecord_active->_prev->_vb_state[prm_player_no] & prm_VB) && (_pVBRecord_active->_vb_state[prm_player_no] & prm_VB)) ? true : false;
    }

    /**
     * 過去にボタンが押された瞬間があったのかどうか判定 .
     * prm_frame_agoフレーム前は押されていた、かつ、(prm_frame_ago+1)フレーム前は押されていなかった場合に true
     * @param prm_VB 判定対象仮想ボタン。VB_ で始まる定数(の論理和)
     * @param prm_frame_ago 何フレーム前(>0)を判定するのか指定。
     *                      1 で 1フレーム前、2 で 2フレーム前、0 は isPushedDown(vb_sta) と同じ意味になる。
     *                      最大 (VB_MAP_BUFFER-1) フレーム前まで可
     * @return true / false
     */
    bool wasPushedDown(int prm_player_no, vb_sta prm_VB, frame prm_frame_ago) const;

    /**
     * 現在ボタンを離した瞬間なのかどうか判定 .
     * 現在は押されていない、かつ、１フレーム前は押されていた場合に true
     * @param prm_VB 判定対象仮想ボタン。VB_ で始まる定数(の論理和)
     * @return true / false
     */
    bool isReleasedUp(int prm_player_no, vb_sta prm_VB) const;

    /**
     * 過去にボタンを離した瞬間があったのかどうか判定 .
     * prm_frame_agoフレーム前は押されていなかった、かつ、(prm_frame_ago+1)フレーム前は押されていた場合に true
     * @param prm_VB 判定対象仮想ボタン。VB_ で始まる定数(の論理和)
     * @param prm_frame_ago 何フレーム前(>0)を判定するのか指定。
     *                      1 で 1フレーム前、2 で 2フレーム前、0 は isReleasedUp(vb_sta) と同じ意味になる。
     * @return true / false
     */
    bool wasReleasedUp(int prm_player_no, vb_sta prm_VB, frame prm_frame_ago) const;

    /**
     * チョン押し判定 .
     * 「ボタンを押していなかった→ボタンを押した→ボタンを離した」というフェーズが、
     * 現在成立したかどうか判定する。
     * 但し押していた期間が prm_frame_push 以上押していると成立しない（チョン押しと認められない）。
     * ※たとえば独歩のGボタン判定なら prm_frame_push=2 を指定。ﾅﾝﾉｺｯﾁｬ;
     * @param prm_VB 判定対象仮想ボタン。VB_ で始まる定数(の論理和)
     * @param prm_frame_push 許容するボタンを押していた期間フレーム(default=5)
     * @return true / false
     */
    bool isPushedUp(int prm_player_no, vb_sta prm_VB, frame prm_frame_push = 5) const;

    /**
     * ダブルプッシュ判定 .
     * 「(a)ボタンを押していなかった→(b)ボタンを押した→(c)ボタンを離した→(d)ボタンを押した」というフェーズが、
     * 現在成立したかどうか判定する。
     * 但し   (b)～(c)の押していた期間が prm_frame_push 以上押していると成立しない。
     * さらに (c)～(d)の２回目のボタン押しまでの期間が prm_frame_delay 以上開いていると成立しない。
     * @param prm_VB 判定対象仮想ボタン。VB_ で始まる定数(の論理和)
     * @param prm_frame_push 許容する(b)～(c) の期間
     * @param prm_frame_delay 許容する(c)～(d) の期間
     * @return true / false
     */
    bool isDoublePushedDown(int prm_player_no, vb_sta prm_VB, frame prm_frame_push = 5, frame prm_frame_delay = 5) const;

    /**
     * 複数ボタン同時押し判定 .
     * isPushedDown(vb_sta) の引数に複数ボタンを指定して判定を行えば、同時押し判定は可能である。
     * しかし、その判定方法は複数ボタンを押す際に1フレームでもバラツキがあれば成立せず、
     * 完全に同時に押さなければならないため、シビアすぎるという問題点がある。
     * そこで、本メソッドは、同時押しのバラツキを許容考慮した同時押し判定である。
     * 具体的には、引数のそれぞれの各ボタンの現在に至るまでの４フレームの状態履歴が、
     * 次のいずれかのフェーズであれば1回成立という判定を行っている。(つまり3フレーム猶予)
     * <pre>
     * ↑ > ？ > ？ > ↓
     *       or
     * ？ > ↑ > ？ > ↓
     *       or
     * ？ > ？ > ↑ > ↓
     *
     * ※↓：押している ／ ↑：離している ／ ？：任意
     * ※一番右が現在の状態、左が過去
     * </pre>
     * @param prm_aVB (3フレ猶予)同時押し判定対象仮想ボタン配列
     * @param prm_num_button 配列の要素数
     * @return true / false
     */
    bool arePushedDownAtOnce(int prm_player_no, vb_sta prm_aVB[], int prm_num_button, int delay=2) const;

    /**
     * 2フレ猶予の２つボタン同時押し判定 .
     * @param prm_VB1 判定対象仮想ボタン１
     * @param prm_VB2 判定対象仮想ボタン２
     * @return true / false
     */
    bool arePushedDownAtOnce(int prm_player_no, vb_sta prm_VB1, vb_sta prm_VB2, int delay=2) const {
        vb_sta vb[2];
        vb[0] = prm_VB1;
        vb[1] = prm_VB2;
        return arePushedDownAtOnce(prm_player_no, vb, 2, delay);
    }

    /**
     * 2フレ猶予の３つボタン同時押し判定 .
     * @param prm_VB1 判定対象仮想ボタン１
     * @param prm_VB2 判定対象仮想ボタン２
     * @param prm_VB3 判定対象仮想ボタン３
     * @return true / false
     */
    bool arePushedDownAtOnce(int prm_player_no, vb_sta prm_VB1, vb_sta prm_VB2, vb_sta prm_VB3, int delay=2) const {
        vb_sta vb[3];
        vb[0] = prm_VB1;
        vb[1] = prm_VB2;
        vb[2] = prm_VB3;
        return arePushedDownAtOnce(prm_player_no, vb, 3, delay);
    }

    /**
     * 2フレ猶予の４つボタン同時押し判定 .
     * @param prm_VB1 判定対象仮想ボタン１
     * @param prm_VB2 判定対象仮想ボタン２
     * @param prm_VB3 判定対象仮想ボタン３
     * @param prm_VB4 判定対象仮想ボタン４
     * @return true / false
     */
    bool arePushedDownAtOnce(int prm_player_no, vb_sta prm_VB1, vb_sta prm_VB2, vb_sta prm_VB3, vb_sta prm_VB4, int delay=2) const {
        vb_sta vb[4];
        vb[0] = prm_VB1;
        vb[1] = prm_VB2;
        vb[2] = prm_VB3;
        vb[3] = prm_VB4;
        return arePushedDownAtOnce(prm_player_no, vb, 4, delay);
    }

    /**
     * オートリピート入力判定 .
     * @param prm_VB 判定対象仮想ボタン。VB_ で始まる定数(の論理和)
     * @param prm_begin_repeat オートリピート開始フレーム数
     * @param prm_while_repeat オートリピート開始後、リピート間隔フレーム数
     * @return true / false
     */
    bool isAutoRepeat(int prm_player_no, vb_sta prm_VB, frame prm_begin_repeat = 20, frame prm_while_repeat = 5);

    /**
     * グルッとポンか否か判定 .
     * ザンギエフのスクリューパイルドライバーコマンド入力判定です。
     * 具体的には、prm_frame_delay 以内に
     * ↑ → ↓ ← の４方向ボタン押しが成立後、isPushedDown(prm_VB) が成立。
     * の場合に true としています。
     * @param prm_VB 「グルッとポン」の「ポン」のボタン
     * @param prm_frame_delay 「グルッとポン」が成立する全体の許容フレーム
     * @return true / false
     */
    bool isScrewPushDown(int prm_player_no, vb_sta prm_VB, frame prm_frame_delay=30) const;


    //vb_sta getPushedDownStick() const;


    inline vb_sta getState(int prm_player_no) const {
        return _pVBRecord_active->_vb_state[prm_player_no];
    }

    /**
     * 入力情報を更新 .
     * 通常時はキー入力、ジョイスティック、マウスのデバイスに入力により、内部ステートを更新。
     * 但し、リプレイ再生中は、読み込まれた外部ファイルのデータで、内部ステートを更新。
     */
    void update();

    void clear();


    void printDebugState();

    virtual ~VirtualButton();
};

}
#endif /*GGAF_LIB_VIRTUALBUTTON_H_*/
