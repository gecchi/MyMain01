#include "stdafx.h"
#include "SpriteLabelTest.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

SpriteLabelTest::SpriteLabelTest(const char* prm_name) :
        StringSpriteActor(prm_name, "Gecchi_16Font")
{
    _class_name = "SpriteLabelTest";
    _aWidthPx[' '] = 8;
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
    _aWidthPx['@'] = 15;
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

void SpriteLabelTest::onCreateModel() {
}

void SpriteLabelTest::initialize() {
    setAlpha(0.9);
}

void SpriteLabelTest::processBehavior() {
    //_pKuroko->setFaceAngVelo(AXIS_X, D_ANG(1));
//    pKuroko->setFaceAngVelo(AXIS_Z, D_ANG(1));
//    pKuroko->behave();

//    if (GgafDxInput::isBeingPressedKey(DIK_P)) {
//        addScale(100);
//    }

//    //入力で移動
//    if (GgafDxInput::isBeingPressedKey(DIK_SPACE)) {
//        //ボタン１（スペースキー）を押しながらの場合
//        if (GgafDxInput::isBeingPressedKey(DIK_UP)) {
//            _z += PX_C(2); //奥
//        }
//        if (GgafDxInput::isBeingPressedKey(DIK_DOWN)) {
//            _z -= PX_C(2); //手前
//        }
//    } else {
//        //ボタン１（スペースキー）を離している場合
//        if (GgafDxInput::isBeingPressedKey(DIK_RIGHT)) {
//            _x += PX_C(2); //右
//        }
//        if (GgafDxInput::isBeingPressedKey(DIK_LEFT)) {
//            _x -= PX_C(2); //左
//        }
//        if (GgafDxInput::isBeingPressedKey(DIK_UP)) {
//            _y += PX_C(2); //上
//        }
//        if (GgafDxInput::isBeingPressedKey(DIK_DOWN)) {
//            _y -= PX_C(2); //下
//        }
//    }
}

SpriteLabelTest::~SpriteLabelTest() {
}

