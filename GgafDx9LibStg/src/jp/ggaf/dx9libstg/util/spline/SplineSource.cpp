#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


#define MAX_SP_POINT 1000

SplineSource::SplineSource(char* prm_idstr)  : GgafObject() {
    _accuracy = 1.0;
    _spent_frame = 1;
    _ang_veloRzRyMv = 0;
    _classname = "";
    string data_filename = CFG_PROPERTY(DIR_SPLINE_DATA) + string(prm_idstr) + ".spl";
    ifstream ifs(data_filename.c_str());
    if (ifs.fail()) {
        throwGgafCriticalException("SplineSource::SplineSource "<<prm_idstr<<" ���J���܂���");
    }
    double p[MAX_SP_POINT][3];
    string line;
    int n = 0;
    while( getline(ifs,line) ) {
        if (line.size() == 0 ) continue;
        if (line.c_str()[0] == '#') continue;

        LOOP_SPLFILE:
        if (line.find("[CLASS]") != string::npos) {
            while( getline(ifs,line) ) {
                if (line.size() == 0 ) break;
                if (line.c_str()[0] == '#') continue;
                if (line.c_str()[0] == '[') goto LOOP_SPLFILE;
                istringstream iss(line);
                iss >> _classname;
                if (_classname == "FixedFrameSplineProgram") {
                    iss >> _spent_frame;
                    iss >> _ang_veloRzRyMv;
                } else if (_classname == "FixedVelocitySplineProgram") {
                    iss >> _ang_veloRzRyMv;
                    _spent_frame = 0;
                }
            }
        }
        if (line.find("[BASEPOINT]") != string::npos) {
            while( getline(ifs,line) ) {
                if (line.size() == 0 ) break;
                if (line.c_str()[0] == '#') continue;
                if (line.c_str()[0] == '[') goto LOOP_SPLFILE;
                istringstream iss(line);
                iss >> p[n][0];
                iss >> p[n][1];
                iss >> p[n][2];
                n++;
#ifdef MY_DEBUG
                if (n >= MAX_SP_POINT) {
                    throwGgafCriticalException("SplineSource::SplineSource "<<prm_idstr<<" �|�C���g��"<<MAX_SP_POINT<<"�𒴂��܂����B");
                }
#endif
            }
        }
        if (line.find("[ACCURACY]") != string::npos) {
            while( getline(ifs,line) ) {
                if (line.size() == 0 ) break;
                if (line.c_str()[0] == '#') continue;
                if (line.c_str()[0] == '[') goto LOOP_SPLFILE;
                istringstream iss(line);
                iss >> _accuracy;
            }
        }
    }
#ifdef MY_DEBUG
    if (_classname.length() == 0) {
        throwGgafCriticalException("SplineSource::SplineSource "<<prm_idstr<<" _classname ���w�肳��Ă܂���B");
    }
    if (n == 0) {
        throwGgafCriticalException("SplineSource::SplineSource "<<prm_idstr<<" �|�C���g������܂���B");
    }
#endif
    //-1.0 �` 1.0 �� ���@�̈ړ��\�͈͂Ƃ���
    for (int i = 0; i < n; i++) {
//        p[i][0] = p[i][0] * MyShip::_lim_front; //X
//        p[i][1] = p[i][1] * MyShip::_lim_top;   //Y
//        p[i][2] = p[i][2] * MyShip::_lim_zleft; //Z

        if (p[i][0] > GgafDx9Universe::_X_goneRight*0.9) {
            p[i][0] = GgafDx9Universe::_X_goneRight*0.9;
        }
        if (p[i][0] < GgafDx9Universe::_X_goneLeft*0.9) {
            p[i][0] = GgafDx9Universe::_X_goneLeft*0.9;
        }
        if (p[i][1] > GgafDx9Universe::_Y_goneTop*0.9) {
            p[i][1] = GgafDx9Universe::_Y_goneTop*0.9;
        }
        if (p[i][1] < GgafDx9Universe::_Y_goneBottom*0.9) {
            p[i][1] = GgafDx9Universe::_Y_goneBottom*0.9;
        }
        if (p[i][2] < GgafDx9Universe::_Z_goneFar*0.9) {
            p[i][2] = GgafDx9Universe::_Z_goneFar*0.9;
        }
        if (p[i][2] < GgafDx9Universe::_Z_goneNear*0.9) {
            p[i][2] = GgafDx9Universe::_Z_goneNear*0.9;
        }
    }
    _pSp = NEW Spline3D(p, n, _accuracy);
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
//
//[CLASS]
//FixedFrameSplineProgram 420 6000
//--------------------------------------------

//[BASEPOINT]
//�X�v���C���Ȑ���̊�_�� X Y Z �Őݒ�B
//�w��ł���|�C���g���͍ő�1000�܂�
//���@�̈ړ��͈͂� -1.0 �` 1.0 �Ƃ��Đݒ肷��B
//�A���A���̃X�v���C�����W�́A��΍��W�Ƃ��Ĉړ����s���L���������邵�A
//�n�_���L�����̌����_�̍��W�Ƃ����A��_�͑��΍��W�Ƃ��Ĉړ�����L����������A
//�����̐ݒ�͊e�L�����̃v���O�����ɑg�ݍ��܂�Ă���A�R�R�ł̎w��͕s�B
//
//[ACCURACY]
//�X�v���C���Ȑ��̐��x�BBASEPOINT�Ŏw�肵����_�`��_�̊Ԃɂǂ̂��炢�̕⊮�_��ǉ����āA�܂�����Ȃ߂炩�ȋȐ��ɋ߂Â��邩�Ƃ��������B
//1.0  ���w�肷��Ɗ�_�`��_�̊Ԃɕ⊮�_�͑}�����ꂸ�ABASEPOINT�w��ʂ�̂܂܂ƂȂ�B
//0.5  ���w�肷��Ɗe��_�`��_�ɂ��āA2���������_�ɕ⊮�_���v�Z����đ}�������B(�܂�⊮�_��1�}�������)
//0.25 ���w�肷��Ɗe��_�`��_�ɂ��āA4���������_�ɕ⊮�_���v�Z����đ}�������B(�܂�⊮�_��3�}�������)
//0.1  ���w�肷��Ɗe��_�`��_�ɂ��āA10���������_�ɕ⊮�_���v�Z����đ}�������B(�܂�⊮�_��9�}�������)
//0.01 ���w�肷��Ɗe��_�`��_�ɂ��āA100���������_�ɕ⊮�_���v�Z����đ}�������B(�܂�⊮�_��99�}�������)
//�Ƃ�������B
//
//[CLASS]
//�X�v���C���N���X���w�肷��B�\���͈ȉ��̂Q��ނ̂�
//-------------------------------------------------------------
//FixedFrameSplineProgram <spent_frame> <ang_veloRzRyMv>
//����
//FixedVelocitySplineProgram <ang_veloRzRyMv>
//-------------------------------------------------------------
//
//FixedFrameSplineProgram �E�E�E �X�v���C���̊J�n�_�`�I���_�̈ړ����A����(�t���[��)�Œ�ňړ�������B
//<spent_frame>   �E�E�E ��₷�t���[����
//<ang_veloRzRyMv> �E�E�E ���t���[�������]���\�ȍő�p(1000 �� 1�x�j
//�e�L�������ێ����Ă���ړ����x�͖�������܂��B
//�X�v���C���Ȑ��̓_�̌��Ɣ�₷�t���[��������v�Z���ꂽ�ړ����x������L�����̑��x�l�ɏ㏑���ݒ肳��܂��B
//���̂��߁A�X�v���C���Ȑ��̓_�̖��x���Z���Ƃ���̓X�s�[�h���x���A�_�̖��x�������Ƃ���̓X�s�[�h�������ړ��ƂȂ�܂��B
//
//FixedVelocitySplineProgram �E�E�E �X�v���C���̊J�n�_�`�I���_�̈ړ����A���x�Œ�ňړ�������B
//<ang_veloRzRyMv> �E�E�E ���t���[�������]���\�ȍő�p(1000 �� 1�x�j
//�e�L�������ێ����Ă���ړ����x�������Ǝg�p����܂��B
//�X�v���C���Ȑ��̓_�̖��x���X�s�[�h�ɉe�����܂���B



SplineProgram* SplineSource::makeSplineProgram(GgafDx9GeometricActor* prm_pForWhichActor) {
    SplineProgram* pSpProg = NULL;
    if (_classname.find("FixedFrameSplineProgram") != string::npos) {
        pSpProg = NEW FixedFrameSplineProgram(prm_pForWhichActor, _pSp, _spent_frame, _ang_veloRzRyMv);
    } else if (_classname.find("FixedVelocitySplineProgram") != string::npos) {
        pSpProg = NEW FixedVelocitySplineProgram(prm_pForWhichActor, _pSp, _ang_veloRzRyMv);
    } else {
        throwGgafCriticalException("SplineSource::makeSplineProgram _classname="<<_classname<< "�͕s���ȃN���X�ł�");
    }
    return pSpProg;
}

SplineSource::~SplineSource() {
    DELETE_IMPOSSIBLE_NULL(_pSp);
}
