#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Stage01MainScene::Stage01MainScene(const char* prm_name) : DefaultScene(prm_name) {

    _pRot = NEW RotationActor("RotEnemyMeshS001");
    EnemyMeshShot001* pEnemyMeshShot;
    for (int i = 0; i < 100; i++) {
        Sleep(1);
        pEnemyMeshShot = NEW EnemyMeshShot001("EnemyMeshShot", "M/myvic");
        pEnemyMeshShot->refrainImmediately(); //最初非表示
            _pRot->addSubLast(pEnemyMeshShot);
        }
        getLordActor()->accept(KIND_ENEMY, _pRot);

        // 以下の gen01 start ～ end はマクロにより自動生成されたコードです。
        // gen01 start
        DWORD dw[] = {1,40,100,120,170,200,240,300,310,380,400,450,460,490,500,520,580,640,670,700,750,760,780,800,850,860,900,940,950,1000,1020,1040,1050,1070,1080,1100,1120,1140,1160,1200,1210,1240,1280,1300,1320,1330,1350,1360,1390,1400,1420,1450,1480,1510,1540,1570,1600,1620,1630,1640,1650,1660,1680,1690,1700,1720,1740,1750,1760,1780,1800,1820,1840,1850,1860,1880,1900,1920,1940,1950,1960,1980,2000,2020,2060,2100,2140,2180,2200,2220,2230,2260,2290,2300,2320,2350,2380,2410,2440,2470,2500,2520,2530,2540,2560,2580,2590,2600,2620,2640,2660,2680,2700,2720,2740,2760,2780,2800,2820,2840,2860,2880,2900};
        _paFrame_NextEvent = new DWORD[123];
        for (int i = 0; i < 123; i++) {
            _paFrame_NextEvent[i] = dw[i];
        }
        orderActorWithRotToFactory(11077100, EnemyCeres, "Ceres_1", "M/Ceres", _pRot);
        orderActorWithRotToFactory(11077200, EnemyCeres, "Ceres_2", "M/Ceres", _pRot);
        orderActorWithRotToFactory(11077300, EnemyCeres, "Ceres_3", "M/Ceres", _pRot);
        orderActorWithRotToFactory(11077400, EnemyCeres, "Ceres_4", "M/Ceres", _pRot);
        orderActorWithRotToFactory(11077500, EnemyCeres, "Ceres_5", "M/Ceres", _pRot);
        orderActorWithRotToFactory(11087400, EnemyCeres, "Ceres_6", "M/Ceres", _pRot);
        orderActorWithRotToFactory(11087490, EnemyCeres, "Ceres_7", "M/Ceres", _pRot);
        orderActorWithRotToFactory(11087580, EnemyCeres, "Ceres_8", "M/Ceres", _pRot);
        orderActorWithRotToFactory(11087670, EnemyCeres, "Ceres_9", "M/Ceres", _pRot);
        orderActorWithRotToFactory(11087760, EnemyCeres, "Ceres_10", "M/Ceres", _pRot);
        orderActorWithRotToFactory(11097700, EnemyCeres, "Ceres_11", "M/Ceres", _pRot);
        orderActorWithRotToFactory(11097780, EnemyCeres, "Ceres_12", "M/Ceres", _pRot);
        orderActorWithRotToFactory(11097860, EnemyCeres, "Ceres_13", "M/Ceres", _pRot);
        // gen01 end

        refrainImmediately(); //GameMainSceneが解除してくれる


    }

void Stage01MainScene::initialize() {
}

void Stage01MainScene::processBehavior() {
    // 以下の gen02 start ～ end はマクロにより自動生成されたコードです。
    // gen02 start
    if (_dwFrame == _paFrame_NextEvent[_iCnt_Event]) {
        switch (_dwFrame) {
            case 1:
                break;
            case 40:
                orderActorWithRotToFactory(11097940, EnemyCeres, "Ceres_14", "M/Ceres", _pRot);
                break;
            case 100: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11077100);
                pActor->_Z = -1500000;
                pActor->_Y_turn = -300000;
                pActor->_iBeginVelocity = 5000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                orderActorWithRotToFactory(111071000, EnemyCeres, "Ceres_15", "M/Ceres", _pRot);
                break;
            case 120:
                orderActorWithRotToFactory(110971020, EnemyCeres, "Ceres_16", "M/Ceres", _pRot);
                break;
            case 170:
                orderActorWithRotToFactory(111071070, EnemyCeres, "Ceres_17", "M/Ceres", _pRot);
                break;
            case 200: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11077200);
                pActor->_Z = -1500000;
                pActor->_Y_turn = -300000;
                pActor->_iBeginVelocity = 5000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                orderActorWithRotToFactory(110971100, EnemyCeres, "Ceres_18", "M/Ceres", _pRot);
                break;
            case 240:
                orderActorWithRotToFactory(111071140, EnemyCeres, "Ceres_19", "M/Ceres", _pRot);
                break;
            case 300: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11077300);
                pActor->_Z = -1500000;
                pActor->_Y_turn = -300000;
                pActor->_iBeginVelocity = 5000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                break;
            case 310:
                orderActorWithRotToFactory(111071210, EnemyCeres, "Ceres_20", "M/Ceres", _pRot);
                break;
            case 380:
                orderActorWithRotToFactory(111071280, EnemyCeres, "Ceres_21", "M/Ceres", _pRot);
                break;
            case 400: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11077400);
                pActor->_Z = -1500000;
                pActor->_Y_turn = -300000;
                pActor->_iBeginVelocity = 5000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                {
                    EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11087400);
                    pActor->_Z = -1500000;
                    pActor->_Y_turn = -250000;
                    pActor->_iBeginVelocity = 6000;
                    getLordActor()->accept(KIND_ENEMY, pActor);
                }
                orderActorWithRotToFactory(111171300, EnemyCeres, "Ceres_22", "M/Ceres", _pRot);
                break;
            case 450:
                orderActorWithRotToFactory(111071350, EnemyCeres, "Ceres_23", "M/Ceres", _pRot);
                break;
            case 460:
                orderActorWithRotToFactory(111171360, EnemyCeres, "Ceres_24", "M/Ceres", _pRot);
                break;
            case 490: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11087490);
                pActor->_Z = -1500000;
                pActor->_Y_turn = -250000;
                pActor->_iBeginVelocity = 6000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                break;
            case 500: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11077500);
                pActor->_Z = -1500000;
                pActor->_Y_turn = -300000;
                pActor->_iBeginVelocity = 5000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                break;
            case 520:
                orderActorWithRotToFactory(111171420, EnemyCeres, "Ceres_25", "M/Ceres", _pRot);
                break;
            case 580: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11087580);
                pActor->_Z = -1500000;
                pActor->_Y_turn = -250000;
                pActor->_iBeginVelocity = 6000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                orderActorWithRotToFactory(111171480, EnemyCeres, "Ceres_26", "M/Ceres", _pRot);
                break;
            case 640:
                orderActorWithRotToFactory(111171540, EnemyCeres, "Ceres_27", "M/Ceres", _pRot);
                break;
            case 670: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11087670);
                pActor->_Z = -1500000;
                pActor->_Y_turn = -250000;
                pActor->_iBeginVelocity = 6000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                break;
            case 700: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11097700);
                pActor->_Z = -1500000;
                pActor->_Y_turn = -200000;
                pActor->_iBeginVelocity = 7000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                orderActorWithRotToFactory(111171600, EnemyCeres, "Ceres_28", "M/Ceres", _pRot);
                orderActorWithRotToFactory(111271600, EnemyCeres, "Ceres_29", "M/Ceres", _pRot);
                break;
            case 750:
                orderActorWithRotToFactory(111271650, EnemyCeres, "Ceres_30", "M/Ceres", _pRot);
                break;
            case 760: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11087760);
                pActor->_Z = -1500000;
                pActor->_Y_turn = -250000;
                pActor->_iBeginVelocity = 6000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                orderActorWithRotToFactory(111171660, EnemyCeres, "Ceres_31", "M/Ceres", _pRot);
                break;
            case 780: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11097780);
                pActor->_Z = -1500000;
                pActor->_Y_turn = -200000;
                pActor->_iBeginVelocity = 7000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                break;
            case 800:
                orderActorWithRotToFactory(111271700, EnemyCeres, "Ceres_32", "M/Ceres", _pRot);
                break;
            case 850:
                orderActorWithRotToFactory(111271750, EnemyCeres, "Ceres_33", "M/Ceres", _pRot);
                break;
            case 860: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11097860);
                pActor->_Z = -1500000;
                pActor->_Y_turn = -200000;
                pActor->_iBeginVelocity = 7000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                break;
            case 900:
                orderActorWithRotToFactory(111271800, EnemyCeres, "Ceres_34", "M/Ceres", _pRot);
                break;
            case 940: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11097940);
                pActor->_Z = -1500000;
                pActor->_Y_turn = -200000;
                pActor->_iBeginVelocity = 7000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                break;
            case 950:
                orderActorWithRotToFactory(111271850, EnemyCeres, "Ceres_35", "M/Ceres", _pRot);
                break;
            case 1000: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111071000);
                pActor->_Z = -1500000;
                pActor->_Y_turn = -150000;
                pActor->_iBeginVelocity = 8000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                orderActorWithRotToFactory(111271900, EnemyCeres, "Ceres_36", "M/Ceres", _pRot);
                orderActorWithRotToFactory(111371900, EnemyCeres, "Ceres_37", "M/Ceres", _pRot);
                break;
            case 1020: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(110971020);
                pActor->_Z = -1500000;
                pActor->_Y_turn = -200000;
                pActor->_iBeginVelocity = 7000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                break;
            case 1040:
                orderActorWithRotToFactory(111371940, EnemyCeres, "Ceres_38", "M/Ceres", _pRot);
                break;
            case 1050:
                orderActorWithRotToFactory(111271950, EnemyCeres, "Ceres_39", "M/Ceres", _pRot);
                break;
            case 1070: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111071070);
                pActor->_Z = -1500000;
                pActor->_Y_turn = -150000;
                pActor->_iBeginVelocity = 8000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                break;
            case 1080:
                orderActorWithRotToFactory(111371980, EnemyCeres, "Ceres_40", "M/Ceres", _pRot);
                break;
            case 1100: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(110971100);
                pActor->_Z = -1500000;
                pActor->_Y_turn = -200000;
                pActor->_iBeginVelocity = 7000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                orderActorWithRotToFactory(111272000, EnemyCeres, "Ceres_41", "M/Ceres", _pRot);
                break;
            case 1120:
                orderActorWithRotToFactory(111372020, EnemyCeres, "Ceres_42", "M/Ceres", _pRot);
                break;
            case 1140: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111071140);
                pActor->_Z = -1500000;
                pActor->_Y_turn = -150000;
                pActor->_iBeginVelocity = 8000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                break;
            case 1160:
                orderActorWithRotToFactory(111372060, EnemyCeres, "Ceres_43", "M/Ceres", _pRot);
                break;
            case 1200:
                orderActorWithRotToFactory(111372100, EnemyCeres, "Ceres_44", "M/Ceres", _pRot);
                break;
            case 1210: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111071210);
                pActor->_Z = -1500000;
                pActor->_Y_turn = -150000;
                pActor->_iBeginVelocity = 8000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                break;
            case 1240:
                orderActorWithRotToFactory(111372140, EnemyCeres, "Ceres_45", "M/Ceres", _pRot);
                break;
            case 1280: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111071280);
                pActor->_Z = -1500000;
                pActor->_Y_turn = -150000;
                pActor->_iBeginVelocity = 8000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                orderActorWithRotToFactory(111372180, EnemyCeres, "Ceres_46", "M/Ceres", _pRot);
                break;
            case 1300: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111171300);
                pActor->_Z = -1500000;
                pActor->_Y_turn = 0;
                pActor->_iBeginVelocity = 9000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                orderActorWithRotToFactory(111472200, EnemyCeres, "Ceres_47", "M/Ceres", _pRot);
                break;
            case 1320:
                orderActorWithRotToFactory(111372220, EnemyCeres, "Ceres_48", "M/Ceres", _pRot);
                break;
            case 1330:
                orderActorWithRotToFactory(111472230, EnemyCeres, "Ceres_49", "M/Ceres", _pRot);
                break;
            case 1350: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111071350);
                pActor->_Z = -1500000;
                pActor->_Y_turn = -150000;
                pActor->_iBeginVelocity = 8000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                break;
            case 1360: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111171360);
                pActor->_Z = -1500000;
                pActor->_Y_turn = 0;
                pActor->_iBeginVelocity = 9000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                orderActorWithRotToFactory(111372260, EnemyCeres, "Ceres_50", "M/Ceres", _pRot);
                orderActorWithRotToFactory(111472260, EnemyCeres, "Ceres_51", "M/Ceres", _pRot);
                break;
            case 1390:
                orderActorWithRotToFactory(111472290, EnemyCeres, "Ceres_52", "M/Ceres", _pRot);
                break;
            case 1400:
                orderActorWithRotToFactory(111372300, EnemyCeres, "Ceres_53", "M/Ceres", _pRot);
                break;
            case 1420: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111171420);
                pActor->_Z = -1500000;
                pActor->_Y_turn = 0;
                pActor->_iBeginVelocity = 9000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                orderActorWithRotToFactory(111472320, EnemyCeres, "Ceres_54", "M/Ceres", _pRot);
                break;
            case 1450:
                orderActorWithRotToFactory(111472350, EnemyCeres, "Ceres_55", "M/Ceres", _pRot);
                break;
            case 1480: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111171480);
                pActor->_Z = -1500000;
                pActor->_Y_turn = 0;
                pActor->_iBeginVelocity = 9000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                orderActorWithRotToFactory(111472380, EnemyCeres, "Ceres_56", "M/Ceres", _pRot);
                break;
            case 1510:
                orderActorWithRotToFactory(111472410, EnemyCeres, "Ceres_57", "M/Ceres", _pRot);
                break;
            case 1540: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111171540);
                pActor->_Z = -1500000;
                pActor->_Y_turn = 0;
                pActor->_iBeginVelocity = 9000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                orderActorWithRotToFactory(111472440, EnemyCeres, "Ceres_58", "M/Ceres", _pRot);
                break;
            case 1570:
                orderActorWithRotToFactory(111472470, EnemyCeres, "Ceres_59", "M/Ceres", _pRot);
                break;
            case 1600: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111171600);
                pActor->_Z = -1500000;
                pActor->_Y_turn = 0;
                pActor->_iBeginVelocity = 9000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                {
                    EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111271600);
                    pActor->_Z = -1500000;
                    pActor->_Y_turn = 150000;
                    pActor->_iBeginVelocity = 10000;
                    getLordActor()->accept(KIND_ENEMY, pActor);
                }
                orderActorWithRotToFactory(111472500, EnemyCeres, "Ceres_60", "M/Ceres", _pRot);
                orderActorWithRotToFactory(111572500, EnemyCeres, "Ceres_61", "M/Ceres", _pRot);
                break;
            case 1620:
                orderActorWithRotToFactory(111572520, EnemyCeres, "Ceres_62", "M/Ceres", _pRot);
                break;
            case 1630:
                orderActorWithRotToFactory(111472530, EnemyCeres, "Ceres_63", "M/Ceres", _pRot);
                break;
            case 1640:
                orderActorWithRotToFactory(111572540, EnemyCeres, "Ceres_64", "M/Ceres", _pRot);
                break;
            case 1650: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111271650);
                pActor->_Z = -1500000;
                pActor->_Y_turn = 150000;
                pActor->_iBeginVelocity = 10000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                break;
            case 1660: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111171660);
                pActor->_Z = -1500000;
                pActor->_Y_turn = 0;
                pActor->_iBeginVelocity = 9000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                orderActorWithRotToFactory(111472560, EnemyCeres, "Ceres_65", "M/Ceres", _pRot);
                orderActorWithRotToFactory(111572560, EnemyCeres, "Ceres_66", "M/Ceres", _pRot);
                break;
            case 1680:
                orderActorWithRotToFactory(111572580, EnemyCeres, "Ceres_67", "M/Ceres", _pRot);
                break;
            case 1690:
                orderActorWithRotToFactory(111472590, EnemyCeres, "Ceres_68", "M/Ceres", _pRot);
                break;
            case 1700: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111271700);
                pActor->_Z = -1500000;
                pActor->_Y_turn = 150000;
                pActor->_iBeginVelocity = 10000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                orderActorWithRotToFactory(111572600, EnemyCeres, "Ceres_69", "M/Ceres", _pRot);
                break;
            case 1720:
                orderActorWithRotToFactory(111572620, EnemyCeres, "Ceres_70", "M/Ceres", _pRot);
                break;
            case 1740:
                orderActorWithRotToFactory(111572640, EnemyCeres, "Ceres_71", "M/Ceres", _pRot);
                break;
            case 1750: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111271750);
                pActor->_Z = -1500000;
                pActor->_Y_turn = 150000;
                pActor->_iBeginVelocity = 10000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                break;
            case 1760:
                orderActorWithRotToFactory(111572660, EnemyCeres, "Ceres_72", "M/Ceres", _pRot);
                break;
            case 1780:
                orderActorWithRotToFactory(111572680, EnemyCeres, "Ceres_73", "M/Ceres", _pRot);
                break;
            case 1800: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111271800);
                pActor->_Z = -1500000;
                pActor->_Y_turn = 150000;
                pActor->_iBeginVelocity = 10000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                orderActorWithRotToFactory(111572700, EnemyCeres, "Ceres_74", "M/Ceres", _pRot);
                break;
            case 1820:
                orderActorWithRotToFactory(111572720, EnemyCeres, "Ceres_75", "M/Ceres", _pRot);
                break;
            case 1840:
                orderActorWithRotToFactory(111572740, EnemyCeres, "Ceres_76", "M/Ceres", _pRot);
                break;
            case 1850: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111271850);
                pActor->_Z = -1500000;
                pActor->_Y_turn = 150000;
                pActor->_iBeginVelocity = 10000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                break;
            case 1860:
                orderActorWithRotToFactory(111572760, EnemyCeres, "Ceres_77", "M/Ceres", _pRot);
                break;
            case 1880:
                orderActorWithRotToFactory(111572780, EnemyCeres, "Ceres_78", "M/Ceres", _pRot);
                break;
            case 1900: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111271900);
                pActor->_Z = -1500000;
                pActor->_Y_turn = 150000;
                pActor->_iBeginVelocity = 10000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                {
                    EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111371900);
                    pActor->_Z = -1500000;
                    pActor->_Y_turn = 200000;
                    pActor->_iBeginVelocity = 11000;
                    getLordActor()->accept(KIND_ENEMY, pActor);
                }
                orderActorWithRotToFactory(111572800, EnemyCeres, "Ceres_79", "M/Ceres", _pRot);
                break;
            case 1920:
                orderActorWithRotToFactory(111572820, EnemyCeres, "Ceres_80", "M/Ceres", _pRot);
                break;
            case 1940: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111371940);
                pActor->_Z = -1500000;
                pActor->_Y_turn = 200000;
                pActor->_iBeginVelocity = 11000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                orderActorWithRotToFactory(111572840, EnemyCeres, "Ceres_81", "M/Ceres", _pRot);
                break;
            case 1950: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111271950);
                pActor->_Z = -1500000;
                pActor->_Y_turn = 150000;
                pActor->_iBeginVelocity = 10000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                break;
            case 1960:
                orderActorWithRotToFactory(111572860, EnemyCeres, "Ceres_82", "M/Ceres", _pRot);
                break;
            case 1980: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111371980);
                pActor->_Z = -1500000;
                pActor->_Y_turn = 200000;
                pActor->_iBeginVelocity = 11000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                orderActorWithRotToFactory(111572880, EnemyCeres, "Ceres_83", "M/Ceres", _pRot);
                break;
            case 2000: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111272000);
                pActor->_Z = -1500000;
                pActor->_Y_turn = 150000;
                pActor->_iBeginVelocity = 10000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                orderActorWithRotToFactory(111572900, EnemyCeres, "Ceres_84", "M/Ceres", _pRot);
                break;
            case 2020: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111372020);
                pActor->_Z = -1500000;
                pActor->_Y_turn = 200000;
                pActor->_iBeginVelocity = 11000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                break;
            case 2060: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111372060);
                pActor->_Z = -1500000;
                pActor->_Y_turn = 200000;
                pActor->_iBeginVelocity = 11000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                break;
            case 2100: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111372100);
                pActor->_Z = -1500000;
                pActor->_Y_turn = 200000;
                pActor->_iBeginVelocity = 11000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                break;
            case 2140: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111372140);
                pActor->_Z = -1500000;
                pActor->_Y_turn = 200000;
                pActor->_iBeginVelocity = 11000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                break;
            case 2180: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111372180);
                pActor->_Z = -1500000;
                pActor->_Y_turn = 200000;
                pActor->_iBeginVelocity = 11000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                break;
            case 2200: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111472200);
                pActor->_Z = -1500000;
                pActor->_Y_turn = 250000;
                pActor->_iBeginVelocity = 12000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                break;
            case 2220: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111372220);
                pActor->_Z = -1500000;
                pActor->_Y_turn = 200000;
                pActor->_iBeginVelocity = 11000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                break;
            case 2230: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111472230);
                pActor->_Z = -1500000;
                pActor->_Y_turn = 250000;
                pActor->_iBeginVelocity = 12000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                break;
            case 2260: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111372260);
                pActor->_Z = -1500000;
                pActor->_Y_turn = 200000;
                pActor->_iBeginVelocity = 11000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                {
                    EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111472260);
                    pActor->_Z = -1500000;
                    pActor->_Y_turn = 250000;
                    pActor->_iBeginVelocity = 12000;
                    getLordActor()->accept(KIND_ENEMY, pActor);
                }
                break;
            case 2290: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111472290);
                pActor->_Z = -1500000;
                pActor->_Y_turn = 250000;
                pActor->_iBeginVelocity = 12000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                break;
            case 2300: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111372300);
                pActor->_Z = -1500000;
                pActor->_Y_turn = 200000;
                pActor->_iBeginVelocity = 11000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                break;
            case 2320: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111472320);
                pActor->_Z = -1500000;
                pActor->_Y_turn = 250000;
                pActor->_iBeginVelocity = 12000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                break;
            case 2350: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111472350);
                pActor->_Z = -1500000;
                pActor->_Y_turn = 250000;
                pActor->_iBeginVelocity = 12000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                break;
            case 2380: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111472380);
                pActor->_Z = -1500000;
                pActor->_Y_turn = 250000;
                pActor->_iBeginVelocity = 12000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                break;
            case 2410: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111472410);
                pActor->_Z = -1500000;
                pActor->_Y_turn = 250000;
                pActor->_iBeginVelocity = 12000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                break;
            case 2440: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111472440);
                pActor->_Z = -1500000;
                pActor->_Y_turn = 250000;
                pActor->_iBeginVelocity = 12000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                break;
            case 2470: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111472470);
                pActor->_Z = -1500000;
                pActor->_Y_turn = 250000;
                pActor->_iBeginVelocity = 12000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                break;
            case 2500: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111472500);
                pActor->_Z = -1500000;
                pActor->_Y_turn = 250000;
                pActor->_iBeginVelocity = 12000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                {
                    EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111572500);
                    pActor->_Z = -1500000;
                    pActor->_Y_turn = 300000;
                    pActor->_iBeginVelocity = 13000;
                    getLordActor()->accept(KIND_ENEMY, pActor);
                }
                break;
            case 2520: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111572520);
                pActor->_Z = -1500000;
                pActor->_Y_turn = 300000;
                pActor->_iBeginVelocity = 13000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                break;
            case 2530: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111472530);
                pActor->_Z = -1500000;
                pActor->_Y_turn = 250000;
                pActor->_iBeginVelocity = 12000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                break;
            case 2540: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111572540);
                pActor->_Z = -1500000;
                pActor->_Y_turn = 300000;
                pActor->_iBeginVelocity = 13000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                break;
            case 2560: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111472560);
                pActor->_Z = -1500000;
                pActor->_Y_turn = 250000;
                pActor->_iBeginVelocity = 12000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                {
                    EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111572560);
                    pActor->_Z = -1500000;
                    pActor->_Y_turn = 300000;
                    pActor->_iBeginVelocity = 13000;
                    getLordActor()->accept(KIND_ENEMY, pActor);
                }
                break;
            case 2580: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111572580);
                pActor->_Z = -1500000;
                pActor->_Y_turn = 300000;
                pActor->_iBeginVelocity = 13000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                break;
            case 2590: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111472590);
                pActor->_Z = -1500000;
                pActor->_Y_turn = 250000;
                pActor->_iBeginVelocity = 12000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                break;
            case 2600: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111572600);
                pActor->_Z = -1500000;
                pActor->_Y_turn = 300000;
                pActor->_iBeginVelocity = 13000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                break;
            case 2620: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111572620);
                pActor->_Z = -1500000;
                pActor->_Y_turn = 300000;
                pActor->_iBeginVelocity = 13000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                break;
            case 2640: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111572640);
                pActor->_Z = -1500000;
                pActor->_Y_turn = 300000;
                pActor->_iBeginVelocity = 13000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                break;
            case 2660: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111572660);
                pActor->_Z = -1500000;
                pActor->_Y_turn = 300000;
                pActor->_iBeginVelocity = 13000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                break;
            case 2680: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111572680);
                pActor->_Z = -1500000;
                pActor->_Y_turn = 300000;
                pActor->_iBeginVelocity = 13000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                break;
            case 2700: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111572700);
                pActor->_Z = -1500000;
                pActor->_Y_turn = 300000;
                pActor->_iBeginVelocity = 13000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                break;
            case 2720: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111572720);
                pActor->_Z = -1500000;
                pActor->_Y_turn = 300000;
                pActor->_iBeginVelocity = 13000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                break;
            case 2740: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111572740);
                pActor->_Z = -1500000;
                pActor->_Y_turn = 300000;
                pActor->_iBeginVelocity = 13000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                break;
            case 2760: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111572760);
                pActor->_Z = -1500000;
                pActor->_Y_turn = 300000;
                pActor->_iBeginVelocity = 13000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                break;
            case 2780: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111572780);
                pActor->_Z = -1500000;
                pActor->_Y_turn = 300000;
                pActor->_iBeginVelocity = 13000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                break;
            case 2800: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111572800);
                pActor->_Z = -1500000;
                pActor->_Y_turn = 300000;
                pActor->_iBeginVelocity = 13000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                break;
            case 2820: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111572820);
                pActor->_Z = -1500000;
                pActor->_Y_turn = 300000;
                pActor->_iBeginVelocity = 13000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                break;
            case 2840: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111572840);
                pActor->_Z = -1500000;
                pActor->_Y_turn = 300000;
                pActor->_iBeginVelocity = 13000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                break;
            case 2860: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111572860);
                pActor->_Z = -1500000;
                pActor->_Y_turn = 300000;
                pActor->_iBeginVelocity = 13000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                break;
            case 2880: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111572880);
                pActor->_Z = -1500000;
                pActor->_Y_turn = 300000;
                pActor->_iBeginVelocity = 13000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                break;
            case 2900: {
                EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111572900);
                pActor->_Z = -1500000;
                pActor->_Y_turn = 300000;
                pActor->_iBeginVelocity = 13000;
                getLordActor()->accept(KIND_ENEMY, pActor);
            }
                break;
            default:
                break;
        }
        _iCnt_Event++;
    }
    // gen02 end

    if (_dwFrame == 2) {

        _TRACE_("Stage01MainScene::processBehavior はいはいDemoさんありがとう、私も起動しましたよ");
        // 共通シーンを配下に移動
        addSubLast(GameGlobal::_pSceneCommon->tear());

    }

}

void Stage01MainScene::processFinal() {
    //	if (_dwFrame == 1) {
    //		_TRACE_("Stage01MainScene::processFinally 私はいきなり停止します。GameMainSceneが解除してくれるはずー");
    //		this->refrain(); //GameMainSceneが解除してくれる
    //	}
}

Stage01MainScene::~Stage01MainScene() {
}
