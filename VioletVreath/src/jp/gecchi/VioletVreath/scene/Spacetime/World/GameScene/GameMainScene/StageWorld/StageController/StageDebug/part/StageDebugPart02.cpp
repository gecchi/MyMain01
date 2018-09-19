#include "StageDebugPart02.h"

#include "jp/ggaf/core/actor/GgafSceneMediator.h"
#include "jp/ggaf/dxcore/sound/GgafDxBgmConductor.h"
#include "jp/ggaf/lib/scene/FormationTableScene.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "../StageDebugPartController.h"
#include "jp/ggaf/dxcore/manager/GgafDxBgmConnection.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

StageDebugPart02::StageDebugPart02(const char* prm_name) :
        StageDebugPart<GgafLib::DefaultScene>(prm_name, EVENT_STAGE_DEBUG_PART_02_WAS_FINISHED) {
    _class_name = "StageDebugPart02";
    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
    frame f[] = {1,10,40,70,100,130,160,190,220,250,280,310,340,370,400,430,460,490,520,550,580,610,640,670,700,730,760,790,820,850,880,910,940,970,1000,1030,1060,1090,1120,1150,1180,1210,1240,1270,1300,1330,1360,1390,1420,1450,1480,1510,1540,1570,1600,1630,1660,1690,1700,1720,1750,1780,1810,1840,1870,1900,1930,1960,1990,2020,2050,2080,2100,2110,2140,2170,2200,2230,2260,2290,2300,2320,2350,2380,2400,2410,2440,2470,2500,2530,2560,2590,2620,2650,2680,2700,2710,2740,2770,2800,2830,2860,2890,2920,2950,2980,3000,3010,3040,3070,3100,3130,3160,3190,3220,3250,3280,3310,3340,3370,3400,3430,3460,3490,3520,3550,3580,3610,3640,3670,3700,3730,3760,3790,3820,3850,3880,3910,3940,3970,4000,4030,4060,4090,4120,4150,4180,4210,4240,4270,4300,4330,4360,4390,4400,4420,4450,4480,4510,4540,4570,4600,4630,4660,4690,4720,4750,4780,4810,4840,4870,4900,4930,4960,4990,5000,5020,5050,5080,5110,5140,5170,5200,5230,5260,5290,5320,5350,5380,5400,5410,5440,5470,5500,5530,5560,5590,5620,5650,5680,5710,5740,5770,5800,5830,5860,5890,5920,5950,5980,6000,6010,6040,6070,6100,6130,6160,6190,6220,6250,6280,6310,6340,6370,6400,6430,6460,6490,6520,6550,6580,6610,6640,6670,6700,6730,6760,6790,6820,6850,6880,6910,6940,6970,7000,7030,7060,7090,7120,7150,7180,7210,7240,7270,7300,7330,7360,7390,7400,7420,7450,7480,7510,7540,7570,7600,7630,7660,7690,7720,7750,7780,7810,7840,7870,7900,7930,7960,7990,8000,8020,8050,8080,8110,8140,8170,8200,8230,8260,8290,8320,8350,8380,8400,8410,8440,8470,8500,8530,8560,8590,8600,8620,8650,8680,8710,8740,8770,8800,8830,8860,8890,8900,8920,8950,8980,9000,9010,9040,9070,9100,9130,9160,9190,9200,9220,9250,9280,9310,9340,9370,9400,9430,9460,9490,9500,9520,9550,9580,9610,9640,9670,9700,9730,9760,9790,9820,9850,9880,9910,9940,9970,10000,10030,10060,10090,10120,10150,10180,10210,10240,10270,10300,10330,10360,10390,10420,10450,10480,10510,10540,10570,10600,10630,10660,10690,10720,10750,10780,10810,10840,10870,10900,10930,10960,10990,11020,11050,11080,11110,11140,11170,11200,11230,11260,11290,11320,11350,11380,11410,11440,11470,11500,11530,11560,11590,11620,11650,11680,11710,11740,11770,11800,11830,11860,11890,11920,11950,11980,12010,12040,12070,12100,12130,12160,12190,12220,12250,12280,12310,12340,12370,12400,12430,12460,12490,12520,12550,12580,12610,12640,12670,12700,12730,12760,12790,12820,12850,12880,12910,12940,12970,13000,13030,13060,13090,13120,13150,13180,13210,13240,13270,13300,13330,13360,13390,13420,13450,13480,13510,13540,13570,13600,13630,13660,13690,13720,13750,13780,13810,13840,13870,13900,13930,13960,13990,14020,14050,14080,14110,14140,14170,14200,14230,14260,14290,14320,14350,14380,14410,14440,14470,14500,14530,14560,14590,14620,14650,14680,14710,14740,14770,14800,14830,14860,14890,14920,14950,14980,15010,15040,15070,15100,15130,15160,15190,15220,15250,15280,15310,15340,15370,15400,15430,15460,15490,15520,15550,15580,15610,15640,15670,15700,15730,15760,15790,15820,15850,15880,15910,15940,15970,16000,16030,16060,16090,16120,16150,16180,16210,16240,16270,16300,16330,16360,16390,16420,16450,16480,16510,16540,16570,16600,16630,16660,16690,16720,16750,16780,16810,16840,16870,16900,16930,16960,16990,17020,17050,17080,17110,17140,17170,17200,17230,17260,17290,17320,17350,17380,17410,17440,17470,17500,17530,17560,17590,17620,17650,17680,17710,17740,17770,17800,17830,17860,17890,17920,17950,17980,18010,18040,18070,18100,18130,18160,18190,18220,18250,18280,18310,18340,18370,18400,18430,18460,18490,18520,18550,18580,18610,18640,18670,18700,18730,18760,18790,18820,18850,18880,18910,18940,18970,19000,19030,19060,19090,19120,19150,19180,19210,19240,19270,19300,19330,19360,19390,19420,19450,19480,19510,19540,19570,19600,19630,19660,19690,19720,19750,19780,19810,19840,19870,19900,19930,19960,19990,20020,20050,20080,20110,20140,20170,20200,20230,20260,20290,20320,20350,20380,20410,20440,20470,20500,20530,20560,20590,20620,20650,20680,20710,20740,20770,20800,20830,20860,20890,20920,20950,20980,21010,21040,21070,21100,21130,21160,21190,21220,21250,21280,21310,21340,21370,21400,21430,21460,21490,21520,21550,21580,21610,21640,21670,21700,21730,21760,21790,21820,21850,21880,21910,21940,21970,22000,22030,22060,22090,22120,22150,22180,22210,22240,22270,22300,22330,22360,22390,22420,22450,22480,22510,22540,22570,22600,22630,22660,22690,22720,22750,22780,22810,22840,22870,22900,22930,22960,22990,23020,23050,23080,23110,23140,23170,23200,23230,23260,23290,23320,23350,23380,23410,23440,23470,23500,23530,23560,23590,23620,23650,23680,23710,23740,23770,23800,23830,23860,23890,23920,23950,23980,24010,24040,24070,24100,24130,24160,24190,24220,24250,24280,24310,24340,24370,24400,24430,24460,24490,24520,24550,24580,24610,24640,24670,24700,24730,24760,24790,24820,24850,24880,24910,24940,24970,25000,25030,25060,25090,25120,25150,25180,25210,25240,25270,25300,25330,25360,25390,25420,25450,25480,25510,25540,25570,25600,25630,25660,25690,25720,25750,25780,25810,25840,25870,25900,25930,25960,25990,26020,26050,26080,26110,26140,26170,26200,26230,26260,26290,26320,26350,26380,26410,26440,26470,26500,26530,26560,26590,26620,26650,26680,26710,26740,26770,26800,26830,26860,26890,26920,26950,26980,27010,27040,27070,27100,27130,27160,27190,27220,27250,27280,27310,27340,27370,27400,27430,27460,27490,27520,27550,27580,27610,27640,27670,27700,27730,27760,27790,27820,27850,27880,27910,27940,27970,28000,28030,28060,28090,28120,28150,28180,28210,28240,28270,28300,28330,28360,28390,28420,28450,28480,28510,28540,28570,28600,28630,28660,28690,28720,28750,28780,28810,28840,28870,28900,28930,28960,28990,29020,29050,29080,29110,29140,29170,29200,29230,29260,29290,29320,29350,29380,29410,29440,29470,29500,29530,29560,29590,29620,29650,29680,29710,29740,29770,29800,29830,29860,29890,29920,29950,29980};
    _paFrame_NextEvent = new frame[1019];
    memcpy(_paFrame_NextEvent, f, sizeof(f));
    _event_num = 1019;
    requestActor(30000000, EnemyEtis, "EnemyEtis-30000000");
    requestActor(30000001, EnemyEtis, "EnemyEtis-30000001");
    requestActor(30000002, EnemyEtis, "EnemyEtis-30000002");
    requestActor(30000003, EnemyEtis, "EnemyEtis-30000003");
    requestActor(30000004, EnemyEtis, "EnemyEtis-30000004");
    requestActor(30000005, EnemyEtis, "EnemyEtis-30000005");
    requestActor(30000006, EnemyEtis, "EnemyEtis-30000006");
    requestActor(30000007, EnemyEtis, "EnemyEtis-30000007");
    requestActor(30000008, EnemyEtis, "EnemyEtis-30000008");
    requestActor(30000009, EnemyEtis, "EnemyEtis-30000009");
    requestActor(30000010, EnemyEtis, "EnemyEtis-30000010");
    requestActor(30000011, EnemyEtis, "EnemyEtis-30000011");
    requestActor(30000012, EnemyEtis, "EnemyEtis-30000012");
    requestActor(30000013, EnemyEtis, "EnemyEtis-30000013");
    requestActor(30000014, EnemyEtis, "EnemyEtis-30000014");
    requestActor(30000015, EnemyEtis, "EnemyEtis-30000015");
    requestActor(30000016, EnemyEtis, "EnemyEtis-30000016");
    // gen01 end

    getBgmConductor()->ready(0, "OGG_BGM_01_02");
}

void StageDebugPart02::initialize() {

}

void StageDebugPart02::processBehavior() {
    // 以下の gen02 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen02 start
    if (getBehaveingFrame() == _paFrame_NextEvent[_cnt_event]) {
        switch (getBehaveingFrame()) {
            case 1: {
                break;
            }
            case 10: {
                requestActor(30000017, EnemyEtis, "EnemyEtis-30000017");
                break;
            }
            case 40: {
                requestActor(30000018, EnemyEtis, "EnemyEtis-30000018");
                break;
            }
            case 70: {
                requestActor(30000019, EnemyEtis, "EnemyEtis-30000019");
                break;
            }
            case 100: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000000);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000020, EnemyEtis, "EnemyEtis-30000020");
                break;
            }
            case 130: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000001);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000021, EnemyEtis, "EnemyEtis-30000021");
                break;
            }
            case 160: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000002);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000022, EnemyEtis, "EnemyEtis-30000022");
                break;
            }
            case 190: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000003);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000023, EnemyEtis, "EnemyEtis-30000023");
                break;
            }
            case 220: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000004);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000024, EnemyEtis, "EnemyEtis-30000024");
                break;
            }
            case 250: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000005);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000025, EnemyEtis, "EnemyEtis-30000025");
                break;
            }
            case 280: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000006);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000026, EnemyEtis, "EnemyEtis-30000026");
                break;
            }
            case 310: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000007);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000027, EnemyEtis, "EnemyEtis-30000027");
                break;
            }
            case 340: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000008);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000028, EnemyEtis, "EnemyEtis-30000028");
                break;
            }
            case 370: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000009);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000029, EnemyEtis, "EnemyEtis-30000029");
                break;
            }
            case 400: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000010);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000030, EnemyEtis, "EnemyEtis-30000030");
                requestActor(30000997, VarietyRatislavia001, "VarietyRatislavia001-30000997");
                requestActor(30001018, FormationHalia, "FormationHalia-30001018");
                requestActor(30001029, FormationEbe001, "FormationEbe001-30001029");
                break;
            }
            case 430: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000011);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000031, EnemyEtis, "EnemyEtis-30000031");
                break;
            }
            case 460: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000012);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000032, EnemyEtis, "EnemyEtis-30000032");
                break;
            }
            case 490: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000013);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000033, EnemyEtis, "EnemyEtis-30000033");
                break;
            }
            case 520: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000014);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000034, EnemyEtis, "EnemyEtis-30000034");
                break;
            }
            case 550: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000015);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000035, EnemyEtis, "EnemyEtis-30000035");
                break;
            }
            case 580: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000016);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000036, EnemyEtis, "EnemyEtis-30000036");
                break;
            }
            case 610: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000017);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000037, EnemyEtis, "EnemyEtis-30000037");
                break;
            }
            case 640: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000018);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000038, EnemyEtis, "EnemyEtis-30000038");
                break;
            }
            case 670: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000019);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000039, EnemyEtis, "EnemyEtis-30000039");
                break;
            }
            case 700: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000020);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000040, EnemyEtis, "EnemyEtis-30000040");
                break;
            }
            case 730: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000021);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000041, EnemyEtis, "EnemyEtis-30000041");
                break;
            }
            case 760: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000022);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000042, EnemyEtis, "EnemyEtis-30000042");
                break;
            }
            case 790: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000023);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000043, EnemyEtis, "EnemyEtis-30000043");
                break;
            }
            case 820: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000024);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000044, EnemyEtis, "EnemyEtis-30000044");
                break;
            }
            case 850: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000025);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000045, EnemyEtis, "EnemyEtis-30000045");
                break;
            }
            case 880: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000026);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000046, EnemyEtis, "EnemyEtis-30000046");
                break;
            }
            case 910: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000027);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000047, EnemyEtis, "EnemyEtis-30000047");
                break;
            }
            case 940: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000028);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000048, EnemyEtis, "EnemyEtis-30000048");
                break;
            }
            case 970: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000029);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000049, EnemyEtis, "EnemyEtis-30000049");
                break;
            }
            case 1000: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000030);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000050, EnemyEtis, "EnemyEtis-30000050");
                VarietyRatislavia001* pRatislavia = (VarietyRatislavia001*)receiveActor(30000997);
                bringSceneMediator()->addSubGroup(pRatislavia);
                FormationHalia* pF = (FormationHalia*)receiveActor(30001018);
                bringSceneMediator()->addSubGroup(pF);
                FormationEbe001* pF1 = (FormationEbe001*)receiveActor(30001029);
                bringSceneMediator()->addSubGroup(pF1);
                break;
            }
            case 1030: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000031);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000051, EnemyEtis, "EnemyEtis-30000051");
                break;
            }
            case 1060: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000032);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000052, EnemyEtis, "EnemyEtis-30000052");
                break;
            }
            case 1090: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000033);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000053, EnemyEtis, "EnemyEtis-30000053");
                break;
            }
            case 1120: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000034);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000054, EnemyEtis, "EnemyEtis-30000054");
                break;
            }
            case 1150: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000035);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000055, EnemyEtis, "EnemyEtis-30000055");
                break;
            }
            case 1180: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000036);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000056, EnemyEtis, "EnemyEtis-30000056");
                break;
            }
            case 1210: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000037);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000057, EnemyEtis, "EnemyEtis-30000057");
                break;
            }
            case 1240: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000038);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000058, EnemyEtis, "EnemyEtis-30000058");
                break;
            }
            case 1270: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000039);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000059, EnemyEtis, "EnemyEtis-30000059");
                break;
            }
            case 1300: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000040);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000060, EnemyEtis, "EnemyEtis-30000060");
                break;
            }
            case 1330: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000041);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000061, EnemyEtis, "EnemyEtis-30000061");
                break;
            }
            case 1360: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000042);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000062, EnemyEtis, "EnemyEtis-30000062");
                break;
            }
            case 1390: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000043);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000063, EnemyEtis, "EnemyEtis-30000063");
                break;
            }
            case 1420: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000044);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000064, EnemyEtis, "EnemyEtis-30000064");
                break;
            }
            case 1450: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000045);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000065, EnemyEtis, "EnemyEtis-30000065");
                break;
            }
            case 1480: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000046);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000066, EnemyEtis, "EnemyEtis-30000066");
                break;
            }
            case 1510: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000047);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000067, EnemyEtis, "EnemyEtis-30000067");
                break;
            }
            case 1540: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000048);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000068, EnemyEtis, "EnemyEtis-30000068");
                break;
            }
            case 1570: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000049);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000069, EnemyEtis, "EnemyEtis-30000069");
                break;
            }
            case 1600: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000050);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000070, EnemyEtis, "EnemyEtis-30000070");
                break;
            }
            case 1630: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000051);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000071, EnemyEtis, "EnemyEtis-30000071");
                break;
            }
            case 1660: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000052);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000072, EnemyEtis, "EnemyEtis-30000072");
                break;
            }
            case 1690: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000053);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000073, EnemyEtis, "EnemyEtis-30000073");
                break;
            }
            case 1700: {
                requestActor(30000998, EnemyStraea, "EnemyStraea-30000998");
                break;
            }
            case 1720: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000054);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000074, EnemyEtis, "EnemyEtis-30000074");
                break;
            }
            case 1750: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000055);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000075, EnemyEtis, "EnemyEtis-30000075");
                break;
            }
            case 1780: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000056);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000076, EnemyEtis, "EnemyEtis-30000076");
                break;
            }
            case 1810: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000057);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000077, EnemyEtis, "EnemyEtis-30000077");
                break;
            }
            case 1840: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000058);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000078, EnemyEtis, "EnemyEtis-30000078");
                break;
            }
            case 1870: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000059);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000079, EnemyEtis, "EnemyEtis-30000079");
                break;
            }
            case 1900: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000060);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000080, EnemyEtis, "EnemyEtis-30000080");
                requestActor(30000999, FormationEmilia, "FormationEmilia-30000999");
                break;
            }
            case 1930: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000061);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000081, EnemyEtis, "EnemyEtis-30000081");
                break;
            }
            case 1960: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000062);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000082, EnemyEtis, "EnemyEtis-30000082");
                break;
            }
            case 1990: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000063);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000083, EnemyEtis, "EnemyEtis-30000083");
                break;
            }
            case 2020: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000064);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000084, EnemyEtis, "EnemyEtis-30000084");
                break;
            }
            case 2050: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000065);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000085, EnemyEtis, "EnemyEtis-30000085");
                break;
            }
            case 2080: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000066);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000086, EnemyEtis, "EnemyEtis-30000086");
                break;
            }
            case 2100: {
                requestActor(30001001, FormationAllas001a, "FormationAllas001a-30001001");
                requestActor(30001002, FormationAllas001b, "FormationAllas001b-30001002");
                requestActor(30001003, FormationAllas001c, "FormationAllas001c-30001003");
                requestActor(30001004, FormationAllas001d, "FormationAllas001d-30001004");
                requestActor(30001005, FormationAllas001a, "FormationAllas001a-30001005");
                requestActor(30001006, FormationAllas001d, "FormationAllas001d-30001006");
                requestActor(30001007, FormationAllas001b, "FormationAllas001b-30001007");
                requestActor(30001008, FormationAllas001c, "FormationAllas001c-30001008");
                requestActor(30001009, FormationAllas001a, "FormationAllas001a-30001009");
                requestActor(30001010, FormationAllas001d, "FormationAllas001d-30001010");
                requestActor(30001011, FormationAllas001b, "FormationAllas001b-30001011");
                requestActor(30001012, FormationAllas001c, "FormationAllas001c-30001012");
                break;
            }
            case 2110: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000067);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000087, EnemyEtis, "EnemyEtis-30000087");
                break;
            }
            case 2140: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000068);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000088, EnemyEtis, "EnemyEtis-30000088");
                break;
            }
            case 2170: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000069);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000089, EnemyEtis, "EnemyEtis-30000089");
                break;
            }
            case 2200: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000070);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000090, EnemyEtis, "EnemyEtis-30000090");
                break;
            }
            case 2230: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000071);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000091, EnemyEtis, "EnemyEtis-30000091");
                break;
            }
            case 2260: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000072);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000092, EnemyEtis, "EnemyEtis-30000092");
                break;
            }
            case 2290: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000073);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000093, EnemyEtis, "EnemyEtis-30000093");
                break;
            }
            case 2300: {
                EnemyStraea* pStraea2 = (EnemyStraea*)receiveActor(30000998);
                bringSceneMediator()->addSubGroup(pStraea2);
                pStraea2->_z = 1800000;
                pStraea2->_y = -100000;
                break;
            }
            case 2320: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000074);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000094, EnemyEtis, "EnemyEtis-30000094");
                break;
            }
            case 2350: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000075);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000095, EnemyEtis, "EnemyEtis-30000095");
                break;
            }
            case 2380: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000076);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000096, EnemyEtis, "EnemyEtis-30000096");
                break;
            }
            case 2400: {
                requestActor(30001013, FormationGeria001, "FormationGeria001-30001013");
                break;
            }
            case 2410: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000077);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000097, EnemyEtis, "EnemyEtis-30000097");
                break;
            }
            case 2440: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000078);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000098, EnemyEtis, "EnemyEtis-30000098");
                break;
            }
            case 2470: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000079);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000099, EnemyEtis, "EnemyEtis-30000099");
                break;
            }
            case 2500: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000080);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000100, EnemyEtis, "EnemyEtis-30000100");
                FormationEmilia* pFormationEmilia = (FormationEmilia*)receiveActor(30000999);
                bringSceneMediator()->addSubGroup(pFormationEmilia);
                break;
            }
            case 2530: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000081);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000101, EnemyEtis, "EnemyEtis-30000101");
                break;
            }
            case 2560: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000082);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000102, EnemyEtis, "EnemyEtis-30000102");
                break;
            }
            case 2590: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000083);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000103, EnemyEtis, "EnemyEtis-30000103");
                break;
            }
            case 2620: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000084);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000104, EnemyEtis, "EnemyEtis-30000104");
                break;
            }
            case 2650: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000085);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000105, EnemyEtis, "EnemyEtis-30000105");
                break;
            }
            case 2680: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000086);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000106, EnemyEtis, "EnemyEtis-30000106");
                break;
            }
            case 2700: {
                {
                FormationTableScene* ta = NEW FormationTableScene("FormationTableScene-2");
                ta->setMaxPerformFrame(2500);
                addSubLast(ta);
                ta->addToTable(((FormationAllas001a*)receiveActor(30001001)), 400);
                ta->addToTable(((FormationAllas001b*)receiveActor(30001002)), 400);
                ta->addToTable(((FormationAllas001c*)receiveActor(30001003)), 400);
                ta->addToTable(((FormationAllas001d*)receiveActor(30001004)), 400);
                ta->addToTable(((FormationAllas001a*)receiveActor(30001005)), 1);
                ta->addToTable(((FormationAllas001d*)receiveActor(30001006)), 400);
                ta->addToTable(((FormationAllas001b*)receiveActor(30001007)), 1);
                ta->addToTable(((FormationAllas001c*)receiveActor(30001008)), 400);
                ta->addToTable(((FormationAllas001a*)receiveActor(30001009)), 1);
                ta->addToTable(((FormationAllas001d*)receiveActor(30001010)), 1);
                ta->addToTable(((FormationAllas001b*)receiveActor(30001011)), 1);
                ta->addToTable(((FormationAllas001c*)receiveActor(30001012)), 400);
                }
                break;
            }
            case 2710: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000087);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000107, EnemyEtis, "EnemyEtis-30000107");
                break;
            }
            case 2740: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000088);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000108, EnemyEtis, "EnemyEtis-30000108");
                break;
            }
            case 2770: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000089);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000109, EnemyEtis, "EnemyEtis-30000109");
                break;
            }
            case 2800: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000090);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000110, EnemyEtis, "EnemyEtis-30000110");
                break;
            }
            case 2830: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000091);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000111, EnemyEtis, "EnemyEtis-30000111");
                break;
            }
            case 2860: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000092);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000112, EnemyEtis, "EnemyEtis-30000112");
                break;
            }
            case 2890: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000093);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000113, EnemyEtis, "EnemyEtis-30000113");
                break;
            }
            case 2920: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000094);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000114, EnemyEtis, "EnemyEtis-30000114");
                break;
            }
            case 2950: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000095);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000115, EnemyEtis, "EnemyEtis-30000115");
                break;
            }
            case 2980: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000096);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000116, EnemyEtis, "EnemyEtis-30000116");
                break;
            }
            case 3000: {
                FormationGeria001* pF3 = (FormationGeria001*)receiveActor(30001013);
                bringSceneMediator()->addSubGroup(pF3);
                break;
            }
            case 3010: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000097);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000117, EnemyEtis, "EnemyEtis-30000117");
                break;
            }
            case 3040: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000098);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000118, EnemyEtis, "EnemyEtis-30000118");
                break;
            }
            case 3070: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000099);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000119, EnemyEtis, "EnemyEtis-30000119");
                break;
            }
            case 3100: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000100);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000120, EnemyEtis, "EnemyEtis-30000120");
                break;
            }
            case 3130: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000101);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000121, EnemyEtis, "EnemyEtis-30000121");
                break;
            }
            case 3160: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000102);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000122, EnemyEtis, "EnemyEtis-30000122");
                break;
            }
            case 3190: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000103);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000123, EnemyEtis, "EnemyEtis-30000123");
                break;
            }
            case 3220: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000104);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000124, EnemyEtis, "EnemyEtis-30000124");
                break;
            }
            case 3250: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000105);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000125, EnemyEtis, "EnemyEtis-30000125");
                break;
            }
            case 3280: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000106);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000126, EnemyEtis, "EnemyEtis-30000126");
                break;
            }
            case 3310: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000107);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000127, EnemyEtis, "EnemyEtis-30000127");
                break;
            }
            case 3340: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000108);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000128, EnemyEtis, "EnemyEtis-30000128");
                break;
            }
            case 3370: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000109);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000129, EnemyEtis, "EnemyEtis-30000129");
                break;
            }
            case 3400: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000110);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000130, EnemyEtis, "EnemyEtis-30000130");
                requestActor(30001014, VarietyRatislavia001, "VarietyRatislavia001-30001014");
                break;
            }
            case 3430: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000111);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000131, EnemyEtis, "EnemyEtis-30000131");
                break;
            }
            case 3460: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000112);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000132, EnemyEtis, "EnemyEtis-30000132");
                break;
            }
            case 3490: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000113);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000133, EnemyEtis, "EnemyEtis-30000133");
                break;
            }
            case 3520: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000114);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000134, EnemyEtis, "EnemyEtis-30000134");
                break;
            }
            case 3550: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000115);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000135, EnemyEtis, "EnemyEtis-30000135");
                break;
            }
            case 3580: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000116);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000136, EnemyEtis, "EnemyEtis-30000136");
                break;
            }
            case 3610: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000117);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000137, EnemyEtis, "EnemyEtis-30000137");
                break;
            }
            case 3640: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000118);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000138, EnemyEtis, "EnemyEtis-30000138");
                break;
            }
            case 3670: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000119);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000139, EnemyEtis, "EnemyEtis-30000139");
                break;
            }
            case 3700: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000120);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000140, EnemyEtis, "EnemyEtis-30000140");
                break;
            }
            case 3730: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000121);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000141, EnemyEtis, "EnemyEtis-30000141");
                break;
            }
            case 3760: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000122);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000142, EnemyEtis, "EnemyEtis-30000142");
                break;
            }
            case 3790: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000123);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000143, EnemyEtis, "EnemyEtis-30000143");
                break;
            }
            case 3820: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000124);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000144, EnemyEtis, "EnemyEtis-30000144");
                break;
            }
            case 3850: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000125);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000145, EnemyEtis, "EnemyEtis-30000145");
                break;
            }
            case 3880: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000126);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000146, EnemyEtis, "EnemyEtis-30000146");
                break;
            }
            case 3910: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000127);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000147, EnemyEtis, "EnemyEtis-30000147");
                break;
            }
            case 3940: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000128);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000148, EnemyEtis, "EnemyEtis-30000148");
                break;
            }
            case 3970: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000129);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000149, EnemyEtis, "EnemyEtis-30000149");
                break;
            }
            case 4000: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000130);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000150, EnemyEtis, "EnemyEtis-30000150");
                VarietyRatislavia001* pRatislavia = (VarietyRatislavia001*)receiveActor(30001014);
                bringSceneMediator()->addSubGroup(pRatislavia);
                break;
            }
            case 4030: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000131);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000151, EnemyEtis, "EnemyEtis-30000151");
                break;
            }
            case 4060: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000132);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000152, EnemyEtis, "EnemyEtis-30000152");
                break;
            }
            case 4090: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000133);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000153, EnemyEtis, "EnemyEtis-30000153");
                break;
            }
            case 4120: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000134);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000154, EnemyEtis, "EnemyEtis-30000154");
                break;
            }
            case 4150: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000135);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000155, EnemyEtis, "EnemyEtis-30000155");
                break;
            }
            case 4180: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000136);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000156, EnemyEtis, "EnemyEtis-30000156");
                break;
            }
            case 4210: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000137);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000157, EnemyEtis, "EnemyEtis-30000157");
                break;
            }
            case 4240: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000138);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000158, EnemyEtis, "EnemyEtis-30000158");
                break;
            }
            case 4270: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000139);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000159, EnemyEtis, "EnemyEtis-30000159");
                break;
            }
            case 4300: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000140);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000160, EnemyEtis, "EnemyEtis-30000160");
                break;
            }
            case 4330: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000141);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000161, EnemyEtis, "EnemyEtis-30000161");
                break;
            }
            case 4360: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000142);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000162, EnemyEtis, "EnemyEtis-30000162");
                break;
            }
            case 4390: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000143);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000163, EnemyEtis, "EnemyEtis-30000163");
                break;
            }
            case 4400: {
                requestActor(30001015, VarietyRatislavia002, "VarietyRatislavia002-30001015");
                requestActor(30001019, FormationHalia, "FormationHalia-30001019");
                requestActor(30001030, EnemyEsperia, "EnemyEsperia-30001030");
                break;
            }
            case 4420: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000144);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000164, EnemyEtis, "EnemyEtis-30000164");
                break;
            }
            case 4450: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000145);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000165, EnemyEtis, "EnemyEtis-30000165");
                break;
            }
            case 4480: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000146);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000166, EnemyEtis, "EnemyEtis-30000166");
                break;
            }
            case 4510: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000147);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000167, EnemyEtis, "EnemyEtis-30000167");
                break;
            }
            case 4540: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000148);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000168, EnemyEtis, "EnemyEtis-30000168");
                break;
            }
            case 4570: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000149);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000169, EnemyEtis, "EnemyEtis-30000169");
                break;
            }
            case 4600: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000150);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000170, EnemyEtis, "EnemyEtis-30000170");
                break;
            }
            case 4630: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000151);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000171, EnemyEtis, "EnemyEtis-30000171");
                break;
            }
            case 4660: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000152);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000172, EnemyEtis, "EnemyEtis-30000172");
                break;
            }
            case 4690: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000153);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000173, EnemyEtis, "EnemyEtis-30000173");
                break;
            }
            case 4720: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000154);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000174, EnemyEtis, "EnemyEtis-30000174");
                break;
            }
            case 4750: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000155);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000175, EnemyEtis, "EnemyEtis-30000175");
                break;
            }
            case 4780: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000156);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000176, EnemyEtis, "EnemyEtis-30000176");
                break;
            }
            case 4810: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000157);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000177, EnemyEtis, "EnemyEtis-30000177");
                break;
            }
            case 4840: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000158);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000178, EnemyEtis, "EnemyEtis-30000178");
                break;
            }
            case 4870: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000159);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000179, EnemyEtis, "EnemyEtis-30000179");
                break;
            }
            case 4900: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000160);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000180, EnemyEtis, "EnemyEtis-30000180");
                break;
            }
            case 4930: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000161);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000181, EnemyEtis, "EnemyEtis-30000181");
                break;
            }
            case 4960: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000162);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000182, EnemyEtis, "EnemyEtis-30000182");
                break;
            }
            case 4990: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000163);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000183, EnemyEtis, "EnemyEtis-30000183");
                break;
            }
            case 5000: {
                VarietyRatislavia002* pRatislaviaA = (VarietyRatislavia002*)receiveActor(30001015);
                bringSceneMediator()->addSubGroup(pRatislaviaA);
                FormationHalia* pF = (FormationHalia*)receiveActor(30001019);
                bringSceneMediator()->addSubGroup(pF);
                bringSceneMediator()->addSubGroup(receiveActor(30001030));
                break;
            }
            case 5020: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000164);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000184, EnemyEtis, "EnemyEtis-30000184");
                break;
            }
            case 5050: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000165);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000185, EnemyEtis, "EnemyEtis-30000185");
                break;
            }
            case 5080: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000166);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000186, EnemyEtis, "EnemyEtis-30000186");
                break;
            }
            case 5110: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000167);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000187, EnemyEtis, "EnemyEtis-30000187");
                break;
            }
            case 5140: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000168);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000188, EnemyEtis, "EnemyEtis-30000188");
                break;
            }
            case 5170: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000169);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000189, EnemyEtis, "EnemyEtis-30000189");
                break;
            }
            case 5200: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000170);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000190, EnemyEtis, "EnemyEtis-30000190");
                break;
            }
            case 5230: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000171);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000191, EnemyEtis, "EnemyEtis-30000191");
                break;
            }
            case 5260: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000172);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000192, EnemyEtis, "EnemyEtis-30000192");
                break;
            }
            case 5290: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000173);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000193, EnemyEtis, "EnemyEtis-30000193");
                break;
            }
            case 5320: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000174);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000194, EnemyEtis, "EnemyEtis-30000194");
                break;
            }
            case 5350: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000175);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000195, EnemyEtis, "EnemyEtis-30000195");
                break;
            }
            case 5380: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000176);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000196, EnemyEtis, "EnemyEtis-30000196");
                break;
            }
            case 5400: {
                requestActor(30001016, VarietyRatislavia003, "VarietyRatislavia003-30001016");
                requestActor(30001031, EnemyEsperia, "EnemyEsperia-30001031");
                break;
            }
            case 5410: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000177);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000197, EnemyEtis, "EnemyEtis-30000197");
                break;
            }
            case 5440: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000178);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000198, EnemyEtis, "EnemyEtis-30000198");
                break;
            }
            case 5470: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000179);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000199, EnemyEtis, "EnemyEtis-30000199");
                break;
            }
            case 5500: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000180);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000200, EnemyEtis, "EnemyEtis-30000200");
                break;
            }
            case 5530: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000181);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000201, EnemyEtis, "EnemyEtis-30000201");
                break;
            }
            case 5560: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000182);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000202, EnemyEtis, "EnemyEtis-30000202");
                break;
            }
            case 5590: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000183);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000203, EnemyEtis, "EnemyEtis-30000203");
                break;
            }
            case 5620: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000184);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000204, EnemyEtis, "EnemyEtis-30000204");
                break;
            }
            case 5650: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000185);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000205, EnemyEtis, "EnemyEtis-30000205");
                break;
            }
            case 5680: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000186);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000206, EnemyEtis, "EnemyEtis-30000206");
                break;
            }
            case 5710: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000187);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000207, EnemyEtis, "EnemyEtis-30000207");
                break;
            }
            case 5740: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000188);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000208, EnemyEtis, "EnemyEtis-30000208");
                break;
            }
            case 5770: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000189);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000209, EnemyEtis, "EnemyEtis-30000209");
                break;
            }
            case 5800: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000190);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000210, EnemyEtis, "EnemyEtis-30000210");
                break;
            }
            case 5830: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000191);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000211, EnemyEtis, "EnemyEtis-30000211");
                break;
            }
            case 5860: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000192);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000212, EnemyEtis, "EnemyEtis-30000212");
                break;
            }
            case 5890: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000193);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000213, EnemyEtis, "EnemyEtis-30000213");
                break;
            }
            case 5920: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000194);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000214, EnemyEtis, "EnemyEtis-30000214");
                break;
            }
            case 5950: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000195);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000215, EnemyEtis, "EnemyEtis-30000215");
                break;
            }
            case 5980: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000196);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000216, EnemyEtis, "EnemyEtis-30000216");
                break;
            }
            case 6000: {
                VarietyRatislavia003* pRatislaviaB = (VarietyRatislavia003*)receiveActor(30001016);
                bringSceneMediator()->addSubGroup(pRatislaviaB);
                bringSceneMediator()->addSubGroup(receiveActor(30001031));
                break;
            }
            case 6010: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000197);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000217, EnemyEtis, "EnemyEtis-30000217");
                break;
            }
            case 6040: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000198);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000218, EnemyEtis, "EnemyEtis-30000218");
                break;
            }
            case 6070: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000199);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000219, EnemyEtis, "EnemyEtis-30000219");
                break;
            }
            case 6100: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000200);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000220, EnemyEtis, "EnemyEtis-30000220");
                break;
            }
            case 6130: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000201);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000221, EnemyEtis, "EnemyEtis-30000221");
                break;
            }
            case 6160: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000202);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000222, EnemyEtis, "EnemyEtis-30000222");
                break;
            }
            case 6190: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000203);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000223, EnemyEtis, "EnemyEtis-30000223");
                break;
            }
            case 6220: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000204);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000224, EnemyEtis, "EnemyEtis-30000224");
                break;
            }
            case 6250: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000205);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000225, EnemyEtis, "EnemyEtis-30000225");
                break;
            }
            case 6280: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000206);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000226, EnemyEtis, "EnemyEtis-30000226");
                break;
            }
            case 6310: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000207);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000227, EnemyEtis, "EnemyEtis-30000227");
                break;
            }
            case 6340: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000208);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000228, EnemyEtis, "EnemyEtis-30000228");
                break;
            }
            case 6370: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000209);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000229, EnemyEtis, "EnemyEtis-30000229");
                break;
            }
            case 6400: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000210);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000230, EnemyEtis, "EnemyEtis-30000230");
                requestActor(30001017, VarietyRatislavia004, "VarietyRatislavia004-30001017");
                requestActor(30001032, EnemyEsperia, "EnemyEsperia-30001032");
                break;
            }
            case 6430: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000211);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000231, EnemyEtis, "EnemyEtis-30000231");
                break;
            }
            case 6460: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000212);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000232, EnemyEtis, "EnemyEtis-30000232");
                break;
            }
            case 6490: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000213);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000233, EnemyEtis, "EnemyEtis-30000233");
                break;
            }
            case 6520: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000214);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000234, EnemyEtis, "EnemyEtis-30000234");
                break;
            }
            case 6550: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000215);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000235, EnemyEtis, "EnemyEtis-30000235");
                break;
            }
            case 6580: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000216);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000236, EnemyEtis, "EnemyEtis-30000236");
                break;
            }
            case 6610: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000217);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000237, EnemyEtis, "EnemyEtis-30000237");
                break;
            }
            case 6640: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000218);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000238, EnemyEtis, "EnemyEtis-30000238");
                break;
            }
            case 6670: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000219);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000239, EnemyEtis, "EnemyEtis-30000239");
                break;
            }
            case 6700: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000220);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000240, EnemyEtis, "EnemyEtis-30000240");
                break;
            }
            case 6730: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000221);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000241, EnemyEtis, "EnemyEtis-30000241");
                break;
            }
            case 6760: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000222);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000242, EnemyEtis, "EnemyEtis-30000242");
                break;
            }
            case 6790: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000223);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000243, EnemyEtis, "EnemyEtis-30000243");
                break;
            }
            case 6820: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000224);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000244, EnemyEtis, "EnemyEtis-30000244");
                break;
            }
            case 6850: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000225);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000245, EnemyEtis, "EnemyEtis-30000245");
                break;
            }
            case 6880: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000226);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000246, EnemyEtis, "EnemyEtis-30000246");
                break;
            }
            case 6910: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000227);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000247, EnemyEtis, "EnemyEtis-30000247");
                break;
            }
            case 6940: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000228);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000248, EnemyEtis, "EnemyEtis-30000248");
                break;
            }
            case 6970: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000229);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000249, EnemyEtis, "EnemyEtis-30000249");
                break;
            }
            case 7000: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000230);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000250, EnemyEtis, "EnemyEtis-30000250");
                VarietyRatislavia004* pRatislavia = (VarietyRatislavia004*)receiveActor(30001017);
                bringSceneMediator()->addSubGroup(pRatislavia);
                bringSceneMediator()->addSubGroup(receiveActor(30001032));
                break;
            }
            case 7030: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000231);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000251, EnemyEtis, "EnemyEtis-30000251");
                break;
            }
            case 7060: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000232);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000252, EnemyEtis, "EnemyEtis-30000252");
                break;
            }
            case 7090: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000233);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000253, EnemyEtis, "EnemyEtis-30000253");
                break;
            }
            case 7120: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000234);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000254, EnemyEtis, "EnemyEtis-30000254");
                break;
            }
            case 7150: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000235);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000255, EnemyEtis, "EnemyEtis-30000255");
                break;
            }
            case 7180: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000236);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000256, EnemyEtis, "EnemyEtis-30000256");
                break;
            }
            case 7210: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000237);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000257, EnemyEtis, "EnemyEtis-30000257");
                break;
            }
            case 7240: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000238);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000258, EnemyEtis, "EnemyEtis-30000258");
                break;
            }
            case 7270: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000239);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000259, EnemyEtis, "EnemyEtis-30000259");
                break;
            }
            case 7300: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000240);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000260, EnemyEtis, "EnemyEtis-30000260");
                break;
            }
            case 7330: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000241);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000261, EnemyEtis, "EnemyEtis-30000261");
                break;
            }
            case 7360: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000242);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000262, EnemyEtis, "EnemyEtis-30000262");
                break;
            }
            case 7390: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000243);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000263, EnemyEtis, "EnemyEtis-30000263");
                break;
            }
            case 7400: {
                requestActor(30001033, EnemyEsperia, "EnemyEsperia-30001033");
                break;
            }
            case 7420: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000244);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000264, EnemyEtis, "EnemyEtis-30000264");
                break;
            }
            case 7450: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000245);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000265, EnemyEtis, "EnemyEtis-30000265");
                break;
            }
            case 7480: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000246);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000266, EnemyEtis, "EnemyEtis-30000266");
                break;
            }
            case 7510: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000247);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000267, EnemyEtis, "EnemyEtis-30000267");
                break;
            }
            case 7540: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000248);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000268, EnemyEtis, "EnemyEtis-30000268");
                break;
            }
            case 7570: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000249);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000269, EnemyEtis, "EnemyEtis-30000269");
                break;
            }
            case 7600: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000250);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000270, EnemyEtis, "EnemyEtis-30000270");
                break;
            }
            case 7630: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000251);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000271, EnemyEtis, "EnemyEtis-30000271");
                break;
            }
            case 7660: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000252);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000272, EnemyEtis, "EnemyEtis-30000272");
                break;
            }
            case 7690: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000253);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000273, EnemyEtis, "EnemyEtis-30000273");
                break;
            }
            case 7720: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000254);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000274, EnemyEtis, "EnemyEtis-30000274");
                break;
            }
            case 7750: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000255);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000275, EnemyEtis, "EnemyEtis-30000275");
                break;
            }
            case 7780: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000256);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000276, EnemyEtis, "EnemyEtis-30000276");
                break;
            }
            case 7810: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000257);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000277, EnemyEtis, "EnemyEtis-30000277");
                break;
            }
            case 7840: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000258);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000278, EnemyEtis, "EnemyEtis-30000278");
                break;
            }
            case 7870: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000259);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000279, EnemyEtis, "EnemyEtis-30000279");
                break;
            }
            case 7900: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000260);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000280, EnemyEtis, "EnemyEtis-30000280");
                break;
            }
            case 7930: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000261);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000281, EnemyEtis, "EnemyEtis-30000281");
                break;
            }
            case 7960: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000262);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000282, EnemyEtis, "EnemyEtis-30000282");
                break;
            }
            case 7990: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000263);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000283, EnemyEtis, "EnemyEtis-30000283");
                break;
            }
            case 8000: {
                bringSceneMediator()->addSubGroup(receiveActor(30001033));
                break;
            }
            case 8020: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000264);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000284, EnemyEtis, "EnemyEtis-30000284");
                break;
            }
            case 8050: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000265);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000285, EnemyEtis, "EnemyEtis-30000285");
                break;
            }
            case 8080: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000266);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000286, EnemyEtis, "EnemyEtis-30000286");
                break;
            }
            case 8110: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000267);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000287, EnemyEtis, "EnemyEtis-30000287");
                break;
            }
            case 8140: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000268);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000288, EnemyEtis, "EnemyEtis-30000288");
                break;
            }
            case 8170: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000269);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000289, EnemyEtis, "EnemyEtis-30000289");
                break;
            }
            case 8200: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000270);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000290, EnemyEtis, "EnemyEtis-30000290");
                break;
            }
            case 8230: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000271);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000291, EnemyEtis, "EnemyEtis-30000291");
                break;
            }
            case 8260: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000272);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000292, EnemyEtis, "EnemyEtis-30000292");
                break;
            }
            case 8290: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000273);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000293, EnemyEtis, "EnemyEtis-30000293");
                break;
            }
            case 8320: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000274);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000294, EnemyEtis, "EnemyEtis-30000294");
                break;
            }
            case 8350: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000275);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000295, EnemyEtis, "EnemyEtis-30000295");
                break;
            }
            case 8380: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000276);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000296, EnemyEtis, "EnemyEtis-30000296");
                break;
            }
            case 8400: {
                requestActor(30001020, FormationHalia, "FormationHalia-30001020");
                requestActor(30001034, EnemyEsperia, "EnemyEsperia-30001034");
                break;
            }
            case 8410: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000277);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000297, EnemyEtis, "EnemyEtis-30000297");
                break;
            }
            case 8440: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000278);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000298, EnemyEtis, "EnemyEtis-30000298");
                break;
            }
            case 8470: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000279);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000299, EnemyEtis, "EnemyEtis-30000299");
                break;
            }
            case 8500: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000280);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000300, EnemyEtis, "EnemyEtis-30000300");
                break;
            }
            case 8530: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000281);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000301, EnemyEtis, "EnemyEtis-30000301");
                break;
            }
            case 8560: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000282);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000302, EnemyEtis, "EnemyEtis-30000302");
                break;
            }
            case 8590: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000283);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000303, EnemyEtis, "EnemyEtis-30000303");
                break;
            }
            case 8600: {
                requestActor(30001022, FormationRis002, "FormationRis002-30001022");
                requestActor(30001023, FormationRis001, "FormationRis001-30001023");
                requestActor(30001024, FormationRis001, "FormationRis001-30001024");
                requestActor(30001025, FormationRis002, "FormationRis002-30001025");
                requestActor(30001026, FormationRis001, "FormationRis001-30001026");
                requestActor(30001027, FormationRis002, "FormationRis002-30001027");
                break;
            }
            case 8620: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000284);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000304, EnemyEtis, "EnemyEtis-30000304");
                break;
            }
            case 8650: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000285);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000305, EnemyEtis, "EnemyEtis-30000305");
                break;
            }
            case 8680: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000286);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000306, EnemyEtis, "EnemyEtis-30000306");
                break;
            }
            case 8710: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000287);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000307, EnemyEtis, "EnemyEtis-30000307");
                break;
            }
            case 8740: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000288);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000308, EnemyEtis, "EnemyEtis-30000308");
                break;
            }
            case 8770: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000289);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000309, EnemyEtis, "EnemyEtis-30000309");
                break;
            }
            case 8800: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000290);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000310, EnemyEtis, "EnemyEtis-30000310");
                break;
            }
            case 8830: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000291);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000311, EnemyEtis, "EnemyEtis-30000311");
                break;
            }
            case 8860: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000292);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000312, EnemyEtis, "EnemyEtis-30000312");
                break;
            }
            case 8890: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000293);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000313, EnemyEtis, "EnemyEtis-30000313");
                break;
            }
            case 8900: {
                requestActor(30001028, EnemyIrce, "EnemyIrce-30001028");
                break;
            }
            case 8920: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000294);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000314, EnemyEtis, "EnemyEtis-30000314");
                break;
            }
            case 8950: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000295);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000315, EnemyEtis, "EnemyEtis-30000315");
                break;
            }
            case 8980: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000296);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000316, EnemyEtis, "EnemyEtis-30000316");
                break;
            }
            case 9000: {
                FormationHalia* pF = (FormationHalia*)receiveActor(30001020);
                bringSceneMediator()->addSubGroup(pF);
                bringSceneMediator()->addSubGroup(receiveActor(30001034));
                break;
            }
            case 9010: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000297);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000317, EnemyEtis, "EnemyEtis-30000317");
                break;
            }
            case 9040: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000298);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000318, EnemyEtis, "EnemyEtis-30000318");
                break;
            }
            case 9070: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000299);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000319, EnemyEtis, "EnemyEtis-30000319");
                break;
            }
            case 9100: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000300);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000320, EnemyEtis, "EnemyEtis-30000320");
                break;
            }
            case 9130: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000301);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000321, EnemyEtis, "EnemyEtis-30000321");
                break;
            }
            case 9160: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000302);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000322, EnemyEtis, "EnemyEtis-30000322");
                break;
            }
            case 9190: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000303);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000323, EnemyEtis, "EnemyEtis-30000323");
                break;
            }
            case 9200: {
                {
                FormationTableScene* ta = NEW FormationTableScene("FormationTableScene-4");
                ta->setMaxPerformFrame(2000);
                addSubLast(ta);
                ta->addToTable(((FormationRis002*)receiveActor(30001022)), 400);
                ta->addToTable(((FormationRis001*)receiveActor(30001023)), 400);
                ta->addToTable(((FormationRis001*)receiveActor(30001024)), 400);
                ta->addToTable(((FormationRis002*)receiveActor(30001025)), 400);
                ta->addToTable(((FormationRis001*)receiveActor(30001026)), 400);
                ta->addToTable(((FormationRis002*)receiveActor(30001027)), 400);
                }
                break;
            }
            case 9220: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000304);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000324, EnemyEtis, "EnemyEtis-30000324");
                break;
            }
            case 9250: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000305);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000325, EnemyEtis, "EnemyEtis-30000325");
                break;
            }
            case 9280: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000306);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000326, EnemyEtis, "EnemyEtis-30000326");
                break;
            }
            case 9310: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000307);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000327, EnemyEtis, "EnemyEtis-30000327");
                break;
            }
            case 9340: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000308);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000328, EnemyEtis, "EnemyEtis-30000328");
                break;
            }
            case 9370: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000309);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000329, EnemyEtis, "EnemyEtis-30000329");
                break;
            }
            case 9400: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000310);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000330, EnemyEtis, "EnemyEtis-30000330");
                requestActor(30001035, EnemyEsperia, "EnemyEsperia-30001035");
                break;
            }
            case 9430: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000311);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000331, EnemyEtis, "EnemyEtis-30000331");
                break;
            }
            case 9460: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000312);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000332, EnemyEtis, "EnemyEtis-30000332");
                break;
            }
            case 9490: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000313);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000333, EnemyEtis, "EnemyEtis-30000333");
                break;
            }
            case 9500: {
                EnemyIrce* p5 = (EnemyIrce*)receiveActor(30001028);
                bringSceneMediator()->addSubGroup(p5);
                break;
            }
            case 9520: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000314);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000334, EnemyEtis, "EnemyEtis-30000334");
                break;
            }
            case 9550: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000315);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000335, EnemyEtis, "EnemyEtis-30000335");
                break;
            }
            case 9580: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000316);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000336, EnemyEtis, "EnemyEtis-30000336");
                break;
            }
            case 9610: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000317);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000337, EnemyEtis, "EnemyEtis-30000337");
                break;
            }
            case 9640: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000318);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000338, EnemyEtis, "EnemyEtis-30000338");
                break;
            }
            case 9670: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000319);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000339, EnemyEtis, "EnemyEtis-30000339");
                break;
            }
            case 9700: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000320);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000340, EnemyEtis, "EnemyEtis-30000340");
                break;
            }
            case 9730: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000321);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000341, EnemyEtis, "EnemyEtis-30000341");
                break;
            }
            case 9760: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000322);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000342, EnemyEtis, "EnemyEtis-30000342");
                break;
            }
            case 9790: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000323);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000343, EnemyEtis, "EnemyEtis-30000343");
                break;
            }
            case 9820: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000324);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000344, EnemyEtis, "EnemyEtis-30000344");
                break;
            }
            case 9850: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000325);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000345, EnemyEtis, "EnemyEtis-30000345");
                break;
            }
            case 9880: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000326);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000346, EnemyEtis, "EnemyEtis-30000346");
                break;
            }
            case 9910: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000327);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000347, EnemyEtis, "EnemyEtis-30000347");
                break;
            }
            case 9940: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000328);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000348, EnemyEtis, "EnemyEtis-30000348");
                break;
            }
            case 9970: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000329);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000349, EnemyEtis, "EnemyEtis-30000349");
                break;
            }
            case 10000: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000330);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000350, EnemyEtis, "EnemyEtis-30000350");
                bringSceneMediator()->addSubGroup(receiveActor(30001035));
                break;
            }
            case 10030: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000331);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000351, EnemyEtis, "EnemyEtis-30000351");
                break;
            }
            case 10060: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000332);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000352, EnemyEtis, "EnemyEtis-30000352");
                break;
            }
            case 10090: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000333);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000353, EnemyEtis, "EnemyEtis-30000353");
                break;
            }
            case 10120: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000334);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000354, EnemyEtis, "EnemyEtis-30000354");
                break;
            }
            case 10150: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000335);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000355, EnemyEtis, "EnemyEtis-30000355");
                break;
            }
            case 10180: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000336);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000356, EnemyEtis, "EnemyEtis-30000356");
                break;
            }
            case 10210: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000337);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000357, EnemyEtis, "EnemyEtis-30000357");
                break;
            }
            case 10240: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000338);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000358, EnemyEtis, "EnemyEtis-30000358");
                break;
            }
            case 10270: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000339);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000359, EnemyEtis, "EnemyEtis-30000359");
                break;
            }
            case 10300: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000340);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000360, EnemyEtis, "EnemyEtis-30000360");
                break;
            }
            case 10330: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000341);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000361, EnemyEtis, "EnemyEtis-30000361");
                break;
            }
            case 10360: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000342);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000362, EnemyEtis, "EnemyEtis-30000362");
                break;
            }
            case 10390: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000343);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000363, EnemyEtis, "EnemyEtis-30000363");
                break;
            }
            case 10420: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000344);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000364, EnemyEtis, "EnemyEtis-30000364");
                break;
            }
            case 10450: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000345);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000365, EnemyEtis, "EnemyEtis-30000365");
                break;
            }
            case 10480: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000346);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000366, EnemyEtis, "EnemyEtis-30000366");
                break;
            }
            case 10510: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000347);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000367, EnemyEtis, "EnemyEtis-30000367");
                break;
            }
            case 10540: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000348);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000368, EnemyEtis, "EnemyEtis-30000368");
                break;
            }
            case 10570: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000349);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000369, EnemyEtis, "EnemyEtis-30000369");
                break;
            }
            case 10600: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000350);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000370, EnemyEtis, "EnemyEtis-30000370");
                break;
            }
            case 10630: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000351);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000371, EnemyEtis, "EnemyEtis-30000371");
                break;
            }
            case 10660: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000352);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000372, EnemyEtis, "EnemyEtis-30000372");
                break;
            }
            case 10690: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000353);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000373, EnemyEtis, "EnemyEtis-30000373");
                break;
            }
            case 10720: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000354);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000374, EnemyEtis, "EnemyEtis-30000374");
                break;
            }
            case 10750: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000355);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000375, EnemyEtis, "EnemyEtis-30000375");
                break;
            }
            case 10780: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000356);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000376, EnemyEtis, "EnemyEtis-30000376");
                break;
            }
            case 10810: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000357);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000377, EnemyEtis, "EnemyEtis-30000377");
                break;
            }
            case 10840: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000358);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000378, EnemyEtis, "EnemyEtis-30000378");
                break;
            }
            case 10870: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000359);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000379, EnemyEtis, "EnemyEtis-30000379");
                break;
            }
            case 10900: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000360);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000380, EnemyEtis, "EnemyEtis-30000380");
                break;
            }
            case 10930: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000361);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000381, EnemyEtis, "EnemyEtis-30000381");
                break;
            }
            case 10960: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000362);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000382, EnemyEtis, "EnemyEtis-30000382");
                break;
            }
            case 10990: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000363);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000383, EnemyEtis, "EnemyEtis-30000383");
                break;
            }
            case 11020: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000364);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000384, EnemyEtis, "EnemyEtis-30000384");
                break;
            }
            case 11050: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000365);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000385, EnemyEtis, "EnemyEtis-30000385");
                break;
            }
            case 11080: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000366);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000386, EnemyEtis, "EnemyEtis-30000386");
                break;
            }
            case 11110: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000367);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000387, EnemyEtis, "EnemyEtis-30000387");
                break;
            }
            case 11140: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000368);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000388, EnemyEtis, "EnemyEtis-30000388");
                break;
            }
            case 11170: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000369);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000389, EnemyEtis, "EnemyEtis-30000389");
                break;
            }
            case 11200: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000370);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000390, EnemyEtis, "EnemyEtis-30000390");
                break;
            }
            case 11230: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000371);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000391, EnemyEtis, "EnemyEtis-30000391");
                break;
            }
            case 11260: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000372);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000392, EnemyEtis, "EnemyEtis-30000392");
                break;
            }
            case 11290: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000373);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000393, EnemyEtis, "EnemyEtis-30000393");
                break;
            }
            case 11320: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000374);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000394, EnemyEtis, "EnemyEtis-30000394");
                break;
            }
            case 11350: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000375);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000395, EnemyEtis, "EnemyEtis-30000395");
                break;
            }
            case 11380: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000376);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000396, EnemyEtis, "EnemyEtis-30000396");
                break;
            }
            case 11410: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000377);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000397, EnemyEtis, "EnemyEtis-30000397");
                break;
            }
            case 11440: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000378);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000398, EnemyEtis, "EnemyEtis-30000398");
                break;
            }
            case 11470: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000379);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000399, EnemyEtis, "EnemyEtis-30000399");
                break;
            }
            case 11500: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000380);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000400, EnemyEtis, "EnemyEtis-30000400");
                break;
            }
            case 11530: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000381);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000401, EnemyEtis, "EnemyEtis-30000401");
                break;
            }
            case 11560: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000382);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000402, EnemyEtis, "EnemyEtis-30000402");
                break;
            }
            case 11590: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000383);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000403, EnemyEtis, "EnemyEtis-30000403");
                break;
            }
            case 11620: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000384);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000404, EnemyEtis, "EnemyEtis-30000404");
                break;
            }
            case 11650: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000385);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000405, EnemyEtis, "EnemyEtis-30000405");
                break;
            }
            case 11680: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000386);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000406, EnemyEtis, "EnemyEtis-30000406");
                break;
            }
            case 11710: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000387);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000407, EnemyEtis, "EnemyEtis-30000407");
                break;
            }
            case 11740: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000388);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000408, EnemyEtis, "EnemyEtis-30000408");
                break;
            }
            case 11770: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000389);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000409, EnemyEtis, "EnemyEtis-30000409");
                break;
            }
            case 11800: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000390);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000410, EnemyEtis, "EnemyEtis-30000410");
                break;
            }
            case 11830: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000391);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000411, EnemyEtis, "EnemyEtis-30000411");
                break;
            }
            case 11860: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000392);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000412, EnemyEtis, "EnemyEtis-30000412");
                break;
            }
            case 11890: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000393);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000413, EnemyEtis, "EnemyEtis-30000413");
                break;
            }
            case 11920: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000394);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000414, EnemyEtis, "EnemyEtis-30000414");
                break;
            }
            case 11950: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000395);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000415, EnemyEtis, "EnemyEtis-30000415");
                break;
            }
            case 11980: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000396);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000416, EnemyEtis, "EnemyEtis-30000416");
                break;
            }
            case 12010: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000397);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000417, EnemyEtis, "EnemyEtis-30000417");
                break;
            }
            case 12040: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000398);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000418, EnemyEtis, "EnemyEtis-30000418");
                break;
            }
            case 12070: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000399);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000419, EnemyEtis, "EnemyEtis-30000419");
                break;
            }
            case 12100: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000400);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000420, EnemyEtis, "EnemyEtis-30000420");
                break;
            }
            case 12130: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000401);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000421, EnemyEtis, "EnemyEtis-30000421");
                break;
            }
            case 12160: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000402);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000422, EnemyEtis, "EnemyEtis-30000422");
                break;
            }
            case 12190: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000403);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000423, EnemyEtis, "EnemyEtis-30000423");
                break;
            }
            case 12220: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000404);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000424, EnemyEtis, "EnemyEtis-30000424");
                break;
            }
            case 12250: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000405);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000425, EnemyEtis, "EnemyEtis-30000425");
                break;
            }
            case 12280: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000406);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000426, EnemyEtis, "EnemyEtis-30000426");
                break;
            }
            case 12310: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000407);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000427, EnemyEtis, "EnemyEtis-30000427");
                break;
            }
            case 12340: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000408);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000428, EnemyEtis, "EnemyEtis-30000428");
                break;
            }
            case 12370: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000409);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000429, EnemyEtis, "EnemyEtis-30000429");
                break;
            }
            case 12400: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000410);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000430, EnemyEtis, "EnemyEtis-30000430");
                break;
            }
            case 12430: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000411);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000431, EnemyEtis, "EnemyEtis-30000431");
                break;
            }
            case 12460: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000412);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000432, EnemyEtis, "EnemyEtis-30000432");
                break;
            }
            case 12490: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000413);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000433, EnemyEtis, "EnemyEtis-30000433");
                break;
            }
            case 12520: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000414);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000434, EnemyEtis, "EnemyEtis-30000434");
                break;
            }
            case 12550: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000415);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000435, EnemyEtis, "EnemyEtis-30000435");
                break;
            }
            case 12580: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000416);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000436, EnemyEtis, "EnemyEtis-30000436");
                break;
            }
            case 12610: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000417);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000437, EnemyEtis, "EnemyEtis-30000437");
                break;
            }
            case 12640: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000418);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000438, EnemyEtis, "EnemyEtis-30000438");
                break;
            }
            case 12670: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000419);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000439, EnemyEtis, "EnemyEtis-30000439");
                break;
            }
            case 12700: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000420);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000440, EnemyEtis, "EnemyEtis-30000440");
                break;
            }
            case 12730: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000421);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000441, EnemyEtis, "EnemyEtis-30000441");
                break;
            }
            case 12760: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000422);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000442, EnemyEtis, "EnemyEtis-30000442");
                break;
            }
            case 12790: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000423);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000443, EnemyEtis, "EnemyEtis-30000443");
                break;
            }
            case 12820: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000424);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000444, EnemyEtis, "EnemyEtis-30000444");
                break;
            }
            case 12850: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000425);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000445, EnemyEtis, "EnemyEtis-30000445");
                break;
            }
            case 12880: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000426);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000446, EnemyEtis, "EnemyEtis-30000446");
                break;
            }
            case 12910: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000427);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000447, EnemyEtis, "EnemyEtis-30000447");
                break;
            }
            case 12940: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000428);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000448, EnemyEtis, "EnemyEtis-30000448");
                break;
            }
            case 12970: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000429);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000449, EnemyEtis, "EnemyEtis-30000449");
                break;
            }
            case 13000: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000430);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000450, EnemyEtis, "EnemyEtis-30000450");
                break;
            }
            case 13030: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000431);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000451, EnemyEtis, "EnemyEtis-30000451");
                break;
            }
            case 13060: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000432);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000452, EnemyEtis, "EnemyEtis-30000452");
                break;
            }
            case 13090: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000433);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000453, EnemyEtis, "EnemyEtis-30000453");
                break;
            }
            case 13120: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000434);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000454, EnemyEtis, "EnemyEtis-30000454");
                break;
            }
            case 13150: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000435);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000455, EnemyEtis, "EnemyEtis-30000455");
                break;
            }
            case 13180: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000436);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000456, EnemyEtis, "EnemyEtis-30000456");
                break;
            }
            case 13210: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000437);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000457, EnemyEtis, "EnemyEtis-30000457");
                break;
            }
            case 13240: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000438);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000458, EnemyEtis, "EnemyEtis-30000458");
                break;
            }
            case 13270: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000439);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000459, EnemyEtis, "EnemyEtis-30000459");
                break;
            }
            case 13300: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000440);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000460, EnemyEtis, "EnemyEtis-30000460");
                break;
            }
            case 13330: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000441);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000461, EnemyEtis, "EnemyEtis-30000461");
                break;
            }
            case 13360: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000442);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000462, EnemyEtis, "EnemyEtis-30000462");
                break;
            }
            case 13390: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000443);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000463, EnemyEtis, "EnemyEtis-30000463");
                break;
            }
            case 13420: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000444);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000464, EnemyEtis, "EnemyEtis-30000464");
                break;
            }
            case 13450: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000445);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000465, EnemyEtis, "EnemyEtis-30000465");
                break;
            }
            case 13480: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000446);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000466, EnemyEtis, "EnemyEtis-30000466");
                break;
            }
            case 13510: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000447);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000467, EnemyEtis, "EnemyEtis-30000467");
                break;
            }
            case 13540: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000448);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000468, EnemyEtis, "EnemyEtis-30000468");
                break;
            }
            case 13570: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000449);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000469, EnemyEtis, "EnemyEtis-30000469");
                break;
            }
            case 13600: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000450);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000470, EnemyEtis, "EnemyEtis-30000470");
                break;
            }
            case 13630: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000451);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000471, EnemyEtis, "EnemyEtis-30000471");
                break;
            }
            case 13660: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000452);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000472, EnemyEtis, "EnemyEtis-30000472");
                break;
            }
            case 13690: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000453);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000473, EnemyEtis, "EnemyEtis-30000473");
                break;
            }
            case 13720: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000454);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000474, EnemyEtis, "EnemyEtis-30000474");
                break;
            }
            case 13750: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000455);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000475, EnemyEtis, "EnemyEtis-30000475");
                break;
            }
            case 13780: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000456);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000476, EnemyEtis, "EnemyEtis-30000476");
                break;
            }
            case 13810: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000457);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000477, EnemyEtis, "EnemyEtis-30000477");
                break;
            }
            case 13840: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000458);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000478, EnemyEtis, "EnemyEtis-30000478");
                break;
            }
            case 13870: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000459);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000479, EnemyEtis, "EnemyEtis-30000479");
                break;
            }
            case 13900: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000460);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000480, EnemyEtis, "EnemyEtis-30000480");
                break;
            }
            case 13930: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000461);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000481, EnemyEtis, "EnemyEtis-30000481");
                break;
            }
            case 13960: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000462);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000482, EnemyEtis, "EnemyEtis-30000482");
                break;
            }
            case 13990: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000463);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000483, EnemyEtis, "EnemyEtis-30000483");
                break;
            }
            case 14020: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000464);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000484, EnemyEtis, "EnemyEtis-30000484");
                break;
            }
            case 14050: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000465);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000485, EnemyEtis, "EnemyEtis-30000485");
                break;
            }
            case 14080: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000466);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000486, EnemyEtis, "EnemyEtis-30000486");
                break;
            }
            case 14110: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000467);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000487, EnemyEtis, "EnemyEtis-30000487");
                break;
            }
            case 14140: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000468);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000488, EnemyEtis, "EnemyEtis-30000488");
                break;
            }
            case 14170: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000469);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000489, EnemyEtis, "EnemyEtis-30000489");
                break;
            }
            case 14200: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000470);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000490, EnemyEtis, "EnemyEtis-30000490");
                break;
            }
            case 14230: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000471);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000491, EnemyEtis, "EnemyEtis-30000491");
                break;
            }
            case 14260: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000472);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000492, EnemyEtis, "EnemyEtis-30000492");
                break;
            }
            case 14290: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000473);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000493, EnemyEtis, "EnemyEtis-30000493");
                break;
            }
            case 14320: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000474);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000494, EnemyEtis, "EnemyEtis-30000494");
                break;
            }
            case 14350: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000475);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000495, EnemyEtis, "EnemyEtis-30000495");
                break;
            }
            case 14380: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000476);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000496, EnemyEtis, "EnemyEtis-30000496");
                break;
            }
            case 14410: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000477);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000497, EnemyEtis, "EnemyEtis-30000497");
                break;
            }
            case 14440: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000478);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000498, EnemyEtis, "EnemyEtis-30000498");
                break;
            }
            case 14470: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000479);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000499, EnemyEtis, "EnemyEtis-30000499");
                break;
            }
            case 14500: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000480);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000500, EnemyEtis, "EnemyEtis-30000500");
                break;
            }
            case 14530: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000481);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000501, EnemyEtis, "EnemyEtis-30000501");
                break;
            }
            case 14560: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000482);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000502, EnemyEtis, "EnemyEtis-30000502");
                break;
            }
            case 14590: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000483);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000503, EnemyEtis, "EnemyEtis-30000503");
                break;
            }
            case 14620: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000484);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000504, EnemyEtis, "EnemyEtis-30000504");
                break;
            }
            case 14650: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000485);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000505, EnemyEtis, "EnemyEtis-30000505");
                break;
            }
            case 14680: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000486);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000506, EnemyEtis, "EnemyEtis-30000506");
                break;
            }
            case 14710: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000487);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000507, EnemyEtis, "EnemyEtis-30000507");
                break;
            }
            case 14740: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000488);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000508, EnemyEtis, "EnemyEtis-30000508");
                break;
            }
            case 14770: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000489);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000509, EnemyEtis, "EnemyEtis-30000509");
                break;
            }
            case 14800: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000490);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000510, EnemyEtis, "EnemyEtis-30000510");
                break;
            }
            case 14830: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000491);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000511, EnemyEtis, "EnemyEtis-30000511");
                break;
            }
            case 14860: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000492);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000512, EnemyEtis, "EnemyEtis-30000512");
                break;
            }
            case 14890: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000493);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000513, EnemyEtis, "EnemyEtis-30000513");
                break;
            }
            case 14920: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000494);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000514, EnemyEtis, "EnemyEtis-30000514");
                break;
            }
            case 14950: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000495);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000515, EnemyEtis, "EnemyEtis-30000515");
                break;
            }
            case 14980: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000496);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000516, EnemyEtis, "EnemyEtis-30000516");
                break;
            }
            case 15010: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000497);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000517, EnemyEtis, "EnemyEtis-30000517");
                break;
            }
            case 15040: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000498);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000518, EnemyEtis, "EnemyEtis-30000518");
                break;
            }
            case 15070: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000499);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000519, EnemyEtis, "EnemyEtis-30000519");
                break;
            }
            case 15100: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000500);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000520, EnemyEtis, "EnemyEtis-30000520");
                break;
            }
            case 15130: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000501);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000521, EnemyEtis, "EnemyEtis-30000521");
                break;
            }
            case 15160: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000502);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000522, EnemyEtis, "EnemyEtis-30000522");
                break;
            }
            case 15190: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000503);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000523, EnemyEtis, "EnemyEtis-30000523");
                break;
            }
            case 15220: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000504);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000524, EnemyEtis, "EnemyEtis-30000524");
                break;
            }
            case 15250: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000505);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000525, EnemyEtis, "EnemyEtis-30000525");
                break;
            }
            case 15280: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000506);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000526, EnemyEtis, "EnemyEtis-30000526");
                break;
            }
            case 15310: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000507);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000527, EnemyEtis, "EnemyEtis-30000527");
                break;
            }
            case 15340: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000508);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000528, EnemyEtis, "EnemyEtis-30000528");
                break;
            }
            case 15370: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000509);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000529, EnemyEtis, "EnemyEtis-30000529");
                break;
            }
            case 15400: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000510);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000530, EnemyEtis, "EnemyEtis-30000530");
                break;
            }
            case 15430: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000511);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000531, EnemyEtis, "EnemyEtis-30000531");
                break;
            }
            case 15460: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000512);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000532, EnemyEtis, "EnemyEtis-30000532");
                break;
            }
            case 15490: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000513);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000533, EnemyEtis, "EnemyEtis-30000533");
                break;
            }
            case 15520: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000514);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000534, EnemyEtis, "EnemyEtis-30000534");
                break;
            }
            case 15550: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000515);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000535, EnemyEtis, "EnemyEtis-30000535");
                break;
            }
            case 15580: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000516);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000536, EnemyEtis, "EnemyEtis-30000536");
                break;
            }
            case 15610: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000517);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000537, EnemyEtis, "EnemyEtis-30000537");
                break;
            }
            case 15640: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000518);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000538, EnemyEtis, "EnemyEtis-30000538");
                break;
            }
            case 15670: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000519);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000539, EnemyEtis, "EnemyEtis-30000539");
                break;
            }
            case 15700: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000520);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000540, EnemyEtis, "EnemyEtis-30000540");
                break;
            }
            case 15730: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000521);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000541, EnemyEtis, "EnemyEtis-30000541");
                break;
            }
            case 15760: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000522);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000542, EnemyEtis, "EnemyEtis-30000542");
                break;
            }
            case 15790: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000523);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000543, EnemyEtis, "EnemyEtis-30000543");
                break;
            }
            case 15820: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000524);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000544, EnemyEtis, "EnemyEtis-30000544");
                break;
            }
            case 15850: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000525);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000545, EnemyEtis, "EnemyEtis-30000545");
                break;
            }
            case 15880: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000526);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000546, EnemyEtis, "EnemyEtis-30000546");
                break;
            }
            case 15910: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000527);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000547, EnemyEtis, "EnemyEtis-30000547");
                break;
            }
            case 15940: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000528);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000548, EnemyEtis, "EnemyEtis-30000548");
                break;
            }
            case 15970: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000529);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000549, EnemyEtis, "EnemyEtis-30000549");
                break;
            }
            case 16000: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000530);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000550, EnemyEtis, "EnemyEtis-30000550");
                break;
            }
            case 16030: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000531);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000551, EnemyEtis, "EnemyEtis-30000551");
                break;
            }
            case 16060: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000532);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000552, EnemyEtis, "EnemyEtis-30000552");
                break;
            }
            case 16090: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000533);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000553, EnemyEtis, "EnemyEtis-30000553");
                break;
            }
            case 16120: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000534);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000554, EnemyEtis, "EnemyEtis-30000554");
                break;
            }
            case 16150: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000535);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000555, EnemyEtis, "EnemyEtis-30000555");
                break;
            }
            case 16180: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000536);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000556, EnemyEtis, "EnemyEtis-30000556");
                break;
            }
            case 16210: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000537);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000557, EnemyEtis, "EnemyEtis-30000557");
                break;
            }
            case 16240: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000538);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000558, EnemyEtis, "EnemyEtis-30000558");
                break;
            }
            case 16270: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000539);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000559, EnemyEtis, "EnemyEtis-30000559");
                break;
            }
            case 16300: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000540);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000560, EnemyEtis, "EnemyEtis-30000560");
                break;
            }
            case 16330: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000541);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000561, EnemyEtis, "EnemyEtis-30000561");
                break;
            }
            case 16360: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000542);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000562, EnemyEtis, "EnemyEtis-30000562");
                break;
            }
            case 16390: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000543);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000563, EnemyEtis, "EnemyEtis-30000563");
                break;
            }
            case 16420: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000544);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000564, EnemyEtis, "EnemyEtis-30000564");
                break;
            }
            case 16450: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000545);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000565, EnemyEtis, "EnemyEtis-30000565");
                break;
            }
            case 16480: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000546);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000566, EnemyEtis, "EnemyEtis-30000566");
                break;
            }
            case 16510: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000547);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000567, EnemyEtis, "EnemyEtis-30000567");
                break;
            }
            case 16540: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000548);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000568, EnemyEtis, "EnemyEtis-30000568");
                break;
            }
            case 16570: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000549);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000569, EnemyEtis, "EnemyEtis-30000569");
                break;
            }
            case 16600: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000550);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000570, EnemyEtis, "EnemyEtis-30000570");
                break;
            }
            case 16630: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000551);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000571, EnemyEtis, "EnemyEtis-30000571");
                break;
            }
            case 16660: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000552);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000572, EnemyEtis, "EnemyEtis-30000572");
                break;
            }
            case 16690: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000553);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000573, EnemyEtis, "EnemyEtis-30000573");
                break;
            }
            case 16720: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000554);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000574, EnemyEtis, "EnemyEtis-30000574");
                break;
            }
            case 16750: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000555);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000575, EnemyEtis, "EnemyEtis-30000575");
                break;
            }
            case 16780: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000556);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000576, EnemyEtis, "EnemyEtis-30000576");
                break;
            }
            case 16810: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000557);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000577, EnemyEtis, "EnemyEtis-30000577");
                break;
            }
            case 16840: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000558);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000578, EnemyEtis, "EnemyEtis-30000578");
                break;
            }
            case 16870: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000559);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000579, EnemyEtis, "EnemyEtis-30000579");
                break;
            }
            case 16900: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000560);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000580, EnemyEtis, "EnemyEtis-30000580");
                break;
            }
            case 16930: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000561);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000581, EnemyEtis, "EnemyEtis-30000581");
                break;
            }
            case 16960: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000562);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000582, EnemyEtis, "EnemyEtis-30000582");
                break;
            }
            case 16990: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000563);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000583, EnemyEtis, "EnemyEtis-30000583");
                break;
            }
            case 17020: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000564);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000584, EnemyEtis, "EnemyEtis-30000584");
                break;
            }
            case 17050: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000565);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000585, EnemyEtis, "EnemyEtis-30000585");
                break;
            }
            case 17080: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000566);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000586, EnemyEtis, "EnemyEtis-30000586");
                break;
            }
            case 17110: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000567);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000587, EnemyEtis, "EnemyEtis-30000587");
                break;
            }
            case 17140: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000568);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000588, EnemyEtis, "EnemyEtis-30000588");
                break;
            }
            case 17170: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000569);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000589, EnemyEtis, "EnemyEtis-30000589");
                break;
            }
            case 17200: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000570);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000590, EnemyEtis, "EnemyEtis-30000590");
                break;
            }
            case 17230: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000571);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000591, EnemyEtis, "EnemyEtis-30000591");
                break;
            }
            case 17260: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000572);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000592, EnemyEtis, "EnemyEtis-30000592");
                break;
            }
            case 17290: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000573);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000593, EnemyEtis, "EnemyEtis-30000593");
                break;
            }
            case 17320: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000574);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000594, EnemyEtis, "EnemyEtis-30000594");
                break;
            }
            case 17350: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000575);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000595, EnemyEtis, "EnemyEtis-30000595");
                break;
            }
            case 17380: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000576);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000596, EnemyEtis, "EnemyEtis-30000596");
                break;
            }
            case 17410: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000577);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000597, EnemyEtis, "EnemyEtis-30000597");
                break;
            }
            case 17440: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000578);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000598, EnemyEtis, "EnemyEtis-30000598");
                break;
            }
            case 17470: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000579);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000599, EnemyEtis, "EnemyEtis-30000599");
                break;
            }
            case 17500: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000580);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000600, EnemyEtis, "EnemyEtis-30000600");
                break;
            }
            case 17530: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000581);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000601, EnemyEtis, "EnemyEtis-30000601");
                break;
            }
            case 17560: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000582);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000602, EnemyEtis, "EnemyEtis-30000602");
                break;
            }
            case 17590: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000583);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000603, EnemyEtis, "EnemyEtis-30000603");
                break;
            }
            case 17620: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000584);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000604, EnemyEtis, "EnemyEtis-30000604");
                break;
            }
            case 17650: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000585);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000605, EnemyEtis, "EnemyEtis-30000605");
                break;
            }
            case 17680: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000586);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000606, EnemyEtis, "EnemyEtis-30000606");
                break;
            }
            case 17710: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000587);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000607, EnemyEtis, "EnemyEtis-30000607");
                break;
            }
            case 17740: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000588);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000608, EnemyEtis, "EnemyEtis-30000608");
                break;
            }
            case 17770: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000589);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000609, EnemyEtis, "EnemyEtis-30000609");
                break;
            }
            case 17800: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000590);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000610, EnemyEtis, "EnemyEtis-30000610");
                break;
            }
            case 17830: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000591);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000611, EnemyEtis, "EnemyEtis-30000611");
                break;
            }
            case 17860: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000592);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000612, EnemyEtis, "EnemyEtis-30000612");
                break;
            }
            case 17890: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000593);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000613, EnemyEtis, "EnemyEtis-30000613");
                break;
            }
            case 17920: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000594);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000614, EnemyEtis, "EnemyEtis-30000614");
                break;
            }
            case 17950: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000595);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000615, EnemyEtis, "EnemyEtis-30000615");
                break;
            }
            case 17980: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000596);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000616, EnemyEtis, "EnemyEtis-30000616");
                break;
            }
            case 18010: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000597);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000617, EnemyEtis, "EnemyEtis-30000617");
                break;
            }
            case 18040: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000598);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000618, EnemyEtis, "EnemyEtis-30000618");
                break;
            }
            case 18070: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000599);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000619, EnemyEtis, "EnemyEtis-30000619");
                break;
            }
            case 18100: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000600);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000620, EnemyEtis, "EnemyEtis-30000620");
                break;
            }
            case 18130: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000601);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000621, EnemyEtis, "EnemyEtis-30000621");
                break;
            }
            case 18160: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000602);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000622, EnemyEtis, "EnemyEtis-30000622");
                break;
            }
            case 18190: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000603);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000623, EnemyEtis, "EnemyEtis-30000623");
                break;
            }
            case 18220: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000604);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000624, EnemyEtis, "EnemyEtis-30000624");
                break;
            }
            case 18250: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000605);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000625, EnemyEtis, "EnemyEtis-30000625");
                break;
            }
            case 18280: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000606);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000626, EnemyEtis, "EnemyEtis-30000626");
                break;
            }
            case 18310: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000607);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000627, EnemyEtis, "EnemyEtis-30000627");
                break;
            }
            case 18340: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000608);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000628, EnemyEtis, "EnemyEtis-30000628");
                break;
            }
            case 18370: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000609);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000629, EnemyEtis, "EnemyEtis-30000629");
                break;
            }
            case 18400: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000610);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000630, EnemyEtis, "EnemyEtis-30000630");
                break;
            }
            case 18430: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000611);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000631, EnemyEtis, "EnemyEtis-30000631");
                break;
            }
            case 18460: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000612);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000632, EnemyEtis, "EnemyEtis-30000632");
                break;
            }
            case 18490: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000613);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000633, EnemyEtis, "EnemyEtis-30000633");
                break;
            }
            case 18520: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000614);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000634, EnemyEtis, "EnemyEtis-30000634");
                break;
            }
            case 18550: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000615);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000635, EnemyEtis, "EnemyEtis-30000635");
                break;
            }
            case 18580: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000616);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000636, EnemyEtis, "EnemyEtis-30000636");
                break;
            }
            case 18610: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000617);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000637, EnemyEtis, "EnemyEtis-30000637");
                break;
            }
            case 18640: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000618);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000638, EnemyEtis, "EnemyEtis-30000638");
                break;
            }
            case 18670: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000619);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000639, EnemyEtis, "EnemyEtis-30000639");
                break;
            }
            case 18700: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000620);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000640, EnemyEtis, "EnemyEtis-30000640");
                break;
            }
            case 18730: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000621);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000641, EnemyEtis, "EnemyEtis-30000641");
                break;
            }
            case 18760: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000622);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000642, EnemyEtis, "EnemyEtis-30000642");
                break;
            }
            case 18790: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000623);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000643, EnemyEtis, "EnemyEtis-30000643");
                break;
            }
            case 18820: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000624);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000644, EnemyEtis, "EnemyEtis-30000644");
                break;
            }
            case 18850: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000625);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000645, EnemyEtis, "EnemyEtis-30000645");
                break;
            }
            case 18880: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000626);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000646, EnemyEtis, "EnemyEtis-30000646");
                break;
            }
            case 18910: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000627);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000647, EnemyEtis, "EnemyEtis-30000647");
                break;
            }
            case 18940: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000628);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000648, EnemyEtis, "EnemyEtis-30000648");
                break;
            }
            case 18970: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000629);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000649, EnemyEtis, "EnemyEtis-30000649");
                break;
            }
            case 19000: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000630);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000650, EnemyEtis, "EnemyEtis-30000650");
                break;
            }
            case 19030: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000631);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000651, EnemyEtis, "EnemyEtis-30000651");
                break;
            }
            case 19060: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000632);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000652, EnemyEtis, "EnemyEtis-30000652");
                break;
            }
            case 19090: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000633);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000653, EnemyEtis, "EnemyEtis-30000653");
                break;
            }
            case 19120: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000634);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000654, EnemyEtis, "EnemyEtis-30000654");
                break;
            }
            case 19150: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000635);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000655, EnemyEtis, "EnemyEtis-30000655");
                break;
            }
            case 19180: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000636);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000656, EnemyEtis, "EnemyEtis-30000656");
                break;
            }
            case 19210: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000637);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000657, EnemyEtis, "EnemyEtis-30000657");
                break;
            }
            case 19240: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000638);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000658, EnemyEtis, "EnemyEtis-30000658");
                break;
            }
            case 19270: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000639);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000659, EnemyEtis, "EnemyEtis-30000659");
                break;
            }
            case 19300: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000640);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000660, EnemyEtis, "EnemyEtis-30000660");
                break;
            }
            case 19330: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000641);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000661, EnemyEtis, "EnemyEtis-30000661");
                break;
            }
            case 19360: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000642);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000662, EnemyEtis, "EnemyEtis-30000662");
                break;
            }
            case 19390: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000643);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000663, EnemyEtis, "EnemyEtis-30000663");
                break;
            }
            case 19420: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000644);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000664, EnemyEtis, "EnemyEtis-30000664");
                break;
            }
            case 19450: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000645);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000665, EnemyEtis, "EnemyEtis-30000665");
                break;
            }
            case 19480: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000646);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000666, EnemyEtis, "EnemyEtis-30000666");
                break;
            }
            case 19510: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000647);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000667, EnemyEtis, "EnemyEtis-30000667");
                break;
            }
            case 19540: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000648);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000668, EnemyEtis, "EnemyEtis-30000668");
                break;
            }
            case 19570: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000649);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000669, EnemyEtis, "EnemyEtis-30000669");
                break;
            }
            case 19600: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000650);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000670, EnemyEtis, "EnemyEtis-30000670");
                break;
            }
            case 19630: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000651);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000671, EnemyEtis, "EnemyEtis-30000671");
                break;
            }
            case 19660: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000652);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000672, EnemyEtis, "EnemyEtis-30000672");
                break;
            }
            case 19690: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000653);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000673, EnemyEtis, "EnemyEtis-30000673");
                break;
            }
            case 19720: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000654);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000674, EnemyEtis, "EnemyEtis-30000674");
                break;
            }
            case 19750: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000655);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000675, EnemyEtis, "EnemyEtis-30000675");
                break;
            }
            case 19780: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000656);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000676, EnemyEtis, "EnemyEtis-30000676");
                break;
            }
            case 19810: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000657);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000677, EnemyEtis, "EnemyEtis-30000677");
                break;
            }
            case 19840: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000658);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000678, EnemyEtis, "EnemyEtis-30000678");
                break;
            }
            case 19870: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000659);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000679, EnemyEtis, "EnemyEtis-30000679");
                break;
            }
            case 19900: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000660);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000680, EnemyEtis, "EnemyEtis-30000680");
                break;
            }
            case 19930: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000661);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000681, EnemyEtis, "EnemyEtis-30000681");
                break;
            }
            case 19960: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000662);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000682, EnemyEtis, "EnemyEtis-30000682");
                break;
            }
            case 19990: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000663);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000683, EnemyEtis, "EnemyEtis-30000683");
                break;
            }
            case 20020: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000664);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000684, EnemyEtis, "EnemyEtis-30000684");
                break;
            }
            case 20050: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000665);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000685, EnemyEtis, "EnemyEtis-30000685");
                break;
            }
            case 20080: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000666);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000686, EnemyEtis, "EnemyEtis-30000686");
                break;
            }
            case 20110: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000667);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000687, EnemyEtis, "EnemyEtis-30000687");
                break;
            }
            case 20140: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000668);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000688, EnemyEtis, "EnemyEtis-30000688");
                break;
            }
            case 20170: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000669);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000689, EnemyEtis, "EnemyEtis-30000689");
                break;
            }
            case 20200: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000670);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000690, EnemyEtis, "EnemyEtis-30000690");
                break;
            }
            case 20230: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000671);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000691, EnemyEtis, "EnemyEtis-30000691");
                break;
            }
            case 20260: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000672);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000692, EnemyEtis, "EnemyEtis-30000692");
                break;
            }
            case 20290: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000673);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000693, EnemyEtis, "EnemyEtis-30000693");
                break;
            }
            case 20320: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000674);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000694, EnemyEtis, "EnemyEtis-30000694");
                break;
            }
            case 20350: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000675);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000695, EnemyEtis, "EnemyEtis-30000695");
                break;
            }
            case 20380: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000676);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000696, EnemyEtis, "EnemyEtis-30000696");
                break;
            }
            case 20410: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000677);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000697, EnemyEtis, "EnemyEtis-30000697");
                break;
            }
            case 20440: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000678);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000698, EnemyEtis, "EnemyEtis-30000698");
                break;
            }
            case 20470: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000679);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000699, EnemyEtis, "EnemyEtis-30000699");
                break;
            }
            case 20500: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000680);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000700, EnemyEtis, "EnemyEtis-30000700");
                break;
            }
            case 20530: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000681);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000701, EnemyEtis, "EnemyEtis-30000701");
                break;
            }
            case 20560: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000682);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000702, EnemyEtis, "EnemyEtis-30000702");
                break;
            }
            case 20590: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000683);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000703, EnemyEtis, "EnemyEtis-30000703");
                break;
            }
            case 20620: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000684);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000704, EnemyEtis, "EnemyEtis-30000704");
                break;
            }
            case 20650: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000685);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000705, EnemyEtis, "EnemyEtis-30000705");
                break;
            }
            case 20680: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000686);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000706, EnemyEtis, "EnemyEtis-30000706");
                break;
            }
            case 20710: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000687);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000707, EnemyEtis, "EnemyEtis-30000707");
                break;
            }
            case 20740: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000688);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000708, EnemyEtis, "EnemyEtis-30000708");
                break;
            }
            case 20770: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000689);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000709, EnemyEtis, "EnemyEtis-30000709");
                break;
            }
            case 20800: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000690);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000710, EnemyEtis, "EnemyEtis-30000710");
                break;
            }
            case 20830: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000691);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000711, EnemyEtis, "EnemyEtis-30000711");
                break;
            }
            case 20860: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000692);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000712, EnemyEtis, "EnemyEtis-30000712");
                break;
            }
            case 20890: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000693);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000713, EnemyEtis, "EnemyEtis-30000713");
                break;
            }
            case 20920: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000694);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000714, EnemyEtis, "EnemyEtis-30000714");
                break;
            }
            case 20950: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000695);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000715, EnemyEtis, "EnemyEtis-30000715");
                break;
            }
            case 20980: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000696);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000716, EnemyEtis, "EnemyEtis-30000716");
                break;
            }
            case 21010: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000697);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000717, EnemyEtis, "EnemyEtis-30000717");
                break;
            }
            case 21040: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000698);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000718, EnemyEtis, "EnemyEtis-30000718");
                break;
            }
            case 21070: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000699);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000719, EnemyEtis, "EnemyEtis-30000719");
                break;
            }
            case 21100: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000700);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000720, EnemyEtis, "EnemyEtis-30000720");
                break;
            }
            case 21130: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000701);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000721, EnemyEtis, "EnemyEtis-30000721");
                break;
            }
            case 21160: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000702);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000722, EnemyEtis, "EnemyEtis-30000722");
                break;
            }
            case 21190: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000703);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000723, EnemyEtis, "EnemyEtis-30000723");
                break;
            }
            case 21220: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000704);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000724, EnemyEtis, "EnemyEtis-30000724");
                break;
            }
            case 21250: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000705);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000725, EnemyEtis, "EnemyEtis-30000725");
                break;
            }
            case 21280: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000706);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000726, EnemyEtis, "EnemyEtis-30000726");
                break;
            }
            case 21310: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000707);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000727, EnemyEtis, "EnemyEtis-30000727");
                break;
            }
            case 21340: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000708);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000728, EnemyEtis, "EnemyEtis-30000728");
                break;
            }
            case 21370: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000709);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000729, EnemyEtis, "EnemyEtis-30000729");
                break;
            }
            case 21400: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000710);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000730, EnemyEtis, "EnemyEtis-30000730");
                break;
            }
            case 21430: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000711);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000731, EnemyEtis, "EnemyEtis-30000731");
                break;
            }
            case 21460: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000712);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000732, EnemyEtis, "EnemyEtis-30000732");
                break;
            }
            case 21490: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000713);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000733, EnemyEtis, "EnemyEtis-30000733");
                break;
            }
            case 21520: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000714);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000734, EnemyEtis, "EnemyEtis-30000734");
                break;
            }
            case 21550: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000715);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000735, EnemyEtis, "EnemyEtis-30000735");
                break;
            }
            case 21580: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000716);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000736, EnemyEtis, "EnemyEtis-30000736");
                break;
            }
            case 21610: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000717);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000737, EnemyEtis, "EnemyEtis-30000737");
                break;
            }
            case 21640: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000718);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000738, EnemyEtis, "EnemyEtis-30000738");
                break;
            }
            case 21670: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000719);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000739, EnemyEtis, "EnemyEtis-30000739");
                break;
            }
            case 21700: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000720);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000740, EnemyEtis, "EnemyEtis-30000740");
                break;
            }
            case 21730: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000721);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000741, EnemyEtis, "EnemyEtis-30000741");
                break;
            }
            case 21760: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000722);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000742, EnemyEtis, "EnemyEtis-30000742");
                break;
            }
            case 21790: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000723);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000743, EnemyEtis, "EnemyEtis-30000743");
                break;
            }
            case 21820: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000724);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000744, EnemyEtis, "EnemyEtis-30000744");
                break;
            }
            case 21850: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000725);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000745, EnemyEtis, "EnemyEtis-30000745");
                break;
            }
            case 21880: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000726);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000746, EnemyEtis, "EnemyEtis-30000746");
                break;
            }
            case 21910: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000727);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000747, EnemyEtis, "EnemyEtis-30000747");
                break;
            }
            case 21940: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000728);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000748, EnemyEtis, "EnemyEtis-30000748");
                break;
            }
            case 21970: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000729);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000749, EnemyEtis, "EnemyEtis-30000749");
                break;
            }
            case 22000: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000730);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000750, EnemyEtis, "EnemyEtis-30000750");
                break;
            }
            case 22030: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000731);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000751, EnemyEtis, "EnemyEtis-30000751");
                break;
            }
            case 22060: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000732);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000752, EnemyEtis, "EnemyEtis-30000752");
                break;
            }
            case 22090: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000733);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000753, EnemyEtis, "EnemyEtis-30000753");
                break;
            }
            case 22120: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000734);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000754, EnemyEtis, "EnemyEtis-30000754");
                break;
            }
            case 22150: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000735);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000755, EnemyEtis, "EnemyEtis-30000755");
                break;
            }
            case 22180: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000736);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000756, EnemyEtis, "EnemyEtis-30000756");
                break;
            }
            case 22210: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000737);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000757, EnemyEtis, "EnemyEtis-30000757");
                break;
            }
            case 22240: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000738);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000758, EnemyEtis, "EnemyEtis-30000758");
                break;
            }
            case 22270: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000739);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000759, EnemyEtis, "EnemyEtis-30000759");
                break;
            }
            case 22300: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000740);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000760, EnemyEtis, "EnemyEtis-30000760");
                break;
            }
            case 22330: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000741);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000761, EnemyEtis, "EnemyEtis-30000761");
                break;
            }
            case 22360: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000742);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000762, EnemyEtis, "EnemyEtis-30000762");
                break;
            }
            case 22390: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000743);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000763, EnemyEtis, "EnemyEtis-30000763");
                break;
            }
            case 22420: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000744);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000764, EnemyEtis, "EnemyEtis-30000764");
                break;
            }
            case 22450: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000745);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000765, EnemyEtis, "EnemyEtis-30000765");
                break;
            }
            case 22480: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000746);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000766, EnemyEtis, "EnemyEtis-30000766");
                break;
            }
            case 22510: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000747);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000767, EnemyEtis, "EnemyEtis-30000767");
                break;
            }
            case 22540: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000748);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000768, EnemyEtis, "EnemyEtis-30000768");
                break;
            }
            case 22570: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000749);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000769, EnemyEtis, "EnemyEtis-30000769");
                break;
            }
            case 22600: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000750);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000770, EnemyEtis, "EnemyEtis-30000770");
                break;
            }
            case 22630: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000751);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000771, EnemyEtis, "EnemyEtis-30000771");
                break;
            }
            case 22660: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000752);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000772, EnemyEtis, "EnemyEtis-30000772");
                break;
            }
            case 22690: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000753);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000773, EnemyEtis, "EnemyEtis-30000773");
                break;
            }
            case 22720: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000754);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000774, EnemyEtis, "EnemyEtis-30000774");
                break;
            }
            case 22750: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000755);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000775, EnemyEtis, "EnemyEtis-30000775");
                break;
            }
            case 22780: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000756);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000776, EnemyEtis, "EnemyEtis-30000776");
                break;
            }
            case 22810: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000757);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000777, EnemyEtis, "EnemyEtis-30000777");
                break;
            }
            case 22840: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000758);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000778, EnemyEtis, "EnemyEtis-30000778");
                break;
            }
            case 22870: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000759);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000779, EnemyEtis, "EnemyEtis-30000779");
                break;
            }
            case 22900: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000760);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000780, EnemyEtis, "EnemyEtis-30000780");
                break;
            }
            case 22930: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000761);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000781, EnemyEtis, "EnemyEtis-30000781");
                break;
            }
            case 22960: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000762);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000782, EnemyEtis, "EnemyEtis-30000782");
                break;
            }
            case 22990: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000763);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000783, EnemyEtis, "EnemyEtis-30000783");
                break;
            }
            case 23020: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000764);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000784, EnemyEtis, "EnemyEtis-30000784");
                break;
            }
            case 23050: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000765);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000785, EnemyEtis, "EnemyEtis-30000785");
                break;
            }
            case 23080: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000766);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000786, EnemyEtis, "EnemyEtis-30000786");
                break;
            }
            case 23110: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000767);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000787, EnemyEtis, "EnemyEtis-30000787");
                break;
            }
            case 23140: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000768);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000788, EnemyEtis, "EnemyEtis-30000788");
                break;
            }
            case 23170: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000769);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000789, EnemyEtis, "EnemyEtis-30000789");
                break;
            }
            case 23200: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000770);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000790, EnemyEtis, "EnemyEtis-30000790");
                break;
            }
            case 23230: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000771);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000791, EnemyEtis, "EnemyEtis-30000791");
                break;
            }
            case 23260: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000772);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000792, EnemyEtis, "EnemyEtis-30000792");
                break;
            }
            case 23290: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000773);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000793, EnemyEtis, "EnemyEtis-30000793");
                break;
            }
            case 23320: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000774);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000794, EnemyEtis, "EnemyEtis-30000794");
                break;
            }
            case 23350: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000775);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000795, EnemyEtis, "EnemyEtis-30000795");
                break;
            }
            case 23380: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000776);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000796, EnemyEtis, "EnemyEtis-30000796");
                break;
            }
            case 23410: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000777);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000797, EnemyEtis, "EnemyEtis-30000797");
                break;
            }
            case 23440: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000778);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000798, EnemyEtis, "EnemyEtis-30000798");
                break;
            }
            case 23470: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000779);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000799, EnemyEtis, "EnemyEtis-30000799");
                break;
            }
            case 23500: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000780);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000800, EnemyEtis, "EnemyEtis-30000800");
                break;
            }
            case 23530: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000781);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000801, EnemyEtis, "EnemyEtis-30000801");
                break;
            }
            case 23560: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000782);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000802, EnemyEtis, "EnemyEtis-30000802");
                break;
            }
            case 23590: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000783);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000803, EnemyEtis, "EnemyEtis-30000803");
                break;
            }
            case 23620: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000784);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000804, EnemyEtis, "EnemyEtis-30000804");
                break;
            }
            case 23650: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000785);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000805, EnemyEtis, "EnemyEtis-30000805");
                break;
            }
            case 23680: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000786);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000806, EnemyEtis, "EnemyEtis-30000806");
                break;
            }
            case 23710: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000787);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000807, EnemyEtis, "EnemyEtis-30000807");
                break;
            }
            case 23740: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000788);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000808, EnemyEtis, "EnemyEtis-30000808");
                break;
            }
            case 23770: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000789);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000809, EnemyEtis, "EnemyEtis-30000809");
                break;
            }
            case 23800: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000790);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000810, EnemyEtis, "EnemyEtis-30000810");
                break;
            }
            case 23830: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000791);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000811, EnemyEtis, "EnemyEtis-30000811");
                break;
            }
            case 23860: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000792);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000812, EnemyEtis, "EnemyEtis-30000812");
                break;
            }
            case 23890: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000793);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000813, EnemyEtis, "EnemyEtis-30000813");
                break;
            }
            case 23920: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000794);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000814, EnemyEtis, "EnemyEtis-30000814");
                break;
            }
            case 23950: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000795);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000815, EnemyEtis, "EnemyEtis-30000815");
                break;
            }
            case 23980: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000796);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000816, EnemyEtis, "EnemyEtis-30000816");
                break;
            }
            case 24010: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000797);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000817, EnemyEtis, "EnemyEtis-30000817");
                break;
            }
            case 24040: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000798);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000818, EnemyEtis, "EnemyEtis-30000818");
                break;
            }
            case 24070: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000799);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000819, EnemyEtis, "EnemyEtis-30000819");
                break;
            }
            case 24100: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000800);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000820, EnemyEtis, "EnemyEtis-30000820");
                break;
            }
            case 24130: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000801);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000821, EnemyEtis, "EnemyEtis-30000821");
                break;
            }
            case 24160: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000802);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000822, EnemyEtis, "EnemyEtis-30000822");
                break;
            }
            case 24190: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000803);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000823, EnemyEtis, "EnemyEtis-30000823");
                break;
            }
            case 24220: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000804);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000824, EnemyEtis, "EnemyEtis-30000824");
                break;
            }
            case 24250: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000805);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000825, EnemyEtis, "EnemyEtis-30000825");
                break;
            }
            case 24280: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000806);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000826, EnemyEtis, "EnemyEtis-30000826");
                break;
            }
            case 24310: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000807);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000827, EnemyEtis, "EnemyEtis-30000827");
                break;
            }
            case 24340: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000808);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000828, EnemyEtis, "EnemyEtis-30000828");
                break;
            }
            case 24370: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000809);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000829, EnemyEtis, "EnemyEtis-30000829");
                break;
            }
            case 24400: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000810);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000830, EnemyEtis, "EnemyEtis-30000830");
                break;
            }
            case 24430: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000811);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000831, EnemyEtis, "EnemyEtis-30000831");
                break;
            }
            case 24460: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000812);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000832, EnemyEtis, "EnemyEtis-30000832");
                break;
            }
            case 24490: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000813);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000833, EnemyEtis, "EnemyEtis-30000833");
                break;
            }
            case 24520: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000814);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000834, EnemyEtis, "EnemyEtis-30000834");
                break;
            }
            case 24550: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000815);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000835, EnemyEtis, "EnemyEtis-30000835");
                break;
            }
            case 24580: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000816);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000836, EnemyEtis, "EnemyEtis-30000836");
                break;
            }
            case 24610: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000817);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000837, EnemyEtis, "EnemyEtis-30000837");
                break;
            }
            case 24640: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000818);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000838, EnemyEtis, "EnemyEtis-30000838");
                break;
            }
            case 24670: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000819);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000839, EnemyEtis, "EnemyEtis-30000839");
                break;
            }
            case 24700: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000820);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000840, EnemyEtis, "EnemyEtis-30000840");
                break;
            }
            case 24730: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000821);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000841, EnemyEtis, "EnemyEtis-30000841");
                break;
            }
            case 24760: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000822);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000842, EnemyEtis, "EnemyEtis-30000842");
                break;
            }
            case 24790: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000823);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000843, EnemyEtis, "EnemyEtis-30000843");
                break;
            }
            case 24820: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000824);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000844, EnemyEtis, "EnemyEtis-30000844");
                break;
            }
            case 24850: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000825);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000845, EnemyEtis, "EnemyEtis-30000845");
                break;
            }
            case 24880: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000826);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000846, EnemyEtis, "EnemyEtis-30000846");
                break;
            }
            case 24910: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000827);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000847, EnemyEtis, "EnemyEtis-30000847");
                break;
            }
            case 24940: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000828);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000848, EnemyEtis, "EnemyEtis-30000848");
                break;
            }
            case 24970: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000829);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000849, EnemyEtis, "EnemyEtis-30000849");
                break;
            }
            case 25000: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000830);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000850, EnemyEtis, "EnemyEtis-30000850");
                break;
            }
            case 25030: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000831);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000851, EnemyEtis, "EnemyEtis-30000851");
                break;
            }
            case 25060: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000832);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000852, EnemyEtis, "EnemyEtis-30000852");
                break;
            }
            case 25090: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000833);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000853, EnemyEtis, "EnemyEtis-30000853");
                break;
            }
            case 25120: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000834);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000854, EnemyEtis, "EnemyEtis-30000854");
                break;
            }
            case 25150: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000835);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000855, EnemyEtis, "EnemyEtis-30000855");
                break;
            }
            case 25180: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000836);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000856, EnemyEtis, "EnemyEtis-30000856");
                break;
            }
            case 25210: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000837);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000857, EnemyEtis, "EnemyEtis-30000857");
                break;
            }
            case 25240: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000838);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000858, EnemyEtis, "EnemyEtis-30000858");
                break;
            }
            case 25270: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000839);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000859, EnemyEtis, "EnemyEtis-30000859");
                break;
            }
            case 25300: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000840);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000860, EnemyEtis, "EnemyEtis-30000860");
                break;
            }
            case 25330: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000841);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000861, EnemyEtis, "EnemyEtis-30000861");
                break;
            }
            case 25360: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000842);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000862, EnemyEtis, "EnemyEtis-30000862");
                break;
            }
            case 25390: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000843);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000863, EnemyEtis, "EnemyEtis-30000863");
                break;
            }
            case 25420: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000844);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000864, EnemyEtis, "EnemyEtis-30000864");
                break;
            }
            case 25450: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000845);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000865, EnemyEtis, "EnemyEtis-30000865");
                break;
            }
            case 25480: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000846);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000866, EnemyEtis, "EnemyEtis-30000866");
                break;
            }
            case 25510: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000847);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000867, EnemyEtis, "EnemyEtis-30000867");
                break;
            }
            case 25540: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000848);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000868, EnemyEtis, "EnemyEtis-30000868");
                break;
            }
            case 25570: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000849);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000869, EnemyEtis, "EnemyEtis-30000869");
                break;
            }
            case 25600: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000850);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000870, EnemyEtis, "EnemyEtis-30000870");
                break;
            }
            case 25630: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000851);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000871, EnemyEtis, "EnemyEtis-30000871");
                break;
            }
            case 25660: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000852);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000872, EnemyEtis, "EnemyEtis-30000872");
                break;
            }
            case 25690: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000853);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000873, EnemyEtis, "EnemyEtis-30000873");
                break;
            }
            case 25720: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000854);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000874, EnemyEtis, "EnemyEtis-30000874");
                break;
            }
            case 25750: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000855);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000875, EnemyEtis, "EnemyEtis-30000875");
                break;
            }
            case 25780: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000856);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000876, EnemyEtis, "EnemyEtis-30000876");
                break;
            }
            case 25810: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000857);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000877, EnemyEtis, "EnemyEtis-30000877");
                break;
            }
            case 25840: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000858);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000878, EnemyEtis, "EnemyEtis-30000878");
                break;
            }
            case 25870: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000859);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000879, EnemyEtis, "EnemyEtis-30000879");
                break;
            }
            case 25900: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000860);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000880, EnemyEtis, "EnemyEtis-30000880");
                break;
            }
            case 25930: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000861);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000881, EnemyEtis, "EnemyEtis-30000881");
                break;
            }
            case 25960: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000862);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000882, EnemyEtis, "EnemyEtis-30000882");
                break;
            }
            case 25990: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000863);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000883, EnemyEtis, "EnemyEtis-30000883");
                break;
            }
            case 26020: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000864);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000884, EnemyEtis, "EnemyEtis-30000884");
                break;
            }
            case 26050: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000865);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000885, EnemyEtis, "EnemyEtis-30000885");
                break;
            }
            case 26080: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000866);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000886, EnemyEtis, "EnemyEtis-30000886");
                break;
            }
            case 26110: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000867);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000887, EnemyEtis, "EnemyEtis-30000887");
                break;
            }
            case 26140: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000868);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000888, EnemyEtis, "EnemyEtis-30000888");
                break;
            }
            case 26170: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000869);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000889, EnemyEtis, "EnemyEtis-30000889");
                break;
            }
            case 26200: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000870);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000890, EnemyEtis, "EnemyEtis-30000890");
                break;
            }
            case 26230: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000871);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000891, EnemyEtis, "EnemyEtis-30000891");
                break;
            }
            case 26260: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000872);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000892, EnemyEtis, "EnemyEtis-30000892");
                break;
            }
            case 26290: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000873);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000893, EnemyEtis, "EnemyEtis-30000893");
                break;
            }
            case 26320: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000874);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000894, EnemyEtis, "EnemyEtis-30000894");
                break;
            }
            case 26350: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000875);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000895, EnemyEtis, "EnemyEtis-30000895");
                break;
            }
            case 26380: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000876);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000896, EnemyEtis, "EnemyEtis-30000896");
                break;
            }
            case 26410: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000877);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000897, EnemyEtis, "EnemyEtis-30000897");
                break;
            }
            case 26440: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000878);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000898, EnemyEtis, "EnemyEtis-30000898");
                break;
            }
            case 26470: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000879);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000899, EnemyEtis, "EnemyEtis-30000899");
                break;
            }
            case 26500: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000880);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000900, EnemyEtis, "EnemyEtis-30000900");
                break;
            }
            case 26530: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000881);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000901, EnemyEtis, "EnemyEtis-30000901");
                break;
            }
            case 26560: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000882);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000902, EnemyEtis, "EnemyEtis-30000902");
                break;
            }
            case 26590: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000883);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000903, EnemyEtis, "EnemyEtis-30000903");
                break;
            }
            case 26620: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000884);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000904, EnemyEtis, "EnemyEtis-30000904");
                break;
            }
            case 26650: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000885);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000905, EnemyEtis, "EnemyEtis-30000905");
                break;
            }
            case 26680: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000886);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000906, EnemyEtis, "EnemyEtis-30000906");
                break;
            }
            case 26710: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000887);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000907, EnemyEtis, "EnemyEtis-30000907");
                break;
            }
            case 26740: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000888);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000908, EnemyEtis, "EnemyEtis-30000908");
                break;
            }
            case 26770: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000889);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000909, EnemyEtis, "EnemyEtis-30000909");
                break;
            }
            case 26800: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000890);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000910, EnemyEtis, "EnemyEtis-30000910");
                break;
            }
            case 26830: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000891);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000911, EnemyEtis, "EnemyEtis-30000911");
                break;
            }
            case 26860: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000892);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000912, EnemyEtis, "EnemyEtis-30000912");
                break;
            }
            case 26890: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000893);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000913, EnemyEtis, "EnemyEtis-30000913");
                break;
            }
            case 26920: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000894);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000914, EnemyEtis, "EnemyEtis-30000914");
                break;
            }
            case 26950: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000895);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000915, EnemyEtis, "EnemyEtis-30000915");
                break;
            }
            case 26980: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000896);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000916, EnemyEtis, "EnemyEtis-30000916");
                break;
            }
            case 27010: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000897);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000917, EnemyEtis, "EnemyEtis-30000917");
                break;
            }
            case 27040: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000898);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000918, EnemyEtis, "EnemyEtis-30000918");
                break;
            }
            case 27070: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000899);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000919, EnemyEtis, "EnemyEtis-30000919");
                break;
            }
            case 27100: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000900);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000920, EnemyEtis, "EnemyEtis-30000920");
                break;
            }
            case 27130: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000901);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000921, EnemyEtis, "EnemyEtis-30000921");
                break;
            }
            case 27160: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000902);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000922, EnemyEtis, "EnemyEtis-30000922");
                break;
            }
            case 27190: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000903);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000923, EnemyEtis, "EnemyEtis-30000923");
                break;
            }
            case 27220: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000904);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000924, EnemyEtis, "EnemyEtis-30000924");
                break;
            }
            case 27250: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000905);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000925, EnemyEtis, "EnemyEtis-30000925");
                break;
            }
            case 27280: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000906);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000926, EnemyEtis, "EnemyEtis-30000926");
                break;
            }
            case 27310: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000907);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000927, EnemyEtis, "EnemyEtis-30000927");
                break;
            }
            case 27340: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000908);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000928, EnemyEtis, "EnemyEtis-30000928");
                break;
            }
            case 27370: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000909);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000929, EnemyEtis, "EnemyEtis-30000929");
                break;
            }
            case 27400: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000910);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000930, EnemyEtis, "EnemyEtis-30000930");
                break;
            }
            case 27430: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000911);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000931, EnemyEtis, "EnemyEtis-30000931");
                break;
            }
            case 27460: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000912);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000932, EnemyEtis, "EnemyEtis-30000932");
                break;
            }
            case 27490: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000913);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000933, EnemyEtis, "EnemyEtis-30000933");
                break;
            }
            case 27520: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000914);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000934, EnemyEtis, "EnemyEtis-30000934");
                break;
            }
            case 27550: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000915);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000935, EnemyEtis, "EnemyEtis-30000935");
                break;
            }
            case 27580: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000916);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000936, EnemyEtis, "EnemyEtis-30000936");
                break;
            }
            case 27610: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000917);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000937, EnemyEtis, "EnemyEtis-30000937");
                break;
            }
            case 27640: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000918);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000938, EnemyEtis, "EnemyEtis-30000938");
                break;
            }
            case 27670: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000919);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000939, EnemyEtis, "EnemyEtis-30000939");
                break;
            }
            case 27700: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000920);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000940, EnemyEtis, "EnemyEtis-30000940");
                break;
            }
            case 27730: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000921);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000941, EnemyEtis, "EnemyEtis-30000941");
                break;
            }
            case 27760: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000922);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000942, EnemyEtis, "EnemyEtis-30000942");
                break;
            }
            case 27790: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000923);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000943, EnemyEtis, "EnemyEtis-30000943");
                break;
            }
            case 27820: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000924);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000944, EnemyEtis, "EnemyEtis-30000944");
                break;
            }
            case 27850: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000925);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000945, EnemyEtis, "EnemyEtis-30000945");
                break;
            }
            case 27880: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000926);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000946, EnemyEtis, "EnemyEtis-30000946");
                break;
            }
            case 27910: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000927);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000947, EnemyEtis, "EnemyEtis-30000947");
                break;
            }
            case 27940: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000928);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000948, EnemyEtis, "EnemyEtis-30000948");
                break;
            }
            case 27970: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000929);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000949, EnemyEtis, "EnemyEtis-30000949");
                break;
            }
            case 28000: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000930);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000950, EnemyEtis, "EnemyEtis-30000950");
                break;
            }
            case 28030: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000931);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000951, EnemyEtis, "EnemyEtis-30000951");
                break;
            }
            case 28060: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000932);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000952, EnemyEtis, "EnemyEtis-30000952");
                break;
            }
            case 28090: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000933);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000953, EnemyEtis, "EnemyEtis-30000953");
                break;
            }
            case 28120: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000934);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000954, EnemyEtis, "EnemyEtis-30000954");
                break;
            }
            case 28150: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000935);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000955, EnemyEtis, "EnemyEtis-30000955");
                break;
            }
            case 28180: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000936);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000956, EnemyEtis, "EnemyEtis-30000956");
                break;
            }
            case 28210: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000937);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000957, EnemyEtis, "EnemyEtis-30000957");
                break;
            }
            case 28240: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000938);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000958, EnemyEtis, "EnemyEtis-30000958");
                break;
            }
            case 28270: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000939);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000959, EnemyEtis, "EnemyEtis-30000959");
                break;
            }
            case 28300: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000940);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000960, EnemyEtis, "EnemyEtis-30000960");
                break;
            }
            case 28330: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000941);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000961, EnemyEtis, "EnemyEtis-30000961");
                break;
            }
            case 28360: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000942);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000962, EnemyEtis, "EnemyEtis-30000962");
                break;
            }
            case 28390: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000943);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000963, EnemyEtis, "EnemyEtis-30000963");
                break;
            }
            case 28420: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000944);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000964, EnemyEtis, "EnemyEtis-30000964");
                break;
            }
            case 28450: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000945);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000965, EnemyEtis, "EnemyEtis-30000965");
                break;
            }
            case 28480: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000946);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000966, EnemyEtis, "EnemyEtis-30000966");
                break;
            }
            case 28510: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000947);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000967, EnemyEtis, "EnemyEtis-30000967");
                break;
            }
            case 28540: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000948);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000968, EnemyEtis, "EnemyEtis-30000968");
                break;
            }
            case 28570: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000949);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000969, EnemyEtis, "EnemyEtis-30000969");
                break;
            }
            case 28600: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000950);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000970, EnemyEtis, "EnemyEtis-30000970");
                break;
            }
            case 28630: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000951);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000971, EnemyEtis, "EnemyEtis-30000971");
                break;
            }
            case 28660: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000952);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000972, EnemyEtis, "EnemyEtis-30000972");
                break;
            }
            case 28690: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000953);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000973, EnemyEtis, "EnemyEtis-30000973");
                break;
            }
            case 28720: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000954);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000974, EnemyEtis, "EnemyEtis-30000974");
                break;
            }
            case 28750: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000955);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000975, EnemyEtis, "EnemyEtis-30000975");
                break;
            }
            case 28780: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000956);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000976, EnemyEtis, "EnemyEtis-30000976");
                break;
            }
            case 28810: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000957);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000977, EnemyEtis, "EnemyEtis-30000977");
                break;
            }
            case 28840: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000958);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000978, EnemyEtis, "EnemyEtis-30000978");
                break;
            }
            case 28870: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000959);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000979, EnemyEtis, "EnemyEtis-30000979");
                break;
            }
            case 28900: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000960);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000980, EnemyEtis, "EnemyEtis-30000980");
                break;
            }
            case 28930: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000961);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000981, EnemyEtis, "EnemyEtis-30000981");
                break;
            }
            case 28960: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000962);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000982, EnemyEtis, "EnemyEtis-30000982");
                break;
            }
            case 28990: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000963);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000983, EnemyEtis, "EnemyEtis-30000983");
                break;
            }
            case 29020: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000964);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000984, EnemyEtis, "EnemyEtis-30000984");
                break;
            }
            case 29050: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000965);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000985, EnemyEtis, "EnemyEtis-30000985");
                break;
            }
            case 29080: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000966);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000986, EnemyEtis, "EnemyEtis-30000986");
                break;
            }
            case 29110: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000967);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000987, EnemyEtis, "EnemyEtis-30000987");
                break;
            }
            case 29140: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000968);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000988, EnemyEtis, "EnemyEtis-30000988");
                break;
            }
            case 29170: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000969);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000989, EnemyEtis, "EnemyEtis-30000989");
                break;
            }
            case 29200: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000970);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000990, EnemyEtis, "EnemyEtis-30000990");
                break;
            }
            case 29230: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000971);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000991, EnemyEtis, "EnemyEtis-30000991");
                break;
            }
            case 29260: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000972);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000992, EnemyEtis, "EnemyEtis-30000992");
                break;
            }
            case 29290: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000973);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000993, EnemyEtis, "EnemyEtis-30000993");
                break;
            }
            case 29320: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000974);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000994, EnemyEtis, "EnemyEtis-30000994");
                break;
            }
            case 29350: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000975);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000995, EnemyEtis, "EnemyEtis-30000995");
                break;
            }
            case 29380: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000976);
                bringSceneMediator()->addSubGroup(pEtis);
                requestActor(30000996, EnemyEtis, "EnemyEtis-30000996");
                break;
            }
            case 29410: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000977);
                bringSceneMediator()->addSubGroup(pEtis);
                break;
            }
            case 29440: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000978);
                bringSceneMediator()->addSubGroup(pEtis);
                break;
            }
            case 29470: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000979);
                bringSceneMediator()->addSubGroup(pEtis);
                break;
            }
            case 29500: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000980);
                bringSceneMediator()->addSubGroup(pEtis);
                break;
            }
            case 29530: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000981);
                bringSceneMediator()->addSubGroup(pEtis);
                break;
            }
            case 29560: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000982);
                bringSceneMediator()->addSubGroup(pEtis);
                break;
            }
            case 29590: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000983);
                bringSceneMediator()->addSubGroup(pEtis);
                break;
            }
            case 29620: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000984);
                bringSceneMediator()->addSubGroup(pEtis);
                break;
            }
            case 29650: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000985);
                bringSceneMediator()->addSubGroup(pEtis);
                break;
            }
            case 29680: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000986);
                bringSceneMediator()->addSubGroup(pEtis);
                break;
            }
            case 29710: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000987);
                bringSceneMediator()->addSubGroup(pEtis);
                break;
            }
            case 29740: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000988);
                bringSceneMediator()->addSubGroup(pEtis);
                break;
            }
            case 29770: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000989);
                bringSceneMediator()->addSubGroup(pEtis);
                break;
            }
            case 29800: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000990);
                bringSceneMediator()->addSubGroup(pEtis);
                break;
            }
            case 29830: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000991);
                bringSceneMediator()->addSubGroup(pEtis);
                break;
            }
            case 29860: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000992);
                bringSceneMediator()->addSubGroup(pEtis);
                break;
            }
            case 29890: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000993);
                bringSceneMediator()->addSubGroup(pEtis);
                break;
            }
            case 29920: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000994);
                bringSceneMediator()->addSubGroup(pEtis);
                break;
            }
            case 29950: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000995);
                bringSceneMediator()->addSubGroup(pEtis);
                break;
            }
            case 29980: {
                EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000996);
                bringSceneMediator()->addSubGroup(pEtis);
                break;
            }
            default :
                break;
        }
        _cnt_event = (_cnt_event < 1019-1 ? _cnt_event+1 : _cnt_event);
    }
    // gen02 end

}

StageDebugPart02::~StageDebugPart02() {

}
