#include "SpriteLabelTest.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

SpriteLabelTest::SpriteLabelTest(const char* prm_name) :
        FixedFontSpriteActor(prm_name, "Gecchi_16Font")
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
    setAlpha(0.9);
}

void SpriteLabelTest::processBehavior() {
    //_pKuroko->setFaceAngVelo(AXIS_X, D_ANG(1));
//    pKuroko->setFaceAngVelo(AXIS_Z, D_ANG(1));
//    pKuroko->behave();

//    if (GgafDxInput::isBeingPressedKey(DIK_P)) {
//        addScale(100);
//    }

//    //���͂ňړ�
//    if (GgafDxInput::isBeingPressedKey(DIK_SPACE)) {
//        //�{�^���P�i�X�y�[�X�L�[�j�������Ȃ���̏ꍇ
//        if (GgafDxInput::isBeingPressedKey(DIK_UP)) {
//            _z += PX_C(2); //��
//        }
//        if (GgafDxInput::isBeingPressedKey(DIK_DOWN)) {
//            _z -= PX_C(2); //��O
//        }
//    } else {
//        //�{�^���P�i�X�y�[�X�L�[�j�𗣂��Ă���ꍇ
//        if (GgafDxInput::isBeingPressedKey(DIK_RIGHT)) {
//            _x += PX_C(2); //�E
//        }
//        if (GgafDxInput::isBeingPressedKey(DIK_LEFT)) {
//            _x -= PX_C(2); //��
//        }
//        if (GgafDxInput::isBeingPressedKey(DIK_UP)) {
//            _y += PX_C(2); //��
//        }
//        if (GgafDxInput::isBeingPressedKey(DIK_DOWN)) {
//            _y -= PX_C(2); //��
//        }
//    }
}

SpriteLabelTest::~SpriteLabelTest() {
}

