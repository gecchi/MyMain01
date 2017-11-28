#include "Stage01_02.h"

#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/dxcore/sound/GgafDxBgmConductor.h"
#include "jp/ggaf/lib/scene/FormationTableScene.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "../Stage01PartController.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld/StageController/Stage/StagePartController.h"
#include "jp/ggaf/dxcore/manager/GgafDxBgmConnection.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Stage01_02::Stage01_02(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "Stage01_02";
    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
    frame f[] = {1,10,40,70,100,130,160,190,220,250,280,310,340,370,400,430,460,490,520,550,580,610,640,670,700,730,760,790,820,850,880,910,940,970,1000,1030,1060,1090,1120,1150,1180,1210,1240,1270,1300,1330,1360,1390,1420,1450,1480,1510,1540,1570,1600,1630,1660,1690,1700,1720,1750,1780,1810,1840,1870,1900,1930,1960,1990,2020,2050,2080,2100,2110,2140,2170,2200,2230,2260,2290,2300,2320,2350,2380,2400,2410,2440,2470,2500,2530,2560,2590,2620,2650,2680,2700,2710,2740,2770,2800,2830,2860,2890,2920,2950,2980,3000,3010,3040,3070,3100,3130,3160,3190,3220,3250,3280,3310,3340,3370,3400,3430,3460,3490,3520,3550,3580,3610,3640,3670,3700,3730,3760,3790,3820,3850,3880,3910,3940,3970,4000,4030,4060,4090,4120,4150,4180,4210,4240,4270,4300,4330,4360,4390,4400,4420,4450,4480,4510,4540,4570,4600,4630,4660,4690,4720,4750,4780,4810,4840,4870,4900,4930,4960,4990,5000,5020,5050,5080,5110,5140,5170,5200,5230,5260,5290,5320,5350,5380,5400,5410,5440,5470,5500,5530,5560,5590,5620,5650,5680,5710,5740,5770,5800,5830,5860,5890,5920,5950,5980,6000,6010,6040,6070,6100,6130,6160,6190,6220,6250,6280,6310,6340,6370,6400,6430,6460,6490,6520,6550,6580,6610,6640,6670,6700,6730,6760,6790,6820,6850,6880,6910,6940,6970,7000,7030,7060,7090,7120,7150,7180,7210,7240,7270,7300,7330,7360,7390,7400,7420,7450,7480,7510,7540,7570,7600,7630,7660,7690,7720,7750,7780,7810,7840,7870,7900,7930,7960,7990,8000,8020,8050,8080,8110,8140,8170,8200,8230,8260,8290,8320,8350,8380,8400,8410,8440,8470,8500,8530,8560,8590,8600,8620,8650,8680,8710,8740,8770,8800,8830,8860,8890,8900,8920,8950,8980,9000,9010,9040,9070,9100,9130,9160,9190,9200,9220,9250,9280,9310,9340,9370,9400,9430,9460,9490,9500,9520,9550,9580,9610,9640,9670,9700,9730,9760,9790,9820,9850,9880,9910,9940,9970,10000,10030,10060,10090,10120,10150,10180,10210,10240,10270,10300,10330,10360,10390,10420,10450,10480,10510,10540,10570,10600,10630,10660,10690,10720,10750,10780,10810,10840,10870,10900,10930,10960,10990,11020,11050,11080,11110,11140,11170,11200,11230,11260,11290,11320,11350,11380,11410,11440,11470,11500,11530,11560,11590,11620,11650,11680,11710,11740,11770,11800,11830,11860,11890,11920,11950,11980,12010,12040,12070,12100,12130,12160,12190,12220,12250,12280,12310,12340,12370,12400,12430,12460,12490,12520,12550,12580,12610,12640,12670,12700,12730,12760,12790,12820,12850,12880,12910,12940,12970,13000,13030,13060,13090,13120,13150,13180,13210,13240,13270,13300,13330,13360,13390,13420,13450,13480,13510,13540,13570,13600,13630,13660,13690,13720,13750,13780,13810,13840,13870,13900,13930,13960,13990,14020,14050,14080,14110,14140,14170,14200,14230,14260,14290,14320,14350,14380,14410,14440,14470,14500,14530,14560,14590,14620,14650,14680,14710,14740,14770,14800,14830,14860,14890,14920,14950,14980,15010,15040,15070,15100,15130,15160,15190,15220,15250,15280,15310,15340,15370,15400,15430,15460,15490,15520,15550,15580,15610,15640,15670,15700,15730,15760,15790,15820,15850,15880,15910,15940,15970,16000,16030,16060,16090,16120,16150,16180,16210,16240,16270,16300,16330,16360,16390,16420,16450,16480,16510,16540,16570,16600,16630,16660,16690,16720,16750,16780,16810,16840,16870,16900,16930,16960,16990,17020,17050,17080,17110,17140,17170,17200,17230,17260,17290,17320,17350,17380,17410,17440,17470,17500,17530,17560,17590,17620,17650,17680,17710,17740,17770,17800,17830,17860,17890,17920,17950,17980,18010,18040,18070,18100,18130,18160,18190,18220,18250,18280,18310,18340,18370,18400,18430,18460,18490,18520,18550,18580,18610,18640,18670,18700,18730,18760,18790,18820,18850,18880,18910,18940,18970,19000,19030,19060,19090,19120,19150,19180,19210,19240,19270,19300,19330,19360,19390,19420,19450,19480,19510,19540,19570,19600,19630,19660,19690,19720,19750,19780,19810,19840,19870,19900,19930,19960,19990,20020,20050,20080,20110,20140,20170,20200,20230,20260,20290,20320,20350,20380,20410,20440,20470,20500,20530,20560,20590,20620,20650,20680,20710,20740,20770,20800,20830,20860,20890,20920,20950,20980,21010,21040,21070,21100,21130,21160,21190,21220,21250,21280,21310,21340,21370,21400,21430,21460,21490,21520,21550,21580,21610,21640,21670,21700,21730,21760,21790,21820,21850,21880,21910,21940,21970,22000,22030,22060,22090,22120,22150,22180,22210,22240,22270,22300,22330,22360,22390,22420,22450,22480,22510,22540,22570,22600,22630,22660,22690,22720,22750,22780,22810,22840,22870,22900,22930,22960,22990,23020,23050,23080,23110,23140,23170,23200,23230,23260,23290,23320,23350,23380,23410,23440,23470,23500,23530,23560,23590,23620,23650,23680,23710,23740,23770,23800,23830,23860,23890,23920,23950,23980,24010,24040,24070,24100,24130,24160,24190,24220,24250,24280,24310,24340,24370,24400,24430,24460,24490,24520,24550,24580,24610,24640,24670,24700,24730,24760,24790,24820,24850,24880,24910,24940,24970,25000,25030,25060,25090,25120,25150,25180,25210,25240,25270,25300,25330,25360,25390,25420,25450,25480,25510,25540,25570,25600,25630,25660,25690,25720,25750,25780,25810,25840,25870,25900,25930,25960,25990,26020,26050,26080,26110,26140,26170,26200,26230,26260,26290,26320,26350,26380,26410,26440,26470,26500,26530,26560,26590,26620,26650,26680,26710,26740,26770,26800,26830,26860,26890,26920,26950,26980,27010,27040,27070,27100,27130,27160,27190,27220,27250,27280,27310,27340,27370,27400,27430,27460,27490,27520,27550,27580,27610,27640,27670,27700,27730,27760,27790,27820,27850,27880,27910,27940,27970,28000,28030,28060,28090,28120,28150,28180,28210,28240,28270,28300,28330,28360,28390,28420,28450,28480,28510,28540,28570,28600,28630,28660,28690,28720,28750,28780,28810,28840,28870,28900,28930,28960,28990,29020,29050,29080,29110,29140,29170,29200,29230,29260,29290,29320,29350,29380,29410,29440,29470,29500,29530,29560,29590,29620,29650,29680,29710,29740,29770,29800,29830,29860,29890,29920,29950,29980};
    _paFrame_NextEvent = new frame[1019];
    memcpy(_paFrame_NextEvent, f, sizeof(f));
    _event_num = 1019;
    orderActorToFactory(30000000, EnemyEtis, "EnemyEtis-30000000");
    orderActorToFactory(30000001, EnemyEtis, "EnemyEtis-30000001");
    orderActorToFactory(30000002, EnemyEtis, "EnemyEtis-30000002");
    orderActorToFactory(30000003, EnemyEtis, "EnemyEtis-30000003");
    orderActorToFactory(30000004, EnemyEtis, "EnemyEtis-30000004");
    orderActorToFactory(30000005, EnemyEtis, "EnemyEtis-30000005");
    orderActorToFactory(30000006, EnemyEtis, "EnemyEtis-30000006");
    orderActorToFactory(30000007, EnemyEtis, "EnemyEtis-30000007");
    orderActorToFactory(30000008, EnemyEtis, "EnemyEtis-30000008");
    orderActorToFactory(30000009, EnemyEtis, "EnemyEtis-30000009");
    orderActorToFactory(30000010, EnemyEtis, "EnemyEtis-30000010");
    orderActorToFactory(30000011, EnemyEtis, "EnemyEtis-30000011");
    orderActorToFactory(30000012, EnemyEtis, "EnemyEtis-30000012");
    orderActorToFactory(30000013, EnemyEtis, "EnemyEtis-30000013");
    orderActorToFactory(30000014, EnemyEtis, "EnemyEtis-30000014");
    orderActorToFactory(30000015, EnemyEtis, "EnemyEtis-30000015");
    orderActorToFactory(30000016, EnemyEtis, "EnemyEtis-30000016");
    // gen01 end

    getConductor()->ready(0, "OGG_BGM_01_02");
}

void Stage01_02::initialize() {

}

void Stage01_02::processBehavior() {
    // 以下の gen02 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen02 start
    if (getBehaveingFrame() == _paFrame_NextEvent[_cnt_event]) {
        switch (getBehaveingFrame()) {
            case 1: {
                break;
            }
            case 10: {
                orderActorToFactory(30000017, EnemyEtis, "EnemyEtis-30000017");
                break;
            }
            case 40: {
                orderActorToFactory(30000018, EnemyEtis, "EnemyEtis-30000018");
                break;
            }
            case 70: {
                orderActorToFactory(30000019, EnemyEtis, "EnemyEtis-30000019");
                break;
            }
            case 100: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000000);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000020, EnemyEtis, "EnemyEtis-30000020");
                break;
            }
            case 130: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000001);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000021, EnemyEtis, "EnemyEtis-30000021");
                break;
            }
            case 160: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000002);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000022, EnemyEtis, "EnemyEtis-30000022");
                break;
            }
            case 190: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000003);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000023, EnemyEtis, "EnemyEtis-30000023");
                break;
            }
            case 220: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000004);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000024, EnemyEtis, "EnemyEtis-30000024");
                break;
            }
            case 250: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000005);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000025, EnemyEtis, "EnemyEtis-30000025");
                break;
            }
            case 280: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000006);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000026, EnemyEtis, "EnemyEtis-30000026");
                break;
            }
            case 310: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000007);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000027, EnemyEtis, "EnemyEtis-30000027");
                break;
            }
            case 340: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000008);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000028, EnemyEtis, "EnemyEtis-30000028");
                break;
            }
            case 370: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000009);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000029, EnemyEtis, "EnemyEtis-30000029");
                break;
            }
            case 400: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000010);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000030, EnemyEtis, "EnemyEtis-30000030");
                orderActorToFactory(30000997, VarietyRatislavia001, "VarietyRatislavia001-30000997");
                orderActorToFactory(30001018, FormationHalia, "FormationHalia-30001018");
                orderActorToFactory(30001029, FormationEbe001, "FormationEbe001-30001029");
                break;
            }
            case 430: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000011);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000031, EnemyEtis, "EnemyEtis-30000031");
                break;
            }
            case 460: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000012);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000032, EnemyEtis, "EnemyEtis-30000032");
                break;
            }
            case 490: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000013);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000033, EnemyEtis, "EnemyEtis-30000033");
                break;
            }
            case 520: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000014);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000034, EnemyEtis, "EnemyEtis-30000034");
                break;
            }
            case 550: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000015);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000035, EnemyEtis, "EnemyEtis-30000035");
                break;
            }
            case 580: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000016);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000036, EnemyEtis, "EnemyEtis-30000036");
                break;
            }
            case 610: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000017);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000037, EnemyEtis, "EnemyEtis-30000037");
                break;
            }
            case 640: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000018);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000038, EnemyEtis, "EnemyEtis-30000038");
                break;
            }
            case 670: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000019);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000039, EnemyEtis, "EnemyEtis-30000039");
                break;
            }
            case 700: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000020);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000040, EnemyEtis, "EnemyEtis-30000040");
                break;
            }
            case 730: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000021);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000041, EnemyEtis, "EnemyEtis-30000041");
                break;
            }
            case 760: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000022);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000042, EnemyEtis, "EnemyEtis-30000042");
                break;
            }
            case 790: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000023);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000043, EnemyEtis, "EnemyEtis-30000043");
                break;
            }
            case 820: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000024);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000044, EnemyEtis, "EnemyEtis-30000044");
                break;
            }
            case 850: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000025);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000045, EnemyEtis, "EnemyEtis-30000045");
                break;
            }
            case 880: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000026);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000046, EnemyEtis, "EnemyEtis-30000046");
                break;
            }
            case 910: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000027);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000047, EnemyEtis, "EnemyEtis-30000047");
                break;
            }
            case 940: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000028);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000048, EnemyEtis, "EnemyEtis-30000048");
                break;
            }
            case 970: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000029);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000049, EnemyEtis, "EnemyEtis-30000049");
                break;
            }
            case 1000: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000030);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000050, EnemyEtis, "EnemyEtis-30000050");
                VarietyRatislavia001* pRatislavia = (VarietyRatislavia001*)obtainActorFromFactory(30000997);
                bringDirector()->addSubGroup(pRatislavia);
                FormationHalia* pF = (FormationHalia*)obtainActorFromFactory(30001018);
                bringDirector()->addSubGroup(pF);
                FormationEbe001* pF1 = (FormationEbe001*)obtainActorFromFactory(30001029);
                bringDirector()->addSubGroup(pF1);
                break;
            }
            case 1030: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000031);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000051, EnemyEtis, "EnemyEtis-30000051");
                break;
            }
            case 1060: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000032);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000052, EnemyEtis, "EnemyEtis-30000052");
                break;
            }
            case 1090: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000033);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000053, EnemyEtis, "EnemyEtis-30000053");
                break;
            }
            case 1120: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000034);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000054, EnemyEtis, "EnemyEtis-30000054");
                break;
            }
            case 1150: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000035);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000055, EnemyEtis, "EnemyEtis-30000055");
                break;
            }
            case 1180: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000036);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000056, EnemyEtis, "EnemyEtis-30000056");
                break;
            }
            case 1210: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000037);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000057, EnemyEtis, "EnemyEtis-30000057");
                break;
            }
            case 1240: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000038);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000058, EnemyEtis, "EnemyEtis-30000058");
                break;
            }
            case 1270: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000039);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000059, EnemyEtis, "EnemyEtis-30000059");
                break;
            }
            case 1300: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000040);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000060, EnemyEtis, "EnemyEtis-30000060");
                break;
            }
            case 1330: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000041);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000061, EnemyEtis, "EnemyEtis-30000061");
                break;
            }
            case 1360: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000042);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000062, EnemyEtis, "EnemyEtis-30000062");
                break;
            }
            case 1390: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000043);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000063, EnemyEtis, "EnemyEtis-30000063");
                break;
            }
            case 1420: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000044);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000064, EnemyEtis, "EnemyEtis-30000064");
                break;
            }
            case 1450: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000045);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000065, EnemyEtis, "EnemyEtis-30000065");
                break;
            }
            case 1480: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000046);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000066, EnemyEtis, "EnemyEtis-30000066");
                break;
            }
            case 1510: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000047);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000067, EnemyEtis, "EnemyEtis-30000067");
                break;
            }
            case 1540: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000048);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000068, EnemyEtis, "EnemyEtis-30000068");
                break;
            }
            case 1570: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000049);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000069, EnemyEtis, "EnemyEtis-30000069");
                break;
            }
            case 1600: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000050);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000070, EnemyEtis, "EnemyEtis-30000070");
                break;
            }
            case 1630: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000051);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000071, EnemyEtis, "EnemyEtis-30000071");
                break;
            }
            case 1660: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000052);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000072, EnemyEtis, "EnemyEtis-30000072");
                break;
            }
            case 1690: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000053);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000073, EnemyEtis, "EnemyEtis-30000073");
                break;
            }
            case 1700: {
                orderActorToFactory(30000998, EnemyStraea, "EnemyStraea-30000998");
                break;
            }
            case 1720: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000054);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000074, EnemyEtis, "EnemyEtis-30000074");
                break;
            }
            case 1750: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000055);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000075, EnemyEtis, "EnemyEtis-30000075");
                break;
            }
            case 1780: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000056);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000076, EnemyEtis, "EnemyEtis-30000076");
                break;
            }
            case 1810: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000057);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000077, EnemyEtis, "EnemyEtis-30000077");
                break;
            }
            case 1840: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000058);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000078, EnemyEtis, "EnemyEtis-30000078");
                break;
            }
            case 1870: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000059);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000079, EnemyEtis, "EnemyEtis-30000079");
                break;
            }
            case 1900: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000060);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000080, EnemyEtis, "EnemyEtis-30000080");
                orderActorToFactory(30000999, FormationEmilia, "FormationEmilia-30000999");
                break;
            }
            case 1930: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000061);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000081, EnemyEtis, "EnemyEtis-30000081");
                break;
            }
            case 1960: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000062);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000082, EnemyEtis, "EnemyEtis-30000082");
                break;
            }
            case 1990: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000063);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000083, EnemyEtis, "EnemyEtis-30000083");
                break;
            }
            case 2020: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000064);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000084, EnemyEtis, "EnemyEtis-30000084");
                break;
            }
            case 2050: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000065);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000085, EnemyEtis, "EnemyEtis-30000085");
                break;
            }
            case 2080: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000066);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000086, EnemyEtis, "EnemyEtis-30000086");
                break;
            }
            case 2100: {
                orderActorToFactory(30001001, FormationAllas001a, "FormationAllas001a-30001001");
                orderActorToFactory(30001002, FormationAllas001b, "FormationAllas001b-30001002");
                orderActorToFactory(30001003, FormationAllas001c, "FormationAllas001c-30001003");
                orderActorToFactory(30001004, FormationAllas001d, "FormationAllas001d-30001004");
                orderActorToFactory(30001005, FormationAllas001a, "FormationAllas001a-30001005");
                orderActorToFactory(30001006, FormationAllas001d, "FormationAllas001d-30001006");
                orderActorToFactory(30001007, FormationAllas001b, "FormationAllas001b-30001007");
                orderActorToFactory(30001008, FormationAllas001c, "FormationAllas001c-30001008");
                orderActorToFactory(30001009, FormationAllas001a, "FormationAllas001a-30001009");
                orderActorToFactory(30001010, FormationAllas001d, "FormationAllas001d-30001010");
                orderActorToFactory(30001011, FormationAllas001b, "FormationAllas001b-30001011");
                orderActorToFactory(30001012, FormationAllas001c, "FormationAllas001c-30001012");
                break;
            }
            case 2110: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000067);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000087, EnemyEtis, "EnemyEtis-30000087");
                break;
            }
            case 2140: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000068);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000088, EnemyEtis, "EnemyEtis-30000088");
                break;
            }
            case 2170: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000069);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000089, EnemyEtis, "EnemyEtis-30000089");
                break;
            }
            case 2200: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000070);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000090, EnemyEtis, "EnemyEtis-30000090");
                break;
            }
            case 2230: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000071);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000091, EnemyEtis, "EnemyEtis-30000091");
                break;
            }
            case 2260: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000072);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000092, EnemyEtis, "EnemyEtis-30000092");
                break;
            }
            case 2290: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000073);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000093, EnemyEtis, "EnemyEtis-30000093");
                break;
            }
            case 2300: {
                EnemyStraea* pStraea2 = (EnemyStraea*)obtainActorFromFactory(30000998);
                bringDirector()->addSubGroup(pStraea2);
                pStraea2->_z = 1800000;
                pStraea2->_y = -100000;
                break;
            }
            case 2320: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000074);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000094, EnemyEtis, "EnemyEtis-30000094");
                break;
            }
            case 2350: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000075);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000095, EnemyEtis, "EnemyEtis-30000095");
                break;
            }
            case 2380: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000076);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000096, EnemyEtis, "EnemyEtis-30000096");
                break;
            }
            case 2400: {
                orderActorToFactory(30001013, FormationGeria001, "FormationGeria001-30001013");
                break;
            }
            case 2410: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000077);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000097, EnemyEtis, "EnemyEtis-30000097");
                break;
            }
            case 2440: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000078);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000098, EnemyEtis, "EnemyEtis-30000098");
                break;
            }
            case 2470: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000079);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000099, EnemyEtis, "EnemyEtis-30000099");
                break;
            }
            case 2500: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000080);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000100, EnemyEtis, "EnemyEtis-30000100");
                FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(30000999);
                bringDirector()->addSubGroup(pFormationEmilia);
                break;
            }
            case 2530: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000081);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000101, EnemyEtis, "EnemyEtis-30000101");
                break;
            }
            case 2560: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000082);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000102, EnemyEtis, "EnemyEtis-30000102");
                break;
            }
            case 2590: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000083);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000103, EnemyEtis, "EnemyEtis-30000103");
                break;
            }
            case 2620: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000084);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000104, EnemyEtis, "EnemyEtis-30000104");
                break;
            }
            case 2650: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000085);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000105, EnemyEtis, "EnemyEtis-30000105");
                break;
            }
            case 2680: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000086);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000106, EnemyEtis, "EnemyEtis-30000106");
                break;
            }
            case 2700: {
                {
                FormationTableScene* ta = NEW FormationTableScene("FormationTableScene-2");
                ta->setMaxPerformFrame(2500);
                addSubLast(ta);
                ta->addToTable(((FormationAllas001a*)obtainActorFromFactory(30001001)), 400);
                ta->addToTable(((FormationAllas001b*)obtainActorFromFactory(30001002)), 400);
                ta->addToTable(((FormationAllas001c*)obtainActorFromFactory(30001003)), 400);
                ta->addToTable(((FormationAllas001d*)obtainActorFromFactory(30001004)), 400);
                ta->addToTable(((FormationAllas001a*)obtainActorFromFactory(30001005)), 1);
                ta->addToTable(((FormationAllas001d*)obtainActorFromFactory(30001006)), 400);
                ta->addToTable(((FormationAllas001b*)obtainActorFromFactory(30001007)), 1);
                ta->addToTable(((FormationAllas001c*)obtainActorFromFactory(30001008)), 400);
                ta->addToTable(((FormationAllas001a*)obtainActorFromFactory(30001009)), 1);
                ta->addToTable(((FormationAllas001d*)obtainActorFromFactory(30001010)), 1);
                ta->addToTable(((FormationAllas001b*)obtainActorFromFactory(30001011)), 1);
                ta->addToTable(((FormationAllas001c*)obtainActorFromFactory(30001012)), 400);
                }
                break;
            }
            case 2710: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000087);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000107, EnemyEtis, "EnemyEtis-30000107");
                break;
            }
            case 2740: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000088);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000108, EnemyEtis, "EnemyEtis-30000108");
                break;
            }
            case 2770: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000089);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000109, EnemyEtis, "EnemyEtis-30000109");
                break;
            }
            case 2800: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000090);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000110, EnemyEtis, "EnemyEtis-30000110");
                break;
            }
            case 2830: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000091);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000111, EnemyEtis, "EnemyEtis-30000111");
                break;
            }
            case 2860: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000092);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000112, EnemyEtis, "EnemyEtis-30000112");
                break;
            }
            case 2890: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000093);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000113, EnemyEtis, "EnemyEtis-30000113");
                break;
            }
            case 2920: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000094);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000114, EnemyEtis, "EnemyEtis-30000114");
                break;
            }
            case 2950: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000095);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000115, EnemyEtis, "EnemyEtis-30000115");
                break;
            }
            case 2980: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000096);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000116, EnemyEtis, "EnemyEtis-30000116");
                break;
            }
            case 3000: {
                FormationGeria001* pF3 = (FormationGeria001*)obtainActorFromFactory(30001013);
                bringDirector()->addSubGroup(pF3);
                break;
            }
            case 3010: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000097);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000117, EnemyEtis, "EnemyEtis-30000117");
                break;
            }
            case 3040: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000098);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000118, EnemyEtis, "EnemyEtis-30000118");
                break;
            }
            case 3070: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000099);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000119, EnemyEtis, "EnemyEtis-30000119");
                break;
            }
            case 3100: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000100);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000120, EnemyEtis, "EnemyEtis-30000120");
                break;
            }
            case 3130: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000101);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000121, EnemyEtis, "EnemyEtis-30000121");
                break;
            }
            case 3160: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000102);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000122, EnemyEtis, "EnemyEtis-30000122");
                break;
            }
            case 3190: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000103);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000123, EnemyEtis, "EnemyEtis-30000123");
                break;
            }
            case 3220: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000104);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000124, EnemyEtis, "EnemyEtis-30000124");
                break;
            }
            case 3250: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000105);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000125, EnemyEtis, "EnemyEtis-30000125");
                break;
            }
            case 3280: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000106);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000126, EnemyEtis, "EnemyEtis-30000126");
                break;
            }
            case 3310: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000107);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000127, EnemyEtis, "EnemyEtis-30000127");
                break;
            }
            case 3340: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000108);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000128, EnemyEtis, "EnemyEtis-30000128");
                break;
            }
            case 3370: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000109);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000129, EnemyEtis, "EnemyEtis-30000129");
                break;
            }
            case 3400: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000110);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000130, EnemyEtis, "EnemyEtis-30000130");
                orderActorToFactory(30001014, VarietyRatislavia001, "VarietyRatislavia001-30001014");
                break;
            }
            case 3430: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000111);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000131, EnemyEtis, "EnemyEtis-30000131");
                break;
            }
            case 3460: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000112);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000132, EnemyEtis, "EnemyEtis-30000132");
                break;
            }
            case 3490: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000113);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000133, EnemyEtis, "EnemyEtis-30000133");
                break;
            }
            case 3520: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000114);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000134, EnemyEtis, "EnemyEtis-30000134");
                break;
            }
            case 3550: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000115);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000135, EnemyEtis, "EnemyEtis-30000135");
                break;
            }
            case 3580: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000116);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000136, EnemyEtis, "EnemyEtis-30000136");
                break;
            }
            case 3610: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000117);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000137, EnemyEtis, "EnemyEtis-30000137");
                break;
            }
            case 3640: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000118);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000138, EnemyEtis, "EnemyEtis-30000138");
                break;
            }
            case 3670: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000119);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000139, EnemyEtis, "EnemyEtis-30000139");
                break;
            }
            case 3700: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000120);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000140, EnemyEtis, "EnemyEtis-30000140");
                break;
            }
            case 3730: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000121);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000141, EnemyEtis, "EnemyEtis-30000141");
                break;
            }
            case 3760: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000122);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000142, EnemyEtis, "EnemyEtis-30000142");
                break;
            }
            case 3790: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000123);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000143, EnemyEtis, "EnemyEtis-30000143");
                break;
            }
            case 3820: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000124);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000144, EnemyEtis, "EnemyEtis-30000144");
                break;
            }
            case 3850: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000125);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000145, EnemyEtis, "EnemyEtis-30000145");
                break;
            }
            case 3880: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000126);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000146, EnemyEtis, "EnemyEtis-30000146");
                break;
            }
            case 3910: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000127);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000147, EnemyEtis, "EnemyEtis-30000147");
                break;
            }
            case 3940: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000128);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000148, EnemyEtis, "EnemyEtis-30000148");
                break;
            }
            case 3970: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000129);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000149, EnemyEtis, "EnemyEtis-30000149");
                break;
            }
            case 4000: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000130);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000150, EnemyEtis, "EnemyEtis-30000150");
                VarietyRatislavia001* pRatislavia = (VarietyRatislavia001*)obtainActorFromFactory(30001014);
                bringDirector()->addSubGroup(pRatislavia);
                break;
            }
            case 4030: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000131);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000151, EnemyEtis, "EnemyEtis-30000151");
                break;
            }
            case 4060: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000132);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000152, EnemyEtis, "EnemyEtis-30000152");
                break;
            }
            case 4090: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000133);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000153, EnemyEtis, "EnemyEtis-30000153");
                break;
            }
            case 4120: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000134);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000154, EnemyEtis, "EnemyEtis-30000154");
                break;
            }
            case 4150: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000135);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000155, EnemyEtis, "EnemyEtis-30000155");
                break;
            }
            case 4180: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000136);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000156, EnemyEtis, "EnemyEtis-30000156");
                break;
            }
            case 4210: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000137);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000157, EnemyEtis, "EnemyEtis-30000157");
                break;
            }
            case 4240: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000138);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000158, EnemyEtis, "EnemyEtis-30000158");
                break;
            }
            case 4270: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000139);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000159, EnemyEtis, "EnemyEtis-30000159");
                break;
            }
            case 4300: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000140);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000160, EnemyEtis, "EnemyEtis-30000160");
                break;
            }
            case 4330: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000141);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000161, EnemyEtis, "EnemyEtis-30000161");
                break;
            }
            case 4360: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000142);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000162, EnemyEtis, "EnemyEtis-30000162");
                break;
            }
            case 4390: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000143);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000163, EnemyEtis, "EnemyEtis-30000163");
                break;
            }
            case 4400: {
                orderActorToFactory(30001015, VarietyRatislavia002, "VarietyRatislavia002-30001015");
                orderActorToFactory(30001019, FormationHalia, "FormationHalia-30001019");
                orderActorToFactory(30001030, EnemyEsperia, "EnemyEsperia-30001030");
                break;
            }
            case 4420: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000144);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000164, EnemyEtis, "EnemyEtis-30000164");
                break;
            }
            case 4450: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000145);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000165, EnemyEtis, "EnemyEtis-30000165");
                break;
            }
            case 4480: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000146);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000166, EnemyEtis, "EnemyEtis-30000166");
                break;
            }
            case 4510: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000147);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000167, EnemyEtis, "EnemyEtis-30000167");
                break;
            }
            case 4540: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000148);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000168, EnemyEtis, "EnemyEtis-30000168");
                break;
            }
            case 4570: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000149);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000169, EnemyEtis, "EnemyEtis-30000169");
                break;
            }
            case 4600: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000150);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000170, EnemyEtis, "EnemyEtis-30000170");
                break;
            }
            case 4630: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000151);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000171, EnemyEtis, "EnemyEtis-30000171");
                break;
            }
            case 4660: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000152);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000172, EnemyEtis, "EnemyEtis-30000172");
                break;
            }
            case 4690: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000153);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000173, EnemyEtis, "EnemyEtis-30000173");
                break;
            }
            case 4720: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000154);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000174, EnemyEtis, "EnemyEtis-30000174");
                break;
            }
            case 4750: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000155);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000175, EnemyEtis, "EnemyEtis-30000175");
                break;
            }
            case 4780: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000156);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000176, EnemyEtis, "EnemyEtis-30000176");
                break;
            }
            case 4810: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000157);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000177, EnemyEtis, "EnemyEtis-30000177");
                break;
            }
            case 4840: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000158);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000178, EnemyEtis, "EnemyEtis-30000178");
                break;
            }
            case 4870: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000159);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000179, EnemyEtis, "EnemyEtis-30000179");
                break;
            }
            case 4900: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000160);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000180, EnemyEtis, "EnemyEtis-30000180");
                break;
            }
            case 4930: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000161);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000181, EnemyEtis, "EnemyEtis-30000181");
                break;
            }
            case 4960: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000162);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000182, EnemyEtis, "EnemyEtis-30000182");
                break;
            }
            case 4990: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000163);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000183, EnemyEtis, "EnemyEtis-30000183");
                break;
            }
            case 5000: {
                VarietyRatislavia002* pRatislaviaA = (VarietyRatislavia002*)obtainActorFromFactory(30001015);
                bringDirector()->addSubGroup(pRatislaviaA);
                FormationHalia* pF = (FormationHalia*)obtainActorFromFactory(30001019);
                bringDirector()->addSubGroup(pF);
                EnemyEsperia* p4 = (EnemyEsperia*)obtainActorFromFactory(30001030);
                bringDirector()->addSubGroup(p4);
                break;
            }
            case 5020: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000164);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000184, EnemyEtis, "EnemyEtis-30000184");
                break;
            }
            case 5050: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000165);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000185, EnemyEtis, "EnemyEtis-30000185");
                break;
            }
            case 5080: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000166);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000186, EnemyEtis, "EnemyEtis-30000186");
                break;
            }
            case 5110: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000167);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000187, EnemyEtis, "EnemyEtis-30000187");
                break;
            }
            case 5140: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000168);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000188, EnemyEtis, "EnemyEtis-30000188");
                break;
            }
            case 5170: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000169);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000189, EnemyEtis, "EnemyEtis-30000189");
                break;
            }
            case 5200: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000170);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000190, EnemyEtis, "EnemyEtis-30000190");
                break;
            }
            case 5230: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000171);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000191, EnemyEtis, "EnemyEtis-30000191");
                break;
            }
            case 5260: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000172);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000192, EnemyEtis, "EnemyEtis-30000192");
                break;
            }
            case 5290: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000173);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000193, EnemyEtis, "EnemyEtis-30000193");
                break;
            }
            case 5320: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000174);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000194, EnemyEtis, "EnemyEtis-30000194");
                break;
            }
            case 5350: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000175);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000195, EnemyEtis, "EnemyEtis-30000195");
                break;
            }
            case 5380: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000176);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000196, EnemyEtis, "EnemyEtis-30000196");
                break;
            }
            case 5400: {
                orderActorToFactory(30001016, VarietyRatislavia003, "VarietyRatislavia003-30001016");
                orderActorToFactory(30001031, EnemyEsperia, "EnemyEsperia-30001031");
                break;
            }
            case 5410: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000177);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000197, EnemyEtis, "EnemyEtis-30000197");
                break;
            }
            case 5440: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000178);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000198, EnemyEtis, "EnemyEtis-30000198");
                break;
            }
            case 5470: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000179);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000199, EnemyEtis, "EnemyEtis-30000199");
                break;
            }
            case 5500: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000180);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000200, EnemyEtis, "EnemyEtis-30000200");
                break;
            }
            case 5530: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000181);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000201, EnemyEtis, "EnemyEtis-30000201");
                break;
            }
            case 5560: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000182);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000202, EnemyEtis, "EnemyEtis-30000202");
                break;
            }
            case 5590: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000183);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000203, EnemyEtis, "EnemyEtis-30000203");
                break;
            }
            case 5620: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000184);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000204, EnemyEtis, "EnemyEtis-30000204");
                break;
            }
            case 5650: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000185);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000205, EnemyEtis, "EnemyEtis-30000205");
                break;
            }
            case 5680: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000186);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000206, EnemyEtis, "EnemyEtis-30000206");
                break;
            }
            case 5710: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000187);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000207, EnemyEtis, "EnemyEtis-30000207");
                break;
            }
            case 5740: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000188);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000208, EnemyEtis, "EnemyEtis-30000208");
                break;
            }
            case 5770: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000189);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000209, EnemyEtis, "EnemyEtis-30000209");
                break;
            }
            case 5800: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000190);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000210, EnemyEtis, "EnemyEtis-30000210");
                break;
            }
            case 5830: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000191);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000211, EnemyEtis, "EnemyEtis-30000211");
                break;
            }
            case 5860: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000192);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000212, EnemyEtis, "EnemyEtis-30000212");
                break;
            }
            case 5890: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000193);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000213, EnemyEtis, "EnemyEtis-30000213");
                break;
            }
            case 5920: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000194);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000214, EnemyEtis, "EnemyEtis-30000214");
                break;
            }
            case 5950: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000195);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000215, EnemyEtis, "EnemyEtis-30000215");
                break;
            }
            case 5980: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000196);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000216, EnemyEtis, "EnemyEtis-30000216");
                break;
            }
            case 6000: {
                VarietyRatislavia003* pRatislaviaB = (VarietyRatislavia003*)obtainActorFromFactory(30001016);
                bringDirector()->addSubGroup(pRatislaviaB);
                EnemyEsperia* p5 = (EnemyEsperia*)obtainActorFromFactory(30001031);
                bringDirector()->addSubGroup(p5);
                break;
            }
            case 6010: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000197);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000217, EnemyEtis, "EnemyEtis-30000217");
                break;
            }
            case 6040: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000198);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000218, EnemyEtis, "EnemyEtis-30000218");
                break;
            }
            case 6070: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000199);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000219, EnemyEtis, "EnemyEtis-30000219");
                break;
            }
            case 6100: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000200);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000220, EnemyEtis, "EnemyEtis-30000220");
                break;
            }
            case 6130: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000201);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000221, EnemyEtis, "EnemyEtis-30000221");
                break;
            }
            case 6160: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000202);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000222, EnemyEtis, "EnemyEtis-30000222");
                break;
            }
            case 6190: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000203);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000223, EnemyEtis, "EnemyEtis-30000223");
                break;
            }
            case 6220: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000204);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000224, EnemyEtis, "EnemyEtis-30000224");
                break;
            }
            case 6250: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000205);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000225, EnemyEtis, "EnemyEtis-30000225");
                break;
            }
            case 6280: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000206);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000226, EnemyEtis, "EnemyEtis-30000226");
                break;
            }
            case 6310: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000207);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000227, EnemyEtis, "EnemyEtis-30000227");
                break;
            }
            case 6340: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000208);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000228, EnemyEtis, "EnemyEtis-30000228");
                break;
            }
            case 6370: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000209);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000229, EnemyEtis, "EnemyEtis-30000229");
                break;
            }
            case 6400: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000210);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000230, EnemyEtis, "EnemyEtis-30000230");
                orderActorToFactory(30001017, VarietyRatislavia004, "VarietyRatislavia004-30001017");
                orderActorToFactory(30001032, EnemyEsperia, "EnemyEsperia-30001032");
                break;
            }
            case 6430: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000211);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000231, EnemyEtis, "EnemyEtis-30000231");
                break;
            }
            case 6460: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000212);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000232, EnemyEtis, "EnemyEtis-30000232");
                break;
            }
            case 6490: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000213);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000233, EnemyEtis, "EnemyEtis-30000233");
                break;
            }
            case 6520: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000214);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000234, EnemyEtis, "EnemyEtis-30000234");
                break;
            }
            case 6550: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000215);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000235, EnemyEtis, "EnemyEtis-30000235");
                break;
            }
            case 6580: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000216);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000236, EnemyEtis, "EnemyEtis-30000236");
                break;
            }
            case 6610: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000217);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000237, EnemyEtis, "EnemyEtis-30000237");
                break;
            }
            case 6640: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000218);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000238, EnemyEtis, "EnemyEtis-30000238");
                break;
            }
            case 6670: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000219);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000239, EnemyEtis, "EnemyEtis-30000239");
                break;
            }
            case 6700: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000220);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000240, EnemyEtis, "EnemyEtis-30000240");
                break;
            }
            case 6730: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000221);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000241, EnemyEtis, "EnemyEtis-30000241");
                break;
            }
            case 6760: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000222);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000242, EnemyEtis, "EnemyEtis-30000242");
                break;
            }
            case 6790: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000223);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000243, EnemyEtis, "EnemyEtis-30000243");
                break;
            }
            case 6820: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000224);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000244, EnemyEtis, "EnemyEtis-30000244");
                break;
            }
            case 6850: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000225);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000245, EnemyEtis, "EnemyEtis-30000245");
                break;
            }
            case 6880: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000226);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000246, EnemyEtis, "EnemyEtis-30000246");
                break;
            }
            case 6910: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000227);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000247, EnemyEtis, "EnemyEtis-30000247");
                break;
            }
            case 6940: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000228);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000248, EnemyEtis, "EnemyEtis-30000248");
                break;
            }
            case 6970: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000229);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000249, EnemyEtis, "EnemyEtis-30000249");
                break;
            }
            case 7000: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000230);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000250, EnemyEtis, "EnemyEtis-30000250");
                VarietyRatislavia004* pRatislavia = (VarietyRatislavia004*)obtainActorFromFactory(30001017);
                bringDirector()->addSubGroup(pRatislavia);
                EnemyEsperia* p6 = (EnemyEsperia*)obtainActorFromFactory(30001032);
                bringDirector()->addSubGroup(p6);
                break;
            }
            case 7030: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000231);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000251, EnemyEtis, "EnemyEtis-30000251");
                break;
            }
            case 7060: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000232);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000252, EnemyEtis, "EnemyEtis-30000252");
                break;
            }
            case 7090: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000233);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000253, EnemyEtis, "EnemyEtis-30000253");
                break;
            }
            case 7120: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000234);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000254, EnemyEtis, "EnemyEtis-30000254");
                break;
            }
            case 7150: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000235);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000255, EnemyEtis, "EnemyEtis-30000255");
                break;
            }
            case 7180: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000236);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000256, EnemyEtis, "EnemyEtis-30000256");
                break;
            }
            case 7210: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000237);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000257, EnemyEtis, "EnemyEtis-30000257");
                break;
            }
            case 7240: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000238);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000258, EnemyEtis, "EnemyEtis-30000258");
                break;
            }
            case 7270: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000239);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000259, EnemyEtis, "EnemyEtis-30000259");
                break;
            }
            case 7300: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000240);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000260, EnemyEtis, "EnemyEtis-30000260");
                break;
            }
            case 7330: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000241);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000261, EnemyEtis, "EnemyEtis-30000261");
                break;
            }
            case 7360: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000242);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000262, EnemyEtis, "EnemyEtis-30000262");
                break;
            }
            case 7390: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000243);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000263, EnemyEtis, "EnemyEtis-30000263");
                break;
            }
            case 7400: {
                orderActorToFactory(30001033, EnemyEsperia, "EnemyEsperia-30001033");
                break;
            }
            case 7420: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000244);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000264, EnemyEtis, "EnemyEtis-30000264");
                break;
            }
            case 7450: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000245);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000265, EnemyEtis, "EnemyEtis-30000265");
                break;
            }
            case 7480: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000246);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000266, EnemyEtis, "EnemyEtis-30000266");
                break;
            }
            case 7510: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000247);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000267, EnemyEtis, "EnemyEtis-30000267");
                break;
            }
            case 7540: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000248);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000268, EnemyEtis, "EnemyEtis-30000268");
                break;
            }
            case 7570: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000249);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000269, EnemyEtis, "EnemyEtis-30000269");
                break;
            }
            case 7600: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000250);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000270, EnemyEtis, "EnemyEtis-30000270");
                break;
            }
            case 7630: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000251);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000271, EnemyEtis, "EnemyEtis-30000271");
                break;
            }
            case 7660: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000252);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000272, EnemyEtis, "EnemyEtis-30000272");
                break;
            }
            case 7690: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000253);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000273, EnemyEtis, "EnemyEtis-30000273");
                break;
            }
            case 7720: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000254);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000274, EnemyEtis, "EnemyEtis-30000274");
                break;
            }
            case 7750: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000255);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000275, EnemyEtis, "EnemyEtis-30000275");
                break;
            }
            case 7780: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000256);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000276, EnemyEtis, "EnemyEtis-30000276");
                break;
            }
            case 7810: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000257);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000277, EnemyEtis, "EnemyEtis-30000277");
                break;
            }
            case 7840: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000258);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000278, EnemyEtis, "EnemyEtis-30000278");
                break;
            }
            case 7870: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000259);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000279, EnemyEtis, "EnemyEtis-30000279");
                break;
            }
            case 7900: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000260);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000280, EnemyEtis, "EnemyEtis-30000280");
                break;
            }
            case 7930: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000261);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000281, EnemyEtis, "EnemyEtis-30000281");
                break;
            }
            case 7960: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000262);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000282, EnemyEtis, "EnemyEtis-30000282");
                break;
            }
            case 7990: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000263);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000283, EnemyEtis, "EnemyEtis-30000283");
                break;
            }
            case 8000: {
                EnemyEsperia* p7 = (EnemyEsperia*)obtainActorFromFactory(30001033);
                bringDirector()->addSubGroup(p7);
                break;
            }
            case 8020: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000264);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000284, EnemyEtis, "EnemyEtis-30000284");
                break;
            }
            case 8050: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000265);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000285, EnemyEtis, "EnemyEtis-30000285");
                break;
            }
            case 8080: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000266);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000286, EnemyEtis, "EnemyEtis-30000286");
                break;
            }
            case 8110: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000267);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000287, EnemyEtis, "EnemyEtis-30000287");
                break;
            }
            case 8140: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000268);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000288, EnemyEtis, "EnemyEtis-30000288");
                break;
            }
            case 8170: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000269);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000289, EnemyEtis, "EnemyEtis-30000289");
                break;
            }
            case 8200: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000270);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000290, EnemyEtis, "EnemyEtis-30000290");
                break;
            }
            case 8230: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000271);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000291, EnemyEtis, "EnemyEtis-30000291");
                break;
            }
            case 8260: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000272);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000292, EnemyEtis, "EnemyEtis-30000292");
                break;
            }
            case 8290: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000273);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000293, EnemyEtis, "EnemyEtis-30000293");
                break;
            }
            case 8320: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000274);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000294, EnemyEtis, "EnemyEtis-30000294");
                break;
            }
            case 8350: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000275);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000295, EnemyEtis, "EnemyEtis-30000295");
                break;
            }
            case 8380: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000276);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000296, EnemyEtis, "EnemyEtis-30000296");
                break;
            }
            case 8400: {
                orderActorToFactory(30001020, FormationHalia, "FormationHalia-30001020");
                orderActorToFactory(30001034, EnemyEsperia, "EnemyEsperia-30001034");
                break;
            }
            case 8410: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000277);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000297, EnemyEtis, "EnemyEtis-30000297");
                break;
            }
            case 8440: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000278);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000298, EnemyEtis, "EnemyEtis-30000298");
                break;
            }
            case 8470: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000279);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000299, EnemyEtis, "EnemyEtis-30000299");
                break;
            }
            case 8500: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000280);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000300, EnemyEtis, "EnemyEtis-30000300");
                break;
            }
            case 8530: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000281);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000301, EnemyEtis, "EnemyEtis-30000301");
                break;
            }
            case 8560: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000282);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000302, EnemyEtis, "EnemyEtis-30000302");
                break;
            }
            case 8590: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000283);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000303, EnemyEtis, "EnemyEtis-30000303");
                break;
            }
            case 8600: {
                orderActorToFactory(30001022, FormationRis002, "FormationRis002-30001022");
                orderActorToFactory(30001023, FormationRis001, "FormationRis001-30001023");
                orderActorToFactory(30001024, FormationRis001, "FormationRis001-30001024");
                orderActorToFactory(30001025, FormationRis002, "FormationRis002-30001025");
                orderActorToFactory(30001026, FormationRis001, "FormationRis001-30001026");
                orderActorToFactory(30001027, FormationRis002, "FormationRis002-30001027");
                break;
            }
            case 8620: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000284);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000304, EnemyEtis, "EnemyEtis-30000304");
                break;
            }
            case 8650: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000285);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000305, EnemyEtis, "EnemyEtis-30000305");
                break;
            }
            case 8680: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000286);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000306, EnemyEtis, "EnemyEtis-30000306");
                break;
            }
            case 8710: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000287);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000307, EnemyEtis, "EnemyEtis-30000307");
                break;
            }
            case 8740: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000288);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000308, EnemyEtis, "EnemyEtis-30000308");
                break;
            }
            case 8770: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000289);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000309, EnemyEtis, "EnemyEtis-30000309");
                break;
            }
            case 8800: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000290);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000310, EnemyEtis, "EnemyEtis-30000310");
                break;
            }
            case 8830: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000291);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000311, EnemyEtis, "EnemyEtis-30000311");
                break;
            }
            case 8860: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000292);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000312, EnemyEtis, "EnemyEtis-30000312");
                break;
            }
            case 8890: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000293);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000313, EnemyEtis, "EnemyEtis-30000313");
                break;
            }
            case 8900: {
                orderActorToFactory(30001028, EnemyIrce, "EnemyIrce-30001028");
                break;
            }
            case 8920: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000294);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000314, EnemyEtis, "EnemyEtis-30000314");
                break;
            }
            case 8950: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000295);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000315, EnemyEtis, "EnemyEtis-30000315");
                break;
            }
            case 8980: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000296);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000316, EnemyEtis, "EnemyEtis-30000316");
                break;
            }
            case 9000: {
                FormationHalia* pF = (FormationHalia*)obtainActorFromFactory(30001020);
                bringDirector()->addSubGroup(pF);
                EnemyEsperia* p8 = (EnemyEsperia*)obtainActorFromFactory(30001034);
                bringDirector()->addSubGroup(p8);
                break;
            }
            case 9010: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000297);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000317, EnemyEtis, "EnemyEtis-30000317");
                break;
            }
            case 9040: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000298);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000318, EnemyEtis, "EnemyEtis-30000318");
                break;
            }
            case 9070: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000299);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000319, EnemyEtis, "EnemyEtis-30000319");
                break;
            }
            case 9100: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000300);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000320, EnemyEtis, "EnemyEtis-30000320");
                break;
            }
            case 9130: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000301);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000321, EnemyEtis, "EnemyEtis-30000321");
                break;
            }
            case 9160: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000302);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000322, EnemyEtis, "EnemyEtis-30000322");
                break;
            }
            case 9190: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000303);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000323, EnemyEtis, "EnemyEtis-30000323");
                break;
            }
            case 9200: {
                {
                FormationTableScene* ta = NEW FormationTableScene("FormationTableScene-9");
                ta->setMaxPerformFrame(2000);
                addSubLast(ta);
                ta->addToTable(((FormationRis002*)obtainActorFromFactory(30001022)), 400);
                ta->addToTable(((FormationRis001*)obtainActorFromFactory(30001023)), 400);
                ta->addToTable(((FormationRis001*)obtainActorFromFactory(30001024)), 400);
                ta->addToTable(((FormationRis002*)obtainActorFromFactory(30001025)), 400);
                ta->addToTable(((FormationRis001*)obtainActorFromFactory(30001026)), 400);
                ta->addToTable(((FormationRis002*)obtainActorFromFactory(30001027)), 400);
                }
                break;
            }
            case 9220: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000304);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000324, EnemyEtis, "EnemyEtis-30000324");
                break;
            }
            case 9250: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000305);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000325, EnemyEtis, "EnemyEtis-30000325");
                break;
            }
            case 9280: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000306);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000326, EnemyEtis, "EnemyEtis-30000326");
                break;
            }
            case 9310: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000307);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000327, EnemyEtis, "EnemyEtis-30000327");
                break;
            }
            case 9340: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000308);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000328, EnemyEtis, "EnemyEtis-30000328");
                break;
            }
            case 9370: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000309);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000329, EnemyEtis, "EnemyEtis-30000329");
                break;
            }
            case 9400: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000310);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000330, EnemyEtis, "EnemyEtis-30000330");
                orderActorToFactory(30001035, EnemyEsperia, "EnemyEsperia-30001035");
                break;
            }
            case 9430: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000311);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000331, EnemyEtis, "EnemyEtis-30000331");
                break;
            }
            case 9460: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000312);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000332, EnemyEtis, "EnemyEtis-30000332");
                break;
            }
            case 9490: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000313);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000333, EnemyEtis, "EnemyEtis-30000333");
                break;
            }
            case 9500: {
                EnemyIrce* p10 = (EnemyIrce*)obtainActorFromFactory(30001028);
                bringDirector()->addSubGroup(p10);
                break;
            }
            case 9520: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000314);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000334, EnemyEtis, "EnemyEtis-30000334");
                break;
            }
            case 9550: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000315);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000335, EnemyEtis, "EnemyEtis-30000335");
                break;
            }
            case 9580: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000316);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000336, EnemyEtis, "EnemyEtis-30000336");
                break;
            }
            case 9610: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000317);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000337, EnemyEtis, "EnemyEtis-30000337");
                break;
            }
            case 9640: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000318);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000338, EnemyEtis, "EnemyEtis-30000338");
                break;
            }
            case 9670: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000319);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000339, EnemyEtis, "EnemyEtis-30000339");
                break;
            }
            case 9700: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000320);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000340, EnemyEtis, "EnemyEtis-30000340");
                break;
            }
            case 9730: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000321);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000341, EnemyEtis, "EnemyEtis-30000341");
                break;
            }
            case 9760: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000322);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000342, EnemyEtis, "EnemyEtis-30000342");
                break;
            }
            case 9790: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000323);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000343, EnemyEtis, "EnemyEtis-30000343");
                break;
            }
            case 9820: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000324);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000344, EnemyEtis, "EnemyEtis-30000344");
                break;
            }
            case 9850: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000325);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000345, EnemyEtis, "EnemyEtis-30000345");
                break;
            }
            case 9880: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000326);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000346, EnemyEtis, "EnemyEtis-30000346");
                break;
            }
            case 9910: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000327);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000347, EnemyEtis, "EnemyEtis-30000347");
                break;
            }
            case 9940: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000328);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000348, EnemyEtis, "EnemyEtis-30000348");
                break;
            }
            case 9970: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000329);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000349, EnemyEtis, "EnemyEtis-30000349");
                break;
            }
            case 10000: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000330);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000350, EnemyEtis, "EnemyEtis-30000350");
                EnemyEsperia* p11 = (EnemyEsperia*)obtainActorFromFactory(30001035);
                bringDirector()->addSubGroup(p11);
                break;
            }
            case 10030: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000331);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000351, EnemyEtis, "EnemyEtis-30000351");
                break;
            }
            case 10060: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000332);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000352, EnemyEtis, "EnemyEtis-30000352");
                break;
            }
            case 10090: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000333);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000353, EnemyEtis, "EnemyEtis-30000353");
                break;
            }
            case 10120: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000334);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000354, EnemyEtis, "EnemyEtis-30000354");
                break;
            }
            case 10150: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000335);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000355, EnemyEtis, "EnemyEtis-30000355");
                break;
            }
            case 10180: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000336);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000356, EnemyEtis, "EnemyEtis-30000356");
                break;
            }
            case 10210: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000337);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000357, EnemyEtis, "EnemyEtis-30000357");
                break;
            }
            case 10240: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000338);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000358, EnemyEtis, "EnemyEtis-30000358");
                break;
            }
            case 10270: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000339);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000359, EnemyEtis, "EnemyEtis-30000359");
                break;
            }
            case 10300: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000340);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000360, EnemyEtis, "EnemyEtis-30000360");
                break;
            }
            case 10330: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000341);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000361, EnemyEtis, "EnemyEtis-30000361");
                break;
            }
            case 10360: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000342);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000362, EnemyEtis, "EnemyEtis-30000362");
                break;
            }
            case 10390: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000343);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000363, EnemyEtis, "EnemyEtis-30000363");
                break;
            }
            case 10420: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000344);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000364, EnemyEtis, "EnemyEtis-30000364");
                break;
            }
            case 10450: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000345);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000365, EnemyEtis, "EnemyEtis-30000365");
                break;
            }
            case 10480: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000346);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000366, EnemyEtis, "EnemyEtis-30000366");
                break;
            }
            case 10510: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000347);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000367, EnemyEtis, "EnemyEtis-30000367");
                break;
            }
            case 10540: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000348);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000368, EnemyEtis, "EnemyEtis-30000368");
                break;
            }
            case 10570: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000349);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000369, EnemyEtis, "EnemyEtis-30000369");
                break;
            }
            case 10600: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000350);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000370, EnemyEtis, "EnemyEtis-30000370");
                break;
            }
            case 10630: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000351);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000371, EnemyEtis, "EnemyEtis-30000371");
                break;
            }
            case 10660: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000352);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000372, EnemyEtis, "EnemyEtis-30000372");
                break;
            }
            case 10690: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000353);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000373, EnemyEtis, "EnemyEtis-30000373");
                break;
            }
            case 10720: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000354);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000374, EnemyEtis, "EnemyEtis-30000374");
                break;
            }
            case 10750: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000355);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000375, EnemyEtis, "EnemyEtis-30000375");
                break;
            }
            case 10780: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000356);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000376, EnemyEtis, "EnemyEtis-30000376");
                break;
            }
            case 10810: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000357);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000377, EnemyEtis, "EnemyEtis-30000377");
                break;
            }
            case 10840: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000358);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000378, EnemyEtis, "EnemyEtis-30000378");
                break;
            }
            case 10870: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000359);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000379, EnemyEtis, "EnemyEtis-30000379");
                break;
            }
            case 10900: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000360);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000380, EnemyEtis, "EnemyEtis-30000380");
                break;
            }
            case 10930: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000361);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000381, EnemyEtis, "EnemyEtis-30000381");
                break;
            }
            case 10960: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000362);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000382, EnemyEtis, "EnemyEtis-30000382");
                break;
            }
            case 10990: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000363);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000383, EnemyEtis, "EnemyEtis-30000383");
                break;
            }
            case 11020: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000364);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000384, EnemyEtis, "EnemyEtis-30000384");
                break;
            }
            case 11050: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000365);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000385, EnemyEtis, "EnemyEtis-30000385");
                break;
            }
            case 11080: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000366);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000386, EnemyEtis, "EnemyEtis-30000386");
                break;
            }
            case 11110: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000367);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000387, EnemyEtis, "EnemyEtis-30000387");
                break;
            }
            case 11140: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000368);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000388, EnemyEtis, "EnemyEtis-30000388");
                break;
            }
            case 11170: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000369);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000389, EnemyEtis, "EnemyEtis-30000389");
                break;
            }
            case 11200: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000370);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000390, EnemyEtis, "EnemyEtis-30000390");
                break;
            }
            case 11230: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000371);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000391, EnemyEtis, "EnemyEtis-30000391");
                break;
            }
            case 11260: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000372);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000392, EnemyEtis, "EnemyEtis-30000392");
                break;
            }
            case 11290: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000373);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000393, EnemyEtis, "EnemyEtis-30000393");
                break;
            }
            case 11320: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000374);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000394, EnemyEtis, "EnemyEtis-30000394");
                break;
            }
            case 11350: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000375);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000395, EnemyEtis, "EnemyEtis-30000395");
                break;
            }
            case 11380: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000376);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000396, EnemyEtis, "EnemyEtis-30000396");
                break;
            }
            case 11410: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000377);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000397, EnemyEtis, "EnemyEtis-30000397");
                break;
            }
            case 11440: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000378);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000398, EnemyEtis, "EnemyEtis-30000398");
                break;
            }
            case 11470: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000379);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000399, EnemyEtis, "EnemyEtis-30000399");
                break;
            }
            case 11500: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000380);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000400, EnemyEtis, "EnemyEtis-30000400");
                break;
            }
            case 11530: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000381);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000401, EnemyEtis, "EnemyEtis-30000401");
                break;
            }
            case 11560: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000382);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000402, EnemyEtis, "EnemyEtis-30000402");
                break;
            }
            case 11590: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000383);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000403, EnemyEtis, "EnemyEtis-30000403");
                break;
            }
            case 11620: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000384);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000404, EnemyEtis, "EnemyEtis-30000404");
                break;
            }
            case 11650: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000385);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000405, EnemyEtis, "EnemyEtis-30000405");
                break;
            }
            case 11680: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000386);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000406, EnemyEtis, "EnemyEtis-30000406");
                break;
            }
            case 11710: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000387);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000407, EnemyEtis, "EnemyEtis-30000407");
                break;
            }
            case 11740: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000388);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000408, EnemyEtis, "EnemyEtis-30000408");
                break;
            }
            case 11770: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000389);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000409, EnemyEtis, "EnemyEtis-30000409");
                break;
            }
            case 11800: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000390);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000410, EnemyEtis, "EnemyEtis-30000410");
                break;
            }
            case 11830: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000391);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000411, EnemyEtis, "EnemyEtis-30000411");
                break;
            }
            case 11860: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000392);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000412, EnemyEtis, "EnemyEtis-30000412");
                break;
            }
            case 11890: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000393);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000413, EnemyEtis, "EnemyEtis-30000413");
                break;
            }
            case 11920: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000394);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000414, EnemyEtis, "EnemyEtis-30000414");
                break;
            }
            case 11950: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000395);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000415, EnemyEtis, "EnemyEtis-30000415");
                break;
            }
            case 11980: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000396);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000416, EnemyEtis, "EnemyEtis-30000416");
                break;
            }
            case 12010: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000397);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000417, EnemyEtis, "EnemyEtis-30000417");
                break;
            }
            case 12040: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000398);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000418, EnemyEtis, "EnemyEtis-30000418");
                break;
            }
            case 12070: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000399);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000419, EnemyEtis, "EnemyEtis-30000419");
                break;
            }
            case 12100: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000400);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000420, EnemyEtis, "EnemyEtis-30000420");
                break;
            }
            case 12130: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000401);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000421, EnemyEtis, "EnemyEtis-30000421");
                break;
            }
            case 12160: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000402);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000422, EnemyEtis, "EnemyEtis-30000422");
                break;
            }
            case 12190: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000403);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000423, EnemyEtis, "EnemyEtis-30000423");
                break;
            }
            case 12220: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000404);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000424, EnemyEtis, "EnemyEtis-30000424");
                break;
            }
            case 12250: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000405);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000425, EnemyEtis, "EnemyEtis-30000425");
                break;
            }
            case 12280: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000406);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000426, EnemyEtis, "EnemyEtis-30000426");
                break;
            }
            case 12310: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000407);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000427, EnemyEtis, "EnemyEtis-30000427");
                break;
            }
            case 12340: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000408);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000428, EnemyEtis, "EnemyEtis-30000428");
                break;
            }
            case 12370: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000409);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000429, EnemyEtis, "EnemyEtis-30000429");
                break;
            }
            case 12400: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000410);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000430, EnemyEtis, "EnemyEtis-30000430");
                break;
            }
            case 12430: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000411);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000431, EnemyEtis, "EnemyEtis-30000431");
                break;
            }
            case 12460: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000412);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000432, EnemyEtis, "EnemyEtis-30000432");
                break;
            }
            case 12490: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000413);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000433, EnemyEtis, "EnemyEtis-30000433");
                break;
            }
            case 12520: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000414);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000434, EnemyEtis, "EnemyEtis-30000434");
                break;
            }
            case 12550: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000415);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000435, EnemyEtis, "EnemyEtis-30000435");
                break;
            }
            case 12580: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000416);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000436, EnemyEtis, "EnemyEtis-30000436");
                break;
            }
            case 12610: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000417);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000437, EnemyEtis, "EnemyEtis-30000437");
                break;
            }
            case 12640: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000418);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000438, EnemyEtis, "EnemyEtis-30000438");
                break;
            }
            case 12670: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000419);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000439, EnemyEtis, "EnemyEtis-30000439");
                break;
            }
            case 12700: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000420);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000440, EnemyEtis, "EnemyEtis-30000440");
                break;
            }
            case 12730: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000421);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000441, EnemyEtis, "EnemyEtis-30000441");
                break;
            }
            case 12760: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000422);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000442, EnemyEtis, "EnemyEtis-30000442");
                break;
            }
            case 12790: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000423);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000443, EnemyEtis, "EnemyEtis-30000443");
                break;
            }
            case 12820: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000424);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000444, EnemyEtis, "EnemyEtis-30000444");
                break;
            }
            case 12850: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000425);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000445, EnemyEtis, "EnemyEtis-30000445");
                break;
            }
            case 12880: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000426);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000446, EnemyEtis, "EnemyEtis-30000446");
                break;
            }
            case 12910: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000427);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000447, EnemyEtis, "EnemyEtis-30000447");
                break;
            }
            case 12940: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000428);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000448, EnemyEtis, "EnemyEtis-30000448");
                break;
            }
            case 12970: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000429);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000449, EnemyEtis, "EnemyEtis-30000449");
                break;
            }
            case 13000: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000430);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000450, EnemyEtis, "EnemyEtis-30000450");
                break;
            }
            case 13030: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000431);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000451, EnemyEtis, "EnemyEtis-30000451");
                break;
            }
            case 13060: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000432);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000452, EnemyEtis, "EnemyEtis-30000452");
                break;
            }
            case 13090: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000433);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000453, EnemyEtis, "EnemyEtis-30000453");
                break;
            }
            case 13120: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000434);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000454, EnemyEtis, "EnemyEtis-30000454");
                break;
            }
            case 13150: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000435);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000455, EnemyEtis, "EnemyEtis-30000455");
                break;
            }
            case 13180: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000436);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000456, EnemyEtis, "EnemyEtis-30000456");
                break;
            }
            case 13210: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000437);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000457, EnemyEtis, "EnemyEtis-30000457");
                break;
            }
            case 13240: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000438);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000458, EnemyEtis, "EnemyEtis-30000458");
                break;
            }
            case 13270: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000439);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000459, EnemyEtis, "EnemyEtis-30000459");
                break;
            }
            case 13300: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000440);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000460, EnemyEtis, "EnemyEtis-30000460");
                break;
            }
            case 13330: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000441);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000461, EnemyEtis, "EnemyEtis-30000461");
                break;
            }
            case 13360: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000442);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000462, EnemyEtis, "EnemyEtis-30000462");
                break;
            }
            case 13390: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000443);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000463, EnemyEtis, "EnemyEtis-30000463");
                break;
            }
            case 13420: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000444);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000464, EnemyEtis, "EnemyEtis-30000464");
                break;
            }
            case 13450: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000445);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000465, EnemyEtis, "EnemyEtis-30000465");
                break;
            }
            case 13480: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000446);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000466, EnemyEtis, "EnemyEtis-30000466");
                break;
            }
            case 13510: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000447);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000467, EnemyEtis, "EnemyEtis-30000467");
                break;
            }
            case 13540: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000448);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000468, EnemyEtis, "EnemyEtis-30000468");
                break;
            }
            case 13570: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000449);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000469, EnemyEtis, "EnemyEtis-30000469");
                break;
            }
            case 13600: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000450);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000470, EnemyEtis, "EnemyEtis-30000470");
                break;
            }
            case 13630: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000451);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000471, EnemyEtis, "EnemyEtis-30000471");
                break;
            }
            case 13660: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000452);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000472, EnemyEtis, "EnemyEtis-30000472");
                break;
            }
            case 13690: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000453);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000473, EnemyEtis, "EnemyEtis-30000473");
                break;
            }
            case 13720: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000454);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000474, EnemyEtis, "EnemyEtis-30000474");
                break;
            }
            case 13750: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000455);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000475, EnemyEtis, "EnemyEtis-30000475");
                break;
            }
            case 13780: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000456);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000476, EnemyEtis, "EnemyEtis-30000476");
                break;
            }
            case 13810: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000457);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000477, EnemyEtis, "EnemyEtis-30000477");
                break;
            }
            case 13840: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000458);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000478, EnemyEtis, "EnemyEtis-30000478");
                break;
            }
            case 13870: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000459);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000479, EnemyEtis, "EnemyEtis-30000479");
                break;
            }
            case 13900: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000460);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000480, EnemyEtis, "EnemyEtis-30000480");
                break;
            }
            case 13930: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000461);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000481, EnemyEtis, "EnemyEtis-30000481");
                break;
            }
            case 13960: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000462);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000482, EnemyEtis, "EnemyEtis-30000482");
                break;
            }
            case 13990: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000463);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000483, EnemyEtis, "EnemyEtis-30000483");
                break;
            }
            case 14020: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000464);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000484, EnemyEtis, "EnemyEtis-30000484");
                break;
            }
            case 14050: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000465);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000485, EnemyEtis, "EnemyEtis-30000485");
                break;
            }
            case 14080: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000466);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000486, EnemyEtis, "EnemyEtis-30000486");
                break;
            }
            case 14110: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000467);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000487, EnemyEtis, "EnemyEtis-30000487");
                break;
            }
            case 14140: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000468);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000488, EnemyEtis, "EnemyEtis-30000488");
                break;
            }
            case 14170: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000469);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000489, EnemyEtis, "EnemyEtis-30000489");
                break;
            }
            case 14200: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000470);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000490, EnemyEtis, "EnemyEtis-30000490");
                break;
            }
            case 14230: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000471);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000491, EnemyEtis, "EnemyEtis-30000491");
                break;
            }
            case 14260: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000472);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000492, EnemyEtis, "EnemyEtis-30000492");
                break;
            }
            case 14290: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000473);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000493, EnemyEtis, "EnemyEtis-30000493");
                break;
            }
            case 14320: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000474);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000494, EnemyEtis, "EnemyEtis-30000494");
                break;
            }
            case 14350: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000475);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000495, EnemyEtis, "EnemyEtis-30000495");
                break;
            }
            case 14380: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000476);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000496, EnemyEtis, "EnemyEtis-30000496");
                break;
            }
            case 14410: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000477);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000497, EnemyEtis, "EnemyEtis-30000497");
                break;
            }
            case 14440: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000478);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000498, EnemyEtis, "EnemyEtis-30000498");
                break;
            }
            case 14470: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000479);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000499, EnemyEtis, "EnemyEtis-30000499");
                break;
            }
            case 14500: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000480);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000500, EnemyEtis, "EnemyEtis-30000500");
                break;
            }
            case 14530: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000481);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000501, EnemyEtis, "EnemyEtis-30000501");
                break;
            }
            case 14560: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000482);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000502, EnemyEtis, "EnemyEtis-30000502");
                break;
            }
            case 14590: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000483);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000503, EnemyEtis, "EnemyEtis-30000503");
                break;
            }
            case 14620: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000484);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000504, EnemyEtis, "EnemyEtis-30000504");
                break;
            }
            case 14650: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000485);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000505, EnemyEtis, "EnemyEtis-30000505");
                break;
            }
            case 14680: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000486);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000506, EnemyEtis, "EnemyEtis-30000506");
                break;
            }
            case 14710: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000487);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000507, EnemyEtis, "EnemyEtis-30000507");
                break;
            }
            case 14740: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000488);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000508, EnemyEtis, "EnemyEtis-30000508");
                break;
            }
            case 14770: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000489);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000509, EnemyEtis, "EnemyEtis-30000509");
                break;
            }
            case 14800: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000490);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000510, EnemyEtis, "EnemyEtis-30000510");
                break;
            }
            case 14830: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000491);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000511, EnemyEtis, "EnemyEtis-30000511");
                break;
            }
            case 14860: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000492);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000512, EnemyEtis, "EnemyEtis-30000512");
                break;
            }
            case 14890: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000493);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000513, EnemyEtis, "EnemyEtis-30000513");
                break;
            }
            case 14920: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000494);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000514, EnemyEtis, "EnemyEtis-30000514");
                break;
            }
            case 14950: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000495);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000515, EnemyEtis, "EnemyEtis-30000515");
                break;
            }
            case 14980: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000496);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000516, EnemyEtis, "EnemyEtis-30000516");
                break;
            }
            case 15010: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000497);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000517, EnemyEtis, "EnemyEtis-30000517");
                break;
            }
            case 15040: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000498);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000518, EnemyEtis, "EnemyEtis-30000518");
                break;
            }
            case 15070: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000499);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000519, EnemyEtis, "EnemyEtis-30000519");
                break;
            }
            case 15100: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000500);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000520, EnemyEtis, "EnemyEtis-30000520");
                break;
            }
            case 15130: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000501);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000521, EnemyEtis, "EnemyEtis-30000521");
                break;
            }
            case 15160: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000502);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000522, EnemyEtis, "EnemyEtis-30000522");
                break;
            }
            case 15190: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000503);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000523, EnemyEtis, "EnemyEtis-30000523");
                break;
            }
            case 15220: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000504);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000524, EnemyEtis, "EnemyEtis-30000524");
                break;
            }
            case 15250: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000505);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000525, EnemyEtis, "EnemyEtis-30000525");
                break;
            }
            case 15280: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000506);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000526, EnemyEtis, "EnemyEtis-30000526");
                break;
            }
            case 15310: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000507);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000527, EnemyEtis, "EnemyEtis-30000527");
                break;
            }
            case 15340: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000508);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000528, EnemyEtis, "EnemyEtis-30000528");
                break;
            }
            case 15370: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000509);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000529, EnemyEtis, "EnemyEtis-30000529");
                break;
            }
            case 15400: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000510);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000530, EnemyEtis, "EnemyEtis-30000530");
                break;
            }
            case 15430: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000511);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000531, EnemyEtis, "EnemyEtis-30000531");
                break;
            }
            case 15460: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000512);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000532, EnemyEtis, "EnemyEtis-30000532");
                break;
            }
            case 15490: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000513);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000533, EnemyEtis, "EnemyEtis-30000533");
                break;
            }
            case 15520: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000514);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000534, EnemyEtis, "EnemyEtis-30000534");
                break;
            }
            case 15550: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000515);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000535, EnemyEtis, "EnemyEtis-30000535");
                break;
            }
            case 15580: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000516);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000536, EnemyEtis, "EnemyEtis-30000536");
                break;
            }
            case 15610: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000517);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000537, EnemyEtis, "EnemyEtis-30000537");
                break;
            }
            case 15640: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000518);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000538, EnemyEtis, "EnemyEtis-30000538");
                break;
            }
            case 15670: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000519);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000539, EnemyEtis, "EnemyEtis-30000539");
                break;
            }
            case 15700: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000520);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000540, EnemyEtis, "EnemyEtis-30000540");
                break;
            }
            case 15730: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000521);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000541, EnemyEtis, "EnemyEtis-30000541");
                break;
            }
            case 15760: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000522);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000542, EnemyEtis, "EnemyEtis-30000542");
                break;
            }
            case 15790: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000523);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000543, EnemyEtis, "EnemyEtis-30000543");
                break;
            }
            case 15820: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000524);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000544, EnemyEtis, "EnemyEtis-30000544");
                break;
            }
            case 15850: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000525);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000545, EnemyEtis, "EnemyEtis-30000545");
                break;
            }
            case 15880: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000526);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000546, EnemyEtis, "EnemyEtis-30000546");
                break;
            }
            case 15910: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000527);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000547, EnemyEtis, "EnemyEtis-30000547");
                break;
            }
            case 15940: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000528);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000548, EnemyEtis, "EnemyEtis-30000548");
                break;
            }
            case 15970: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000529);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000549, EnemyEtis, "EnemyEtis-30000549");
                break;
            }
            case 16000: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000530);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000550, EnemyEtis, "EnemyEtis-30000550");
                break;
            }
            case 16030: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000531);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000551, EnemyEtis, "EnemyEtis-30000551");
                break;
            }
            case 16060: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000532);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000552, EnemyEtis, "EnemyEtis-30000552");
                break;
            }
            case 16090: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000533);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000553, EnemyEtis, "EnemyEtis-30000553");
                break;
            }
            case 16120: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000534);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000554, EnemyEtis, "EnemyEtis-30000554");
                break;
            }
            case 16150: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000535);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000555, EnemyEtis, "EnemyEtis-30000555");
                break;
            }
            case 16180: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000536);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000556, EnemyEtis, "EnemyEtis-30000556");
                break;
            }
            case 16210: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000537);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000557, EnemyEtis, "EnemyEtis-30000557");
                break;
            }
            case 16240: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000538);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000558, EnemyEtis, "EnemyEtis-30000558");
                break;
            }
            case 16270: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000539);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000559, EnemyEtis, "EnemyEtis-30000559");
                break;
            }
            case 16300: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000540);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000560, EnemyEtis, "EnemyEtis-30000560");
                break;
            }
            case 16330: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000541);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000561, EnemyEtis, "EnemyEtis-30000561");
                break;
            }
            case 16360: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000542);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000562, EnemyEtis, "EnemyEtis-30000562");
                break;
            }
            case 16390: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000543);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000563, EnemyEtis, "EnemyEtis-30000563");
                break;
            }
            case 16420: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000544);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000564, EnemyEtis, "EnemyEtis-30000564");
                break;
            }
            case 16450: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000545);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000565, EnemyEtis, "EnemyEtis-30000565");
                break;
            }
            case 16480: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000546);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000566, EnemyEtis, "EnemyEtis-30000566");
                break;
            }
            case 16510: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000547);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000567, EnemyEtis, "EnemyEtis-30000567");
                break;
            }
            case 16540: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000548);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000568, EnemyEtis, "EnemyEtis-30000568");
                break;
            }
            case 16570: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000549);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000569, EnemyEtis, "EnemyEtis-30000569");
                break;
            }
            case 16600: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000550);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000570, EnemyEtis, "EnemyEtis-30000570");
                break;
            }
            case 16630: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000551);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000571, EnemyEtis, "EnemyEtis-30000571");
                break;
            }
            case 16660: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000552);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000572, EnemyEtis, "EnemyEtis-30000572");
                break;
            }
            case 16690: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000553);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000573, EnemyEtis, "EnemyEtis-30000573");
                break;
            }
            case 16720: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000554);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000574, EnemyEtis, "EnemyEtis-30000574");
                break;
            }
            case 16750: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000555);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000575, EnemyEtis, "EnemyEtis-30000575");
                break;
            }
            case 16780: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000556);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000576, EnemyEtis, "EnemyEtis-30000576");
                break;
            }
            case 16810: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000557);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000577, EnemyEtis, "EnemyEtis-30000577");
                break;
            }
            case 16840: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000558);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000578, EnemyEtis, "EnemyEtis-30000578");
                break;
            }
            case 16870: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000559);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000579, EnemyEtis, "EnemyEtis-30000579");
                break;
            }
            case 16900: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000560);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000580, EnemyEtis, "EnemyEtis-30000580");
                break;
            }
            case 16930: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000561);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000581, EnemyEtis, "EnemyEtis-30000581");
                break;
            }
            case 16960: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000562);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000582, EnemyEtis, "EnemyEtis-30000582");
                break;
            }
            case 16990: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000563);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000583, EnemyEtis, "EnemyEtis-30000583");
                break;
            }
            case 17020: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000564);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000584, EnemyEtis, "EnemyEtis-30000584");
                break;
            }
            case 17050: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000565);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000585, EnemyEtis, "EnemyEtis-30000585");
                break;
            }
            case 17080: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000566);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000586, EnemyEtis, "EnemyEtis-30000586");
                break;
            }
            case 17110: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000567);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000587, EnemyEtis, "EnemyEtis-30000587");
                break;
            }
            case 17140: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000568);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000588, EnemyEtis, "EnemyEtis-30000588");
                break;
            }
            case 17170: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000569);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000589, EnemyEtis, "EnemyEtis-30000589");
                break;
            }
            case 17200: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000570);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000590, EnemyEtis, "EnemyEtis-30000590");
                break;
            }
            case 17230: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000571);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000591, EnemyEtis, "EnemyEtis-30000591");
                break;
            }
            case 17260: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000572);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000592, EnemyEtis, "EnemyEtis-30000592");
                break;
            }
            case 17290: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000573);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000593, EnemyEtis, "EnemyEtis-30000593");
                break;
            }
            case 17320: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000574);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000594, EnemyEtis, "EnemyEtis-30000594");
                break;
            }
            case 17350: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000575);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000595, EnemyEtis, "EnemyEtis-30000595");
                break;
            }
            case 17380: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000576);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000596, EnemyEtis, "EnemyEtis-30000596");
                break;
            }
            case 17410: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000577);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000597, EnemyEtis, "EnemyEtis-30000597");
                break;
            }
            case 17440: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000578);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000598, EnemyEtis, "EnemyEtis-30000598");
                break;
            }
            case 17470: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000579);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000599, EnemyEtis, "EnemyEtis-30000599");
                break;
            }
            case 17500: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000580);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000600, EnemyEtis, "EnemyEtis-30000600");
                break;
            }
            case 17530: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000581);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000601, EnemyEtis, "EnemyEtis-30000601");
                break;
            }
            case 17560: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000582);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000602, EnemyEtis, "EnemyEtis-30000602");
                break;
            }
            case 17590: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000583);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000603, EnemyEtis, "EnemyEtis-30000603");
                break;
            }
            case 17620: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000584);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000604, EnemyEtis, "EnemyEtis-30000604");
                break;
            }
            case 17650: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000585);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000605, EnemyEtis, "EnemyEtis-30000605");
                break;
            }
            case 17680: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000586);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000606, EnemyEtis, "EnemyEtis-30000606");
                break;
            }
            case 17710: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000587);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000607, EnemyEtis, "EnemyEtis-30000607");
                break;
            }
            case 17740: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000588);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000608, EnemyEtis, "EnemyEtis-30000608");
                break;
            }
            case 17770: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000589);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000609, EnemyEtis, "EnemyEtis-30000609");
                break;
            }
            case 17800: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000590);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000610, EnemyEtis, "EnemyEtis-30000610");
                break;
            }
            case 17830: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000591);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000611, EnemyEtis, "EnemyEtis-30000611");
                break;
            }
            case 17860: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000592);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000612, EnemyEtis, "EnemyEtis-30000612");
                break;
            }
            case 17890: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000593);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000613, EnemyEtis, "EnemyEtis-30000613");
                break;
            }
            case 17920: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000594);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000614, EnemyEtis, "EnemyEtis-30000614");
                break;
            }
            case 17950: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000595);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000615, EnemyEtis, "EnemyEtis-30000615");
                break;
            }
            case 17980: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000596);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000616, EnemyEtis, "EnemyEtis-30000616");
                break;
            }
            case 18010: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000597);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000617, EnemyEtis, "EnemyEtis-30000617");
                break;
            }
            case 18040: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000598);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000618, EnemyEtis, "EnemyEtis-30000618");
                break;
            }
            case 18070: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000599);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000619, EnemyEtis, "EnemyEtis-30000619");
                break;
            }
            case 18100: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000600);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000620, EnemyEtis, "EnemyEtis-30000620");
                break;
            }
            case 18130: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000601);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000621, EnemyEtis, "EnemyEtis-30000621");
                break;
            }
            case 18160: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000602);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000622, EnemyEtis, "EnemyEtis-30000622");
                break;
            }
            case 18190: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000603);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000623, EnemyEtis, "EnemyEtis-30000623");
                break;
            }
            case 18220: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000604);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000624, EnemyEtis, "EnemyEtis-30000624");
                break;
            }
            case 18250: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000605);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000625, EnemyEtis, "EnemyEtis-30000625");
                break;
            }
            case 18280: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000606);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000626, EnemyEtis, "EnemyEtis-30000626");
                break;
            }
            case 18310: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000607);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000627, EnemyEtis, "EnemyEtis-30000627");
                break;
            }
            case 18340: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000608);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000628, EnemyEtis, "EnemyEtis-30000628");
                break;
            }
            case 18370: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000609);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000629, EnemyEtis, "EnemyEtis-30000629");
                break;
            }
            case 18400: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000610);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000630, EnemyEtis, "EnemyEtis-30000630");
                break;
            }
            case 18430: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000611);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000631, EnemyEtis, "EnemyEtis-30000631");
                break;
            }
            case 18460: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000612);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000632, EnemyEtis, "EnemyEtis-30000632");
                break;
            }
            case 18490: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000613);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000633, EnemyEtis, "EnemyEtis-30000633");
                break;
            }
            case 18520: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000614);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000634, EnemyEtis, "EnemyEtis-30000634");
                break;
            }
            case 18550: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000615);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000635, EnemyEtis, "EnemyEtis-30000635");
                break;
            }
            case 18580: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000616);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000636, EnemyEtis, "EnemyEtis-30000636");
                break;
            }
            case 18610: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000617);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000637, EnemyEtis, "EnemyEtis-30000637");
                break;
            }
            case 18640: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000618);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000638, EnemyEtis, "EnemyEtis-30000638");
                break;
            }
            case 18670: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000619);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000639, EnemyEtis, "EnemyEtis-30000639");
                break;
            }
            case 18700: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000620);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000640, EnemyEtis, "EnemyEtis-30000640");
                break;
            }
            case 18730: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000621);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000641, EnemyEtis, "EnemyEtis-30000641");
                break;
            }
            case 18760: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000622);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000642, EnemyEtis, "EnemyEtis-30000642");
                break;
            }
            case 18790: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000623);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000643, EnemyEtis, "EnemyEtis-30000643");
                break;
            }
            case 18820: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000624);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000644, EnemyEtis, "EnemyEtis-30000644");
                break;
            }
            case 18850: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000625);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000645, EnemyEtis, "EnemyEtis-30000645");
                break;
            }
            case 18880: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000626);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000646, EnemyEtis, "EnemyEtis-30000646");
                break;
            }
            case 18910: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000627);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000647, EnemyEtis, "EnemyEtis-30000647");
                break;
            }
            case 18940: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000628);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000648, EnemyEtis, "EnemyEtis-30000648");
                break;
            }
            case 18970: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000629);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000649, EnemyEtis, "EnemyEtis-30000649");
                break;
            }
            case 19000: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000630);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000650, EnemyEtis, "EnemyEtis-30000650");
                break;
            }
            case 19030: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000631);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000651, EnemyEtis, "EnemyEtis-30000651");
                break;
            }
            case 19060: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000632);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000652, EnemyEtis, "EnemyEtis-30000652");
                break;
            }
            case 19090: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000633);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000653, EnemyEtis, "EnemyEtis-30000653");
                break;
            }
            case 19120: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000634);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000654, EnemyEtis, "EnemyEtis-30000654");
                break;
            }
            case 19150: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000635);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000655, EnemyEtis, "EnemyEtis-30000655");
                break;
            }
            case 19180: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000636);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000656, EnemyEtis, "EnemyEtis-30000656");
                break;
            }
            case 19210: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000637);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000657, EnemyEtis, "EnemyEtis-30000657");
                break;
            }
            case 19240: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000638);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000658, EnemyEtis, "EnemyEtis-30000658");
                break;
            }
            case 19270: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000639);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000659, EnemyEtis, "EnemyEtis-30000659");
                break;
            }
            case 19300: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000640);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000660, EnemyEtis, "EnemyEtis-30000660");
                break;
            }
            case 19330: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000641);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000661, EnemyEtis, "EnemyEtis-30000661");
                break;
            }
            case 19360: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000642);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000662, EnemyEtis, "EnemyEtis-30000662");
                break;
            }
            case 19390: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000643);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000663, EnemyEtis, "EnemyEtis-30000663");
                break;
            }
            case 19420: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000644);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000664, EnemyEtis, "EnemyEtis-30000664");
                break;
            }
            case 19450: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000645);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000665, EnemyEtis, "EnemyEtis-30000665");
                break;
            }
            case 19480: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000646);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000666, EnemyEtis, "EnemyEtis-30000666");
                break;
            }
            case 19510: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000647);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000667, EnemyEtis, "EnemyEtis-30000667");
                break;
            }
            case 19540: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000648);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000668, EnemyEtis, "EnemyEtis-30000668");
                break;
            }
            case 19570: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000649);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000669, EnemyEtis, "EnemyEtis-30000669");
                break;
            }
            case 19600: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000650);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000670, EnemyEtis, "EnemyEtis-30000670");
                break;
            }
            case 19630: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000651);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000671, EnemyEtis, "EnemyEtis-30000671");
                break;
            }
            case 19660: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000652);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000672, EnemyEtis, "EnemyEtis-30000672");
                break;
            }
            case 19690: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000653);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000673, EnemyEtis, "EnemyEtis-30000673");
                break;
            }
            case 19720: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000654);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000674, EnemyEtis, "EnemyEtis-30000674");
                break;
            }
            case 19750: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000655);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000675, EnemyEtis, "EnemyEtis-30000675");
                break;
            }
            case 19780: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000656);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000676, EnemyEtis, "EnemyEtis-30000676");
                break;
            }
            case 19810: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000657);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000677, EnemyEtis, "EnemyEtis-30000677");
                break;
            }
            case 19840: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000658);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000678, EnemyEtis, "EnemyEtis-30000678");
                break;
            }
            case 19870: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000659);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000679, EnemyEtis, "EnemyEtis-30000679");
                break;
            }
            case 19900: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000660);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000680, EnemyEtis, "EnemyEtis-30000680");
                break;
            }
            case 19930: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000661);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000681, EnemyEtis, "EnemyEtis-30000681");
                break;
            }
            case 19960: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000662);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000682, EnemyEtis, "EnemyEtis-30000682");
                break;
            }
            case 19990: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000663);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000683, EnemyEtis, "EnemyEtis-30000683");
                break;
            }
            case 20020: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000664);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000684, EnemyEtis, "EnemyEtis-30000684");
                break;
            }
            case 20050: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000665);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000685, EnemyEtis, "EnemyEtis-30000685");
                break;
            }
            case 20080: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000666);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000686, EnemyEtis, "EnemyEtis-30000686");
                break;
            }
            case 20110: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000667);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000687, EnemyEtis, "EnemyEtis-30000687");
                break;
            }
            case 20140: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000668);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000688, EnemyEtis, "EnemyEtis-30000688");
                break;
            }
            case 20170: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000669);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000689, EnemyEtis, "EnemyEtis-30000689");
                break;
            }
            case 20200: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000670);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000690, EnemyEtis, "EnemyEtis-30000690");
                break;
            }
            case 20230: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000671);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000691, EnemyEtis, "EnemyEtis-30000691");
                break;
            }
            case 20260: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000672);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000692, EnemyEtis, "EnemyEtis-30000692");
                break;
            }
            case 20290: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000673);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000693, EnemyEtis, "EnemyEtis-30000693");
                break;
            }
            case 20320: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000674);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000694, EnemyEtis, "EnemyEtis-30000694");
                break;
            }
            case 20350: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000675);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000695, EnemyEtis, "EnemyEtis-30000695");
                break;
            }
            case 20380: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000676);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000696, EnemyEtis, "EnemyEtis-30000696");
                break;
            }
            case 20410: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000677);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000697, EnemyEtis, "EnemyEtis-30000697");
                break;
            }
            case 20440: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000678);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000698, EnemyEtis, "EnemyEtis-30000698");
                break;
            }
            case 20470: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000679);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000699, EnemyEtis, "EnemyEtis-30000699");
                break;
            }
            case 20500: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000680);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000700, EnemyEtis, "EnemyEtis-30000700");
                break;
            }
            case 20530: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000681);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000701, EnemyEtis, "EnemyEtis-30000701");
                break;
            }
            case 20560: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000682);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000702, EnemyEtis, "EnemyEtis-30000702");
                break;
            }
            case 20590: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000683);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000703, EnemyEtis, "EnemyEtis-30000703");
                break;
            }
            case 20620: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000684);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000704, EnemyEtis, "EnemyEtis-30000704");
                break;
            }
            case 20650: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000685);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000705, EnemyEtis, "EnemyEtis-30000705");
                break;
            }
            case 20680: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000686);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000706, EnemyEtis, "EnemyEtis-30000706");
                break;
            }
            case 20710: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000687);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000707, EnemyEtis, "EnemyEtis-30000707");
                break;
            }
            case 20740: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000688);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000708, EnemyEtis, "EnemyEtis-30000708");
                break;
            }
            case 20770: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000689);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000709, EnemyEtis, "EnemyEtis-30000709");
                break;
            }
            case 20800: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000690);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000710, EnemyEtis, "EnemyEtis-30000710");
                break;
            }
            case 20830: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000691);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000711, EnemyEtis, "EnemyEtis-30000711");
                break;
            }
            case 20860: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000692);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000712, EnemyEtis, "EnemyEtis-30000712");
                break;
            }
            case 20890: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000693);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000713, EnemyEtis, "EnemyEtis-30000713");
                break;
            }
            case 20920: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000694);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000714, EnemyEtis, "EnemyEtis-30000714");
                break;
            }
            case 20950: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000695);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000715, EnemyEtis, "EnemyEtis-30000715");
                break;
            }
            case 20980: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000696);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000716, EnemyEtis, "EnemyEtis-30000716");
                break;
            }
            case 21010: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000697);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000717, EnemyEtis, "EnemyEtis-30000717");
                break;
            }
            case 21040: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000698);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000718, EnemyEtis, "EnemyEtis-30000718");
                break;
            }
            case 21070: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000699);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000719, EnemyEtis, "EnemyEtis-30000719");
                break;
            }
            case 21100: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000700);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000720, EnemyEtis, "EnemyEtis-30000720");
                break;
            }
            case 21130: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000701);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000721, EnemyEtis, "EnemyEtis-30000721");
                break;
            }
            case 21160: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000702);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000722, EnemyEtis, "EnemyEtis-30000722");
                break;
            }
            case 21190: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000703);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000723, EnemyEtis, "EnemyEtis-30000723");
                break;
            }
            case 21220: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000704);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000724, EnemyEtis, "EnemyEtis-30000724");
                break;
            }
            case 21250: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000705);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000725, EnemyEtis, "EnemyEtis-30000725");
                break;
            }
            case 21280: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000706);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000726, EnemyEtis, "EnemyEtis-30000726");
                break;
            }
            case 21310: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000707);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000727, EnemyEtis, "EnemyEtis-30000727");
                break;
            }
            case 21340: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000708);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000728, EnemyEtis, "EnemyEtis-30000728");
                break;
            }
            case 21370: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000709);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000729, EnemyEtis, "EnemyEtis-30000729");
                break;
            }
            case 21400: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000710);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000730, EnemyEtis, "EnemyEtis-30000730");
                break;
            }
            case 21430: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000711);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000731, EnemyEtis, "EnemyEtis-30000731");
                break;
            }
            case 21460: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000712);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000732, EnemyEtis, "EnemyEtis-30000732");
                break;
            }
            case 21490: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000713);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000733, EnemyEtis, "EnemyEtis-30000733");
                break;
            }
            case 21520: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000714);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000734, EnemyEtis, "EnemyEtis-30000734");
                break;
            }
            case 21550: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000715);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000735, EnemyEtis, "EnemyEtis-30000735");
                break;
            }
            case 21580: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000716);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000736, EnemyEtis, "EnemyEtis-30000736");
                break;
            }
            case 21610: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000717);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000737, EnemyEtis, "EnemyEtis-30000737");
                break;
            }
            case 21640: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000718);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000738, EnemyEtis, "EnemyEtis-30000738");
                break;
            }
            case 21670: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000719);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000739, EnemyEtis, "EnemyEtis-30000739");
                break;
            }
            case 21700: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000720);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000740, EnemyEtis, "EnemyEtis-30000740");
                break;
            }
            case 21730: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000721);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000741, EnemyEtis, "EnemyEtis-30000741");
                break;
            }
            case 21760: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000722);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000742, EnemyEtis, "EnemyEtis-30000742");
                break;
            }
            case 21790: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000723);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000743, EnemyEtis, "EnemyEtis-30000743");
                break;
            }
            case 21820: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000724);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000744, EnemyEtis, "EnemyEtis-30000744");
                break;
            }
            case 21850: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000725);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000745, EnemyEtis, "EnemyEtis-30000745");
                break;
            }
            case 21880: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000726);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000746, EnemyEtis, "EnemyEtis-30000746");
                break;
            }
            case 21910: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000727);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000747, EnemyEtis, "EnemyEtis-30000747");
                break;
            }
            case 21940: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000728);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000748, EnemyEtis, "EnemyEtis-30000748");
                break;
            }
            case 21970: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000729);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000749, EnemyEtis, "EnemyEtis-30000749");
                break;
            }
            case 22000: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000730);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000750, EnemyEtis, "EnemyEtis-30000750");
                break;
            }
            case 22030: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000731);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000751, EnemyEtis, "EnemyEtis-30000751");
                break;
            }
            case 22060: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000732);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000752, EnemyEtis, "EnemyEtis-30000752");
                break;
            }
            case 22090: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000733);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000753, EnemyEtis, "EnemyEtis-30000753");
                break;
            }
            case 22120: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000734);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000754, EnemyEtis, "EnemyEtis-30000754");
                break;
            }
            case 22150: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000735);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000755, EnemyEtis, "EnemyEtis-30000755");
                break;
            }
            case 22180: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000736);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000756, EnemyEtis, "EnemyEtis-30000756");
                break;
            }
            case 22210: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000737);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000757, EnemyEtis, "EnemyEtis-30000757");
                break;
            }
            case 22240: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000738);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000758, EnemyEtis, "EnemyEtis-30000758");
                break;
            }
            case 22270: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000739);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000759, EnemyEtis, "EnemyEtis-30000759");
                break;
            }
            case 22300: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000740);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000760, EnemyEtis, "EnemyEtis-30000760");
                break;
            }
            case 22330: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000741);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000761, EnemyEtis, "EnemyEtis-30000761");
                break;
            }
            case 22360: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000742);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000762, EnemyEtis, "EnemyEtis-30000762");
                break;
            }
            case 22390: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000743);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000763, EnemyEtis, "EnemyEtis-30000763");
                break;
            }
            case 22420: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000744);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000764, EnemyEtis, "EnemyEtis-30000764");
                break;
            }
            case 22450: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000745);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000765, EnemyEtis, "EnemyEtis-30000765");
                break;
            }
            case 22480: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000746);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000766, EnemyEtis, "EnemyEtis-30000766");
                break;
            }
            case 22510: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000747);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000767, EnemyEtis, "EnemyEtis-30000767");
                break;
            }
            case 22540: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000748);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000768, EnemyEtis, "EnemyEtis-30000768");
                break;
            }
            case 22570: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000749);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000769, EnemyEtis, "EnemyEtis-30000769");
                break;
            }
            case 22600: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000750);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000770, EnemyEtis, "EnemyEtis-30000770");
                break;
            }
            case 22630: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000751);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000771, EnemyEtis, "EnemyEtis-30000771");
                break;
            }
            case 22660: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000752);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000772, EnemyEtis, "EnemyEtis-30000772");
                break;
            }
            case 22690: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000753);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000773, EnemyEtis, "EnemyEtis-30000773");
                break;
            }
            case 22720: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000754);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000774, EnemyEtis, "EnemyEtis-30000774");
                break;
            }
            case 22750: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000755);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000775, EnemyEtis, "EnemyEtis-30000775");
                break;
            }
            case 22780: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000756);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000776, EnemyEtis, "EnemyEtis-30000776");
                break;
            }
            case 22810: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000757);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000777, EnemyEtis, "EnemyEtis-30000777");
                break;
            }
            case 22840: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000758);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000778, EnemyEtis, "EnemyEtis-30000778");
                break;
            }
            case 22870: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000759);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000779, EnemyEtis, "EnemyEtis-30000779");
                break;
            }
            case 22900: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000760);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000780, EnemyEtis, "EnemyEtis-30000780");
                break;
            }
            case 22930: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000761);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000781, EnemyEtis, "EnemyEtis-30000781");
                break;
            }
            case 22960: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000762);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000782, EnemyEtis, "EnemyEtis-30000782");
                break;
            }
            case 22990: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000763);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000783, EnemyEtis, "EnemyEtis-30000783");
                break;
            }
            case 23020: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000764);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000784, EnemyEtis, "EnemyEtis-30000784");
                break;
            }
            case 23050: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000765);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000785, EnemyEtis, "EnemyEtis-30000785");
                break;
            }
            case 23080: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000766);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000786, EnemyEtis, "EnemyEtis-30000786");
                break;
            }
            case 23110: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000767);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000787, EnemyEtis, "EnemyEtis-30000787");
                break;
            }
            case 23140: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000768);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000788, EnemyEtis, "EnemyEtis-30000788");
                break;
            }
            case 23170: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000769);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000789, EnemyEtis, "EnemyEtis-30000789");
                break;
            }
            case 23200: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000770);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000790, EnemyEtis, "EnemyEtis-30000790");
                break;
            }
            case 23230: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000771);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000791, EnemyEtis, "EnemyEtis-30000791");
                break;
            }
            case 23260: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000772);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000792, EnemyEtis, "EnemyEtis-30000792");
                break;
            }
            case 23290: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000773);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000793, EnemyEtis, "EnemyEtis-30000793");
                break;
            }
            case 23320: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000774);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000794, EnemyEtis, "EnemyEtis-30000794");
                break;
            }
            case 23350: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000775);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000795, EnemyEtis, "EnemyEtis-30000795");
                break;
            }
            case 23380: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000776);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000796, EnemyEtis, "EnemyEtis-30000796");
                break;
            }
            case 23410: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000777);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000797, EnemyEtis, "EnemyEtis-30000797");
                break;
            }
            case 23440: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000778);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000798, EnemyEtis, "EnemyEtis-30000798");
                break;
            }
            case 23470: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000779);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000799, EnemyEtis, "EnemyEtis-30000799");
                break;
            }
            case 23500: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000780);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000800, EnemyEtis, "EnemyEtis-30000800");
                break;
            }
            case 23530: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000781);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000801, EnemyEtis, "EnemyEtis-30000801");
                break;
            }
            case 23560: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000782);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000802, EnemyEtis, "EnemyEtis-30000802");
                break;
            }
            case 23590: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000783);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000803, EnemyEtis, "EnemyEtis-30000803");
                break;
            }
            case 23620: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000784);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000804, EnemyEtis, "EnemyEtis-30000804");
                break;
            }
            case 23650: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000785);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000805, EnemyEtis, "EnemyEtis-30000805");
                break;
            }
            case 23680: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000786);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000806, EnemyEtis, "EnemyEtis-30000806");
                break;
            }
            case 23710: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000787);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000807, EnemyEtis, "EnemyEtis-30000807");
                break;
            }
            case 23740: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000788);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000808, EnemyEtis, "EnemyEtis-30000808");
                break;
            }
            case 23770: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000789);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000809, EnemyEtis, "EnemyEtis-30000809");
                break;
            }
            case 23800: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000790);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000810, EnemyEtis, "EnemyEtis-30000810");
                break;
            }
            case 23830: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000791);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000811, EnemyEtis, "EnemyEtis-30000811");
                break;
            }
            case 23860: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000792);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000812, EnemyEtis, "EnemyEtis-30000812");
                break;
            }
            case 23890: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000793);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000813, EnemyEtis, "EnemyEtis-30000813");
                break;
            }
            case 23920: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000794);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000814, EnemyEtis, "EnemyEtis-30000814");
                break;
            }
            case 23950: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000795);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000815, EnemyEtis, "EnemyEtis-30000815");
                break;
            }
            case 23980: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000796);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000816, EnemyEtis, "EnemyEtis-30000816");
                break;
            }
            case 24010: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000797);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000817, EnemyEtis, "EnemyEtis-30000817");
                break;
            }
            case 24040: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000798);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000818, EnemyEtis, "EnemyEtis-30000818");
                break;
            }
            case 24070: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000799);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000819, EnemyEtis, "EnemyEtis-30000819");
                break;
            }
            case 24100: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000800);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000820, EnemyEtis, "EnemyEtis-30000820");
                break;
            }
            case 24130: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000801);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000821, EnemyEtis, "EnemyEtis-30000821");
                break;
            }
            case 24160: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000802);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000822, EnemyEtis, "EnemyEtis-30000822");
                break;
            }
            case 24190: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000803);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000823, EnemyEtis, "EnemyEtis-30000823");
                break;
            }
            case 24220: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000804);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000824, EnemyEtis, "EnemyEtis-30000824");
                break;
            }
            case 24250: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000805);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000825, EnemyEtis, "EnemyEtis-30000825");
                break;
            }
            case 24280: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000806);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000826, EnemyEtis, "EnemyEtis-30000826");
                break;
            }
            case 24310: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000807);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000827, EnemyEtis, "EnemyEtis-30000827");
                break;
            }
            case 24340: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000808);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000828, EnemyEtis, "EnemyEtis-30000828");
                break;
            }
            case 24370: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000809);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000829, EnemyEtis, "EnemyEtis-30000829");
                break;
            }
            case 24400: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000810);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000830, EnemyEtis, "EnemyEtis-30000830");
                break;
            }
            case 24430: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000811);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000831, EnemyEtis, "EnemyEtis-30000831");
                break;
            }
            case 24460: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000812);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000832, EnemyEtis, "EnemyEtis-30000832");
                break;
            }
            case 24490: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000813);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000833, EnemyEtis, "EnemyEtis-30000833");
                break;
            }
            case 24520: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000814);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000834, EnemyEtis, "EnemyEtis-30000834");
                break;
            }
            case 24550: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000815);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000835, EnemyEtis, "EnemyEtis-30000835");
                break;
            }
            case 24580: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000816);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000836, EnemyEtis, "EnemyEtis-30000836");
                break;
            }
            case 24610: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000817);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000837, EnemyEtis, "EnemyEtis-30000837");
                break;
            }
            case 24640: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000818);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000838, EnemyEtis, "EnemyEtis-30000838");
                break;
            }
            case 24670: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000819);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000839, EnemyEtis, "EnemyEtis-30000839");
                break;
            }
            case 24700: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000820);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000840, EnemyEtis, "EnemyEtis-30000840");
                break;
            }
            case 24730: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000821);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000841, EnemyEtis, "EnemyEtis-30000841");
                break;
            }
            case 24760: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000822);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000842, EnemyEtis, "EnemyEtis-30000842");
                break;
            }
            case 24790: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000823);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000843, EnemyEtis, "EnemyEtis-30000843");
                break;
            }
            case 24820: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000824);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000844, EnemyEtis, "EnemyEtis-30000844");
                break;
            }
            case 24850: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000825);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000845, EnemyEtis, "EnemyEtis-30000845");
                break;
            }
            case 24880: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000826);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000846, EnemyEtis, "EnemyEtis-30000846");
                break;
            }
            case 24910: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000827);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000847, EnemyEtis, "EnemyEtis-30000847");
                break;
            }
            case 24940: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000828);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000848, EnemyEtis, "EnemyEtis-30000848");
                break;
            }
            case 24970: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000829);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000849, EnemyEtis, "EnemyEtis-30000849");
                break;
            }
            case 25000: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000830);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000850, EnemyEtis, "EnemyEtis-30000850");
                break;
            }
            case 25030: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000831);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000851, EnemyEtis, "EnemyEtis-30000851");
                break;
            }
            case 25060: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000832);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000852, EnemyEtis, "EnemyEtis-30000852");
                break;
            }
            case 25090: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000833);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000853, EnemyEtis, "EnemyEtis-30000853");
                break;
            }
            case 25120: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000834);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000854, EnemyEtis, "EnemyEtis-30000854");
                break;
            }
            case 25150: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000835);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000855, EnemyEtis, "EnemyEtis-30000855");
                break;
            }
            case 25180: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000836);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000856, EnemyEtis, "EnemyEtis-30000856");
                break;
            }
            case 25210: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000837);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000857, EnemyEtis, "EnemyEtis-30000857");
                break;
            }
            case 25240: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000838);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000858, EnemyEtis, "EnemyEtis-30000858");
                break;
            }
            case 25270: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000839);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000859, EnemyEtis, "EnemyEtis-30000859");
                break;
            }
            case 25300: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000840);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000860, EnemyEtis, "EnemyEtis-30000860");
                break;
            }
            case 25330: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000841);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000861, EnemyEtis, "EnemyEtis-30000861");
                break;
            }
            case 25360: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000842);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000862, EnemyEtis, "EnemyEtis-30000862");
                break;
            }
            case 25390: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000843);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000863, EnemyEtis, "EnemyEtis-30000863");
                break;
            }
            case 25420: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000844);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000864, EnemyEtis, "EnemyEtis-30000864");
                break;
            }
            case 25450: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000845);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000865, EnemyEtis, "EnemyEtis-30000865");
                break;
            }
            case 25480: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000846);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000866, EnemyEtis, "EnemyEtis-30000866");
                break;
            }
            case 25510: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000847);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000867, EnemyEtis, "EnemyEtis-30000867");
                break;
            }
            case 25540: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000848);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000868, EnemyEtis, "EnemyEtis-30000868");
                break;
            }
            case 25570: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000849);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000869, EnemyEtis, "EnemyEtis-30000869");
                break;
            }
            case 25600: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000850);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000870, EnemyEtis, "EnemyEtis-30000870");
                break;
            }
            case 25630: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000851);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000871, EnemyEtis, "EnemyEtis-30000871");
                break;
            }
            case 25660: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000852);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000872, EnemyEtis, "EnemyEtis-30000872");
                break;
            }
            case 25690: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000853);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000873, EnemyEtis, "EnemyEtis-30000873");
                break;
            }
            case 25720: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000854);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000874, EnemyEtis, "EnemyEtis-30000874");
                break;
            }
            case 25750: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000855);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000875, EnemyEtis, "EnemyEtis-30000875");
                break;
            }
            case 25780: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000856);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000876, EnemyEtis, "EnemyEtis-30000876");
                break;
            }
            case 25810: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000857);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000877, EnemyEtis, "EnemyEtis-30000877");
                break;
            }
            case 25840: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000858);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000878, EnemyEtis, "EnemyEtis-30000878");
                break;
            }
            case 25870: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000859);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000879, EnemyEtis, "EnemyEtis-30000879");
                break;
            }
            case 25900: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000860);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000880, EnemyEtis, "EnemyEtis-30000880");
                break;
            }
            case 25930: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000861);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000881, EnemyEtis, "EnemyEtis-30000881");
                break;
            }
            case 25960: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000862);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000882, EnemyEtis, "EnemyEtis-30000882");
                break;
            }
            case 25990: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000863);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000883, EnemyEtis, "EnemyEtis-30000883");
                break;
            }
            case 26020: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000864);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000884, EnemyEtis, "EnemyEtis-30000884");
                break;
            }
            case 26050: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000865);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000885, EnemyEtis, "EnemyEtis-30000885");
                break;
            }
            case 26080: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000866);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000886, EnemyEtis, "EnemyEtis-30000886");
                break;
            }
            case 26110: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000867);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000887, EnemyEtis, "EnemyEtis-30000887");
                break;
            }
            case 26140: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000868);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000888, EnemyEtis, "EnemyEtis-30000888");
                break;
            }
            case 26170: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000869);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000889, EnemyEtis, "EnemyEtis-30000889");
                break;
            }
            case 26200: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000870);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000890, EnemyEtis, "EnemyEtis-30000890");
                break;
            }
            case 26230: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000871);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000891, EnemyEtis, "EnemyEtis-30000891");
                break;
            }
            case 26260: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000872);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000892, EnemyEtis, "EnemyEtis-30000892");
                break;
            }
            case 26290: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000873);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000893, EnemyEtis, "EnemyEtis-30000893");
                break;
            }
            case 26320: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000874);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000894, EnemyEtis, "EnemyEtis-30000894");
                break;
            }
            case 26350: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000875);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000895, EnemyEtis, "EnemyEtis-30000895");
                break;
            }
            case 26380: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000876);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000896, EnemyEtis, "EnemyEtis-30000896");
                break;
            }
            case 26410: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000877);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000897, EnemyEtis, "EnemyEtis-30000897");
                break;
            }
            case 26440: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000878);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000898, EnemyEtis, "EnemyEtis-30000898");
                break;
            }
            case 26470: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000879);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000899, EnemyEtis, "EnemyEtis-30000899");
                break;
            }
            case 26500: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000880);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000900, EnemyEtis, "EnemyEtis-30000900");
                break;
            }
            case 26530: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000881);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000901, EnemyEtis, "EnemyEtis-30000901");
                break;
            }
            case 26560: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000882);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000902, EnemyEtis, "EnemyEtis-30000902");
                break;
            }
            case 26590: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000883);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000903, EnemyEtis, "EnemyEtis-30000903");
                break;
            }
            case 26620: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000884);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000904, EnemyEtis, "EnemyEtis-30000904");
                break;
            }
            case 26650: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000885);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000905, EnemyEtis, "EnemyEtis-30000905");
                break;
            }
            case 26680: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000886);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000906, EnemyEtis, "EnemyEtis-30000906");
                break;
            }
            case 26710: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000887);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000907, EnemyEtis, "EnemyEtis-30000907");
                break;
            }
            case 26740: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000888);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000908, EnemyEtis, "EnemyEtis-30000908");
                break;
            }
            case 26770: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000889);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000909, EnemyEtis, "EnemyEtis-30000909");
                break;
            }
            case 26800: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000890);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000910, EnemyEtis, "EnemyEtis-30000910");
                break;
            }
            case 26830: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000891);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000911, EnemyEtis, "EnemyEtis-30000911");
                break;
            }
            case 26860: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000892);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000912, EnemyEtis, "EnemyEtis-30000912");
                break;
            }
            case 26890: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000893);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000913, EnemyEtis, "EnemyEtis-30000913");
                break;
            }
            case 26920: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000894);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000914, EnemyEtis, "EnemyEtis-30000914");
                break;
            }
            case 26950: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000895);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000915, EnemyEtis, "EnemyEtis-30000915");
                break;
            }
            case 26980: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000896);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000916, EnemyEtis, "EnemyEtis-30000916");
                break;
            }
            case 27010: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000897);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000917, EnemyEtis, "EnemyEtis-30000917");
                break;
            }
            case 27040: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000898);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000918, EnemyEtis, "EnemyEtis-30000918");
                break;
            }
            case 27070: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000899);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000919, EnemyEtis, "EnemyEtis-30000919");
                break;
            }
            case 27100: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000900);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000920, EnemyEtis, "EnemyEtis-30000920");
                break;
            }
            case 27130: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000901);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000921, EnemyEtis, "EnemyEtis-30000921");
                break;
            }
            case 27160: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000902);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000922, EnemyEtis, "EnemyEtis-30000922");
                break;
            }
            case 27190: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000903);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000923, EnemyEtis, "EnemyEtis-30000923");
                break;
            }
            case 27220: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000904);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000924, EnemyEtis, "EnemyEtis-30000924");
                break;
            }
            case 27250: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000905);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000925, EnemyEtis, "EnemyEtis-30000925");
                break;
            }
            case 27280: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000906);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000926, EnemyEtis, "EnemyEtis-30000926");
                break;
            }
            case 27310: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000907);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000927, EnemyEtis, "EnemyEtis-30000927");
                break;
            }
            case 27340: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000908);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000928, EnemyEtis, "EnemyEtis-30000928");
                break;
            }
            case 27370: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000909);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000929, EnemyEtis, "EnemyEtis-30000929");
                break;
            }
            case 27400: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000910);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000930, EnemyEtis, "EnemyEtis-30000930");
                break;
            }
            case 27430: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000911);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000931, EnemyEtis, "EnemyEtis-30000931");
                break;
            }
            case 27460: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000912);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000932, EnemyEtis, "EnemyEtis-30000932");
                break;
            }
            case 27490: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000913);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000933, EnemyEtis, "EnemyEtis-30000933");
                break;
            }
            case 27520: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000914);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000934, EnemyEtis, "EnemyEtis-30000934");
                break;
            }
            case 27550: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000915);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000935, EnemyEtis, "EnemyEtis-30000935");
                break;
            }
            case 27580: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000916);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000936, EnemyEtis, "EnemyEtis-30000936");
                break;
            }
            case 27610: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000917);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000937, EnemyEtis, "EnemyEtis-30000937");
                break;
            }
            case 27640: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000918);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000938, EnemyEtis, "EnemyEtis-30000938");
                break;
            }
            case 27670: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000919);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000939, EnemyEtis, "EnemyEtis-30000939");
                break;
            }
            case 27700: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000920);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000940, EnemyEtis, "EnemyEtis-30000940");
                break;
            }
            case 27730: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000921);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000941, EnemyEtis, "EnemyEtis-30000941");
                break;
            }
            case 27760: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000922);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000942, EnemyEtis, "EnemyEtis-30000942");
                break;
            }
            case 27790: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000923);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000943, EnemyEtis, "EnemyEtis-30000943");
                break;
            }
            case 27820: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000924);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000944, EnemyEtis, "EnemyEtis-30000944");
                break;
            }
            case 27850: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000925);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000945, EnemyEtis, "EnemyEtis-30000945");
                break;
            }
            case 27880: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000926);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000946, EnemyEtis, "EnemyEtis-30000946");
                break;
            }
            case 27910: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000927);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000947, EnemyEtis, "EnemyEtis-30000947");
                break;
            }
            case 27940: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000928);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000948, EnemyEtis, "EnemyEtis-30000948");
                break;
            }
            case 27970: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000929);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000949, EnemyEtis, "EnemyEtis-30000949");
                break;
            }
            case 28000: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000930);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000950, EnemyEtis, "EnemyEtis-30000950");
                break;
            }
            case 28030: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000931);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000951, EnemyEtis, "EnemyEtis-30000951");
                break;
            }
            case 28060: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000932);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000952, EnemyEtis, "EnemyEtis-30000952");
                break;
            }
            case 28090: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000933);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000953, EnemyEtis, "EnemyEtis-30000953");
                break;
            }
            case 28120: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000934);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000954, EnemyEtis, "EnemyEtis-30000954");
                break;
            }
            case 28150: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000935);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000955, EnemyEtis, "EnemyEtis-30000955");
                break;
            }
            case 28180: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000936);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000956, EnemyEtis, "EnemyEtis-30000956");
                break;
            }
            case 28210: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000937);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000957, EnemyEtis, "EnemyEtis-30000957");
                break;
            }
            case 28240: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000938);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000958, EnemyEtis, "EnemyEtis-30000958");
                break;
            }
            case 28270: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000939);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000959, EnemyEtis, "EnemyEtis-30000959");
                break;
            }
            case 28300: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000940);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000960, EnemyEtis, "EnemyEtis-30000960");
                break;
            }
            case 28330: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000941);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000961, EnemyEtis, "EnemyEtis-30000961");
                break;
            }
            case 28360: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000942);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000962, EnemyEtis, "EnemyEtis-30000962");
                break;
            }
            case 28390: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000943);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000963, EnemyEtis, "EnemyEtis-30000963");
                break;
            }
            case 28420: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000944);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000964, EnemyEtis, "EnemyEtis-30000964");
                break;
            }
            case 28450: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000945);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000965, EnemyEtis, "EnemyEtis-30000965");
                break;
            }
            case 28480: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000946);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000966, EnemyEtis, "EnemyEtis-30000966");
                break;
            }
            case 28510: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000947);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000967, EnemyEtis, "EnemyEtis-30000967");
                break;
            }
            case 28540: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000948);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000968, EnemyEtis, "EnemyEtis-30000968");
                break;
            }
            case 28570: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000949);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000969, EnemyEtis, "EnemyEtis-30000969");
                break;
            }
            case 28600: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000950);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000970, EnemyEtis, "EnemyEtis-30000970");
                break;
            }
            case 28630: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000951);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000971, EnemyEtis, "EnemyEtis-30000971");
                break;
            }
            case 28660: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000952);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000972, EnemyEtis, "EnemyEtis-30000972");
                break;
            }
            case 28690: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000953);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000973, EnemyEtis, "EnemyEtis-30000973");
                break;
            }
            case 28720: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000954);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000974, EnemyEtis, "EnemyEtis-30000974");
                break;
            }
            case 28750: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000955);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000975, EnemyEtis, "EnemyEtis-30000975");
                break;
            }
            case 28780: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000956);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000976, EnemyEtis, "EnemyEtis-30000976");
                break;
            }
            case 28810: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000957);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000977, EnemyEtis, "EnemyEtis-30000977");
                break;
            }
            case 28840: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000958);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000978, EnemyEtis, "EnemyEtis-30000978");
                break;
            }
            case 28870: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000959);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000979, EnemyEtis, "EnemyEtis-30000979");
                break;
            }
            case 28900: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000960);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000980, EnemyEtis, "EnemyEtis-30000980");
                break;
            }
            case 28930: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000961);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000981, EnemyEtis, "EnemyEtis-30000981");
                break;
            }
            case 28960: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000962);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000982, EnemyEtis, "EnemyEtis-30000982");
                break;
            }
            case 28990: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000963);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000983, EnemyEtis, "EnemyEtis-30000983");
                break;
            }
            case 29020: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000964);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000984, EnemyEtis, "EnemyEtis-30000984");
                break;
            }
            case 29050: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000965);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000985, EnemyEtis, "EnemyEtis-30000985");
                break;
            }
            case 29080: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000966);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000986, EnemyEtis, "EnemyEtis-30000986");
                break;
            }
            case 29110: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000967);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000987, EnemyEtis, "EnemyEtis-30000987");
                break;
            }
            case 29140: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000968);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000988, EnemyEtis, "EnemyEtis-30000988");
                break;
            }
            case 29170: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000969);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000989, EnemyEtis, "EnemyEtis-30000989");
                break;
            }
            case 29200: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000970);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000990, EnemyEtis, "EnemyEtis-30000990");
                break;
            }
            case 29230: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000971);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000991, EnemyEtis, "EnemyEtis-30000991");
                break;
            }
            case 29260: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000972);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000992, EnemyEtis, "EnemyEtis-30000992");
                break;
            }
            case 29290: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000973);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000993, EnemyEtis, "EnemyEtis-30000993");
                break;
            }
            case 29320: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000974);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000994, EnemyEtis, "EnemyEtis-30000994");
                break;
            }
            case 29350: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000975);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000995, EnemyEtis, "EnemyEtis-30000995");
                break;
            }
            case 29380: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000976);
                bringDirector()->addSubGroup(pEtis);
                orderActorToFactory(30000996, EnemyEtis, "EnemyEtis-30000996");
                break;
            }
            case 29410: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000977);
                bringDirector()->addSubGroup(pEtis);
                break;
            }
            case 29440: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000978);
                bringDirector()->addSubGroup(pEtis);
                break;
            }
            case 29470: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000979);
                bringDirector()->addSubGroup(pEtis);
                break;
            }
            case 29500: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000980);
                bringDirector()->addSubGroup(pEtis);
                break;
            }
            case 29530: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000981);
                bringDirector()->addSubGroup(pEtis);
                break;
            }
            case 29560: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000982);
                bringDirector()->addSubGroup(pEtis);
                break;
            }
            case 29590: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000983);
                bringDirector()->addSubGroup(pEtis);
                break;
            }
            case 29620: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000984);
                bringDirector()->addSubGroup(pEtis);
                break;
            }
            case 29650: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000985);
                bringDirector()->addSubGroup(pEtis);
                break;
            }
            case 29680: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000986);
                bringDirector()->addSubGroup(pEtis);
                break;
            }
            case 29710: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000987);
                bringDirector()->addSubGroup(pEtis);
                break;
            }
            case 29740: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000988);
                bringDirector()->addSubGroup(pEtis);
                break;
            }
            case 29770: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000989);
                bringDirector()->addSubGroup(pEtis);
                break;
            }
            case 29800: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000990);
                bringDirector()->addSubGroup(pEtis);
                break;
            }
            case 29830: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000991);
                bringDirector()->addSubGroup(pEtis);
                break;
            }
            case 29860: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000992);
                bringDirector()->addSubGroup(pEtis);
                break;
            }
            case 29890: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000993);
                bringDirector()->addSubGroup(pEtis);
                break;
            }
            case 29920: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000994);
                bringDirector()->addSubGroup(pEtis);
                break;
            }
            case 29950: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000995);
                bringDirector()->addSubGroup(pEtis);
                break;
            }
            case 29980: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(30000996);
                bringDirector()->addSubGroup(pEtis);
                break;
            }
            default :
                break;
        }
        _cnt_event = (_cnt_event < 1019-1 ? _cnt_event+1 : _cnt_event);
    }
    // gen02 end


    if (getBehaveingFrame() == 1 && pGAME_SCENE->getProgress()->get() == GameScene::PROG_MAIN) {
        //兄弟シーンのBGMを全てフェードアウトし、自分のシーンBGMをフェードイン
        StagePartController* pStagePartController = (StagePartController*)(getParent());
        pStagePartController->fadeout_stop_AllPartSceneBgm();
        getConductor()->performFromTheBegining(0);
    }
    if (getBehaveingFrame() == _paFrame_NextEvent[_event_num-1] + 60*60) {
        getConductor()->fadeoutStop(0, 120);
        throwEventUpperTree(EVENT_STG01_02_WAS_BROKEN);
    }
}

Stage01_02::~Stage01_02() {

}
