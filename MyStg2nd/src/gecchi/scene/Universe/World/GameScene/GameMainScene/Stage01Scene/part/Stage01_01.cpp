#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Stage01_01::Stage01_01(const char* prm_name) : DefaultScene(prm_name) {
    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
	frame f[] = {1,100,300,600,800,1100,1200,1230,1260,1290,1300,1320,1350,1380,1410,1440,1470,1500,1530,1560,1590,1600,1620,1650,1680,1710,1740,1770,1800,1830,1860,1890,1920,1950,1980,2010,2040,2070,2100,2130,2160,2190,2220,2250,2280,2300,2310,2340,2370,2400,2430,2460,2490,2520,2550,2580,2600,2610,2640,2670,2700,2730,2760,2790,2800,2820,2850,2880,2910,2940,2970,3000,3030,3060,3090,3100,3120,3150,3180,3210,3240,3270,3300,3330,3360,3390,3420,3450,3480,3510,3540,3570,3600,3630,3660,3690,3720,3750,3780,3800,3810,3840,3870,3900,3930,3960,3990,4020,4050,4080,4100,4110,4140,4170,4200,4230,4260,4290,4300,4320,4350,4380,4410,4440,4470,4500,4530,4560,4590,4600,4620,4650,4680,4710,4740,4770,4800,4830,4860,4890,4920,4950,4980,5010,5040,5070,5100,5130,5160,5190,5220,5250,5280,5300,5310,5340,5370,5400,5430,5460,5490,5520,5550,5580,5600,5610,5640,5670,5700,5730,5760,5790,5800,5820,5850,5880,5910,5940,5970,6000,6030,6060,6090,6100,6120,6150,6180,6210,6240,6270,6300,6330,6360,6390,6420,6450,6480,6510,6540,6570,6600,6630,6660,6690,6720,6750,6780,6800,6810,6840,6870,6900,6930,6960,6990,7020,7050,7080,7100,7110,7140,7170,7200,7230,7260,7290,7300,7320,7350,7380,7410,7440,7470,7500,7530,7560,7590,7600,7620,7650,7680,7710,7740,7770,7800,7830,7860,7890,7920,7950,7980,8010,8040,8070,8100,8130,8160,8190,8220,8250,8280,8310,8340,8370,8400,8430,8460,8490,8520,8550,8580,8600,8610,8640,8670,8700,8730,8760,8790,8820,8850,8880,8910,8940,8970,9000,9030,9060,9090,9100,9120,9150,9180,9210,9240,9270,9300,9330,9360,9390,9420,9450,9480,9510,9540,9570,9600,9630,9660,9690,9720,9750,9780,9810,9840,9870,9900,9930,9960,9990,10020,10050,10080,10110,10140,10170,10200,10230,10260,10290,10320,10350,10380,10410,10440,10470,10500,10530,10560,10590,10620,10650,10680,10710,10740,10770,10800,10830,10860,10890,10920,10950,10980,11010,11040,11070,11100,11130,11160,11190,11220,11250,11280,11310,11340,11370,11400,11430,11460,11490,11520,11550,11580,11610,11640,11670,11700,11730,11760,11790,11820,11850,11880,11910,11940,11970,12000,12030,12060,12090,12120,12150,12180,12210,12240,12270,12300,12330,12360,12390,12420,12450,12480,12510,12540,12570,12600,12630,12660,12690,12720,12750,12780,12810,12840,12870,12900,12930,12960,12990,13020,13050,13080,13110,13140,13170,13200,13230,13260,13290,13320,13350,13380,13410,13440,13470,13500,13530,13560,13590,13620,13650,13680,13710,13740,13770,13800,13830,13860,13890,13920,13950,13980,14010,14040,14070,14100,14130,14160,14190,14220,14250,14280,14310,14340,14370,14400,14430,14460,14490,14520,14550,14580,14610,14640,14670,14700,14730,14760,14790,14820,14850,14880,14910,14940,14970,15000,15030,15060,15090,15120,15150,15180,15210,15240,15270,15300,15330,15360,15390,15420,15450,15480,15510,15540,15570,15600,15630,15660,15690,15720,15750,15780,15810,15840,15870,15900,15930,15960,15990,16020,16050,16080,16110,16140,16170,16200,16230,16260,16290,16320,16350,16380,16410,16440,16470,16500,16530,16560,16590,16620,16650,16680,16710,16740,16770,16800,16830,16860,16890,16920,16950,16980,17010,17040,17070,17100,17130,17160,17190,17220,17250,17280,17310,17340,17370,17400,17430,17460,17490,17520,17550,17580,17610,17640,17670,17700,17730,17760,17790,17820,17850,17880,17910,17940,17970,18000,18030,18060,18090,18120,18150,18180,18210,18240,18270,18300,18330,18360,18390,18420,18450,18480,18510,18540,18570,18600,18630,18660,18690,18720,18750,18780,18810,18840,18870,18900,18930,18960,18990,19020,19050,19080,19110,19140,19170,19200,19230,19260,19290,19320,19350,19380,19410,19440,19470,19500,19530,19560,19590,19620,19650,19680,19710,19740,19770,19800,19830,19860,19890,19920,19950,19980,20010,20040,20070,20100,20130,20160,20190,20220,20250,20280,20310,20340,20370,20400,20430,20460,20490,20520,20550,20580,20610,20640,20670,20700,20730,20760,20790,20820,20850,20880,20910,20940,20970,21000,21030,21060,21090,21120,21150,21180,21210,21240,21270,21300,21330,21360,21390,21420,21450,21480,21510,21540,21570,21600,21630,21660,21690,21720,21750,21780,21810,21840,21870,21900,21930,21960,21990,22020,22050,22080,22110,22140,22170,22200,22230,22260,22290,22320,22350,22380,22410,22440,22470,22500,22530,22560,22590,22620,22650,22680,22710,22740,22770,22800,22830,22860,22890,22920,22950,22980,23010,23040,23070,23100,23130,23160,23190,23220,23250,23280,23310,23340,23370,23400,23430,23460,23490,23520,23550,23580,23610,23640,23670,23700,23730,23760,23790,23820,23850,23880,23910,23940,23970,24000,24030,24060,24090,24120,24150,24180,24210,24240,24270,24300,24330,24360,24390,24420,24450,24480,24510,24540,24570,24600,24630,24660,24690,24720,24750,24780,24810,24840,24870,24900,24930,24960,24990,25020,25050,25080,25110,25140,25170,25200,25230,25260,25290,25320,25350,25380,25410,25440,25470,25500,25530,25560,25590,25620,25650,25680,25710,25740,25770,25800,25830,25860,25890,25920,25950,25980,26010,26040,26070,26100,26130,26160,26190,26220,26250,26280,26310,26340,26370,26400,26430,26460,26490,26520,26550,26580,26610,26640,26670,26700,26730,26760,26790,26820,26850,26880,26910,26940,26970,27000,27030,27060,27090,27120,27150,27180,27210,27240,27270,27300,27330,27360,27390,27420,27450,27480,27510,27540,27570,27600,27630,27660,27690,27720,27750,27780,27810,27840,27870,27900,27930,27960,27990,28020,28050,28080,28110,28140,28170,28200,28230,28260,28290,28320,28350,28380,28410,28440,28470,28500,28530,28560,28590,28620,28650,28680,28710,28740,28770,28800,28830,28860,28890,28920,28950,28980,29010,29040,29070,29100,29130,29160,29190,29220,29250,29280,29310,29340,29370,29400,29430,29460,29490,29520,29550,29580,29610,29640,29670,29700,29730,29760,29790,29820,29850,29880,29910,29940,29970,30000};
	_paFrame_NextEvent = new frame[987];
	for (int i = 0; i < 987; i++) {
		_paFrame_NextEvent[i] = f[i];
	}
	orderActorToFactory(21037100, FormationThalia, "FormationThalia_1");
	orderActorToFactory(21037600, FormationThalia, "FormationThalia_2");
	orderActorToFactory(210371100, FormationThalia, "FormationThalia_3");
	orderActorToFactory(210371600, FormationThalia, "FormationThalia_4");
    // gen01 end
}

void Stage01_01::initialize() {

}

void Stage01_01::processBehavior() {
    // 以下の gen02 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen02 start
	if (getActivePartFrame() == _paFrame_NextEvent[_iCnt_Event]) {
		switch (getActivePartFrame()) {
			case 1:
				break;
			case 100:
				{
				FormationThalia* pActor = (FormationThalia*)obtainActorFromFactory(21037100);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 300:
				orderActorToFactory(210372100, FormationThalia, "FormationThalia_5");
				break;
			case 600:
				{
				FormationThalia* pActor = (FormationThalia*)obtainActorFromFactory(21037600);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 800:
				orderActorToFactory(210372600, FormationThalia, "FormationThalia_6");
				break;
			case 1100:
				{
				FormationThalia* pActor = (FormationThalia*)obtainActorFromFactory(210371100);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 1200:
				orderActorToFactory(211773000, EnemyMetis, "Metis_7");
				break;
			case 1230:
				orderActorToFactory(211773030, EnemyMetis, "Metis_8");
				break;
			case 1260:
				orderActorToFactory(211773060, EnemyMetis, "Metis_9");
				break;
			case 1290:
				orderActorToFactory(211773090, EnemyMetis, "Metis_10");
				break;
			case 1300:
				orderActorToFactory(210373100, FormationThalia, "FormationThalia_11");
				break;
			case 1320:
				orderActorToFactory(211773120, EnemyMetis, "Metis_12");
				break;
			case 1350:
				orderActorToFactory(211773150, EnemyMetis, "Metis_13");
				break;
			case 1380:
				orderActorToFactory(211773180, EnemyMetis, "Metis_14");
				break;
			case 1410:
				orderActorToFactory(211773210, EnemyMetis, "Metis_15");
				break;
			case 1440:
				orderActorToFactory(211773240, EnemyMetis, "Metis_16");
				break;
			case 1470:
				orderActorToFactory(211773270, EnemyMetis, "Metis_17");
				break;
			case 1500:
				orderActorToFactory(211773300, EnemyMetis, "Metis_18");
				break;
			case 1530:
				orderActorToFactory(211773330, EnemyMetis, "Metis_19");
				break;
			case 1560:
				orderActorToFactory(211773360, EnemyMetis, "Metis_20");
				break;
			case 1590:
				orderActorToFactory(211773390, EnemyMetis, "Metis_21");
				break;
			case 1600:
				{
				FormationThalia* pActor = (FormationThalia*)obtainActorFromFactory(210371600);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 1620:
				orderActorToFactory(211773420, EnemyMetis, "Metis_22");
				break;
			case 1650:
				orderActorToFactory(211773450, EnemyMetis, "Metis_23");
				break;
			case 1680:
				orderActorToFactory(211773480, EnemyMetis, "Metis_24");
				break;
			case 1710:
				orderActorToFactory(211773510, EnemyMetis, "Metis_25");
				break;
			case 1740:
				orderActorToFactory(211773540, EnemyMetis, "Metis_26");
				break;
			case 1770:
				orderActorToFactory(211773570, EnemyMetis, "Metis_27");
				break;
			case 1800:
				orderActorToFactory(210373600, FormationThalia, "FormationThalia_28");
				orderActorToFactory(211773600, EnemyMetis, "Metis_29");
				break;
			case 1830:
				orderActorToFactory(211773630, EnemyMetis, "Metis_30");
				break;
			case 1860:
				orderActorToFactory(211773660, EnemyMetis, "Metis_31");
				break;
			case 1890:
				orderActorToFactory(211773690, EnemyMetis, "Metis_32");
				break;
			case 1920:
				orderActorToFactory(211773720, EnemyMetis, "Metis_33");
				break;
			case 1950:
				orderActorToFactory(211773750, EnemyMetis, "Metis_34");
				break;
			case 1980:
				orderActorToFactory(211773780, EnemyMetis, "Metis_35");
				break;
			case 2010:
				orderActorToFactory(211773810, EnemyMetis, "Metis_36");
				break;
			case 2040:
				orderActorToFactory(211773840, EnemyMetis, "Metis_37");
				break;
			case 2070:
				orderActorToFactory(211773870, EnemyMetis, "Metis_38");
				break;
			case 2100:
				{
				FormationThalia* pActor = (FormationThalia*)obtainActorFromFactory(210372100);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773900, EnemyMetis, "Metis_39");
				break;
			case 2130:
				orderActorToFactory(211773930, EnemyMetis, "Metis_40");
				break;
			case 2160:
				orderActorToFactory(211773960, EnemyMetis, "Metis_41");
				break;
			case 2190:
				orderActorToFactory(211773990, EnemyMetis, "Metis_42");
				break;
			case 2220:
				orderActorToFactory(211774020, EnemyMetis, "Metis_43");
				break;
			case 2250:
				orderActorToFactory(211774050, EnemyMetis, "Metis_44");
				break;
			case 2280:
				orderActorToFactory(211774080, EnemyMetis, "Metis_45");
				break;
			case 2300:
				orderActorToFactory(210374100, FormationThalia, "FormationThalia_46");
				break;
			case 2310:
				orderActorToFactory(211774110, EnemyMetis, "Metis_47");
				break;
			case 2340:
				orderActorToFactory(211774140, EnemyMetis, "Metis_48");
				break;
			case 2370:
				orderActorToFactory(211774170, EnemyMetis, "Metis_49");
				break;
			case 2400:
				orderActorToFactory(211774200, EnemyMetis, "Metis_50");
				break;
			case 2430:
				orderActorToFactory(211774230, EnemyMetis, "Metis_51");
				break;
			case 2460:
				orderActorToFactory(211774260, EnemyMetis, "Metis_52");
				break;
			case 2490:
				orderActorToFactory(211774290, EnemyMetis, "Metis_53");
				break;
			case 2520:
				orderActorToFactory(211774320, EnemyMetis, "Metis_54");
				break;
			case 2550:
				orderActorToFactory(211774350, EnemyMetis, "Metis_55");
				break;
			case 2580:
				orderActorToFactory(211774380, EnemyMetis, "Metis_56");
				break;
			case 2600:
				{
				FormationThalia* pActor = (FormationThalia*)obtainActorFromFactory(210372600);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 2610:
				orderActorToFactory(211774410, EnemyMetis, "Metis_57");
				break;
			case 2640:
				orderActorToFactory(211774440, EnemyMetis, "Metis_58");
				break;
			case 2670:
				orderActorToFactory(211774470, EnemyMetis, "Metis_59");
				break;
			case 2700:
				orderActorToFactory(211774500, EnemyMetis, "Metis_60");
				break;
			case 2730:
				orderActorToFactory(211774530, EnemyMetis, "Metis_61");
				break;
			case 2760:
				orderActorToFactory(211774560, EnemyMetis, "Metis_62");
				break;
			case 2790:
				orderActorToFactory(211774590, EnemyMetis, "Metis_63");
				break;
			case 2800:
				orderActorToFactory(210374600, FormationThalia, "FormationThalia_64");
				break;
			case 2820:
				orderActorToFactory(211774620, EnemyMetis, "Metis_65");
				break;
			case 2850:
				orderActorToFactory(211774650, EnemyMetis, "Metis_66");
				break;
			case 2880:
				orderActorToFactory(211774680, EnemyMetis, "Metis_67");
				break;
			case 2910:
				orderActorToFactory(211774710, EnemyMetis, "Metis_68");
				break;
			case 2940:
				orderActorToFactory(211774740, EnemyMetis, "Metis_69");
				break;
			case 2970:
				orderActorToFactory(211774770, EnemyMetis, "Metis_70");
				break;
			case 3000:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773000);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774800, EnemyMetis, "Metis_71");
				break;
			case 3030:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773030);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774830, EnemyMetis, "Metis_72");
				break;
			case 3060:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773060);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774860, EnemyMetis, "Metis_73");
				break;
			case 3090:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773090);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774890, EnemyMetis, "Metis_74");
				break;
			case 3100:
				{
				FormationThalia* pActor = (FormationThalia*)obtainActorFromFactory(210373100);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 3120:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773120);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774920, EnemyMetis, "Metis_75");
				break;
			case 3150:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773150);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774950, EnemyMetis, "Metis_76");
				break;
			case 3180:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773180);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774980, EnemyMetis, "Metis_77");
				break;
			case 3210:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773210);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775010, EnemyMetis, "Metis_78");
				break;
			case 3240:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773240);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775040, EnemyMetis, "Metis_79");
				break;
			case 3270:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773270);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775070, EnemyMetis, "Metis_80");
				break;
			case 3300:
				orderActorToFactory(210375100, FormationThalia, "FormationThalia_81");
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773300);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775100, EnemyMetis, "Metis_82");
				break;
			case 3330:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773330);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775130, EnemyMetis, "Metis_83");
				break;
			case 3360:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773360);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775160, EnemyMetis, "Metis_84");
				break;
			case 3390:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773390);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775190, EnemyMetis, "Metis_85");
				break;
			case 3420:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773420);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775220, EnemyMetis, "Metis_86");
				break;
			case 3450:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773450);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775250, EnemyMetis, "Metis_87");
				break;
			case 3480:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773480);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775280, EnemyMetis, "Metis_88");
				break;
			case 3510:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773510);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775310, EnemyMetis, "Metis_89");
				break;
			case 3540:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773540);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775340, EnemyMetis, "Metis_90");
				break;
			case 3570:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773570);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775370, EnemyMetis, "Metis_91");
				break;
			case 3600:
				{
				FormationThalia* pActor = (FormationThalia*)obtainActorFromFactory(210373600);
				getLordActor()->addSubGroup(pActor);
				}
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773600);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775400, EnemyMetis, "Metis_92");
				break;
			case 3630:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773630);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775430, EnemyMetis, "Metis_93");
				break;
			case 3660:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773660);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775460, EnemyMetis, "Metis_94");
				break;
			case 3690:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773690);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775490, EnemyMetis, "Metis_95");
				break;
			case 3720:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773720);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775520, EnemyMetis, "Metis_96");
				break;
			case 3750:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773750);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775550, EnemyMetis, "Metis_97");
				break;
			case 3780:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773780);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775580, EnemyMetis, "Metis_98");
				break;
			case 3800:
				orderActorToFactory(210375600, FormationThalia, "FormationThalia_99");
				break;
			case 3810:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773810);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775610, EnemyMetis, "Metis_100");
				break;
			case 3840:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773840);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775640, EnemyMetis, "Metis_101");
				break;
			case 3870:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773870);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775670, EnemyMetis, "Metis_102");
				break;
			case 3900:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773900);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775700, EnemyMetis, "Metis_103");
				break;
			case 3930:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773930);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775730, EnemyMetis, "Metis_104");
				break;
			case 3960:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773960);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775760, EnemyMetis, "Metis_105");
				break;
			case 3990:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773990);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775790, EnemyMetis, "Metis_106");
				break;
			case 4020:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774020);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775820, EnemyMetis, "Metis_107");
				break;
			case 4050:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774050);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775850, EnemyMetis, "Metis_108");
				break;
			case 4080:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774080);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775880, EnemyMetis, "Metis_109");
				break;
			case 4100:
				{
				FormationThalia* pActor = (FormationThalia*)obtainActorFromFactory(210374100);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 4110:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774110);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775910, EnemyMetis, "Metis_110");
				break;
			case 4140:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774140);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775940, EnemyMetis, "Metis_111");
				break;
			case 4170:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774170);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775970, EnemyMetis, "Metis_112");
				break;
			case 4200:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774200);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776000, EnemyMetis, "Metis_113");
				break;
			case 4230:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774230);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776030, EnemyMetis, "Metis_114");
				break;
			case 4260:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774260);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776060, EnemyMetis, "Metis_115");
				break;
			case 4290:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774290);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776090, EnemyMetis, "Metis_116");
				break;
			case 4300:
				orderActorToFactory(210376100, FormationThalia, "FormationThalia_117");
				break;
			case 4320:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774320);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776120, EnemyMetis, "Metis_118");
				break;
			case 4350:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774350);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776150, EnemyMetis, "Metis_119");
				break;
			case 4380:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774380);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776180, EnemyMetis, "Metis_120");
				break;
			case 4410:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774410);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776210, EnemyMetis, "Metis_121");
				break;
			case 4440:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774440);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776240, EnemyMetis, "Metis_122");
				break;
			case 4470:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774470);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776270, EnemyMetis, "Metis_123");
				break;
			case 4500:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774500);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776300, EnemyMetis, "Metis_124");
				break;
			case 4530:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774530);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776330, EnemyMetis, "Metis_125");
				break;
			case 4560:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774560);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776360, EnemyMetis, "Metis_126");
				break;
			case 4590:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774590);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776390, EnemyMetis, "Metis_127");
				break;
			case 4600:
				{
				FormationThalia* pActor = (FormationThalia*)obtainActorFromFactory(210374600);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 4620:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774620);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776420, EnemyMetis, "Metis_128");
				break;
			case 4650:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774650);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776450, EnemyMetis, "Metis_129");
				break;
			case 4680:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774680);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776480, EnemyMetis, "Metis_130");
				break;
			case 4710:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774710);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776510, EnemyMetis, "Metis_131");
				break;
			case 4740:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774740);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776540, EnemyMetis, "Metis_132");
				break;
			case 4770:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774770);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776570, EnemyMetis, "Metis_133");
				break;
			case 4800:
				orderActorToFactory(210376600, FormationThalia, "FormationThalia_134");
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774800);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776600, EnemyMetis, "Metis_135");
				break;
			case 4830:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774830);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776630, EnemyMetis, "Metis_136");
				break;
			case 4860:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774860);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776660, EnemyMetis, "Metis_137");
				break;
			case 4890:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774890);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776690, EnemyMetis, "Metis_138");
				break;
			case 4920:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774920);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776720, EnemyMetis, "Metis_139");
				break;
			case 4950:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774950);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776750, EnemyMetis, "Metis_140");
				break;
			case 4980:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774980);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776780, EnemyMetis, "Metis_141");
				break;
			case 5010:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775010);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776810, EnemyMetis, "Metis_142");
				break;
			case 5040:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775040);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776840, EnemyMetis, "Metis_143");
				break;
			case 5070:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775070);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776870, EnemyMetis, "Metis_144");
				break;
			case 5100:
				{
				FormationThalia* pActor = (FormationThalia*)obtainActorFromFactory(210375100);
				getLordActor()->addSubGroup(pActor);
				}
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775100);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776900, EnemyMetis, "Metis_145");
				break;
			case 5130:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775130);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776930, EnemyMetis, "Metis_146");
				break;
			case 5160:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775160);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776960, EnemyMetis, "Metis_147");
				break;
			case 5190:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775190);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776990, EnemyMetis, "Metis_148");
				break;
			case 5220:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775220);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777020, EnemyMetis, "Metis_149");
				break;
			case 5250:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775250);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777050, EnemyMetis, "Metis_150");
				break;
			case 5280:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775280);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777080, EnemyMetis, "Metis_151");
				break;
			case 5300:
				orderActorToFactory(210377100, FormationThalia, "FormationThalia_152");
				break;
			case 5310:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775310);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777110, EnemyMetis, "Metis_153");
				break;
			case 5340:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775340);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777140, EnemyMetis, "Metis_154");
				break;
			case 5370:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775370);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777170, EnemyMetis, "Metis_155");
				break;
			case 5400:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775400);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777200, EnemyMetis, "Metis_156");
				break;
			case 5430:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775430);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777230, EnemyMetis, "Metis_157");
				break;
			case 5460:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775460);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777260, EnemyMetis, "Metis_158");
				break;
			case 5490:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775490);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777290, EnemyMetis, "Metis_159");
				break;
			case 5520:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775520);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777320, EnemyMetis, "Metis_160");
				break;
			case 5550:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775550);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777350, EnemyMetis, "Metis_161");
				break;
			case 5580:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775580);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777380, EnemyMetis, "Metis_162");
				break;
			case 5600:
				{
				FormationThalia* pActor = (FormationThalia*)obtainActorFromFactory(210375600);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 5610:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775610);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777410, EnemyMetis, "Metis_163");
				break;
			case 5640:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775640);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777440, EnemyMetis, "Metis_164");
				break;
			case 5670:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775670);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777470, EnemyMetis, "Metis_165");
				break;
			case 5700:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775700);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777500, EnemyMetis, "Metis_166");
				break;
			case 5730:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775730);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777530, EnemyMetis, "Metis_167");
				break;
			case 5760:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775760);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777560, EnemyMetis, "Metis_168");
				break;
			case 5790:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775790);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777590, EnemyMetis, "Metis_169");
				break;
			case 5800:
				orderActorToFactory(210377600, FormationThalia, "FormationThalia_170");
				break;
			case 5820:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775820);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777620, EnemyMetis, "Metis_171");
				break;
			case 5850:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775850);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777650, EnemyMetis, "Metis_172");
				break;
			case 5880:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775880);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777680, EnemyMetis, "Metis_173");
				break;
			case 5910:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775910);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777710, EnemyMetis, "Metis_174");
				break;
			case 5940:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775940);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777740, EnemyMetis, "Metis_175");
				break;
			case 5970:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775970);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777770, EnemyMetis, "Metis_176");
				break;
			case 6000:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776000);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777800, EnemyMetis, "Metis_177");
				break;
			case 6030:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776030);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777830, EnemyMetis, "Metis_178");
				break;
			case 6060:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776060);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777860, EnemyMetis, "Metis_179");
				break;
			case 6090:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776090);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777890, EnemyMetis, "Metis_180");
				break;
			case 6100:
				{
				FormationThalia* pActor = (FormationThalia*)obtainActorFromFactory(210376100);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 6120:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776120);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777920, EnemyMetis, "Metis_181");
				break;
			case 6150:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776150);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777950, EnemyMetis, "Metis_182");
				break;
			case 6180:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776180);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777980, EnemyMetis, "Metis_183");
				break;
			case 6210:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776210);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778010, EnemyMetis, "Metis_184");
				break;
			case 6240:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776240);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778040, EnemyMetis, "Metis_185");
				break;
			case 6270:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776270);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778070, EnemyMetis, "Metis_186");
				break;
			case 6300:
				orderActorToFactory(210378100, FormationThalia, "FormationThalia_187");
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776300);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778100, EnemyMetis, "Metis_188");
				break;
			case 6330:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776330);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778130, EnemyMetis, "Metis_189");
				break;
			case 6360:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776360);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778160, EnemyMetis, "Metis_190");
				break;
			case 6390:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776390);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778190, EnemyMetis, "Metis_191");
				break;
			case 6420:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776420);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778220, EnemyMetis, "Metis_192");
				break;
			case 6450:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776450);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778250, EnemyMetis, "Metis_193");
				break;
			case 6480:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776480);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778280, EnemyMetis, "Metis_194");
				break;
			case 6510:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776510);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778310, EnemyMetis, "Metis_195");
				break;
			case 6540:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776540);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778340, EnemyMetis, "Metis_196");
				break;
			case 6570:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776570);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778370, EnemyMetis, "Metis_197");
				break;
			case 6600:
				{
				FormationThalia* pActor = (FormationThalia*)obtainActorFromFactory(210376600);
				getLordActor()->addSubGroup(pActor);
				}
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776600);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778400, EnemyMetis, "Metis_198");
				break;
			case 6630:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776630);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778430, EnemyMetis, "Metis_199");
				break;
			case 6660:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776660);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778460, EnemyMetis, "Metis_200");
				break;
			case 6690:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776690);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778490, EnemyMetis, "Metis_201");
				break;
			case 6720:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776720);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778520, EnemyMetis, "Metis_202");
				break;
			case 6750:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776750);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778550, EnemyMetis, "Metis_203");
				break;
			case 6780:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776780);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778580, EnemyMetis, "Metis_204");
				break;
			case 6800:
				orderActorToFactory(210378600, FormationThalia, "FormationThalia_205");
				break;
			case 6810:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776810);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778610, EnemyMetis, "Metis_206");
				break;
			case 6840:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776840);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778640, EnemyMetis, "Metis_207");
				break;
			case 6870:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776870);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778670, EnemyMetis, "Metis_208");
				break;
			case 6900:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776900);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778700, EnemyMetis, "Metis_209");
				break;
			case 6930:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776930);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778730, EnemyMetis, "Metis_210");
				break;
			case 6960:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776960);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778760, EnemyMetis, "Metis_211");
				break;
			case 6990:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776990);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778790, EnemyMetis, "Metis_212");
				break;
			case 7020:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777020);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778820, EnemyMetis, "Metis_213");
				break;
			case 7050:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777050);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778850, EnemyMetis, "Metis_214");
				break;
			case 7080:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777080);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778880, EnemyMetis, "Metis_215");
				break;
			case 7100:
				{
				FormationThalia* pActor = (FormationThalia*)obtainActorFromFactory(210377100);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 7110:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777110);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778910, EnemyMetis, "Metis_216");
				break;
			case 7140:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777140);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778940, EnemyMetis, "Metis_217");
				break;
			case 7170:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777170);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778970, EnemyMetis, "Metis_218");
				break;
			case 7200:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777200);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779000, EnemyMetis, "Metis_219");
				break;
			case 7230:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777230);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779030, EnemyMetis, "Metis_220");
				break;
			case 7260:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777260);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779060, EnemyMetis, "Metis_221");
				break;
			case 7290:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777290);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779090, EnemyMetis, "Metis_222");
				break;
			case 7300:
				orderActorToFactory(210379100, FormationThalia, "FormationThalia_223");
				break;
			case 7320:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777320);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779120, EnemyMetis, "Metis_224");
				break;
			case 7350:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777350);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779150, EnemyMetis, "Metis_225");
				break;
			case 7380:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777380);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779180, EnemyMetis, "Metis_226");
				break;
			case 7410:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777410);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779210, EnemyMetis, "Metis_227");
				break;
			case 7440:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777440);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779240, EnemyMetis, "Metis_228");
				break;
			case 7470:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777470);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779270, EnemyMetis, "Metis_229");
				break;
			case 7500:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777500);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779300, EnemyMetis, "Metis_230");
				break;
			case 7530:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777530);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779330, EnemyMetis, "Metis_231");
				break;
			case 7560:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777560);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779360, EnemyMetis, "Metis_232");
				break;
			case 7590:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777590);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779390, EnemyMetis, "Metis_233");
				break;
			case 7600:
				{
				FormationThalia* pActor = (FormationThalia*)obtainActorFromFactory(210377600);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 7620:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777620);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779420, EnemyMetis, "Metis_234");
				break;
			case 7650:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777650);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779450, EnemyMetis, "Metis_235");
				break;
			case 7680:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777680);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779480, EnemyMetis, "Metis_236");
				break;
			case 7710:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777710);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779510, EnemyMetis, "Metis_237");
				break;
			case 7740:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777740);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779540, EnemyMetis, "Metis_238");
				break;
			case 7770:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777770);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779570, EnemyMetis, "Metis_239");
				break;
			case 7800:
				orderActorToFactory(210379600, FormationThalia, "FormationThalia_240");
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777800);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779600, EnemyMetis, "Metis_241");
				break;
			case 7830:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777830);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779630, EnemyMetis, "Metis_242");
				break;
			case 7860:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777860);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779660, EnemyMetis, "Metis_243");
				break;
			case 7890:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777890);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779690, EnemyMetis, "Metis_244");
				break;
			case 7920:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777920);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779720, EnemyMetis, "Metis_245");
				break;
			case 7950:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777950);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779750, EnemyMetis, "Metis_246");
				break;
			case 7980:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777980);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779780, EnemyMetis, "Metis_247");
				break;
			case 8010:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778010);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779810, EnemyMetis, "Metis_248");
				break;
			case 8040:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778040);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779840, EnemyMetis, "Metis_249");
				break;
			case 8070:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778070);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779870, EnemyMetis, "Metis_250");
				break;
			case 8100:
				{
				FormationThalia* pActor = (FormationThalia*)obtainActorFromFactory(210378100);
				getLordActor()->addSubGroup(pActor);
				}
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778100);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779900, EnemyMetis, "Metis_251");
				break;
			case 8130:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778130);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779930, EnemyMetis, "Metis_252");
				break;
			case 8160:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778160);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779960, EnemyMetis, "Metis_253");
				break;
			case 8190:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778190);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779990, EnemyMetis, "Metis_254");
				break;
			case 8220:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778220);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710020, EnemyMetis, "Metis_255");
				break;
			case 8250:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778250);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710050, EnemyMetis, "Metis_256");
				break;
			case 8280:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778280);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710080, EnemyMetis, "Metis_257");
				break;
			case 8310:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778310);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710110, EnemyMetis, "Metis_258");
				break;
			case 8340:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778340);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710140, EnemyMetis, "Metis_259");
				break;
			case 8370:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778370);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710170, EnemyMetis, "Metis_260");
				break;
			case 8400:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778400);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710200, EnemyMetis, "Metis_261");
				break;
			case 8430:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778430);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710230, EnemyMetis, "Metis_262");
				break;
			case 8460:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778460);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710260, EnemyMetis, "Metis_263");
				break;
			case 8490:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778490);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710290, EnemyMetis, "Metis_264");
				break;
			case 8520:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778520);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710320, EnemyMetis, "Metis_265");
				break;
			case 8550:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778550);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710350, EnemyMetis, "Metis_266");
				break;
			case 8580:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778580);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710380, EnemyMetis, "Metis_267");
				break;
			case 8600:
				{
				FormationThalia* pActor = (FormationThalia*)obtainActorFromFactory(210378600);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 8610:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778610);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710410, EnemyMetis, "Metis_268");
				break;
			case 8640:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778640);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710440, EnemyMetis, "Metis_269");
				break;
			case 8670:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778670);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710470, EnemyMetis, "Metis_270");
				break;
			case 8700:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778700);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710500, EnemyMetis, "Metis_271");
				break;
			case 8730:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778730);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710530, EnemyMetis, "Metis_272");
				break;
			case 8760:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778760);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710560, EnemyMetis, "Metis_273");
				break;
			case 8790:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778790);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710590, EnemyMetis, "Metis_274");
				break;
			case 8820:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778820);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710620, EnemyMetis, "Metis_275");
				break;
			case 8850:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778850);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710650, EnemyMetis, "Metis_276");
				break;
			case 8880:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778880);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710680, EnemyMetis, "Metis_277");
				break;
			case 8910:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778910);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710710, EnemyMetis, "Metis_278");
				break;
			case 8940:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778940);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710740, EnemyMetis, "Metis_279");
				break;
			case 8970:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778970);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710770, EnemyMetis, "Metis_280");
				break;
			case 9000:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779000);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710800, EnemyMetis, "Metis_281");
				break;
			case 9030:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779030);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710830, EnemyMetis, "Metis_282");
				break;
			case 9060:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779060);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710860, EnemyMetis, "Metis_283");
				break;
			case 9090:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779090);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710890, EnemyMetis, "Metis_284");
				break;
			case 9100:
				{
				FormationThalia* pActor = (FormationThalia*)obtainActorFromFactory(210379100);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 9120:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779120);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710920, EnemyMetis, "Metis_285");
				break;
			case 9150:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779150);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710950, EnemyMetis, "Metis_286");
				break;
			case 9180:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779180);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710980, EnemyMetis, "Metis_287");
				break;
			case 9210:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779210);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711010, EnemyMetis, "Metis_288");
				break;
			case 9240:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779240);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711040, EnemyMetis, "Metis_289");
				break;
			case 9270:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779270);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711070, EnemyMetis, "Metis_290");
				break;
			case 9300:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779300);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711100, EnemyMetis, "Metis_291");
				break;
			case 9330:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779330);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711130, EnemyMetis, "Metis_292");
				break;
			case 9360:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779360);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711160, EnemyMetis, "Metis_293");
				break;
			case 9390:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779390);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711190, EnemyMetis, "Metis_294");
				break;
			case 9420:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779420);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711220, EnemyMetis, "Metis_295");
				break;
			case 9450:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779450);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711250, EnemyMetis, "Metis_296");
				break;
			case 9480:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779480);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711280, EnemyMetis, "Metis_297");
				break;
			case 9510:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779510);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711310, EnemyMetis, "Metis_298");
				break;
			case 9540:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779540);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711340, EnemyMetis, "Metis_299");
				break;
			case 9570:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779570);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711370, EnemyMetis, "Metis_300");
				break;
			case 9600:
				{
				FormationThalia* pActor = (FormationThalia*)obtainActorFromFactory(210379600);
				getLordActor()->addSubGroup(pActor);
				}
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779600);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711400, EnemyMetis, "Metis_301");
				break;
			case 9630:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779630);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711430, EnemyMetis, "Metis_302");
				break;
			case 9660:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779660);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711460, EnemyMetis, "Metis_303");
				break;
			case 9690:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779690);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711490, EnemyMetis, "Metis_304");
				break;
			case 9720:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779720);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711520, EnemyMetis, "Metis_305");
				break;
			case 9750:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779750);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711550, EnemyMetis, "Metis_306");
				break;
			case 9780:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779780);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711580, EnemyMetis, "Metis_307");
				break;
			case 9810:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779810);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711610, EnemyMetis, "Metis_308");
				break;
			case 9840:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779840);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711640, EnemyMetis, "Metis_309");
				break;
			case 9870:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779870);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711670, EnemyMetis, "Metis_310");
				break;
			case 9900:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779900);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711700, EnemyMetis, "Metis_311");
				break;
			case 9930:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779930);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711730, EnemyMetis, "Metis_312");
				break;
			case 9960:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779960);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711760, EnemyMetis, "Metis_313");
				break;
			case 9990:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779990);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711790, EnemyMetis, "Metis_314");
				break;
			case 10020:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710020);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711820, EnemyMetis, "Metis_315");
				break;
			case 10050:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710050);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711850, EnemyMetis, "Metis_316");
				break;
			case 10080:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710080);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711880, EnemyMetis, "Metis_317");
				break;
			case 10110:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710110);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711910, EnemyMetis, "Metis_318");
				break;
			case 10140:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710140);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711940, EnemyMetis, "Metis_319");
				break;
			case 10170:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710170);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711970, EnemyMetis, "Metis_320");
				break;
			case 10200:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710200);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712000, EnemyMetis, "Metis_321");
				break;
			case 10230:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710230);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712030, EnemyMetis, "Metis_322");
				break;
			case 10260:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710260);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712060, EnemyMetis, "Metis_323");
				break;
			case 10290:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710290);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712090, EnemyMetis, "Metis_324");
				break;
			case 10320:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710320);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712120, EnemyMetis, "Metis_325");
				break;
			case 10350:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710350);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712150, EnemyMetis, "Metis_326");
				break;
			case 10380:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710380);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712180, EnemyMetis, "Metis_327");
				break;
			case 10410:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710410);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712210, EnemyMetis, "Metis_328");
				break;
			case 10440:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710440);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712240, EnemyMetis, "Metis_329");
				break;
			case 10470:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710470);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712270, EnemyMetis, "Metis_330");
				break;
			case 10500:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710500);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712300, EnemyMetis, "Metis_331");
				break;
			case 10530:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710530);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712330, EnemyMetis, "Metis_332");
				break;
			case 10560:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710560);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712360, EnemyMetis, "Metis_333");
				break;
			case 10590:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710590);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712390, EnemyMetis, "Metis_334");
				break;
			case 10620:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710620);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712420, EnemyMetis, "Metis_335");
				break;
			case 10650:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710650);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712450, EnemyMetis, "Metis_336");
				break;
			case 10680:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710680);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712480, EnemyMetis, "Metis_337");
				break;
			case 10710:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710710);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712510, EnemyMetis, "Metis_338");
				break;
			case 10740:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710740);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712540, EnemyMetis, "Metis_339");
				break;
			case 10770:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710770);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712570, EnemyMetis, "Metis_340");
				break;
			case 10800:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710800);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712600, EnemyMetis, "Metis_341");
				break;
			case 10830:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710830);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712630, EnemyMetis, "Metis_342");
				break;
			case 10860:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710860);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712660, EnemyMetis, "Metis_343");
				break;
			case 10890:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710890);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712690, EnemyMetis, "Metis_344");
				break;
			case 10920:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710920);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712720, EnemyMetis, "Metis_345");
				break;
			case 10950:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710950);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712750, EnemyMetis, "Metis_346");
				break;
			case 10980:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710980);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712780, EnemyMetis, "Metis_347");
				break;
			case 11010:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711010);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712810, EnemyMetis, "Metis_348");
				break;
			case 11040:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711040);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712840, EnemyMetis, "Metis_349");
				break;
			case 11070:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711070);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712870, EnemyMetis, "Metis_350");
				break;
			case 11100:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711100);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712900, EnemyMetis, "Metis_351");
				break;
			case 11130:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711130);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712930, EnemyMetis, "Metis_352");
				break;
			case 11160:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711160);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712960, EnemyMetis, "Metis_353");
				break;
			case 11190:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711190);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712990, EnemyMetis, "Metis_354");
				break;
			case 11220:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711220);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713020, EnemyMetis, "Metis_355");
				break;
			case 11250:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711250);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713050, EnemyMetis, "Metis_356");
				break;
			case 11280:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711280);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713080, EnemyMetis, "Metis_357");
				break;
			case 11310:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711310);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713110, EnemyMetis, "Metis_358");
				break;
			case 11340:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711340);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713140, EnemyMetis, "Metis_359");
				break;
			case 11370:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711370);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713170, EnemyMetis, "Metis_360");
				break;
			case 11400:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711400);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713200, EnemyMetis, "Metis_361");
				break;
			case 11430:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711430);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713230, EnemyMetis, "Metis_362");
				break;
			case 11460:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711460);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713260, EnemyMetis, "Metis_363");
				break;
			case 11490:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711490);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713290, EnemyMetis, "Metis_364");
				break;
			case 11520:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711520);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713320, EnemyMetis, "Metis_365");
				break;
			case 11550:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711550);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713350, EnemyMetis, "Metis_366");
				break;
			case 11580:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711580);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713380, EnemyMetis, "Metis_367");
				break;
			case 11610:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711610);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713410, EnemyMetis, "Metis_368");
				break;
			case 11640:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711640);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713440, EnemyMetis, "Metis_369");
				break;
			case 11670:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711670);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713470, EnemyMetis, "Metis_370");
				break;
			case 11700:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711700);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713500, EnemyMetis, "Metis_371");
				break;
			case 11730:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711730);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713530, EnemyMetis, "Metis_372");
				break;
			case 11760:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711760);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713560, EnemyMetis, "Metis_373");
				break;
			case 11790:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711790);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713590, EnemyMetis, "Metis_374");
				break;
			case 11820:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711820);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713620, EnemyMetis, "Metis_375");
				break;
			case 11850:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711850);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713650, EnemyMetis, "Metis_376");
				break;
			case 11880:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711880);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713680, EnemyMetis, "Metis_377");
				break;
			case 11910:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711910);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713710, EnemyMetis, "Metis_378");
				break;
			case 11940:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711940);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713740, EnemyMetis, "Metis_379");
				break;
			case 11970:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711970);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713770, EnemyMetis, "Metis_380");
				break;
			case 12000:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712000);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713800, EnemyMetis, "Metis_381");
				break;
			case 12030:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712030);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713830, EnemyMetis, "Metis_382");
				break;
			case 12060:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712060);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713860, EnemyMetis, "Metis_383");
				break;
			case 12090:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712090);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713890, EnemyMetis, "Metis_384");
				break;
			case 12120:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712120);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713920, EnemyMetis, "Metis_385");
				break;
			case 12150:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712150);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713950, EnemyMetis, "Metis_386");
				break;
			case 12180:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712180);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713980, EnemyMetis, "Metis_387");
				break;
			case 12210:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712210);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714010, EnemyMetis, "Metis_388");
				break;
			case 12240:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712240);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714040, EnemyMetis, "Metis_389");
				break;
			case 12270:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712270);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714070, EnemyMetis, "Metis_390");
				break;
			case 12300:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712300);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714100, EnemyMetis, "Metis_391");
				break;
			case 12330:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712330);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714130, EnemyMetis, "Metis_392");
				break;
			case 12360:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712360);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714160, EnemyMetis, "Metis_393");
				break;
			case 12390:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712390);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714190, EnemyMetis, "Metis_394");
				break;
			case 12420:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712420);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714220, EnemyMetis, "Metis_395");
				break;
			case 12450:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712450);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714250, EnemyMetis, "Metis_396");
				break;
			case 12480:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712480);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714280, EnemyMetis, "Metis_397");
				break;
			case 12510:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712510);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714310, EnemyMetis, "Metis_398");
				break;
			case 12540:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712540);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714340, EnemyMetis, "Metis_399");
				break;
			case 12570:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712570);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714370, EnemyMetis, "Metis_400");
				break;
			case 12600:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712600);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714400, EnemyMetis, "Metis_401");
				break;
			case 12630:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712630);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714430, EnemyMetis, "Metis_402");
				break;
			case 12660:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712660);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714460, EnemyMetis, "Metis_403");
				break;
			case 12690:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712690);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714490, EnemyMetis, "Metis_404");
				break;
			case 12720:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712720);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714520, EnemyMetis, "Metis_405");
				break;
			case 12750:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712750);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714550, EnemyMetis, "Metis_406");
				break;
			case 12780:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712780);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714580, EnemyMetis, "Metis_407");
				break;
			case 12810:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712810);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714610, EnemyMetis, "Metis_408");
				break;
			case 12840:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712840);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714640, EnemyMetis, "Metis_409");
				break;
			case 12870:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712870);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714670, EnemyMetis, "Metis_410");
				break;
			case 12900:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712900);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714700, EnemyMetis, "Metis_411");
				break;
			case 12930:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712930);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714730, EnemyMetis, "Metis_412");
				break;
			case 12960:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712960);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714760, EnemyMetis, "Metis_413");
				break;
			case 12990:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712990);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714790, EnemyMetis, "Metis_414");
				break;
			case 13020:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713020);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714820, EnemyMetis, "Metis_415");
				break;
			case 13050:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713050);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714850, EnemyMetis, "Metis_416");
				break;
			case 13080:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713080);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714880, EnemyMetis, "Metis_417");
				break;
			case 13110:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713110);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714910, EnemyMetis, "Metis_418");
				break;
			case 13140:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713140);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714940, EnemyMetis, "Metis_419");
				break;
			case 13170:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713170);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714970, EnemyMetis, "Metis_420");
				break;
			case 13200:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713200);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715000, EnemyMetis, "Metis_421");
				break;
			case 13230:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713230);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715030, EnemyMetis, "Metis_422");
				break;
			case 13260:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713260);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715060, EnemyMetis, "Metis_423");
				break;
			case 13290:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713290);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715090, EnemyMetis, "Metis_424");
				break;
			case 13320:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713320);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715120, EnemyMetis, "Metis_425");
				break;
			case 13350:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713350);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715150, EnemyMetis, "Metis_426");
				break;
			case 13380:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713380);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715180, EnemyMetis, "Metis_427");
				break;
			case 13410:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713410);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715210, EnemyMetis, "Metis_428");
				break;
			case 13440:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713440);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715240, EnemyMetis, "Metis_429");
				break;
			case 13470:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713470);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715270, EnemyMetis, "Metis_430");
				break;
			case 13500:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713500);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715300, EnemyMetis, "Metis_431");
				break;
			case 13530:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713530);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715330, EnemyMetis, "Metis_432");
				break;
			case 13560:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713560);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715360, EnemyMetis, "Metis_433");
				break;
			case 13590:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713590);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715390, EnemyMetis, "Metis_434");
				break;
			case 13620:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713620);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715420, EnemyMetis, "Metis_435");
				break;
			case 13650:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713650);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715450, EnemyMetis, "Metis_436");
				break;
			case 13680:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713680);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715480, EnemyMetis, "Metis_437");
				break;
			case 13710:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713710);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715510, EnemyMetis, "Metis_438");
				break;
			case 13740:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713740);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715540, EnemyMetis, "Metis_439");
				break;
			case 13770:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713770);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715570, EnemyMetis, "Metis_440");
				break;
			case 13800:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713800);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715600, EnemyMetis, "Metis_441");
				break;
			case 13830:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713830);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715630, EnemyMetis, "Metis_442");
				break;
			case 13860:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713860);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715660, EnemyMetis, "Metis_443");
				break;
			case 13890:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713890);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715690, EnemyMetis, "Metis_444");
				break;
			case 13920:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713920);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715720, EnemyMetis, "Metis_445");
				break;
			case 13950:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713950);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715750, EnemyMetis, "Metis_446");
				break;
			case 13980:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713980);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715780, EnemyMetis, "Metis_447");
				break;
			case 14010:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714010);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715810, EnemyMetis, "Metis_448");
				break;
			case 14040:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714040);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715840, EnemyMetis, "Metis_449");
				break;
			case 14070:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714070);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715870, EnemyMetis, "Metis_450");
				break;
			case 14100:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714100);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715900, EnemyMetis, "Metis_451");
				break;
			case 14130:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714130);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715930, EnemyMetis, "Metis_452");
				break;
			case 14160:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714160);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715960, EnemyMetis, "Metis_453");
				break;
			case 14190:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714190);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715990, EnemyMetis, "Metis_454");
				break;
			case 14220:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714220);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716020, EnemyMetis, "Metis_455");
				break;
			case 14250:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714250);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716050, EnemyMetis, "Metis_456");
				break;
			case 14280:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714280);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716080, EnemyMetis, "Metis_457");
				break;
			case 14310:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714310);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716110, EnemyMetis, "Metis_458");
				break;
			case 14340:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714340);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716140, EnemyMetis, "Metis_459");
				break;
			case 14370:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714370);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716170, EnemyMetis, "Metis_460");
				break;
			case 14400:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714400);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716200, EnemyMetis, "Metis_461");
				break;
			case 14430:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714430);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716230, EnemyMetis, "Metis_462");
				break;
			case 14460:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714460);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716260, EnemyMetis, "Metis_463");
				break;
			case 14490:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714490);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716290, EnemyMetis, "Metis_464");
				break;
			case 14520:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714520);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716320, EnemyMetis, "Metis_465");
				break;
			case 14550:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714550);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716350, EnemyMetis, "Metis_466");
				break;
			case 14580:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714580);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716380, EnemyMetis, "Metis_467");
				break;
			case 14610:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714610);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716410, EnemyMetis, "Metis_468");
				break;
			case 14640:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714640);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716440, EnemyMetis, "Metis_469");
				break;
			case 14670:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714670);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716470, EnemyMetis, "Metis_470");
				break;
			case 14700:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714700);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716500, EnemyMetis, "Metis_471");
				break;
			case 14730:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714730);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716530, EnemyMetis, "Metis_472");
				break;
			case 14760:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714760);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716560, EnemyMetis, "Metis_473");
				break;
			case 14790:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714790);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716590, EnemyMetis, "Metis_474");
				break;
			case 14820:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714820);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716620, EnemyMetis, "Metis_475");
				break;
			case 14850:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714850);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716650, EnemyMetis, "Metis_476");
				break;
			case 14880:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714880);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716680, EnemyMetis, "Metis_477");
				break;
			case 14910:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714910);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716710, EnemyMetis, "Metis_478");
				break;
			case 14940:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714940);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716740, EnemyMetis, "Metis_479");
				break;
			case 14970:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714970);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716770, EnemyMetis, "Metis_480");
				break;
			case 15000:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715000);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716800, EnemyMetis, "Metis_481");
				break;
			case 15030:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715030);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716830, EnemyMetis, "Metis_482");
				break;
			case 15060:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715060);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716860, EnemyMetis, "Metis_483");
				break;
			case 15090:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715090);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716890, EnemyMetis, "Metis_484");
				break;
			case 15120:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715120);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716920, EnemyMetis, "Metis_485");
				break;
			case 15150:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715150);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716950, EnemyMetis, "Metis_486");
				break;
			case 15180:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715180);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716980, EnemyMetis, "Metis_487");
				break;
			case 15210:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715210);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717010, EnemyMetis, "Metis_488");
				break;
			case 15240:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715240);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717040, EnemyMetis, "Metis_489");
				break;
			case 15270:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715270);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717070, EnemyMetis, "Metis_490");
				break;
			case 15300:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715300);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717100, EnemyMetis, "Metis_491");
				break;
			case 15330:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715330);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717130, EnemyMetis, "Metis_492");
				break;
			case 15360:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715360);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717160, EnemyMetis, "Metis_493");
				break;
			case 15390:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715390);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717190, EnemyMetis, "Metis_494");
				break;
			case 15420:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715420);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717220, EnemyMetis, "Metis_495");
				break;
			case 15450:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715450);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717250, EnemyMetis, "Metis_496");
				break;
			case 15480:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715480);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717280, EnemyMetis, "Metis_497");
				break;
			case 15510:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715510);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717310, EnemyMetis, "Metis_498");
				break;
			case 15540:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715540);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717340, EnemyMetis, "Metis_499");
				break;
			case 15570:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715570);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717370, EnemyMetis, "Metis_500");
				break;
			case 15600:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715600);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717400, EnemyMetis, "Metis_501");
				break;
			case 15630:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715630);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717430, EnemyMetis, "Metis_502");
				break;
			case 15660:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715660);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717460, EnemyMetis, "Metis_503");
				break;
			case 15690:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715690);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717490, EnemyMetis, "Metis_504");
				break;
			case 15720:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715720);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717520, EnemyMetis, "Metis_505");
				break;
			case 15750:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715750);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717550, EnemyMetis, "Metis_506");
				break;
			case 15780:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715780);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717580, EnemyMetis, "Metis_507");
				break;
			case 15810:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715810);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717610, EnemyMetis, "Metis_508");
				break;
			case 15840:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715840);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717640, EnemyMetis, "Metis_509");
				break;
			case 15870:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715870);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717670, EnemyMetis, "Metis_510");
				break;
			case 15900:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715900);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717700, EnemyMetis, "Metis_511");
				break;
			case 15930:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715930);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717730, EnemyMetis, "Metis_512");
				break;
			case 15960:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715960);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717760, EnemyMetis, "Metis_513");
				break;
			case 15990:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715990);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717790, EnemyMetis, "Metis_514");
				break;
			case 16020:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716020);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717820, EnemyMetis, "Metis_515");
				break;
			case 16050:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716050);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717850, EnemyMetis, "Metis_516");
				break;
			case 16080:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716080);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717880, EnemyMetis, "Metis_517");
				break;
			case 16110:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716110);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717910, EnemyMetis, "Metis_518");
				break;
			case 16140:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716140);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717940, EnemyMetis, "Metis_519");
				break;
			case 16170:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716170);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717970, EnemyMetis, "Metis_520");
				break;
			case 16200:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716200);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718000, EnemyMetis, "Metis_521");
				break;
			case 16230:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716230);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718030, EnemyMetis, "Metis_522");
				break;
			case 16260:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716260);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718060, EnemyMetis, "Metis_523");
				break;
			case 16290:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716290);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718090, EnemyMetis, "Metis_524");
				break;
			case 16320:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716320);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718120, EnemyMetis, "Metis_525");
				break;
			case 16350:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716350);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718150, EnemyMetis, "Metis_526");
				break;
			case 16380:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716380);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718180, EnemyMetis, "Metis_527");
				break;
			case 16410:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716410);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718210, EnemyMetis, "Metis_528");
				break;
			case 16440:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716440);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718240, EnemyMetis, "Metis_529");
				break;
			case 16470:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716470);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718270, EnemyMetis, "Metis_530");
				break;
			case 16500:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716500);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718300, EnemyMetis, "Metis_531");
				break;
			case 16530:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716530);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718330, EnemyMetis, "Metis_532");
				break;
			case 16560:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716560);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718360, EnemyMetis, "Metis_533");
				break;
			case 16590:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716590);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718390, EnemyMetis, "Metis_534");
				break;
			case 16620:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716620);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718420, EnemyMetis, "Metis_535");
				break;
			case 16650:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716650);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718450, EnemyMetis, "Metis_536");
				break;
			case 16680:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716680);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718480, EnemyMetis, "Metis_537");
				break;
			case 16710:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716710);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718510, EnemyMetis, "Metis_538");
				break;
			case 16740:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716740);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718540, EnemyMetis, "Metis_539");
				break;
			case 16770:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716770);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718570, EnemyMetis, "Metis_540");
				break;
			case 16800:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716800);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718600, EnemyMetis, "Metis_541");
				break;
			case 16830:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716830);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718630, EnemyMetis, "Metis_542");
				break;
			case 16860:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716860);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718660, EnemyMetis, "Metis_543");
				break;
			case 16890:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716890);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718690, EnemyMetis, "Metis_544");
				break;
			case 16920:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716920);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718720, EnemyMetis, "Metis_545");
				break;
			case 16950:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716950);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718750, EnemyMetis, "Metis_546");
				break;
			case 16980:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716980);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718780, EnemyMetis, "Metis_547");
				break;
			case 17010:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717010);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718810, EnemyMetis, "Metis_548");
				break;
			case 17040:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717040);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718840, EnemyMetis, "Metis_549");
				break;
			case 17070:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717070);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718870, EnemyMetis, "Metis_550");
				break;
			case 17100:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717100);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718900, EnemyMetis, "Metis_551");
				break;
			case 17130:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717130);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718930, EnemyMetis, "Metis_552");
				break;
			case 17160:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717160);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718960, EnemyMetis, "Metis_553");
				break;
			case 17190:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717190);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718990, EnemyMetis, "Metis_554");
				break;
			case 17220:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717220);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719020, EnemyMetis, "Metis_555");
				break;
			case 17250:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717250);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719050, EnemyMetis, "Metis_556");
				break;
			case 17280:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717280);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719080, EnemyMetis, "Metis_557");
				break;
			case 17310:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717310);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719110, EnemyMetis, "Metis_558");
				break;
			case 17340:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717340);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719140, EnemyMetis, "Metis_559");
				break;
			case 17370:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717370);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719170, EnemyMetis, "Metis_560");
				break;
			case 17400:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717400);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719200, EnemyMetis, "Metis_561");
				break;
			case 17430:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717430);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719230, EnemyMetis, "Metis_562");
				break;
			case 17460:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717460);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719260, EnemyMetis, "Metis_563");
				break;
			case 17490:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717490);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719290, EnemyMetis, "Metis_564");
				break;
			case 17520:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717520);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719320, EnemyMetis, "Metis_565");
				break;
			case 17550:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717550);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719350, EnemyMetis, "Metis_566");
				break;
			case 17580:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717580);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719380, EnemyMetis, "Metis_567");
				break;
			case 17610:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717610);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719410, EnemyMetis, "Metis_568");
				break;
			case 17640:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717640);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719440, EnemyMetis, "Metis_569");
				break;
			case 17670:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717670);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719470, EnemyMetis, "Metis_570");
				break;
			case 17700:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717700);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719500, EnemyMetis, "Metis_571");
				break;
			case 17730:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717730);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719530, EnemyMetis, "Metis_572");
				break;
			case 17760:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717760);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719560, EnemyMetis, "Metis_573");
				break;
			case 17790:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717790);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719590, EnemyMetis, "Metis_574");
				break;
			case 17820:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717820);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719620, EnemyMetis, "Metis_575");
				break;
			case 17850:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717850);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719650, EnemyMetis, "Metis_576");
				break;
			case 17880:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717880);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719680, EnemyMetis, "Metis_577");
				break;
			case 17910:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717910);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719710, EnemyMetis, "Metis_578");
				break;
			case 17940:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717940);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719740, EnemyMetis, "Metis_579");
				break;
			case 17970:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717970);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719770, EnemyMetis, "Metis_580");
				break;
			case 18000:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718000);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719800, EnemyMetis, "Metis_581");
				break;
			case 18030:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718030);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719830, EnemyMetis, "Metis_582");
				break;
			case 18060:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718060);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719860, EnemyMetis, "Metis_583");
				break;
			case 18090:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718090);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719890, EnemyMetis, "Metis_584");
				break;
			case 18120:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718120);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719920, EnemyMetis, "Metis_585");
				break;
			case 18150:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718150);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719950, EnemyMetis, "Metis_586");
				break;
			case 18180:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718180);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719980, EnemyMetis, "Metis_587");
				break;
			case 18210:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718210);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720010, EnemyMetis, "Metis_588");
				break;
			case 18240:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718240);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720040, EnemyMetis, "Metis_589");
				break;
			case 18270:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718270);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720070, EnemyMetis, "Metis_590");
				break;
			case 18300:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718300);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720100, EnemyMetis, "Metis_591");
				break;
			case 18330:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718330);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720130, EnemyMetis, "Metis_592");
				break;
			case 18360:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718360);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720160, EnemyMetis, "Metis_593");
				break;
			case 18390:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718390);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720190, EnemyMetis, "Metis_594");
				break;
			case 18420:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718420);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720220, EnemyMetis, "Metis_595");
				break;
			case 18450:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718450);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720250, EnemyMetis, "Metis_596");
				break;
			case 18480:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718480);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720280, EnemyMetis, "Metis_597");
				break;
			case 18510:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718510);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720310, EnemyMetis, "Metis_598");
				break;
			case 18540:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718540);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720340, EnemyMetis, "Metis_599");
				break;
			case 18570:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718570);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720370, EnemyMetis, "Metis_600");
				break;
			case 18600:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718600);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720400, EnemyMetis, "Metis_601");
				break;
			case 18630:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718630);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720430, EnemyMetis, "Metis_602");
				break;
			case 18660:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718660);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720460, EnemyMetis, "Metis_603");
				break;
			case 18690:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718690);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720490, EnemyMetis, "Metis_604");
				break;
			case 18720:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718720);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720520, EnemyMetis, "Metis_605");
				break;
			case 18750:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718750);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720550, EnemyMetis, "Metis_606");
				break;
			case 18780:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718780);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720580, EnemyMetis, "Metis_607");
				break;
			case 18810:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718810);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720610, EnemyMetis, "Metis_608");
				break;
			case 18840:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718840);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720640, EnemyMetis, "Metis_609");
				break;
			case 18870:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718870);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720670, EnemyMetis, "Metis_610");
				break;
			case 18900:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718900);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720700, EnemyMetis, "Metis_611");
				break;
			case 18930:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718930);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720730, EnemyMetis, "Metis_612");
				break;
			case 18960:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718960);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720760, EnemyMetis, "Metis_613");
				break;
			case 18990:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718990);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720790, EnemyMetis, "Metis_614");
				break;
			case 19020:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719020);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720820, EnemyMetis, "Metis_615");
				break;
			case 19050:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719050);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720850, EnemyMetis, "Metis_616");
				break;
			case 19080:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719080);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720880, EnemyMetis, "Metis_617");
				break;
			case 19110:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719110);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720910, EnemyMetis, "Metis_618");
				break;
			case 19140:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719140);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720940, EnemyMetis, "Metis_619");
				break;
			case 19170:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719170);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720970, EnemyMetis, "Metis_620");
				break;
			case 19200:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719200);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721000, EnemyMetis, "Metis_621");
				break;
			case 19230:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719230);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721030, EnemyMetis, "Metis_622");
				break;
			case 19260:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719260);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721060, EnemyMetis, "Metis_623");
				break;
			case 19290:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719290);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721090, EnemyMetis, "Metis_624");
				break;
			case 19320:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719320);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721120, EnemyMetis, "Metis_625");
				break;
			case 19350:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719350);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721150, EnemyMetis, "Metis_626");
				break;
			case 19380:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719380);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721180, EnemyMetis, "Metis_627");
				break;
			case 19410:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719410);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721210, EnemyMetis, "Metis_628");
				break;
			case 19440:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719440);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721240, EnemyMetis, "Metis_629");
				break;
			case 19470:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719470);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721270, EnemyMetis, "Metis_630");
				break;
			case 19500:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719500);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721300, EnemyMetis, "Metis_631");
				break;
			case 19530:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719530);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721330, EnemyMetis, "Metis_632");
				break;
			case 19560:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719560);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721360, EnemyMetis, "Metis_633");
				break;
			case 19590:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719590);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721390, EnemyMetis, "Metis_634");
				break;
			case 19620:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719620);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721420, EnemyMetis, "Metis_635");
				break;
			case 19650:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719650);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721450, EnemyMetis, "Metis_636");
				break;
			case 19680:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719680);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721480, EnemyMetis, "Metis_637");
				break;
			case 19710:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719710);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721510, EnemyMetis, "Metis_638");
				break;
			case 19740:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719740);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721540, EnemyMetis, "Metis_639");
				break;
			case 19770:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719770);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721570, EnemyMetis, "Metis_640");
				break;
			case 19800:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719800);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721600, EnemyMetis, "Metis_641");
				break;
			case 19830:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719830);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721630, EnemyMetis, "Metis_642");
				break;
			case 19860:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719860);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721660, EnemyMetis, "Metis_643");
				break;
			case 19890:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719890);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721690, EnemyMetis, "Metis_644");
				break;
			case 19920:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719920);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721720, EnemyMetis, "Metis_645");
				break;
			case 19950:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719950);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721750, EnemyMetis, "Metis_646");
				break;
			case 19980:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719980);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721780, EnemyMetis, "Metis_647");
				break;
			case 20010:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720010);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721810, EnemyMetis, "Metis_648");
				break;
			case 20040:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720040);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721840, EnemyMetis, "Metis_649");
				break;
			case 20070:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720070);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721870, EnemyMetis, "Metis_650");
				break;
			case 20100:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720100);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721900, EnemyMetis, "Metis_651");
				break;
			case 20130:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720130);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721930, EnemyMetis, "Metis_652");
				break;
			case 20160:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720160);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721960, EnemyMetis, "Metis_653");
				break;
			case 20190:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720190);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721990, EnemyMetis, "Metis_654");
				break;
			case 20220:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720220);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722020, EnemyMetis, "Metis_655");
				break;
			case 20250:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720250);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722050, EnemyMetis, "Metis_656");
				break;
			case 20280:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720280);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722080, EnemyMetis, "Metis_657");
				break;
			case 20310:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720310);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722110, EnemyMetis, "Metis_658");
				break;
			case 20340:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720340);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722140, EnemyMetis, "Metis_659");
				break;
			case 20370:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720370);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722170, EnemyMetis, "Metis_660");
				break;
			case 20400:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720400);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722200, EnemyMetis, "Metis_661");
				break;
			case 20430:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720430);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722230, EnemyMetis, "Metis_662");
				break;
			case 20460:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720460);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722260, EnemyMetis, "Metis_663");
				break;
			case 20490:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720490);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722290, EnemyMetis, "Metis_664");
				break;
			case 20520:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720520);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722320, EnemyMetis, "Metis_665");
				break;
			case 20550:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720550);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722350, EnemyMetis, "Metis_666");
				break;
			case 20580:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720580);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722380, EnemyMetis, "Metis_667");
				break;
			case 20610:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720610);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722410, EnemyMetis, "Metis_668");
				break;
			case 20640:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720640);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722440, EnemyMetis, "Metis_669");
				break;
			case 20670:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720670);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722470, EnemyMetis, "Metis_670");
				break;
			case 20700:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720700);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722500, EnemyMetis, "Metis_671");
				break;
			case 20730:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720730);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722530, EnemyMetis, "Metis_672");
				break;
			case 20760:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720760);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722560, EnemyMetis, "Metis_673");
				break;
			case 20790:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720790);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722590, EnemyMetis, "Metis_674");
				break;
			case 20820:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720820);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722620, EnemyMetis, "Metis_675");
				break;
			case 20850:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720850);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722650, EnemyMetis, "Metis_676");
				break;
			case 20880:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720880);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722680, EnemyMetis, "Metis_677");
				break;
			case 20910:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720910);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722710, EnemyMetis, "Metis_678");
				break;
			case 20940:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720940);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722740, EnemyMetis, "Metis_679");
				break;
			case 20970:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720970);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722770, EnemyMetis, "Metis_680");
				break;
			case 21000:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721000);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722800, EnemyMetis, "Metis_681");
				break;
			case 21030:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721030);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722830, EnemyMetis, "Metis_682");
				break;
			case 21060:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721060);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722860, EnemyMetis, "Metis_683");
				break;
			case 21090:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721090);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722890, EnemyMetis, "Metis_684");
				break;
			case 21120:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721120);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722920, EnemyMetis, "Metis_685");
				break;
			case 21150:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721150);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722950, EnemyMetis, "Metis_686");
				break;
			case 21180:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721180);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722980, EnemyMetis, "Metis_687");
				break;
			case 21210:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721210);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723010, EnemyMetis, "Metis_688");
				break;
			case 21240:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721240);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723040, EnemyMetis, "Metis_689");
				break;
			case 21270:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721270);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723070, EnemyMetis, "Metis_690");
				break;
			case 21300:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721300);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723100, EnemyMetis, "Metis_691");
				break;
			case 21330:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721330);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723130, EnemyMetis, "Metis_692");
				break;
			case 21360:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721360);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723160, EnemyMetis, "Metis_693");
				break;
			case 21390:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721390);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723190, EnemyMetis, "Metis_694");
				break;
			case 21420:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721420);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723220, EnemyMetis, "Metis_695");
				break;
			case 21450:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721450);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723250, EnemyMetis, "Metis_696");
				break;
			case 21480:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721480);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723280, EnemyMetis, "Metis_697");
				break;
			case 21510:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721510);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723310, EnemyMetis, "Metis_698");
				break;
			case 21540:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721540);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723340, EnemyMetis, "Metis_699");
				break;
			case 21570:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721570);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723370, EnemyMetis, "Metis_700");
				break;
			case 21600:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721600);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723400, EnemyMetis, "Metis_701");
				break;
			case 21630:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721630);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723430, EnemyMetis, "Metis_702");
				break;
			case 21660:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721660);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723460, EnemyMetis, "Metis_703");
				break;
			case 21690:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721690);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723490, EnemyMetis, "Metis_704");
				break;
			case 21720:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721720);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723520, EnemyMetis, "Metis_705");
				break;
			case 21750:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721750);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723550, EnemyMetis, "Metis_706");
				break;
			case 21780:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721780);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723580, EnemyMetis, "Metis_707");
				break;
			case 21810:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721810);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723610, EnemyMetis, "Metis_708");
				break;
			case 21840:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721840);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723640, EnemyMetis, "Metis_709");
				break;
			case 21870:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721870);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723670, EnemyMetis, "Metis_710");
				break;
			case 21900:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721900);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723700, EnemyMetis, "Metis_711");
				break;
			case 21930:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721930);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723730, EnemyMetis, "Metis_712");
				break;
			case 21960:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721960);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723760, EnemyMetis, "Metis_713");
				break;
			case 21990:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721990);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723790, EnemyMetis, "Metis_714");
				break;
			case 22020:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722020);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723820, EnemyMetis, "Metis_715");
				break;
			case 22050:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722050);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723850, EnemyMetis, "Metis_716");
				break;
			case 22080:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722080);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723880, EnemyMetis, "Metis_717");
				break;
			case 22110:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722110);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723910, EnemyMetis, "Metis_718");
				break;
			case 22140:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722140);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723940, EnemyMetis, "Metis_719");
				break;
			case 22170:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722170);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723970, EnemyMetis, "Metis_720");
				break;
			case 22200:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722200);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724000, EnemyMetis, "Metis_721");
				break;
			case 22230:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722230);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724030, EnemyMetis, "Metis_722");
				break;
			case 22260:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722260);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724060, EnemyMetis, "Metis_723");
				break;
			case 22290:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722290);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724090, EnemyMetis, "Metis_724");
				break;
			case 22320:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722320);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724120, EnemyMetis, "Metis_725");
				break;
			case 22350:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722350);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724150, EnemyMetis, "Metis_726");
				break;
			case 22380:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722380);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724180, EnemyMetis, "Metis_727");
				break;
			case 22410:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722410);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724210, EnemyMetis, "Metis_728");
				break;
			case 22440:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722440);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724240, EnemyMetis, "Metis_729");
				break;
			case 22470:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722470);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724270, EnemyMetis, "Metis_730");
				break;
			case 22500:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722500);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724300, EnemyMetis, "Metis_731");
				break;
			case 22530:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722530);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724330, EnemyMetis, "Metis_732");
				break;
			case 22560:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722560);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724360, EnemyMetis, "Metis_733");
				break;
			case 22590:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722590);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724390, EnemyMetis, "Metis_734");
				break;
			case 22620:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722620);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724420, EnemyMetis, "Metis_735");
				break;
			case 22650:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722650);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724450, EnemyMetis, "Metis_736");
				break;
			case 22680:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722680);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724480, EnemyMetis, "Metis_737");
				break;
			case 22710:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722710);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724510, EnemyMetis, "Metis_738");
				break;
			case 22740:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722740);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724540, EnemyMetis, "Metis_739");
				break;
			case 22770:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722770);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724570, EnemyMetis, "Metis_740");
				break;
			case 22800:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722800);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724600, EnemyMetis, "Metis_741");
				break;
			case 22830:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722830);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724630, EnemyMetis, "Metis_742");
				break;
			case 22860:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722860);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724660, EnemyMetis, "Metis_743");
				break;
			case 22890:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722890);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724690, EnemyMetis, "Metis_744");
				break;
			case 22920:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722920);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724720, EnemyMetis, "Metis_745");
				break;
			case 22950:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722950);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724750, EnemyMetis, "Metis_746");
				break;
			case 22980:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722980);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724780, EnemyMetis, "Metis_747");
				break;
			case 23010:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723010);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724810, EnemyMetis, "Metis_748");
				break;
			case 23040:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723040);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724840, EnemyMetis, "Metis_749");
				break;
			case 23070:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723070);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724870, EnemyMetis, "Metis_750");
				break;
			case 23100:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723100);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724900, EnemyMetis, "Metis_751");
				break;
			case 23130:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723130);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724930, EnemyMetis, "Metis_752");
				break;
			case 23160:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723160);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724960, EnemyMetis, "Metis_753");
				break;
			case 23190:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723190);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724990, EnemyMetis, "Metis_754");
				break;
			case 23220:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723220);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725020, EnemyMetis, "Metis_755");
				break;
			case 23250:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723250);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725050, EnemyMetis, "Metis_756");
				break;
			case 23280:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723280);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725080, EnemyMetis, "Metis_757");
				break;
			case 23310:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723310);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725110, EnemyMetis, "Metis_758");
				break;
			case 23340:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723340);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725140, EnemyMetis, "Metis_759");
				break;
			case 23370:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723370);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725170, EnemyMetis, "Metis_760");
				break;
			case 23400:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723400);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725200, EnemyMetis, "Metis_761");
				break;
			case 23430:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723430);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725230, EnemyMetis, "Metis_762");
				break;
			case 23460:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723460);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725260, EnemyMetis, "Metis_763");
				break;
			case 23490:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723490);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725290, EnemyMetis, "Metis_764");
				break;
			case 23520:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723520);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725320, EnemyMetis, "Metis_765");
				break;
			case 23550:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723550);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725350, EnemyMetis, "Metis_766");
				break;
			case 23580:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723580);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725380, EnemyMetis, "Metis_767");
				break;
			case 23610:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723610);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725410, EnemyMetis, "Metis_768");
				break;
			case 23640:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723640);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725440, EnemyMetis, "Metis_769");
				break;
			case 23670:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723670);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725470, EnemyMetis, "Metis_770");
				break;
			case 23700:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723700);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725500, EnemyMetis, "Metis_771");
				break;
			case 23730:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723730);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725530, EnemyMetis, "Metis_772");
				break;
			case 23760:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723760);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725560, EnemyMetis, "Metis_773");
				break;
			case 23790:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723790);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725590, EnemyMetis, "Metis_774");
				break;
			case 23820:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723820);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725620, EnemyMetis, "Metis_775");
				break;
			case 23850:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723850);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725650, EnemyMetis, "Metis_776");
				break;
			case 23880:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723880);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725680, EnemyMetis, "Metis_777");
				break;
			case 23910:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723910);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725710, EnemyMetis, "Metis_778");
				break;
			case 23940:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723940);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725740, EnemyMetis, "Metis_779");
				break;
			case 23970:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723970);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725770, EnemyMetis, "Metis_780");
				break;
			case 24000:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724000);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725800, EnemyMetis, "Metis_781");
				break;
			case 24030:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724030);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725830, EnemyMetis, "Metis_782");
				break;
			case 24060:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724060);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725860, EnemyMetis, "Metis_783");
				break;
			case 24090:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724090);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725890, EnemyMetis, "Metis_784");
				break;
			case 24120:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724120);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725920, EnemyMetis, "Metis_785");
				break;
			case 24150:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724150);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725950, EnemyMetis, "Metis_786");
				break;
			case 24180:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724180);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725980, EnemyMetis, "Metis_787");
				break;
			case 24210:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724210);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726010, EnemyMetis, "Metis_788");
				break;
			case 24240:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724240);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726040, EnemyMetis, "Metis_789");
				break;
			case 24270:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724270);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726070, EnemyMetis, "Metis_790");
				break;
			case 24300:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724300);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726100, EnemyMetis, "Metis_791");
				break;
			case 24330:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724330);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726130, EnemyMetis, "Metis_792");
				break;
			case 24360:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724360);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726160, EnemyMetis, "Metis_793");
				break;
			case 24390:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724390);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726190, EnemyMetis, "Metis_794");
				break;
			case 24420:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724420);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726220, EnemyMetis, "Metis_795");
				break;
			case 24450:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724450);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726250, EnemyMetis, "Metis_796");
				break;
			case 24480:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724480);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726280, EnemyMetis, "Metis_797");
				break;
			case 24510:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724510);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726310, EnemyMetis, "Metis_798");
				break;
			case 24540:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724540);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726340, EnemyMetis, "Metis_799");
				break;
			case 24570:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724570);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726370, EnemyMetis, "Metis_800");
				break;
			case 24600:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724600);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726400, EnemyMetis, "Metis_801");
				break;
			case 24630:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724630);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726430, EnemyMetis, "Metis_802");
				break;
			case 24660:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724660);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726460, EnemyMetis, "Metis_803");
				break;
			case 24690:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724690);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726490, EnemyMetis, "Metis_804");
				break;
			case 24720:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724720);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726520, EnemyMetis, "Metis_805");
				break;
			case 24750:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724750);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726550, EnemyMetis, "Metis_806");
				break;
			case 24780:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724780);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726580, EnemyMetis, "Metis_807");
				break;
			case 24810:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724810);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726610, EnemyMetis, "Metis_808");
				break;
			case 24840:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724840);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726640, EnemyMetis, "Metis_809");
				break;
			case 24870:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724870);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726670, EnemyMetis, "Metis_810");
				break;
			case 24900:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724900);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726700, EnemyMetis, "Metis_811");
				break;
			case 24930:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724930);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726730, EnemyMetis, "Metis_812");
				break;
			case 24960:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724960);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726760, EnemyMetis, "Metis_813");
				break;
			case 24990:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724990);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726790, EnemyMetis, "Metis_814");
				break;
			case 25020:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725020);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726820, EnemyMetis, "Metis_815");
				break;
			case 25050:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725050);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726850, EnemyMetis, "Metis_816");
				break;
			case 25080:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725080);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726880, EnemyMetis, "Metis_817");
				break;
			case 25110:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725110);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726910, EnemyMetis, "Metis_818");
				break;
			case 25140:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725140);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726940, EnemyMetis, "Metis_819");
				break;
			case 25170:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725170);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726970, EnemyMetis, "Metis_820");
				break;
			case 25200:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725200);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727000, EnemyMetis, "Metis_821");
				break;
			case 25230:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725230);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727030, EnemyMetis, "Metis_822");
				break;
			case 25260:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725260);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727060, EnemyMetis, "Metis_823");
				break;
			case 25290:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725290);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727090, EnemyMetis, "Metis_824");
				break;
			case 25320:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725320);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727120, EnemyMetis, "Metis_825");
				break;
			case 25350:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725350);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727150, EnemyMetis, "Metis_826");
				break;
			case 25380:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725380);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727180, EnemyMetis, "Metis_827");
				break;
			case 25410:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725410);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727210, EnemyMetis, "Metis_828");
				break;
			case 25440:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725440);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727240, EnemyMetis, "Metis_829");
				break;
			case 25470:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725470);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727270, EnemyMetis, "Metis_830");
				break;
			case 25500:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725500);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727300, EnemyMetis, "Metis_831");
				break;
			case 25530:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725530);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727330, EnemyMetis, "Metis_832");
				break;
			case 25560:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725560);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727360, EnemyMetis, "Metis_833");
				break;
			case 25590:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725590);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727390, EnemyMetis, "Metis_834");
				break;
			case 25620:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725620);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727420, EnemyMetis, "Metis_835");
				break;
			case 25650:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725650);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727450, EnemyMetis, "Metis_836");
				break;
			case 25680:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725680);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727480, EnemyMetis, "Metis_837");
				break;
			case 25710:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725710);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727510, EnemyMetis, "Metis_838");
				break;
			case 25740:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725740);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727540, EnemyMetis, "Metis_839");
				break;
			case 25770:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725770);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727570, EnemyMetis, "Metis_840");
				break;
			case 25800:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725800);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727600, EnemyMetis, "Metis_841");
				break;
			case 25830:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725830);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727630, EnemyMetis, "Metis_842");
				break;
			case 25860:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725860);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727660, EnemyMetis, "Metis_843");
				break;
			case 25890:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725890);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727690, EnemyMetis, "Metis_844");
				break;
			case 25920:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725920);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727720, EnemyMetis, "Metis_845");
				break;
			case 25950:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725950);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727750, EnemyMetis, "Metis_846");
				break;
			case 25980:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725980);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727780, EnemyMetis, "Metis_847");
				break;
			case 26010:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726010);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727810, EnemyMetis, "Metis_848");
				break;
			case 26040:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726040);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727840, EnemyMetis, "Metis_849");
				break;
			case 26070:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726070);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727870, EnemyMetis, "Metis_850");
				break;
			case 26100:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726100);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727900, EnemyMetis, "Metis_851");
				break;
			case 26130:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726130);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727930, EnemyMetis, "Metis_852");
				break;
			case 26160:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726160);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727960, EnemyMetis, "Metis_853");
				break;
			case 26190:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726190);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727990, EnemyMetis, "Metis_854");
				break;
			case 26220:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726220);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728020, EnemyMetis, "Metis_855");
				break;
			case 26250:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726250);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728050, EnemyMetis, "Metis_856");
				break;
			case 26280:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726280);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728080, EnemyMetis, "Metis_857");
				break;
			case 26310:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726310);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728110, EnemyMetis, "Metis_858");
				break;
			case 26340:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726340);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728140, EnemyMetis, "Metis_859");
				break;
			case 26370:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726370);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728170, EnemyMetis, "Metis_860");
				break;
			case 26400:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726400);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728200, EnemyMetis, "Metis_861");
				break;
			case 26430:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726430);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728230, EnemyMetis, "Metis_862");
				break;
			case 26460:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726460);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728260, EnemyMetis, "Metis_863");
				break;
			case 26490:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726490);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728290, EnemyMetis, "Metis_864");
				break;
			case 26520:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726520);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728320, EnemyMetis, "Metis_865");
				break;
			case 26550:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726550);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728350, EnemyMetis, "Metis_866");
				break;
			case 26580:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726580);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728380, EnemyMetis, "Metis_867");
				break;
			case 26610:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726610);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728410, EnemyMetis, "Metis_868");
				break;
			case 26640:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726640);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728440, EnemyMetis, "Metis_869");
				break;
			case 26670:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726670);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728470, EnemyMetis, "Metis_870");
				break;
			case 26700:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726700);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728500, EnemyMetis, "Metis_871");
				break;
			case 26730:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726730);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728530, EnemyMetis, "Metis_872");
				break;
			case 26760:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726760);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728560, EnemyMetis, "Metis_873");
				break;
			case 26790:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726790);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728590, EnemyMetis, "Metis_874");
				break;
			case 26820:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726820);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728620, EnemyMetis, "Metis_875");
				break;
			case 26850:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726850);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728650, EnemyMetis, "Metis_876");
				break;
			case 26880:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726880);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728680, EnemyMetis, "Metis_877");
				break;
			case 26910:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726910);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728710, EnemyMetis, "Metis_878");
				break;
			case 26940:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726940);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728740, EnemyMetis, "Metis_879");
				break;
			case 26970:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726970);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728770, EnemyMetis, "Metis_880");
				break;
			case 27000:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727000);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728800, EnemyMetis, "Metis_881");
				break;
			case 27030:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727030);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728830, EnemyMetis, "Metis_882");
				break;
			case 27060:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727060);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728860, EnemyMetis, "Metis_883");
				break;
			case 27090:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727090);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728890, EnemyMetis, "Metis_884");
				break;
			case 27120:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727120);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728920, EnemyMetis, "Metis_885");
				break;
			case 27150:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727150);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728950, EnemyMetis, "Metis_886");
				break;
			case 27180:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727180);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728980, EnemyMetis, "Metis_887");
				break;
			case 27210:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727210);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729010, EnemyMetis, "Metis_888");
				break;
			case 27240:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727240);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729040, EnemyMetis, "Metis_889");
				break;
			case 27270:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727270);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729070, EnemyMetis, "Metis_890");
				break;
			case 27300:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727300);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729100, EnemyMetis, "Metis_891");
				break;
			case 27330:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727330);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729130, EnemyMetis, "Metis_892");
				break;
			case 27360:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727360);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729160, EnemyMetis, "Metis_893");
				break;
			case 27390:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727390);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729190, EnemyMetis, "Metis_894");
				break;
			case 27420:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727420);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729220, EnemyMetis, "Metis_895");
				break;
			case 27450:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727450);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729250, EnemyMetis, "Metis_896");
				break;
			case 27480:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727480);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729280, EnemyMetis, "Metis_897");
				break;
			case 27510:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727510);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729310, EnemyMetis, "Metis_898");
				break;
			case 27540:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727540);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729340, EnemyMetis, "Metis_899");
				break;
			case 27570:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727570);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729370, EnemyMetis, "Metis_900");
				break;
			case 27600:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727600);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729400, EnemyMetis, "Metis_901");
				break;
			case 27630:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727630);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729430, EnemyMetis, "Metis_902");
				break;
			case 27660:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727660);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729460, EnemyMetis, "Metis_903");
				break;
			case 27690:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727690);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729490, EnemyMetis, "Metis_904");
				break;
			case 27720:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727720);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729520, EnemyMetis, "Metis_905");
				break;
			case 27750:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727750);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729550, EnemyMetis, "Metis_906");
				break;
			case 27780:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727780);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729580, EnemyMetis, "Metis_907");
				break;
			case 27810:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727810);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729610, EnemyMetis, "Metis_908");
				break;
			case 27840:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727840);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729640, EnemyMetis, "Metis_909");
				break;
			case 27870:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727870);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729670, EnemyMetis, "Metis_910");
				break;
			case 27900:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727900);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729700, EnemyMetis, "Metis_911");
				break;
			case 27930:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727930);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729730, EnemyMetis, "Metis_912");
				break;
			case 27960:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727960);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729760, EnemyMetis, "Metis_913");
				break;
			case 27990:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727990);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729790, EnemyMetis, "Metis_914");
				break;
			case 28020:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728020);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729820, EnemyMetis, "Metis_915");
				break;
			case 28050:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728050);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729850, EnemyMetis, "Metis_916");
				break;
			case 28080:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728080);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729880, EnemyMetis, "Metis_917");
				break;
			case 28110:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728110);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729910, EnemyMetis, "Metis_918");
				break;
			case 28140:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728140);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729940, EnemyMetis, "Metis_919");
				break;
			case 28170:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728170);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729970, EnemyMetis, "Metis_920");
				break;
			case 28200:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728200);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117730000, EnemyMetis, "Metis_921");
				break;
			case 28230:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728230);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28260:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728260);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28290:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728290);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28320:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728320);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28350:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728350);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28380:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728380);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28410:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728410);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28440:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728440);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28470:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728470);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28500:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728500);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28530:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728530);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28560:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728560);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28590:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728590);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28620:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728620);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28650:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728650);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28680:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728680);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28710:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728710);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28740:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728740);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28770:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728770);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28800:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728800);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28830:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728830);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28860:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728860);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28890:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728890);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28920:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728920);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28950:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728950);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28980:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728980);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29010:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729010);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29040:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729040);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29070:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729070);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29100:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729100);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29130:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729130);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29160:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729160);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29190:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729190);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29220:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729220);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29250:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729250);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29280:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729280);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29310:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729310);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29340:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729340);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29370:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729370);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29400:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729400);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29430:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729430);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29460:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729460);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29490:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729490);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29520:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729520);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29550:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729550);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29580:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729580);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29610:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729610);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29640:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729640);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29670:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729670);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29700:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729700);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29730:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729730);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29760:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729760);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29790:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729790);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29820:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729820);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29850:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729850);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29880:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729880);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29910:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729910);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29940:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729940);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29970:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729970);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 30000:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117730000);
				getLordActor()->addSubGroup(pActor);
				}
				throwUpEvent(STG01_01_WAS_BROKEN,this);
				break;
			default :
				break;
		}
		_iCnt_Event = (_iCnt_Event < 987-1 ? _iCnt_Event+1 : _iCnt_Event);
	}
    // gen02 end

}

void Stage01_01::processFinal() {
}

Stage01_01::~Stage01_01() {

}
