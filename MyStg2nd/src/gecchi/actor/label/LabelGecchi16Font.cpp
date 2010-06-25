#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

LabelGecchi16Font::LabelGecchi16Font(const char* prm_name) :
        StringBoardActor(prm_name, "Gecchi_16Font")
{
    _class_name = "LabelGecchi16Font";
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
    _aWidthPx['0'] = 13;
    _aWidthPx['1'] = 13;
    _aWidthPx['2'] = 13;
    _aWidthPx['3'] = 13;
    _aWidthPx['4'] = 13;
    _aWidthPx['5'] = 13;
    _aWidthPx['6'] = 13;
    _aWidthPx['7'] = 13;
    _aWidthPx['8'] = 13;
    _aWidthPx['9'] = 13;
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
    _aWidthPx['I'] = 8;
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
    _aWidthPx['^'] = 14;
    _aWidthPx['_'] = 16;
}

void LabelGecchi16Font::onCreateModel() {
}

void LabelGecchi16Font::initialize() {
}

void LabelGecchi16Font::processBehavior() {
}

LabelGecchi16Font::~LabelGecchi16Font() {
}

