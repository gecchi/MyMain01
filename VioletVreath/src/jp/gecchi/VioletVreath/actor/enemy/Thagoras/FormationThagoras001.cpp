#include "stdafx.h"
#include "FormationThagoras001.h"

#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Thagoras/EnemyThagoras.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;



uint32_t FormationThagoras001::bitmap_[96] = {
      0x0F,  // 0b00001111
      0x3F,  // 0b00111111
      0x7F,  // 0b01111111
      0x70,  // 0b01110000
      0x7F,  // 0b01111111
      0x3F,  // 0b00111111
      0x0F,  // 0b00001111
      0x00,  // 0b00000000
      0x00,  // 0b00000000
      0x44,  // 0b01000100
      0x7D,  // 0b01111101
      0x7D,  // 0b01111101
      0x7D,  // 0b01111101
      0x40,  // 0b01000000
      0x00,  // 0b00000000
      0x00,  // 0b00000000
      0x38,  // 0b00111000
      0x7C,  // 0b01111100
      0x7C,  // 0b01111100
      0x44,  // 0b01000100
      0x7C,  // 0b01111100
      0x7C,  // 0b01111100
      0x38,  // 0b00111000
      0x00,  // 0b00000000
      0x00,  // 0b00000000
      0x41,  // 0b01000001
      0x7F,  // 0b01111111
      0x7F,  // 0b01111111
      0x7F,  // 0b01111111
      0x40,  // 0b01000000
      0x00,  // 0b00000000
      0x00,  // 0b00000000
      0x38,  // 0b00111000
      0x7C,  // 0b01111100
      0x7C,  // 0b01111100
      0x54,  // 0b01010100
      0x5C,  // 0b01011100
      0x5C,  // 0b01011100
      0x18,  // 0b00011000
      0x00,  // 0b00000000
      0x04,  // 0b00000100
      0x3F,  // 0b00111111
      0x7F,  // 0b01111111
      0x7F,  // 0b01111111
      0x64,  // 0b01100100
      0x64,  // 0b01100100
      0x20,  // 0b00100000
      0x00,  // 0b00000000
      0x0F,  // 0b00001111
      0x3F,  // 0b00111111
      0x7F,  // 0b01111111
      0x70,  // 0b01110000
      0x7F,  // 0b01111111
      0x3F,  // 0b00111111
      0x0F,  // 0b00001111
      0x00,  // 0b00000000
      0x7C,  // 0b01111100
      0x7C,  // 0b01111100
      0x7C,  // 0b01111100
      0x0C,  // 0b00001100
      0x0C,  // 0b00001100
      0x0C,  // 0b00001100
      0x08,  // 0b00001000
      0x00,  // 0b00000000
      0x38,  // 0b00111000
      0x7C,  // 0b01111100
      0x7C,  // 0b01111100
      0x54,  // 0b01010100
      0x5C,  // 0b01011100
      0x5C,  // 0b01011100
      0x18,  // 0b00011000
      0x00,  // 0b00000000
      0x20,  // 0b00100000
      0x74,  // 0b01110100
      0x74,  // 0b01110100
      0x54,  // 0b01010100
      0x7C,  // 0b01111100
      0x7C,  // 0b01111100
      0x78,  // 0b01111000
      0x00,  // 0b00000000
      0x04,  // 0b00000100
      0x3F,  // 0b00111111
      0x7F,  // 0b01111111
      0x7F,  // 0b01111111
      0x64,  // 0b01100100
      0x64,  // 0b01100100
      0x20,  // 0b00100000
      0x00,  // 0b00000000
      0x7F,  // 0b01111111
      0x7F,  // 0b01111111
      0x7F,  // 0b01111111
      0x04,  // 0b00000100
      0x7C,  // 0b01111100
      0x7C,  // 0b01111100
      0x78,  // 0b01111000
      0x00   // 0b00000000
};


char FormationThagoras001::pixmap_[8][9] = {
    "00001111",
    "00112223",
    "01223333",
    "01230000",
    "01223333",
    "00112223",
    "00001111",
    "00000000"
};

FormationThagoras001::FormationThagoras001(const char* prm_name) : FormationThagoras(prm_name, 339) {
    _class_name = "FormationThagoras001";
    row_interval_frames_ = 6;
    column_dY_ = PX_C(40);
    cnt_call_up_line_ = 0;
    apSplManufConn_[0] = connect_SplineManufactureManager("FormationThagoras001");
    apSplManufConn_[1] = connect_SplineManufactureManager("FormationThagoras001");
    apSplManufConn_[2] = connect_SplineManufactureManager("FormationThagoras001");
    apSplManufConn_[3] = connect_SplineManufactureManager("FormationThagoras001");
    apSplManufConn_[4] = connect_SplineManufactureManager("FormationThagoras001");
    apSplManufConn_[5] = connect_SplineManufactureManager("FormationThagoras001");
    apSplManufConn_[6] = connect_SplineManufactureManager("FormationThagoras001");
    apSplManufConn_[7] = connect_SplineManufactureManager("FormationThagoras001");
}

void FormationThagoras001::processBehavior() {
    FormationThagoras::processBehavior();

    if (cnt_call_up_line_ < 8 && canCallUp() && getActiveFrame() % row_interval_frames_ == 0) {

        for (int i = 0; i < 8; i++) {
            if (FormationThagoras001::pixmap_[cnt_call_up_line_][i] != '0') {
                EnemyThagoras* pThagoras = (EnemyThagoras*)callUpMember();
                if (pThagoras) {
                    pThagoras->position(entry_pos_._X,
                                        entry_pos_._Y + (i*column_dY_),
                                        entry_pos_._Z);
                    pThagoras->pKurokoLeader_ = apSplManufConn_[i]->peek()->
                            createKurokoLeader(pThagoras->_pKurokoA);
                }
                if (FormationThagoras001::pixmap_[cnt_call_up_line_][i] == '1') {
                    pThagoras->setMaterialColor(1.0, 0.0, 0.0);
                } else if (FormationThagoras001::pixmap_[cnt_call_up_line_][i] == '2') {
                    pThagoras->setMaterialColor(0.0, 1.0, 0.0);
                } else if (FormationThagoras001::pixmap_[cnt_call_up_line_][i] == '3') {
                    pThagoras->setMaterialColor(0.0, 0.0, 1.0);
                }

            }
        }
        cnt_call_up_line_++;
    }
}

FormationThagoras001::~FormationThagoras001() {
    apSplManufConn_[0]->close();
    apSplManufConn_[1]->close();
    apSplManufConn_[2]->close();
    apSplManufConn_[3]->close();
    apSplManufConn_[4]->close();
    apSplManufConn_[5]->close();
    apSplManufConn_[6]->close();
    apSplManufConn_[7]->close();
}



// [0]        0   0   0   0   1   1   1   1       00001111    0x0F
// [1]        0   0   1   1   1   1   1   1       00111111    0x3F
// [2]        0   1   1   1   1   1   1   1       01111111    0x7F
// [3]        0   1   1   1   0   0   0   0       01110000    0x70
// [4]        0   1   1   1   1   1   1   1       01111111    0x7F
// [5]        0   0   1   1   1   1   1   1       00111111    0x3F
// [6]        0   0   0   0   1   1   1   1       00001111    0x0F
// [7]        0   0   0   0   0   0   0   0       00000000    0x00
// [8]        0   0   0   0   0   0   0   0       00000000    0x00
// [9]        0   1   0   0   0   1   0   0       01000100    0x44
//[10]        0   1   1   1   1   1   0   1       01111101    0x7D
//[11]        0   1   1   1   1   1   0   1       01111101    0x7D
//[12]        0   1   1   1   1   1   0   1       01111101    0x7D
//[13]        0   1   0   0   0   0   0   0       01000000    0x40
//[14]        0   0   0   0   0   0   0   0       00000000    0x00
//[15]        0   0   0   0   0   0   0   0       00000000    0x00
//[16]        0   0   1   1   1   0   0   0       00111000    0x38
//[17]        0   1   1   1   1   1   0   0       01111100    0x7C
//[18]        0   1   1   1   1   1   0   0       01111100    0x7C
//[19]        0   1   0   0   0   1   0   0       01000100    0x44
//[20]        0   1   1   1   1   1   0   0       01111100    0x7C
//[21]        0   1   1   1   1   1   0   0       01111100    0x7C
//[22]        0   0   1   1   1   0   0   0       00111000    0x38
//[23]        0   0   0   0   0   0   0   0       00000000    0x00
//[24]        0   0   0   0   0   0   0   0       00000000    0x00
//[25]        0   1   0   0   0   0   0   1       01000001    0x41
//[26]        0   1   1   1   1   1   1   1       01111111    0x7F
//[27]        0   1   1   1   1   1   1   1       01111111    0x7F
//[28]        0   1   1   1   1   1   1   1       01111111    0x7F
//[29]        0   1   0   0   0   0   0   0       01000000    0x40
//[30]        0   0   0   0   0   0   0   0       00000000    0x00
//[31]        0   0   0   0   0   0   0   0       00000000    0x00
//[32]        0   0   1   1   1   0   0   0       00111000    0x38
//[33]        0   1   1   1   1   1   0   0       01111100    0x7C
//[34]        0   1   1   1   1   1   0   0       01111100    0x7C
//[35]        0   1   0   1   0   1   0   0       01010100    0x54
//[36]        0   1   0   1   1   1   0   0       01011100    0x5C
//[37]        0   1   0   1   1   1   0   0       01011100    0x5C
//[38]        0   0   0   1   1   0   0   0       00011000    0x18
//[39]        0   0   0   0   0   0   0   0       00000000    0x00
//[40]        0   0   0   0   0   1   0   0       00000100    0x04
//[41]        0   0   1   1   1   1   1   1       00111111    0x3F
//[42]        0   1   1   1   1   1   1   1       01111111    0x7F
//[43]        0   1   1   1   1   1   1   1       01111111    0x7F
//[44]        0   1   1   0   0   1   0   0       01100100    0x64
//[45]        0   1   1   0   0   1   0   0       01100100    0x64
//[46]        0   0   1   0   0   0   0   0       00100000    0x20
//[47]        0   0   0   0   0   0   0   0       00000000    0x00
//[48]        0   0   0   0   1   1   1   1       00001111    0xF
//[49]        0   0   1   1   1   1   1   1       00111111    0x3F
//[50]        0   1   1   1   1   1   1   1       01111111    0x7F
//[51]        0   1   1   1   0   0   0   0       01110000    0x70
//[52]        0   1   1   1   1   1   1   1       01111111    0x7F
//[53]        0   0   1   1   1   1   1   1       00111111    0x3F
//[54]        0   0   0   0   1   1   1   1       00001111    0xF
//[55]        0   0   0   0   0   0   0   0       00000000    0x00
//[56]        0   1   1   1   1   1   0   0       01111100    0x7C
//[57]        0   1   1   1   1   1   0   0       01111100    0x7C
//[58]        0   1   1   1   1   1   0   0       01111100    0x7C
//[59]        0   0   0   0   1   1   0   0       00001100    0x0C
//[60]        0   0   0   0   1   1   0   0       00001100    0x0C
//[61]        0   0   0   0   1   1   0   0       00001100    0x0C
//[62]        0   0   0   0   1   0   0   0       00001000    0x08
//[63]        0   0   0   0   0   0   0   0       00000000    0x00
//[64]        0   0   1   1   1   0   0   0       00111000    0x38
//[65]        0   1   1   1   1   1   0   0       01111100    0x7C
//[66]        0   1   1   1   1   1   0   0       01111100    0x7C
//[67]        0   1   0   1   0   1   0   0       01010100    0x54
//[68]        0   1   0   1   1   1   0   0       01011100    0x5C
//[69]        0   1   0   1   1   1   0   0       01011100    0x5C
//[70]        0   0   0   1   1   0   0   0       00011000    0x18
//[71]        0   0   0   0   0   0   0   0       00000000    0x00
//[72]        0   0   1   0   0   0   0   0       00100000    0x20
//[73]        0   1   1   1   0   1   0   0       01110100    0x74
//[74]        0   1   1   1   0   1   0   0       01110100    0x74
//[75]        0   1   0   1   0   1   0   0       01010100    0x54
//[76]        0   1   1   1   1   1   0   0       01111100    0x7C
//[77]        0   1   1   1   1   1   0   0       01111100    0x7C
//[78]        0   1   1   1   1   0   0   0       01111000    0x78
//[79]        0   0   0   0   0   0   0   0       00000000    0x00
//[80]        0   0   0   0   0   1   0   0       00000100    0x04
//[81]        0   0   1   1   1   1   1   1       00111111    0x3F
//[82]        0   1   1   1   1   1   1   1       01111111    0x7F
//[83]        0   1   1   1   1   1   1   1       01111111    0x7F
//[84]        0   1   1   0   0   1   0   0       01100100    0x64
//[85]        0   1   1   0   0   1   0   0       01100100    0x64
//[86]        0   0   1   0   0   0   0   0       00100000    0x20
//[87]        0   0   0   0   0   0   0   0       00000000    0x00
//[88]        0   1   1   1   1   1   1   1       01111111    0x7F
//[89]        0   1   1   1   1   1   1   1       01111111    0x7F
//[90]        0   1   1   1   1   1   1   1       01111111    0x7F
//[91]        0   0   0   0   0   1   0   0       00000100    0x04
//[92]        0   1   1   1   1   1   0   0       01111100    0x7C
//[93]        0   1   1   1   1   1   0   0       01111100    0x7C
//[94]        0   1   1   1   1   0   0   0       01111000    0x78
//[95]        0   0   0   0   0   0   0   0       00000000    0x00

