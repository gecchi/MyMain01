#ifndef GGAF_CORE_XPM_H_
#define GGAF_CORE_XPM_H_
#include "jp/ggaf/core/Object.h"

#include <map>
#include <vector>

namespace GgafCore {

/**
 * �Ȉ�XPM(Pixmap)�x���N���X .
 * @version 1.00
 * @since 2013/07/16
 * @author Masatoshi Tsuge
 */
class Xpm : public Object {
public:
    /** [r]���s�N�Z���� */
    int _width;
    /** [r]�����s�N�Z���� */
    int _height;
    /** [r]�F�� */
    int _colors;
    /** [r]�����F�ł͖����s�N�Z���̐� */
    int _num_color_pixels;
    /** [r]�����s�N�Z���̕��� */
    char _c_px_non;

    int _char_on_pixel;

    /** [r]�s�N�Z���F�̕����̔z�� */
    std::vector<char> _vecColorChar;
    /** [r]�s�N�Z���F�̕����ɑΉ�����A���ۂ�RGB�l */
    std::map<char, Rgb*> _mapCharRgb;
    char** _pixels;
public:
    /**
     * �R���X�g���N�^ .
     * @param prm_xpm Pixmap�ւ̃|�C���^�B���l��ێ����Ȃ��̂ŃX�R�[�v�ɒ��ӁB(static �Ȃǂ�z��)
     */
    Xpm(const char** prm_xpm);

    /**
     * Pixmap�̗񐔂��擾 .
     * @return ��
     */
    inline int getWidth() {
        return _width;
    }

    /**
     * Pixmap�̍s�����擾 .
     * @return �s��
     */
    inline int getHeight() {
        return _height;
    }

    /**
     * Pixmap�̂���Ă���F�̐����擾 .
     * @return �F�̐�
     */
    inline int getColorNum() {
        return _colors;
    }

    /**
     * Pixmap�̃s�N�Z���̐�(�����F������)���擾 .
     * @return
     */
    inline int getPixelNum() {
        return _num_color_pixels;
    }

    /**
     * Pixmap�̎w��̃s�N�Z���̐F���擾 .
     * @param prm_row_idx ���s�ڂ����w��(0�`)
     * @param prm_col_idx ����ڂ����w��(0�`)
     * @return �F
     */
    inline Rgb* getColor(int prm_row_idx, int prm_col_idx) {
        Rgb* r = nullptr;
        if (prm_row_idx < _height && prm_col_idx < _width) {
            //�͈͓�
            r = _mapCharRgb[_pixels[prm_row_idx][prm_col_idx]];
        } else {
            //�͈͊O
            r = _mapCharRgb['\0'];
        }
        return r;
    }

    /**
     * Pixmap�̎w��̃s�N�Z���̐F�������F���ۂ��擾 .
     * @param prm_row_idx ���s�ڂ����w��(0�`)
     * @param prm_col_idx ����ڂ����w��(0�`)
     * @return true:�����F / false:�����F�ȊO
     */
    inline bool isNonColor(int prm_row_idx, int prm_col_idx) {
        if (prm_row_idx < _height && prm_col_idx < _width) {
            //�͈͓�
            if (_pixels[prm_row_idx][prm_col_idx] == _c_px_non) {
                return true;
            } else {
                return false;
            }
        } else {
            //�͈͊O
            return true;
        }
    }

    virtual ~Xpm();
};
}
#endif /*GGAF_CORE_XPM_H_*/
