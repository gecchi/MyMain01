#include "SpriteLabelTest.h"

using namespace GgafLib;
using namespace VioletVreath;

SpriteLabelTest::SpriteLabelTest(const char* prm_name) :
        FontSpriteActor(prm_name, "Gecchi_16Font")
{
    _class_name = "SpriteLabelTest";
//    _px_chr_width[' '] = 8;
//    _px_chr_width['!'] = 10;
//    _px_chr_width['"'] = 10;
//    _px_chr_width['#'] = 14;
//    _px_chr_width['$'] = 14;
//    _px_chr_width['%'] = 14;
//    _px_chr_width['&'] = 14;
//    _px_chr_width['\''] = 10;
//    _px_chr_width['('] = 10;
//    _px_chr_width[')'] = 10;
//    _px_chr_width['*'] = 12;
//    _px_chr_width['+'] = 10;
//    _px_chr_width[','] = 8;
//    _px_chr_width['-'] = 10;
//    _px_chr_width['.'] = 8;
//    _px_chr_width['/'] = 14;
//    _px_chr_width['0'] = 14;
//    _px_chr_width['1'] = 14;
//    _px_chr_width['2'] = 14;
//    _px_chr_width['3'] = 14;
//    _px_chr_width['4'] = 14;
//    _px_chr_width['5'] = 14;
//    _px_chr_width['6'] = 14;
//    _px_chr_width['7'] = 14;
//    _px_chr_width['8'] = 14;
//    _px_chr_width['9'] = 14;
//    _px_chr_width[':'] = 8;
//    _px_chr_width[';'] = 8;
//    _px_chr_width['<'] = 14;
//    _px_chr_width['='] = 14;
//    _px_chr_width['>'] = 14;
//    _px_chr_width['?'] = 14;
//    _px_chr_width['@'] = 15;
//    _px_chr_width['A'] = 15;
//    _px_chr_width['B'] = 14;
//    _px_chr_width['C'] = 15;
//    _px_chr_width['D'] = 15;
//    _px_chr_width['E'] = 14;
//    _px_chr_width['F'] = 14;
//    _px_chr_width['G'] = 14;
//    _px_chr_width['H'] = 14;
//    _px_chr_width['I'] = 10;
//    _px_chr_width['J'] = 14;
//    _px_chr_width['K'] = 14;
//    _px_chr_width['L'] = 15;
//    _px_chr_width['M'] = 15;
//    _px_chr_width['N'] = 14;
//    _px_chr_width['O'] = 14;
//    _px_chr_width['P'] = 14;
//    _px_chr_width['Q'] = 14;
//    _px_chr_width['R'] = 14;
//    _px_chr_width['S'] = 14;
//    _px_chr_width['T'] = 13;
//    _px_chr_width['U'] = 14;
//    _px_chr_width['V'] = 14;
//    _px_chr_width['W'] = 15;
//    _px_chr_width['X'] = 14;
//    _px_chr_width['Y'] = 14;
//    _px_chr_width['Z'] = 14;
//    _px_chr_width['['] = 10;
//    _px_chr_width['\\'] = 12;
//    _px_chr_width[']'] = 10;
//    _px_chr_width['^'] = 12;
//    _px_chr_width['_'] = 16;
}

void SpriteLabelTest::onCreateModel() {
}

void SpriteLabelTest::initialize() {
    setCullingDraw(false);
}

void SpriteLabelTest::processBehavior() {
    //_pLocusVehicle->setFaceAngVelo(AXIS_X, D_ANG(1));
//    pLocusVehicle->setFaceAngVelo(AXIS_Z, D_ANG(1));
//    pLocusVehicle->behave();

//    if (GgafDx::Input::isPressedKey(DIK_P)) {
//        addScale(100);
//    }

//    //入力で移動
//    if (GgafDx::Input::isPressedKey(DIK_SPACE)) {
//        //ボタン１（スペースキー）を押しながらの場合
//        if (GgafDx::Input::isPressedKey(DIK_UP)) {
//            _z += PX_C(2); //奥
//        }
//        if (GgafDx::Input::isPressedKey(DIK_DOWN)) {
//            _z -= PX_C(2); //手前
//        }
//    } else {
//        //ボタン１（スペースキー）を離している場合
//        if (GgafDx::Input::isPressedKey(DIK_RIGHT)) {
//            _x += PX_C(2); //右
//        }
//        if (GgafDx::Input::isPressedKey(DIK_LEFT)) {
//            _x -= PX_C(2); //左
//        }
//        if (GgafDx::Input::isPressedKey(DIK_UP)) {
//            _y += PX_C(2); //上
//        }
//        if (GgafDx::Input::isPressedKey(DIK_DOWN)) {
//            _y -= PX_C(2); //下
//        }
//    }
}

SpriteLabelTest::~SpriteLabelTest() {
}

