#ifndef XPMHEADER_H_
#define XPMHEADER_H_
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
    virtual ~XpmHeader();
};
}
#endif /*XPMHEADER_H_*/
