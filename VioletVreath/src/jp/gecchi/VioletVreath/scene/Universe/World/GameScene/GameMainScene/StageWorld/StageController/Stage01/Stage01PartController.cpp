#include "stdafx.h"
#include "Stage01PartController.h"

#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/dxcore/scene/supporter/GgafDxBgmPerformerForScene.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "../Stage.h"
#include "part/Stage01_01.h"
#include "part/Stage01_02.h"
#include "part/Stage01_03.h"
#include "part/Stage01_Climax.h"
#include "part/Stage01WalledScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Stage01PartController::Stage01PartController(const char* prm_name) : StagePartController(prm_name) {
    _class_name = "Stage01PartController";

    _pBgmPerformer->useBgm(4);
    _pBgmPerformer->set(0, "OGG_BGM_01_01");
    _pBgmPerformer->set(1, "OGG_BGM_01_02");
    _pBgmPerformer->set(2, "OGG_BGM_01_03");
    _pBgmPerformer->set(3, "OGG_BGM_01_CLIMAX");
    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
	frame f[] = {1,20,40,60,80,100,120,140,160,180,200,220,240,260,280,300,320,340,360,380,400,420,440,460,480,500,520,540,560,580,600,620,640,660,680,700,720,740,760,780,800,820,840,860,880,900,920,940,960,980,1000,1020,1040,1060,1080,1100,1120,1140,1160,1180,1200,1220,1240,1260,1280,1300,1320,1340,1360,1380,1400,1420,1440,1460,1480,1500,1520,1540,1560,1580,1600,1620,1640,1660,1680,1700,1720,1740,1760,1780,1800,1820,1840,1860,1880,1900,1920,1940,1960,1980,2000,2020,2040,2060,2080,2100,2120,2140,2160,2180,2200,2220,2240,2260,2280,2300,2320,2340,2360,2380,2400,2420,2440,2460,2480,2500,2520,2540,2560,2580,2600,2620,2640,2660,2680,2700,2720,2740,2760,2780,2800,2820,2840,2860,2880,2900,2920,2940,2960,2980,3000,3020,3040,3060,3080,3100,3120,3140,3160,3180,3200,3220,3240,3260,3280,3300,3320,3340,3360,3380,3400,3420,3440,3460,3480,3500,3520,3540,3560,3580,3600,3620,3640,3660,3680,3700,3720,3740,3760,3780,3800,3820,3840,3860,3880,3900,3920,3940,3960,3980,4000,4020,4040,4060,4080,4100,4120,4140,4160,4180,4200,4220,4240,4260,4280,4300,4320,4340,4360,4380,4400,4420,4440,4460,4480,4500,4520,4540,4560,4580,4600,4620,4640,4660,4680,4700,4720,4740,4760,4780,4800,4820,4840,4860,4880,4900,4920,4940,4960,4980,5000,5020,5040,5060,5080,5100,5120,5140,5160,5180,5200,5220,5240,5260,5280,5300,5320,5340,5360,5380,5400,5420,5440,5460,5480,5500,5520,5540,5560,5580,5600,5620,5640,5660,5680,5700,5720,5740,5760,5780,5800,5820,5840,5860,5880,5900,5920,5940,5960,5980,6000,6020,6040,6060,6080,6100,6120,6140,6160,6180,6200,6220,6240,6260,6280,6300,6320,6340,6360,6380,6400,6420,6440,6460,6480,6500,6520,6540,6560,6580,6600,6620,6640,6660,6680,6700,6720,6740,6760,6780,6800,6820,6840,6860,6880,6900,6920,6940,6960,6980,7000,7020,7040,7060,7080,7100,7120,7140,7160,7180,7200,7220,7240,7260,7280,7300,7320,7340,7360,7380,7400,7420,7440,7460,7480,7500,7520,7540,7560,7580,7600,7620,7640,7660,7680,7700,7720,7740,7760,7780,7800,7820,7840,7860,7880,7900,7920,7940,7960,7980,8000,8020,8040,8060,8080,8100,8120,8140,8160,8180,8200,8220,8240,8260,8280,8300,8320,8340,8360,8380,8400,8420,8440,8460,8480,8500,8520,8540,8560,8580,8600,8620,8640,8660,8680,8700,8720,8740,8760,8780,8800,8820,8840,8860,8880,8900,8920,8940,8960,8980,9000,9020,9040,9060,9080,9100,9120,9140,9160,9180,9200,9220,9240,9260,9280,9300,9320,9340,9360,9380,9400,9420,9440,9460,9480,9500,9520,9540,9560,9580,9600,9620,9640,9660,9680,9700,9720,9740,9760,9780,9800,9820,9840,9860,9880,9900,9920,9940,9960,9980,10000,10020,10040,10060,10080,10100,10120,10140,10160,10180,10200,10220,10240,10260,10280,10300,10320,10340,10360,10380,10400,10420,10440,10460,10480,10500,10520,10540,10560,10580,10600,10620,10640,10660,10680,10700,10720,10740,10760,10780,10800,10820,10840,10860,10880,10900,10920,10940,10960,10980,11000,11020,11040,11060,11080,11100,11120,11140,11160,11180,11200,11220,11240,11260,11280,11300,11320,11340,11360,11380,11400,11420,11440,11460,11480,11500,11520,11540,11560,11580,11600,11620,11640,11660,11680,11700,11720,11740,11760,11780,11800,11820,11840,11860,11880,11900,11920,11940,11960,11980,12000,12020,12040,12060,12080,12100,12120,12140,12160,12180,12200,12220,12240,12260,12280,12300,12320,12340,12360,12380,12400,12420,12440,12460,12480,12500,12520,12540,12560,12580,12600,12620,12640,12660,12680,12700,12720,12740,12760,12780,12800,12820,12840,12860,12880,12900,12920,12940,12960,12980,13000,13020,13040,13060,13080,13100,13120,13140,13160,13180,13200,13220,13240,13260,13280,13300,13320,13340,13360,13380,13400,13420,13440,13460,13480,13500,13520,13540,13560,13580,13600,13620,13640,13660,13680,13700,13720,13740,13760,13780,13800,13820,13840,13860,13880,13900,13920,13940,13960,13980,14000,14020,14040,14060,14080,14100,14120,14140,14160,14180,14200,14220,14240,14260,14280,14300,14320,14340,14360,14380,14400,14420,14440,14460,14480,14500,14520,14540,14560,14580,14600,14620,14640,14660,14680,14700,14720,14740,14760,14780,14800,14820,14840,14860,14880,14900,14920,14940,14960,14980,15000,15020,15040,15060,15080,15100,15120,15140,15160,15180,15200,15220,15240,15260,15280,15300,15320,15340,15360,15380,15400,15420,15440,15460,15480,15500,15520,15540,15560,15580,15600,15620,15640,15660,15680,15700,15720,15740,15760,15780,15800,15820,15840,15860,15880,15900,15920,15940,15960,15980,16000,16020,16040,16060,16080,16100,16120,16140,16160,16180,16200,16220,16240,16260,16280,16300,16320,16340,16360,16380,16400,16420,16440,16460,16480,16500,16520,16540,16560,16580,16600,16620,16640,16660,16680,16700,16720,16740,16760,16780,16800,16820,16840,16860,16880,16900,16920,16940,16960,16980,17000,17020,17040,17060,17080,17100,17120,17140,17160,17180,17200,17220,17240,17260,17280,17300,17320,17340,17360,17380,17400,17420,17440,17460,17480,17500,17520,17540,17560,17580,17600,17620,17640,17660,17680,17700,17720,17740,17760,17780,17800,17820,17840,17860,17880,17900,17920,17940,17960,17980,18000,18020,18040,18060,18080,18100,18120,18140,18160,18180,18200,18220,18240,18260,18280,18300,18320,18340,18360,18380,18400,18420,18440,18460,18480,18500,18520,18540,18560,18580,18600,18620,18640,18660,18680,18700,18720,18740,18760,18780,18800,18820,18840,18860,18880,18900,18920,18940,18960,18980,19000,19020,19040,19060,19080,19100,19120,19140,19160,19180,19200,19220,19240,19260,19280,19300,19320,19340,19360,19380,19400,19420,19440,19460,19480,19500,19520,19540,19560,19580,19600,19620,19640,19660,19680,19700,19720,19740,19760,19780,19800,19820,19840,19860,19880,19900,19920,19940,19960,19980,20000,20020,20040,20060,20080,20100,20120,20140,20160,20180,20200,20220,20240,20260,20280,20300,20320,20340,20360,20380,20400,20420,20440,20460,20480,20500,20520,20540,20560,20580,20600,20620,20640,20660,20680,20700,20720,20740,20760,20780,20800,20820,20840,20860,20880,20900,20920,20940,20960,20980,21000,21020,21040,21060,21080,21100,21120,21140,21160,21180,21200,21220,21240,21260,21280,21300,21320,21340,21360,21380,21400,21420,21440,21460,21480,21500,21520,21540,21560,21580,21600,21620,21640,21660,21680,21700,21720,21740,21760,21780,21800,21820,21840,21860,21880,21900,21920,21940,21960,21980,22000,22020,22040,22060,22080,22100,22120,22140,22160,22180,22200,22220,22240,22260,22280,22300,22320,22340,22360,22380,22400,22420,22440,22460,22480,22500,22520,22540,22560,22580,22600,22620,22640,22660,22680,22700,22720,22740,22760,22780,22800,22820,22840,22860,22880,22900,22920,22940,22960,22980,23000,23020,23040,23060,23080,23100,23120,23140,23160,23180,23200,23220,23240,23260,23280,23300,23320,23340,23360,23380,23400,23420,23440,23460,23480,23500,23520,23540,23560,23580,23600,23620,23640,23660,23680,23700,23720,23740,23760,23780,23800,23820,23840,23860,23880,23900,23920,23940,23960,23980,24000,24020,24040,24060,24080,24100,24120,24140,24160,24180,24200,24220,24240,24260,24280,24300,24320,24340,24360,24380,24400,24420,24440,24460,24480,24500,24520,24540,24560,24580,24600,24620,24640,24660,24680,24700,24720,24740,24760,24780,24800,24820,24840,24860,24880,24900,24920,24940,24960,24980,25000,25020,25040,25060,25080,25100,25120,25140,25160,25180,25200,25220,25240,25260,25280,25300,25320,25340,25360,25380,25400,25420,25440,25460,25480,25500,25520,25540,25560,25580,25600,25620,25640,25660,25680,25700,25720,25740,25760,25780,25800,25820,25840,25860,25880,25900,25920,25940,25960,25980,26000,26020,26040,26060,26080,26100,26120,26140,26160,26180,26200,26220,26240,26260,26280,26300,26320,26340,26360,26380,26400,26420,26440,26460,26480,26500,26520,26540,26560,26580,26600,26620,26640,26660,26680,26700,26720,26740,26760,26780,26800,26820,26840,26860,26880,26900,26920,26940,26960,26980,27000,27020,27040,27060,27080,27100,27120,27140,27160,27180,27200,27220,27240,27260,27280,27300,27320,27340,27360,27380,27400,27420,27440,27460,27480,27500,27520,27540,27560,27580,27600,27620,27640,27660,27680,27700,27720,27740,27760,27780,27800,27820,27840,27860,27880,27900,27920,27940,27960,27980,28000,28020,28040,28060,28080,28100,28120,28140,28160,28180,28200,28220,28240,28260,28280,28300,28320,28340,28360,28380,28400,28420,28440,28460,28480,28500,28520,28540,28560,28580,28600,28620,28640,28660,28680,28700,28720,28740,28760,28780,28800,28820,28840,28860,28880,28900,28920,28940,28960,28980,29000,29020,29040,29060,29080,29100,29120,29140,29160,29180,29200,29220,29240,29260,29280,29300,29320,29340,29360,29380,29400,29420,29440,29460,29480,29500,29520,29540,29560,29580,29600,29620,29640,29660,29680,29700,29720,29740,29760,29780,29800,29820,29840,29860,29880,29900,29920,29940,29960,29980,30000};
	_paFrame_NextEvent = new frame[1501];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 1501;
	orderActorToFactory(10000000, EnemyEtis, "EnemyEtis-1");
	orderActorToFactory(10000001, EnemyEtis, "EnemyEtis-2");
	orderActorToFactory(10000002, EnemyEtis, "EnemyEtis-3");
	orderActorToFactory(10000003, EnemyEtis, "EnemyEtis-4");
	orderActorToFactory(10000004, EnemyEtis, "EnemyEtis-5");
	orderActorToFactory(10000005, EnemyEtis, "EnemyEtis-6");
	orderActorToFactory(10000006, EnemyEtis, "EnemyEtis-7");
	orderActorToFactory(10000007, EnemyEtis, "EnemyEtis-8");
	orderActorToFactory(10000008, EnemyEtis, "EnemyEtis-9");
	orderActorToFactory(10000009, EnemyEtis, "EnemyEtis-10");
	orderActorToFactory(10000010, EnemyEtis, "EnemyEtis-11");
	orderActorToFactory(10000011, EnemyEtis, "EnemyEtis-12");
	orderActorToFactory(10000012, EnemyEtis, "EnemyEtis-13");
	orderActorToFactory(10000013, EnemyEtis, "EnemyEtis-14");
	orderActorToFactory(10000014, EnemyEtis, "EnemyEtis-15");
	orderActorToFactory(10000015, EnemyEtis, "EnemyEtis-16");
	orderActorToFactory(10000016, EnemyEtis, "EnemyEtis-17");
	orderActorToFactory(10000017, EnemyEtis, "EnemyEtis-18");
	orderActorToFactory(10000018, EnemyEtis, "EnemyEtis-19");
	orderActorToFactory(10000019, EnemyEtis, "EnemyEtis-20");
	orderActorToFactory(10000020, EnemyEtis, "EnemyEtis-21");
	orderActorToFactory(10000021, EnemyEtis, "EnemyEtis-22");
	orderActorToFactory(10000022, EnemyEtis, "EnemyEtis-23");
	orderActorToFactory(10000023, EnemyEtis, "EnemyEtis-24");
	orderActorToFactory(10000024, EnemyEtis, "EnemyEtis-25");
	orderActorToFactory(10000025, EnemyEtis, "EnemyEtis-26");
	orderActorToFactory(10000026, EnemyEtis, "EnemyEtis-27");
	orderActorToFactory(10000027, EnemyEtis, "EnemyEtis-28");
	orderActorToFactory(10000028, EnemyEtis, "EnemyEtis-29");
	orderActorToFactory(10000029, EnemyEtis, "EnemyEtis-30");
	orderActorToFactory(10000030, EnemyEtis, "EnemyEtis-31");
	orderActorToFactory(10000031, EnemyEtis, "EnemyEtis-32");
	orderActorToFactory(10000032, EnemyEtis, "EnemyEtis-33");
	orderActorToFactory(10000033, EnemyEtis, "EnemyEtis-34");
	orderActorToFactory(10000034, EnemyEtis, "EnemyEtis-35");
	orderActorToFactory(10000035, EnemyEtis, "EnemyEtis-36");
	orderActorToFactory(10000036, EnemyEtis, "EnemyEtis-37");
	orderActorToFactory(10000037, EnemyEtis, "EnemyEtis-38");
	orderActorToFactory(10000038, EnemyEtis, "EnemyEtis-39");
	orderActorToFactory(10000039, EnemyEtis, "EnemyEtis-40");
	orderActorToFactory(10000040, EnemyEtis, "EnemyEtis-41");
    // gen01 end
    useProgress(Stage01PartController::PROG_FAINAL);
}

void Stage01PartController::initialize() {
    _pProg->reset(Stage01PartController::PROG_INIT);
}

void Stage01PartController::processBehavior() {
    // 以下の gen02 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen02 start
	if (getBehaveingFrame() == _paFrame_NextEvent[_cnt_event]) {
		switch (getBehaveingFrame()) {
			case 1: {
				break;
			}
			case 20: {
				orderActorToFactory(10000041, EnemyEtis, "EnemyEtis-42");
				break;
			}
			case 40: {
				orderActorToFactory(10000042, EnemyEtis, "EnemyEtis-43");
				break;
			}
			case 60: {
				orderActorToFactory(10000043, EnemyEtis, "EnemyEtis-44");
				break;
			}
			case 80: {
				orderActorToFactory(10000044, EnemyEtis, "EnemyEtis-45");
				break;
			}
			case 100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000000);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000045, EnemyEtis, "EnemyEtis-46");
				orderActorToFactory(10001497, FormationAllas001a, "FormationAllas001a-47");
				orderActorToFactory(10001498, FormationAllas001b, "FormationAllas001b-48");
				orderActorToFactory(10001499, FormationAllas001c, "FormationAllas001c-49");
				orderActorToFactory(10001500, FormationAllas001d, "FormationAllas001d-50");
				orderActorToFactory(10001501, FormationAllas001a, "FormationAllas001a-51");
				orderActorToFactory(10001502, FormationAllas001d, "FormationAllas001d-52");
				orderActorToFactory(10001503, FormationAllas001b, "FormationAllas001b-53");
				orderActorToFactory(10001504, FormationAllas001c, "FormationAllas001c-54");
				orderActorToFactory(10001505, FormationAllas001a, "FormationAllas001a-55");
				orderActorToFactory(10001506, FormationAllas001d, "FormationAllas001d-56");
				orderActorToFactory(10001507, FormationAllas001b, "FormationAllas001b-57");
				orderActorToFactory(10001508, FormationAllas001c, "FormationAllas001c-58");
				break;
			}
			case 120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000001);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000046, EnemyEtis, "EnemyEtis-59");
				break;
			}
			case 140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000002);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000047, EnemyEtis, "EnemyEtis-60");
				break;
			}
			case 160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000003);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000048, EnemyEtis, "EnemyEtis-61");
				break;
			}
			case 180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000004);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000049, EnemyEtis, "EnemyEtis-62");
				break;
			}
			case 200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000005);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000050, EnemyEtis, "EnemyEtis-63");
				break;
			}
			case 220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000006);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000051, EnemyEtis, "EnemyEtis-64");
				break;
			}
			case 240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000007);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000052, EnemyEtis, "EnemyEtis-65");
				break;
			}
			case 260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000008);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000053, EnemyEtis, "EnemyEtis-66");
				break;
			}
			case 280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000009);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000054, EnemyEtis, "EnemyEtis-67");
				break;
			}
			case 300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000010);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000055, EnemyEtis, "EnemyEtis-68");
				break;
			}
			case 320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000011);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000056, EnemyEtis, "EnemyEtis-69");
				break;
			}
			case 340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000012);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000057, EnemyEtis, "EnemyEtis-70");
				break;
			}
			case 360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000013);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000058, EnemyEtis, "EnemyEtis-71");
				break;
			}
			case 380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000014);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000059, EnemyEtis, "EnemyEtis-72");
				break;
			}
			case 400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000015);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000060, EnemyEtis, "EnemyEtis-73");
				break;
			}
			case 420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000016);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000061, EnemyEtis, "EnemyEtis-74");
				break;
			}
			case 440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000017);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000062, EnemyEtis, "EnemyEtis-75");
				break;
			}
			case 460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000018);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000063, EnemyEtis, "EnemyEtis-76");
				break;
			}
			case 480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000019);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000064, EnemyEtis, "EnemyEtis-77");
				break;
			}
			case 500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000020);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000065, EnemyEtis, "EnemyEtis-78");
				break;
			}
			case 520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000021);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000066, EnemyEtis, "EnemyEtis-79");
				break;
			}
			case 540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000022);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000067, EnemyEtis, "EnemyEtis-80");
				break;
			}
			case 560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000023);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000068, EnemyEtis, "EnemyEtis-81");
				break;
			}
			case 580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000024);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000069, EnemyEtis, "EnemyEtis-82");
				break;
			}
			case 600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000025);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000070, EnemyEtis, "EnemyEtis-83");
				break;
			}
			case 620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000026);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000071, EnemyEtis, "EnemyEtis-84");
				break;
			}
			case 640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000027);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000072, EnemyEtis, "EnemyEtis-85");
				break;
			}
			case 660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000028);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000073, EnemyEtis, "EnemyEtis-86");
				break;
			}
			case 680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000029);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000074, EnemyEtis, "EnemyEtis-87");
				break;
			}
			case 700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000030);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000075, EnemyEtis, "EnemyEtis-88");
				break;
			}
			case 720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000031);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000076, EnemyEtis, "EnemyEtis-89");
				break;
			}
			case 740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000032);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000077, EnemyEtis, "EnemyEtis-90");
				break;
			}
			case 760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000033);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000078, EnemyEtis, "EnemyEtis-91");
				break;
			}
			case 780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000034);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000079, EnemyEtis, "EnemyEtis-92");
				break;
			}
			case 800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000035);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000080, EnemyEtis, "EnemyEtis-93");
				break;
			}
			case 820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000036);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000081, EnemyEtis, "EnemyEtis-94");
				break;
			}
			case 840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000037);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000082, EnemyEtis, "EnemyEtis-95");
				break;
			}
			case 860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000038);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000083, EnemyEtis, "EnemyEtis-96");
				break;
			}
			case 880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000039);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000084, EnemyEtis, "EnemyEtis-97");
				break;
			}
			case 900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000040);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000085, EnemyEtis, "EnemyEtis-98");
				break;
			}
			case 920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000041);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000086, EnemyEtis, "EnemyEtis-99");
				break;
			}
			case 940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000042);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000087, EnemyEtis, "EnemyEtis-100");
				break;
			}
			case 960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000043);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000088, EnemyEtis, "EnemyEtis-101");
				break;
			}
			case 980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000044);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000089, EnemyEtis, "EnemyEtis-102");
				break;
			}
			case 1000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000045);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000090, EnemyEtis, "EnemyEtis-103");
				{
				FormationTableScene* ta = NEW FormationTableScene("FormationTableScene-104");
				ta->setMaxPerformFrame(3000);
				addSubLast(ta);
				ta->addToTable(((FormationAllas001a*)obtainActorFromFactory(10001497)), 400);
				ta->addToTable(((FormationAllas001b*)obtainActorFromFactory(10001498)), 400);
				ta->addToTable(((FormationAllas001c*)obtainActorFromFactory(10001499)), 400);
				ta->addToTable(((FormationAllas001d*)obtainActorFromFactory(10001500)), 400);
				ta->addToTable(((FormationAllas001a*)obtainActorFromFactory(10001501)), 1);
				ta->addToTable(((FormationAllas001d*)obtainActorFromFactory(10001502)), 400);
				ta->addToTable(((FormationAllas001b*)obtainActorFromFactory(10001503)), 1);
				ta->addToTable(((FormationAllas001c*)obtainActorFromFactory(10001504)), 400);
				ta->addToTable(((FormationAllas001a*)obtainActorFromFactory(10001505)), 1);
				ta->addToTable(((FormationAllas001d*)obtainActorFromFactory(10001506)), 1);
				ta->addToTable(((FormationAllas001b*)obtainActorFromFactory(10001507)), 1);
				ta->addToTable(((FormationAllas001c*)obtainActorFromFactory(10001508)), 400);
				}
				break;
			}
			case 1020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000046);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000091, EnemyEtis, "EnemyEtis-105");
				break;
			}
			case 1040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000047);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000092, EnemyEtis, "EnemyEtis-106");
				break;
			}
			case 1060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000048);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000093, EnemyEtis, "EnemyEtis-107");
				break;
			}
			case 1080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000049);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000094, EnemyEtis, "EnemyEtis-108");
				break;
			}
			case 1100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000050);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000095, EnemyEtis, "EnemyEtis-109");
				break;
			}
			case 1120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000051);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000096, EnemyEtis, "EnemyEtis-110");
				break;
			}
			case 1140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000052);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000097, EnemyEtis, "EnemyEtis-111");
				break;
			}
			case 1160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000053);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000098, EnemyEtis, "EnemyEtis-112");
				break;
			}
			case 1180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000054);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000099, EnemyEtis, "EnemyEtis-113");
				break;
			}
			case 1200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000055);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000100, EnemyEtis, "EnemyEtis-114");
				break;
			}
			case 1220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000056);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000101, EnemyEtis, "EnemyEtis-115");
				break;
			}
			case 1240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000057);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000102, EnemyEtis, "EnemyEtis-116");
				break;
			}
			case 1260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000058);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000103, EnemyEtis, "EnemyEtis-117");
				break;
			}
			case 1280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000059);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000104, EnemyEtis, "EnemyEtis-118");
				break;
			}
			case 1300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000060);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000105, EnemyEtis, "EnemyEtis-119");
				break;
			}
			case 1320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000061);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000106, EnemyEtis, "EnemyEtis-120");
				break;
			}
			case 1340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000062);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000107, EnemyEtis, "EnemyEtis-121");
				break;
			}
			case 1360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000063);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000108, EnemyEtis, "EnemyEtis-122");
				break;
			}
			case 1380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000064);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000109, EnemyEtis, "EnemyEtis-123");
				break;
			}
			case 1400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000065);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000110, EnemyEtis, "EnemyEtis-124");
				break;
			}
			case 1420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000066);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000111, EnemyEtis, "EnemyEtis-125");
				break;
			}
			case 1440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000067);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000112, EnemyEtis, "EnemyEtis-126");
				break;
			}
			case 1460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000068);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000113, EnemyEtis, "EnemyEtis-127");
				break;
			}
			case 1480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000069);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000114, EnemyEtis, "EnemyEtis-128");
				break;
			}
			case 1500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000070);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000115, EnemyEtis, "EnemyEtis-129");
				break;
			}
			case 1520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000071);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000116, EnemyEtis, "EnemyEtis-130");
				break;
			}
			case 1540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000072);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000117, EnemyEtis, "EnemyEtis-131");
				break;
			}
			case 1560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000073);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000118, EnemyEtis, "EnemyEtis-132");
				break;
			}
			case 1580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000074);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000119, EnemyEtis, "EnemyEtis-133");
				break;
			}
			case 1600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000075);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000120, EnemyEtis, "EnemyEtis-134");
				break;
			}
			case 1620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000076);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000121, EnemyEtis, "EnemyEtis-135");
				break;
			}
			case 1640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000077);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000122, EnemyEtis, "EnemyEtis-136");
				break;
			}
			case 1660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000078);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000123, EnemyEtis, "EnemyEtis-137");
				break;
			}
			case 1680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000079);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000124, EnemyEtis, "EnemyEtis-138");
				break;
			}
			case 1700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000080);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000125, EnemyEtis, "EnemyEtis-139");
				break;
			}
			case 1720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000081);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000126, EnemyEtis, "EnemyEtis-140");
				break;
			}
			case 1740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000082);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000127, EnemyEtis, "EnemyEtis-141");
				break;
			}
			case 1760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000083);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000128, EnemyEtis, "EnemyEtis-142");
				break;
			}
			case 1780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000084);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000129, EnemyEtis, "EnemyEtis-143");
				break;
			}
			case 1800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000085);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000130, EnemyEtis, "EnemyEtis-144");
				break;
			}
			case 1820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000086);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000131, EnemyEtis, "EnemyEtis-145");
				break;
			}
			case 1840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000087);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000132, EnemyEtis, "EnemyEtis-146");
				break;
			}
			case 1860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000088);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000133, EnemyEtis, "EnemyEtis-147");
				break;
			}
			case 1880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000089);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000134, EnemyEtis, "EnemyEtis-148");
				break;
			}
			case 1900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000090);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000135, EnemyEtis, "EnemyEtis-149");
				break;
			}
			case 1920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000091);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000136, EnemyEtis, "EnemyEtis-150");
				break;
			}
			case 1940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000092);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000137, EnemyEtis, "EnemyEtis-151");
				break;
			}
			case 1960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000093);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000138, EnemyEtis, "EnemyEtis-152");
				break;
			}
			case 1980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000094);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000139, EnemyEtis, "EnemyEtis-153");
				break;
			}
			case 2000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000095);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000140, EnemyEtis, "EnemyEtis-154");
				break;
			}
			case 2020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000096);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000141, EnemyEtis, "EnemyEtis-155");
				break;
			}
			case 2040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000097);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000142, EnemyEtis, "EnemyEtis-156");
				break;
			}
			case 2060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000098);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000143, EnemyEtis, "EnemyEtis-157");
				break;
			}
			case 2080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000099);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000144, EnemyEtis, "EnemyEtis-158");
				break;
			}
			case 2100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000100);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000145, EnemyEtis, "EnemyEtis-159");
				break;
			}
			case 2120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000101);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000146, EnemyEtis, "EnemyEtis-160");
				break;
			}
			case 2140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000102);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000147, EnemyEtis, "EnemyEtis-161");
				break;
			}
			case 2160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000103);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000148, EnemyEtis, "EnemyEtis-162");
				break;
			}
			case 2180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000104);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000149, EnemyEtis, "EnemyEtis-163");
				break;
			}
			case 2200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000105);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000150, EnemyEtis, "EnemyEtis-164");
				break;
			}
			case 2220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000106);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000151, EnemyEtis, "EnemyEtis-165");
				break;
			}
			case 2240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000107);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000152, EnemyEtis, "EnemyEtis-166");
				break;
			}
			case 2260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000108);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000153, EnemyEtis, "EnemyEtis-167");
				break;
			}
			case 2280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000109);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000154, EnemyEtis, "EnemyEtis-168");
				break;
			}
			case 2300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000110);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000155, EnemyEtis, "EnemyEtis-169");
				break;
			}
			case 2320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000111);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000156, EnemyEtis, "EnemyEtis-170");
				break;
			}
			case 2340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000112);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000157, EnemyEtis, "EnemyEtis-171");
				break;
			}
			case 2360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000113);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000158, EnemyEtis, "EnemyEtis-172");
				break;
			}
			case 2380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000114);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000159, EnemyEtis, "EnemyEtis-173");
				break;
			}
			case 2400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000115);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000160, EnemyEtis, "EnemyEtis-174");
				break;
			}
			case 2420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000116);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000161, EnemyEtis, "EnemyEtis-175");
				break;
			}
			case 2440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000117);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000162, EnemyEtis, "EnemyEtis-176");
				break;
			}
			case 2460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000118);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000163, EnemyEtis, "EnemyEtis-177");
				break;
			}
			case 2480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000119);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000164, EnemyEtis, "EnemyEtis-178");
				break;
			}
			case 2500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000120);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000165, EnemyEtis, "EnemyEtis-179");
				break;
			}
			case 2520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000121);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000166, EnemyEtis, "EnemyEtis-180");
				break;
			}
			case 2540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000122);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000167, EnemyEtis, "EnemyEtis-181");
				break;
			}
			case 2560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000123);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000168, EnemyEtis, "EnemyEtis-182");
				break;
			}
			case 2580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000124);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000169, EnemyEtis, "EnemyEtis-183");
				break;
			}
			case 2600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000125);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000170, EnemyEtis, "EnemyEtis-184");
				break;
			}
			case 2620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000126);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000171, EnemyEtis, "EnemyEtis-185");
				break;
			}
			case 2640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000127);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000172, EnemyEtis, "EnemyEtis-186");
				break;
			}
			case 2660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000128);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000173, EnemyEtis, "EnemyEtis-187");
				break;
			}
			case 2680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000129);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000174, EnemyEtis, "EnemyEtis-188");
				break;
			}
			case 2700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000130);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000175, EnemyEtis, "EnemyEtis-189");
				break;
			}
			case 2720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000131);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000176, EnemyEtis, "EnemyEtis-190");
				break;
			}
			case 2740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000132);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000177, EnemyEtis, "EnemyEtis-191");
				break;
			}
			case 2760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000133);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000178, EnemyEtis, "EnemyEtis-192");
				break;
			}
			case 2780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000134);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000179, EnemyEtis, "EnemyEtis-193");
				break;
			}
			case 2800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000135);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000180, EnemyEtis, "EnemyEtis-194");
				break;
			}
			case 2820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000136);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000181, EnemyEtis, "EnemyEtis-195");
				break;
			}
			case 2840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000137);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000182, EnemyEtis, "EnemyEtis-196");
				break;
			}
			case 2860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000138);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000183, EnemyEtis, "EnemyEtis-197");
				break;
			}
			case 2880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000139);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000184, EnemyEtis, "EnemyEtis-198");
				break;
			}
			case 2900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000140);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000185, EnemyEtis, "EnemyEtis-199");
				break;
			}
			case 2920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000141);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000186, EnemyEtis, "EnemyEtis-200");
				break;
			}
			case 2940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000142);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000187, EnemyEtis, "EnemyEtis-201");
				break;
			}
			case 2960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000143);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000188, EnemyEtis, "EnemyEtis-202");
				break;
			}
			case 2980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000144);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000189, EnemyEtis, "EnemyEtis-203");
				break;
			}
			case 3000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000145);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000190, EnemyEtis, "EnemyEtis-204");
				break;
			}
			case 3020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000146);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000191, EnemyEtis, "EnemyEtis-205");
				break;
			}
			case 3040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000147);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000192, EnemyEtis, "EnemyEtis-206");
				break;
			}
			case 3060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000148);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000193, EnemyEtis, "EnemyEtis-207");
				break;
			}
			case 3080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000149);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000194, EnemyEtis, "EnemyEtis-208");
				break;
			}
			case 3100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000150);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000195, EnemyEtis, "EnemyEtis-209");
				break;
			}
			case 3120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000151);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000196, EnemyEtis, "EnemyEtis-210");
				break;
			}
			case 3140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000152);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000197, EnemyEtis, "EnemyEtis-211");
				break;
			}
			case 3160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000153);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000198, EnemyEtis, "EnemyEtis-212");
				break;
			}
			case 3180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000154);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000199, EnemyEtis, "EnemyEtis-213");
				break;
			}
			case 3200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000155);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000200, EnemyEtis, "EnemyEtis-214");
				break;
			}
			case 3220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000156);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000201, EnemyEtis, "EnemyEtis-215");
				break;
			}
			case 3240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000157);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000202, EnemyEtis, "EnemyEtis-216");
				break;
			}
			case 3260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000158);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000203, EnemyEtis, "EnemyEtis-217");
				break;
			}
			case 3280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000159);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000204, EnemyEtis, "EnemyEtis-218");
				break;
			}
			case 3300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000160);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000205, EnemyEtis, "EnemyEtis-219");
				break;
			}
			case 3320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000161);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000206, EnemyEtis, "EnemyEtis-220");
				break;
			}
			case 3340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000162);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000207, EnemyEtis, "EnemyEtis-221");
				break;
			}
			case 3360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000163);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000208, EnemyEtis, "EnemyEtis-222");
				break;
			}
			case 3380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000164);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000209, EnemyEtis, "EnemyEtis-223");
				break;
			}
			case 3400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000165);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000210, EnemyEtis, "EnemyEtis-224");
				break;
			}
			case 3420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000166);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000211, EnemyEtis, "EnemyEtis-225");
				break;
			}
			case 3440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000167);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000212, EnemyEtis, "EnemyEtis-226");
				break;
			}
			case 3460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000168);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000213, EnemyEtis, "EnemyEtis-227");
				break;
			}
			case 3480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000169);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000214, EnemyEtis, "EnemyEtis-228");
				break;
			}
			case 3500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000170);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000215, EnemyEtis, "EnemyEtis-229");
				break;
			}
			case 3520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000171);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000216, EnemyEtis, "EnemyEtis-230");
				break;
			}
			case 3540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000172);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000217, EnemyEtis, "EnemyEtis-231");
				break;
			}
			case 3560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000173);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000218, EnemyEtis, "EnemyEtis-232");
				break;
			}
			case 3580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000174);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000219, EnemyEtis, "EnemyEtis-233");
				break;
			}
			case 3600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000175);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000220, EnemyEtis, "EnemyEtis-234");
				break;
			}
			case 3620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000176);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000221, EnemyEtis, "EnemyEtis-235");
				break;
			}
			case 3640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000177);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000222, EnemyEtis, "EnemyEtis-236");
				break;
			}
			case 3660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000178);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000223, EnemyEtis, "EnemyEtis-237");
				break;
			}
			case 3680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000179);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000224, EnemyEtis, "EnemyEtis-238");
				break;
			}
			case 3700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000180);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000225, EnemyEtis, "EnemyEtis-239");
				break;
			}
			case 3720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000181);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000226, EnemyEtis, "EnemyEtis-240");
				break;
			}
			case 3740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000182);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000227, EnemyEtis, "EnemyEtis-241");
				break;
			}
			case 3760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000183);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000228, EnemyEtis, "EnemyEtis-242");
				break;
			}
			case 3780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000184);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000229, EnemyEtis, "EnemyEtis-243");
				break;
			}
			case 3800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000185);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000230, EnemyEtis, "EnemyEtis-244");
				break;
			}
			case 3820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000186);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000231, EnemyEtis, "EnemyEtis-245");
				break;
			}
			case 3840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000187);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000232, EnemyEtis, "EnemyEtis-246");
				break;
			}
			case 3860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000188);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000233, EnemyEtis, "EnemyEtis-247");
				break;
			}
			case 3880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000189);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000234, EnemyEtis, "EnemyEtis-248");
				break;
			}
			case 3900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000190);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000235, EnemyEtis, "EnemyEtis-249");
				break;
			}
			case 3920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000191);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000236, EnemyEtis, "EnemyEtis-250");
				break;
			}
			case 3940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000192);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000237, EnemyEtis, "EnemyEtis-251");
				break;
			}
			case 3960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000193);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000238, EnemyEtis, "EnemyEtis-252");
				break;
			}
			case 3980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000194);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000239, EnemyEtis, "EnemyEtis-253");
				break;
			}
			case 4000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000195);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000240, EnemyEtis, "EnemyEtis-254");
				break;
			}
			case 4020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000196);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000241, EnemyEtis, "EnemyEtis-255");
				break;
			}
			case 4040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000197);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000242, EnemyEtis, "EnemyEtis-256");
				break;
			}
			case 4060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000198);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000243, EnemyEtis, "EnemyEtis-257");
				break;
			}
			case 4080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000199);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000244, EnemyEtis, "EnemyEtis-258");
				break;
			}
			case 4100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000200);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000245, EnemyEtis, "EnemyEtis-259");
				break;
			}
			case 4120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000201);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000246, EnemyEtis, "EnemyEtis-260");
				break;
			}
			case 4140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000202);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000247, EnemyEtis, "EnemyEtis-261");
				break;
			}
			case 4160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000203);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000248, EnemyEtis, "EnemyEtis-262");
				break;
			}
			case 4180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000204);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000249, EnemyEtis, "EnemyEtis-263");
				break;
			}
			case 4200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000205);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000250, EnemyEtis, "EnemyEtis-264");
				break;
			}
			case 4220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000206);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000251, EnemyEtis, "EnemyEtis-265");
				break;
			}
			case 4240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000207);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000252, EnemyEtis, "EnemyEtis-266");
				break;
			}
			case 4260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000208);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000253, EnemyEtis, "EnemyEtis-267");
				break;
			}
			case 4280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000209);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000254, EnemyEtis, "EnemyEtis-268");
				break;
			}
			case 4300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000210);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000255, EnemyEtis, "EnemyEtis-269");
				break;
			}
			case 4320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000211);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000256, EnemyEtis, "EnemyEtis-270");
				break;
			}
			case 4340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000212);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000257, EnemyEtis, "EnemyEtis-271");
				break;
			}
			case 4360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000213);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000258, EnemyEtis, "EnemyEtis-272");
				break;
			}
			case 4380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000214);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000259, EnemyEtis, "EnemyEtis-273");
				break;
			}
			case 4400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000215);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000260, EnemyEtis, "EnemyEtis-274");
				break;
			}
			case 4420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000216);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000261, EnemyEtis, "EnemyEtis-275");
				break;
			}
			case 4440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000217);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000262, EnemyEtis, "EnemyEtis-276");
				break;
			}
			case 4460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000218);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000263, EnemyEtis, "EnemyEtis-277");
				break;
			}
			case 4480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000219);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000264, EnemyEtis, "EnemyEtis-278");
				break;
			}
			case 4500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000220);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000265, EnemyEtis, "EnemyEtis-279");
				break;
			}
			case 4520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000221);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000266, EnemyEtis, "EnemyEtis-280");
				break;
			}
			case 4540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000222);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000267, EnemyEtis, "EnemyEtis-281");
				break;
			}
			case 4560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000223);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000268, EnemyEtis, "EnemyEtis-282");
				break;
			}
			case 4580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000224);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000269, EnemyEtis, "EnemyEtis-283");
				break;
			}
			case 4600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000225);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000270, EnemyEtis, "EnemyEtis-284");
				break;
			}
			case 4620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000226);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000271, EnemyEtis, "EnemyEtis-285");
				break;
			}
			case 4640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000227);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000272, EnemyEtis, "EnemyEtis-286");
				break;
			}
			case 4660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000228);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000273, EnemyEtis, "EnemyEtis-287");
				break;
			}
			case 4680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000229);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000274, EnemyEtis, "EnemyEtis-288");
				break;
			}
			case 4700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000230);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000275, EnemyEtis, "EnemyEtis-289");
				break;
			}
			case 4720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000231);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000276, EnemyEtis, "EnemyEtis-290");
				break;
			}
			case 4740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000232);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000277, EnemyEtis, "EnemyEtis-291");
				break;
			}
			case 4760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000233);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000278, EnemyEtis, "EnemyEtis-292");
				break;
			}
			case 4780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000234);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000279, EnemyEtis, "EnemyEtis-293");
				break;
			}
			case 4800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000235);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000280, EnemyEtis, "EnemyEtis-294");
				break;
			}
			case 4820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000236);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000281, EnemyEtis, "EnemyEtis-295");
				break;
			}
			case 4840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000237);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000282, EnemyEtis, "EnemyEtis-296");
				break;
			}
			case 4860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000238);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000283, EnemyEtis, "EnemyEtis-297");
				break;
			}
			case 4880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000239);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000284, EnemyEtis, "EnemyEtis-298");
				break;
			}
			case 4900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000240);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000285, EnemyEtis, "EnemyEtis-299");
				break;
			}
			case 4920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000241);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000286, EnemyEtis, "EnemyEtis-300");
				break;
			}
			case 4940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000242);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000287, EnemyEtis, "EnemyEtis-301");
				break;
			}
			case 4960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000243);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000288, EnemyEtis, "EnemyEtis-302");
				break;
			}
			case 4980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000244);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000289, EnemyEtis, "EnemyEtis-303");
				break;
			}
			case 5000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000245);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000290, EnemyEtis, "EnemyEtis-304");
				break;
			}
			case 5020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000246);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000291, EnemyEtis, "EnemyEtis-305");
				break;
			}
			case 5040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000247);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000292, EnemyEtis, "EnemyEtis-306");
				break;
			}
			case 5060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000248);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000293, EnemyEtis, "EnemyEtis-307");
				break;
			}
			case 5080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000249);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000294, EnemyEtis, "EnemyEtis-308");
				break;
			}
			case 5100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000250);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000295, EnemyEtis, "EnemyEtis-309");
				break;
			}
			case 5120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000251);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000296, EnemyEtis, "EnemyEtis-310");
				break;
			}
			case 5140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000252);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000297, EnemyEtis, "EnemyEtis-311");
				break;
			}
			case 5160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000253);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000298, EnemyEtis, "EnemyEtis-312");
				break;
			}
			case 5180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000254);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000299, EnemyEtis, "EnemyEtis-313");
				break;
			}
			case 5200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000255);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000300, EnemyEtis, "EnemyEtis-314");
				break;
			}
			case 5220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000256);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000301, EnemyEtis, "EnemyEtis-315");
				break;
			}
			case 5240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000257);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000302, EnemyEtis, "EnemyEtis-316");
				break;
			}
			case 5260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000258);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000303, EnemyEtis, "EnemyEtis-317");
				break;
			}
			case 5280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000259);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000304, EnemyEtis, "EnemyEtis-318");
				break;
			}
			case 5300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000260);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000305, EnemyEtis, "EnemyEtis-319");
				break;
			}
			case 5320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000261);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000306, EnemyEtis, "EnemyEtis-320");
				break;
			}
			case 5340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000262);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000307, EnemyEtis, "EnemyEtis-321");
				break;
			}
			case 5360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000263);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000308, EnemyEtis, "EnemyEtis-322");
				break;
			}
			case 5380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000264);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000309, EnemyEtis, "EnemyEtis-323");
				break;
			}
			case 5400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000265);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000310, EnemyEtis, "EnemyEtis-324");
				break;
			}
			case 5420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000266);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000311, EnemyEtis, "EnemyEtis-325");
				break;
			}
			case 5440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000267);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000312, EnemyEtis, "EnemyEtis-326");
				break;
			}
			case 5460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000268);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000313, EnemyEtis, "EnemyEtis-327");
				break;
			}
			case 5480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000269);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000314, EnemyEtis, "EnemyEtis-328");
				break;
			}
			case 5500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000270);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000315, EnemyEtis, "EnemyEtis-329");
				break;
			}
			case 5520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000271);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000316, EnemyEtis, "EnemyEtis-330");
				break;
			}
			case 5540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000272);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000317, EnemyEtis, "EnemyEtis-331");
				break;
			}
			case 5560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000273);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000318, EnemyEtis, "EnemyEtis-332");
				break;
			}
			case 5580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000274);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000319, EnemyEtis, "EnemyEtis-333");
				break;
			}
			case 5600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000275);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000320, EnemyEtis, "EnemyEtis-334");
				break;
			}
			case 5620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000276);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000321, EnemyEtis, "EnemyEtis-335");
				break;
			}
			case 5640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000277);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000322, EnemyEtis, "EnemyEtis-336");
				break;
			}
			case 5660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000278);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000323, EnemyEtis, "EnemyEtis-337");
				break;
			}
			case 5680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000279);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000324, EnemyEtis, "EnemyEtis-338");
				break;
			}
			case 5700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000280);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000325, EnemyEtis, "EnemyEtis-339");
				break;
			}
			case 5720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000281);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000326, EnemyEtis, "EnemyEtis-340");
				break;
			}
			case 5740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000282);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000327, EnemyEtis, "EnemyEtis-341");
				break;
			}
			case 5760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000283);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000328, EnemyEtis, "EnemyEtis-342");
				break;
			}
			case 5780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000284);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000329, EnemyEtis, "EnemyEtis-343");
				break;
			}
			case 5800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000285);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000330, EnemyEtis, "EnemyEtis-344");
				break;
			}
			case 5820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000286);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000331, EnemyEtis, "EnemyEtis-345");
				break;
			}
			case 5840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000287);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000332, EnemyEtis, "EnemyEtis-346");
				break;
			}
			case 5860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000288);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000333, EnemyEtis, "EnemyEtis-347");
				break;
			}
			case 5880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000289);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000334, EnemyEtis, "EnemyEtis-348");
				break;
			}
			case 5900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000290);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000335, EnemyEtis, "EnemyEtis-349");
				break;
			}
			case 5920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000291);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000336, EnemyEtis, "EnemyEtis-350");
				break;
			}
			case 5940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000292);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000337, EnemyEtis, "EnemyEtis-351");
				break;
			}
			case 5960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000293);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000338, EnemyEtis, "EnemyEtis-352");
				break;
			}
			case 5980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000294);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000339, EnemyEtis, "EnemyEtis-353");
				break;
			}
			case 6000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000295);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000340, EnemyEtis, "EnemyEtis-354");
				break;
			}
			case 6020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000296);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000341, EnemyEtis, "EnemyEtis-355");
				break;
			}
			case 6040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000297);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000342, EnemyEtis, "EnemyEtis-356");
				break;
			}
			case 6060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000298);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000343, EnemyEtis, "EnemyEtis-357");
				break;
			}
			case 6080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000299);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000344, EnemyEtis, "EnemyEtis-358");
				break;
			}
			case 6100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000300);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000345, EnemyEtis, "EnemyEtis-359");
				break;
			}
			case 6120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000301);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000346, EnemyEtis, "EnemyEtis-360");
				break;
			}
			case 6140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000302);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000347, EnemyEtis, "EnemyEtis-361");
				break;
			}
			case 6160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000303);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000348, EnemyEtis, "EnemyEtis-362");
				break;
			}
			case 6180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000304);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000349, EnemyEtis, "EnemyEtis-363");
				break;
			}
			case 6200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000305);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000350, EnemyEtis, "EnemyEtis-364");
				break;
			}
			case 6220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000306);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000351, EnemyEtis, "EnemyEtis-365");
				break;
			}
			case 6240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000307);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000352, EnemyEtis, "EnemyEtis-366");
				break;
			}
			case 6260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000308);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000353, EnemyEtis, "EnemyEtis-367");
				break;
			}
			case 6280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000309);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000354, EnemyEtis, "EnemyEtis-368");
				break;
			}
			case 6300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000310);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000355, EnemyEtis, "EnemyEtis-369");
				break;
			}
			case 6320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000311);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000356, EnemyEtis, "EnemyEtis-370");
				break;
			}
			case 6340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000312);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000357, EnemyEtis, "EnemyEtis-371");
				break;
			}
			case 6360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000313);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000358, EnemyEtis, "EnemyEtis-372");
				break;
			}
			case 6380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000314);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000359, EnemyEtis, "EnemyEtis-373");
				break;
			}
			case 6400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000315);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000360, EnemyEtis, "EnemyEtis-374");
				break;
			}
			case 6420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000316);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000361, EnemyEtis, "EnemyEtis-375");
				break;
			}
			case 6440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000317);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000362, EnemyEtis, "EnemyEtis-376");
				break;
			}
			case 6460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000318);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000363, EnemyEtis, "EnemyEtis-377");
				break;
			}
			case 6480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000319);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000364, EnemyEtis, "EnemyEtis-378");
				break;
			}
			case 6500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000320);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000365, EnemyEtis, "EnemyEtis-379");
				break;
			}
			case 6520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000321);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000366, EnemyEtis, "EnemyEtis-380");
				break;
			}
			case 6540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000322);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000367, EnemyEtis, "EnemyEtis-381");
				break;
			}
			case 6560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000323);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000368, EnemyEtis, "EnemyEtis-382");
				break;
			}
			case 6580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000324);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000369, EnemyEtis, "EnemyEtis-383");
				break;
			}
			case 6600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000325);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000370, EnemyEtis, "EnemyEtis-384");
				break;
			}
			case 6620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000326);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000371, EnemyEtis, "EnemyEtis-385");
				break;
			}
			case 6640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000327);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000372, EnemyEtis, "EnemyEtis-386");
				break;
			}
			case 6660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000328);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000373, EnemyEtis, "EnemyEtis-387");
				break;
			}
			case 6680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000329);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000374, EnemyEtis, "EnemyEtis-388");
				break;
			}
			case 6700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000330);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000375, EnemyEtis, "EnemyEtis-389");
				break;
			}
			case 6720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000331);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000376, EnemyEtis, "EnemyEtis-390");
				break;
			}
			case 6740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000332);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000377, EnemyEtis, "EnemyEtis-391");
				break;
			}
			case 6760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000333);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000378, EnemyEtis, "EnemyEtis-392");
				break;
			}
			case 6780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000334);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000379, EnemyEtis, "EnemyEtis-393");
				break;
			}
			case 6800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000335);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000380, EnemyEtis, "EnemyEtis-394");
				break;
			}
			case 6820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000336);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000381, EnemyEtis, "EnemyEtis-395");
				break;
			}
			case 6840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000337);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000382, EnemyEtis, "EnemyEtis-396");
				break;
			}
			case 6860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000338);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000383, EnemyEtis, "EnemyEtis-397");
				break;
			}
			case 6880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000339);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000384, EnemyEtis, "EnemyEtis-398");
				break;
			}
			case 6900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000340);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000385, EnemyEtis, "EnemyEtis-399");
				break;
			}
			case 6920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000341);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000386, EnemyEtis, "EnemyEtis-400");
				break;
			}
			case 6940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000342);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000387, EnemyEtis, "EnemyEtis-401");
				break;
			}
			case 6960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000343);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000388, EnemyEtis, "EnemyEtis-402");
				break;
			}
			case 6980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000344);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000389, EnemyEtis, "EnemyEtis-403");
				break;
			}
			case 7000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000345);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000390, EnemyEtis, "EnemyEtis-404");
				break;
			}
			case 7020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000346);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000391, EnemyEtis, "EnemyEtis-405");
				break;
			}
			case 7040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000347);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000392, EnemyEtis, "EnemyEtis-406");
				break;
			}
			case 7060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000348);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000393, EnemyEtis, "EnemyEtis-407");
				break;
			}
			case 7080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000349);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000394, EnemyEtis, "EnemyEtis-408");
				break;
			}
			case 7100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000350);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000395, EnemyEtis, "EnemyEtis-409");
				break;
			}
			case 7120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000351);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000396, EnemyEtis, "EnemyEtis-410");
				break;
			}
			case 7140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000352);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000397, EnemyEtis, "EnemyEtis-411");
				break;
			}
			case 7160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000353);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000398, EnemyEtis, "EnemyEtis-412");
				break;
			}
			case 7180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000354);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000399, EnemyEtis, "EnemyEtis-413");
				break;
			}
			case 7200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000355);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000400, EnemyEtis, "EnemyEtis-414");
				break;
			}
			case 7220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000356);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000401, EnemyEtis, "EnemyEtis-415");
				break;
			}
			case 7240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000357);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000402, EnemyEtis, "EnemyEtis-416");
				break;
			}
			case 7260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000358);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000403, EnemyEtis, "EnemyEtis-417");
				break;
			}
			case 7280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000359);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000404, EnemyEtis, "EnemyEtis-418");
				break;
			}
			case 7300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000360);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000405, EnemyEtis, "EnemyEtis-419");
				break;
			}
			case 7320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000361);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000406, EnemyEtis, "EnemyEtis-420");
				break;
			}
			case 7340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000362);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000407, EnemyEtis, "EnemyEtis-421");
				break;
			}
			case 7360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000363);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000408, EnemyEtis, "EnemyEtis-422");
				break;
			}
			case 7380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000364);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000409, EnemyEtis, "EnemyEtis-423");
				break;
			}
			case 7400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000365);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000410, EnemyEtis, "EnemyEtis-424");
				break;
			}
			case 7420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000366);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000411, EnemyEtis, "EnemyEtis-425");
				break;
			}
			case 7440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000367);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000412, EnemyEtis, "EnemyEtis-426");
				break;
			}
			case 7460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000368);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000413, EnemyEtis, "EnemyEtis-427");
				break;
			}
			case 7480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000369);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000414, EnemyEtis, "EnemyEtis-428");
				break;
			}
			case 7500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000370);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000415, EnemyEtis, "EnemyEtis-429");
				break;
			}
			case 7520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000371);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000416, EnemyEtis, "EnemyEtis-430");
				break;
			}
			case 7540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000372);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000417, EnemyEtis, "EnemyEtis-431");
				break;
			}
			case 7560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000373);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000418, EnemyEtis, "EnemyEtis-432");
				break;
			}
			case 7580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000374);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000419, EnemyEtis, "EnemyEtis-433");
				break;
			}
			case 7600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000375);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000420, EnemyEtis, "EnemyEtis-434");
				break;
			}
			case 7620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000376);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000421, EnemyEtis, "EnemyEtis-435");
				break;
			}
			case 7640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000377);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000422, EnemyEtis, "EnemyEtis-436");
				break;
			}
			case 7660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000378);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000423, EnemyEtis, "EnemyEtis-437");
				break;
			}
			case 7680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000379);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000424, EnemyEtis, "EnemyEtis-438");
				break;
			}
			case 7700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000380);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000425, EnemyEtis, "EnemyEtis-439");
				break;
			}
			case 7720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000381);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000426, EnemyEtis, "EnemyEtis-440");
				break;
			}
			case 7740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000382);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000427, EnemyEtis, "EnemyEtis-441");
				break;
			}
			case 7760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000383);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000428, EnemyEtis, "EnemyEtis-442");
				break;
			}
			case 7780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000384);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000429, EnemyEtis, "EnemyEtis-443");
				break;
			}
			case 7800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000385);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000430, EnemyEtis, "EnemyEtis-444");
				break;
			}
			case 7820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000386);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000431, EnemyEtis, "EnemyEtis-445");
				break;
			}
			case 7840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000387);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000432, EnemyEtis, "EnemyEtis-446");
				break;
			}
			case 7860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000388);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000433, EnemyEtis, "EnemyEtis-447");
				break;
			}
			case 7880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000389);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000434, EnemyEtis, "EnemyEtis-448");
				break;
			}
			case 7900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000390);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000435, EnemyEtis, "EnemyEtis-449");
				break;
			}
			case 7920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000391);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000436, EnemyEtis, "EnemyEtis-450");
				break;
			}
			case 7940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000392);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000437, EnemyEtis, "EnemyEtis-451");
				break;
			}
			case 7960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000393);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000438, EnemyEtis, "EnemyEtis-452");
				break;
			}
			case 7980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000394);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000439, EnemyEtis, "EnemyEtis-453");
				break;
			}
			case 8000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000395);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000440, EnemyEtis, "EnemyEtis-454");
				break;
			}
			case 8020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000396);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000441, EnemyEtis, "EnemyEtis-455");
				break;
			}
			case 8040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000397);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000442, EnemyEtis, "EnemyEtis-456");
				break;
			}
			case 8060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000398);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000443, EnemyEtis, "EnemyEtis-457");
				break;
			}
			case 8080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000399);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000444, EnemyEtis, "EnemyEtis-458");
				break;
			}
			case 8100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000400);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000445, EnemyEtis, "EnemyEtis-459");
				break;
			}
			case 8120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000401);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000446, EnemyEtis, "EnemyEtis-460");
				break;
			}
			case 8140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000402);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000447, EnemyEtis, "EnemyEtis-461");
				break;
			}
			case 8160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000403);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000448, EnemyEtis, "EnemyEtis-462");
				break;
			}
			case 8180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000404);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000449, EnemyEtis, "EnemyEtis-463");
				break;
			}
			case 8200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000405);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000450, EnemyEtis, "EnemyEtis-464");
				break;
			}
			case 8220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000406);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000451, EnemyEtis, "EnemyEtis-465");
				break;
			}
			case 8240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000407);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000452, EnemyEtis, "EnemyEtis-466");
				break;
			}
			case 8260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000408);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000453, EnemyEtis, "EnemyEtis-467");
				break;
			}
			case 8280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000409);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000454, EnemyEtis, "EnemyEtis-468");
				break;
			}
			case 8300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000410);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000455, EnemyEtis, "EnemyEtis-469");
				break;
			}
			case 8320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000411);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000456, EnemyEtis, "EnemyEtis-470");
				break;
			}
			case 8340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000412);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000457, EnemyEtis, "EnemyEtis-471");
				break;
			}
			case 8360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000413);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000458, EnemyEtis, "EnemyEtis-472");
				break;
			}
			case 8380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000414);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000459, EnemyEtis, "EnemyEtis-473");
				break;
			}
			case 8400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000415);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000460, EnemyEtis, "EnemyEtis-474");
				break;
			}
			case 8420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000416);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000461, EnemyEtis, "EnemyEtis-475");
				break;
			}
			case 8440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000417);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000462, EnemyEtis, "EnemyEtis-476");
				break;
			}
			case 8460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000418);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000463, EnemyEtis, "EnemyEtis-477");
				break;
			}
			case 8480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000419);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000464, EnemyEtis, "EnemyEtis-478");
				break;
			}
			case 8500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000420);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000465, EnemyEtis, "EnemyEtis-479");
				break;
			}
			case 8520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000421);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000466, EnemyEtis, "EnemyEtis-480");
				break;
			}
			case 8540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000422);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000467, EnemyEtis, "EnemyEtis-481");
				break;
			}
			case 8560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000423);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000468, EnemyEtis, "EnemyEtis-482");
				break;
			}
			case 8580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000424);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000469, EnemyEtis, "EnemyEtis-483");
				break;
			}
			case 8600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000425);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000470, EnemyEtis, "EnemyEtis-484");
				break;
			}
			case 8620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000426);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000471, EnemyEtis, "EnemyEtis-485");
				break;
			}
			case 8640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000427);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000472, EnemyEtis, "EnemyEtis-486");
				break;
			}
			case 8660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000428);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000473, EnemyEtis, "EnemyEtis-487");
				break;
			}
			case 8680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000429);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000474, EnemyEtis, "EnemyEtis-488");
				break;
			}
			case 8700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000430);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000475, EnemyEtis, "EnemyEtis-489");
				break;
			}
			case 8720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000431);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000476, EnemyEtis, "EnemyEtis-490");
				break;
			}
			case 8740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000432);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000477, EnemyEtis, "EnemyEtis-491");
				break;
			}
			case 8760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000433);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000478, EnemyEtis, "EnemyEtis-492");
				break;
			}
			case 8780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000434);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000479, EnemyEtis, "EnemyEtis-493");
				break;
			}
			case 8800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000435);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000480, EnemyEtis, "EnemyEtis-494");
				break;
			}
			case 8820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000436);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000481, EnemyEtis, "EnemyEtis-495");
				break;
			}
			case 8840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000437);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000482, EnemyEtis, "EnemyEtis-496");
				break;
			}
			case 8860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000438);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000483, EnemyEtis, "EnemyEtis-497");
				break;
			}
			case 8880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000439);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000484, EnemyEtis, "EnemyEtis-498");
				break;
			}
			case 8900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000440);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000485, EnemyEtis, "EnemyEtis-499");
				break;
			}
			case 8920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000441);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000486, EnemyEtis, "EnemyEtis-500");
				break;
			}
			case 8940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000442);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000487, EnemyEtis, "EnemyEtis-501");
				break;
			}
			case 8960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000443);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000488, EnemyEtis, "EnemyEtis-502");
				break;
			}
			case 8980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000444);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000489, EnemyEtis, "EnemyEtis-503");
				break;
			}
			case 9000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000445);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000490, EnemyEtis, "EnemyEtis-504");
				break;
			}
			case 9020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000446);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000491, EnemyEtis, "EnemyEtis-505");
				break;
			}
			case 9040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000447);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000492, EnemyEtis, "EnemyEtis-506");
				break;
			}
			case 9060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000448);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000493, EnemyEtis, "EnemyEtis-507");
				break;
			}
			case 9080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000449);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000494, EnemyEtis, "EnemyEtis-508");
				break;
			}
			case 9100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000450);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000495, EnemyEtis, "EnemyEtis-509");
				break;
			}
			case 9120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000451);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000496, EnemyEtis, "EnemyEtis-510");
				break;
			}
			case 9140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000452);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000497, EnemyEtis, "EnemyEtis-511");
				break;
			}
			case 9160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000453);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000498, EnemyEtis, "EnemyEtis-512");
				break;
			}
			case 9180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000454);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000499, EnemyEtis, "EnemyEtis-513");
				break;
			}
			case 9200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000455);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000500, EnemyEtis, "EnemyEtis-514");
				break;
			}
			case 9220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000456);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000501, EnemyEtis, "EnemyEtis-515");
				break;
			}
			case 9240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000457);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000502, EnemyEtis, "EnemyEtis-516");
				break;
			}
			case 9260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000458);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000503, EnemyEtis, "EnemyEtis-517");
				break;
			}
			case 9280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000459);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000504, EnemyEtis, "EnemyEtis-518");
				break;
			}
			case 9300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000460);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000505, EnemyEtis, "EnemyEtis-519");
				break;
			}
			case 9320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000461);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000506, EnemyEtis, "EnemyEtis-520");
				break;
			}
			case 9340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000462);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000507, EnemyEtis, "EnemyEtis-521");
				break;
			}
			case 9360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000463);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000508, EnemyEtis, "EnemyEtis-522");
				break;
			}
			case 9380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000464);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000509, EnemyEtis, "EnemyEtis-523");
				break;
			}
			case 9400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000465);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000510, EnemyEtis, "EnemyEtis-524");
				break;
			}
			case 9420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000466);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000511, EnemyEtis, "EnemyEtis-525");
				break;
			}
			case 9440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000467);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000512, EnemyEtis, "EnemyEtis-526");
				break;
			}
			case 9460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000468);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000513, EnemyEtis, "EnemyEtis-527");
				break;
			}
			case 9480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000469);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000514, EnemyEtis, "EnemyEtis-528");
				break;
			}
			case 9500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000470);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000515, EnemyEtis, "EnemyEtis-529");
				break;
			}
			case 9520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000471);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000516, EnemyEtis, "EnemyEtis-530");
				break;
			}
			case 9540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000472);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000517, EnemyEtis, "EnemyEtis-531");
				break;
			}
			case 9560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000473);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000518, EnemyEtis, "EnemyEtis-532");
				break;
			}
			case 9580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000474);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000519, EnemyEtis, "EnemyEtis-533");
				break;
			}
			case 9600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000475);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000520, EnemyEtis, "EnemyEtis-534");
				break;
			}
			case 9620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000476);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000521, EnemyEtis, "EnemyEtis-535");
				break;
			}
			case 9640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000477);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000522, EnemyEtis, "EnemyEtis-536");
				break;
			}
			case 9660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000478);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000523, EnemyEtis, "EnemyEtis-537");
				break;
			}
			case 9680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000479);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000524, EnemyEtis, "EnemyEtis-538");
				break;
			}
			case 9700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000480);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000525, EnemyEtis, "EnemyEtis-539");
				break;
			}
			case 9720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000481);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000526, EnemyEtis, "EnemyEtis-540");
				break;
			}
			case 9740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000482);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000527, EnemyEtis, "EnemyEtis-541");
				break;
			}
			case 9760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000483);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000528, EnemyEtis, "EnemyEtis-542");
				break;
			}
			case 9780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000484);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000529, EnemyEtis, "EnemyEtis-543");
				break;
			}
			case 9800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000485);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000530, EnemyEtis, "EnemyEtis-544");
				break;
			}
			case 9820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000486);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000531, EnemyEtis, "EnemyEtis-545");
				break;
			}
			case 9840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000487);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000532, EnemyEtis, "EnemyEtis-546");
				break;
			}
			case 9860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000488);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000533, EnemyEtis, "EnemyEtis-547");
				break;
			}
			case 9880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000489);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000534, EnemyEtis, "EnemyEtis-548");
				break;
			}
			case 9900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000490);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000535, EnemyEtis, "EnemyEtis-549");
				break;
			}
			case 9920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000491);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000536, EnemyEtis, "EnemyEtis-550");
				break;
			}
			case 9940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000492);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000537, EnemyEtis, "EnemyEtis-551");
				break;
			}
			case 9960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000493);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000538, EnemyEtis, "EnemyEtis-552");
				break;
			}
			case 9980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000494);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000539, EnemyEtis, "EnemyEtis-553");
				break;
			}
			case 10000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000495);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000540, EnemyEtis, "EnemyEtis-554");
				break;
			}
			case 10020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000496);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000541, EnemyEtis, "EnemyEtis-555");
				break;
			}
			case 10040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000497);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000542, EnemyEtis, "EnemyEtis-556");
				break;
			}
			case 10060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000498);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000543, EnemyEtis, "EnemyEtis-557");
				break;
			}
			case 10080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000499);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000544, EnemyEtis, "EnemyEtis-558");
				break;
			}
			case 10100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000500);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000545, EnemyEtis, "EnemyEtis-559");
				break;
			}
			case 10120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000501);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000546, EnemyEtis, "EnemyEtis-560");
				break;
			}
			case 10140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000502);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000547, EnemyEtis, "EnemyEtis-561");
				break;
			}
			case 10160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000503);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000548, EnemyEtis, "EnemyEtis-562");
				break;
			}
			case 10180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000504);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000549, EnemyEtis, "EnemyEtis-563");
				break;
			}
			case 10200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000505);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000550, EnemyEtis, "EnemyEtis-564");
				break;
			}
			case 10220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000506);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000551, EnemyEtis, "EnemyEtis-565");
				break;
			}
			case 10240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000507);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000552, EnemyEtis, "EnemyEtis-566");
				break;
			}
			case 10260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000508);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000553, EnemyEtis, "EnemyEtis-567");
				break;
			}
			case 10280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000509);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000554, EnemyEtis, "EnemyEtis-568");
				break;
			}
			case 10300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000510);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000555, EnemyEtis, "EnemyEtis-569");
				break;
			}
			case 10320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000511);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000556, EnemyEtis, "EnemyEtis-570");
				break;
			}
			case 10340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000512);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000557, EnemyEtis, "EnemyEtis-571");
				break;
			}
			case 10360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000513);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000558, EnemyEtis, "EnemyEtis-572");
				break;
			}
			case 10380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000514);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000559, EnemyEtis, "EnemyEtis-573");
				break;
			}
			case 10400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000515);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000560, EnemyEtis, "EnemyEtis-574");
				break;
			}
			case 10420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000516);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000561, EnemyEtis, "EnemyEtis-575");
				break;
			}
			case 10440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000517);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000562, EnemyEtis, "EnemyEtis-576");
				break;
			}
			case 10460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000518);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000563, EnemyEtis, "EnemyEtis-577");
				break;
			}
			case 10480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000519);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000564, EnemyEtis, "EnemyEtis-578");
				break;
			}
			case 10500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000520);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000565, EnemyEtis, "EnemyEtis-579");
				break;
			}
			case 10520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000521);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000566, EnemyEtis, "EnemyEtis-580");
				break;
			}
			case 10540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000522);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000567, EnemyEtis, "EnemyEtis-581");
				break;
			}
			case 10560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000523);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000568, EnemyEtis, "EnemyEtis-582");
				break;
			}
			case 10580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000524);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000569, EnemyEtis, "EnemyEtis-583");
				break;
			}
			case 10600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000525);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000570, EnemyEtis, "EnemyEtis-584");
				break;
			}
			case 10620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000526);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000571, EnemyEtis, "EnemyEtis-585");
				break;
			}
			case 10640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000527);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000572, EnemyEtis, "EnemyEtis-586");
				break;
			}
			case 10660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000528);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000573, EnemyEtis, "EnemyEtis-587");
				break;
			}
			case 10680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000529);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000574, EnemyEtis, "EnemyEtis-588");
				break;
			}
			case 10700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000530);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000575, EnemyEtis, "EnemyEtis-589");
				break;
			}
			case 10720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000531);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000576, EnemyEtis, "EnemyEtis-590");
				break;
			}
			case 10740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000532);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000577, EnemyEtis, "EnemyEtis-591");
				break;
			}
			case 10760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000533);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000578, EnemyEtis, "EnemyEtis-592");
				break;
			}
			case 10780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000534);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000579, EnemyEtis, "EnemyEtis-593");
				break;
			}
			case 10800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000535);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000580, EnemyEtis, "EnemyEtis-594");
				break;
			}
			case 10820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000536);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000581, EnemyEtis, "EnemyEtis-595");
				break;
			}
			case 10840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000537);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000582, EnemyEtis, "EnemyEtis-596");
				break;
			}
			case 10860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000538);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000583, EnemyEtis, "EnemyEtis-597");
				break;
			}
			case 10880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000539);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000584, EnemyEtis, "EnemyEtis-598");
				break;
			}
			case 10900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000540);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000585, EnemyEtis, "EnemyEtis-599");
				break;
			}
			case 10920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000541);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000586, EnemyEtis, "EnemyEtis-600");
				break;
			}
			case 10940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000542);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000587, EnemyEtis, "EnemyEtis-601");
				break;
			}
			case 10960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000543);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000588, EnemyEtis, "EnemyEtis-602");
				break;
			}
			case 10980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000544);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000589, EnemyEtis, "EnemyEtis-603");
				break;
			}
			case 11000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000545);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000590, EnemyEtis, "EnemyEtis-604");
				break;
			}
			case 11020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000546);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000591, EnemyEtis, "EnemyEtis-605");
				break;
			}
			case 11040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000547);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000592, EnemyEtis, "EnemyEtis-606");
				break;
			}
			case 11060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000548);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000593, EnemyEtis, "EnemyEtis-607");
				break;
			}
			case 11080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000549);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000594, EnemyEtis, "EnemyEtis-608");
				break;
			}
			case 11100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000550);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000595, EnemyEtis, "EnemyEtis-609");
				break;
			}
			case 11120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000551);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000596, EnemyEtis, "EnemyEtis-610");
				break;
			}
			case 11140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000552);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000597, EnemyEtis, "EnemyEtis-611");
				break;
			}
			case 11160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000553);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000598, EnemyEtis, "EnemyEtis-612");
				break;
			}
			case 11180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000554);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000599, EnemyEtis, "EnemyEtis-613");
				break;
			}
			case 11200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000555);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000600, EnemyEtis, "EnemyEtis-614");
				break;
			}
			case 11220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000556);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000601, EnemyEtis, "EnemyEtis-615");
				break;
			}
			case 11240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000557);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000602, EnemyEtis, "EnemyEtis-616");
				break;
			}
			case 11260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000558);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000603, EnemyEtis, "EnemyEtis-617");
				break;
			}
			case 11280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000559);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000604, EnemyEtis, "EnemyEtis-618");
				break;
			}
			case 11300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000560);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000605, EnemyEtis, "EnemyEtis-619");
				break;
			}
			case 11320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000561);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000606, EnemyEtis, "EnemyEtis-620");
				break;
			}
			case 11340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000562);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000607, EnemyEtis, "EnemyEtis-621");
				break;
			}
			case 11360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000563);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000608, EnemyEtis, "EnemyEtis-622");
				break;
			}
			case 11380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000564);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000609, EnemyEtis, "EnemyEtis-623");
				break;
			}
			case 11400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000565);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000610, EnemyEtis, "EnemyEtis-624");
				break;
			}
			case 11420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000566);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000611, EnemyEtis, "EnemyEtis-625");
				break;
			}
			case 11440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000567);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000612, EnemyEtis, "EnemyEtis-626");
				break;
			}
			case 11460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000568);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000613, EnemyEtis, "EnemyEtis-627");
				break;
			}
			case 11480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000569);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000614, EnemyEtis, "EnemyEtis-628");
				break;
			}
			case 11500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000570);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000615, EnemyEtis, "EnemyEtis-629");
				break;
			}
			case 11520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000571);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000616, EnemyEtis, "EnemyEtis-630");
				break;
			}
			case 11540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000572);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000617, EnemyEtis, "EnemyEtis-631");
				break;
			}
			case 11560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000573);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000618, EnemyEtis, "EnemyEtis-632");
				break;
			}
			case 11580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000574);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000619, EnemyEtis, "EnemyEtis-633");
				break;
			}
			case 11600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000575);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000620, EnemyEtis, "EnemyEtis-634");
				break;
			}
			case 11620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000576);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000621, EnemyEtis, "EnemyEtis-635");
				break;
			}
			case 11640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000577);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000622, EnemyEtis, "EnemyEtis-636");
				break;
			}
			case 11660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000578);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000623, EnemyEtis, "EnemyEtis-637");
				break;
			}
			case 11680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000579);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000624, EnemyEtis, "EnemyEtis-638");
				break;
			}
			case 11700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000580);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000625, EnemyEtis, "EnemyEtis-639");
				break;
			}
			case 11720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000581);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000626, EnemyEtis, "EnemyEtis-640");
				break;
			}
			case 11740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000582);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000627, EnemyEtis, "EnemyEtis-641");
				break;
			}
			case 11760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000583);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000628, EnemyEtis, "EnemyEtis-642");
				break;
			}
			case 11780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000584);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000629, EnemyEtis, "EnemyEtis-643");
				break;
			}
			case 11800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000585);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000630, EnemyEtis, "EnemyEtis-644");
				break;
			}
			case 11820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000586);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000631, EnemyEtis, "EnemyEtis-645");
				break;
			}
			case 11840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000587);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000632, EnemyEtis, "EnemyEtis-646");
				break;
			}
			case 11860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000588);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000633, EnemyEtis, "EnemyEtis-647");
				break;
			}
			case 11880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000589);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000634, EnemyEtis, "EnemyEtis-648");
				break;
			}
			case 11900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000590);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000635, EnemyEtis, "EnemyEtis-649");
				break;
			}
			case 11920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000591);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000636, EnemyEtis, "EnemyEtis-650");
				break;
			}
			case 11940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000592);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000637, EnemyEtis, "EnemyEtis-651");
				break;
			}
			case 11960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000593);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000638, EnemyEtis, "EnemyEtis-652");
				break;
			}
			case 11980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000594);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000639, EnemyEtis, "EnemyEtis-653");
				break;
			}
			case 12000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000595);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000640, EnemyEtis, "EnemyEtis-654");
				break;
			}
			case 12020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000596);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000641, EnemyEtis, "EnemyEtis-655");
				break;
			}
			case 12040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000597);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000642, EnemyEtis, "EnemyEtis-656");
				break;
			}
			case 12060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000598);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000643, EnemyEtis, "EnemyEtis-657");
				break;
			}
			case 12080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000599);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000644, EnemyEtis, "EnemyEtis-658");
				break;
			}
			case 12100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000600);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000645, EnemyEtis, "EnemyEtis-659");
				break;
			}
			case 12120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000601);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000646, EnemyEtis, "EnemyEtis-660");
				break;
			}
			case 12140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000602);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000647, EnemyEtis, "EnemyEtis-661");
				break;
			}
			case 12160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000603);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000648, EnemyEtis, "EnemyEtis-662");
				break;
			}
			case 12180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000604);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000649, EnemyEtis, "EnemyEtis-663");
				break;
			}
			case 12200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000605);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000650, EnemyEtis, "EnemyEtis-664");
				break;
			}
			case 12220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000606);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000651, EnemyEtis, "EnemyEtis-665");
				break;
			}
			case 12240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000607);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000652, EnemyEtis, "EnemyEtis-666");
				break;
			}
			case 12260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000608);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000653, EnemyEtis, "EnemyEtis-667");
				break;
			}
			case 12280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000609);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000654, EnemyEtis, "EnemyEtis-668");
				break;
			}
			case 12300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000610);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000655, EnemyEtis, "EnemyEtis-669");
				break;
			}
			case 12320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000611);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000656, EnemyEtis, "EnemyEtis-670");
				break;
			}
			case 12340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000612);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000657, EnemyEtis, "EnemyEtis-671");
				break;
			}
			case 12360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000613);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000658, EnemyEtis, "EnemyEtis-672");
				break;
			}
			case 12380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000614);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000659, EnemyEtis, "EnemyEtis-673");
				break;
			}
			case 12400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000615);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000660, EnemyEtis, "EnemyEtis-674");
				break;
			}
			case 12420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000616);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000661, EnemyEtis, "EnemyEtis-675");
				break;
			}
			case 12440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000617);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000662, EnemyEtis, "EnemyEtis-676");
				break;
			}
			case 12460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000618);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000663, EnemyEtis, "EnemyEtis-677");
				break;
			}
			case 12480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000619);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000664, EnemyEtis, "EnemyEtis-678");
				break;
			}
			case 12500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000620);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000665, EnemyEtis, "EnemyEtis-679");
				break;
			}
			case 12520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000621);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000666, EnemyEtis, "EnemyEtis-680");
				break;
			}
			case 12540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000622);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000667, EnemyEtis, "EnemyEtis-681");
				break;
			}
			case 12560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000623);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000668, EnemyEtis, "EnemyEtis-682");
				break;
			}
			case 12580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000624);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000669, EnemyEtis, "EnemyEtis-683");
				break;
			}
			case 12600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000625);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000670, EnemyEtis, "EnemyEtis-684");
				break;
			}
			case 12620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000626);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000671, EnemyEtis, "EnemyEtis-685");
				break;
			}
			case 12640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000627);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000672, EnemyEtis, "EnemyEtis-686");
				break;
			}
			case 12660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000628);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000673, EnemyEtis, "EnemyEtis-687");
				break;
			}
			case 12680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000629);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000674, EnemyEtis, "EnemyEtis-688");
				break;
			}
			case 12700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000630);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000675, EnemyEtis, "EnemyEtis-689");
				break;
			}
			case 12720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000631);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000676, EnemyEtis, "EnemyEtis-690");
				break;
			}
			case 12740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000632);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000677, EnemyEtis, "EnemyEtis-691");
				break;
			}
			case 12760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000633);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000678, EnemyEtis, "EnemyEtis-692");
				break;
			}
			case 12780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000634);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000679, EnemyEtis, "EnemyEtis-693");
				break;
			}
			case 12800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000635);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000680, EnemyEtis, "EnemyEtis-694");
				break;
			}
			case 12820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000636);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000681, EnemyEtis, "EnemyEtis-695");
				break;
			}
			case 12840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000637);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000682, EnemyEtis, "EnemyEtis-696");
				break;
			}
			case 12860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000638);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000683, EnemyEtis, "EnemyEtis-697");
				break;
			}
			case 12880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000639);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000684, EnemyEtis, "EnemyEtis-698");
				break;
			}
			case 12900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000640);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000685, EnemyEtis, "EnemyEtis-699");
				break;
			}
			case 12920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000641);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000686, EnemyEtis, "EnemyEtis-700");
				break;
			}
			case 12940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000642);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000687, EnemyEtis, "EnemyEtis-701");
				break;
			}
			case 12960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000643);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000688, EnemyEtis, "EnemyEtis-702");
				break;
			}
			case 12980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000644);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000689, EnemyEtis, "EnemyEtis-703");
				break;
			}
			case 13000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000645);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000690, EnemyEtis, "EnemyEtis-704");
				break;
			}
			case 13020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000646);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000691, EnemyEtis, "EnemyEtis-705");
				break;
			}
			case 13040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000647);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000692, EnemyEtis, "EnemyEtis-706");
				break;
			}
			case 13060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000648);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000693, EnemyEtis, "EnemyEtis-707");
				break;
			}
			case 13080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000649);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000694, EnemyEtis, "EnemyEtis-708");
				break;
			}
			case 13100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000650);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000695, EnemyEtis, "EnemyEtis-709");
				break;
			}
			case 13120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000651);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000696, EnemyEtis, "EnemyEtis-710");
				break;
			}
			case 13140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000652);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000697, EnemyEtis, "EnemyEtis-711");
				break;
			}
			case 13160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000653);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000698, EnemyEtis, "EnemyEtis-712");
				break;
			}
			case 13180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000654);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000699, EnemyEtis, "EnemyEtis-713");
				break;
			}
			case 13200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000655);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000700, EnemyEtis, "EnemyEtis-714");
				break;
			}
			case 13220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000656);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000701, EnemyEtis, "EnemyEtis-715");
				break;
			}
			case 13240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000657);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000702, EnemyEtis, "EnemyEtis-716");
				break;
			}
			case 13260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000658);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000703, EnemyEtis, "EnemyEtis-717");
				break;
			}
			case 13280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000659);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000704, EnemyEtis, "EnemyEtis-718");
				break;
			}
			case 13300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000660);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000705, EnemyEtis, "EnemyEtis-719");
				break;
			}
			case 13320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000661);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000706, EnemyEtis, "EnemyEtis-720");
				break;
			}
			case 13340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000662);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000707, EnemyEtis, "EnemyEtis-721");
				break;
			}
			case 13360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000663);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000708, EnemyEtis, "EnemyEtis-722");
				break;
			}
			case 13380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000664);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000709, EnemyEtis, "EnemyEtis-723");
				break;
			}
			case 13400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000665);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000710, EnemyEtis, "EnemyEtis-724");
				break;
			}
			case 13420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000666);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000711, EnemyEtis, "EnemyEtis-725");
				break;
			}
			case 13440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000667);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000712, EnemyEtis, "EnemyEtis-726");
				break;
			}
			case 13460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000668);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000713, EnemyEtis, "EnemyEtis-727");
				break;
			}
			case 13480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000669);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000714, EnemyEtis, "EnemyEtis-728");
				break;
			}
			case 13500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000670);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000715, EnemyEtis, "EnemyEtis-729");
				break;
			}
			case 13520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000671);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000716, EnemyEtis, "EnemyEtis-730");
				break;
			}
			case 13540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000672);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000717, EnemyEtis, "EnemyEtis-731");
				break;
			}
			case 13560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000673);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000718, EnemyEtis, "EnemyEtis-732");
				break;
			}
			case 13580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000674);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000719, EnemyEtis, "EnemyEtis-733");
				break;
			}
			case 13600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000675);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000720, EnemyEtis, "EnemyEtis-734");
				break;
			}
			case 13620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000676);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000721, EnemyEtis, "EnemyEtis-735");
				break;
			}
			case 13640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000677);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000722, EnemyEtis, "EnemyEtis-736");
				break;
			}
			case 13660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000678);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000723, EnemyEtis, "EnemyEtis-737");
				break;
			}
			case 13680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000679);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000724, EnemyEtis, "EnemyEtis-738");
				break;
			}
			case 13700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000680);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000725, EnemyEtis, "EnemyEtis-739");
				break;
			}
			case 13720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000681);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000726, EnemyEtis, "EnemyEtis-740");
				break;
			}
			case 13740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000682);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000727, EnemyEtis, "EnemyEtis-741");
				break;
			}
			case 13760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000683);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000728, EnemyEtis, "EnemyEtis-742");
				break;
			}
			case 13780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000684);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000729, EnemyEtis, "EnemyEtis-743");
				break;
			}
			case 13800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000685);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000730, EnemyEtis, "EnemyEtis-744");
				break;
			}
			case 13820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000686);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000731, EnemyEtis, "EnemyEtis-745");
				break;
			}
			case 13840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000687);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000732, EnemyEtis, "EnemyEtis-746");
				break;
			}
			case 13860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000688);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000733, EnemyEtis, "EnemyEtis-747");
				break;
			}
			case 13880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000689);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000734, EnemyEtis, "EnemyEtis-748");
				break;
			}
			case 13900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000690);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000735, EnemyEtis, "EnemyEtis-749");
				break;
			}
			case 13920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000691);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000736, EnemyEtis, "EnemyEtis-750");
				break;
			}
			case 13940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000692);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000737, EnemyEtis, "EnemyEtis-751");
				break;
			}
			case 13960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000693);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000738, EnemyEtis, "EnemyEtis-752");
				break;
			}
			case 13980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000694);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000739, EnemyEtis, "EnemyEtis-753");
				break;
			}
			case 14000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000695);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000740, EnemyEtis, "EnemyEtis-754");
				break;
			}
			case 14020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000696);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000741, EnemyEtis, "EnemyEtis-755");
				break;
			}
			case 14040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000697);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000742, EnemyEtis, "EnemyEtis-756");
				break;
			}
			case 14060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000698);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000743, EnemyEtis, "EnemyEtis-757");
				break;
			}
			case 14080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000699);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000744, EnemyEtis, "EnemyEtis-758");
				break;
			}
			case 14100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000700);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000745, EnemyEtis, "EnemyEtis-759");
				break;
			}
			case 14120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000701);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000746, EnemyEtis, "EnemyEtis-760");
				break;
			}
			case 14140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000702);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000747, EnemyEtis, "EnemyEtis-761");
				break;
			}
			case 14160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000703);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000748, EnemyEtis, "EnemyEtis-762");
				break;
			}
			case 14180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000704);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000749, EnemyEtis, "EnemyEtis-763");
				break;
			}
			case 14200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000705);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000750, EnemyEtis, "EnemyEtis-764");
				break;
			}
			case 14220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000706);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000751, EnemyEtis, "EnemyEtis-765");
				break;
			}
			case 14240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000707);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000752, EnemyEtis, "EnemyEtis-766");
				break;
			}
			case 14260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000708);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000753, EnemyEtis, "EnemyEtis-767");
				break;
			}
			case 14280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000709);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000754, EnemyEtis, "EnemyEtis-768");
				break;
			}
			case 14300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000710);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000755, EnemyEtis, "EnemyEtis-769");
				break;
			}
			case 14320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000711);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000756, EnemyEtis, "EnemyEtis-770");
				break;
			}
			case 14340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000712);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000757, EnemyEtis, "EnemyEtis-771");
				break;
			}
			case 14360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000713);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000758, EnemyEtis, "EnemyEtis-772");
				break;
			}
			case 14380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000714);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000759, EnemyEtis, "EnemyEtis-773");
				break;
			}
			case 14400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000715);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000760, EnemyEtis, "EnemyEtis-774");
				break;
			}
			case 14420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000716);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000761, EnemyEtis, "EnemyEtis-775");
				break;
			}
			case 14440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000717);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000762, EnemyEtis, "EnemyEtis-776");
				break;
			}
			case 14460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000718);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000763, EnemyEtis, "EnemyEtis-777");
				break;
			}
			case 14480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000719);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000764, EnemyEtis, "EnemyEtis-778");
				break;
			}
			case 14500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000720);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000765, EnemyEtis, "EnemyEtis-779");
				break;
			}
			case 14520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000721);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000766, EnemyEtis, "EnemyEtis-780");
				break;
			}
			case 14540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000722);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000767, EnemyEtis, "EnemyEtis-781");
				break;
			}
			case 14560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000723);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000768, EnemyEtis, "EnemyEtis-782");
				break;
			}
			case 14580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000724);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000769, EnemyEtis, "EnemyEtis-783");
				break;
			}
			case 14600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000725);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000770, EnemyEtis, "EnemyEtis-784");
				break;
			}
			case 14620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000726);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000771, EnemyEtis, "EnemyEtis-785");
				break;
			}
			case 14640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000727);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000772, EnemyEtis, "EnemyEtis-786");
				break;
			}
			case 14660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000728);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000773, EnemyEtis, "EnemyEtis-787");
				break;
			}
			case 14680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000729);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000774, EnemyEtis, "EnemyEtis-788");
				break;
			}
			case 14700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000730);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000775, EnemyEtis, "EnemyEtis-789");
				break;
			}
			case 14720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000731);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000776, EnemyEtis, "EnemyEtis-790");
				break;
			}
			case 14740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000732);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000777, EnemyEtis, "EnemyEtis-791");
				break;
			}
			case 14760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000733);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000778, EnemyEtis, "EnemyEtis-792");
				break;
			}
			case 14780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000734);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000779, EnemyEtis, "EnemyEtis-793");
				break;
			}
			case 14800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000735);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000780, EnemyEtis, "EnemyEtis-794");
				break;
			}
			case 14820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000736);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000781, EnemyEtis, "EnemyEtis-795");
				break;
			}
			case 14840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000737);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000782, EnemyEtis, "EnemyEtis-796");
				break;
			}
			case 14860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000738);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000783, EnemyEtis, "EnemyEtis-797");
				break;
			}
			case 14880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000739);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000784, EnemyEtis, "EnemyEtis-798");
				break;
			}
			case 14900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000740);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000785, EnemyEtis, "EnemyEtis-799");
				break;
			}
			case 14920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000741);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000786, EnemyEtis, "EnemyEtis-800");
				break;
			}
			case 14940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000742);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000787, EnemyEtis, "EnemyEtis-801");
				break;
			}
			case 14960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000743);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000788, EnemyEtis, "EnemyEtis-802");
				break;
			}
			case 14980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000744);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000789, EnemyEtis, "EnemyEtis-803");
				break;
			}
			case 15000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000745);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000790, EnemyEtis, "EnemyEtis-804");
				break;
			}
			case 15020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000746);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000791, EnemyEtis, "EnemyEtis-805");
				break;
			}
			case 15040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000747);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000792, EnemyEtis, "EnemyEtis-806");
				break;
			}
			case 15060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000748);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000793, EnemyEtis, "EnemyEtis-807");
				break;
			}
			case 15080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000749);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000794, EnemyEtis, "EnemyEtis-808");
				break;
			}
			case 15100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000750);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000795, EnemyEtis, "EnemyEtis-809");
				break;
			}
			case 15120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000751);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000796, EnemyEtis, "EnemyEtis-810");
				break;
			}
			case 15140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000752);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000797, EnemyEtis, "EnemyEtis-811");
				break;
			}
			case 15160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000753);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000798, EnemyEtis, "EnemyEtis-812");
				break;
			}
			case 15180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000754);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000799, EnemyEtis, "EnemyEtis-813");
				break;
			}
			case 15200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000755);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000800, EnemyEtis, "EnemyEtis-814");
				break;
			}
			case 15220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000756);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000801, EnemyEtis, "EnemyEtis-815");
				break;
			}
			case 15240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000757);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000802, EnemyEtis, "EnemyEtis-816");
				break;
			}
			case 15260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000758);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000803, EnemyEtis, "EnemyEtis-817");
				break;
			}
			case 15280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000759);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000804, EnemyEtis, "EnemyEtis-818");
				break;
			}
			case 15300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000760);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000805, EnemyEtis, "EnemyEtis-819");
				break;
			}
			case 15320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000761);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000806, EnemyEtis, "EnemyEtis-820");
				break;
			}
			case 15340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000762);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000807, EnemyEtis, "EnemyEtis-821");
				break;
			}
			case 15360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000763);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000808, EnemyEtis, "EnemyEtis-822");
				break;
			}
			case 15380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000764);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000809, EnemyEtis, "EnemyEtis-823");
				break;
			}
			case 15400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000765);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000810, EnemyEtis, "EnemyEtis-824");
				break;
			}
			case 15420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000766);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000811, EnemyEtis, "EnemyEtis-825");
				break;
			}
			case 15440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000767);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000812, EnemyEtis, "EnemyEtis-826");
				break;
			}
			case 15460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000768);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000813, EnemyEtis, "EnemyEtis-827");
				break;
			}
			case 15480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000769);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000814, EnemyEtis, "EnemyEtis-828");
				break;
			}
			case 15500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000770);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000815, EnemyEtis, "EnemyEtis-829");
				break;
			}
			case 15520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000771);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000816, EnemyEtis, "EnemyEtis-830");
				break;
			}
			case 15540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000772);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000817, EnemyEtis, "EnemyEtis-831");
				break;
			}
			case 15560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000773);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000818, EnemyEtis, "EnemyEtis-832");
				break;
			}
			case 15580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000774);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000819, EnemyEtis, "EnemyEtis-833");
				break;
			}
			case 15600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000775);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000820, EnemyEtis, "EnemyEtis-834");
				break;
			}
			case 15620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000776);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000821, EnemyEtis, "EnemyEtis-835");
				break;
			}
			case 15640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000777);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000822, EnemyEtis, "EnemyEtis-836");
				break;
			}
			case 15660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000778);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000823, EnemyEtis, "EnemyEtis-837");
				break;
			}
			case 15680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000779);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000824, EnemyEtis, "EnemyEtis-838");
				break;
			}
			case 15700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000780);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000825, EnemyEtis, "EnemyEtis-839");
				break;
			}
			case 15720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000781);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000826, EnemyEtis, "EnemyEtis-840");
				break;
			}
			case 15740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000782);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000827, EnemyEtis, "EnemyEtis-841");
				break;
			}
			case 15760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000783);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000828, EnemyEtis, "EnemyEtis-842");
				break;
			}
			case 15780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000784);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000829, EnemyEtis, "EnemyEtis-843");
				break;
			}
			case 15800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000785);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000830, EnemyEtis, "EnemyEtis-844");
				break;
			}
			case 15820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000786);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000831, EnemyEtis, "EnemyEtis-845");
				break;
			}
			case 15840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000787);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000832, EnemyEtis, "EnemyEtis-846");
				break;
			}
			case 15860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000788);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000833, EnemyEtis, "EnemyEtis-847");
				break;
			}
			case 15880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000789);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000834, EnemyEtis, "EnemyEtis-848");
				break;
			}
			case 15900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000790);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000835, EnemyEtis, "EnemyEtis-849");
				break;
			}
			case 15920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000791);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000836, EnemyEtis, "EnemyEtis-850");
				break;
			}
			case 15940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000792);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000837, EnemyEtis, "EnemyEtis-851");
				break;
			}
			case 15960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000793);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000838, EnemyEtis, "EnemyEtis-852");
				break;
			}
			case 15980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000794);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000839, EnemyEtis, "EnemyEtis-853");
				break;
			}
			case 16000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000795);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000840, EnemyEtis, "EnemyEtis-854");
				break;
			}
			case 16020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000796);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000841, EnemyEtis, "EnemyEtis-855");
				break;
			}
			case 16040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000797);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000842, EnemyEtis, "EnemyEtis-856");
				break;
			}
			case 16060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000798);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000843, EnemyEtis, "EnemyEtis-857");
				break;
			}
			case 16080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000799);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000844, EnemyEtis, "EnemyEtis-858");
				break;
			}
			case 16100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000800);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000845, EnemyEtis, "EnemyEtis-859");
				break;
			}
			case 16120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000801);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000846, EnemyEtis, "EnemyEtis-860");
				break;
			}
			case 16140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000802);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000847, EnemyEtis, "EnemyEtis-861");
				break;
			}
			case 16160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000803);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000848, EnemyEtis, "EnemyEtis-862");
				break;
			}
			case 16180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000804);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000849, EnemyEtis, "EnemyEtis-863");
				break;
			}
			case 16200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000805);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000850, EnemyEtis, "EnemyEtis-864");
				break;
			}
			case 16220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000806);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000851, EnemyEtis, "EnemyEtis-865");
				break;
			}
			case 16240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000807);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000852, EnemyEtis, "EnemyEtis-866");
				break;
			}
			case 16260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000808);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000853, EnemyEtis, "EnemyEtis-867");
				break;
			}
			case 16280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000809);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000854, EnemyEtis, "EnemyEtis-868");
				break;
			}
			case 16300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000810);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000855, EnemyEtis, "EnemyEtis-869");
				break;
			}
			case 16320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000811);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000856, EnemyEtis, "EnemyEtis-870");
				break;
			}
			case 16340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000812);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000857, EnemyEtis, "EnemyEtis-871");
				break;
			}
			case 16360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000813);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000858, EnemyEtis, "EnemyEtis-872");
				break;
			}
			case 16380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000814);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000859, EnemyEtis, "EnemyEtis-873");
				break;
			}
			case 16400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000815);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000860, EnemyEtis, "EnemyEtis-874");
				break;
			}
			case 16420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000816);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000861, EnemyEtis, "EnemyEtis-875");
				break;
			}
			case 16440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000817);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000862, EnemyEtis, "EnemyEtis-876");
				break;
			}
			case 16460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000818);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000863, EnemyEtis, "EnemyEtis-877");
				break;
			}
			case 16480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000819);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000864, EnemyEtis, "EnemyEtis-878");
				break;
			}
			case 16500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000820);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000865, EnemyEtis, "EnemyEtis-879");
				break;
			}
			case 16520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000821);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000866, EnemyEtis, "EnemyEtis-880");
				break;
			}
			case 16540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000822);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000867, EnemyEtis, "EnemyEtis-881");
				break;
			}
			case 16560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000823);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000868, EnemyEtis, "EnemyEtis-882");
				break;
			}
			case 16580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000824);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000869, EnemyEtis, "EnemyEtis-883");
				break;
			}
			case 16600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000825);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000870, EnemyEtis, "EnemyEtis-884");
				break;
			}
			case 16620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000826);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000871, EnemyEtis, "EnemyEtis-885");
				break;
			}
			case 16640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000827);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000872, EnemyEtis, "EnemyEtis-886");
				break;
			}
			case 16660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000828);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000873, EnemyEtis, "EnemyEtis-887");
				break;
			}
			case 16680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000829);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000874, EnemyEtis, "EnemyEtis-888");
				break;
			}
			case 16700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000830);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000875, EnemyEtis, "EnemyEtis-889");
				break;
			}
			case 16720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000831);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000876, EnemyEtis, "EnemyEtis-890");
				break;
			}
			case 16740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000832);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000877, EnemyEtis, "EnemyEtis-891");
				break;
			}
			case 16760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000833);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000878, EnemyEtis, "EnemyEtis-892");
				break;
			}
			case 16780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000834);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000879, EnemyEtis, "EnemyEtis-893");
				break;
			}
			case 16800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000835);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000880, EnemyEtis, "EnemyEtis-894");
				break;
			}
			case 16820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000836);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000881, EnemyEtis, "EnemyEtis-895");
				break;
			}
			case 16840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000837);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000882, EnemyEtis, "EnemyEtis-896");
				break;
			}
			case 16860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000838);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000883, EnemyEtis, "EnemyEtis-897");
				break;
			}
			case 16880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000839);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000884, EnemyEtis, "EnemyEtis-898");
				break;
			}
			case 16900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000840);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000885, EnemyEtis, "EnemyEtis-899");
				break;
			}
			case 16920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000841);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000886, EnemyEtis, "EnemyEtis-900");
				break;
			}
			case 16940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000842);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000887, EnemyEtis, "EnemyEtis-901");
				break;
			}
			case 16960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000843);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000888, EnemyEtis, "EnemyEtis-902");
				break;
			}
			case 16980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000844);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000889, EnemyEtis, "EnemyEtis-903");
				break;
			}
			case 17000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000845);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000890, EnemyEtis, "EnemyEtis-904");
				break;
			}
			case 17020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000846);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000891, EnemyEtis, "EnemyEtis-905");
				break;
			}
			case 17040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000847);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000892, EnemyEtis, "EnemyEtis-906");
				break;
			}
			case 17060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000848);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000893, EnemyEtis, "EnemyEtis-907");
				break;
			}
			case 17080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000849);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000894, EnemyEtis, "EnemyEtis-908");
				break;
			}
			case 17100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000850);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000895, EnemyEtis, "EnemyEtis-909");
				break;
			}
			case 17120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000851);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000896, EnemyEtis, "EnemyEtis-910");
				break;
			}
			case 17140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000852);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000897, EnemyEtis, "EnemyEtis-911");
				break;
			}
			case 17160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000853);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000898, EnemyEtis, "EnemyEtis-912");
				break;
			}
			case 17180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000854);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000899, EnemyEtis, "EnemyEtis-913");
				break;
			}
			case 17200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000855);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000900, EnemyEtis, "EnemyEtis-914");
				break;
			}
			case 17220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000856);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000901, EnemyEtis, "EnemyEtis-915");
				break;
			}
			case 17240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000857);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000902, EnemyEtis, "EnemyEtis-916");
				break;
			}
			case 17260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000858);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000903, EnemyEtis, "EnemyEtis-917");
				break;
			}
			case 17280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000859);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000904, EnemyEtis, "EnemyEtis-918");
				break;
			}
			case 17300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000860);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000905, EnemyEtis, "EnemyEtis-919");
				break;
			}
			case 17320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000861);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000906, EnemyEtis, "EnemyEtis-920");
				break;
			}
			case 17340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000862);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000907, EnemyEtis, "EnemyEtis-921");
				break;
			}
			case 17360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000863);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000908, EnemyEtis, "EnemyEtis-922");
				break;
			}
			case 17380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000864);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000909, EnemyEtis, "EnemyEtis-923");
				break;
			}
			case 17400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000865);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000910, EnemyEtis, "EnemyEtis-924");
				break;
			}
			case 17420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000866);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000911, EnemyEtis, "EnemyEtis-925");
				break;
			}
			case 17440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000867);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000912, EnemyEtis, "EnemyEtis-926");
				break;
			}
			case 17460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000868);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000913, EnemyEtis, "EnemyEtis-927");
				break;
			}
			case 17480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000869);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000914, EnemyEtis, "EnemyEtis-928");
				break;
			}
			case 17500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000870);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000915, EnemyEtis, "EnemyEtis-929");
				break;
			}
			case 17520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000871);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000916, EnemyEtis, "EnemyEtis-930");
				break;
			}
			case 17540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000872);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000917, EnemyEtis, "EnemyEtis-931");
				break;
			}
			case 17560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000873);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000918, EnemyEtis, "EnemyEtis-932");
				break;
			}
			case 17580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000874);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000919, EnemyEtis, "EnemyEtis-933");
				break;
			}
			case 17600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000875);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000920, EnemyEtis, "EnemyEtis-934");
				break;
			}
			case 17620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000876);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000921, EnemyEtis, "EnemyEtis-935");
				break;
			}
			case 17640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000877);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000922, EnemyEtis, "EnemyEtis-936");
				break;
			}
			case 17660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000878);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000923, EnemyEtis, "EnemyEtis-937");
				break;
			}
			case 17680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000879);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000924, EnemyEtis, "EnemyEtis-938");
				break;
			}
			case 17700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000880);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000925, EnemyEtis, "EnemyEtis-939");
				break;
			}
			case 17720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000881);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000926, EnemyEtis, "EnemyEtis-940");
				break;
			}
			case 17740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000882);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000927, EnemyEtis, "EnemyEtis-941");
				break;
			}
			case 17760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000883);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000928, EnemyEtis, "EnemyEtis-942");
				break;
			}
			case 17780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000884);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000929, EnemyEtis, "EnemyEtis-943");
				break;
			}
			case 17800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000885);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000930, EnemyEtis, "EnemyEtis-944");
				break;
			}
			case 17820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000886);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000931, EnemyEtis, "EnemyEtis-945");
				break;
			}
			case 17840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000887);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000932, EnemyEtis, "EnemyEtis-946");
				break;
			}
			case 17860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000888);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000933, EnemyEtis, "EnemyEtis-947");
				break;
			}
			case 17880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000889);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000934, EnemyEtis, "EnemyEtis-948");
				break;
			}
			case 17900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000890);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000935, EnemyEtis, "EnemyEtis-949");
				break;
			}
			case 17920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000891);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000936, EnemyEtis, "EnemyEtis-950");
				break;
			}
			case 17940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000892);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000937, EnemyEtis, "EnemyEtis-951");
				break;
			}
			case 17960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000893);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000938, EnemyEtis, "EnemyEtis-952");
				break;
			}
			case 17980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000894);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000939, EnemyEtis, "EnemyEtis-953");
				break;
			}
			case 18000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000895);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000940, EnemyEtis, "EnemyEtis-954");
				break;
			}
			case 18020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000896);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000941, EnemyEtis, "EnemyEtis-955");
				break;
			}
			case 18040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000897);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000942, EnemyEtis, "EnemyEtis-956");
				break;
			}
			case 18060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000898);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000943, EnemyEtis, "EnemyEtis-957");
				break;
			}
			case 18080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000899);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000944, EnemyEtis, "EnemyEtis-958");
				break;
			}
			case 18100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000900);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000945, EnemyEtis, "EnemyEtis-959");
				break;
			}
			case 18120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000901);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000946, EnemyEtis, "EnemyEtis-960");
				break;
			}
			case 18140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000902);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000947, EnemyEtis, "EnemyEtis-961");
				break;
			}
			case 18160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000903);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000948, EnemyEtis, "EnemyEtis-962");
				break;
			}
			case 18180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000904);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000949, EnemyEtis, "EnemyEtis-963");
				break;
			}
			case 18200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000905);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000950, EnemyEtis, "EnemyEtis-964");
				break;
			}
			case 18220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000906);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000951, EnemyEtis, "EnemyEtis-965");
				break;
			}
			case 18240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000907);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000952, EnemyEtis, "EnemyEtis-966");
				break;
			}
			case 18260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000908);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000953, EnemyEtis, "EnemyEtis-967");
				break;
			}
			case 18280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000909);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000954, EnemyEtis, "EnemyEtis-968");
				break;
			}
			case 18300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000910);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000955, EnemyEtis, "EnemyEtis-969");
				break;
			}
			case 18320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000911);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000956, EnemyEtis, "EnemyEtis-970");
				break;
			}
			case 18340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000912);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000957, EnemyEtis, "EnemyEtis-971");
				break;
			}
			case 18360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000913);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000958, EnemyEtis, "EnemyEtis-972");
				break;
			}
			case 18380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000914);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000959, EnemyEtis, "EnemyEtis-973");
				break;
			}
			case 18400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000915);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000960, EnemyEtis, "EnemyEtis-974");
				break;
			}
			case 18420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000916);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000961, EnemyEtis, "EnemyEtis-975");
				break;
			}
			case 18440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000917);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000962, EnemyEtis, "EnemyEtis-976");
				break;
			}
			case 18460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000918);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000963, EnemyEtis, "EnemyEtis-977");
				break;
			}
			case 18480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000919);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000964, EnemyEtis, "EnemyEtis-978");
				break;
			}
			case 18500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000920);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000965, EnemyEtis, "EnemyEtis-979");
				break;
			}
			case 18520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000921);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000966, EnemyEtis, "EnemyEtis-980");
				break;
			}
			case 18540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000922);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000967, EnemyEtis, "EnemyEtis-981");
				break;
			}
			case 18560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000923);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000968, EnemyEtis, "EnemyEtis-982");
				break;
			}
			case 18580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000924);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000969, EnemyEtis, "EnemyEtis-983");
				break;
			}
			case 18600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000925);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000970, EnemyEtis, "EnemyEtis-984");
				break;
			}
			case 18620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000926);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000971, EnemyEtis, "EnemyEtis-985");
				break;
			}
			case 18640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000927);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000972, EnemyEtis, "EnemyEtis-986");
				break;
			}
			case 18660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000928);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000973, EnemyEtis, "EnemyEtis-987");
				break;
			}
			case 18680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000929);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000974, EnemyEtis, "EnemyEtis-988");
				break;
			}
			case 18700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000930);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000975, EnemyEtis, "EnemyEtis-989");
				break;
			}
			case 18720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000931);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000976, EnemyEtis, "EnemyEtis-990");
				break;
			}
			case 18740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000932);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000977, EnemyEtis, "EnemyEtis-991");
				break;
			}
			case 18760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000933);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000978, EnemyEtis, "EnemyEtis-992");
				break;
			}
			case 18780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000934);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000979, EnemyEtis, "EnemyEtis-993");
				break;
			}
			case 18800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000935);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000980, EnemyEtis, "EnemyEtis-994");
				break;
			}
			case 18820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000936);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000981, EnemyEtis, "EnemyEtis-995");
				break;
			}
			case 18840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000937);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000982, EnemyEtis, "EnemyEtis-996");
				break;
			}
			case 18860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000938);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000983, EnemyEtis, "EnemyEtis-997");
				break;
			}
			case 18880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000939);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000984, EnemyEtis, "EnemyEtis-998");
				break;
			}
			case 18900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000940);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000985, EnemyEtis, "EnemyEtis-999");
				break;
			}
			case 18920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000941);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000986, EnemyEtis, "EnemyEtis-1000");
				break;
			}
			case 18940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000942);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000987, EnemyEtis, "EnemyEtis-1001");
				break;
			}
			case 18960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000943);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000988, EnemyEtis, "EnemyEtis-1002");
				break;
			}
			case 18980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000944);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000989, EnemyEtis, "EnemyEtis-1003");
				break;
			}
			case 19000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000945);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000990, EnemyEtis, "EnemyEtis-1004");
				break;
			}
			case 19020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000946);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000991, EnemyEtis, "EnemyEtis-1005");
				break;
			}
			case 19040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000947);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000992, EnemyEtis, "EnemyEtis-1006");
				break;
			}
			case 19060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000948);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000993, EnemyEtis, "EnemyEtis-1007");
				break;
			}
			case 19080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000949);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000994, EnemyEtis, "EnemyEtis-1008");
				break;
			}
			case 19100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000950);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000995, EnemyEtis, "EnemyEtis-1009");
				break;
			}
			case 19120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000951);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000996, EnemyEtis, "EnemyEtis-1010");
				break;
			}
			case 19140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000952);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000997, EnemyEtis, "EnemyEtis-1011");
				break;
			}
			case 19160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000953);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000998, EnemyEtis, "EnemyEtis-1012");
				break;
			}
			case 19180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000954);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000999, EnemyEtis, "EnemyEtis-1013");
				break;
			}
			case 19200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000955);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001000, EnemyEtis, "EnemyEtis-1014");
				break;
			}
			case 19220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000956);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001001, EnemyEtis, "EnemyEtis-1015");
				break;
			}
			case 19240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000957);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001002, EnemyEtis, "EnemyEtis-1016");
				break;
			}
			case 19260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000958);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001003, EnemyEtis, "EnemyEtis-1017");
				break;
			}
			case 19280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000959);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001004, EnemyEtis, "EnemyEtis-1018");
				break;
			}
			case 19300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000960);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001005, EnemyEtis, "EnemyEtis-1019");
				break;
			}
			case 19320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000961);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001006, EnemyEtis, "EnemyEtis-1020");
				break;
			}
			case 19340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000962);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001007, EnemyEtis, "EnemyEtis-1021");
				break;
			}
			case 19360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000963);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001008, EnemyEtis, "EnemyEtis-1022");
				break;
			}
			case 19380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000964);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001009, EnemyEtis, "EnemyEtis-1023");
				break;
			}
			case 19400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000965);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001010, EnemyEtis, "EnemyEtis-1024");
				break;
			}
			case 19420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000966);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001011, EnemyEtis, "EnemyEtis-1025");
				break;
			}
			case 19440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000967);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001012, EnemyEtis, "EnemyEtis-1026");
				break;
			}
			case 19460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000968);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001013, EnemyEtis, "EnemyEtis-1027");
				break;
			}
			case 19480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000969);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001014, EnemyEtis, "EnemyEtis-1028");
				break;
			}
			case 19500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000970);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001015, EnemyEtis, "EnemyEtis-1029");
				break;
			}
			case 19520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000971);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001016, EnemyEtis, "EnemyEtis-1030");
				break;
			}
			case 19540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000972);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001017, EnemyEtis, "EnemyEtis-1031");
				break;
			}
			case 19560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000973);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001018, EnemyEtis, "EnemyEtis-1032");
				break;
			}
			case 19580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000974);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001019, EnemyEtis, "EnemyEtis-1033");
				break;
			}
			case 19600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000975);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001020, EnemyEtis, "EnemyEtis-1034");
				break;
			}
			case 19620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000976);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001021, EnemyEtis, "EnemyEtis-1035");
				break;
			}
			case 19640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000977);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001022, EnemyEtis, "EnemyEtis-1036");
				break;
			}
			case 19660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000978);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001023, EnemyEtis, "EnemyEtis-1037");
				break;
			}
			case 19680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000979);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001024, EnemyEtis, "EnemyEtis-1038");
				break;
			}
			case 19700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000980);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001025, EnemyEtis, "EnemyEtis-1039");
				break;
			}
			case 19720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000981);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001026, EnemyEtis, "EnemyEtis-1040");
				break;
			}
			case 19740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000982);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001027, EnemyEtis, "EnemyEtis-1041");
				break;
			}
			case 19760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000983);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001028, EnemyEtis, "EnemyEtis-1042");
				break;
			}
			case 19780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000984);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001029, EnemyEtis, "EnemyEtis-1043");
				break;
			}
			case 19800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000985);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001030, EnemyEtis, "EnemyEtis-1044");
				break;
			}
			case 19820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000986);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001031, EnemyEtis, "EnemyEtis-1045");
				break;
			}
			case 19840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000987);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001032, EnemyEtis, "EnemyEtis-1046");
				break;
			}
			case 19860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000988);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001033, EnemyEtis, "EnemyEtis-1047");
				break;
			}
			case 19880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000989);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001034, EnemyEtis, "EnemyEtis-1048");
				break;
			}
			case 19900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000990);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001035, EnemyEtis, "EnemyEtis-1049");
				break;
			}
			case 19920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000991);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001036, EnemyEtis, "EnemyEtis-1050");
				break;
			}
			case 19940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000992);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001037, EnemyEtis, "EnemyEtis-1051");
				break;
			}
			case 19960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000993);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001038, EnemyEtis, "EnemyEtis-1052");
				break;
			}
			case 19980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000994);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001039, EnemyEtis, "EnemyEtis-1053");
				break;
			}
			case 20000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000995);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001040, EnemyEtis, "EnemyEtis-1054");
				break;
			}
			case 20020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000996);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001041, EnemyEtis, "EnemyEtis-1055");
				break;
			}
			case 20040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000997);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001042, EnemyEtis, "EnemyEtis-1056");
				break;
			}
			case 20060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000998);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001043, EnemyEtis, "EnemyEtis-1057");
				break;
			}
			case 20080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000999);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001044, EnemyEtis, "EnemyEtis-1058");
				break;
			}
			case 20100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001000);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001045, EnemyEtis, "EnemyEtis-1059");
				break;
			}
			case 20120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001001);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001046, EnemyEtis, "EnemyEtis-1060");
				break;
			}
			case 20140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001002);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001047, EnemyEtis, "EnemyEtis-1061");
				break;
			}
			case 20160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001003);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001048, EnemyEtis, "EnemyEtis-1062");
				break;
			}
			case 20180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001004);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001049, EnemyEtis, "EnemyEtis-1063");
				break;
			}
			case 20200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001005);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001050, EnemyEtis, "EnemyEtis-1064");
				break;
			}
			case 20220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001006);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001051, EnemyEtis, "EnemyEtis-1065");
				break;
			}
			case 20240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001007);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001052, EnemyEtis, "EnemyEtis-1066");
				break;
			}
			case 20260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001008);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001053, EnemyEtis, "EnemyEtis-1067");
				break;
			}
			case 20280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001009);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001054, EnemyEtis, "EnemyEtis-1068");
				break;
			}
			case 20300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001010);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001055, EnemyEtis, "EnemyEtis-1069");
				break;
			}
			case 20320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001011);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001056, EnemyEtis, "EnemyEtis-1070");
				break;
			}
			case 20340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001012);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001057, EnemyEtis, "EnemyEtis-1071");
				break;
			}
			case 20360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001013);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001058, EnemyEtis, "EnemyEtis-1072");
				break;
			}
			case 20380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001014);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001059, EnemyEtis, "EnemyEtis-1073");
				break;
			}
			case 20400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001015);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001060, EnemyEtis, "EnemyEtis-1074");
				break;
			}
			case 20420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001016);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001061, EnemyEtis, "EnemyEtis-1075");
				break;
			}
			case 20440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001017);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001062, EnemyEtis, "EnemyEtis-1076");
				break;
			}
			case 20460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001018);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001063, EnemyEtis, "EnemyEtis-1077");
				break;
			}
			case 20480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001019);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001064, EnemyEtis, "EnemyEtis-1078");
				break;
			}
			case 20500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001020);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001065, EnemyEtis, "EnemyEtis-1079");
				break;
			}
			case 20520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001021);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001066, EnemyEtis, "EnemyEtis-1080");
				break;
			}
			case 20540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001022);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001067, EnemyEtis, "EnemyEtis-1081");
				break;
			}
			case 20560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001023);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001068, EnemyEtis, "EnemyEtis-1082");
				break;
			}
			case 20580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001024);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001069, EnemyEtis, "EnemyEtis-1083");
				break;
			}
			case 20600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001025);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001070, EnemyEtis, "EnemyEtis-1084");
				break;
			}
			case 20620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001026);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001071, EnemyEtis, "EnemyEtis-1085");
				break;
			}
			case 20640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001027);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001072, EnemyEtis, "EnemyEtis-1086");
				break;
			}
			case 20660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001028);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001073, EnemyEtis, "EnemyEtis-1087");
				break;
			}
			case 20680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001029);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001074, EnemyEtis, "EnemyEtis-1088");
				break;
			}
			case 20700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001030);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001075, EnemyEtis, "EnemyEtis-1089");
				break;
			}
			case 20720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001031);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001076, EnemyEtis, "EnemyEtis-1090");
				break;
			}
			case 20740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001032);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001077, EnemyEtis, "EnemyEtis-1091");
				break;
			}
			case 20760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001033);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001078, EnemyEtis, "EnemyEtis-1092");
				break;
			}
			case 20780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001034);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001079, EnemyEtis, "EnemyEtis-1093");
				break;
			}
			case 20800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001035);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001080, EnemyEtis, "EnemyEtis-1094");
				break;
			}
			case 20820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001036);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001081, EnemyEtis, "EnemyEtis-1095");
				break;
			}
			case 20840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001037);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001082, EnemyEtis, "EnemyEtis-1096");
				break;
			}
			case 20860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001038);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001083, EnemyEtis, "EnemyEtis-1097");
				break;
			}
			case 20880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001039);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001084, EnemyEtis, "EnemyEtis-1098");
				break;
			}
			case 20900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001040);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001085, EnemyEtis, "EnemyEtis-1099");
				break;
			}
			case 20920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001041);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001086, EnemyEtis, "EnemyEtis-1100");
				break;
			}
			case 20940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001042);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001087, EnemyEtis, "EnemyEtis-1101");
				break;
			}
			case 20960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001043);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001088, EnemyEtis, "EnemyEtis-1102");
				break;
			}
			case 20980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001044);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001089, EnemyEtis, "EnemyEtis-1103");
				break;
			}
			case 21000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001045);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001090, EnemyEtis, "EnemyEtis-1104");
				break;
			}
			case 21020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001046);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001091, EnemyEtis, "EnemyEtis-1105");
				break;
			}
			case 21040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001047);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001092, EnemyEtis, "EnemyEtis-1106");
				break;
			}
			case 21060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001048);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001093, EnemyEtis, "EnemyEtis-1107");
				break;
			}
			case 21080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001049);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001094, EnemyEtis, "EnemyEtis-1108");
				break;
			}
			case 21100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001050);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001095, EnemyEtis, "EnemyEtis-1109");
				break;
			}
			case 21120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001051);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001096, EnemyEtis, "EnemyEtis-1110");
				break;
			}
			case 21140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001052);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001097, EnemyEtis, "EnemyEtis-1111");
				break;
			}
			case 21160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001053);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001098, EnemyEtis, "EnemyEtis-1112");
				break;
			}
			case 21180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001054);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001099, EnemyEtis, "EnemyEtis-1113");
				break;
			}
			case 21200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001055);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001100, EnemyEtis, "EnemyEtis-1114");
				break;
			}
			case 21220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001056);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001101, EnemyEtis, "EnemyEtis-1115");
				break;
			}
			case 21240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001057);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001102, EnemyEtis, "EnemyEtis-1116");
				break;
			}
			case 21260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001058);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001103, EnemyEtis, "EnemyEtis-1117");
				break;
			}
			case 21280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001059);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001104, EnemyEtis, "EnemyEtis-1118");
				break;
			}
			case 21300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001060);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001105, EnemyEtis, "EnemyEtis-1119");
				break;
			}
			case 21320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001061);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001106, EnemyEtis, "EnemyEtis-1120");
				break;
			}
			case 21340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001062);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001107, EnemyEtis, "EnemyEtis-1121");
				break;
			}
			case 21360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001063);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001108, EnemyEtis, "EnemyEtis-1122");
				break;
			}
			case 21380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001064);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001109, EnemyEtis, "EnemyEtis-1123");
				break;
			}
			case 21400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001065);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001110, EnemyEtis, "EnemyEtis-1124");
				break;
			}
			case 21420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001066);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001111, EnemyEtis, "EnemyEtis-1125");
				break;
			}
			case 21440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001067);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001112, EnemyEtis, "EnemyEtis-1126");
				break;
			}
			case 21460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001068);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001113, EnemyEtis, "EnemyEtis-1127");
				break;
			}
			case 21480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001069);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001114, EnemyEtis, "EnemyEtis-1128");
				break;
			}
			case 21500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001070);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001115, EnemyEtis, "EnemyEtis-1129");
				break;
			}
			case 21520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001071);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001116, EnemyEtis, "EnemyEtis-1130");
				break;
			}
			case 21540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001072);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001117, EnemyEtis, "EnemyEtis-1131");
				break;
			}
			case 21560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001073);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001118, EnemyEtis, "EnemyEtis-1132");
				break;
			}
			case 21580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001074);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001119, EnemyEtis, "EnemyEtis-1133");
				break;
			}
			case 21600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001075);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001120, EnemyEtis, "EnemyEtis-1134");
				break;
			}
			case 21620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001076);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001121, EnemyEtis, "EnemyEtis-1135");
				break;
			}
			case 21640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001077);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001122, EnemyEtis, "EnemyEtis-1136");
				break;
			}
			case 21660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001078);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001123, EnemyEtis, "EnemyEtis-1137");
				break;
			}
			case 21680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001079);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001124, EnemyEtis, "EnemyEtis-1138");
				break;
			}
			case 21700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001080);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001125, EnemyEtis, "EnemyEtis-1139");
				break;
			}
			case 21720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001081);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001126, EnemyEtis, "EnemyEtis-1140");
				break;
			}
			case 21740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001082);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001127, EnemyEtis, "EnemyEtis-1141");
				break;
			}
			case 21760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001083);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001128, EnemyEtis, "EnemyEtis-1142");
				break;
			}
			case 21780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001084);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001129, EnemyEtis, "EnemyEtis-1143");
				break;
			}
			case 21800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001085);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001130, EnemyEtis, "EnemyEtis-1144");
				break;
			}
			case 21820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001086);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001131, EnemyEtis, "EnemyEtis-1145");
				break;
			}
			case 21840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001087);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001132, EnemyEtis, "EnemyEtis-1146");
				break;
			}
			case 21860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001088);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001133, EnemyEtis, "EnemyEtis-1147");
				break;
			}
			case 21880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001089);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001134, EnemyEtis, "EnemyEtis-1148");
				break;
			}
			case 21900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001090);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001135, EnemyEtis, "EnemyEtis-1149");
				break;
			}
			case 21920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001091);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001136, EnemyEtis, "EnemyEtis-1150");
				break;
			}
			case 21940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001092);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001137, EnemyEtis, "EnemyEtis-1151");
				break;
			}
			case 21960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001093);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001138, EnemyEtis, "EnemyEtis-1152");
				break;
			}
			case 21980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001094);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001139, EnemyEtis, "EnemyEtis-1153");
				break;
			}
			case 22000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001095);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001140, EnemyEtis, "EnemyEtis-1154");
				break;
			}
			case 22020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001096);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001141, EnemyEtis, "EnemyEtis-1155");
				break;
			}
			case 22040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001097);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001142, EnemyEtis, "EnemyEtis-1156");
				break;
			}
			case 22060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001098);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001143, EnemyEtis, "EnemyEtis-1157");
				break;
			}
			case 22080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001099);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001144, EnemyEtis, "EnemyEtis-1158");
				break;
			}
			case 22100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001100);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001145, EnemyEtis, "EnemyEtis-1159");
				break;
			}
			case 22120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001101);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001146, EnemyEtis, "EnemyEtis-1160");
				break;
			}
			case 22140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001102);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001147, EnemyEtis, "EnemyEtis-1161");
				break;
			}
			case 22160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001103);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001148, EnemyEtis, "EnemyEtis-1162");
				break;
			}
			case 22180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001104);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001149, EnemyEtis, "EnemyEtis-1163");
				break;
			}
			case 22200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001105);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001150, EnemyEtis, "EnemyEtis-1164");
				break;
			}
			case 22220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001106);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001151, EnemyEtis, "EnemyEtis-1165");
				break;
			}
			case 22240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001107);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001152, EnemyEtis, "EnemyEtis-1166");
				break;
			}
			case 22260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001108);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001153, EnemyEtis, "EnemyEtis-1167");
				break;
			}
			case 22280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001109);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001154, EnemyEtis, "EnemyEtis-1168");
				break;
			}
			case 22300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001110);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001155, EnemyEtis, "EnemyEtis-1169");
				break;
			}
			case 22320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001111);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001156, EnemyEtis, "EnemyEtis-1170");
				break;
			}
			case 22340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001112);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001157, EnemyEtis, "EnemyEtis-1171");
				break;
			}
			case 22360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001113);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001158, EnemyEtis, "EnemyEtis-1172");
				break;
			}
			case 22380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001114);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001159, EnemyEtis, "EnemyEtis-1173");
				break;
			}
			case 22400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001115);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001160, EnemyEtis, "EnemyEtis-1174");
				break;
			}
			case 22420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001116);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001161, EnemyEtis, "EnemyEtis-1175");
				break;
			}
			case 22440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001117);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001162, EnemyEtis, "EnemyEtis-1176");
				break;
			}
			case 22460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001118);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001163, EnemyEtis, "EnemyEtis-1177");
				break;
			}
			case 22480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001119);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001164, EnemyEtis, "EnemyEtis-1178");
				break;
			}
			case 22500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001120);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001165, EnemyEtis, "EnemyEtis-1179");
				break;
			}
			case 22520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001121);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001166, EnemyEtis, "EnemyEtis-1180");
				break;
			}
			case 22540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001122);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001167, EnemyEtis, "EnemyEtis-1181");
				break;
			}
			case 22560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001123);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001168, EnemyEtis, "EnemyEtis-1182");
				break;
			}
			case 22580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001124);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001169, EnemyEtis, "EnemyEtis-1183");
				break;
			}
			case 22600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001125);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001170, EnemyEtis, "EnemyEtis-1184");
				break;
			}
			case 22620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001126);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001171, EnemyEtis, "EnemyEtis-1185");
				break;
			}
			case 22640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001127);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001172, EnemyEtis, "EnemyEtis-1186");
				break;
			}
			case 22660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001128);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001173, EnemyEtis, "EnemyEtis-1187");
				break;
			}
			case 22680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001129);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001174, EnemyEtis, "EnemyEtis-1188");
				break;
			}
			case 22700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001130);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001175, EnemyEtis, "EnemyEtis-1189");
				break;
			}
			case 22720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001131);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001176, EnemyEtis, "EnemyEtis-1190");
				break;
			}
			case 22740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001132);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001177, EnemyEtis, "EnemyEtis-1191");
				break;
			}
			case 22760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001133);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001178, EnemyEtis, "EnemyEtis-1192");
				break;
			}
			case 22780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001134);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001179, EnemyEtis, "EnemyEtis-1193");
				break;
			}
			case 22800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001135);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001180, EnemyEtis, "EnemyEtis-1194");
				break;
			}
			case 22820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001136);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001181, EnemyEtis, "EnemyEtis-1195");
				break;
			}
			case 22840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001137);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001182, EnemyEtis, "EnemyEtis-1196");
				break;
			}
			case 22860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001138);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001183, EnemyEtis, "EnemyEtis-1197");
				break;
			}
			case 22880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001139);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001184, EnemyEtis, "EnemyEtis-1198");
				break;
			}
			case 22900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001140);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001185, EnemyEtis, "EnemyEtis-1199");
				break;
			}
			case 22920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001141);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001186, EnemyEtis, "EnemyEtis-1200");
				break;
			}
			case 22940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001142);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001187, EnemyEtis, "EnemyEtis-1201");
				break;
			}
			case 22960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001143);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001188, EnemyEtis, "EnemyEtis-1202");
				break;
			}
			case 22980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001144);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001189, EnemyEtis, "EnemyEtis-1203");
				break;
			}
			case 23000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001145);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001190, EnemyEtis, "EnemyEtis-1204");
				break;
			}
			case 23020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001146);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001191, EnemyEtis, "EnemyEtis-1205");
				break;
			}
			case 23040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001147);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001192, EnemyEtis, "EnemyEtis-1206");
				break;
			}
			case 23060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001148);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001193, EnemyEtis, "EnemyEtis-1207");
				break;
			}
			case 23080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001149);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001194, EnemyEtis, "EnemyEtis-1208");
				break;
			}
			case 23100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001150);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001195, EnemyEtis, "EnemyEtis-1209");
				break;
			}
			case 23120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001151);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001196, EnemyEtis, "EnemyEtis-1210");
				break;
			}
			case 23140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001152);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001197, EnemyEtis, "EnemyEtis-1211");
				break;
			}
			case 23160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001153);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001198, EnemyEtis, "EnemyEtis-1212");
				break;
			}
			case 23180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001154);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001199, EnemyEtis, "EnemyEtis-1213");
				break;
			}
			case 23200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001155);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001200, EnemyEtis, "EnemyEtis-1214");
				break;
			}
			case 23220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001156);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001201, EnemyEtis, "EnemyEtis-1215");
				break;
			}
			case 23240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001157);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001202, EnemyEtis, "EnemyEtis-1216");
				break;
			}
			case 23260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001158);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001203, EnemyEtis, "EnemyEtis-1217");
				break;
			}
			case 23280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001159);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001204, EnemyEtis, "EnemyEtis-1218");
				break;
			}
			case 23300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001160);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001205, EnemyEtis, "EnemyEtis-1219");
				break;
			}
			case 23320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001161);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001206, EnemyEtis, "EnemyEtis-1220");
				break;
			}
			case 23340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001162);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001207, EnemyEtis, "EnemyEtis-1221");
				break;
			}
			case 23360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001163);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001208, EnemyEtis, "EnemyEtis-1222");
				break;
			}
			case 23380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001164);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001209, EnemyEtis, "EnemyEtis-1223");
				break;
			}
			case 23400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001165);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001210, EnemyEtis, "EnemyEtis-1224");
				break;
			}
			case 23420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001166);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001211, EnemyEtis, "EnemyEtis-1225");
				break;
			}
			case 23440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001167);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001212, EnemyEtis, "EnemyEtis-1226");
				break;
			}
			case 23460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001168);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001213, EnemyEtis, "EnemyEtis-1227");
				break;
			}
			case 23480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001169);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001214, EnemyEtis, "EnemyEtis-1228");
				break;
			}
			case 23500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001170);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001215, EnemyEtis, "EnemyEtis-1229");
				break;
			}
			case 23520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001171);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001216, EnemyEtis, "EnemyEtis-1230");
				break;
			}
			case 23540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001172);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001217, EnemyEtis, "EnemyEtis-1231");
				break;
			}
			case 23560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001173);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001218, EnemyEtis, "EnemyEtis-1232");
				break;
			}
			case 23580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001174);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001219, EnemyEtis, "EnemyEtis-1233");
				break;
			}
			case 23600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001175);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001220, EnemyEtis, "EnemyEtis-1234");
				break;
			}
			case 23620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001176);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001221, EnemyEtis, "EnemyEtis-1235");
				break;
			}
			case 23640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001177);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001222, EnemyEtis, "EnemyEtis-1236");
				break;
			}
			case 23660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001178);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001223, EnemyEtis, "EnemyEtis-1237");
				break;
			}
			case 23680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001179);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001224, EnemyEtis, "EnemyEtis-1238");
				break;
			}
			case 23700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001180);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001225, EnemyEtis, "EnemyEtis-1239");
				break;
			}
			case 23720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001181);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001226, EnemyEtis, "EnemyEtis-1240");
				break;
			}
			case 23740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001182);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001227, EnemyEtis, "EnemyEtis-1241");
				break;
			}
			case 23760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001183);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001228, EnemyEtis, "EnemyEtis-1242");
				break;
			}
			case 23780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001184);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001229, EnemyEtis, "EnemyEtis-1243");
				break;
			}
			case 23800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001185);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001230, EnemyEtis, "EnemyEtis-1244");
				break;
			}
			case 23820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001186);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001231, EnemyEtis, "EnemyEtis-1245");
				break;
			}
			case 23840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001187);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001232, EnemyEtis, "EnemyEtis-1246");
				break;
			}
			case 23860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001188);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001233, EnemyEtis, "EnemyEtis-1247");
				break;
			}
			case 23880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001189);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001234, EnemyEtis, "EnemyEtis-1248");
				break;
			}
			case 23900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001190);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001235, EnemyEtis, "EnemyEtis-1249");
				break;
			}
			case 23920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001191);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001236, EnemyEtis, "EnemyEtis-1250");
				break;
			}
			case 23940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001192);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001237, EnemyEtis, "EnemyEtis-1251");
				break;
			}
			case 23960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001193);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001238, EnemyEtis, "EnemyEtis-1252");
				break;
			}
			case 23980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001194);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001239, EnemyEtis, "EnemyEtis-1253");
				break;
			}
			case 24000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001195);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001240, EnemyEtis, "EnemyEtis-1254");
				break;
			}
			case 24020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001196);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001241, EnemyEtis, "EnemyEtis-1255");
				break;
			}
			case 24040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001197);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001242, EnemyEtis, "EnemyEtis-1256");
				break;
			}
			case 24060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001198);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001243, EnemyEtis, "EnemyEtis-1257");
				break;
			}
			case 24080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001199);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001244, EnemyEtis, "EnemyEtis-1258");
				break;
			}
			case 24100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001200);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001245, EnemyEtis, "EnemyEtis-1259");
				break;
			}
			case 24120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001201);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001246, EnemyEtis, "EnemyEtis-1260");
				break;
			}
			case 24140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001202);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001247, EnemyEtis, "EnemyEtis-1261");
				break;
			}
			case 24160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001203);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001248, EnemyEtis, "EnemyEtis-1262");
				break;
			}
			case 24180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001204);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001249, EnemyEtis, "EnemyEtis-1263");
				break;
			}
			case 24200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001205);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001250, EnemyEtis, "EnemyEtis-1264");
				break;
			}
			case 24220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001206);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001251, EnemyEtis, "EnemyEtis-1265");
				break;
			}
			case 24240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001207);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001252, EnemyEtis, "EnemyEtis-1266");
				break;
			}
			case 24260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001208);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001253, EnemyEtis, "EnemyEtis-1267");
				break;
			}
			case 24280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001209);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001254, EnemyEtis, "EnemyEtis-1268");
				break;
			}
			case 24300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001210);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001255, EnemyEtis, "EnemyEtis-1269");
				break;
			}
			case 24320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001211);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001256, EnemyEtis, "EnemyEtis-1270");
				break;
			}
			case 24340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001212);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001257, EnemyEtis, "EnemyEtis-1271");
				break;
			}
			case 24360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001213);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001258, EnemyEtis, "EnemyEtis-1272");
				break;
			}
			case 24380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001214);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001259, EnemyEtis, "EnemyEtis-1273");
				break;
			}
			case 24400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001215);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001260, EnemyEtis, "EnemyEtis-1274");
				break;
			}
			case 24420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001216);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001261, EnemyEtis, "EnemyEtis-1275");
				break;
			}
			case 24440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001217);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001262, EnemyEtis, "EnemyEtis-1276");
				break;
			}
			case 24460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001218);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001263, EnemyEtis, "EnemyEtis-1277");
				break;
			}
			case 24480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001219);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001264, EnemyEtis, "EnemyEtis-1278");
				break;
			}
			case 24500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001220);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001265, EnemyEtis, "EnemyEtis-1279");
				break;
			}
			case 24520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001221);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001266, EnemyEtis, "EnemyEtis-1280");
				break;
			}
			case 24540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001222);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001267, EnemyEtis, "EnemyEtis-1281");
				break;
			}
			case 24560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001223);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001268, EnemyEtis, "EnemyEtis-1282");
				break;
			}
			case 24580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001224);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001269, EnemyEtis, "EnemyEtis-1283");
				break;
			}
			case 24600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001225);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001270, EnemyEtis, "EnemyEtis-1284");
				break;
			}
			case 24620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001226);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001271, EnemyEtis, "EnemyEtis-1285");
				break;
			}
			case 24640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001227);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001272, EnemyEtis, "EnemyEtis-1286");
				break;
			}
			case 24660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001228);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001273, EnemyEtis, "EnemyEtis-1287");
				break;
			}
			case 24680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001229);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001274, EnemyEtis, "EnemyEtis-1288");
				break;
			}
			case 24700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001230);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001275, EnemyEtis, "EnemyEtis-1289");
				break;
			}
			case 24720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001231);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001276, EnemyEtis, "EnemyEtis-1290");
				break;
			}
			case 24740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001232);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001277, EnemyEtis, "EnemyEtis-1291");
				break;
			}
			case 24760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001233);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001278, EnemyEtis, "EnemyEtis-1292");
				break;
			}
			case 24780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001234);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001279, EnemyEtis, "EnemyEtis-1293");
				break;
			}
			case 24800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001235);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001280, EnemyEtis, "EnemyEtis-1294");
				break;
			}
			case 24820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001236);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001281, EnemyEtis, "EnemyEtis-1295");
				break;
			}
			case 24840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001237);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001282, EnemyEtis, "EnemyEtis-1296");
				break;
			}
			case 24860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001238);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001283, EnemyEtis, "EnemyEtis-1297");
				break;
			}
			case 24880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001239);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001284, EnemyEtis, "EnemyEtis-1298");
				break;
			}
			case 24900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001240);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001285, EnemyEtis, "EnemyEtis-1299");
				break;
			}
			case 24920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001241);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001286, EnemyEtis, "EnemyEtis-1300");
				break;
			}
			case 24940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001242);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001287, EnemyEtis, "EnemyEtis-1301");
				break;
			}
			case 24960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001243);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001288, EnemyEtis, "EnemyEtis-1302");
				break;
			}
			case 24980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001244);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001289, EnemyEtis, "EnemyEtis-1303");
				break;
			}
			case 25000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001245);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001290, EnemyEtis, "EnemyEtis-1304");
				break;
			}
			case 25020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001246);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001291, EnemyEtis, "EnemyEtis-1305");
				break;
			}
			case 25040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001247);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001292, EnemyEtis, "EnemyEtis-1306");
				break;
			}
			case 25060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001248);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001293, EnemyEtis, "EnemyEtis-1307");
				break;
			}
			case 25080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001249);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001294, EnemyEtis, "EnemyEtis-1308");
				break;
			}
			case 25100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001250);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001295, EnemyEtis, "EnemyEtis-1309");
				break;
			}
			case 25120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001251);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001296, EnemyEtis, "EnemyEtis-1310");
				break;
			}
			case 25140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001252);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001297, EnemyEtis, "EnemyEtis-1311");
				break;
			}
			case 25160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001253);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001298, EnemyEtis, "EnemyEtis-1312");
				break;
			}
			case 25180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001254);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001299, EnemyEtis, "EnemyEtis-1313");
				break;
			}
			case 25200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001255);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001300, EnemyEtis, "EnemyEtis-1314");
				break;
			}
			case 25220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001256);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001301, EnemyEtis, "EnemyEtis-1315");
				break;
			}
			case 25240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001257);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001302, EnemyEtis, "EnemyEtis-1316");
				break;
			}
			case 25260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001258);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001303, EnemyEtis, "EnemyEtis-1317");
				break;
			}
			case 25280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001259);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001304, EnemyEtis, "EnemyEtis-1318");
				break;
			}
			case 25300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001260);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001305, EnemyEtis, "EnemyEtis-1319");
				break;
			}
			case 25320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001261);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001306, EnemyEtis, "EnemyEtis-1320");
				break;
			}
			case 25340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001262);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001307, EnemyEtis, "EnemyEtis-1321");
				break;
			}
			case 25360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001263);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001308, EnemyEtis, "EnemyEtis-1322");
				break;
			}
			case 25380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001264);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001309, EnemyEtis, "EnemyEtis-1323");
				break;
			}
			case 25400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001265);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001310, EnemyEtis, "EnemyEtis-1324");
				break;
			}
			case 25420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001266);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001311, EnemyEtis, "EnemyEtis-1325");
				break;
			}
			case 25440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001267);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001312, EnemyEtis, "EnemyEtis-1326");
				break;
			}
			case 25460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001268);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001313, EnemyEtis, "EnemyEtis-1327");
				break;
			}
			case 25480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001269);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001314, EnemyEtis, "EnemyEtis-1328");
				break;
			}
			case 25500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001270);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001315, EnemyEtis, "EnemyEtis-1329");
				break;
			}
			case 25520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001271);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001316, EnemyEtis, "EnemyEtis-1330");
				break;
			}
			case 25540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001272);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001317, EnemyEtis, "EnemyEtis-1331");
				break;
			}
			case 25560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001273);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001318, EnemyEtis, "EnemyEtis-1332");
				break;
			}
			case 25580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001274);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001319, EnemyEtis, "EnemyEtis-1333");
				break;
			}
			case 25600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001275);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001320, EnemyEtis, "EnemyEtis-1334");
				break;
			}
			case 25620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001276);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001321, EnemyEtis, "EnemyEtis-1335");
				break;
			}
			case 25640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001277);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001322, EnemyEtis, "EnemyEtis-1336");
				break;
			}
			case 25660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001278);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001323, EnemyEtis, "EnemyEtis-1337");
				break;
			}
			case 25680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001279);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001324, EnemyEtis, "EnemyEtis-1338");
				break;
			}
			case 25700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001280);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001325, EnemyEtis, "EnemyEtis-1339");
				break;
			}
			case 25720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001281);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001326, EnemyEtis, "EnemyEtis-1340");
				break;
			}
			case 25740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001282);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001327, EnemyEtis, "EnemyEtis-1341");
				break;
			}
			case 25760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001283);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001328, EnemyEtis, "EnemyEtis-1342");
				break;
			}
			case 25780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001284);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001329, EnemyEtis, "EnemyEtis-1343");
				break;
			}
			case 25800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001285);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001330, EnemyEtis, "EnemyEtis-1344");
				break;
			}
			case 25820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001286);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001331, EnemyEtis, "EnemyEtis-1345");
				break;
			}
			case 25840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001287);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001332, EnemyEtis, "EnemyEtis-1346");
				break;
			}
			case 25860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001288);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001333, EnemyEtis, "EnemyEtis-1347");
				break;
			}
			case 25880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001289);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001334, EnemyEtis, "EnemyEtis-1348");
				break;
			}
			case 25900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001290);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001335, EnemyEtis, "EnemyEtis-1349");
				break;
			}
			case 25920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001291);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001336, EnemyEtis, "EnemyEtis-1350");
				break;
			}
			case 25940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001292);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001337, EnemyEtis, "EnemyEtis-1351");
				break;
			}
			case 25960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001293);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001338, EnemyEtis, "EnemyEtis-1352");
				break;
			}
			case 25980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001294);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001339, EnemyEtis, "EnemyEtis-1353");
				break;
			}
			case 26000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001295);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001340, EnemyEtis, "EnemyEtis-1354");
				break;
			}
			case 26020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001296);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001341, EnemyEtis, "EnemyEtis-1355");
				break;
			}
			case 26040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001297);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001342, EnemyEtis, "EnemyEtis-1356");
				break;
			}
			case 26060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001298);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001343, EnemyEtis, "EnemyEtis-1357");
				break;
			}
			case 26080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001299);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001344, EnemyEtis, "EnemyEtis-1358");
				break;
			}
			case 26100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001300);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001345, EnemyEtis, "EnemyEtis-1359");
				break;
			}
			case 26120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001301);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001346, EnemyEtis, "EnemyEtis-1360");
				break;
			}
			case 26140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001302);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001347, EnemyEtis, "EnemyEtis-1361");
				break;
			}
			case 26160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001303);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001348, EnemyEtis, "EnemyEtis-1362");
				break;
			}
			case 26180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001304);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001349, EnemyEtis, "EnemyEtis-1363");
				break;
			}
			case 26200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001305);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001350, EnemyEtis, "EnemyEtis-1364");
				break;
			}
			case 26220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001306);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001351, EnemyEtis, "EnemyEtis-1365");
				break;
			}
			case 26240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001307);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001352, EnemyEtis, "EnemyEtis-1366");
				break;
			}
			case 26260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001308);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001353, EnemyEtis, "EnemyEtis-1367");
				break;
			}
			case 26280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001309);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001354, EnemyEtis, "EnemyEtis-1368");
				break;
			}
			case 26300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001310);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001355, EnemyEtis, "EnemyEtis-1369");
				break;
			}
			case 26320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001311);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001356, EnemyEtis, "EnemyEtis-1370");
				break;
			}
			case 26340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001312);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001357, EnemyEtis, "EnemyEtis-1371");
				break;
			}
			case 26360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001313);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001358, EnemyEtis, "EnemyEtis-1372");
				break;
			}
			case 26380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001314);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001359, EnemyEtis, "EnemyEtis-1373");
				break;
			}
			case 26400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001315);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001360, EnemyEtis, "EnemyEtis-1374");
				break;
			}
			case 26420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001316);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001361, EnemyEtis, "EnemyEtis-1375");
				break;
			}
			case 26440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001317);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001362, EnemyEtis, "EnemyEtis-1376");
				break;
			}
			case 26460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001318);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001363, EnemyEtis, "EnemyEtis-1377");
				break;
			}
			case 26480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001319);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001364, EnemyEtis, "EnemyEtis-1378");
				break;
			}
			case 26500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001320);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001365, EnemyEtis, "EnemyEtis-1379");
				break;
			}
			case 26520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001321);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001366, EnemyEtis, "EnemyEtis-1380");
				break;
			}
			case 26540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001322);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001367, EnemyEtis, "EnemyEtis-1381");
				break;
			}
			case 26560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001323);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001368, EnemyEtis, "EnemyEtis-1382");
				break;
			}
			case 26580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001324);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001369, EnemyEtis, "EnemyEtis-1383");
				break;
			}
			case 26600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001325);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001370, EnemyEtis, "EnemyEtis-1384");
				break;
			}
			case 26620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001326);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001371, EnemyEtis, "EnemyEtis-1385");
				break;
			}
			case 26640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001327);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001372, EnemyEtis, "EnemyEtis-1386");
				break;
			}
			case 26660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001328);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001373, EnemyEtis, "EnemyEtis-1387");
				break;
			}
			case 26680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001329);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001374, EnemyEtis, "EnemyEtis-1388");
				break;
			}
			case 26700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001330);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001375, EnemyEtis, "EnemyEtis-1389");
				break;
			}
			case 26720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001331);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001376, EnemyEtis, "EnemyEtis-1390");
				break;
			}
			case 26740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001332);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001377, EnemyEtis, "EnemyEtis-1391");
				break;
			}
			case 26760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001333);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001378, EnemyEtis, "EnemyEtis-1392");
				break;
			}
			case 26780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001334);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001379, EnemyEtis, "EnemyEtis-1393");
				break;
			}
			case 26800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001335);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001380, EnemyEtis, "EnemyEtis-1394");
				break;
			}
			case 26820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001336);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001381, EnemyEtis, "EnemyEtis-1395");
				break;
			}
			case 26840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001337);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001382, EnemyEtis, "EnemyEtis-1396");
				break;
			}
			case 26860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001338);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001383, EnemyEtis, "EnemyEtis-1397");
				break;
			}
			case 26880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001339);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001384, EnemyEtis, "EnemyEtis-1398");
				break;
			}
			case 26900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001340);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001385, EnemyEtis, "EnemyEtis-1399");
				break;
			}
			case 26920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001341);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001386, EnemyEtis, "EnemyEtis-1400");
				break;
			}
			case 26940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001342);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001387, EnemyEtis, "EnemyEtis-1401");
				break;
			}
			case 26960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001343);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001388, EnemyEtis, "EnemyEtis-1402");
				break;
			}
			case 26980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001344);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001389, EnemyEtis, "EnemyEtis-1403");
				break;
			}
			case 27000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001345);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001390, EnemyEtis, "EnemyEtis-1404");
				break;
			}
			case 27020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001346);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001391, EnemyEtis, "EnemyEtis-1405");
				break;
			}
			case 27040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001347);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001392, EnemyEtis, "EnemyEtis-1406");
				break;
			}
			case 27060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001348);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001393, EnemyEtis, "EnemyEtis-1407");
				break;
			}
			case 27080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001349);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001394, EnemyEtis, "EnemyEtis-1408");
				break;
			}
			case 27100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001350);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001395, EnemyEtis, "EnemyEtis-1409");
				break;
			}
			case 27120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001351);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001396, EnemyEtis, "EnemyEtis-1410");
				break;
			}
			case 27140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001352);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001397, EnemyEtis, "EnemyEtis-1411");
				break;
			}
			case 27160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001353);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001398, EnemyEtis, "EnemyEtis-1412");
				break;
			}
			case 27180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001354);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001399, EnemyEtis, "EnemyEtis-1413");
				break;
			}
			case 27200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001355);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001400, EnemyEtis, "EnemyEtis-1414");
				break;
			}
			case 27220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001356);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001401, EnemyEtis, "EnemyEtis-1415");
				break;
			}
			case 27240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001357);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001402, EnemyEtis, "EnemyEtis-1416");
				break;
			}
			case 27260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001358);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001403, EnemyEtis, "EnemyEtis-1417");
				break;
			}
			case 27280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001359);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001404, EnemyEtis, "EnemyEtis-1418");
				break;
			}
			case 27300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001360);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001405, EnemyEtis, "EnemyEtis-1419");
				break;
			}
			case 27320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001361);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001406, EnemyEtis, "EnemyEtis-1420");
				break;
			}
			case 27340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001362);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001407, EnemyEtis, "EnemyEtis-1421");
				break;
			}
			case 27360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001363);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001408, EnemyEtis, "EnemyEtis-1422");
				break;
			}
			case 27380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001364);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001409, EnemyEtis, "EnemyEtis-1423");
				break;
			}
			case 27400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001365);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001410, EnemyEtis, "EnemyEtis-1424");
				break;
			}
			case 27420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001366);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001411, EnemyEtis, "EnemyEtis-1425");
				break;
			}
			case 27440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001367);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001412, EnemyEtis, "EnemyEtis-1426");
				break;
			}
			case 27460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001368);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001413, EnemyEtis, "EnemyEtis-1427");
				break;
			}
			case 27480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001369);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001414, EnemyEtis, "EnemyEtis-1428");
				break;
			}
			case 27500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001370);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001415, EnemyEtis, "EnemyEtis-1429");
				break;
			}
			case 27520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001371);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001416, EnemyEtis, "EnemyEtis-1430");
				break;
			}
			case 27540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001372);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001417, EnemyEtis, "EnemyEtis-1431");
				break;
			}
			case 27560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001373);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001418, EnemyEtis, "EnemyEtis-1432");
				break;
			}
			case 27580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001374);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001419, EnemyEtis, "EnemyEtis-1433");
				break;
			}
			case 27600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001375);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001420, EnemyEtis, "EnemyEtis-1434");
				break;
			}
			case 27620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001376);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001421, EnemyEtis, "EnemyEtis-1435");
				break;
			}
			case 27640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001377);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001422, EnemyEtis, "EnemyEtis-1436");
				break;
			}
			case 27660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001378);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001423, EnemyEtis, "EnemyEtis-1437");
				break;
			}
			case 27680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001379);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001424, EnemyEtis, "EnemyEtis-1438");
				break;
			}
			case 27700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001380);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001425, EnemyEtis, "EnemyEtis-1439");
				break;
			}
			case 27720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001381);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001426, EnemyEtis, "EnemyEtis-1440");
				break;
			}
			case 27740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001382);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001427, EnemyEtis, "EnemyEtis-1441");
				break;
			}
			case 27760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001383);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001428, EnemyEtis, "EnemyEtis-1442");
				break;
			}
			case 27780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001384);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001429, EnemyEtis, "EnemyEtis-1443");
				break;
			}
			case 27800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001385);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001430, EnemyEtis, "EnemyEtis-1444");
				break;
			}
			case 27820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001386);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001431, EnemyEtis, "EnemyEtis-1445");
				break;
			}
			case 27840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001387);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001432, EnemyEtis, "EnemyEtis-1446");
				break;
			}
			case 27860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001388);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001433, EnemyEtis, "EnemyEtis-1447");
				break;
			}
			case 27880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001389);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001434, EnemyEtis, "EnemyEtis-1448");
				break;
			}
			case 27900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001390);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001435, EnemyEtis, "EnemyEtis-1449");
				break;
			}
			case 27920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001391);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001436, EnemyEtis, "EnemyEtis-1450");
				break;
			}
			case 27940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001392);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001437, EnemyEtis, "EnemyEtis-1451");
				break;
			}
			case 27960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001393);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001438, EnemyEtis, "EnemyEtis-1452");
				break;
			}
			case 27980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001394);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001439, EnemyEtis, "EnemyEtis-1453");
				break;
			}
			case 28000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001395);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001440, EnemyEtis, "EnemyEtis-1454");
				break;
			}
			case 28020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001396);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001441, EnemyEtis, "EnemyEtis-1455");
				break;
			}
			case 28040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001397);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001442, EnemyEtis, "EnemyEtis-1456");
				break;
			}
			case 28060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001398);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001443, EnemyEtis, "EnemyEtis-1457");
				break;
			}
			case 28080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001399);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001444, EnemyEtis, "EnemyEtis-1458");
				break;
			}
			case 28100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001400);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001445, EnemyEtis, "EnemyEtis-1459");
				break;
			}
			case 28120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001401);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001446, EnemyEtis, "EnemyEtis-1460");
				break;
			}
			case 28140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001402);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001447, EnemyEtis, "EnemyEtis-1461");
				break;
			}
			case 28160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001403);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001448, EnemyEtis, "EnemyEtis-1462");
				break;
			}
			case 28180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001404);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001449, EnemyEtis, "EnemyEtis-1463");
				break;
			}
			case 28200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001405);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001450, EnemyEtis, "EnemyEtis-1464");
				break;
			}
			case 28220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001406);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001451, EnemyEtis, "EnemyEtis-1465");
				break;
			}
			case 28240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001407);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001452, EnemyEtis, "EnemyEtis-1466");
				break;
			}
			case 28260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001408);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001453, EnemyEtis, "EnemyEtis-1467");
				break;
			}
			case 28280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001409);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001454, EnemyEtis, "EnemyEtis-1468");
				break;
			}
			case 28300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001410);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001455, EnemyEtis, "EnemyEtis-1469");
				break;
			}
			case 28320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001411);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001456, EnemyEtis, "EnemyEtis-1470");
				break;
			}
			case 28340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001412);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001457, EnemyEtis, "EnemyEtis-1471");
				break;
			}
			case 28360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001413);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001458, EnemyEtis, "EnemyEtis-1472");
				break;
			}
			case 28380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001414);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001459, EnemyEtis, "EnemyEtis-1473");
				break;
			}
			case 28400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001415);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001460, EnemyEtis, "EnemyEtis-1474");
				break;
			}
			case 28420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001416);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001461, EnemyEtis, "EnemyEtis-1475");
				break;
			}
			case 28440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001417);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001462, EnemyEtis, "EnemyEtis-1476");
				break;
			}
			case 28460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001418);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001463, EnemyEtis, "EnemyEtis-1477");
				break;
			}
			case 28480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001419);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001464, EnemyEtis, "EnemyEtis-1478");
				break;
			}
			case 28500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001420);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001465, EnemyEtis, "EnemyEtis-1479");
				break;
			}
			case 28520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001421);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001466, EnemyEtis, "EnemyEtis-1480");
				break;
			}
			case 28540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001422);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001467, EnemyEtis, "EnemyEtis-1481");
				break;
			}
			case 28560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001423);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001468, EnemyEtis, "EnemyEtis-1482");
				break;
			}
			case 28580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001424);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001469, EnemyEtis, "EnemyEtis-1483");
				break;
			}
			case 28600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001425);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001470, EnemyEtis, "EnemyEtis-1484");
				break;
			}
			case 28620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001426);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001471, EnemyEtis, "EnemyEtis-1485");
				break;
			}
			case 28640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001427);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001472, EnemyEtis, "EnemyEtis-1486");
				break;
			}
			case 28660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001428);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001473, EnemyEtis, "EnemyEtis-1487");
				break;
			}
			case 28680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001429);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001474, EnemyEtis, "EnemyEtis-1488");
				break;
			}
			case 28700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001430);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001475, EnemyEtis, "EnemyEtis-1489");
				break;
			}
			case 28720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001431);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001476, EnemyEtis, "EnemyEtis-1490");
				break;
			}
			case 28740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001432);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001477, EnemyEtis, "EnemyEtis-1491");
				break;
			}
			case 28760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001433);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001478, EnemyEtis, "EnemyEtis-1492");
				break;
			}
			case 28780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001434);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001479, EnemyEtis, "EnemyEtis-1493");
				break;
			}
			case 28800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001435);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001480, EnemyEtis, "EnemyEtis-1494");
				break;
			}
			case 28820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001436);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001481, EnemyEtis, "EnemyEtis-1495");
				break;
			}
			case 28840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001437);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001482, EnemyEtis, "EnemyEtis-1496");
				break;
			}
			case 28860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001438);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001483, EnemyEtis, "EnemyEtis-1497");
				break;
			}
			case 28880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001439);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001484, EnemyEtis, "EnemyEtis-1498");
				break;
			}
			case 28900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001440);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001485, EnemyEtis, "EnemyEtis-1499");
				break;
			}
			case 28920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001441);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001486, EnemyEtis, "EnemyEtis-1500");
				break;
			}
			case 28940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001442);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001487, EnemyEtis, "EnemyEtis-1501");
				break;
			}
			case 28960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001443);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001488, EnemyEtis, "EnemyEtis-1502");
				break;
			}
			case 28980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001444);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001489, EnemyEtis, "EnemyEtis-1503");
				break;
			}
			case 29000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001445);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001490, EnemyEtis, "EnemyEtis-1504");
				break;
			}
			case 29020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001446);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001491, EnemyEtis, "EnemyEtis-1505");
				break;
			}
			case 29040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001447);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001492, EnemyEtis, "EnemyEtis-1506");
				break;
			}
			case 29060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001448);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001493, EnemyEtis, "EnemyEtis-1507");
				break;
			}
			case 29080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001449);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001494, EnemyEtis, "EnemyEtis-1508");
				break;
			}
			case 29100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001450);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001495, EnemyEtis, "EnemyEtis-1509");
				break;
			}
			case 29120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001451);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001452);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001453);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001454);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001455);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001456);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001457);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001458);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001459);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001460);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001461);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001462);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001463);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001464);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001465);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001466);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001467);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001468);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001469);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001470);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001471);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001472);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001473);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001474);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001475);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001476);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001477);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001478);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001479);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001480);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001481);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001482);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001483);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001484);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001485);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001486);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001487);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001488);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001489);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001490);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001491);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001492);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001493);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001494);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 30000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001495);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 1501-1 ? _cnt_event+1 : _cnt_event);
	}
    // gen02 end


    switch (_pProg->get()) {
        case PROG_FAINAL: {
            if (_pProg->isJustChanged()) {
                //STG01Climax_終焉の処理
                _TRACE_("STG01Climax_終焉のStage01PartController::PROG_FAINALきた");
            }

            if (_pProg->getFrameInProgress() == 60) {
                fadeoutSceneWithBgm(300);
                throwEventUpperTree(EVENT_STG01_CTRLER_WAS_END); //ステージエンドを上位に伝える
            }
            //イベント発生待ち
            break;
        }
        default :
            break;
    }
}

void Stage01PartController::onCatchEvent(hashval prm_no, void* prm_pSource) {
    if (prm_no == EVENT_STG01_01_WAS_BROKEN) {
        _TRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_01_WAS_BROKEN");
        ((Stage*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STG01_02_WAS_BROKEN) {
        _TRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_02_WAS_BROKEN");
        ((Stage*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STG01_03_WAS_BROKEN) {
        _TRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_03_WAS_BROKEN");
        ((Stage*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STG01_WALLED_WAS_BROKEN) {
        _TRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_WALLED_WAS_BROKEN");
        ((Stage*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STG01_CLIMAX_WAS_BROKEN) {
        _TRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_CLIMAX_WAS_BROKENキャッチした。STAGE01PARTCONTROLLER_ENDINGを投げる");
        ((Stage*)prm_pSource)->sayonara(60*60);
        _pProg->change(PROG_FAINAL); //進捗をStage01PartController::PROG_FAINALに切り替える
    } else {

    }

}

Stage01PartController::~Stage01PartController() {

}
