#include "jp/ggaf/core/util/Xpm.h"

#include "jp/ggaf/core/util/Rgb.h"
#include <sstream>
#include <string>
#include <vector>
#include <map>

using namespace GgafCore;

Xpm::Xpm(const char** prm_xpm) : Object() {
    const char** xpm_hd = prm_xpm;
    _width = 0;
    _height = 0;
    _colors = 0;
    _char_on_pixel = 0;
    _c_px_non = '\0';
    _mapCharRgb['\0'] = NEW Rgb("#000000");

    std::istringstream line0(xpm_hd[0]); //"16 491 5 1 "  <width/cols> <height/rows> <colors> <char on pixel>
    line0 >> _width >> _height >> _colors >> _char_on_pixel;  //char on pixel �� 1 �����Ή����Ă��Ȃ��E�E�E
    if (line0.fail()) {
        throwCriticalException("Xpm::Xpm() �s���ȃw�b�_�f�[�^�ł� line0=["<<line0.str()<<"]");
    }
    if (_char_on_pixel != 1) {
        throwCriticalException("Xpm::Xpm() _char_on_pixel ��1���������Ή����Ă��܂���B�F�������Ȃ����Ă��������Bline0=["<<line0.str()<<"]");
    }
    //"X    c #E08000"
    for (int i = 0; i < _colors; i++) {
        const char* p = xpm_hd[i + 1]; //�P���������Ή�
        char c = (*p);
        _vecColorChar.push_back(c);
        p++;
        std::istringstream line(p); // "    c #E08000"
        char dummy = '\0';
        std::string str_color = "";
        line >> dummy >> str_color; //dummy='c', str_color="#E08000"
        if (str_color == "None" || str_color == "none" || str_color == "") {
            _c_px_non = c;
            _mapCharRgb[c] = NEW Rgb("#000000");
        } else {
            _mapCharRgb[c] = NEW Rgb(str_color);
        }
    }
    //pixels �̓w�b�_�[�ȍ~�̔z��
    const char** pixels = &(prm_xpm[1+_colors+1 -1]); //1+       :�ŏ��̂P�s�ڂ��΂��Ӗ��B("16 491 5 1 ", )
                                                      //_colors+1:�c�̎��̍s���炾��Ƃ����ӁB
                                                      //-1       :�z�񂾂���Y����-1
    _num_color_pixels = 0;
    _pixels = NEW char*[_height];
    for (int i = 0; i < _height; i++) {
        _pixels[i] = NEW char[_width];
        for (int j = 0; j < _width; j++) {
            if (pixels[i][j] == '\0') {
                throwCriticalException("Xpm::Xpm() �c���̐��ƃf�[�^����v���Ă��܂���");
            } else {
                _pixels[i][j] = pixels[i][j]; //�R�s�[
                if (_pixels[i][j] != _c_px_non) {
                    _num_color_pixels++;
                }
            }
        }
    }
}

Xpm::~Xpm() {
    Rgb* p1 = _mapCharRgb['\0'];
    GGAF_DELETE(p1);
    for (int i = 0; i < _colors; i++) {
        Rgb* pRgb = _mapCharRgb[_vecColorChar[i]];
        GGAF_DELETE(pRgb);
    }
    for (int i = 0; i < _height; i++) {
        char* p2 = _pixels[i];
        GGAF_DELETEARR(p2);
    }
    GGAF_DELETEARR(_pixels);
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

