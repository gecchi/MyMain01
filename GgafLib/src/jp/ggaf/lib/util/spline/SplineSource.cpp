#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;


SplineSource::SplineSource(SplineLine* prm_pSp) : GgafObject() {
    _idstr = "Nothing";
    _pSp = prm_pSp;
    _accuracy = _pSp->_accuracy;
    _is_create_SplineLine = false;
}

SplineSource::SplineSource(char* prm_idstr)  : GgafObject() {
    _idstr = std::string(prm_idstr);
    _accuracy = 1.0;
    std::string data_filename = PROPERTY::DIR_SPLINE + _idstr;// + ".spls";
    std::ifstream ifs(data_filename.c_str());
    if (ifs.fail()) {
        throwGgafCriticalException("SplineSource::SplineSource "<<data_filename<<" ���J���܂���");
    }
    double p[MaxSplineSize][3];
    std::string line;
    int n = 0;
    while( getline(ifs,line) ) {
        if (UTIL::trim(line).size() == 0 ) continue;
        if (line.c_str()[0] == '#') continue;

        LOOP_SPLFILE:

        if (line.find("[BASEPOINT]") != std::string::npos) {
            while( getline(ifs,line) ) {
                if (UTIL::trim(line).size() == 0 ) {
                    break;
                }
                if (line.c_str()[0] == '#') continue;
                if (line.c_str()[0] == '[') goto LOOP_SPLFILE;
                std::istringstream iss(line);
                iss >> p[n][0];
                iss >> p[n][1];
                iss >> p[n][2];
                n++;
                if (n >= MaxSplineSize) {
                    throwGgafCriticalException("SplineSource::SplineSource "<<_idstr<<" �|�C���g��"<<MaxSplineSize<<"�𒴂��܂����B");
                }
            }
        }
        if (line.find("[ACCURACY]") != std::string::npos) {
            while( getline(ifs,line) ) {
                if (UTIL::trim(line).size() == 0 ) break;
                if (line.c_str()[0] == '#') continue;
                if (line.c_str()[0] == '[') goto LOOP_SPLFILE;
                std::istringstream iss(line);
                iss >> _accuracy;
            }
        }
    }
    if (int(_accuracy*100000000) == 0) {
        throwGgafCriticalException("SplineSource::SplineSource "<<_idstr<<" [ACCURACY] ���w�肳��Ă܂���B");
    }
    if (n == 0) {
        throwGgafCriticalException("SplineSource::SplineSource "<<_idstr<<" [BASEPOINT] �ɍ��W������܂���B");
    }
    for (int i = 0; i < n; i++) {
        if (p[i][0] > GgafDxUniverse::_X_goneRight*0.9999) {
            p[i][0] = GgafDxUniverse::_X_goneRight*0.9999;
        }
        if (p[i][0] < GgafDxUniverse::_X_goneLeft*0.9999) {
            p[i][0] = GgafDxUniverse::_X_goneLeft*0.9999;
        }
        if (p[i][1] > GgafDxUniverse::_Y_goneTop*0.9999) {
            p[i][1] = GgafDxUniverse::_Y_goneTop*0.9999;
        }
        if (p[i][1] < GgafDxUniverse::_Y_goneBottom*0.9999) {
            p[i][1] = GgafDxUniverse::_Y_goneBottom*0.9999;
        }
        if (p[i][2] > GgafDxUniverse::_Z_goneFar*0.9999) {
            p[i][2] = GgafDxUniverse::_Z_goneFar*0.9999;
        }
        if (p[i][2] < GgafDxUniverse::_Z_goneNear*0.9999) {
            p[i][2] = GgafDxUniverse::_Z_goneNear*0.9999;
        }
    }
    _pSp = NEW SplineLine(p, n, _accuracy);
    _is_create_SplineLine = true;
}

//��������
//�R���X�g���N�^�œǂݍ��� spl �t�@�C���̃t�H�[�}�b�g
//--------------------------------------------
//[BASEPOINT]
//#       X         Y         Z
//-1.724577  0.000000  0.000000
//-0.964337 -0.088378 -0.344892
//-0.501305 -0.055518 -0.298879
//-0.179336 -0.031628 -0.240141
// 0.123544 -0.016126 -0.165195
// 0.362343  0.000000  0.000000
// 0.545634  0.038709  0.176104
// 0.704048  0.173192  0.372772
// 0.864812  0.444651  0.516556
// 1.055714  0.626849  0.569336
// 1.246407  0.655359  0.547772
// 1.365876  0.590994  0.453279
// 1.388259  0.465998  0.332581
// 1.362117  0.328636  0.211183
// 1.242692  0.226675  0.087900
// 1.064405  0.202917  0.000000
// 0.920421  0.202917  0.000000
//
//[ACCURACY]
//0.2
//--------------------------------------------

//[BASEPOINT]
//�X�v���C���Ȑ���̐���_�� X Y Z �Őݒ�B
//�w��ł���|�C���g���͍ő�1000�܂�
//���@�̈ړ��͈͂� -1.0 �` 1.0 �Ƃ��Đݒ肷��B
//�A���A���̃X�v���C�����W�́A��΍��W�Ƃ��Ĉړ����s���L���������邵�A
//�n�_���L�����̌����_�̍��W�Ƃ����A����_�͑��΍��W�Ƃ��Ĉړ�����L����������A
//�����̐ݒ�͊e�L�����̃v���O�����ɑg�ݍ��܂�Ă���A�R�R�ł̎w��͕s�B
//
//[ACCURACY]
//�X�v���C���Ȑ��̐��x�BBASEPOINT�Ŏw�肵������_�`����_�̊Ԃɂǂ̂��炢�̕⊮�_��ǉ����āA�܂�����Ȃ߂炩�ȋȐ��ɋ߂Â��邩�Ƃ��������B
//1.0  ���w�肷��Ɛ���_�`����_�̊Ԃɕ⊮�_�͑}�����ꂸ�ABASEPOINT�w��ʂ�̂܂܂ƂȂ�B
//0.5  ���w�肷��Ɗe����_�`����_�ɂ��āA2���������_�ɕ⊮�_���v�Z����đ}�������B(�܂�⊮�_��1�}�������)
//0.25 ���w�肷��Ɗe����_�`����_�ɂ��āA4���������_�ɕ⊮�_���v�Z����đ}�������B(�܂�⊮�_��3�}�������)
//0.1  ���w�肷��Ɗe����_�`����_�ɂ��āA10���������_�ɕ⊮�_���v�Z����đ}�������B(�܂�⊮�_��9�}�������)
//0.01 ���w�肷��Ɗe����_�`����_�ɂ��āA100���������_�ɕ⊮�_���v�Z����đ}�������B(�܂�⊮�_��99�}�������)
//�Ƃ�������B
//

SplineSource::~SplineSource() {
    if (_is_create_SplineLine) {
        DELETE_IMPOSSIBLE_NULL(_pSp);
    }
}
