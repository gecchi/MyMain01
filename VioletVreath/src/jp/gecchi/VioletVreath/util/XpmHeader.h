#ifndef XPMHEADER_H_
#define XPMHEADER_H_
#include "VioletVreath.h"
#include "jp/ggaf/core/GgafObject.h"

#include <map>
#include <vector>

namespace VioletVreath {

/**
 * �Ȉ�XPM(Pixmap)�x���N���X .
 * @version 1.00
 * @since 2013/07/16
 * @author Masatoshi Tsuge
 */
class XpmHeader : public GgafCore::GgafObject {
public:
    /** [r]�� */
    int columns_;
    /** [r]�s�� */
    int rows_;
    /** [r]�F�� */
    int colors_;
    /** [r]�����F�ł͖����s�N�Z���̐� */
    int num_color_pixels_;
    /** [r]�����s�N�Z���̕��� */
    char c_px_non_;
    /** [r]�s�N�Z���F�̕����̔z�� */
    std::vector<char> c_px;
    /** [r]�s�N�Z���F�̕����ɑΉ�����A���ۂ�RGB�l */
    std::map<char, GgafCore::GgafRgb*> c_rgb_;
    const char** xpm_hd_;
    const char** pixels_;
public:
    /**
     * �R���X�g���N�^ .
     * @param prm_xpm Pixmap�ւ̃|�C���^�B���l��ێ����Ȃ��̂ŃX�R�[�v�ɒ��ӁB(static �Ȃǂ�z��)
     */
    XpmHeader(const char** prm_xpm);

    /**
     * Pixmap�̗񐔂��擾 .
     * @return ��
     */
    inline int getColumns() {
        return columns_;
    }

    /**
     * Pixmap�̍s�����擾 .
     * @return �s��
     */
    inline int getRows() {
        return rows_;
    }

    /**
     * Pixmap�̂���Ă���F�̐����擾 .
     * @return �F�̐�
     */
    inline int getColorNum() {
        return colors_;
    }

    /**
     * Pixmap�̃s�N�Z���̐�(�����F������)���擾 .
     * @return
     */
    inline int getPixelNum() {
        return num_color_pixels_;
    }

    /**
     * Pixmap�̎w��̃s�N�Z���̐F���擾 .
     * @param prm_row ���s�ڂ����w��
     * @param prm_col ����ڂ����w��
     * @return �F
     */
    inline GgafCore::GgafRgb* getColor(int prm_row, int prm_col) {
        return c_rgb_[pixels_[prm_row][prm_col]];
    }

    /**
     * Pixmap�̎w��̃s�N�Z���̐F�������F���ۂ��擾 .
     * @param prm_row ���s�ڂ����w��
     * @param prm_col ����ڂ����w��
     * @return true:�����F / false:�����F�ȊO
     */
    inline bool isNonColor(int prm_row, int prm_col) {
        if (pixels_[prm_row][prm_col] == c_px_non_) {
            return true;
        } else {
            return false;
        }
    }

    virtual ~XpmHeader();
};
}
#endif /*XPMHEADER_H_*/
