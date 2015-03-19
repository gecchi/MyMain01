#include "jp/ggaf/lib/util/spline/SplineSource.h"

#include <fstream>
#include "jp/ggaf/dxcore/scene/GgafDxUniverse.h"
#include "jp/ggaf/lib/util/spline/SplineLine.h"
#include "jp/ggaf/lib/GgafLibProperties.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

SplineSource::SplineSource(SplineLine* prm_pSp) : GgafObject() {
    _idstr = "Nothing";
    _pSp = prm_pSp;
    _is_create_SplineLine = false;
}

SplineSource::SplineSource(const char* prm_idstr)  : GgafObject() {
    _idstr = std::string(prm_idstr);
    double accuracy = 1.0;
    SplineLine::RotMat rotmat;
    std::string data_filename = PROPERTY::DIR_SPLINE + _idstr;// + ".spls";
    std::ifstream ifs(data_filename.c_str());
    if (ifs.fail()) {
        throwGgafCriticalException("SplineSource::SplineSource "<<data_filename<<" ���J���܂���");
    }
    double p[MaxSplineSize][3];
    std::string line;
    int n = 0;
    int d = 0;
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
                if (iss.fail()) {
                    throwGgafCriticalException("SplineSource::SplineSource "<<_idstr<<" [BASEPOINT]�s���Ȑ��l�f�[�^�ł� line=["<<line<<"]");
                }
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
                iss >> accuracy;
                if (iss.fail()) {
                    throwGgafCriticalException("SplineSource::SplineSource "<<_idstr<<" [ACCURACY]�s���Ȑ��l�f�[�^�ł� line=["<<line<<"]");
                }
            }
        }
        if (line.find("[ADJUST_MAT]") != std::string::npos) {
            while( getline(ifs,line) ) {
                if (UTIL::trim(line).size() == 0 ) break;
                if (line.c_str()[0] == '#') continue;
                if (line.c_str()[0] == '[') goto LOOP_SPLFILE;
                std::istringstream iss(line);
                if (d == 0) {
                    iss >> rotmat._11; iss >> rotmat._12; iss >> rotmat._13; iss >> rotmat._14;
                } else if (d == 1) {
                    iss >> rotmat._21; iss >> rotmat._22; iss >> rotmat._23; iss >> rotmat._24;
                } else if (d == 2) {
                    iss >> rotmat._31; iss >> rotmat._32; iss >> rotmat._33; iss >> rotmat._34;
                } else if (d == 3) {
                    iss >> rotmat._41; iss >> rotmat._42; iss >> rotmat._43; iss >> rotmat._44;
                } else {
                    throwGgafCriticalException("SplineSource::SplineSource "<<_idstr<<" [ADJUST_MAT] �̃f�[�^���������ł��B�S��S�s�̍s���ݒ肵�Ă��������B");
                }
                if (iss.fail()) {
                    throwGgafCriticalException("SplineSource::SplineSource "<<_idstr<<" [ADJUST_MAT] �s���Ȑ��l�f�[�^�ł� line=["<<line<<"]");
                }
                d++;
            }
        }
    }
    if (int(accuracy*100000000) == 0) {
        throwGgafCriticalException("SplineSource::SplineSource "<<_idstr<<" [ACCURACY] ���w�肳��Ă܂���B");
    }
    if (n == 0) {
        throwGgafCriticalException("SplineSource::SplineSource "<<_idstr<<" [BASEPOINT] �ɍ��W������܂���B");
    }
    if (d != 0 && d != 4) {
        throwGgafCriticalException("SplineSource::SplineSource "<<_idstr<<" [ADJUST_MAT] �̃f�[�^�������r���[�ł��B�S��S�s�̍s���ݒ肵�Ă��������B");
    }
    for (int i = 0; i < n; i++) {
        if (p[i][0] > GgafDxUniverse::_x_gone_right*0.9999) {
            p[i][0] = GgafDxUniverse::_x_gone_right*0.9999;
        }
        if (p[i][0] < GgafDxUniverse::_x_gone_left*0.9999) {
            p[i][0] = GgafDxUniverse::_x_gone_left*0.9999;
        }
        if (p[i][1] > GgafDxUniverse::_y_gone_top*0.9999) {
            p[i][1] = GgafDxUniverse::_y_gone_top*0.9999;
        }
        if (p[i][1] < GgafDxUniverse::_y_gone_bottom*0.9999) {
            p[i][1] = GgafDxUniverse::_y_gone_bottom*0.9999;
        }
        if (p[i][2] > GgafDxUniverse::_z_gone_far*0.9999) {
            p[i][2] = GgafDxUniverse::_z_gone_far*0.9999;
        }
        if (p[i][2] < GgafDxUniverse::_z_gone_near*0.9999) {
            p[i][2] = GgafDxUniverse::_z_gone_near*0.9999;
        }
    }
    if (d == 4) {
        _pSp = NEW SplineLine(p, n, accuracy, rotmat);
    } else {
        _pSp = NEW SplineLine(p, n, accuracy);
    }
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
//[ADJUST_MAT]
//�ϊ��s��(4x4)��ݒ肵�ABASEPOINT���W���̕␳���\�ł��B
//��ł� ����BASEPOINT�̍��W�ɁAX����5.0�ړ���90�xY���� ���s���␳�̕ϊ��s��ł��B
//
//0		0		-1		0
//0		1		0		0
//1		0		0		0
//0		0		-5.0	1
//
//���� ADJUST_MAT �ȗ������ꍇ�́A���̒P�ʍs�񂪐ݒ肳�ꂽ���̂Ƃ��܂��B
//
//1		0		0		0
//0		1		0		0
//0		0		1		0
//0		0		0		1


SplineSource::~SplineSource() {
    if (_is_create_SplineLine) {
        GGAF_DELETE(_pSp);
    }
}
