#include "jp/ggaf/core/util/GgafXpm.h"

#include "jp/ggaf/core/util/GgafRgb.h"
#include <sstream>
#include <string>
#include <vector>
#include <map>

using namespace GgafCore;

GgafXpm::GgafXpm(const char** prm_xpm) : GgafObject() {
    _xpm_hd = prm_xpm;
    _width = 0;
    _height = 0;
    _colors = 0;
    _char_on_pixel = 0;
    std::istringstream line0(_xpm_hd[0]); //"16 491 5 1 "  <width/cols> <height/rows> <colors> <char on pixel>
    line0 >> _width >> _height >> _colors >> _char_on_pixel;  //char on pixel �� 1 �����Ή����Ă��Ȃ��E�E�E
    if (line0.fail()) {
        throwGgafCriticalException("�s���ȃw�b�_�f�[�^�ł� line0=["<<line0.str()<<"]");
    }
    if (_char_on_pixel != 1) {
        throwGgafCriticalException("_char_on_pixel ��1���������Ή����Ă��܂���B line0=["<<line0.str()<<"]");
    }
    for (int i = 0; i < _colors; i++) {
        char c = _xpm_hd[i + 1][0]; //�P���������Ή�
        _vecColorChar.push_back(c);
        if (_xpm_hd[i + 1][4] == '#') {                             //                   0123456789
            std::string strcolor = std::string(&(_xpm_hd[i+1][4])); //"#"�ȍ~�𕶎���� "X c #E08000",
            _mapCharRgb[c] = NEW GgafRgb(strcolor);
        } else {
            std::string strcolor = std::string(&(_xpm_hd[i+1][4]));
            if (strcolor == "None" || strcolor == "none" || strcolor == "    ") {
                _c_px_non = c;
                _mapCharRgb[c] = NEW GgafRgb("#000000");
            } else {
                _mapCharRgb[c] = NEW GgafRgb(strcolor);
            }
        }
    }
    //pixels_�̓w�b�_�[�ȍ~�̔z��
    _pixels = &(prm_xpm[1+_colors+1 -1]);//1+       :�ŏ��̂P�s�ڂ��΂��Ӗ��B("16 491 5 1 ", )
                                         //_colors+1:�c�̎��̍s���炾��Ƃ����ӁB
                                         //-1       :�z�񂾂���Y����-1
    _num_color_pixels = 0;
    for (int i = 0; i < _height; i++) {
        for (int j = 0; j < _width; j++) {
            if (_pixels[i][j] != _c_px_non) {
                _num_color_pixels++;
            }
        }
    }
}

GgafXpm::~GgafXpm() {
    for (int i = 0; i < _colors; i++) {
        GgafRgb* pRgb = _mapCharRgb[_vecColorChar[i]];
        GGAF_DELETE(pRgb);
    }
}

//static const char* ttt[] = {
///* columns rows colors chars-per-pixel */
//"16 491 5 1 ",               [0]
//"  c #000000",               [1]
//". c #008000",               [2]
//"X c #E08000",               [3]
//"o c #4665A2",               [4]
//"O c None",                  [5]
///* pixels */
//"OOOOOOOOOOOOOOOO",          [6]
//"OOOOOOOOOOOOOOOO",
//"OOOOOOOOOOOOOOOO",
//"OOOOOOOOOOOOOOOO",
//"OOOXXXXXXXOXXOOO",
//"OOOOOOOOOOOOOOOO"
//...
//}

