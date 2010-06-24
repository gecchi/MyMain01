#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

LabelGecchi16Font::LabelGecchi16Font(const char* prm_name) :
        StringBoardActor(prm_name, "28/Gecchi_16Font")
{
    _class_name = "LabelGecchi16Font";
}

void LabelGecchi16Font::onCreateModel() {
    StringBoardActor::onCreateModel();
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
    _aWidthPx[','] = 10;
    _aWidthPx['-'] = 10;
    _aWidthPx['.'] = 10;
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
    _aWidthPx[':'] = 10;
    _aWidthPx[';'] = 10;
    _aWidthPx['<'] = 14;
    _aWidthPx['='] = 14;
    _aWidthPx['>'] = 14;
    _aWidthPx['?'] = 14;
    _aWidthPx[' '] = 8;
    _aWidthPx['A'] = 14;
    _aWidthPx['B'] = 14;
    _aWidthPx['C'] = 14;
    _aWidthPx['D'] = 14;
    _aWidthPx['E'] = 14;
    _aWidthPx['F'] = 14;
    _aWidthPx['G'] = 14;
    _aWidthPx['H'] = 14;
    _aWidthPx['I'] = 12;
    _aWidthPx['J'] = 14;
    _aWidthPx['K'] = 14;
    _aWidthPx['L'] = 14;
    _aWidthPx['M'] = 15;
    _aWidthPx['N'] = 14;
    _aWidthPx['O'] = 14;
    _aWidthPx['P'] = 14;
    _aWidthPx['Q'] = 14;
    _aWidthPx['R'] = 14;
    _aWidthPx['S'] = 14;
    _aWidthPx['T'] = 14;
    _aWidthPx['U'] = 14;
    _aWidthPx['V'] = 14;
    _aWidthPx['W'] = 15;
    _aWidthPx['X'] = 14;
    _aWidthPx['Y'] = 14;
    _aWidthPx['Z'] = 14;
    _aWidthPx['['] = 10;
    _aWidthPx['\\'] = 12;
    _aWidthPx[']'] = 10;
    _aWidthPx['^'] = 14;
    _aWidthPx['_'] = 16;
}

void LabelGecchi16Font::initialize() {
}

void LabelGecchi16Font::processBehavior() {
}

LabelGecchi16Font::~LabelGecchi16Font() {
}

