#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

GroundBoxScene::GroundBoxScene(const char* prm_name) : DefaultScene(prm_name) {

    _area_len = 23;
    _area_height = 24;
    _area_width = 32;
    BoxInfo area[23][24*32] =
    {
        { {7,10,16,{1,11,8,1,1,1}},{7,11,16,{1,1,8,1,1,1}},{7,12,16,{1,1,8,1,1,1}},{7,13,16,{1,1,8,1,1,1}},{7,14,16,{1,1,8,1,1,1}},{7,15,16,{1,1,8,1,1,1}},{7,16,16,{1,1,8,1,1,1}},{7,17,16,{1,1,8,1,1,1}},{7,18,16,{1,1,8,1,1,1}},{7,19,16,{1,1,8,1,1,1}},{7,20,16,{1,1,8,1,1,1}},{7,21,16,{1,1,8,11,1,1}},{8,10,16,{1,11,1,1,1,1}},{8,11,16,{1,1,1,1,1,1}},{8,12,16,{1,1,1,1,1,1}},{8,13,16,{1,1,1,1,1,1}},{8,14,16,{1,1,1,1,1,1}},{8,15,16,{1,1,1,1,1,1}},{8,16,16,{1,1,1,1,1,1}},{8,17,16,{1,1,1,1,1,1}},{8,18,16,{1,1,1,1,1,1}},{8,19,16,{1,1,1,1,1,1}},{8,20,16,{1,1,1,1,1,1}},{8,21,16,{1,1,1,11,1,1}},{9,10,16,{1,11,1,1,1,1}},{9,11,16,{1,1,1,1,1,1}},{9,12,16,{1,1,1,1,1,1}},{9,13,16,{1,1,1,1,1,1}},{9,14,16,{1,1,1,1,1,1}},{9,15,16,{1,1,1,1,1,1}},{9,16,16,{1,1,1,1,1,1}},{9,17,16,{1,1,1,1,1,1}},{9,18,16,{1,1,1,1,1,1}},{9,19,16,{1,1,1,1,1,1}},{9,20,16,{1,1,1,1,1,1}},{9,21,16,{1,1,1,11,1,1}},{10,10,16,{1,11,1,1,1,1}},{10,11,16,{1,1,1,1,1,1}},{10,12,16,{1,1,1,1,1,1}},{10,13,16,{1,1,1,1,1,1}},{10,14,16,{1,1,1,1,1,1}},{10,15,48,{1,1,1,1,1,1}},{10,16,48,{1,1,1,1,1,1}},{10,17,16,{1,1,1,1,1,1}},{10,18,16,{1,1,1,1,1,1}},{10,19,16,{1,1,1,1,1,1}},{10,20,16,{1,1,1,1,1,1}},{10,21,16,{1,1,1,11,1,1}},{11,10,16,{1,11,1,1,1,1}},{11,11,16,{1,1,1,1,1,1}},{11,12,16,{1,1,1,1,1,1}},{11,13,16,{1,1,1,1,1,1}},{11,14,24,{1,1,1,1,1,1}},{11,17,18,{1,1,1,1,1,1}},{11,18,16,{1,1,1,1,1,1}},{11,19,16,{1,1,1,1,1,1}},{11,20,16,{1,1,1,1,1,1}},{11,21,16,{1,1,1,11,1,1}},{12,10,16,{1,11,1,1,1,1}},{12,11,16,{1,1,1,1,1,1}},{12,12,16,{1,1,1,1,1,1}},{12,13,16,{1,1,1,1,1,1}},{12,14,24,{1,1,1,1,1,1}},{12,17,18,{1,1,1,1,1,1}},{12,18,16,{1,1,1,1,1,1}},{12,19,16,{1,1,1,1,1,1}},{12,20,16,{1,1,1,1,1,1}},{12,21,16,{1,1,1,11,1,1}},{13,10,16,{1,11,1,1,1,1}},{13,11,16,{1,1,1,1,1,1}},{13,12,16,{1,1,1,1,1,1}},{13,13,16,{1,1,1,1,1,1}},{13,14,16,{1,1,1,1,1,1}},{13,15,20,{1,1,1,1,1,1}},{13,16,20,{1,1,1,1,1,1}},{13,17,16,{1,1,1,1,1,1}},{13,18,16,{1,1,1,1,1,1}},{13,19,16,{1,1,1,1,1,1}},{13,20,16,{1,1,1,1,1,1}},{13,21,16,{1,1,1,11,1,1}},{14,10,16,{1,11,1,1,1,1}},{14,11,16,{1,1,1,1,1,1}},{14,12,16,{1,1,1,1,1,1}},{14,13,16,{1,1,1,1,1,1}},{14,14,16,{1,1,1,1,1,1}},{14,15,16,{1,1,1,1,1,1}},{14,16,16,{1,1,1,1,1,1}},{14,17,16,{1,1,1,1,1,1}},{14,18,16,{1,1,1,1,1,1}},{14,19,16,{1,1,1,1,1,1}},{14,20,16,{1,1,1,1,1,1}},{14,21,16,{1,1,1,11,1,1}},{15,10,16,{1,11,1,1,1,1}},{15,11,16,{1,1,1,1,1,1}},{15,12,16,{1,1,1,1,1,1}},{15,13,16,{1,1,1,1,1,1}},{15,14,16,{1,1,1,1,1,1}},{15,15,16,{1,1,1,1,1,1}},{15,16,16,{1,1,1,1,1,1}},{15,17,16,{1,1,1,1,1,1}},{15,18,16,{1,1,1,1,1,1}},{15,19,16,{1,1,1,1,1,1}},{15,20,16,{1,1,1,1,1,1}},{15,21,16,{1,1,1,11,1,1}},{16,10,16,{1,11,1,1,1,8}},{16,11,16,{1,1,1,1,1,8}},{16,12,16,{1,1,1,1,1,8}},{16,13,16,{1,1,1,1,1,8}},{16,14,16,{1,1,1,1,1,8}},{16,15,16,{1,1,1,1,1,8}},{16,16,16,{1,1,1,1,1,8}},{16,17,16,{1,1,1,1,1,8}},{16,18,16,{1,1,1,1,1,8}},{16,19,16,{1,1,1,1,1,8}},{16,20,16,{1,1,1,1,1,8}},{16,21,16,{1,1,1,11,1,8}} },
        { {10,14,0,{1,15,11,1,1,1}},{10,15,32,{1,1,11,1,1,1}},{10,16,32,{1,1,11,1,1,1}},{10,17,0,{1,1,11,15,1,1}},{11,14,8,{1,15,1,1,1,1}},{11,17,2,{1,1,1,15,1,1}},{12,14,8,{1,15,1,1,1,1}},{12,17,2,{1,1,1,15,1,1}},{13,14,0,{1,15,1,1,1,11}},{13,15,4,{1,1,1,1,1,11}},{13,16,4,{1,1,1,1,1,11}},{13,17,0,{1,1,1,15,1,11}} },
        { {10,14,0,{1,15,11,1,1,1}},{10,15,32,{1,1,11,1,1,1}},{10,16,32,{1,1,11,1,1,1}},{10,17,0,{1,1,11,15,1,1}},{11,14,8,{1,15,1,1,1,1}},{11,17,2,{1,1,1,15,1,1}},{12,14,8,{1,15,1,1,1,1}},{12,17,2,{1,1,1,15,1,1}},{13,14,0,{1,15,1,1,1,11}},{13,15,4,{1,1,1,1,1,11}},{13,16,4,{1,1,1,1,1,11}},{13,17,0,{1,1,1,15,1,11}} },
        { {10,14,1,{1,15,11,1,1,1}},{10,15,33,{1,1,11,1,1,1}},{10,16,33,{1,1,11,1,1,1}},{10,17,1,{1,1,11,15,1,1}},{11,14,9,{1,15,1,1,1,1}},{11,17,3,{1,1,1,15,1,1}},{12,14,9,{1,15,1,1,1,1}},{12,17,3,{1,1,1,15,1,1}},{13,14,1,{1,15,1,1,1,11}},{13,15,5,{1,1,1,1,1,11}},{13,16,5,{1,1,1,1,1,11}},{13,17,1,{1,1,1,15,1,11}} },
        { {9,13,0,{1,14,10,1,1,1}},{9,14,32,{1,1,10,1,1,1}},{9,15,32,{1,1,10,1,1,1}},{9,16,32,{1,1,10,1,1,1}},{9,17,32,{1,1,10,1,1,1}},{9,18,0,{1,1,10,14,1,1}},{10,13,8,{1,14,1,1,1,1}},{10,18,2,{1,1,1,14,1,1}},{11,13,8,{1,14,1,1,1,1}},{11,18,2,{1,1,1,14,1,1}},{12,13,8,{1,14,1,1,1,1}},{12,18,2,{1,1,1,14,1,1}},{13,13,8,{1,14,1,1,1,1}},{13,18,2,{1,1,1,14,1,1}},{14,13,0,{1,14,1,1,1,10}},{14,14,4,{1,1,1,1,1,10}},{14,15,4,{1,1,1,1,1,10}},{14,16,4,{1,1,1,1,1,10}},{14,17,4,{1,1,1,1,1,10}},{14,18,0,{1,1,1,14,1,10}} },
        { {9,13,0,{1,14,10,1,1,1}},{9,14,32,{1,1,10,1,1,1}},{9,15,32,{1,1,10,1,1,1}},{9,16,32,{1,1,10,1,1,1}},{9,17,32,{1,1,10,1,1,1}},{9,18,0,{1,1,10,14,1,1}},{10,13,8,{1,14,1,1,1,1}},{10,18,2,{1,1,1,14,1,1}},{11,13,8,{1,14,1,1,1,1}},{11,18,2,{1,1,1,14,1,1}},{12,13,8,{1,14,1,1,1,1}},{12,18,2,{1,1,1,14,1,1}},{13,13,8,{1,14,1,1,1,1}},{13,18,2,{1,1,1,14,1,1}},{14,13,0,{1,14,1,1,1,10}},{14,14,4,{1,1,1,1,1,10}},{14,15,4,{1,1,1,1,1,10}},{14,16,4,{1,1,1,1,1,10}},{14,17,4,{1,1,1,1,1,10}},{14,18,0,{1,1,1,14,1,10}} },
        { {9,13,0,{1,14,10,1,1,1}},{9,14,32,{1,1,10,1,1,1}},{9,15,32,{1,1,10,1,1,1}},{9,16,32,{1,1,10,1,1,1}},{9,17,32,{1,1,10,1,1,1}},{9,18,0,{1,1,10,14,1,1}},{10,13,8,{1,14,1,1,1,1}},{10,18,2,{1,1,1,14,1,1}},{11,13,8,{1,14,1,1,1,1}},{11,18,2,{1,1,1,14,1,1}},{12,13,8,{1,14,1,1,1,1}},{12,18,2,{1,1,1,14,1,1}},{13,13,8,{1,14,1,1,1,1}},{13,18,2,{1,1,1,14,1,1}},{14,13,0,{1,14,1,1,1,10}},{14,14,4,{1,1,1,1,1,10}},{14,15,4,{1,1,1,1,1,10}},{14,16,4,{1,1,1,1,1,10}},{14,17,4,{1,1,1,1,1,10}},{14,18,0,{1,1,1,14,1,10}} },
        { {9,13,0,{1,14,10,1,1,1}},{9,14,33,{1,1,10,1,1,1}},{9,15,33,{1,1,10,1,1,1}},{9,16,33,{1,1,10,1,1,1}},{9,17,33,{1,1,10,1,1,1}},{9,18,0,{1,1,10,14,1,1}},{10,13,8,{1,14,1,1,1,1}},{10,18,2,{1,1,1,14,1,1}},{11,13,8,{1,14,1,1,1,1}},{11,18,2,{1,1,1,14,1,1}},{12,13,8,{1,14,1,1,1,1}},{12,18,2,{1,1,1,14,1,1}},{13,13,0,{1,14,1,1,1,11}},{13,14,20,{1,1,1,1,1,11}},{13,15,20,{1,1,1,1,1,11}},{13,16,20,{1,1,1,1,1,11}},{13,17,20,{1,1,1,1,1,11}},{13,18,0,{1,1,1,14,1,11}} },
        { {8,13,0,{1,14,9,1,1,1}},{8,14,32,{1,1,9,1,1,1}},{8,15,32,{1,1,9,1,1,1}},{8,16,32,{1,1,9,1,1,1}},{8,17,32,{1,1,9,1,1,1}},{8,18,0,{1,1,9,14,1,1}},{9,13,8,{1,14,1,1,1,1}},{9,18,2,{1,1,1,14,1,1}},{10,13,8,{1,14,1,1,1,1}},{10,18,2,{1,1,1,14,1,1}},{11,13,8,{1,14,1,1,1,1}},{11,18,2,{1,1,1,14,1,1}},{12,13,0,{1,14,1,1,1,12}},{12,14,20,{1,1,1,1,1,12}},{12,15,20,{1,1,1,1,1,12}},{12,16,20,{1,1,1,1,1,12}},{12,17,20,{1,1,1,1,1,12}},{12,18,0,{1,1,1,14,1,12}} },
        { {8,13,0,{1,14,9,1,1,1}},{8,14,32,{1,1,9,1,1,1}},{8,15,32,{1,1,9,1,1,1}},{8,16,32,{1,1,9,1,1,1}},{8,17,32,{1,1,9,1,1,1}},{8,18,0,{1,1,9,14,1,1}},{9,13,8,{1,14,1,1,1,1}},{9,18,2,{1,1,1,14,1,1}},{10,13,8,{1,14,1,1,1,1}},{10,18,2,{1,1,1,14,1,1}},{11,13,8,{1,14,1,1,1,1}},{11,18,2,{1,1,1,14,1,1}},{12,13,0,{1,14,1,1,1,12}},{12,14,4,{1,1,1,1,1,12}},{12,15,4,{1,1,1,1,1,12}},{12,16,4,{1,1,1,1,1,12}},{12,17,4,{1,1,1,1,1,12}},{12,18,0,{1,1,1,14,1,12}} },
        { {8,13,0,{1,14,9,1,1,1}},{8,14,32,{1,1,9,1,1,1}},{8,15,32,{1,1,9,1,1,1}},{8,16,32,{1,1,9,1,1,1}},{8,17,32,{1,1,9,1,1,1}},{8,18,0,{1,1,9,14,1,1}},{9,13,8,{1,14,1,1,1,1}},{9,18,2,{1,1,1,14,1,1}},{10,13,8,{1,14,1,1,1,1}},{10,18,2,{1,1,1,14,1,1}},{11,13,8,{1,14,1,1,1,1}},{11,18,2,{1,1,1,14,1,1}},{12,13,0,{1,14,1,1,1,12}},{12,14,4,{1,1,1,1,1,12}},{12,15,4,{1,1,1,1,1,12}},{12,16,4,{1,1,1,1,1,12}},{12,17,4,{1,1,1,1,1,12}},{12,18,0,{1,1,1,14,1,12}} },
        { {8,13,0,{1,14,9,1,1,1}},{8,14,32,{1,1,9,1,1,1}},{8,15,33,{1,1,9,1,1,1}},{8,16,33,{1,1,9,1,1,1}},{8,17,33,{1,1,9,1,1,1}},{8,18,1,{1,1,9,14,1,1}},{9,13,8,{1,14,1,1,1,1}},{9,18,3,{1,1,1,14,1,1}},{10,13,8,{1,14,1,1,1,1}},{10,18,3,{1,1,1,14,1,1}},{11,13,8,{1,14,1,1,1,1}},{11,18,2,{1,1,1,14,1,1}},{12,13,0,{1,14,1,1,1,12}},{12,14,4,{1,1,1,1,1,12}},{12,15,4,{1,1,1,1,1,12}},{12,16,4,{1,1,1,1,1,12}},{12,17,4,{1,1,1,1,1,12}},{12,18,0,{1,1,1,14,1,12}} },
        { {7,14,0,{1,15,8,1,1,1}},{7,15,32,{1,1,8,1,1,1}},{7,16,32,{1,1,8,1,1,1}},{7,17,32,{1,1,8,1,1,1}},{7,18,32,{1,1,8,1,1,1}},{7,19,0,{1,1,8,13,1,1}},{8,14,8,{1,15,1,1,1,1}},{8,19,2,{1,1,1,13,1,1}},{9,14,24,{1,15,1,1,1,1}},{9,19,2,{1,1,1,13,1,1}},{10,14,24,{1,15,1,1,1,1}},{10,19,2,{1,1,1,13,1,1}},{11,14,16,{1,15,1,1,1,13}},{11,15,20,{1,1,1,1,1,13}},{11,16,20,{1,1,1,1,1,13}},{11,17,20,{1,1,1,1,1,13}},{11,18,4,{1,1,1,1,1,13}},{11,19,0,{1,1,1,13,1,13}} },
        { {7,14,0,{1,15,8,1,1,1}},{7,15,32,{1,1,8,1,1,1}},{7,16,32,{1,1,8,1,1,1}},{7,17,32,{1,1,8,1,1,1}},{7,18,32,{1,1,8,1,1,1}},{7,19,0,{1,1,8,13,1,1}},{8,14,8,{1,15,1,1,1,1}},{8,19,2,{1,1,1,13,1,1}},{9,14,8,{1,15,1,1,1,1}},{9,19,2,{1,1,1,13,1,1}},{10,14,8,{1,15,1,1,1,1}},{10,19,2,{1,1,1,13,1,1}},{11,14,0,{1,15,1,1,1,13}},{11,15,4,{1,1,1,1,1,13}},{11,16,4,{1,1,1,1,1,13}},{11,17,4,{1,1,1,1,1,13}},{11,18,4,{1,1,1,1,1,13}},{11,19,0,{1,1,1,13,1,13}} },
        { {7,14,0,{1,15,8,1,1,1}},{7,15,32,{1,1,8,1,1,1}},{7,16,32,{1,1,8,1,1,1}},{7,17,32,{1,1,8,1,1,1}},{7,18,32,{1,1,8,1,1,1}},{7,19,0,{1,1,8,13,1,1}},{8,14,8,{1,15,1,1,1,1}},{8,19,2,{1,1,1,13,1,1}},{9,14,8,{1,15,1,1,1,1}},{9,19,2,{1,1,1,13,1,1}},{10,14,8,{1,15,1,1,1,1}},{10,19,2,{1,1,1,13,1,1}},{11,14,0,{1,15,1,1,1,13}},{11,15,4,{1,1,1,1,1,13}},{11,16,4,{1,1,1,1,1,13}},{11,17,4,{1,1,1,1,1,13}},{11,18,4,{1,1,1,1,1,13}},{11,19,0,{1,1,1,13,1,13}} },
        { {7,14,0,{1,15,8,1,1,1}},{7,15,32,{1,1,8,1,1,1}},{7,16,32,{1,1,8,1,1,1}},{7,17,32,{1,1,8,1,1,1}},{7,18,32,{1,1,8,1,1,1}},{7,19,0,{1,1,8,13,1,1}},{8,14,8,{1,15,1,1,1,1}},{8,19,2,{1,1,1,13,1,1}},{9,14,9,{1,15,1,1,1,1}},{9,19,2,{1,1,1,13,1,1}},{10,14,9,{1,15,1,1,1,1}},{10,19,2,{1,1,1,13,1,1}},{11,14,1,{1,15,1,1,1,13}},{11,15,5,{1,1,1,1,1,13}},{11,16,5,{1,1,1,1,1,13}},{11,17,5,{1,1,1,1,1,13}},{11,18,4,{1,1,1,1,1,13}},{11,19,0,{1,1,1,13,1,13}} },
        { {8,13,0,{1,14,9,1,1,1}},{8,14,32,{1,1,9,1,1,1}},{8,15,48,{1,1,9,1,1,1}},{8,16,48,{1,1,9,1,1,1}},{8,17,48,{1,1,9,1,1,1}},{8,18,16,{1,1,9,14,1,1}},{9,13,8,{1,14,1,1,1,1}},{9,18,18,{1,1,1,14,1,1}},{10,13,8,{1,14,1,1,1,1}},{10,18,18,{1,1,1,14,1,1}},{11,13,8,{1,14,1,1,1,1}},{11,18,2,{1,1,1,14,1,1}},{12,13,0,{1,14,1,1,1,12}},{12,14,4,{1,1,1,1,1,12}},{12,15,4,{1,1,1,1,1,12}},{12,16,4,{1,1,1,1,1,12}},{12,17,4,{1,1,1,1,1,12}},{12,18,0,{1,1,1,14,1,12}} },
        { {8,13,0,{1,14,9,1,1,1}},{8,14,32,{1,1,9,1,1,1}},{8,15,33,{1,1,9,1,1,1}},{8,16,33,{1,1,9,1,1,1}},{8,17,33,{1,1,9,1,1,1}},{8,18,1,{1,1,9,14,1,1}},{9,13,8,{1,14,1,1,1,1}},{9,18,3,{1,1,1,14,1,1}},{10,13,8,{1,14,1,1,1,1}},{10,18,3,{1,1,1,14,1,1}},{11,13,8,{1,14,1,1,1,1}},{11,18,2,{1,1,1,14,1,1}},{12,13,0,{1,14,1,1,1,12}},{12,14,4,{1,1,1,1,1,12}},{12,15,4,{1,1,1,1,1,12}},{12,16,4,{1,1,1,1,1,12}},{12,17,4,{1,1,1,1,1,12}},{12,18,0,{1,1,1,14,1,12}} },
        { {7,14,0,{1,15,8,1,1,1}},{7,15,32,{1,1,8,1,1,1}},{7,16,32,{1,1,8,1,1,1}},{7,17,32,{1,1,8,1,1,1}},{7,18,32,{1,1,8,1,1,1}},{7,19,0,{1,1,8,13,1,1}},{8,14,8,{1,15,1,1,1,1}},{8,19,2,{1,1,1,13,1,1}},{9,14,24,{1,15,1,1,1,1}},{9,19,2,{1,1,1,13,1,1}},{10,14,24,{1,15,1,1,1,1}},{10,19,2,{1,1,1,13,1,1}},{11,14,16,{1,15,1,1,1,13}},{11,15,20,{1,1,1,1,1,13}},{11,16,20,{1,1,1,1,1,13}},{11,17,20,{1,1,1,1,1,13}},{11,18,4,{1,1,1,1,1,13}},{11,19,0,{1,1,1,13,1,13}} },
        { {7,14,0,{1,15,8,1,1,1}},{7,15,32,{1,1,8,1,1,1}},{7,16,32,{1,1,8,1,1,1}},{7,17,32,{1,1,8,1,1,1}},{7,18,32,{1,1,8,1,1,1}},{7,19,0,{1,1,8,13,1,1}},{8,14,8,{1,15,1,1,1,1}},{8,19,2,{1,1,1,13,1,1}},{9,14,8,{1,15,1,1,1,1}},{9,19,2,{1,1,1,13,1,1}},{10,14,8,{1,15,1,1,1,1}},{10,19,2,{1,1,1,13,1,1}},{11,14,0,{1,15,1,1,1,13}},{11,15,4,{1,1,1,1,1,13}},{11,16,4,{1,1,1,1,1,13}},{11,17,4,{1,1,1,1,1,13}},{11,18,4,{1,1,1,1,1,13}},{11,19,0,{1,1,1,13,1,13}} },
        { {7,14,0,{1,15,8,1,1,1}},{7,15,32,{1,1,8,1,1,1}},{7,16,32,{1,1,8,1,1,1}},{7,17,32,{1,1,8,1,1,1}},{7,18,32,{1,1,8,1,1,1}},{7,19,0,{1,1,8,13,1,1}},{8,14,8,{1,15,1,1,1,1}},{8,19,2,{1,1,1,13,1,1}},{9,14,8,{1,15,1,1,1,1}},{9,19,2,{1,1,1,13,1,1}},{10,14,8,{1,15,1,1,1,1}},{10,19,2,{1,1,1,13,1,1}},{11,14,0,{1,15,1,1,1,13}},{11,15,4,{1,1,1,1,1,13}},{11,16,4,{1,1,1,1,1,13}},{11,17,4,{1,1,1,1,1,13}},{11,18,4,{1,1,1,1,1,13}},{11,19,0,{1,1,1,13,1,13}} },
        { {7,14,0,{1,15,8,1,1,1}},{7,15,32,{1,1,8,1,1,1}},{7,16,32,{1,1,8,1,1,1}},{7,17,32,{1,1,8,1,1,1}},{7,18,32,{1,1,8,1,1,1}},{7,19,0,{1,1,8,13,1,1}},{8,14,8,{1,15,1,1,1,1}},{8,19,2,{1,1,1,13,1,1}},{9,14,8,{1,15,1,1,1,1}},{9,19,2,{1,1,1,13,1,1}},{10,14,8,{1,15,1,1,1,1}},{10,19,2,{1,1,1,13,1,1}},{11,14,0,{1,15,1,1,1,13}},{11,15,4,{1,1,1,1,1,13}},{11,16,4,{1,1,1,1,1,13}},{11,17,4,{1,1,1,1,1,13}},{11,18,4,{1,1,1,1,1,13}},{11,19,0,{1,1,1,13,1,13}} },
        { {7,10,1,{1,11,8,1,1,1}},{7,11,1,{1,1,8,1,1,1}},{7,12,1,{1,1,8,1,1,1}},{7,13,1,{1,1,8,1,1,1}},{7,14,1,{1,1,8,1,1,1}},{7,15,33,{1,1,8,1,1,1}},{7,16,33,{1,1,8,1,1,1}},{7,17,33,{1,1,8,1,1,1}},{7,18,33,{1,1,8,1,1,1}},{7,19,1,{1,1,8,1,1,1}},{7,20,1,{1,1,8,1,1,1}},{7,21,1,{1,1,8,11,1,1}},{8,10,1,{1,11,1,1,1,1}},{8,11,1,{1,1,1,1,1,1}},{8,12,1,{1,1,1,1,1,1}},{8,13,1,{1,1,1,1,1,1}},{8,14,9,{1,1,1,1,1,1}},{8,19,3,{1,1,1,1,1,1}},{8,20,1,{1,1,1,1,1,1}},{8,21,1,{1,1,1,11,1,1}},{9,10,1,{1,11,1,1,1,1}},{9,11,1,{1,1,1,1,1,1}},{9,12,1,{1,1,1,1,1,1}},{9,13,1,{1,1,1,1,1,1}},{9,14,9,{1,1,1,1,1,1}},{9,19,3,{1,1,1,1,1,1}},{9,20,1,{1,1,1,1,1,1}},{9,21,1,{1,1,1,11,1,1}},{10,10,1,{1,11,1,1,1,1}},{10,11,1,{1,1,1,1,1,1}},{10,12,1,{1,1,1,1,1,1}},{10,13,1,{1,1,1,1,1,1}},{10,14,9,{1,1,1,1,1,1}},{10,19,3,{1,1,1,1,1,1}},{10,20,1,{1,1,1,1,1,1}},{10,21,1,{1,1,1,11,1,1}},{11,10,1,{1,11,1,1,1,1}},{11,11,1,{1,1,1,1,1,1}},{11,12,1,{1,1,1,1,1,1}},{11,13,1,{1,1,1,1,1,1}},{11,14,1,{1,1,1,1,1,1}},{11,15,5,{1,1,1,1,1,1}},{11,16,5,{1,1,1,1,1,1}},{11,17,5,{1,1,1,1,1,1}},{11,18,5,{1,1,1,1,1,1}},{11,19,1,{1,1,1,1,1,1}},{11,20,1,{1,1,1,1,1,1}},{11,21,1,{1,1,1,11,1,1}},{12,10,1,{1,11,1,1,1,1}},{12,11,1,{1,1,1,1,1,1}},{12,12,1,{1,1,1,1,1,1}},{12,13,1,{1,1,1,1,1,1}},{12,14,1,{1,1,1,1,1,1}},{12,15,1,{1,1,1,1,1,1}},{12,16,1,{1,1,1,1,1,1}},{12,17,1,{1,1,1,1,1,1}},{12,18,1,{1,1,1,1,1,1}},{12,19,1,{1,1,1,1,1,1}},{12,20,1,{1,1,1,1,1,1}},{12,21,1,{1,1,1,11,1,1}},{13,10,1,{1,11,1,1,1,1}},{13,11,1,{1,1,1,1,1,1}},{13,12,1,{1,1,1,1,1,1}},{13,13,1,{1,1,1,1,1,1}},{13,14,1,{1,1,1,1,1,1}},{13,15,1,{1,1,1,1,1,1}},{13,16,1,{1,1,1,1,1,1}},{13,17,1,{1,1,1,1,1,1}},{13,18,1,{1,1,1,1,1,1}},{13,19,1,{1,1,1,1,1,1}},{13,20,1,{1,1,1,1,1,1}},{13,21,1,{1,1,1,11,1,1}},{14,10,1,{1,11,1,1,1,1}},{14,11,1,{1,1,1,1,1,1}},{14,12,1,{1,1,1,1,1,1}},{14,13,1,{1,1,1,1,1,1}},{14,14,1,{1,1,1,1,1,1}},{14,15,1,{1,1,1,1,1,1}},{14,16,1,{1,1,1,1,1,1}},{14,17,1,{1,1,1,1,1,1}},{14,18,1,{1,1,1,1,1,1}},{14,19,1,{1,1,1,1,1,1}},{14,20,1,{1,1,1,1,1,1}},{14,21,1,{1,1,1,11,1,1}},{15,10,1,{1,11,1,1,1,1}},{15,11,1,{1,1,1,1,1,1}},{15,12,1,{1,1,1,1,1,1}},{15,13,1,{1,1,1,1,1,1}},{15,14,1,{1,1,1,1,1,1}},{15,15,1,{1,1,1,1,1,1}},{15,16,1,{1,1,1,1,1,1}},{15,17,1,{1,1,1,1,1,1}},{15,18,1,{1,1,1,1,1,1}},{15,19,1,{1,1,1,1,1,1}},{15,20,1,{1,1,1,1,1,1}},{15,21,1,{1,1,1,11,1,1}},{16,10,1,{1,11,1,1,1,8}},{16,11,1,{1,1,1,1,1,8}},{16,12,1,{1,1,1,1,1,8}},{16,13,1,{1,1,1,1,1,8}},{16,14,1,{1,1,1,1,1,8}},{16,15,1,{1,1,1,1,1,8}},{16,16,1,{1,1,1,1,1,8}},{16,17,1,{1,1,1,1,1,8}},{16,18,1,{1,1,1,1,1,8}},{16,19,1,{1,1,1,1,1,8}},{16,20,1,{1,1,1,1,1,8}},{16,21,1,{1,1,1,11,1,8}} }
    };
    int aBoxInfoLen[] = {116,12,12,12,20,20,20,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,108};



    _papaBoxInfo = NEW BoxInfo*[_area_len];
    for (int i = 0; i < _area_len; i++) {
        _papaBoxInfo[i] = NEW BoxInfo[aBoxInfoLen[i]];
    }
    for (int i = 0; i < _area_len; i++) {
        for (int j = 0; j < aBoxInfoLen[i]; j++) {
            _papaBoxInfo[i][j] = area[i][j]; //�R�s�[
        }
    }
    _paBoxInfoLen = NEW int[_area_len];
    for (int i = 0; i < _area_len; i++) {
        _paBoxInfoLen[i] = aBoxInfoLen[i];
    }



    _ground_speed = 8000;

    _box_dep = 1600000;
    _box_width = 400000;
    _box_height = 400000;
    _frame_of_launch_interval = (frame)(_box_dep /_ground_speed);

    _box_stock = 800;
    _pDispatcher_Box = NEW GgafActorDispatcher("Dp_Box");
    for (int i = 0; i < _box_stock; i++) {
        GroundBoxActor* pGroundBoxActor =  NEW GroundBoxActor("GroundBox","gbox",
                                                              _box_dep, _box_width, _box_height);
        pGroundBoxActor->_ground_speed = _ground_speed;
        pGroundBoxActor->inactivateTreeImmediately();
        _pDispatcher_Box->addSubLast(pGroundBoxActor);
    }
    getLordActor()->addSubGroup(_pDispatcher_Box);
}

void GroundBoxScene::initialize() {
//    for (int i = 0; i < _area_len; i++) {
//        for (int j = 0; j < _paBoxInfoLen[i]; j++) {
//            _TRACE_("_papaBoxInfo["<<i<<"]["<<j<<"]:--------------");
//            _TRACE_("{"<<_papaBoxInfo[i][j]._Y <<","<<_papaBoxInfo[i][j]._Z<<","<<_papaBoxInfo[i][j]._box_draw_face<<","<<
//                    "{"<<
//                    _papaBoxInfo[i][j]._aColliBoxStretch[0]<<","<<
//                    _papaBoxInfo[i][j]._aColliBoxStretch[1]<<","<<
//                    _papaBoxInfo[i][j]._aColliBoxStretch[2]<<","<<
//                    _papaBoxInfo[i][j]._aColliBoxStretch[3]<<","<<
//                    _papaBoxInfo[i][j]._aColliBoxStretch[4]<<","<<
//                    _papaBoxInfo[i][j]._aColliBoxStretch[5]<<""<<
//                    "}"<<
//                    "}");
//
//        }
//    }
}

void GroundBoxScene::onActive() {
    _cnt_area_len = 0;
}


void GroundBoxScene::processBehavior() {

    if (_cnt_area_len < _area_len && getActivePartFrame() % _frame_of_launch_interval == 0) {
        for (int n = 0; n < _paBoxInfoLen[_cnt_area_len]; n++) {
            GroundBoxActor* pBox = (GroundBoxActor*)_pDispatcher_Box->employ();
            if (pBox) {
                pBox->config(_papaBoxInfo[_cnt_area_len][n]._box_draw_face,
                             _papaBoxInfo[_cnt_area_len][n]._aColliBoxStretch);
                pBox->setGeometry(10000000,
                                  ((-_area_height/2) + _papaBoxInfo[_cnt_area_len][n]._Y) * _box_height,
                                  ((-_area_width/2) + _papaBoxInfo[_cnt_area_len][n]._Z) * _box_width);
                pBox->activate();
            }
        }
        _cnt_area_len++;
    }
}

void GroundBoxScene::processFinal() {
}

GroundBoxScene::~GroundBoxScene() {

}
