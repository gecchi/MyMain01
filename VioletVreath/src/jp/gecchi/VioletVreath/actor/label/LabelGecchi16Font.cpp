#include "LabelGecchi16Font.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

LabelGecchi16Font::LabelGecchi16Font(const char* prm_name) :
        FontBoardActor(prm_name, "Gecchi_16Font")
{
    _class_name = "LabelGecchi16Font";
    pAFader_ = NEW GgafDxAlphaFader(this);
    setChrWidthRatio(' ',  0.5  );
    setChrWidthRatio('!',  0.625);
    setChrWidthRatio('"',  0.625);
    setChrWidthRatio('#',  0.875);
    setChrWidthRatio('$',  0.875);
    setChrWidthRatio('%',  0.875);
    setChrWidthRatio('&',  0.875);
    setChrWidthRatio('\'', 0.625);
    setChrWidthRatio('(',  0.625);
    setChrWidthRatio(')',  0.625);
    setChrWidthRatio('*',  0.75 );
    setChrWidthRatio('+',  0.625);
    setChrWidthRatio(',',  0.5  );
    setChrWidthRatio('-',  0.625);
    setChrWidthRatio('.',  0.5  );
    setChrWidthRatio('/',  0.875);
    setChrWidthRatio('0',  0.875);
    setChrWidthRatio('1',  0.875);
    setChrWidthRatio('2',  0.875);
    setChrWidthRatio('3',  0.875);
    setChrWidthRatio('4',  0.875);
    setChrWidthRatio('5',  0.875);
    setChrWidthRatio('6',  0.875);
    setChrWidthRatio('7',  0.875);
    setChrWidthRatio('8',  0.875);
    setChrWidthRatio('9',  0.875);
    setChrWidthRatio(':',  0.5  );
    setChrWidthRatio(' ',  0.5  );
    setChrWidthRatio('<',  0.875);
    setChrWidthRatio('=',  0.875);
    setChrWidthRatio('>',  0.875);
    setChrWidthRatio('?',  0.875);
    setChrWidthRatio('@',  0.937);
    setChrWidthRatio('A',  0.937);
    setChrWidthRatio('B',  0.875);
    setChrWidthRatio('C',  0.937);
    setChrWidthRatio('D',  0.937);
    setChrWidthRatio('E',  0.875);
    setChrWidthRatio('F',  0.875);
    setChrWidthRatio('G',  0.875);
    setChrWidthRatio('H',  0.875);
    setChrWidthRatio('I',  0.625);
    setChrWidthRatio('J',  0.875);
    setChrWidthRatio('K',  0.875);
    setChrWidthRatio('L',  0.937);
    setChrWidthRatio('M',  0.937);
    setChrWidthRatio('N',  0.875);
    setChrWidthRatio('O',  0.875);
    setChrWidthRatio('P',  0.875);
    setChrWidthRatio('Q',  0.875);
    setChrWidthRatio('R',  0.875);
    setChrWidthRatio('S',  0.875);
    setChrWidthRatio('T',  0.812);
    setChrWidthRatio('U',  0.875);
    setChrWidthRatio('V',  0.875);
    setChrWidthRatio('W',  0.937);
    setChrWidthRatio('X',  0.875);
    setChrWidthRatio('Y',  0.875);
    setChrWidthRatio('Z',  0.875);
    setChrWidthRatio('[',  0.625);
    setChrWidthRatio('\\', 0.75 );
    setChrWidthRatio(']',  0.625);
    setChrWidthRatio('^',  0.75 );
    setChrWidthRatio('_',  1.0  );
}

void LabelGecchi16Font::onCreateModel() {
}

void LabelGecchi16Font::initialize() {
}

void LabelGecchi16Font::processBehavior() {
}

LabelGecchi16Font::~LabelGecchi16Font() {
    GGAF_DELETE(pAFader_);
}

