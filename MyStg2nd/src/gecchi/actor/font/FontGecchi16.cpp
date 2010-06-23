#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

FontGecchi16::FontGecchi16(const char* prm_name) :
        StringBoardActor(prm_name, "28/Gecchi_16Font")
{
    _class_name = "FontGecchi16";
}

void FontGecchi16::onCreateModel() {
    _pBoardSetModel->_fSize_BoardSetModelWidthPx -= 2;
}

void FontGecchi16::initialize() {
}

void FontGecchi16::processBehavior() {
}

FontGecchi16::~FontGecchi16() {
}

