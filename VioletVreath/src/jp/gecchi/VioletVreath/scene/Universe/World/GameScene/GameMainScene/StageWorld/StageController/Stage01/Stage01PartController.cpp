#include "stdafx.h"
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
	frame f[] = {1,20,40,60,80,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,140,160,180,200,220,240,260,280,300,320,340,360,380,400,420,440,460,480,500,520,540,560,580,600,620,640,660,680,700,720,740,760,780,800,820,840,860,880,900,920,940,960,980,1000,1020,1040,1060,1080,1100,1120,1140,1160,1180,1200,1220,1240,1260,1280,1300,1320,1340,1360,1380,1400,1420,1440,1460,1480,1500,1520,1540,1560,1580,1600,1620,1640,1660,1680,1700,1720,1740,1760,1780,1800,1820,1840,1860,1880,1900,1920,1940,1960,1980,2000,2020,2040,2060,2080,2100,2120,2140,2160,2180,2200,2220,2240,2260,2280,2300,2320,2340,2360,2380,2400,2420,2440,2460,2480,2500,2520,2540,2560,2580,2600,2620,2640,2660,2680,2700,2720,2740,2760,2780,2800,2820,2840,2860,2880,2900,2920,2940,2960,2980,3000,3020,3040,3060,3080,3100,3120,3140,3160,3180,3200,3220,3240,3260,3280,3300,3320,3340,3360,3380,3400,3420,3440,3460,3480,3500,3520,3540,3560,3580,3600,3620,3640,3660,3680,3700,3720,3740,3760,3780,3800,3820,3840,3860,3880,3900,3920,3940,3960,3980,4000,4020,4040,4060,4080,4100,4120,4140,4160,4180,4200,4220,4240,4260,4280,4300,4320,4340,4360,4380,4400,4420,4440,4460,4480,4500,4520,4540,4560,4580,4600,4620,4640,4660,4680,4700,4720,4740,4760,4780,4800,4820,4840,4860,4880,4900,4920,4940,4960,4980,5000,5020,5040,5060,5080,5100,5120,5140,5160,5180,5200,5220,5240,5260,5280,5300,5320,5340,5360,5380,5400,5420,5440,5460,5480,5500,5520,5540,5560,5580,5600,5620,5640,5660,5680,5700,5720,5740,5760,5780,5800,5820,5840,5860,5880,5900,5920,5940,5960,5980,6000,6020,6040,6060,6080,6100,6120,6140,6160,6180,6200,6220,6240,6260,6280,6300,6320,6340,6360,6380,6400,6420,6440,6460,6480,6500,6520,6540,6560,6580,6600,6620,6640,6660,6680,6700,6720,6740,6760,6780,6800,6820,6840,6860,6880,6900,6920,6940,6960,6980,7000,7020,7040,7060,7080,7100,7120,7140,7160,7180,7200,7220,7240,7260,7280,7300,7320,7340,7360,7380,7400,7420,7440,7460,7480,7500,7520,7540,7560,7580,7600,7620,7640,7660,7680,7700,7720,7740,7760,7780,7800,7820,7840,7860,7880,7900,7920,7940,7960,7980,8000,8020,8040,8060,8080,8100,8120,8140,8160,8180,8200,8220,8240,8260,8280,8300,8320,8340,8360,8380,8400,8420,8440,8460,8480,8500,8520,8540,8560,8580,8600,8620,8640,8660,8680,8700,8720,8740,8760,8780,8800,8820,8840,8860,8880,8900,8920,8940,8960,8980,9000,9020,9040,9060,9080,9100,9120,9140,9160,9180,9200,9220,9240,9260,9280,9300,9320,9340,9360,9380,9400,9420,9440,9460,9480,9500,9520,9540,9560,9580,9600,9620,9640,9660,9680,9700,9720,9740,9760,9780,9800,9820,9840,9860,9880,9900,9920,9940,9960,9980,10000,10020,10040,10060,10080,10100,10120,10140,10160,10180,10200,10220,10240,10260,10280,10300,10320,10340,10360,10380,10400,10420,10440,10460,10480,10500,10520,10540,10560,10580,10600,10620,10640,10660,10680,10700,10720,10740,10760,10780,10800,10820,10840,10860,10880,10900,10920,10940,10960,10980,11000,11020,11040,11060,11080,11100,11120,11140,11160,11180,11200,11220,11240,11260,11280,11300,11320,11340,11360,11380,11400,11420,11440,11460,11480,11500,11520,11540,11560,11580,11600,11620,11640,11660,11680,11700,11720,11740,11760,11780,11800,11820,11840,11860,11880,11900,11920,11940,11960,11980,12000,12020,12040,12060,12080,12100,12120,12140,12160,12180,12200,12220,12240,12260,12280,12300,12320,12340,12360,12380,12400,12420,12440,12460,12480,12500,12520,12540,12560,12580,12600,12620,12640,12660,12680,12700,12720,12740,12760,12780,12800,12820,12840,12860,12880,12900,12920,12940,12960,12980,13000,13020,13040,13060,13080,13100,13120,13140,13160,13180,13200,13220,13240,13260,13280,13300,13320,13340,13360,13380,13400,13420,13440,13460,13480,13500,13520,13540,13560,13580,13600,13620,13640,13660,13680,13700,13720,13740,13760,13780,13800,13820,13840,13860,13880,13900,13920,13940,13960,13980,14000,14020,14040,14060,14080,14100,14120,14140,14160,14180,14200,14220,14240,14260,14280,14300,14320,14340,14360,14380,14400,14420,14440,14460,14480,14500,14520,14540,14560,14580,14600,14620,14640,14660,14680,14700,14720,14740,14760,14780,14800,14820,14840,14860,14880,14900,14920,14940,14960,14980,15000,15020,15040,15060,15080,15100,15120,15140,15160,15180,15200,15220,15240,15260,15280,15300,15320,15340,15360,15380,15400,15420,15440,15460,15480,15500,15520,15540,15560,15580,15600,15620,15640,15660,15680,15700,15720,15740,15760,15780,15800,15820,15840,15860,15880,15900,15920,15940,15960,15980,16000,16020,16040,16060,16080,16100,16120,16140,16160,16180,16200,16220,16240,16260,16280,16300,16320,16340,16360,16380,16400,16420,16440,16460,16480,16500,16520,16540,16560,16580,16600,16620,16640,16660,16680,16700,16720,16740,16760,16780,16800,16820,16840,16860,16880,16900,16920,16940,16960,16980,17000,17020,17040,17060,17080,17100,17120,17140,17160,17180,17200,17220,17240,17260,17280,17300,17320,17340,17360,17380,17400,17420,17440,17460,17480,17500,17520,17540,17560,17580,17600,17620,17640,17660,17680,17700,17720,17740,17760,17780,17800,17820,17840,17860,17880,17900,17920,17940,17960,17980,18000,18020,18040,18060,18080,18100,18120,18140,18160,18180,18200,18220,18240,18260,18280,18300,18320,18340,18360,18380,18400,18420,18440,18460,18480,18500,18520,18540,18560,18580,18600,18620,18640,18660,18680,18700,18720,18740,18760,18780,18800,18820,18840,18860,18880,18900,18920,18940,18960,18980,19000,19020,19040,19060,19080,19100,19120,19140,19160,19180,19200,19220,19240,19260,19280,19300,19320,19340,19360,19380,19400,19420,19440,19460,19480,19500,19520,19540,19560,19580,19600,19620,19640,19660,19680,19700,19720,19740,19760,19780,19800,19820,19840,19860,19880,19900,19920,19940,19960,19980,20000,20020,20040,20060,20080,20100,20120,20140,20160,20180,20200,20220,20240,20260,20280,20300,20320,20340,20360,20380,20400,20420,20440,20460,20480,20500,20520,20540,20560,20580,20600,20620,20640,20660,20680,20700,20720,20740,20760,20780,20800,20820,20840,20860,20880,20900,20920,20940,20960,20980,21000,21020,21040,21060,21080,21100,21120,21140,21160,21180,21200,21220,21240,21260,21280,21300,21320,21340,21360,21380,21400,21420,21440,21460,21480,21500,21520,21540,21560,21580,21600,21620,21640,21660,21680,21700,21720,21740,21760,21780,21800,21820,21840,21860,21880,21900,21920,21940,21960,21980,22000,22020,22040,22060,22080,22100,22120,22140,22160,22180,22200,22220,22240,22260,22280,22300,22320,22340,22360,22380,22400,22420,22440,22460,22480,22500,22520,22540,22560,22580,22600,22620,22640,22660,22680,22700,22720,22740,22760,22780,22800,22820,22840,22860,22880,22900,22920,22940,22960,22980,23000,23020,23040,23060,23080,23100,23120,23140,23160,23180,23200,23220,23240,23260,23280,23300,23320,23340,23360,23380,23400,23420,23440,23460,23480,23500,23520,23540,23560,23580,23600,23620,23640,23660,23680,23700,23720,23740,23760,23780,23800,23820,23840,23860,23880,23900,23920,23940,23960,23980,24000,24020,24040,24060,24080,24100,24120,24140,24160,24180,24200,24220,24240,24260,24280,24300,24320,24340,24360,24380,24400,24420,24440,24460,24480,24500,24520,24540,24560,24580,24600,24620,24640,24660,24680,24700,24720,24740,24760,24780,24800,24820,24840,24860,24880,24900,24920,24940,24960,24980,25000,25020,25040,25060,25080,25100,25120,25140,25160,25180,25200,25220,25240,25260,25280,25300,25320,25340,25360,25380,25400,25420,25440,25460,25480,25500,25520,25540,25560,25580,25600,25620,25640,25660,25680,25700,25720,25740,25760,25780,25800,25820,25840,25860,25880,25900,25920,25940,25960,25980,26000,26020,26040,26060,26080,26100,26120,26140,26160,26180,26200,26220,26240,26260,26280,26300,26320,26340,26360,26380,26400,26420,26440,26460,26480,26500,26520,26540,26560,26580,26600,26620,26640,26660,26680,26700,26720,26740,26760,26780,26800,26820,26840,26860,26880,26900,26920,26940,26960,26980,27000,27020,27040,27060,27080,27100,27120,27140,27160,27180,27200,27220,27240,27260,27280,27300,27320,27340,27360,27380,27400,27420,27440,27460,27480,27500,27520,27540,27560,27580,27600,27620,27640,27660,27680,27700,27720,27740,27760,27780,27800,27820,27840,27860,27880,27900,27920,27940,27960,27980,28000,28020,28040,28060,28080,28100,28120,28140,28160,28180,28200,28220,28240,28260,28280,28300,28320,28340,28360,28380,28400,28420,28440,28460,28480,28500,28520,28540,28560,28580,28600,28620,28640,28660,28680,28700,28720,28740,28760,28780,28800,28820,28840,28860,28880,28900,28920,28940,28960,28980,29000,29020,29040,29060,29080,29100,29120,29140,29160,29180,29200,29220,29240,29260,29280,29300,29320,29340,29360,29380,29400,29420,29440,29460,29480,29500,29520,29540,29560,29580,29600,29620,29640,29660,29680,29700,29720,29740,29760,29780,29800,29820,29840,29860,29880,29900,29920,29940,29960,29980,30000};
	_paFrame_NextEvent = new frame[1527];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 1527;
	orderSceneToFactory(10000000, Stage01_01, "Stage01_01-1");
	orderActorToFactory(10000020, EnemyThisbe, "EnemyThisbe-2");
	orderActorToFactory(10000021, FormationHebe001, "FormationHebe001-3");
	orderActorToFactory(10000022, FormationEunomia001a, "FormationEunomia001a-4");
	orderActorToFactory(10000023, FormationEunomia001b, "FormationEunomia001b-5");
	orderActorToFactory(10000024, EnemyAstraea, "EnemyAstraea-6");
	orderActorToFactory(10000025, EnemyThisbe002, "EnemyThisbe002-7");
	orderActorToFactory(10000026, EnemyHermione, "EnemyHermione-8");
	orderActorToFactory(10000027, EnemyMetis, "EnemyMetis-9");
	orderActorToFactory(10000028, EnemyMetis, "EnemyMetis-10");
	orderActorToFactory(10000029, EnemyMetis, "EnemyMetis-11");
	orderActorToFactory(10000030, EnemyMetis, "EnemyMetis-12");
	orderActorToFactory(10000031, EnemyMetis, "EnemyMetis-13");
	orderActorToFactory(10000032, EnemyMetis, "EnemyMetis-14");
	orderActorToFactory(10000033, EnemyMetis, "EnemyMetis-15");
	orderActorToFactory(10000034, EnemyMetis, "EnemyMetis-16");
	orderActorToFactory(10000035, EnemyMetis, "EnemyMetis-17");
	orderActorToFactory(10000036, EnemyMetis, "EnemyMetis-18");
	orderActorToFactory(10000037, EnemyMetis, "EnemyMetis-19");
	orderActorToFactory(10000038, EnemyMetis, "EnemyMetis-20");
	orderActorToFactory(10000039, EnemyMetis, "EnemyMetis-21");
	orderActorToFactory(10000040, EnemyMetis, "EnemyMetis-22");
	orderActorToFactory(10000041, EnemyMetis, "EnemyMetis-23");
	orderActorToFactory(10000042, EnemyMetis, "EnemyMetis-24");
	orderActorToFactory(10000043, EnemyMetis, "EnemyMetis-25");
	orderActorToFactory(10000044, EnemyMetis, "EnemyMetis-26");
	orderActorToFactory(10000045, EnemyMetis, "EnemyMetis-27");
	orderActorToFactory(10000046, EnemyMetis, "EnemyMetis-28");
	orderActorToFactory(10000047, EnemyMetis, "EnemyMetis-29");
	orderActorToFactory(10000048, EnemyMetis, "EnemyMetis-30");
	orderActorToFactory(10000049, EnemyMetis, "EnemyMetis-31");
	orderActorToFactory(10000050, EnemyMetis, "EnemyMetis-32");
	orderActorToFactory(10000051, EnemyMetis, "EnemyMetis-33");
	orderActorToFactory(10000052, EnemyMetis, "EnemyMetis-34");
	orderActorToFactory(10000053, EnemyMetis, "EnemyMetis-35");
	orderActorToFactory(10000054, EnemyMetis, "EnemyMetis-36");
	orderActorToFactory(10000055, EnemyMetis, "EnemyMetis-37");
	orderActorToFactory(10000056, EnemyMetis, "EnemyMetis-38");
	orderActorToFactory(10000057, EnemyMetis, "EnemyMetis-39");
	orderActorToFactory(10000058, EnemyMetis, "EnemyMetis-40");
	orderActorToFactory(10000059, EnemyMetis, "EnemyMetis-41");
	orderActorToFactory(10000060, EnemyMetis, "EnemyMetis-42");
	orderActorToFactory(10000061, EnemyMetis, "EnemyMetis-43");
	orderActorToFactory(10000062, EnemyMetis, "EnemyMetis-44");
	orderActorToFactory(10000063, EnemyMetis, "EnemyMetis-45");
	orderActorToFactory(10000064, EnemyMetis, "EnemyMetis-46");
	orderActorToFactory(10000065, EnemyMetis, "EnemyMetis-47");
	orderActorToFactory(10000066, EnemyMetis, "EnemyMetis-48");
	orderActorToFactory(10000067, EnemyMetis, "EnemyMetis-49");
	orderActorToFactory(10001523, TestGu, "TestGu-50");
	orderActorToFactory(10001524, TestGu, "TestGu-51");
	orderActorToFactory(10001525, TestGu, "TestGu-52");
	orderActorToFactory(10001526, TestGu, "TestGu-53");
	orderActorToFactory(10001527, TestGu, "TestGu-54");
	orderActorToFactory(10001528, TestGu, "TestGu-55");
	orderActorToFactory(10001529, TestGu, "TestGu-56");
	orderActorToFactory(10001530, TestChoki, "TestChoki-57");
	orderActorToFactory(10001531, TestChoki, "TestChoki-58");
	orderActorToFactory(10001532, TestChoki, "TestChoki-59");
	orderActorToFactory(10001533, TestChoki, "TestChoki-60");
	orderActorToFactory(10001534, TestChoki, "TestChoki-61");
	orderActorToFactory(10001535, TestChoki, "TestChoki-62");
	orderActorToFactory(10001536, TestChoki, "TestChoki-63");
	orderActorToFactory(10001537, TestPa, "TestPa-64");
	orderActorToFactory(10001538, TestPa, "TestPa-65");
	orderActorToFactory(10001539, TestPa, "TestPa-66");
	orderActorToFactory(10001540, TestPa, "TestPa-67");
	orderActorToFactory(10001541, TestPa, "TestPa-68");
	orderActorToFactory(10001542, TestPa, "TestPa-69");
	orderActorToFactory(10001543, TestPa, "TestPa-70");
	orderActorToFactory(10001544, TestNomal, "TestNomal-71");
	orderActorToFactory(10001545, TestNomal, "TestNomal-72");
	orderActorToFactory(10001546, TestNomal, "TestNomal-73");
	orderActorToFactory(10001547, TestNomal, "TestNomal-74");
	orderActorToFactory(10001548, TestNomal, "TestNomal-75");
	orderActorToFactory(10001549, TestNomal, "TestNomal-76");
	orderActorToFactory(10001550, TestNomal, "TestNomal-77");
	orderActorToFactory(10001552, FormationSappho001a, "FormationSappho001a-78");
	orderActorToFactory(10001553, EnemyHermione, "EnemyHermione-79");
	orderActorToFactory(10001554, FormationSappho001a, "FormationSappho001a-80");
	orderActorToFactory(10001555, FormationSappho001b, "FormationSappho001b-81");
	orderActorToFactory(10001556, FormationSappho001a, "FormationSappho001a-82");
	orderActorToFactory(10001571, FormationAntiope001, "FormationAntiope001-83");
	orderActorToFactory(10001582, FormationAdelheid001, "FormationAdelheid001-84");
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
	if (getActiveFrame() == _paFrame_NextEvent[_cnt_event]) {
		switch (getActiveFrame()) {
			case 1: {
				break;
			}
			case 20: {
				orderActorToFactory(10000068, EnemyMetis, "EnemyMetis-85");
				break;
			}
			case 40: {
				orderActorToFactory(10000069, EnemyMetis, "EnemyMetis-86");
				break;
			}
			case 60: {
				orderActorToFactory(10000070, EnemyMetis, "EnemyMetis-87");
				break;
			}
			case 80: {
				orderActorToFactory(10000071, EnemyMetis, "EnemyMetis-88");
				break;
			}
			case 100: {
				Stage01_01* pScene = (Stage01_01*)obtainSceneFromFactory(10000000);
				addSubLast(pScene);
				_pBgmPerformer->play_fadein(0);
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000027);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000072, EnemyMetis, "EnemyMetis-89");
				TestGu* p = (TestGu*)obtainActorFromFactory(10001523);
				getSceneDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = 300000;
				p->_Z = 100000;
				orderActorToFactory(10001551, FormationSappho001b, "FormationSappho001b-90");
				orderActorToFactory(10001559, FormationPallas001a, "FormationPallas001a-91");
				orderActorToFactory(10001560, FormationPallas001b, "FormationPallas001b-92");
				orderActorToFactory(10001561, FormationPallas001c, "FormationPallas001c-93");
				orderActorToFactory(10001562, FormationPallas001d, "FormationPallas001d-94");
				orderActorToFactory(10001563, FormationPallas001a, "FormationPallas001a-95");
				orderActorToFactory(10001564, FormationPallas001d, "FormationPallas001d-96");
				orderActorToFactory(10001565, FormationPallas001b, "FormationPallas001b-97");
				orderActorToFactory(10001566, FormationPallas001c, "FormationPallas001c-98");
				orderActorToFactory(10001567, FormationPallas001a, "FormationPallas001a-99");
				orderActorToFactory(10001568, FormationPallas001d, "FormationPallas001d-100");
				orderActorToFactory(10001569, FormationPallas001b, "FormationPallas001b-101");
				orderActorToFactory(10001570, FormationPallas001c, "FormationPallas001c-102");
				orderActorToFactory(10001572, FormationAntiope001, "FormationAntiope001-103");
				break;
			}
			case 101: {
				TestGu* p = (TestGu*)obtainActorFromFactory(10001524);
				getSceneDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = 200000;
				p->_Z = 100000;
				break;
			}
			case 102: {
				TestGu* p = (TestGu*)obtainActorFromFactory(10001525);
				getSceneDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = 100000;
				p->_Z = 100000;
				break;
			}
			case 103: {
				TestGu* p = (TestGu*)obtainActorFromFactory(10001526);
				getSceneDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = 0;
				p->_Z = 100000;
				break;
			}
			case 104: {
				TestGu* p = (TestGu*)obtainActorFromFactory(10001527);
				getSceneDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = -100000;
				p->_Z = 100000;
				break;
			}
			case 105: {
				TestGu* p = (TestGu*)obtainActorFromFactory(10001528);
				getSceneDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = -200000;
				p->_Z = 100000;
				break;
			}
			case 106: {
				TestGu* p = (TestGu*)obtainActorFromFactory(10001529);
				getSceneDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = -300000;
				p->_Z = 100000;
				break;
			}
			case 107: {
				TestChoki* p = (TestChoki*)obtainActorFromFactory(10001530);
				getSceneDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = 300000;
				p->_Z = 0;
				break;
			}
			case 108: {
				TestChoki* p = (TestChoki*)obtainActorFromFactory(10001531);
				getSceneDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = 200000;
				p->_Z = 0;
				break;
			}
			case 109: {
				TestChoki* p = (TestChoki*)obtainActorFromFactory(10001532);
				getSceneDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = 100000;
				p->_Z = 0;
				break;
			}
			case 110: {
				TestChoki* p = (TestChoki*)obtainActorFromFactory(10001533);
				getSceneDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = 0;
				p->_Z = 0;
				break;
			}
			case 111: {
				TestChoki* p = (TestChoki*)obtainActorFromFactory(10001534);
				getSceneDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = -100000;
				p->_Z = 0;
				break;
			}
			case 112: {
				TestChoki* p = (TestChoki*)obtainActorFromFactory(10001535);
				getSceneDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = -200000;
				p->_Z = 0;
				break;
			}
			case 113: {
				TestChoki* p = (TestChoki*)obtainActorFromFactory(10001536);
				getSceneDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = -300000;
				p->_Z = 0;
				break;
			}
			case 114: {
				TestPa* p = (TestPa*)obtainActorFromFactory(10001537);
				getSceneDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = 300000;
				p->_Z = -100000;
				break;
			}
			case 115: {
				TestPa* p = (TestPa*)obtainActorFromFactory(10001538);
				getSceneDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = 200000;
				p->_Z = -100000;
				break;
			}
			case 116: {
				TestPa* p = (TestPa*)obtainActorFromFactory(10001539);
				getSceneDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = 100000;
				p->_Z = -100000;
				break;
			}
			case 117: {
				TestPa* p = (TestPa*)obtainActorFromFactory(10001540);
				getSceneDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = 0;
				p->_Z = -100000;
				break;
			}
			case 118: {
				TestPa* p = (TestPa*)obtainActorFromFactory(10001541);
				getSceneDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = -100000;
				p->_Z = -100000;
				break;
			}
			case 119: {
				TestPa* p = (TestPa*)obtainActorFromFactory(10001542);
				getSceneDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = -200000;
				p->_Z = -100000;
				break;
			}
			case 120: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000028);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000073, EnemyMetis, "EnemyMetis-104");
				TestPa* p = (TestPa*)obtainActorFromFactory(10001543);
				getSceneDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = -300000;
				p->_Z = -100000;
				orderActorToFactory(10001557, FormationSappho001b, "FormationSappho001b-105");
				break;
			}
			case 121: {
				TestNomal* p = (TestNomal*)obtainActorFromFactory(10001544);
				getSceneDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = 300000;
				p->_Z = -200000;
				break;
			}
			case 122: {
				TestNomal* p = (TestNomal*)obtainActorFromFactory(10001545);
				getSceneDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = 200000;
				p->_Z = -200000;
				break;
			}
			case 123: {
				TestNomal* p = (TestNomal*)obtainActorFromFactory(10001546);
				getSceneDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = 100000;
				p->_Z = -200000;
				break;
			}
			case 124: {
				TestNomal* p = (TestNomal*)obtainActorFromFactory(10001547);
				getSceneDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = 0;
				p->_Z = -200000;
				break;
			}
			case 125: {
				TestNomal* p = (TestNomal*)obtainActorFromFactory(10001548);
				getSceneDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = -100000;
				p->_Z = -200000;
				break;
			}
			case 126: {
				TestNomal* p = (TestNomal*)obtainActorFromFactory(10001549);
				getSceneDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = -200000;
				p->_Z = -200000;
				break;
			}
			case 127: {
				TestNomal* p = (TestNomal*)obtainActorFromFactory(10001550);
				getSceneDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = -300000;
				p->_Z = -200000;
				break;
			}
			case 140: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000029);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000074, EnemyMetis, "EnemyMetis-106");
				break;
			}
			case 160: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000030);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000075, EnemyMetis, "EnemyMetis-107");
				break;
			}
			case 180: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000031);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000076, EnemyMetis, "EnemyMetis-108");
				break;
			}
			case 200: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000032);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000077, EnemyMetis, "EnemyMetis-109");
				break;
			}
			case 220: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000033);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000078, EnemyMetis, "EnemyMetis-110");
				break;
			}
			case 240: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000034);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000079, EnemyMetis, "EnemyMetis-111");
				break;
			}
			case 260: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000035);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000080, EnemyMetis, "EnemyMetis-112");
				break;
			}
			case 280: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000036);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000081, EnemyMetis, "EnemyMetis-113");
				break;
			}
			case 300: {
				orderActorToFactory(10000005, EnemyHermione, "EnemyHermione-114");
				EnemyThisbe* p = (EnemyThisbe*)obtainActorFromFactory(10000020);
				getSceneDirector()->addSubGroup(p);
				p->_X = 0;
				p->_Y = 0;
				p->_Z = 2000000;
				FormationHebe001* pF115 = (FormationHebe001*)obtainActorFromFactory(10000021);
				getSceneDirector()->addSubGroup(pF115);
				FormationEunomia001a* pFormationEunomia = (FormationEunomia001a*)obtainActorFromFactory(10000022);
				getSceneDirector()->addSubGroup(pFormationEunomia);
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000037);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000082, EnemyMetis, "EnemyMetis-116");
				FormationSappho001a* pFSap = (FormationSappho001a*)obtainActorFromFactory(10001554);
				getSceneDirector()->addSubGroup(pFSap);
				break;
			}
			case 320: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000038);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000083, EnemyMetis, "EnemyMetis-117");
				break;
			}
			case 340: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000039);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000084, EnemyMetis, "EnemyMetis-118");
				break;
			}
			case 360: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000040);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000085, EnemyMetis, "EnemyMetis-119");
				break;
			}
			case 380: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000041);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000086, EnemyMetis, "EnemyMetis-120");
				break;
			}
			case 400: {
				EnemyThisbe002* p = (EnemyThisbe002*)obtainActorFromFactory(10000025);
				getSceneDirector()->addSubGroup(p);
				p->_X = 0;
				p->_Y = 0;
				p->_Z = 2000000;
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000042);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000087, EnemyMetis, "EnemyMetis-121");
				FormationSappho001a* pF = (FormationSappho001a*)obtainActorFromFactory(10001552);
				getSceneDirector()->addSubGroup(pF);
				FormationAntiope001* pFAnti = (FormationAntiope001*)obtainActorFromFactory(10001571);
				getSceneDirector()->addSubGroup(pFAnti);
				break;
			}
			case 420: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000043);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000088, EnemyMetis, "EnemyMetis-122");
				break;
			}
			case 440: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000044);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000089, EnemyMetis, "EnemyMetis-123");
				break;
			}
			case 460: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000045);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000090, EnemyMetis, "EnemyMetis-124");
				break;
			}
			case 480: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000046);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000091, EnemyMetis, "EnemyMetis-125");
				break;
			}
			case 500: {
				FormationEunomia001b* pFormationEunomia = (FormationEunomia001b*)obtainActorFromFactory(10000023);
				getSceneDirector()->addSubGroup(pFormationEunomia);
				EnemyHermione* p = (EnemyHermione*)obtainActorFromFactory(10000026);
				getSceneDirector()->addSubGroup(p);
				p->_X = 300000;
				p->_Y = 0;
				p->_Z = 0;
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000047);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000092, EnemyMetis, "EnemyMetis-126");
				FormationAdelheid001* pF = (FormationAdelheid001*)obtainActorFromFactory(10001582);
				getSceneDirector()->addSubGroup(pF);
				pF->locate(PX_C(200), PX_C(0), PX_C(0), D_ANG(10), D_ANG(0));
				break;
			}
			case 520: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000048);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000093, EnemyMetis, "EnemyMetis-127");
				break;
			}
			case 540: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000049);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000094, EnemyMetis, "EnemyMetis-128");
				FormationSappho001b* pFSap = (FormationSappho001b*)obtainActorFromFactory(10001555);
				getSceneDirector()->addSubGroup(pFSap);
				break;
			}
			case 560: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000050);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000095, EnemyMetis, "EnemyMetis-129");
				break;
			}
			case 580: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000051);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000096, EnemyMetis, "EnemyMetis-130");
				break;
			}
			case 600: {
				EnemyAstraea* pAstraea2 = (EnemyAstraea*)obtainActorFromFactory(10000024);
				getSceneDirector()->addSubGroup(pAstraea2);
				pAstraea2->_Z = 1000000;
				pAstraea2->_Y = 10000;
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000052);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000097, EnemyMetis, "EnemyMetis-131");
				break;
			}
			case 620: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000053);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000098, EnemyMetis, "EnemyMetis-132");
				break;
			}
			case 640: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000054);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000099, EnemyMetis, "EnemyMetis-133");
				break;
			}
			case 660: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000055);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000100, EnemyMetis, "EnemyMetis-134");
				break;
			}
			case 680: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000056);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000101, EnemyMetis, "EnemyMetis-135");
				break;
			}
			case 700: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000057);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000102, EnemyMetis, "EnemyMetis-136");
				break;
			}
			case 720: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000058);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000103, EnemyMetis, "EnemyMetis-137");
				break;
			}
			case 740: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000059);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000104, EnemyMetis, "EnemyMetis-138");
				break;
			}
			case 760: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000060);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000105, EnemyMetis, "EnemyMetis-139");
				break;
			}
			case 780: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000061);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000106, EnemyMetis, "EnemyMetis-140");
				FormationSappho001a* pFSap = (FormationSappho001a*)obtainActorFromFactory(10001556);
				getSceneDirector()->addSubGroup(pFSap);
				break;
			}
			case 800: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000062);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000107, EnemyMetis, "EnemyMetis-141");
				break;
			}
			case 820: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000063);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000108, EnemyMetis, "EnemyMetis-142");
				break;
			}
			case 840: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000064);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000109, EnemyMetis, "EnemyMetis-143");
				break;
			}
			case 860: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000065);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000110, EnemyMetis, "EnemyMetis-144");
				break;
			}
			case 880: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000066);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000111, EnemyMetis, "EnemyMetis-145");
				break;
			}
			case 900: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000067);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000112, EnemyMetis, "EnemyMetis-146");
				EnemyHermione* p = (EnemyHermione*)obtainActorFromFactory(10001553);
				getSceneDirector()->addSubGroup(p);
				p->_X = 8000000;
				p->_Y = RND(-200000,200000);
				p->_Z = RND(-200000,200000);
				break;
			}
			case 920: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000068);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000113, EnemyMetis, "EnemyMetis-147");
				break;
			}
			case 940: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000069);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000114, EnemyMetis, "EnemyMetis-148");
				break;
			}
			case 960: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000070);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000115, EnemyMetis, "EnemyMetis-149");
				break;
			}
			case 980: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000071);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000116, EnemyMetis, "EnemyMetis-150");
				break;
			}
			case 1000: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000072);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000117, EnemyMetis, "EnemyMetis-151");
				FormationSappho001b* pF = (FormationSappho001b*)obtainActorFromFactory(10001551);
				getSceneDirector()->addSubGroup(pF);
				{
				FormationTableScene* ta = NEW FormationTableScene("FormationTableScene-152");
				ta->setMaxPerformFrame(3000);
				addSubLast(ta);
				ta->addToTable(((FormationPallas001a*)obtainActorFromFactory(10001559)), 400);
				ta->addToTable(((FormationPallas001b*)obtainActorFromFactory(10001560)), 400);
				ta->addToTable(((FormationPallas001c*)obtainActorFromFactory(10001561)), 400);
				ta->addToTable(((FormationPallas001d*)obtainActorFromFactory(10001562)), 400);
				ta->addToTable(((FormationPallas001a*)obtainActorFromFactory(10001563)), 1);
				ta->addToTable(((FormationPallas001d*)obtainActorFromFactory(10001564)), 400);
				ta->addToTable(((FormationPallas001b*)obtainActorFromFactory(10001565)), 1);
				ta->addToTable(((FormationPallas001c*)obtainActorFromFactory(10001566)), 400);
				ta->addToTable(((FormationPallas001a*)obtainActorFromFactory(10001567)), 1);
				ta->addToTable(((FormationPallas001d*)obtainActorFromFactory(10001568)), 1);
				ta->addToTable(((FormationPallas001b*)obtainActorFromFactory(10001569)), 1);
				ta->addToTable(((FormationPallas001c*)obtainActorFromFactory(10001570)), 400);
				}
				FormationAntiope001* pFAnti = (FormationAntiope001*)obtainActorFromFactory(10001572);
				getSceneDirector()->addSubGroup(pFAnti);
				break;
			}
			case 1020: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000073);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000118, EnemyMetis, "EnemyMetis-153");
				FormationSappho001b* pFSap = (FormationSappho001b*)obtainActorFromFactory(10001557);
				getSceneDirector()->addSubGroup(pFSap);
				break;
			}
			case 1040: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000074);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000119, EnemyMetis, "EnemyMetis-154");
				break;
			}
			case 1060: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000075);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000120, EnemyMetis, "EnemyMetis-155");
				break;
			}
			case 1080: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000076);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000121, EnemyMetis, "EnemyMetis-156");
				break;
			}
			case 1100: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000077);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000122, EnemyMetis, "EnemyMetis-157");
				break;
			}
			case 1120: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000078);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000123, EnemyMetis, "EnemyMetis-158");
				break;
			}
			case 1140: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000079);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000124, EnemyMetis, "EnemyMetis-159");
				break;
			}
			case 1160: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000080);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000125, EnemyMetis, "EnemyMetis-160");
				break;
			}
			case 1180: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000081);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000126, EnemyMetis, "EnemyMetis-161");
				break;
			}
			case 1200: {
				EnemyHermione* p = (EnemyHermione*)obtainActorFromFactory(10000005);
				getSceneDirector()->addSubGroup(p);
				p->_X = RND(000000,1000000);
				p->_Y = RND(-600000,600000);
				p->_Z = RND(-600000,600000);
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000082);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000127, EnemyMetis, "EnemyMetis-162");
				break;
			}
			case 1220: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000083);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000128, EnemyMetis, "EnemyMetis-163");
				break;
			}
			case 1240: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000084);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000129, EnemyMetis, "EnemyMetis-164");
				break;
			}
			case 1260: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000085);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000130, EnemyMetis, "EnemyMetis-165");
				break;
			}
			case 1280: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000086);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000131, EnemyMetis, "EnemyMetis-166");
				break;
			}
			case 1300: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000087);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000132, EnemyMetis, "EnemyMetis-167");
				break;
			}
			case 1320: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000088);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000133, EnemyMetis, "EnemyMetis-168");
				break;
			}
			case 1340: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000089);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000134, EnemyMetis, "EnemyMetis-169");
				break;
			}
			case 1360: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000090);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000135, EnemyMetis, "EnemyMetis-170");
				break;
			}
			case 1380: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000091);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000136, EnemyMetis, "EnemyMetis-171");
				break;
			}
			case 1400: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000092);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000137, EnemyMetis, "EnemyMetis-172");
				break;
			}
			case 1420: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000093);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000138, EnemyMetis, "EnemyMetis-173");
				break;
			}
			case 1440: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000094);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000139, EnemyMetis, "EnemyMetis-174");
				break;
			}
			case 1460: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000095);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000140, EnemyMetis, "EnemyMetis-175");
				break;
			}
			case 1480: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000096);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000141, EnemyMetis, "EnemyMetis-176");
				break;
			}
			case 1500: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000097);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000142, EnemyMetis, "EnemyMetis-177");
				break;
			}
			case 1520: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000098);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000143, EnemyMetis, "EnemyMetis-178");
				break;
			}
			case 1540: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000099);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000144, EnemyMetis, "EnemyMetis-179");
				break;
			}
			case 1560: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000100);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000145, EnemyMetis, "EnemyMetis-180");
				break;
			}
			case 1580: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000101);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000146, EnemyMetis, "EnemyMetis-181");
				break;
			}
			case 1600: {
				orderActorToFactory(10000004, FormationEunomia001a, "FormationEunomia001a-182");
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000102);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000147, EnemyMetis, "EnemyMetis-183");
				break;
			}
			case 1620: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000103);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000148, EnemyMetis, "EnemyMetis-184");
				break;
			}
			case 1640: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000104);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000149, EnemyMetis, "EnemyMetis-185");
				break;
			}
			case 1660: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000105);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000150, EnemyMetis, "EnemyMetis-186");
				break;
			}
			case 1680: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000106);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000151, EnemyMetis, "EnemyMetis-187");
				break;
			}
			case 1700: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000107);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000152, EnemyMetis, "EnemyMetis-188");
				break;
			}
			case 1720: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000108);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000153, EnemyMetis, "EnemyMetis-189");
				break;
			}
			case 1740: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000109);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000154, EnemyMetis, "EnemyMetis-190");
				break;
			}
			case 1760: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000110);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000155, EnemyMetis, "EnemyMetis-191");
				break;
			}
			case 1780: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000111);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000156, EnemyMetis, "EnemyMetis-192");
				break;
			}
			case 1800: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000112);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000157, EnemyMetis, "EnemyMetis-193");
				break;
			}
			case 1820: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000113);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000158, EnemyMetis, "EnemyMetis-194");
				break;
			}
			case 1840: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000114);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000159, EnemyMetis, "EnemyMetis-195");
				break;
			}
			case 1860: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000115);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000160, EnemyMetis, "EnemyMetis-196");
				break;
			}
			case 1880: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000116);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000161, EnemyMetis, "EnemyMetis-197");
				break;
			}
			case 1900: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000117);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000162, EnemyMetis, "EnemyMetis-198");
				break;
			}
			case 1920: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000118);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000163, EnemyMetis, "EnemyMetis-199");
				break;
			}
			case 1940: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000119);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000164, EnemyMetis, "EnemyMetis-200");
				break;
			}
			case 1960: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000120);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000165, EnemyMetis, "EnemyMetis-201");
				break;
			}
			case 1980: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000121);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000166, EnemyMetis, "EnemyMetis-202");
				break;
			}
			case 2000: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000122);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000167, EnemyMetis, "EnemyMetis-203");
				break;
			}
			case 2020: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000123);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000168, EnemyMetis, "EnemyMetis-204");
				break;
			}
			case 2040: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000124);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000169, EnemyMetis, "EnemyMetis-205");
				break;
			}
			case 2060: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000125);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000170, EnemyMetis, "EnemyMetis-206");
				break;
			}
			case 2080: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000126);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000171, EnemyMetis, "EnemyMetis-207");
				break;
			}
			case 2100: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000127);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000172, EnemyMetis, "EnemyMetis-208");
				break;
			}
			case 2120: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000128);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000173, EnemyMetis, "EnemyMetis-209");
				break;
			}
			case 2140: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000129);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000174, EnemyMetis, "EnemyMetis-210");
				break;
			}
			case 2160: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000130);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000175, EnemyMetis, "EnemyMetis-211");
				break;
			}
			case 2180: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000131);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000176, EnemyMetis, "EnemyMetis-212");
				break;
			}
			case 2200: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000132);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000177, EnemyMetis, "EnemyMetis-213");
				break;
			}
			case 2220: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000133);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000178, EnemyMetis, "EnemyMetis-214");
				break;
			}
			case 2240: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000134);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000179, EnemyMetis, "EnemyMetis-215");
				break;
			}
			case 2260: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000135);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000180, EnemyMetis, "EnemyMetis-216");
				break;
			}
			case 2280: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000136);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000181, EnemyMetis, "EnemyMetis-217");
				break;
			}
			case 2300: {
				orderActorToFactory(10000006, EnemyHermione, "EnemyHermione-218");
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000137);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000182, EnemyMetis, "EnemyMetis-219");
				break;
			}
			case 2320: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000138);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000183, EnemyMetis, "EnemyMetis-220");
				break;
			}
			case 2340: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000139);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000184, EnemyMetis, "EnemyMetis-221");
				break;
			}
			case 2360: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000140);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000185, EnemyMetis, "EnemyMetis-222");
				break;
			}
			case 2380: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000141);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000186, EnemyMetis, "EnemyMetis-223");
				break;
			}
			case 2400: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000142);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000187, EnemyMetis, "EnemyMetis-224");
				break;
			}
			case 2420: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000143);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000188, EnemyMetis, "EnemyMetis-225");
				break;
			}
			case 2440: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000144);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000189, EnemyMetis, "EnemyMetis-226");
				break;
			}
			case 2460: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000145);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000190, EnemyMetis, "EnemyMetis-227");
				break;
			}
			case 2480: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000146);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000191, EnemyMetis, "EnemyMetis-228");
				break;
			}
			case 2500: {
				FormationEunomia001a* pFormationEunomia = (FormationEunomia001a*)obtainActorFromFactory(10000004);
				getSceneDirector()->addSubGroup(pFormationEunomia);
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000147);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000192, EnemyMetis, "EnemyMetis-229");
				break;
			}
			case 2520: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000148);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000193, EnemyMetis, "EnemyMetis-230");
				break;
			}
			case 2540: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000149);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000194, EnemyMetis, "EnemyMetis-231");
				break;
			}
			case 2560: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000150);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000195, EnemyMetis, "EnemyMetis-232");
				break;
			}
			case 2580: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000151);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000196, EnemyMetis, "EnemyMetis-233");
				break;
			}
			case 2600: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000152);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000197, EnemyMetis, "EnemyMetis-234");
				break;
			}
			case 2620: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000153);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000198, EnemyMetis, "EnemyMetis-235");
				break;
			}
			case 2640: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000154);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000199, EnemyMetis, "EnemyMetis-236");
				break;
			}
			case 2660: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000155);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000200, EnemyMetis, "EnemyMetis-237");
				break;
			}
			case 2680: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000156);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000201, EnemyMetis, "EnemyMetis-238");
				break;
			}
			case 2700: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000157);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000202, EnemyMetis, "EnemyMetis-239");
				break;
			}
			case 2720: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000158);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000203, EnemyMetis, "EnemyMetis-240");
				break;
			}
			case 2740: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000159);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000204, EnemyMetis, "EnemyMetis-241");
				break;
			}
			case 2760: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000160);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000205, EnemyMetis, "EnemyMetis-242");
				break;
			}
			case 2780: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000161);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000206, EnemyMetis, "EnemyMetis-243");
				break;
			}
			case 2800: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000162);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000207, EnemyMetis, "EnemyMetis-244");
				break;
			}
			case 2820: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000163);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000208, EnemyMetis, "EnemyMetis-245");
				break;
			}
			case 2840: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000164);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000209, EnemyMetis, "EnemyMetis-246");
				break;
			}
			case 2860: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000165);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000210, EnemyMetis, "EnemyMetis-247");
				break;
			}
			case 2880: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000166);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000211, EnemyMetis, "EnemyMetis-248");
				break;
			}
			case 2900: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000167);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000212, EnemyMetis, "EnemyMetis-249");
				break;
			}
			case 2920: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000168);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000213, EnemyMetis, "EnemyMetis-250");
				break;
			}
			case 2940: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000169);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000214, EnemyMetis, "EnemyMetis-251");
				break;
			}
			case 2960: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000170);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000215, EnemyMetis, "EnemyMetis-252");
				break;
			}
			case 2980: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000171);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000216, EnemyMetis, "EnemyMetis-253");
				break;
			}
			case 3000: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000172);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000217, EnemyMetis, "EnemyMetis-254");
				break;
			}
			case 3020: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000173);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000218, EnemyMetis, "EnemyMetis-255");
				break;
			}
			case 3040: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000174);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000219, EnemyMetis, "EnemyMetis-256");
				break;
			}
			case 3060: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000175);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000220, EnemyMetis, "EnemyMetis-257");
				break;
			}
			case 3080: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000176);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000221, EnemyMetis, "EnemyMetis-258");
				break;
			}
			case 3100: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000177);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000222, EnemyMetis, "EnemyMetis-259");
				break;
			}
			case 3120: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000178);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000223, EnemyMetis, "EnemyMetis-260");
				break;
			}
			case 3140: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000179);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000224, EnemyMetis, "EnemyMetis-261");
				break;
			}
			case 3160: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000180);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000225, EnemyMetis, "EnemyMetis-262");
				break;
			}
			case 3180: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000181);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000226, EnemyMetis, "EnemyMetis-263");
				break;
			}
			case 3200: {
				EnemyHermione* p = (EnemyHermione*)obtainActorFromFactory(10000006);
				getSceneDirector()->addSubGroup(p);
				p->_X = RND(000000,1000000);
				p->_Y = RND(-600000,600000);
				p->_Z = RND(-600000,600000);
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000182);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000227, EnemyMetis, "EnemyMetis-264");
				break;
			}
			case 3220: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000183);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000228, EnemyMetis, "EnemyMetis-265");
				break;
			}
			case 3240: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000184);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000229, EnemyMetis, "EnemyMetis-266");
				break;
			}
			case 3260: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000185);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000230, EnemyMetis, "EnemyMetis-267");
				break;
			}
			case 3280: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000186);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000231, EnemyMetis, "EnemyMetis-268");
				break;
			}
			case 3300: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000187);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000232, EnemyMetis, "EnemyMetis-269");
				break;
			}
			case 3320: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000188);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000233, EnemyMetis, "EnemyMetis-270");
				break;
			}
			case 3340: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000189);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000234, EnemyMetis, "EnemyMetis-271");
				break;
			}
			case 3360: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000190);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000235, EnemyMetis, "EnemyMetis-272");
				break;
			}
			case 3380: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000191);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000236, EnemyMetis, "EnemyMetis-273");
				break;
			}
			case 3400: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000192);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000237, EnemyMetis, "EnemyMetis-274");
				break;
			}
			case 3420: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000193);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000238, EnemyMetis, "EnemyMetis-275");
				break;
			}
			case 3440: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000194);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000239, EnemyMetis, "EnemyMetis-276");
				break;
			}
			case 3460: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000195);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000240, EnemyMetis, "EnemyMetis-277");
				break;
			}
			case 3480: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000196);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000241, EnemyMetis, "EnemyMetis-278");
				break;
			}
			case 3500: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000197);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000242, EnemyMetis, "EnemyMetis-279");
				break;
			}
			case 3520: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000198);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000243, EnemyMetis, "EnemyMetis-280");
				break;
			}
			case 3540: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000199);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000244, EnemyMetis, "EnemyMetis-281");
				break;
			}
			case 3560: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000200);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000245, EnemyMetis, "EnemyMetis-282");
				break;
			}
			case 3580: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000201);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000246, EnemyMetis, "EnemyMetis-283");
				break;
			}
			case 3600: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000202);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000247, EnemyMetis, "EnemyMetis-284");
				break;
			}
			case 3620: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000203);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000248, EnemyMetis, "EnemyMetis-285");
				break;
			}
			case 3640: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000204);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000249, EnemyMetis, "EnemyMetis-286");
				break;
			}
			case 3660: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000205);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000250, EnemyMetis, "EnemyMetis-287");
				break;
			}
			case 3680: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000206);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000251, EnemyMetis, "EnemyMetis-288");
				break;
			}
			case 3700: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000207);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000252, EnemyMetis, "EnemyMetis-289");
				break;
			}
			case 3720: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000208);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000253, EnemyMetis, "EnemyMetis-290");
				break;
			}
			case 3740: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000209);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000254, EnemyMetis, "EnemyMetis-291");
				break;
			}
			case 3760: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000210);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000255, EnemyMetis, "EnemyMetis-292");
				break;
			}
			case 3780: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000211);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000256, EnemyMetis, "EnemyMetis-293");
				break;
			}
			case 3800: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000212);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000257, EnemyMetis, "EnemyMetis-294");
				break;
			}
			case 3820: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000213);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000258, EnemyMetis, "EnemyMetis-295");
				break;
			}
			case 3840: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000214);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000259, EnemyMetis, "EnemyMetis-296");
				break;
			}
			case 3860: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000215);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000260, EnemyMetis, "EnemyMetis-297");
				break;
			}
			case 3880: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000216);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000261, EnemyMetis, "EnemyMetis-298");
				break;
			}
			case 3900: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000217);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000262, EnemyMetis, "EnemyMetis-299");
				break;
			}
			case 3920: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000218);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000263, EnemyMetis, "EnemyMetis-300");
				break;
			}
			case 3940: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000219);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000264, EnemyMetis, "EnemyMetis-301");
				break;
			}
			case 3960: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000220);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000265, EnemyMetis, "EnemyMetis-302");
				break;
			}
			case 3980: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000221);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000266, EnemyMetis, "EnemyMetis-303");
				break;
			}
			case 4000: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000222);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000267, EnemyMetis, "EnemyMetis-304");
				break;
			}
			case 4020: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000223);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000268, EnemyMetis, "EnemyMetis-305");
				break;
			}
			case 4040: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000224);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000269, EnemyMetis, "EnemyMetis-306");
				break;
			}
			case 4060: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000225);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000270, EnemyMetis, "EnemyMetis-307");
				break;
			}
			case 4080: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000226);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000271, EnemyMetis, "EnemyMetis-308");
				break;
			}
			case 4100: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000227);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000272, EnemyMetis, "EnemyMetis-309");
				break;
			}
			case 4120: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000228);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000273, EnemyMetis, "EnemyMetis-310");
				break;
			}
			case 4140: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000229);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000274, EnemyMetis, "EnemyMetis-311");
				break;
			}
			case 4160: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000230);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000275, EnemyMetis, "EnemyMetis-312");
				break;
			}
			case 4180: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000231);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000276, EnemyMetis, "EnemyMetis-313");
				break;
			}
			case 4200: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000232);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000277, EnemyMetis, "EnemyMetis-314");
				break;
			}
			case 4220: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000233);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000278, EnemyMetis, "EnemyMetis-315");
				break;
			}
			case 4240: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000234);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000279, EnemyMetis, "EnemyMetis-316");
				break;
			}
			case 4260: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000235);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000280, EnemyMetis, "EnemyMetis-317");
				break;
			}
			case 4280: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000236);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000281, EnemyMetis, "EnemyMetis-318");
				break;
			}
			case 4300: {
				orderActorToFactory(10000007, EnemyHermione, "EnemyHermione-319");
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000237);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000282, EnemyMetis, "EnemyMetis-320");
				break;
			}
			case 4320: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000238);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000283, EnemyMetis, "EnemyMetis-321");
				break;
			}
			case 4340: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000239);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000284, EnemyMetis, "EnemyMetis-322");
				break;
			}
			case 4360: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000240);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000285, EnemyMetis, "EnemyMetis-323");
				break;
			}
			case 4380: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000241);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000286, EnemyMetis, "EnemyMetis-324");
				break;
			}
			case 4400: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000242);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000287, EnemyMetis, "EnemyMetis-325");
				break;
			}
			case 4420: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000243);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000288, EnemyMetis, "EnemyMetis-326");
				break;
			}
			case 4440: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000244);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000289, EnemyMetis, "EnemyMetis-327");
				break;
			}
			case 4460: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000245);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000290, EnemyMetis, "EnemyMetis-328");
				break;
			}
			case 4480: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000246);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000291, EnemyMetis, "EnemyMetis-329");
				break;
			}
			case 4500: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000247);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000292, EnemyMetis, "EnemyMetis-330");
				break;
			}
			case 4520: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000248);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000293, EnemyMetis, "EnemyMetis-331");
				break;
			}
			case 4540: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000249);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000294, EnemyMetis, "EnemyMetis-332");
				break;
			}
			case 4560: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000250);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000295, EnemyMetis, "EnemyMetis-333");
				break;
			}
			case 4580: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000251);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000296, EnemyMetis, "EnemyMetis-334");
				break;
			}
			case 4600: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000252);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000297, EnemyMetis, "EnemyMetis-335");
				break;
			}
			case 4620: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000253);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000298, EnemyMetis, "EnemyMetis-336");
				break;
			}
			case 4640: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000254);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000299, EnemyMetis, "EnemyMetis-337");
				break;
			}
			case 4660: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000255);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000300, EnemyMetis, "EnemyMetis-338");
				break;
			}
			case 4680: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000256);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000301, EnemyMetis, "EnemyMetis-339");
				break;
			}
			case 4700: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000257);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000302, EnemyMetis, "EnemyMetis-340");
				break;
			}
			case 4720: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000258);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000303, EnemyMetis, "EnemyMetis-341");
				break;
			}
			case 4740: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000259);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000304, EnemyMetis, "EnemyMetis-342");
				break;
			}
			case 4760: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000260);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000305, EnemyMetis, "EnemyMetis-343");
				break;
			}
			case 4780: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000261);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000306, EnemyMetis, "EnemyMetis-344");
				break;
			}
			case 4800: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000262);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000307, EnemyMetis, "EnemyMetis-345");
				break;
			}
			case 4820: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000263);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000308, EnemyMetis, "EnemyMetis-346");
				break;
			}
			case 4840: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000264);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000309, EnemyMetis, "EnemyMetis-347");
				break;
			}
			case 4860: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000265);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000310, EnemyMetis, "EnemyMetis-348");
				break;
			}
			case 4880: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000266);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000311, EnemyMetis, "EnemyMetis-349");
				break;
			}
			case 4900: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000267);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000312, EnemyMetis, "EnemyMetis-350");
				break;
			}
			case 4920: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000268);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000313, EnemyMetis, "EnemyMetis-351");
				break;
			}
			case 4940: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000269);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000314, EnemyMetis, "EnemyMetis-352");
				break;
			}
			case 4960: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000270);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000315, EnemyMetis, "EnemyMetis-353");
				break;
			}
			case 4980: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000271);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000316, EnemyMetis, "EnemyMetis-354");
				break;
			}
			case 5000: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000272);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000317, EnemyMetis, "EnemyMetis-355");
				break;
			}
			case 5020: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000273);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000318, EnemyMetis, "EnemyMetis-356");
				break;
			}
			case 5040: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000274);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000319, EnemyMetis, "EnemyMetis-357");
				break;
			}
			case 5060: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000275);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000320, EnemyMetis, "EnemyMetis-358");
				break;
			}
			case 5080: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000276);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000321, EnemyMetis, "EnemyMetis-359");
				break;
			}
			case 5100: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000277);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000322, EnemyMetis, "EnemyMetis-360");
				break;
			}
			case 5120: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000278);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000323, EnemyMetis, "EnemyMetis-361");
				break;
			}
			case 5140: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000279);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000324, EnemyMetis, "EnemyMetis-362");
				break;
			}
			case 5160: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000280);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000325, EnemyMetis, "EnemyMetis-363");
				break;
			}
			case 5180: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000281);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000326, EnemyMetis, "EnemyMetis-364");
				break;
			}
			case 5200: {
				EnemyHermione* p = (EnemyHermione*)obtainActorFromFactory(10000007);
				getSceneDirector()->addSubGroup(p);
				p->_X = RND(000000,1000000);
				p->_Y = RND(-600000,600000);
				p->_Z = RND(-600000,600000);
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000282);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000327, EnemyMetis, "EnemyMetis-365");
				break;
			}
			case 5220: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000283);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000328, EnemyMetis, "EnemyMetis-366");
				break;
			}
			case 5240: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000284);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000329, EnemyMetis, "EnemyMetis-367");
				break;
			}
			case 5260: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000285);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000330, EnemyMetis, "EnemyMetis-368");
				break;
			}
			case 5280: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000286);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000331, EnemyMetis, "EnemyMetis-369");
				break;
			}
			case 5300: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000287);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000332, EnemyMetis, "EnemyMetis-370");
				break;
			}
			case 5320: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000288);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000333, EnemyMetis, "EnemyMetis-371");
				break;
			}
			case 5340: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000289);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000334, EnemyMetis, "EnemyMetis-372");
				break;
			}
			case 5360: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000290);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000335, EnemyMetis, "EnemyMetis-373");
				break;
			}
			case 5380: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000291);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000336, EnemyMetis, "EnemyMetis-374");
				break;
			}
			case 5400: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000292);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000337, EnemyMetis, "EnemyMetis-375");
				break;
			}
			case 5420: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000293);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000338, EnemyMetis, "EnemyMetis-376");
				break;
			}
			case 5440: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000294);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000339, EnemyMetis, "EnemyMetis-377");
				break;
			}
			case 5460: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000295);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000340, EnemyMetis, "EnemyMetis-378");
				break;
			}
			case 5480: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000296);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000341, EnemyMetis, "EnemyMetis-379");
				break;
			}
			case 5500: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000297);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000342, EnemyMetis, "EnemyMetis-380");
				break;
			}
			case 5520: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000298);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000343, EnemyMetis, "EnemyMetis-381");
				break;
			}
			case 5540: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000299);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000344, EnemyMetis, "EnemyMetis-382");
				break;
			}
			case 5560: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000300);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000345, EnemyMetis, "EnemyMetis-383");
				break;
			}
			case 5580: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000301);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000346, EnemyMetis, "EnemyMetis-384");
				break;
			}
			case 5600: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000302);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000347, EnemyMetis, "EnemyMetis-385");
				break;
			}
			case 5620: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000303);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000348, EnemyMetis, "EnemyMetis-386");
				break;
			}
			case 5640: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000304);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000349, EnemyMetis, "EnemyMetis-387");
				break;
			}
			case 5660: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000305);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000350, EnemyMetis, "EnemyMetis-388");
				break;
			}
			case 5680: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000306);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000351, EnemyMetis, "EnemyMetis-389");
				break;
			}
			case 5700: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000307);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000352, EnemyMetis, "EnemyMetis-390");
				break;
			}
			case 5720: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000308);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000353, EnemyMetis, "EnemyMetis-391");
				break;
			}
			case 5740: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000309);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000354, EnemyMetis, "EnemyMetis-392");
				break;
			}
			case 5760: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000310);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000355, EnemyMetis, "EnemyMetis-393");
				break;
			}
			case 5780: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000311);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000356, EnemyMetis, "EnemyMetis-394");
				break;
			}
			case 5800: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000312);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000357, EnemyMetis, "EnemyMetis-395");
				break;
			}
			case 5820: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000313);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000358, EnemyMetis, "EnemyMetis-396");
				break;
			}
			case 5840: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000314);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000359, EnemyMetis, "EnemyMetis-397");
				break;
			}
			case 5860: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000315);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000360, EnemyMetis, "EnemyMetis-398");
				break;
			}
			case 5880: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000316);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000361, EnemyMetis, "EnemyMetis-399");
				break;
			}
			case 5900: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000317);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000362, EnemyMetis, "EnemyMetis-400");
				break;
			}
			case 5920: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000318);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000363, EnemyMetis, "EnemyMetis-401");
				break;
			}
			case 5940: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000319);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000364, EnemyMetis, "EnemyMetis-402");
				break;
			}
			case 5960: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000320);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000365, EnemyMetis, "EnemyMetis-403");
				break;
			}
			case 5980: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000321);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000366, EnemyMetis, "EnemyMetis-404");
				break;
			}
			case 6000: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000322);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000367, EnemyMetis, "EnemyMetis-405");
				break;
			}
			case 6020: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000323);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000368, EnemyMetis, "EnemyMetis-406");
				break;
			}
			case 6040: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000324);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000369, EnemyMetis, "EnemyMetis-407");
				break;
			}
			case 6060: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000325);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000370, EnemyMetis, "EnemyMetis-408");
				break;
			}
			case 6080: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000326);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000371, EnemyMetis, "EnemyMetis-409");
				break;
			}
			case 6100: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000327);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000372, EnemyMetis, "EnemyMetis-410");
				break;
			}
			case 6120: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000328);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000373, EnemyMetis, "EnemyMetis-411");
				break;
			}
			case 6140: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000329);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000374, EnemyMetis, "EnemyMetis-412");
				break;
			}
			case 6160: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000330);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000375, EnemyMetis, "EnemyMetis-413");
				break;
			}
			case 6180: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000331);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000376, EnemyMetis, "EnemyMetis-414");
				break;
			}
			case 6200: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000332);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000377, EnemyMetis, "EnemyMetis-415");
				break;
			}
			case 6220: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000333);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000378, EnemyMetis, "EnemyMetis-416");
				break;
			}
			case 6240: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000334);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000379, EnemyMetis, "EnemyMetis-417");
				break;
			}
			case 6260: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000335);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000380, EnemyMetis, "EnemyMetis-418");
				break;
			}
			case 6280: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000336);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000381, EnemyMetis, "EnemyMetis-419");
				break;
			}
			case 6300: {
				orderActorToFactory(10000008, EnemyHermione, "EnemyHermione-420");
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000337);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000382, EnemyMetis, "EnemyMetis-421");
				break;
			}
			case 6320: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000338);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000383, EnemyMetis, "EnemyMetis-422");
				break;
			}
			case 6340: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000339);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000384, EnemyMetis, "EnemyMetis-423");
				break;
			}
			case 6360: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000340);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000385, EnemyMetis, "EnemyMetis-424");
				break;
			}
			case 6380: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000341);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000386, EnemyMetis, "EnemyMetis-425");
				break;
			}
			case 6400: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000342);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000387, EnemyMetis, "EnemyMetis-426");
				break;
			}
			case 6420: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000343);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000388, EnemyMetis, "EnemyMetis-427");
				break;
			}
			case 6440: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000344);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000389, EnemyMetis, "EnemyMetis-428");
				break;
			}
			case 6460: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000345);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000390, EnemyMetis, "EnemyMetis-429");
				break;
			}
			case 6480: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000346);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000391, EnemyMetis, "EnemyMetis-430");
				break;
			}
			case 6500: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000347);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000392, EnemyMetis, "EnemyMetis-431");
				break;
			}
			case 6520: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000348);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000393, EnemyMetis, "EnemyMetis-432");
				break;
			}
			case 6540: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000349);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000394, EnemyMetis, "EnemyMetis-433");
				break;
			}
			case 6560: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000350);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000395, EnemyMetis, "EnemyMetis-434");
				break;
			}
			case 6580: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000351);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000396, EnemyMetis, "EnemyMetis-435");
				break;
			}
			case 6600: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000352);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000397, EnemyMetis, "EnemyMetis-436");
				break;
			}
			case 6620: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000353);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000398, EnemyMetis, "EnemyMetis-437");
				break;
			}
			case 6640: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000354);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000399, EnemyMetis, "EnemyMetis-438");
				break;
			}
			case 6660: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000355);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000400, EnemyMetis, "EnemyMetis-439");
				break;
			}
			case 6680: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000356);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000401, EnemyMetis, "EnemyMetis-440");
				break;
			}
			case 6700: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000357);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000402, EnemyMetis, "EnemyMetis-441");
				break;
			}
			case 6720: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000358);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000403, EnemyMetis, "EnemyMetis-442");
				break;
			}
			case 6740: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000359);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000404, EnemyMetis, "EnemyMetis-443");
				break;
			}
			case 6760: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000360);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000405, EnemyMetis, "EnemyMetis-444");
				break;
			}
			case 6780: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000361);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000406, EnemyMetis, "EnemyMetis-445");
				break;
			}
			case 6800: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000362);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000407, EnemyMetis, "EnemyMetis-446");
				break;
			}
			case 6820: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000363);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000408, EnemyMetis, "EnemyMetis-447");
				break;
			}
			case 6840: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000364);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000409, EnemyMetis, "EnemyMetis-448");
				break;
			}
			case 6860: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000365);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000410, EnemyMetis, "EnemyMetis-449");
				break;
			}
			case 6880: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000366);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000411, EnemyMetis, "EnemyMetis-450");
				break;
			}
			case 6900: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000367);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000412, EnemyMetis, "EnemyMetis-451");
				break;
			}
			case 6920: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000368);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000413, EnemyMetis, "EnemyMetis-452");
				break;
			}
			case 6940: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000369);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000414, EnemyMetis, "EnemyMetis-453");
				break;
			}
			case 6960: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000370);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000415, EnemyMetis, "EnemyMetis-454");
				break;
			}
			case 6980: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000371);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000416, EnemyMetis, "EnemyMetis-455");
				break;
			}
			case 7000: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000372);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000417, EnemyMetis, "EnemyMetis-456");
				break;
			}
			case 7020: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000373);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000418, EnemyMetis, "EnemyMetis-457");
				break;
			}
			case 7040: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000374);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000419, EnemyMetis, "EnemyMetis-458");
				break;
			}
			case 7060: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000375);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000420, EnemyMetis, "EnemyMetis-459");
				break;
			}
			case 7080: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000376);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000421, EnemyMetis, "EnemyMetis-460");
				break;
			}
			case 7100: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000377);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000422, EnemyMetis, "EnemyMetis-461");
				break;
			}
			case 7120: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000378);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000423, EnemyMetis, "EnemyMetis-462");
				break;
			}
			case 7140: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000379);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000424, EnemyMetis, "EnemyMetis-463");
				break;
			}
			case 7160: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000380);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000425, EnemyMetis, "EnemyMetis-464");
				break;
			}
			case 7180: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000381);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000426, EnemyMetis, "EnemyMetis-465");
				break;
			}
			case 7200: {
				EnemyHermione* p = (EnemyHermione*)obtainActorFromFactory(10000008);
				getSceneDirector()->addSubGroup(p);
				p->_X = RND(000000,1000000);
				p->_Y = RND(-600000,600000);
				p->_Z = RND(-600000,600000);
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000382);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000427, EnemyMetis, "EnemyMetis-466");
				break;
			}
			case 7220: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000383);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000428, EnemyMetis, "EnemyMetis-467");
				break;
			}
			case 7240: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000384);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000429, EnemyMetis, "EnemyMetis-468");
				break;
			}
			case 7260: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000385);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000430, EnemyMetis, "EnemyMetis-469");
				break;
			}
			case 7280: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000386);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000431, EnemyMetis, "EnemyMetis-470");
				break;
			}
			case 7300: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000387);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000432, EnemyMetis, "EnemyMetis-471");
				break;
			}
			case 7320: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000388);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000433, EnemyMetis, "EnemyMetis-472");
				break;
			}
			case 7340: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000389);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000434, EnemyMetis, "EnemyMetis-473");
				break;
			}
			case 7360: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000390);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000435, EnemyMetis, "EnemyMetis-474");
				break;
			}
			case 7380: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000391);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000436, EnemyMetis, "EnemyMetis-475");
				break;
			}
			case 7400: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000392);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000437, EnemyMetis, "EnemyMetis-476");
				break;
			}
			case 7420: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000393);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000438, EnemyMetis, "EnemyMetis-477");
				break;
			}
			case 7440: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000394);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000439, EnemyMetis, "EnemyMetis-478");
				break;
			}
			case 7460: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000395);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000440, EnemyMetis, "EnemyMetis-479");
				break;
			}
			case 7480: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000396);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000441, EnemyMetis, "EnemyMetis-480");
				break;
			}
			case 7500: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000397);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000442, EnemyMetis, "EnemyMetis-481");
				break;
			}
			case 7520: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000398);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000443, EnemyMetis, "EnemyMetis-482");
				break;
			}
			case 7540: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000399);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000444, EnemyMetis, "EnemyMetis-483");
				break;
			}
			case 7560: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000400);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000445, EnemyMetis, "EnemyMetis-484");
				break;
			}
			case 7580: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000401);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000446, EnemyMetis, "EnemyMetis-485");
				break;
			}
			case 7600: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000402);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000447, EnemyMetis, "EnemyMetis-486");
				break;
			}
			case 7620: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000403);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000448, EnemyMetis, "EnemyMetis-487");
				break;
			}
			case 7640: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000404);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000449, EnemyMetis, "EnemyMetis-488");
				break;
			}
			case 7660: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000405);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000450, EnemyMetis, "EnemyMetis-489");
				break;
			}
			case 7680: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000406);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000451, EnemyMetis, "EnemyMetis-490");
				break;
			}
			case 7700: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000407);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000452, EnemyMetis, "EnemyMetis-491");
				break;
			}
			case 7720: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000408);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000453, EnemyMetis, "EnemyMetis-492");
				break;
			}
			case 7740: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000409);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000454, EnemyMetis, "EnemyMetis-493");
				break;
			}
			case 7760: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000410);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000455, EnemyMetis, "EnemyMetis-494");
				break;
			}
			case 7780: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000411);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000456, EnemyMetis, "EnemyMetis-495");
				break;
			}
			case 7800: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000412);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000457, EnemyMetis, "EnemyMetis-496");
				break;
			}
			case 7820: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000413);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000458, EnemyMetis, "EnemyMetis-497");
				break;
			}
			case 7840: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000414);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000459, EnemyMetis, "EnemyMetis-498");
				break;
			}
			case 7860: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000415);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000460, EnemyMetis, "EnemyMetis-499");
				break;
			}
			case 7880: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000416);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000461, EnemyMetis, "EnemyMetis-500");
				break;
			}
			case 7900: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000417);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000462, EnemyMetis, "EnemyMetis-501");
				break;
			}
			case 7920: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000418);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000463, EnemyMetis, "EnemyMetis-502");
				break;
			}
			case 7940: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000419);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000464, EnemyMetis, "EnemyMetis-503");
				break;
			}
			case 7960: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000420);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000465, EnemyMetis, "EnemyMetis-504");
				break;
			}
			case 7980: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000421);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000466, EnemyMetis, "EnemyMetis-505");
				break;
			}
			case 8000: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000422);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000467, EnemyMetis, "EnemyMetis-506");
				break;
			}
			case 8020: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000423);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000468, EnemyMetis, "EnemyMetis-507");
				break;
			}
			case 8040: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000424);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000469, EnemyMetis, "EnemyMetis-508");
				break;
			}
			case 8060: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000425);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000470, EnemyMetis, "EnemyMetis-509");
				break;
			}
			case 8080: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000426);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000471, EnemyMetis, "EnemyMetis-510");
				break;
			}
			case 8100: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000427);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000472, EnemyMetis, "EnemyMetis-511");
				break;
			}
			case 8120: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000428);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000473, EnemyMetis, "EnemyMetis-512");
				break;
			}
			case 8140: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000429);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000474, EnemyMetis, "EnemyMetis-513");
				break;
			}
			case 8160: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000430);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000475, EnemyMetis, "EnemyMetis-514");
				break;
			}
			case 8180: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000431);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000476, EnemyMetis, "EnemyMetis-515");
				break;
			}
			case 8200: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000432);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000477, EnemyMetis, "EnemyMetis-516");
				break;
			}
			case 8220: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000433);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000478, EnemyMetis, "EnemyMetis-517");
				break;
			}
			case 8240: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000434);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000479, EnemyMetis, "EnemyMetis-518");
				break;
			}
			case 8260: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000435);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000480, EnemyMetis, "EnemyMetis-519");
				break;
			}
			case 8280: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000436);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000481, EnemyMetis, "EnemyMetis-520");
				break;
			}
			case 8300: {
				orderActorToFactory(10000009, EnemyHermione, "EnemyHermione-521");
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000437);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000482, EnemyMetis, "EnemyMetis-522");
				break;
			}
			case 8320: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000438);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000483, EnemyMetis, "EnemyMetis-523");
				break;
			}
			case 8340: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000439);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000484, EnemyMetis, "EnemyMetis-524");
				break;
			}
			case 8360: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000440);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000485, EnemyMetis, "EnemyMetis-525");
				break;
			}
			case 8380: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000441);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000486, EnemyMetis, "EnemyMetis-526");
				break;
			}
			case 8400: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000442);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000487, EnemyMetis, "EnemyMetis-527");
				break;
			}
			case 8420: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000443);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000488, EnemyMetis, "EnemyMetis-528");
				break;
			}
			case 8440: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000444);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000489, EnemyMetis, "EnemyMetis-529");
				break;
			}
			case 8460: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000445);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000490, EnemyMetis, "EnemyMetis-530");
				break;
			}
			case 8480: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000446);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000491, EnemyMetis, "EnemyMetis-531");
				break;
			}
			case 8500: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000447);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000492, EnemyMetis, "EnemyMetis-532");
				break;
			}
			case 8520: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000448);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000493, EnemyMetis, "EnemyMetis-533");
				break;
			}
			case 8540: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000449);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000494, EnemyMetis, "EnemyMetis-534");
				break;
			}
			case 8560: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000450);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000495, EnemyMetis, "EnemyMetis-535");
				break;
			}
			case 8580: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000451);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000496, EnemyMetis, "EnemyMetis-536");
				break;
			}
			case 8600: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000452);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000497, EnemyMetis, "EnemyMetis-537");
				break;
			}
			case 8620: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000453);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000498, EnemyMetis, "EnemyMetis-538");
				break;
			}
			case 8640: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000454);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000499, EnemyMetis, "EnemyMetis-539");
				break;
			}
			case 8660: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000455);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000500, EnemyMetis, "EnemyMetis-540");
				break;
			}
			case 8680: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000456);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000501, EnemyMetis, "EnemyMetis-541");
				break;
			}
			case 8700: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000457);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000502, EnemyMetis, "EnemyMetis-542");
				break;
			}
			case 8720: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000458);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000503, EnemyMetis, "EnemyMetis-543");
				break;
			}
			case 8740: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000459);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000504, EnemyMetis, "EnemyMetis-544");
				break;
			}
			case 8760: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000460);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000505, EnemyMetis, "EnemyMetis-545");
				break;
			}
			case 8780: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000461);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000506, EnemyMetis, "EnemyMetis-546");
				break;
			}
			case 8800: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000462);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000507, EnemyMetis, "EnemyMetis-547");
				break;
			}
			case 8820: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000463);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000508, EnemyMetis, "EnemyMetis-548");
				break;
			}
			case 8840: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000464);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000509, EnemyMetis, "EnemyMetis-549");
				break;
			}
			case 8860: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000465);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000510, EnemyMetis, "EnemyMetis-550");
				break;
			}
			case 8880: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000466);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000511, EnemyMetis, "EnemyMetis-551");
				break;
			}
			case 8900: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000467);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000512, EnemyMetis, "EnemyMetis-552");
				break;
			}
			case 8920: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000468);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000513, EnemyMetis, "EnemyMetis-553");
				break;
			}
			case 8940: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000469);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000514, EnemyMetis, "EnemyMetis-554");
				break;
			}
			case 8960: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000470);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000515, EnemyMetis, "EnemyMetis-555");
				break;
			}
			case 8980: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000471);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000516, EnemyMetis, "EnemyMetis-556");
				break;
			}
			case 9000: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000472);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000517, EnemyMetis, "EnemyMetis-557");
				break;
			}
			case 9020: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000473);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000518, EnemyMetis, "EnemyMetis-558");
				break;
			}
			case 9040: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000474);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000519, EnemyMetis, "EnemyMetis-559");
				break;
			}
			case 9060: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000475);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000520, EnemyMetis, "EnemyMetis-560");
				break;
			}
			case 9080: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000476);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000521, EnemyMetis, "EnemyMetis-561");
				break;
			}
			case 9100: {
				orderSceneToFactory(10000001, Stage01_02, "Stage01_02-562");
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000477);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000522, EnemyMetis, "EnemyMetis-563");
				break;
			}
			case 9120: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000478);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000523, EnemyMetis, "EnemyMetis-564");
				break;
			}
			case 9140: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000479);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000524, EnemyMetis, "EnemyMetis-565");
				break;
			}
			case 9160: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000480);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000525, EnemyMetis, "EnemyMetis-566");
				break;
			}
			case 9180: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000481);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000526, EnemyMetis, "EnemyMetis-567");
				break;
			}
			case 9200: {
				EnemyHermione* p = (EnemyHermione*)obtainActorFromFactory(10000009);
				getSceneDirector()->addSubGroup(p);
				p->_X = RND(000000,1000000);
				p->_Y = RND(-600000,600000);
				p->_Z = RND(-600000,600000);
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000482);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000527, EnemyMetis, "EnemyMetis-568");
				break;
			}
			case 9220: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000483);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000528, EnemyMetis, "EnemyMetis-569");
				break;
			}
			case 9240: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000484);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000529, EnemyMetis, "EnemyMetis-570");
				break;
			}
			case 9260: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000485);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000530, EnemyMetis, "EnemyMetis-571");
				break;
			}
			case 9280: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000486);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000531, EnemyMetis, "EnemyMetis-572");
				break;
			}
			case 9300: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000487);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000532, EnemyMetis, "EnemyMetis-573");
				break;
			}
			case 9320: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000488);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000533, EnemyMetis, "EnemyMetis-574");
				break;
			}
			case 9340: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000489);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000534, EnemyMetis, "EnemyMetis-575");
				break;
			}
			case 9360: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000490);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000535, EnemyMetis, "EnemyMetis-576");
				break;
			}
			case 9380: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000491);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000536, EnemyMetis, "EnemyMetis-577");
				break;
			}
			case 9400: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000492);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000537, EnemyMetis, "EnemyMetis-578");
				break;
			}
			case 9420: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000493);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000538, EnemyMetis, "EnemyMetis-579");
				break;
			}
			case 9440: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000494);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000539, EnemyMetis, "EnemyMetis-580");
				break;
			}
			case 9460: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000495);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000540, EnemyMetis, "EnemyMetis-581");
				break;
			}
			case 9480: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000496);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000541, EnemyMetis, "EnemyMetis-582");
				break;
			}
			case 9500: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000497);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000542, EnemyMetis, "EnemyMetis-583");
				break;
			}
			case 9520: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000498);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000543, EnemyMetis, "EnemyMetis-584");
				break;
			}
			case 9540: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000499);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000544, EnemyMetis, "EnemyMetis-585");
				break;
			}
			case 9560: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000500);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000545, EnemyMetis, "EnemyMetis-586");
				break;
			}
			case 9580: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000501);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000546, EnemyMetis, "EnemyMetis-587");
				break;
			}
			case 9600: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000502);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000547, EnemyMetis, "EnemyMetis-588");
				break;
			}
			case 9620: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000503);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000548, EnemyMetis, "EnemyMetis-589");
				break;
			}
			case 9640: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000504);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000549, EnemyMetis, "EnemyMetis-590");
				break;
			}
			case 9660: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000505);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000550, EnemyMetis, "EnemyMetis-591");
				break;
			}
			case 9680: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000506);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000551, EnemyMetis, "EnemyMetis-592");
				break;
			}
			case 9700: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000507);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000552, EnemyMetis, "EnemyMetis-593");
				break;
			}
			case 9720: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000508);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000553, EnemyMetis, "EnemyMetis-594");
				break;
			}
			case 9740: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000509);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000554, EnemyMetis, "EnemyMetis-595");
				break;
			}
			case 9760: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000510);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000555, EnemyMetis, "EnemyMetis-596");
				break;
			}
			case 9780: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000511);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000556, EnemyMetis, "EnemyMetis-597");
				break;
			}
			case 9800: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000512);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000557, EnemyMetis, "EnemyMetis-598");
				break;
			}
			case 9820: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000513);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000558, EnemyMetis, "EnemyMetis-599");
				break;
			}
			case 9840: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000514);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000559, EnemyMetis, "EnemyMetis-600");
				break;
			}
			case 9860: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000515);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000560, EnemyMetis, "EnemyMetis-601");
				break;
			}
			case 9880: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000516);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000561, EnemyMetis, "EnemyMetis-602");
				break;
			}
			case 9900: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000517);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000562, EnemyMetis, "EnemyMetis-603");
				break;
			}
			case 9920: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000518);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000563, EnemyMetis, "EnemyMetis-604");
				break;
			}
			case 9940: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000519);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000564, EnemyMetis, "EnemyMetis-605");
				break;
			}
			case 9960: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000520);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000565, EnemyMetis, "EnemyMetis-606");
				break;
			}
			case 9980: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000521);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000566, EnemyMetis, "EnemyMetis-607");
				break;
			}
			case 10000: {
				Stage01_02* pScene = (Stage01_02*)obtainSceneFromFactory(10000001);
				addSubLast(pScene);
				_pBgmPerformer->fadeout_stop(0);
				_pBgmPerformer->play_fadein(1);
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000522);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000567, EnemyMetis, "EnemyMetis-608");
				break;
			}
			case 10020: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000523);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000568, EnemyMetis, "EnemyMetis-609");
				break;
			}
			case 10040: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000524);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000569, EnemyMetis, "EnemyMetis-610");
				break;
			}
			case 10060: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000525);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000570, EnemyMetis, "EnemyMetis-611");
				break;
			}
			case 10080: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000526);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000571, EnemyMetis, "EnemyMetis-612");
				break;
			}
			case 10100: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000527);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000572, EnemyMetis, "EnemyMetis-613");
				break;
			}
			case 10120: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000528);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000573, EnemyMetis, "EnemyMetis-614");
				break;
			}
			case 10140: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000529);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000574, EnemyMetis, "EnemyMetis-615");
				break;
			}
			case 10160: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000530);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000575, EnemyMetis, "EnemyMetis-616");
				break;
			}
			case 10180: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000531);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000576, EnemyMetis, "EnemyMetis-617");
				break;
			}
			case 10200: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000532);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000577, EnemyMetis, "EnemyMetis-618");
				break;
			}
			case 10220: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000533);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000578, EnemyMetis, "EnemyMetis-619");
				break;
			}
			case 10240: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000534);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000579, EnemyMetis, "EnemyMetis-620");
				break;
			}
			case 10260: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000535);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000580, EnemyMetis, "EnemyMetis-621");
				break;
			}
			case 10280: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000536);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000581, EnemyMetis, "EnemyMetis-622");
				break;
			}
			case 10300: {
				orderActorToFactory(10000010, EnemyHermione, "EnemyHermione-623");
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000537);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000582, EnemyMetis, "EnemyMetis-624");
				break;
			}
			case 10320: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000538);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000583, EnemyMetis, "EnemyMetis-625");
				break;
			}
			case 10340: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000539);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000584, EnemyMetis, "EnemyMetis-626");
				break;
			}
			case 10360: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000540);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000585, EnemyMetis, "EnemyMetis-627");
				break;
			}
			case 10380: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000541);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000586, EnemyMetis, "EnemyMetis-628");
				break;
			}
			case 10400: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000542);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000587, EnemyMetis, "EnemyMetis-629");
				break;
			}
			case 10420: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000543);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000588, EnemyMetis, "EnemyMetis-630");
				break;
			}
			case 10440: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000544);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000589, EnemyMetis, "EnemyMetis-631");
				break;
			}
			case 10460: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000545);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000590, EnemyMetis, "EnemyMetis-632");
				break;
			}
			case 10480: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000546);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000591, EnemyMetis, "EnemyMetis-633");
				break;
			}
			case 10500: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000547);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000592, EnemyMetis, "EnemyMetis-634");
				break;
			}
			case 10520: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000548);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000593, EnemyMetis, "EnemyMetis-635");
				break;
			}
			case 10540: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000549);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000594, EnemyMetis, "EnemyMetis-636");
				break;
			}
			case 10560: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000550);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000595, EnemyMetis, "EnemyMetis-637");
				break;
			}
			case 10580: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000551);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000596, EnemyMetis, "EnemyMetis-638");
				break;
			}
			case 10600: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000552);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000597, EnemyMetis, "EnemyMetis-639");
				break;
			}
			case 10620: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000553);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000598, EnemyMetis, "EnemyMetis-640");
				break;
			}
			case 10640: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000554);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000599, EnemyMetis, "EnemyMetis-641");
				break;
			}
			case 10660: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000555);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000600, EnemyMetis, "EnemyMetis-642");
				break;
			}
			case 10680: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000556);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000601, EnemyMetis, "EnemyMetis-643");
				break;
			}
			case 10700: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000557);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000602, EnemyMetis, "EnemyMetis-644");
				break;
			}
			case 10720: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000558);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000603, EnemyMetis, "EnemyMetis-645");
				break;
			}
			case 10740: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000559);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000604, EnemyMetis, "EnemyMetis-646");
				break;
			}
			case 10760: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000560);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000605, EnemyMetis, "EnemyMetis-647");
				break;
			}
			case 10780: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000561);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000606, EnemyMetis, "EnemyMetis-648");
				break;
			}
			case 10800: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000562);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000607, EnemyMetis, "EnemyMetis-649");
				break;
			}
			case 10820: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000563);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000608, EnemyMetis, "EnemyMetis-650");
				break;
			}
			case 10840: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000564);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000609, EnemyMetis, "EnemyMetis-651");
				break;
			}
			case 10860: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000565);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000610, EnemyMetis, "EnemyMetis-652");
				break;
			}
			case 10880: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000566);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000611, EnemyMetis, "EnemyMetis-653");
				break;
			}
			case 10900: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000567);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000612, EnemyMetis, "EnemyMetis-654");
				break;
			}
			case 10920: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000568);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000613, EnemyMetis, "EnemyMetis-655");
				break;
			}
			case 10940: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000569);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000614, EnemyMetis, "EnemyMetis-656");
				break;
			}
			case 10960: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000570);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000615, EnemyMetis, "EnemyMetis-657");
				break;
			}
			case 10980: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000571);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000616, EnemyMetis, "EnemyMetis-658");
				break;
			}
			case 11000: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000572);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000617, EnemyMetis, "EnemyMetis-659");
				break;
			}
			case 11020: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000573);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000618, EnemyMetis, "EnemyMetis-660");
				break;
			}
			case 11040: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000574);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000619, EnemyMetis, "EnemyMetis-661");
				break;
			}
			case 11060: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000575);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000620, EnemyMetis, "EnemyMetis-662");
				break;
			}
			case 11080: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000576);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000621, EnemyMetis, "EnemyMetis-663");
				break;
			}
			case 11100: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000577);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000622, EnemyMetis, "EnemyMetis-664");
				break;
			}
			case 11120: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000578);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000623, EnemyMetis, "EnemyMetis-665");
				break;
			}
			case 11140: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000579);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000624, EnemyMetis, "EnemyMetis-666");
				break;
			}
			case 11160: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000580);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000625, EnemyMetis, "EnemyMetis-667");
				break;
			}
			case 11180: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000581);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000626, EnemyMetis, "EnemyMetis-668");
				break;
			}
			case 11200: {
				EnemyHermione* p = (EnemyHermione*)obtainActorFromFactory(10000010);
				getSceneDirector()->addSubGroup(p);
				p->_X = RND(000000,1000000);
				p->_Y = RND(-600000,600000);
				p->_Z = RND(-600000,600000);
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000582);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000627, EnemyMetis, "EnemyMetis-669");
				break;
			}
			case 11220: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000583);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000628, EnemyMetis, "EnemyMetis-670");
				break;
			}
			case 11240: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000584);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000629, EnemyMetis, "EnemyMetis-671");
				break;
			}
			case 11260: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000585);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000630, EnemyMetis, "EnemyMetis-672");
				break;
			}
			case 11280: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000586);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000631, EnemyMetis, "EnemyMetis-673");
				break;
			}
			case 11300: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000587);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000632, EnemyMetis, "EnemyMetis-674");
				break;
			}
			case 11320: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000588);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000633, EnemyMetis, "EnemyMetis-675");
				break;
			}
			case 11340: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000589);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000634, EnemyMetis, "EnemyMetis-676");
				break;
			}
			case 11360: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000590);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000635, EnemyMetis, "EnemyMetis-677");
				break;
			}
			case 11380: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000591);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000636, EnemyMetis, "EnemyMetis-678");
				break;
			}
			case 11400: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000592);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000637, EnemyMetis, "EnemyMetis-679");
				break;
			}
			case 11420: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000593);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000638, EnemyMetis, "EnemyMetis-680");
				break;
			}
			case 11440: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000594);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000639, EnemyMetis, "EnemyMetis-681");
				break;
			}
			case 11460: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000595);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000640, EnemyMetis, "EnemyMetis-682");
				break;
			}
			case 11480: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000596);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000641, EnemyMetis, "EnemyMetis-683");
				break;
			}
			case 11500: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000597);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000642, EnemyMetis, "EnemyMetis-684");
				break;
			}
			case 11520: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000598);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000643, EnemyMetis, "EnemyMetis-685");
				break;
			}
			case 11540: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000599);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000644, EnemyMetis, "EnemyMetis-686");
				break;
			}
			case 11560: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000600);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000645, EnemyMetis, "EnemyMetis-687");
				break;
			}
			case 11580: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000601);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000646, EnemyMetis, "EnemyMetis-688");
				break;
			}
			case 11600: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000602);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000647, EnemyMetis, "EnemyMetis-689");
				break;
			}
			case 11620: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000603);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000648, EnemyMetis, "EnemyMetis-690");
				break;
			}
			case 11640: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000604);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000649, EnemyMetis, "EnemyMetis-691");
				break;
			}
			case 11660: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000605);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000650, EnemyMetis, "EnemyMetis-692");
				break;
			}
			case 11680: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000606);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000651, EnemyMetis, "EnemyMetis-693");
				break;
			}
			case 11700: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000607);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000652, EnemyMetis, "EnemyMetis-694");
				break;
			}
			case 11720: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000608);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000653, EnemyMetis, "EnemyMetis-695");
				break;
			}
			case 11740: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000609);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000654, EnemyMetis, "EnemyMetis-696");
				break;
			}
			case 11760: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000610);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000655, EnemyMetis, "EnemyMetis-697");
				break;
			}
			case 11780: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000611);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000656, EnemyMetis, "EnemyMetis-698");
				break;
			}
			case 11800: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000612);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000657, EnemyMetis, "EnemyMetis-699");
				break;
			}
			case 11820: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000613);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000658, EnemyMetis, "EnemyMetis-700");
				break;
			}
			case 11840: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000614);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000659, EnemyMetis, "EnemyMetis-701");
				break;
			}
			case 11860: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000615);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000660, EnemyMetis, "EnemyMetis-702");
				break;
			}
			case 11880: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000616);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000661, EnemyMetis, "EnemyMetis-703");
				break;
			}
			case 11900: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000617);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000662, EnemyMetis, "EnemyMetis-704");
				break;
			}
			case 11920: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000618);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000663, EnemyMetis, "EnemyMetis-705");
				break;
			}
			case 11940: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000619);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000664, EnemyMetis, "EnemyMetis-706");
				break;
			}
			case 11960: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000620);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000665, EnemyMetis, "EnemyMetis-707");
				break;
			}
			case 11980: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000621);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000666, EnemyMetis, "EnemyMetis-708");
				break;
			}
			case 12000: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000622);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000667, EnemyMetis, "EnemyMetis-709");
				break;
			}
			case 12020: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000623);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000668, EnemyMetis, "EnemyMetis-710");
				break;
			}
			case 12040: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000624);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000669, EnemyMetis, "EnemyMetis-711");
				break;
			}
			case 12060: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000625);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000670, EnemyMetis, "EnemyMetis-712");
				break;
			}
			case 12080: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000626);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000671, EnemyMetis, "EnemyMetis-713");
				break;
			}
			case 12100: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000627);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000672, EnemyMetis, "EnemyMetis-714");
				break;
			}
			case 12120: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000628);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000673, EnemyMetis, "EnemyMetis-715");
				break;
			}
			case 12140: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000629);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000674, EnemyMetis, "EnemyMetis-716");
				break;
			}
			case 12160: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000630);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000675, EnemyMetis, "EnemyMetis-717");
				break;
			}
			case 12180: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000631);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000676, EnemyMetis, "EnemyMetis-718");
				break;
			}
			case 12200: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000632);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000677, EnemyMetis, "EnemyMetis-719");
				break;
			}
			case 12220: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000633);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000678, EnemyMetis, "EnemyMetis-720");
				break;
			}
			case 12240: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000634);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000679, EnemyMetis, "EnemyMetis-721");
				break;
			}
			case 12260: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000635);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000680, EnemyMetis, "EnemyMetis-722");
				break;
			}
			case 12280: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000636);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000681, EnemyMetis, "EnemyMetis-723");
				break;
			}
			case 12300: {
				orderActorToFactory(10000011, EnemyHermione, "EnemyHermione-724");
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000637);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000682, EnemyMetis, "EnemyMetis-725");
				break;
			}
			case 12320: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000638);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000683, EnemyMetis, "EnemyMetis-726");
				break;
			}
			case 12340: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000639);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000684, EnemyMetis, "EnemyMetis-727");
				break;
			}
			case 12360: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000640);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000685, EnemyMetis, "EnemyMetis-728");
				break;
			}
			case 12380: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000641);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000686, EnemyMetis, "EnemyMetis-729");
				break;
			}
			case 12400: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000642);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000687, EnemyMetis, "EnemyMetis-730");
				break;
			}
			case 12420: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000643);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000688, EnemyMetis, "EnemyMetis-731");
				break;
			}
			case 12440: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000644);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000689, EnemyMetis, "EnemyMetis-732");
				break;
			}
			case 12460: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000645);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000690, EnemyMetis, "EnemyMetis-733");
				break;
			}
			case 12480: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000646);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000691, EnemyMetis, "EnemyMetis-734");
				break;
			}
			case 12500: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000647);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000692, EnemyMetis, "EnemyMetis-735");
				break;
			}
			case 12520: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000648);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000693, EnemyMetis, "EnemyMetis-736");
				break;
			}
			case 12540: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000649);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000694, EnemyMetis, "EnemyMetis-737");
				break;
			}
			case 12560: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000650);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000695, EnemyMetis, "EnemyMetis-738");
				break;
			}
			case 12580: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000651);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000696, EnemyMetis, "EnemyMetis-739");
				break;
			}
			case 12600: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000652);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000697, EnemyMetis, "EnemyMetis-740");
				break;
			}
			case 12620: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000653);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000698, EnemyMetis, "EnemyMetis-741");
				break;
			}
			case 12640: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000654);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000699, EnemyMetis, "EnemyMetis-742");
				break;
			}
			case 12660: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000655);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000700, EnemyMetis, "EnemyMetis-743");
				break;
			}
			case 12680: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000656);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000701, EnemyMetis, "EnemyMetis-744");
				break;
			}
			case 12700: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000657);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000702, EnemyMetis, "EnemyMetis-745");
				break;
			}
			case 12720: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000658);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000703, EnemyMetis, "EnemyMetis-746");
				break;
			}
			case 12740: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000659);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000704, EnemyMetis, "EnemyMetis-747");
				break;
			}
			case 12760: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000660);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000705, EnemyMetis, "EnemyMetis-748");
				break;
			}
			case 12780: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000661);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000706, EnemyMetis, "EnemyMetis-749");
				break;
			}
			case 12800: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000662);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000707, EnemyMetis, "EnemyMetis-750");
				break;
			}
			case 12820: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000663);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000708, EnemyMetis, "EnemyMetis-751");
				break;
			}
			case 12840: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000664);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000709, EnemyMetis, "EnemyMetis-752");
				break;
			}
			case 12860: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000665);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000710, EnemyMetis, "EnemyMetis-753");
				break;
			}
			case 12880: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000666);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000711, EnemyMetis, "EnemyMetis-754");
				break;
			}
			case 12900: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000667);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000712, EnemyMetis, "EnemyMetis-755");
				break;
			}
			case 12920: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000668);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000713, EnemyMetis, "EnemyMetis-756");
				break;
			}
			case 12940: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000669);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000714, EnemyMetis, "EnemyMetis-757");
				break;
			}
			case 12960: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000670);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000715, EnemyMetis, "EnemyMetis-758");
				break;
			}
			case 12980: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000671);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000716, EnemyMetis, "EnemyMetis-759");
				break;
			}
			case 13000: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000672);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000717, EnemyMetis, "EnemyMetis-760");
				break;
			}
			case 13020: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000673);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000718, EnemyMetis, "EnemyMetis-761");
				break;
			}
			case 13040: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000674);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000719, EnemyMetis, "EnemyMetis-762");
				break;
			}
			case 13060: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000675);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000720, EnemyMetis, "EnemyMetis-763");
				break;
			}
			case 13080: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000676);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000721, EnemyMetis, "EnemyMetis-764");
				break;
			}
			case 13100: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000677);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000722, EnemyMetis, "EnemyMetis-765");
				break;
			}
			case 13120: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000678);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000723, EnemyMetis, "EnemyMetis-766");
				break;
			}
			case 13140: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000679);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000724, EnemyMetis, "EnemyMetis-767");
				break;
			}
			case 13160: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000680);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000725, EnemyMetis, "EnemyMetis-768");
				break;
			}
			case 13180: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000681);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000726, EnemyMetis, "EnemyMetis-769");
				break;
			}
			case 13200: {
				EnemyHermione* p = (EnemyHermione*)obtainActorFromFactory(10000011);
				getSceneDirector()->addSubGroup(p);
				p->_X = RND(000000,1000000);
				p->_Y = RND(-600000,600000);
				p->_Z = RND(-600000,600000);
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000682);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000727, EnemyMetis, "EnemyMetis-770");
				break;
			}
			case 13220: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000683);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000728, EnemyMetis, "EnemyMetis-771");
				break;
			}
			case 13240: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000684);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000729, EnemyMetis, "EnemyMetis-772");
				break;
			}
			case 13260: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000685);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000730, EnemyMetis, "EnemyMetis-773");
				break;
			}
			case 13280: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000686);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000731, EnemyMetis, "EnemyMetis-774");
				break;
			}
			case 13300: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000687);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000732, EnemyMetis, "EnemyMetis-775");
				break;
			}
			case 13320: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000688);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000733, EnemyMetis, "EnemyMetis-776");
				break;
			}
			case 13340: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000689);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000734, EnemyMetis, "EnemyMetis-777");
				break;
			}
			case 13360: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000690);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000735, EnemyMetis, "EnemyMetis-778");
				break;
			}
			case 13380: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000691);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000736, EnemyMetis, "EnemyMetis-779");
				break;
			}
			case 13400: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000692);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000737, EnemyMetis, "EnemyMetis-780");
				break;
			}
			case 13420: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000693);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000738, EnemyMetis, "EnemyMetis-781");
				break;
			}
			case 13440: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000694);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000739, EnemyMetis, "EnemyMetis-782");
				break;
			}
			case 13460: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000695);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000740, EnemyMetis, "EnemyMetis-783");
				break;
			}
			case 13480: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000696);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000741, EnemyMetis, "EnemyMetis-784");
				break;
			}
			case 13500: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000697);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000742, EnemyMetis, "EnemyMetis-785");
				break;
			}
			case 13520: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000698);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000743, EnemyMetis, "EnemyMetis-786");
				break;
			}
			case 13540: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000699);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000744, EnemyMetis, "EnemyMetis-787");
				break;
			}
			case 13560: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000700);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000745, EnemyMetis, "EnemyMetis-788");
				break;
			}
			case 13580: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000701);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000746, EnemyMetis, "EnemyMetis-789");
				break;
			}
			case 13600: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000702);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000747, EnemyMetis, "EnemyMetis-790");
				break;
			}
			case 13620: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000703);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000748, EnemyMetis, "EnemyMetis-791");
				break;
			}
			case 13640: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000704);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000749, EnemyMetis, "EnemyMetis-792");
				break;
			}
			case 13660: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000705);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000750, EnemyMetis, "EnemyMetis-793");
				break;
			}
			case 13680: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000706);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000751, EnemyMetis, "EnemyMetis-794");
				break;
			}
			case 13700: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000707);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000752, EnemyMetis, "EnemyMetis-795");
				break;
			}
			case 13720: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000708);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000753, EnemyMetis, "EnemyMetis-796");
				break;
			}
			case 13740: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000709);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000754, EnemyMetis, "EnemyMetis-797");
				break;
			}
			case 13760: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000710);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000755, EnemyMetis, "EnemyMetis-798");
				break;
			}
			case 13780: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000711);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000756, EnemyMetis, "EnemyMetis-799");
				break;
			}
			case 13800: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000712);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000757, EnemyMetis, "EnemyMetis-800");
				break;
			}
			case 13820: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000713);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000758, EnemyMetis, "EnemyMetis-801");
				break;
			}
			case 13840: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000714);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000759, EnemyMetis, "EnemyMetis-802");
				break;
			}
			case 13860: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000715);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000760, EnemyMetis, "EnemyMetis-803");
				break;
			}
			case 13880: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000716);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000761, EnemyMetis, "EnemyMetis-804");
				break;
			}
			case 13900: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000717);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000762, EnemyMetis, "EnemyMetis-805");
				break;
			}
			case 13920: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000718);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000763, EnemyMetis, "EnemyMetis-806");
				break;
			}
			case 13940: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000719);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000764, EnemyMetis, "EnemyMetis-807");
				break;
			}
			case 13960: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000720);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000765, EnemyMetis, "EnemyMetis-808");
				break;
			}
			case 13980: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000721);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000766, EnemyMetis, "EnemyMetis-809");
				break;
			}
			case 14000: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000722);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000767, EnemyMetis, "EnemyMetis-810");
				break;
			}
			case 14020: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000723);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000768, EnemyMetis, "EnemyMetis-811");
				break;
			}
			case 14040: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000724);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000769, EnemyMetis, "EnemyMetis-812");
				break;
			}
			case 14060: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000725);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000770, EnemyMetis, "EnemyMetis-813");
				break;
			}
			case 14080: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000726);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000771, EnemyMetis, "EnemyMetis-814");
				break;
			}
			case 14100: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000727);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000772, EnemyMetis, "EnemyMetis-815");
				break;
			}
			case 14120: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000728);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000773, EnemyMetis, "EnemyMetis-816");
				break;
			}
			case 14140: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000729);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000774, EnemyMetis, "EnemyMetis-817");
				break;
			}
			case 14160: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000730);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000775, EnemyMetis, "EnemyMetis-818");
				break;
			}
			case 14180: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000731);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000776, EnemyMetis, "EnemyMetis-819");
				break;
			}
			case 14200: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000732);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000777, EnemyMetis, "EnemyMetis-820");
				break;
			}
			case 14220: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000733);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000778, EnemyMetis, "EnemyMetis-821");
				break;
			}
			case 14240: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000734);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000779, EnemyMetis, "EnemyMetis-822");
				break;
			}
			case 14260: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000735);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000780, EnemyMetis, "EnemyMetis-823");
				break;
			}
			case 14280: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000736);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000781, EnemyMetis, "EnemyMetis-824");
				break;
			}
			case 14300: {
				orderActorToFactory(10000012, EnemyHermione, "EnemyHermione-825");
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000737);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000782, EnemyMetis, "EnemyMetis-826");
				break;
			}
			case 14320: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000738);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000783, EnemyMetis, "EnemyMetis-827");
				break;
			}
			case 14340: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000739);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000784, EnemyMetis, "EnemyMetis-828");
				break;
			}
			case 14360: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000740);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000785, EnemyMetis, "EnemyMetis-829");
				break;
			}
			case 14380: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000741);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000786, EnemyMetis, "EnemyMetis-830");
				break;
			}
			case 14400: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000742);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000787, EnemyMetis, "EnemyMetis-831");
				break;
			}
			case 14420: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000743);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000788, EnemyMetis, "EnemyMetis-832");
				break;
			}
			case 14440: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000744);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000789, EnemyMetis, "EnemyMetis-833");
				break;
			}
			case 14460: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000745);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000790, EnemyMetis, "EnemyMetis-834");
				break;
			}
			case 14480: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000746);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000791, EnemyMetis, "EnemyMetis-835");
				break;
			}
			case 14500: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000747);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000792, EnemyMetis, "EnemyMetis-836");
				break;
			}
			case 14520: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000748);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000793, EnemyMetis, "EnemyMetis-837");
				break;
			}
			case 14540: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000749);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000794, EnemyMetis, "EnemyMetis-838");
				break;
			}
			case 14560: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000750);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000795, EnemyMetis, "EnemyMetis-839");
				break;
			}
			case 14580: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000751);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000796, EnemyMetis, "EnemyMetis-840");
				break;
			}
			case 14600: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000752);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000797, EnemyMetis, "EnemyMetis-841");
				break;
			}
			case 14620: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000753);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000798, EnemyMetis, "EnemyMetis-842");
				break;
			}
			case 14640: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000754);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000799, EnemyMetis, "EnemyMetis-843");
				break;
			}
			case 14660: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000755);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000800, EnemyMetis, "EnemyMetis-844");
				break;
			}
			case 14680: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000756);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000801, EnemyMetis, "EnemyMetis-845");
				break;
			}
			case 14700: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000757);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000802, EnemyMetis, "EnemyMetis-846");
				break;
			}
			case 14720: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000758);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000803, EnemyMetis, "EnemyMetis-847");
				break;
			}
			case 14740: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000759);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000804, EnemyMetis, "EnemyMetis-848");
				break;
			}
			case 14760: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000760);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000805, EnemyMetis, "EnemyMetis-849");
				break;
			}
			case 14780: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000761);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000806, EnemyMetis, "EnemyMetis-850");
				break;
			}
			case 14800: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000762);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000807, EnemyMetis, "EnemyMetis-851");
				break;
			}
			case 14820: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000763);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000808, EnemyMetis, "EnemyMetis-852");
				break;
			}
			case 14840: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000764);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000809, EnemyMetis, "EnemyMetis-853");
				break;
			}
			case 14860: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000765);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000810, EnemyMetis, "EnemyMetis-854");
				break;
			}
			case 14880: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000766);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000811, EnemyMetis, "EnemyMetis-855");
				break;
			}
			case 14900: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000767);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000812, EnemyMetis, "EnemyMetis-856");
				break;
			}
			case 14920: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000768);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000813, EnemyMetis, "EnemyMetis-857");
				break;
			}
			case 14940: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000769);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000814, EnemyMetis, "EnemyMetis-858");
				break;
			}
			case 14960: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000770);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000815, EnemyMetis, "EnemyMetis-859");
				break;
			}
			case 14980: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000771);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000816, EnemyMetis, "EnemyMetis-860");
				break;
			}
			case 15000: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000772);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000817, EnemyMetis, "EnemyMetis-861");
				break;
			}
			case 15020: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000773);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000818, EnemyMetis, "EnemyMetis-862");
				break;
			}
			case 15040: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000774);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000819, EnemyMetis, "EnemyMetis-863");
				break;
			}
			case 15060: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000775);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000820, EnemyMetis, "EnemyMetis-864");
				break;
			}
			case 15080: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000776);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000821, EnemyMetis, "EnemyMetis-865");
				break;
			}
			case 15100: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000777);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000822, EnemyMetis, "EnemyMetis-866");
				break;
			}
			case 15120: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000778);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000823, EnemyMetis, "EnemyMetis-867");
				break;
			}
			case 15140: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000779);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000824, EnemyMetis, "EnemyMetis-868");
				break;
			}
			case 15160: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000780);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000825, EnemyMetis, "EnemyMetis-869");
				break;
			}
			case 15180: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000781);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000826, EnemyMetis, "EnemyMetis-870");
				break;
			}
			case 15200: {
				EnemyHermione* p = (EnemyHermione*)obtainActorFromFactory(10000012);
				getSceneDirector()->addSubGroup(p);
				p->_X = RND(000000,1000000);
				p->_Y = RND(-600000,600000);
				p->_Z = RND(-600000,600000);
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000782);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000827, EnemyMetis, "EnemyMetis-871");
				break;
			}
			case 15220: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000783);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000828, EnemyMetis, "EnemyMetis-872");
				break;
			}
			case 15240: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000784);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000829, EnemyMetis, "EnemyMetis-873");
				break;
			}
			case 15260: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000785);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000830, EnemyMetis, "EnemyMetis-874");
				break;
			}
			case 15280: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000786);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000831, EnemyMetis, "EnemyMetis-875");
				break;
			}
			case 15300: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000787);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000832, EnemyMetis, "EnemyMetis-876");
				break;
			}
			case 15320: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000788);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000833, EnemyMetis, "EnemyMetis-877");
				break;
			}
			case 15340: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000789);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000834, EnemyMetis, "EnemyMetis-878");
				break;
			}
			case 15360: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000790);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000835, EnemyMetis, "EnemyMetis-879");
				break;
			}
			case 15380: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000791);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000836, EnemyMetis, "EnemyMetis-880");
				break;
			}
			case 15400: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000792);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000837, EnemyMetis, "EnemyMetis-881");
				break;
			}
			case 15420: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000793);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000838, EnemyMetis, "EnemyMetis-882");
				break;
			}
			case 15440: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000794);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000839, EnemyMetis, "EnemyMetis-883");
				break;
			}
			case 15460: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000795);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000840, EnemyMetis, "EnemyMetis-884");
				break;
			}
			case 15480: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000796);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000841, EnemyMetis, "EnemyMetis-885");
				break;
			}
			case 15500: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000797);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000842, EnemyMetis, "EnemyMetis-886");
				break;
			}
			case 15520: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000798);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000843, EnemyMetis, "EnemyMetis-887");
				break;
			}
			case 15540: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000799);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000844, EnemyMetis, "EnemyMetis-888");
				break;
			}
			case 15560: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000800);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000845, EnemyMetis, "EnemyMetis-889");
				break;
			}
			case 15580: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000801);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000846, EnemyMetis, "EnemyMetis-890");
				break;
			}
			case 15600: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000802);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000847, EnemyMetis, "EnemyMetis-891");
				break;
			}
			case 15620: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000803);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000848, EnemyMetis, "EnemyMetis-892");
				break;
			}
			case 15640: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000804);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000849, EnemyMetis, "EnemyMetis-893");
				break;
			}
			case 15660: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000805);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000850, EnemyMetis, "EnemyMetis-894");
				break;
			}
			case 15680: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000806);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000851, EnemyMetis, "EnemyMetis-895");
				break;
			}
			case 15700: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000807);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000852, EnemyMetis, "EnemyMetis-896");
				break;
			}
			case 15720: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000808);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000853, EnemyMetis, "EnemyMetis-897");
				break;
			}
			case 15740: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000809);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000854, EnemyMetis, "EnemyMetis-898");
				break;
			}
			case 15760: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000810);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000855, EnemyMetis, "EnemyMetis-899");
				break;
			}
			case 15780: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000811);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000856, EnemyMetis, "EnemyMetis-900");
				break;
			}
			case 15800: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000812);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000857, EnemyMetis, "EnemyMetis-901");
				break;
			}
			case 15820: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000813);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000858, EnemyMetis, "EnemyMetis-902");
				break;
			}
			case 15840: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000814);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000859, EnemyMetis, "EnemyMetis-903");
				break;
			}
			case 15860: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000815);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000860, EnemyMetis, "EnemyMetis-904");
				break;
			}
			case 15880: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000816);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000861, EnemyMetis, "EnemyMetis-905");
				break;
			}
			case 15900: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000817);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000862, EnemyMetis, "EnemyMetis-906");
				break;
			}
			case 15920: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000818);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000863, EnemyMetis, "EnemyMetis-907");
				break;
			}
			case 15940: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000819);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000864, EnemyMetis, "EnemyMetis-908");
				break;
			}
			case 15960: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000820);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000865, EnemyMetis, "EnemyMetis-909");
				break;
			}
			case 15980: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000821);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000866, EnemyMetis, "EnemyMetis-910");
				break;
			}
			case 16000: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000822);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000867, EnemyMetis, "EnemyMetis-911");
				break;
			}
			case 16020: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000823);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000868, EnemyMetis, "EnemyMetis-912");
				break;
			}
			case 16040: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000824);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000869, EnemyMetis, "EnemyMetis-913");
				break;
			}
			case 16060: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000825);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000870, EnemyMetis, "EnemyMetis-914");
				break;
			}
			case 16080: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000826);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000871, EnemyMetis, "EnemyMetis-915");
				break;
			}
			case 16100: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000827);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000872, EnemyMetis, "EnemyMetis-916");
				break;
			}
			case 16120: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000828);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000873, EnemyMetis, "EnemyMetis-917");
				break;
			}
			case 16140: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000829);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000874, EnemyMetis, "EnemyMetis-918");
				break;
			}
			case 16160: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000830);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000875, EnemyMetis, "EnemyMetis-919");
				break;
			}
			case 16180: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000831);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000876, EnemyMetis, "EnemyMetis-920");
				break;
			}
			case 16200: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000832);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000877, EnemyMetis, "EnemyMetis-921");
				break;
			}
			case 16220: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000833);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000878, EnemyMetis, "EnemyMetis-922");
				break;
			}
			case 16240: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000834);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000879, EnemyMetis, "EnemyMetis-923");
				break;
			}
			case 16260: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000835);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000880, EnemyMetis, "EnemyMetis-924");
				break;
			}
			case 16280: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000836);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000881, EnemyMetis, "EnemyMetis-925");
				break;
			}
			case 16300: {
				orderActorToFactory(10000013, EnemyHermione, "EnemyHermione-926");
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000837);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000882, EnemyMetis, "EnemyMetis-927");
				break;
			}
			case 16320: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000838);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000883, EnemyMetis, "EnemyMetis-928");
				break;
			}
			case 16340: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000839);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000884, EnemyMetis, "EnemyMetis-929");
				break;
			}
			case 16360: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000840);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000885, EnemyMetis, "EnemyMetis-930");
				break;
			}
			case 16380: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000841);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000886, EnemyMetis, "EnemyMetis-931");
				break;
			}
			case 16400: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000842);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000887, EnemyMetis, "EnemyMetis-932");
				break;
			}
			case 16420: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000843);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000888, EnemyMetis, "EnemyMetis-933");
				break;
			}
			case 16440: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000844);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000889, EnemyMetis, "EnemyMetis-934");
				break;
			}
			case 16460: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000845);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000890, EnemyMetis, "EnemyMetis-935");
				break;
			}
			case 16480: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000846);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000891, EnemyMetis, "EnemyMetis-936");
				break;
			}
			case 16500: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000847);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000892, EnemyMetis, "EnemyMetis-937");
				break;
			}
			case 16520: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000848);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000893, EnemyMetis, "EnemyMetis-938");
				break;
			}
			case 16540: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000849);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000894, EnemyMetis, "EnemyMetis-939");
				break;
			}
			case 16560: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000850);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000895, EnemyMetis, "EnemyMetis-940");
				break;
			}
			case 16580: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000851);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000896, EnemyMetis, "EnemyMetis-941");
				break;
			}
			case 16600: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000852);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000897, EnemyMetis, "EnemyMetis-942");
				break;
			}
			case 16620: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000853);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000898, EnemyMetis, "EnemyMetis-943");
				break;
			}
			case 16640: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000854);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000899, EnemyMetis, "EnemyMetis-944");
				break;
			}
			case 16660: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000855);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000900, EnemyMetis, "EnemyMetis-945");
				break;
			}
			case 16680: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000856);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000901, EnemyMetis, "EnemyMetis-946");
				break;
			}
			case 16700: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000857);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000902, EnemyMetis, "EnemyMetis-947");
				break;
			}
			case 16720: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000858);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000903, EnemyMetis, "EnemyMetis-948");
				break;
			}
			case 16740: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000859);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000904, EnemyMetis, "EnemyMetis-949");
				break;
			}
			case 16760: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000860);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000905, EnemyMetis, "EnemyMetis-950");
				break;
			}
			case 16780: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000861);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000906, EnemyMetis, "EnemyMetis-951");
				break;
			}
			case 16800: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000862);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000907, EnemyMetis, "EnemyMetis-952");
				break;
			}
			case 16820: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000863);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000908, EnemyMetis, "EnemyMetis-953");
				break;
			}
			case 16840: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000864);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000909, EnemyMetis, "EnemyMetis-954");
				break;
			}
			case 16860: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000865);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000910, EnemyMetis, "EnemyMetis-955");
				break;
			}
			case 16880: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000866);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000911, EnemyMetis, "EnemyMetis-956");
				break;
			}
			case 16900: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000867);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000912, EnemyMetis, "EnemyMetis-957");
				break;
			}
			case 16920: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000868);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000913, EnemyMetis, "EnemyMetis-958");
				break;
			}
			case 16940: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000869);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000914, EnemyMetis, "EnemyMetis-959");
				break;
			}
			case 16960: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000870);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000915, EnemyMetis, "EnemyMetis-960");
				break;
			}
			case 16980: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000871);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000916, EnemyMetis, "EnemyMetis-961");
				break;
			}
			case 17000: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000872);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000917, EnemyMetis, "EnemyMetis-962");
				break;
			}
			case 17020: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000873);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000918, EnemyMetis, "EnemyMetis-963");
				break;
			}
			case 17040: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000874);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000919, EnemyMetis, "EnemyMetis-964");
				break;
			}
			case 17060: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000875);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000920, EnemyMetis, "EnemyMetis-965");
				break;
			}
			case 17080: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000876);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000921, EnemyMetis, "EnemyMetis-966");
				break;
			}
			case 17100: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000877);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000922, EnemyMetis, "EnemyMetis-967");
				break;
			}
			case 17120: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000878);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000923, EnemyMetis, "EnemyMetis-968");
				break;
			}
			case 17140: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000879);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000924, EnemyMetis, "EnemyMetis-969");
				break;
			}
			case 17160: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000880);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000925, EnemyMetis, "EnemyMetis-970");
				break;
			}
			case 17180: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000881);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000926, EnemyMetis, "EnemyMetis-971");
				break;
			}
			case 17200: {
				EnemyHermione* p = (EnemyHermione*)obtainActorFromFactory(10000013);
				getSceneDirector()->addSubGroup(p);
				p->_X = RND(000000,1000000);
				p->_Y = RND(-600000,600000);
				p->_Z = RND(-600000,600000);
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000882);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000927, EnemyMetis, "EnemyMetis-972");
				break;
			}
			case 17220: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000883);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000928, EnemyMetis, "EnemyMetis-973");
				break;
			}
			case 17240: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000884);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000929, EnemyMetis, "EnemyMetis-974");
				break;
			}
			case 17260: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000885);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000930, EnemyMetis, "EnemyMetis-975");
				break;
			}
			case 17280: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000886);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000931, EnemyMetis, "EnemyMetis-976");
				break;
			}
			case 17300: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000887);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000932, EnemyMetis, "EnemyMetis-977");
				break;
			}
			case 17320: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000888);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000933, EnemyMetis, "EnemyMetis-978");
				break;
			}
			case 17340: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000889);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000934, EnemyMetis, "EnemyMetis-979");
				break;
			}
			case 17360: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000890);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000935, EnemyMetis, "EnemyMetis-980");
				break;
			}
			case 17380: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000891);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000936, EnemyMetis, "EnemyMetis-981");
				break;
			}
			case 17400: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000892);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000937, EnemyMetis, "EnemyMetis-982");
				break;
			}
			case 17420: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000893);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000938, EnemyMetis, "EnemyMetis-983");
				break;
			}
			case 17440: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000894);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000939, EnemyMetis, "EnemyMetis-984");
				break;
			}
			case 17460: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000895);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000940, EnemyMetis, "EnemyMetis-985");
				break;
			}
			case 17480: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000896);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000941, EnemyMetis, "EnemyMetis-986");
				break;
			}
			case 17500: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000897);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000942, EnemyMetis, "EnemyMetis-987");
				break;
			}
			case 17520: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000898);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000943, EnemyMetis, "EnemyMetis-988");
				break;
			}
			case 17540: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000899);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000944, EnemyMetis, "EnemyMetis-989");
				break;
			}
			case 17560: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000900);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000945, EnemyMetis, "EnemyMetis-990");
				break;
			}
			case 17580: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000901);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000946, EnemyMetis, "EnemyMetis-991");
				break;
			}
			case 17600: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000902);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000947, EnemyMetis, "EnemyMetis-992");
				break;
			}
			case 17620: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000903);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000948, EnemyMetis, "EnemyMetis-993");
				break;
			}
			case 17640: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000904);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000949, EnemyMetis, "EnemyMetis-994");
				break;
			}
			case 17660: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000905);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000950, EnemyMetis, "EnemyMetis-995");
				break;
			}
			case 17680: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000906);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000951, EnemyMetis, "EnemyMetis-996");
				break;
			}
			case 17700: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000907);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000952, EnemyMetis, "EnemyMetis-997");
				break;
			}
			case 17720: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000908);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000953, EnemyMetis, "EnemyMetis-998");
				break;
			}
			case 17740: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000909);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000954, EnemyMetis, "EnemyMetis-999");
				break;
			}
			case 17760: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000910);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000955, EnemyMetis, "EnemyMetis-1000");
				break;
			}
			case 17780: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000911);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000956, EnemyMetis, "EnemyMetis-1001");
				break;
			}
			case 17800: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000912);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000957, EnemyMetis, "EnemyMetis-1002");
				break;
			}
			case 17820: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000913);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000958, EnemyMetis, "EnemyMetis-1003");
				break;
			}
			case 17840: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000914);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000959, EnemyMetis, "EnemyMetis-1004");
				break;
			}
			case 17860: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000915);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000960, EnemyMetis, "EnemyMetis-1005");
				break;
			}
			case 17880: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000916);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000961, EnemyMetis, "EnemyMetis-1006");
				break;
			}
			case 17900: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000917);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000962, EnemyMetis, "EnemyMetis-1007");
				break;
			}
			case 17920: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000918);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000963, EnemyMetis, "EnemyMetis-1008");
				break;
			}
			case 17940: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000919);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000964, EnemyMetis, "EnemyMetis-1009");
				break;
			}
			case 17960: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000920);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000965, EnemyMetis, "EnemyMetis-1010");
				break;
			}
			case 17980: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000921);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000966, EnemyMetis, "EnemyMetis-1011");
				break;
			}
			case 18000: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000922);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000967, EnemyMetis, "EnemyMetis-1012");
				break;
			}
			case 18020: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000923);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000968, EnemyMetis, "EnemyMetis-1013");
				break;
			}
			case 18040: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000924);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000969, EnemyMetis, "EnemyMetis-1014");
				break;
			}
			case 18060: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000925);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000970, EnemyMetis, "EnemyMetis-1015");
				break;
			}
			case 18080: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000926);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000971, EnemyMetis, "EnemyMetis-1016");
				break;
			}
			case 18100: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000927);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000972, EnemyMetis, "EnemyMetis-1017");
				break;
			}
			case 18120: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000928);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000973, EnemyMetis, "EnemyMetis-1018");
				break;
			}
			case 18140: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000929);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000974, EnemyMetis, "EnemyMetis-1019");
				break;
			}
			case 18160: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000930);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000975, EnemyMetis, "EnemyMetis-1020");
				break;
			}
			case 18180: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000931);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000976, EnemyMetis, "EnemyMetis-1021");
				break;
			}
			case 18200: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000932);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000977, EnemyMetis, "EnemyMetis-1022");
				break;
			}
			case 18220: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000933);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000978, EnemyMetis, "EnemyMetis-1023");
				break;
			}
			case 18240: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000934);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000979, EnemyMetis, "EnemyMetis-1024");
				break;
			}
			case 18260: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000935);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000980, EnemyMetis, "EnemyMetis-1025");
				break;
			}
			case 18280: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000936);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000981, EnemyMetis, "EnemyMetis-1026");
				break;
			}
			case 18300: {
				orderActorToFactory(10000014, EnemyHermione, "EnemyHermione-1027");
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000937);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000982, EnemyMetis, "EnemyMetis-1028");
				break;
			}
			case 18320: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000938);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000983, EnemyMetis, "EnemyMetis-1029");
				break;
			}
			case 18340: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000939);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000984, EnemyMetis, "EnemyMetis-1030");
				break;
			}
			case 18360: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000940);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000985, EnemyMetis, "EnemyMetis-1031");
				break;
			}
			case 18380: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000941);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000986, EnemyMetis, "EnemyMetis-1032");
				break;
			}
			case 18400: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000942);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000987, EnemyMetis, "EnemyMetis-1033");
				break;
			}
			case 18420: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000943);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000988, EnemyMetis, "EnemyMetis-1034");
				break;
			}
			case 18440: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000944);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000989, EnemyMetis, "EnemyMetis-1035");
				break;
			}
			case 18460: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000945);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000990, EnemyMetis, "EnemyMetis-1036");
				break;
			}
			case 18480: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000946);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000991, EnemyMetis, "EnemyMetis-1037");
				break;
			}
			case 18500: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000947);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000992, EnemyMetis, "EnemyMetis-1038");
				break;
			}
			case 18520: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000948);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000993, EnemyMetis, "EnemyMetis-1039");
				break;
			}
			case 18540: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000949);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000994, EnemyMetis, "EnemyMetis-1040");
				break;
			}
			case 18560: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000950);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000995, EnemyMetis, "EnemyMetis-1041");
				break;
			}
			case 18580: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000951);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000996, EnemyMetis, "EnemyMetis-1042");
				break;
			}
			case 18600: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000952);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000997, EnemyMetis, "EnemyMetis-1043");
				break;
			}
			case 18620: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000953);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000998, EnemyMetis, "EnemyMetis-1044");
				break;
			}
			case 18640: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000954);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10000999, EnemyMetis, "EnemyMetis-1045");
				break;
			}
			case 18660: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000955);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001000, EnemyMetis, "EnemyMetis-1046");
				break;
			}
			case 18680: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000956);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001001, EnemyMetis, "EnemyMetis-1047");
				break;
			}
			case 18700: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000957);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001002, EnemyMetis, "EnemyMetis-1048");
				break;
			}
			case 18720: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000958);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001003, EnemyMetis, "EnemyMetis-1049");
				break;
			}
			case 18740: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000959);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001004, EnemyMetis, "EnemyMetis-1050");
				break;
			}
			case 18760: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000960);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001005, EnemyMetis, "EnemyMetis-1051");
				break;
			}
			case 18780: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000961);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001006, EnemyMetis, "EnemyMetis-1052");
				break;
			}
			case 18800: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000962);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001007, EnemyMetis, "EnemyMetis-1053");
				break;
			}
			case 18820: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000963);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001008, EnemyMetis, "EnemyMetis-1054");
				break;
			}
			case 18840: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000964);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001009, EnemyMetis, "EnemyMetis-1055");
				break;
			}
			case 18860: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000965);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001010, EnemyMetis, "EnemyMetis-1056");
				break;
			}
			case 18880: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000966);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001011, EnemyMetis, "EnemyMetis-1057");
				break;
			}
			case 18900: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000967);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001012, EnemyMetis, "EnemyMetis-1058");
				break;
			}
			case 18920: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000968);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001013, EnemyMetis, "EnemyMetis-1059");
				break;
			}
			case 18940: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000969);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001014, EnemyMetis, "EnemyMetis-1060");
				break;
			}
			case 18960: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000970);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001015, EnemyMetis, "EnemyMetis-1061");
				break;
			}
			case 18980: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000971);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001016, EnemyMetis, "EnemyMetis-1062");
				break;
			}
			case 19000: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000972);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001017, EnemyMetis, "EnemyMetis-1063");
				break;
			}
			case 19020: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000973);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001018, EnemyMetis, "EnemyMetis-1064");
				break;
			}
			case 19040: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000974);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001019, EnemyMetis, "EnemyMetis-1065");
				break;
			}
			case 19060: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000975);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001020, EnemyMetis, "EnemyMetis-1066");
				break;
			}
			case 19080: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000976);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001021, EnemyMetis, "EnemyMetis-1067");
				break;
			}
			case 19100: {
				orderSceneToFactory(10000002, Stage01_03, "Stage01_03-1068");
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000977);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001022, EnemyMetis, "EnemyMetis-1069");
				orderActorToFactory(10001573, FormationAdelheid001, "FormationAdelheid001-1070");
				break;
			}
			case 19120: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000978);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001023, EnemyMetis, "EnemyMetis-1071");
				break;
			}
			case 19140: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000979);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001024, EnemyMetis, "EnemyMetis-1072");
				break;
			}
			case 19160: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000980);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001025, EnemyMetis, "EnemyMetis-1073");
				break;
			}
			case 19180: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000981);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001026, EnemyMetis, "EnemyMetis-1074");
				break;
			}
			case 19200: {
				EnemyHermione* p = (EnemyHermione*)obtainActorFromFactory(10000014);
				getSceneDirector()->addSubGroup(p);
				p->_X = RND(000000,1000000);
				p->_Y = RND(-600000,600000);
				p->_Z = RND(-600000,600000);
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000982);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001027, EnemyMetis, "EnemyMetis-1075");
				orderActorToFactory(10001574, FormationAdelheid001, "FormationAdelheid001-1076");
				break;
			}
			case 19220: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000983);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001028, EnemyMetis, "EnemyMetis-1077");
				break;
			}
			case 19240: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000984);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001029, EnemyMetis, "EnemyMetis-1078");
				break;
			}
			case 19260: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000985);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001030, EnemyMetis, "EnemyMetis-1079");
				break;
			}
			case 19280: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000986);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001031, EnemyMetis, "EnemyMetis-1080");
				break;
			}
			case 19300: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000987);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001032, EnemyMetis, "EnemyMetis-1081");
				orderActorToFactory(10001575, FormationAdelheid001, "FormationAdelheid001-1082");
				break;
			}
			case 19320: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000988);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001033, EnemyMetis, "EnemyMetis-1083");
				break;
			}
			case 19340: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000989);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001034, EnemyMetis, "EnemyMetis-1084");
				break;
			}
			case 19360: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000990);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001035, EnemyMetis, "EnemyMetis-1085");
				break;
			}
			case 19380: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000991);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001036, EnemyMetis, "EnemyMetis-1086");
				break;
			}
			case 19400: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000992);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001037, EnemyMetis, "EnemyMetis-1087");
				orderActorToFactory(10001576, FormationAdelheid001, "FormationAdelheid001-1088");
				break;
			}
			case 19420: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000993);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001038, EnemyMetis, "EnemyMetis-1089");
				break;
			}
			case 19440: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000994);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001039, EnemyMetis, "EnemyMetis-1090");
				break;
			}
			case 19460: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000995);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001040, EnemyMetis, "EnemyMetis-1091");
				break;
			}
			case 19480: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000996);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001041, EnemyMetis, "EnemyMetis-1092");
				break;
			}
			case 19500: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000997);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001042, EnemyMetis, "EnemyMetis-1093");
				orderActorToFactory(10001577, FormationAdelheid001, "FormationAdelheid001-1094");
				break;
			}
			case 19520: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000998);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001043, EnemyMetis, "EnemyMetis-1095");
				break;
			}
			case 19540: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000999);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001044, EnemyMetis, "EnemyMetis-1096");
				break;
			}
			case 19560: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001000);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001045, EnemyMetis, "EnemyMetis-1097");
				break;
			}
			case 19580: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001001);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001046, EnemyMetis, "EnemyMetis-1098");
				break;
			}
			case 19600: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001002);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001047, EnemyMetis, "EnemyMetis-1099");
				orderActorToFactory(10001578, FormationAdelheid001, "FormationAdelheid001-1100");
				break;
			}
			case 19620: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001003);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001048, EnemyMetis, "EnemyMetis-1101");
				break;
			}
			case 19640: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001004);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001049, EnemyMetis, "EnemyMetis-1102");
				break;
			}
			case 19660: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001005);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001050, EnemyMetis, "EnemyMetis-1103");
				break;
			}
			case 19680: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001006);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001051, EnemyMetis, "EnemyMetis-1104");
				break;
			}
			case 19700: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001007);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001052, EnemyMetis, "EnemyMetis-1105");
				orderActorToFactory(10001579, FormationAdelheid001, "FormationAdelheid001-1106");
				break;
			}
			case 19720: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001008);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001053, EnemyMetis, "EnemyMetis-1107");
				break;
			}
			case 19740: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001009);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001054, EnemyMetis, "EnemyMetis-1108");
				break;
			}
			case 19760: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001010);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001055, EnemyMetis, "EnemyMetis-1109");
				break;
			}
			case 19780: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001011);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001056, EnemyMetis, "EnemyMetis-1110");
				break;
			}
			case 19800: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001012);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001057, EnemyMetis, "EnemyMetis-1111");
				orderActorToFactory(10001580, FormationAdelheid001, "FormationAdelheid001-1112");
				break;
			}
			case 19820: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001013);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001058, EnemyMetis, "EnemyMetis-1113");
				break;
			}
			case 19840: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001014);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001059, EnemyMetis, "EnemyMetis-1114");
				break;
			}
			case 19860: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001015);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001060, EnemyMetis, "EnemyMetis-1115");
				break;
			}
			case 19880: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001016);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001061, EnemyMetis, "EnemyMetis-1116");
				break;
			}
			case 19900: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001017);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001062, EnemyMetis, "EnemyMetis-1117");
				orderActorToFactory(10001581, FormationAdelheid001, "FormationAdelheid001-1118");
				break;
			}
			case 19920: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001018);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001063, EnemyMetis, "EnemyMetis-1119");
				break;
			}
			case 19940: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001019);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001064, EnemyMetis, "EnemyMetis-1120");
				break;
			}
			case 19960: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001020);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001065, EnemyMetis, "EnemyMetis-1121");
				break;
			}
			case 19980: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001021);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001066, EnemyMetis, "EnemyMetis-1122");
				break;
			}
			case 20000: {
				Stage01_03* pScene = (Stage01_03*)obtainSceneFromFactory(10000002);
				addSubLast(pScene);
				_pBgmPerformer->fadeout_stop(1);
				_pBgmPerformer->play_fadein(2);
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001022);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001067, EnemyMetis, "EnemyMetis-1123");
				FormationAdelheid001* pF = (FormationAdelheid001*)obtainActorFromFactory(10001573);
				getSceneDirector()->addSubGroup(pF);
				pF->locate(PX_C(-200), PX_C(-400), PX_C(500), D_ANG(-40), D_ANG(0));
				break;
			}
			case 20020: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001023);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001068, EnemyMetis, "EnemyMetis-1124");
				break;
			}
			case 20040: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001024);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001069, EnemyMetis, "EnemyMetis-1125");
				break;
			}
			case 20060: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001025);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001070, EnemyMetis, "EnemyMetis-1126");
				break;
			}
			case 20080: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001026);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001071, EnemyMetis, "EnemyMetis-1127");
				break;
			}
			case 20100: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001027);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001072, EnemyMetis, "EnemyMetis-1128");
				FormationAdelheid001* pF = (FormationAdelheid001*)obtainActorFromFactory(10001574);
				getSceneDirector()->addSubGroup(pF);
				pF->locate(PX_C(-200), PX_C(-300), PX_C(500), D_ANG(-30), D_ANG(0));
				break;
			}
			case 20120: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001028);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001073, EnemyMetis, "EnemyMetis-1129");
				break;
			}
			case 20140: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001029);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001074, EnemyMetis, "EnemyMetis-1130");
				break;
			}
			case 20160: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001030);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001075, EnemyMetis, "EnemyMetis-1131");
				break;
			}
			case 20180: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001031);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001076, EnemyMetis, "EnemyMetis-1132");
				break;
			}
			case 20200: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001032);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001077, EnemyMetis, "EnemyMetis-1133");
				FormationAdelheid001* pF = (FormationAdelheid001*)obtainActorFromFactory(10001575);
				getSceneDirector()->addSubGroup(pF);
				pF->locate(PX_C(-200), PX_C(-200), PX_C(500), D_ANG(-20), D_ANG(0));
				break;
			}
			case 20220: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001033);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001078, EnemyMetis, "EnemyMetis-1134");
				break;
			}
			case 20240: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001034);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001079, EnemyMetis, "EnemyMetis-1135");
				break;
			}
			case 20260: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001035);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001080, EnemyMetis, "EnemyMetis-1136");
				break;
			}
			case 20280: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001036);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001081, EnemyMetis, "EnemyMetis-1137");
				break;
			}
			case 20300: {
				orderActorToFactory(10000015, EnemyHermione, "EnemyHermione-1138");
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001037);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001082, EnemyMetis, "EnemyMetis-1139");
				FormationAdelheid001* pF = (FormationAdelheid001*)obtainActorFromFactory(10001576);
				getSceneDirector()->addSubGroup(pF);
				pF->locate(PX_C(-200), PX_C(-100), PX_C(500), D_ANG(-10), D_ANG(0));
				break;
			}
			case 20320: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001038);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001083, EnemyMetis, "EnemyMetis-1140");
				break;
			}
			case 20340: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001039);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001084, EnemyMetis, "EnemyMetis-1141");
				break;
			}
			case 20360: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001040);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001085, EnemyMetis, "EnemyMetis-1142");
				break;
			}
			case 20380: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001041);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001086, EnemyMetis, "EnemyMetis-1143");
				break;
			}
			case 20400: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001042);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001087, EnemyMetis, "EnemyMetis-1144");
				FormationAdelheid001* pF = (FormationAdelheid001*)obtainActorFromFactory(10001577);
				getSceneDirector()->addSubGroup(pF);
				pF->locate(PX_C(-200), PX_C(  0), PX_C(500), D_ANG(0), D_ANG(0));
				break;
			}
			case 20420: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001043);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001088, EnemyMetis, "EnemyMetis-1145");
				break;
			}
			case 20440: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001044);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001089, EnemyMetis, "EnemyMetis-1146");
				break;
			}
			case 20460: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001045);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001090, EnemyMetis, "EnemyMetis-1147");
				break;
			}
			case 20480: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001046);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001091, EnemyMetis, "EnemyMetis-1148");
				break;
			}
			case 20500: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001047);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001092, EnemyMetis, "EnemyMetis-1149");
				FormationAdelheid001* pF = (FormationAdelheid001*)obtainActorFromFactory(10001578);
				getSceneDirector()->addSubGroup(pF);
				pF->locate(PX_C(-200), PX_C( 100), PX_C(500), D_ANG(10), D_ANG(0));
				break;
			}
			case 20520: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001048);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001093, EnemyMetis, "EnemyMetis-1150");
				break;
			}
			case 20540: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001049);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001094, EnemyMetis, "EnemyMetis-1151");
				break;
			}
			case 20560: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001050);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001095, EnemyMetis, "EnemyMetis-1152");
				break;
			}
			case 20580: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001051);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001096, EnemyMetis, "EnemyMetis-1153");
				break;
			}
			case 20600: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001052);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001097, EnemyMetis, "EnemyMetis-1154");
				FormationAdelheid001* pF = (FormationAdelheid001*)obtainActorFromFactory(10001579);
				getSceneDirector()->addSubGroup(pF);
				pF->locate(PX_C(-200), PX_C( 200), PX_C(500), D_ANG(20), D_ANG(0));
				break;
			}
			case 20620: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001053);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001098, EnemyMetis, "EnemyMetis-1155");
				break;
			}
			case 20640: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001054);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001099, EnemyMetis, "EnemyMetis-1156");
				break;
			}
			case 20660: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001055);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001100, EnemyMetis, "EnemyMetis-1157");
				break;
			}
			case 20680: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001056);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001101, EnemyMetis, "EnemyMetis-1158");
				break;
			}
			case 20700: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001057);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001102, EnemyMetis, "EnemyMetis-1159");
				FormationAdelheid001* pF = (FormationAdelheid001*)obtainActorFromFactory(10001580);
				getSceneDirector()->addSubGroup(pF);
				pF->locate(PX_C(-200), PX_C( 300), PX_C(500), D_ANG(30), D_ANG(0));
				break;
			}
			case 20720: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001058);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001103, EnemyMetis, "EnemyMetis-1160");
				break;
			}
			case 20740: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001059);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001104, EnemyMetis, "EnemyMetis-1161");
				break;
			}
			case 20760: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001060);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001105, EnemyMetis, "EnemyMetis-1162");
				break;
			}
			case 20780: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001061);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001106, EnemyMetis, "EnemyMetis-1163");
				break;
			}
			case 20800: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001062);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001107, EnemyMetis, "EnemyMetis-1164");
				FormationAdelheid001* pF = (FormationAdelheid001*)obtainActorFromFactory(10001581);
				getSceneDirector()->addSubGroup(pF);
				pF->locate(PX_C(-200), PX_C( 400), PX_C(500), D_ANG(40), D_ANG(0));
				break;
			}
			case 20820: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001063);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001108, EnemyMetis, "EnemyMetis-1165");
				break;
			}
			case 20840: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001064);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001109, EnemyMetis, "EnemyMetis-1166");
				break;
			}
			case 20860: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001065);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001110, EnemyMetis, "EnemyMetis-1167");
				break;
			}
			case 20880: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001066);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001111, EnemyMetis, "EnemyMetis-1168");
				break;
			}
			case 20900: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001067);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001112, EnemyMetis, "EnemyMetis-1169");
				break;
			}
			case 20920: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001068);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001113, EnemyMetis, "EnemyMetis-1170");
				break;
			}
			case 20940: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001069);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001114, EnemyMetis, "EnemyMetis-1171");
				break;
			}
			case 20960: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001070);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001115, EnemyMetis, "EnemyMetis-1172");
				break;
			}
			case 20980: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001071);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001116, EnemyMetis, "EnemyMetis-1173");
				break;
			}
			case 21000: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001072);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001117, EnemyMetis, "EnemyMetis-1174");
				break;
			}
			case 21020: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001073);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001118, EnemyMetis, "EnemyMetis-1175");
				break;
			}
			case 21040: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001074);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001119, EnemyMetis, "EnemyMetis-1176");
				break;
			}
			case 21060: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001075);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001120, EnemyMetis, "EnemyMetis-1177");
				break;
			}
			case 21080: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001076);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001121, EnemyMetis, "EnemyMetis-1178");
				break;
			}
			case 21100: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001077);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001122, EnemyMetis, "EnemyMetis-1179");
				break;
			}
			case 21120: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001078);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001123, EnemyMetis, "EnemyMetis-1180");
				break;
			}
			case 21140: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001079);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001124, EnemyMetis, "EnemyMetis-1181");
				break;
			}
			case 21160: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001080);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001125, EnemyMetis, "EnemyMetis-1182");
				break;
			}
			case 21180: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001081);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001126, EnemyMetis, "EnemyMetis-1183");
				break;
			}
			case 21200: {
				EnemyHermione* p = (EnemyHermione*)obtainActorFromFactory(10000015);
				getSceneDirector()->addSubGroup(p);
				p->_X = RND(000000,1000000);
				p->_Y = RND(-600000,600000);
				p->_Z = RND(-600000,600000);
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001082);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001127, EnemyMetis, "EnemyMetis-1184");
				break;
			}
			case 21220: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001083);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001128, EnemyMetis, "EnemyMetis-1185");
				break;
			}
			case 21240: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001084);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001129, EnemyMetis, "EnemyMetis-1186");
				break;
			}
			case 21260: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001085);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001130, EnemyMetis, "EnemyMetis-1187");
				break;
			}
			case 21280: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001086);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001131, EnemyMetis, "EnemyMetis-1188");
				break;
			}
			case 21300: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001087);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001132, EnemyMetis, "EnemyMetis-1189");
				break;
			}
			case 21320: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001088);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001133, EnemyMetis, "EnemyMetis-1190");
				break;
			}
			case 21340: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001089);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001134, EnemyMetis, "EnemyMetis-1191");
				break;
			}
			case 21360: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001090);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001135, EnemyMetis, "EnemyMetis-1192");
				break;
			}
			case 21380: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001091);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001136, EnemyMetis, "EnemyMetis-1193");
				break;
			}
			case 21400: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001092);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001137, EnemyMetis, "EnemyMetis-1194");
				break;
			}
			case 21420: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001093);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001138, EnemyMetis, "EnemyMetis-1195");
				break;
			}
			case 21440: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001094);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001139, EnemyMetis, "EnemyMetis-1196");
				break;
			}
			case 21460: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001095);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001140, EnemyMetis, "EnemyMetis-1197");
				break;
			}
			case 21480: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001096);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001141, EnemyMetis, "EnemyMetis-1198");
				break;
			}
			case 21500: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001097);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001142, EnemyMetis, "EnemyMetis-1199");
				break;
			}
			case 21520: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001098);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001143, EnemyMetis, "EnemyMetis-1200");
				break;
			}
			case 21540: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001099);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001144, EnemyMetis, "EnemyMetis-1201");
				break;
			}
			case 21560: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001100);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001145, EnemyMetis, "EnemyMetis-1202");
				break;
			}
			case 21580: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001101);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001146, EnemyMetis, "EnemyMetis-1203");
				break;
			}
			case 21600: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001102);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001147, EnemyMetis, "EnemyMetis-1204");
				break;
			}
			case 21620: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001103);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001148, EnemyMetis, "EnemyMetis-1205");
				break;
			}
			case 21640: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001104);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001149, EnemyMetis, "EnemyMetis-1206");
				break;
			}
			case 21660: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001105);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001150, EnemyMetis, "EnemyMetis-1207");
				break;
			}
			case 21680: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001106);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001151, EnemyMetis, "EnemyMetis-1208");
				break;
			}
			case 21700: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001107);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001152, EnemyMetis, "EnemyMetis-1209");
				break;
			}
			case 21720: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001108);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001153, EnemyMetis, "EnemyMetis-1210");
				break;
			}
			case 21740: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001109);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001154, EnemyMetis, "EnemyMetis-1211");
				break;
			}
			case 21760: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001110);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001155, EnemyMetis, "EnemyMetis-1212");
				break;
			}
			case 21780: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001111);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001156, EnemyMetis, "EnemyMetis-1213");
				break;
			}
			case 21800: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001112);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001157, EnemyMetis, "EnemyMetis-1214");
				break;
			}
			case 21820: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001113);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001158, EnemyMetis, "EnemyMetis-1215");
				break;
			}
			case 21840: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001114);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001159, EnemyMetis, "EnemyMetis-1216");
				break;
			}
			case 21860: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001115);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001160, EnemyMetis, "EnemyMetis-1217");
				break;
			}
			case 21880: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001116);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001161, EnemyMetis, "EnemyMetis-1218");
				break;
			}
			case 21900: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001117);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001162, EnemyMetis, "EnemyMetis-1219");
				break;
			}
			case 21920: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001118);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001163, EnemyMetis, "EnemyMetis-1220");
				break;
			}
			case 21940: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001119);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001164, EnemyMetis, "EnemyMetis-1221");
				break;
			}
			case 21960: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001120);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001165, EnemyMetis, "EnemyMetis-1222");
				break;
			}
			case 21980: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001121);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001166, EnemyMetis, "EnemyMetis-1223");
				break;
			}
			case 22000: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001122);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001167, EnemyMetis, "EnemyMetis-1224");
				break;
			}
			case 22020: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001123);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001168, EnemyMetis, "EnemyMetis-1225");
				break;
			}
			case 22040: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001124);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001169, EnemyMetis, "EnemyMetis-1226");
				break;
			}
			case 22060: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001125);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001170, EnemyMetis, "EnemyMetis-1227");
				break;
			}
			case 22080: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001126);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001171, EnemyMetis, "EnemyMetis-1228");
				break;
			}
			case 22100: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001127);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001172, EnemyMetis, "EnemyMetis-1229");
				break;
			}
			case 22120: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001128);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001173, EnemyMetis, "EnemyMetis-1230");
				break;
			}
			case 22140: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001129);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001174, EnemyMetis, "EnemyMetis-1231");
				break;
			}
			case 22160: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001130);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001175, EnemyMetis, "EnemyMetis-1232");
				break;
			}
			case 22180: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001131);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001176, EnemyMetis, "EnemyMetis-1233");
				break;
			}
			case 22200: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001132);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001177, EnemyMetis, "EnemyMetis-1234");
				break;
			}
			case 22220: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001133);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001178, EnemyMetis, "EnemyMetis-1235");
				break;
			}
			case 22240: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001134);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001179, EnemyMetis, "EnemyMetis-1236");
				break;
			}
			case 22260: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001135);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001180, EnemyMetis, "EnemyMetis-1237");
				break;
			}
			case 22280: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001136);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001181, EnemyMetis, "EnemyMetis-1238");
				break;
			}
			case 22300: {
				orderActorToFactory(10000016, EnemyHermione, "EnemyHermione-1239");
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001137);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001182, EnemyMetis, "EnemyMetis-1240");
				break;
			}
			case 22320: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001138);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001183, EnemyMetis, "EnemyMetis-1241");
				break;
			}
			case 22340: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001139);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001184, EnemyMetis, "EnemyMetis-1242");
				break;
			}
			case 22360: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001140);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001185, EnemyMetis, "EnemyMetis-1243");
				break;
			}
			case 22380: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001141);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001186, EnemyMetis, "EnemyMetis-1244");
				break;
			}
			case 22400: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001142);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001187, EnemyMetis, "EnemyMetis-1245");
				break;
			}
			case 22420: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001143);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001188, EnemyMetis, "EnemyMetis-1246");
				break;
			}
			case 22440: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001144);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001189, EnemyMetis, "EnemyMetis-1247");
				break;
			}
			case 22460: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001145);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001190, EnemyMetis, "EnemyMetis-1248");
				break;
			}
			case 22480: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001146);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001191, EnemyMetis, "EnemyMetis-1249");
				break;
			}
			case 22500: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001147);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001192, EnemyMetis, "EnemyMetis-1250");
				break;
			}
			case 22520: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001148);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001193, EnemyMetis, "EnemyMetis-1251");
				break;
			}
			case 22540: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001149);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001194, EnemyMetis, "EnemyMetis-1252");
				break;
			}
			case 22560: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001150);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001195, EnemyMetis, "EnemyMetis-1253");
				break;
			}
			case 22580: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001151);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001196, EnemyMetis, "EnemyMetis-1254");
				break;
			}
			case 22600: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001152);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001197, EnemyMetis, "EnemyMetis-1255");
				break;
			}
			case 22620: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001153);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001198, EnemyMetis, "EnemyMetis-1256");
				break;
			}
			case 22640: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001154);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001199, EnemyMetis, "EnemyMetis-1257");
				break;
			}
			case 22660: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001155);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001200, EnemyMetis, "EnemyMetis-1258");
				break;
			}
			case 22680: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001156);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001201, EnemyMetis, "EnemyMetis-1259");
				break;
			}
			case 22700: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001157);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001202, EnemyMetis, "EnemyMetis-1260");
				break;
			}
			case 22720: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001158);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001203, EnemyMetis, "EnemyMetis-1261");
				break;
			}
			case 22740: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001159);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001204, EnemyMetis, "EnemyMetis-1262");
				break;
			}
			case 22760: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001160);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001205, EnemyMetis, "EnemyMetis-1263");
				break;
			}
			case 22780: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001161);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001206, EnemyMetis, "EnemyMetis-1264");
				break;
			}
			case 22800: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001162);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001207, EnemyMetis, "EnemyMetis-1265");
				break;
			}
			case 22820: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001163);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001208, EnemyMetis, "EnemyMetis-1266");
				break;
			}
			case 22840: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001164);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001209, EnemyMetis, "EnemyMetis-1267");
				break;
			}
			case 22860: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001165);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001210, EnemyMetis, "EnemyMetis-1268");
				break;
			}
			case 22880: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001166);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001211, EnemyMetis, "EnemyMetis-1269");
				break;
			}
			case 22900: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001167);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001212, EnemyMetis, "EnemyMetis-1270");
				break;
			}
			case 22920: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001168);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001213, EnemyMetis, "EnemyMetis-1271");
				break;
			}
			case 22940: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001169);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001214, EnemyMetis, "EnemyMetis-1272");
				break;
			}
			case 22960: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001170);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001215, EnemyMetis, "EnemyMetis-1273");
				break;
			}
			case 22980: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001171);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001216, EnemyMetis, "EnemyMetis-1274");
				break;
			}
			case 23000: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001172);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001217, EnemyMetis, "EnemyMetis-1275");
				break;
			}
			case 23020: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001173);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001218, EnemyMetis, "EnemyMetis-1276");
				break;
			}
			case 23040: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001174);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001219, EnemyMetis, "EnemyMetis-1277");
				break;
			}
			case 23060: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001175);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001220, EnemyMetis, "EnemyMetis-1278");
				break;
			}
			case 23080: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001176);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001221, EnemyMetis, "EnemyMetis-1279");
				break;
			}
			case 23100: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001177);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001222, EnemyMetis, "EnemyMetis-1280");
				break;
			}
			case 23120: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001178);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001223, EnemyMetis, "EnemyMetis-1281");
				break;
			}
			case 23140: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001179);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001224, EnemyMetis, "EnemyMetis-1282");
				break;
			}
			case 23160: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001180);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001225, EnemyMetis, "EnemyMetis-1283");
				break;
			}
			case 23180: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001181);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001226, EnemyMetis, "EnemyMetis-1284");
				break;
			}
			case 23200: {
				EnemyHermione* p = (EnemyHermione*)obtainActorFromFactory(10000016);
				getSceneDirector()->addSubGroup(p);
				p->_X = RND(000000,1000000);
				p->_Y = RND(-600000,600000);
				p->_Z = RND(-600000,600000);
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001182);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001227, EnemyMetis, "EnemyMetis-1285");
				break;
			}
			case 23220: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001183);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001228, EnemyMetis, "EnemyMetis-1286");
				break;
			}
			case 23240: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001184);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001229, EnemyMetis, "EnemyMetis-1287");
				break;
			}
			case 23260: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001185);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001230, EnemyMetis, "EnemyMetis-1288");
				break;
			}
			case 23280: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001186);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001231, EnemyMetis, "EnemyMetis-1289");
				break;
			}
			case 23300: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001187);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001232, EnemyMetis, "EnemyMetis-1290");
				break;
			}
			case 23320: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001188);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001233, EnemyMetis, "EnemyMetis-1291");
				break;
			}
			case 23340: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001189);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001234, EnemyMetis, "EnemyMetis-1292");
				break;
			}
			case 23360: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001190);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001235, EnemyMetis, "EnemyMetis-1293");
				break;
			}
			case 23380: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001191);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001236, EnemyMetis, "EnemyMetis-1294");
				break;
			}
			case 23400: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001192);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001237, EnemyMetis, "EnemyMetis-1295");
				break;
			}
			case 23420: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001193);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001238, EnemyMetis, "EnemyMetis-1296");
				break;
			}
			case 23440: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001194);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001239, EnemyMetis, "EnemyMetis-1297");
				break;
			}
			case 23460: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001195);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001240, EnemyMetis, "EnemyMetis-1298");
				break;
			}
			case 23480: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001196);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001241, EnemyMetis, "EnemyMetis-1299");
				break;
			}
			case 23500: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001197);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001242, EnemyMetis, "EnemyMetis-1300");
				break;
			}
			case 23520: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001198);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001243, EnemyMetis, "EnemyMetis-1301");
				break;
			}
			case 23540: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001199);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001244, EnemyMetis, "EnemyMetis-1302");
				break;
			}
			case 23560: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001200);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001245, EnemyMetis, "EnemyMetis-1303");
				break;
			}
			case 23580: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001201);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001246, EnemyMetis, "EnemyMetis-1304");
				break;
			}
			case 23600: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001202);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001247, EnemyMetis, "EnemyMetis-1305");
				break;
			}
			case 23620: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001203);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001248, EnemyMetis, "EnemyMetis-1306");
				break;
			}
			case 23640: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001204);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001249, EnemyMetis, "EnemyMetis-1307");
				break;
			}
			case 23660: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001205);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001250, EnemyMetis, "EnemyMetis-1308");
				break;
			}
			case 23680: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001206);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001251, EnemyMetis, "EnemyMetis-1309");
				break;
			}
			case 23700: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001207);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001252, EnemyMetis, "EnemyMetis-1310");
				break;
			}
			case 23720: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001208);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001253, EnemyMetis, "EnemyMetis-1311");
				break;
			}
			case 23740: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001209);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001254, EnemyMetis, "EnemyMetis-1312");
				break;
			}
			case 23760: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001210);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001255, EnemyMetis, "EnemyMetis-1313");
				break;
			}
			case 23780: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001211);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001256, EnemyMetis, "EnemyMetis-1314");
				break;
			}
			case 23800: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001212);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001257, EnemyMetis, "EnemyMetis-1315");
				break;
			}
			case 23820: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001213);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001258, EnemyMetis, "EnemyMetis-1316");
				break;
			}
			case 23840: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001214);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001259, EnemyMetis, "EnemyMetis-1317");
				break;
			}
			case 23860: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001215);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001260, EnemyMetis, "EnemyMetis-1318");
				break;
			}
			case 23880: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001216);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001261, EnemyMetis, "EnemyMetis-1319");
				break;
			}
			case 23900: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001217);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001262, EnemyMetis, "EnemyMetis-1320");
				break;
			}
			case 23920: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001218);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001263, EnemyMetis, "EnemyMetis-1321");
				break;
			}
			case 23940: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001219);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001264, EnemyMetis, "EnemyMetis-1322");
				break;
			}
			case 23960: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001220);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001265, EnemyMetis, "EnemyMetis-1323");
				break;
			}
			case 23980: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001221);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001266, EnemyMetis, "EnemyMetis-1324");
				break;
			}
			case 24000: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001222);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001267, EnemyMetis, "EnemyMetis-1325");
				break;
			}
			case 24020: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001223);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001268, EnemyMetis, "EnemyMetis-1326");
				break;
			}
			case 24040: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001224);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001269, EnemyMetis, "EnemyMetis-1327");
				break;
			}
			case 24060: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001225);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001270, EnemyMetis, "EnemyMetis-1328");
				break;
			}
			case 24080: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001226);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001271, EnemyMetis, "EnemyMetis-1329");
				break;
			}
			case 24100: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001227);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001272, EnemyMetis, "EnemyMetis-1330");
				break;
			}
			case 24120: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001228);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001273, EnemyMetis, "EnemyMetis-1331");
				break;
			}
			case 24140: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001229);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001274, EnemyMetis, "EnemyMetis-1332");
				break;
			}
			case 24160: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001230);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001275, EnemyMetis, "EnemyMetis-1333");
				break;
			}
			case 24180: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001231);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001276, EnemyMetis, "EnemyMetis-1334");
				break;
			}
			case 24200: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001232);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001277, EnemyMetis, "EnemyMetis-1335");
				break;
			}
			case 24220: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001233);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001278, EnemyMetis, "EnemyMetis-1336");
				break;
			}
			case 24240: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001234);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001279, EnemyMetis, "EnemyMetis-1337");
				break;
			}
			case 24260: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001235);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001280, EnemyMetis, "EnemyMetis-1338");
				break;
			}
			case 24280: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001236);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001281, EnemyMetis, "EnemyMetis-1339");
				break;
			}
			case 24300: {
				orderActorToFactory(10000017, EnemyHermione, "EnemyHermione-1340");
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001237);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001282, EnemyMetis, "EnemyMetis-1341");
				break;
			}
			case 24320: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001238);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001283, EnemyMetis, "EnemyMetis-1342");
				break;
			}
			case 24340: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001239);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001284, EnemyMetis, "EnemyMetis-1343");
				break;
			}
			case 24360: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001240);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001285, EnemyMetis, "EnemyMetis-1344");
				break;
			}
			case 24380: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001241);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001286, EnemyMetis, "EnemyMetis-1345");
				break;
			}
			case 24400: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001242);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001287, EnemyMetis, "EnemyMetis-1346");
				break;
			}
			case 24420: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001243);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001288, EnemyMetis, "EnemyMetis-1347");
				break;
			}
			case 24440: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001244);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001289, EnemyMetis, "EnemyMetis-1348");
				break;
			}
			case 24460: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001245);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001290, EnemyMetis, "EnemyMetis-1349");
				break;
			}
			case 24480: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001246);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001291, EnemyMetis, "EnemyMetis-1350");
				break;
			}
			case 24500: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001247);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001292, EnemyMetis, "EnemyMetis-1351");
				break;
			}
			case 24520: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001248);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001293, EnemyMetis, "EnemyMetis-1352");
				break;
			}
			case 24540: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001249);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001294, EnemyMetis, "EnemyMetis-1353");
				break;
			}
			case 24560: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001250);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001295, EnemyMetis, "EnemyMetis-1354");
				break;
			}
			case 24580: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001251);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001296, EnemyMetis, "EnemyMetis-1355");
				break;
			}
			case 24600: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001252);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001297, EnemyMetis, "EnemyMetis-1356");
				break;
			}
			case 24620: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001253);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001298, EnemyMetis, "EnemyMetis-1357");
				break;
			}
			case 24640: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001254);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001299, EnemyMetis, "EnemyMetis-1358");
				break;
			}
			case 24660: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001255);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001300, EnemyMetis, "EnemyMetis-1359");
				break;
			}
			case 24680: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001256);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001301, EnemyMetis, "EnemyMetis-1360");
				break;
			}
			case 24700: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001257);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001302, EnemyMetis, "EnemyMetis-1361");
				break;
			}
			case 24720: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001258);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001303, EnemyMetis, "EnemyMetis-1362");
				break;
			}
			case 24740: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001259);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001304, EnemyMetis, "EnemyMetis-1363");
				break;
			}
			case 24760: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001260);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001305, EnemyMetis, "EnemyMetis-1364");
				break;
			}
			case 24780: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001261);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001306, EnemyMetis, "EnemyMetis-1365");
				break;
			}
			case 24800: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001262);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001307, EnemyMetis, "EnemyMetis-1366");
				break;
			}
			case 24820: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001263);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001308, EnemyMetis, "EnemyMetis-1367");
				break;
			}
			case 24840: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001264);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001309, EnemyMetis, "EnemyMetis-1368");
				break;
			}
			case 24860: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001265);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001310, EnemyMetis, "EnemyMetis-1369");
				break;
			}
			case 24880: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001266);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001311, EnemyMetis, "EnemyMetis-1370");
				break;
			}
			case 24900: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001267);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001312, EnemyMetis, "EnemyMetis-1371");
				break;
			}
			case 24920: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001268);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001313, EnemyMetis, "EnemyMetis-1372");
				break;
			}
			case 24940: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001269);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001314, EnemyMetis, "EnemyMetis-1373");
				break;
			}
			case 24960: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001270);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001315, EnemyMetis, "EnemyMetis-1374");
				break;
			}
			case 24980: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001271);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001316, EnemyMetis, "EnemyMetis-1375");
				break;
			}
			case 25000: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001272);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001317, EnemyMetis, "EnemyMetis-1376");
				break;
			}
			case 25020: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001273);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001318, EnemyMetis, "EnemyMetis-1377");
				break;
			}
			case 25040: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001274);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001319, EnemyMetis, "EnemyMetis-1378");
				break;
			}
			case 25060: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001275);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001320, EnemyMetis, "EnemyMetis-1379");
				break;
			}
			case 25080: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001276);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001321, EnemyMetis, "EnemyMetis-1380");
				break;
			}
			case 25100: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001277);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001322, EnemyMetis, "EnemyMetis-1381");
				break;
			}
			case 25120: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001278);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001323, EnemyMetis, "EnemyMetis-1382");
				break;
			}
			case 25140: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001279);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001324, EnemyMetis, "EnemyMetis-1383");
				break;
			}
			case 25160: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001280);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001325, EnemyMetis, "EnemyMetis-1384");
				break;
			}
			case 25180: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001281);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001326, EnemyMetis, "EnemyMetis-1385");
				break;
			}
			case 25200: {
				EnemyHermione* p = (EnemyHermione*)obtainActorFromFactory(10000017);
				getSceneDirector()->addSubGroup(p);
				p->_X = RND(000000,1000000);
				p->_Y = RND(-600000,600000);
				p->_Z = RND(-600000,600000);
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001282);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001327, EnemyMetis, "EnemyMetis-1386");
				break;
			}
			case 25220: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001283);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001328, EnemyMetis, "EnemyMetis-1387");
				break;
			}
			case 25240: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001284);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001329, EnemyMetis, "EnemyMetis-1388");
				break;
			}
			case 25260: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001285);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001330, EnemyMetis, "EnemyMetis-1389");
				break;
			}
			case 25280: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001286);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001331, EnemyMetis, "EnemyMetis-1390");
				break;
			}
			case 25300: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001287);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001332, EnemyMetis, "EnemyMetis-1391");
				break;
			}
			case 25320: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001288);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001333, EnemyMetis, "EnemyMetis-1392");
				break;
			}
			case 25340: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001289);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001334, EnemyMetis, "EnemyMetis-1393");
				break;
			}
			case 25360: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001290);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001335, EnemyMetis, "EnemyMetis-1394");
				break;
			}
			case 25380: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001291);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001336, EnemyMetis, "EnemyMetis-1395");
				break;
			}
			case 25400: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001292);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001337, EnemyMetis, "EnemyMetis-1396");
				break;
			}
			case 25420: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001293);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001338, EnemyMetis, "EnemyMetis-1397");
				break;
			}
			case 25440: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001294);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001339, EnemyMetis, "EnemyMetis-1398");
				break;
			}
			case 25460: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001295);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001340, EnemyMetis, "EnemyMetis-1399");
				break;
			}
			case 25480: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001296);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001341, EnemyMetis, "EnemyMetis-1400");
				break;
			}
			case 25500: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001297);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001342, EnemyMetis, "EnemyMetis-1401");
				break;
			}
			case 25520: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001298);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001343, EnemyMetis, "EnemyMetis-1402");
				break;
			}
			case 25540: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001299);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001344, EnemyMetis, "EnemyMetis-1403");
				break;
			}
			case 25560: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001300);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001345, EnemyMetis, "EnemyMetis-1404");
				break;
			}
			case 25580: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001301);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001346, EnemyMetis, "EnemyMetis-1405");
				break;
			}
			case 25600: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001302);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001347, EnemyMetis, "EnemyMetis-1406");
				break;
			}
			case 25620: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001303);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001348, EnemyMetis, "EnemyMetis-1407");
				break;
			}
			case 25640: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001304);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001349, EnemyMetis, "EnemyMetis-1408");
				break;
			}
			case 25660: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001305);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001350, EnemyMetis, "EnemyMetis-1409");
				break;
			}
			case 25680: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001306);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001351, EnemyMetis, "EnemyMetis-1410");
				break;
			}
			case 25700: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001307);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001352, EnemyMetis, "EnemyMetis-1411");
				break;
			}
			case 25720: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001308);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001353, EnemyMetis, "EnemyMetis-1412");
				break;
			}
			case 25740: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001309);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001354, EnemyMetis, "EnemyMetis-1413");
				break;
			}
			case 25760: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001310);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001355, EnemyMetis, "EnemyMetis-1414");
				break;
			}
			case 25780: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001311);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001356, EnemyMetis, "EnemyMetis-1415");
				break;
			}
			case 25800: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001312);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001357, EnemyMetis, "EnemyMetis-1416");
				break;
			}
			case 25820: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001313);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001358, EnemyMetis, "EnemyMetis-1417");
				break;
			}
			case 25840: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001314);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001359, EnemyMetis, "EnemyMetis-1418");
				break;
			}
			case 25860: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001315);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001360, EnemyMetis, "EnemyMetis-1419");
				break;
			}
			case 25880: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001316);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001361, EnemyMetis, "EnemyMetis-1420");
				break;
			}
			case 25900: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001317);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001362, EnemyMetis, "EnemyMetis-1421");
				break;
			}
			case 25920: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001318);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001363, EnemyMetis, "EnemyMetis-1422");
				break;
			}
			case 25940: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001319);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001364, EnemyMetis, "EnemyMetis-1423");
				break;
			}
			case 25960: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001320);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001365, EnemyMetis, "EnemyMetis-1424");
				break;
			}
			case 25980: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001321);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001366, EnemyMetis, "EnemyMetis-1425");
				break;
			}
			case 26000: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001322);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001367, EnemyMetis, "EnemyMetis-1426");
				break;
			}
			case 26020: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001323);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001368, EnemyMetis, "EnemyMetis-1427");
				break;
			}
			case 26040: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001324);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001369, EnemyMetis, "EnemyMetis-1428");
				break;
			}
			case 26060: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001325);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001370, EnemyMetis, "EnemyMetis-1429");
				break;
			}
			case 26080: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001326);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001371, EnemyMetis, "EnemyMetis-1430");
				break;
			}
			case 26100: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001327);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001372, EnemyMetis, "EnemyMetis-1431");
				break;
			}
			case 26120: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001328);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001373, EnemyMetis, "EnemyMetis-1432");
				break;
			}
			case 26140: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001329);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001374, EnemyMetis, "EnemyMetis-1433");
				break;
			}
			case 26160: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001330);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001375, EnemyMetis, "EnemyMetis-1434");
				break;
			}
			case 26180: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001331);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001376, EnemyMetis, "EnemyMetis-1435");
				break;
			}
			case 26200: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001332);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001377, EnemyMetis, "EnemyMetis-1436");
				break;
			}
			case 26220: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001333);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001378, EnemyMetis, "EnemyMetis-1437");
				break;
			}
			case 26240: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001334);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001379, EnemyMetis, "EnemyMetis-1438");
				break;
			}
			case 26260: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001335);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001380, EnemyMetis, "EnemyMetis-1439");
				break;
			}
			case 26280: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001336);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001381, EnemyMetis, "EnemyMetis-1440");
				break;
			}
			case 26300: {
				orderActorToFactory(10000018, EnemyHermione, "EnemyHermione-1441");
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001337);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001382, EnemyMetis, "EnemyMetis-1442");
				break;
			}
			case 26320: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001338);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001383, EnemyMetis, "EnemyMetis-1443");
				break;
			}
			case 26340: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001339);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001384, EnemyMetis, "EnemyMetis-1444");
				break;
			}
			case 26360: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001340);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001385, EnemyMetis, "EnemyMetis-1445");
				break;
			}
			case 26380: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001341);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001386, EnemyMetis, "EnemyMetis-1446");
				break;
			}
			case 26400: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001342);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001387, EnemyMetis, "EnemyMetis-1447");
				break;
			}
			case 26420: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001343);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001388, EnemyMetis, "EnemyMetis-1448");
				break;
			}
			case 26440: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001344);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001389, EnemyMetis, "EnemyMetis-1449");
				break;
			}
			case 26460: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001345);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001390, EnemyMetis, "EnemyMetis-1450");
				break;
			}
			case 26480: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001346);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001391, EnemyMetis, "EnemyMetis-1451");
				break;
			}
			case 26500: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001347);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001392, EnemyMetis, "EnemyMetis-1452");
				break;
			}
			case 26520: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001348);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001393, EnemyMetis, "EnemyMetis-1453");
				break;
			}
			case 26540: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001349);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001394, EnemyMetis, "EnemyMetis-1454");
				break;
			}
			case 26560: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001350);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001395, EnemyMetis, "EnemyMetis-1455");
				break;
			}
			case 26580: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001351);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001396, EnemyMetis, "EnemyMetis-1456");
				break;
			}
			case 26600: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001352);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001397, EnemyMetis, "EnemyMetis-1457");
				break;
			}
			case 26620: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001353);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001398, EnemyMetis, "EnemyMetis-1458");
				break;
			}
			case 26640: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001354);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001399, EnemyMetis, "EnemyMetis-1459");
				break;
			}
			case 26660: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001355);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001400, EnemyMetis, "EnemyMetis-1460");
				break;
			}
			case 26680: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001356);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001401, EnemyMetis, "EnemyMetis-1461");
				break;
			}
			case 26700: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001357);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001402, EnemyMetis, "EnemyMetis-1462");
				break;
			}
			case 26720: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001358);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001403, EnemyMetis, "EnemyMetis-1463");
				break;
			}
			case 26740: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001359);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001404, EnemyMetis, "EnemyMetis-1464");
				break;
			}
			case 26760: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001360);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001405, EnemyMetis, "EnemyMetis-1465");
				break;
			}
			case 26780: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001361);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001406, EnemyMetis, "EnemyMetis-1466");
				break;
			}
			case 26800: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001362);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001407, EnemyMetis, "EnemyMetis-1467");
				break;
			}
			case 26820: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001363);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001408, EnemyMetis, "EnemyMetis-1468");
				break;
			}
			case 26840: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001364);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001409, EnemyMetis, "EnemyMetis-1469");
				break;
			}
			case 26860: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001365);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001410, EnemyMetis, "EnemyMetis-1470");
				break;
			}
			case 26880: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001366);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001411, EnemyMetis, "EnemyMetis-1471");
				break;
			}
			case 26900: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001367);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001412, EnemyMetis, "EnemyMetis-1472");
				break;
			}
			case 26920: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001368);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001413, EnemyMetis, "EnemyMetis-1473");
				break;
			}
			case 26940: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001369);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001414, EnemyMetis, "EnemyMetis-1474");
				break;
			}
			case 26960: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001370);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001415, EnemyMetis, "EnemyMetis-1475");
				break;
			}
			case 26980: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001371);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001416, EnemyMetis, "EnemyMetis-1476");
				break;
			}
			case 27000: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001372);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001417, EnemyMetis, "EnemyMetis-1477");
				break;
			}
			case 27020: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001373);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001418, EnemyMetis, "EnemyMetis-1478");
				break;
			}
			case 27040: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001374);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001419, EnemyMetis, "EnemyMetis-1479");
				break;
			}
			case 27060: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001375);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001420, EnemyMetis, "EnemyMetis-1480");
				break;
			}
			case 27080: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001376);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001421, EnemyMetis, "EnemyMetis-1481");
				break;
			}
			case 27100: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001377);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001422, EnemyMetis, "EnemyMetis-1482");
				break;
			}
			case 27120: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001378);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001423, EnemyMetis, "EnemyMetis-1483");
				break;
			}
			case 27140: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001379);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001424, EnemyMetis, "EnemyMetis-1484");
				break;
			}
			case 27160: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001380);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001425, EnemyMetis, "EnemyMetis-1485");
				break;
			}
			case 27180: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001381);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001426, EnemyMetis, "EnemyMetis-1486");
				break;
			}
			case 27200: {
				EnemyHermione* p = (EnemyHermione*)obtainActorFromFactory(10000018);
				getSceneDirector()->addSubGroup(p);
				p->_X = RND(000000,1000000);
				p->_Y = RND(-600000,600000);
				p->_Z = RND(-600000,600000);
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001382);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001427, EnemyMetis, "EnemyMetis-1487");
				break;
			}
			case 27220: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001383);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001428, EnemyMetis, "EnemyMetis-1488");
				break;
			}
			case 27240: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001384);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001429, EnemyMetis, "EnemyMetis-1489");
				break;
			}
			case 27260: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001385);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001430, EnemyMetis, "EnemyMetis-1490");
				break;
			}
			case 27280: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001386);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001431, EnemyMetis, "EnemyMetis-1491");
				break;
			}
			case 27300: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001387);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001432, EnemyMetis, "EnemyMetis-1492");
				break;
			}
			case 27320: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001388);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001433, EnemyMetis, "EnemyMetis-1493");
				break;
			}
			case 27340: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001389);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001434, EnemyMetis, "EnemyMetis-1494");
				break;
			}
			case 27360: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001390);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001435, EnemyMetis, "EnemyMetis-1495");
				break;
			}
			case 27380: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001391);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001436, EnemyMetis, "EnemyMetis-1496");
				break;
			}
			case 27400: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001392);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001437, EnemyMetis, "EnemyMetis-1497");
				break;
			}
			case 27420: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001393);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001438, EnemyMetis, "EnemyMetis-1498");
				break;
			}
			case 27440: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001394);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001439, EnemyMetis, "EnemyMetis-1499");
				break;
			}
			case 27460: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001395);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001440, EnemyMetis, "EnemyMetis-1500");
				break;
			}
			case 27480: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001396);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001441, EnemyMetis, "EnemyMetis-1501");
				break;
			}
			case 27500: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001397);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001442, EnemyMetis, "EnemyMetis-1502");
				break;
			}
			case 27520: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001398);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001443, EnemyMetis, "EnemyMetis-1503");
				break;
			}
			case 27540: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001399);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001444, EnemyMetis, "EnemyMetis-1504");
				break;
			}
			case 27560: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001400);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001445, EnemyMetis, "EnemyMetis-1505");
				break;
			}
			case 27580: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001401);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001446, EnemyMetis, "EnemyMetis-1506");
				break;
			}
			case 27600: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001402);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001447, EnemyMetis, "EnemyMetis-1507");
				break;
			}
			case 27620: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001403);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001448, EnemyMetis, "EnemyMetis-1508");
				break;
			}
			case 27640: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001404);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001449, EnemyMetis, "EnemyMetis-1509");
				break;
			}
			case 27660: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001405);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001450, EnemyMetis, "EnemyMetis-1510");
				break;
			}
			case 27680: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001406);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001451, EnemyMetis, "EnemyMetis-1511");
				break;
			}
			case 27700: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001407);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001452, EnemyMetis, "EnemyMetis-1512");
				break;
			}
			case 27720: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001408);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001453, EnemyMetis, "EnemyMetis-1513");
				break;
			}
			case 27740: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001409);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001454, EnemyMetis, "EnemyMetis-1514");
				break;
			}
			case 27760: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001410);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001455, EnemyMetis, "EnemyMetis-1515");
				break;
			}
			case 27780: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001411);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001456, EnemyMetis, "EnemyMetis-1516");
				break;
			}
			case 27800: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001412);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001457, EnemyMetis, "EnemyMetis-1517");
				break;
			}
			case 27820: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001413);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001458, EnemyMetis, "EnemyMetis-1518");
				break;
			}
			case 27840: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001414);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001459, EnemyMetis, "EnemyMetis-1519");
				break;
			}
			case 27860: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001415);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001460, EnemyMetis, "EnemyMetis-1520");
				break;
			}
			case 27880: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001416);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001461, EnemyMetis, "EnemyMetis-1521");
				break;
			}
			case 27900: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001417);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001462, EnemyMetis, "EnemyMetis-1522");
				break;
			}
			case 27920: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001418);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001463, EnemyMetis, "EnemyMetis-1523");
				break;
			}
			case 27940: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001419);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001464, EnemyMetis, "EnemyMetis-1524");
				break;
			}
			case 27960: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001420);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001465, EnemyMetis, "EnemyMetis-1525");
				break;
			}
			case 27980: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001421);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001466, EnemyMetis, "EnemyMetis-1526");
				break;
			}
			case 28000: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001422);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001467, EnemyMetis, "EnemyMetis-1527");
				break;
			}
			case 28020: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001423);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001468, EnemyMetis, "EnemyMetis-1528");
				break;
			}
			case 28040: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001424);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001469, EnemyMetis, "EnemyMetis-1529");
				break;
			}
			case 28060: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001425);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001470, EnemyMetis, "EnemyMetis-1530");
				break;
			}
			case 28080: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001426);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001471, EnemyMetis, "EnemyMetis-1531");
				break;
			}
			case 28100: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001427);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001472, EnemyMetis, "EnemyMetis-1532");
				break;
			}
			case 28120: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001428);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001473, EnemyMetis, "EnemyMetis-1533");
				break;
			}
			case 28140: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001429);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001474, EnemyMetis, "EnemyMetis-1534");
				break;
			}
			case 28160: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001430);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001475, EnemyMetis, "EnemyMetis-1535");
				break;
			}
			case 28180: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001431);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001476, EnemyMetis, "EnemyMetis-1536");
				break;
			}
			case 28200: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001432);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001477, EnemyMetis, "EnemyMetis-1537");
				break;
			}
			case 28220: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001433);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001478, EnemyMetis, "EnemyMetis-1538");
				break;
			}
			case 28240: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001434);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001479, EnemyMetis, "EnemyMetis-1539");
				break;
			}
			case 28260: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001435);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001480, EnemyMetis, "EnemyMetis-1540");
				break;
			}
			case 28280: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001436);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001481, EnemyMetis, "EnemyMetis-1541");
				break;
			}
			case 28300: {
				orderActorToFactory(10000019, EnemyHermione, "EnemyHermione-1542");
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001437);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001482, EnemyMetis, "EnemyMetis-1543");
				break;
			}
			case 28320: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001438);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001483, EnemyMetis, "EnemyMetis-1544");
				break;
			}
			case 28340: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001439);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001484, EnemyMetis, "EnemyMetis-1545");
				break;
			}
			case 28360: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001440);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001485, EnemyMetis, "EnemyMetis-1546");
				break;
			}
			case 28380: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001441);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001486, EnemyMetis, "EnemyMetis-1547");
				break;
			}
			case 28400: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001442);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001487, EnemyMetis, "EnemyMetis-1548");
				break;
			}
			case 28420: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001443);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001488, EnemyMetis, "EnemyMetis-1549");
				break;
			}
			case 28440: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001444);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001489, EnemyMetis, "EnemyMetis-1550");
				break;
			}
			case 28460: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001445);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001490, EnemyMetis, "EnemyMetis-1551");
				break;
			}
			case 28480: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001446);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001491, EnemyMetis, "EnemyMetis-1552");
				break;
			}
			case 28500: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001447);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001492, EnemyMetis, "EnemyMetis-1553");
				break;
			}
			case 28520: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001448);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001493, EnemyMetis, "EnemyMetis-1554");
				break;
			}
			case 28540: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001449);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001494, EnemyMetis, "EnemyMetis-1555");
				break;
			}
			case 28560: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001450);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001495, EnemyMetis, "EnemyMetis-1556");
				break;
			}
			case 28580: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001451);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001496, EnemyMetis, "EnemyMetis-1557");
				break;
			}
			case 28600: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001452);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001497, EnemyMetis, "EnemyMetis-1558");
				break;
			}
			case 28620: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001453);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001498, EnemyMetis, "EnemyMetis-1559");
				break;
			}
			case 28640: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001454);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001499, EnemyMetis, "EnemyMetis-1560");
				break;
			}
			case 28660: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001455);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001500, EnemyMetis, "EnemyMetis-1561");
				break;
			}
			case 28680: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001456);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001501, EnemyMetis, "EnemyMetis-1562");
				break;
			}
			case 28700: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001457);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001502, EnemyMetis, "EnemyMetis-1563");
				break;
			}
			case 28720: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001458);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001503, EnemyMetis, "EnemyMetis-1564");
				break;
			}
			case 28740: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001459);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001504, EnemyMetis, "EnemyMetis-1565");
				break;
			}
			case 28760: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001460);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001505, EnemyMetis, "EnemyMetis-1566");
				break;
			}
			case 28780: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001461);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001506, EnemyMetis, "EnemyMetis-1567");
				break;
			}
			case 28800: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001462);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001507, EnemyMetis, "EnemyMetis-1568");
				break;
			}
			case 28820: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001463);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001508, EnemyMetis, "EnemyMetis-1569");
				break;
			}
			case 28840: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001464);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001509, EnemyMetis, "EnemyMetis-1570");
				break;
			}
			case 28860: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001465);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001510, EnemyMetis, "EnemyMetis-1571");
				break;
			}
			case 28880: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001466);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001511, EnemyMetis, "EnemyMetis-1572");
				break;
			}
			case 28900: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001467);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001512, EnemyMetis, "EnemyMetis-1573");
				break;
			}
			case 28920: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001468);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001513, EnemyMetis, "EnemyMetis-1574");
				break;
			}
			case 28940: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001469);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001514, EnemyMetis, "EnemyMetis-1575");
				break;
			}
			case 28960: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001470);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001515, EnemyMetis, "EnemyMetis-1576");
				break;
			}
			case 28980: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001471);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001516, EnemyMetis, "EnemyMetis-1577");
				break;
			}
			case 29000: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001472);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001517, EnemyMetis, "EnemyMetis-1578");
				break;
			}
			case 29020: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001473);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001518, EnemyMetis, "EnemyMetis-1579");
				break;
			}
			case 29040: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001474);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001519, EnemyMetis, "EnemyMetis-1580");
				break;
			}
			case 29060: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001475);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001520, EnemyMetis, "EnemyMetis-1581");
				break;
			}
			case 29080: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001476);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001521, EnemyMetis, "EnemyMetis-1582");
				break;
			}
			case 29100: {
				orderSceneToFactory(10000003, Stage01_Climax, "Stage01_Climax-1583");
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001477);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(10001522, EnemyMetis, "EnemyMetis-1584");
				break;
			}
			case 29120: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001478);
				getSceneDirector()->addSubGroup(pMetis);
				break;
			}
			case 29140: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001479);
				getSceneDirector()->addSubGroup(pMetis);
				break;
			}
			case 29160: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001480);
				getSceneDirector()->addSubGroup(pMetis);
				break;
			}
			case 29180: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001481);
				getSceneDirector()->addSubGroup(pMetis);
				break;
			}
			case 29200: {
				EnemyHermione* p = (EnemyHermione*)obtainActorFromFactory(10000019);
				getSceneDirector()->addSubGroup(p);
				p->_X = RND(000000,1000000);
				p->_Y = RND(-600000,600000);
				p->_Z = RND(-600000,600000);
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001482);
				getSceneDirector()->addSubGroup(pMetis);
				break;
			}
			case 29220: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001483);
				getSceneDirector()->addSubGroup(pMetis);
				break;
			}
			case 29240: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001484);
				getSceneDirector()->addSubGroup(pMetis);
				break;
			}
			case 29260: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001485);
				getSceneDirector()->addSubGroup(pMetis);
				break;
			}
			case 29280: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001486);
				getSceneDirector()->addSubGroup(pMetis);
				break;
			}
			case 29300: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001487);
				getSceneDirector()->addSubGroup(pMetis);
				break;
			}
			case 29320: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001488);
				getSceneDirector()->addSubGroup(pMetis);
				break;
			}
			case 29340: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001489);
				getSceneDirector()->addSubGroup(pMetis);
				break;
			}
			case 29360: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001490);
				getSceneDirector()->addSubGroup(pMetis);
				break;
			}
			case 29380: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001491);
				getSceneDirector()->addSubGroup(pMetis);
				break;
			}
			case 29400: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001492);
				getSceneDirector()->addSubGroup(pMetis);
				break;
			}
			case 29420: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001493);
				getSceneDirector()->addSubGroup(pMetis);
				break;
			}
			case 29440: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001494);
				getSceneDirector()->addSubGroup(pMetis);
				break;
			}
			case 29460: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001495);
				getSceneDirector()->addSubGroup(pMetis);
				break;
			}
			case 29480: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001496);
				getSceneDirector()->addSubGroup(pMetis);
				break;
			}
			case 29500: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001497);
				getSceneDirector()->addSubGroup(pMetis);
				break;
			}
			case 29520: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001498);
				getSceneDirector()->addSubGroup(pMetis);
				break;
			}
			case 29540: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001499);
				getSceneDirector()->addSubGroup(pMetis);
				break;
			}
			case 29560: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001500);
				getSceneDirector()->addSubGroup(pMetis);
				break;
			}
			case 29580: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001501);
				getSceneDirector()->addSubGroup(pMetis);
				break;
			}
			case 29600: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001502);
				getSceneDirector()->addSubGroup(pMetis);
				break;
			}
			case 29620: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001503);
				getSceneDirector()->addSubGroup(pMetis);
				break;
			}
			case 29640: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001504);
				getSceneDirector()->addSubGroup(pMetis);
				break;
			}
			case 29660: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001505);
				getSceneDirector()->addSubGroup(pMetis);
				break;
			}
			case 29680: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001506);
				getSceneDirector()->addSubGroup(pMetis);
				break;
			}
			case 29700: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001507);
				getSceneDirector()->addSubGroup(pMetis);
				break;
			}
			case 29720: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001508);
				getSceneDirector()->addSubGroup(pMetis);
				break;
			}
			case 29740: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001509);
				getSceneDirector()->addSubGroup(pMetis);
				break;
			}
			case 29760: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001510);
				getSceneDirector()->addSubGroup(pMetis);
				break;
			}
			case 29780: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001511);
				getSceneDirector()->addSubGroup(pMetis);
				break;
			}
			case 29800: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001512);
				getSceneDirector()->addSubGroup(pMetis);
				break;
			}
			case 29820: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001513);
				getSceneDirector()->addSubGroup(pMetis);
				break;
			}
			case 29840: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001514);
				getSceneDirector()->addSubGroup(pMetis);
				break;
			}
			case 29860: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001515);
				getSceneDirector()->addSubGroup(pMetis);
				break;
			}
			case 29880: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001516);
				getSceneDirector()->addSubGroup(pMetis);
				break;
			}
			case 29900: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001517);
				getSceneDirector()->addSubGroup(pMetis);
				break;
			}
			case 29920: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001518);
				getSceneDirector()->addSubGroup(pMetis);
				break;
			}
			case 29940: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001519);
				getSceneDirector()->addSubGroup(pMetis);
				break;
			}
			case 29960: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001520);
				getSceneDirector()->addSubGroup(pMetis);
				break;
			}
			case 29980: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001521);
				getSceneDirector()->addSubGroup(pMetis);
				break;
			}
			case 30000: {
				Stage01_Climax* pScene = (Stage01_Climax*)obtainSceneFromFactory(10000003);
				addSubLast(pScene);
				_pBgmPerformer->fadeout_stop(2);
				_pBgmPerformer->play_fadein(3);
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10001522);
				getSceneDirector()->addSubGroup(pMetis);
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 1527-1 ? _cnt_event+1 : _cnt_event);
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
        ((Stage01_01*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STG01_02_WAS_BROKEN) {
        _TRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_02_WAS_BROKEN");
        ((Stage01_02*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STG01_03_WAS_BROKEN) {
        _TRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_03_WAS_BROKEN");
        ((Stage01_03*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STG01_WALLED_WAS_BROKEN) {
        _TRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_WALLED_WAS_BROKEN");
        ((Stage01WalledScene*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STG01_CLIMAX_WAS_BROKEN) {
        _TRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_CLIMAX_WAS_BROKENキャッチした。STAGE01PARTCONTROLLER_ENDINGを投げる");
        ((Stage01_Climax*)prm_pSource)->sayonara(60*60);
        _pProg->change(PROG_FAINAL); //進捗をStage01PartController::PROG_FAINALに切り替える
    } else {

    }

}

Stage01PartController::~Stage01PartController() {

}
