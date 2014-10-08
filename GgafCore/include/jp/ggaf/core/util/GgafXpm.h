#ifndef GGAFCORE_GGAFXPM_H_
#define GGAFCORE_GGAFXPM_H_
#include "jp/ggaf/core/GgafObject.h"

#include <map>
#include <vector>

namespace GgafCore {

/**
 * �Ȉ�XPM(Pixmap)�x���N���X .
 * @version 1.00
 * @since 2013/07/16
 * @author Masatoshi Tsuge
 */
class GgafXpm : public GgafCore::GgafObject {
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
    /** [r]�s�N�Z���F�̕����̔z�� */
    std::vector<char> _vecColorChar;
    /** [r]�s�N�Z���F�̕����ɑΉ�����A���ۂ�RGB�l */
    std::map<char, GgafCore::GgafRgb*> _mapCharRgb;
    const char** _xpm_hd;
    const char** _pixels;
public:
    /**
     * �R���X�g���N�^ .
     * @param prm_xpm Pixmap�ւ̃|�C���^�B���l��ێ����Ȃ��̂ŃX�R�[�v�ɒ��ӁB(static �Ȃǂ�z��)
     */
    GgafXpm(const char** prm_xpm);

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
     * @param prm_row ���s�ڂ����w��
     * @param prm_col ����ڂ����w��
     * @return �F
     */
    inline GgafCore::GgafRgb* getColor(int prm_row, int prm_col) {
        return _mapCharRgb[_pixels[prm_row][prm_col]];
    }

    /**
     * Pixmap�̎w��̃s�N�Z���̐F�������F���ۂ��擾 .
     * @param prm_row ���s�ڂ����w��
     * @param prm_col ����ڂ����w��
     * @return true:�����F / false:�����F�ȊO
     */
    inline bool isNonColor(int prm_row, int prm_col) {
        if (_pixels[prm_row][prm_col] == _c_px_non) {
            return true;
        } else {
            return false;
        }
    }

    virtual ~GgafXpm();
};
}
#endif /*GGAFCORE_GGAFXPM_H_*/
