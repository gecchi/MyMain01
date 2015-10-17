#include "Stage01PartController.h"

#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/dxcore/scene/supporter/GgafDxBgmPerformerForScene.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "../Stage01.h"
#include "part/Stage01_01.h"
#include "part/Stage01_02.h"
#include "part/Stage01_03.h"
#include "part/Stage01_Climax.h"
#include "part/Stage01WalledScene.h"

#include "jp/gecchi/VioletVreath/actor/_predrawer/DefaultMeshTestActor.h"


using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Stage01PartController::Stage01PartController(const char* prm_name) : StagePartController(prm_name) {
    _class_name = "Stage01PartController";

    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
	frame f[] = {1,10,20,40,70,100,130,160,190,200,220,250,280,300,310,340,370,400,430,460,490,500,520,550,580,600,610,620,640,670,700,730,760,790,800,820,850,880,900,910,940,970,1000,1030,1060,1090,1100,1120,1150,1180,1200,1210,1240,1270,1300,1330,1360,1390,1400,1420,1450,1480,1500,1510,1540,1570,1600,1630,1660,1690,1700,1720,1750,1780,1800,1810,1840,1870,1900,1930,1960,1990,2000,2020,2050,2080,2100,2110,2140,2170,2200,2230,2260,2290,2300,2320,2350,2380,2400,2410,2440,2470,2500,2530,2560,2590,2600,2620,2650,2680,2700,2710,2740,2770,2800,2830,2860,2890,2900,2920,2950,2980,3000,3010,3040,3070,3100,3130,3160,3190,3200,3220,3250,3280,3300,3310,3340,3370,3400,3430,3460,3490,3500,3520,3550,3580,3600,3610,3640,3670,3700,3730,3760,3790,3800,3820,3850,3880,3900,3910,3940,3970,4000,4030,4060,4090,4100,4120,4150,4180,4200,4210,4240,4270,4300,4330,4360,4390,4400,4420,4450,4480,4500,4510,4540,4570,4600,4630,4660,4690,4700,4720,4750,4780,4800,4810,4840,4870,4900,4930,4960,4990,5000,5020,5050,5080,5100,5110,5140,5170,5200,5230,5260,5290,5300,5320,5350,5380,5400,5410,5440,5470,5500,5530,5560,5590,5600,5620,5650,5680,5700,5710,5740,5770,5800,5830,5860,5890,5900,5920,5950,5980,6000,6010,6040,6070,6100,6130,6160,6190,6200,6220,6250,6280,6300,6310,6340,6370,6400,6430,6460,6490,6500,6520,6550,6580,6600,6610,6640,6670,6700,6730,6760,6790,6800,6820,6850,6880,6900,6910,6940,6970,7000,7030,7060,7090,7100,7120,7150,7180,7200,7210,7240,7270,7300,7330,7360,7390,7400,7420,7450,7480,7500,7510,7540,7570,7600,7630,7660,7690,7700,7720,7750,7780,7800,7810,7840,7870,7900,7930,7960,7990,8000,8020,8050,8080,8100,8110,8140,8170,8200,8230,8260,8290,8300,8320,8350,8380,8400,8410,8440,8470,8500,8530,8560,8590,8600,8620,8650,8680,8700,8710,8740,8770,8800,8830,8860,8890,8900,8920,8950,8980,9000,9010,9040,9070,9100,9130,9160,9190,9200,9220,9250,9280,9300,9310,9340,9370,9400,9430,9460,9490,9500,9520,9550,9580,9600,9610,9640,9670,9700,9730,9760,9790,9800,9820,9850,9880,9900,9910,9940,9970,10000,10030,10060,10090,10100,10120,10150,10180,10200,10210,10240,10270,10300,10330,10360,10390,10400,10420,10450,10480,10500,10510,10540,10570,10600,10630,10660,10690,10700,10720,10750,10780,10800,10810,10840,10870,10900,10930,10960,10990,11000,11020,11050,11080,11100,11110,11140,11170,11200,11230,11260,11290,11300,11320,11350,11380,11400,11410,11440,11470,11500,11530,11560,11590,11600,11620,11650,11680,11700,11710,11740,11770,11800,11830,11860,11890,11900,11920,11950,11980,12000,12010,12040,12070,12100,12130,12160,12190,12200,12220,12250,12280,12300,12310,12340,12370,12400,12430,12460,12490,12500,12520,12550,12580,12600,12610,12640,12670,12700,12730,12760,12790,12800,12820,12850,12880,12900,12910,12940,12970,13000,13030,13060,13090,13100,13120,13150,13180,13200,13210,13240,13270,13300,13330,13360,13390,13400,13420,13450,13480,13500,13510,13540,13570,13600,13630,13660,13690,13700,13720,13750,13780,13800,13810,13840,13870,13900,13930,13960,13990,14000,14020,14050,14080,14100,14110,14140,14170,14200,14230,14260,14290,14300,14320,14350,14380,14400,14410,14440,14470,14500,14530,14560,14590,14600,14620,14650,14680,14700,14710,14740,14770,14800,14830,14860,14890,14900,14920,14950,14980,15000,15010,15040,15070,15100,15130,15160,15190,15200,15220,15250,15280,15300,15310,15340,15370,15400,15430,15460,15490,15500,15520,15550,15580,15600,15610,15640,15670,15700,15730,15760,15790,15800,15820,15850,15880,15900,15910,15940,15970,16000,16030,16060,16090,16100,16120,16150,16180,16200,16210,16240,16270,16300,16330,16360,16390,16400,16420,16450,16480,16500,16510,16540,16570,16600,16630,16660,16690,16700,16720,16750,16780,16800,16810,16840,16870,16900,16930,16960,16990,17000,17020,17050,17080,17100,17110,17140,17170,17200,17230,17260,17290,17300,17320,17350,17380,17400,17410,17440,17470,17500,17530,17560,17590,17600,17620,17650,17680,17700,17710,17740,17770,17800,17830,17860,17890,17900,17920,17950,17980,18000,18010,18040,18070,18100,18130,18160,18190,18200,18220,18250,18280,18300,18310,18340,18370,18400,18430,18460,18490,18500,18520,18550,18580,18600,18610,18640,18670,18700,18730,18760,18790,18800,18820,18850,18880,18900,18910,18940,18970,19000,19030,19060,19090,19100,19120,19150,19180,19200,19210,19240,19270,19300,19330,19360,19390,19400,19420,19450,19480,19500,19510,19540,19570,19600,19630,19660,19690,19700,19720,19750,19780,19800,19810,19840,19870,19900,19930,19960,19990,20000,20020,20050,20080,20100,20110,20140,20170,20200,20230,20260,20290,20300,20320,20350,20380,20400,20410,20440,20470,20500,20530,20560,20590,20600,20620,20650,20680,20700,20710,20740,20770,20800,20830,20860,20890,20900,20920,20950,20980,21000,21010,21040,21070,21100,21130,21160,21190,21200,21220,21250,21280,21300,21310,21340,21370,21400,21430,21460,21490,21500,21520,21550,21580,21600,21610,21640,21670,21700,21730,21760,21790,21800,21820,21850,21880,21900,21910,21940,21970,22000,22030,22060,22090,22100,22120,22150,22180,22200,22210,22240,22270,22300,22330,22360,22390,22400,22420,22450,22480,22500,22510,22540,22570,22600,22630,22660,22690,22700,22720,22750,22780,22800,22810,22840,22870,22900,22930,22960,22990,23000,23020,23050,23080,23100,23110,23140,23170,23200,23230,23260,23290,23300,23320,23350,23380,23400,23410,23440,23470,23500,23530,23560,23590,23600,23620,23650,23680,23700,23710,23740,23770,23800,23830,23860,23890,23900,23920,23950,23980,24000,24010,24040,24070,24100,24130,24160,24190,24200,24220,24250,24280,24300,24310,24340,24370,24400,24430,24460,24490,24500,24520,24550,24580,24600,24610,24640,24670,24700,24730,24760,24790,24800,24820,24850,24880,24900,24910,24940,24970,25000,25030,25060,25090,25100,25120,25150,25180,25200,25210,25240,25270,25300,25330,25360,25390,25400,25420,25450,25480,25500,25510,25540,25570,25600,25630,25660,25690,25700,25720,25750,25780,25800,25810,25840,25870,25900,25930,25960,25990,26000,26020,26050,26080,26100,26110,26140,26170,26200,26230,26260,26290,26300,26320,26350,26380,26400,26410,26440,26470,26500,26530,26560,26590,26600,26620,26650,26680,26700,26710,26740,26770,26800,26830,26860,26890,26900,26920,26950,26980,27000,27010,27040,27070,27100,27130,27160,27190,27200,27220,27250,27280,27300,27310,27340,27370,27400,27430,27460,27490,27500,27520,27550,27580,27600,27610,27640,27670,27700,27730,27760,27790,27800,27820,27850,27880,27900,27910,27940,27970,28000,28030,28060,28090,28100,28120,28150,28180,28200,28210,28240,28270,28300,28330,28360,28390,28400,28420,28450,28480,28500,28510,28540,28570,28600,28630,28660,28690,28700,28720,28750,28780,28800,28810,28840,28870,28900,28930,28960,28990,29000,29020,29050,29080,29100,29110,29140,29170,29200,29230,29260,29290,29300,29320,29350,29380,29400,29410,29440,29470,29500,29530,29560,29590,29600,29620,29650,29680,29700,29710,29740,29770,29800,29830,29860,29890,29900,29920,29950,29980,30000,30010,30040,30070,30100,30130,30160,30190,30200,30220,30250,30280,30300,30310,30340,30370,30400,30430,30460,30490,30500,30520,30550,30580,30600,30610,30640,30670,30700,30730,30760,30790,30800,30820,30850,30880,30900,30910,30940,30970,31000,31030,31060,31090,31100,31120,31150,31180,31200,31210,31240,31270,31300,31330,31360,31390,31400,31420,31450,31480,31500,31510,31540,31570,31600,31630,31660,31690,31700,31720,31750,31780,31800,31810,31840,31870,31900,31930,31960,31990,32000,32020,32050,32080,32100,32110,32140,32170,32200,32230,32260,32290,32300,32320,32350,32380,32400,32410,32440,32470,32500,32530,32560,32590,32600,32620,32650,32680,32700,32710,32740,32770,32800,32830,32860,32890,32900,32920,32950,32980,33000,33010,33040,33070,33100,33130,33160,33190,33200,33220,33250,33280,33300,33310,33340,33370,33400,33430,33460,33490,33500,33520,33550,33580,33600,33610,33640,33670,33700,33730,33760,33790,33800,33820,33850,33880,33900,33910,33940,33970,34000,34030,34060,34090,34100,34120,34150,34180,34200,34210,34240,34270,34300,34330,34360,34390,34400,34420,34450,34480,34500,34510,34540,34570,34600,34630,34660,34690,34700,34720,34750,34780,34800,34810,34840,34870,34900,34930,34960,34990,35000,35020,35050,35080,35100,35110,35140,35170,35200,35230,35260,35290,35300,35320,35350,35380,35400,35410,35440,35470,35500,35530,35560,35590,35600,35620,35650,35680,35700,35710,35740,35770,35800,35830,35860,35890,35900,35920,35950,35980,36000,36010,36040,36070,36100,36130,36160,36190,36200,36220,36250,36280,36300,36310,36340,36370,36400,36430,36460,36490,36500,36520,36550,36580,36600,36610,36640,36670,36700,36730,36760,36790,36800,36820,36850,36880,36900,36910,36940,36970,37000,37030,37060,37090,37100,37120,37150,37180,37200,37210,37240,37270,37300,37330,37360,37390,37400,37420,37450,37480,37500,37510,37540,37570,37600,37630,37660,37690,37700,37720,37750,37780,37800,37810,37840,37870,37900,37930,37960,37990,38000,38020,38050,38080,38100,38110,38140,38170,38200,38230,38260,38290,38300,38320,38350,38380,38400,38410,38440,38470,38500,38530,38560,38590,38600,38620,38650,38680,38700,38710,38740,38770,38800,38830,38860,38890,38900,38920,38950,38980,39000,39010,39040,39070,39100,39130,39160,39190,39200,39220,39250,39280,39300,39310,39340,39370,39400,39430,39460,39490,39500,39520,39550,39580,39600,39610,39640,39670,39700,39730,39760,39790,39800,39820,39850,39880,39900,39910,39940,39970,40000,40030,40060,40090,40100,40120,40150,40180,40200,40210,40240,40270,40300,40330,40360,40390,40400,40420,40450,40480,40500,40510,40540,40570,40600,40630,40660,40690,40700,40720,40750,40780,40800,40810,40840,40870,40900,40930,40960,40990,41000,41020,41050,41080,41100,41110,41140,41170,41200,41230,41260,41290,41300,41320,41350,41380,41400,41410,41440,41470,41500,41530,41560,41590,41600,41620,41650,41680,41700,41710,41740,41770,41800,41830,41860,41890,41900,41920,41950,41980,42000,42010,42040,42070,42100,42130,42160,42190,42200,42220,42250,42280,42300,42310,42340,42370,42400,42430,42460,42490,42500,42520,42550,42580,42600,42610,42640,42670,42700,42730,42760,42790,42800,42820,42850,42880,42900,42910,42940,42970,43000,43030,43060,43090,43100,43120,43150,43180,43200,43210,43240,43270,43300,43330,43360,43390,43400,43420,43450,43480,43500,43510,43540,43570,43600,43630,43660,43690,43700,43720,43750,43780,43800,43810,43840,43870,43900,43930,43960,43990,44000,44020,44050,44080,44100,44110,44140,44170,44200,44230,44260,44290,44300,44320,44350,44380,44400,44410,44440,44470,44500,44530,44560,44590,44600,44620,44650,44680,44700,44710,44740,44770,44800,44830,44860,44890,44900,44920,44950,44980,45000,45010,45040,45070,45100,45130,45160,45190,45200,45220,45250,45280,45300,45310,45340,45370,45400,45430,45460,45490,45500,45520,45550,45580,45600,45610,45640,45670,45700,45730,45760,45790,45800,45820,45850,45880,45900,45910,45940,45970,46000,46030,46060,46090,46100,46120,46150,46180,46200,46210,46240,46270,46300,46330,46360,46390,46400,46420,46450,46480,46500,46510,46540,46570,46600,46630,46660,46690,46700,46720,46750,46780,46800,46810,46840,46870,46900,46930,46960,46990,47000,47020,47050,47080,47100,47110,47140,47170,47200,47230,47260,47290,47300,47320,47350,47380,47400,47410,47440,47470,47500,47530,47560,47590,47600,47620,47650,47680,47700,47710,47740,47770,47800,47830,47860,47890,47900,47920,47950,47980,48000,48010,48040,48070,48100,48130,48160,48190,48200,48220,48250,48280,48300,48310,48340,48370,48400,48430,48460,48490,48500,48520,48550,48580,48600,48610,48640,48670,48700,48730,48760,48790,48800,48820,48850,48880,48900,48910,48940,48970,49000,49030,49060,49090,49100,49120,49150,49180,49200,49210,49240,49270,49300,49330,49360,49390,49400,49420,49450,49480,49500,49510,49540,49570,49600,49630,49660,49690,49700,49720,49750,49780,49800,49810,49840,49870,49900,49930,49960,49990,50000};
	_paFrame_NextEvent = new frame[2003];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 2003;
	orderActorToFactory(10000000, EnemyOebiusController001, "EnemyOebiusController001-1");
	orderActorToFactory(10000002, EnemyErmione, "EnemyErmione-2");
	orderActorToFactory(10000012, EnemyEtis, "EnemyEtis-3");
	orderActorToFactory(10000013, EnemyEtis, "EnemyEtis-4");
	orderActorToFactory(10000014, EnemyEtis, "EnemyEtis-5");
	orderActorToFactory(10000015, EnemyEtis, "EnemyEtis-6");
	orderActorToFactory(10000016, EnemyEtis, "EnemyEtis-7");
	orderActorToFactory(10000017, EnemyEtis, "EnemyEtis-8");
	orderActorToFactory(10000018, EnemyEtis, "EnemyEtis-9");
	orderActorToFactory(10000019, EnemyEtis, "EnemyEtis-10");
	orderActorToFactory(10000020, EnemyEtis, "EnemyEtis-11");
	orderActorToFactory(10000021, EnemyEtis, "EnemyEtis-12");
	orderActorToFactory(10000022, EnemyEtis, "EnemyEtis-13");
	orderActorToFactory(10000023, EnemyEtis, "EnemyEtis-14");
	orderActorToFactory(10000024, EnemyEtis, "EnemyEtis-15");
	orderActorToFactory(10000025, EnemyEtis, "EnemyEtis-16");
	orderActorToFactory(10000026, EnemyEtis, "EnemyEtis-17");
	orderActorToFactory(10000027, EnemyEtis, "EnemyEtis-18");
	orderActorToFactory(10000028, EnemyEtis, "EnemyEtis-19");
	orderActorToFactory(10001676, EnemyDrastea, "EnemyDrastea-20");
	orderActorToFactory(10001677, EnemyDrastea, "EnemyDrastea-21");
    // gen01 end
    useProgress(Stage01PartController::PROG_BANPEI-1);
}

void Stage01PartController::initialize() {
    getProgress()->reset(Stage01PartController::PROG_INIT);
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
			case 10: {
				orderActorToFactory(10000029, EnemyEtis, "EnemyEtis-22");
				break;
			}
			case 20: {
				orderActorToFactory(10000001, EnemyOebiusController002, "EnemyOebiusController002-23");
				break;
			}
			case 40: {
				orderActorToFactory(10000030, EnemyEtis, "EnemyEtis-24");
				break;
			}
			case 70: {
				orderActorToFactory(10000031, EnemyEtis, "EnemyEtis-25");
				break;
			}
			case 100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000012);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000032, EnemyEtis, "EnemyEtis-26");
				orderActorToFactory(10001678, EnemyDrastea, "EnemyDrastea-27");
				break;
			}
			case 130: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000013);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000033, EnemyEtis, "EnemyEtis-28");
				break;
			}
			case 160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000014);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000034, EnemyEtis, "EnemyEtis-29");
				break;
			}
			case 190: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000015);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000035, EnemyEtis, "EnemyEtis-30");
				break;
			}
			case 200: {
				orderActorToFactory(10001679, EnemyDrastea, "EnemyDrastea-31");
				break;
			}
			case 220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000016);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000036, EnemyEtis, "EnemyEtis-32");
				break;
			}
			case 250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000017);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000037, EnemyEtis, "EnemyEtis-33");
				break;
			}
			case 280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000018);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000038, EnemyEtis, "EnemyEtis-34");
				break;
			}
			case 300: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(10000002);
				bringDirector()->addSubGroup(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				orderActorToFactory(10001680, EnemyDrastea, "EnemyDrastea-35");
				break;
			}
			case 310: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000019);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000039, EnemyEtis, "EnemyEtis-36");
				break;
			}
			case 340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000020);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000040, EnemyEtis, "EnemyEtis-37");
				break;
			}
			case 370: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000021);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000041, EnemyEtis, "EnemyEtis-38");
				break;
			}
			case 400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000022);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000042, EnemyEtis, "EnemyEtis-39");
				orderActorToFactory(10001681, EnemyDrastea, "EnemyDrastea-40");
				break;
			}
			case 430: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000023);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000043, EnemyEtis, "EnemyEtis-41");
				break;
			}
			case 460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000024);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000044, EnemyEtis, "EnemyEtis-42");
				break;
			}
			case 490: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000025);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000045, EnemyEtis, "EnemyEtis-43");
				break;
			}
			case 500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001676);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001682, EnemyDrastea, "EnemyDrastea-44");
				break;
			}
			case 520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000026);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000046, EnemyEtis, "EnemyEtis-45");
				break;
			}
			case 550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000027);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000047, EnemyEtis, "EnemyEtis-46");
				break;
			}
			case 580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000028);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000048, EnemyEtis, "EnemyEtis-47");
				break;
			}
			case 600: {
				EnemyOebiusController001* p1 = (EnemyOebiusController001*)obtainActorFromFactory(10000000);
				bringDirector()->addSubGroup(p1);
				p1->position(PX_C(800), PX_C(100), PX_C(400) );
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001677);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001683, EnemyDrastea, "EnemyDrastea-48");
				break;
			}
			case 610: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000029);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000049, EnemyEtis, "EnemyEtis-49");
				break;
			}
			case 620: {
				EnemyOebiusController002* p2 = (EnemyOebiusController002*)obtainActorFromFactory(10000001);
				bringDirector()->addSubGroup(p2);
				p2->position(PX_C(800), PX_C(400), PX_C(100) );
				break;
			}
			case 640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000030);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000050, EnemyEtis, "EnemyEtis-50");
				break;
			}
			case 670: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000031);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000051, EnemyEtis, "EnemyEtis-51");
				break;
			}
			case 700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000032);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000052, EnemyEtis, "EnemyEtis-52");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001678);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001684, EnemyDrastea, "EnemyDrastea-53");
				break;
			}
			case 730: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000033);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000053, EnemyEtis, "EnemyEtis-54");
				break;
			}
			case 760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000034);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000054, EnemyEtis, "EnemyEtis-55");
				break;
			}
			case 790: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000035);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000055, EnemyEtis, "EnemyEtis-56");
				break;
			}
			case 800: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001679);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001685, EnemyDrastea, "EnemyDrastea-57");
				break;
			}
			case 820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000036);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000056, EnemyEtis, "EnemyEtis-58");
				break;
			}
			case 850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000037);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000057, EnemyEtis, "EnemyEtis-59");
				break;
			}
			case 880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000038);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000058, EnemyEtis, "EnemyEtis-60");
				break;
			}
			case 900: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001680);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001686, EnemyDrastea, "EnemyDrastea-61");
				break;
			}
			case 910: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000039);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000059, EnemyEtis, "EnemyEtis-62");
				break;
			}
			case 940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000040);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000060, EnemyEtis, "EnemyEtis-63");
				break;
			}
			case 970: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000041);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000061, EnemyEtis, "EnemyEtis-64");
				break;
			}
			case 1000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000042);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000062, EnemyEtis, "EnemyEtis-65");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001681);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001687, EnemyDrastea, "EnemyDrastea-66");
				break;
			}
			case 1030: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000043);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000063, EnemyEtis, "EnemyEtis-67");
				break;
			}
			case 1060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000044);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000064, EnemyEtis, "EnemyEtis-68");
				break;
			}
			case 1090: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000045);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000065, EnemyEtis, "EnemyEtis-69");
				break;
			}
			case 1100: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001682);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001688, EnemyDrastea, "EnemyDrastea-70");
				break;
			}
			case 1120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000046);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000066, EnemyEtis, "EnemyEtis-71");
				break;
			}
			case 1150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000047);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000067, EnemyEtis, "EnemyEtis-72");
				break;
			}
			case 1180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000048);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000068, EnemyEtis, "EnemyEtis-73");
				break;
			}
			case 1200: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001683);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001689, EnemyDrastea, "EnemyDrastea-74");
				break;
			}
			case 1210: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000049);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000069, EnemyEtis, "EnemyEtis-75");
				break;
			}
			case 1240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000050);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000070, EnemyEtis, "EnemyEtis-76");
				break;
			}
			case 1270: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000051);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000071, EnemyEtis, "EnemyEtis-77");
				break;
			}
			case 1300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000052);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000072, EnemyEtis, "EnemyEtis-78");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001684);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001690, EnemyDrastea, "EnemyDrastea-79");
				break;
			}
			case 1330: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000053);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000073, EnemyEtis, "EnemyEtis-80");
				break;
			}
			case 1360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000054);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000074, EnemyEtis, "EnemyEtis-81");
				break;
			}
			case 1390: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000055);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000075, EnemyEtis, "EnemyEtis-82");
				break;
			}
			case 1400: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001685);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001691, EnemyDrastea, "EnemyDrastea-83");
				break;
			}
			case 1420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000056);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000076, EnemyEtis, "EnemyEtis-84");
				break;
			}
			case 1450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000057);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000077, EnemyEtis, "EnemyEtis-85");
				break;
			}
			case 1480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000058);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000078, EnemyEtis, "EnemyEtis-86");
				break;
			}
			case 1500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001686);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001692, EnemyDrastea, "EnemyDrastea-87");
				break;
			}
			case 1510: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000059);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000079, EnemyEtis, "EnemyEtis-88");
				break;
			}
			case 1540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000060);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000080, EnemyEtis, "EnemyEtis-89");
				break;
			}
			case 1570: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000061);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000081, EnemyEtis, "EnemyEtis-90");
				break;
			}
			case 1600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000062);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000082, EnemyEtis, "EnemyEtis-91");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001687);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001693, EnemyDrastea, "EnemyDrastea-92");
				break;
			}
			case 1630: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000063);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000083, EnemyEtis, "EnemyEtis-93");
				break;
			}
			case 1660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000064);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000084, EnemyEtis, "EnemyEtis-94");
				break;
			}
			case 1690: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000065);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000085, EnemyEtis, "EnemyEtis-95");
				break;
			}
			case 1700: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001688);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001694, EnemyDrastea, "EnemyDrastea-96");
				break;
			}
			case 1720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000066);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000086, EnemyEtis, "EnemyEtis-97");
				break;
			}
			case 1750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000067);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000087, EnemyEtis, "EnemyEtis-98");
				break;
			}
			case 1780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000068);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000088, EnemyEtis, "EnemyEtis-99");
				break;
			}
			case 1800: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001689);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001695, EnemyDrastea, "EnemyDrastea-100");
				break;
			}
			case 1810: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000069);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000089, EnemyEtis, "EnemyEtis-101");
				break;
			}
			case 1840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000070);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000090, EnemyEtis, "EnemyEtis-102");
				break;
			}
			case 1870: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000071);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000091, EnemyEtis, "EnemyEtis-103");
				break;
			}
			case 1900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000072);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000092, EnemyEtis, "EnemyEtis-104");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001690);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001696, EnemyDrastea, "EnemyDrastea-105");
				break;
			}
			case 1930: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000073);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000093, EnemyEtis, "EnemyEtis-106");
				break;
			}
			case 1960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000074);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000094, EnemyEtis, "EnemyEtis-107");
				break;
			}
			case 1990: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000075);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000095, EnemyEtis, "EnemyEtis-108");
				break;
			}
			case 2000: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001691);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001697, EnemyDrastea, "EnemyDrastea-109");
				break;
			}
			case 2020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000076);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000096, EnemyEtis, "EnemyEtis-110");
				break;
			}
			case 2050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000077);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000097, EnemyEtis, "EnemyEtis-111");
				break;
			}
			case 2080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000078);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000098, EnemyEtis, "EnemyEtis-112");
				break;
			}
			case 2100: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001692);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001698, EnemyDrastea, "EnemyDrastea-113");
				break;
			}
			case 2110: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000079);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000099, EnemyEtis, "EnemyEtis-114");
				break;
			}
			case 2140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000080);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000100, EnemyEtis, "EnemyEtis-115");
				break;
			}
			case 2170: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000081);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000101, EnemyEtis, "EnemyEtis-116");
				break;
			}
			case 2200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000082);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000102, EnemyEtis, "EnemyEtis-117");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001693);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001699, EnemyDrastea, "EnemyDrastea-118");
				break;
			}
			case 2230: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000083);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000103, EnemyEtis, "EnemyEtis-119");
				break;
			}
			case 2260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000084);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000104, EnemyEtis, "EnemyEtis-120");
				break;
			}
			case 2290: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000085);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000105, EnemyEtis, "EnemyEtis-121");
				break;
			}
			case 2300: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001694);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001700, EnemyDrastea, "EnemyDrastea-122");
				break;
			}
			case 2320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000086);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000106, EnemyEtis, "EnemyEtis-123");
				break;
			}
			case 2350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000087);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000107, EnemyEtis, "EnemyEtis-124");
				break;
			}
			case 2380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000088);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000108, EnemyEtis, "EnemyEtis-125");
				break;
			}
			case 2400: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001695);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001701, EnemyDrastea, "EnemyDrastea-126");
				break;
			}
			case 2410: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000089);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000109, EnemyEtis, "EnemyEtis-127");
				break;
			}
			case 2440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000090);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000110, EnemyEtis, "EnemyEtis-128");
				break;
			}
			case 2470: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000091);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000111, EnemyEtis, "EnemyEtis-129");
				break;
			}
			case 2500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000092);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000112, EnemyEtis, "EnemyEtis-130");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001696);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001702, EnemyDrastea, "EnemyDrastea-131");
				break;
			}
			case 2530: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000093);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000113, EnemyEtis, "EnemyEtis-132");
				break;
			}
			case 2560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000094);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000114, EnemyEtis, "EnemyEtis-133");
				break;
			}
			case 2590: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000095);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000115, EnemyEtis, "EnemyEtis-134");
				break;
			}
			case 2600: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001697);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001703, EnemyDrastea, "EnemyDrastea-135");
				break;
			}
			case 2620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000096);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000116, EnemyEtis, "EnemyEtis-136");
				break;
			}
			case 2650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000097);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000117, EnemyEtis, "EnemyEtis-137");
				break;
			}
			case 2680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000098);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000118, EnemyEtis, "EnemyEtis-138");
				break;
			}
			case 2700: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001698);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001704, EnemyDrastea, "EnemyDrastea-139");
				break;
			}
			case 2710: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000099);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000119, EnemyEtis, "EnemyEtis-140");
				break;
			}
			case 2740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000100);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000120, EnemyEtis, "EnemyEtis-141");
				break;
			}
			case 2770: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000101);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000121, EnemyEtis, "EnemyEtis-142");
				break;
			}
			case 2800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000102);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000122, EnemyEtis, "EnemyEtis-143");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001699);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001705, EnemyDrastea, "EnemyDrastea-144");
				break;
			}
			case 2830: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000103);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000123, EnemyEtis, "EnemyEtis-145");
				break;
			}
			case 2860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000104);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000124, EnemyEtis, "EnemyEtis-146");
				break;
			}
			case 2890: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000105);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000125, EnemyEtis, "EnemyEtis-147");
				break;
			}
			case 2900: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001700);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001706, EnemyDrastea, "EnemyDrastea-148");
				break;
			}
			case 2920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000106);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000126, EnemyEtis, "EnemyEtis-149");
				break;
			}
			case 2950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000107);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000127, EnemyEtis, "EnemyEtis-150");
				break;
			}
			case 2980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000108);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000128, EnemyEtis, "EnemyEtis-151");
				break;
			}
			case 3000: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001701);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001707, EnemyDrastea, "EnemyDrastea-152");
				break;
			}
			case 3010: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000109);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000129, EnemyEtis, "EnemyEtis-153");
				break;
			}
			case 3040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000110);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000130, EnemyEtis, "EnemyEtis-154");
				break;
			}
			case 3070: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000111);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000131, EnemyEtis, "EnemyEtis-155");
				break;
			}
			case 3100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000112);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000132, EnemyEtis, "EnemyEtis-156");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001702);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001708, EnemyDrastea, "EnemyDrastea-157");
				break;
			}
			case 3130: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000113);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000133, EnemyEtis, "EnemyEtis-158");
				break;
			}
			case 3160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000114);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000134, EnemyEtis, "EnemyEtis-159");
				break;
			}
			case 3190: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000115);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000135, EnemyEtis, "EnemyEtis-160");
				break;
			}
			case 3200: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001703);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001709, EnemyDrastea, "EnemyDrastea-161");
				break;
			}
			case 3220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000116);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000136, EnemyEtis, "EnemyEtis-162");
				break;
			}
			case 3250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000117);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000137, EnemyEtis, "EnemyEtis-163");
				break;
			}
			case 3280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000118);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000138, EnemyEtis, "EnemyEtis-164");
				break;
			}
			case 3300: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001704);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001710, EnemyDrastea, "EnemyDrastea-165");
				break;
			}
			case 3310: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000119);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000139, EnemyEtis, "EnemyEtis-166");
				break;
			}
			case 3340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000120);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000140, EnemyEtis, "EnemyEtis-167");
				break;
			}
			case 3370: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000121);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000141, EnemyEtis, "EnemyEtis-168");
				break;
			}
			case 3400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000122);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000142, EnemyEtis, "EnemyEtis-169");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001705);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001711, EnemyDrastea, "EnemyDrastea-170");
				break;
			}
			case 3430: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000123);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000143, EnemyEtis, "EnemyEtis-171");
				break;
			}
			case 3460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000124);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000144, EnemyEtis, "EnemyEtis-172");
				break;
			}
			case 3490: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000125);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000145, EnemyEtis, "EnemyEtis-173");
				break;
			}
			case 3500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001706);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001712, EnemyDrastea, "EnemyDrastea-174");
				break;
			}
			case 3520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000126);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000146, EnemyEtis, "EnemyEtis-175");
				break;
			}
			case 3550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000127);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000147, EnemyEtis, "EnemyEtis-176");
				break;
			}
			case 3580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000128);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000148, EnemyEtis, "EnemyEtis-177");
				break;
			}
			case 3600: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001707);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001713, EnemyDrastea, "EnemyDrastea-178");
				break;
			}
			case 3610: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000129);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000149, EnemyEtis, "EnemyEtis-179");
				break;
			}
			case 3640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000130);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000150, EnemyEtis, "EnemyEtis-180");
				break;
			}
			case 3670: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000131);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000151, EnemyEtis, "EnemyEtis-181");
				break;
			}
			case 3700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000132);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000152, EnemyEtis, "EnemyEtis-182");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001708);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001714, EnemyDrastea, "EnemyDrastea-183");
				break;
			}
			case 3730: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000133);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000153, EnemyEtis, "EnemyEtis-184");
				break;
			}
			case 3760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000134);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000154, EnemyEtis, "EnemyEtis-185");
				break;
			}
			case 3790: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000135);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000155, EnemyEtis, "EnemyEtis-186");
				break;
			}
			case 3800: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001709);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001715, EnemyDrastea, "EnemyDrastea-187");
				break;
			}
			case 3820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000136);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000156, EnemyEtis, "EnemyEtis-188");
				break;
			}
			case 3850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000137);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000157, EnemyEtis, "EnemyEtis-189");
				break;
			}
			case 3880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000138);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000158, EnemyEtis, "EnemyEtis-190");
				break;
			}
			case 3900: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001710);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001716, EnemyDrastea, "EnemyDrastea-191");
				break;
			}
			case 3910: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000139);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000159, EnemyEtis, "EnemyEtis-192");
				break;
			}
			case 3940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000140);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000160, EnemyEtis, "EnemyEtis-193");
				break;
			}
			case 3970: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000141);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000161, EnemyEtis, "EnemyEtis-194");
				break;
			}
			case 4000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000142);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000162, EnemyEtis, "EnemyEtis-195");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001711);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001717, EnemyDrastea, "EnemyDrastea-196");
				break;
			}
			case 4030: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000143);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000163, EnemyEtis, "EnemyEtis-197");
				break;
			}
			case 4060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000144);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000164, EnemyEtis, "EnemyEtis-198");
				break;
			}
			case 4090: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000145);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000165, EnemyEtis, "EnemyEtis-199");
				break;
			}
			case 4100: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001712);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001718, EnemyDrastea, "EnemyDrastea-200");
				break;
			}
			case 4120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000146);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000166, EnemyEtis, "EnemyEtis-201");
				break;
			}
			case 4150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000147);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000167, EnemyEtis, "EnemyEtis-202");
				break;
			}
			case 4180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000148);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000168, EnemyEtis, "EnemyEtis-203");
				break;
			}
			case 4200: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001713);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001719, EnemyDrastea, "EnemyDrastea-204");
				break;
			}
			case 4210: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000149);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000169, EnemyEtis, "EnemyEtis-205");
				break;
			}
			case 4240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000150);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000170, EnemyEtis, "EnemyEtis-206");
				break;
			}
			case 4270: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000151);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000171, EnemyEtis, "EnemyEtis-207");
				break;
			}
			case 4300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000152);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000172, EnemyEtis, "EnemyEtis-208");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001714);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001720, EnemyDrastea, "EnemyDrastea-209");
				break;
			}
			case 4330: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000153);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000173, EnemyEtis, "EnemyEtis-210");
				break;
			}
			case 4360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000154);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000174, EnemyEtis, "EnemyEtis-211");
				break;
			}
			case 4390: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000155);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000175, EnemyEtis, "EnemyEtis-212");
				break;
			}
			case 4400: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001715);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001721, EnemyDrastea, "EnemyDrastea-213");
				break;
			}
			case 4420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000156);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000176, EnemyEtis, "EnemyEtis-214");
				break;
			}
			case 4450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000157);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000177, EnemyEtis, "EnemyEtis-215");
				break;
			}
			case 4480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000158);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000178, EnemyEtis, "EnemyEtis-216");
				break;
			}
			case 4500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001716);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001722, EnemyDrastea, "EnemyDrastea-217");
				break;
			}
			case 4510: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000159);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000179, EnemyEtis, "EnemyEtis-218");
				break;
			}
			case 4540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000160);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000180, EnemyEtis, "EnemyEtis-219");
				break;
			}
			case 4570: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000161);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000181, EnemyEtis, "EnemyEtis-220");
				break;
			}
			case 4600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000162);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000182, EnemyEtis, "EnemyEtis-221");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001717);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001723, EnemyDrastea, "EnemyDrastea-222");
				break;
			}
			case 4630: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000163);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000183, EnemyEtis, "EnemyEtis-223");
				break;
			}
			case 4660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000164);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000184, EnemyEtis, "EnemyEtis-224");
				break;
			}
			case 4690: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000165);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000185, EnemyEtis, "EnemyEtis-225");
				break;
			}
			case 4700: {
				orderActorToFactory(10000003, EnemyErmione, "EnemyErmione-226");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001718);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001724, EnemyDrastea, "EnemyDrastea-227");
				break;
			}
			case 4720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000166);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000186, EnemyEtis, "EnemyEtis-228");
				break;
			}
			case 4750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000167);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000187, EnemyEtis, "EnemyEtis-229");
				break;
			}
			case 4780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000168);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000188, EnemyEtis, "EnemyEtis-230");
				break;
			}
			case 4800: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001719);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001725, EnemyDrastea, "EnemyDrastea-231");
				break;
			}
			case 4810: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000169);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000189, EnemyEtis, "EnemyEtis-232");
				break;
			}
			case 4840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000170);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000190, EnemyEtis, "EnemyEtis-233");
				break;
			}
			case 4870: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000171);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000191, EnemyEtis, "EnemyEtis-234");
				break;
			}
			case 4900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000172);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000192, EnemyEtis, "EnemyEtis-235");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001720);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001726, EnemyDrastea, "EnemyDrastea-236");
				break;
			}
			case 4930: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000173);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000193, EnemyEtis, "EnemyEtis-237");
				break;
			}
			case 4960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000174);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000194, EnemyEtis, "EnemyEtis-238");
				break;
			}
			case 4990: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000175);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000195, EnemyEtis, "EnemyEtis-239");
				break;
			}
			case 5000: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001721);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001727, EnemyDrastea, "EnemyDrastea-240");
				break;
			}
			case 5020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000176);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000196, EnemyEtis, "EnemyEtis-241");
				break;
			}
			case 5050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000177);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000197, EnemyEtis, "EnemyEtis-242");
				break;
			}
			case 5080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000178);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000198, EnemyEtis, "EnemyEtis-243");
				break;
			}
			case 5100: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001722);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001728, EnemyDrastea, "EnemyDrastea-244");
				break;
			}
			case 5110: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000179);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000199, EnemyEtis, "EnemyEtis-245");
				break;
			}
			case 5140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000180);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000200, EnemyEtis, "EnemyEtis-246");
				break;
			}
			case 5170: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000181);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000201, EnemyEtis, "EnemyEtis-247");
				break;
			}
			case 5200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000182);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000202, EnemyEtis, "EnemyEtis-248");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001723);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001729, EnemyDrastea, "EnemyDrastea-249");
				break;
			}
			case 5230: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000183);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000203, EnemyEtis, "EnemyEtis-250");
				break;
			}
			case 5260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000184);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000204, EnemyEtis, "EnemyEtis-251");
				break;
			}
			case 5290: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000185);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000205, EnemyEtis, "EnemyEtis-252");
				break;
			}
			case 5300: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(10000003);
				bringDirector()->addSubGroup(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001724);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001730, EnemyDrastea, "EnemyDrastea-253");
				break;
			}
			case 5320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000186);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000206, EnemyEtis, "EnemyEtis-254");
				break;
			}
			case 5350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000187);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000207, EnemyEtis, "EnemyEtis-255");
				break;
			}
			case 5380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000188);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000208, EnemyEtis, "EnemyEtis-256");
				break;
			}
			case 5400: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001725);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001731, EnemyDrastea, "EnemyDrastea-257");
				break;
			}
			case 5410: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000189);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000209, EnemyEtis, "EnemyEtis-258");
				break;
			}
			case 5440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000190);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000210, EnemyEtis, "EnemyEtis-259");
				break;
			}
			case 5470: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000191);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000211, EnemyEtis, "EnemyEtis-260");
				break;
			}
			case 5500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000192);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000212, EnemyEtis, "EnemyEtis-261");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001726);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001732, EnemyDrastea, "EnemyDrastea-262");
				break;
			}
			case 5530: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000193);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000213, EnemyEtis, "EnemyEtis-263");
				break;
			}
			case 5560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000194);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000214, EnemyEtis, "EnemyEtis-264");
				break;
			}
			case 5590: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000195);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000215, EnemyEtis, "EnemyEtis-265");
				break;
			}
			case 5600: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001727);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001733, EnemyDrastea, "EnemyDrastea-266");
				break;
			}
			case 5620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000196);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000216, EnemyEtis, "EnemyEtis-267");
				break;
			}
			case 5650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000197);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000217, EnemyEtis, "EnemyEtis-268");
				break;
			}
			case 5680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000198);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000218, EnemyEtis, "EnemyEtis-269");
				break;
			}
			case 5700: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001728);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001734, EnemyDrastea, "EnemyDrastea-270");
				break;
			}
			case 5710: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000199);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000219, EnemyEtis, "EnemyEtis-271");
				break;
			}
			case 5740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000200);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000220, EnemyEtis, "EnemyEtis-272");
				break;
			}
			case 5770: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000201);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000221, EnemyEtis, "EnemyEtis-273");
				break;
			}
			case 5800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000202);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000222, EnemyEtis, "EnemyEtis-274");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001729);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001735, EnemyDrastea, "EnemyDrastea-275");
				break;
			}
			case 5830: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000203);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000223, EnemyEtis, "EnemyEtis-276");
				break;
			}
			case 5860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000204);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000224, EnemyEtis, "EnemyEtis-277");
				break;
			}
			case 5890: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000205);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000225, EnemyEtis, "EnemyEtis-278");
				break;
			}
			case 5900: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001730);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001736, EnemyDrastea, "EnemyDrastea-279");
				break;
			}
			case 5920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000206);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000226, EnemyEtis, "EnemyEtis-280");
				break;
			}
			case 5950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000207);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000227, EnemyEtis, "EnemyEtis-281");
				break;
			}
			case 5980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000208);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000228, EnemyEtis, "EnemyEtis-282");
				break;
			}
			case 6000: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001731);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001737, EnemyDrastea, "EnemyDrastea-283");
				break;
			}
			case 6010: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000209);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000229, EnemyEtis, "EnemyEtis-284");
				break;
			}
			case 6040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000210);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000230, EnemyEtis, "EnemyEtis-285");
				break;
			}
			case 6070: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000211);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000231, EnemyEtis, "EnemyEtis-286");
				break;
			}
			case 6100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000212);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000232, EnemyEtis, "EnemyEtis-287");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001732);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001738, EnemyDrastea, "EnemyDrastea-288");
				break;
			}
			case 6130: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000213);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000233, EnemyEtis, "EnemyEtis-289");
				break;
			}
			case 6160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000214);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000234, EnemyEtis, "EnemyEtis-290");
				break;
			}
			case 6190: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000215);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000235, EnemyEtis, "EnemyEtis-291");
				break;
			}
			case 6200: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001733);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001739, EnemyDrastea, "EnemyDrastea-292");
				break;
			}
			case 6220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000216);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000236, EnemyEtis, "EnemyEtis-293");
				break;
			}
			case 6250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000217);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000237, EnemyEtis, "EnemyEtis-294");
				break;
			}
			case 6280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000218);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000238, EnemyEtis, "EnemyEtis-295");
				break;
			}
			case 6300: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001734);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001740, EnemyDrastea, "EnemyDrastea-296");
				break;
			}
			case 6310: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000219);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000239, EnemyEtis, "EnemyEtis-297");
				break;
			}
			case 6340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000220);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000240, EnemyEtis, "EnemyEtis-298");
				break;
			}
			case 6370: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000221);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000241, EnemyEtis, "EnemyEtis-299");
				break;
			}
			case 6400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000222);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000242, EnemyEtis, "EnemyEtis-300");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001735);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001741, EnemyDrastea, "EnemyDrastea-301");
				break;
			}
			case 6430: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000223);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000243, EnemyEtis, "EnemyEtis-302");
				break;
			}
			case 6460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000224);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000244, EnemyEtis, "EnemyEtis-303");
				break;
			}
			case 6490: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000225);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000245, EnemyEtis, "EnemyEtis-304");
				break;
			}
			case 6500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001736);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001742, EnemyDrastea, "EnemyDrastea-305");
				break;
			}
			case 6520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000226);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000246, EnemyEtis, "EnemyEtis-306");
				break;
			}
			case 6550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000227);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000247, EnemyEtis, "EnemyEtis-307");
				break;
			}
			case 6580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000228);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000248, EnemyEtis, "EnemyEtis-308");
				break;
			}
			case 6600: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001737);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001743, EnemyDrastea, "EnemyDrastea-309");
				break;
			}
			case 6610: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000229);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000249, EnemyEtis, "EnemyEtis-310");
				break;
			}
			case 6640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000230);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000250, EnemyEtis, "EnemyEtis-311");
				break;
			}
			case 6670: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000231);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000251, EnemyEtis, "EnemyEtis-312");
				break;
			}
			case 6700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000232);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000252, EnemyEtis, "EnemyEtis-313");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001738);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001744, EnemyDrastea, "EnemyDrastea-314");
				break;
			}
			case 6730: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000233);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000253, EnemyEtis, "EnemyEtis-315");
				break;
			}
			case 6760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000234);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000254, EnemyEtis, "EnemyEtis-316");
				break;
			}
			case 6790: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000235);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000255, EnemyEtis, "EnemyEtis-317");
				break;
			}
			case 6800: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001739);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001745, EnemyDrastea, "EnemyDrastea-318");
				break;
			}
			case 6820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000236);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000256, EnemyEtis, "EnemyEtis-319");
				break;
			}
			case 6850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000237);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000257, EnemyEtis, "EnemyEtis-320");
				break;
			}
			case 6880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000238);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000258, EnemyEtis, "EnemyEtis-321");
				break;
			}
			case 6900: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001740);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001746, EnemyDrastea, "EnemyDrastea-322");
				break;
			}
			case 6910: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000239);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000259, EnemyEtis, "EnemyEtis-323");
				break;
			}
			case 6940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000240);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000260, EnemyEtis, "EnemyEtis-324");
				break;
			}
			case 6970: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000241);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000261, EnemyEtis, "EnemyEtis-325");
				break;
			}
			case 7000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000242);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000262, EnemyEtis, "EnemyEtis-326");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001741);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001747, EnemyDrastea, "EnemyDrastea-327");
				break;
			}
			case 7030: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000243);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000263, EnemyEtis, "EnemyEtis-328");
				break;
			}
			case 7060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000244);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000264, EnemyEtis, "EnemyEtis-329");
				break;
			}
			case 7090: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000245);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000265, EnemyEtis, "EnemyEtis-330");
				break;
			}
			case 7100: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001742);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001748, EnemyDrastea, "EnemyDrastea-331");
				break;
			}
			case 7120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000246);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000266, EnemyEtis, "EnemyEtis-332");
				break;
			}
			case 7150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000247);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000267, EnemyEtis, "EnemyEtis-333");
				break;
			}
			case 7180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000248);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000268, EnemyEtis, "EnemyEtis-334");
				break;
			}
			case 7200: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001743);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001749, EnemyDrastea, "EnemyDrastea-335");
				break;
			}
			case 7210: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000249);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000269, EnemyEtis, "EnemyEtis-336");
				break;
			}
			case 7240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000250);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000270, EnemyEtis, "EnemyEtis-337");
				break;
			}
			case 7270: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000251);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000271, EnemyEtis, "EnemyEtis-338");
				break;
			}
			case 7300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000252);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000272, EnemyEtis, "EnemyEtis-339");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001744);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001750, EnemyDrastea, "EnemyDrastea-340");
				break;
			}
			case 7330: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000253);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000273, EnemyEtis, "EnemyEtis-341");
				break;
			}
			case 7360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000254);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000274, EnemyEtis, "EnemyEtis-342");
				break;
			}
			case 7390: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000255);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000275, EnemyEtis, "EnemyEtis-343");
				break;
			}
			case 7400: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001745);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001751, EnemyDrastea, "EnemyDrastea-344");
				break;
			}
			case 7420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000256);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000276, EnemyEtis, "EnemyEtis-345");
				break;
			}
			case 7450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000257);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000277, EnemyEtis, "EnemyEtis-346");
				break;
			}
			case 7480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000258);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000278, EnemyEtis, "EnemyEtis-347");
				break;
			}
			case 7500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001746);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001752, EnemyDrastea, "EnemyDrastea-348");
				break;
			}
			case 7510: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000259);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000279, EnemyEtis, "EnemyEtis-349");
				break;
			}
			case 7540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000260);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000280, EnemyEtis, "EnemyEtis-350");
				break;
			}
			case 7570: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000261);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000281, EnemyEtis, "EnemyEtis-351");
				break;
			}
			case 7600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000262);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000282, EnemyEtis, "EnemyEtis-352");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001747);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001753, EnemyDrastea, "EnemyDrastea-353");
				break;
			}
			case 7630: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000263);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000283, EnemyEtis, "EnemyEtis-354");
				break;
			}
			case 7660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000264);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000284, EnemyEtis, "EnemyEtis-355");
				break;
			}
			case 7690: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000265);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000285, EnemyEtis, "EnemyEtis-356");
				break;
			}
			case 7700: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001748);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001754, EnemyDrastea, "EnemyDrastea-357");
				break;
			}
			case 7720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000266);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000286, EnemyEtis, "EnemyEtis-358");
				break;
			}
			case 7750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000267);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000287, EnemyEtis, "EnemyEtis-359");
				break;
			}
			case 7780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000268);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000288, EnemyEtis, "EnemyEtis-360");
				break;
			}
			case 7800: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001749);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001755, EnemyDrastea, "EnemyDrastea-361");
				break;
			}
			case 7810: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000269);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000289, EnemyEtis, "EnemyEtis-362");
				break;
			}
			case 7840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000270);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000290, EnemyEtis, "EnemyEtis-363");
				break;
			}
			case 7870: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000271);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000291, EnemyEtis, "EnemyEtis-364");
				break;
			}
			case 7900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000272);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000292, EnemyEtis, "EnemyEtis-365");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001750);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001756, EnemyDrastea, "EnemyDrastea-366");
				break;
			}
			case 7930: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000273);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000293, EnemyEtis, "EnemyEtis-367");
				break;
			}
			case 7960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000274);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000294, EnemyEtis, "EnemyEtis-368");
				break;
			}
			case 7990: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000275);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000295, EnemyEtis, "EnemyEtis-369");
				break;
			}
			case 8000: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001751);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001757, EnemyDrastea, "EnemyDrastea-370");
				break;
			}
			case 8020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000276);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000296, EnemyEtis, "EnemyEtis-371");
				break;
			}
			case 8050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000277);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000297, EnemyEtis, "EnemyEtis-372");
				break;
			}
			case 8080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000278);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000298, EnemyEtis, "EnemyEtis-373");
				break;
			}
			case 8100: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001752);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001758, EnemyDrastea, "EnemyDrastea-374");
				break;
			}
			case 8110: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000279);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000299, EnemyEtis, "EnemyEtis-375");
				break;
			}
			case 8140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000280);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000300, EnemyEtis, "EnemyEtis-376");
				break;
			}
			case 8170: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000281);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000301, EnemyEtis, "EnemyEtis-377");
				break;
			}
			case 8200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000282);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000302, EnemyEtis, "EnemyEtis-378");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001753);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001759, EnemyDrastea, "EnemyDrastea-379");
				break;
			}
			case 8230: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000283);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000303, EnemyEtis, "EnemyEtis-380");
				break;
			}
			case 8260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000284);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000304, EnemyEtis, "EnemyEtis-381");
				break;
			}
			case 8290: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000285);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000305, EnemyEtis, "EnemyEtis-382");
				break;
			}
			case 8300: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001754);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001760, EnemyDrastea, "EnemyDrastea-383");
				break;
			}
			case 8320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000286);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000306, EnemyEtis, "EnemyEtis-384");
				break;
			}
			case 8350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000287);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000307, EnemyEtis, "EnemyEtis-385");
				break;
			}
			case 8380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000288);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000308, EnemyEtis, "EnemyEtis-386");
				break;
			}
			case 8400: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001755);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001761, EnemyDrastea, "EnemyDrastea-387");
				break;
			}
			case 8410: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000289);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000309, EnemyEtis, "EnemyEtis-388");
				break;
			}
			case 8440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000290);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000310, EnemyEtis, "EnemyEtis-389");
				break;
			}
			case 8470: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000291);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000311, EnemyEtis, "EnemyEtis-390");
				break;
			}
			case 8500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000292);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000312, EnemyEtis, "EnemyEtis-391");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001756);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001762, EnemyDrastea, "EnemyDrastea-392");
				break;
			}
			case 8530: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000293);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000313, EnemyEtis, "EnemyEtis-393");
				break;
			}
			case 8560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000294);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000314, EnemyEtis, "EnemyEtis-394");
				break;
			}
			case 8590: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000295);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000315, EnemyEtis, "EnemyEtis-395");
				break;
			}
			case 8600: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001757);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001763, EnemyDrastea, "EnemyDrastea-396");
				break;
			}
			case 8620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000296);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000316, EnemyEtis, "EnemyEtis-397");
				break;
			}
			case 8650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000297);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000317, EnemyEtis, "EnemyEtis-398");
				break;
			}
			case 8680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000298);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000318, EnemyEtis, "EnemyEtis-399");
				break;
			}
			case 8700: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001758);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001764, EnemyDrastea, "EnemyDrastea-400");
				break;
			}
			case 8710: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000299);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000319, EnemyEtis, "EnemyEtis-401");
				break;
			}
			case 8740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000300);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000320, EnemyEtis, "EnemyEtis-402");
				break;
			}
			case 8770: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000301);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000321, EnemyEtis, "EnemyEtis-403");
				break;
			}
			case 8800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000302);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000322, EnemyEtis, "EnemyEtis-404");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001759);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001765, EnemyDrastea, "EnemyDrastea-405");
				break;
			}
			case 8830: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000303);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000323, EnemyEtis, "EnemyEtis-406");
				break;
			}
			case 8860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000304);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000324, EnemyEtis, "EnemyEtis-407");
				break;
			}
			case 8890: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000305);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000325, EnemyEtis, "EnemyEtis-408");
				break;
			}
			case 8900: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001760);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001766, EnemyDrastea, "EnemyDrastea-409");
				break;
			}
			case 8920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000306);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000326, EnemyEtis, "EnemyEtis-410");
				break;
			}
			case 8950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000307);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000327, EnemyEtis, "EnemyEtis-411");
				break;
			}
			case 8980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000308);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000328, EnemyEtis, "EnemyEtis-412");
				break;
			}
			case 9000: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001761);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001767, EnemyDrastea, "EnemyDrastea-413");
				break;
			}
			case 9010: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000309);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000329, EnemyEtis, "EnemyEtis-414");
				break;
			}
			case 9040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000310);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000330, EnemyEtis, "EnemyEtis-415");
				break;
			}
			case 9070: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000311);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000331, EnemyEtis, "EnemyEtis-416");
				break;
			}
			case 9100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000312);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000332, EnemyEtis, "EnemyEtis-417");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001762);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001768, EnemyDrastea, "EnemyDrastea-418");
				break;
			}
			case 9130: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000313);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000333, EnemyEtis, "EnemyEtis-419");
				break;
			}
			case 9160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000314);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000334, EnemyEtis, "EnemyEtis-420");
				break;
			}
			case 9190: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000315);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000335, EnemyEtis, "EnemyEtis-421");
				break;
			}
			case 9200: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001763);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001769, EnemyDrastea, "EnemyDrastea-422");
				break;
			}
			case 9220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000316);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000336, EnemyEtis, "EnemyEtis-423");
				break;
			}
			case 9250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000317);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000337, EnemyEtis, "EnemyEtis-424");
				break;
			}
			case 9280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000318);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000338, EnemyEtis, "EnemyEtis-425");
				break;
			}
			case 9300: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001764);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001770, EnemyDrastea, "EnemyDrastea-426");
				break;
			}
			case 9310: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000319);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000339, EnemyEtis, "EnemyEtis-427");
				break;
			}
			case 9340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000320);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000340, EnemyEtis, "EnemyEtis-428");
				break;
			}
			case 9370: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000321);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000341, EnemyEtis, "EnemyEtis-429");
				break;
			}
			case 9400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000322);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000342, EnemyEtis, "EnemyEtis-430");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001765);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001771, EnemyDrastea, "EnemyDrastea-431");
				break;
			}
			case 9430: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000323);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000343, EnemyEtis, "EnemyEtis-432");
				break;
			}
			case 9460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000324);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000344, EnemyEtis, "EnemyEtis-433");
				break;
			}
			case 9490: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000325);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000345, EnemyEtis, "EnemyEtis-434");
				break;
			}
			case 9500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001766);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001772, EnemyDrastea, "EnemyDrastea-435");
				break;
			}
			case 9520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000326);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000346, EnemyEtis, "EnemyEtis-436");
				break;
			}
			case 9550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000327);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000347, EnemyEtis, "EnemyEtis-437");
				break;
			}
			case 9580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000328);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000348, EnemyEtis, "EnemyEtis-438");
				break;
			}
			case 9600: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001767);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001773, EnemyDrastea, "EnemyDrastea-439");
				break;
			}
			case 9610: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000329);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000349, EnemyEtis, "EnemyEtis-440");
				break;
			}
			case 9640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000330);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000350, EnemyEtis, "EnemyEtis-441");
				break;
			}
			case 9670: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000331);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000351, EnemyEtis, "EnemyEtis-442");
				break;
			}
			case 9700: {
				orderActorToFactory(10000004, EnemyErmione, "EnemyErmione-443");
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000332);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000352, EnemyEtis, "EnemyEtis-444");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001768);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001774, EnemyDrastea, "EnemyDrastea-445");
				break;
			}
			case 9730: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000333);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000353, EnemyEtis, "EnemyEtis-446");
				break;
			}
			case 9760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000334);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000354, EnemyEtis, "EnemyEtis-447");
				break;
			}
			case 9790: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000335);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000355, EnemyEtis, "EnemyEtis-448");
				break;
			}
			case 9800: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001769);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001775, EnemyDrastea, "EnemyDrastea-449");
				break;
			}
			case 9820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000336);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000356, EnemyEtis, "EnemyEtis-450");
				break;
			}
			case 9850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000337);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000357, EnemyEtis, "EnemyEtis-451");
				break;
			}
			case 9880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000338);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000358, EnemyEtis, "EnemyEtis-452");
				break;
			}
			case 9900: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001770);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001776, EnemyDrastea, "EnemyDrastea-453");
				break;
			}
			case 9910: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000339);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000359, EnemyEtis, "EnemyEtis-454");
				break;
			}
			case 9940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000340);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000360, EnemyEtis, "EnemyEtis-455");
				break;
			}
			case 9970: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000341);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000361, EnemyEtis, "EnemyEtis-456");
				break;
			}
			case 10000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000342);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000362, EnemyEtis, "EnemyEtis-457");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001771);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001777, EnemyDrastea, "EnemyDrastea-458");
				break;
			}
			case 10030: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000343);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000363, EnemyEtis, "EnemyEtis-459");
				break;
			}
			case 10060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000344);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000364, EnemyEtis, "EnemyEtis-460");
				break;
			}
			case 10090: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000345);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000365, EnemyEtis, "EnemyEtis-461");
				break;
			}
			case 10100: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001772);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001778, EnemyDrastea, "EnemyDrastea-462");
				break;
			}
			case 10120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000346);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000366, EnemyEtis, "EnemyEtis-463");
				break;
			}
			case 10150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000347);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000367, EnemyEtis, "EnemyEtis-464");
				break;
			}
			case 10180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000348);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000368, EnemyEtis, "EnemyEtis-465");
				break;
			}
			case 10200: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001773);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001779, EnemyDrastea, "EnemyDrastea-466");
				break;
			}
			case 10210: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000349);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000369, EnemyEtis, "EnemyEtis-467");
				break;
			}
			case 10240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000350);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000370, EnemyEtis, "EnemyEtis-468");
				break;
			}
			case 10270: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000351);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000371, EnemyEtis, "EnemyEtis-469");
				break;
			}
			case 10300: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(10000004);
				bringDirector()->addSubGroup(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000352);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000372, EnemyEtis, "EnemyEtis-470");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001774);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001780, EnemyDrastea, "EnemyDrastea-471");
				break;
			}
			case 10330: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000353);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000373, EnemyEtis, "EnemyEtis-472");
				break;
			}
			case 10360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000354);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000374, EnemyEtis, "EnemyEtis-473");
				break;
			}
			case 10390: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000355);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000375, EnemyEtis, "EnemyEtis-474");
				break;
			}
			case 10400: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001775);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001781, EnemyDrastea, "EnemyDrastea-475");
				break;
			}
			case 10420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000356);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000376, EnemyEtis, "EnemyEtis-476");
				break;
			}
			case 10450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000357);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000377, EnemyEtis, "EnemyEtis-477");
				break;
			}
			case 10480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000358);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000378, EnemyEtis, "EnemyEtis-478");
				break;
			}
			case 10500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001776);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001782, EnemyDrastea, "EnemyDrastea-479");
				break;
			}
			case 10510: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000359);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000379, EnemyEtis, "EnemyEtis-480");
				break;
			}
			case 10540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000360);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000380, EnemyEtis, "EnemyEtis-481");
				break;
			}
			case 10570: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000361);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000381, EnemyEtis, "EnemyEtis-482");
				break;
			}
			case 10600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000362);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000382, EnemyEtis, "EnemyEtis-483");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001777);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001783, EnemyDrastea, "EnemyDrastea-484");
				break;
			}
			case 10630: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000363);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000383, EnemyEtis, "EnemyEtis-485");
				break;
			}
			case 10660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000364);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000384, EnemyEtis, "EnemyEtis-486");
				break;
			}
			case 10690: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000365);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000385, EnemyEtis, "EnemyEtis-487");
				break;
			}
			case 10700: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001778);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001784, EnemyDrastea, "EnemyDrastea-488");
				break;
			}
			case 10720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000366);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000386, EnemyEtis, "EnemyEtis-489");
				break;
			}
			case 10750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000367);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000387, EnemyEtis, "EnemyEtis-490");
				break;
			}
			case 10780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000368);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000388, EnemyEtis, "EnemyEtis-491");
				break;
			}
			case 10800: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001779);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001785, EnemyDrastea, "EnemyDrastea-492");
				break;
			}
			case 10810: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000369);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000389, EnemyEtis, "EnemyEtis-493");
				break;
			}
			case 10840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000370);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000390, EnemyEtis, "EnemyEtis-494");
				break;
			}
			case 10870: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000371);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000391, EnemyEtis, "EnemyEtis-495");
				break;
			}
			case 10900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000372);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000392, EnemyEtis, "EnemyEtis-496");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001780);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001786, EnemyDrastea, "EnemyDrastea-497");
				break;
			}
			case 10930: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000373);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000393, EnemyEtis, "EnemyEtis-498");
				break;
			}
			case 10960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000374);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000394, EnemyEtis, "EnemyEtis-499");
				break;
			}
			case 10990: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000375);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000395, EnemyEtis, "EnemyEtis-500");
				break;
			}
			case 11000: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001781);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001787, EnemyDrastea, "EnemyDrastea-501");
				break;
			}
			case 11020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000376);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000396, EnemyEtis, "EnemyEtis-502");
				break;
			}
			case 11050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000377);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000397, EnemyEtis, "EnemyEtis-503");
				break;
			}
			case 11080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000378);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000398, EnemyEtis, "EnemyEtis-504");
				break;
			}
			case 11100: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001782);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001788, EnemyDrastea, "EnemyDrastea-505");
				break;
			}
			case 11110: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000379);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000399, EnemyEtis, "EnemyEtis-506");
				break;
			}
			case 11140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000380);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000400, EnemyEtis, "EnemyEtis-507");
				break;
			}
			case 11170: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000381);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000401, EnemyEtis, "EnemyEtis-508");
				break;
			}
			case 11200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000382);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000402, EnemyEtis, "EnemyEtis-509");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001783);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001789, EnemyDrastea, "EnemyDrastea-510");
				break;
			}
			case 11230: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000383);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000403, EnemyEtis, "EnemyEtis-511");
				break;
			}
			case 11260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000384);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000404, EnemyEtis, "EnemyEtis-512");
				break;
			}
			case 11290: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000385);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000405, EnemyEtis, "EnemyEtis-513");
				break;
			}
			case 11300: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001784);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001790, EnemyDrastea, "EnemyDrastea-514");
				break;
			}
			case 11320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000386);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000406, EnemyEtis, "EnemyEtis-515");
				break;
			}
			case 11350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000387);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000407, EnemyEtis, "EnemyEtis-516");
				break;
			}
			case 11380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000388);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000408, EnemyEtis, "EnemyEtis-517");
				break;
			}
			case 11400: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001785);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001791, EnemyDrastea, "EnemyDrastea-518");
				break;
			}
			case 11410: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000389);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000409, EnemyEtis, "EnemyEtis-519");
				break;
			}
			case 11440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000390);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000410, EnemyEtis, "EnemyEtis-520");
				break;
			}
			case 11470: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000391);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000411, EnemyEtis, "EnemyEtis-521");
				break;
			}
			case 11500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000392);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000412, EnemyEtis, "EnemyEtis-522");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001786);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001792, EnemyDrastea, "EnemyDrastea-523");
				break;
			}
			case 11530: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000393);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000413, EnemyEtis, "EnemyEtis-524");
				break;
			}
			case 11560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000394);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000414, EnemyEtis, "EnemyEtis-525");
				break;
			}
			case 11590: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000395);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000415, EnemyEtis, "EnemyEtis-526");
				break;
			}
			case 11600: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001787);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001793, EnemyDrastea, "EnemyDrastea-527");
				break;
			}
			case 11620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000396);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000416, EnemyEtis, "EnemyEtis-528");
				break;
			}
			case 11650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000397);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000417, EnemyEtis, "EnemyEtis-529");
				break;
			}
			case 11680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000398);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000418, EnemyEtis, "EnemyEtis-530");
				break;
			}
			case 11700: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001788);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001794, EnemyDrastea, "EnemyDrastea-531");
				break;
			}
			case 11710: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000399);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000419, EnemyEtis, "EnemyEtis-532");
				break;
			}
			case 11740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000400);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000420, EnemyEtis, "EnemyEtis-533");
				break;
			}
			case 11770: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000401);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000421, EnemyEtis, "EnemyEtis-534");
				break;
			}
			case 11800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000402);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000422, EnemyEtis, "EnemyEtis-535");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001789);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001795, EnemyDrastea, "EnemyDrastea-536");
				break;
			}
			case 11830: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000403);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000423, EnemyEtis, "EnemyEtis-537");
				break;
			}
			case 11860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000404);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000424, EnemyEtis, "EnemyEtis-538");
				break;
			}
			case 11890: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000405);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000425, EnemyEtis, "EnemyEtis-539");
				break;
			}
			case 11900: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001790);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001796, EnemyDrastea, "EnemyDrastea-540");
				break;
			}
			case 11920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000406);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000426, EnemyEtis, "EnemyEtis-541");
				break;
			}
			case 11950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000407);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000427, EnemyEtis, "EnemyEtis-542");
				break;
			}
			case 11980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000408);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000428, EnemyEtis, "EnemyEtis-543");
				break;
			}
			case 12000: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001791);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001797, EnemyDrastea, "EnemyDrastea-544");
				break;
			}
			case 12010: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000409);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000429, EnemyEtis, "EnemyEtis-545");
				break;
			}
			case 12040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000410);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000430, EnemyEtis, "EnemyEtis-546");
				break;
			}
			case 12070: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000411);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000431, EnemyEtis, "EnemyEtis-547");
				break;
			}
			case 12100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000412);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000432, EnemyEtis, "EnemyEtis-548");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001792);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001798, EnemyDrastea, "EnemyDrastea-549");
				break;
			}
			case 12130: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000413);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000433, EnemyEtis, "EnemyEtis-550");
				break;
			}
			case 12160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000414);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000434, EnemyEtis, "EnemyEtis-551");
				break;
			}
			case 12190: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000415);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000435, EnemyEtis, "EnemyEtis-552");
				break;
			}
			case 12200: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001793);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001799, EnemyDrastea, "EnemyDrastea-553");
				break;
			}
			case 12220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000416);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000436, EnemyEtis, "EnemyEtis-554");
				break;
			}
			case 12250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000417);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000437, EnemyEtis, "EnemyEtis-555");
				break;
			}
			case 12280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000418);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000438, EnemyEtis, "EnemyEtis-556");
				break;
			}
			case 12300: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001794);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001800, EnemyDrastea, "EnemyDrastea-557");
				break;
			}
			case 12310: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000419);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000439, EnemyEtis, "EnemyEtis-558");
				break;
			}
			case 12340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000420);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000440, EnemyEtis, "EnemyEtis-559");
				break;
			}
			case 12370: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000421);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000441, EnemyEtis, "EnemyEtis-560");
				break;
			}
			case 12400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000422);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000442, EnemyEtis, "EnemyEtis-561");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001795);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001801, EnemyDrastea, "EnemyDrastea-562");
				break;
			}
			case 12430: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000423);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000443, EnemyEtis, "EnemyEtis-563");
				break;
			}
			case 12460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000424);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000444, EnemyEtis, "EnemyEtis-564");
				break;
			}
			case 12490: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000425);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000445, EnemyEtis, "EnemyEtis-565");
				break;
			}
			case 12500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001796);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001802, EnemyDrastea, "EnemyDrastea-566");
				break;
			}
			case 12520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000426);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000446, EnemyEtis, "EnemyEtis-567");
				break;
			}
			case 12550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000427);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000447, EnemyEtis, "EnemyEtis-568");
				break;
			}
			case 12580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000428);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000448, EnemyEtis, "EnemyEtis-569");
				break;
			}
			case 12600: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001797);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001803, EnemyDrastea, "EnemyDrastea-570");
				break;
			}
			case 12610: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000429);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000449, EnemyEtis, "EnemyEtis-571");
				break;
			}
			case 12640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000430);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000450, EnemyEtis, "EnemyEtis-572");
				break;
			}
			case 12670: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000431);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000451, EnemyEtis, "EnemyEtis-573");
				break;
			}
			case 12700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000432);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000452, EnemyEtis, "EnemyEtis-574");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001798);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001804, EnemyDrastea, "EnemyDrastea-575");
				break;
			}
			case 12730: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000433);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000453, EnemyEtis, "EnemyEtis-576");
				break;
			}
			case 12760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000434);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000454, EnemyEtis, "EnemyEtis-577");
				break;
			}
			case 12790: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000435);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000455, EnemyEtis, "EnemyEtis-578");
				break;
			}
			case 12800: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001799);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001805, EnemyDrastea, "EnemyDrastea-579");
				break;
			}
			case 12820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000436);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000456, EnemyEtis, "EnemyEtis-580");
				break;
			}
			case 12850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000437);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000457, EnemyEtis, "EnemyEtis-581");
				break;
			}
			case 12880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000438);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000458, EnemyEtis, "EnemyEtis-582");
				break;
			}
			case 12900: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001800);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001806, EnemyDrastea, "EnemyDrastea-583");
				break;
			}
			case 12910: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000439);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000459, EnemyEtis, "EnemyEtis-584");
				break;
			}
			case 12940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000440);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000460, EnemyEtis, "EnemyEtis-585");
				break;
			}
			case 12970: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000441);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000461, EnemyEtis, "EnemyEtis-586");
				break;
			}
			case 13000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000442);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000462, EnemyEtis, "EnemyEtis-587");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001801);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001807, EnemyDrastea, "EnemyDrastea-588");
				break;
			}
			case 13030: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000443);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000463, EnemyEtis, "EnemyEtis-589");
				break;
			}
			case 13060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000444);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000464, EnemyEtis, "EnemyEtis-590");
				break;
			}
			case 13090: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000445);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000465, EnemyEtis, "EnemyEtis-591");
				break;
			}
			case 13100: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001802);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001808, EnemyDrastea, "EnemyDrastea-592");
				break;
			}
			case 13120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000446);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000466, EnemyEtis, "EnemyEtis-593");
				break;
			}
			case 13150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000447);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000467, EnemyEtis, "EnemyEtis-594");
				break;
			}
			case 13180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000448);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000468, EnemyEtis, "EnemyEtis-595");
				break;
			}
			case 13200: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001803);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001809, EnemyDrastea, "EnemyDrastea-596");
				break;
			}
			case 13210: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000449);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000469, EnemyEtis, "EnemyEtis-597");
				break;
			}
			case 13240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000450);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000470, EnemyEtis, "EnemyEtis-598");
				break;
			}
			case 13270: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000451);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000471, EnemyEtis, "EnemyEtis-599");
				break;
			}
			case 13300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000452);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000472, EnemyEtis, "EnemyEtis-600");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001804);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001810, EnemyDrastea, "EnemyDrastea-601");
				break;
			}
			case 13330: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000453);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000473, EnemyEtis, "EnemyEtis-602");
				break;
			}
			case 13360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000454);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000474, EnemyEtis, "EnemyEtis-603");
				break;
			}
			case 13390: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000455);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000475, EnemyEtis, "EnemyEtis-604");
				break;
			}
			case 13400: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001805);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001811, EnemyDrastea, "EnemyDrastea-605");
				break;
			}
			case 13420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000456);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000476, EnemyEtis, "EnemyEtis-606");
				break;
			}
			case 13450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000457);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000477, EnemyEtis, "EnemyEtis-607");
				break;
			}
			case 13480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000458);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000478, EnemyEtis, "EnemyEtis-608");
				break;
			}
			case 13500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001806);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001812, EnemyDrastea, "EnemyDrastea-609");
				break;
			}
			case 13510: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000459);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000479, EnemyEtis, "EnemyEtis-610");
				break;
			}
			case 13540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000460);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000480, EnemyEtis, "EnemyEtis-611");
				break;
			}
			case 13570: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000461);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000481, EnemyEtis, "EnemyEtis-612");
				break;
			}
			case 13600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000462);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000482, EnemyEtis, "EnemyEtis-613");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001807);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001813, EnemyDrastea, "EnemyDrastea-614");
				break;
			}
			case 13630: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000463);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000483, EnemyEtis, "EnemyEtis-615");
				break;
			}
			case 13660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000464);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000484, EnemyEtis, "EnemyEtis-616");
				break;
			}
			case 13690: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000465);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000485, EnemyEtis, "EnemyEtis-617");
				break;
			}
			case 13700: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001808);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001814, EnemyDrastea, "EnemyDrastea-618");
				break;
			}
			case 13720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000466);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000486, EnemyEtis, "EnemyEtis-619");
				break;
			}
			case 13750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000467);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000487, EnemyEtis, "EnemyEtis-620");
				break;
			}
			case 13780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000468);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000488, EnemyEtis, "EnemyEtis-621");
				break;
			}
			case 13800: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001809);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001815, EnemyDrastea, "EnemyDrastea-622");
				break;
			}
			case 13810: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000469);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000489, EnemyEtis, "EnemyEtis-623");
				break;
			}
			case 13840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000470);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000490, EnemyEtis, "EnemyEtis-624");
				break;
			}
			case 13870: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000471);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000491, EnemyEtis, "EnemyEtis-625");
				break;
			}
			case 13900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000472);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000492, EnemyEtis, "EnemyEtis-626");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001810);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001816, EnemyDrastea, "EnemyDrastea-627");
				break;
			}
			case 13930: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000473);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000493, EnemyEtis, "EnemyEtis-628");
				break;
			}
			case 13960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000474);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000494, EnemyEtis, "EnemyEtis-629");
				break;
			}
			case 13990: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000475);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000495, EnemyEtis, "EnemyEtis-630");
				break;
			}
			case 14000: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001811);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001817, EnemyDrastea, "EnemyDrastea-631");
				break;
			}
			case 14020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000476);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000496, EnemyEtis, "EnemyEtis-632");
				break;
			}
			case 14050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000477);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000497, EnemyEtis, "EnemyEtis-633");
				break;
			}
			case 14080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000478);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000498, EnemyEtis, "EnemyEtis-634");
				break;
			}
			case 14100: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001812);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001818, EnemyDrastea, "EnemyDrastea-635");
				break;
			}
			case 14110: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000479);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000499, EnemyEtis, "EnemyEtis-636");
				break;
			}
			case 14140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000480);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000500, EnemyEtis, "EnemyEtis-637");
				break;
			}
			case 14170: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000481);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000501, EnemyEtis, "EnemyEtis-638");
				break;
			}
			case 14200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000482);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000502, EnemyEtis, "EnemyEtis-639");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001813);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001819, EnemyDrastea, "EnemyDrastea-640");
				break;
			}
			case 14230: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000483);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000503, EnemyEtis, "EnemyEtis-641");
				break;
			}
			case 14260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000484);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000504, EnemyEtis, "EnemyEtis-642");
				break;
			}
			case 14290: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000485);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000505, EnemyEtis, "EnemyEtis-643");
				break;
			}
			case 14300: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001814);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001820, EnemyDrastea, "EnemyDrastea-644");
				break;
			}
			case 14320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000486);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000506, EnemyEtis, "EnemyEtis-645");
				break;
			}
			case 14350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000487);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000507, EnemyEtis, "EnemyEtis-646");
				break;
			}
			case 14380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000488);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000508, EnemyEtis, "EnemyEtis-647");
				break;
			}
			case 14400: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001815);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001821, EnemyDrastea, "EnemyDrastea-648");
				break;
			}
			case 14410: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000489);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000509, EnemyEtis, "EnemyEtis-649");
				break;
			}
			case 14440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000490);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000510, EnemyEtis, "EnemyEtis-650");
				break;
			}
			case 14470: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000491);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000511, EnemyEtis, "EnemyEtis-651");
				break;
			}
			case 14500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000492);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000512, EnemyEtis, "EnemyEtis-652");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001816);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001822, EnemyDrastea, "EnemyDrastea-653");
				break;
			}
			case 14530: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000493);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000513, EnemyEtis, "EnemyEtis-654");
				break;
			}
			case 14560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000494);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000514, EnemyEtis, "EnemyEtis-655");
				break;
			}
			case 14590: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000495);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000515, EnemyEtis, "EnemyEtis-656");
				break;
			}
			case 14600: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001817);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001823, EnemyDrastea, "EnemyDrastea-657");
				break;
			}
			case 14620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000496);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000516, EnemyEtis, "EnemyEtis-658");
				break;
			}
			case 14650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000497);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000517, EnemyEtis, "EnemyEtis-659");
				break;
			}
			case 14680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000498);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000518, EnemyEtis, "EnemyEtis-660");
				break;
			}
			case 14700: {
				orderActorToFactory(10000005, EnemyErmione, "EnemyErmione-661");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001818);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001824, EnemyDrastea, "EnemyDrastea-662");
				break;
			}
			case 14710: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000499);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000519, EnemyEtis, "EnemyEtis-663");
				break;
			}
			case 14740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000500);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000520, EnemyEtis, "EnemyEtis-664");
				break;
			}
			case 14770: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000501);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000521, EnemyEtis, "EnemyEtis-665");
				break;
			}
			case 14800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000502);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000522, EnemyEtis, "EnemyEtis-666");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001819);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001825, EnemyDrastea, "EnemyDrastea-667");
				break;
			}
			case 14830: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000503);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000523, EnemyEtis, "EnemyEtis-668");
				break;
			}
			case 14860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000504);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000524, EnemyEtis, "EnemyEtis-669");
				break;
			}
			case 14890: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000505);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000525, EnemyEtis, "EnemyEtis-670");
				break;
			}
			case 14900: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001820);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001826, EnemyDrastea, "EnemyDrastea-671");
				break;
			}
			case 14920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000506);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000526, EnemyEtis, "EnemyEtis-672");
				break;
			}
			case 14950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000507);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000527, EnemyEtis, "EnemyEtis-673");
				break;
			}
			case 14980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000508);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000528, EnemyEtis, "EnemyEtis-674");
				break;
			}
			case 15000: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001821);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001827, EnemyDrastea, "EnemyDrastea-675");
				break;
			}
			case 15010: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000509);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000529, EnemyEtis, "EnemyEtis-676");
				break;
			}
			case 15040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000510);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000530, EnemyEtis, "EnemyEtis-677");
				break;
			}
			case 15070: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000511);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000531, EnemyEtis, "EnemyEtis-678");
				break;
			}
			case 15100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000512);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000532, EnemyEtis, "EnemyEtis-679");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001822);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001828, EnemyDrastea, "EnemyDrastea-680");
				break;
			}
			case 15130: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000513);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000533, EnemyEtis, "EnemyEtis-681");
				break;
			}
			case 15160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000514);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000534, EnemyEtis, "EnemyEtis-682");
				break;
			}
			case 15190: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000515);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000535, EnemyEtis, "EnemyEtis-683");
				break;
			}
			case 15200: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001823);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001829, EnemyDrastea, "EnemyDrastea-684");
				break;
			}
			case 15220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000516);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000536, EnemyEtis, "EnemyEtis-685");
				break;
			}
			case 15250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000517);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000537, EnemyEtis, "EnemyEtis-686");
				break;
			}
			case 15280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000518);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000538, EnemyEtis, "EnemyEtis-687");
				break;
			}
			case 15300: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(10000005);
				bringDirector()->addSubGroup(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001824);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001830, EnemyDrastea, "EnemyDrastea-688");
				break;
			}
			case 15310: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000519);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000539, EnemyEtis, "EnemyEtis-689");
				break;
			}
			case 15340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000520);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000540, EnemyEtis, "EnemyEtis-690");
				break;
			}
			case 15370: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000521);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000541, EnemyEtis, "EnemyEtis-691");
				break;
			}
			case 15400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000522);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000542, EnemyEtis, "EnemyEtis-692");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001825);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001831, EnemyDrastea, "EnemyDrastea-693");
				break;
			}
			case 15430: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000523);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000543, EnemyEtis, "EnemyEtis-694");
				break;
			}
			case 15460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000524);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000544, EnemyEtis, "EnemyEtis-695");
				break;
			}
			case 15490: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000525);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000545, EnemyEtis, "EnemyEtis-696");
				break;
			}
			case 15500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001826);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001832, EnemyDrastea, "EnemyDrastea-697");
				break;
			}
			case 15520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000526);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000546, EnemyEtis, "EnemyEtis-698");
				break;
			}
			case 15550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000527);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000547, EnemyEtis, "EnemyEtis-699");
				break;
			}
			case 15580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000528);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000548, EnemyEtis, "EnemyEtis-700");
				break;
			}
			case 15600: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001827);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001833, EnemyDrastea, "EnemyDrastea-701");
				break;
			}
			case 15610: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000529);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000549, EnemyEtis, "EnemyEtis-702");
				break;
			}
			case 15640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000530);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000550, EnemyEtis, "EnemyEtis-703");
				break;
			}
			case 15670: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000531);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000551, EnemyEtis, "EnemyEtis-704");
				break;
			}
			case 15700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000532);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000552, EnemyEtis, "EnemyEtis-705");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001828);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001834, EnemyDrastea, "EnemyDrastea-706");
				break;
			}
			case 15730: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000533);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000553, EnemyEtis, "EnemyEtis-707");
				break;
			}
			case 15760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000534);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000554, EnemyEtis, "EnemyEtis-708");
				break;
			}
			case 15790: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000535);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000555, EnemyEtis, "EnemyEtis-709");
				break;
			}
			case 15800: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001829);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001835, EnemyDrastea, "EnemyDrastea-710");
				break;
			}
			case 15820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000536);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000556, EnemyEtis, "EnemyEtis-711");
				break;
			}
			case 15850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000537);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000557, EnemyEtis, "EnemyEtis-712");
				break;
			}
			case 15880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000538);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000558, EnemyEtis, "EnemyEtis-713");
				break;
			}
			case 15900: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001830);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001836, EnemyDrastea, "EnemyDrastea-714");
				break;
			}
			case 15910: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000539);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000559, EnemyEtis, "EnemyEtis-715");
				break;
			}
			case 15940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000540);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000560, EnemyEtis, "EnemyEtis-716");
				break;
			}
			case 15970: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000541);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000561, EnemyEtis, "EnemyEtis-717");
				break;
			}
			case 16000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000542);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000562, EnemyEtis, "EnemyEtis-718");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001831);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001837, EnemyDrastea, "EnemyDrastea-719");
				break;
			}
			case 16030: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000543);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000563, EnemyEtis, "EnemyEtis-720");
				break;
			}
			case 16060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000544);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000564, EnemyEtis, "EnemyEtis-721");
				break;
			}
			case 16090: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000545);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000565, EnemyEtis, "EnemyEtis-722");
				break;
			}
			case 16100: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001832);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001838, EnemyDrastea, "EnemyDrastea-723");
				break;
			}
			case 16120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000546);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000566, EnemyEtis, "EnemyEtis-724");
				break;
			}
			case 16150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000547);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000567, EnemyEtis, "EnemyEtis-725");
				break;
			}
			case 16180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000548);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000568, EnemyEtis, "EnemyEtis-726");
				break;
			}
			case 16200: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001833);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001839, EnemyDrastea, "EnemyDrastea-727");
				break;
			}
			case 16210: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000549);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000569, EnemyEtis, "EnemyEtis-728");
				break;
			}
			case 16240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000550);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000570, EnemyEtis, "EnemyEtis-729");
				break;
			}
			case 16270: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000551);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000571, EnemyEtis, "EnemyEtis-730");
				break;
			}
			case 16300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000552);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000572, EnemyEtis, "EnemyEtis-731");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001834);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001840, EnemyDrastea, "EnemyDrastea-732");
				break;
			}
			case 16330: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000553);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000573, EnemyEtis, "EnemyEtis-733");
				break;
			}
			case 16360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000554);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000574, EnemyEtis, "EnemyEtis-734");
				break;
			}
			case 16390: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000555);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000575, EnemyEtis, "EnemyEtis-735");
				break;
			}
			case 16400: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001835);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001841, EnemyDrastea, "EnemyDrastea-736");
				break;
			}
			case 16420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000556);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000576, EnemyEtis, "EnemyEtis-737");
				break;
			}
			case 16450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000557);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000577, EnemyEtis, "EnemyEtis-738");
				break;
			}
			case 16480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000558);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000578, EnemyEtis, "EnemyEtis-739");
				break;
			}
			case 16500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001836);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001842, EnemyDrastea, "EnemyDrastea-740");
				break;
			}
			case 16510: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000559);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000579, EnemyEtis, "EnemyEtis-741");
				break;
			}
			case 16540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000560);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000580, EnemyEtis, "EnemyEtis-742");
				break;
			}
			case 16570: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000561);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000581, EnemyEtis, "EnemyEtis-743");
				break;
			}
			case 16600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000562);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000582, EnemyEtis, "EnemyEtis-744");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001837);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001843, EnemyDrastea, "EnemyDrastea-745");
				break;
			}
			case 16630: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000563);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000583, EnemyEtis, "EnemyEtis-746");
				break;
			}
			case 16660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000564);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000584, EnemyEtis, "EnemyEtis-747");
				break;
			}
			case 16690: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000565);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000585, EnemyEtis, "EnemyEtis-748");
				break;
			}
			case 16700: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001838);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001844, EnemyDrastea, "EnemyDrastea-749");
				break;
			}
			case 16720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000566);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000586, EnemyEtis, "EnemyEtis-750");
				break;
			}
			case 16750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000567);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000587, EnemyEtis, "EnemyEtis-751");
				break;
			}
			case 16780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000568);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000588, EnemyEtis, "EnemyEtis-752");
				break;
			}
			case 16800: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001839);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001845, EnemyDrastea, "EnemyDrastea-753");
				break;
			}
			case 16810: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000569);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000589, EnemyEtis, "EnemyEtis-754");
				break;
			}
			case 16840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000570);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000590, EnemyEtis, "EnemyEtis-755");
				break;
			}
			case 16870: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000571);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000591, EnemyEtis, "EnemyEtis-756");
				break;
			}
			case 16900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000572);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000592, EnemyEtis, "EnemyEtis-757");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001840);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001846, EnemyDrastea, "EnemyDrastea-758");
				break;
			}
			case 16930: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000573);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000593, EnemyEtis, "EnemyEtis-759");
				break;
			}
			case 16960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000574);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000594, EnemyEtis, "EnemyEtis-760");
				break;
			}
			case 16990: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000575);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000595, EnemyEtis, "EnemyEtis-761");
				break;
			}
			case 17000: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001841);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001847, EnemyDrastea, "EnemyDrastea-762");
				break;
			}
			case 17020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000576);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000596, EnemyEtis, "EnemyEtis-763");
				break;
			}
			case 17050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000577);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000597, EnemyEtis, "EnemyEtis-764");
				break;
			}
			case 17080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000578);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000598, EnemyEtis, "EnemyEtis-765");
				break;
			}
			case 17100: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001842);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001848, EnemyDrastea, "EnemyDrastea-766");
				break;
			}
			case 17110: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000579);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000599, EnemyEtis, "EnemyEtis-767");
				break;
			}
			case 17140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000580);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000600, EnemyEtis, "EnemyEtis-768");
				break;
			}
			case 17170: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000581);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000601, EnemyEtis, "EnemyEtis-769");
				break;
			}
			case 17200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000582);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000602, EnemyEtis, "EnemyEtis-770");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001843);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001849, EnemyDrastea, "EnemyDrastea-771");
				break;
			}
			case 17230: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000583);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000603, EnemyEtis, "EnemyEtis-772");
				break;
			}
			case 17260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000584);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000604, EnemyEtis, "EnemyEtis-773");
				break;
			}
			case 17290: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000585);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000605, EnemyEtis, "EnemyEtis-774");
				break;
			}
			case 17300: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001844);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001850, EnemyDrastea, "EnemyDrastea-775");
				break;
			}
			case 17320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000586);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000606, EnemyEtis, "EnemyEtis-776");
				break;
			}
			case 17350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000587);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000607, EnemyEtis, "EnemyEtis-777");
				break;
			}
			case 17380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000588);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000608, EnemyEtis, "EnemyEtis-778");
				break;
			}
			case 17400: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001845);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001851, EnemyDrastea, "EnemyDrastea-779");
				break;
			}
			case 17410: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000589);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000609, EnemyEtis, "EnemyEtis-780");
				break;
			}
			case 17440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000590);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000610, EnemyEtis, "EnemyEtis-781");
				break;
			}
			case 17470: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000591);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000611, EnemyEtis, "EnemyEtis-782");
				break;
			}
			case 17500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000592);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000612, EnemyEtis, "EnemyEtis-783");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001846);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001852, EnemyDrastea, "EnemyDrastea-784");
				break;
			}
			case 17530: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000593);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000613, EnemyEtis, "EnemyEtis-785");
				break;
			}
			case 17560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000594);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000614, EnemyEtis, "EnemyEtis-786");
				break;
			}
			case 17590: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000595);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000615, EnemyEtis, "EnemyEtis-787");
				break;
			}
			case 17600: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001847);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001853, EnemyDrastea, "EnemyDrastea-788");
				break;
			}
			case 17620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000596);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000616, EnemyEtis, "EnemyEtis-789");
				break;
			}
			case 17650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000597);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000617, EnemyEtis, "EnemyEtis-790");
				break;
			}
			case 17680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000598);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000618, EnemyEtis, "EnemyEtis-791");
				break;
			}
			case 17700: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001848);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001854, EnemyDrastea, "EnemyDrastea-792");
				break;
			}
			case 17710: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000599);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000619, EnemyEtis, "EnemyEtis-793");
				break;
			}
			case 17740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000600);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000620, EnemyEtis, "EnemyEtis-794");
				break;
			}
			case 17770: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000601);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000621, EnemyEtis, "EnemyEtis-795");
				break;
			}
			case 17800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000602);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000622, EnemyEtis, "EnemyEtis-796");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001849);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001855, EnemyDrastea, "EnemyDrastea-797");
				break;
			}
			case 17830: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000603);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000623, EnemyEtis, "EnemyEtis-798");
				break;
			}
			case 17860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000604);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000624, EnemyEtis, "EnemyEtis-799");
				break;
			}
			case 17890: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000605);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000625, EnemyEtis, "EnemyEtis-800");
				break;
			}
			case 17900: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001850);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001856, EnemyDrastea, "EnemyDrastea-801");
				break;
			}
			case 17920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000606);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000626, EnemyEtis, "EnemyEtis-802");
				break;
			}
			case 17950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000607);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000627, EnemyEtis, "EnemyEtis-803");
				break;
			}
			case 17980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000608);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000628, EnemyEtis, "EnemyEtis-804");
				break;
			}
			case 18000: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001851);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001857, EnemyDrastea, "EnemyDrastea-805");
				break;
			}
			case 18010: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000609);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000629, EnemyEtis, "EnemyEtis-806");
				break;
			}
			case 18040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000610);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000630, EnemyEtis, "EnemyEtis-807");
				break;
			}
			case 18070: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000611);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000631, EnemyEtis, "EnemyEtis-808");
				break;
			}
			case 18100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000612);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000632, EnemyEtis, "EnemyEtis-809");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001852);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001858, EnemyDrastea, "EnemyDrastea-810");
				break;
			}
			case 18130: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000613);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000633, EnemyEtis, "EnemyEtis-811");
				break;
			}
			case 18160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000614);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000634, EnemyEtis, "EnemyEtis-812");
				break;
			}
			case 18190: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000615);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000635, EnemyEtis, "EnemyEtis-813");
				break;
			}
			case 18200: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001853);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001859, EnemyDrastea, "EnemyDrastea-814");
				break;
			}
			case 18220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000616);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000636, EnemyEtis, "EnemyEtis-815");
				break;
			}
			case 18250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000617);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000637, EnemyEtis, "EnemyEtis-816");
				break;
			}
			case 18280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000618);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000638, EnemyEtis, "EnemyEtis-817");
				break;
			}
			case 18300: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001854);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001860, EnemyDrastea, "EnemyDrastea-818");
				break;
			}
			case 18310: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000619);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000639, EnemyEtis, "EnemyEtis-819");
				break;
			}
			case 18340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000620);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000640, EnemyEtis, "EnemyEtis-820");
				break;
			}
			case 18370: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000621);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000641, EnemyEtis, "EnemyEtis-821");
				break;
			}
			case 18400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000622);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000642, EnemyEtis, "EnemyEtis-822");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001855);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001861, EnemyDrastea, "EnemyDrastea-823");
				break;
			}
			case 18430: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000623);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000643, EnemyEtis, "EnemyEtis-824");
				break;
			}
			case 18460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000624);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000644, EnemyEtis, "EnemyEtis-825");
				break;
			}
			case 18490: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000625);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000645, EnemyEtis, "EnemyEtis-826");
				break;
			}
			case 18500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001856);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001862, EnemyDrastea, "EnemyDrastea-827");
				break;
			}
			case 18520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000626);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000646, EnemyEtis, "EnemyEtis-828");
				break;
			}
			case 18550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000627);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000647, EnemyEtis, "EnemyEtis-829");
				break;
			}
			case 18580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000628);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000648, EnemyEtis, "EnemyEtis-830");
				break;
			}
			case 18600: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001857);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001863, EnemyDrastea, "EnemyDrastea-831");
				break;
			}
			case 18610: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000629);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000649, EnemyEtis, "EnemyEtis-832");
				break;
			}
			case 18640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000630);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000650, EnemyEtis, "EnemyEtis-833");
				break;
			}
			case 18670: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000631);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000651, EnemyEtis, "EnemyEtis-834");
				break;
			}
			case 18700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000632);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000652, EnemyEtis, "EnemyEtis-835");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001858);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001864, EnemyDrastea, "EnemyDrastea-836");
				break;
			}
			case 18730: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000633);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000653, EnemyEtis, "EnemyEtis-837");
				break;
			}
			case 18760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000634);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000654, EnemyEtis, "EnemyEtis-838");
				break;
			}
			case 18790: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000635);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000655, EnemyEtis, "EnemyEtis-839");
				break;
			}
			case 18800: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001859);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001865, EnemyDrastea, "EnemyDrastea-840");
				break;
			}
			case 18820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000636);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000656, EnemyEtis, "EnemyEtis-841");
				break;
			}
			case 18850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000637);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000657, EnemyEtis, "EnemyEtis-842");
				break;
			}
			case 18880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000638);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000658, EnemyEtis, "EnemyEtis-843");
				break;
			}
			case 18900: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001860);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001866, EnemyDrastea, "EnemyDrastea-844");
				break;
			}
			case 18910: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000639);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000659, EnemyEtis, "EnemyEtis-845");
				break;
			}
			case 18940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000640);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000660, EnemyEtis, "EnemyEtis-846");
				break;
			}
			case 18970: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000641);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000661, EnemyEtis, "EnemyEtis-847");
				break;
			}
			case 19000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000642);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000662, EnemyEtis, "EnemyEtis-848");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001861);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001867, EnemyDrastea, "EnemyDrastea-849");
				break;
			}
			case 19030: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000643);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000663, EnemyEtis, "EnemyEtis-850");
				break;
			}
			case 19060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000644);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000664, EnemyEtis, "EnemyEtis-851");
				break;
			}
			case 19090: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000645);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000665, EnemyEtis, "EnemyEtis-852");
				break;
			}
			case 19100: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001862);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001868, EnemyDrastea, "EnemyDrastea-853");
				break;
			}
			case 19120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000646);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000666, EnemyEtis, "EnemyEtis-854");
				break;
			}
			case 19150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000647);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000667, EnemyEtis, "EnemyEtis-855");
				break;
			}
			case 19180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000648);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000668, EnemyEtis, "EnemyEtis-856");
				break;
			}
			case 19200: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001863);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001869, EnemyDrastea, "EnemyDrastea-857");
				break;
			}
			case 19210: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000649);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000669, EnemyEtis, "EnemyEtis-858");
				break;
			}
			case 19240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000650);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000670, EnemyEtis, "EnemyEtis-859");
				break;
			}
			case 19270: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000651);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000671, EnemyEtis, "EnemyEtis-860");
				break;
			}
			case 19300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000652);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000672, EnemyEtis, "EnemyEtis-861");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001864);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001870, EnemyDrastea, "EnemyDrastea-862");
				break;
			}
			case 19330: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000653);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000673, EnemyEtis, "EnemyEtis-863");
				break;
			}
			case 19360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000654);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000674, EnemyEtis, "EnemyEtis-864");
				break;
			}
			case 19390: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000655);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000675, EnemyEtis, "EnemyEtis-865");
				break;
			}
			case 19400: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001865);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001871, EnemyDrastea, "EnemyDrastea-866");
				break;
			}
			case 19420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000656);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000676, EnemyEtis, "EnemyEtis-867");
				break;
			}
			case 19450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000657);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000677, EnemyEtis, "EnemyEtis-868");
				break;
			}
			case 19480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000658);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000678, EnemyEtis, "EnemyEtis-869");
				break;
			}
			case 19500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001866);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001872, EnemyDrastea, "EnemyDrastea-870");
				break;
			}
			case 19510: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000659);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000679, EnemyEtis, "EnemyEtis-871");
				break;
			}
			case 19540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000660);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000680, EnemyEtis, "EnemyEtis-872");
				break;
			}
			case 19570: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000661);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000681, EnemyEtis, "EnemyEtis-873");
				break;
			}
			case 19600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000662);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000682, EnemyEtis, "EnemyEtis-874");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001867);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001873, EnemyDrastea, "EnemyDrastea-875");
				break;
			}
			case 19630: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000663);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000683, EnemyEtis, "EnemyEtis-876");
				break;
			}
			case 19660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000664);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000684, EnemyEtis, "EnemyEtis-877");
				break;
			}
			case 19690: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000665);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000685, EnemyEtis, "EnemyEtis-878");
				break;
			}
			case 19700: {
				orderActorToFactory(10000006, EnemyErmione, "EnemyErmione-879");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001868);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001874, EnemyDrastea, "EnemyDrastea-880");
				break;
			}
			case 19720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000666);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000686, EnemyEtis, "EnemyEtis-881");
				break;
			}
			case 19750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000667);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000687, EnemyEtis, "EnemyEtis-882");
				break;
			}
			case 19780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000668);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000688, EnemyEtis, "EnemyEtis-883");
				break;
			}
			case 19800: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001869);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001875, EnemyDrastea, "EnemyDrastea-884");
				break;
			}
			case 19810: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000669);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000689, EnemyEtis, "EnemyEtis-885");
				break;
			}
			case 19840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000670);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000690, EnemyEtis, "EnemyEtis-886");
				break;
			}
			case 19870: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000671);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000691, EnemyEtis, "EnemyEtis-887");
				break;
			}
			case 19900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000672);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000692, EnemyEtis, "EnemyEtis-888");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001870);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001876, EnemyDrastea, "EnemyDrastea-889");
				break;
			}
			case 19930: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000673);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000693, EnemyEtis, "EnemyEtis-890");
				break;
			}
			case 19960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000674);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000694, EnemyEtis, "EnemyEtis-891");
				break;
			}
			case 19990: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000675);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000695, EnemyEtis, "EnemyEtis-892");
				break;
			}
			case 20000: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001871);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001877, EnemyDrastea, "EnemyDrastea-893");
				break;
			}
			case 20020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000676);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000696, EnemyEtis, "EnemyEtis-894");
				break;
			}
			case 20050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000677);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000697, EnemyEtis, "EnemyEtis-895");
				break;
			}
			case 20080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000678);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000698, EnemyEtis, "EnemyEtis-896");
				break;
			}
			case 20100: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001872);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001878, EnemyDrastea, "EnemyDrastea-897");
				break;
			}
			case 20110: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000679);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000699, EnemyEtis, "EnemyEtis-898");
				break;
			}
			case 20140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000680);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000700, EnemyEtis, "EnemyEtis-899");
				break;
			}
			case 20170: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000681);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000701, EnemyEtis, "EnemyEtis-900");
				break;
			}
			case 20200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000682);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000702, EnemyEtis, "EnemyEtis-901");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001873);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001879, EnemyDrastea, "EnemyDrastea-902");
				break;
			}
			case 20230: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000683);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000703, EnemyEtis, "EnemyEtis-903");
				break;
			}
			case 20260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000684);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000704, EnemyEtis, "EnemyEtis-904");
				break;
			}
			case 20290: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000685);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000705, EnemyEtis, "EnemyEtis-905");
				break;
			}
			case 20300: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(10000006);
				bringDirector()->addSubGroup(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001874);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001880, EnemyDrastea, "EnemyDrastea-906");
				break;
			}
			case 20320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000686);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000706, EnemyEtis, "EnemyEtis-907");
				break;
			}
			case 20350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000687);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000707, EnemyEtis, "EnemyEtis-908");
				break;
			}
			case 20380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000688);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000708, EnemyEtis, "EnemyEtis-909");
				break;
			}
			case 20400: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001875);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001881, EnemyDrastea, "EnemyDrastea-910");
				break;
			}
			case 20410: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000689);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000709, EnemyEtis, "EnemyEtis-911");
				break;
			}
			case 20440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000690);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000710, EnemyEtis, "EnemyEtis-912");
				break;
			}
			case 20470: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000691);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000711, EnemyEtis, "EnemyEtis-913");
				break;
			}
			case 20500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000692);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000712, EnemyEtis, "EnemyEtis-914");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001876);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001882, EnemyDrastea, "EnemyDrastea-915");
				break;
			}
			case 20530: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000693);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000713, EnemyEtis, "EnemyEtis-916");
				break;
			}
			case 20560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000694);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000714, EnemyEtis, "EnemyEtis-917");
				break;
			}
			case 20590: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000695);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000715, EnemyEtis, "EnemyEtis-918");
				break;
			}
			case 20600: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001877);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001883, EnemyDrastea, "EnemyDrastea-919");
				break;
			}
			case 20620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000696);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000716, EnemyEtis, "EnemyEtis-920");
				break;
			}
			case 20650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000697);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000717, EnemyEtis, "EnemyEtis-921");
				break;
			}
			case 20680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000698);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000718, EnemyEtis, "EnemyEtis-922");
				break;
			}
			case 20700: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001878);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001884, EnemyDrastea, "EnemyDrastea-923");
				break;
			}
			case 20710: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000699);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000719, EnemyEtis, "EnemyEtis-924");
				break;
			}
			case 20740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000700);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000720, EnemyEtis, "EnemyEtis-925");
				break;
			}
			case 20770: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000701);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000721, EnemyEtis, "EnemyEtis-926");
				break;
			}
			case 20800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000702);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000722, EnemyEtis, "EnemyEtis-927");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001879);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001885, EnemyDrastea, "EnemyDrastea-928");
				break;
			}
			case 20830: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000703);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000723, EnemyEtis, "EnemyEtis-929");
				break;
			}
			case 20860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000704);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000724, EnemyEtis, "EnemyEtis-930");
				break;
			}
			case 20890: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000705);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000725, EnemyEtis, "EnemyEtis-931");
				break;
			}
			case 20900: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001880);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001886, EnemyDrastea, "EnemyDrastea-932");
				break;
			}
			case 20920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000706);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000726, EnemyEtis, "EnemyEtis-933");
				break;
			}
			case 20950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000707);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000727, EnemyEtis, "EnemyEtis-934");
				break;
			}
			case 20980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000708);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000728, EnemyEtis, "EnemyEtis-935");
				break;
			}
			case 21000: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001881);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001887, EnemyDrastea, "EnemyDrastea-936");
				break;
			}
			case 21010: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000709);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000729, EnemyEtis, "EnemyEtis-937");
				break;
			}
			case 21040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000710);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000730, EnemyEtis, "EnemyEtis-938");
				break;
			}
			case 21070: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000711);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000731, EnemyEtis, "EnemyEtis-939");
				break;
			}
			case 21100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000712);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000732, EnemyEtis, "EnemyEtis-940");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001882);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001888, EnemyDrastea, "EnemyDrastea-941");
				break;
			}
			case 21130: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000713);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000733, EnemyEtis, "EnemyEtis-942");
				break;
			}
			case 21160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000714);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000734, EnemyEtis, "EnemyEtis-943");
				break;
			}
			case 21190: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000715);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000735, EnemyEtis, "EnemyEtis-944");
				break;
			}
			case 21200: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001883);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001889, EnemyDrastea, "EnemyDrastea-945");
				break;
			}
			case 21220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000716);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000736, EnemyEtis, "EnemyEtis-946");
				break;
			}
			case 21250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000717);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000737, EnemyEtis, "EnemyEtis-947");
				break;
			}
			case 21280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000718);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000738, EnemyEtis, "EnemyEtis-948");
				break;
			}
			case 21300: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001884);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001890, EnemyDrastea, "EnemyDrastea-949");
				break;
			}
			case 21310: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000719);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000739, EnemyEtis, "EnemyEtis-950");
				break;
			}
			case 21340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000720);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000740, EnemyEtis, "EnemyEtis-951");
				break;
			}
			case 21370: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000721);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000741, EnemyEtis, "EnemyEtis-952");
				break;
			}
			case 21400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000722);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000742, EnemyEtis, "EnemyEtis-953");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001885);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001891, EnemyDrastea, "EnemyDrastea-954");
				break;
			}
			case 21430: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000723);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000743, EnemyEtis, "EnemyEtis-955");
				break;
			}
			case 21460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000724);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000744, EnemyEtis, "EnemyEtis-956");
				break;
			}
			case 21490: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000725);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000745, EnemyEtis, "EnemyEtis-957");
				break;
			}
			case 21500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001886);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001892, EnemyDrastea, "EnemyDrastea-958");
				break;
			}
			case 21520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000726);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000746, EnemyEtis, "EnemyEtis-959");
				break;
			}
			case 21550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000727);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000747, EnemyEtis, "EnemyEtis-960");
				break;
			}
			case 21580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000728);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000748, EnemyEtis, "EnemyEtis-961");
				break;
			}
			case 21600: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001887);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001893, EnemyDrastea, "EnemyDrastea-962");
				break;
			}
			case 21610: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000729);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000749, EnemyEtis, "EnemyEtis-963");
				break;
			}
			case 21640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000730);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000750, EnemyEtis, "EnemyEtis-964");
				break;
			}
			case 21670: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000731);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000751, EnemyEtis, "EnemyEtis-965");
				break;
			}
			case 21700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000732);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000752, EnemyEtis, "EnemyEtis-966");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001888);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001894, EnemyDrastea, "EnemyDrastea-967");
				break;
			}
			case 21730: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000733);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000753, EnemyEtis, "EnemyEtis-968");
				break;
			}
			case 21760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000734);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000754, EnemyEtis, "EnemyEtis-969");
				break;
			}
			case 21790: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000735);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000755, EnemyEtis, "EnemyEtis-970");
				break;
			}
			case 21800: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001889);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001895, EnemyDrastea, "EnemyDrastea-971");
				break;
			}
			case 21820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000736);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000756, EnemyEtis, "EnemyEtis-972");
				break;
			}
			case 21850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000737);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000757, EnemyEtis, "EnemyEtis-973");
				break;
			}
			case 21880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000738);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000758, EnemyEtis, "EnemyEtis-974");
				break;
			}
			case 21900: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001890);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001896, EnemyDrastea, "EnemyDrastea-975");
				break;
			}
			case 21910: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000739);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000759, EnemyEtis, "EnemyEtis-976");
				break;
			}
			case 21940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000740);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000760, EnemyEtis, "EnemyEtis-977");
				break;
			}
			case 21970: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000741);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000761, EnemyEtis, "EnemyEtis-978");
				break;
			}
			case 22000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000742);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000762, EnemyEtis, "EnemyEtis-979");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001891);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001897, EnemyDrastea, "EnemyDrastea-980");
				break;
			}
			case 22030: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000743);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000763, EnemyEtis, "EnemyEtis-981");
				break;
			}
			case 22060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000744);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000764, EnemyEtis, "EnemyEtis-982");
				break;
			}
			case 22090: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000745);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000765, EnemyEtis, "EnemyEtis-983");
				break;
			}
			case 22100: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001892);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001898, EnemyDrastea, "EnemyDrastea-984");
				break;
			}
			case 22120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000746);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000766, EnemyEtis, "EnemyEtis-985");
				break;
			}
			case 22150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000747);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000767, EnemyEtis, "EnemyEtis-986");
				break;
			}
			case 22180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000748);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000768, EnemyEtis, "EnemyEtis-987");
				break;
			}
			case 22200: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001893);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001899, EnemyDrastea, "EnemyDrastea-988");
				break;
			}
			case 22210: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000749);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000769, EnemyEtis, "EnemyEtis-989");
				break;
			}
			case 22240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000750);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000770, EnemyEtis, "EnemyEtis-990");
				break;
			}
			case 22270: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000751);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000771, EnemyEtis, "EnemyEtis-991");
				break;
			}
			case 22300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000752);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000772, EnemyEtis, "EnemyEtis-992");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001894);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001900, EnemyDrastea, "EnemyDrastea-993");
				break;
			}
			case 22330: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000753);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000773, EnemyEtis, "EnemyEtis-994");
				break;
			}
			case 22360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000754);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000774, EnemyEtis, "EnemyEtis-995");
				break;
			}
			case 22390: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000755);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000775, EnemyEtis, "EnemyEtis-996");
				break;
			}
			case 22400: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001895);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001901, EnemyDrastea, "EnemyDrastea-997");
				break;
			}
			case 22420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000756);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000776, EnemyEtis, "EnemyEtis-998");
				break;
			}
			case 22450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000757);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000777, EnemyEtis, "EnemyEtis-999");
				break;
			}
			case 22480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000758);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000778, EnemyEtis, "EnemyEtis-1000");
				break;
			}
			case 22500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001896);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001902, EnemyDrastea, "EnemyDrastea-1001");
				break;
			}
			case 22510: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000759);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000779, EnemyEtis, "EnemyEtis-1002");
				break;
			}
			case 22540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000760);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000780, EnemyEtis, "EnemyEtis-1003");
				break;
			}
			case 22570: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000761);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000781, EnemyEtis, "EnemyEtis-1004");
				break;
			}
			case 22600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000762);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000782, EnemyEtis, "EnemyEtis-1005");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001897);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001903, EnemyDrastea, "EnemyDrastea-1006");
				break;
			}
			case 22630: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000763);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000783, EnemyEtis, "EnemyEtis-1007");
				break;
			}
			case 22660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000764);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000784, EnemyEtis, "EnemyEtis-1008");
				break;
			}
			case 22690: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000765);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000785, EnemyEtis, "EnemyEtis-1009");
				break;
			}
			case 22700: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001898);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001904, EnemyDrastea, "EnemyDrastea-1010");
				break;
			}
			case 22720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000766);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000786, EnemyEtis, "EnemyEtis-1011");
				break;
			}
			case 22750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000767);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000787, EnemyEtis, "EnemyEtis-1012");
				break;
			}
			case 22780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000768);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000788, EnemyEtis, "EnemyEtis-1013");
				break;
			}
			case 22800: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001899);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001905, EnemyDrastea, "EnemyDrastea-1014");
				break;
			}
			case 22810: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000769);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000789, EnemyEtis, "EnemyEtis-1015");
				break;
			}
			case 22840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000770);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000790, EnemyEtis, "EnemyEtis-1016");
				break;
			}
			case 22870: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000771);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000791, EnemyEtis, "EnemyEtis-1017");
				break;
			}
			case 22900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000772);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000792, EnemyEtis, "EnemyEtis-1018");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001900);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001906, EnemyDrastea, "EnemyDrastea-1019");
				break;
			}
			case 22930: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000773);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000793, EnemyEtis, "EnemyEtis-1020");
				break;
			}
			case 22960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000774);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000794, EnemyEtis, "EnemyEtis-1021");
				break;
			}
			case 22990: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000775);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000795, EnemyEtis, "EnemyEtis-1022");
				break;
			}
			case 23000: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001901);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001907, EnemyDrastea, "EnemyDrastea-1023");
				break;
			}
			case 23020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000776);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000796, EnemyEtis, "EnemyEtis-1024");
				break;
			}
			case 23050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000777);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000797, EnemyEtis, "EnemyEtis-1025");
				break;
			}
			case 23080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000778);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000798, EnemyEtis, "EnemyEtis-1026");
				break;
			}
			case 23100: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001902);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001908, EnemyDrastea, "EnemyDrastea-1027");
				break;
			}
			case 23110: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000779);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000799, EnemyEtis, "EnemyEtis-1028");
				break;
			}
			case 23140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000780);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000800, EnemyEtis, "EnemyEtis-1029");
				break;
			}
			case 23170: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000781);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000801, EnemyEtis, "EnemyEtis-1030");
				break;
			}
			case 23200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000782);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000802, EnemyEtis, "EnemyEtis-1031");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001903);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001909, EnemyDrastea, "EnemyDrastea-1032");
				break;
			}
			case 23230: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000783);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000803, EnemyEtis, "EnemyEtis-1033");
				break;
			}
			case 23260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000784);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000804, EnemyEtis, "EnemyEtis-1034");
				break;
			}
			case 23290: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000785);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000805, EnemyEtis, "EnemyEtis-1035");
				break;
			}
			case 23300: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001904);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001910, EnemyDrastea, "EnemyDrastea-1036");
				break;
			}
			case 23320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000786);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000806, EnemyEtis, "EnemyEtis-1037");
				break;
			}
			case 23350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000787);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000807, EnemyEtis, "EnemyEtis-1038");
				break;
			}
			case 23380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000788);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000808, EnemyEtis, "EnemyEtis-1039");
				break;
			}
			case 23400: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001905);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001911, EnemyDrastea, "EnemyDrastea-1040");
				break;
			}
			case 23410: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000789);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000809, EnemyEtis, "EnemyEtis-1041");
				break;
			}
			case 23440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000790);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000810, EnemyEtis, "EnemyEtis-1042");
				break;
			}
			case 23470: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000791);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000811, EnemyEtis, "EnemyEtis-1043");
				break;
			}
			case 23500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000792);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000812, EnemyEtis, "EnemyEtis-1044");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001906);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001912, EnemyDrastea, "EnemyDrastea-1045");
				break;
			}
			case 23530: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000793);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000813, EnemyEtis, "EnemyEtis-1046");
				break;
			}
			case 23560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000794);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000814, EnemyEtis, "EnemyEtis-1047");
				break;
			}
			case 23590: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000795);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000815, EnemyEtis, "EnemyEtis-1048");
				break;
			}
			case 23600: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001907);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001913, EnemyDrastea, "EnemyDrastea-1049");
				break;
			}
			case 23620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000796);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000816, EnemyEtis, "EnemyEtis-1050");
				break;
			}
			case 23650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000797);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000817, EnemyEtis, "EnemyEtis-1051");
				break;
			}
			case 23680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000798);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000818, EnemyEtis, "EnemyEtis-1052");
				break;
			}
			case 23700: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001908);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001914, EnemyDrastea, "EnemyDrastea-1053");
				break;
			}
			case 23710: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000799);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000819, EnemyEtis, "EnemyEtis-1054");
				break;
			}
			case 23740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000800);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000820, EnemyEtis, "EnemyEtis-1055");
				break;
			}
			case 23770: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000801);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000821, EnemyEtis, "EnemyEtis-1056");
				break;
			}
			case 23800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000802);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000822, EnemyEtis, "EnemyEtis-1057");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001909);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001915, EnemyDrastea, "EnemyDrastea-1058");
				break;
			}
			case 23830: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000803);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000823, EnemyEtis, "EnemyEtis-1059");
				break;
			}
			case 23860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000804);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000824, EnemyEtis, "EnemyEtis-1060");
				break;
			}
			case 23890: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000805);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000825, EnemyEtis, "EnemyEtis-1061");
				break;
			}
			case 23900: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001910);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001916, EnemyDrastea, "EnemyDrastea-1062");
				break;
			}
			case 23920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000806);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000826, EnemyEtis, "EnemyEtis-1063");
				break;
			}
			case 23950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000807);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000827, EnemyEtis, "EnemyEtis-1064");
				break;
			}
			case 23980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000808);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000828, EnemyEtis, "EnemyEtis-1065");
				break;
			}
			case 24000: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001911);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001917, EnemyDrastea, "EnemyDrastea-1066");
				break;
			}
			case 24010: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000809);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000829, EnemyEtis, "EnemyEtis-1067");
				break;
			}
			case 24040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000810);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000830, EnemyEtis, "EnemyEtis-1068");
				break;
			}
			case 24070: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000811);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000831, EnemyEtis, "EnemyEtis-1069");
				break;
			}
			case 24100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000812);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000832, EnemyEtis, "EnemyEtis-1070");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001912);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001918, EnemyDrastea, "EnemyDrastea-1071");
				break;
			}
			case 24130: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000813);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000833, EnemyEtis, "EnemyEtis-1072");
				break;
			}
			case 24160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000814);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000834, EnemyEtis, "EnemyEtis-1073");
				break;
			}
			case 24190: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000815);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000835, EnemyEtis, "EnemyEtis-1074");
				break;
			}
			case 24200: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001913);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001919, EnemyDrastea, "EnemyDrastea-1075");
				break;
			}
			case 24220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000816);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000836, EnemyEtis, "EnemyEtis-1076");
				break;
			}
			case 24250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000817);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000837, EnemyEtis, "EnemyEtis-1077");
				break;
			}
			case 24280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000818);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000838, EnemyEtis, "EnemyEtis-1078");
				break;
			}
			case 24300: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001914);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001920, EnemyDrastea, "EnemyDrastea-1079");
				break;
			}
			case 24310: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000819);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000839, EnemyEtis, "EnemyEtis-1080");
				break;
			}
			case 24340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000820);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000840, EnemyEtis, "EnemyEtis-1081");
				break;
			}
			case 24370: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000821);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000841, EnemyEtis, "EnemyEtis-1082");
				break;
			}
			case 24400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000822);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000842, EnemyEtis, "EnemyEtis-1083");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001915);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001921, EnemyDrastea, "EnemyDrastea-1084");
				break;
			}
			case 24430: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000823);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000843, EnemyEtis, "EnemyEtis-1085");
				break;
			}
			case 24460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000824);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000844, EnemyEtis, "EnemyEtis-1086");
				break;
			}
			case 24490: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000825);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000845, EnemyEtis, "EnemyEtis-1087");
				break;
			}
			case 24500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001916);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001922, EnemyDrastea, "EnemyDrastea-1088");
				break;
			}
			case 24520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000826);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000846, EnemyEtis, "EnemyEtis-1089");
				break;
			}
			case 24550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000827);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000847, EnemyEtis, "EnemyEtis-1090");
				break;
			}
			case 24580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000828);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000848, EnemyEtis, "EnemyEtis-1091");
				break;
			}
			case 24600: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001917);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001923, EnemyDrastea, "EnemyDrastea-1092");
				break;
			}
			case 24610: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000829);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000849, EnemyEtis, "EnemyEtis-1093");
				break;
			}
			case 24640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000830);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000850, EnemyEtis, "EnemyEtis-1094");
				break;
			}
			case 24670: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000831);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000851, EnemyEtis, "EnemyEtis-1095");
				break;
			}
			case 24700: {
				orderActorToFactory(10000007, EnemyErmione, "EnemyErmione-1096");
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000832);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000852, EnemyEtis, "EnemyEtis-1097");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001918);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001924, EnemyDrastea, "EnemyDrastea-1098");
				break;
			}
			case 24730: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000833);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000853, EnemyEtis, "EnemyEtis-1099");
				break;
			}
			case 24760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000834);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000854, EnemyEtis, "EnemyEtis-1100");
				break;
			}
			case 24790: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000835);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000855, EnemyEtis, "EnemyEtis-1101");
				break;
			}
			case 24800: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001919);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001925, EnemyDrastea, "EnemyDrastea-1102");
				break;
			}
			case 24820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000836);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000856, EnemyEtis, "EnemyEtis-1103");
				break;
			}
			case 24850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000837);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000857, EnemyEtis, "EnemyEtis-1104");
				break;
			}
			case 24880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000838);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000858, EnemyEtis, "EnemyEtis-1105");
				break;
			}
			case 24900: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001920);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001926, EnemyDrastea, "EnemyDrastea-1106");
				break;
			}
			case 24910: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000839);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000859, EnemyEtis, "EnemyEtis-1107");
				break;
			}
			case 24940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000840);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000860, EnemyEtis, "EnemyEtis-1108");
				break;
			}
			case 24970: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000841);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000861, EnemyEtis, "EnemyEtis-1109");
				break;
			}
			case 25000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000842);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000862, EnemyEtis, "EnemyEtis-1110");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001921);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001927, EnemyDrastea, "EnemyDrastea-1111");
				break;
			}
			case 25030: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000843);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000863, EnemyEtis, "EnemyEtis-1112");
				break;
			}
			case 25060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000844);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000864, EnemyEtis, "EnemyEtis-1113");
				break;
			}
			case 25090: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000845);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000865, EnemyEtis, "EnemyEtis-1114");
				break;
			}
			case 25100: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001922);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001928, EnemyDrastea, "EnemyDrastea-1115");
				break;
			}
			case 25120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000846);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000866, EnemyEtis, "EnemyEtis-1116");
				break;
			}
			case 25150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000847);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000867, EnemyEtis, "EnemyEtis-1117");
				break;
			}
			case 25180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000848);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000868, EnemyEtis, "EnemyEtis-1118");
				break;
			}
			case 25200: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001923);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001929, EnemyDrastea, "EnemyDrastea-1119");
				break;
			}
			case 25210: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000849);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000869, EnemyEtis, "EnemyEtis-1120");
				break;
			}
			case 25240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000850);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000870, EnemyEtis, "EnemyEtis-1121");
				break;
			}
			case 25270: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000851);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000871, EnemyEtis, "EnemyEtis-1122");
				break;
			}
			case 25300: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(10000007);
				bringDirector()->addSubGroup(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000852);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000872, EnemyEtis, "EnemyEtis-1123");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001924);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001930, EnemyDrastea, "EnemyDrastea-1124");
				break;
			}
			case 25330: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000853);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000873, EnemyEtis, "EnemyEtis-1125");
				break;
			}
			case 25360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000854);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000874, EnemyEtis, "EnemyEtis-1126");
				break;
			}
			case 25390: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000855);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000875, EnemyEtis, "EnemyEtis-1127");
				break;
			}
			case 25400: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001925);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001931, EnemyDrastea, "EnemyDrastea-1128");
				break;
			}
			case 25420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000856);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000876, EnemyEtis, "EnemyEtis-1129");
				break;
			}
			case 25450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000857);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000877, EnemyEtis, "EnemyEtis-1130");
				break;
			}
			case 25480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000858);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000878, EnemyEtis, "EnemyEtis-1131");
				break;
			}
			case 25500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001926);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001932, EnemyDrastea, "EnemyDrastea-1132");
				break;
			}
			case 25510: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000859);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000879, EnemyEtis, "EnemyEtis-1133");
				break;
			}
			case 25540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000860);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000880, EnemyEtis, "EnemyEtis-1134");
				break;
			}
			case 25570: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000861);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000881, EnemyEtis, "EnemyEtis-1135");
				break;
			}
			case 25600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000862);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000882, EnemyEtis, "EnemyEtis-1136");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001927);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001933, EnemyDrastea, "EnemyDrastea-1137");
				break;
			}
			case 25630: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000863);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000883, EnemyEtis, "EnemyEtis-1138");
				break;
			}
			case 25660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000864);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000884, EnemyEtis, "EnemyEtis-1139");
				break;
			}
			case 25690: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000865);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000885, EnemyEtis, "EnemyEtis-1140");
				break;
			}
			case 25700: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001928);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001934, EnemyDrastea, "EnemyDrastea-1141");
				break;
			}
			case 25720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000866);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000886, EnemyEtis, "EnemyEtis-1142");
				break;
			}
			case 25750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000867);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000887, EnemyEtis, "EnemyEtis-1143");
				break;
			}
			case 25780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000868);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000888, EnemyEtis, "EnemyEtis-1144");
				break;
			}
			case 25800: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001929);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001935, EnemyDrastea, "EnemyDrastea-1145");
				break;
			}
			case 25810: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000869);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000889, EnemyEtis, "EnemyEtis-1146");
				break;
			}
			case 25840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000870);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000890, EnemyEtis, "EnemyEtis-1147");
				break;
			}
			case 25870: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000871);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000891, EnemyEtis, "EnemyEtis-1148");
				break;
			}
			case 25900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000872);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000892, EnemyEtis, "EnemyEtis-1149");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001930);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001936, EnemyDrastea, "EnemyDrastea-1150");
				break;
			}
			case 25930: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000873);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000893, EnemyEtis, "EnemyEtis-1151");
				break;
			}
			case 25960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000874);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000894, EnemyEtis, "EnemyEtis-1152");
				break;
			}
			case 25990: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000875);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000895, EnemyEtis, "EnemyEtis-1153");
				break;
			}
			case 26000: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001931);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001937, EnemyDrastea, "EnemyDrastea-1154");
				break;
			}
			case 26020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000876);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000896, EnemyEtis, "EnemyEtis-1155");
				break;
			}
			case 26050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000877);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000897, EnemyEtis, "EnemyEtis-1156");
				break;
			}
			case 26080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000878);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000898, EnemyEtis, "EnemyEtis-1157");
				break;
			}
			case 26100: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001932);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001938, EnemyDrastea, "EnemyDrastea-1158");
				break;
			}
			case 26110: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000879);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000899, EnemyEtis, "EnemyEtis-1159");
				break;
			}
			case 26140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000880);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000900, EnemyEtis, "EnemyEtis-1160");
				break;
			}
			case 26170: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000881);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000901, EnemyEtis, "EnemyEtis-1161");
				break;
			}
			case 26200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000882);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000902, EnemyEtis, "EnemyEtis-1162");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001933);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001939, EnemyDrastea, "EnemyDrastea-1163");
				break;
			}
			case 26230: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000883);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000903, EnemyEtis, "EnemyEtis-1164");
				break;
			}
			case 26260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000884);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000904, EnemyEtis, "EnemyEtis-1165");
				break;
			}
			case 26290: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000885);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000905, EnemyEtis, "EnemyEtis-1166");
				break;
			}
			case 26300: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001934);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001940, EnemyDrastea, "EnemyDrastea-1167");
				break;
			}
			case 26320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000886);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000906, EnemyEtis, "EnemyEtis-1168");
				break;
			}
			case 26350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000887);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000907, EnemyEtis, "EnemyEtis-1169");
				break;
			}
			case 26380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000888);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000908, EnemyEtis, "EnemyEtis-1170");
				break;
			}
			case 26400: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001935);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001941, EnemyDrastea, "EnemyDrastea-1171");
				break;
			}
			case 26410: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000889);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000909, EnemyEtis, "EnemyEtis-1172");
				break;
			}
			case 26440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000890);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000910, EnemyEtis, "EnemyEtis-1173");
				break;
			}
			case 26470: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000891);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000911, EnemyEtis, "EnemyEtis-1174");
				break;
			}
			case 26500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000892);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000912, EnemyEtis, "EnemyEtis-1175");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001936);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001942, EnemyDrastea, "EnemyDrastea-1176");
				break;
			}
			case 26530: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000893);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000913, EnemyEtis, "EnemyEtis-1177");
				break;
			}
			case 26560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000894);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000914, EnemyEtis, "EnemyEtis-1178");
				break;
			}
			case 26590: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000895);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000915, EnemyEtis, "EnemyEtis-1179");
				break;
			}
			case 26600: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001937);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001943, EnemyDrastea, "EnemyDrastea-1180");
				break;
			}
			case 26620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000896);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000916, EnemyEtis, "EnemyEtis-1181");
				break;
			}
			case 26650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000897);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000917, EnemyEtis, "EnemyEtis-1182");
				break;
			}
			case 26680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000898);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000918, EnemyEtis, "EnemyEtis-1183");
				break;
			}
			case 26700: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001938);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001944, EnemyDrastea, "EnemyDrastea-1184");
				break;
			}
			case 26710: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000899);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000919, EnemyEtis, "EnemyEtis-1185");
				break;
			}
			case 26740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000900);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000920, EnemyEtis, "EnemyEtis-1186");
				break;
			}
			case 26770: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000901);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000921, EnemyEtis, "EnemyEtis-1187");
				break;
			}
			case 26800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000902);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000922, EnemyEtis, "EnemyEtis-1188");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001939);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001945, EnemyDrastea, "EnemyDrastea-1189");
				break;
			}
			case 26830: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000903);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000923, EnemyEtis, "EnemyEtis-1190");
				break;
			}
			case 26860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000904);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000924, EnemyEtis, "EnemyEtis-1191");
				break;
			}
			case 26890: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000905);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000925, EnemyEtis, "EnemyEtis-1192");
				break;
			}
			case 26900: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001940);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001946, EnemyDrastea, "EnemyDrastea-1193");
				break;
			}
			case 26920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000906);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000926, EnemyEtis, "EnemyEtis-1194");
				break;
			}
			case 26950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000907);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000927, EnemyEtis, "EnemyEtis-1195");
				break;
			}
			case 26980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000908);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000928, EnemyEtis, "EnemyEtis-1196");
				break;
			}
			case 27000: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001941);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001947, EnemyDrastea, "EnemyDrastea-1197");
				break;
			}
			case 27010: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000909);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000929, EnemyEtis, "EnemyEtis-1198");
				break;
			}
			case 27040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000910);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000930, EnemyEtis, "EnemyEtis-1199");
				break;
			}
			case 27070: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000911);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000931, EnemyEtis, "EnemyEtis-1200");
				break;
			}
			case 27100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000912);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000932, EnemyEtis, "EnemyEtis-1201");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001942);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001948, EnemyDrastea, "EnemyDrastea-1202");
				break;
			}
			case 27130: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000913);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000933, EnemyEtis, "EnemyEtis-1203");
				break;
			}
			case 27160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000914);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000934, EnemyEtis, "EnemyEtis-1204");
				break;
			}
			case 27190: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000915);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000935, EnemyEtis, "EnemyEtis-1205");
				break;
			}
			case 27200: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001943);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001949, EnemyDrastea, "EnemyDrastea-1206");
				break;
			}
			case 27220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000916);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000936, EnemyEtis, "EnemyEtis-1207");
				break;
			}
			case 27250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000917);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000937, EnemyEtis, "EnemyEtis-1208");
				break;
			}
			case 27280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000918);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000938, EnemyEtis, "EnemyEtis-1209");
				break;
			}
			case 27300: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001944);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001950, EnemyDrastea, "EnemyDrastea-1210");
				break;
			}
			case 27310: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000919);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000939, EnemyEtis, "EnemyEtis-1211");
				break;
			}
			case 27340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000920);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000940, EnemyEtis, "EnemyEtis-1212");
				break;
			}
			case 27370: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000921);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000941, EnemyEtis, "EnemyEtis-1213");
				break;
			}
			case 27400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000922);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000942, EnemyEtis, "EnemyEtis-1214");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001945);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001951, EnemyDrastea, "EnemyDrastea-1215");
				break;
			}
			case 27430: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000923);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000943, EnemyEtis, "EnemyEtis-1216");
				break;
			}
			case 27460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000924);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000944, EnemyEtis, "EnemyEtis-1217");
				break;
			}
			case 27490: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000925);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000945, EnemyEtis, "EnemyEtis-1218");
				break;
			}
			case 27500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001946);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001952, EnemyDrastea, "EnemyDrastea-1219");
				break;
			}
			case 27520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000926);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000946, EnemyEtis, "EnemyEtis-1220");
				break;
			}
			case 27550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000927);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000947, EnemyEtis, "EnemyEtis-1221");
				break;
			}
			case 27580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000928);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000948, EnemyEtis, "EnemyEtis-1222");
				break;
			}
			case 27600: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001947);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001953, EnemyDrastea, "EnemyDrastea-1223");
				break;
			}
			case 27610: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000929);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000949, EnemyEtis, "EnemyEtis-1224");
				break;
			}
			case 27640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000930);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000950, EnemyEtis, "EnemyEtis-1225");
				break;
			}
			case 27670: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000931);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000951, EnemyEtis, "EnemyEtis-1226");
				break;
			}
			case 27700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000932);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000952, EnemyEtis, "EnemyEtis-1227");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001948);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001954, EnemyDrastea, "EnemyDrastea-1228");
				break;
			}
			case 27730: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000933);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000953, EnemyEtis, "EnemyEtis-1229");
				break;
			}
			case 27760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000934);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000954, EnemyEtis, "EnemyEtis-1230");
				break;
			}
			case 27790: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000935);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000955, EnemyEtis, "EnemyEtis-1231");
				break;
			}
			case 27800: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001949);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001955, EnemyDrastea, "EnemyDrastea-1232");
				break;
			}
			case 27820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000936);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000956, EnemyEtis, "EnemyEtis-1233");
				break;
			}
			case 27850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000937);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000957, EnemyEtis, "EnemyEtis-1234");
				break;
			}
			case 27880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000938);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000958, EnemyEtis, "EnemyEtis-1235");
				break;
			}
			case 27900: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001950);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001956, EnemyDrastea, "EnemyDrastea-1236");
				break;
			}
			case 27910: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000939);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000959, EnemyEtis, "EnemyEtis-1237");
				break;
			}
			case 27940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000940);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000960, EnemyEtis, "EnemyEtis-1238");
				break;
			}
			case 27970: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000941);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000961, EnemyEtis, "EnemyEtis-1239");
				break;
			}
			case 28000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000942);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000962, EnemyEtis, "EnemyEtis-1240");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001951);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001957, EnemyDrastea, "EnemyDrastea-1241");
				break;
			}
			case 28030: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000943);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000963, EnemyEtis, "EnemyEtis-1242");
				break;
			}
			case 28060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000944);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000964, EnemyEtis, "EnemyEtis-1243");
				break;
			}
			case 28090: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000945);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000965, EnemyEtis, "EnemyEtis-1244");
				break;
			}
			case 28100: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001952);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001958, EnemyDrastea, "EnemyDrastea-1245");
				break;
			}
			case 28120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000946);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000966, EnemyEtis, "EnemyEtis-1246");
				break;
			}
			case 28150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000947);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000967, EnemyEtis, "EnemyEtis-1247");
				break;
			}
			case 28180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000948);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000968, EnemyEtis, "EnemyEtis-1248");
				break;
			}
			case 28200: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001953);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001959, EnemyDrastea, "EnemyDrastea-1249");
				break;
			}
			case 28210: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000949);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000969, EnemyEtis, "EnemyEtis-1250");
				break;
			}
			case 28240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000950);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000970, EnemyEtis, "EnemyEtis-1251");
				break;
			}
			case 28270: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000951);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000971, EnemyEtis, "EnemyEtis-1252");
				break;
			}
			case 28300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000952);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000972, EnemyEtis, "EnemyEtis-1253");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001954);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001960, EnemyDrastea, "EnemyDrastea-1254");
				break;
			}
			case 28330: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000953);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000973, EnemyEtis, "EnemyEtis-1255");
				break;
			}
			case 28360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000954);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000974, EnemyEtis, "EnemyEtis-1256");
				break;
			}
			case 28390: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000955);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000975, EnemyEtis, "EnemyEtis-1257");
				break;
			}
			case 28400: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001955);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001961, EnemyDrastea, "EnemyDrastea-1258");
				break;
			}
			case 28420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000956);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000976, EnemyEtis, "EnemyEtis-1259");
				break;
			}
			case 28450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000957);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000977, EnemyEtis, "EnemyEtis-1260");
				break;
			}
			case 28480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000958);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000978, EnemyEtis, "EnemyEtis-1261");
				break;
			}
			case 28500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001956);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001962, EnemyDrastea, "EnemyDrastea-1262");
				break;
			}
			case 28510: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000959);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000979, EnemyEtis, "EnemyEtis-1263");
				break;
			}
			case 28540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000960);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000980, EnemyEtis, "EnemyEtis-1264");
				break;
			}
			case 28570: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000961);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000981, EnemyEtis, "EnemyEtis-1265");
				break;
			}
			case 28600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000962);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000982, EnemyEtis, "EnemyEtis-1266");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001957);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001963, EnemyDrastea, "EnemyDrastea-1267");
				break;
			}
			case 28630: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000963);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000983, EnemyEtis, "EnemyEtis-1268");
				break;
			}
			case 28660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000964);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000984, EnemyEtis, "EnemyEtis-1269");
				break;
			}
			case 28690: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000965);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000985, EnemyEtis, "EnemyEtis-1270");
				break;
			}
			case 28700: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001958);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001964, EnemyDrastea, "EnemyDrastea-1271");
				break;
			}
			case 28720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000966);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000986, EnemyEtis, "EnemyEtis-1272");
				break;
			}
			case 28750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000967);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000987, EnemyEtis, "EnemyEtis-1273");
				break;
			}
			case 28780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000968);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000988, EnemyEtis, "EnemyEtis-1274");
				break;
			}
			case 28800: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001959);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001965, EnemyDrastea, "EnemyDrastea-1275");
				break;
			}
			case 28810: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000969);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000989, EnemyEtis, "EnemyEtis-1276");
				break;
			}
			case 28840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000970);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000990, EnemyEtis, "EnemyEtis-1277");
				break;
			}
			case 28870: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000971);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000991, EnemyEtis, "EnemyEtis-1278");
				break;
			}
			case 28900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000972);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000992, EnemyEtis, "EnemyEtis-1279");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001960);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001966, EnemyDrastea, "EnemyDrastea-1280");
				break;
			}
			case 28930: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000973);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000993, EnemyEtis, "EnemyEtis-1281");
				break;
			}
			case 28960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000974);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000994, EnemyEtis, "EnemyEtis-1282");
				break;
			}
			case 28990: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000975);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000995, EnemyEtis, "EnemyEtis-1283");
				break;
			}
			case 29000: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001961);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001967, EnemyDrastea, "EnemyDrastea-1284");
				break;
			}
			case 29020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000976);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000996, EnemyEtis, "EnemyEtis-1285");
				break;
			}
			case 29050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000977);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000997, EnemyEtis, "EnemyEtis-1286");
				break;
			}
			case 29080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000978);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000998, EnemyEtis, "EnemyEtis-1287");
				break;
			}
			case 29100: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001962);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001968, EnemyDrastea, "EnemyDrastea-1288");
				break;
			}
			case 29110: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000979);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000999, EnemyEtis, "EnemyEtis-1289");
				break;
			}
			case 29140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000980);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001000, EnemyEtis, "EnemyEtis-1290");
				break;
			}
			case 29170: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000981);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001001, EnemyEtis, "EnemyEtis-1291");
				break;
			}
			case 29200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000982);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001002, EnemyEtis, "EnemyEtis-1292");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001963);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001969, EnemyDrastea, "EnemyDrastea-1293");
				break;
			}
			case 29230: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000983);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001003, EnemyEtis, "EnemyEtis-1294");
				break;
			}
			case 29260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000984);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001004, EnemyEtis, "EnemyEtis-1295");
				break;
			}
			case 29290: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000985);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001005, EnemyEtis, "EnemyEtis-1296");
				break;
			}
			case 29300: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001964);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001970, EnemyDrastea, "EnemyDrastea-1297");
				break;
			}
			case 29320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000986);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001006, EnemyEtis, "EnemyEtis-1298");
				break;
			}
			case 29350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000987);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001007, EnemyEtis, "EnemyEtis-1299");
				break;
			}
			case 29380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000988);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001008, EnemyEtis, "EnemyEtis-1300");
				break;
			}
			case 29400: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001965);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001971, EnemyDrastea, "EnemyDrastea-1301");
				break;
			}
			case 29410: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000989);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001009, EnemyEtis, "EnemyEtis-1302");
				break;
			}
			case 29440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000990);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001010, EnemyEtis, "EnemyEtis-1303");
				break;
			}
			case 29470: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000991);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001011, EnemyEtis, "EnemyEtis-1304");
				break;
			}
			case 29500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000992);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001012, EnemyEtis, "EnemyEtis-1305");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001966);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001972, EnemyDrastea, "EnemyDrastea-1306");
				break;
			}
			case 29530: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000993);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001013, EnemyEtis, "EnemyEtis-1307");
				break;
			}
			case 29560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000994);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001014, EnemyEtis, "EnemyEtis-1308");
				break;
			}
			case 29590: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000995);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001015, EnemyEtis, "EnemyEtis-1309");
				break;
			}
			case 29600: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001967);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001973, EnemyDrastea, "EnemyDrastea-1310");
				break;
			}
			case 29620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000996);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001016, EnemyEtis, "EnemyEtis-1311");
				break;
			}
			case 29650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000997);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001017, EnemyEtis, "EnemyEtis-1312");
				break;
			}
			case 29680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000998);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001018, EnemyEtis, "EnemyEtis-1313");
				break;
			}
			case 29700: {
				orderActorToFactory(10000008, EnemyErmione, "EnemyErmione-1314");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001968);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001974, EnemyDrastea, "EnemyDrastea-1315");
				break;
			}
			case 29710: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000999);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001019, EnemyEtis, "EnemyEtis-1316");
				break;
			}
			case 29740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001000);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001020, EnemyEtis, "EnemyEtis-1317");
				break;
			}
			case 29770: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001001);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001021, EnemyEtis, "EnemyEtis-1318");
				break;
			}
			case 29800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001002);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001022, EnemyEtis, "EnemyEtis-1319");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001969);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001975, EnemyDrastea, "EnemyDrastea-1320");
				break;
			}
			case 29830: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001003);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001023, EnemyEtis, "EnemyEtis-1321");
				break;
			}
			case 29860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001004);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001024, EnemyEtis, "EnemyEtis-1322");
				break;
			}
			case 29890: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001005);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001025, EnemyEtis, "EnemyEtis-1323");
				break;
			}
			case 29900: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001970);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001976, EnemyDrastea, "EnemyDrastea-1324");
				break;
			}
			case 29920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001006);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001026, EnemyEtis, "EnemyEtis-1325");
				break;
			}
			case 29950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001007);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001027, EnemyEtis, "EnemyEtis-1326");
				break;
			}
			case 29980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001008);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001028, EnemyEtis, "EnemyEtis-1327");
				break;
			}
			case 30000: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001971);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001977, EnemyDrastea, "EnemyDrastea-1328");
				break;
			}
			case 30010: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001009);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001029, EnemyEtis, "EnemyEtis-1329");
				break;
			}
			case 30040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001010);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001030, EnemyEtis, "EnemyEtis-1330");
				break;
			}
			case 30070: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001011);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001031, EnemyEtis, "EnemyEtis-1331");
				break;
			}
			case 30100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001012);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001032, EnemyEtis, "EnemyEtis-1332");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001972);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001978, EnemyDrastea, "EnemyDrastea-1333");
				break;
			}
			case 30130: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001013);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001033, EnemyEtis, "EnemyEtis-1334");
				break;
			}
			case 30160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001014);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001034, EnemyEtis, "EnemyEtis-1335");
				break;
			}
			case 30190: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001015);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001035, EnemyEtis, "EnemyEtis-1336");
				break;
			}
			case 30200: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001973);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001979, EnemyDrastea, "EnemyDrastea-1337");
				break;
			}
			case 30220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001016);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001036, EnemyEtis, "EnemyEtis-1338");
				break;
			}
			case 30250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001017);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001037, EnemyEtis, "EnemyEtis-1339");
				break;
			}
			case 30280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001018);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001038, EnemyEtis, "EnemyEtis-1340");
				break;
			}
			case 30300: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(10000008);
				bringDirector()->addSubGroup(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001974);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001980, EnemyDrastea, "EnemyDrastea-1341");
				break;
			}
			case 30310: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001019);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001039, EnemyEtis, "EnemyEtis-1342");
				break;
			}
			case 30340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001020);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001040, EnemyEtis, "EnemyEtis-1343");
				break;
			}
			case 30370: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001021);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001041, EnemyEtis, "EnemyEtis-1344");
				break;
			}
			case 30400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001022);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001042, EnemyEtis, "EnemyEtis-1345");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001975);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001981, EnemyDrastea, "EnemyDrastea-1346");
				break;
			}
			case 30430: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001023);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001043, EnemyEtis, "EnemyEtis-1347");
				break;
			}
			case 30460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001024);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001044, EnemyEtis, "EnemyEtis-1348");
				break;
			}
			case 30490: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001025);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001045, EnemyEtis, "EnemyEtis-1349");
				break;
			}
			case 30500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001976);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001982, EnemyDrastea, "EnemyDrastea-1350");
				break;
			}
			case 30520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001026);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001046, EnemyEtis, "EnemyEtis-1351");
				break;
			}
			case 30550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001027);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001047, EnemyEtis, "EnemyEtis-1352");
				break;
			}
			case 30580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001028);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001048, EnemyEtis, "EnemyEtis-1353");
				break;
			}
			case 30600: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001977);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001983, EnemyDrastea, "EnemyDrastea-1354");
				break;
			}
			case 30610: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001029);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001049, EnemyEtis, "EnemyEtis-1355");
				break;
			}
			case 30640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001030);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001050, EnemyEtis, "EnemyEtis-1356");
				break;
			}
			case 30670: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001031);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001051, EnemyEtis, "EnemyEtis-1357");
				break;
			}
			case 30700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001032);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001052, EnemyEtis, "EnemyEtis-1358");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001978);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001984, EnemyDrastea, "EnemyDrastea-1359");
				break;
			}
			case 30730: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001033);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001053, EnemyEtis, "EnemyEtis-1360");
				break;
			}
			case 30760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001034);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001054, EnemyEtis, "EnemyEtis-1361");
				break;
			}
			case 30790: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001035);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001055, EnemyEtis, "EnemyEtis-1362");
				break;
			}
			case 30800: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001979);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001985, EnemyDrastea, "EnemyDrastea-1363");
				break;
			}
			case 30820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001036);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001056, EnemyEtis, "EnemyEtis-1364");
				break;
			}
			case 30850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001037);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001057, EnemyEtis, "EnemyEtis-1365");
				break;
			}
			case 30880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001038);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001058, EnemyEtis, "EnemyEtis-1366");
				break;
			}
			case 30900: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001980);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001986, EnemyDrastea, "EnemyDrastea-1367");
				break;
			}
			case 30910: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001039);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001059, EnemyEtis, "EnemyEtis-1368");
				break;
			}
			case 30940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001040);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001060, EnemyEtis, "EnemyEtis-1369");
				break;
			}
			case 30970: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001041);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001061, EnemyEtis, "EnemyEtis-1370");
				break;
			}
			case 31000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001042);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001062, EnemyEtis, "EnemyEtis-1371");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001981);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001987, EnemyDrastea, "EnemyDrastea-1372");
				break;
			}
			case 31030: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001043);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001063, EnemyEtis, "EnemyEtis-1373");
				break;
			}
			case 31060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001044);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001064, EnemyEtis, "EnemyEtis-1374");
				break;
			}
			case 31090: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001045);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001065, EnemyEtis, "EnemyEtis-1375");
				break;
			}
			case 31100: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001982);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001988, EnemyDrastea, "EnemyDrastea-1376");
				break;
			}
			case 31120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001046);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001066, EnemyEtis, "EnemyEtis-1377");
				break;
			}
			case 31150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001047);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001067, EnemyEtis, "EnemyEtis-1378");
				break;
			}
			case 31180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001048);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001068, EnemyEtis, "EnemyEtis-1379");
				break;
			}
			case 31200: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001983);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001989, EnemyDrastea, "EnemyDrastea-1380");
				break;
			}
			case 31210: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001049);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001069, EnemyEtis, "EnemyEtis-1381");
				break;
			}
			case 31240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001050);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001070, EnemyEtis, "EnemyEtis-1382");
				break;
			}
			case 31270: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001051);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001071, EnemyEtis, "EnemyEtis-1383");
				break;
			}
			case 31300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001052);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001072, EnemyEtis, "EnemyEtis-1384");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001984);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001990, EnemyDrastea, "EnemyDrastea-1385");
				break;
			}
			case 31330: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001053);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001073, EnemyEtis, "EnemyEtis-1386");
				break;
			}
			case 31360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001054);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001074, EnemyEtis, "EnemyEtis-1387");
				break;
			}
			case 31390: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001055);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001075, EnemyEtis, "EnemyEtis-1388");
				break;
			}
			case 31400: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001985);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001991, EnemyDrastea, "EnemyDrastea-1389");
				break;
			}
			case 31420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001056);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001076, EnemyEtis, "EnemyEtis-1390");
				break;
			}
			case 31450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001057);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001077, EnemyEtis, "EnemyEtis-1391");
				break;
			}
			case 31480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001058);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001078, EnemyEtis, "EnemyEtis-1392");
				break;
			}
			case 31500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001986);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001992, EnemyDrastea, "EnemyDrastea-1393");
				break;
			}
			case 31510: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001059);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001079, EnemyEtis, "EnemyEtis-1394");
				break;
			}
			case 31540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001060);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001080, EnemyEtis, "EnemyEtis-1395");
				break;
			}
			case 31570: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001061);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001081, EnemyEtis, "EnemyEtis-1396");
				break;
			}
			case 31600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001062);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001082, EnemyEtis, "EnemyEtis-1397");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001987);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001993, EnemyDrastea, "EnemyDrastea-1398");
				break;
			}
			case 31630: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001063);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001083, EnemyEtis, "EnemyEtis-1399");
				break;
			}
			case 31660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001064);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001084, EnemyEtis, "EnemyEtis-1400");
				break;
			}
			case 31690: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001065);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001085, EnemyEtis, "EnemyEtis-1401");
				break;
			}
			case 31700: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001988);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001994, EnemyDrastea, "EnemyDrastea-1402");
				break;
			}
			case 31720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001066);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001086, EnemyEtis, "EnemyEtis-1403");
				break;
			}
			case 31750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001067);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001087, EnemyEtis, "EnemyEtis-1404");
				break;
			}
			case 31780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001068);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001088, EnemyEtis, "EnemyEtis-1405");
				break;
			}
			case 31800: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001989);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001995, EnemyDrastea, "EnemyDrastea-1406");
				break;
			}
			case 31810: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001069);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001089, EnemyEtis, "EnemyEtis-1407");
				break;
			}
			case 31840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001070);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001090, EnemyEtis, "EnemyEtis-1408");
				break;
			}
			case 31870: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001071);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001091, EnemyEtis, "EnemyEtis-1409");
				break;
			}
			case 31900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001072);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001092, EnemyEtis, "EnemyEtis-1410");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001990);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001996, EnemyDrastea, "EnemyDrastea-1411");
				break;
			}
			case 31930: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001073);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001093, EnemyEtis, "EnemyEtis-1412");
				break;
			}
			case 31960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001074);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001094, EnemyEtis, "EnemyEtis-1413");
				break;
			}
			case 31990: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001075);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001095, EnemyEtis, "EnemyEtis-1414");
				break;
			}
			case 32000: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001991);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001997, EnemyDrastea, "EnemyDrastea-1415");
				break;
			}
			case 32020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001076);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001096, EnemyEtis, "EnemyEtis-1416");
				break;
			}
			case 32050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001077);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001097, EnemyEtis, "EnemyEtis-1417");
				break;
			}
			case 32080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001078);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001098, EnemyEtis, "EnemyEtis-1418");
				break;
			}
			case 32100: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001992);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001998, EnemyDrastea, "EnemyDrastea-1419");
				break;
			}
			case 32110: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001079);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001099, EnemyEtis, "EnemyEtis-1420");
				break;
			}
			case 32140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001080);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001100, EnemyEtis, "EnemyEtis-1421");
				break;
			}
			case 32170: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001081);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001101, EnemyEtis, "EnemyEtis-1422");
				break;
			}
			case 32200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001082);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001102, EnemyEtis, "EnemyEtis-1423");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001993);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001999, EnemyDrastea, "EnemyDrastea-1424");
				break;
			}
			case 32230: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001083);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001103, EnemyEtis, "EnemyEtis-1425");
				break;
			}
			case 32260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001084);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001104, EnemyEtis, "EnemyEtis-1426");
				break;
			}
			case 32290: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001085);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001105, EnemyEtis, "EnemyEtis-1427");
				break;
			}
			case 32300: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001994);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002000, EnemyDrastea, "EnemyDrastea-1428");
				break;
			}
			case 32320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001086);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001106, EnemyEtis, "EnemyEtis-1429");
				break;
			}
			case 32350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001087);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001107, EnemyEtis, "EnemyEtis-1430");
				break;
			}
			case 32380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001088);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001108, EnemyEtis, "EnemyEtis-1431");
				break;
			}
			case 32400: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001995);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002001, EnemyDrastea, "EnemyDrastea-1432");
				break;
			}
			case 32410: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001089);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001109, EnemyEtis, "EnemyEtis-1433");
				break;
			}
			case 32440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001090);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001110, EnemyEtis, "EnemyEtis-1434");
				break;
			}
			case 32470: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001091);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001111, EnemyEtis, "EnemyEtis-1435");
				break;
			}
			case 32500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001092);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001112, EnemyEtis, "EnemyEtis-1436");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001996);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002002, EnemyDrastea, "EnemyDrastea-1437");
				break;
			}
			case 32530: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001093);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001113, EnemyEtis, "EnemyEtis-1438");
				break;
			}
			case 32560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001094);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001114, EnemyEtis, "EnemyEtis-1439");
				break;
			}
			case 32590: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001095);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001115, EnemyEtis, "EnemyEtis-1440");
				break;
			}
			case 32600: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001997);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002003, EnemyDrastea, "EnemyDrastea-1441");
				break;
			}
			case 32620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001096);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001116, EnemyEtis, "EnemyEtis-1442");
				break;
			}
			case 32650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001097);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001117, EnemyEtis, "EnemyEtis-1443");
				break;
			}
			case 32680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001098);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001118, EnemyEtis, "EnemyEtis-1444");
				break;
			}
			case 32700: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001998);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002004, EnemyDrastea, "EnemyDrastea-1445");
				break;
			}
			case 32710: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001099);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001119, EnemyEtis, "EnemyEtis-1446");
				break;
			}
			case 32740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001100);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001120, EnemyEtis, "EnemyEtis-1447");
				break;
			}
			case 32770: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001101);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001121, EnemyEtis, "EnemyEtis-1448");
				break;
			}
			case 32800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001102);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001122, EnemyEtis, "EnemyEtis-1449");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001999);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002005, EnemyDrastea, "EnemyDrastea-1450");
				break;
			}
			case 32830: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001103);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001123, EnemyEtis, "EnemyEtis-1451");
				break;
			}
			case 32860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001104);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001124, EnemyEtis, "EnemyEtis-1452");
				break;
			}
			case 32890: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001105);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001125, EnemyEtis, "EnemyEtis-1453");
				break;
			}
			case 32900: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002000);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002006, EnemyDrastea, "EnemyDrastea-1454");
				break;
			}
			case 32920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001106);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001126, EnemyEtis, "EnemyEtis-1455");
				break;
			}
			case 32950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001107);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001127, EnemyEtis, "EnemyEtis-1456");
				break;
			}
			case 32980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001108);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001128, EnemyEtis, "EnemyEtis-1457");
				break;
			}
			case 33000: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002001);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002007, EnemyDrastea, "EnemyDrastea-1458");
				break;
			}
			case 33010: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001109);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001129, EnemyEtis, "EnemyEtis-1459");
				break;
			}
			case 33040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001110);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001130, EnemyEtis, "EnemyEtis-1460");
				break;
			}
			case 33070: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001111);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001131, EnemyEtis, "EnemyEtis-1461");
				break;
			}
			case 33100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001112);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001132, EnemyEtis, "EnemyEtis-1462");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002002);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002008, EnemyDrastea, "EnemyDrastea-1463");
				break;
			}
			case 33130: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001113);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001133, EnemyEtis, "EnemyEtis-1464");
				break;
			}
			case 33160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001114);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001134, EnemyEtis, "EnemyEtis-1465");
				break;
			}
			case 33190: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001115);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001135, EnemyEtis, "EnemyEtis-1466");
				break;
			}
			case 33200: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002003);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002009, EnemyDrastea, "EnemyDrastea-1467");
				break;
			}
			case 33220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001116);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001136, EnemyEtis, "EnemyEtis-1468");
				break;
			}
			case 33250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001117);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001137, EnemyEtis, "EnemyEtis-1469");
				break;
			}
			case 33280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001118);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001138, EnemyEtis, "EnemyEtis-1470");
				break;
			}
			case 33300: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002004);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002010, EnemyDrastea, "EnemyDrastea-1471");
				break;
			}
			case 33310: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001119);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001139, EnemyEtis, "EnemyEtis-1472");
				break;
			}
			case 33340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001120);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001140, EnemyEtis, "EnemyEtis-1473");
				break;
			}
			case 33370: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001121);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001141, EnemyEtis, "EnemyEtis-1474");
				break;
			}
			case 33400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001122);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001142, EnemyEtis, "EnemyEtis-1475");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002005);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002011, EnemyDrastea, "EnemyDrastea-1476");
				break;
			}
			case 33430: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001123);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001143, EnemyEtis, "EnemyEtis-1477");
				break;
			}
			case 33460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001124);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001144, EnemyEtis, "EnemyEtis-1478");
				break;
			}
			case 33490: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001125);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001145, EnemyEtis, "EnemyEtis-1479");
				break;
			}
			case 33500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002006);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002012, EnemyDrastea, "EnemyDrastea-1480");
				break;
			}
			case 33520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001126);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001146, EnemyEtis, "EnemyEtis-1481");
				break;
			}
			case 33550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001127);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001147, EnemyEtis, "EnemyEtis-1482");
				break;
			}
			case 33580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001128);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001148, EnemyEtis, "EnemyEtis-1483");
				break;
			}
			case 33600: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002007);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002013, EnemyDrastea, "EnemyDrastea-1484");
				break;
			}
			case 33610: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001129);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001149, EnemyEtis, "EnemyEtis-1485");
				break;
			}
			case 33640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001130);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001150, EnemyEtis, "EnemyEtis-1486");
				break;
			}
			case 33670: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001131);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001151, EnemyEtis, "EnemyEtis-1487");
				break;
			}
			case 33700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001132);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001152, EnemyEtis, "EnemyEtis-1488");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002008);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002014, EnemyDrastea, "EnemyDrastea-1489");
				break;
			}
			case 33730: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001133);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001153, EnemyEtis, "EnemyEtis-1490");
				break;
			}
			case 33760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001134);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001154, EnemyEtis, "EnemyEtis-1491");
				break;
			}
			case 33790: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001135);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001155, EnemyEtis, "EnemyEtis-1492");
				break;
			}
			case 33800: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002009);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002015, EnemyDrastea, "EnemyDrastea-1493");
				break;
			}
			case 33820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001136);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001156, EnemyEtis, "EnemyEtis-1494");
				break;
			}
			case 33850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001137);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001157, EnemyEtis, "EnemyEtis-1495");
				break;
			}
			case 33880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001138);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001158, EnemyEtis, "EnemyEtis-1496");
				break;
			}
			case 33900: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002010);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002016, EnemyDrastea, "EnemyDrastea-1497");
				break;
			}
			case 33910: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001139);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001159, EnemyEtis, "EnemyEtis-1498");
				break;
			}
			case 33940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001140);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001160, EnemyEtis, "EnemyEtis-1499");
				break;
			}
			case 33970: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001141);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001161, EnemyEtis, "EnemyEtis-1500");
				break;
			}
			case 34000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001142);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001162, EnemyEtis, "EnemyEtis-1501");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002011);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002017, EnemyDrastea, "EnemyDrastea-1502");
				break;
			}
			case 34030: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001143);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001163, EnemyEtis, "EnemyEtis-1503");
				break;
			}
			case 34060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001144);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001164, EnemyEtis, "EnemyEtis-1504");
				break;
			}
			case 34090: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001145);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001165, EnemyEtis, "EnemyEtis-1505");
				break;
			}
			case 34100: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002012);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002018, EnemyDrastea, "EnemyDrastea-1506");
				break;
			}
			case 34120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001146);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001166, EnemyEtis, "EnemyEtis-1507");
				break;
			}
			case 34150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001147);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001167, EnemyEtis, "EnemyEtis-1508");
				break;
			}
			case 34180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001148);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001168, EnemyEtis, "EnemyEtis-1509");
				break;
			}
			case 34200: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002013);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002019, EnemyDrastea, "EnemyDrastea-1510");
				break;
			}
			case 34210: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001149);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001169, EnemyEtis, "EnemyEtis-1511");
				break;
			}
			case 34240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001150);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001170, EnemyEtis, "EnemyEtis-1512");
				break;
			}
			case 34270: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001151);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001171, EnemyEtis, "EnemyEtis-1513");
				break;
			}
			case 34300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001152);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001172, EnemyEtis, "EnemyEtis-1514");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002014);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002020, EnemyDrastea, "EnemyDrastea-1515");
				break;
			}
			case 34330: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001153);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001173, EnemyEtis, "EnemyEtis-1516");
				break;
			}
			case 34360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001154);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001174, EnemyEtis, "EnemyEtis-1517");
				break;
			}
			case 34390: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001155);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001175, EnemyEtis, "EnemyEtis-1518");
				break;
			}
			case 34400: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002015);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002021, EnemyDrastea, "EnemyDrastea-1519");
				break;
			}
			case 34420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001156);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001176, EnemyEtis, "EnemyEtis-1520");
				break;
			}
			case 34450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001157);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001177, EnemyEtis, "EnemyEtis-1521");
				break;
			}
			case 34480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001158);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001178, EnemyEtis, "EnemyEtis-1522");
				break;
			}
			case 34500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002016);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002022, EnemyDrastea, "EnemyDrastea-1523");
				break;
			}
			case 34510: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001159);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001179, EnemyEtis, "EnemyEtis-1524");
				break;
			}
			case 34540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001160);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001180, EnemyEtis, "EnemyEtis-1525");
				break;
			}
			case 34570: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001161);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001181, EnemyEtis, "EnemyEtis-1526");
				break;
			}
			case 34600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001162);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001182, EnemyEtis, "EnemyEtis-1527");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002017);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002023, EnemyDrastea, "EnemyDrastea-1528");
				break;
			}
			case 34630: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001163);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001183, EnemyEtis, "EnemyEtis-1529");
				break;
			}
			case 34660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001164);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001184, EnemyEtis, "EnemyEtis-1530");
				break;
			}
			case 34690: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001165);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001185, EnemyEtis, "EnemyEtis-1531");
				break;
			}
			case 34700: {
				orderActorToFactory(10000009, EnemyErmione, "EnemyErmione-1532");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002018);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002024, EnemyDrastea, "EnemyDrastea-1533");
				break;
			}
			case 34720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001166);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001186, EnemyEtis, "EnemyEtis-1534");
				break;
			}
			case 34750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001167);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001187, EnemyEtis, "EnemyEtis-1535");
				break;
			}
			case 34780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001168);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001188, EnemyEtis, "EnemyEtis-1536");
				break;
			}
			case 34800: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002019);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002025, EnemyDrastea, "EnemyDrastea-1537");
				break;
			}
			case 34810: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001169);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001189, EnemyEtis, "EnemyEtis-1538");
				break;
			}
			case 34840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001170);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001190, EnemyEtis, "EnemyEtis-1539");
				break;
			}
			case 34870: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001171);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001191, EnemyEtis, "EnemyEtis-1540");
				break;
			}
			case 34900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001172);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001192, EnemyEtis, "EnemyEtis-1541");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002020);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002026, EnemyDrastea, "EnemyDrastea-1542");
				break;
			}
			case 34930: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001173);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001193, EnemyEtis, "EnemyEtis-1543");
				break;
			}
			case 34960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001174);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001194, EnemyEtis, "EnemyEtis-1544");
				break;
			}
			case 34990: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001175);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001195, EnemyEtis, "EnemyEtis-1545");
				break;
			}
			case 35000: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002021);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002027, EnemyDrastea, "EnemyDrastea-1546");
				break;
			}
			case 35020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001176);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001196, EnemyEtis, "EnemyEtis-1547");
				break;
			}
			case 35050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001177);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001197, EnemyEtis, "EnemyEtis-1548");
				break;
			}
			case 35080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001178);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001198, EnemyEtis, "EnemyEtis-1549");
				break;
			}
			case 35100: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002022);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002028, EnemyDrastea, "EnemyDrastea-1550");
				break;
			}
			case 35110: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001179);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001199, EnemyEtis, "EnemyEtis-1551");
				break;
			}
			case 35140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001180);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001200, EnemyEtis, "EnemyEtis-1552");
				break;
			}
			case 35170: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001181);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001201, EnemyEtis, "EnemyEtis-1553");
				break;
			}
			case 35200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001182);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001202, EnemyEtis, "EnemyEtis-1554");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002023);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002029, EnemyDrastea, "EnemyDrastea-1555");
				break;
			}
			case 35230: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001183);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001203, EnemyEtis, "EnemyEtis-1556");
				break;
			}
			case 35260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001184);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001204, EnemyEtis, "EnemyEtis-1557");
				break;
			}
			case 35290: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001185);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001205, EnemyEtis, "EnemyEtis-1558");
				break;
			}
			case 35300: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(10000009);
				bringDirector()->addSubGroup(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002024);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002030, EnemyDrastea, "EnemyDrastea-1559");
				break;
			}
			case 35320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001186);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001206, EnemyEtis, "EnemyEtis-1560");
				break;
			}
			case 35350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001187);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001207, EnemyEtis, "EnemyEtis-1561");
				break;
			}
			case 35380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001188);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001208, EnemyEtis, "EnemyEtis-1562");
				break;
			}
			case 35400: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002025);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002031, EnemyDrastea, "EnemyDrastea-1563");
				break;
			}
			case 35410: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001189);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001209, EnemyEtis, "EnemyEtis-1564");
				break;
			}
			case 35440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001190);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001210, EnemyEtis, "EnemyEtis-1565");
				break;
			}
			case 35470: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001191);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001211, EnemyEtis, "EnemyEtis-1566");
				break;
			}
			case 35500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001192);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001212, EnemyEtis, "EnemyEtis-1567");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002026);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002032, EnemyDrastea, "EnemyDrastea-1568");
				break;
			}
			case 35530: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001193);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001213, EnemyEtis, "EnemyEtis-1569");
				break;
			}
			case 35560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001194);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001214, EnemyEtis, "EnemyEtis-1570");
				break;
			}
			case 35590: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001195);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001215, EnemyEtis, "EnemyEtis-1571");
				break;
			}
			case 35600: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002027);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002033, EnemyDrastea, "EnemyDrastea-1572");
				break;
			}
			case 35620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001196);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001216, EnemyEtis, "EnemyEtis-1573");
				break;
			}
			case 35650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001197);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001217, EnemyEtis, "EnemyEtis-1574");
				break;
			}
			case 35680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001198);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001218, EnemyEtis, "EnemyEtis-1575");
				break;
			}
			case 35700: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002028);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002034, EnemyDrastea, "EnemyDrastea-1576");
				break;
			}
			case 35710: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001199);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001219, EnemyEtis, "EnemyEtis-1577");
				break;
			}
			case 35740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001200);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001220, EnemyEtis, "EnemyEtis-1578");
				break;
			}
			case 35770: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001201);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001221, EnemyEtis, "EnemyEtis-1579");
				break;
			}
			case 35800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001202);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001222, EnemyEtis, "EnemyEtis-1580");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002029);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002035, EnemyDrastea, "EnemyDrastea-1581");
				break;
			}
			case 35830: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001203);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001223, EnemyEtis, "EnemyEtis-1582");
				break;
			}
			case 35860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001204);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001224, EnemyEtis, "EnemyEtis-1583");
				break;
			}
			case 35890: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001205);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001225, EnemyEtis, "EnemyEtis-1584");
				break;
			}
			case 35900: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002030);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002036, EnemyDrastea, "EnemyDrastea-1585");
				break;
			}
			case 35920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001206);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001226, EnemyEtis, "EnemyEtis-1586");
				break;
			}
			case 35950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001207);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001227, EnemyEtis, "EnemyEtis-1587");
				break;
			}
			case 35980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001208);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001228, EnemyEtis, "EnemyEtis-1588");
				break;
			}
			case 36000: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002031);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002037, EnemyDrastea, "EnemyDrastea-1589");
				break;
			}
			case 36010: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001209);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001229, EnemyEtis, "EnemyEtis-1590");
				break;
			}
			case 36040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001210);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001230, EnemyEtis, "EnemyEtis-1591");
				break;
			}
			case 36070: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001211);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001231, EnemyEtis, "EnemyEtis-1592");
				break;
			}
			case 36100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001212);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001232, EnemyEtis, "EnemyEtis-1593");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002032);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002038, EnemyDrastea, "EnemyDrastea-1594");
				break;
			}
			case 36130: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001213);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001233, EnemyEtis, "EnemyEtis-1595");
				break;
			}
			case 36160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001214);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001234, EnemyEtis, "EnemyEtis-1596");
				break;
			}
			case 36190: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001215);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001235, EnemyEtis, "EnemyEtis-1597");
				break;
			}
			case 36200: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002033);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002039, EnemyDrastea, "EnemyDrastea-1598");
				break;
			}
			case 36220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001216);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001236, EnemyEtis, "EnemyEtis-1599");
				break;
			}
			case 36250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001217);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001237, EnemyEtis, "EnemyEtis-1600");
				break;
			}
			case 36280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001218);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001238, EnemyEtis, "EnemyEtis-1601");
				break;
			}
			case 36300: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002034);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002040, EnemyDrastea, "EnemyDrastea-1602");
				break;
			}
			case 36310: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001219);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001239, EnemyEtis, "EnemyEtis-1603");
				break;
			}
			case 36340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001220);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001240, EnemyEtis, "EnemyEtis-1604");
				break;
			}
			case 36370: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001221);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001241, EnemyEtis, "EnemyEtis-1605");
				break;
			}
			case 36400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001222);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001242, EnemyEtis, "EnemyEtis-1606");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002035);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002041, EnemyDrastea, "EnemyDrastea-1607");
				break;
			}
			case 36430: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001223);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001243, EnemyEtis, "EnemyEtis-1608");
				break;
			}
			case 36460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001224);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001244, EnemyEtis, "EnemyEtis-1609");
				break;
			}
			case 36490: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001225);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001245, EnemyEtis, "EnemyEtis-1610");
				break;
			}
			case 36500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002036);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002042, EnemyDrastea, "EnemyDrastea-1611");
				break;
			}
			case 36520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001226);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001246, EnemyEtis, "EnemyEtis-1612");
				break;
			}
			case 36550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001227);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001247, EnemyEtis, "EnemyEtis-1613");
				break;
			}
			case 36580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001228);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001248, EnemyEtis, "EnemyEtis-1614");
				break;
			}
			case 36600: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002037);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002043, EnemyDrastea, "EnemyDrastea-1615");
				break;
			}
			case 36610: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001229);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001249, EnemyEtis, "EnemyEtis-1616");
				break;
			}
			case 36640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001230);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001250, EnemyEtis, "EnemyEtis-1617");
				break;
			}
			case 36670: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001231);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001251, EnemyEtis, "EnemyEtis-1618");
				break;
			}
			case 36700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001232);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001252, EnemyEtis, "EnemyEtis-1619");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002038);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002044, EnemyDrastea, "EnemyDrastea-1620");
				break;
			}
			case 36730: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001233);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001253, EnemyEtis, "EnemyEtis-1621");
				break;
			}
			case 36760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001234);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001254, EnemyEtis, "EnemyEtis-1622");
				break;
			}
			case 36790: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001235);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001255, EnemyEtis, "EnemyEtis-1623");
				break;
			}
			case 36800: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002039);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002045, EnemyDrastea, "EnemyDrastea-1624");
				break;
			}
			case 36820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001236);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001256, EnemyEtis, "EnemyEtis-1625");
				break;
			}
			case 36850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001237);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001257, EnemyEtis, "EnemyEtis-1626");
				break;
			}
			case 36880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001238);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001258, EnemyEtis, "EnemyEtis-1627");
				break;
			}
			case 36900: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002040);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002046, EnemyDrastea, "EnemyDrastea-1628");
				break;
			}
			case 36910: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001239);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001259, EnemyEtis, "EnemyEtis-1629");
				break;
			}
			case 36940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001240);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001260, EnemyEtis, "EnemyEtis-1630");
				break;
			}
			case 36970: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001241);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001261, EnemyEtis, "EnemyEtis-1631");
				break;
			}
			case 37000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001242);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001262, EnemyEtis, "EnemyEtis-1632");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002041);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002047, EnemyDrastea, "EnemyDrastea-1633");
				break;
			}
			case 37030: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001243);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001263, EnemyEtis, "EnemyEtis-1634");
				break;
			}
			case 37060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001244);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001264, EnemyEtis, "EnemyEtis-1635");
				break;
			}
			case 37090: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001245);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001265, EnemyEtis, "EnemyEtis-1636");
				break;
			}
			case 37100: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002042);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002048, EnemyDrastea, "EnemyDrastea-1637");
				break;
			}
			case 37120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001246);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001266, EnemyEtis, "EnemyEtis-1638");
				break;
			}
			case 37150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001247);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001267, EnemyEtis, "EnemyEtis-1639");
				break;
			}
			case 37180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001248);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001268, EnemyEtis, "EnemyEtis-1640");
				break;
			}
			case 37200: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002043);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002049, EnemyDrastea, "EnemyDrastea-1641");
				break;
			}
			case 37210: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001249);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001269, EnemyEtis, "EnemyEtis-1642");
				break;
			}
			case 37240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001250);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001270, EnemyEtis, "EnemyEtis-1643");
				break;
			}
			case 37270: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001251);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001271, EnemyEtis, "EnemyEtis-1644");
				break;
			}
			case 37300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001252);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001272, EnemyEtis, "EnemyEtis-1645");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002044);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002050, EnemyDrastea, "EnemyDrastea-1646");
				break;
			}
			case 37330: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001253);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001273, EnemyEtis, "EnemyEtis-1647");
				break;
			}
			case 37360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001254);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001274, EnemyEtis, "EnemyEtis-1648");
				break;
			}
			case 37390: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001255);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001275, EnemyEtis, "EnemyEtis-1649");
				break;
			}
			case 37400: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002045);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002051, EnemyDrastea, "EnemyDrastea-1650");
				break;
			}
			case 37420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001256);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001276, EnemyEtis, "EnemyEtis-1651");
				break;
			}
			case 37450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001257);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001277, EnemyEtis, "EnemyEtis-1652");
				break;
			}
			case 37480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001258);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001278, EnemyEtis, "EnemyEtis-1653");
				break;
			}
			case 37500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002046);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002052, EnemyDrastea, "EnemyDrastea-1654");
				break;
			}
			case 37510: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001259);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001279, EnemyEtis, "EnemyEtis-1655");
				break;
			}
			case 37540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001260);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001280, EnemyEtis, "EnemyEtis-1656");
				break;
			}
			case 37570: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001261);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001281, EnemyEtis, "EnemyEtis-1657");
				break;
			}
			case 37600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001262);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001282, EnemyEtis, "EnemyEtis-1658");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002047);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002053, EnemyDrastea, "EnemyDrastea-1659");
				break;
			}
			case 37630: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001263);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001283, EnemyEtis, "EnemyEtis-1660");
				break;
			}
			case 37660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001264);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001284, EnemyEtis, "EnemyEtis-1661");
				break;
			}
			case 37690: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001265);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001285, EnemyEtis, "EnemyEtis-1662");
				break;
			}
			case 37700: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002048);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002054, EnemyDrastea, "EnemyDrastea-1663");
				break;
			}
			case 37720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001266);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001286, EnemyEtis, "EnemyEtis-1664");
				break;
			}
			case 37750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001267);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001287, EnemyEtis, "EnemyEtis-1665");
				break;
			}
			case 37780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001268);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001288, EnemyEtis, "EnemyEtis-1666");
				break;
			}
			case 37800: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002049);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002055, EnemyDrastea, "EnemyDrastea-1667");
				break;
			}
			case 37810: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001269);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001289, EnemyEtis, "EnemyEtis-1668");
				break;
			}
			case 37840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001270);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001290, EnemyEtis, "EnemyEtis-1669");
				break;
			}
			case 37870: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001271);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001291, EnemyEtis, "EnemyEtis-1670");
				break;
			}
			case 37900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001272);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001292, EnemyEtis, "EnemyEtis-1671");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002050);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002056, EnemyDrastea, "EnemyDrastea-1672");
				break;
			}
			case 37930: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001273);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001293, EnemyEtis, "EnemyEtis-1673");
				break;
			}
			case 37960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001274);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001294, EnemyEtis, "EnemyEtis-1674");
				break;
			}
			case 37990: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001275);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001295, EnemyEtis, "EnemyEtis-1675");
				break;
			}
			case 38000: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002051);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002057, EnemyDrastea, "EnemyDrastea-1676");
				break;
			}
			case 38020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001276);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001296, EnemyEtis, "EnemyEtis-1677");
				break;
			}
			case 38050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001277);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001297, EnemyEtis, "EnemyEtis-1678");
				break;
			}
			case 38080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001278);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001298, EnemyEtis, "EnemyEtis-1679");
				break;
			}
			case 38100: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002052);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002058, EnemyDrastea, "EnemyDrastea-1680");
				break;
			}
			case 38110: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001279);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001299, EnemyEtis, "EnemyEtis-1681");
				break;
			}
			case 38140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001280);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001300, EnemyEtis, "EnemyEtis-1682");
				break;
			}
			case 38170: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001281);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001301, EnemyEtis, "EnemyEtis-1683");
				break;
			}
			case 38200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001282);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001302, EnemyEtis, "EnemyEtis-1684");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002053);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002059, EnemyDrastea, "EnemyDrastea-1685");
				break;
			}
			case 38230: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001283);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001303, EnemyEtis, "EnemyEtis-1686");
				break;
			}
			case 38260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001284);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001304, EnemyEtis, "EnemyEtis-1687");
				break;
			}
			case 38290: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001285);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001305, EnemyEtis, "EnemyEtis-1688");
				break;
			}
			case 38300: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002054);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002060, EnemyDrastea, "EnemyDrastea-1689");
				break;
			}
			case 38320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001286);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001306, EnemyEtis, "EnemyEtis-1690");
				break;
			}
			case 38350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001287);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001307, EnemyEtis, "EnemyEtis-1691");
				break;
			}
			case 38380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001288);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001308, EnemyEtis, "EnemyEtis-1692");
				break;
			}
			case 38400: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002055);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002061, EnemyDrastea, "EnemyDrastea-1693");
				break;
			}
			case 38410: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001289);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001309, EnemyEtis, "EnemyEtis-1694");
				break;
			}
			case 38440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001290);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001310, EnemyEtis, "EnemyEtis-1695");
				break;
			}
			case 38470: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001291);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001311, EnemyEtis, "EnemyEtis-1696");
				break;
			}
			case 38500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001292);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001312, EnemyEtis, "EnemyEtis-1697");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002056);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002062, EnemyDrastea, "EnemyDrastea-1698");
				break;
			}
			case 38530: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001293);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001313, EnemyEtis, "EnemyEtis-1699");
				break;
			}
			case 38560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001294);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001314, EnemyEtis, "EnemyEtis-1700");
				break;
			}
			case 38590: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001295);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001315, EnemyEtis, "EnemyEtis-1701");
				break;
			}
			case 38600: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002057);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002063, EnemyDrastea, "EnemyDrastea-1702");
				break;
			}
			case 38620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001296);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001316, EnemyEtis, "EnemyEtis-1703");
				break;
			}
			case 38650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001297);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001317, EnemyEtis, "EnemyEtis-1704");
				break;
			}
			case 38680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001298);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001318, EnemyEtis, "EnemyEtis-1705");
				break;
			}
			case 38700: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002058);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002064, EnemyDrastea, "EnemyDrastea-1706");
				break;
			}
			case 38710: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001299);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001319, EnemyEtis, "EnemyEtis-1707");
				break;
			}
			case 38740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001300);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001320, EnemyEtis, "EnemyEtis-1708");
				break;
			}
			case 38770: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001301);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001321, EnemyEtis, "EnemyEtis-1709");
				break;
			}
			case 38800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001302);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001322, EnemyEtis, "EnemyEtis-1710");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002059);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002065, EnemyDrastea, "EnemyDrastea-1711");
				break;
			}
			case 38830: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001303);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001323, EnemyEtis, "EnemyEtis-1712");
				break;
			}
			case 38860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001304);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001324, EnemyEtis, "EnemyEtis-1713");
				break;
			}
			case 38890: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001305);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001325, EnemyEtis, "EnemyEtis-1714");
				break;
			}
			case 38900: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002060);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002066, EnemyDrastea, "EnemyDrastea-1715");
				break;
			}
			case 38920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001306);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001326, EnemyEtis, "EnemyEtis-1716");
				break;
			}
			case 38950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001307);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001327, EnemyEtis, "EnemyEtis-1717");
				break;
			}
			case 38980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001308);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001328, EnemyEtis, "EnemyEtis-1718");
				break;
			}
			case 39000: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002061);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002067, EnemyDrastea, "EnemyDrastea-1719");
				break;
			}
			case 39010: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001309);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001329, EnemyEtis, "EnemyEtis-1720");
				break;
			}
			case 39040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001310);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001330, EnemyEtis, "EnemyEtis-1721");
				break;
			}
			case 39070: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001311);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001331, EnemyEtis, "EnemyEtis-1722");
				break;
			}
			case 39100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001312);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001332, EnemyEtis, "EnemyEtis-1723");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002062);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002068, EnemyDrastea, "EnemyDrastea-1724");
				break;
			}
			case 39130: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001313);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001333, EnemyEtis, "EnemyEtis-1725");
				break;
			}
			case 39160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001314);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001334, EnemyEtis, "EnemyEtis-1726");
				break;
			}
			case 39190: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001315);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001335, EnemyEtis, "EnemyEtis-1727");
				break;
			}
			case 39200: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002063);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002069, EnemyDrastea, "EnemyDrastea-1728");
				break;
			}
			case 39220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001316);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001336, EnemyEtis, "EnemyEtis-1729");
				break;
			}
			case 39250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001317);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001337, EnemyEtis, "EnemyEtis-1730");
				break;
			}
			case 39280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001318);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001338, EnemyEtis, "EnemyEtis-1731");
				break;
			}
			case 39300: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002064);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002070, EnemyDrastea, "EnemyDrastea-1732");
				break;
			}
			case 39310: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001319);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001339, EnemyEtis, "EnemyEtis-1733");
				break;
			}
			case 39340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001320);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001340, EnemyEtis, "EnemyEtis-1734");
				break;
			}
			case 39370: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001321);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001341, EnemyEtis, "EnemyEtis-1735");
				break;
			}
			case 39400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001322);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001342, EnemyEtis, "EnemyEtis-1736");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002065);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002071, EnemyDrastea, "EnemyDrastea-1737");
				break;
			}
			case 39430: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001323);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001343, EnemyEtis, "EnemyEtis-1738");
				break;
			}
			case 39460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001324);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001344, EnemyEtis, "EnemyEtis-1739");
				break;
			}
			case 39490: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001325);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001345, EnemyEtis, "EnemyEtis-1740");
				break;
			}
			case 39500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002066);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002072, EnemyDrastea, "EnemyDrastea-1741");
				break;
			}
			case 39520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001326);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001346, EnemyEtis, "EnemyEtis-1742");
				break;
			}
			case 39550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001327);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001347, EnemyEtis, "EnemyEtis-1743");
				break;
			}
			case 39580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001328);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001348, EnemyEtis, "EnemyEtis-1744");
				break;
			}
			case 39600: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002067);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002073, EnemyDrastea, "EnemyDrastea-1745");
				break;
			}
			case 39610: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001329);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001349, EnemyEtis, "EnemyEtis-1746");
				break;
			}
			case 39640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001330);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001350, EnemyEtis, "EnemyEtis-1747");
				break;
			}
			case 39670: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001331);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001351, EnemyEtis, "EnemyEtis-1748");
				break;
			}
			case 39700: {
				orderActorToFactory(10000010, EnemyErmione, "EnemyErmione-1749");
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001332);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001352, EnemyEtis, "EnemyEtis-1750");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002068);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002074, EnemyDrastea, "EnemyDrastea-1751");
				break;
			}
			case 39730: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001333);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001353, EnemyEtis, "EnemyEtis-1752");
				break;
			}
			case 39760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001334);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001354, EnemyEtis, "EnemyEtis-1753");
				break;
			}
			case 39790: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001335);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001355, EnemyEtis, "EnemyEtis-1754");
				break;
			}
			case 39800: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002069);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002075, EnemyDrastea, "EnemyDrastea-1755");
				break;
			}
			case 39820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001336);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001356, EnemyEtis, "EnemyEtis-1756");
				break;
			}
			case 39850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001337);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001357, EnemyEtis, "EnemyEtis-1757");
				break;
			}
			case 39880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001338);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001358, EnemyEtis, "EnemyEtis-1758");
				break;
			}
			case 39900: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002070);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002076, EnemyDrastea, "EnemyDrastea-1759");
				break;
			}
			case 39910: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001339);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001359, EnemyEtis, "EnemyEtis-1760");
				break;
			}
			case 39940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001340);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001360, EnemyEtis, "EnemyEtis-1761");
				break;
			}
			case 39970: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001341);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001361, EnemyEtis, "EnemyEtis-1762");
				break;
			}
			case 40000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001342);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001362, EnemyEtis, "EnemyEtis-1763");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002071);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002077, EnemyDrastea, "EnemyDrastea-1764");
				break;
			}
			case 40030: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001343);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001363, EnemyEtis, "EnemyEtis-1765");
				break;
			}
			case 40060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001344);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001364, EnemyEtis, "EnemyEtis-1766");
				break;
			}
			case 40090: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001345);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001365, EnemyEtis, "EnemyEtis-1767");
				break;
			}
			case 40100: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002072);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002078, EnemyDrastea, "EnemyDrastea-1768");
				break;
			}
			case 40120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001346);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001366, EnemyEtis, "EnemyEtis-1769");
				break;
			}
			case 40150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001347);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001367, EnemyEtis, "EnemyEtis-1770");
				break;
			}
			case 40180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001348);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001368, EnemyEtis, "EnemyEtis-1771");
				break;
			}
			case 40200: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002073);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002079, EnemyDrastea, "EnemyDrastea-1772");
				break;
			}
			case 40210: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001349);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001369, EnemyEtis, "EnemyEtis-1773");
				break;
			}
			case 40240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001350);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001370, EnemyEtis, "EnemyEtis-1774");
				break;
			}
			case 40270: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001351);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001371, EnemyEtis, "EnemyEtis-1775");
				break;
			}
			case 40300: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(10000010);
				bringDirector()->addSubGroup(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001352);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001372, EnemyEtis, "EnemyEtis-1776");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002074);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002080, EnemyDrastea, "EnemyDrastea-1777");
				break;
			}
			case 40330: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001353);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001373, EnemyEtis, "EnemyEtis-1778");
				break;
			}
			case 40360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001354);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001374, EnemyEtis, "EnemyEtis-1779");
				break;
			}
			case 40390: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001355);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001375, EnemyEtis, "EnemyEtis-1780");
				break;
			}
			case 40400: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002075);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002081, EnemyDrastea, "EnemyDrastea-1781");
				break;
			}
			case 40420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001356);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001376, EnemyEtis, "EnemyEtis-1782");
				break;
			}
			case 40450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001357);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001377, EnemyEtis, "EnemyEtis-1783");
				break;
			}
			case 40480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001358);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001378, EnemyEtis, "EnemyEtis-1784");
				break;
			}
			case 40500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002076);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002082, EnemyDrastea, "EnemyDrastea-1785");
				break;
			}
			case 40510: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001359);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001379, EnemyEtis, "EnemyEtis-1786");
				break;
			}
			case 40540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001360);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001380, EnemyEtis, "EnemyEtis-1787");
				break;
			}
			case 40570: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001361);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001381, EnemyEtis, "EnemyEtis-1788");
				break;
			}
			case 40600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001362);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001382, EnemyEtis, "EnemyEtis-1789");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002077);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002083, EnemyDrastea, "EnemyDrastea-1790");
				break;
			}
			case 40630: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001363);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001383, EnemyEtis, "EnemyEtis-1791");
				break;
			}
			case 40660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001364);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001384, EnemyEtis, "EnemyEtis-1792");
				break;
			}
			case 40690: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001365);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001385, EnemyEtis, "EnemyEtis-1793");
				break;
			}
			case 40700: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002078);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002084, EnemyDrastea, "EnemyDrastea-1794");
				break;
			}
			case 40720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001366);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001386, EnemyEtis, "EnemyEtis-1795");
				break;
			}
			case 40750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001367);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001387, EnemyEtis, "EnemyEtis-1796");
				break;
			}
			case 40780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001368);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001388, EnemyEtis, "EnemyEtis-1797");
				break;
			}
			case 40800: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002079);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002085, EnemyDrastea, "EnemyDrastea-1798");
				break;
			}
			case 40810: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001369);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001389, EnemyEtis, "EnemyEtis-1799");
				break;
			}
			case 40840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001370);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001390, EnemyEtis, "EnemyEtis-1800");
				break;
			}
			case 40870: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001371);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001391, EnemyEtis, "EnemyEtis-1801");
				break;
			}
			case 40900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001372);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001392, EnemyEtis, "EnemyEtis-1802");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002080);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002086, EnemyDrastea, "EnemyDrastea-1803");
				break;
			}
			case 40930: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001373);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001393, EnemyEtis, "EnemyEtis-1804");
				break;
			}
			case 40960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001374);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001394, EnemyEtis, "EnemyEtis-1805");
				break;
			}
			case 40990: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001375);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001395, EnemyEtis, "EnemyEtis-1806");
				break;
			}
			case 41000: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002081);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002087, EnemyDrastea, "EnemyDrastea-1807");
				break;
			}
			case 41020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001376);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001396, EnemyEtis, "EnemyEtis-1808");
				break;
			}
			case 41050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001377);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001397, EnemyEtis, "EnemyEtis-1809");
				break;
			}
			case 41080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001378);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001398, EnemyEtis, "EnemyEtis-1810");
				break;
			}
			case 41100: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002082);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002088, EnemyDrastea, "EnemyDrastea-1811");
				break;
			}
			case 41110: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001379);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001399, EnemyEtis, "EnemyEtis-1812");
				break;
			}
			case 41140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001380);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001400, EnemyEtis, "EnemyEtis-1813");
				break;
			}
			case 41170: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001381);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001401, EnemyEtis, "EnemyEtis-1814");
				break;
			}
			case 41200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001382);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001402, EnemyEtis, "EnemyEtis-1815");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002083);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002089, EnemyDrastea, "EnemyDrastea-1816");
				break;
			}
			case 41230: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001383);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001403, EnemyEtis, "EnemyEtis-1817");
				break;
			}
			case 41260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001384);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001404, EnemyEtis, "EnemyEtis-1818");
				break;
			}
			case 41290: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001385);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001405, EnemyEtis, "EnemyEtis-1819");
				break;
			}
			case 41300: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002084);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002090, EnemyDrastea, "EnemyDrastea-1820");
				break;
			}
			case 41320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001386);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001406, EnemyEtis, "EnemyEtis-1821");
				break;
			}
			case 41350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001387);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001407, EnemyEtis, "EnemyEtis-1822");
				break;
			}
			case 41380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001388);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001408, EnemyEtis, "EnemyEtis-1823");
				break;
			}
			case 41400: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002085);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002091, EnemyDrastea, "EnemyDrastea-1824");
				break;
			}
			case 41410: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001389);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001409, EnemyEtis, "EnemyEtis-1825");
				break;
			}
			case 41440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001390);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001410, EnemyEtis, "EnemyEtis-1826");
				break;
			}
			case 41470: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001391);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001411, EnemyEtis, "EnemyEtis-1827");
				break;
			}
			case 41500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001392);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001412, EnemyEtis, "EnemyEtis-1828");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002086);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002092, EnemyDrastea, "EnemyDrastea-1829");
				break;
			}
			case 41530: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001393);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001413, EnemyEtis, "EnemyEtis-1830");
				break;
			}
			case 41560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001394);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001414, EnemyEtis, "EnemyEtis-1831");
				break;
			}
			case 41590: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001395);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001415, EnemyEtis, "EnemyEtis-1832");
				break;
			}
			case 41600: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002087);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002093, EnemyDrastea, "EnemyDrastea-1833");
				break;
			}
			case 41620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001396);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001416, EnemyEtis, "EnemyEtis-1834");
				break;
			}
			case 41650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001397);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001417, EnemyEtis, "EnemyEtis-1835");
				break;
			}
			case 41680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001398);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001418, EnemyEtis, "EnemyEtis-1836");
				break;
			}
			case 41700: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002088);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002094, EnemyDrastea, "EnemyDrastea-1837");
				break;
			}
			case 41710: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001399);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001419, EnemyEtis, "EnemyEtis-1838");
				break;
			}
			case 41740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001400);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001420, EnemyEtis, "EnemyEtis-1839");
				break;
			}
			case 41770: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001401);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001421, EnemyEtis, "EnemyEtis-1840");
				break;
			}
			case 41800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001402);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001422, EnemyEtis, "EnemyEtis-1841");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002089);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002095, EnemyDrastea, "EnemyDrastea-1842");
				break;
			}
			case 41830: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001403);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001423, EnemyEtis, "EnemyEtis-1843");
				break;
			}
			case 41860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001404);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001424, EnemyEtis, "EnemyEtis-1844");
				break;
			}
			case 41890: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001405);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001425, EnemyEtis, "EnemyEtis-1845");
				break;
			}
			case 41900: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002090);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002096, EnemyDrastea, "EnemyDrastea-1846");
				break;
			}
			case 41920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001406);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001426, EnemyEtis, "EnemyEtis-1847");
				break;
			}
			case 41950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001407);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001427, EnemyEtis, "EnemyEtis-1848");
				break;
			}
			case 41980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001408);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001428, EnemyEtis, "EnemyEtis-1849");
				break;
			}
			case 42000: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002091);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002097, EnemyDrastea, "EnemyDrastea-1850");
				break;
			}
			case 42010: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001409);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001429, EnemyEtis, "EnemyEtis-1851");
				break;
			}
			case 42040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001410);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001430, EnemyEtis, "EnemyEtis-1852");
				break;
			}
			case 42070: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001411);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001431, EnemyEtis, "EnemyEtis-1853");
				break;
			}
			case 42100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001412);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001432, EnemyEtis, "EnemyEtis-1854");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002092);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002098, EnemyDrastea, "EnemyDrastea-1855");
				break;
			}
			case 42130: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001413);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001433, EnemyEtis, "EnemyEtis-1856");
				break;
			}
			case 42160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001414);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001434, EnemyEtis, "EnemyEtis-1857");
				break;
			}
			case 42190: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001415);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001435, EnemyEtis, "EnemyEtis-1858");
				break;
			}
			case 42200: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002093);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002099, EnemyDrastea, "EnemyDrastea-1859");
				break;
			}
			case 42220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001416);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001436, EnemyEtis, "EnemyEtis-1860");
				break;
			}
			case 42250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001417);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001437, EnemyEtis, "EnemyEtis-1861");
				break;
			}
			case 42280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001418);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001438, EnemyEtis, "EnemyEtis-1862");
				break;
			}
			case 42300: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002094);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002100, EnemyDrastea, "EnemyDrastea-1863");
				break;
			}
			case 42310: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001419);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001439, EnemyEtis, "EnemyEtis-1864");
				break;
			}
			case 42340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001420);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001440, EnemyEtis, "EnemyEtis-1865");
				break;
			}
			case 42370: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001421);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001441, EnemyEtis, "EnemyEtis-1866");
				break;
			}
			case 42400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001422);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001442, EnemyEtis, "EnemyEtis-1867");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002095);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002101, EnemyDrastea, "EnemyDrastea-1868");
				break;
			}
			case 42430: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001423);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001443, EnemyEtis, "EnemyEtis-1869");
				break;
			}
			case 42460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001424);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001444, EnemyEtis, "EnemyEtis-1870");
				break;
			}
			case 42490: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001425);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001445, EnemyEtis, "EnemyEtis-1871");
				break;
			}
			case 42500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002096);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002102, EnemyDrastea, "EnemyDrastea-1872");
				break;
			}
			case 42520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001426);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001446, EnemyEtis, "EnemyEtis-1873");
				break;
			}
			case 42550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001427);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001447, EnemyEtis, "EnemyEtis-1874");
				break;
			}
			case 42580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001428);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001448, EnemyEtis, "EnemyEtis-1875");
				break;
			}
			case 42600: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002097);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002103, EnemyDrastea, "EnemyDrastea-1876");
				break;
			}
			case 42610: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001429);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001449, EnemyEtis, "EnemyEtis-1877");
				break;
			}
			case 42640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001430);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001450, EnemyEtis, "EnemyEtis-1878");
				break;
			}
			case 42670: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001431);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001451, EnemyEtis, "EnemyEtis-1879");
				break;
			}
			case 42700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001432);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001452, EnemyEtis, "EnemyEtis-1880");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002098);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002104, EnemyDrastea, "EnemyDrastea-1881");
				break;
			}
			case 42730: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001433);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001453, EnemyEtis, "EnemyEtis-1882");
				break;
			}
			case 42760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001434);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001454, EnemyEtis, "EnemyEtis-1883");
				break;
			}
			case 42790: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001435);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001455, EnemyEtis, "EnemyEtis-1884");
				break;
			}
			case 42800: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002099);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002105, EnemyDrastea, "EnemyDrastea-1885");
				break;
			}
			case 42820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001436);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001456, EnemyEtis, "EnemyEtis-1886");
				break;
			}
			case 42850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001437);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001457, EnemyEtis, "EnemyEtis-1887");
				break;
			}
			case 42880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001438);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001458, EnemyEtis, "EnemyEtis-1888");
				break;
			}
			case 42900: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002100);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002106, EnemyDrastea, "EnemyDrastea-1889");
				break;
			}
			case 42910: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001439);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001459, EnemyEtis, "EnemyEtis-1890");
				break;
			}
			case 42940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001440);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001460, EnemyEtis, "EnemyEtis-1891");
				break;
			}
			case 42970: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001441);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001461, EnemyEtis, "EnemyEtis-1892");
				break;
			}
			case 43000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001442);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001462, EnemyEtis, "EnemyEtis-1893");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002101);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002107, EnemyDrastea, "EnemyDrastea-1894");
				break;
			}
			case 43030: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001443);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001463, EnemyEtis, "EnemyEtis-1895");
				break;
			}
			case 43060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001444);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001464, EnemyEtis, "EnemyEtis-1896");
				break;
			}
			case 43090: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001445);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001465, EnemyEtis, "EnemyEtis-1897");
				break;
			}
			case 43100: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002102);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002108, EnemyDrastea, "EnemyDrastea-1898");
				break;
			}
			case 43120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001446);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001466, EnemyEtis, "EnemyEtis-1899");
				break;
			}
			case 43150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001447);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001467, EnemyEtis, "EnemyEtis-1900");
				break;
			}
			case 43180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001448);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001468, EnemyEtis, "EnemyEtis-1901");
				break;
			}
			case 43200: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002103);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002109, EnemyDrastea, "EnemyDrastea-1902");
				break;
			}
			case 43210: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001449);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001469, EnemyEtis, "EnemyEtis-1903");
				break;
			}
			case 43240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001450);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001470, EnemyEtis, "EnemyEtis-1904");
				break;
			}
			case 43270: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001451);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001471, EnemyEtis, "EnemyEtis-1905");
				break;
			}
			case 43300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001452);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001472, EnemyEtis, "EnemyEtis-1906");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002104);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002110, EnemyDrastea, "EnemyDrastea-1907");
				break;
			}
			case 43330: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001453);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001473, EnemyEtis, "EnemyEtis-1908");
				break;
			}
			case 43360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001454);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001474, EnemyEtis, "EnemyEtis-1909");
				break;
			}
			case 43390: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001455);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001475, EnemyEtis, "EnemyEtis-1910");
				break;
			}
			case 43400: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002105);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002111, EnemyDrastea, "EnemyDrastea-1911");
				break;
			}
			case 43420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001456);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001476, EnemyEtis, "EnemyEtis-1912");
				break;
			}
			case 43450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001457);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001477, EnemyEtis, "EnemyEtis-1913");
				break;
			}
			case 43480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001458);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001478, EnemyEtis, "EnemyEtis-1914");
				break;
			}
			case 43500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002106);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002112, EnemyDrastea, "EnemyDrastea-1915");
				break;
			}
			case 43510: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001459);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001479, EnemyEtis, "EnemyEtis-1916");
				break;
			}
			case 43540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001460);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001480, EnemyEtis, "EnemyEtis-1917");
				break;
			}
			case 43570: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001461);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001481, EnemyEtis, "EnemyEtis-1918");
				break;
			}
			case 43600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001462);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001482, EnemyEtis, "EnemyEtis-1919");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002107);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002113, EnemyDrastea, "EnemyDrastea-1920");
				break;
			}
			case 43630: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001463);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001483, EnemyEtis, "EnemyEtis-1921");
				break;
			}
			case 43660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001464);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001484, EnemyEtis, "EnemyEtis-1922");
				break;
			}
			case 43690: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001465);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001485, EnemyEtis, "EnemyEtis-1923");
				break;
			}
			case 43700: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002108);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002114, EnemyDrastea, "EnemyDrastea-1924");
				break;
			}
			case 43720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001466);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001486, EnemyEtis, "EnemyEtis-1925");
				break;
			}
			case 43750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001467);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001487, EnemyEtis, "EnemyEtis-1926");
				break;
			}
			case 43780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001468);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001488, EnemyEtis, "EnemyEtis-1927");
				break;
			}
			case 43800: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002109);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002115, EnemyDrastea, "EnemyDrastea-1928");
				break;
			}
			case 43810: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001469);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001489, EnemyEtis, "EnemyEtis-1929");
				break;
			}
			case 43840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001470);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001490, EnemyEtis, "EnemyEtis-1930");
				break;
			}
			case 43870: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001471);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001491, EnemyEtis, "EnemyEtis-1931");
				break;
			}
			case 43900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001472);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001492, EnemyEtis, "EnemyEtis-1932");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002110);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002116, EnemyDrastea, "EnemyDrastea-1933");
				break;
			}
			case 43930: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001473);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001493, EnemyEtis, "EnemyEtis-1934");
				break;
			}
			case 43960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001474);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001494, EnemyEtis, "EnemyEtis-1935");
				break;
			}
			case 43990: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001475);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001495, EnemyEtis, "EnemyEtis-1936");
				break;
			}
			case 44000: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002111);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002117, EnemyDrastea, "EnemyDrastea-1937");
				break;
			}
			case 44020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001476);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001496, EnemyEtis, "EnemyEtis-1938");
				break;
			}
			case 44050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001477);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001497, EnemyEtis, "EnemyEtis-1939");
				break;
			}
			case 44080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001478);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001498, EnemyEtis, "EnemyEtis-1940");
				break;
			}
			case 44100: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002112);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002118, EnemyDrastea, "EnemyDrastea-1941");
				break;
			}
			case 44110: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001479);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001499, EnemyEtis, "EnemyEtis-1942");
				break;
			}
			case 44140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001480);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001500, EnemyEtis, "EnemyEtis-1943");
				break;
			}
			case 44170: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001481);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001501, EnemyEtis, "EnemyEtis-1944");
				break;
			}
			case 44200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001482);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001502, EnemyEtis, "EnemyEtis-1945");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002113);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002119, EnemyDrastea, "EnemyDrastea-1946");
				break;
			}
			case 44230: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001483);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001503, EnemyEtis, "EnemyEtis-1947");
				break;
			}
			case 44260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001484);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001504, EnemyEtis, "EnemyEtis-1948");
				break;
			}
			case 44290: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001485);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001505, EnemyEtis, "EnemyEtis-1949");
				break;
			}
			case 44300: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002114);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002120, EnemyDrastea, "EnemyDrastea-1950");
				break;
			}
			case 44320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001486);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001506, EnemyEtis, "EnemyEtis-1951");
				break;
			}
			case 44350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001487);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001507, EnemyEtis, "EnemyEtis-1952");
				break;
			}
			case 44380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001488);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001508, EnemyEtis, "EnemyEtis-1953");
				break;
			}
			case 44400: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002115);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002121, EnemyDrastea, "EnemyDrastea-1954");
				break;
			}
			case 44410: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001489);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001509, EnemyEtis, "EnemyEtis-1955");
				break;
			}
			case 44440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001490);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001510, EnemyEtis, "EnemyEtis-1956");
				break;
			}
			case 44470: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001491);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001511, EnemyEtis, "EnemyEtis-1957");
				break;
			}
			case 44500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001492);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001512, EnemyEtis, "EnemyEtis-1958");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002116);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002122, EnemyDrastea, "EnemyDrastea-1959");
				break;
			}
			case 44530: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001493);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001513, EnemyEtis, "EnemyEtis-1960");
				break;
			}
			case 44560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001494);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001514, EnemyEtis, "EnemyEtis-1961");
				break;
			}
			case 44590: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001495);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001515, EnemyEtis, "EnemyEtis-1962");
				break;
			}
			case 44600: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002117);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002123, EnemyDrastea, "EnemyDrastea-1963");
				break;
			}
			case 44620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001496);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001516, EnemyEtis, "EnemyEtis-1964");
				break;
			}
			case 44650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001497);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001517, EnemyEtis, "EnemyEtis-1965");
				break;
			}
			case 44680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001498);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001518, EnemyEtis, "EnemyEtis-1966");
				break;
			}
			case 44700: {
				orderActorToFactory(10000011, EnemyErmione, "EnemyErmione-1967");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002118);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002124, EnemyDrastea, "EnemyDrastea-1968");
				break;
			}
			case 44710: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001499);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001519, EnemyEtis, "EnemyEtis-1969");
				break;
			}
			case 44740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001500);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001520, EnemyEtis, "EnemyEtis-1970");
				break;
			}
			case 44770: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001501);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001521, EnemyEtis, "EnemyEtis-1971");
				break;
			}
			case 44800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001502);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001522, EnemyEtis, "EnemyEtis-1972");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002119);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002125, EnemyDrastea, "EnemyDrastea-1973");
				break;
			}
			case 44830: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001503);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001523, EnemyEtis, "EnemyEtis-1974");
				break;
			}
			case 44860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001504);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001524, EnemyEtis, "EnemyEtis-1975");
				break;
			}
			case 44890: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001505);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001525, EnemyEtis, "EnemyEtis-1976");
				break;
			}
			case 44900: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002120);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002126, EnemyDrastea, "EnemyDrastea-1977");
				break;
			}
			case 44920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001506);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001526, EnemyEtis, "EnemyEtis-1978");
				break;
			}
			case 44950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001507);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001527, EnemyEtis, "EnemyEtis-1979");
				break;
			}
			case 44980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001508);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001528, EnemyEtis, "EnemyEtis-1980");
				break;
			}
			case 45000: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002121);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002127, EnemyDrastea, "EnemyDrastea-1981");
				break;
			}
			case 45010: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001509);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001529, EnemyEtis, "EnemyEtis-1982");
				break;
			}
			case 45040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001510);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001530, EnemyEtis, "EnemyEtis-1983");
				break;
			}
			case 45070: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001511);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001531, EnemyEtis, "EnemyEtis-1984");
				break;
			}
			case 45100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001512);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001532, EnemyEtis, "EnemyEtis-1985");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002122);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002128, EnemyDrastea, "EnemyDrastea-1986");
				break;
			}
			case 45130: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001513);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001533, EnemyEtis, "EnemyEtis-1987");
				break;
			}
			case 45160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001514);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001534, EnemyEtis, "EnemyEtis-1988");
				break;
			}
			case 45190: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001515);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001535, EnemyEtis, "EnemyEtis-1989");
				break;
			}
			case 45200: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002123);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002129, EnemyDrastea, "EnemyDrastea-1990");
				break;
			}
			case 45220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001516);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001536, EnemyEtis, "EnemyEtis-1991");
				break;
			}
			case 45250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001517);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001537, EnemyEtis, "EnemyEtis-1992");
				break;
			}
			case 45280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001518);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001538, EnemyEtis, "EnemyEtis-1993");
				break;
			}
			case 45300: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(10000011);
				bringDirector()->addSubGroup(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002124);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002130, EnemyDrastea, "EnemyDrastea-1994");
				break;
			}
			case 45310: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001519);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001539, EnemyEtis, "EnemyEtis-1995");
				break;
			}
			case 45340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001520);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001540, EnemyEtis, "EnemyEtis-1996");
				break;
			}
			case 45370: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001521);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001541, EnemyEtis, "EnemyEtis-1997");
				break;
			}
			case 45400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001522);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001542, EnemyEtis, "EnemyEtis-1998");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002125);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002131, EnemyDrastea, "EnemyDrastea-1999");
				break;
			}
			case 45430: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001523);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001543, EnemyEtis, "EnemyEtis-2000");
				break;
			}
			case 45460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001524);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001544, EnemyEtis, "EnemyEtis-2001");
				break;
			}
			case 45490: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001525);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001545, EnemyEtis, "EnemyEtis-2002");
				break;
			}
			case 45500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002126);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002132, EnemyDrastea, "EnemyDrastea-2003");
				break;
			}
			case 45520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001526);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001546, EnemyEtis, "EnemyEtis-2004");
				break;
			}
			case 45550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001527);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001547, EnemyEtis, "EnemyEtis-2005");
				break;
			}
			case 45580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001528);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001548, EnemyEtis, "EnemyEtis-2006");
				break;
			}
			case 45600: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002127);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002133, EnemyDrastea, "EnemyDrastea-2007");
				break;
			}
			case 45610: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001529);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001549, EnemyEtis, "EnemyEtis-2008");
				break;
			}
			case 45640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001530);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001550, EnemyEtis, "EnemyEtis-2009");
				break;
			}
			case 45670: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001531);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001551, EnemyEtis, "EnemyEtis-2010");
				break;
			}
			case 45700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001532);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001552, EnemyEtis, "EnemyEtis-2011");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002128);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002134, EnemyDrastea, "EnemyDrastea-2012");
				break;
			}
			case 45730: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001533);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001553, EnemyEtis, "EnemyEtis-2013");
				break;
			}
			case 45760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001534);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001554, EnemyEtis, "EnemyEtis-2014");
				break;
			}
			case 45790: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001535);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001555, EnemyEtis, "EnemyEtis-2015");
				break;
			}
			case 45800: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002129);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002135, EnemyDrastea, "EnemyDrastea-2016");
				break;
			}
			case 45820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001536);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001556, EnemyEtis, "EnemyEtis-2017");
				break;
			}
			case 45850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001537);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001557, EnemyEtis, "EnemyEtis-2018");
				break;
			}
			case 45880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001538);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001558, EnemyEtis, "EnemyEtis-2019");
				break;
			}
			case 45900: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002130);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002136, EnemyDrastea, "EnemyDrastea-2020");
				break;
			}
			case 45910: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001539);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001559, EnemyEtis, "EnemyEtis-2021");
				break;
			}
			case 45940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001540);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001560, EnemyEtis, "EnemyEtis-2022");
				break;
			}
			case 45970: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001541);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001561, EnemyEtis, "EnemyEtis-2023");
				break;
			}
			case 46000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001542);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001562, EnemyEtis, "EnemyEtis-2024");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002131);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002137, EnemyDrastea, "EnemyDrastea-2025");
				break;
			}
			case 46030: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001543);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001563, EnemyEtis, "EnemyEtis-2026");
				break;
			}
			case 46060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001544);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001564, EnemyEtis, "EnemyEtis-2027");
				break;
			}
			case 46090: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001545);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001565, EnemyEtis, "EnemyEtis-2028");
				break;
			}
			case 46100: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002132);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002138, EnemyDrastea, "EnemyDrastea-2029");
				break;
			}
			case 46120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001546);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001566, EnemyEtis, "EnemyEtis-2030");
				break;
			}
			case 46150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001547);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001567, EnemyEtis, "EnemyEtis-2031");
				break;
			}
			case 46180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001548);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001568, EnemyEtis, "EnemyEtis-2032");
				break;
			}
			case 46200: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002133);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002139, EnemyDrastea, "EnemyDrastea-2033");
				break;
			}
			case 46210: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001549);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001569, EnemyEtis, "EnemyEtis-2034");
				break;
			}
			case 46240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001550);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001570, EnemyEtis, "EnemyEtis-2035");
				break;
			}
			case 46270: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001551);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001571, EnemyEtis, "EnemyEtis-2036");
				break;
			}
			case 46300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001552);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001572, EnemyEtis, "EnemyEtis-2037");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002134);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002140, EnemyDrastea, "EnemyDrastea-2038");
				break;
			}
			case 46330: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001553);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001573, EnemyEtis, "EnemyEtis-2039");
				break;
			}
			case 46360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001554);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001574, EnemyEtis, "EnemyEtis-2040");
				break;
			}
			case 46390: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001555);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001575, EnemyEtis, "EnemyEtis-2041");
				break;
			}
			case 46400: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002135);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002141, EnemyDrastea, "EnemyDrastea-2042");
				break;
			}
			case 46420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001556);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001576, EnemyEtis, "EnemyEtis-2043");
				break;
			}
			case 46450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001557);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001577, EnemyEtis, "EnemyEtis-2044");
				break;
			}
			case 46480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001558);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001578, EnemyEtis, "EnemyEtis-2045");
				break;
			}
			case 46500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002136);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002142, EnemyDrastea, "EnemyDrastea-2046");
				break;
			}
			case 46510: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001559);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001579, EnemyEtis, "EnemyEtis-2047");
				break;
			}
			case 46540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001560);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001580, EnemyEtis, "EnemyEtis-2048");
				break;
			}
			case 46570: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001561);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001581, EnemyEtis, "EnemyEtis-2049");
				break;
			}
			case 46600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001562);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001582, EnemyEtis, "EnemyEtis-2050");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002137);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002143, EnemyDrastea, "EnemyDrastea-2051");
				break;
			}
			case 46630: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001563);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001583, EnemyEtis, "EnemyEtis-2052");
				break;
			}
			case 46660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001564);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001584, EnemyEtis, "EnemyEtis-2053");
				break;
			}
			case 46690: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001565);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001585, EnemyEtis, "EnemyEtis-2054");
				break;
			}
			case 46700: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002138);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002144, EnemyDrastea, "EnemyDrastea-2055");
				break;
			}
			case 46720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001566);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001586, EnemyEtis, "EnemyEtis-2056");
				break;
			}
			case 46750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001567);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001587, EnemyEtis, "EnemyEtis-2057");
				break;
			}
			case 46780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001568);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001588, EnemyEtis, "EnemyEtis-2058");
				break;
			}
			case 46800: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002139);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002145, EnemyDrastea, "EnemyDrastea-2059");
				break;
			}
			case 46810: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001569);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001589, EnemyEtis, "EnemyEtis-2060");
				break;
			}
			case 46840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001570);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001590, EnemyEtis, "EnemyEtis-2061");
				break;
			}
			case 46870: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001571);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001591, EnemyEtis, "EnemyEtis-2062");
				break;
			}
			case 46900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001572);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001592, EnemyEtis, "EnemyEtis-2063");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002140);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002146, EnemyDrastea, "EnemyDrastea-2064");
				break;
			}
			case 46930: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001573);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001593, EnemyEtis, "EnemyEtis-2065");
				break;
			}
			case 46960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001574);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001594, EnemyEtis, "EnemyEtis-2066");
				break;
			}
			case 46990: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001575);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001595, EnemyEtis, "EnemyEtis-2067");
				break;
			}
			case 47000: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002141);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002147, EnemyDrastea, "EnemyDrastea-2068");
				break;
			}
			case 47020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001576);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001596, EnemyEtis, "EnemyEtis-2069");
				break;
			}
			case 47050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001577);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001597, EnemyEtis, "EnemyEtis-2070");
				break;
			}
			case 47080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001578);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001598, EnemyEtis, "EnemyEtis-2071");
				break;
			}
			case 47100: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002142);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002148, EnemyDrastea, "EnemyDrastea-2072");
				break;
			}
			case 47110: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001579);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001599, EnemyEtis, "EnemyEtis-2073");
				break;
			}
			case 47140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001580);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001600, EnemyEtis, "EnemyEtis-2074");
				break;
			}
			case 47170: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001581);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001601, EnemyEtis, "EnemyEtis-2075");
				break;
			}
			case 47200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001582);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001602, EnemyEtis, "EnemyEtis-2076");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002143);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002149, EnemyDrastea, "EnemyDrastea-2077");
				break;
			}
			case 47230: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001583);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001603, EnemyEtis, "EnemyEtis-2078");
				break;
			}
			case 47260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001584);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001604, EnemyEtis, "EnemyEtis-2079");
				break;
			}
			case 47290: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001585);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001605, EnemyEtis, "EnemyEtis-2080");
				break;
			}
			case 47300: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002144);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002150, EnemyDrastea, "EnemyDrastea-2081");
				break;
			}
			case 47320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001586);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001606, EnemyEtis, "EnemyEtis-2082");
				break;
			}
			case 47350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001587);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001607, EnemyEtis, "EnemyEtis-2083");
				break;
			}
			case 47380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001588);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001608, EnemyEtis, "EnemyEtis-2084");
				break;
			}
			case 47400: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002145);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002151, EnemyDrastea, "EnemyDrastea-2085");
				break;
			}
			case 47410: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001589);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001609, EnemyEtis, "EnemyEtis-2086");
				break;
			}
			case 47440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001590);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001610, EnemyEtis, "EnemyEtis-2087");
				break;
			}
			case 47470: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001591);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001611, EnemyEtis, "EnemyEtis-2088");
				break;
			}
			case 47500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001592);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001612, EnemyEtis, "EnemyEtis-2089");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002146);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002152, EnemyDrastea, "EnemyDrastea-2090");
				break;
			}
			case 47530: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001593);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001613, EnemyEtis, "EnemyEtis-2091");
				break;
			}
			case 47560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001594);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001614, EnemyEtis, "EnemyEtis-2092");
				break;
			}
			case 47590: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001595);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001615, EnemyEtis, "EnemyEtis-2093");
				break;
			}
			case 47600: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002147);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002153, EnemyDrastea, "EnemyDrastea-2094");
				break;
			}
			case 47620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001596);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001616, EnemyEtis, "EnemyEtis-2095");
				break;
			}
			case 47650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001597);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001617, EnemyEtis, "EnemyEtis-2096");
				break;
			}
			case 47680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001598);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001618, EnemyEtis, "EnemyEtis-2097");
				break;
			}
			case 47700: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002148);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002154, EnemyDrastea, "EnemyDrastea-2098");
				break;
			}
			case 47710: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001599);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001619, EnemyEtis, "EnemyEtis-2099");
				break;
			}
			case 47740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001600);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001620, EnemyEtis, "EnemyEtis-2100");
				break;
			}
			case 47770: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001601);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001621, EnemyEtis, "EnemyEtis-2101");
				break;
			}
			case 47800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001602);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001622, EnemyEtis, "EnemyEtis-2102");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002149);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002155, EnemyDrastea, "EnemyDrastea-2103");
				break;
			}
			case 47830: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001603);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001623, EnemyEtis, "EnemyEtis-2104");
				break;
			}
			case 47860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001604);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001624, EnemyEtis, "EnemyEtis-2105");
				break;
			}
			case 47890: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001605);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001625, EnemyEtis, "EnemyEtis-2106");
				break;
			}
			case 47900: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002150);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002156, EnemyDrastea, "EnemyDrastea-2107");
				break;
			}
			case 47920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001606);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001626, EnemyEtis, "EnemyEtis-2108");
				break;
			}
			case 47950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001607);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001627, EnemyEtis, "EnemyEtis-2109");
				break;
			}
			case 47980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001608);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001628, EnemyEtis, "EnemyEtis-2110");
				break;
			}
			case 48000: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002151);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002157, EnemyDrastea, "EnemyDrastea-2111");
				break;
			}
			case 48010: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001609);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001629, EnemyEtis, "EnemyEtis-2112");
				break;
			}
			case 48040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001610);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001630, EnemyEtis, "EnemyEtis-2113");
				break;
			}
			case 48070: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001611);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001631, EnemyEtis, "EnemyEtis-2114");
				break;
			}
			case 48100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001612);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001632, EnemyEtis, "EnemyEtis-2115");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002152);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002158, EnemyDrastea, "EnemyDrastea-2116");
				break;
			}
			case 48130: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001613);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001633, EnemyEtis, "EnemyEtis-2117");
				break;
			}
			case 48160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001614);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001634, EnemyEtis, "EnemyEtis-2118");
				break;
			}
			case 48190: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001615);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001635, EnemyEtis, "EnemyEtis-2119");
				break;
			}
			case 48200: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002153);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002159, EnemyDrastea, "EnemyDrastea-2120");
				break;
			}
			case 48220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001616);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001636, EnemyEtis, "EnemyEtis-2121");
				break;
			}
			case 48250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001617);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001637, EnemyEtis, "EnemyEtis-2122");
				break;
			}
			case 48280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001618);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001638, EnemyEtis, "EnemyEtis-2123");
				break;
			}
			case 48300: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002154);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002160, EnemyDrastea, "EnemyDrastea-2124");
				break;
			}
			case 48310: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001619);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001639, EnemyEtis, "EnemyEtis-2125");
				break;
			}
			case 48340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001620);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001640, EnemyEtis, "EnemyEtis-2126");
				break;
			}
			case 48370: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001621);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001641, EnemyEtis, "EnemyEtis-2127");
				break;
			}
			case 48400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001622);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001642, EnemyEtis, "EnemyEtis-2128");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002155);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002161, EnemyDrastea, "EnemyDrastea-2129");
				break;
			}
			case 48430: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001623);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001643, EnemyEtis, "EnemyEtis-2130");
				break;
			}
			case 48460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001624);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001644, EnemyEtis, "EnemyEtis-2131");
				break;
			}
			case 48490: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001625);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001645, EnemyEtis, "EnemyEtis-2132");
				break;
			}
			case 48500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002156);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002162, EnemyDrastea, "EnemyDrastea-2133");
				break;
			}
			case 48520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001626);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001646, EnemyEtis, "EnemyEtis-2134");
				break;
			}
			case 48550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001627);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001647, EnemyEtis, "EnemyEtis-2135");
				break;
			}
			case 48580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001628);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001648, EnemyEtis, "EnemyEtis-2136");
				break;
			}
			case 48600: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002157);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002163, EnemyDrastea, "EnemyDrastea-2137");
				break;
			}
			case 48610: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001629);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001649, EnemyEtis, "EnemyEtis-2138");
				break;
			}
			case 48640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001630);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001650, EnemyEtis, "EnemyEtis-2139");
				break;
			}
			case 48670: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001631);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001651, EnemyEtis, "EnemyEtis-2140");
				break;
			}
			case 48700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001632);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001652, EnemyEtis, "EnemyEtis-2141");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002158);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002164, EnemyDrastea, "EnemyDrastea-2142");
				break;
			}
			case 48730: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001633);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001653, EnemyEtis, "EnemyEtis-2143");
				break;
			}
			case 48760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001634);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001654, EnemyEtis, "EnemyEtis-2144");
				break;
			}
			case 48790: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001635);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001655, EnemyEtis, "EnemyEtis-2145");
				break;
			}
			case 48800: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002159);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002165, EnemyDrastea, "EnemyDrastea-2146");
				break;
			}
			case 48820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001636);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001656, EnemyEtis, "EnemyEtis-2147");
				break;
			}
			case 48850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001637);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001657, EnemyEtis, "EnemyEtis-2148");
				break;
			}
			case 48880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001638);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001658, EnemyEtis, "EnemyEtis-2149");
				break;
			}
			case 48900: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002160);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002166, EnemyDrastea, "EnemyDrastea-2150");
				break;
			}
			case 48910: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001639);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001659, EnemyEtis, "EnemyEtis-2151");
				break;
			}
			case 48940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001640);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001660, EnemyEtis, "EnemyEtis-2152");
				break;
			}
			case 48970: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001641);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001661, EnemyEtis, "EnemyEtis-2153");
				break;
			}
			case 49000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001642);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001662, EnemyEtis, "EnemyEtis-2154");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002161);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002167, EnemyDrastea, "EnemyDrastea-2155");
				break;
			}
			case 49030: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001643);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001663, EnemyEtis, "EnemyEtis-2156");
				break;
			}
			case 49060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001644);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001664, EnemyEtis, "EnemyEtis-2157");
				break;
			}
			case 49090: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001645);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001665, EnemyEtis, "EnemyEtis-2158");
				break;
			}
			case 49100: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002162);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002168, EnemyDrastea, "EnemyDrastea-2159");
				break;
			}
			case 49120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001646);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001666, EnemyEtis, "EnemyEtis-2160");
				break;
			}
			case 49150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001647);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001667, EnemyEtis, "EnemyEtis-2161");
				break;
			}
			case 49180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001648);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001668, EnemyEtis, "EnemyEtis-2162");
				break;
			}
			case 49200: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002163);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002169, EnemyDrastea, "EnemyDrastea-2163");
				break;
			}
			case 49210: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001649);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001669, EnemyEtis, "EnemyEtis-2164");
				break;
			}
			case 49240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001650);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001670, EnemyEtis, "EnemyEtis-2165");
				break;
			}
			case 49270: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001651);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001671, EnemyEtis, "EnemyEtis-2166");
				break;
			}
			case 49300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001652);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001672, EnemyEtis, "EnemyEtis-2167");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002164);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002170, EnemyDrastea, "EnemyDrastea-2168");
				break;
			}
			case 49330: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001653);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001673, EnemyEtis, "EnemyEtis-2169");
				break;
			}
			case 49360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001654);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001674, EnemyEtis, "EnemyEtis-2170");
				break;
			}
			case 49390: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001655);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001675, EnemyEtis, "EnemyEtis-2171");
				break;
			}
			case 49400: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002165);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10002171, EnemyDrastea, "EnemyDrastea-2172");
				break;
			}
			case 49420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001656);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 49450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001657);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 49480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001658);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 49500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002166);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 49510: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001659);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 49540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001660);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 49570: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001661);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 49600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001662);
				bringDirector()->addSubGroup(pEtis);
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002167);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 49630: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001663);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 49660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001664);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 49690: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001665);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 49700: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002168);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 49720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001666);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 49750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001667);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 49780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001668);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 49800: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002169);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 49810: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001669);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 49840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001670);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 49870: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001671);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 49900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001672);
				bringDirector()->addSubGroup(pEtis);
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002170);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 49930: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001673);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 49960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001674);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 49990: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001675);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 50000: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10002171);
				bringDirector()->addSubGroup(p);
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 2003-1 ? _cnt_event+1 : _cnt_event);
	}
    // gen02 end

    SceneProgress* pProg = getProgress();
    switch (pProg->get()) {
        case PROG_FAINAL: {
            if (pProg->hasJustChanged()) {
                //STG01Climax_終焉の処理
                _TRACE_("STG01Climax_終焉のStage01PartController::PROG_FAINALきた");
            }

            if (pProg->hasArrivedAt(60)) {
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
    SceneProgress* pProg = getProgress();
    if (prm_no == EVENT_STG01_01_WAS_BROKEN) {
        _TRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_01_WAS_BROKEN");
        ((DefaultScene*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STG01_02_WAS_BROKEN) {
        _TRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_02_WAS_BROKEN");
        ((DefaultScene*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STG01_03_WAS_BROKEN) {
        _TRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_03_WAS_BROKEN");
        ((DefaultScene*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STG01_WALLED_WAS_BROKEN) {
        _TRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_WALLED_WAS_BROKEN");
        ((DefaultScene*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STG01_CLIMAX_WAS_BROKEN) {
        _TRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_CLIMAX_WAS_BROKENキャッチした。STAGE01PARTCONTROLLER_ENDINGを投げる");
        ((DefaultScene*)prm_pSource)->sayonara(60*60);
        pProg->change(PROG_FAINAL); //進捗をStage01PartController::PROG_FAINALに切り替える
    } else {

    }

}

Stage01PartController::~Stage01PartController() {

}
