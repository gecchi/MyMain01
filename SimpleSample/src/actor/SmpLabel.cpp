#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace SimpleSample;

SmpLabel::SmpLabel(const char* prm_name) :
        StringBoardActor(prm_name, "SimpleFont")
{
    _class_name = "SmpLabel";
    _aWidthPx['!'] = 10;
    _aWidthPx['"'] = 10;
    _aWidthPx['#'] = 14;
    _aWidthPx['$'] = 14;
    _aWidthPx['%'] = 14;
    _aWidthPx['&'] = 14;
    _aWidthPx['\''] = 10;
    _aWidthPx['('] = 10;
    _aWidthPx[')'] = 10;
    _aWidthPx['*'] = 12;
    _aWidthPx['+'] = 10;
    _aWidthPx[','] = 8;
    _aWidthPx['-'] = 10;
    _aWidthPx['.'] = 8;
    _aWidthPx['/'] = 14;
    _aWidthPx['0'] = 14;
    _aWidthPx['1'] = 14;
    _aWidthPx['2'] = 14;
    _aWidthPx['3'] = 14;
    _aWidthPx['4'] = 14;
    _aWidthPx['5'] = 14;
    _aWidthPx['6'] = 14;
    _aWidthPx['7'] = 14;
    _aWidthPx['8'] = 14;
    _aWidthPx['9'] = 14;
    _aWidthPx[':'] = 8;
    _aWidthPx[';'] = 8;
    _aWidthPx['<'] = 14;
    _aWidthPx['='] = 14;
    _aWidthPx['>'] = 14;
    _aWidthPx['?'] = 14;
    _aWidthPx[' '] = 8;
    _aWidthPx['A'] = 15;
    _aWidthPx['B'] = 14;
    _aWidthPx['C'] = 15;
    _aWidthPx['D'] = 15;
    _aWidthPx['E'] = 14;
    _aWidthPx['F'] = 14;
    _aWidthPx['G'] = 14;
    _aWidthPx['H'] = 14;
    _aWidthPx['I'] = 10;
    _aWidthPx['J'] = 14;
    _aWidthPx['K'] = 14;
    _aWidthPx['L'] = 15;
    _aWidthPx['M'] = 15;
    _aWidthPx['N'] = 14;
    _aWidthPx['O'] = 14;
    _aWidthPx['P'] = 14;
    _aWidthPx['Q'] = 14;
    _aWidthPx['R'] = 14;
    _aWidthPx['S'] = 14;
    _aWidthPx['T'] = 13;
    _aWidthPx['U'] = 14;
    _aWidthPx['V'] = 14;
    _aWidthPx['W'] = 15;
    _aWidthPx['X'] = 14;
    _aWidthPx['Y'] = 14;
    _aWidthPx['Z'] = 14;
    _aWidthPx['['] = 10;
    _aWidthPx['\\'] = 12;
    _aWidthPx[']'] = 10;
    _aWidthPx['^'] = 12;
    _aWidthPx['_'] = 16;
}

void SmpLabel::onCreateModel() {
}

void SmpLabel::initialize() {
    setAlpha(0.99);
}

void SmpLabel::processBehavior() {

    if (GgafDxInput::isBeingPressedKey(DIK_Z)) {
        _pKurokoA->setFaceAngVelo(AXIS_Z, D_ANG(1));
    } else {
        _pKurokoA->setFaceAngVelo(AXIS_Z, D_ANG(0));
    }
    if (GgafDxInput::isBeingPressedKey(DIK_X)) {
        _pKurokoA->setFaceAngVelo(AXIS_X, D_ANG(1));
    } else {
        _pKurokoA->setFaceAngVelo(AXIS_X, D_ANG(0));
    }
    if (GgafDxInput::isBeingPressedKey(DIK_C)) {
        _pKurokoA->setFaceAngVelo(AXIS_Y, D_ANG(1));
    } else {
        _pKurokoA->setFaceAngVelo(AXIS_Y, D_ANG(0));
    }
    _pKurokoA->behave();

    //入力で移動
    if (GgafDxInput::isBeingPressedKey(DIK_SPACE)) {
        //ボタン１（スペースキー）を押しながらの場合
        if (GgafDxInput::isBeingPressedKey(DIK_UP)) {
            _Z += PX_C(2); //奥
        }
        if (GgafDxInput::isBeingPressedKey(DIK_DOWN)) {
            _Z -= PX_C(2); //手前
        }
    } else {
        //ボタン１（スペースキー）を離している場合
        if (GgafDxInput::isBeingPressedKey(DIK_RIGHT)) {
            _X += PX_C(2); //右
        }
        if (GgafDxInput::isBeingPressedKey(DIK_LEFT)) {
            _X -= PX_C(2); //左
        }
        if (GgafDxInput::isBeingPressedKey(DIK_UP)) {
            _Y += PX_C(2); //上
        }
        if (GgafDxInput::isBeingPressedKey(DIK_DOWN)) {
            _Y -= PX_C(2); //下
        }
    }
}

SmpLabel::~SmpLabel() {
}

