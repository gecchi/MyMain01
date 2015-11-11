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
	frame f[] = {1,50,100,150,200,250,300,350,400,450,500,550,600,650,700,750,800,850,900,950,1000,1050,1100,1150,1200,1250,1300,1350,1400,1450,1500,1550,1600,1650,1700,1750,1800,1850,1900,1950,2000,2050,2100,2150,2200,2250,2300,2350,2400,2450,2500,2550,2600,2650,2700,2750,2800,2850,2900,2950,3000,3050,3100,3150,3200,3250,3300,3350,3400,3450,3500,3550,3600,3650,3700,3750,3800,3850,3900,3950,4000,4050,4100,4150,4200,4250,4300,4350,4400,4450,4500,4550,4600,4650,4700,4750,4800,4850,4900,4950,5000,5050,5100,5150,5200,5250,5300,5350,5400,5450,5500,5550,5600,5650,5700,5750,5800,5850,5900,5950,6000,6050,6100,6150,6200,6250,6300,6350,6400,6450,6500,6550,6600,6650,6700,6750,6800,6850,6900,6950,7000,7050,7100,7150,7200,7250,7300,7350,7400,7450,7500,7550,7600,7650,7700,7750,7800,7850,7900,7950,8000,8050,8100,8150,8200,8250,8300,8350,8400,8450,8500,8550,8600,8650,8700,8750,8800,8850,8900,8950,9000,9050,9100,9150,9200,9250,9300,9350,9400,9450,9500,9550,9600,9650,9700,9750,9800,9850,9900,9950,10000,10050,10100,10150,10200,10250,10300,10350,10400,10450,10500,10550,10600,10650,10700,10750,10800,10850,10900,10950,11000,11050,11100,11150,11200,11250,11300,11350,11400,11450,11500,11550,11600,11650,11700,11750,11800,11850,11900,11950,12000,12050,12100,12150,12200,12250,12300,12350,12400,12450,12500,12550,12600,12650,12700,12750,12800,12850,12900,12950,13000,13050,13100,13150,13200,13250,13300,13350,13400,13450,13500,13550,13600,13650,13700,13750,13800,13850,13900,13950,14000,14050,14100,14150,14200,14250,14300,14350,14400,14450,14500,14550,14600,14650,14700,14750,14800,14850,14900,14950,15000,15050,15100,15150,15200,15250,15300,15350,15400,15450,15500,15550,15600,15650,15700,15750,15800,15850,15900,15950,16000,16050,16100,16150,16200,16250,16300,16350,16400,16450,16500,16550,16600,16650,16700,16750,16800,16850,16900,16950,17000,17050,17100,17150,17200,17250,17300,17350,17400,17450,17500,17550,17600,17650,17700,17750,17800,17850,17900,17950,18000,18050,18100,18150,18200,18250,18300,18350,18400,18450,18500,18550,18600,18650,18700,18750,18800,18850,18900,18950,19000,19050,19100,19150,19200,19250,19300,19350,19400,19450,19500,19550,19600,19650,19700,19750,19800,19850,19900,19950,20000,20050,20100,20150,20200,20250,20300,20350,20400,20450,20500,20550,20600,20650,20700,20750,20800,20850,20900,20950,21000,21050,21100,21150,21200,21250,21300,21350,21400,21450,21500,21550,21600,21650,21700,21750,21800,21850,21900,21950,22000,22050,22100,22150,22200,22250,22300,22350,22400,22450,22500,22550,22600,22650,22700,22750,22800,22850,22900,22950,23000,23050,23100,23150,23200,23250,23300,23350,23400,23450,23500,23550,23600,23650,23700,23750,23800,23850,23900,23950,24000,24050,24100,24150,24200,24250,24300,24350,24400,24450,24500,24550,24600,24650,24700,24750,24800,24850,24900,24950,25000,25050,25100,25150,25200,25250,25300,25350,25400,25450,25500,25550,25600,25650,25700,25750,25800,25850,25900,25950,26000,26050,26100,26150,26200,26250,26300,26350,26400,26450,26500,26550,26600,26650,26700,26750,26800,26850,26900,26950,27000,27050,27100,27150,27200,27250,27300,27350,27400,27450,27500,27550,27600,27650,27700,27750,27800,27850,27900,27950,28000,28050,28100,28150,28200,28250,28300,28350,28400,28450,28500,28550,28600,28650,28700,28750,28800,28850,28900,28950,29000,29050,29100,29150,29200,29250,29300,29350,29400,29450,29500,29550,29600,29650,29700,29750,29800,29850,29900,29950,30000,30050,30100,30150,30200,30250,30300,30350,30400,30450,30500,30550,30600,30650,30700,30750,30800,30850,30900,30950,31000,31050,31100,31150,31200,31250,31300,31350,31400,31450,31500,31550,31600,31650,31700,31750,31800,31850,31900,31950,32000,32050,32100,32150,32200,32250,32300,32350,32400,32450,32500,32550,32600,32650,32700,32750,32800,32850,32900,32950,33000,33050,33100,33150,33200,33250,33300,33350,33400,33450,33500,33550,33600,33650,33700,33750,33800,33850,33900,33950,34000,34050,34100,34150,34200,34250,34300,34350,34400,34450,34500,34550,34600,34650,34700,34750,34800,34850,34900,34950,35000,35050,35100,35150,35200,35250,35300,35350,35400,35450,35500,35550,35600,35650,35700,35750,35800,35850,35900,35950,36000,36050,36100,36150,36200,36250,36300,36350,36400,36450,36500,36550,36600,36650,36700,36750,36800,36850,36900,36950,37000,37050,37100,37150,37200,37250,37300,37350,37400,37450,37500,37550,37600,37650,37700,37750,37800,37850,37900,37950,38000,38050,38100,38150,38200,38250,38300,38350,38400,38450,38500,38550,38600,38650,38700,38750,38800,38850,38900,38950,39000,39050,39100,39150,39200,39250,39300,39350,39400,39450,39500,39550,39600,39650,39700,39750,39800,39850,39900,39950,40000,40050,40100,40150,40200,40250,40300,40350,40400,40450,40500,40550,40600,40650,40700,40750,40800,40850,40900,40950,41000,41050,41100,41150,41200,41250,41300,41350,41400,41450,41500,41550,41600,41650,41700,41750,41800,41850,41900,41950,42000,42050,42100,42150,42200,42250,42300,42350,42400,42450,42500,42550,42600,42650,42700,42750,42800,42850,42900,42950,43000,43050,43100,43150,43200,43250,43300,43350,43400,43450,43500,43550,43600,43650,43700,43750,43800,43850,43900,43950,44000,44050,44100,44150,44200,44250,44300,44350,44400,44450,44500,44550,44600,44650,44700,44750,44800,44850,44900,44950,45000,45050,45100,45150,45200,45250,45300,45350,45400,45450,45500,45550,45600,45650,45700,45750,45800,45850,45900,45950,46000,46050,46100,46150,46200,46250,46300,46350,46400,46450,46500,46550,46600,46650,46700,46750,46800,46850,46900,46950,47000,47050,47100,47150,47200,47250,47300,47350,47400,47450,47500,47550,47600,47650,47700,47750,47800,47850,47900,47950,48000,48050,48100,48150,48200,48250,48300,48350,48400,48450,48500,48550,48600,48650,48700,48750,48800,48850,48900,48950,49000,49050,49100,49150,49200,49250,49300,49350,49400,49450,49500,49550,49600,49650,49700,49750,49800,49850,49900,49950,50000,50050,50100,50150,50200,50250,50300,50350,50400,50450,50500,50550,50600,50650,50700,50750,50800,50850,50900,50950,51000,51050,51100,51150,51200,51250,51300,51350,51400,51450,51500,51550,51600,51650,51700,51750,51800,51850,51900,51950,52000,52050,52100,52150,52200,52250,52300,52350,52400,52450,52500,52550,52600,52650,52700,52750,52800,52850,52900,52950,53000,53050,53100,53150,53200,53250,53300,53350,53400,53450,53500,53550,53600,53650,53700,53750,53800,53850,53900,53950,54000,54050,54100,54150,54200,54250,54300,54350,54400,54450,54500,54550,54600,54650,54700,54750,54800,54850,54900,54950,55000,55050,55100,55150,55200,55250,55300,55350,55400,55450,55500,55550,55600,55650,55700,55750,55800,55850,55900,55950,56000,56050,56100,56150,56200,56250,56300,56350,56400,56450,56500,56550,56600,56650,56700,56750,56800,56850,56900,56950,57000,57050,57100,57150,57200,57250,57300,57350,57400,57450,57500,57550,57600,57650,57700,57750,57800,57850,57900,57950,58000,58050,58100,58150,58200,58250,58300,58350,58400,58450,58500,58550,58600,58650,58700,58750,58800,58850,58900,58950,59000,59050,59100,59150,59200,59250,59300,59350,59400,59450,59500,59550,59600,59650,59700,59750,59800,59850,59900,59950,60000};
	_paFrame_NextEvent = new frame[1201];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 1201;
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
	orderActorToFactory(10001199, EnemyDrastea, "EnemyDrastea-12");
	orderActorToFactory(10001200, EnemyDrastea, "EnemyDrastea-13");
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
			case 50: {
				orderActorToFactory(10000011, EnemyEtis, "EnemyEtis-14");
				break;
			}
			case 100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000000);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000012, EnemyEtis, "EnemyEtis-15");
				orderActorToFactory(10001201, EnemyDrastea, "EnemyDrastea-16");
				break;
			}
			case 150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000001);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000013, EnemyEtis, "EnemyEtis-17");
				break;
			}
			case 200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000002);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000014, EnemyEtis, "EnemyEtis-18");
				orderActorToFactory(10001202, EnemyDrastea, "EnemyDrastea-19");
				break;
			}
			case 250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000003);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000015, EnemyEtis, "EnemyEtis-20");
				break;
			}
			case 300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000004);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000016, EnemyEtis, "EnemyEtis-21");
				orderActorToFactory(10001203, EnemyDrastea, "EnemyDrastea-22");
				break;
			}
			case 350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000005);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000017, EnemyEtis, "EnemyEtis-23");
				break;
			}
			case 400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000006);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000018, EnemyEtis, "EnemyEtis-24");
				orderActorToFactory(10001204, EnemyDrastea, "EnemyDrastea-25");
				break;
			}
			case 450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000007);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000019, EnemyEtis, "EnemyEtis-26");
				break;
			}
			case 500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000008);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000020, EnemyEtis, "EnemyEtis-27");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001199);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001205, EnemyDrastea, "EnemyDrastea-28");
				break;
			}
			case 550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000009);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000021, EnemyEtis, "EnemyEtis-29");
				break;
			}
			case 600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000010);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000022, EnemyEtis, "EnemyEtis-30");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001200);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001206, EnemyDrastea, "EnemyDrastea-31");
				break;
			}
			case 650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000011);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000023, EnemyEtis, "EnemyEtis-32");
				break;
			}
			case 700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000012);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000024, EnemyEtis, "EnemyEtis-33");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001201);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001207, EnemyDrastea, "EnemyDrastea-34");
				break;
			}
			case 750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000013);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000025, EnemyEtis, "EnemyEtis-35");
				break;
			}
			case 800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000014);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000026, EnemyEtis, "EnemyEtis-36");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001202);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001208, EnemyDrastea, "EnemyDrastea-37");
				break;
			}
			case 850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000015);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000027, EnemyEtis, "EnemyEtis-38");
				break;
			}
			case 900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000016);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000028, EnemyEtis, "EnemyEtis-39");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001203);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001209, EnemyDrastea, "EnemyDrastea-40");
				break;
			}
			case 950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000017);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000029, EnemyEtis, "EnemyEtis-41");
				break;
			}
			case 1000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000018);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000030, EnemyEtis, "EnemyEtis-42");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001204);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001210, EnemyDrastea, "EnemyDrastea-43");
				break;
			}
			case 1050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000019);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000031, EnemyEtis, "EnemyEtis-44");
				break;
			}
			case 1100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000020);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000032, EnemyEtis, "EnemyEtis-45");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001205);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001211, EnemyDrastea, "EnemyDrastea-46");
				break;
			}
			case 1150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000021);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000033, EnemyEtis, "EnemyEtis-47");
				break;
			}
			case 1200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000022);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000034, EnemyEtis, "EnemyEtis-48");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001206);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001212, EnemyDrastea, "EnemyDrastea-49");
				break;
			}
			case 1250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000023);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000035, EnemyEtis, "EnemyEtis-50");
				break;
			}
			case 1300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000024);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000036, EnemyEtis, "EnemyEtis-51");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001207);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001213, EnemyDrastea, "EnemyDrastea-52");
				break;
			}
			case 1350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000025);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000037, EnemyEtis, "EnemyEtis-53");
				break;
			}
			case 1400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000026);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000038, EnemyEtis, "EnemyEtis-54");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001208);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001214, EnemyDrastea, "EnemyDrastea-55");
				break;
			}
			case 1450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000027);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000039, EnemyEtis, "EnemyEtis-56");
				break;
			}
			case 1500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000028);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000040, EnemyEtis, "EnemyEtis-57");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001209);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001215, EnemyDrastea, "EnemyDrastea-58");
				break;
			}
			case 1550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000029);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000041, EnemyEtis, "EnemyEtis-59");
				break;
			}
			case 1600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000030);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000042, EnemyEtis, "EnemyEtis-60");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001210);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001216, EnemyDrastea, "EnemyDrastea-61");
				break;
			}
			case 1650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000031);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000043, EnemyEtis, "EnemyEtis-62");
				break;
			}
			case 1700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000032);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000044, EnemyEtis, "EnemyEtis-63");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001211);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001217, EnemyDrastea, "EnemyDrastea-64");
				break;
			}
			case 1750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000033);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000045, EnemyEtis, "EnemyEtis-65");
				break;
			}
			case 1800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000034);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000046, EnemyEtis, "EnemyEtis-66");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001212);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001218, EnemyDrastea, "EnemyDrastea-67");
				break;
			}
			case 1850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000035);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000047, EnemyEtis, "EnemyEtis-68");
				break;
			}
			case 1900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000036);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000048, EnemyEtis, "EnemyEtis-69");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001213);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001219, EnemyDrastea, "EnemyDrastea-70");
				break;
			}
			case 1950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000037);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000049, EnemyEtis, "EnemyEtis-71");
				break;
			}
			case 2000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000038);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000050, EnemyEtis, "EnemyEtis-72");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001214);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001220, EnemyDrastea, "EnemyDrastea-73");
				break;
			}
			case 2050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000039);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000051, EnemyEtis, "EnemyEtis-74");
				break;
			}
			case 2100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000040);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000052, EnemyEtis, "EnemyEtis-75");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001215);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001221, EnemyDrastea, "EnemyDrastea-76");
				break;
			}
			case 2150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000041);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000053, EnemyEtis, "EnemyEtis-77");
				break;
			}
			case 2200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000042);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000054, EnemyEtis, "EnemyEtis-78");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001216);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001222, EnemyDrastea, "EnemyDrastea-79");
				break;
			}
			case 2250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000043);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000055, EnemyEtis, "EnemyEtis-80");
				break;
			}
			case 2300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000044);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000056, EnemyEtis, "EnemyEtis-81");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001217);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001223, EnemyDrastea, "EnemyDrastea-82");
				break;
			}
			case 2350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000045);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000057, EnemyEtis, "EnemyEtis-83");
				break;
			}
			case 2400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000046);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000058, EnemyEtis, "EnemyEtis-84");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001218);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001224, EnemyDrastea, "EnemyDrastea-85");
				orderActorToFactory(10001795, FormationDelheid001, "FormationDelheid001-86");
				break;
			}
			case 2450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000047);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000059, EnemyEtis, "EnemyEtis-87");
				break;
			}
			case 2500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000048);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000060, EnemyEtis, "EnemyEtis-88");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001219);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001225, EnemyDrastea, "EnemyDrastea-89");
				orderActorToFactory(10001796, FormationDelheid001, "FormationDelheid001-90");
				break;
			}
			case 2550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000049);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000061, EnemyEtis, "EnemyEtis-91");
				break;
			}
			case 2600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000050);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000062, EnemyEtis, "EnemyEtis-92");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001220);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001226, EnemyDrastea, "EnemyDrastea-93");
				orderActorToFactory(10001797, FormationDelheid001, "FormationDelheid001-94");
				break;
			}
			case 2650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000051);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000063, EnemyEtis, "EnemyEtis-95");
				break;
			}
			case 2700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000052);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000064, EnemyEtis, "EnemyEtis-96");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001221);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001227, EnemyDrastea, "EnemyDrastea-97");
				orderActorToFactory(10001798, FormationDelheid001, "FormationDelheid001-98");
				break;
			}
			case 2750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000053);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000065, EnemyEtis, "EnemyEtis-99");
				break;
			}
			case 2800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000054);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000066, EnemyEtis, "EnemyEtis-100");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001222);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001228, EnemyDrastea, "EnemyDrastea-101");
				orderActorToFactory(10001799, FormationDelheid001, "FormationDelheid001-102");
				break;
			}
			case 2850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000055);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000067, EnemyEtis, "EnemyEtis-103");
				break;
			}
			case 2900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000056);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000068, EnemyEtis, "EnemyEtis-104");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001223);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001229, EnemyDrastea, "EnemyDrastea-105");
				orderActorToFactory(10001800, FormationDelheid001, "FormationDelheid001-106");
				break;
			}
			case 2950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000057);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000069, EnemyEtis, "EnemyEtis-107");
				break;
			}
			case 3000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000058);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000070, EnemyEtis, "EnemyEtis-108");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001224);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001230, EnemyDrastea, "EnemyDrastea-109");
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10001795);
				bringDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C(-400), PX_C(500), D_ANG(0), D_ANG(-40), D_ANG(0));
				orderActorToFactory(10001801, FormationDelheid001, "FormationDelheid001-110");
				break;
			}
			case 3050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000059);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000071, EnemyEtis, "EnemyEtis-111");
				break;
			}
			case 3100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000060);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000072, EnemyEtis, "EnemyEtis-112");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001225);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001231, EnemyDrastea, "EnemyDrastea-113");
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10001796);
				bringDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C(-300), PX_C(500), D_ANG(0), D_ANG(-30), D_ANG(0));
				orderActorToFactory(10001802, FormationDelheid001, "FormationDelheid001-114");
				break;
			}
			case 3150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000061);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000073, EnemyEtis, "EnemyEtis-115");
				break;
			}
			case 3200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000062);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000074, EnemyEtis, "EnemyEtis-116");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001226);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001232, EnemyDrastea, "EnemyDrastea-117");
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10001797);
				bringDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C(-200), PX_C(500), D_ANG(0), D_ANG(-20), D_ANG(0));
				orderActorToFactory(10001803, FormationDelheid001, "FormationDelheid001-118");
				break;
			}
			case 3250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000063);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000075, EnemyEtis, "EnemyEtis-119");
				break;
			}
			case 3300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000064);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000076, EnemyEtis, "EnemyEtis-120");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001227);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001233, EnemyDrastea, "EnemyDrastea-121");
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10001798);
				bringDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C(-100), PX_C(500), D_ANG(0), D_ANG(-10), D_ANG(0));
				break;
			}
			case 3350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000065);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000077, EnemyEtis, "EnemyEtis-122");
				break;
			}
			case 3400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000066);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000078, EnemyEtis, "EnemyEtis-123");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001228);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001234, EnemyDrastea, "EnemyDrastea-124");
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10001799);
				bringDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C(   0), PX_C(500), D_ANG(0), D_ANG(  0), D_ANG(0));
				break;
			}
			case 3450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000067);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000079, EnemyEtis, "EnemyEtis-125");
				break;
			}
			case 3500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000068);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000080, EnemyEtis, "EnemyEtis-126");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001229);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001235, EnemyDrastea, "EnemyDrastea-127");
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10001800);
				bringDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C( 100), PX_C(500), D_ANG(0), D_ANG( 10), D_ANG(0));
				break;
			}
			case 3550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000069);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000081, EnemyEtis, "EnemyEtis-128");
				break;
			}
			case 3600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000070);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000082, EnemyEtis, "EnemyEtis-129");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001230);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001236, EnemyDrastea, "EnemyDrastea-130");
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10001801);
				bringDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C( 200), PX_C(500), D_ANG(0), D_ANG( 20), D_ANG(0));
				break;
			}
			case 3650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000071);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000083, EnemyEtis, "EnemyEtis-131");
				break;
			}
			case 3700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000072);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000084, EnemyEtis, "EnemyEtis-132");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001231);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001237, EnemyDrastea, "EnemyDrastea-133");
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10001802);
				bringDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C( 300), PX_C(500), D_ANG(0), D_ANG( 30), D_ANG(0));
				break;
			}
			case 3750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000073);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000085, EnemyEtis, "EnemyEtis-134");
				break;
			}
			case 3800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000074);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000086, EnemyEtis, "EnemyEtis-135");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001232);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001238, EnemyDrastea, "EnemyDrastea-136");
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10001803);
				bringDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C( 400), PX_C(500), D_ANG(0), D_ANG( 40), D_ANG(0));
				break;
			}
			case 3850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000075);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000087, EnemyEtis, "EnemyEtis-137");
				break;
			}
			case 3900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000076);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000088, EnemyEtis, "EnemyEtis-138");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001233);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001239, EnemyDrastea, "EnemyDrastea-139");
				break;
			}
			case 3950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000077);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000089, EnemyEtis, "EnemyEtis-140");
				break;
			}
			case 4000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000078);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000090, EnemyEtis, "EnemyEtis-141");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001234);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001240, EnemyDrastea, "EnemyDrastea-142");
				break;
			}
			case 4050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000079);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000091, EnemyEtis, "EnemyEtis-143");
				break;
			}
			case 4100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000080);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000092, EnemyEtis, "EnemyEtis-144");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001235);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001241, EnemyDrastea, "EnemyDrastea-145");
				break;
			}
			case 4150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000081);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000093, EnemyEtis, "EnemyEtis-146");
				break;
			}
			case 4200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000082);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000094, EnemyEtis, "EnemyEtis-147");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001236);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001242, EnemyDrastea, "EnemyDrastea-148");
				break;
			}
			case 4250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000083);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000095, EnemyEtis, "EnemyEtis-149");
				break;
			}
			case 4300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000084);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000096, EnemyEtis, "EnemyEtis-150");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001237);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001243, EnemyDrastea, "EnemyDrastea-151");
				break;
			}
			case 4350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000085);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000097, EnemyEtis, "EnemyEtis-152");
				break;
			}
			case 4400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000086);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000098, EnemyEtis, "EnemyEtis-153");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001238);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001244, EnemyDrastea, "EnemyDrastea-154");
				break;
			}
			case 4450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000087);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000099, EnemyEtis, "EnemyEtis-155");
				break;
			}
			case 4500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000088);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000100, EnemyEtis, "EnemyEtis-156");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001239);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001245, EnemyDrastea, "EnemyDrastea-157");
				break;
			}
			case 4550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000089);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000101, EnemyEtis, "EnemyEtis-158");
				break;
			}
			case 4600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000090);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000102, EnemyEtis, "EnemyEtis-159");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001240);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001246, EnemyDrastea, "EnemyDrastea-160");
				break;
			}
			case 4650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000091);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000103, EnemyEtis, "EnemyEtis-161");
				break;
			}
			case 4700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000092);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000104, EnemyEtis, "EnemyEtis-162");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001241);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001247, EnemyDrastea, "EnemyDrastea-163");
				break;
			}
			case 4750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000093);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000105, EnemyEtis, "EnemyEtis-164");
				break;
			}
			case 4800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000094);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000106, EnemyEtis, "EnemyEtis-165");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001242);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001248, EnemyDrastea, "EnemyDrastea-166");
				break;
			}
			case 4850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000095);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000107, EnemyEtis, "EnemyEtis-167");
				break;
			}
			case 4900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000096);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000108, EnemyEtis, "EnemyEtis-168");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001243);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001249, EnemyDrastea, "EnemyDrastea-169");
				break;
			}
			case 4950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000097);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000109, EnemyEtis, "EnemyEtis-170");
				break;
			}
			case 5000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000098);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000110, EnemyEtis, "EnemyEtis-171");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001244);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001250, EnemyDrastea, "EnemyDrastea-172");
				break;
			}
			case 5050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000099);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000111, EnemyEtis, "EnemyEtis-173");
				break;
			}
			case 5100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000100);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000112, EnemyEtis, "EnemyEtis-174");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001245);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001251, EnemyDrastea, "EnemyDrastea-175");
				break;
			}
			case 5150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000101);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000113, EnemyEtis, "EnemyEtis-176");
				break;
			}
			case 5200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000102);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000114, EnemyEtis, "EnemyEtis-177");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001246);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001252, EnemyDrastea, "EnemyDrastea-178");
				break;
			}
			case 5250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000103);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000115, EnemyEtis, "EnemyEtis-179");
				break;
			}
			case 5300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000104);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000116, EnemyEtis, "EnemyEtis-180");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001247);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001253, EnemyDrastea, "EnemyDrastea-181");
				break;
			}
			case 5350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000105);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000117, EnemyEtis, "EnemyEtis-182");
				break;
			}
			case 5400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000106);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000118, EnemyEtis, "EnemyEtis-183");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001248);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001254, EnemyDrastea, "EnemyDrastea-184");
				break;
			}
			case 5450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000107);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000119, EnemyEtis, "EnemyEtis-185");
				break;
			}
			case 5500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000108);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000120, EnemyEtis, "EnemyEtis-186");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001249);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001255, EnemyDrastea, "EnemyDrastea-187");
				break;
			}
			case 5550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000109);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000121, EnemyEtis, "EnemyEtis-188");
				break;
			}
			case 5600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000110);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000122, EnemyEtis, "EnemyEtis-189");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001250);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001256, EnemyDrastea, "EnemyDrastea-190");
				break;
			}
			case 5650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000111);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000123, EnemyEtis, "EnemyEtis-191");
				break;
			}
			case 5700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000112);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000124, EnemyEtis, "EnemyEtis-192");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001251);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001257, EnemyDrastea, "EnemyDrastea-193");
				break;
			}
			case 5750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000113);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000125, EnemyEtis, "EnemyEtis-194");
				break;
			}
			case 5800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000114);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000126, EnemyEtis, "EnemyEtis-195");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001252);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001258, EnemyDrastea, "EnemyDrastea-196");
				break;
			}
			case 5850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000115);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000127, EnemyEtis, "EnemyEtis-197");
				break;
			}
			case 5900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000116);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000128, EnemyEtis, "EnemyEtis-198");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001253);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001259, EnemyDrastea, "EnemyDrastea-199");
				break;
			}
			case 5950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000117);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000129, EnemyEtis, "EnemyEtis-200");
				break;
			}
			case 6000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000118);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000130, EnemyEtis, "EnemyEtis-201");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001254);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001260, EnemyDrastea, "EnemyDrastea-202");
				break;
			}
			case 6050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000119);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000131, EnemyEtis, "EnemyEtis-203");
				break;
			}
			case 6100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000120);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000132, EnemyEtis, "EnemyEtis-204");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001255);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001261, EnemyDrastea, "EnemyDrastea-205");
				break;
			}
			case 6150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000121);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000133, EnemyEtis, "EnemyEtis-206");
				break;
			}
			case 6200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000122);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000134, EnemyEtis, "EnemyEtis-207");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001256);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001262, EnemyDrastea, "EnemyDrastea-208");
				break;
			}
			case 6250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000123);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000135, EnemyEtis, "EnemyEtis-209");
				break;
			}
			case 6300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000124);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000136, EnemyEtis, "EnemyEtis-210");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001257);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001263, EnemyDrastea, "EnemyDrastea-211");
				break;
			}
			case 6350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000125);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000137, EnemyEtis, "EnemyEtis-212");
				break;
			}
			case 6400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000126);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000138, EnemyEtis, "EnemyEtis-213");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001258);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001264, EnemyDrastea, "EnemyDrastea-214");
				break;
			}
			case 6450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000127);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000139, EnemyEtis, "EnemyEtis-215");
				break;
			}
			case 6500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000128);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000140, EnemyEtis, "EnemyEtis-216");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001259);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001265, EnemyDrastea, "EnemyDrastea-217");
				break;
			}
			case 6550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000129);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000141, EnemyEtis, "EnemyEtis-218");
				break;
			}
			case 6600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000130);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000142, EnemyEtis, "EnemyEtis-219");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001260);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001266, EnemyDrastea, "EnemyDrastea-220");
				break;
			}
			case 6650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000131);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000143, EnemyEtis, "EnemyEtis-221");
				break;
			}
			case 6700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000132);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000144, EnemyEtis, "EnemyEtis-222");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001261);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001267, EnemyDrastea, "EnemyDrastea-223");
				break;
			}
			case 6750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000133);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000145, EnemyEtis, "EnemyEtis-224");
				break;
			}
			case 6800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000134);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000146, EnemyEtis, "EnemyEtis-225");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001262);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001268, EnemyDrastea, "EnemyDrastea-226");
				break;
			}
			case 6850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000135);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000147, EnemyEtis, "EnemyEtis-227");
				break;
			}
			case 6900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000136);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000148, EnemyEtis, "EnemyEtis-228");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001263);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001269, EnemyDrastea, "EnemyDrastea-229");
				break;
			}
			case 6950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000137);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000149, EnemyEtis, "EnemyEtis-230");
				break;
			}
			case 7000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000138);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000150, EnemyEtis, "EnemyEtis-231");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001264);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001270, EnemyDrastea, "EnemyDrastea-232");
				break;
			}
			case 7050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000139);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000151, EnemyEtis, "EnemyEtis-233");
				break;
			}
			case 7100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000140);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000152, EnemyEtis, "EnemyEtis-234");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001265);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001271, EnemyDrastea, "EnemyDrastea-235");
				break;
			}
			case 7150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000141);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000153, EnemyEtis, "EnemyEtis-236");
				break;
			}
			case 7200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000142);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000154, EnemyEtis, "EnemyEtis-237");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001266);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001272, EnemyDrastea, "EnemyDrastea-238");
				break;
			}
			case 7250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000143);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000155, EnemyEtis, "EnemyEtis-239");
				break;
			}
			case 7300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000144);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000156, EnemyEtis, "EnemyEtis-240");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001267);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001273, EnemyDrastea, "EnemyDrastea-241");
				break;
			}
			case 7350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000145);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000157, EnemyEtis, "EnemyEtis-242");
				break;
			}
			case 7400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000146);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000158, EnemyEtis, "EnemyEtis-243");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001268);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001274, EnemyDrastea, "EnemyDrastea-244");
				break;
			}
			case 7450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000147);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000159, EnemyEtis, "EnemyEtis-245");
				break;
			}
			case 7500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000148);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000160, EnemyEtis, "EnemyEtis-246");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001269);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001275, EnemyDrastea, "EnemyDrastea-247");
				break;
			}
			case 7550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000149);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000161, EnemyEtis, "EnemyEtis-248");
				break;
			}
			case 7600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000150);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000162, EnemyEtis, "EnemyEtis-249");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001270);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001276, EnemyDrastea, "EnemyDrastea-250");
				break;
			}
			case 7650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000151);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000163, EnemyEtis, "EnemyEtis-251");
				break;
			}
			case 7700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000152);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000164, EnemyEtis, "EnemyEtis-252");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001271);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001277, EnemyDrastea, "EnemyDrastea-253");
				break;
			}
			case 7750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000153);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000165, EnemyEtis, "EnemyEtis-254");
				break;
			}
			case 7800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000154);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000166, EnemyEtis, "EnemyEtis-255");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001272);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001278, EnemyDrastea, "EnemyDrastea-256");
				break;
			}
			case 7850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000155);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000167, EnemyEtis, "EnemyEtis-257");
				break;
			}
			case 7900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000156);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000168, EnemyEtis, "EnemyEtis-258");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001273);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001279, EnemyDrastea, "EnemyDrastea-259");
				break;
			}
			case 7950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000157);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000169, EnemyEtis, "EnemyEtis-260");
				break;
			}
			case 8000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000158);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000170, EnemyEtis, "EnemyEtis-261");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001274);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001280, EnemyDrastea, "EnemyDrastea-262");
				break;
			}
			case 8050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000159);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000171, EnemyEtis, "EnemyEtis-263");
				break;
			}
			case 8100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000160);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000172, EnemyEtis, "EnemyEtis-264");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001275);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001281, EnemyDrastea, "EnemyDrastea-265");
				break;
			}
			case 8150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000161);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000173, EnemyEtis, "EnemyEtis-266");
				break;
			}
			case 8200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000162);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000174, EnemyEtis, "EnemyEtis-267");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001276);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001282, EnemyDrastea, "EnemyDrastea-268");
				break;
			}
			case 8250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000163);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000175, EnemyEtis, "EnemyEtis-269");
				break;
			}
			case 8300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000164);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000176, EnemyEtis, "EnemyEtis-270");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001277);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001283, EnemyDrastea, "EnemyDrastea-271");
				break;
			}
			case 8350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000165);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000177, EnemyEtis, "EnemyEtis-272");
				break;
			}
			case 8400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000166);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000178, EnemyEtis, "EnemyEtis-273");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001278);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001284, EnemyDrastea, "EnemyDrastea-274");
				break;
			}
			case 8450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000167);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000179, EnemyEtis, "EnemyEtis-275");
				break;
			}
			case 8500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000168);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000180, EnemyEtis, "EnemyEtis-276");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001279);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001285, EnemyDrastea, "EnemyDrastea-277");
				break;
			}
			case 8550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000169);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000181, EnemyEtis, "EnemyEtis-278");
				break;
			}
			case 8600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000170);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000182, EnemyEtis, "EnemyEtis-279");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001280);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001286, EnemyDrastea, "EnemyDrastea-280");
				break;
			}
			case 8650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000171);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000183, EnemyEtis, "EnemyEtis-281");
				break;
			}
			case 8700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000172);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000184, EnemyEtis, "EnemyEtis-282");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001281);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001287, EnemyDrastea, "EnemyDrastea-283");
				break;
			}
			case 8750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000173);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000185, EnemyEtis, "EnemyEtis-284");
				break;
			}
			case 8800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000174);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000186, EnemyEtis, "EnemyEtis-285");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001282);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001288, EnemyDrastea, "EnemyDrastea-286");
				break;
			}
			case 8850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000175);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000187, EnemyEtis, "EnemyEtis-287");
				break;
			}
			case 8900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000176);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000188, EnemyEtis, "EnemyEtis-288");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001283);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001289, EnemyDrastea, "EnemyDrastea-289");
				break;
			}
			case 8950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000177);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000189, EnemyEtis, "EnemyEtis-290");
				break;
			}
			case 9000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000178);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000190, EnemyEtis, "EnemyEtis-291");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001284);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001290, EnemyDrastea, "EnemyDrastea-292");
				break;
			}
			case 9050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000179);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000191, EnemyEtis, "EnemyEtis-293");
				break;
			}
			case 9100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000180);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000192, EnemyEtis, "EnemyEtis-294");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001285);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001291, EnemyDrastea, "EnemyDrastea-295");
				break;
			}
			case 9150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000181);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000193, EnemyEtis, "EnemyEtis-296");
				break;
			}
			case 9200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000182);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000194, EnemyEtis, "EnemyEtis-297");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001286);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001292, EnemyDrastea, "EnemyDrastea-298");
				break;
			}
			case 9250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000183);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000195, EnemyEtis, "EnemyEtis-299");
				break;
			}
			case 9300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000184);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000196, EnemyEtis, "EnemyEtis-300");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001287);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001293, EnemyDrastea, "EnemyDrastea-301");
				break;
			}
			case 9350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000185);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000197, EnemyEtis, "EnemyEtis-302");
				break;
			}
			case 9400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000186);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000198, EnemyEtis, "EnemyEtis-303");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001288);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001294, EnemyDrastea, "EnemyDrastea-304");
				break;
			}
			case 9450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000187);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000199, EnemyEtis, "EnemyEtis-305");
				break;
			}
			case 9500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000188);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000200, EnemyEtis, "EnemyEtis-306");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001289);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001295, EnemyDrastea, "EnemyDrastea-307");
				break;
			}
			case 9550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000189);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000201, EnemyEtis, "EnemyEtis-308");
				break;
			}
			case 9600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000190);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000202, EnemyEtis, "EnemyEtis-309");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001290);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001296, EnemyDrastea, "EnemyDrastea-310");
				break;
			}
			case 9650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000191);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000203, EnemyEtis, "EnemyEtis-311");
				break;
			}
			case 9700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000192);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000204, EnemyEtis, "EnemyEtis-312");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001291);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001297, EnemyDrastea, "EnemyDrastea-313");
				break;
			}
			case 9750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000193);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000205, EnemyEtis, "EnemyEtis-314");
				break;
			}
			case 9800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000194);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000206, EnemyEtis, "EnemyEtis-315");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001292);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001298, EnemyDrastea, "EnemyDrastea-316");
				break;
			}
			case 9850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000195);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000207, EnemyEtis, "EnemyEtis-317");
				break;
			}
			case 9900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000196);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000208, EnemyEtis, "EnemyEtis-318");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001293);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001299, EnemyDrastea, "EnemyDrastea-319");
				break;
			}
			case 9950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000197);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000209, EnemyEtis, "EnemyEtis-320");
				break;
			}
			case 10000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000198);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000210, EnemyEtis, "EnemyEtis-321");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001294);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001300, EnemyDrastea, "EnemyDrastea-322");
				break;
			}
			case 10050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000199);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000211, EnemyEtis, "EnemyEtis-323");
				break;
			}
			case 10100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000200);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000212, EnemyEtis, "EnemyEtis-324");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001295);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001301, EnemyDrastea, "EnemyDrastea-325");
				break;
			}
			case 10150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000201);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000213, EnemyEtis, "EnemyEtis-326");
				break;
			}
			case 10200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000202);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000214, EnemyEtis, "EnemyEtis-327");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001296);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001302, EnemyDrastea, "EnemyDrastea-328");
				break;
			}
			case 10250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000203);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000215, EnemyEtis, "EnemyEtis-329");
				break;
			}
			case 10300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000204);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000216, EnemyEtis, "EnemyEtis-330");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001297);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001303, EnemyDrastea, "EnemyDrastea-331");
				break;
			}
			case 10350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000205);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000217, EnemyEtis, "EnemyEtis-332");
				break;
			}
			case 10400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000206);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000218, EnemyEtis, "EnemyEtis-333");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001298);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001304, EnemyDrastea, "EnemyDrastea-334");
				break;
			}
			case 10450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000207);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000219, EnemyEtis, "EnemyEtis-335");
				break;
			}
			case 10500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000208);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000220, EnemyEtis, "EnemyEtis-336");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001299);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001305, EnemyDrastea, "EnemyDrastea-337");
				break;
			}
			case 10550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000209);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000221, EnemyEtis, "EnemyEtis-338");
				break;
			}
			case 10600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000210);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000222, EnemyEtis, "EnemyEtis-339");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001300);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001306, EnemyDrastea, "EnemyDrastea-340");
				break;
			}
			case 10650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000211);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000223, EnemyEtis, "EnemyEtis-341");
				break;
			}
			case 10700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000212);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000224, EnemyEtis, "EnemyEtis-342");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001301);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001307, EnemyDrastea, "EnemyDrastea-343");
				break;
			}
			case 10750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000213);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000225, EnemyEtis, "EnemyEtis-344");
				break;
			}
			case 10800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000214);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000226, EnemyEtis, "EnemyEtis-345");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001302);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001308, EnemyDrastea, "EnemyDrastea-346");
				break;
			}
			case 10850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000215);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000227, EnemyEtis, "EnemyEtis-347");
				break;
			}
			case 10900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000216);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000228, EnemyEtis, "EnemyEtis-348");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001303);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001309, EnemyDrastea, "EnemyDrastea-349");
				break;
			}
			case 10950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000217);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000229, EnemyEtis, "EnemyEtis-350");
				break;
			}
			case 11000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000218);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000230, EnemyEtis, "EnemyEtis-351");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001304);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001310, EnemyDrastea, "EnemyDrastea-352");
				break;
			}
			case 11050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000219);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000231, EnemyEtis, "EnemyEtis-353");
				break;
			}
			case 11100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000220);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000232, EnemyEtis, "EnemyEtis-354");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001305);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001311, EnemyDrastea, "EnemyDrastea-355");
				break;
			}
			case 11150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000221);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000233, EnemyEtis, "EnemyEtis-356");
				break;
			}
			case 11200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000222);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000234, EnemyEtis, "EnemyEtis-357");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001306);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001312, EnemyDrastea, "EnemyDrastea-358");
				break;
			}
			case 11250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000223);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000235, EnemyEtis, "EnemyEtis-359");
				break;
			}
			case 11300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000224);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000236, EnemyEtis, "EnemyEtis-360");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001307);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001313, EnemyDrastea, "EnemyDrastea-361");
				break;
			}
			case 11350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000225);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000237, EnemyEtis, "EnemyEtis-362");
				break;
			}
			case 11400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000226);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000238, EnemyEtis, "EnemyEtis-363");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001308);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001314, EnemyDrastea, "EnemyDrastea-364");
				break;
			}
			case 11450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000227);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000239, EnemyEtis, "EnemyEtis-365");
				break;
			}
			case 11500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000228);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000240, EnemyEtis, "EnemyEtis-366");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001309);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001315, EnemyDrastea, "EnemyDrastea-367");
				break;
			}
			case 11550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000229);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000241, EnemyEtis, "EnemyEtis-368");
				break;
			}
			case 11600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000230);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000242, EnemyEtis, "EnemyEtis-369");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001310);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001316, EnemyDrastea, "EnemyDrastea-370");
				break;
			}
			case 11650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000231);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000243, EnemyEtis, "EnemyEtis-371");
				break;
			}
			case 11700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000232);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000244, EnemyEtis, "EnemyEtis-372");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001311);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001317, EnemyDrastea, "EnemyDrastea-373");
				break;
			}
			case 11750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000233);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000245, EnemyEtis, "EnemyEtis-374");
				break;
			}
			case 11800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000234);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000246, EnemyEtis, "EnemyEtis-375");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001312);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001318, EnemyDrastea, "EnemyDrastea-376");
				break;
			}
			case 11850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000235);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000247, EnemyEtis, "EnemyEtis-377");
				break;
			}
			case 11900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000236);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000248, EnemyEtis, "EnemyEtis-378");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001313);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001319, EnemyDrastea, "EnemyDrastea-379");
				break;
			}
			case 11950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000237);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000249, EnemyEtis, "EnemyEtis-380");
				break;
			}
			case 12000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000238);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000250, EnemyEtis, "EnemyEtis-381");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001314);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001320, EnemyDrastea, "EnemyDrastea-382");
				break;
			}
			case 12050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000239);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000251, EnemyEtis, "EnemyEtis-383");
				break;
			}
			case 12100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000240);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000252, EnemyEtis, "EnemyEtis-384");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001315);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001321, EnemyDrastea, "EnemyDrastea-385");
				break;
			}
			case 12150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000241);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000253, EnemyEtis, "EnemyEtis-386");
				break;
			}
			case 12200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000242);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000254, EnemyEtis, "EnemyEtis-387");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001316);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001322, EnemyDrastea, "EnemyDrastea-388");
				break;
			}
			case 12250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000243);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000255, EnemyEtis, "EnemyEtis-389");
				break;
			}
			case 12300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000244);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000256, EnemyEtis, "EnemyEtis-390");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001317);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001323, EnemyDrastea, "EnemyDrastea-391");
				break;
			}
			case 12350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000245);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000257, EnemyEtis, "EnemyEtis-392");
				break;
			}
			case 12400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000246);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000258, EnemyEtis, "EnemyEtis-393");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001318);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001324, EnemyDrastea, "EnemyDrastea-394");
				break;
			}
			case 12450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000247);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000259, EnemyEtis, "EnemyEtis-395");
				break;
			}
			case 12500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000248);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000260, EnemyEtis, "EnemyEtis-396");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001319);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001325, EnemyDrastea, "EnemyDrastea-397");
				break;
			}
			case 12550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000249);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000261, EnemyEtis, "EnemyEtis-398");
				break;
			}
			case 12600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000250);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000262, EnemyEtis, "EnemyEtis-399");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001320);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001326, EnemyDrastea, "EnemyDrastea-400");
				break;
			}
			case 12650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000251);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000263, EnemyEtis, "EnemyEtis-401");
				break;
			}
			case 12700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000252);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000264, EnemyEtis, "EnemyEtis-402");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001321);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001327, EnemyDrastea, "EnemyDrastea-403");
				break;
			}
			case 12750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000253);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000265, EnemyEtis, "EnemyEtis-404");
				break;
			}
			case 12800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000254);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000266, EnemyEtis, "EnemyEtis-405");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001322);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001328, EnemyDrastea, "EnemyDrastea-406");
				break;
			}
			case 12850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000255);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000267, EnemyEtis, "EnemyEtis-407");
				break;
			}
			case 12900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000256);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000268, EnemyEtis, "EnemyEtis-408");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001323);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001329, EnemyDrastea, "EnemyDrastea-409");
				break;
			}
			case 12950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000257);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000269, EnemyEtis, "EnemyEtis-410");
				break;
			}
			case 13000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000258);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000270, EnemyEtis, "EnemyEtis-411");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001324);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001330, EnemyDrastea, "EnemyDrastea-412");
				break;
			}
			case 13050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000259);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000271, EnemyEtis, "EnemyEtis-413");
				break;
			}
			case 13100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000260);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000272, EnemyEtis, "EnemyEtis-414");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001325);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001331, EnemyDrastea, "EnemyDrastea-415");
				break;
			}
			case 13150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000261);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000273, EnemyEtis, "EnemyEtis-416");
				break;
			}
			case 13200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000262);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000274, EnemyEtis, "EnemyEtis-417");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001326);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001332, EnemyDrastea, "EnemyDrastea-418");
				break;
			}
			case 13250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000263);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000275, EnemyEtis, "EnemyEtis-419");
				break;
			}
			case 13300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000264);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000276, EnemyEtis, "EnemyEtis-420");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001327);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001333, EnemyDrastea, "EnemyDrastea-421");
				break;
			}
			case 13350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000265);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000277, EnemyEtis, "EnemyEtis-422");
				break;
			}
			case 13400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000266);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000278, EnemyEtis, "EnemyEtis-423");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001328);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001334, EnemyDrastea, "EnemyDrastea-424");
				break;
			}
			case 13450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000267);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000279, EnemyEtis, "EnemyEtis-425");
				break;
			}
			case 13500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000268);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000280, EnemyEtis, "EnemyEtis-426");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001329);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001335, EnemyDrastea, "EnemyDrastea-427");
				break;
			}
			case 13550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000269);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000281, EnemyEtis, "EnemyEtis-428");
				break;
			}
			case 13600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000270);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000282, EnemyEtis, "EnemyEtis-429");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001330);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001336, EnemyDrastea, "EnemyDrastea-430");
				break;
			}
			case 13650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000271);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000283, EnemyEtis, "EnemyEtis-431");
				break;
			}
			case 13700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000272);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000284, EnemyEtis, "EnemyEtis-432");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001331);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001337, EnemyDrastea, "EnemyDrastea-433");
				break;
			}
			case 13750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000273);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000285, EnemyEtis, "EnemyEtis-434");
				break;
			}
			case 13800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000274);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000286, EnemyEtis, "EnemyEtis-435");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001332);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001338, EnemyDrastea, "EnemyDrastea-436");
				break;
			}
			case 13850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000275);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000287, EnemyEtis, "EnemyEtis-437");
				break;
			}
			case 13900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000276);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000288, EnemyEtis, "EnemyEtis-438");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001333);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001339, EnemyDrastea, "EnemyDrastea-439");
				break;
			}
			case 13950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000277);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000289, EnemyEtis, "EnemyEtis-440");
				break;
			}
			case 14000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000278);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000290, EnemyEtis, "EnemyEtis-441");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001334);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001340, EnemyDrastea, "EnemyDrastea-442");
				break;
			}
			case 14050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000279);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000291, EnemyEtis, "EnemyEtis-443");
				break;
			}
			case 14100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000280);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000292, EnemyEtis, "EnemyEtis-444");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001335);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001341, EnemyDrastea, "EnemyDrastea-445");
				break;
			}
			case 14150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000281);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000293, EnemyEtis, "EnemyEtis-446");
				break;
			}
			case 14200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000282);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000294, EnemyEtis, "EnemyEtis-447");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001336);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001342, EnemyDrastea, "EnemyDrastea-448");
				break;
			}
			case 14250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000283);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000295, EnemyEtis, "EnemyEtis-449");
				break;
			}
			case 14300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000284);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000296, EnemyEtis, "EnemyEtis-450");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001337);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001343, EnemyDrastea, "EnemyDrastea-451");
				break;
			}
			case 14350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000285);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000297, EnemyEtis, "EnemyEtis-452");
				break;
			}
			case 14400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000286);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000298, EnemyEtis, "EnemyEtis-453");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001338);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001344, EnemyDrastea, "EnemyDrastea-454");
				break;
			}
			case 14450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000287);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000299, EnemyEtis, "EnemyEtis-455");
				break;
			}
			case 14500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000288);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000300, EnemyEtis, "EnemyEtis-456");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001339);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001345, EnemyDrastea, "EnemyDrastea-457");
				break;
			}
			case 14550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000289);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000301, EnemyEtis, "EnemyEtis-458");
				break;
			}
			case 14600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000290);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000302, EnemyEtis, "EnemyEtis-459");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001340);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001346, EnemyDrastea, "EnemyDrastea-460");
				break;
			}
			case 14650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000291);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000303, EnemyEtis, "EnemyEtis-461");
				break;
			}
			case 14700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000292);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000304, EnemyEtis, "EnemyEtis-462");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001341);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001347, EnemyDrastea, "EnemyDrastea-463");
				break;
			}
			case 14750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000293);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000305, EnemyEtis, "EnemyEtis-464");
				break;
			}
			case 14800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000294);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000306, EnemyEtis, "EnemyEtis-465");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001342);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001348, EnemyDrastea, "EnemyDrastea-466");
				break;
			}
			case 14850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000295);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000307, EnemyEtis, "EnemyEtis-467");
				break;
			}
			case 14900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000296);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000308, EnemyEtis, "EnemyEtis-468");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001343);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001349, EnemyDrastea, "EnemyDrastea-469");
				break;
			}
			case 14950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000297);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000309, EnemyEtis, "EnemyEtis-470");
				break;
			}
			case 15000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000298);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000310, EnemyEtis, "EnemyEtis-471");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001344);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001350, EnemyDrastea, "EnemyDrastea-472");
				break;
			}
			case 15050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000299);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000311, EnemyEtis, "EnemyEtis-473");
				break;
			}
			case 15100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000300);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000312, EnemyEtis, "EnemyEtis-474");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001345);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001351, EnemyDrastea, "EnemyDrastea-475");
				break;
			}
			case 15150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000301);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000313, EnemyEtis, "EnemyEtis-476");
				break;
			}
			case 15200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000302);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000314, EnemyEtis, "EnemyEtis-477");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001346);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001352, EnemyDrastea, "EnemyDrastea-478");
				break;
			}
			case 15250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000303);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000315, EnemyEtis, "EnemyEtis-479");
				break;
			}
			case 15300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000304);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000316, EnemyEtis, "EnemyEtis-480");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001347);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001353, EnemyDrastea, "EnemyDrastea-481");
				break;
			}
			case 15350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000305);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000317, EnemyEtis, "EnemyEtis-482");
				break;
			}
			case 15400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000306);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000318, EnemyEtis, "EnemyEtis-483");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001348);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001354, EnemyDrastea, "EnemyDrastea-484");
				break;
			}
			case 15450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000307);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000319, EnemyEtis, "EnemyEtis-485");
				break;
			}
			case 15500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000308);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000320, EnemyEtis, "EnemyEtis-486");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001349);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001355, EnemyDrastea, "EnemyDrastea-487");
				break;
			}
			case 15550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000309);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000321, EnemyEtis, "EnemyEtis-488");
				break;
			}
			case 15600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000310);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000322, EnemyEtis, "EnemyEtis-489");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001350);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001356, EnemyDrastea, "EnemyDrastea-490");
				break;
			}
			case 15650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000311);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000323, EnemyEtis, "EnemyEtis-491");
				break;
			}
			case 15700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000312);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000324, EnemyEtis, "EnemyEtis-492");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001351);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001357, EnemyDrastea, "EnemyDrastea-493");
				break;
			}
			case 15750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000313);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000325, EnemyEtis, "EnemyEtis-494");
				break;
			}
			case 15800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000314);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000326, EnemyEtis, "EnemyEtis-495");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001352);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001358, EnemyDrastea, "EnemyDrastea-496");
				break;
			}
			case 15850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000315);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000327, EnemyEtis, "EnemyEtis-497");
				break;
			}
			case 15900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000316);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000328, EnemyEtis, "EnemyEtis-498");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001353);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001359, EnemyDrastea, "EnemyDrastea-499");
				break;
			}
			case 15950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000317);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000329, EnemyEtis, "EnemyEtis-500");
				break;
			}
			case 16000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000318);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000330, EnemyEtis, "EnemyEtis-501");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001354);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001360, EnemyDrastea, "EnemyDrastea-502");
				break;
			}
			case 16050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000319);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000331, EnemyEtis, "EnemyEtis-503");
				break;
			}
			case 16100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000320);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000332, EnemyEtis, "EnemyEtis-504");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001355);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001361, EnemyDrastea, "EnemyDrastea-505");
				break;
			}
			case 16150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000321);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000333, EnemyEtis, "EnemyEtis-506");
				break;
			}
			case 16200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000322);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000334, EnemyEtis, "EnemyEtis-507");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001356);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001362, EnemyDrastea, "EnemyDrastea-508");
				break;
			}
			case 16250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000323);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000335, EnemyEtis, "EnemyEtis-509");
				break;
			}
			case 16300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000324);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000336, EnemyEtis, "EnemyEtis-510");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001357);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001363, EnemyDrastea, "EnemyDrastea-511");
				break;
			}
			case 16350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000325);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000337, EnemyEtis, "EnemyEtis-512");
				break;
			}
			case 16400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000326);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000338, EnemyEtis, "EnemyEtis-513");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001358);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001364, EnemyDrastea, "EnemyDrastea-514");
				break;
			}
			case 16450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000327);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000339, EnemyEtis, "EnemyEtis-515");
				break;
			}
			case 16500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000328);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000340, EnemyEtis, "EnemyEtis-516");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001359);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001365, EnemyDrastea, "EnemyDrastea-517");
				break;
			}
			case 16550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000329);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000341, EnemyEtis, "EnemyEtis-518");
				break;
			}
			case 16600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000330);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000342, EnemyEtis, "EnemyEtis-519");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001360);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001366, EnemyDrastea, "EnemyDrastea-520");
				break;
			}
			case 16650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000331);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000343, EnemyEtis, "EnemyEtis-521");
				break;
			}
			case 16700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000332);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000344, EnemyEtis, "EnemyEtis-522");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001361);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001367, EnemyDrastea, "EnemyDrastea-523");
				break;
			}
			case 16750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000333);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000345, EnemyEtis, "EnemyEtis-524");
				break;
			}
			case 16800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000334);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000346, EnemyEtis, "EnemyEtis-525");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001362);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001368, EnemyDrastea, "EnemyDrastea-526");
				break;
			}
			case 16850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000335);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000347, EnemyEtis, "EnemyEtis-527");
				break;
			}
			case 16900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000336);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000348, EnemyEtis, "EnemyEtis-528");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001363);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001369, EnemyDrastea, "EnemyDrastea-529");
				break;
			}
			case 16950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000337);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000349, EnemyEtis, "EnemyEtis-530");
				break;
			}
			case 17000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000338);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000350, EnemyEtis, "EnemyEtis-531");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001364);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001370, EnemyDrastea, "EnemyDrastea-532");
				break;
			}
			case 17050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000339);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000351, EnemyEtis, "EnemyEtis-533");
				break;
			}
			case 17100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000340);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000352, EnemyEtis, "EnemyEtis-534");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001365);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001371, EnemyDrastea, "EnemyDrastea-535");
				break;
			}
			case 17150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000341);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000353, EnemyEtis, "EnemyEtis-536");
				break;
			}
			case 17200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000342);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000354, EnemyEtis, "EnemyEtis-537");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001366);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001372, EnemyDrastea, "EnemyDrastea-538");
				break;
			}
			case 17250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000343);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000355, EnemyEtis, "EnemyEtis-539");
				break;
			}
			case 17300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000344);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000356, EnemyEtis, "EnemyEtis-540");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001367);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001373, EnemyDrastea, "EnemyDrastea-541");
				break;
			}
			case 17350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000345);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000357, EnemyEtis, "EnemyEtis-542");
				break;
			}
			case 17400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000346);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000358, EnemyEtis, "EnemyEtis-543");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001368);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001374, EnemyDrastea, "EnemyDrastea-544");
				break;
			}
			case 17450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000347);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000359, EnemyEtis, "EnemyEtis-545");
				break;
			}
			case 17500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000348);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000360, EnemyEtis, "EnemyEtis-546");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001369);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001375, EnemyDrastea, "EnemyDrastea-547");
				break;
			}
			case 17550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000349);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000361, EnemyEtis, "EnemyEtis-548");
				break;
			}
			case 17600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000350);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000362, EnemyEtis, "EnemyEtis-549");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001370);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001376, EnemyDrastea, "EnemyDrastea-550");
				break;
			}
			case 17650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000351);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000363, EnemyEtis, "EnemyEtis-551");
				break;
			}
			case 17700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000352);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000364, EnemyEtis, "EnemyEtis-552");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001371);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001377, EnemyDrastea, "EnemyDrastea-553");
				break;
			}
			case 17750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000353);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000365, EnemyEtis, "EnemyEtis-554");
				break;
			}
			case 17800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000354);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000366, EnemyEtis, "EnemyEtis-555");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001372);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001378, EnemyDrastea, "EnemyDrastea-556");
				break;
			}
			case 17850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000355);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000367, EnemyEtis, "EnemyEtis-557");
				break;
			}
			case 17900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000356);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000368, EnemyEtis, "EnemyEtis-558");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001373);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001379, EnemyDrastea, "EnemyDrastea-559");
				break;
			}
			case 17950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000357);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000369, EnemyEtis, "EnemyEtis-560");
				break;
			}
			case 18000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000358);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000370, EnemyEtis, "EnemyEtis-561");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001374);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001380, EnemyDrastea, "EnemyDrastea-562");
				break;
			}
			case 18050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000359);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000371, EnemyEtis, "EnemyEtis-563");
				break;
			}
			case 18100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000360);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000372, EnemyEtis, "EnemyEtis-564");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001375);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001381, EnemyDrastea, "EnemyDrastea-565");
				break;
			}
			case 18150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000361);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000373, EnemyEtis, "EnemyEtis-566");
				break;
			}
			case 18200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000362);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000374, EnemyEtis, "EnemyEtis-567");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001376);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001382, EnemyDrastea, "EnemyDrastea-568");
				break;
			}
			case 18250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000363);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000375, EnemyEtis, "EnemyEtis-569");
				break;
			}
			case 18300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000364);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000376, EnemyEtis, "EnemyEtis-570");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001377);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001383, EnemyDrastea, "EnemyDrastea-571");
				break;
			}
			case 18350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000365);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000377, EnemyEtis, "EnemyEtis-572");
				break;
			}
			case 18400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000366);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000378, EnemyEtis, "EnemyEtis-573");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001378);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001384, EnemyDrastea, "EnemyDrastea-574");
				break;
			}
			case 18450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000367);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000379, EnemyEtis, "EnemyEtis-575");
				break;
			}
			case 18500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000368);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000380, EnemyEtis, "EnemyEtis-576");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001379);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001385, EnemyDrastea, "EnemyDrastea-577");
				break;
			}
			case 18550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000369);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000381, EnemyEtis, "EnemyEtis-578");
				break;
			}
			case 18600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000370);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000382, EnemyEtis, "EnemyEtis-579");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001380);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001386, EnemyDrastea, "EnemyDrastea-580");
				break;
			}
			case 18650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000371);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000383, EnemyEtis, "EnemyEtis-581");
				break;
			}
			case 18700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000372);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000384, EnemyEtis, "EnemyEtis-582");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001381);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001387, EnemyDrastea, "EnemyDrastea-583");
				break;
			}
			case 18750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000373);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000385, EnemyEtis, "EnemyEtis-584");
				break;
			}
			case 18800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000374);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000386, EnemyEtis, "EnemyEtis-585");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001382);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001388, EnemyDrastea, "EnemyDrastea-586");
				break;
			}
			case 18850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000375);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000387, EnemyEtis, "EnemyEtis-587");
				break;
			}
			case 18900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000376);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000388, EnemyEtis, "EnemyEtis-588");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001383);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001389, EnemyDrastea, "EnemyDrastea-589");
				break;
			}
			case 18950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000377);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000389, EnemyEtis, "EnemyEtis-590");
				break;
			}
			case 19000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000378);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000390, EnemyEtis, "EnemyEtis-591");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001384);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001390, EnemyDrastea, "EnemyDrastea-592");
				break;
			}
			case 19050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000379);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000391, EnemyEtis, "EnemyEtis-593");
				break;
			}
			case 19100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000380);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000392, EnemyEtis, "EnemyEtis-594");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001385);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001391, EnemyDrastea, "EnemyDrastea-595");
				break;
			}
			case 19150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000381);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000393, EnemyEtis, "EnemyEtis-596");
				break;
			}
			case 19200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000382);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000394, EnemyEtis, "EnemyEtis-597");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001386);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001392, EnemyDrastea, "EnemyDrastea-598");
				break;
			}
			case 19250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000383);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000395, EnemyEtis, "EnemyEtis-599");
				break;
			}
			case 19300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000384);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000396, EnemyEtis, "EnemyEtis-600");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001387);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001393, EnemyDrastea, "EnemyDrastea-601");
				break;
			}
			case 19350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000385);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000397, EnemyEtis, "EnemyEtis-602");
				break;
			}
			case 19400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000386);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000398, EnemyEtis, "EnemyEtis-603");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001388);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001394, EnemyDrastea, "EnemyDrastea-604");
				break;
			}
			case 19450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000387);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000399, EnemyEtis, "EnemyEtis-605");
				break;
			}
			case 19500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000388);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000400, EnemyEtis, "EnemyEtis-606");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001389);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001395, EnemyDrastea, "EnemyDrastea-607");
				break;
			}
			case 19550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000389);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000401, EnemyEtis, "EnemyEtis-608");
				break;
			}
			case 19600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000390);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000402, EnemyEtis, "EnemyEtis-609");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001390);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001396, EnemyDrastea, "EnemyDrastea-610");
				break;
			}
			case 19650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000391);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000403, EnemyEtis, "EnemyEtis-611");
				break;
			}
			case 19700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000392);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000404, EnemyEtis, "EnemyEtis-612");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001391);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001397, EnemyDrastea, "EnemyDrastea-613");
				break;
			}
			case 19750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000393);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000405, EnemyEtis, "EnemyEtis-614");
				break;
			}
			case 19800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000394);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000406, EnemyEtis, "EnemyEtis-615");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001392);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001398, EnemyDrastea, "EnemyDrastea-616");
				break;
			}
			case 19850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000395);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000407, EnemyEtis, "EnemyEtis-617");
				break;
			}
			case 19900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000396);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000408, EnemyEtis, "EnemyEtis-618");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001393);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001399, EnemyDrastea, "EnemyDrastea-619");
				break;
			}
			case 19950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000397);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000409, EnemyEtis, "EnemyEtis-620");
				break;
			}
			case 20000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000398);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000410, EnemyEtis, "EnemyEtis-621");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001394);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001400, EnemyDrastea, "EnemyDrastea-622");
				break;
			}
			case 20050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000399);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000411, EnemyEtis, "EnemyEtis-623");
				break;
			}
			case 20100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000400);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000412, EnemyEtis, "EnemyEtis-624");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001395);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001401, EnemyDrastea, "EnemyDrastea-625");
				break;
			}
			case 20150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000401);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000413, EnemyEtis, "EnemyEtis-626");
				break;
			}
			case 20200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000402);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000414, EnemyEtis, "EnemyEtis-627");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001396);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001402, EnemyDrastea, "EnemyDrastea-628");
				break;
			}
			case 20250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000403);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000415, EnemyEtis, "EnemyEtis-629");
				break;
			}
			case 20300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000404);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000416, EnemyEtis, "EnemyEtis-630");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001397);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001403, EnemyDrastea, "EnemyDrastea-631");
				break;
			}
			case 20350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000405);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000417, EnemyEtis, "EnemyEtis-632");
				break;
			}
			case 20400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000406);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000418, EnemyEtis, "EnemyEtis-633");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001398);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001404, EnemyDrastea, "EnemyDrastea-634");
				break;
			}
			case 20450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000407);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000419, EnemyEtis, "EnemyEtis-635");
				break;
			}
			case 20500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000408);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000420, EnemyEtis, "EnemyEtis-636");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001399);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001405, EnemyDrastea, "EnemyDrastea-637");
				break;
			}
			case 20550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000409);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000421, EnemyEtis, "EnemyEtis-638");
				break;
			}
			case 20600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000410);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000422, EnemyEtis, "EnemyEtis-639");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001400);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001406, EnemyDrastea, "EnemyDrastea-640");
				break;
			}
			case 20650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000411);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000423, EnemyEtis, "EnemyEtis-641");
				break;
			}
			case 20700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000412);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000424, EnemyEtis, "EnemyEtis-642");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001401);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001407, EnemyDrastea, "EnemyDrastea-643");
				break;
			}
			case 20750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000413);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000425, EnemyEtis, "EnemyEtis-644");
				break;
			}
			case 20800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000414);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000426, EnemyEtis, "EnemyEtis-645");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001402);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001408, EnemyDrastea, "EnemyDrastea-646");
				break;
			}
			case 20850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000415);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000427, EnemyEtis, "EnemyEtis-647");
				break;
			}
			case 20900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000416);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000428, EnemyEtis, "EnemyEtis-648");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001403);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001409, EnemyDrastea, "EnemyDrastea-649");
				break;
			}
			case 20950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000417);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000429, EnemyEtis, "EnemyEtis-650");
				break;
			}
			case 21000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000418);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000430, EnemyEtis, "EnemyEtis-651");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001404);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001410, EnemyDrastea, "EnemyDrastea-652");
				break;
			}
			case 21050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000419);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000431, EnemyEtis, "EnemyEtis-653");
				break;
			}
			case 21100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000420);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000432, EnemyEtis, "EnemyEtis-654");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001405);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001411, EnemyDrastea, "EnemyDrastea-655");
				break;
			}
			case 21150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000421);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000433, EnemyEtis, "EnemyEtis-656");
				break;
			}
			case 21200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000422);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000434, EnemyEtis, "EnemyEtis-657");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001406);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001412, EnemyDrastea, "EnemyDrastea-658");
				break;
			}
			case 21250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000423);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000435, EnemyEtis, "EnemyEtis-659");
				break;
			}
			case 21300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000424);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000436, EnemyEtis, "EnemyEtis-660");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001407);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001413, EnemyDrastea, "EnemyDrastea-661");
				break;
			}
			case 21350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000425);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000437, EnemyEtis, "EnemyEtis-662");
				break;
			}
			case 21400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000426);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000438, EnemyEtis, "EnemyEtis-663");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001408);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001414, EnemyDrastea, "EnemyDrastea-664");
				break;
			}
			case 21450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000427);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000439, EnemyEtis, "EnemyEtis-665");
				break;
			}
			case 21500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000428);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000440, EnemyEtis, "EnemyEtis-666");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001409);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001415, EnemyDrastea, "EnemyDrastea-667");
				break;
			}
			case 21550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000429);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000441, EnemyEtis, "EnemyEtis-668");
				break;
			}
			case 21600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000430);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000442, EnemyEtis, "EnemyEtis-669");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001410);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001416, EnemyDrastea, "EnemyDrastea-670");
				break;
			}
			case 21650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000431);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000443, EnemyEtis, "EnemyEtis-671");
				break;
			}
			case 21700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000432);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000444, EnemyEtis, "EnemyEtis-672");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001411);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001417, EnemyDrastea, "EnemyDrastea-673");
				break;
			}
			case 21750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000433);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000445, EnemyEtis, "EnemyEtis-674");
				break;
			}
			case 21800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000434);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000446, EnemyEtis, "EnemyEtis-675");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001412);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001418, EnemyDrastea, "EnemyDrastea-676");
				break;
			}
			case 21850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000435);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000447, EnemyEtis, "EnemyEtis-677");
				break;
			}
			case 21900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000436);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000448, EnemyEtis, "EnemyEtis-678");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001413);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001419, EnemyDrastea, "EnemyDrastea-679");
				break;
			}
			case 21950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000437);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000449, EnemyEtis, "EnemyEtis-680");
				break;
			}
			case 22000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000438);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000450, EnemyEtis, "EnemyEtis-681");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001414);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001420, EnemyDrastea, "EnemyDrastea-682");
				break;
			}
			case 22050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000439);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000451, EnemyEtis, "EnemyEtis-683");
				break;
			}
			case 22100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000440);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000452, EnemyEtis, "EnemyEtis-684");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001415);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001421, EnemyDrastea, "EnemyDrastea-685");
				break;
			}
			case 22150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000441);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000453, EnemyEtis, "EnemyEtis-686");
				break;
			}
			case 22200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000442);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000454, EnemyEtis, "EnemyEtis-687");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001416);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001422, EnemyDrastea, "EnemyDrastea-688");
				break;
			}
			case 22250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000443);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000455, EnemyEtis, "EnemyEtis-689");
				break;
			}
			case 22300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000444);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000456, EnemyEtis, "EnemyEtis-690");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001417);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001423, EnemyDrastea, "EnemyDrastea-691");
				break;
			}
			case 22350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000445);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000457, EnemyEtis, "EnemyEtis-692");
				break;
			}
			case 22400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000446);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000458, EnemyEtis, "EnemyEtis-693");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001418);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001424, EnemyDrastea, "EnemyDrastea-694");
				break;
			}
			case 22450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000447);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000459, EnemyEtis, "EnemyEtis-695");
				break;
			}
			case 22500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000448);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000460, EnemyEtis, "EnemyEtis-696");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001419);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001425, EnemyDrastea, "EnemyDrastea-697");
				break;
			}
			case 22550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000449);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000461, EnemyEtis, "EnemyEtis-698");
				break;
			}
			case 22600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000450);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000462, EnemyEtis, "EnemyEtis-699");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001420);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001426, EnemyDrastea, "EnemyDrastea-700");
				break;
			}
			case 22650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000451);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000463, EnemyEtis, "EnemyEtis-701");
				break;
			}
			case 22700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000452);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000464, EnemyEtis, "EnemyEtis-702");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001421);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001427, EnemyDrastea, "EnemyDrastea-703");
				break;
			}
			case 22750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000453);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000465, EnemyEtis, "EnemyEtis-704");
				break;
			}
			case 22800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000454);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000466, EnemyEtis, "EnemyEtis-705");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001422);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001428, EnemyDrastea, "EnemyDrastea-706");
				break;
			}
			case 22850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000455);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000467, EnemyEtis, "EnemyEtis-707");
				break;
			}
			case 22900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000456);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000468, EnemyEtis, "EnemyEtis-708");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001423);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001429, EnemyDrastea, "EnemyDrastea-709");
				break;
			}
			case 22950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000457);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000469, EnemyEtis, "EnemyEtis-710");
				break;
			}
			case 23000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000458);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000470, EnemyEtis, "EnemyEtis-711");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001424);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001430, EnemyDrastea, "EnemyDrastea-712");
				break;
			}
			case 23050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000459);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000471, EnemyEtis, "EnemyEtis-713");
				break;
			}
			case 23100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000460);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000472, EnemyEtis, "EnemyEtis-714");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001425);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001431, EnemyDrastea, "EnemyDrastea-715");
				break;
			}
			case 23150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000461);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000473, EnemyEtis, "EnemyEtis-716");
				break;
			}
			case 23200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000462);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000474, EnemyEtis, "EnemyEtis-717");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001426);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001432, EnemyDrastea, "EnemyDrastea-718");
				break;
			}
			case 23250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000463);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000475, EnemyEtis, "EnemyEtis-719");
				break;
			}
			case 23300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000464);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000476, EnemyEtis, "EnemyEtis-720");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001427);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001433, EnemyDrastea, "EnemyDrastea-721");
				break;
			}
			case 23350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000465);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000477, EnemyEtis, "EnemyEtis-722");
				break;
			}
			case 23400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000466);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000478, EnemyEtis, "EnemyEtis-723");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001428);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001434, EnemyDrastea, "EnemyDrastea-724");
				break;
			}
			case 23450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000467);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000479, EnemyEtis, "EnemyEtis-725");
				break;
			}
			case 23500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000468);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000480, EnemyEtis, "EnemyEtis-726");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001429);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001435, EnemyDrastea, "EnemyDrastea-727");
				break;
			}
			case 23550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000469);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000481, EnemyEtis, "EnemyEtis-728");
				break;
			}
			case 23600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000470);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000482, EnemyEtis, "EnemyEtis-729");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001430);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001436, EnemyDrastea, "EnemyDrastea-730");
				break;
			}
			case 23650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000471);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000483, EnemyEtis, "EnemyEtis-731");
				break;
			}
			case 23700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000472);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000484, EnemyEtis, "EnemyEtis-732");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001431);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001437, EnemyDrastea, "EnemyDrastea-733");
				break;
			}
			case 23750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000473);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000485, EnemyEtis, "EnemyEtis-734");
				break;
			}
			case 23800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000474);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000486, EnemyEtis, "EnemyEtis-735");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001432);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001438, EnemyDrastea, "EnemyDrastea-736");
				break;
			}
			case 23850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000475);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000487, EnemyEtis, "EnemyEtis-737");
				break;
			}
			case 23900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000476);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000488, EnemyEtis, "EnemyEtis-738");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001433);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001439, EnemyDrastea, "EnemyDrastea-739");
				break;
			}
			case 23950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000477);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000489, EnemyEtis, "EnemyEtis-740");
				break;
			}
			case 24000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000478);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000490, EnemyEtis, "EnemyEtis-741");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001434);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001440, EnemyDrastea, "EnemyDrastea-742");
				break;
			}
			case 24050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000479);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000491, EnemyEtis, "EnemyEtis-743");
				break;
			}
			case 24100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000480);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000492, EnemyEtis, "EnemyEtis-744");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001435);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001441, EnemyDrastea, "EnemyDrastea-745");
				break;
			}
			case 24150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000481);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000493, EnemyEtis, "EnemyEtis-746");
				break;
			}
			case 24200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000482);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000494, EnemyEtis, "EnemyEtis-747");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001436);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001442, EnemyDrastea, "EnemyDrastea-748");
				break;
			}
			case 24250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000483);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000495, EnemyEtis, "EnemyEtis-749");
				break;
			}
			case 24300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000484);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000496, EnemyEtis, "EnemyEtis-750");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001437);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001443, EnemyDrastea, "EnemyDrastea-751");
				break;
			}
			case 24350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000485);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000497, EnemyEtis, "EnemyEtis-752");
				break;
			}
			case 24400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000486);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000498, EnemyEtis, "EnemyEtis-753");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001438);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001444, EnemyDrastea, "EnemyDrastea-754");
				break;
			}
			case 24450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000487);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000499, EnemyEtis, "EnemyEtis-755");
				break;
			}
			case 24500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000488);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000500, EnemyEtis, "EnemyEtis-756");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001439);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001445, EnemyDrastea, "EnemyDrastea-757");
				break;
			}
			case 24550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000489);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000501, EnemyEtis, "EnemyEtis-758");
				break;
			}
			case 24600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000490);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000502, EnemyEtis, "EnemyEtis-759");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001440);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001446, EnemyDrastea, "EnemyDrastea-760");
				break;
			}
			case 24650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000491);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000503, EnemyEtis, "EnemyEtis-761");
				break;
			}
			case 24700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000492);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000504, EnemyEtis, "EnemyEtis-762");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001441);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001447, EnemyDrastea, "EnemyDrastea-763");
				break;
			}
			case 24750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000493);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000505, EnemyEtis, "EnemyEtis-764");
				break;
			}
			case 24800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000494);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000506, EnemyEtis, "EnemyEtis-765");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001442);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001448, EnemyDrastea, "EnemyDrastea-766");
				break;
			}
			case 24850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000495);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000507, EnemyEtis, "EnemyEtis-767");
				break;
			}
			case 24900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000496);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000508, EnemyEtis, "EnemyEtis-768");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001443);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001449, EnemyDrastea, "EnemyDrastea-769");
				break;
			}
			case 24950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000497);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000509, EnemyEtis, "EnemyEtis-770");
				break;
			}
			case 25000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000498);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000510, EnemyEtis, "EnemyEtis-771");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001444);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001450, EnemyDrastea, "EnemyDrastea-772");
				break;
			}
			case 25050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000499);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000511, EnemyEtis, "EnemyEtis-773");
				break;
			}
			case 25100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000500);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000512, EnemyEtis, "EnemyEtis-774");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001445);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001451, EnemyDrastea, "EnemyDrastea-775");
				break;
			}
			case 25150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000501);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000513, EnemyEtis, "EnemyEtis-776");
				break;
			}
			case 25200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000502);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000514, EnemyEtis, "EnemyEtis-777");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001446);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001452, EnemyDrastea, "EnemyDrastea-778");
				break;
			}
			case 25250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000503);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000515, EnemyEtis, "EnemyEtis-779");
				break;
			}
			case 25300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000504);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000516, EnemyEtis, "EnemyEtis-780");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001447);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001453, EnemyDrastea, "EnemyDrastea-781");
				break;
			}
			case 25350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000505);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000517, EnemyEtis, "EnemyEtis-782");
				break;
			}
			case 25400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000506);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000518, EnemyEtis, "EnemyEtis-783");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001448);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001454, EnemyDrastea, "EnemyDrastea-784");
				break;
			}
			case 25450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000507);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000519, EnemyEtis, "EnemyEtis-785");
				break;
			}
			case 25500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000508);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000520, EnemyEtis, "EnemyEtis-786");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001449);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001455, EnemyDrastea, "EnemyDrastea-787");
				break;
			}
			case 25550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000509);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000521, EnemyEtis, "EnemyEtis-788");
				break;
			}
			case 25600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000510);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000522, EnemyEtis, "EnemyEtis-789");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001450);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001456, EnemyDrastea, "EnemyDrastea-790");
				break;
			}
			case 25650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000511);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000523, EnemyEtis, "EnemyEtis-791");
				break;
			}
			case 25700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000512);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000524, EnemyEtis, "EnemyEtis-792");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001451);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001457, EnemyDrastea, "EnemyDrastea-793");
				break;
			}
			case 25750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000513);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000525, EnemyEtis, "EnemyEtis-794");
				break;
			}
			case 25800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000514);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000526, EnemyEtis, "EnemyEtis-795");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001452);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001458, EnemyDrastea, "EnemyDrastea-796");
				break;
			}
			case 25850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000515);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000527, EnemyEtis, "EnemyEtis-797");
				break;
			}
			case 25900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000516);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000528, EnemyEtis, "EnemyEtis-798");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001453);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001459, EnemyDrastea, "EnemyDrastea-799");
				break;
			}
			case 25950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000517);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000529, EnemyEtis, "EnemyEtis-800");
				break;
			}
			case 26000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000518);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000530, EnemyEtis, "EnemyEtis-801");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001454);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001460, EnemyDrastea, "EnemyDrastea-802");
				break;
			}
			case 26050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000519);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000531, EnemyEtis, "EnemyEtis-803");
				break;
			}
			case 26100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000520);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000532, EnemyEtis, "EnemyEtis-804");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001455);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001461, EnemyDrastea, "EnemyDrastea-805");
				break;
			}
			case 26150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000521);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000533, EnemyEtis, "EnemyEtis-806");
				break;
			}
			case 26200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000522);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000534, EnemyEtis, "EnemyEtis-807");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001456);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001462, EnemyDrastea, "EnemyDrastea-808");
				break;
			}
			case 26250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000523);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000535, EnemyEtis, "EnemyEtis-809");
				break;
			}
			case 26300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000524);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000536, EnemyEtis, "EnemyEtis-810");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001457);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001463, EnemyDrastea, "EnemyDrastea-811");
				break;
			}
			case 26350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000525);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000537, EnemyEtis, "EnemyEtis-812");
				break;
			}
			case 26400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000526);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000538, EnemyEtis, "EnemyEtis-813");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001458);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001464, EnemyDrastea, "EnemyDrastea-814");
				break;
			}
			case 26450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000527);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000539, EnemyEtis, "EnemyEtis-815");
				break;
			}
			case 26500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000528);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000540, EnemyEtis, "EnemyEtis-816");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001459);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001465, EnemyDrastea, "EnemyDrastea-817");
				break;
			}
			case 26550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000529);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000541, EnemyEtis, "EnemyEtis-818");
				break;
			}
			case 26600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000530);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000542, EnemyEtis, "EnemyEtis-819");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001460);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001466, EnemyDrastea, "EnemyDrastea-820");
				break;
			}
			case 26650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000531);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000543, EnemyEtis, "EnemyEtis-821");
				break;
			}
			case 26700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000532);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000544, EnemyEtis, "EnemyEtis-822");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001461);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001467, EnemyDrastea, "EnemyDrastea-823");
				break;
			}
			case 26750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000533);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000545, EnemyEtis, "EnemyEtis-824");
				break;
			}
			case 26800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000534);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000546, EnemyEtis, "EnemyEtis-825");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001462);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001468, EnemyDrastea, "EnemyDrastea-826");
				break;
			}
			case 26850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000535);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000547, EnemyEtis, "EnemyEtis-827");
				break;
			}
			case 26900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000536);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000548, EnemyEtis, "EnemyEtis-828");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001463);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001469, EnemyDrastea, "EnemyDrastea-829");
				break;
			}
			case 26950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000537);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000549, EnemyEtis, "EnemyEtis-830");
				break;
			}
			case 27000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000538);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000550, EnemyEtis, "EnemyEtis-831");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001464);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001470, EnemyDrastea, "EnemyDrastea-832");
				break;
			}
			case 27050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000539);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000551, EnemyEtis, "EnemyEtis-833");
				break;
			}
			case 27100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000540);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000552, EnemyEtis, "EnemyEtis-834");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001465);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001471, EnemyDrastea, "EnemyDrastea-835");
				break;
			}
			case 27150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000541);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000553, EnemyEtis, "EnemyEtis-836");
				break;
			}
			case 27200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000542);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000554, EnemyEtis, "EnemyEtis-837");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001466);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001472, EnemyDrastea, "EnemyDrastea-838");
				break;
			}
			case 27250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000543);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000555, EnemyEtis, "EnemyEtis-839");
				break;
			}
			case 27300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000544);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000556, EnemyEtis, "EnemyEtis-840");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001467);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001473, EnemyDrastea, "EnemyDrastea-841");
				break;
			}
			case 27350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000545);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000557, EnemyEtis, "EnemyEtis-842");
				break;
			}
			case 27400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000546);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000558, EnemyEtis, "EnemyEtis-843");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001468);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001474, EnemyDrastea, "EnemyDrastea-844");
				break;
			}
			case 27450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000547);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000559, EnemyEtis, "EnemyEtis-845");
				break;
			}
			case 27500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000548);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000560, EnemyEtis, "EnemyEtis-846");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001469);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001475, EnemyDrastea, "EnemyDrastea-847");
				break;
			}
			case 27550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000549);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000561, EnemyEtis, "EnemyEtis-848");
				break;
			}
			case 27600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000550);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000562, EnemyEtis, "EnemyEtis-849");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001470);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001476, EnemyDrastea, "EnemyDrastea-850");
				break;
			}
			case 27650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000551);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000563, EnemyEtis, "EnemyEtis-851");
				break;
			}
			case 27700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000552);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000564, EnemyEtis, "EnemyEtis-852");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001471);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001477, EnemyDrastea, "EnemyDrastea-853");
				break;
			}
			case 27750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000553);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000565, EnemyEtis, "EnemyEtis-854");
				break;
			}
			case 27800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000554);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000566, EnemyEtis, "EnemyEtis-855");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001472);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001478, EnemyDrastea, "EnemyDrastea-856");
				break;
			}
			case 27850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000555);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000567, EnemyEtis, "EnemyEtis-857");
				break;
			}
			case 27900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000556);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000568, EnemyEtis, "EnemyEtis-858");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001473);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001479, EnemyDrastea, "EnemyDrastea-859");
				break;
			}
			case 27950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000557);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000569, EnemyEtis, "EnemyEtis-860");
				break;
			}
			case 28000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000558);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000570, EnemyEtis, "EnemyEtis-861");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001474);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001480, EnemyDrastea, "EnemyDrastea-862");
				break;
			}
			case 28050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000559);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000571, EnemyEtis, "EnemyEtis-863");
				break;
			}
			case 28100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000560);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000572, EnemyEtis, "EnemyEtis-864");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001475);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001481, EnemyDrastea, "EnemyDrastea-865");
				break;
			}
			case 28150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000561);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000573, EnemyEtis, "EnemyEtis-866");
				break;
			}
			case 28200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000562);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000574, EnemyEtis, "EnemyEtis-867");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001476);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001482, EnemyDrastea, "EnemyDrastea-868");
				break;
			}
			case 28250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000563);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000575, EnemyEtis, "EnemyEtis-869");
				break;
			}
			case 28300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000564);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000576, EnemyEtis, "EnemyEtis-870");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001477);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001483, EnemyDrastea, "EnemyDrastea-871");
				break;
			}
			case 28350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000565);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000577, EnemyEtis, "EnemyEtis-872");
				break;
			}
			case 28400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000566);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000578, EnemyEtis, "EnemyEtis-873");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001478);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001484, EnemyDrastea, "EnemyDrastea-874");
				break;
			}
			case 28450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000567);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000579, EnemyEtis, "EnemyEtis-875");
				break;
			}
			case 28500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000568);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000580, EnemyEtis, "EnemyEtis-876");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001479);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001485, EnemyDrastea, "EnemyDrastea-877");
				break;
			}
			case 28550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000569);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000581, EnemyEtis, "EnemyEtis-878");
				break;
			}
			case 28600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000570);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000582, EnemyEtis, "EnemyEtis-879");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001480);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001486, EnemyDrastea, "EnemyDrastea-880");
				break;
			}
			case 28650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000571);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000583, EnemyEtis, "EnemyEtis-881");
				break;
			}
			case 28700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000572);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000584, EnemyEtis, "EnemyEtis-882");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001481);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001487, EnemyDrastea, "EnemyDrastea-883");
				break;
			}
			case 28750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000573);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000585, EnemyEtis, "EnemyEtis-884");
				break;
			}
			case 28800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000574);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000586, EnemyEtis, "EnemyEtis-885");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001482);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001488, EnemyDrastea, "EnemyDrastea-886");
				break;
			}
			case 28850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000575);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000587, EnemyEtis, "EnemyEtis-887");
				break;
			}
			case 28900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000576);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000588, EnemyEtis, "EnemyEtis-888");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001483);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001489, EnemyDrastea, "EnemyDrastea-889");
				break;
			}
			case 28950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000577);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000589, EnemyEtis, "EnemyEtis-890");
				break;
			}
			case 29000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000578);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000590, EnemyEtis, "EnemyEtis-891");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001484);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001490, EnemyDrastea, "EnemyDrastea-892");
				break;
			}
			case 29050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000579);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000591, EnemyEtis, "EnemyEtis-893");
				break;
			}
			case 29100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000580);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000592, EnemyEtis, "EnemyEtis-894");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001485);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001491, EnemyDrastea, "EnemyDrastea-895");
				break;
			}
			case 29150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000581);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000593, EnemyEtis, "EnemyEtis-896");
				break;
			}
			case 29200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000582);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000594, EnemyEtis, "EnemyEtis-897");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001486);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001492, EnemyDrastea, "EnemyDrastea-898");
				break;
			}
			case 29250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000583);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000595, EnemyEtis, "EnemyEtis-899");
				break;
			}
			case 29300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000584);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000596, EnemyEtis, "EnemyEtis-900");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001487);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001493, EnemyDrastea, "EnemyDrastea-901");
				break;
			}
			case 29350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000585);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000597, EnemyEtis, "EnemyEtis-902");
				break;
			}
			case 29400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000586);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000598, EnemyEtis, "EnemyEtis-903");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001488);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001494, EnemyDrastea, "EnemyDrastea-904");
				break;
			}
			case 29450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000587);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000599, EnemyEtis, "EnemyEtis-905");
				break;
			}
			case 29500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000588);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000600, EnemyEtis, "EnemyEtis-906");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001489);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001495, EnemyDrastea, "EnemyDrastea-907");
				break;
			}
			case 29550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000589);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000601, EnemyEtis, "EnemyEtis-908");
				break;
			}
			case 29600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000590);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000602, EnemyEtis, "EnemyEtis-909");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001490);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001496, EnemyDrastea, "EnemyDrastea-910");
				break;
			}
			case 29650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000591);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000603, EnemyEtis, "EnemyEtis-911");
				break;
			}
			case 29700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000592);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000604, EnemyEtis, "EnemyEtis-912");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001491);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001497, EnemyDrastea, "EnemyDrastea-913");
				break;
			}
			case 29750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000593);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000605, EnemyEtis, "EnemyEtis-914");
				break;
			}
			case 29800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000594);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000606, EnemyEtis, "EnemyEtis-915");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001492);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001498, EnemyDrastea, "EnemyDrastea-916");
				break;
			}
			case 29850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000595);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000607, EnemyEtis, "EnemyEtis-917");
				break;
			}
			case 29900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000596);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000608, EnemyEtis, "EnemyEtis-918");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001493);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001499, EnemyDrastea, "EnemyDrastea-919");
				break;
			}
			case 29950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000597);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000609, EnemyEtis, "EnemyEtis-920");
				break;
			}
			case 30000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000598);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000610, EnemyEtis, "EnemyEtis-921");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001494);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001500, EnemyDrastea, "EnemyDrastea-922");
				break;
			}
			case 30050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000599);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000611, EnemyEtis, "EnemyEtis-923");
				break;
			}
			case 30100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000600);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000612, EnemyEtis, "EnemyEtis-924");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001495);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001501, EnemyDrastea, "EnemyDrastea-925");
				break;
			}
			case 30150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000601);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000613, EnemyEtis, "EnemyEtis-926");
				break;
			}
			case 30200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000602);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000614, EnemyEtis, "EnemyEtis-927");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001496);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001502, EnemyDrastea, "EnemyDrastea-928");
				break;
			}
			case 30250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000603);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000615, EnemyEtis, "EnemyEtis-929");
				break;
			}
			case 30300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000604);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000616, EnemyEtis, "EnemyEtis-930");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001497);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001503, EnemyDrastea, "EnemyDrastea-931");
				break;
			}
			case 30350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000605);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000617, EnemyEtis, "EnemyEtis-932");
				break;
			}
			case 30400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000606);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000618, EnemyEtis, "EnemyEtis-933");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001498);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001504, EnemyDrastea, "EnemyDrastea-934");
				break;
			}
			case 30450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000607);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000619, EnemyEtis, "EnemyEtis-935");
				break;
			}
			case 30500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000608);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000620, EnemyEtis, "EnemyEtis-936");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001499);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001505, EnemyDrastea, "EnemyDrastea-937");
				break;
			}
			case 30550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000609);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000621, EnemyEtis, "EnemyEtis-938");
				break;
			}
			case 30600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000610);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000622, EnemyEtis, "EnemyEtis-939");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001500);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001506, EnemyDrastea, "EnemyDrastea-940");
				break;
			}
			case 30650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000611);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000623, EnemyEtis, "EnemyEtis-941");
				break;
			}
			case 30700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000612);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000624, EnemyEtis, "EnemyEtis-942");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001501);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001507, EnemyDrastea, "EnemyDrastea-943");
				break;
			}
			case 30750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000613);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000625, EnemyEtis, "EnemyEtis-944");
				break;
			}
			case 30800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000614);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000626, EnemyEtis, "EnemyEtis-945");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001502);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001508, EnemyDrastea, "EnemyDrastea-946");
				break;
			}
			case 30850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000615);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000627, EnemyEtis, "EnemyEtis-947");
				break;
			}
			case 30900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000616);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000628, EnemyEtis, "EnemyEtis-948");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001503);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001509, EnemyDrastea, "EnemyDrastea-949");
				break;
			}
			case 30950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000617);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000629, EnemyEtis, "EnemyEtis-950");
				break;
			}
			case 31000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000618);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000630, EnemyEtis, "EnemyEtis-951");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001504);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001510, EnemyDrastea, "EnemyDrastea-952");
				break;
			}
			case 31050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000619);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000631, EnemyEtis, "EnemyEtis-953");
				break;
			}
			case 31100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000620);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000632, EnemyEtis, "EnemyEtis-954");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001505);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001511, EnemyDrastea, "EnemyDrastea-955");
				break;
			}
			case 31150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000621);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000633, EnemyEtis, "EnemyEtis-956");
				break;
			}
			case 31200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000622);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000634, EnemyEtis, "EnemyEtis-957");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001506);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001512, EnemyDrastea, "EnemyDrastea-958");
				break;
			}
			case 31250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000623);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000635, EnemyEtis, "EnemyEtis-959");
				break;
			}
			case 31300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000624);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000636, EnemyEtis, "EnemyEtis-960");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001507);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001513, EnemyDrastea, "EnemyDrastea-961");
				break;
			}
			case 31350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000625);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000637, EnemyEtis, "EnemyEtis-962");
				break;
			}
			case 31400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000626);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000638, EnemyEtis, "EnemyEtis-963");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001508);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001514, EnemyDrastea, "EnemyDrastea-964");
				break;
			}
			case 31450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000627);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000639, EnemyEtis, "EnemyEtis-965");
				break;
			}
			case 31500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000628);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000640, EnemyEtis, "EnemyEtis-966");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001509);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001515, EnemyDrastea, "EnemyDrastea-967");
				break;
			}
			case 31550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000629);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000641, EnemyEtis, "EnemyEtis-968");
				break;
			}
			case 31600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000630);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000642, EnemyEtis, "EnemyEtis-969");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001510);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001516, EnemyDrastea, "EnemyDrastea-970");
				break;
			}
			case 31650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000631);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000643, EnemyEtis, "EnemyEtis-971");
				break;
			}
			case 31700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000632);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000644, EnemyEtis, "EnemyEtis-972");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001511);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001517, EnemyDrastea, "EnemyDrastea-973");
				break;
			}
			case 31750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000633);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000645, EnemyEtis, "EnemyEtis-974");
				break;
			}
			case 31800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000634);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000646, EnemyEtis, "EnemyEtis-975");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001512);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001518, EnemyDrastea, "EnemyDrastea-976");
				break;
			}
			case 31850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000635);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000647, EnemyEtis, "EnemyEtis-977");
				break;
			}
			case 31900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000636);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000648, EnemyEtis, "EnemyEtis-978");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001513);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001519, EnemyDrastea, "EnemyDrastea-979");
				break;
			}
			case 31950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000637);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000649, EnemyEtis, "EnemyEtis-980");
				break;
			}
			case 32000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000638);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000650, EnemyEtis, "EnemyEtis-981");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001514);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001520, EnemyDrastea, "EnemyDrastea-982");
				break;
			}
			case 32050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000639);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000651, EnemyEtis, "EnemyEtis-983");
				break;
			}
			case 32100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000640);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000652, EnemyEtis, "EnemyEtis-984");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001515);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001521, EnemyDrastea, "EnemyDrastea-985");
				break;
			}
			case 32150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000641);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000653, EnemyEtis, "EnemyEtis-986");
				break;
			}
			case 32200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000642);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000654, EnemyEtis, "EnemyEtis-987");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001516);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001522, EnemyDrastea, "EnemyDrastea-988");
				break;
			}
			case 32250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000643);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000655, EnemyEtis, "EnemyEtis-989");
				break;
			}
			case 32300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000644);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000656, EnemyEtis, "EnemyEtis-990");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001517);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001523, EnemyDrastea, "EnemyDrastea-991");
				break;
			}
			case 32350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000645);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000657, EnemyEtis, "EnemyEtis-992");
				break;
			}
			case 32400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000646);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000658, EnemyEtis, "EnemyEtis-993");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001518);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001524, EnemyDrastea, "EnemyDrastea-994");
				break;
			}
			case 32450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000647);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000659, EnemyEtis, "EnemyEtis-995");
				break;
			}
			case 32500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000648);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000660, EnemyEtis, "EnemyEtis-996");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001519);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001525, EnemyDrastea, "EnemyDrastea-997");
				break;
			}
			case 32550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000649);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000661, EnemyEtis, "EnemyEtis-998");
				break;
			}
			case 32600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000650);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000662, EnemyEtis, "EnemyEtis-999");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001520);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001526, EnemyDrastea, "EnemyDrastea-1000");
				break;
			}
			case 32650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000651);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000663, EnemyEtis, "EnemyEtis-1001");
				break;
			}
			case 32700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000652);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000664, EnemyEtis, "EnemyEtis-1002");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001521);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001527, EnemyDrastea, "EnemyDrastea-1003");
				break;
			}
			case 32750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000653);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000665, EnemyEtis, "EnemyEtis-1004");
				break;
			}
			case 32800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000654);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000666, EnemyEtis, "EnemyEtis-1005");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001522);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001528, EnemyDrastea, "EnemyDrastea-1006");
				break;
			}
			case 32850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000655);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000667, EnemyEtis, "EnemyEtis-1007");
				break;
			}
			case 32900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000656);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000668, EnemyEtis, "EnemyEtis-1008");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001523);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001529, EnemyDrastea, "EnemyDrastea-1009");
				break;
			}
			case 32950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000657);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000669, EnemyEtis, "EnemyEtis-1010");
				break;
			}
			case 33000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000658);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000670, EnemyEtis, "EnemyEtis-1011");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001524);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001530, EnemyDrastea, "EnemyDrastea-1012");
				break;
			}
			case 33050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000659);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000671, EnemyEtis, "EnemyEtis-1013");
				break;
			}
			case 33100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000660);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000672, EnemyEtis, "EnemyEtis-1014");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001525);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001531, EnemyDrastea, "EnemyDrastea-1015");
				break;
			}
			case 33150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000661);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000673, EnemyEtis, "EnemyEtis-1016");
				break;
			}
			case 33200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000662);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000674, EnemyEtis, "EnemyEtis-1017");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001526);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001532, EnemyDrastea, "EnemyDrastea-1018");
				break;
			}
			case 33250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000663);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000675, EnemyEtis, "EnemyEtis-1019");
				break;
			}
			case 33300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000664);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000676, EnemyEtis, "EnemyEtis-1020");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001527);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001533, EnemyDrastea, "EnemyDrastea-1021");
				break;
			}
			case 33350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000665);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000677, EnemyEtis, "EnemyEtis-1022");
				break;
			}
			case 33400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000666);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000678, EnemyEtis, "EnemyEtis-1023");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001528);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001534, EnemyDrastea, "EnemyDrastea-1024");
				break;
			}
			case 33450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000667);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000679, EnemyEtis, "EnemyEtis-1025");
				break;
			}
			case 33500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000668);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000680, EnemyEtis, "EnemyEtis-1026");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001529);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001535, EnemyDrastea, "EnemyDrastea-1027");
				break;
			}
			case 33550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000669);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000681, EnemyEtis, "EnemyEtis-1028");
				break;
			}
			case 33600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000670);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000682, EnemyEtis, "EnemyEtis-1029");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001530);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001536, EnemyDrastea, "EnemyDrastea-1030");
				break;
			}
			case 33650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000671);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000683, EnemyEtis, "EnemyEtis-1031");
				break;
			}
			case 33700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000672);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000684, EnemyEtis, "EnemyEtis-1032");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001531);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001537, EnemyDrastea, "EnemyDrastea-1033");
				break;
			}
			case 33750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000673);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000685, EnemyEtis, "EnemyEtis-1034");
				break;
			}
			case 33800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000674);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000686, EnemyEtis, "EnemyEtis-1035");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001532);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001538, EnemyDrastea, "EnemyDrastea-1036");
				break;
			}
			case 33850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000675);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000687, EnemyEtis, "EnemyEtis-1037");
				break;
			}
			case 33900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000676);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000688, EnemyEtis, "EnemyEtis-1038");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001533);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001539, EnemyDrastea, "EnemyDrastea-1039");
				break;
			}
			case 33950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000677);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000689, EnemyEtis, "EnemyEtis-1040");
				break;
			}
			case 34000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000678);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000690, EnemyEtis, "EnemyEtis-1041");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001534);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001540, EnemyDrastea, "EnemyDrastea-1042");
				break;
			}
			case 34050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000679);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000691, EnemyEtis, "EnemyEtis-1043");
				break;
			}
			case 34100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000680);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000692, EnemyEtis, "EnemyEtis-1044");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001535);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001541, EnemyDrastea, "EnemyDrastea-1045");
				break;
			}
			case 34150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000681);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000693, EnemyEtis, "EnemyEtis-1046");
				break;
			}
			case 34200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000682);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000694, EnemyEtis, "EnemyEtis-1047");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001536);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001542, EnemyDrastea, "EnemyDrastea-1048");
				break;
			}
			case 34250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000683);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000695, EnemyEtis, "EnemyEtis-1049");
				break;
			}
			case 34300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000684);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000696, EnemyEtis, "EnemyEtis-1050");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001537);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001543, EnemyDrastea, "EnemyDrastea-1051");
				break;
			}
			case 34350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000685);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000697, EnemyEtis, "EnemyEtis-1052");
				break;
			}
			case 34400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000686);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000698, EnemyEtis, "EnemyEtis-1053");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001538);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001544, EnemyDrastea, "EnemyDrastea-1054");
				break;
			}
			case 34450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000687);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000699, EnemyEtis, "EnemyEtis-1055");
				break;
			}
			case 34500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000688);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000700, EnemyEtis, "EnemyEtis-1056");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001539);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001545, EnemyDrastea, "EnemyDrastea-1057");
				break;
			}
			case 34550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000689);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000701, EnemyEtis, "EnemyEtis-1058");
				break;
			}
			case 34600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000690);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000702, EnemyEtis, "EnemyEtis-1059");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001540);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001546, EnemyDrastea, "EnemyDrastea-1060");
				break;
			}
			case 34650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000691);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000703, EnemyEtis, "EnemyEtis-1061");
				break;
			}
			case 34700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000692);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000704, EnemyEtis, "EnemyEtis-1062");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001541);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001547, EnemyDrastea, "EnemyDrastea-1063");
				break;
			}
			case 34750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000693);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000705, EnemyEtis, "EnemyEtis-1064");
				break;
			}
			case 34800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000694);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000706, EnemyEtis, "EnemyEtis-1065");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001542);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001548, EnemyDrastea, "EnemyDrastea-1066");
				break;
			}
			case 34850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000695);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000707, EnemyEtis, "EnemyEtis-1067");
				break;
			}
			case 34900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000696);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000708, EnemyEtis, "EnemyEtis-1068");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001543);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001549, EnemyDrastea, "EnemyDrastea-1069");
				break;
			}
			case 34950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000697);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000709, EnemyEtis, "EnemyEtis-1070");
				break;
			}
			case 35000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000698);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000710, EnemyEtis, "EnemyEtis-1071");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001544);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001550, EnemyDrastea, "EnemyDrastea-1072");
				break;
			}
			case 35050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000699);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000711, EnemyEtis, "EnemyEtis-1073");
				break;
			}
			case 35100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000700);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000712, EnemyEtis, "EnemyEtis-1074");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001545);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001551, EnemyDrastea, "EnemyDrastea-1075");
				break;
			}
			case 35150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000701);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000713, EnemyEtis, "EnemyEtis-1076");
				break;
			}
			case 35200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000702);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000714, EnemyEtis, "EnemyEtis-1077");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001546);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001552, EnemyDrastea, "EnemyDrastea-1078");
				break;
			}
			case 35250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000703);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000715, EnemyEtis, "EnemyEtis-1079");
				break;
			}
			case 35300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000704);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000716, EnemyEtis, "EnemyEtis-1080");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001547);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001553, EnemyDrastea, "EnemyDrastea-1081");
				break;
			}
			case 35350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000705);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000717, EnemyEtis, "EnemyEtis-1082");
				break;
			}
			case 35400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000706);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000718, EnemyEtis, "EnemyEtis-1083");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001548);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001554, EnemyDrastea, "EnemyDrastea-1084");
				break;
			}
			case 35450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000707);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000719, EnemyEtis, "EnemyEtis-1085");
				break;
			}
			case 35500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000708);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000720, EnemyEtis, "EnemyEtis-1086");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001549);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001555, EnemyDrastea, "EnemyDrastea-1087");
				break;
			}
			case 35550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000709);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000721, EnemyEtis, "EnemyEtis-1088");
				break;
			}
			case 35600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000710);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000722, EnemyEtis, "EnemyEtis-1089");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001550);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001556, EnemyDrastea, "EnemyDrastea-1090");
				break;
			}
			case 35650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000711);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000723, EnemyEtis, "EnemyEtis-1091");
				break;
			}
			case 35700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000712);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000724, EnemyEtis, "EnemyEtis-1092");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001551);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001557, EnemyDrastea, "EnemyDrastea-1093");
				break;
			}
			case 35750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000713);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000725, EnemyEtis, "EnemyEtis-1094");
				break;
			}
			case 35800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000714);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000726, EnemyEtis, "EnemyEtis-1095");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001552);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001558, EnemyDrastea, "EnemyDrastea-1096");
				break;
			}
			case 35850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000715);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000727, EnemyEtis, "EnemyEtis-1097");
				break;
			}
			case 35900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000716);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000728, EnemyEtis, "EnemyEtis-1098");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001553);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001559, EnemyDrastea, "EnemyDrastea-1099");
				break;
			}
			case 35950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000717);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000729, EnemyEtis, "EnemyEtis-1100");
				break;
			}
			case 36000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000718);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000730, EnemyEtis, "EnemyEtis-1101");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001554);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001560, EnemyDrastea, "EnemyDrastea-1102");
				break;
			}
			case 36050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000719);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000731, EnemyEtis, "EnemyEtis-1103");
				break;
			}
			case 36100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000720);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000732, EnemyEtis, "EnemyEtis-1104");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001555);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001561, EnemyDrastea, "EnemyDrastea-1105");
				break;
			}
			case 36150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000721);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000733, EnemyEtis, "EnemyEtis-1106");
				break;
			}
			case 36200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000722);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000734, EnemyEtis, "EnemyEtis-1107");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001556);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001562, EnemyDrastea, "EnemyDrastea-1108");
				break;
			}
			case 36250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000723);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000735, EnemyEtis, "EnemyEtis-1109");
				break;
			}
			case 36300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000724);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000736, EnemyEtis, "EnemyEtis-1110");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001557);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001563, EnemyDrastea, "EnemyDrastea-1111");
				break;
			}
			case 36350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000725);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000737, EnemyEtis, "EnemyEtis-1112");
				break;
			}
			case 36400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000726);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000738, EnemyEtis, "EnemyEtis-1113");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001558);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001564, EnemyDrastea, "EnemyDrastea-1114");
				break;
			}
			case 36450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000727);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000739, EnemyEtis, "EnemyEtis-1115");
				break;
			}
			case 36500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000728);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000740, EnemyEtis, "EnemyEtis-1116");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001559);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001565, EnemyDrastea, "EnemyDrastea-1117");
				break;
			}
			case 36550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000729);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000741, EnemyEtis, "EnemyEtis-1118");
				break;
			}
			case 36600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000730);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000742, EnemyEtis, "EnemyEtis-1119");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001560);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001566, EnemyDrastea, "EnemyDrastea-1120");
				break;
			}
			case 36650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000731);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000743, EnemyEtis, "EnemyEtis-1121");
				break;
			}
			case 36700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000732);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000744, EnemyEtis, "EnemyEtis-1122");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001561);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001567, EnemyDrastea, "EnemyDrastea-1123");
				break;
			}
			case 36750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000733);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000745, EnemyEtis, "EnemyEtis-1124");
				break;
			}
			case 36800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000734);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000746, EnemyEtis, "EnemyEtis-1125");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001562);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001568, EnemyDrastea, "EnemyDrastea-1126");
				break;
			}
			case 36850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000735);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000747, EnemyEtis, "EnemyEtis-1127");
				break;
			}
			case 36900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000736);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000748, EnemyEtis, "EnemyEtis-1128");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001563);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001569, EnemyDrastea, "EnemyDrastea-1129");
				break;
			}
			case 36950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000737);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000749, EnemyEtis, "EnemyEtis-1130");
				break;
			}
			case 37000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000738);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000750, EnemyEtis, "EnemyEtis-1131");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001564);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001570, EnemyDrastea, "EnemyDrastea-1132");
				break;
			}
			case 37050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000739);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000751, EnemyEtis, "EnemyEtis-1133");
				break;
			}
			case 37100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000740);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000752, EnemyEtis, "EnemyEtis-1134");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001565);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001571, EnemyDrastea, "EnemyDrastea-1135");
				break;
			}
			case 37150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000741);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000753, EnemyEtis, "EnemyEtis-1136");
				break;
			}
			case 37200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000742);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000754, EnemyEtis, "EnemyEtis-1137");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001566);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001572, EnemyDrastea, "EnemyDrastea-1138");
				break;
			}
			case 37250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000743);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000755, EnemyEtis, "EnemyEtis-1139");
				break;
			}
			case 37300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000744);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000756, EnemyEtis, "EnemyEtis-1140");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001567);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001573, EnemyDrastea, "EnemyDrastea-1141");
				break;
			}
			case 37350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000745);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000757, EnemyEtis, "EnemyEtis-1142");
				break;
			}
			case 37400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000746);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000758, EnemyEtis, "EnemyEtis-1143");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001568);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001574, EnemyDrastea, "EnemyDrastea-1144");
				break;
			}
			case 37450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000747);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000759, EnemyEtis, "EnemyEtis-1145");
				break;
			}
			case 37500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000748);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000760, EnemyEtis, "EnemyEtis-1146");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001569);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001575, EnemyDrastea, "EnemyDrastea-1147");
				break;
			}
			case 37550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000749);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000761, EnemyEtis, "EnemyEtis-1148");
				break;
			}
			case 37600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000750);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000762, EnemyEtis, "EnemyEtis-1149");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001570);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001576, EnemyDrastea, "EnemyDrastea-1150");
				break;
			}
			case 37650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000751);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000763, EnemyEtis, "EnemyEtis-1151");
				break;
			}
			case 37700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000752);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000764, EnemyEtis, "EnemyEtis-1152");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001571);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001577, EnemyDrastea, "EnemyDrastea-1153");
				break;
			}
			case 37750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000753);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000765, EnemyEtis, "EnemyEtis-1154");
				break;
			}
			case 37800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000754);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000766, EnemyEtis, "EnemyEtis-1155");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001572);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001578, EnemyDrastea, "EnemyDrastea-1156");
				break;
			}
			case 37850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000755);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000767, EnemyEtis, "EnemyEtis-1157");
				break;
			}
			case 37900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000756);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000768, EnemyEtis, "EnemyEtis-1158");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001573);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001579, EnemyDrastea, "EnemyDrastea-1159");
				break;
			}
			case 37950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000757);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000769, EnemyEtis, "EnemyEtis-1160");
				break;
			}
			case 38000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000758);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000770, EnemyEtis, "EnemyEtis-1161");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001574);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001580, EnemyDrastea, "EnemyDrastea-1162");
				break;
			}
			case 38050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000759);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000771, EnemyEtis, "EnemyEtis-1163");
				break;
			}
			case 38100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000760);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000772, EnemyEtis, "EnemyEtis-1164");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001575);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001581, EnemyDrastea, "EnemyDrastea-1165");
				break;
			}
			case 38150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000761);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000773, EnemyEtis, "EnemyEtis-1166");
				break;
			}
			case 38200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000762);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000774, EnemyEtis, "EnemyEtis-1167");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001576);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001582, EnemyDrastea, "EnemyDrastea-1168");
				break;
			}
			case 38250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000763);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000775, EnemyEtis, "EnemyEtis-1169");
				break;
			}
			case 38300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000764);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000776, EnemyEtis, "EnemyEtis-1170");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001577);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001583, EnemyDrastea, "EnemyDrastea-1171");
				break;
			}
			case 38350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000765);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000777, EnemyEtis, "EnemyEtis-1172");
				break;
			}
			case 38400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000766);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000778, EnemyEtis, "EnemyEtis-1173");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001578);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001584, EnemyDrastea, "EnemyDrastea-1174");
				break;
			}
			case 38450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000767);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000779, EnemyEtis, "EnemyEtis-1175");
				break;
			}
			case 38500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000768);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000780, EnemyEtis, "EnemyEtis-1176");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001579);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001585, EnemyDrastea, "EnemyDrastea-1177");
				break;
			}
			case 38550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000769);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000781, EnemyEtis, "EnemyEtis-1178");
				break;
			}
			case 38600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000770);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000782, EnemyEtis, "EnemyEtis-1179");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001580);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001586, EnemyDrastea, "EnemyDrastea-1180");
				break;
			}
			case 38650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000771);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000783, EnemyEtis, "EnemyEtis-1181");
				break;
			}
			case 38700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000772);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000784, EnemyEtis, "EnemyEtis-1182");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001581);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001587, EnemyDrastea, "EnemyDrastea-1183");
				break;
			}
			case 38750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000773);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000785, EnemyEtis, "EnemyEtis-1184");
				break;
			}
			case 38800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000774);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000786, EnemyEtis, "EnemyEtis-1185");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001582);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001588, EnemyDrastea, "EnemyDrastea-1186");
				break;
			}
			case 38850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000775);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000787, EnemyEtis, "EnemyEtis-1187");
				break;
			}
			case 38900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000776);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000788, EnemyEtis, "EnemyEtis-1188");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001583);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001589, EnemyDrastea, "EnemyDrastea-1189");
				break;
			}
			case 38950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000777);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000789, EnemyEtis, "EnemyEtis-1190");
				break;
			}
			case 39000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000778);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000790, EnemyEtis, "EnemyEtis-1191");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001584);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001590, EnemyDrastea, "EnemyDrastea-1192");
				break;
			}
			case 39050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000779);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000791, EnemyEtis, "EnemyEtis-1193");
				break;
			}
			case 39100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000780);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000792, EnemyEtis, "EnemyEtis-1194");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001585);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001591, EnemyDrastea, "EnemyDrastea-1195");
				break;
			}
			case 39150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000781);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000793, EnemyEtis, "EnemyEtis-1196");
				break;
			}
			case 39200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000782);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000794, EnemyEtis, "EnemyEtis-1197");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001586);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001592, EnemyDrastea, "EnemyDrastea-1198");
				break;
			}
			case 39250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000783);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000795, EnemyEtis, "EnemyEtis-1199");
				break;
			}
			case 39300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000784);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000796, EnemyEtis, "EnemyEtis-1200");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001587);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001593, EnemyDrastea, "EnemyDrastea-1201");
				break;
			}
			case 39350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000785);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000797, EnemyEtis, "EnemyEtis-1202");
				break;
			}
			case 39400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000786);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000798, EnemyEtis, "EnemyEtis-1203");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001588);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001594, EnemyDrastea, "EnemyDrastea-1204");
				break;
			}
			case 39450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000787);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000799, EnemyEtis, "EnemyEtis-1205");
				break;
			}
			case 39500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000788);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000800, EnemyEtis, "EnemyEtis-1206");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001589);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001595, EnemyDrastea, "EnemyDrastea-1207");
				break;
			}
			case 39550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000789);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000801, EnemyEtis, "EnemyEtis-1208");
				break;
			}
			case 39600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000790);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000802, EnemyEtis, "EnemyEtis-1209");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001590);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001596, EnemyDrastea, "EnemyDrastea-1210");
				break;
			}
			case 39650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000791);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000803, EnemyEtis, "EnemyEtis-1211");
				break;
			}
			case 39700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000792);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000804, EnemyEtis, "EnemyEtis-1212");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001591);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001597, EnemyDrastea, "EnemyDrastea-1213");
				break;
			}
			case 39750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000793);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000805, EnemyEtis, "EnemyEtis-1214");
				break;
			}
			case 39800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000794);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000806, EnemyEtis, "EnemyEtis-1215");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001592);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001598, EnemyDrastea, "EnemyDrastea-1216");
				break;
			}
			case 39850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000795);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000807, EnemyEtis, "EnemyEtis-1217");
				break;
			}
			case 39900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000796);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000808, EnemyEtis, "EnemyEtis-1218");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001593);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001599, EnemyDrastea, "EnemyDrastea-1219");
				break;
			}
			case 39950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000797);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000809, EnemyEtis, "EnemyEtis-1220");
				break;
			}
			case 40000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000798);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000810, EnemyEtis, "EnemyEtis-1221");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001594);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001600, EnemyDrastea, "EnemyDrastea-1222");
				break;
			}
			case 40050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000799);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000811, EnemyEtis, "EnemyEtis-1223");
				break;
			}
			case 40100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000800);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000812, EnemyEtis, "EnemyEtis-1224");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001595);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001601, EnemyDrastea, "EnemyDrastea-1225");
				break;
			}
			case 40150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000801);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000813, EnemyEtis, "EnemyEtis-1226");
				break;
			}
			case 40200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000802);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000814, EnemyEtis, "EnemyEtis-1227");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001596);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001602, EnemyDrastea, "EnemyDrastea-1228");
				break;
			}
			case 40250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000803);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000815, EnemyEtis, "EnemyEtis-1229");
				break;
			}
			case 40300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000804);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000816, EnemyEtis, "EnemyEtis-1230");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001597);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001603, EnemyDrastea, "EnemyDrastea-1231");
				break;
			}
			case 40350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000805);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000817, EnemyEtis, "EnemyEtis-1232");
				break;
			}
			case 40400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000806);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000818, EnemyEtis, "EnemyEtis-1233");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001598);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001604, EnemyDrastea, "EnemyDrastea-1234");
				break;
			}
			case 40450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000807);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000819, EnemyEtis, "EnemyEtis-1235");
				break;
			}
			case 40500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000808);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000820, EnemyEtis, "EnemyEtis-1236");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001599);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001605, EnemyDrastea, "EnemyDrastea-1237");
				break;
			}
			case 40550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000809);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000821, EnemyEtis, "EnemyEtis-1238");
				break;
			}
			case 40600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000810);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000822, EnemyEtis, "EnemyEtis-1239");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001600);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001606, EnemyDrastea, "EnemyDrastea-1240");
				break;
			}
			case 40650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000811);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000823, EnemyEtis, "EnemyEtis-1241");
				break;
			}
			case 40700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000812);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000824, EnemyEtis, "EnemyEtis-1242");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001601);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001607, EnemyDrastea, "EnemyDrastea-1243");
				break;
			}
			case 40750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000813);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000825, EnemyEtis, "EnemyEtis-1244");
				break;
			}
			case 40800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000814);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000826, EnemyEtis, "EnemyEtis-1245");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001602);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001608, EnemyDrastea, "EnemyDrastea-1246");
				break;
			}
			case 40850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000815);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000827, EnemyEtis, "EnemyEtis-1247");
				break;
			}
			case 40900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000816);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000828, EnemyEtis, "EnemyEtis-1248");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001603);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001609, EnemyDrastea, "EnemyDrastea-1249");
				break;
			}
			case 40950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000817);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000829, EnemyEtis, "EnemyEtis-1250");
				break;
			}
			case 41000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000818);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000830, EnemyEtis, "EnemyEtis-1251");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001604);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001610, EnemyDrastea, "EnemyDrastea-1252");
				break;
			}
			case 41050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000819);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000831, EnemyEtis, "EnemyEtis-1253");
				break;
			}
			case 41100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000820);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000832, EnemyEtis, "EnemyEtis-1254");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001605);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001611, EnemyDrastea, "EnemyDrastea-1255");
				break;
			}
			case 41150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000821);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000833, EnemyEtis, "EnemyEtis-1256");
				break;
			}
			case 41200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000822);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000834, EnemyEtis, "EnemyEtis-1257");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001606);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001612, EnemyDrastea, "EnemyDrastea-1258");
				break;
			}
			case 41250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000823);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000835, EnemyEtis, "EnemyEtis-1259");
				break;
			}
			case 41300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000824);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000836, EnemyEtis, "EnemyEtis-1260");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001607);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001613, EnemyDrastea, "EnemyDrastea-1261");
				break;
			}
			case 41350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000825);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000837, EnemyEtis, "EnemyEtis-1262");
				break;
			}
			case 41400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000826);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000838, EnemyEtis, "EnemyEtis-1263");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001608);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001614, EnemyDrastea, "EnemyDrastea-1264");
				break;
			}
			case 41450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000827);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000839, EnemyEtis, "EnemyEtis-1265");
				break;
			}
			case 41500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000828);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000840, EnemyEtis, "EnemyEtis-1266");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001609);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001615, EnemyDrastea, "EnemyDrastea-1267");
				break;
			}
			case 41550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000829);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000841, EnemyEtis, "EnemyEtis-1268");
				break;
			}
			case 41600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000830);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000842, EnemyEtis, "EnemyEtis-1269");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001610);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001616, EnemyDrastea, "EnemyDrastea-1270");
				break;
			}
			case 41650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000831);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000843, EnemyEtis, "EnemyEtis-1271");
				break;
			}
			case 41700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000832);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000844, EnemyEtis, "EnemyEtis-1272");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001611);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001617, EnemyDrastea, "EnemyDrastea-1273");
				break;
			}
			case 41750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000833);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000845, EnemyEtis, "EnemyEtis-1274");
				break;
			}
			case 41800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000834);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000846, EnemyEtis, "EnemyEtis-1275");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001612);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001618, EnemyDrastea, "EnemyDrastea-1276");
				break;
			}
			case 41850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000835);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000847, EnemyEtis, "EnemyEtis-1277");
				break;
			}
			case 41900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000836);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000848, EnemyEtis, "EnemyEtis-1278");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001613);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001619, EnemyDrastea, "EnemyDrastea-1279");
				break;
			}
			case 41950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000837);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000849, EnemyEtis, "EnemyEtis-1280");
				break;
			}
			case 42000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000838);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000850, EnemyEtis, "EnemyEtis-1281");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001614);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001620, EnemyDrastea, "EnemyDrastea-1282");
				break;
			}
			case 42050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000839);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000851, EnemyEtis, "EnemyEtis-1283");
				break;
			}
			case 42100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000840);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000852, EnemyEtis, "EnemyEtis-1284");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001615);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001621, EnemyDrastea, "EnemyDrastea-1285");
				break;
			}
			case 42150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000841);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000853, EnemyEtis, "EnemyEtis-1286");
				break;
			}
			case 42200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000842);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000854, EnemyEtis, "EnemyEtis-1287");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001616);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001622, EnemyDrastea, "EnemyDrastea-1288");
				break;
			}
			case 42250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000843);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000855, EnemyEtis, "EnemyEtis-1289");
				break;
			}
			case 42300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000844);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000856, EnemyEtis, "EnemyEtis-1290");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001617);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001623, EnemyDrastea, "EnemyDrastea-1291");
				break;
			}
			case 42350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000845);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000857, EnemyEtis, "EnemyEtis-1292");
				break;
			}
			case 42400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000846);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000858, EnemyEtis, "EnemyEtis-1293");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001618);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001624, EnemyDrastea, "EnemyDrastea-1294");
				break;
			}
			case 42450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000847);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000859, EnemyEtis, "EnemyEtis-1295");
				break;
			}
			case 42500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000848);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000860, EnemyEtis, "EnemyEtis-1296");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001619);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001625, EnemyDrastea, "EnemyDrastea-1297");
				break;
			}
			case 42550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000849);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000861, EnemyEtis, "EnemyEtis-1298");
				break;
			}
			case 42600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000850);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000862, EnemyEtis, "EnemyEtis-1299");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001620);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001626, EnemyDrastea, "EnemyDrastea-1300");
				break;
			}
			case 42650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000851);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000863, EnemyEtis, "EnemyEtis-1301");
				break;
			}
			case 42700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000852);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000864, EnemyEtis, "EnemyEtis-1302");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001621);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001627, EnemyDrastea, "EnemyDrastea-1303");
				break;
			}
			case 42750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000853);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000865, EnemyEtis, "EnemyEtis-1304");
				break;
			}
			case 42800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000854);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000866, EnemyEtis, "EnemyEtis-1305");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001622);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001628, EnemyDrastea, "EnemyDrastea-1306");
				break;
			}
			case 42850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000855);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000867, EnemyEtis, "EnemyEtis-1307");
				break;
			}
			case 42900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000856);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000868, EnemyEtis, "EnemyEtis-1308");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001623);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001629, EnemyDrastea, "EnemyDrastea-1309");
				break;
			}
			case 42950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000857);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000869, EnemyEtis, "EnemyEtis-1310");
				break;
			}
			case 43000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000858);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000870, EnemyEtis, "EnemyEtis-1311");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001624);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001630, EnemyDrastea, "EnemyDrastea-1312");
				break;
			}
			case 43050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000859);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000871, EnemyEtis, "EnemyEtis-1313");
				break;
			}
			case 43100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000860);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000872, EnemyEtis, "EnemyEtis-1314");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001625);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001631, EnemyDrastea, "EnemyDrastea-1315");
				break;
			}
			case 43150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000861);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000873, EnemyEtis, "EnemyEtis-1316");
				break;
			}
			case 43200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000862);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000874, EnemyEtis, "EnemyEtis-1317");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001626);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001632, EnemyDrastea, "EnemyDrastea-1318");
				break;
			}
			case 43250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000863);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000875, EnemyEtis, "EnemyEtis-1319");
				break;
			}
			case 43300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000864);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000876, EnemyEtis, "EnemyEtis-1320");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001627);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001633, EnemyDrastea, "EnemyDrastea-1321");
				break;
			}
			case 43350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000865);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000877, EnemyEtis, "EnemyEtis-1322");
				break;
			}
			case 43400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000866);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000878, EnemyEtis, "EnemyEtis-1323");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001628);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001634, EnemyDrastea, "EnemyDrastea-1324");
				break;
			}
			case 43450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000867);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000879, EnemyEtis, "EnemyEtis-1325");
				break;
			}
			case 43500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000868);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000880, EnemyEtis, "EnemyEtis-1326");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001629);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001635, EnemyDrastea, "EnemyDrastea-1327");
				break;
			}
			case 43550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000869);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000881, EnemyEtis, "EnemyEtis-1328");
				break;
			}
			case 43600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000870);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000882, EnemyEtis, "EnemyEtis-1329");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001630);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001636, EnemyDrastea, "EnemyDrastea-1330");
				break;
			}
			case 43650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000871);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000883, EnemyEtis, "EnemyEtis-1331");
				break;
			}
			case 43700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000872);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000884, EnemyEtis, "EnemyEtis-1332");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001631);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001637, EnemyDrastea, "EnemyDrastea-1333");
				break;
			}
			case 43750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000873);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000885, EnemyEtis, "EnemyEtis-1334");
				break;
			}
			case 43800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000874);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000886, EnemyEtis, "EnemyEtis-1335");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001632);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001638, EnemyDrastea, "EnemyDrastea-1336");
				break;
			}
			case 43850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000875);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000887, EnemyEtis, "EnemyEtis-1337");
				break;
			}
			case 43900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000876);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000888, EnemyEtis, "EnemyEtis-1338");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001633);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001639, EnemyDrastea, "EnemyDrastea-1339");
				break;
			}
			case 43950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000877);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000889, EnemyEtis, "EnemyEtis-1340");
				break;
			}
			case 44000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000878);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000890, EnemyEtis, "EnemyEtis-1341");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001634);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001640, EnemyDrastea, "EnemyDrastea-1342");
				break;
			}
			case 44050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000879);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000891, EnemyEtis, "EnemyEtis-1343");
				break;
			}
			case 44100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000880);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000892, EnemyEtis, "EnemyEtis-1344");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001635);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001641, EnemyDrastea, "EnemyDrastea-1345");
				break;
			}
			case 44150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000881);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000893, EnemyEtis, "EnemyEtis-1346");
				break;
			}
			case 44200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000882);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000894, EnemyEtis, "EnemyEtis-1347");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001636);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001642, EnemyDrastea, "EnemyDrastea-1348");
				break;
			}
			case 44250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000883);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000895, EnemyEtis, "EnemyEtis-1349");
				break;
			}
			case 44300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000884);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000896, EnemyEtis, "EnemyEtis-1350");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001637);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001643, EnemyDrastea, "EnemyDrastea-1351");
				break;
			}
			case 44350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000885);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000897, EnemyEtis, "EnemyEtis-1352");
				break;
			}
			case 44400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000886);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000898, EnemyEtis, "EnemyEtis-1353");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001638);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001644, EnemyDrastea, "EnemyDrastea-1354");
				break;
			}
			case 44450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000887);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000899, EnemyEtis, "EnemyEtis-1355");
				break;
			}
			case 44500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000888);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000900, EnemyEtis, "EnemyEtis-1356");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001639);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001645, EnemyDrastea, "EnemyDrastea-1357");
				break;
			}
			case 44550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000889);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000901, EnemyEtis, "EnemyEtis-1358");
				break;
			}
			case 44600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000890);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000902, EnemyEtis, "EnemyEtis-1359");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001640);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001646, EnemyDrastea, "EnemyDrastea-1360");
				break;
			}
			case 44650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000891);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000903, EnemyEtis, "EnemyEtis-1361");
				break;
			}
			case 44700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000892);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000904, EnemyEtis, "EnemyEtis-1362");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001641);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001647, EnemyDrastea, "EnemyDrastea-1363");
				break;
			}
			case 44750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000893);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000905, EnemyEtis, "EnemyEtis-1364");
				break;
			}
			case 44800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000894);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000906, EnemyEtis, "EnemyEtis-1365");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001642);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001648, EnemyDrastea, "EnemyDrastea-1366");
				break;
			}
			case 44850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000895);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000907, EnemyEtis, "EnemyEtis-1367");
				break;
			}
			case 44900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000896);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000908, EnemyEtis, "EnemyEtis-1368");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001643);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001649, EnemyDrastea, "EnemyDrastea-1369");
				break;
			}
			case 44950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000897);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000909, EnemyEtis, "EnemyEtis-1370");
				break;
			}
			case 45000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000898);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000910, EnemyEtis, "EnemyEtis-1371");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001644);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001650, EnemyDrastea, "EnemyDrastea-1372");
				break;
			}
			case 45050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000899);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000911, EnemyEtis, "EnemyEtis-1373");
				break;
			}
			case 45100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000900);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000912, EnemyEtis, "EnemyEtis-1374");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001645);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001651, EnemyDrastea, "EnemyDrastea-1375");
				break;
			}
			case 45150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000901);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000913, EnemyEtis, "EnemyEtis-1376");
				break;
			}
			case 45200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000902);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000914, EnemyEtis, "EnemyEtis-1377");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001646);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001652, EnemyDrastea, "EnemyDrastea-1378");
				break;
			}
			case 45250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000903);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000915, EnemyEtis, "EnemyEtis-1379");
				break;
			}
			case 45300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000904);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000916, EnemyEtis, "EnemyEtis-1380");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001647);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001653, EnemyDrastea, "EnemyDrastea-1381");
				break;
			}
			case 45350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000905);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000917, EnemyEtis, "EnemyEtis-1382");
				break;
			}
			case 45400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000906);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000918, EnemyEtis, "EnemyEtis-1383");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001648);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001654, EnemyDrastea, "EnemyDrastea-1384");
				break;
			}
			case 45450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000907);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000919, EnemyEtis, "EnemyEtis-1385");
				break;
			}
			case 45500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000908);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000920, EnemyEtis, "EnemyEtis-1386");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001649);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001655, EnemyDrastea, "EnemyDrastea-1387");
				break;
			}
			case 45550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000909);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000921, EnemyEtis, "EnemyEtis-1388");
				break;
			}
			case 45600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000910);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000922, EnemyEtis, "EnemyEtis-1389");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001650);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001656, EnemyDrastea, "EnemyDrastea-1390");
				break;
			}
			case 45650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000911);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000923, EnemyEtis, "EnemyEtis-1391");
				break;
			}
			case 45700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000912);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000924, EnemyEtis, "EnemyEtis-1392");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001651);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001657, EnemyDrastea, "EnemyDrastea-1393");
				break;
			}
			case 45750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000913);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000925, EnemyEtis, "EnemyEtis-1394");
				break;
			}
			case 45800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000914);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000926, EnemyEtis, "EnemyEtis-1395");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001652);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001658, EnemyDrastea, "EnemyDrastea-1396");
				break;
			}
			case 45850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000915);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000927, EnemyEtis, "EnemyEtis-1397");
				break;
			}
			case 45900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000916);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000928, EnemyEtis, "EnemyEtis-1398");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001653);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001659, EnemyDrastea, "EnemyDrastea-1399");
				break;
			}
			case 45950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000917);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000929, EnemyEtis, "EnemyEtis-1400");
				break;
			}
			case 46000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000918);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000930, EnemyEtis, "EnemyEtis-1401");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001654);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001660, EnemyDrastea, "EnemyDrastea-1402");
				break;
			}
			case 46050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000919);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000931, EnemyEtis, "EnemyEtis-1403");
				break;
			}
			case 46100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000920);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000932, EnemyEtis, "EnemyEtis-1404");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001655);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001661, EnemyDrastea, "EnemyDrastea-1405");
				break;
			}
			case 46150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000921);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000933, EnemyEtis, "EnemyEtis-1406");
				break;
			}
			case 46200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000922);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000934, EnemyEtis, "EnemyEtis-1407");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001656);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001662, EnemyDrastea, "EnemyDrastea-1408");
				break;
			}
			case 46250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000923);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000935, EnemyEtis, "EnemyEtis-1409");
				break;
			}
			case 46300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000924);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000936, EnemyEtis, "EnemyEtis-1410");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001657);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001663, EnemyDrastea, "EnemyDrastea-1411");
				break;
			}
			case 46350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000925);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000937, EnemyEtis, "EnemyEtis-1412");
				break;
			}
			case 46400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000926);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000938, EnemyEtis, "EnemyEtis-1413");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001658);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001664, EnemyDrastea, "EnemyDrastea-1414");
				break;
			}
			case 46450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000927);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000939, EnemyEtis, "EnemyEtis-1415");
				break;
			}
			case 46500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000928);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000940, EnemyEtis, "EnemyEtis-1416");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001659);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001665, EnemyDrastea, "EnemyDrastea-1417");
				break;
			}
			case 46550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000929);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000941, EnemyEtis, "EnemyEtis-1418");
				break;
			}
			case 46600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000930);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000942, EnemyEtis, "EnemyEtis-1419");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001660);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001666, EnemyDrastea, "EnemyDrastea-1420");
				break;
			}
			case 46650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000931);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000943, EnemyEtis, "EnemyEtis-1421");
				break;
			}
			case 46700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000932);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000944, EnemyEtis, "EnemyEtis-1422");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001661);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001667, EnemyDrastea, "EnemyDrastea-1423");
				break;
			}
			case 46750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000933);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000945, EnemyEtis, "EnemyEtis-1424");
				break;
			}
			case 46800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000934);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000946, EnemyEtis, "EnemyEtis-1425");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001662);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001668, EnemyDrastea, "EnemyDrastea-1426");
				break;
			}
			case 46850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000935);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000947, EnemyEtis, "EnemyEtis-1427");
				break;
			}
			case 46900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000936);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000948, EnemyEtis, "EnemyEtis-1428");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001663);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001669, EnemyDrastea, "EnemyDrastea-1429");
				break;
			}
			case 46950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000937);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000949, EnemyEtis, "EnemyEtis-1430");
				break;
			}
			case 47000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000938);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000950, EnemyEtis, "EnemyEtis-1431");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001664);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001670, EnemyDrastea, "EnemyDrastea-1432");
				break;
			}
			case 47050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000939);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000951, EnemyEtis, "EnemyEtis-1433");
				break;
			}
			case 47100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000940);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000952, EnemyEtis, "EnemyEtis-1434");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001665);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001671, EnemyDrastea, "EnemyDrastea-1435");
				break;
			}
			case 47150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000941);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000953, EnemyEtis, "EnemyEtis-1436");
				break;
			}
			case 47200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000942);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000954, EnemyEtis, "EnemyEtis-1437");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001666);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001672, EnemyDrastea, "EnemyDrastea-1438");
				break;
			}
			case 47250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000943);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000955, EnemyEtis, "EnemyEtis-1439");
				break;
			}
			case 47300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000944);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000956, EnemyEtis, "EnemyEtis-1440");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001667);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001673, EnemyDrastea, "EnemyDrastea-1441");
				break;
			}
			case 47350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000945);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000957, EnemyEtis, "EnemyEtis-1442");
				break;
			}
			case 47400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000946);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000958, EnemyEtis, "EnemyEtis-1443");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001668);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001674, EnemyDrastea, "EnemyDrastea-1444");
				break;
			}
			case 47450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000947);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000959, EnemyEtis, "EnemyEtis-1445");
				break;
			}
			case 47500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000948);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000960, EnemyEtis, "EnemyEtis-1446");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001669);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001675, EnemyDrastea, "EnemyDrastea-1447");
				break;
			}
			case 47550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000949);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000961, EnemyEtis, "EnemyEtis-1448");
				break;
			}
			case 47600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000950);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000962, EnemyEtis, "EnemyEtis-1449");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001670);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001676, EnemyDrastea, "EnemyDrastea-1450");
				break;
			}
			case 47650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000951);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000963, EnemyEtis, "EnemyEtis-1451");
				break;
			}
			case 47700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000952);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000964, EnemyEtis, "EnemyEtis-1452");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001671);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001677, EnemyDrastea, "EnemyDrastea-1453");
				break;
			}
			case 47750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000953);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000965, EnemyEtis, "EnemyEtis-1454");
				break;
			}
			case 47800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000954);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000966, EnemyEtis, "EnemyEtis-1455");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001672);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001678, EnemyDrastea, "EnemyDrastea-1456");
				break;
			}
			case 47850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000955);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000967, EnemyEtis, "EnemyEtis-1457");
				break;
			}
			case 47900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000956);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000968, EnemyEtis, "EnemyEtis-1458");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001673);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001679, EnemyDrastea, "EnemyDrastea-1459");
				break;
			}
			case 47950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000957);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000969, EnemyEtis, "EnemyEtis-1460");
				break;
			}
			case 48000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000958);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000970, EnemyEtis, "EnemyEtis-1461");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001674);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001680, EnemyDrastea, "EnemyDrastea-1462");
				break;
			}
			case 48050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000959);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000971, EnemyEtis, "EnemyEtis-1463");
				break;
			}
			case 48100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000960);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000972, EnemyEtis, "EnemyEtis-1464");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001675);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001681, EnemyDrastea, "EnemyDrastea-1465");
				break;
			}
			case 48150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000961);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000973, EnemyEtis, "EnemyEtis-1466");
				break;
			}
			case 48200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000962);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000974, EnemyEtis, "EnemyEtis-1467");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001676);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001682, EnemyDrastea, "EnemyDrastea-1468");
				break;
			}
			case 48250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000963);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000975, EnemyEtis, "EnemyEtis-1469");
				break;
			}
			case 48300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000964);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000976, EnemyEtis, "EnemyEtis-1470");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001677);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001683, EnemyDrastea, "EnemyDrastea-1471");
				break;
			}
			case 48350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000965);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000977, EnemyEtis, "EnemyEtis-1472");
				break;
			}
			case 48400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000966);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000978, EnemyEtis, "EnemyEtis-1473");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001678);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001684, EnemyDrastea, "EnemyDrastea-1474");
				break;
			}
			case 48450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000967);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000979, EnemyEtis, "EnemyEtis-1475");
				break;
			}
			case 48500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000968);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000980, EnemyEtis, "EnemyEtis-1476");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001679);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001685, EnemyDrastea, "EnemyDrastea-1477");
				break;
			}
			case 48550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000969);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000981, EnemyEtis, "EnemyEtis-1478");
				break;
			}
			case 48600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000970);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000982, EnemyEtis, "EnemyEtis-1479");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001680);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001686, EnemyDrastea, "EnemyDrastea-1480");
				break;
			}
			case 48650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000971);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000983, EnemyEtis, "EnemyEtis-1481");
				break;
			}
			case 48700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000972);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000984, EnemyEtis, "EnemyEtis-1482");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001681);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001687, EnemyDrastea, "EnemyDrastea-1483");
				break;
			}
			case 48750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000973);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000985, EnemyEtis, "EnemyEtis-1484");
				break;
			}
			case 48800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000974);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000986, EnemyEtis, "EnemyEtis-1485");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001682);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001688, EnemyDrastea, "EnemyDrastea-1486");
				break;
			}
			case 48850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000975);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000987, EnemyEtis, "EnemyEtis-1487");
				break;
			}
			case 48900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000976);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000988, EnemyEtis, "EnemyEtis-1488");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001683);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001689, EnemyDrastea, "EnemyDrastea-1489");
				break;
			}
			case 48950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000977);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000989, EnemyEtis, "EnemyEtis-1490");
				break;
			}
			case 49000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000978);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000990, EnemyEtis, "EnemyEtis-1491");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001684);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001690, EnemyDrastea, "EnemyDrastea-1492");
				break;
			}
			case 49050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000979);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000991, EnemyEtis, "EnemyEtis-1493");
				break;
			}
			case 49100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000980);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000992, EnemyEtis, "EnemyEtis-1494");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001685);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001691, EnemyDrastea, "EnemyDrastea-1495");
				break;
			}
			case 49150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000981);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000993, EnemyEtis, "EnemyEtis-1496");
				break;
			}
			case 49200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000982);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000994, EnemyEtis, "EnemyEtis-1497");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001686);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001692, EnemyDrastea, "EnemyDrastea-1498");
				break;
			}
			case 49250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000983);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000995, EnemyEtis, "EnemyEtis-1499");
				break;
			}
			case 49300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000984);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000996, EnemyEtis, "EnemyEtis-1500");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001687);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001693, EnemyDrastea, "EnemyDrastea-1501");
				break;
			}
			case 49350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000985);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000997, EnemyEtis, "EnemyEtis-1502");
				break;
			}
			case 49400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000986);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000998, EnemyEtis, "EnemyEtis-1503");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001688);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001694, EnemyDrastea, "EnemyDrastea-1504");
				break;
			}
			case 49450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000987);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000999, EnemyEtis, "EnemyEtis-1505");
				break;
			}
			case 49500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000988);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001000, EnemyEtis, "EnemyEtis-1506");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001689);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001695, EnemyDrastea, "EnemyDrastea-1507");
				break;
			}
			case 49550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000989);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001001, EnemyEtis, "EnemyEtis-1508");
				break;
			}
			case 49600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000990);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001002, EnemyEtis, "EnemyEtis-1509");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001690);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001696, EnemyDrastea, "EnemyDrastea-1510");
				break;
			}
			case 49650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000991);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001003, EnemyEtis, "EnemyEtis-1511");
				break;
			}
			case 49700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000992);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001004, EnemyEtis, "EnemyEtis-1512");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001691);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001697, EnemyDrastea, "EnemyDrastea-1513");
				break;
			}
			case 49750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000993);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001005, EnemyEtis, "EnemyEtis-1514");
				break;
			}
			case 49800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000994);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001006, EnemyEtis, "EnemyEtis-1515");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001692);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001698, EnemyDrastea, "EnemyDrastea-1516");
				break;
			}
			case 49850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000995);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001007, EnemyEtis, "EnemyEtis-1517");
				break;
			}
			case 49900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000996);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001008, EnemyEtis, "EnemyEtis-1518");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001693);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001699, EnemyDrastea, "EnemyDrastea-1519");
				break;
			}
			case 49950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000997);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001009, EnemyEtis, "EnemyEtis-1520");
				break;
			}
			case 50000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000998);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001010, EnemyEtis, "EnemyEtis-1521");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001694);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001700, EnemyDrastea, "EnemyDrastea-1522");
				break;
			}
			case 50050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000999);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001011, EnemyEtis, "EnemyEtis-1523");
				break;
			}
			case 50100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001000);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001012, EnemyEtis, "EnemyEtis-1524");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001695);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001701, EnemyDrastea, "EnemyDrastea-1525");
				break;
			}
			case 50150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001001);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001013, EnemyEtis, "EnemyEtis-1526");
				break;
			}
			case 50200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001002);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001014, EnemyEtis, "EnemyEtis-1527");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001696);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001702, EnemyDrastea, "EnemyDrastea-1528");
				break;
			}
			case 50250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001003);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001015, EnemyEtis, "EnemyEtis-1529");
				break;
			}
			case 50300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001004);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001016, EnemyEtis, "EnemyEtis-1530");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001697);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001703, EnemyDrastea, "EnemyDrastea-1531");
				break;
			}
			case 50350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001005);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001017, EnemyEtis, "EnemyEtis-1532");
				break;
			}
			case 50400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001006);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001018, EnemyEtis, "EnemyEtis-1533");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001698);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001704, EnemyDrastea, "EnemyDrastea-1534");
				break;
			}
			case 50450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001007);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001019, EnemyEtis, "EnemyEtis-1535");
				break;
			}
			case 50500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001008);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001020, EnemyEtis, "EnemyEtis-1536");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001699);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001705, EnemyDrastea, "EnemyDrastea-1537");
				break;
			}
			case 50550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001009);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001021, EnemyEtis, "EnemyEtis-1538");
				break;
			}
			case 50600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001010);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001022, EnemyEtis, "EnemyEtis-1539");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001700);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001706, EnemyDrastea, "EnemyDrastea-1540");
				break;
			}
			case 50650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001011);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001023, EnemyEtis, "EnemyEtis-1541");
				break;
			}
			case 50700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001012);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001024, EnemyEtis, "EnemyEtis-1542");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001701);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001707, EnemyDrastea, "EnemyDrastea-1543");
				break;
			}
			case 50750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001013);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001025, EnemyEtis, "EnemyEtis-1544");
				break;
			}
			case 50800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001014);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001026, EnemyEtis, "EnemyEtis-1545");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001702);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001708, EnemyDrastea, "EnemyDrastea-1546");
				break;
			}
			case 50850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001015);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001027, EnemyEtis, "EnemyEtis-1547");
				break;
			}
			case 50900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001016);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001028, EnemyEtis, "EnemyEtis-1548");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001703);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001709, EnemyDrastea, "EnemyDrastea-1549");
				break;
			}
			case 50950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001017);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001029, EnemyEtis, "EnemyEtis-1550");
				break;
			}
			case 51000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001018);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001030, EnemyEtis, "EnemyEtis-1551");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001704);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001710, EnemyDrastea, "EnemyDrastea-1552");
				break;
			}
			case 51050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001019);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001031, EnemyEtis, "EnemyEtis-1553");
				break;
			}
			case 51100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001020);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001032, EnemyEtis, "EnemyEtis-1554");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001705);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001711, EnemyDrastea, "EnemyDrastea-1555");
				break;
			}
			case 51150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001021);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001033, EnemyEtis, "EnemyEtis-1556");
				break;
			}
			case 51200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001022);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001034, EnemyEtis, "EnemyEtis-1557");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001706);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001712, EnemyDrastea, "EnemyDrastea-1558");
				break;
			}
			case 51250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001023);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001035, EnemyEtis, "EnemyEtis-1559");
				break;
			}
			case 51300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001024);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001036, EnemyEtis, "EnemyEtis-1560");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001707);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001713, EnemyDrastea, "EnemyDrastea-1561");
				break;
			}
			case 51350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001025);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001037, EnemyEtis, "EnemyEtis-1562");
				break;
			}
			case 51400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001026);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001038, EnemyEtis, "EnemyEtis-1563");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001708);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001714, EnemyDrastea, "EnemyDrastea-1564");
				break;
			}
			case 51450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001027);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001039, EnemyEtis, "EnemyEtis-1565");
				break;
			}
			case 51500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001028);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001040, EnemyEtis, "EnemyEtis-1566");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001709);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001715, EnemyDrastea, "EnemyDrastea-1567");
				break;
			}
			case 51550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001029);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001041, EnemyEtis, "EnemyEtis-1568");
				break;
			}
			case 51600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001030);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001042, EnemyEtis, "EnemyEtis-1569");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001710);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001716, EnemyDrastea, "EnemyDrastea-1570");
				break;
			}
			case 51650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001031);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001043, EnemyEtis, "EnemyEtis-1571");
				break;
			}
			case 51700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001032);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001044, EnemyEtis, "EnemyEtis-1572");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001711);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001717, EnemyDrastea, "EnemyDrastea-1573");
				break;
			}
			case 51750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001033);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001045, EnemyEtis, "EnemyEtis-1574");
				break;
			}
			case 51800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001034);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001046, EnemyEtis, "EnemyEtis-1575");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001712);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001718, EnemyDrastea, "EnemyDrastea-1576");
				break;
			}
			case 51850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001035);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001047, EnemyEtis, "EnemyEtis-1577");
				break;
			}
			case 51900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001036);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001048, EnemyEtis, "EnemyEtis-1578");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001713);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001719, EnemyDrastea, "EnemyDrastea-1579");
				break;
			}
			case 51950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001037);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001049, EnemyEtis, "EnemyEtis-1580");
				break;
			}
			case 52000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001038);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001050, EnemyEtis, "EnemyEtis-1581");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001714);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001720, EnemyDrastea, "EnemyDrastea-1582");
				break;
			}
			case 52050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001039);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001051, EnemyEtis, "EnemyEtis-1583");
				break;
			}
			case 52100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001040);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001052, EnemyEtis, "EnemyEtis-1584");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001715);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001721, EnemyDrastea, "EnemyDrastea-1585");
				break;
			}
			case 52150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001041);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001053, EnemyEtis, "EnemyEtis-1586");
				break;
			}
			case 52200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001042);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001054, EnemyEtis, "EnemyEtis-1587");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001716);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001722, EnemyDrastea, "EnemyDrastea-1588");
				break;
			}
			case 52250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001043);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001055, EnemyEtis, "EnemyEtis-1589");
				break;
			}
			case 52300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001044);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001056, EnemyEtis, "EnemyEtis-1590");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001717);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001723, EnemyDrastea, "EnemyDrastea-1591");
				break;
			}
			case 52350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001045);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001057, EnemyEtis, "EnemyEtis-1592");
				break;
			}
			case 52400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001046);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001058, EnemyEtis, "EnemyEtis-1593");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001718);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001724, EnemyDrastea, "EnemyDrastea-1594");
				break;
			}
			case 52450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001047);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001059, EnemyEtis, "EnemyEtis-1595");
				break;
			}
			case 52500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001048);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001060, EnemyEtis, "EnemyEtis-1596");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001719);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001725, EnemyDrastea, "EnemyDrastea-1597");
				break;
			}
			case 52550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001049);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001061, EnemyEtis, "EnemyEtis-1598");
				break;
			}
			case 52600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001050);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001062, EnemyEtis, "EnemyEtis-1599");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001720);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001726, EnemyDrastea, "EnemyDrastea-1600");
				break;
			}
			case 52650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001051);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001063, EnemyEtis, "EnemyEtis-1601");
				break;
			}
			case 52700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001052);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001064, EnemyEtis, "EnemyEtis-1602");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001721);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001727, EnemyDrastea, "EnemyDrastea-1603");
				break;
			}
			case 52750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001053);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001065, EnemyEtis, "EnemyEtis-1604");
				break;
			}
			case 52800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001054);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001066, EnemyEtis, "EnemyEtis-1605");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001722);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001728, EnemyDrastea, "EnemyDrastea-1606");
				break;
			}
			case 52850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001055);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001067, EnemyEtis, "EnemyEtis-1607");
				break;
			}
			case 52900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001056);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001068, EnemyEtis, "EnemyEtis-1608");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001723);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001729, EnemyDrastea, "EnemyDrastea-1609");
				break;
			}
			case 52950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001057);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001069, EnemyEtis, "EnemyEtis-1610");
				break;
			}
			case 53000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001058);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001070, EnemyEtis, "EnemyEtis-1611");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001724);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001730, EnemyDrastea, "EnemyDrastea-1612");
				break;
			}
			case 53050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001059);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001071, EnemyEtis, "EnemyEtis-1613");
				break;
			}
			case 53100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001060);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001072, EnemyEtis, "EnemyEtis-1614");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001725);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001731, EnemyDrastea, "EnemyDrastea-1615");
				break;
			}
			case 53150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001061);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001073, EnemyEtis, "EnemyEtis-1616");
				break;
			}
			case 53200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001062);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001074, EnemyEtis, "EnemyEtis-1617");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001726);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001732, EnemyDrastea, "EnemyDrastea-1618");
				break;
			}
			case 53250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001063);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001075, EnemyEtis, "EnemyEtis-1619");
				break;
			}
			case 53300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001064);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001076, EnemyEtis, "EnemyEtis-1620");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001727);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001733, EnemyDrastea, "EnemyDrastea-1621");
				break;
			}
			case 53350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001065);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001077, EnemyEtis, "EnemyEtis-1622");
				break;
			}
			case 53400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001066);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001078, EnemyEtis, "EnemyEtis-1623");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001728);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001734, EnemyDrastea, "EnemyDrastea-1624");
				break;
			}
			case 53450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001067);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001079, EnemyEtis, "EnemyEtis-1625");
				break;
			}
			case 53500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001068);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001080, EnemyEtis, "EnemyEtis-1626");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001729);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001735, EnemyDrastea, "EnemyDrastea-1627");
				break;
			}
			case 53550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001069);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001081, EnemyEtis, "EnemyEtis-1628");
				break;
			}
			case 53600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001070);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001082, EnemyEtis, "EnemyEtis-1629");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001730);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001736, EnemyDrastea, "EnemyDrastea-1630");
				break;
			}
			case 53650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001071);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001083, EnemyEtis, "EnemyEtis-1631");
				break;
			}
			case 53700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001072);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001084, EnemyEtis, "EnemyEtis-1632");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001731);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001737, EnemyDrastea, "EnemyDrastea-1633");
				break;
			}
			case 53750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001073);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001085, EnemyEtis, "EnemyEtis-1634");
				break;
			}
			case 53800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001074);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001086, EnemyEtis, "EnemyEtis-1635");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001732);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001738, EnemyDrastea, "EnemyDrastea-1636");
				break;
			}
			case 53850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001075);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001087, EnemyEtis, "EnemyEtis-1637");
				break;
			}
			case 53900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001076);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001088, EnemyEtis, "EnemyEtis-1638");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001733);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001739, EnemyDrastea, "EnemyDrastea-1639");
				break;
			}
			case 53950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001077);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001089, EnemyEtis, "EnemyEtis-1640");
				break;
			}
			case 54000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001078);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001090, EnemyEtis, "EnemyEtis-1641");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001734);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001740, EnemyDrastea, "EnemyDrastea-1642");
				break;
			}
			case 54050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001079);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001091, EnemyEtis, "EnemyEtis-1643");
				break;
			}
			case 54100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001080);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001092, EnemyEtis, "EnemyEtis-1644");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001735);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001741, EnemyDrastea, "EnemyDrastea-1645");
				break;
			}
			case 54150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001081);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001093, EnemyEtis, "EnemyEtis-1646");
				break;
			}
			case 54200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001082);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001094, EnemyEtis, "EnemyEtis-1647");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001736);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001742, EnemyDrastea, "EnemyDrastea-1648");
				break;
			}
			case 54250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001083);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001095, EnemyEtis, "EnemyEtis-1649");
				break;
			}
			case 54300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001084);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001096, EnemyEtis, "EnemyEtis-1650");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001737);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001743, EnemyDrastea, "EnemyDrastea-1651");
				break;
			}
			case 54350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001085);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001097, EnemyEtis, "EnemyEtis-1652");
				break;
			}
			case 54400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001086);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001098, EnemyEtis, "EnemyEtis-1653");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001738);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001744, EnemyDrastea, "EnemyDrastea-1654");
				break;
			}
			case 54450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001087);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001099, EnemyEtis, "EnemyEtis-1655");
				break;
			}
			case 54500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001088);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001100, EnemyEtis, "EnemyEtis-1656");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001739);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001745, EnemyDrastea, "EnemyDrastea-1657");
				break;
			}
			case 54550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001089);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001101, EnemyEtis, "EnemyEtis-1658");
				break;
			}
			case 54600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001090);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001102, EnemyEtis, "EnemyEtis-1659");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001740);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001746, EnemyDrastea, "EnemyDrastea-1660");
				break;
			}
			case 54650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001091);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001103, EnemyEtis, "EnemyEtis-1661");
				break;
			}
			case 54700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001092);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001104, EnemyEtis, "EnemyEtis-1662");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001741);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001747, EnemyDrastea, "EnemyDrastea-1663");
				break;
			}
			case 54750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001093);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001105, EnemyEtis, "EnemyEtis-1664");
				break;
			}
			case 54800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001094);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001106, EnemyEtis, "EnemyEtis-1665");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001742);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001748, EnemyDrastea, "EnemyDrastea-1666");
				break;
			}
			case 54850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001095);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001107, EnemyEtis, "EnemyEtis-1667");
				break;
			}
			case 54900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001096);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001108, EnemyEtis, "EnemyEtis-1668");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001743);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001749, EnemyDrastea, "EnemyDrastea-1669");
				break;
			}
			case 54950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001097);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001109, EnemyEtis, "EnemyEtis-1670");
				break;
			}
			case 55000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001098);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001110, EnemyEtis, "EnemyEtis-1671");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001744);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001750, EnemyDrastea, "EnemyDrastea-1672");
				break;
			}
			case 55050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001099);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001111, EnemyEtis, "EnemyEtis-1673");
				break;
			}
			case 55100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001100);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001112, EnemyEtis, "EnemyEtis-1674");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001745);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001751, EnemyDrastea, "EnemyDrastea-1675");
				break;
			}
			case 55150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001101);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001113, EnemyEtis, "EnemyEtis-1676");
				break;
			}
			case 55200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001102);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001114, EnemyEtis, "EnemyEtis-1677");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001746);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001752, EnemyDrastea, "EnemyDrastea-1678");
				break;
			}
			case 55250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001103);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001115, EnemyEtis, "EnemyEtis-1679");
				break;
			}
			case 55300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001104);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001116, EnemyEtis, "EnemyEtis-1680");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001747);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001753, EnemyDrastea, "EnemyDrastea-1681");
				break;
			}
			case 55350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001105);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001117, EnemyEtis, "EnemyEtis-1682");
				break;
			}
			case 55400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001106);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001118, EnemyEtis, "EnemyEtis-1683");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001748);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001754, EnemyDrastea, "EnemyDrastea-1684");
				break;
			}
			case 55450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001107);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001119, EnemyEtis, "EnemyEtis-1685");
				break;
			}
			case 55500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001108);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001120, EnemyEtis, "EnemyEtis-1686");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001749);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001755, EnemyDrastea, "EnemyDrastea-1687");
				break;
			}
			case 55550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001109);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001121, EnemyEtis, "EnemyEtis-1688");
				break;
			}
			case 55600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001110);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001122, EnemyEtis, "EnemyEtis-1689");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001750);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001756, EnemyDrastea, "EnemyDrastea-1690");
				break;
			}
			case 55650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001111);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001123, EnemyEtis, "EnemyEtis-1691");
				break;
			}
			case 55700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001112);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001124, EnemyEtis, "EnemyEtis-1692");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001751);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001757, EnemyDrastea, "EnemyDrastea-1693");
				break;
			}
			case 55750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001113);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001125, EnemyEtis, "EnemyEtis-1694");
				break;
			}
			case 55800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001114);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001126, EnemyEtis, "EnemyEtis-1695");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001752);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001758, EnemyDrastea, "EnemyDrastea-1696");
				break;
			}
			case 55850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001115);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001127, EnemyEtis, "EnemyEtis-1697");
				break;
			}
			case 55900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001116);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001128, EnemyEtis, "EnemyEtis-1698");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001753);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001759, EnemyDrastea, "EnemyDrastea-1699");
				break;
			}
			case 55950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001117);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001129, EnemyEtis, "EnemyEtis-1700");
				break;
			}
			case 56000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001118);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001130, EnemyEtis, "EnemyEtis-1701");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001754);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001760, EnemyDrastea, "EnemyDrastea-1702");
				break;
			}
			case 56050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001119);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001131, EnemyEtis, "EnemyEtis-1703");
				break;
			}
			case 56100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001120);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001132, EnemyEtis, "EnemyEtis-1704");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001755);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001761, EnemyDrastea, "EnemyDrastea-1705");
				break;
			}
			case 56150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001121);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001133, EnemyEtis, "EnemyEtis-1706");
				break;
			}
			case 56200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001122);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001134, EnemyEtis, "EnemyEtis-1707");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001756);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001762, EnemyDrastea, "EnemyDrastea-1708");
				break;
			}
			case 56250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001123);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001135, EnemyEtis, "EnemyEtis-1709");
				break;
			}
			case 56300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001124);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001136, EnemyEtis, "EnemyEtis-1710");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001757);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001763, EnemyDrastea, "EnemyDrastea-1711");
				break;
			}
			case 56350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001125);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001137, EnemyEtis, "EnemyEtis-1712");
				break;
			}
			case 56400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001126);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001138, EnemyEtis, "EnemyEtis-1713");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001758);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001764, EnemyDrastea, "EnemyDrastea-1714");
				break;
			}
			case 56450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001127);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001139, EnemyEtis, "EnemyEtis-1715");
				break;
			}
			case 56500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001128);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001140, EnemyEtis, "EnemyEtis-1716");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001759);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001765, EnemyDrastea, "EnemyDrastea-1717");
				break;
			}
			case 56550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001129);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001141, EnemyEtis, "EnemyEtis-1718");
				break;
			}
			case 56600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001130);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001142, EnemyEtis, "EnemyEtis-1719");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001760);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001766, EnemyDrastea, "EnemyDrastea-1720");
				break;
			}
			case 56650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001131);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001143, EnemyEtis, "EnemyEtis-1721");
				break;
			}
			case 56700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001132);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001144, EnemyEtis, "EnemyEtis-1722");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001761);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001767, EnemyDrastea, "EnemyDrastea-1723");
				break;
			}
			case 56750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001133);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001145, EnemyEtis, "EnemyEtis-1724");
				break;
			}
			case 56800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001134);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001146, EnemyEtis, "EnemyEtis-1725");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001762);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001768, EnemyDrastea, "EnemyDrastea-1726");
				break;
			}
			case 56850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001135);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001147, EnemyEtis, "EnemyEtis-1727");
				break;
			}
			case 56900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001136);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001148, EnemyEtis, "EnemyEtis-1728");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001763);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001769, EnemyDrastea, "EnemyDrastea-1729");
				break;
			}
			case 56950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001137);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001149, EnemyEtis, "EnemyEtis-1730");
				break;
			}
			case 57000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001138);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001150, EnemyEtis, "EnemyEtis-1731");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001764);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001770, EnemyDrastea, "EnemyDrastea-1732");
				break;
			}
			case 57050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001139);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001151, EnemyEtis, "EnemyEtis-1733");
				break;
			}
			case 57100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001140);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001152, EnemyEtis, "EnemyEtis-1734");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001765);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001771, EnemyDrastea, "EnemyDrastea-1735");
				break;
			}
			case 57150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001141);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001153, EnemyEtis, "EnemyEtis-1736");
				break;
			}
			case 57200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001142);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001154, EnemyEtis, "EnemyEtis-1737");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001766);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001772, EnemyDrastea, "EnemyDrastea-1738");
				break;
			}
			case 57250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001143);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001155, EnemyEtis, "EnemyEtis-1739");
				break;
			}
			case 57300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001144);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001156, EnemyEtis, "EnemyEtis-1740");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001767);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001773, EnemyDrastea, "EnemyDrastea-1741");
				break;
			}
			case 57350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001145);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001157, EnemyEtis, "EnemyEtis-1742");
				break;
			}
			case 57400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001146);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001158, EnemyEtis, "EnemyEtis-1743");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001768);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001774, EnemyDrastea, "EnemyDrastea-1744");
				break;
			}
			case 57450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001147);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001159, EnemyEtis, "EnemyEtis-1745");
				break;
			}
			case 57500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001148);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001160, EnemyEtis, "EnemyEtis-1746");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001769);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001775, EnemyDrastea, "EnemyDrastea-1747");
				break;
			}
			case 57550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001149);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001161, EnemyEtis, "EnemyEtis-1748");
				break;
			}
			case 57600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001150);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001162, EnemyEtis, "EnemyEtis-1749");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001770);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001776, EnemyDrastea, "EnemyDrastea-1750");
				break;
			}
			case 57650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001151);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001163, EnemyEtis, "EnemyEtis-1751");
				break;
			}
			case 57700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001152);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001164, EnemyEtis, "EnemyEtis-1752");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001771);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001777, EnemyDrastea, "EnemyDrastea-1753");
				break;
			}
			case 57750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001153);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001165, EnemyEtis, "EnemyEtis-1754");
				break;
			}
			case 57800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001154);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001166, EnemyEtis, "EnemyEtis-1755");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001772);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001778, EnemyDrastea, "EnemyDrastea-1756");
				break;
			}
			case 57850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001155);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001167, EnemyEtis, "EnemyEtis-1757");
				break;
			}
			case 57900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001156);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001168, EnemyEtis, "EnemyEtis-1758");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001773);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001779, EnemyDrastea, "EnemyDrastea-1759");
				break;
			}
			case 57950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001157);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001169, EnemyEtis, "EnemyEtis-1760");
				break;
			}
			case 58000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001158);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001170, EnemyEtis, "EnemyEtis-1761");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001774);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001780, EnemyDrastea, "EnemyDrastea-1762");
				break;
			}
			case 58050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001159);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001171, EnemyEtis, "EnemyEtis-1763");
				break;
			}
			case 58100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001160);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001172, EnemyEtis, "EnemyEtis-1764");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001775);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001781, EnemyDrastea, "EnemyDrastea-1765");
				break;
			}
			case 58150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001161);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001173, EnemyEtis, "EnemyEtis-1766");
				break;
			}
			case 58200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001162);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001174, EnemyEtis, "EnemyEtis-1767");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001776);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001782, EnemyDrastea, "EnemyDrastea-1768");
				break;
			}
			case 58250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001163);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001175, EnemyEtis, "EnemyEtis-1769");
				break;
			}
			case 58300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001164);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001176, EnemyEtis, "EnemyEtis-1770");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001777);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001783, EnemyDrastea, "EnemyDrastea-1771");
				break;
			}
			case 58350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001165);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001177, EnemyEtis, "EnemyEtis-1772");
				break;
			}
			case 58400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001166);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001178, EnemyEtis, "EnemyEtis-1773");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001778);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001784, EnemyDrastea, "EnemyDrastea-1774");
				break;
			}
			case 58450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001167);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001179, EnemyEtis, "EnemyEtis-1775");
				break;
			}
			case 58500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001168);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001180, EnemyEtis, "EnemyEtis-1776");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001779);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001785, EnemyDrastea, "EnemyDrastea-1777");
				break;
			}
			case 58550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001169);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001181, EnemyEtis, "EnemyEtis-1778");
				break;
			}
			case 58600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001170);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001182, EnemyEtis, "EnemyEtis-1779");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001780);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001786, EnemyDrastea, "EnemyDrastea-1780");
				break;
			}
			case 58650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001171);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001183, EnemyEtis, "EnemyEtis-1781");
				break;
			}
			case 58700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001172);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001184, EnemyEtis, "EnemyEtis-1782");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001781);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001787, EnemyDrastea, "EnemyDrastea-1783");
				break;
			}
			case 58750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001173);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001185, EnemyEtis, "EnemyEtis-1784");
				break;
			}
			case 58800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001174);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001186, EnemyEtis, "EnemyEtis-1785");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001782);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001788, EnemyDrastea, "EnemyDrastea-1786");
				break;
			}
			case 58850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001175);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001187, EnemyEtis, "EnemyEtis-1787");
				break;
			}
			case 58900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001176);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001188, EnemyEtis, "EnemyEtis-1788");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001783);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001789, EnemyDrastea, "EnemyDrastea-1789");
				break;
			}
			case 58950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001177);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001189, EnemyEtis, "EnemyEtis-1790");
				break;
			}
			case 59000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001178);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001190, EnemyEtis, "EnemyEtis-1791");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001784);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001790, EnemyDrastea, "EnemyDrastea-1792");
				break;
			}
			case 59050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001179);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001191, EnemyEtis, "EnemyEtis-1793");
				break;
			}
			case 59100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001180);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001192, EnemyEtis, "EnemyEtis-1794");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001785);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001791, EnemyDrastea, "EnemyDrastea-1795");
				break;
			}
			case 59150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001181);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001193, EnemyEtis, "EnemyEtis-1796");
				break;
			}
			case 59200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001182);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001194, EnemyEtis, "EnemyEtis-1797");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001786);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001792, EnemyDrastea, "EnemyDrastea-1798");
				break;
			}
			case 59250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001183);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001195, EnemyEtis, "EnemyEtis-1799");
				break;
			}
			case 59300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001184);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001196, EnemyEtis, "EnemyEtis-1800");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001787);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001793, EnemyDrastea, "EnemyDrastea-1801");
				break;
			}
			case 59350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001185);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001197, EnemyEtis, "EnemyEtis-1802");
				break;
			}
			case 59400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001186);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001198, EnemyEtis, "EnemyEtis-1803");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001788);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10001794, EnemyDrastea, "EnemyDrastea-1804");
				break;
			}
			case 59450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001187);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 59500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001188);
				bringDirector()->addSubGroup(pEtis);
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001789);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 59550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001189);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 59600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001190);
				bringDirector()->addSubGroup(pEtis);
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001790);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 59650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001191);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 59700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001192);
				bringDirector()->addSubGroup(pEtis);
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001791);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 59750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001193);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 59800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001194);
				bringDirector()->addSubGroup(pEtis);
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001792);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 59850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001195);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 59900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001196);
				bringDirector()->addSubGroup(pEtis);
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001793);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 59950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001197);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 60000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001198);
				bringDirector()->addSubGroup(pEtis);
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10001794);
				bringDirector()->addSubGroup(p);
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 1201-1 ? _cnt_event+1 : _cnt_event);
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
