#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Stage01MainScene::Stage01MainScene(const char* prm_name) : DefaultScene(prm_name) {

    _pDispatcher = NEW ActorDispatcher("RotEnemyMeshS001");
    EnemyMeshShot001* pEnemyMeshShot;
    for (int i = 0; i < 100; i++) {
        Sleep(1);
        pEnemyMeshShot = NEW EnemyMeshShot001("EnemyMeshShot");
        pEnemyMeshShot->inactivateTreeImmediately(); //最初非表示
        _pDispatcher->addSubLast(pEnemyMeshShot);
    }
    getLordActor()->addSubGroup(KIND_ENEMY_SHOT_CHOKI, _pDispatcher);

    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コード変更は「シーンCreater.xls」から行っていただきたい。
    // gen01 start
	DWORD dw[] = {1,10,30,50,70,90,110,130,150,170,190,210,230,250,270,290,310,330,350,370,390,410,430,450,470,490,500,510,530,550,560,570,590,610,620,630,650,670,690,710,730,750,770,790,810,830,850,870,890,910,930,950,970,990,1000,1010,1030,1050,1070,1090,1110,1130,1150,1170,1190,1210,1230,1250,1270,1290,1310,1330,1350,1370,1390,1410,1430,1450,1470,1490,1500,1510,1530,1550,1560,1570,1590,1610,1620,1630,1650,1670,1690,1710,1730,1750,1770,1790,1810,1830,1850,1870,1890,1910,1930,1950,1970,1990,2000,2010,2030,2050,2070,2090,2110,2130,2150,2170,2190,2210,2230,2250,2270,2290,2310,2330,2350,2370,2390,2410,2430,2450,2470,2490,2510,2530,2550,2570,2590,2610,2630,2650,2670,2690,2710,2730,2750,2770,2790,2810,2830,2850,2870,2890,2910,2930,2950,2970,2990,3000,3010,3030,3050,3070,3090,3110,3130,3150,3170,3190,3210,3230,3250,3270,3290,3310,3330,3350,3370,3390,3410,3430,3450,3470,3490,3510,3530,3550,3570,3590,3610,3630,3650,3670,3690,3710,3730,3750,3770,3790,3810,3830,3850,3870,3890,3910,3930,3950,3970,3990,4000,4010,4030,4050,4070,4090,4110,4130,4150,4170,4190,4210,4230,4250,4270,4290,4310,4330,4350,4370,4390,4410,4430,4450,4470,4490,4500,4510,4530,4550,4560,4570,4590,4610,4620,4630,4650,4670,4690,4710,4730,4750,4770,4790,4810,4830,4850,4870,4890,4910,4930,4950,4970,4990,5000,5010,5030,5050,5070,5090,5110,5130,5150,5170,5190,5210,5230,5250,5270,5290,5310,5330,5350,5370,5390,5410,5430,5450,5470,5490,5500,5510,5530,5550,5560,5570,5590,5610,5620,5630,5650,5670,5690,5710,5730,5750,5770,5790,5810,5830,5850,5870,5890,5910,5930,5950,5970,5990,6000,6010,6030,6050,6070,6090,6110,6130,6150,6170,6190,6210,6230,6250,6270,6290,6310,6330,6350,6370,6390,6410,6430,6450,6470,6490,6510,6530,6550,6570,6590,6610,6630,6650,6670,6690,6710,6730,6750,6770,6790,6810,6830,6850,6870,6890,6910,6930,6950,6970,6990,7000,7010,7030,7050,7070,7090,7110,7130,7150,7170,7190,7210,7230,7250,7270,7290,7310,7330,7350,7370,7390,7410,7430,7450,7470,7490,7510,7530,7550,7570,7590,7610,7630,7650,7670,7690,7710,7730,7750,7770,7790,7810,7830,7850,7870,7890,7910,7930,7950,7970,7990,8000,8010,8030,8050,8070,8090,8110,8130,8150,8170,8190,8210,8230,8250,8270,8290,8310,8330,8350,8370,8390,8410,8430,8450,8470,8490,8500,8510,8530,8550,8560,8570,8590,8610,8620,8630,8650,8670,8690,8710,8730,8750,8770,8790,8810,8830,8850,8870,8890,8910,8930,8950,8970,8990,9000,9010,9030,9050,9070,9090,9110,9130,9150,9170,9190,9210,9230,9250,9270,9290,9310,9330,9350,9370,9390,9410,9430,9450,9470,9490,9500,9510,9530,9550,9560,9570,9590,9610,9620,9630,9650,9670,9690,9710,9730,9750,9770,9790,9810,9830,9850,9870,9890,9910,9930,9950,9970,9990,10000,10010,10030,10050,10070,10090,10110,10130,10150,10170,10190,10210,10230,10250,10270,10290,10310,10330,10350,10370,10390,10410,10430,10450,10470,10490,10510,10530,10550,10570,10590,10610,10630,10650,10670,10690,10710,10730,10750,10770,10790,10810,10830,10850,10870,10890,10910,10930,10950,10970,10990,11000,11010,11030,11050,11070,11090,11110,11130,11150,11170,11190,11210,11230,11250,11270,11290,11310,11330,11350,11370,11390,11410,11430,11450,11470,11490,11510,11530,11550,11570,11590,11610,11630,11650,11670,11690,11710,11730,11750,11770,11790,11810,11830,11850,11870,11890,11910,11930,11950,11970,11990,12000,12010,12030,12050,12070,12090,12110,12130,12150,12170,12190,12210,12230,12250,12270,12290,12310,12330,12350,12370,12390,12410,12430,12450,12470,12490,12500,12510,12530,12550,12560,12570,12590,12610,12620,12630,12650,12670,12690,12710,12730,12750,12770,12790,12810,12830,12850,12870,12890,12910,12930,12950,12970,12990,13000,13010,13030,13050,13070,13090,13110,13130,13150,13170,13190,13210,13230,13250,13270,13290,13310,13330,13350,13370,13390,13410,13430,13450,13470,13490,13500,13510,13530,13550,13560,13570,13590,13610,13620,13630,13650,13670,13690,13710,13730,13750,13770,13790,13810,13830,13850,13870,13890,13910,13930,13950,13970,13990,14000,14010,14030,14050,14070,14090,14110,14130,14150,14170,14190,14210,14230,14250,14270,14290,14310,14330,14350,14370,14390,14410,14430,14450,14470,14490,14510,14530,14550,14570,14590,14610,14630,14650,14670,14690,14710,14730,14750,14770,14790,14810,14830,14850,14870,14890,14910,14930,14950,14970,14990,15000,15010,15030,15050,15070,15090,15110,15130,15150,15170,15190,15210,15230,15250,15270,15290,15310,15330,15350,15370,15390,15410,15430,15450,15470,15490,15510,15530,15550,15570,15590,15610,15630,15650,15670,15690,15710,15730,15750,15770,15790,15810,15830,15850,15870,15890,15910,15930,15950,15970,15990,16000,16010,16030,16050,16070,16090,16110,16130,16150,16170,16190,16210,16230,16250,16270,16290,16310,16330,16350,16370,16390,16410,16430,16450,16470,16490,16500,16510,16530,16550,16560,16570,16590,16610,16620,16630,16650,16670,16690,16710,16730,16750,16770,16790,16810,16830,16850,16870,16890,16910,16930,16950,16970,16990,17000,17010,17030,17050,17070,17090,17110,17130,17150,17170,17190,17210,17230,17250,17270,17290,17310,17330,17350,17370,17390,17410,17430,17450,17470,17490,17510,17530,17550,17570,17590,17610,17630,17650,17670,17690,17710,17730,17750,17770,17790,17810,17830,17850,17870,17890,17910,17930,17950,17970,17990,18010,18030,18050,18070,18090,18110,18130,18150,18170,18190,18210,18230,18250,18270,18290,18310,18330,18350,18370,18390,18410,18430,18450,18470,18490,18510,18530,18550,18570,18590,18610,18630,18650,18670,18690,18710,18730,18750,18770,18790,18810,18830,18850,18870,18890,18910,18930,18950,18970,18990,19000,19010,19030,19050,19070,19090,19110,19130,19150,19170,19190,19210,19230,19250,19270,19290,19310,19330,19350,19370,19390,19410,19430,19450,19470,19490,19510,19530,19550,19570,19590,19610,19630,19650,19670,19690,19710,19730,19750,19770,19790,19810,19830,19850,19870,19890,19910,19930,19950,19970,19990,20010,20030,20050,20070,20090,20110,20130,20150,20170,20190,20210,20230,20250,20270,20290,20310,20330,20350,20370,20390,20410,20430,20450,20470,20490,20510,20530,20550,20570,20590,20610,20630,20650,20670,20690,20710,20730,20750,20770,20790,20810,20830,20850,20870,20890,20910,20930,20950,20970,20990,21010,21030,21050,21070,21090,21110,21130,21150,21170,21190,21210,21230,21250,21270,21290,21310,21330,21350,21370,21390,21410,21430,21450,21470,21490,21510,21530,21550,21570,21590,21610,21630,21650,21670,21690,21710,21730,21750,21770,21790,21810,21830,21850,21870,21890,21910,21930,21950,21970,21990,22010,22030,22050,22070,22090,22110,22130,22150,22170,22190,22210,22230,22250,22270,22290,22310,22330,22350,22370,22390,22410,22430,22450,22470,22490,22510,22530,22550,22570,22590,22610,22630,22650,22670,22690,22710,22730,22750,22770,22790,22810,22830,22850,22870,22890,22910,22930,22950,22970,22990,23010,23030,23050,23070,23090,23110,23130,23150,23170,23190,23210,23230,23250,23270,23290,23310,23330,23350,23370,23390,23410,23430,23450,23470,23490,23510,23530,23550,23570,23590,23610,23630,23650,23670,23690,23710,23730,23750,23770,23790,23810,23830,23850,23870,23890,23910,23930,23950,23970,23990,24010,24030,24050,24070,24090,24110,24130,24150,24170,24190,24210,24230,24250,24270,24290,24310,24330,24350,24370,24390,24410,24430,24450,24470,24490,24510,24530,24550,24570,24590,24610,24630,24650,24670,24690,24710,24730,24750,24770,24790,24810,24830,24850,24870,24890,24910,24930,24950,24970,24990,25010,25030,25050,25070,25090,25110,25130,25150,25170,25190,25210,25230,25250,25270,25290,25310,25330,25350,25370,25390,25410,25430,25450,25470,25490,25510,25530,25550,25570,25590,25610,25630,25650,25670,25690,25710,25730,25750,25770,25790,25810,25830,25850,25870,25890,25910,25930,25950,25970,25990,26010,26030,26050,26070,26090,26110,26130,26150,26170,26190,26210,26230,26250,26270,26290,26310,26330,26350,26370,26390,26410,26430,26450,26470,26490,26510,26530,26550,26570,26590,26610,26630,26650,26670,26690,26710,26730,26750,26770,26790,26810,26830,26850,26870,26890,26910,26930,26950,26970,26990,27010,27030,27050,27070,27090,27110,27130,27150,27170,27190,27210,27230,27250,27270,27290,27310,27330,27350,27370,27390,27410,27430,27450,27470,27490,27510,27530,27550,27570,27590,27610,27630,27650,27670,27690,27710,27730,27750,27770,27790,27810,27830,27850,27870,27890,27910,27930,27950,27970,27990,28010,28030,28050,28070,28090,28110,28130,28150,28170,28190,28210,28230,28250,28270,28290,28310,28330,28350,28370,28390,28410,28430,28450,28470,28490,28510,28530,28550,28570,28590,28610,28630,28650,28670,28690,28710,28730,28750,28770,28790,28810,28830,28850,28870,28890,28910,28930,28950,28970,28990,29010,29030,29050,29070,29090,29110,29130,29150,29170,29190,29210,29230,29250,29270,29290,29310,29330,29350,29370,29390,29410,29430,29450,29470,29490,29510,29530,29550,29570,29590,29610,29630,29650,29670,29690,29710,29730,29750,29770,29790,29810,29830,29850,29870,29890,29910,29930,29950,29970,29990,30010,30030,30050,30070,30090,30110,30130,30150,30170,30190,30210,30230,30250,30270,30290,30310,30330,30350,30370,30390,30410,30430,30450,30470,30490,30510,30530,30550,30570,30590,30610,30630,30650,30670,30690,30710,30730,30750,30770,30790,30810,30830,30850,30870,30890,30910,30930,30950,30970,30990,31010,31030,31050,31070,31090,31110,31130,31150,31170,31190,31210,31230,31250,31270,31290,31310,31330,31350,31370,31390,31410,31430,31450,31470,31490,31510,31530,31550,31570,31590,31610,31630,31650,31670,31690,31710,31730,31750,31770,31790,31810,31830,31850,31870,31890,31910,31930,31950,31970,31990};
	_paFrame_NextEvent = new DWORD[1646];
	for (int i = 0; i < 1646; i++) {
		_paFrame_NextEvent[i] = dw[i];
	}
	orderActorToFactory(1105710, EnemyMetis, "Metis_1");
	orderActorToFactory(1105730, EnemyMetis, "Metis_2");
	orderActorToFactory(1105750, EnemyMetis, "Metis_3");
	orderActorToFactory(1105770, EnemyMetis, "Metis_4");
	orderActorToFactory(1105790, EnemyMetis, "Metis_5");
	orderActorToFactory(11057110, EnemyMetis, "Metis_6");
	orderActorToFactory(11057130, EnemyMetis, "Metis_7");
	orderActorToFactory(11057150, EnemyMetis, "Metis_8");
	orderActorToFactory(11057170, EnemyMetis, "Metis_9");
	orderActorToFactory(11057190, EnemyMetis, "Metis_10");
	orderActorToFactory(11057210, EnemyMetis, "Metis_11");
	orderActorToFactory(11057230, EnemyMetis, "Metis_12");
	orderActorToFactory(11057250, EnemyMetis, "Metis_13");
	orderActorToFactory(11057270, EnemyMetis, "Metis_14");
	orderActorToFactory(11057290, EnemyMetis, "Metis_15");
	orderActorToFactory(11057310, EnemyMetis, "Metis_16");
	orderActorToFactory(11057330, EnemyMetis, "Metis_17");
	orderActorToFactory(11057350, EnemyMetis, "Metis_18");
	orderActorToFactory(11057370, EnemyMetis, "Metis_19");
	orderActorToFactory(11057390, EnemyMetis, "Metis_20");
	orderActorToFactory(11057410, EnemyMetis, "Metis_21");
	orderActorToFactory(11057430, EnemyMetis, "Metis_22");
	orderActorToFactory(11057450, EnemyMetis, "Metis_23");
	orderActorToFactory(11057470, EnemyMetis, "Metis_24");
	orderActorToFactory(11057490, EnemyMetis, "Metis_25");
	orderActorToFactory(11057510, EnemyMetis, "Metis_26");
	orderActorToFactory(11057530, EnemyMetis, "Metis_27");
	orderActorToFactory(11057550, EnemyMetis, "Metis_28");
	orderActorToFactory(11057570, EnemyMetis, "Metis_29");
	orderActorToFactory(11057590, EnemyMetis, "Metis_30");
	orderActorToFactory(11057610, EnemyMetis, "Metis_31");
	orderActorToFactory(11057630, EnemyMetis, "Metis_32");
	orderActorToFactory(11057650, EnemyMetis, "Metis_33");
	orderActorToFactory(11057670, EnemyMetis, "Metis_34");
	orderActorToFactory(11057690, EnemyMetis, "Metis_35");
	orderActorToFactory(11057710, EnemyMetis, "Metis_36");
	orderActorToFactory(11057730, EnemyMetis, "Metis_37");
	orderActorToFactory(11057750, EnemyMetis, "Metis_38");
	orderActorToFactory(11057770, EnemyMetis, "Metis_39");
	orderActorToFactory(11057790, EnemyMetis, "Metis_40");
	orderActorToFactory(11057810, EnemyMetis, "Metis_41");
	orderActorToFactory(11057830, EnemyMetis, "Metis_42");
	orderActorToFactory(11057850, EnemyMetis, "Metis_43");
	orderActorToFactory(11057870, EnemyMetis, "Metis_44");
	orderActorToFactory(11057890, EnemyMetis, "Metis_45");
	orderActorToFactory(11057910, EnemyMetis, "Metis_46");
	orderActorToFactory(11057930, EnemyMetis, "Metis_47");
	orderActorToFactory(11057950, EnemyMetis, "Metis_48");
	orderActorToFactory(11057970, EnemyMetis, "Metis_49");
	orderActorToFactory(11057990, EnemyMetis, "Metis_50");
	orderActorToFactory(110571010, EnemyMetis, "Metis_51");
	orderActorToFactory(110571030, EnemyMetis, "Metis_52");
	orderActorToFactory(110571050, EnemyMetis, "Metis_53");
	orderActorToFactory(110571070, EnemyMetis, "Metis_54");
	orderActorToFactory(110571090, EnemyMetis, "Metis_55");
	orderActorToFactory(110571110, EnemyMetis, "Metis_56");
	orderActorToFactory(110571130, EnemyMetis, "Metis_57");
	orderActorToFactory(110571150, EnemyMetis, "Metis_58");
	orderActorToFactory(110571170, EnemyMetis, "Metis_59");
	orderActorToFactory(110571190, EnemyMetis, "Metis_60");
	orderActorToFactory(110571210, EnemyMetis, "Metis_61");
	orderActorToFactory(110571230, EnemyMetis, "Metis_62");
	orderActorToFactory(110571250, EnemyMetis, "Metis_63");
	orderActorToFactory(110571270, EnemyMetis, "Metis_64");
	orderActorToFactory(110571290, EnemyMetis, "Metis_65");
	orderActorToFactory(110571310, EnemyMetis, "Metis_66");
	orderActorToFactory(110571330, EnemyMetis, "Metis_67");
	orderActorToFactory(110571350, EnemyMetis, "Metis_68");
	orderActorToFactory(110571370, EnemyMetis, "Metis_69");
	orderActorToFactory(110571390, EnemyMetis, "Metis_70");
	orderActorToFactory(110571410, EnemyMetis, "Metis_71");
	orderActorToFactory(110571430, EnemyMetis, "Metis_72");
	orderActorToFactory(110571450, EnemyMetis, "Metis_73");
	orderActorToFactory(110571470, EnemyMetis, "Metis_74");
	orderActorToFactory(110571490, EnemyMetis, "Metis_75");
	orderActorToFactory(110571510, EnemyMetis, "Metis_76");
	orderActorToFactory(110571530, EnemyMetis, "Metis_77");
	orderActorToFactory(110571550, EnemyMetis, "Metis_78");
	orderActorToFactory(110571570, EnemyMetis, "Metis_79");
	orderActorToFactory(110571590, EnemyMetis, "Metis_80");
	orderActorToFactory(110571610, EnemyMetis, "Metis_81");
	orderActorToFactory(110571630, EnemyMetis, "Metis_82");
	orderActorToFactory(110571650, EnemyMetis, "Metis_83");
	orderActorToFactory(110571670, EnemyMetis, "Metis_84");
	orderActorToFactory(110571690, EnemyMetis, "Metis_85");
	orderActorToFactory(110571710, EnemyMetis, "Metis_86");
	orderActorToFactory(110571730, EnemyMetis, "Metis_87");
	orderActorToFactory(110571750, EnemyMetis, "Metis_88");
	orderActorToFactory(110571770, EnemyMetis, "Metis_89");
	orderActorToFactory(110571790, EnemyMetis, "Metis_90");
	orderActorToFactory(110571810, EnemyMetis, "Metis_91");
	orderActorToFactory(110571830, EnemyMetis, "Metis_92");
	orderActorToFactory(110571850, EnemyMetis, "Metis_93");
	orderActorToFactory(110571870, EnemyMetis, "Metis_94");
	orderActorToFactory(110571890, EnemyMetis, "Metis_95");
	orderActorToFactory(110571910, EnemyMetis, "Metis_96");
	orderActorToFactory(110571930, EnemyMetis, "Metis_97");
	orderActorToFactory(110571950, EnemyMetis, "Metis_98");
	orderActorToFactory(110571970, EnemyMetis, "Metis_99");
	orderActorToFactory(110571990, EnemyMetis, "Metis_100");
	orderActorToFactory(110572010, EnemyMetis, "Metis_101");
	orderActorToFactory(110572030, EnemyMetis, "Metis_102");
	orderActorToFactory(110572050, EnemyMetis, "Metis_103");
	orderActorToFactory(110572070, EnemyMetis, "Metis_104");
	orderActorToFactory(110572090, EnemyMetis, "Metis_105");
	orderActorToFactory(110572110, EnemyMetis, "Metis_106");
	orderActorToFactory(110572130, EnemyMetis, "Metis_107");
	orderActorToFactory(110572150, EnemyMetis, "Metis_108");
	orderActorToFactory(110572170, EnemyMetis, "Metis_109");
	orderActorToFactory(110572190, EnemyMetis, "Metis_110");
	orderActorToFactory(110572210, EnemyMetis, "Metis_111");
	orderActorToFactory(110572230, EnemyMetis, "Metis_112");
	orderActorToFactory(110572250, EnemyMetis, "Metis_113");
	orderActorToFactory(110572270, EnemyMetis, "Metis_114");
	orderActorToFactory(110572290, EnemyMetis, "Metis_115");
	orderActorToFactory(110572310, EnemyMetis, "Metis_116");
	orderActorToFactory(110572330, EnemyMetis, "Metis_117");
	orderActorToFactory(110572350, EnemyMetis, "Metis_118");
	orderActorToFactory(110572370, EnemyMetis, "Metis_119");
	orderActorToFactory(110572390, EnemyMetis, "Metis_120");
	orderActorToFactory(110572410, EnemyMetis, "Metis_121");
	orderActorToFactory(110572430, EnemyMetis, "Metis_122");
	orderActorToFactory(110572450, EnemyMetis, "Metis_123");
	orderActorToFactory(110572470, EnemyMetis, "Metis_124");
	orderActorToFactory(110572490, EnemyMetis, "Metis_125");
	orderActorToFactory(110572510, EnemyMetis, "Metis_126");
	orderActorToFactory(110572530, EnemyMetis, "Metis_127");
	orderActorToFactory(110572550, EnemyMetis, "Metis_128");
	orderActorToFactory(110572570, EnemyMetis, "Metis_129");
	orderActorToFactory(110572590, EnemyMetis, "Metis_130");
	orderActorToFactory(110572610, EnemyMetis, "Metis_131");
	orderActorToFactory(110572630, EnemyMetis, "Metis_132");
	orderActorToFactory(110572650, EnemyMetis, "Metis_133");
	orderActorToFactory(110572670, EnemyMetis, "Metis_134");
	orderActorToFactory(110572690, EnemyMetis, "Metis_135");
	orderActorToFactory(110572710, EnemyMetis, "Metis_136");
	orderActorToFactory(110572730, EnemyMetis, "Metis_137");
	orderActorToFactory(110572750, EnemyMetis, "Metis_138");
	orderActorToFactory(110572770, EnemyMetis, "Metis_139");
	orderActorToFactory(110572790, EnemyMetis, "Metis_140");
	orderActorToFactory(110572810, EnemyMetis, "Metis_141");
	orderActorToFactory(110572830, EnemyMetis, "Metis_142");
	orderActorToFactory(110572850, EnemyMetis, "Metis_143");
	orderActorToFactory(110572870, EnemyMetis, "Metis_144");
	orderActorToFactory(110572890, EnemyMetis, "Metis_145");
	orderActorToFactory(110572910, EnemyMetis, "Metis_146");
	orderActorToFactory(110572930, EnemyMetis, "Metis_147");
	orderActorToFactory(110572950, EnemyMetis, "Metis_148");
	orderActorToFactory(110572970, EnemyMetis, "Metis_149");
	orderActorToFactory(110572990, EnemyMetis, "Metis_150");
	orderActorToFactory(1124710, FormationIris001, "F001_Iris_151");
	orderActorToFactory(112472010, FormationIris001, "F001_Iris_152");
	orderActorToFactory(112571000, FormationIris002, "F002_Iris_153");
	orderActorToFactory(112573000, FormationIris002, "F002_Iris_154");
	orderActorWithDpToFactory(11277500, EnemyCeres, "Ceres_155", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(11287530, EnemyCeres, "Ceres_156", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(11297560, EnemyCeres, "Ceres_157", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(11307590, EnemyCeres, "Ceres_158", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(11317620, EnemyCeres, "Ceres_159", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(11327650, EnemyCeres, "Ceres_160", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
    // gen01 end
}

void Stage01MainScene::initialize() {

}

void Stage01MainScene::processBehavior() {
    // 以下の gen02 start ～ end はマクロにより自動生成されたコードです。
    // gen02 start
	if (getPartFrame() == _paFrame_NextEvent[_iCnt_Event]) {
		switch (getPartFrame()) {
			case 1:
				break;
			case 10:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105710));
				orderActorToFactory(110573010, EnemyMetis, "Metis_161");
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(1124710);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 30:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105730));
				orderActorToFactory(110573030, EnemyMetis, "Metis_162");
				break;
			case 50:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105750));
				orderActorToFactory(110573050, EnemyMetis, "Metis_163");
				break;
			case 70:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105770));
				orderActorToFactory(110573070, EnemyMetis, "Metis_164");
				break;
			case 90:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105790));
				orderActorToFactory(110573090, EnemyMetis, "Metis_165");
				break;
			case 110:
				getLordActor()->addSubGroup(obtainActorFromFactory(11057110));
				orderActorToFactory(110573110, EnemyMetis, "Metis_166");
				break;
			case 130:
				getLordActor()->addSubGroup(obtainActorFromFactory(11057130));
				orderActorToFactory(110573130, EnemyMetis, "Metis_167");
				break;
			case 150:
				getLordActor()->addSubGroup(obtainActorFromFactory(11057150));
				orderActorToFactory(110573150, EnemyMetis, "Metis_168");
				break;
			case 170:
				getLordActor()->addSubGroup(obtainActorFromFactory(11057170));
				orderActorToFactory(110573170, EnemyMetis, "Metis_169");
				break;
			case 190:
				getLordActor()->addSubGroup(obtainActorFromFactory(11057190));
				orderActorToFactory(110573190, EnemyMetis, "Metis_170");
				break;
			case 210:
				getLordActor()->addSubGroup(obtainActorFromFactory(11057210));
				orderActorToFactory(110573210, EnemyMetis, "Metis_171");
				break;
			case 230:
				getLordActor()->addSubGroup(obtainActorFromFactory(11057230));
				orderActorToFactory(110573230, EnemyMetis, "Metis_172");
				break;
			case 250:
				getLordActor()->addSubGroup(obtainActorFromFactory(11057250));
				orderActorToFactory(110573250, EnemyMetis, "Metis_173");
				break;
			case 270:
				getLordActor()->addSubGroup(obtainActorFromFactory(11057270));
				orderActorToFactory(110573270, EnemyMetis, "Metis_174");
				break;
			case 290:
				getLordActor()->addSubGroup(obtainActorFromFactory(11057290));
				orderActorToFactory(110573290, EnemyMetis, "Metis_175");
				break;
			case 310:
				getLordActor()->addSubGroup(obtainActorFromFactory(11057310));
				orderActorToFactory(110573310, EnemyMetis, "Metis_176");
				break;
			case 330:
				getLordActor()->addSubGroup(obtainActorFromFactory(11057330));
				orderActorToFactory(110573330, EnemyMetis, "Metis_177");
				break;
			case 350:
				getLordActor()->addSubGroup(obtainActorFromFactory(11057350));
				orderActorToFactory(110573350, EnemyMetis, "Metis_178");
				break;
			case 370:
				getLordActor()->addSubGroup(obtainActorFromFactory(11057370));
				orderActorToFactory(110573370, EnemyMetis, "Metis_179");
				break;
			case 390:
				getLordActor()->addSubGroup(obtainActorFromFactory(11057390));
				orderActorToFactory(110573390, EnemyMetis, "Metis_180");
				break;
			case 410:
				getLordActor()->addSubGroup(obtainActorFromFactory(11057410));
				orderActorToFactory(110573410, EnemyMetis, "Metis_181");
				break;
			case 430:
				getLordActor()->addSubGroup(obtainActorFromFactory(11057430));
				orderActorToFactory(110573430, EnemyMetis, "Metis_182");
				break;
			case 450:
				getLordActor()->addSubGroup(obtainActorFromFactory(11057450));
				orderActorToFactory(110573450, EnemyMetis, "Metis_183");
				break;
			case 470:
				getLordActor()->addSubGroup(obtainActorFromFactory(11057470));
				orderActorToFactory(110573470, EnemyMetis, "Metis_184");
				break;
			case 490:
				getLordActor()->addSubGroup(obtainActorFromFactory(11057490));
				orderActorToFactory(110573490, EnemyMetis, "Metis_185");
				break;
			case 500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11277500);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 510:
				getLordActor()->addSubGroup(obtainActorFromFactory(11057510));
				orderActorToFactory(110573510, EnemyMetis, "Metis_186");
				break;
			case 530:
				getLordActor()->addSubGroup(obtainActorFromFactory(11057530));
				orderActorToFactory(110573530, EnemyMetis, "Metis_187");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11287530);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 550:
				getLordActor()->addSubGroup(obtainActorFromFactory(11057550));
				orderActorToFactory(110573550, EnemyMetis, "Metis_188");
				break;
			case 560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11297560);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 570:
				getLordActor()->addSubGroup(obtainActorFromFactory(11057570));
				orderActorToFactory(110573570, EnemyMetis, "Metis_189");
				break;
			case 590:
				getLordActor()->addSubGroup(obtainActorFromFactory(11057590));
				orderActorToFactory(110573590, EnemyMetis, "Metis_190");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11307590);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 610:
				getLordActor()->addSubGroup(obtainActorFromFactory(11057610));
				orderActorToFactory(110573610, EnemyMetis, "Metis_191");
				break;
			case 620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11317620);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 630:
				getLordActor()->addSubGroup(obtainActorFromFactory(11057630));
				orderActorToFactory(110573630, EnemyMetis, "Metis_192");
				break;
			case 650:
				getLordActor()->addSubGroup(obtainActorFromFactory(11057650));
				orderActorToFactory(110573650, EnemyMetis, "Metis_193");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11327650);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 670:
				getLordActor()->addSubGroup(obtainActorFromFactory(11057670));
				orderActorToFactory(110573670, EnemyMetis, "Metis_194");
				break;
			case 690:
				getLordActor()->addSubGroup(obtainActorFromFactory(11057690));
				orderActorToFactory(110573690, EnemyMetis, "Metis_195");
				break;
			case 710:
				getLordActor()->addSubGroup(obtainActorFromFactory(11057710));
				orderActorToFactory(110573710, EnemyMetis, "Metis_196");
				break;
			case 730:
				getLordActor()->addSubGroup(obtainActorFromFactory(11057730));
				orderActorToFactory(110573730, EnemyMetis, "Metis_197");
				break;
			case 750:
				getLordActor()->addSubGroup(obtainActorFromFactory(11057750));
				orderActorToFactory(110573750, EnemyMetis, "Metis_198");
				break;
			case 770:
				getLordActor()->addSubGroup(obtainActorFromFactory(11057770));
				orderActorToFactory(110573770, EnemyMetis, "Metis_199");
				break;
			case 790:
				getLordActor()->addSubGroup(obtainActorFromFactory(11057790));
				orderActorToFactory(110573790, EnemyMetis, "Metis_200");
				break;
			case 810:
				getLordActor()->addSubGroup(obtainActorFromFactory(11057810));
				orderActorToFactory(110573810, EnemyMetis, "Metis_201");
				break;
			case 830:
				getLordActor()->addSubGroup(obtainActorFromFactory(11057830));
				orderActorToFactory(110573830, EnemyMetis, "Metis_202");
				break;
			case 850:
				getLordActor()->addSubGroup(obtainActorFromFactory(11057850));
				orderActorToFactory(110573850, EnemyMetis, "Metis_203");
				break;
			case 870:
				getLordActor()->addSubGroup(obtainActorFromFactory(11057870));
				orderActorToFactory(110573870, EnemyMetis, "Metis_204");
				break;
			case 890:
				getLordActor()->addSubGroup(obtainActorFromFactory(11057890));
				orderActorToFactory(110573890, EnemyMetis, "Metis_205");
				break;
			case 910:
				getLordActor()->addSubGroup(obtainActorFromFactory(11057910));
				orderActorToFactory(110573910, EnemyMetis, "Metis_206");
				break;
			case 930:
				getLordActor()->addSubGroup(obtainActorFromFactory(11057930));
				orderActorToFactory(110573930, EnemyMetis, "Metis_207");
				break;
			case 950:
				getLordActor()->addSubGroup(obtainActorFromFactory(11057950));
				orderActorToFactory(110573950, EnemyMetis, "Metis_208");
				break;
			case 970:
				getLordActor()->addSubGroup(obtainActorFromFactory(11057970));
				orderActorToFactory(110573970, EnemyMetis, "Metis_209");
				break;
			case 990:
				getLordActor()->addSubGroup(obtainActorFromFactory(11057990));
				orderActorToFactory(110573990, EnemyMetis, "Metis_210");
				break;
			case 1000:
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(112571000);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 1010:
				getLordActor()->addSubGroup(obtainActorFromFactory(110571010));
				orderActorToFactory(110574010, EnemyMetis, "Metis_211");
				orderActorToFactory(112474010, FormationIris001, "F001_Iris_212");
				break;
			case 1030:
				getLordActor()->addSubGroup(obtainActorFromFactory(110571030));
				orderActorToFactory(110574030, EnemyMetis, "Metis_213");
				break;
			case 1050:
				getLordActor()->addSubGroup(obtainActorFromFactory(110571050));
				orderActorToFactory(110574050, EnemyMetis, "Metis_214");
				break;
			case 1070:
				getLordActor()->addSubGroup(obtainActorFromFactory(110571070));
				orderActorToFactory(110574070, EnemyMetis, "Metis_215");
				break;
			case 1090:
				getLordActor()->addSubGroup(obtainActorFromFactory(110571090));
				orderActorToFactory(110574090, EnemyMetis, "Metis_216");
				break;
			case 1110:
				getLordActor()->addSubGroup(obtainActorFromFactory(110571110));
				orderActorToFactory(110574110, EnemyMetis, "Metis_217");
				break;
			case 1130:
				getLordActor()->addSubGroup(obtainActorFromFactory(110571130));
				orderActorToFactory(110574130, EnemyMetis, "Metis_218");
				break;
			case 1150:
				getLordActor()->addSubGroup(obtainActorFromFactory(110571150));
				orderActorToFactory(110574150, EnemyMetis, "Metis_219");
				break;
			case 1170:
				getLordActor()->addSubGroup(obtainActorFromFactory(110571170));
				orderActorToFactory(110574170, EnemyMetis, "Metis_220");
				break;
			case 1190:
				getLordActor()->addSubGroup(obtainActorFromFactory(110571190));
				orderActorToFactory(110574190, EnemyMetis, "Metis_221");
				break;
			case 1210:
				getLordActor()->addSubGroup(obtainActorFromFactory(110571210));
				orderActorToFactory(110574210, EnemyMetis, "Metis_222");
				break;
			case 1230:
				getLordActor()->addSubGroup(obtainActorFromFactory(110571230));
				orderActorToFactory(110574230, EnemyMetis, "Metis_223");
				break;
			case 1250:
				getLordActor()->addSubGroup(obtainActorFromFactory(110571250));
				orderActorToFactory(110574250, EnemyMetis, "Metis_224");
				break;
			case 1270:
				getLordActor()->addSubGroup(obtainActorFromFactory(110571270));
				orderActorToFactory(110574270, EnemyMetis, "Metis_225");
				break;
			case 1290:
				getLordActor()->addSubGroup(obtainActorFromFactory(110571290));
				orderActorToFactory(110574290, EnemyMetis, "Metis_226");
				break;
			case 1310:
				getLordActor()->addSubGroup(obtainActorFromFactory(110571310));
				orderActorToFactory(110574310, EnemyMetis, "Metis_227");
				break;
			case 1330:
				getLordActor()->addSubGroup(obtainActorFromFactory(110571330));
				orderActorToFactory(110574330, EnemyMetis, "Metis_228");
				break;
			case 1350:
				getLordActor()->addSubGroup(obtainActorFromFactory(110571350));
				orderActorToFactory(110574350, EnemyMetis, "Metis_229");
				break;
			case 1370:
				getLordActor()->addSubGroup(obtainActorFromFactory(110571370));
				orderActorToFactory(110574370, EnemyMetis, "Metis_230");
				break;
			case 1390:
				getLordActor()->addSubGroup(obtainActorFromFactory(110571390));
				orderActorToFactory(110574390, EnemyMetis, "Metis_231");
				break;
			case 1410:
				getLordActor()->addSubGroup(obtainActorFromFactory(110571410));
				orderActorToFactory(110574410, EnemyMetis, "Metis_232");
				break;
			case 1430:
				getLordActor()->addSubGroup(obtainActorFromFactory(110571430));
				orderActorToFactory(110574430, EnemyMetis, "Metis_233");
				break;
			case 1450:
				getLordActor()->addSubGroup(obtainActorFromFactory(110571450));
				orderActorToFactory(110574450, EnemyMetis, "Metis_234");
				break;
			case 1470:
				getLordActor()->addSubGroup(obtainActorFromFactory(110571470));
				orderActorToFactory(110574470, EnemyMetis, "Metis_235");
				break;
			case 1490:
				getLordActor()->addSubGroup(obtainActorFromFactory(110571490));
				orderActorToFactory(110574490, EnemyMetis, "Metis_236");
				break;
			case 1500:
				orderActorWithDpToFactory(112774500, EnemyCeres, "Ceres_237", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 1510:
				getLordActor()->addSubGroup(obtainActorFromFactory(110571510));
				orderActorToFactory(110574510, EnemyMetis, "Metis_238");
				break;
			case 1530:
				getLordActor()->addSubGroup(obtainActorFromFactory(110571530));
				orderActorToFactory(110574530, EnemyMetis, "Metis_239");
				orderActorWithDpToFactory(112874530, EnemyCeres, "Ceres_240", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 1550:
				getLordActor()->addSubGroup(obtainActorFromFactory(110571550));
				orderActorToFactory(110574550, EnemyMetis, "Metis_241");
				break;
			case 1560:
				orderActorWithDpToFactory(112974560, EnemyCeres, "Ceres_242", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 1570:
				getLordActor()->addSubGroup(obtainActorFromFactory(110571570));
				orderActorToFactory(110574570, EnemyMetis, "Metis_243");
				break;
			case 1590:
				getLordActor()->addSubGroup(obtainActorFromFactory(110571590));
				orderActorToFactory(110574590, EnemyMetis, "Metis_244");
				orderActorWithDpToFactory(113074590, EnemyCeres, "Ceres_245", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 1610:
				getLordActor()->addSubGroup(obtainActorFromFactory(110571610));
				orderActorToFactory(110574610, EnemyMetis, "Metis_246");
				break;
			case 1620:
				orderActorWithDpToFactory(113174620, EnemyCeres, "Ceres_247", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 1630:
				getLordActor()->addSubGroup(obtainActorFromFactory(110571630));
				orderActorToFactory(110574630, EnemyMetis, "Metis_248");
				break;
			case 1650:
				getLordActor()->addSubGroup(obtainActorFromFactory(110571650));
				orderActorToFactory(110574650, EnemyMetis, "Metis_249");
				orderActorWithDpToFactory(113274650, EnemyCeres, "Ceres_250", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 1670:
				getLordActor()->addSubGroup(obtainActorFromFactory(110571670));
				orderActorToFactory(110574670, EnemyMetis, "Metis_251");
				break;
			case 1690:
				getLordActor()->addSubGroup(obtainActorFromFactory(110571690));
				orderActorToFactory(110574690, EnemyMetis, "Metis_252");
				break;
			case 1710:
				getLordActor()->addSubGroup(obtainActorFromFactory(110571710));
				orderActorToFactory(110574710, EnemyMetis, "Metis_253");
				break;
			case 1730:
				getLordActor()->addSubGroup(obtainActorFromFactory(110571730));
				orderActorToFactory(110574730, EnemyMetis, "Metis_254");
				break;
			case 1750:
				getLordActor()->addSubGroup(obtainActorFromFactory(110571750));
				orderActorToFactory(110574750, EnemyMetis, "Metis_255");
				break;
			case 1770:
				getLordActor()->addSubGroup(obtainActorFromFactory(110571770));
				orderActorToFactory(110574770, EnemyMetis, "Metis_256");
				break;
			case 1790:
				getLordActor()->addSubGroup(obtainActorFromFactory(110571790));
				orderActorToFactory(110574790, EnemyMetis, "Metis_257");
				break;
			case 1810:
				getLordActor()->addSubGroup(obtainActorFromFactory(110571810));
				orderActorToFactory(110574810, EnemyMetis, "Metis_258");
				break;
			case 1830:
				getLordActor()->addSubGroup(obtainActorFromFactory(110571830));
				orderActorToFactory(110574830, EnemyMetis, "Metis_259");
				break;
			case 1850:
				getLordActor()->addSubGroup(obtainActorFromFactory(110571850));
				orderActorToFactory(110574850, EnemyMetis, "Metis_260");
				break;
			case 1870:
				getLordActor()->addSubGroup(obtainActorFromFactory(110571870));
				orderActorToFactory(110574870, EnemyMetis, "Metis_261");
				break;
			case 1890:
				getLordActor()->addSubGroup(obtainActorFromFactory(110571890));
				orderActorToFactory(110574890, EnemyMetis, "Metis_262");
				break;
			case 1910:
				getLordActor()->addSubGroup(obtainActorFromFactory(110571910));
				orderActorToFactory(110574910, EnemyMetis, "Metis_263");
				break;
			case 1930:
				getLordActor()->addSubGroup(obtainActorFromFactory(110571930));
				orderActorToFactory(110574930, EnemyMetis, "Metis_264");
				break;
			case 1950:
				getLordActor()->addSubGroup(obtainActorFromFactory(110571950));
				orderActorToFactory(110574950, EnemyMetis, "Metis_265");
				break;
			case 1970:
				getLordActor()->addSubGroup(obtainActorFromFactory(110571970));
				orderActorToFactory(110574970, EnemyMetis, "Metis_266");
				break;
			case 1990:
				getLordActor()->addSubGroup(obtainActorFromFactory(110571990));
				orderActorToFactory(110574990, EnemyMetis, "Metis_267");
				break;
			case 2000:
				orderActorToFactory(112575000, FormationIris002, "F002_Iris_268");
				break;
			case 2010:
				getLordActor()->addSubGroup(obtainActorFromFactory(110572010));
				orderActorToFactory(110575010, EnemyMetis, "Metis_269");
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(112472010);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 2030:
				getLordActor()->addSubGroup(obtainActorFromFactory(110572030));
				orderActorToFactory(110575030, EnemyMetis, "Metis_270");
				break;
			case 2050:
				getLordActor()->addSubGroup(obtainActorFromFactory(110572050));
				orderActorToFactory(110575050, EnemyMetis, "Metis_271");
				break;
			case 2070:
				getLordActor()->addSubGroup(obtainActorFromFactory(110572070));
				orderActorToFactory(110575070, EnemyMetis, "Metis_272");
				break;
			case 2090:
				getLordActor()->addSubGroup(obtainActorFromFactory(110572090));
				orderActorToFactory(110575090, EnemyMetis, "Metis_273");
				break;
			case 2110:
				getLordActor()->addSubGroup(obtainActorFromFactory(110572110));
				orderActorToFactory(110575110, EnemyMetis, "Metis_274");
				break;
			case 2130:
				getLordActor()->addSubGroup(obtainActorFromFactory(110572130));
				orderActorToFactory(110575130, EnemyMetis, "Metis_275");
				break;
			case 2150:
				getLordActor()->addSubGroup(obtainActorFromFactory(110572150));
				orderActorToFactory(110575150, EnemyMetis, "Metis_276");
				break;
			case 2170:
				getLordActor()->addSubGroup(obtainActorFromFactory(110572170));
				orderActorToFactory(110575170, EnemyMetis, "Metis_277");
				break;
			case 2190:
				getLordActor()->addSubGroup(obtainActorFromFactory(110572190));
				orderActorToFactory(110575190, EnemyMetis, "Metis_278");
				break;
			case 2210:
				getLordActor()->addSubGroup(obtainActorFromFactory(110572210));
				orderActorToFactory(110575210, EnemyMetis, "Metis_279");
				break;
			case 2230:
				getLordActor()->addSubGroup(obtainActorFromFactory(110572230));
				orderActorToFactory(110575230, EnemyMetis, "Metis_280");
				break;
			case 2250:
				getLordActor()->addSubGroup(obtainActorFromFactory(110572250));
				orderActorToFactory(110575250, EnemyMetis, "Metis_281");
				break;
			case 2270:
				getLordActor()->addSubGroup(obtainActorFromFactory(110572270));
				orderActorToFactory(110575270, EnemyMetis, "Metis_282");
				break;
			case 2290:
				getLordActor()->addSubGroup(obtainActorFromFactory(110572290));
				orderActorToFactory(110575290, EnemyMetis, "Metis_283");
				break;
			case 2310:
				getLordActor()->addSubGroup(obtainActorFromFactory(110572310));
				orderActorToFactory(110575310, EnemyMetis, "Metis_284");
				break;
			case 2330:
				getLordActor()->addSubGroup(obtainActorFromFactory(110572330));
				orderActorToFactory(110575330, EnemyMetis, "Metis_285");
				break;
			case 2350:
				getLordActor()->addSubGroup(obtainActorFromFactory(110572350));
				orderActorToFactory(110575350, EnemyMetis, "Metis_286");
				break;
			case 2370:
				getLordActor()->addSubGroup(obtainActorFromFactory(110572370));
				orderActorToFactory(110575370, EnemyMetis, "Metis_287");
				break;
			case 2390:
				getLordActor()->addSubGroup(obtainActorFromFactory(110572390));
				orderActorToFactory(110575390, EnemyMetis, "Metis_288");
				break;
			case 2410:
				getLordActor()->addSubGroup(obtainActorFromFactory(110572410));
				orderActorToFactory(110575410, EnemyMetis, "Metis_289");
				break;
			case 2430:
				getLordActor()->addSubGroup(obtainActorFromFactory(110572430));
				orderActorToFactory(110575430, EnemyMetis, "Metis_290");
				break;
			case 2450:
				getLordActor()->addSubGroup(obtainActorFromFactory(110572450));
				orderActorToFactory(110575450, EnemyMetis, "Metis_291");
				break;
			case 2470:
				getLordActor()->addSubGroup(obtainActorFromFactory(110572470));
				orderActorToFactory(110575470, EnemyMetis, "Metis_292");
				break;
			case 2490:
				getLordActor()->addSubGroup(obtainActorFromFactory(110572490));
				orderActorToFactory(110575490, EnemyMetis, "Metis_293");
				break;
			case 2510:
				getLordActor()->addSubGroup(obtainActorFromFactory(110572510));
				orderActorToFactory(110575510, EnemyMetis, "Metis_294");
				break;
			case 2530:
				getLordActor()->addSubGroup(obtainActorFromFactory(110572530));
				orderActorToFactory(110575530, EnemyMetis, "Metis_295");
				break;
			case 2550:
				getLordActor()->addSubGroup(obtainActorFromFactory(110572550));
				orderActorToFactory(110575550, EnemyMetis, "Metis_296");
				break;
			case 2570:
				getLordActor()->addSubGroup(obtainActorFromFactory(110572570));
				orderActorToFactory(110575570, EnemyMetis, "Metis_297");
				break;
			case 2590:
				getLordActor()->addSubGroup(obtainActorFromFactory(110572590));
				orderActorToFactory(110575590, EnemyMetis, "Metis_298");
				break;
			case 2610:
				getLordActor()->addSubGroup(obtainActorFromFactory(110572610));
				orderActorToFactory(110575610, EnemyMetis, "Metis_299");
				break;
			case 2630:
				getLordActor()->addSubGroup(obtainActorFromFactory(110572630));
				orderActorToFactory(110575630, EnemyMetis, "Metis_300");
				break;
			case 2650:
				getLordActor()->addSubGroup(obtainActorFromFactory(110572650));
				orderActorToFactory(110575650, EnemyMetis, "Metis_301");
				break;
			case 2670:
				getLordActor()->addSubGroup(obtainActorFromFactory(110572670));
				orderActorToFactory(110575670, EnemyMetis, "Metis_302");
				break;
			case 2690:
				getLordActor()->addSubGroup(obtainActorFromFactory(110572690));
				orderActorToFactory(110575690, EnemyMetis, "Metis_303");
				break;
			case 2710:
				getLordActor()->addSubGroup(obtainActorFromFactory(110572710));
				orderActorToFactory(110575710, EnemyMetis, "Metis_304");
				break;
			case 2730:
				getLordActor()->addSubGroup(obtainActorFromFactory(110572730));
				orderActorToFactory(110575730, EnemyMetis, "Metis_305");
				break;
			case 2750:
				getLordActor()->addSubGroup(obtainActorFromFactory(110572750));
				orderActorToFactory(110575750, EnemyMetis, "Metis_306");
				break;
			case 2770:
				getLordActor()->addSubGroup(obtainActorFromFactory(110572770));
				orderActorToFactory(110575770, EnemyMetis, "Metis_307");
				break;
			case 2790:
				getLordActor()->addSubGroup(obtainActorFromFactory(110572790));
				orderActorToFactory(110575790, EnemyMetis, "Metis_308");
				break;
			case 2810:
				getLordActor()->addSubGroup(obtainActorFromFactory(110572810));
				orderActorToFactory(110575810, EnemyMetis, "Metis_309");
				break;
			case 2830:
				getLordActor()->addSubGroup(obtainActorFromFactory(110572830));
				orderActorToFactory(110575830, EnemyMetis, "Metis_310");
				break;
			case 2850:
				getLordActor()->addSubGroup(obtainActorFromFactory(110572850));
				orderActorToFactory(110575850, EnemyMetis, "Metis_311");
				break;
			case 2870:
				getLordActor()->addSubGroup(obtainActorFromFactory(110572870));
				orderActorToFactory(110575870, EnemyMetis, "Metis_312");
				break;
			case 2890:
				getLordActor()->addSubGroup(obtainActorFromFactory(110572890));
				orderActorToFactory(110575890, EnemyMetis, "Metis_313");
				break;
			case 2910:
				getLordActor()->addSubGroup(obtainActorFromFactory(110572910));
				orderActorToFactory(110575910, EnemyMetis, "Metis_314");
				break;
			case 2930:
				getLordActor()->addSubGroup(obtainActorFromFactory(110572930));
				orderActorToFactory(110575930, EnemyMetis, "Metis_315");
				break;
			case 2950:
				getLordActor()->addSubGroup(obtainActorFromFactory(110572950));
				orderActorToFactory(110575950, EnemyMetis, "Metis_316");
				break;
			case 2970:
				getLordActor()->addSubGroup(obtainActorFromFactory(110572970));
				orderActorToFactory(110575970, EnemyMetis, "Metis_317");
				break;
			case 2990:
				getLordActor()->addSubGroup(obtainActorFromFactory(110572990));
				orderActorToFactory(110575990, EnemyMetis, "Metis_318");
				break;
			case 3000:
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(112573000);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 3010:
				getLordActor()->addSubGroup(obtainActorFromFactory(110573010));
				orderActorToFactory(110576010, EnemyMetis, "Metis_319");
				orderActorToFactory(112476010, FormationIris001, "F001_Iris_320");
				break;
			case 3030:
				getLordActor()->addSubGroup(obtainActorFromFactory(110573030));
				orderActorToFactory(110576030, EnemyMetis, "Metis_321");
				break;
			case 3050:
				getLordActor()->addSubGroup(obtainActorFromFactory(110573050));
				orderActorToFactory(110576050, EnemyMetis, "Metis_322");
				break;
			case 3070:
				getLordActor()->addSubGroup(obtainActorFromFactory(110573070));
				orderActorToFactory(110576070, EnemyMetis, "Metis_323");
				break;
			case 3090:
				getLordActor()->addSubGroup(obtainActorFromFactory(110573090));
				orderActorToFactory(110576090, EnemyMetis, "Metis_324");
				break;
			case 3110:
				getLordActor()->addSubGroup(obtainActorFromFactory(110573110));
				orderActorToFactory(110576110, EnemyMetis, "Metis_325");
				break;
			case 3130:
				getLordActor()->addSubGroup(obtainActorFromFactory(110573130));
				orderActorToFactory(110576130, EnemyMetis, "Metis_326");
				break;
			case 3150:
				getLordActor()->addSubGroup(obtainActorFromFactory(110573150));
				orderActorToFactory(110576150, EnemyMetis, "Metis_327");
				break;
			case 3170:
				getLordActor()->addSubGroup(obtainActorFromFactory(110573170));
				orderActorToFactory(110576170, EnemyMetis, "Metis_328");
				break;
			case 3190:
				getLordActor()->addSubGroup(obtainActorFromFactory(110573190));
				orderActorToFactory(110576190, EnemyMetis, "Metis_329");
				break;
			case 3210:
				getLordActor()->addSubGroup(obtainActorFromFactory(110573210));
				orderActorToFactory(110576210, EnemyMetis, "Metis_330");
				break;
			case 3230:
				getLordActor()->addSubGroup(obtainActorFromFactory(110573230));
				orderActorToFactory(110576230, EnemyMetis, "Metis_331");
				break;
			case 3250:
				getLordActor()->addSubGroup(obtainActorFromFactory(110573250));
				orderActorToFactory(110576250, EnemyMetis, "Metis_332");
				break;
			case 3270:
				getLordActor()->addSubGroup(obtainActorFromFactory(110573270));
				orderActorToFactory(110576270, EnemyMetis, "Metis_333");
				break;
			case 3290:
				getLordActor()->addSubGroup(obtainActorFromFactory(110573290));
				orderActorToFactory(110576290, EnemyMetis, "Metis_334");
				break;
			case 3310:
				getLordActor()->addSubGroup(obtainActorFromFactory(110573310));
				orderActorToFactory(110576310, EnemyMetis, "Metis_335");
				break;
			case 3330:
				getLordActor()->addSubGroup(obtainActorFromFactory(110573330));
				orderActorToFactory(110576330, EnemyMetis, "Metis_336");
				break;
			case 3350:
				getLordActor()->addSubGroup(obtainActorFromFactory(110573350));
				orderActorToFactory(110576350, EnemyMetis, "Metis_337");
				break;
			case 3370:
				getLordActor()->addSubGroup(obtainActorFromFactory(110573370));
				orderActorToFactory(110576370, EnemyMetis, "Metis_338");
				break;
			case 3390:
				getLordActor()->addSubGroup(obtainActorFromFactory(110573390));
				orderActorToFactory(110576390, EnemyMetis, "Metis_339");
				break;
			case 3410:
				getLordActor()->addSubGroup(obtainActorFromFactory(110573410));
				orderActorToFactory(110576410, EnemyMetis, "Metis_340");
				break;
			case 3430:
				getLordActor()->addSubGroup(obtainActorFromFactory(110573430));
				orderActorToFactory(110576430, EnemyMetis, "Metis_341");
				break;
			case 3450:
				getLordActor()->addSubGroup(obtainActorFromFactory(110573450));
				orderActorToFactory(110576450, EnemyMetis, "Metis_342");
				break;
			case 3470:
				getLordActor()->addSubGroup(obtainActorFromFactory(110573470));
				orderActorToFactory(110576470, EnemyMetis, "Metis_343");
				break;
			case 3490:
				getLordActor()->addSubGroup(obtainActorFromFactory(110573490));
				orderActorToFactory(110576490, EnemyMetis, "Metis_344");
				break;
			case 3510:
				getLordActor()->addSubGroup(obtainActorFromFactory(110573510));
				orderActorToFactory(110576510, EnemyMetis, "Metis_345");
				break;
			case 3530:
				getLordActor()->addSubGroup(obtainActorFromFactory(110573530));
				orderActorToFactory(110576530, EnemyMetis, "Metis_346");
				break;
			case 3550:
				getLordActor()->addSubGroup(obtainActorFromFactory(110573550));
				orderActorToFactory(110576550, EnemyMetis, "Metis_347");
				break;
			case 3570:
				getLordActor()->addSubGroup(obtainActorFromFactory(110573570));
				orderActorToFactory(110576570, EnemyMetis, "Metis_348");
				break;
			case 3590:
				getLordActor()->addSubGroup(obtainActorFromFactory(110573590));
				orderActorToFactory(110576590, EnemyMetis, "Metis_349");
				break;
			case 3610:
				getLordActor()->addSubGroup(obtainActorFromFactory(110573610));
				orderActorToFactory(110576610, EnemyMetis, "Metis_350");
				break;
			case 3630:
				getLordActor()->addSubGroup(obtainActorFromFactory(110573630));
				orderActorToFactory(110576630, EnemyMetis, "Metis_351");
				break;
			case 3650:
				getLordActor()->addSubGroup(obtainActorFromFactory(110573650));
				orderActorToFactory(110576650, EnemyMetis, "Metis_352");
				break;
			case 3670:
				getLordActor()->addSubGroup(obtainActorFromFactory(110573670));
				orderActorToFactory(110576670, EnemyMetis, "Metis_353");
				break;
			case 3690:
				getLordActor()->addSubGroup(obtainActorFromFactory(110573690));
				orderActorToFactory(110576690, EnemyMetis, "Metis_354");
				break;
			case 3710:
				getLordActor()->addSubGroup(obtainActorFromFactory(110573710));
				orderActorToFactory(110576710, EnemyMetis, "Metis_355");
				break;
			case 3730:
				getLordActor()->addSubGroup(obtainActorFromFactory(110573730));
				orderActorToFactory(110576730, EnemyMetis, "Metis_356");
				break;
			case 3750:
				getLordActor()->addSubGroup(obtainActorFromFactory(110573750));
				orderActorToFactory(110576750, EnemyMetis, "Metis_357");
				break;
			case 3770:
				getLordActor()->addSubGroup(obtainActorFromFactory(110573770));
				orderActorToFactory(110576770, EnemyMetis, "Metis_358");
				break;
			case 3790:
				getLordActor()->addSubGroup(obtainActorFromFactory(110573790));
				orderActorToFactory(110576790, EnemyMetis, "Metis_359");
				break;
			case 3810:
				getLordActor()->addSubGroup(obtainActorFromFactory(110573810));
				orderActorToFactory(110576810, EnemyMetis, "Metis_360");
				break;
			case 3830:
				getLordActor()->addSubGroup(obtainActorFromFactory(110573830));
				orderActorToFactory(110576830, EnemyMetis, "Metis_361");
				break;
			case 3850:
				getLordActor()->addSubGroup(obtainActorFromFactory(110573850));
				orderActorToFactory(110576850, EnemyMetis, "Metis_362");
				break;
			case 3870:
				getLordActor()->addSubGroup(obtainActorFromFactory(110573870));
				orderActorToFactory(110576870, EnemyMetis, "Metis_363");
				break;
			case 3890:
				getLordActor()->addSubGroup(obtainActorFromFactory(110573890));
				orderActorToFactory(110576890, EnemyMetis, "Metis_364");
				break;
			case 3910:
				getLordActor()->addSubGroup(obtainActorFromFactory(110573910));
				orderActorToFactory(110576910, EnemyMetis, "Metis_365");
				break;
			case 3930:
				getLordActor()->addSubGroup(obtainActorFromFactory(110573930));
				orderActorToFactory(110576930, EnemyMetis, "Metis_366");
				break;
			case 3950:
				getLordActor()->addSubGroup(obtainActorFromFactory(110573950));
				orderActorToFactory(110576950, EnemyMetis, "Metis_367");
				break;
			case 3970:
				getLordActor()->addSubGroup(obtainActorFromFactory(110573970));
				orderActorToFactory(110576970, EnemyMetis, "Metis_368");
				break;
			case 3990:
				getLordActor()->addSubGroup(obtainActorFromFactory(110573990));
				orderActorToFactory(110576990, EnemyMetis, "Metis_369");
				break;
			case 4000:
				orderActorToFactory(112577000, FormationIris002, "F002_Iris_370");
				break;
			case 4010:
				getLordActor()->addSubGroup(obtainActorFromFactory(110574010));
				orderActorToFactory(110577010, EnemyMetis, "Metis_371");
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(112474010);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 4030:
				getLordActor()->addSubGroup(obtainActorFromFactory(110574030));
				orderActorToFactory(110577030, EnemyMetis, "Metis_372");
				break;
			case 4050:
				getLordActor()->addSubGroup(obtainActorFromFactory(110574050));
				orderActorToFactory(110577050, EnemyMetis, "Metis_373");
				break;
			case 4070:
				getLordActor()->addSubGroup(obtainActorFromFactory(110574070));
				orderActorToFactory(110577070, EnemyMetis, "Metis_374");
				break;
			case 4090:
				getLordActor()->addSubGroup(obtainActorFromFactory(110574090));
				orderActorToFactory(110577090, EnemyMetis, "Metis_375");
				break;
			case 4110:
				getLordActor()->addSubGroup(obtainActorFromFactory(110574110));
				orderActorToFactory(110577110, EnemyMetis, "Metis_376");
				break;
			case 4130:
				getLordActor()->addSubGroup(obtainActorFromFactory(110574130));
				orderActorToFactory(110577130, EnemyMetis, "Metis_377");
				break;
			case 4150:
				getLordActor()->addSubGroup(obtainActorFromFactory(110574150));
				orderActorToFactory(110577150, EnemyMetis, "Metis_378");
				break;
			case 4170:
				getLordActor()->addSubGroup(obtainActorFromFactory(110574170));
				orderActorToFactory(110577170, EnemyMetis, "Metis_379");
				break;
			case 4190:
				getLordActor()->addSubGroup(obtainActorFromFactory(110574190));
				orderActorToFactory(110577190, EnemyMetis, "Metis_380");
				break;
			case 4210:
				getLordActor()->addSubGroup(obtainActorFromFactory(110574210));
				orderActorToFactory(110577210, EnemyMetis, "Metis_381");
				break;
			case 4230:
				getLordActor()->addSubGroup(obtainActorFromFactory(110574230));
				orderActorToFactory(110577230, EnemyMetis, "Metis_382");
				break;
			case 4250:
				getLordActor()->addSubGroup(obtainActorFromFactory(110574250));
				orderActorToFactory(110577250, EnemyMetis, "Metis_383");
				break;
			case 4270:
				getLordActor()->addSubGroup(obtainActorFromFactory(110574270));
				orderActorToFactory(110577270, EnemyMetis, "Metis_384");
				break;
			case 4290:
				getLordActor()->addSubGroup(obtainActorFromFactory(110574290));
				orderActorToFactory(110577290, EnemyMetis, "Metis_385");
				break;
			case 4310:
				getLordActor()->addSubGroup(obtainActorFromFactory(110574310));
				orderActorToFactory(110577310, EnemyMetis, "Metis_386");
				break;
			case 4330:
				getLordActor()->addSubGroup(obtainActorFromFactory(110574330));
				orderActorToFactory(110577330, EnemyMetis, "Metis_387");
				break;
			case 4350:
				getLordActor()->addSubGroup(obtainActorFromFactory(110574350));
				orderActorToFactory(110577350, EnemyMetis, "Metis_388");
				break;
			case 4370:
				getLordActor()->addSubGroup(obtainActorFromFactory(110574370));
				orderActorToFactory(110577370, EnemyMetis, "Metis_389");
				break;
			case 4390:
				getLordActor()->addSubGroup(obtainActorFromFactory(110574390));
				orderActorToFactory(110577390, EnemyMetis, "Metis_390");
				break;
			case 4410:
				getLordActor()->addSubGroup(obtainActorFromFactory(110574410));
				orderActorToFactory(110577410, EnemyMetis, "Metis_391");
				break;
			case 4430:
				getLordActor()->addSubGroup(obtainActorFromFactory(110574430));
				orderActorToFactory(110577430, EnemyMetis, "Metis_392");
				break;
			case 4450:
				getLordActor()->addSubGroup(obtainActorFromFactory(110574450));
				orderActorToFactory(110577450, EnemyMetis, "Metis_393");
				break;
			case 4470:
				getLordActor()->addSubGroup(obtainActorFromFactory(110574470));
				orderActorToFactory(110577470, EnemyMetis, "Metis_394");
				break;
			case 4490:
				getLordActor()->addSubGroup(obtainActorFromFactory(110574490));
				orderActorToFactory(110577490, EnemyMetis, "Metis_395");
				break;
			case 4500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112774500);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 4510:
				getLordActor()->addSubGroup(obtainActorFromFactory(110574510));
				orderActorToFactory(110577510, EnemyMetis, "Metis_396");
				break;
			case 4530:
				getLordActor()->addSubGroup(obtainActorFromFactory(110574530));
				orderActorToFactory(110577530, EnemyMetis, "Metis_397");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112874530);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 4550:
				getLordActor()->addSubGroup(obtainActorFromFactory(110574550));
				orderActorToFactory(110577550, EnemyMetis, "Metis_398");
				break;
			case 4560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112974560);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 4570:
				getLordActor()->addSubGroup(obtainActorFromFactory(110574570));
				orderActorToFactory(110577570, EnemyMetis, "Metis_399");
				break;
			case 4590:
				getLordActor()->addSubGroup(obtainActorFromFactory(110574590));
				orderActorToFactory(110577590, EnemyMetis, "Metis_400");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113074590);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 4610:
				getLordActor()->addSubGroup(obtainActorFromFactory(110574610));
				orderActorToFactory(110577610, EnemyMetis, "Metis_401");
				break;
			case 4620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113174620);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 4630:
				getLordActor()->addSubGroup(obtainActorFromFactory(110574630));
				orderActorToFactory(110577630, EnemyMetis, "Metis_402");
				break;
			case 4650:
				getLordActor()->addSubGroup(obtainActorFromFactory(110574650));
				orderActorToFactory(110577650, EnemyMetis, "Metis_403");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113274650);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 4670:
				getLordActor()->addSubGroup(obtainActorFromFactory(110574670));
				orderActorToFactory(110577670, EnemyMetis, "Metis_404");
				break;
			case 4690:
				getLordActor()->addSubGroup(obtainActorFromFactory(110574690));
				orderActorToFactory(110577690, EnemyMetis, "Metis_405");
				break;
			case 4710:
				getLordActor()->addSubGroup(obtainActorFromFactory(110574710));
				orderActorToFactory(110577710, EnemyMetis, "Metis_406");
				break;
			case 4730:
				getLordActor()->addSubGroup(obtainActorFromFactory(110574730));
				orderActorToFactory(110577730, EnemyMetis, "Metis_407");
				break;
			case 4750:
				getLordActor()->addSubGroup(obtainActorFromFactory(110574750));
				orderActorToFactory(110577750, EnemyMetis, "Metis_408");
				break;
			case 4770:
				getLordActor()->addSubGroup(obtainActorFromFactory(110574770));
				orderActorToFactory(110577770, EnemyMetis, "Metis_409");
				break;
			case 4790:
				getLordActor()->addSubGroup(obtainActorFromFactory(110574790));
				orderActorToFactory(110577790, EnemyMetis, "Metis_410");
				break;
			case 4810:
				getLordActor()->addSubGroup(obtainActorFromFactory(110574810));
				orderActorToFactory(110577810, EnemyMetis, "Metis_411");
				break;
			case 4830:
				getLordActor()->addSubGroup(obtainActorFromFactory(110574830));
				orderActorToFactory(110577830, EnemyMetis, "Metis_412");
				break;
			case 4850:
				getLordActor()->addSubGroup(obtainActorFromFactory(110574850));
				orderActorToFactory(110577850, EnemyMetis, "Metis_413");
				break;
			case 4870:
				getLordActor()->addSubGroup(obtainActorFromFactory(110574870));
				orderActorToFactory(110577870, EnemyMetis, "Metis_414");
				break;
			case 4890:
				getLordActor()->addSubGroup(obtainActorFromFactory(110574890));
				orderActorToFactory(110577890, EnemyMetis, "Metis_415");
				break;
			case 4910:
				getLordActor()->addSubGroup(obtainActorFromFactory(110574910));
				orderActorToFactory(110577910, EnemyMetis, "Metis_416");
				break;
			case 4930:
				getLordActor()->addSubGroup(obtainActorFromFactory(110574930));
				orderActorToFactory(110577930, EnemyMetis, "Metis_417");
				break;
			case 4950:
				getLordActor()->addSubGroup(obtainActorFromFactory(110574950));
				orderActorToFactory(110577950, EnemyMetis, "Metis_418");
				break;
			case 4970:
				getLordActor()->addSubGroup(obtainActorFromFactory(110574970));
				orderActorToFactory(110577970, EnemyMetis, "Metis_419");
				break;
			case 4990:
				getLordActor()->addSubGroup(obtainActorFromFactory(110574990));
				orderActorToFactory(110577990, EnemyMetis, "Metis_420");
				break;
			case 5000:
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(112575000);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 5010:
				getLordActor()->addSubGroup(obtainActorFromFactory(110575010));
				orderActorToFactory(110578010, EnemyMetis, "Metis_421");
				orderActorToFactory(112478010, FormationIris001, "F001_Iris_422");
				break;
			case 5030:
				getLordActor()->addSubGroup(obtainActorFromFactory(110575030));
				orderActorToFactory(110578030, EnemyMetis, "Metis_423");
				break;
			case 5050:
				getLordActor()->addSubGroup(obtainActorFromFactory(110575050));
				orderActorToFactory(110578050, EnemyMetis, "Metis_424");
				break;
			case 5070:
				getLordActor()->addSubGroup(obtainActorFromFactory(110575070));
				orderActorToFactory(110578070, EnemyMetis, "Metis_425");
				break;
			case 5090:
				getLordActor()->addSubGroup(obtainActorFromFactory(110575090));
				orderActorToFactory(110578090, EnemyMetis, "Metis_426");
				break;
			case 5110:
				getLordActor()->addSubGroup(obtainActorFromFactory(110575110));
				orderActorToFactory(110578110, EnemyMetis, "Metis_427");
				break;
			case 5130:
				getLordActor()->addSubGroup(obtainActorFromFactory(110575130));
				orderActorToFactory(110578130, EnemyMetis, "Metis_428");
				break;
			case 5150:
				getLordActor()->addSubGroup(obtainActorFromFactory(110575150));
				orderActorToFactory(110578150, EnemyMetis, "Metis_429");
				break;
			case 5170:
				getLordActor()->addSubGroup(obtainActorFromFactory(110575170));
				orderActorToFactory(110578170, EnemyMetis, "Metis_430");
				break;
			case 5190:
				getLordActor()->addSubGroup(obtainActorFromFactory(110575190));
				orderActorToFactory(110578190, EnemyMetis, "Metis_431");
				break;
			case 5210:
				getLordActor()->addSubGroup(obtainActorFromFactory(110575210));
				orderActorToFactory(110578210, EnemyMetis, "Metis_432");
				break;
			case 5230:
				getLordActor()->addSubGroup(obtainActorFromFactory(110575230));
				orderActorToFactory(110578230, EnemyMetis, "Metis_433");
				break;
			case 5250:
				getLordActor()->addSubGroup(obtainActorFromFactory(110575250));
				orderActorToFactory(110578250, EnemyMetis, "Metis_434");
				break;
			case 5270:
				getLordActor()->addSubGroup(obtainActorFromFactory(110575270));
				orderActorToFactory(110578270, EnemyMetis, "Metis_435");
				break;
			case 5290:
				getLordActor()->addSubGroup(obtainActorFromFactory(110575290));
				orderActorToFactory(110578290, EnemyMetis, "Metis_436");
				break;
			case 5310:
				getLordActor()->addSubGroup(obtainActorFromFactory(110575310));
				orderActorToFactory(110578310, EnemyMetis, "Metis_437");
				break;
			case 5330:
				getLordActor()->addSubGroup(obtainActorFromFactory(110575330));
				orderActorToFactory(110578330, EnemyMetis, "Metis_438");
				break;
			case 5350:
				getLordActor()->addSubGroup(obtainActorFromFactory(110575350));
				orderActorToFactory(110578350, EnemyMetis, "Metis_439");
				break;
			case 5370:
				getLordActor()->addSubGroup(obtainActorFromFactory(110575370));
				orderActorToFactory(110578370, EnemyMetis, "Metis_440");
				break;
			case 5390:
				getLordActor()->addSubGroup(obtainActorFromFactory(110575390));
				orderActorToFactory(110578390, EnemyMetis, "Metis_441");
				break;
			case 5410:
				getLordActor()->addSubGroup(obtainActorFromFactory(110575410));
				orderActorToFactory(110578410, EnemyMetis, "Metis_442");
				break;
			case 5430:
				getLordActor()->addSubGroup(obtainActorFromFactory(110575430));
				orderActorToFactory(110578430, EnemyMetis, "Metis_443");
				break;
			case 5450:
				getLordActor()->addSubGroup(obtainActorFromFactory(110575450));
				orderActorToFactory(110578450, EnemyMetis, "Metis_444");
				break;
			case 5470:
				getLordActor()->addSubGroup(obtainActorFromFactory(110575470));
				orderActorToFactory(110578470, EnemyMetis, "Metis_445");
				break;
			case 5490:
				getLordActor()->addSubGroup(obtainActorFromFactory(110575490));
				orderActorToFactory(110578490, EnemyMetis, "Metis_446");
				break;
			case 5500:
				orderActorWithDpToFactory(112778500, EnemyCeres, "Ceres_447", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 5510:
				getLordActor()->addSubGroup(obtainActorFromFactory(110575510));
				orderActorToFactory(110578510, EnemyMetis, "Metis_448");
				break;
			case 5530:
				getLordActor()->addSubGroup(obtainActorFromFactory(110575530));
				orderActorToFactory(110578530, EnemyMetis, "Metis_449");
				orderActorWithDpToFactory(112878530, EnemyCeres, "Ceres_450", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 5550:
				getLordActor()->addSubGroup(obtainActorFromFactory(110575550));
				orderActorToFactory(110578550, EnemyMetis, "Metis_451");
				break;
			case 5560:
				orderActorWithDpToFactory(112978560, EnemyCeres, "Ceres_452", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 5570:
				getLordActor()->addSubGroup(obtainActorFromFactory(110575570));
				orderActorToFactory(110578570, EnemyMetis, "Metis_453");
				break;
			case 5590:
				getLordActor()->addSubGroup(obtainActorFromFactory(110575590));
				orderActorToFactory(110578590, EnemyMetis, "Metis_454");
				orderActorWithDpToFactory(113078590, EnemyCeres, "Ceres_455", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 5610:
				getLordActor()->addSubGroup(obtainActorFromFactory(110575610));
				orderActorToFactory(110578610, EnemyMetis, "Metis_456");
				break;
			case 5620:
				orderActorWithDpToFactory(113178620, EnemyCeres, "Ceres_457", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 5630:
				getLordActor()->addSubGroup(obtainActorFromFactory(110575630));
				orderActorToFactory(110578630, EnemyMetis, "Metis_458");
				break;
			case 5650:
				getLordActor()->addSubGroup(obtainActorFromFactory(110575650));
				orderActorToFactory(110578650, EnemyMetis, "Metis_459");
				orderActorWithDpToFactory(113278650, EnemyCeres, "Ceres_460", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 5670:
				getLordActor()->addSubGroup(obtainActorFromFactory(110575670));
				orderActorToFactory(110578670, EnemyMetis, "Metis_461");
				break;
			case 5690:
				getLordActor()->addSubGroup(obtainActorFromFactory(110575690));
				orderActorToFactory(110578690, EnemyMetis, "Metis_462");
				break;
			case 5710:
				getLordActor()->addSubGroup(obtainActorFromFactory(110575710));
				orderActorToFactory(110578710, EnemyMetis, "Metis_463");
				break;
			case 5730:
				getLordActor()->addSubGroup(obtainActorFromFactory(110575730));
				orderActorToFactory(110578730, EnemyMetis, "Metis_464");
				break;
			case 5750:
				getLordActor()->addSubGroup(obtainActorFromFactory(110575750));
				orderActorToFactory(110578750, EnemyMetis, "Metis_465");
				break;
			case 5770:
				getLordActor()->addSubGroup(obtainActorFromFactory(110575770));
				orderActorToFactory(110578770, EnemyMetis, "Metis_466");
				break;
			case 5790:
				getLordActor()->addSubGroup(obtainActorFromFactory(110575790));
				orderActorToFactory(110578790, EnemyMetis, "Metis_467");
				break;
			case 5810:
				getLordActor()->addSubGroup(obtainActorFromFactory(110575810));
				orderActorToFactory(110578810, EnemyMetis, "Metis_468");
				break;
			case 5830:
				getLordActor()->addSubGroup(obtainActorFromFactory(110575830));
				orderActorToFactory(110578830, EnemyMetis, "Metis_469");
				break;
			case 5850:
				getLordActor()->addSubGroup(obtainActorFromFactory(110575850));
				orderActorToFactory(110578850, EnemyMetis, "Metis_470");
				break;
			case 5870:
				getLordActor()->addSubGroup(obtainActorFromFactory(110575870));
				orderActorToFactory(110578870, EnemyMetis, "Metis_471");
				break;
			case 5890:
				getLordActor()->addSubGroup(obtainActorFromFactory(110575890));
				orderActorToFactory(110578890, EnemyMetis, "Metis_472");
				break;
			case 5910:
				getLordActor()->addSubGroup(obtainActorFromFactory(110575910));
				orderActorToFactory(110578910, EnemyMetis, "Metis_473");
				break;
			case 5930:
				getLordActor()->addSubGroup(obtainActorFromFactory(110575930));
				orderActorToFactory(110578930, EnemyMetis, "Metis_474");
				break;
			case 5950:
				getLordActor()->addSubGroup(obtainActorFromFactory(110575950));
				orderActorToFactory(110578950, EnemyMetis, "Metis_475");
				break;
			case 5970:
				getLordActor()->addSubGroup(obtainActorFromFactory(110575970));
				orderActorToFactory(110578970, EnemyMetis, "Metis_476");
				break;
			case 5990:
				getLordActor()->addSubGroup(obtainActorFromFactory(110575990));
				orderActorToFactory(110578990, EnemyMetis, "Metis_477");
				break;
			case 6000:
				orderActorToFactory(112579000, FormationIris002, "F002_Iris_478");
				break;
			case 6010:
				getLordActor()->addSubGroup(obtainActorFromFactory(110576010));
				orderActorToFactory(110579010, EnemyMetis, "Metis_479");
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(112476010);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 6030:
				getLordActor()->addSubGroup(obtainActorFromFactory(110576030));
				orderActorToFactory(110579030, EnemyMetis, "Metis_480");
				break;
			case 6050:
				getLordActor()->addSubGroup(obtainActorFromFactory(110576050));
				orderActorToFactory(110579050, EnemyMetis, "Metis_481");
				break;
			case 6070:
				getLordActor()->addSubGroup(obtainActorFromFactory(110576070));
				orderActorToFactory(110579070, EnemyMetis, "Metis_482");
				break;
			case 6090:
				getLordActor()->addSubGroup(obtainActorFromFactory(110576090));
				orderActorToFactory(110579090, EnemyMetis, "Metis_483");
				break;
			case 6110:
				getLordActor()->addSubGroup(obtainActorFromFactory(110576110));
				orderActorToFactory(110579110, EnemyMetis, "Metis_484");
				break;
			case 6130:
				getLordActor()->addSubGroup(obtainActorFromFactory(110576130));
				orderActorToFactory(110579130, EnemyMetis, "Metis_485");
				break;
			case 6150:
				getLordActor()->addSubGroup(obtainActorFromFactory(110576150));
				orderActorToFactory(110579150, EnemyMetis, "Metis_486");
				break;
			case 6170:
				getLordActor()->addSubGroup(obtainActorFromFactory(110576170));
				orderActorToFactory(110579170, EnemyMetis, "Metis_487");
				break;
			case 6190:
				getLordActor()->addSubGroup(obtainActorFromFactory(110576190));
				orderActorToFactory(110579190, EnemyMetis, "Metis_488");
				break;
			case 6210:
				getLordActor()->addSubGroup(obtainActorFromFactory(110576210));
				orderActorToFactory(110579210, EnemyMetis, "Metis_489");
				break;
			case 6230:
				getLordActor()->addSubGroup(obtainActorFromFactory(110576230));
				orderActorToFactory(110579230, EnemyMetis, "Metis_490");
				break;
			case 6250:
				getLordActor()->addSubGroup(obtainActorFromFactory(110576250));
				orderActorToFactory(110579250, EnemyMetis, "Metis_491");
				break;
			case 6270:
				getLordActor()->addSubGroup(obtainActorFromFactory(110576270));
				orderActorToFactory(110579270, EnemyMetis, "Metis_492");
				break;
			case 6290:
				getLordActor()->addSubGroup(obtainActorFromFactory(110576290));
				orderActorToFactory(110579290, EnemyMetis, "Metis_493");
				break;
			case 6310:
				getLordActor()->addSubGroup(obtainActorFromFactory(110576310));
				orderActorToFactory(110579310, EnemyMetis, "Metis_494");
				break;
			case 6330:
				getLordActor()->addSubGroup(obtainActorFromFactory(110576330));
				orderActorToFactory(110579330, EnemyMetis, "Metis_495");
				break;
			case 6350:
				getLordActor()->addSubGroup(obtainActorFromFactory(110576350));
				orderActorToFactory(110579350, EnemyMetis, "Metis_496");
				break;
			case 6370:
				getLordActor()->addSubGroup(obtainActorFromFactory(110576370));
				orderActorToFactory(110579370, EnemyMetis, "Metis_497");
				break;
			case 6390:
				getLordActor()->addSubGroup(obtainActorFromFactory(110576390));
				orderActorToFactory(110579390, EnemyMetis, "Metis_498");
				break;
			case 6410:
				getLordActor()->addSubGroup(obtainActorFromFactory(110576410));
				orderActorToFactory(110579410, EnemyMetis, "Metis_499");
				break;
			case 6430:
				getLordActor()->addSubGroup(obtainActorFromFactory(110576430));
				orderActorToFactory(110579430, EnemyMetis, "Metis_500");
				break;
			case 6450:
				getLordActor()->addSubGroup(obtainActorFromFactory(110576450));
				orderActorToFactory(110579450, EnemyMetis, "Metis_501");
				break;
			case 6470:
				getLordActor()->addSubGroup(obtainActorFromFactory(110576470));
				orderActorToFactory(110579470, EnemyMetis, "Metis_502");
				break;
			case 6490:
				getLordActor()->addSubGroup(obtainActorFromFactory(110576490));
				orderActorToFactory(110579490, EnemyMetis, "Metis_503");
				break;
			case 6510:
				getLordActor()->addSubGroup(obtainActorFromFactory(110576510));
				orderActorToFactory(110579510, EnemyMetis, "Metis_504");
				break;
			case 6530:
				getLordActor()->addSubGroup(obtainActorFromFactory(110576530));
				orderActorToFactory(110579530, EnemyMetis, "Metis_505");
				break;
			case 6550:
				getLordActor()->addSubGroup(obtainActorFromFactory(110576550));
				orderActorToFactory(110579550, EnemyMetis, "Metis_506");
				break;
			case 6570:
				getLordActor()->addSubGroup(obtainActorFromFactory(110576570));
				orderActorToFactory(110579570, EnemyMetis, "Metis_507");
				break;
			case 6590:
				getLordActor()->addSubGroup(obtainActorFromFactory(110576590));
				orderActorToFactory(110579590, EnemyMetis, "Metis_508");
				break;
			case 6610:
				getLordActor()->addSubGroup(obtainActorFromFactory(110576610));
				orderActorToFactory(110579610, EnemyMetis, "Metis_509");
				break;
			case 6630:
				getLordActor()->addSubGroup(obtainActorFromFactory(110576630));
				orderActorToFactory(110579630, EnemyMetis, "Metis_510");
				break;
			case 6650:
				getLordActor()->addSubGroup(obtainActorFromFactory(110576650));
				orderActorToFactory(110579650, EnemyMetis, "Metis_511");
				break;
			case 6670:
				getLordActor()->addSubGroup(obtainActorFromFactory(110576670));
				orderActorToFactory(110579670, EnemyMetis, "Metis_512");
				break;
			case 6690:
				getLordActor()->addSubGroup(obtainActorFromFactory(110576690));
				orderActorToFactory(110579690, EnemyMetis, "Metis_513");
				break;
			case 6710:
				getLordActor()->addSubGroup(obtainActorFromFactory(110576710));
				orderActorToFactory(110579710, EnemyMetis, "Metis_514");
				break;
			case 6730:
				getLordActor()->addSubGroup(obtainActorFromFactory(110576730));
				orderActorToFactory(110579730, EnemyMetis, "Metis_515");
				break;
			case 6750:
				getLordActor()->addSubGroup(obtainActorFromFactory(110576750));
				orderActorToFactory(110579750, EnemyMetis, "Metis_516");
				break;
			case 6770:
				getLordActor()->addSubGroup(obtainActorFromFactory(110576770));
				orderActorToFactory(110579770, EnemyMetis, "Metis_517");
				break;
			case 6790:
				getLordActor()->addSubGroup(obtainActorFromFactory(110576790));
				orderActorToFactory(110579790, EnemyMetis, "Metis_518");
				break;
			case 6810:
				getLordActor()->addSubGroup(obtainActorFromFactory(110576810));
				orderActorToFactory(110579810, EnemyMetis, "Metis_519");
				break;
			case 6830:
				getLordActor()->addSubGroup(obtainActorFromFactory(110576830));
				orderActorToFactory(110579830, EnemyMetis, "Metis_520");
				break;
			case 6850:
				getLordActor()->addSubGroup(obtainActorFromFactory(110576850));
				orderActorToFactory(110579850, EnemyMetis, "Metis_521");
				break;
			case 6870:
				getLordActor()->addSubGroup(obtainActorFromFactory(110576870));
				orderActorToFactory(110579870, EnemyMetis, "Metis_522");
				break;
			case 6890:
				getLordActor()->addSubGroup(obtainActorFromFactory(110576890));
				orderActorToFactory(110579890, EnemyMetis, "Metis_523");
				break;
			case 6910:
				getLordActor()->addSubGroup(obtainActorFromFactory(110576910));
				orderActorToFactory(110579910, EnemyMetis, "Metis_524");
				break;
			case 6930:
				getLordActor()->addSubGroup(obtainActorFromFactory(110576930));
				orderActorToFactory(110579930, EnemyMetis, "Metis_525");
				break;
			case 6950:
				getLordActor()->addSubGroup(obtainActorFromFactory(110576950));
				orderActorToFactory(110579950, EnemyMetis, "Metis_526");
				break;
			case 6970:
				getLordActor()->addSubGroup(obtainActorFromFactory(110576970));
				orderActorToFactory(110579970, EnemyMetis, "Metis_527");
				break;
			case 6990:
				getLordActor()->addSubGroup(obtainActorFromFactory(110576990));
				orderActorToFactory(110579990, EnemyMetis, "Metis_528");
				break;
			case 7000:
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(112577000);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 7010:
				getLordActor()->addSubGroup(obtainActorFromFactory(110577010));
				orderActorToFactory(1105710010, EnemyMetis, "Metis_529");
				orderActorToFactory(1124710010, FormationIris001, "F001_Iris_530");
				break;
			case 7030:
				getLordActor()->addSubGroup(obtainActorFromFactory(110577030));
				orderActorToFactory(1105710030, EnemyMetis, "Metis_531");
				break;
			case 7050:
				getLordActor()->addSubGroup(obtainActorFromFactory(110577050));
				orderActorToFactory(1105710050, EnemyMetis, "Metis_532");
				break;
			case 7070:
				getLordActor()->addSubGroup(obtainActorFromFactory(110577070));
				orderActorToFactory(1105710070, EnemyMetis, "Metis_533");
				break;
			case 7090:
				getLordActor()->addSubGroup(obtainActorFromFactory(110577090));
				orderActorToFactory(1105710090, EnemyMetis, "Metis_534");
				break;
			case 7110:
				getLordActor()->addSubGroup(obtainActorFromFactory(110577110));
				orderActorToFactory(1105710110, EnemyMetis, "Metis_535");
				break;
			case 7130:
				getLordActor()->addSubGroup(obtainActorFromFactory(110577130));
				orderActorToFactory(1105710130, EnemyMetis, "Metis_536");
				break;
			case 7150:
				getLordActor()->addSubGroup(obtainActorFromFactory(110577150));
				orderActorToFactory(1105710150, EnemyMetis, "Metis_537");
				break;
			case 7170:
				getLordActor()->addSubGroup(obtainActorFromFactory(110577170));
				orderActorToFactory(1105710170, EnemyMetis, "Metis_538");
				break;
			case 7190:
				getLordActor()->addSubGroup(obtainActorFromFactory(110577190));
				orderActorToFactory(1105710190, EnemyMetis, "Metis_539");
				break;
			case 7210:
				getLordActor()->addSubGroup(obtainActorFromFactory(110577210));
				orderActorToFactory(1105710210, EnemyMetis, "Metis_540");
				break;
			case 7230:
				getLordActor()->addSubGroup(obtainActorFromFactory(110577230));
				orderActorToFactory(1105710230, EnemyMetis, "Metis_541");
				break;
			case 7250:
				getLordActor()->addSubGroup(obtainActorFromFactory(110577250));
				orderActorToFactory(1105710250, EnemyMetis, "Metis_542");
				break;
			case 7270:
				getLordActor()->addSubGroup(obtainActorFromFactory(110577270));
				orderActorToFactory(1105710270, EnemyMetis, "Metis_543");
				break;
			case 7290:
				getLordActor()->addSubGroup(obtainActorFromFactory(110577290));
				orderActorToFactory(1105710290, EnemyMetis, "Metis_544");
				break;
			case 7310:
				getLordActor()->addSubGroup(obtainActorFromFactory(110577310));
				orderActorToFactory(1105710310, EnemyMetis, "Metis_545");
				break;
			case 7330:
				getLordActor()->addSubGroup(obtainActorFromFactory(110577330));
				orderActorToFactory(1105710330, EnemyMetis, "Metis_546");
				break;
			case 7350:
				getLordActor()->addSubGroup(obtainActorFromFactory(110577350));
				orderActorToFactory(1105710350, EnemyMetis, "Metis_547");
				break;
			case 7370:
				getLordActor()->addSubGroup(obtainActorFromFactory(110577370));
				orderActorToFactory(1105710370, EnemyMetis, "Metis_548");
				break;
			case 7390:
				getLordActor()->addSubGroup(obtainActorFromFactory(110577390));
				orderActorToFactory(1105710390, EnemyMetis, "Metis_549");
				break;
			case 7410:
				getLordActor()->addSubGroup(obtainActorFromFactory(110577410));
				orderActorToFactory(1105710410, EnemyMetis, "Metis_550");
				break;
			case 7430:
				getLordActor()->addSubGroup(obtainActorFromFactory(110577430));
				orderActorToFactory(1105710430, EnemyMetis, "Metis_551");
				break;
			case 7450:
				getLordActor()->addSubGroup(obtainActorFromFactory(110577450));
				orderActorToFactory(1105710450, EnemyMetis, "Metis_552");
				break;
			case 7470:
				getLordActor()->addSubGroup(obtainActorFromFactory(110577470));
				orderActorToFactory(1105710470, EnemyMetis, "Metis_553");
				break;
			case 7490:
				getLordActor()->addSubGroup(obtainActorFromFactory(110577490));
				orderActorToFactory(1105710490, EnemyMetis, "Metis_554");
				break;
			case 7510:
				getLordActor()->addSubGroup(obtainActorFromFactory(110577510));
				orderActorToFactory(1105710510, EnemyMetis, "Metis_555");
				break;
			case 7530:
				getLordActor()->addSubGroup(obtainActorFromFactory(110577530));
				orderActorToFactory(1105710530, EnemyMetis, "Metis_556");
				break;
			case 7550:
				getLordActor()->addSubGroup(obtainActorFromFactory(110577550));
				orderActorToFactory(1105710550, EnemyMetis, "Metis_557");
				break;
			case 7570:
				getLordActor()->addSubGroup(obtainActorFromFactory(110577570));
				orderActorToFactory(1105710570, EnemyMetis, "Metis_558");
				break;
			case 7590:
				getLordActor()->addSubGroup(obtainActorFromFactory(110577590));
				orderActorToFactory(1105710590, EnemyMetis, "Metis_559");
				break;
			case 7610:
				getLordActor()->addSubGroup(obtainActorFromFactory(110577610));
				orderActorToFactory(1105710610, EnemyMetis, "Metis_560");
				break;
			case 7630:
				getLordActor()->addSubGroup(obtainActorFromFactory(110577630));
				orderActorToFactory(1105710630, EnemyMetis, "Metis_561");
				break;
			case 7650:
				getLordActor()->addSubGroup(obtainActorFromFactory(110577650));
				orderActorToFactory(1105710650, EnemyMetis, "Metis_562");
				break;
			case 7670:
				getLordActor()->addSubGroup(obtainActorFromFactory(110577670));
				orderActorToFactory(1105710670, EnemyMetis, "Metis_563");
				break;
			case 7690:
				getLordActor()->addSubGroup(obtainActorFromFactory(110577690));
				orderActorToFactory(1105710690, EnemyMetis, "Metis_564");
				break;
			case 7710:
				getLordActor()->addSubGroup(obtainActorFromFactory(110577710));
				orderActorToFactory(1105710710, EnemyMetis, "Metis_565");
				break;
			case 7730:
				getLordActor()->addSubGroup(obtainActorFromFactory(110577730));
				orderActorToFactory(1105710730, EnemyMetis, "Metis_566");
				break;
			case 7750:
				getLordActor()->addSubGroup(obtainActorFromFactory(110577750));
				orderActorToFactory(1105710750, EnemyMetis, "Metis_567");
				break;
			case 7770:
				getLordActor()->addSubGroup(obtainActorFromFactory(110577770));
				orderActorToFactory(1105710770, EnemyMetis, "Metis_568");
				break;
			case 7790:
				getLordActor()->addSubGroup(obtainActorFromFactory(110577790));
				orderActorToFactory(1105710790, EnemyMetis, "Metis_569");
				break;
			case 7810:
				getLordActor()->addSubGroup(obtainActorFromFactory(110577810));
				orderActorToFactory(1105710810, EnemyMetis, "Metis_570");
				break;
			case 7830:
				getLordActor()->addSubGroup(obtainActorFromFactory(110577830));
				orderActorToFactory(1105710830, EnemyMetis, "Metis_571");
				break;
			case 7850:
				getLordActor()->addSubGroup(obtainActorFromFactory(110577850));
				orderActorToFactory(1105710850, EnemyMetis, "Metis_572");
				break;
			case 7870:
				getLordActor()->addSubGroup(obtainActorFromFactory(110577870));
				orderActorToFactory(1105710870, EnemyMetis, "Metis_573");
				break;
			case 7890:
				getLordActor()->addSubGroup(obtainActorFromFactory(110577890));
				orderActorToFactory(1105710890, EnemyMetis, "Metis_574");
				break;
			case 7910:
				getLordActor()->addSubGroup(obtainActorFromFactory(110577910));
				orderActorToFactory(1105710910, EnemyMetis, "Metis_575");
				break;
			case 7930:
				getLordActor()->addSubGroup(obtainActorFromFactory(110577930));
				orderActorToFactory(1105710930, EnemyMetis, "Metis_576");
				break;
			case 7950:
				getLordActor()->addSubGroup(obtainActorFromFactory(110577950));
				orderActorToFactory(1105710950, EnemyMetis, "Metis_577");
				break;
			case 7970:
				getLordActor()->addSubGroup(obtainActorFromFactory(110577970));
				orderActorToFactory(1105710970, EnemyMetis, "Metis_578");
				break;
			case 7990:
				getLordActor()->addSubGroup(obtainActorFromFactory(110577990));
				orderActorToFactory(1105710990, EnemyMetis, "Metis_579");
				break;
			case 8000:
				orderActorToFactory(1125711000, FormationIris002, "F002_Iris_580");
				break;
			case 8010:
				getLordActor()->addSubGroup(obtainActorFromFactory(110578010));
				orderActorToFactory(1105711010, EnemyMetis, "Metis_581");
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(112478010);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 8030:
				getLordActor()->addSubGroup(obtainActorFromFactory(110578030));
				orderActorToFactory(1105711030, EnemyMetis, "Metis_582");
				break;
			case 8050:
				getLordActor()->addSubGroup(obtainActorFromFactory(110578050));
				orderActorToFactory(1105711050, EnemyMetis, "Metis_583");
				break;
			case 8070:
				getLordActor()->addSubGroup(obtainActorFromFactory(110578070));
				orderActorToFactory(1105711070, EnemyMetis, "Metis_584");
				break;
			case 8090:
				getLordActor()->addSubGroup(obtainActorFromFactory(110578090));
				orderActorToFactory(1105711090, EnemyMetis, "Metis_585");
				break;
			case 8110:
				getLordActor()->addSubGroup(obtainActorFromFactory(110578110));
				orderActorToFactory(1105711110, EnemyMetis, "Metis_586");
				break;
			case 8130:
				getLordActor()->addSubGroup(obtainActorFromFactory(110578130));
				orderActorToFactory(1105711130, EnemyMetis, "Metis_587");
				break;
			case 8150:
				getLordActor()->addSubGroup(obtainActorFromFactory(110578150));
				orderActorToFactory(1105711150, EnemyMetis, "Metis_588");
				break;
			case 8170:
				getLordActor()->addSubGroup(obtainActorFromFactory(110578170));
				orderActorToFactory(1105711170, EnemyMetis, "Metis_589");
				break;
			case 8190:
				getLordActor()->addSubGroup(obtainActorFromFactory(110578190));
				orderActorToFactory(1105711190, EnemyMetis, "Metis_590");
				break;
			case 8210:
				getLordActor()->addSubGroup(obtainActorFromFactory(110578210));
				orderActorToFactory(1105711210, EnemyMetis, "Metis_591");
				break;
			case 8230:
				getLordActor()->addSubGroup(obtainActorFromFactory(110578230));
				orderActorToFactory(1105711230, EnemyMetis, "Metis_592");
				break;
			case 8250:
				getLordActor()->addSubGroup(obtainActorFromFactory(110578250));
				orderActorToFactory(1105711250, EnemyMetis, "Metis_593");
				break;
			case 8270:
				getLordActor()->addSubGroup(obtainActorFromFactory(110578270));
				orderActorToFactory(1105711270, EnemyMetis, "Metis_594");
				break;
			case 8290:
				getLordActor()->addSubGroup(obtainActorFromFactory(110578290));
				orderActorToFactory(1105711290, EnemyMetis, "Metis_595");
				break;
			case 8310:
				getLordActor()->addSubGroup(obtainActorFromFactory(110578310));
				orderActorToFactory(1105711310, EnemyMetis, "Metis_596");
				break;
			case 8330:
				getLordActor()->addSubGroup(obtainActorFromFactory(110578330));
				orderActorToFactory(1105711330, EnemyMetis, "Metis_597");
				break;
			case 8350:
				getLordActor()->addSubGroup(obtainActorFromFactory(110578350));
				orderActorToFactory(1105711350, EnemyMetis, "Metis_598");
				break;
			case 8370:
				getLordActor()->addSubGroup(obtainActorFromFactory(110578370));
				orderActorToFactory(1105711370, EnemyMetis, "Metis_599");
				break;
			case 8390:
				getLordActor()->addSubGroup(obtainActorFromFactory(110578390));
				orderActorToFactory(1105711390, EnemyMetis, "Metis_600");
				break;
			case 8410:
				getLordActor()->addSubGroup(obtainActorFromFactory(110578410));
				orderActorToFactory(1105711410, EnemyMetis, "Metis_601");
				break;
			case 8430:
				getLordActor()->addSubGroup(obtainActorFromFactory(110578430));
				orderActorToFactory(1105711430, EnemyMetis, "Metis_602");
				break;
			case 8450:
				getLordActor()->addSubGroup(obtainActorFromFactory(110578450));
				orderActorToFactory(1105711450, EnemyMetis, "Metis_603");
				break;
			case 8470:
				getLordActor()->addSubGroup(obtainActorFromFactory(110578470));
				orderActorToFactory(1105711470, EnemyMetis, "Metis_604");
				break;
			case 8490:
				getLordActor()->addSubGroup(obtainActorFromFactory(110578490));
				orderActorToFactory(1105711490, EnemyMetis, "Metis_605");
				break;
			case 8500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112778500);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 8510:
				getLordActor()->addSubGroup(obtainActorFromFactory(110578510));
				orderActorToFactory(1105711510, EnemyMetis, "Metis_606");
				break;
			case 8530:
				getLordActor()->addSubGroup(obtainActorFromFactory(110578530));
				orderActorToFactory(1105711530, EnemyMetis, "Metis_607");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112878530);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 8550:
				getLordActor()->addSubGroup(obtainActorFromFactory(110578550));
				orderActorToFactory(1105711550, EnemyMetis, "Metis_608");
				break;
			case 8560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112978560);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 8570:
				getLordActor()->addSubGroup(obtainActorFromFactory(110578570));
				orderActorToFactory(1105711570, EnemyMetis, "Metis_609");
				break;
			case 8590:
				getLordActor()->addSubGroup(obtainActorFromFactory(110578590));
				orderActorToFactory(1105711590, EnemyMetis, "Metis_610");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113078590);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 8610:
				getLordActor()->addSubGroup(obtainActorFromFactory(110578610));
				orderActorToFactory(1105711610, EnemyMetis, "Metis_611");
				break;
			case 8620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113178620);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 8630:
				getLordActor()->addSubGroup(obtainActorFromFactory(110578630));
				orderActorToFactory(1105711630, EnemyMetis, "Metis_612");
				break;
			case 8650:
				getLordActor()->addSubGroup(obtainActorFromFactory(110578650));
				orderActorToFactory(1105711650, EnemyMetis, "Metis_613");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113278650);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 8670:
				getLordActor()->addSubGroup(obtainActorFromFactory(110578670));
				orderActorToFactory(1105711670, EnemyMetis, "Metis_614");
				break;
			case 8690:
				getLordActor()->addSubGroup(obtainActorFromFactory(110578690));
				orderActorToFactory(1105711690, EnemyMetis, "Metis_615");
				break;
			case 8710:
				getLordActor()->addSubGroup(obtainActorFromFactory(110578710));
				orderActorToFactory(1105711710, EnemyMetis, "Metis_616");
				break;
			case 8730:
				getLordActor()->addSubGroup(obtainActorFromFactory(110578730));
				orderActorToFactory(1105711730, EnemyMetis, "Metis_617");
				break;
			case 8750:
				getLordActor()->addSubGroup(obtainActorFromFactory(110578750));
				orderActorToFactory(1105711750, EnemyMetis, "Metis_618");
				break;
			case 8770:
				getLordActor()->addSubGroup(obtainActorFromFactory(110578770));
				orderActorToFactory(1105711770, EnemyMetis, "Metis_619");
				break;
			case 8790:
				getLordActor()->addSubGroup(obtainActorFromFactory(110578790));
				orderActorToFactory(1105711790, EnemyMetis, "Metis_620");
				break;
			case 8810:
				getLordActor()->addSubGroup(obtainActorFromFactory(110578810));
				orderActorToFactory(1105711810, EnemyMetis, "Metis_621");
				break;
			case 8830:
				getLordActor()->addSubGroup(obtainActorFromFactory(110578830));
				orderActorToFactory(1105711830, EnemyMetis, "Metis_622");
				break;
			case 8850:
				getLordActor()->addSubGroup(obtainActorFromFactory(110578850));
				orderActorToFactory(1105711850, EnemyMetis, "Metis_623");
				break;
			case 8870:
				getLordActor()->addSubGroup(obtainActorFromFactory(110578870));
				orderActorToFactory(1105711870, EnemyMetis, "Metis_624");
				break;
			case 8890:
				getLordActor()->addSubGroup(obtainActorFromFactory(110578890));
				orderActorToFactory(1105711890, EnemyMetis, "Metis_625");
				break;
			case 8910:
				getLordActor()->addSubGroup(obtainActorFromFactory(110578910));
				orderActorToFactory(1105711910, EnemyMetis, "Metis_626");
				break;
			case 8930:
				getLordActor()->addSubGroup(obtainActorFromFactory(110578930));
				orderActorToFactory(1105711930, EnemyMetis, "Metis_627");
				break;
			case 8950:
				getLordActor()->addSubGroup(obtainActorFromFactory(110578950));
				orderActorToFactory(1105711950, EnemyMetis, "Metis_628");
				break;
			case 8970:
				getLordActor()->addSubGroup(obtainActorFromFactory(110578970));
				orderActorToFactory(1105711970, EnemyMetis, "Metis_629");
				break;
			case 8990:
				getLordActor()->addSubGroup(obtainActorFromFactory(110578990));
				orderActorToFactory(1105711990, EnemyMetis, "Metis_630");
				break;
			case 9000:
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(112579000);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 9010:
				getLordActor()->addSubGroup(obtainActorFromFactory(110579010));
				orderActorToFactory(1105712010, EnemyMetis, "Metis_631");
				orderActorToFactory(1124712010, FormationIris001, "F001_Iris_632");
				break;
			case 9030:
				getLordActor()->addSubGroup(obtainActorFromFactory(110579030));
				orderActorToFactory(1105712030, EnemyMetis, "Metis_633");
				break;
			case 9050:
				getLordActor()->addSubGroup(obtainActorFromFactory(110579050));
				orderActorToFactory(1105712050, EnemyMetis, "Metis_634");
				break;
			case 9070:
				getLordActor()->addSubGroup(obtainActorFromFactory(110579070));
				orderActorToFactory(1105712070, EnemyMetis, "Metis_635");
				break;
			case 9090:
				getLordActor()->addSubGroup(obtainActorFromFactory(110579090));
				orderActorToFactory(1105712090, EnemyMetis, "Metis_636");
				break;
			case 9110:
				getLordActor()->addSubGroup(obtainActorFromFactory(110579110));
				orderActorToFactory(1105712110, EnemyMetis, "Metis_637");
				break;
			case 9130:
				getLordActor()->addSubGroup(obtainActorFromFactory(110579130));
				orderActorToFactory(1105712130, EnemyMetis, "Metis_638");
				break;
			case 9150:
				getLordActor()->addSubGroup(obtainActorFromFactory(110579150));
				orderActorToFactory(1105712150, EnemyMetis, "Metis_639");
				break;
			case 9170:
				getLordActor()->addSubGroup(obtainActorFromFactory(110579170));
				orderActorToFactory(1105712170, EnemyMetis, "Metis_640");
				break;
			case 9190:
				getLordActor()->addSubGroup(obtainActorFromFactory(110579190));
				orderActorToFactory(1105712190, EnemyMetis, "Metis_641");
				break;
			case 9210:
				getLordActor()->addSubGroup(obtainActorFromFactory(110579210));
				orderActorToFactory(1105712210, EnemyMetis, "Metis_642");
				break;
			case 9230:
				getLordActor()->addSubGroup(obtainActorFromFactory(110579230));
				orderActorToFactory(1105712230, EnemyMetis, "Metis_643");
				break;
			case 9250:
				getLordActor()->addSubGroup(obtainActorFromFactory(110579250));
				orderActorToFactory(1105712250, EnemyMetis, "Metis_644");
				break;
			case 9270:
				getLordActor()->addSubGroup(obtainActorFromFactory(110579270));
				orderActorToFactory(1105712270, EnemyMetis, "Metis_645");
				break;
			case 9290:
				getLordActor()->addSubGroup(obtainActorFromFactory(110579290));
				orderActorToFactory(1105712290, EnemyMetis, "Metis_646");
				break;
			case 9310:
				getLordActor()->addSubGroup(obtainActorFromFactory(110579310));
				orderActorToFactory(1105712310, EnemyMetis, "Metis_647");
				break;
			case 9330:
				getLordActor()->addSubGroup(obtainActorFromFactory(110579330));
				orderActorToFactory(1105712330, EnemyMetis, "Metis_648");
				break;
			case 9350:
				getLordActor()->addSubGroup(obtainActorFromFactory(110579350));
				orderActorToFactory(1105712350, EnemyMetis, "Metis_649");
				break;
			case 9370:
				getLordActor()->addSubGroup(obtainActorFromFactory(110579370));
				orderActorToFactory(1105712370, EnemyMetis, "Metis_650");
				break;
			case 9390:
				getLordActor()->addSubGroup(obtainActorFromFactory(110579390));
				orderActorToFactory(1105712390, EnemyMetis, "Metis_651");
				break;
			case 9410:
				getLordActor()->addSubGroup(obtainActorFromFactory(110579410));
				orderActorToFactory(1105712410, EnemyMetis, "Metis_652");
				break;
			case 9430:
				getLordActor()->addSubGroup(obtainActorFromFactory(110579430));
				orderActorToFactory(1105712430, EnemyMetis, "Metis_653");
				break;
			case 9450:
				getLordActor()->addSubGroup(obtainActorFromFactory(110579450));
				orderActorToFactory(1105712450, EnemyMetis, "Metis_654");
				break;
			case 9470:
				getLordActor()->addSubGroup(obtainActorFromFactory(110579470));
				orderActorToFactory(1105712470, EnemyMetis, "Metis_655");
				break;
			case 9490:
				getLordActor()->addSubGroup(obtainActorFromFactory(110579490));
				orderActorToFactory(1105712490, EnemyMetis, "Metis_656");
				break;
			case 9500:
				orderActorWithDpToFactory(1127712500, EnemyCeres, "Ceres_657", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 9510:
				getLordActor()->addSubGroup(obtainActorFromFactory(110579510));
				orderActorToFactory(1105712510, EnemyMetis, "Metis_658");
				break;
			case 9530:
				getLordActor()->addSubGroup(obtainActorFromFactory(110579530));
				orderActorToFactory(1105712530, EnemyMetis, "Metis_659");
				orderActorWithDpToFactory(1128712530, EnemyCeres, "Ceres_660", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 9550:
				getLordActor()->addSubGroup(obtainActorFromFactory(110579550));
				orderActorToFactory(1105712550, EnemyMetis, "Metis_661");
				break;
			case 9560:
				orderActorWithDpToFactory(1129712560, EnemyCeres, "Ceres_662", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 9570:
				getLordActor()->addSubGroup(obtainActorFromFactory(110579570));
				orderActorToFactory(1105712570, EnemyMetis, "Metis_663");
				break;
			case 9590:
				getLordActor()->addSubGroup(obtainActorFromFactory(110579590));
				orderActorToFactory(1105712590, EnemyMetis, "Metis_664");
				orderActorWithDpToFactory(1130712590, EnemyCeres, "Ceres_665", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 9610:
				getLordActor()->addSubGroup(obtainActorFromFactory(110579610));
				orderActorToFactory(1105712610, EnemyMetis, "Metis_666");
				break;
			case 9620:
				orderActorWithDpToFactory(1131712620, EnemyCeres, "Ceres_667", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 9630:
				getLordActor()->addSubGroup(obtainActorFromFactory(110579630));
				orderActorToFactory(1105712630, EnemyMetis, "Metis_668");
				break;
			case 9650:
				getLordActor()->addSubGroup(obtainActorFromFactory(110579650));
				orderActorToFactory(1105712650, EnemyMetis, "Metis_669");
				orderActorWithDpToFactory(1132712650, EnemyCeres, "Ceres_670", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 9670:
				getLordActor()->addSubGroup(obtainActorFromFactory(110579670));
				orderActorToFactory(1105712670, EnemyMetis, "Metis_671");
				break;
			case 9690:
				getLordActor()->addSubGroup(obtainActorFromFactory(110579690));
				orderActorToFactory(1105712690, EnemyMetis, "Metis_672");
				break;
			case 9710:
				getLordActor()->addSubGroup(obtainActorFromFactory(110579710));
				orderActorToFactory(1105712710, EnemyMetis, "Metis_673");
				break;
			case 9730:
				getLordActor()->addSubGroup(obtainActorFromFactory(110579730));
				orderActorToFactory(1105712730, EnemyMetis, "Metis_674");
				break;
			case 9750:
				getLordActor()->addSubGroup(obtainActorFromFactory(110579750));
				orderActorToFactory(1105712750, EnemyMetis, "Metis_675");
				break;
			case 9770:
				getLordActor()->addSubGroup(obtainActorFromFactory(110579770));
				orderActorToFactory(1105712770, EnemyMetis, "Metis_676");
				break;
			case 9790:
				getLordActor()->addSubGroup(obtainActorFromFactory(110579790));
				orderActorToFactory(1105712790, EnemyMetis, "Metis_677");
				break;
			case 9810:
				getLordActor()->addSubGroup(obtainActorFromFactory(110579810));
				orderActorToFactory(1105712810, EnemyMetis, "Metis_678");
				break;
			case 9830:
				getLordActor()->addSubGroup(obtainActorFromFactory(110579830));
				orderActorToFactory(1105712830, EnemyMetis, "Metis_679");
				break;
			case 9850:
				getLordActor()->addSubGroup(obtainActorFromFactory(110579850));
				orderActorToFactory(1105712850, EnemyMetis, "Metis_680");
				break;
			case 9870:
				getLordActor()->addSubGroup(obtainActorFromFactory(110579870));
				orderActorToFactory(1105712870, EnemyMetis, "Metis_681");
				break;
			case 9890:
				getLordActor()->addSubGroup(obtainActorFromFactory(110579890));
				orderActorToFactory(1105712890, EnemyMetis, "Metis_682");
				break;
			case 9910:
				getLordActor()->addSubGroup(obtainActorFromFactory(110579910));
				orderActorToFactory(1105712910, EnemyMetis, "Metis_683");
				break;
			case 9930:
				getLordActor()->addSubGroup(obtainActorFromFactory(110579930));
				orderActorToFactory(1105712930, EnemyMetis, "Metis_684");
				break;
			case 9950:
				getLordActor()->addSubGroup(obtainActorFromFactory(110579950));
				orderActorToFactory(1105712950, EnemyMetis, "Metis_685");
				break;
			case 9970:
				getLordActor()->addSubGroup(obtainActorFromFactory(110579970));
				orderActorToFactory(1105712970, EnemyMetis, "Metis_686");
				break;
			case 9990:
				getLordActor()->addSubGroup(obtainActorFromFactory(110579990));
				orderActorToFactory(1105712990, EnemyMetis, "Metis_687");
				break;
			case 10000:
				orderActorToFactory(1125713000, FormationIris002, "F002_Iris_688");
				break;
			case 10010:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105710010));
				orderActorToFactory(1105713010, EnemyMetis, "Metis_689");
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(1124710010);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 10030:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105710030));
				orderActorToFactory(1105713030, EnemyMetis, "Metis_690");
				break;
			case 10050:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105710050));
				orderActorToFactory(1105713050, EnemyMetis, "Metis_691");
				break;
			case 10070:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105710070));
				orderActorToFactory(1105713070, EnemyMetis, "Metis_692");
				break;
			case 10090:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105710090));
				orderActorToFactory(1105713090, EnemyMetis, "Metis_693");
				break;
			case 10110:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105710110));
				orderActorToFactory(1105713110, EnemyMetis, "Metis_694");
				break;
			case 10130:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105710130));
				orderActorToFactory(1105713130, EnemyMetis, "Metis_695");
				break;
			case 10150:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105710150));
				orderActorToFactory(1105713150, EnemyMetis, "Metis_696");
				break;
			case 10170:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105710170));
				orderActorToFactory(1105713170, EnemyMetis, "Metis_697");
				break;
			case 10190:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105710190));
				orderActorToFactory(1105713190, EnemyMetis, "Metis_698");
				break;
			case 10210:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105710210));
				orderActorToFactory(1105713210, EnemyMetis, "Metis_699");
				break;
			case 10230:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105710230));
				orderActorToFactory(1105713230, EnemyMetis, "Metis_700");
				break;
			case 10250:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105710250));
				orderActorToFactory(1105713250, EnemyMetis, "Metis_701");
				break;
			case 10270:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105710270));
				orderActorToFactory(1105713270, EnemyMetis, "Metis_702");
				break;
			case 10290:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105710290));
				orderActorToFactory(1105713290, EnemyMetis, "Metis_703");
				break;
			case 10310:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105710310));
				orderActorToFactory(1105713310, EnemyMetis, "Metis_704");
				break;
			case 10330:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105710330));
				orderActorToFactory(1105713330, EnemyMetis, "Metis_705");
				break;
			case 10350:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105710350));
				orderActorToFactory(1105713350, EnemyMetis, "Metis_706");
				break;
			case 10370:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105710370));
				orderActorToFactory(1105713370, EnemyMetis, "Metis_707");
				break;
			case 10390:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105710390));
				orderActorToFactory(1105713390, EnemyMetis, "Metis_708");
				break;
			case 10410:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105710410));
				orderActorToFactory(1105713410, EnemyMetis, "Metis_709");
				break;
			case 10430:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105710430));
				orderActorToFactory(1105713430, EnemyMetis, "Metis_710");
				break;
			case 10450:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105710450));
				orderActorToFactory(1105713450, EnemyMetis, "Metis_711");
				break;
			case 10470:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105710470));
				orderActorToFactory(1105713470, EnemyMetis, "Metis_712");
				break;
			case 10490:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105710490));
				orderActorToFactory(1105713490, EnemyMetis, "Metis_713");
				break;
			case 10510:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105710510));
				orderActorToFactory(1105713510, EnemyMetis, "Metis_714");
				break;
			case 10530:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105710530));
				orderActorToFactory(1105713530, EnemyMetis, "Metis_715");
				break;
			case 10550:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105710550));
				orderActorToFactory(1105713550, EnemyMetis, "Metis_716");
				break;
			case 10570:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105710570));
				orderActorToFactory(1105713570, EnemyMetis, "Metis_717");
				break;
			case 10590:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105710590));
				orderActorToFactory(1105713590, EnemyMetis, "Metis_718");
				break;
			case 10610:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105710610));
				orderActorToFactory(1105713610, EnemyMetis, "Metis_719");
				break;
			case 10630:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105710630));
				orderActorToFactory(1105713630, EnemyMetis, "Metis_720");
				break;
			case 10650:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105710650));
				orderActorToFactory(1105713650, EnemyMetis, "Metis_721");
				break;
			case 10670:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105710670));
				orderActorToFactory(1105713670, EnemyMetis, "Metis_722");
				break;
			case 10690:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105710690));
				orderActorToFactory(1105713690, EnemyMetis, "Metis_723");
				break;
			case 10710:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105710710));
				orderActorToFactory(1105713710, EnemyMetis, "Metis_724");
				break;
			case 10730:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105710730));
				orderActorToFactory(1105713730, EnemyMetis, "Metis_725");
				break;
			case 10750:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105710750));
				orderActorToFactory(1105713750, EnemyMetis, "Metis_726");
				break;
			case 10770:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105710770));
				orderActorToFactory(1105713770, EnemyMetis, "Metis_727");
				break;
			case 10790:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105710790));
				orderActorToFactory(1105713790, EnemyMetis, "Metis_728");
				break;
			case 10810:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105710810));
				orderActorToFactory(1105713810, EnemyMetis, "Metis_729");
				break;
			case 10830:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105710830));
				orderActorToFactory(1105713830, EnemyMetis, "Metis_730");
				break;
			case 10850:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105710850));
				orderActorToFactory(1105713850, EnemyMetis, "Metis_731");
				break;
			case 10870:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105710870));
				orderActorToFactory(1105713870, EnemyMetis, "Metis_732");
				break;
			case 10890:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105710890));
				orderActorToFactory(1105713890, EnemyMetis, "Metis_733");
				break;
			case 10910:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105710910));
				orderActorToFactory(1105713910, EnemyMetis, "Metis_734");
				break;
			case 10930:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105710930));
				orderActorToFactory(1105713930, EnemyMetis, "Metis_735");
				break;
			case 10950:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105710950));
				orderActorToFactory(1105713950, EnemyMetis, "Metis_736");
				break;
			case 10970:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105710970));
				orderActorToFactory(1105713970, EnemyMetis, "Metis_737");
				break;
			case 10990:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105710990));
				orderActorToFactory(1105713990, EnemyMetis, "Metis_738");
				break;
			case 11000:
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(1125711000);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 11010:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105711010));
				orderActorToFactory(1105714010, EnemyMetis, "Metis_739");
				orderActorToFactory(1124714010, FormationIris001, "F001_Iris_740");
				break;
			case 11030:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105711030));
				orderActorToFactory(1105714030, EnemyMetis, "Metis_741");
				break;
			case 11050:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105711050));
				orderActorToFactory(1105714050, EnemyMetis, "Metis_742");
				break;
			case 11070:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105711070));
				orderActorToFactory(1105714070, EnemyMetis, "Metis_743");
				break;
			case 11090:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105711090));
				orderActorToFactory(1105714090, EnemyMetis, "Metis_744");
				break;
			case 11110:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105711110));
				orderActorToFactory(1105714110, EnemyMetis, "Metis_745");
				break;
			case 11130:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105711130));
				orderActorToFactory(1105714130, EnemyMetis, "Metis_746");
				break;
			case 11150:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105711150));
				orderActorToFactory(1105714150, EnemyMetis, "Metis_747");
				break;
			case 11170:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105711170));
				orderActorToFactory(1105714170, EnemyMetis, "Metis_748");
				break;
			case 11190:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105711190));
				orderActorToFactory(1105714190, EnemyMetis, "Metis_749");
				break;
			case 11210:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105711210));
				orderActorToFactory(1105714210, EnemyMetis, "Metis_750");
				break;
			case 11230:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105711230));
				orderActorToFactory(1105714230, EnemyMetis, "Metis_751");
				break;
			case 11250:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105711250));
				orderActorToFactory(1105714250, EnemyMetis, "Metis_752");
				break;
			case 11270:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105711270));
				orderActorToFactory(1105714270, EnemyMetis, "Metis_753");
				break;
			case 11290:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105711290));
				orderActorToFactory(1105714290, EnemyMetis, "Metis_754");
				break;
			case 11310:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105711310));
				orderActorToFactory(1105714310, EnemyMetis, "Metis_755");
				break;
			case 11330:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105711330));
				orderActorToFactory(1105714330, EnemyMetis, "Metis_756");
				break;
			case 11350:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105711350));
				orderActorToFactory(1105714350, EnemyMetis, "Metis_757");
				break;
			case 11370:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105711370));
				orderActorToFactory(1105714370, EnemyMetis, "Metis_758");
				break;
			case 11390:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105711390));
				orderActorToFactory(1105714390, EnemyMetis, "Metis_759");
				break;
			case 11410:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105711410));
				orderActorToFactory(1105714410, EnemyMetis, "Metis_760");
				break;
			case 11430:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105711430));
				orderActorToFactory(1105714430, EnemyMetis, "Metis_761");
				break;
			case 11450:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105711450));
				orderActorToFactory(1105714450, EnemyMetis, "Metis_762");
				break;
			case 11470:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105711470));
				orderActorToFactory(1105714470, EnemyMetis, "Metis_763");
				break;
			case 11490:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105711490));
				orderActorToFactory(1105714490, EnemyMetis, "Metis_764");
				break;
			case 11510:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105711510));
				orderActorToFactory(1105714510, EnemyMetis, "Metis_765");
				break;
			case 11530:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105711530));
				orderActorToFactory(1105714530, EnemyMetis, "Metis_766");
				break;
			case 11550:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105711550));
				orderActorToFactory(1105714550, EnemyMetis, "Metis_767");
				break;
			case 11570:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105711570));
				orderActorToFactory(1105714570, EnemyMetis, "Metis_768");
				break;
			case 11590:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105711590));
				orderActorToFactory(1105714590, EnemyMetis, "Metis_769");
				break;
			case 11610:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105711610));
				orderActorToFactory(1105714610, EnemyMetis, "Metis_770");
				break;
			case 11630:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105711630));
				orderActorToFactory(1105714630, EnemyMetis, "Metis_771");
				break;
			case 11650:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105711650));
				orderActorToFactory(1105714650, EnemyMetis, "Metis_772");
				break;
			case 11670:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105711670));
				orderActorToFactory(1105714670, EnemyMetis, "Metis_773");
				break;
			case 11690:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105711690));
				orderActorToFactory(1105714690, EnemyMetis, "Metis_774");
				break;
			case 11710:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105711710));
				orderActorToFactory(1105714710, EnemyMetis, "Metis_775");
				break;
			case 11730:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105711730));
				orderActorToFactory(1105714730, EnemyMetis, "Metis_776");
				break;
			case 11750:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105711750));
				orderActorToFactory(1105714750, EnemyMetis, "Metis_777");
				break;
			case 11770:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105711770));
				orderActorToFactory(1105714770, EnemyMetis, "Metis_778");
				break;
			case 11790:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105711790));
				orderActorToFactory(1105714790, EnemyMetis, "Metis_779");
				break;
			case 11810:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105711810));
				orderActorToFactory(1105714810, EnemyMetis, "Metis_780");
				break;
			case 11830:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105711830));
				orderActorToFactory(1105714830, EnemyMetis, "Metis_781");
				break;
			case 11850:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105711850));
				orderActorToFactory(1105714850, EnemyMetis, "Metis_782");
				break;
			case 11870:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105711870));
				orderActorToFactory(1105714870, EnemyMetis, "Metis_783");
				break;
			case 11890:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105711890));
				orderActorToFactory(1105714890, EnemyMetis, "Metis_784");
				break;
			case 11910:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105711910));
				orderActorToFactory(1105714910, EnemyMetis, "Metis_785");
				break;
			case 11930:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105711930));
				orderActorToFactory(1105714930, EnemyMetis, "Metis_786");
				break;
			case 11950:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105711950));
				orderActorToFactory(1105714950, EnemyMetis, "Metis_787");
				break;
			case 11970:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105711970));
				orderActorToFactory(1105714970, EnemyMetis, "Metis_788");
				break;
			case 11990:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105711990));
				orderActorToFactory(1105714990, EnemyMetis, "Metis_789");
				break;
			case 12000:
				orderActorToFactory(1125715000, FormationIris002, "F002_Iris_790");
				break;
			case 12010:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105712010));
				orderActorToFactory(1105715010, EnemyMetis, "Metis_791");
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(1124712010);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 12030:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105712030));
				orderActorToFactory(1105715030, EnemyMetis, "Metis_792");
				break;
			case 12050:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105712050));
				orderActorToFactory(1105715050, EnemyMetis, "Metis_793");
				break;
			case 12070:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105712070));
				orderActorToFactory(1105715070, EnemyMetis, "Metis_794");
				break;
			case 12090:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105712090));
				orderActorToFactory(1105715090, EnemyMetis, "Metis_795");
				break;
			case 12110:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105712110));
				orderActorToFactory(1105715110, EnemyMetis, "Metis_796");
				break;
			case 12130:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105712130));
				orderActorToFactory(1105715130, EnemyMetis, "Metis_797");
				break;
			case 12150:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105712150));
				orderActorToFactory(1105715150, EnemyMetis, "Metis_798");
				break;
			case 12170:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105712170));
				orderActorToFactory(1105715170, EnemyMetis, "Metis_799");
				break;
			case 12190:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105712190));
				orderActorToFactory(1105715190, EnemyMetis, "Metis_800");
				break;
			case 12210:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105712210));
				orderActorToFactory(1105715210, EnemyMetis, "Metis_801");
				break;
			case 12230:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105712230));
				orderActorToFactory(1105715230, EnemyMetis, "Metis_802");
				break;
			case 12250:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105712250));
				orderActorToFactory(1105715250, EnemyMetis, "Metis_803");
				break;
			case 12270:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105712270));
				orderActorToFactory(1105715270, EnemyMetis, "Metis_804");
				break;
			case 12290:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105712290));
				orderActorToFactory(1105715290, EnemyMetis, "Metis_805");
				break;
			case 12310:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105712310));
				orderActorToFactory(1105715310, EnemyMetis, "Metis_806");
				break;
			case 12330:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105712330));
				orderActorToFactory(1105715330, EnemyMetis, "Metis_807");
				break;
			case 12350:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105712350));
				orderActorToFactory(1105715350, EnemyMetis, "Metis_808");
				break;
			case 12370:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105712370));
				orderActorToFactory(1105715370, EnemyMetis, "Metis_809");
				break;
			case 12390:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105712390));
				orderActorToFactory(1105715390, EnemyMetis, "Metis_810");
				break;
			case 12410:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105712410));
				orderActorToFactory(1105715410, EnemyMetis, "Metis_811");
				break;
			case 12430:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105712430));
				orderActorToFactory(1105715430, EnemyMetis, "Metis_812");
				break;
			case 12450:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105712450));
				orderActorToFactory(1105715450, EnemyMetis, "Metis_813");
				break;
			case 12470:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105712470));
				orderActorToFactory(1105715470, EnemyMetis, "Metis_814");
				break;
			case 12490:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105712490));
				orderActorToFactory(1105715490, EnemyMetis, "Metis_815");
				break;
			case 12500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1127712500);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 12510:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105712510));
				orderActorToFactory(1105715510, EnemyMetis, "Metis_816");
				break;
			case 12530:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105712530));
				orderActorToFactory(1105715530, EnemyMetis, "Metis_817");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1128712530);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 12550:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105712550));
				orderActorToFactory(1105715550, EnemyMetis, "Metis_818");
				break;
			case 12560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1129712560);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 12570:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105712570));
				orderActorToFactory(1105715570, EnemyMetis, "Metis_819");
				break;
			case 12590:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105712590));
				orderActorToFactory(1105715590, EnemyMetis, "Metis_820");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1130712590);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 12610:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105712610));
				orderActorToFactory(1105715610, EnemyMetis, "Metis_821");
				break;
			case 12620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1131712620);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 12630:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105712630));
				orderActorToFactory(1105715630, EnemyMetis, "Metis_822");
				break;
			case 12650:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105712650));
				orderActorToFactory(1105715650, EnemyMetis, "Metis_823");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1132712650);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 12670:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105712670));
				orderActorToFactory(1105715670, EnemyMetis, "Metis_824");
				break;
			case 12690:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105712690));
				orderActorToFactory(1105715690, EnemyMetis, "Metis_825");
				break;
			case 12710:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105712710));
				orderActorToFactory(1105715710, EnemyMetis, "Metis_826");
				break;
			case 12730:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105712730));
				orderActorToFactory(1105715730, EnemyMetis, "Metis_827");
				break;
			case 12750:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105712750));
				orderActorToFactory(1105715750, EnemyMetis, "Metis_828");
				break;
			case 12770:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105712770));
				orderActorToFactory(1105715770, EnemyMetis, "Metis_829");
				break;
			case 12790:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105712790));
				orderActorToFactory(1105715790, EnemyMetis, "Metis_830");
				break;
			case 12810:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105712810));
				orderActorToFactory(1105715810, EnemyMetis, "Metis_831");
				break;
			case 12830:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105712830));
				orderActorToFactory(1105715830, EnemyMetis, "Metis_832");
				break;
			case 12850:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105712850));
				orderActorToFactory(1105715850, EnemyMetis, "Metis_833");
				break;
			case 12870:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105712870));
				orderActorToFactory(1105715870, EnemyMetis, "Metis_834");
				break;
			case 12890:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105712890));
				orderActorToFactory(1105715890, EnemyMetis, "Metis_835");
				break;
			case 12910:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105712910));
				orderActorToFactory(1105715910, EnemyMetis, "Metis_836");
				break;
			case 12930:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105712930));
				orderActorToFactory(1105715930, EnemyMetis, "Metis_837");
				break;
			case 12950:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105712950));
				orderActorToFactory(1105715950, EnemyMetis, "Metis_838");
				break;
			case 12970:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105712970));
				orderActorToFactory(1105715970, EnemyMetis, "Metis_839");
				break;
			case 12990:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105712990));
				orderActorToFactory(1105715990, EnemyMetis, "Metis_840");
				break;
			case 13000:
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(1125713000);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 13010:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105713010));
				orderActorToFactory(1105716010, EnemyMetis, "Metis_841");
				orderActorToFactory(1124716010, FormationIris001, "F001_Iris_842");
				break;
			case 13030:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105713030));
				orderActorToFactory(1105716030, EnemyMetis, "Metis_843");
				break;
			case 13050:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105713050));
				orderActorToFactory(1105716050, EnemyMetis, "Metis_844");
				break;
			case 13070:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105713070));
				orderActorToFactory(1105716070, EnemyMetis, "Metis_845");
				break;
			case 13090:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105713090));
				orderActorToFactory(1105716090, EnemyMetis, "Metis_846");
				break;
			case 13110:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105713110));
				orderActorToFactory(1105716110, EnemyMetis, "Metis_847");
				break;
			case 13130:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105713130));
				orderActorToFactory(1105716130, EnemyMetis, "Metis_848");
				break;
			case 13150:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105713150));
				orderActorToFactory(1105716150, EnemyMetis, "Metis_849");
				break;
			case 13170:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105713170));
				orderActorToFactory(1105716170, EnemyMetis, "Metis_850");
				break;
			case 13190:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105713190));
				orderActorToFactory(1105716190, EnemyMetis, "Metis_851");
				break;
			case 13210:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105713210));
				orderActorToFactory(1105716210, EnemyMetis, "Metis_852");
				break;
			case 13230:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105713230));
				orderActorToFactory(1105716230, EnemyMetis, "Metis_853");
				break;
			case 13250:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105713250));
				orderActorToFactory(1105716250, EnemyMetis, "Metis_854");
				break;
			case 13270:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105713270));
				orderActorToFactory(1105716270, EnemyMetis, "Metis_855");
				break;
			case 13290:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105713290));
				orderActorToFactory(1105716290, EnemyMetis, "Metis_856");
				break;
			case 13310:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105713310));
				orderActorToFactory(1105716310, EnemyMetis, "Metis_857");
				break;
			case 13330:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105713330));
				orderActorToFactory(1105716330, EnemyMetis, "Metis_858");
				break;
			case 13350:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105713350));
				orderActorToFactory(1105716350, EnemyMetis, "Metis_859");
				break;
			case 13370:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105713370));
				orderActorToFactory(1105716370, EnemyMetis, "Metis_860");
				break;
			case 13390:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105713390));
				orderActorToFactory(1105716390, EnemyMetis, "Metis_861");
				break;
			case 13410:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105713410));
				orderActorToFactory(1105716410, EnemyMetis, "Metis_862");
				break;
			case 13430:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105713430));
				orderActorToFactory(1105716430, EnemyMetis, "Metis_863");
				break;
			case 13450:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105713450));
				orderActorToFactory(1105716450, EnemyMetis, "Metis_864");
				break;
			case 13470:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105713470));
				orderActorToFactory(1105716470, EnemyMetis, "Metis_865");
				break;
			case 13490:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105713490));
				orderActorToFactory(1105716490, EnemyMetis, "Metis_866");
				break;
			case 13500:
				orderActorWithDpToFactory(1127716500, EnemyCeres, "Ceres_867", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 13510:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105713510));
				orderActorToFactory(1105716510, EnemyMetis, "Metis_868");
				break;
			case 13530:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105713530));
				orderActorToFactory(1105716530, EnemyMetis, "Metis_869");
				orderActorWithDpToFactory(1128716530, EnemyCeres, "Ceres_870", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 13550:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105713550));
				orderActorToFactory(1105716550, EnemyMetis, "Metis_871");
				break;
			case 13560:
				orderActorWithDpToFactory(1129716560, EnemyCeres, "Ceres_872", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 13570:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105713570));
				orderActorToFactory(1105716570, EnemyMetis, "Metis_873");
				break;
			case 13590:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105713590));
				orderActorToFactory(1105716590, EnemyMetis, "Metis_874");
				orderActorWithDpToFactory(1130716590, EnemyCeres, "Ceres_875", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 13610:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105713610));
				orderActorToFactory(1105716610, EnemyMetis, "Metis_876");
				break;
			case 13620:
				orderActorWithDpToFactory(1131716620, EnemyCeres, "Ceres_877", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 13630:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105713630));
				orderActorToFactory(1105716630, EnemyMetis, "Metis_878");
				break;
			case 13650:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105713650));
				orderActorToFactory(1105716650, EnemyMetis, "Metis_879");
				orderActorWithDpToFactory(1132716650, EnemyCeres, "Ceres_880", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 13670:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105713670));
				orderActorToFactory(1105716670, EnemyMetis, "Metis_881");
				break;
			case 13690:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105713690));
				orderActorToFactory(1105716690, EnemyMetis, "Metis_882");
				break;
			case 13710:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105713710));
				orderActorToFactory(1105716710, EnemyMetis, "Metis_883");
				break;
			case 13730:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105713730));
				orderActorToFactory(1105716730, EnemyMetis, "Metis_884");
				break;
			case 13750:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105713750));
				orderActorToFactory(1105716750, EnemyMetis, "Metis_885");
				break;
			case 13770:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105713770));
				orderActorToFactory(1105716770, EnemyMetis, "Metis_886");
				break;
			case 13790:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105713790));
				orderActorToFactory(1105716790, EnemyMetis, "Metis_887");
				break;
			case 13810:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105713810));
				orderActorToFactory(1105716810, EnemyMetis, "Metis_888");
				break;
			case 13830:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105713830));
				orderActorToFactory(1105716830, EnemyMetis, "Metis_889");
				break;
			case 13850:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105713850));
				orderActorToFactory(1105716850, EnemyMetis, "Metis_890");
				break;
			case 13870:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105713870));
				orderActorToFactory(1105716870, EnemyMetis, "Metis_891");
				break;
			case 13890:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105713890));
				orderActorToFactory(1105716890, EnemyMetis, "Metis_892");
				break;
			case 13910:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105713910));
				orderActorToFactory(1105716910, EnemyMetis, "Metis_893");
				break;
			case 13930:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105713930));
				orderActorToFactory(1105716930, EnemyMetis, "Metis_894");
				break;
			case 13950:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105713950));
				orderActorToFactory(1105716950, EnemyMetis, "Metis_895");
				break;
			case 13970:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105713970));
				orderActorToFactory(1105716970, EnemyMetis, "Metis_896");
				break;
			case 13990:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105713990));
				orderActorToFactory(1105716990, EnemyMetis, "Metis_897");
				break;
			case 14000:
				orderActorToFactory(1125717000, FormationIris002, "F002_Iris_898");
				break;
			case 14010:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105714010));
				orderActorToFactory(1105717010, EnemyMetis, "Metis_899");
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(1124714010);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 14030:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105714030));
				orderActorToFactory(1105717030, EnemyMetis, "Metis_900");
				break;
			case 14050:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105714050));
				orderActorToFactory(1105717050, EnemyMetis, "Metis_901");
				break;
			case 14070:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105714070));
				orderActorToFactory(1105717070, EnemyMetis, "Metis_902");
				break;
			case 14090:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105714090));
				orderActorToFactory(1105717090, EnemyMetis, "Metis_903");
				break;
			case 14110:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105714110));
				orderActorToFactory(1105717110, EnemyMetis, "Metis_904");
				break;
			case 14130:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105714130));
				orderActorToFactory(1105717130, EnemyMetis, "Metis_905");
				break;
			case 14150:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105714150));
				orderActorToFactory(1105717150, EnemyMetis, "Metis_906");
				break;
			case 14170:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105714170));
				orderActorToFactory(1105717170, EnemyMetis, "Metis_907");
				break;
			case 14190:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105714190));
				orderActorToFactory(1105717190, EnemyMetis, "Metis_908");
				break;
			case 14210:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105714210));
				orderActorToFactory(1105717210, EnemyMetis, "Metis_909");
				break;
			case 14230:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105714230));
				orderActorToFactory(1105717230, EnemyMetis, "Metis_910");
				break;
			case 14250:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105714250));
				orderActorToFactory(1105717250, EnemyMetis, "Metis_911");
				break;
			case 14270:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105714270));
				orderActorToFactory(1105717270, EnemyMetis, "Metis_912");
				break;
			case 14290:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105714290));
				orderActorToFactory(1105717290, EnemyMetis, "Metis_913");
				break;
			case 14310:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105714310));
				orderActorToFactory(1105717310, EnemyMetis, "Metis_914");
				break;
			case 14330:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105714330));
				orderActorToFactory(1105717330, EnemyMetis, "Metis_915");
				break;
			case 14350:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105714350));
				orderActorToFactory(1105717350, EnemyMetis, "Metis_916");
				break;
			case 14370:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105714370));
				orderActorToFactory(1105717370, EnemyMetis, "Metis_917");
				break;
			case 14390:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105714390));
				orderActorToFactory(1105717390, EnemyMetis, "Metis_918");
				break;
			case 14410:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105714410));
				orderActorToFactory(1105717410, EnemyMetis, "Metis_919");
				break;
			case 14430:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105714430));
				orderActorToFactory(1105717430, EnemyMetis, "Metis_920");
				break;
			case 14450:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105714450));
				orderActorToFactory(1105717450, EnemyMetis, "Metis_921");
				break;
			case 14470:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105714470));
				orderActorToFactory(1105717470, EnemyMetis, "Metis_922");
				break;
			case 14490:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105714490));
				orderActorToFactory(1105717490, EnemyMetis, "Metis_923");
				break;
			case 14510:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105714510));
				orderActorToFactory(1105717510, EnemyMetis, "Metis_924");
				break;
			case 14530:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105714530));
				orderActorToFactory(1105717530, EnemyMetis, "Metis_925");
				break;
			case 14550:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105714550));
				orderActorToFactory(1105717550, EnemyMetis, "Metis_926");
				break;
			case 14570:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105714570));
				orderActorToFactory(1105717570, EnemyMetis, "Metis_927");
				break;
			case 14590:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105714590));
				orderActorToFactory(1105717590, EnemyMetis, "Metis_928");
				break;
			case 14610:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105714610));
				orderActorToFactory(1105717610, EnemyMetis, "Metis_929");
				break;
			case 14630:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105714630));
				orderActorToFactory(1105717630, EnemyMetis, "Metis_930");
				break;
			case 14650:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105714650));
				orderActorToFactory(1105717650, EnemyMetis, "Metis_931");
				break;
			case 14670:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105714670));
				orderActorToFactory(1105717670, EnemyMetis, "Metis_932");
				break;
			case 14690:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105714690));
				orderActorToFactory(1105717690, EnemyMetis, "Metis_933");
				break;
			case 14710:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105714710));
				orderActorToFactory(1105717710, EnemyMetis, "Metis_934");
				break;
			case 14730:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105714730));
				orderActorToFactory(1105717730, EnemyMetis, "Metis_935");
				break;
			case 14750:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105714750));
				orderActorToFactory(1105717750, EnemyMetis, "Metis_936");
				break;
			case 14770:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105714770));
				orderActorToFactory(1105717770, EnemyMetis, "Metis_937");
				break;
			case 14790:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105714790));
				orderActorToFactory(1105717790, EnemyMetis, "Metis_938");
				break;
			case 14810:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105714810));
				orderActorToFactory(1105717810, EnemyMetis, "Metis_939");
				break;
			case 14830:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105714830));
				orderActorToFactory(1105717830, EnemyMetis, "Metis_940");
				break;
			case 14850:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105714850));
				orderActorToFactory(1105717850, EnemyMetis, "Metis_941");
				break;
			case 14870:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105714870));
				orderActorToFactory(1105717870, EnemyMetis, "Metis_942");
				break;
			case 14890:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105714890));
				orderActorToFactory(1105717890, EnemyMetis, "Metis_943");
				break;
			case 14910:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105714910));
				orderActorToFactory(1105717910, EnemyMetis, "Metis_944");
				break;
			case 14930:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105714930));
				orderActorToFactory(1105717930, EnemyMetis, "Metis_945");
				break;
			case 14950:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105714950));
				orderActorToFactory(1105717950, EnemyMetis, "Metis_946");
				break;
			case 14970:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105714970));
				orderActorToFactory(1105717970, EnemyMetis, "Metis_947");
				break;
			case 14990:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105714990));
				orderActorToFactory(1105717990, EnemyMetis, "Metis_948");
				break;
			case 15000:
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(1125715000);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 15010:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105715010));
				orderActorToFactory(1105718010, EnemyMetis, "Metis_949");
				orderActorToFactory(1124718010, FormationIris001, "F001_Iris_950");
				break;
			case 15030:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105715030));
				orderActorToFactory(1105718030, EnemyMetis, "Metis_951");
				break;
			case 15050:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105715050));
				orderActorToFactory(1105718050, EnemyMetis, "Metis_952");
				break;
			case 15070:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105715070));
				orderActorToFactory(1105718070, EnemyMetis, "Metis_953");
				break;
			case 15090:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105715090));
				orderActorToFactory(1105718090, EnemyMetis, "Metis_954");
				break;
			case 15110:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105715110));
				orderActorToFactory(1105718110, EnemyMetis, "Metis_955");
				break;
			case 15130:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105715130));
				orderActorToFactory(1105718130, EnemyMetis, "Metis_956");
				break;
			case 15150:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105715150));
				orderActorToFactory(1105718150, EnemyMetis, "Metis_957");
				break;
			case 15170:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105715170));
				orderActorToFactory(1105718170, EnemyMetis, "Metis_958");
				break;
			case 15190:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105715190));
				orderActorToFactory(1105718190, EnemyMetis, "Metis_959");
				break;
			case 15210:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105715210));
				orderActorToFactory(1105718210, EnemyMetis, "Metis_960");
				break;
			case 15230:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105715230));
				orderActorToFactory(1105718230, EnemyMetis, "Metis_961");
				break;
			case 15250:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105715250));
				orderActorToFactory(1105718250, EnemyMetis, "Metis_962");
				break;
			case 15270:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105715270));
				orderActorToFactory(1105718270, EnemyMetis, "Metis_963");
				break;
			case 15290:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105715290));
				orderActorToFactory(1105718290, EnemyMetis, "Metis_964");
				break;
			case 15310:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105715310));
				orderActorToFactory(1105718310, EnemyMetis, "Metis_965");
				break;
			case 15330:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105715330));
				orderActorToFactory(1105718330, EnemyMetis, "Metis_966");
				break;
			case 15350:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105715350));
				orderActorToFactory(1105718350, EnemyMetis, "Metis_967");
				break;
			case 15370:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105715370));
				orderActorToFactory(1105718370, EnemyMetis, "Metis_968");
				break;
			case 15390:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105715390));
				orderActorToFactory(1105718390, EnemyMetis, "Metis_969");
				break;
			case 15410:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105715410));
				orderActorToFactory(1105718410, EnemyMetis, "Metis_970");
				break;
			case 15430:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105715430));
				orderActorToFactory(1105718430, EnemyMetis, "Metis_971");
				break;
			case 15450:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105715450));
				orderActorToFactory(1105718450, EnemyMetis, "Metis_972");
				break;
			case 15470:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105715470));
				orderActorToFactory(1105718470, EnemyMetis, "Metis_973");
				break;
			case 15490:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105715490));
				orderActorToFactory(1105718490, EnemyMetis, "Metis_974");
				break;
			case 15510:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105715510));
				orderActorToFactory(1105718510, EnemyMetis, "Metis_975");
				break;
			case 15530:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105715530));
				orderActorToFactory(1105718530, EnemyMetis, "Metis_976");
				break;
			case 15550:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105715550));
				orderActorToFactory(1105718550, EnemyMetis, "Metis_977");
				break;
			case 15570:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105715570));
				orderActorToFactory(1105718570, EnemyMetis, "Metis_978");
				break;
			case 15590:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105715590));
				orderActorToFactory(1105718590, EnemyMetis, "Metis_979");
				break;
			case 15610:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105715610));
				orderActorToFactory(1105718610, EnemyMetis, "Metis_980");
				break;
			case 15630:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105715630));
				orderActorToFactory(1105718630, EnemyMetis, "Metis_981");
				break;
			case 15650:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105715650));
				orderActorToFactory(1105718650, EnemyMetis, "Metis_982");
				break;
			case 15670:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105715670));
				orderActorToFactory(1105718670, EnemyMetis, "Metis_983");
				break;
			case 15690:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105715690));
				orderActorToFactory(1105718690, EnemyMetis, "Metis_984");
				break;
			case 15710:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105715710));
				orderActorToFactory(1105718710, EnemyMetis, "Metis_985");
				break;
			case 15730:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105715730));
				orderActorToFactory(1105718730, EnemyMetis, "Metis_986");
				break;
			case 15750:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105715750));
				orderActorToFactory(1105718750, EnemyMetis, "Metis_987");
				break;
			case 15770:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105715770));
				orderActorToFactory(1105718770, EnemyMetis, "Metis_988");
				break;
			case 15790:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105715790));
				orderActorToFactory(1105718790, EnemyMetis, "Metis_989");
				break;
			case 15810:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105715810));
				orderActorToFactory(1105718810, EnemyMetis, "Metis_990");
				break;
			case 15830:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105715830));
				orderActorToFactory(1105718830, EnemyMetis, "Metis_991");
				break;
			case 15850:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105715850));
				orderActorToFactory(1105718850, EnemyMetis, "Metis_992");
				break;
			case 15870:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105715870));
				orderActorToFactory(1105718870, EnemyMetis, "Metis_993");
				break;
			case 15890:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105715890));
				orderActorToFactory(1105718890, EnemyMetis, "Metis_994");
				break;
			case 15910:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105715910));
				orderActorToFactory(1105718910, EnemyMetis, "Metis_995");
				break;
			case 15930:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105715930));
				orderActorToFactory(1105718930, EnemyMetis, "Metis_996");
				break;
			case 15950:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105715950));
				orderActorToFactory(1105718950, EnemyMetis, "Metis_997");
				break;
			case 15970:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105715970));
				orderActorToFactory(1105718970, EnemyMetis, "Metis_998");
				break;
			case 15990:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105715990));
				orderActorToFactory(1105718990, EnemyMetis, "Metis_999");
				break;
			case 16000:
				orderActorToFactory(1125719000, FormationIris002, "F002_Iris_1000");
				break;
			case 16010:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105716010));
				orderActorToFactory(1105719010, EnemyMetis, "Metis_1001");
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(1124716010);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 16030:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105716030));
				orderActorToFactory(1105719030, EnemyMetis, "Metis_1002");
				break;
			case 16050:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105716050));
				orderActorToFactory(1105719050, EnemyMetis, "Metis_1003");
				break;
			case 16070:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105716070));
				orderActorToFactory(1105719070, EnemyMetis, "Metis_1004");
				break;
			case 16090:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105716090));
				orderActorToFactory(1105719090, EnemyMetis, "Metis_1005");
				break;
			case 16110:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105716110));
				orderActorToFactory(1105719110, EnemyMetis, "Metis_1006");
				break;
			case 16130:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105716130));
				orderActorToFactory(1105719130, EnemyMetis, "Metis_1007");
				break;
			case 16150:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105716150));
				orderActorToFactory(1105719150, EnemyMetis, "Metis_1008");
				break;
			case 16170:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105716170));
				orderActorToFactory(1105719170, EnemyMetis, "Metis_1009");
				break;
			case 16190:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105716190));
				orderActorToFactory(1105719190, EnemyMetis, "Metis_1010");
				break;
			case 16210:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105716210));
				orderActorToFactory(1105719210, EnemyMetis, "Metis_1011");
				break;
			case 16230:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105716230));
				orderActorToFactory(1105719230, EnemyMetis, "Metis_1012");
				break;
			case 16250:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105716250));
				orderActorToFactory(1105719250, EnemyMetis, "Metis_1013");
				break;
			case 16270:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105716270));
				orderActorToFactory(1105719270, EnemyMetis, "Metis_1014");
				break;
			case 16290:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105716290));
				orderActorToFactory(1105719290, EnemyMetis, "Metis_1015");
				break;
			case 16310:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105716310));
				orderActorToFactory(1105719310, EnemyMetis, "Metis_1016");
				break;
			case 16330:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105716330));
				orderActorToFactory(1105719330, EnemyMetis, "Metis_1017");
				break;
			case 16350:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105716350));
				orderActorToFactory(1105719350, EnemyMetis, "Metis_1018");
				break;
			case 16370:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105716370));
				orderActorToFactory(1105719370, EnemyMetis, "Metis_1019");
				break;
			case 16390:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105716390));
				orderActorToFactory(1105719390, EnemyMetis, "Metis_1020");
				break;
			case 16410:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105716410));
				orderActorToFactory(1105719410, EnemyMetis, "Metis_1021");
				break;
			case 16430:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105716430));
				orderActorToFactory(1105719430, EnemyMetis, "Metis_1022");
				break;
			case 16450:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105716450));
				orderActorToFactory(1105719450, EnemyMetis, "Metis_1023");
				break;
			case 16470:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105716470));
				orderActorToFactory(1105719470, EnemyMetis, "Metis_1024");
				break;
			case 16490:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105716490));
				orderActorToFactory(1105719490, EnemyMetis, "Metis_1025");
				break;
			case 16500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1127716500);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 16510:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105716510));
				orderActorToFactory(1105719510, EnemyMetis, "Metis_1026");
				break;
			case 16530:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105716530));
				orderActorToFactory(1105719530, EnemyMetis, "Metis_1027");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1128716530);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 16550:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105716550));
				orderActorToFactory(1105719550, EnemyMetis, "Metis_1028");
				break;
			case 16560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1129716560);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 16570:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105716570));
				orderActorToFactory(1105719570, EnemyMetis, "Metis_1029");
				break;
			case 16590:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105716590));
				orderActorToFactory(1105719590, EnemyMetis, "Metis_1030");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1130716590);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 16610:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105716610));
				orderActorToFactory(1105719610, EnemyMetis, "Metis_1031");
				break;
			case 16620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1131716620);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 16630:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105716630));
				orderActorToFactory(1105719630, EnemyMetis, "Metis_1032");
				break;
			case 16650:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105716650));
				orderActorToFactory(1105719650, EnemyMetis, "Metis_1033");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1132716650);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 16670:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105716670));
				orderActorToFactory(1105719670, EnemyMetis, "Metis_1034");
				break;
			case 16690:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105716690));
				orderActorToFactory(1105719690, EnemyMetis, "Metis_1035");
				break;
			case 16710:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105716710));
				orderActorToFactory(1105719710, EnemyMetis, "Metis_1036");
				break;
			case 16730:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105716730));
				orderActorToFactory(1105719730, EnemyMetis, "Metis_1037");
				break;
			case 16750:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105716750));
				orderActorToFactory(1105719750, EnemyMetis, "Metis_1038");
				break;
			case 16770:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105716770));
				orderActorToFactory(1105719770, EnemyMetis, "Metis_1039");
				break;
			case 16790:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105716790));
				orderActorToFactory(1105719790, EnemyMetis, "Metis_1040");
				break;
			case 16810:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105716810));
				orderActorToFactory(1105719810, EnemyMetis, "Metis_1041");
				break;
			case 16830:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105716830));
				orderActorToFactory(1105719830, EnemyMetis, "Metis_1042");
				break;
			case 16850:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105716850));
				orderActorToFactory(1105719850, EnemyMetis, "Metis_1043");
				break;
			case 16870:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105716870));
				orderActorToFactory(1105719870, EnemyMetis, "Metis_1044");
				break;
			case 16890:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105716890));
				orderActorToFactory(1105719890, EnemyMetis, "Metis_1045");
				break;
			case 16910:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105716910));
				orderActorToFactory(1105719910, EnemyMetis, "Metis_1046");
				break;
			case 16930:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105716930));
				orderActorToFactory(1105719930, EnemyMetis, "Metis_1047");
				break;
			case 16950:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105716950));
				orderActorToFactory(1105719950, EnemyMetis, "Metis_1048");
				break;
			case 16970:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105716970));
				orderActorToFactory(1105719970, EnemyMetis, "Metis_1049");
				break;
			case 16990:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105716990));
				orderActorToFactory(1105719990, EnemyMetis, "Metis_1050");
				break;
			case 17000:
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(1125717000);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 17010:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105717010));
				orderActorToFactory(1105720010, EnemyMetis, "Metis_1051");
				break;
			case 17030:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105717030));
				orderActorToFactory(1105720030, EnemyMetis, "Metis_1052");
				break;
			case 17050:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105717050));
				orderActorToFactory(1105720050, EnemyMetis, "Metis_1053");
				break;
			case 17070:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105717070));
				orderActorToFactory(1105720070, EnemyMetis, "Metis_1054");
				break;
			case 17090:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105717090));
				orderActorToFactory(1105720090, EnemyMetis, "Metis_1055");
				break;
			case 17110:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105717110));
				orderActorToFactory(1105720110, EnemyMetis, "Metis_1056");
				break;
			case 17130:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105717130));
				orderActorToFactory(1105720130, EnemyMetis, "Metis_1057");
				break;
			case 17150:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105717150));
				orderActorToFactory(1105720150, EnemyMetis, "Metis_1058");
				break;
			case 17170:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105717170));
				orderActorToFactory(1105720170, EnemyMetis, "Metis_1059");
				break;
			case 17190:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105717190));
				orderActorToFactory(1105720190, EnemyMetis, "Metis_1060");
				break;
			case 17210:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105717210));
				orderActorToFactory(1105720210, EnemyMetis, "Metis_1061");
				break;
			case 17230:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105717230));
				orderActorToFactory(1105720230, EnemyMetis, "Metis_1062");
				break;
			case 17250:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105717250));
				orderActorToFactory(1105720250, EnemyMetis, "Metis_1063");
				break;
			case 17270:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105717270));
				orderActorToFactory(1105720270, EnemyMetis, "Metis_1064");
				break;
			case 17290:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105717290));
				orderActorToFactory(1105720290, EnemyMetis, "Metis_1065");
				break;
			case 17310:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105717310));
				orderActorToFactory(1105720310, EnemyMetis, "Metis_1066");
				break;
			case 17330:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105717330));
				orderActorToFactory(1105720330, EnemyMetis, "Metis_1067");
				break;
			case 17350:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105717350));
				orderActorToFactory(1105720350, EnemyMetis, "Metis_1068");
				break;
			case 17370:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105717370));
				orderActorToFactory(1105720370, EnemyMetis, "Metis_1069");
				break;
			case 17390:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105717390));
				orderActorToFactory(1105720390, EnemyMetis, "Metis_1070");
				break;
			case 17410:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105717410));
				orderActorToFactory(1105720410, EnemyMetis, "Metis_1071");
				break;
			case 17430:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105717430));
				orderActorToFactory(1105720430, EnemyMetis, "Metis_1072");
				break;
			case 17450:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105717450));
				orderActorToFactory(1105720450, EnemyMetis, "Metis_1073");
				break;
			case 17470:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105717470));
				orderActorToFactory(1105720470, EnemyMetis, "Metis_1074");
				break;
			case 17490:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105717490));
				orderActorToFactory(1105720490, EnemyMetis, "Metis_1075");
				break;
			case 17510:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105717510));
				orderActorToFactory(1105720510, EnemyMetis, "Metis_1076");
				break;
			case 17530:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105717530));
				orderActorToFactory(1105720530, EnemyMetis, "Metis_1077");
				break;
			case 17550:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105717550));
				orderActorToFactory(1105720550, EnemyMetis, "Metis_1078");
				break;
			case 17570:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105717570));
				orderActorToFactory(1105720570, EnemyMetis, "Metis_1079");
				break;
			case 17590:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105717590));
				orderActorToFactory(1105720590, EnemyMetis, "Metis_1080");
				break;
			case 17610:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105717610));
				orderActorToFactory(1105720610, EnemyMetis, "Metis_1081");
				break;
			case 17630:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105717630));
				orderActorToFactory(1105720630, EnemyMetis, "Metis_1082");
				break;
			case 17650:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105717650));
				orderActorToFactory(1105720650, EnemyMetis, "Metis_1083");
				break;
			case 17670:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105717670));
				orderActorToFactory(1105720670, EnemyMetis, "Metis_1084");
				break;
			case 17690:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105717690));
				orderActorToFactory(1105720690, EnemyMetis, "Metis_1085");
				break;
			case 17710:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105717710));
				orderActorToFactory(1105720710, EnemyMetis, "Metis_1086");
				break;
			case 17730:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105717730));
				orderActorToFactory(1105720730, EnemyMetis, "Metis_1087");
				break;
			case 17750:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105717750));
				orderActorToFactory(1105720750, EnemyMetis, "Metis_1088");
				break;
			case 17770:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105717770));
				orderActorToFactory(1105720770, EnemyMetis, "Metis_1089");
				break;
			case 17790:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105717790));
				orderActorToFactory(1105720790, EnemyMetis, "Metis_1090");
				break;
			case 17810:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105717810));
				orderActorToFactory(1105720810, EnemyMetis, "Metis_1091");
				break;
			case 17830:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105717830));
				orderActorToFactory(1105720830, EnemyMetis, "Metis_1092");
				break;
			case 17850:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105717850));
				orderActorToFactory(1105720850, EnemyMetis, "Metis_1093");
				break;
			case 17870:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105717870));
				orderActorToFactory(1105720870, EnemyMetis, "Metis_1094");
				break;
			case 17890:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105717890));
				orderActorToFactory(1105720890, EnemyMetis, "Metis_1095");
				break;
			case 17910:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105717910));
				orderActorToFactory(1105720910, EnemyMetis, "Metis_1096");
				break;
			case 17930:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105717930));
				orderActorToFactory(1105720930, EnemyMetis, "Metis_1097");
				break;
			case 17950:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105717950));
				orderActorToFactory(1105720950, EnemyMetis, "Metis_1098");
				break;
			case 17970:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105717970));
				orderActorToFactory(1105720970, EnemyMetis, "Metis_1099");
				break;
			case 17990:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105717990));
				orderActorToFactory(1105720990, EnemyMetis, "Metis_1100");
				break;
			case 18010:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105718010));
				orderActorToFactory(1105721010, EnemyMetis, "Metis_1101");
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(1124718010);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 18030:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105718030));
				orderActorToFactory(1105721030, EnemyMetis, "Metis_1102");
				break;
			case 18050:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105718050));
				orderActorToFactory(1105721050, EnemyMetis, "Metis_1103");
				break;
			case 18070:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105718070));
				orderActorToFactory(1105721070, EnemyMetis, "Metis_1104");
				break;
			case 18090:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105718090));
				orderActorToFactory(1105721090, EnemyMetis, "Metis_1105");
				break;
			case 18110:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105718110));
				orderActorToFactory(1105721110, EnemyMetis, "Metis_1106");
				break;
			case 18130:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105718130));
				orderActorToFactory(1105721130, EnemyMetis, "Metis_1107");
				break;
			case 18150:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105718150));
				orderActorToFactory(1105721150, EnemyMetis, "Metis_1108");
				break;
			case 18170:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105718170));
				orderActorToFactory(1105721170, EnemyMetis, "Metis_1109");
				break;
			case 18190:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105718190));
				orderActorToFactory(1105721190, EnemyMetis, "Metis_1110");
				break;
			case 18210:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105718210));
				orderActorToFactory(1105721210, EnemyMetis, "Metis_1111");
				break;
			case 18230:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105718230));
				orderActorToFactory(1105721230, EnemyMetis, "Metis_1112");
				break;
			case 18250:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105718250));
				orderActorToFactory(1105721250, EnemyMetis, "Metis_1113");
				break;
			case 18270:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105718270));
				orderActorToFactory(1105721270, EnemyMetis, "Metis_1114");
				break;
			case 18290:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105718290));
				orderActorToFactory(1105721290, EnemyMetis, "Metis_1115");
				break;
			case 18310:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105718310));
				orderActorToFactory(1105721310, EnemyMetis, "Metis_1116");
				break;
			case 18330:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105718330));
				orderActorToFactory(1105721330, EnemyMetis, "Metis_1117");
				break;
			case 18350:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105718350));
				orderActorToFactory(1105721350, EnemyMetis, "Metis_1118");
				break;
			case 18370:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105718370));
				orderActorToFactory(1105721370, EnemyMetis, "Metis_1119");
				break;
			case 18390:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105718390));
				orderActorToFactory(1105721390, EnemyMetis, "Metis_1120");
				break;
			case 18410:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105718410));
				orderActorToFactory(1105721410, EnemyMetis, "Metis_1121");
				break;
			case 18430:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105718430));
				orderActorToFactory(1105721430, EnemyMetis, "Metis_1122");
				break;
			case 18450:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105718450));
				orderActorToFactory(1105721450, EnemyMetis, "Metis_1123");
				break;
			case 18470:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105718470));
				orderActorToFactory(1105721470, EnemyMetis, "Metis_1124");
				break;
			case 18490:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105718490));
				orderActorToFactory(1105721490, EnemyMetis, "Metis_1125");
				break;
			case 18510:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105718510));
				orderActorToFactory(1105721510, EnemyMetis, "Metis_1126");
				break;
			case 18530:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105718530));
				orderActorToFactory(1105721530, EnemyMetis, "Metis_1127");
				break;
			case 18550:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105718550));
				orderActorToFactory(1105721550, EnemyMetis, "Metis_1128");
				break;
			case 18570:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105718570));
				orderActorToFactory(1105721570, EnemyMetis, "Metis_1129");
				break;
			case 18590:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105718590));
				orderActorToFactory(1105721590, EnemyMetis, "Metis_1130");
				break;
			case 18610:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105718610));
				orderActorToFactory(1105721610, EnemyMetis, "Metis_1131");
				break;
			case 18630:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105718630));
				orderActorToFactory(1105721630, EnemyMetis, "Metis_1132");
				break;
			case 18650:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105718650));
				orderActorToFactory(1105721650, EnemyMetis, "Metis_1133");
				break;
			case 18670:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105718670));
				orderActorToFactory(1105721670, EnemyMetis, "Metis_1134");
				break;
			case 18690:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105718690));
				orderActorToFactory(1105721690, EnemyMetis, "Metis_1135");
				break;
			case 18710:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105718710));
				orderActorToFactory(1105721710, EnemyMetis, "Metis_1136");
				break;
			case 18730:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105718730));
				orderActorToFactory(1105721730, EnemyMetis, "Metis_1137");
				break;
			case 18750:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105718750));
				orderActorToFactory(1105721750, EnemyMetis, "Metis_1138");
				break;
			case 18770:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105718770));
				orderActorToFactory(1105721770, EnemyMetis, "Metis_1139");
				break;
			case 18790:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105718790));
				orderActorToFactory(1105721790, EnemyMetis, "Metis_1140");
				break;
			case 18810:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105718810));
				orderActorToFactory(1105721810, EnemyMetis, "Metis_1141");
				break;
			case 18830:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105718830));
				orderActorToFactory(1105721830, EnemyMetis, "Metis_1142");
				break;
			case 18850:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105718850));
				orderActorToFactory(1105721850, EnemyMetis, "Metis_1143");
				break;
			case 18870:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105718870));
				orderActorToFactory(1105721870, EnemyMetis, "Metis_1144");
				break;
			case 18890:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105718890));
				orderActorToFactory(1105721890, EnemyMetis, "Metis_1145");
				break;
			case 18910:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105718910));
				orderActorToFactory(1105721910, EnemyMetis, "Metis_1146");
				break;
			case 18930:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105718930));
				orderActorToFactory(1105721930, EnemyMetis, "Metis_1147");
				break;
			case 18950:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105718950));
				orderActorToFactory(1105721950, EnemyMetis, "Metis_1148");
				break;
			case 18970:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105718970));
				orderActorToFactory(1105721970, EnemyMetis, "Metis_1149");
				break;
			case 18990:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105718990));
				orderActorToFactory(1105721990, EnemyMetis, "Metis_1150");
				break;
			case 19000:
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(1125719000);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 19010:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105719010));
				orderActorToFactory(1105722010, EnemyMetis, "Metis_1151");
				break;
			case 19030:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105719030));
				orderActorToFactory(1105722030, EnemyMetis, "Metis_1152");
				break;
			case 19050:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105719050));
				orderActorToFactory(1105722050, EnemyMetis, "Metis_1153");
				break;
			case 19070:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105719070));
				orderActorToFactory(1105722070, EnemyMetis, "Metis_1154");
				break;
			case 19090:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105719090));
				orderActorToFactory(1105722090, EnemyMetis, "Metis_1155");
				break;
			case 19110:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105719110));
				orderActorToFactory(1105722110, EnemyMetis, "Metis_1156");
				break;
			case 19130:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105719130));
				orderActorToFactory(1105722130, EnemyMetis, "Metis_1157");
				break;
			case 19150:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105719150));
				orderActorToFactory(1105722150, EnemyMetis, "Metis_1158");
				break;
			case 19170:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105719170));
				orderActorToFactory(1105722170, EnemyMetis, "Metis_1159");
				break;
			case 19190:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105719190));
				orderActorToFactory(1105722190, EnemyMetis, "Metis_1160");
				break;
			case 19210:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105719210));
				orderActorToFactory(1105722210, EnemyMetis, "Metis_1161");
				break;
			case 19230:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105719230));
				orderActorToFactory(1105722230, EnemyMetis, "Metis_1162");
				break;
			case 19250:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105719250));
				orderActorToFactory(1105722250, EnemyMetis, "Metis_1163");
				break;
			case 19270:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105719270));
				orderActorToFactory(1105722270, EnemyMetis, "Metis_1164");
				break;
			case 19290:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105719290));
				orderActorToFactory(1105722290, EnemyMetis, "Metis_1165");
				break;
			case 19310:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105719310));
				orderActorToFactory(1105722310, EnemyMetis, "Metis_1166");
				break;
			case 19330:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105719330));
				orderActorToFactory(1105722330, EnemyMetis, "Metis_1167");
				break;
			case 19350:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105719350));
				orderActorToFactory(1105722350, EnemyMetis, "Metis_1168");
				break;
			case 19370:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105719370));
				orderActorToFactory(1105722370, EnemyMetis, "Metis_1169");
				break;
			case 19390:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105719390));
				orderActorToFactory(1105722390, EnemyMetis, "Metis_1170");
				break;
			case 19410:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105719410));
				orderActorToFactory(1105722410, EnemyMetis, "Metis_1171");
				break;
			case 19430:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105719430));
				orderActorToFactory(1105722430, EnemyMetis, "Metis_1172");
				break;
			case 19450:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105719450));
				orderActorToFactory(1105722450, EnemyMetis, "Metis_1173");
				break;
			case 19470:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105719470));
				orderActorToFactory(1105722470, EnemyMetis, "Metis_1174");
				break;
			case 19490:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105719490));
				orderActorToFactory(1105722490, EnemyMetis, "Metis_1175");
				break;
			case 19510:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105719510));
				orderActorToFactory(1105722510, EnemyMetis, "Metis_1176");
				break;
			case 19530:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105719530));
				orderActorToFactory(1105722530, EnemyMetis, "Metis_1177");
				break;
			case 19550:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105719550));
				orderActorToFactory(1105722550, EnemyMetis, "Metis_1178");
				break;
			case 19570:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105719570));
				orderActorToFactory(1105722570, EnemyMetis, "Metis_1179");
				break;
			case 19590:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105719590));
				orderActorToFactory(1105722590, EnemyMetis, "Metis_1180");
				break;
			case 19610:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105719610));
				orderActorToFactory(1105722610, EnemyMetis, "Metis_1181");
				break;
			case 19630:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105719630));
				orderActorToFactory(1105722630, EnemyMetis, "Metis_1182");
				break;
			case 19650:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105719650));
				orderActorToFactory(1105722650, EnemyMetis, "Metis_1183");
				break;
			case 19670:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105719670));
				orderActorToFactory(1105722670, EnemyMetis, "Metis_1184");
				break;
			case 19690:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105719690));
				orderActorToFactory(1105722690, EnemyMetis, "Metis_1185");
				break;
			case 19710:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105719710));
				orderActorToFactory(1105722710, EnemyMetis, "Metis_1186");
				break;
			case 19730:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105719730));
				orderActorToFactory(1105722730, EnemyMetis, "Metis_1187");
				break;
			case 19750:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105719750));
				orderActorToFactory(1105722750, EnemyMetis, "Metis_1188");
				break;
			case 19770:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105719770));
				orderActorToFactory(1105722770, EnemyMetis, "Metis_1189");
				break;
			case 19790:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105719790));
				orderActorToFactory(1105722790, EnemyMetis, "Metis_1190");
				break;
			case 19810:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105719810));
				orderActorToFactory(1105722810, EnemyMetis, "Metis_1191");
				break;
			case 19830:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105719830));
				orderActorToFactory(1105722830, EnemyMetis, "Metis_1192");
				break;
			case 19850:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105719850));
				orderActorToFactory(1105722850, EnemyMetis, "Metis_1193");
				break;
			case 19870:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105719870));
				orderActorToFactory(1105722870, EnemyMetis, "Metis_1194");
				break;
			case 19890:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105719890));
				orderActorToFactory(1105722890, EnemyMetis, "Metis_1195");
				break;
			case 19910:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105719910));
				orderActorToFactory(1105722910, EnemyMetis, "Metis_1196");
				break;
			case 19930:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105719930));
				orderActorToFactory(1105722930, EnemyMetis, "Metis_1197");
				break;
			case 19950:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105719950));
				orderActorToFactory(1105722950, EnemyMetis, "Metis_1198");
				break;
			case 19970:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105719970));
				orderActorToFactory(1105722970, EnemyMetis, "Metis_1199");
				break;
			case 19990:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105719990));
				orderActorToFactory(1105722990, EnemyMetis, "Metis_1200");
				break;
			case 20010:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105720010));
				orderActorToFactory(1105723010, EnemyMetis, "Metis_1201");
				break;
			case 20030:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105720030));
				orderActorToFactory(1105723030, EnemyMetis, "Metis_1202");
				break;
			case 20050:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105720050));
				orderActorToFactory(1105723050, EnemyMetis, "Metis_1203");
				break;
			case 20070:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105720070));
				orderActorToFactory(1105723070, EnemyMetis, "Metis_1204");
				break;
			case 20090:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105720090));
				orderActorToFactory(1105723090, EnemyMetis, "Metis_1205");
				break;
			case 20110:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105720110));
				orderActorToFactory(1105723110, EnemyMetis, "Metis_1206");
				break;
			case 20130:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105720130));
				orderActorToFactory(1105723130, EnemyMetis, "Metis_1207");
				break;
			case 20150:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105720150));
				orderActorToFactory(1105723150, EnemyMetis, "Metis_1208");
				break;
			case 20170:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105720170));
				orderActorToFactory(1105723170, EnemyMetis, "Metis_1209");
				break;
			case 20190:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105720190));
				orderActorToFactory(1105723190, EnemyMetis, "Metis_1210");
				break;
			case 20210:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105720210));
				orderActorToFactory(1105723210, EnemyMetis, "Metis_1211");
				break;
			case 20230:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105720230));
				orderActorToFactory(1105723230, EnemyMetis, "Metis_1212");
				break;
			case 20250:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105720250));
				orderActorToFactory(1105723250, EnemyMetis, "Metis_1213");
				break;
			case 20270:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105720270));
				orderActorToFactory(1105723270, EnemyMetis, "Metis_1214");
				break;
			case 20290:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105720290));
				orderActorToFactory(1105723290, EnemyMetis, "Metis_1215");
				break;
			case 20310:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105720310));
				orderActorToFactory(1105723310, EnemyMetis, "Metis_1216");
				break;
			case 20330:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105720330));
				orderActorToFactory(1105723330, EnemyMetis, "Metis_1217");
				break;
			case 20350:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105720350));
				orderActorToFactory(1105723350, EnemyMetis, "Metis_1218");
				break;
			case 20370:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105720370));
				orderActorToFactory(1105723370, EnemyMetis, "Metis_1219");
				break;
			case 20390:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105720390));
				orderActorToFactory(1105723390, EnemyMetis, "Metis_1220");
				break;
			case 20410:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105720410));
				orderActorToFactory(1105723410, EnemyMetis, "Metis_1221");
				break;
			case 20430:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105720430));
				orderActorToFactory(1105723430, EnemyMetis, "Metis_1222");
				break;
			case 20450:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105720450));
				orderActorToFactory(1105723450, EnemyMetis, "Metis_1223");
				break;
			case 20470:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105720470));
				orderActorToFactory(1105723470, EnemyMetis, "Metis_1224");
				break;
			case 20490:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105720490));
				orderActorToFactory(1105723490, EnemyMetis, "Metis_1225");
				break;
			case 20510:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105720510));
				orderActorToFactory(1105723510, EnemyMetis, "Metis_1226");
				break;
			case 20530:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105720530));
				orderActorToFactory(1105723530, EnemyMetis, "Metis_1227");
				break;
			case 20550:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105720550));
				orderActorToFactory(1105723550, EnemyMetis, "Metis_1228");
				break;
			case 20570:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105720570));
				orderActorToFactory(1105723570, EnemyMetis, "Metis_1229");
				break;
			case 20590:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105720590));
				orderActorToFactory(1105723590, EnemyMetis, "Metis_1230");
				break;
			case 20610:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105720610));
				orderActorToFactory(1105723610, EnemyMetis, "Metis_1231");
				break;
			case 20630:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105720630));
				orderActorToFactory(1105723630, EnemyMetis, "Metis_1232");
				break;
			case 20650:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105720650));
				orderActorToFactory(1105723650, EnemyMetis, "Metis_1233");
				break;
			case 20670:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105720670));
				orderActorToFactory(1105723670, EnemyMetis, "Metis_1234");
				break;
			case 20690:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105720690));
				orderActorToFactory(1105723690, EnemyMetis, "Metis_1235");
				break;
			case 20710:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105720710));
				orderActorToFactory(1105723710, EnemyMetis, "Metis_1236");
				break;
			case 20730:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105720730));
				orderActorToFactory(1105723730, EnemyMetis, "Metis_1237");
				break;
			case 20750:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105720750));
				orderActorToFactory(1105723750, EnemyMetis, "Metis_1238");
				break;
			case 20770:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105720770));
				orderActorToFactory(1105723770, EnemyMetis, "Metis_1239");
				break;
			case 20790:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105720790));
				orderActorToFactory(1105723790, EnemyMetis, "Metis_1240");
				break;
			case 20810:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105720810));
				orderActorToFactory(1105723810, EnemyMetis, "Metis_1241");
				break;
			case 20830:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105720830));
				orderActorToFactory(1105723830, EnemyMetis, "Metis_1242");
				break;
			case 20850:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105720850));
				orderActorToFactory(1105723850, EnemyMetis, "Metis_1243");
				break;
			case 20870:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105720870));
				orderActorToFactory(1105723870, EnemyMetis, "Metis_1244");
				break;
			case 20890:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105720890));
				orderActorToFactory(1105723890, EnemyMetis, "Metis_1245");
				break;
			case 20910:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105720910));
				orderActorToFactory(1105723910, EnemyMetis, "Metis_1246");
				break;
			case 20930:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105720930));
				orderActorToFactory(1105723930, EnemyMetis, "Metis_1247");
				break;
			case 20950:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105720950));
				orderActorToFactory(1105723950, EnemyMetis, "Metis_1248");
				break;
			case 20970:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105720970));
				orderActorToFactory(1105723970, EnemyMetis, "Metis_1249");
				break;
			case 20990:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105720990));
				orderActorToFactory(1105723990, EnemyMetis, "Metis_1250");
				break;
			case 21010:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105721010));
				orderActorToFactory(1105724010, EnemyMetis, "Metis_1251");
				break;
			case 21030:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105721030));
				orderActorToFactory(1105724030, EnemyMetis, "Metis_1252");
				break;
			case 21050:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105721050));
				orderActorToFactory(1105724050, EnemyMetis, "Metis_1253");
				break;
			case 21070:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105721070));
				orderActorToFactory(1105724070, EnemyMetis, "Metis_1254");
				break;
			case 21090:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105721090));
				orderActorToFactory(1105724090, EnemyMetis, "Metis_1255");
				break;
			case 21110:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105721110));
				orderActorToFactory(1105724110, EnemyMetis, "Metis_1256");
				break;
			case 21130:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105721130));
				orderActorToFactory(1105724130, EnemyMetis, "Metis_1257");
				break;
			case 21150:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105721150));
				orderActorToFactory(1105724150, EnemyMetis, "Metis_1258");
				break;
			case 21170:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105721170));
				orderActorToFactory(1105724170, EnemyMetis, "Metis_1259");
				break;
			case 21190:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105721190));
				orderActorToFactory(1105724190, EnemyMetis, "Metis_1260");
				break;
			case 21210:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105721210));
				orderActorToFactory(1105724210, EnemyMetis, "Metis_1261");
				break;
			case 21230:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105721230));
				orderActorToFactory(1105724230, EnemyMetis, "Metis_1262");
				break;
			case 21250:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105721250));
				orderActorToFactory(1105724250, EnemyMetis, "Metis_1263");
				break;
			case 21270:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105721270));
				orderActorToFactory(1105724270, EnemyMetis, "Metis_1264");
				break;
			case 21290:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105721290));
				orderActorToFactory(1105724290, EnemyMetis, "Metis_1265");
				break;
			case 21310:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105721310));
				orderActorToFactory(1105724310, EnemyMetis, "Metis_1266");
				break;
			case 21330:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105721330));
				orderActorToFactory(1105724330, EnemyMetis, "Metis_1267");
				break;
			case 21350:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105721350));
				orderActorToFactory(1105724350, EnemyMetis, "Metis_1268");
				break;
			case 21370:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105721370));
				orderActorToFactory(1105724370, EnemyMetis, "Metis_1269");
				break;
			case 21390:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105721390));
				orderActorToFactory(1105724390, EnemyMetis, "Metis_1270");
				break;
			case 21410:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105721410));
				orderActorToFactory(1105724410, EnemyMetis, "Metis_1271");
				break;
			case 21430:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105721430));
				orderActorToFactory(1105724430, EnemyMetis, "Metis_1272");
				break;
			case 21450:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105721450));
				orderActorToFactory(1105724450, EnemyMetis, "Metis_1273");
				break;
			case 21470:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105721470));
				orderActorToFactory(1105724470, EnemyMetis, "Metis_1274");
				break;
			case 21490:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105721490));
				orderActorToFactory(1105724490, EnemyMetis, "Metis_1275");
				break;
			case 21510:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105721510));
				orderActorToFactory(1105724510, EnemyMetis, "Metis_1276");
				break;
			case 21530:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105721530));
				orderActorToFactory(1105724530, EnemyMetis, "Metis_1277");
				break;
			case 21550:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105721550));
				orderActorToFactory(1105724550, EnemyMetis, "Metis_1278");
				break;
			case 21570:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105721570));
				orderActorToFactory(1105724570, EnemyMetis, "Metis_1279");
				break;
			case 21590:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105721590));
				orderActorToFactory(1105724590, EnemyMetis, "Metis_1280");
				break;
			case 21610:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105721610));
				orderActorToFactory(1105724610, EnemyMetis, "Metis_1281");
				break;
			case 21630:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105721630));
				orderActorToFactory(1105724630, EnemyMetis, "Metis_1282");
				break;
			case 21650:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105721650));
				orderActorToFactory(1105724650, EnemyMetis, "Metis_1283");
				break;
			case 21670:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105721670));
				orderActorToFactory(1105724670, EnemyMetis, "Metis_1284");
				break;
			case 21690:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105721690));
				orderActorToFactory(1105724690, EnemyMetis, "Metis_1285");
				break;
			case 21710:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105721710));
				orderActorToFactory(1105724710, EnemyMetis, "Metis_1286");
				break;
			case 21730:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105721730));
				orderActorToFactory(1105724730, EnemyMetis, "Metis_1287");
				break;
			case 21750:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105721750));
				orderActorToFactory(1105724750, EnemyMetis, "Metis_1288");
				break;
			case 21770:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105721770));
				orderActorToFactory(1105724770, EnemyMetis, "Metis_1289");
				break;
			case 21790:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105721790));
				orderActorToFactory(1105724790, EnemyMetis, "Metis_1290");
				break;
			case 21810:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105721810));
				orderActorToFactory(1105724810, EnemyMetis, "Metis_1291");
				break;
			case 21830:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105721830));
				orderActorToFactory(1105724830, EnemyMetis, "Metis_1292");
				break;
			case 21850:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105721850));
				orderActorToFactory(1105724850, EnemyMetis, "Metis_1293");
				break;
			case 21870:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105721870));
				orderActorToFactory(1105724870, EnemyMetis, "Metis_1294");
				break;
			case 21890:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105721890));
				orderActorToFactory(1105724890, EnemyMetis, "Metis_1295");
				break;
			case 21910:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105721910));
				orderActorToFactory(1105724910, EnemyMetis, "Metis_1296");
				break;
			case 21930:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105721930));
				orderActorToFactory(1105724930, EnemyMetis, "Metis_1297");
				break;
			case 21950:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105721950));
				orderActorToFactory(1105724950, EnemyMetis, "Metis_1298");
				break;
			case 21970:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105721970));
				orderActorToFactory(1105724970, EnemyMetis, "Metis_1299");
				break;
			case 21990:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105721990));
				orderActorToFactory(1105724990, EnemyMetis, "Metis_1300");
				break;
			case 22010:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105722010));
				orderActorToFactory(1105725010, EnemyMetis, "Metis_1301");
				break;
			case 22030:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105722030));
				orderActorToFactory(1105725030, EnemyMetis, "Metis_1302");
				break;
			case 22050:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105722050));
				orderActorToFactory(1105725050, EnemyMetis, "Metis_1303");
				break;
			case 22070:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105722070));
				orderActorToFactory(1105725070, EnemyMetis, "Metis_1304");
				break;
			case 22090:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105722090));
				orderActorToFactory(1105725090, EnemyMetis, "Metis_1305");
				break;
			case 22110:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105722110));
				orderActorToFactory(1105725110, EnemyMetis, "Metis_1306");
				break;
			case 22130:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105722130));
				orderActorToFactory(1105725130, EnemyMetis, "Metis_1307");
				break;
			case 22150:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105722150));
				orderActorToFactory(1105725150, EnemyMetis, "Metis_1308");
				break;
			case 22170:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105722170));
				orderActorToFactory(1105725170, EnemyMetis, "Metis_1309");
				break;
			case 22190:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105722190));
				orderActorToFactory(1105725190, EnemyMetis, "Metis_1310");
				break;
			case 22210:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105722210));
				orderActorToFactory(1105725210, EnemyMetis, "Metis_1311");
				break;
			case 22230:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105722230));
				orderActorToFactory(1105725230, EnemyMetis, "Metis_1312");
				break;
			case 22250:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105722250));
				orderActorToFactory(1105725250, EnemyMetis, "Metis_1313");
				break;
			case 22270:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105722270));
				orderActorToFactory(1105725270, EnemyMetis, "Metis_1314");
				break;
			case 22290:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105722290));
				orderActorToFactory(1105725290, EnemyMetis, "Metis_1315");
				break;
			case 22310:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105722310));
				orderActorToFactory(1105725310, EnemyMetis, "Metis_1316");
				break;
			case 22330:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105722330));
				orderActorToFactory(1105725330, EnemyMetis, "Metis_1317");
				break;
			case 22350:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105722350));
				orderActorToFactory(1105725350, EnemyMetis, "Metis_1318");
				break;
			case 22370:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105722370));
				orderActorToFactory(1105725370, EnemyMetis, "Metis_1319");
				break;
			case 22390:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105722390));
				orderActorToFactory(1105725390, EnemyMetis, "Metis_1320");
				break;
			case 22410:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105722410));
				orderActorToFactory(1105725410, EnemyMetis, "Metis_1321");
				break;
			case 22430:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105722430));
				orderActorToFactory(1105725430, EnemyMetis, "Metis_1322");
				break;
			case 22450:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105722450));
				orderActorToFactory(1105725450, EnemyMetis, "Metis_1323");
				break;
			case 22470:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105722470));
				orderActorToFactory(1105725470, EnemyMetis, "Metis_1324");
				break;
			case 22490:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105722490));
				orderActorToFactory(1105725490, EnemyMetis, "Metis_1325");
				break;
			case 22510:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105722510));
				orderActorToFactory(1105725510, EnemyMetis, "Metis_1326");
				break;
			case 22530:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105722530));
				orderActorToFactory(1105725530, EnemyMetis, "Metis_1327");
				break;
			case 22550:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105722550));
				orderActorToFactory(1105725550, EnemyMetis, "Metis_1328");
				break;
			case 22570:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105722570));
				orderActorToFactory(1105725570, EnemyMetis, "Metis_1329");
				break;
			case 22590:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105722590));
				orderActorToFactory(1105725590, EnemyMetis, "Metis_1330");
				break;
			case 22610:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105722610));
				orderActorToFactory(1105725610, EnemyMetis, "Metis_1331");
				break;
			case 22630:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105722630));
				orderActorToFactory(1105725630, EnemyMetis, "Metis_1332");
				break;
			case 22650:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105722650));
				orderActorToFactory(1105725650, EnemyMetis, "Metis_1333");
				break;
			case 22670:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105722670));
				orderActorToFactory(1105725670, EnemyMetis, "Metis_1334");
				break;
			case 22690:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105722690));
				orderActorToFactory(1105725690, EnemyMetis, "Metis_1335");
				break;
			case 22710:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105722710));
				orderActorToFactory(1105725710, EnemyMetis, "Metis_1336");
				break;
			case 22730:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105722730));
				orderActorToFactory(1105725730, EnemyMetis, "Metis_1337");
				break;
			case 22750:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105722750));
				orderActorToFactory(1105725750, EnemyMetis, "Metis_1338");
				break;
			case 22770:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105722770));
				orderActorToFactory(1105725770, EnemyMetis, "Metis_1339");
				break;
			case 22790:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105722790));
				orderActorToFactory(1105725790, EnemyMetis, "Metis_1340");
				break;
			case 22810:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105722810));
				orderActorToFactory(1105725810, EnemyMetis, "Metis_1341");
				break;
			case 22830:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105722830));
				orderActorToFactory(1105725830, EnemyMetis, "Metis_1342");
				break;
			case 22850:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105722850));
				orderActorToFactory(1105725850, EnemyMetis, "Metis_1343");
				break;
			case 22870:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105722870));
				orderActorToFactory(1105725870, EnemyMetis, "Metis_1344");
				break;
			case 22890:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105722890));
				orderActorToFactory(1105725890, EnemyMetis, "Metis_1345");
				break;
			case 22910:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105722910));
				orderActorToFactory(1105725910, EnemyMetis, "Metis_1346");
				break;
			case 22930:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105722930));
				orderActorToFactory(1105725930, EnemyMetis, "Metis_1347");
				break;
			case 22950:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105722950));
				orderActorToFactory(1105725950, EnemyMetis, "Metis_1348");
				break;
			case 22970:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105722970));
				orderActorToFactory(1105725970, EnemyMetis, "Metis_1349");
				break;
			case 22990:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105722990));
				orderActorToFactory(1105725990, EnemyMetis, "Metis_1350");
				break;
			case 23010:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105723010));
				orderActorToFactory(1105726010, EnemyMetis, "Metis_1351");
				break;
			case 23030:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105723030));
				orderActorToFactory(1105726030, EnemyMetis, "Metis_1352");
				break;
			case 23050:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105723050));
				orderActorToFactory(1105726050, EnemyMetis, "Metis_1353");
				break;
			case 23070:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105723070));
				orderActorToFactory(1105726070, EnemyMetis, "Metis_1354");
				break;
			case 23090:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105723090));
				orderActorToFactory(1105726090, EnemyMetis, "Metis_1355");
				break;
			case 23110:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105723110));
				orderActorToFactory(1105726110, EnemyMetis, "Metis_1356");
				break;
			case 23130:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105723130));
				orderActorToFactory(1105726130, EnemyMetis, "Metis_1357");
				break;
			case 23150:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105723150));
				orderActorToFactory(1105726150, EnemyMetis, "Metis_1358");
				break;
			case 23170:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105723170));
				orderActorToFactory(1105726170, EnemyMetis, "Metis_1359");
				break;
			case 23190:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105723190));
				orderActorToFactory(1105726190, EnemyMetis, "Metis_1360");
				break;
			case 23210:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105723210));
				orderActorToFactory(1105726210, EnemyMetis, "Metis_1361");
				break;
			case 23230:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105723230));
				orderActorToFactory(1105726230, EnemyMetis, "Metis_1362");
				break;
			case 23250:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105723250));
				orderActorToFactory(1105726250, EnemyMetis, "Metis_1363");
				break;
			case 23270:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105723270));
				orderActorToFactory(1105726270, EnemyMetis, "Metis_1364");
				break;
			case 23290:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105723290));
				orderActorToFactory(1105726290, EnemyMetis, "Metis_1365");
				break;
			case 23310:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105723310));
				orderActorToFactory(1105726310, EnemyMetis, "Metis_1366");
				break;
			case 23330:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105723330));
				orderActorToFactory(1105726330, EnemyMetis, "Metis_1367");
				break;
			case 23350:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105723350));
				orderActorToFactory(1105726350, EnemyMetis, "Metis_1368");
				break;
			case 23370:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105723370));
				orderActorToFactory(1105726370, EnemyMetis, "Metis_1369");
				break;
			case 23390:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105723390));
				orderActorToFactory(1105726390, EnemyMetis, "Metis_1370");
				break;
			case 23410:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105723410));
				orderActorToFactory(1105726410, EnemyMetis, "Metis_1371");
				break;
			case 23430:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105723430));
				orderActorToFactory(1105726430, EnemyMetis, "Metis_1372");
				break;
			case 23450:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105723450));
				orderActorToFactory(1105726450, EnemyMetis, "Metis_1373");
				break;
			case 23470:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105723470));
				orderActorToFactory(1105726470, EnemyMetis, "Metis_1374");
				break;
			case 23490:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105723490));
				orderActorToFactory(1105726490, EnemyMetis, "Metis_1375");
				break;
			case 23510:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105723510));
				orderActorToFactory(1105726510, EnemyMetis, "Metis_1376");
				break;
			case 23530:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105723530));
				orderActorToFactory(1105726530, EnemyMetis, "Metis_1377");
				break;
			case 23550:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105723550));
				orderActorToFactory(1105726550, EnemyMetis, "Metis_1378");
				break;
			case 23570:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105723570));
				orderActorToFactory(1105726570, EnemyMetis, "Metis_1379");
				break;
			case 23590:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105723590));
				orderActorToFactory(1105726590, EnemyMetis, "Metis_1380");
				break;
			case 23610:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105723610));
				orderActorToFactory(1105726610, EnemyMetis, "Metis_1381");
				break;
			case 23630:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105723630));
				orderActorToFactory(1105726630, EnemyMetis, "Metis_1382");
				break;
			case 23650:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105723650));
				orderActorToFactory(1105726650, EnemyMetis, "Metis_1383");
				break;
			case 23670:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105723670));
				orderActorToFactory(1105726670, EnemyMetis, "Metis_1384");
				break;
			case 23690:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105723690));
				orderActorToFactory(1105726690, EnemyMetis, "Metis_1385");
				break;
			case 23710:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105723710));
				orderActorToFactory(1105726710, EnemyMetis, "Metis_1386");
				break;
			case 23730:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105723730));
				orderActorToFactory(1105726730, EnemyMetis, "Metis_1387");
				break;
			case 23750:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105723750));
				orderActorToFactory(1105726750, EnemyMetis, "Metis_1388");
				break;
			case 23770:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105723770));
				orderActorToFactory(1105726770, EnemyMetis, "Metis_1389");
				break;
			case 23790:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105723790));
				orderActorToFactory(1105726790, EnemyMetis, "Metis_1390");
				break;
			case 23810:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105723810));
				orderActorToFactory(1105726810, EnemyMetis, "Metis_1391");
				break;
			case 23830:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105723830));
				orderActorToFactory(1105726830, EnemyMetis, "Metis_1392");
				break;
			case 23850:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105723850));
				orderActorToFactory(1105726850, EnemyMetis, "Metis_1393");
				break;
			case 23870:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105723870));
				orderActorToFactory(1105726870, EnemyMetis, "Metis_1394");
				break;
			case 23890:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105723890));
				orderActorToFactory(1105726890, EnemyMetis, "Metis_1395");
				break;
			case 23910:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105723910));
				orderActorToFactory(1105726910, EnemyMetis, "Metis_1396");
				break;
			case 23930:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105723930));
				orderActorToFactory(1105726930, EnemyMetis, "Metis_1397");
				break;
			case 23950:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105723950));
				orderActorToFactory(1105726950, EnemyMetis, "Metis_1398");
				break;
			case 23970:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105723970));
				orderActorToFactory(1105726970, EnemyMetis, "Metis_1399");
				break;
			case 23990:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105723990));
				orderActorToFactory(1105726990, EnemyMetis, "Metis_1400");
				break;
			case 24010:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105724010));
				orderActorToFactory(1105727010, EnemyMetis, "Metis_1401");
				break;
			case 24030:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105724030));
				orderActorToFactory(1105727030, EnemyMetis, "Metis_1402");
				break;
			case 24050:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105724050));
				orderActorToFactory(1105727050, EnemyMetis, "Metis_1403");
				break;
			case 24070:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105724070));
				orderActorToFactory(1105727070, EnemyMetis, "Metis_1404");
				break;
			case 24090:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105724090));
				orderActorToFactory(1105727090, EnemyMetis, "Metis_1405");
				break;
			case 24110:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105724110));
				orderActorToFactory(1105727110, EnemyMetis, "Metis_1406");
				break;
			case 24130:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105724130));
				orderActorToFactory(1105727130, EnemyMetis, "Metis_1407");
				break;
			case 24150:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105724150));
				orderActorToFactory(1105727150, EnemyMetis, "Metis_1408");
				break;
			case 24170:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105724170));
				orderActorToFactory(1105727170, EnemyMetis, "Metis_1409");
				break;
			case 24190:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105724190));
				orderActorToFactory(1105727190, EnemyMetis, "Metis_1410");
				break;
			case 24210:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105724210));
				orderActorToFactory(1105727210, EnemyMetis, "Metis_1411");
				break;
			case 24230:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105724230));
				orderActorToFactory(1105727230, EnemyMetis, "Metis_1412");
				break;
			case 24250:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105724250));
				orderActorToFactory(1105727250, EnemyMetis, "Metis_1413");
				break;
			case 24270:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105724270));
				orderActorToFactory(1105727270, EnemyMetis, "Metis_1414");
				break;
			case 24290:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105724290));
				orderActorToFactory(1105727290, EnemyMetis, "Metis_1415");
				break;
			case 24310:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105724310));
				orderActorToFactory(1105727310, EnemyMetis, "Metis_1416");
				break;
			case 24330:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105724330));
				orderActorToFactory(1105727330, EnemyMetis, "Metis_1417");
				break;
			case 24350:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105724350));
				orderActorToFactory(1105727350, EnemyMetis, "Metis_1418");
				break;
			case 24370:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105724370));
				orderActorToFactory(1105727370, EnemyMetis, "Metis_1419");
				break;
			case 24390:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105724390));
				orderActorToFactory(1105727390, EnemyMetis, "Metis_1420");
				break;
			case 24410:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105724410));
				orderActorToFactory(1105727410, EnemyMetis, "Metis_1421");
				break;
			case 24430:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105724430));
				orderActorToFactory(1105727430, EnemyMetis, "Metis_1422");
				break;
			case 24450:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105724450));
				orderActorToFactory(1105727450, EnemyMetis, "Metis_1423");
				break;
			case 24470:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105724470));
				orderActorToFactory(1105727470, EnemyMetis, "Metis_1424");
				break;
			case 24490:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105724490));
				orderActorToFactory(1105727490, EnemyMetis, "Metis_1425");
				break;
			case 24510:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105724510));
				orderActorToFactory(1105727510, EnemyMetis, "Metis_1426");
				break;
			case 24530:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105724530));
				orderActorToFactory(1105727530, EnemyMetis, "Metis_1427");
				break;
			case 24550:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105724550));
				orderActorToFactory(1105727550, EnemyMetis, "Metis_1428");
				break;
			case 24570:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105724570));
				orderActorToFactory(1105727570, EnemyMetis, "Metis_1429");
				break;
			case 24590:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105724590));
				orderActorToFactory(1105727590, EnemyMetis, "Metis_1430");
				break;
			case 24610:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105724610));
				orderActorToFactory(1105727610, EnemyMetis, "Metis_1431");
				break;
			case 24630:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105724630));
				orderActorToFactory(1105727630, EnemyMetis, "Metis_1432");
				break;
			case 24650:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105724650));
				orderActorToFactory(1105727650, EnemyMetis, "Metis_1433");
				break;
			case 24670:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105724670));
				orderActorToFactory(1105727670, EnemyMetis, "Metis_1434");
				break;
			case 24690:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105724690));
				orderActorToFactory(1105727690, EnemyMetis, "Metis_1435");
				break;
			case 24710:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105724710));
				orderActorToFactory(1105727710, EnemyMetis, "Metis_1436");
				break;
			case 24730:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105724730));
				orderActorToFactory(1105727730, EnemyMetis, "Metis_1437");
				break;
			case 24750:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105724750));
				orderActorToFactory(1105727750, EnemyMetis, "Metis_1438");
				break;
			case 24770:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105724770));
				orderActorToFactory(1105727770, EnemyMetis, "Metis_1439");
				break;
			case 24790:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105724790));
				orderActorToFactory(1105727790, EnemyMetis, "Metis_1440");
				break;
			case 24810:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105724810));
				orderActorToFactory(1105727810, EnemyMetis, "Metis_1441");
				break;
			case 24830:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105724830));
				orderActorToFactory(1105727830, EnemyMetis, "Metis_1442");
				break;
			case 24850:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105724850));
				orderActorToFactory(1105727850, EnemyMetis, "Metis_1443");
				break;
			case 24870:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105724870));
				orderActorToFactory(1105727870, EnemyMetis, "Metis_1444");
				break;
			case 24890:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105724890));
				orderActorToFactory(1105727890, EnemyMetis, "Metis_1445");
				break;
			case 24910:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105724910));
				orderActorToFactory(1105727910, EnemyMetis, "Metis_1446");
				break;
			case 24930:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105724930));
				orderActorToFactory(1105727930, EnemyMetis, "Metis_1447");
				break;
			case 24950:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105724950));
				orderActorToFactory(1105727950, EnemyMetis, "Metis_1448");
				break;
			case 24970:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105724970));
				orderActorToFactory(1105727970, EnemyMetis, "Metis_1449");
				break;
			case 24990:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105724990));
				orderActorToFactory(1105727990, EnemyMetis, "Metis_1450");
				break;
			case 25010:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105725010));
				orderActorToFactory(1105728010, EnemyMetis, "Metis_1451");
				break;
			case 25030:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105725030));
				orderActorToFactory(1105728030, EnemyMetis, "Metis_1452");
				break;
			case 25050:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105725050));
				orderActorToFactory(1105728050, EnemyMetis, "Metis_1453");
				break;
			case 25070:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105725070));
				orderActorToFactory(1105728070, EnemyMetis, "Metis_1454");
				break;
			case 25090:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105725090));
				orderActorToFactory(1105728090, EnemyMetis, "Metis_1455");
				break;
			case 25110:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105725110));
				orderActorToFactory(1105728110, EnemyMetis, "Metis_1456");
				break;
			case 25130:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105725130));
				orderActorToFactory(1105728130, EnemyMetis, "Metis_1457");
				break;
			case 25150:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105725150));
				orderActorToFactory(1105728150, EnemyMetis, "Metis_1458");
				break;
			case 25170:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105725170));
				orderActorToFactory(1105728170, EnemyMetis, "Metis_1459");
				break;
			case 25190:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105725190));
				orderActorToFactory(1105728190, EnemyMetis, "Metis_1460");
				break;
			case 25210:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105725210));
				orderActorToFactory(1105728210, EnemyMetis, "Metis_1461");
				break;
			case 25230:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105725230));
				orderActorToFactory(1105728230, EnemyMetis, "Metis_1462");
				break;
			case 25250:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105725250));
				orderActorToFactory(1105728250, EnemyMetis, "Metis_1463");
				break;
			case 25270:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105725270));
				orderActorToFactory(1105728270, EnemyMetis, "Metis_1464");
				break;
			case 25290:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105725290));
				orderActorToFactory(1105728290, EnemyMetis, "Metis_1465");
				break;
			case 25310:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105725310));
				orderActorToFactory(1105728310, EnemyMetis, "Metis_1466");
				break;
			case 25330:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105725330));
				orderActorToFactory(1105728330, EnemyMetis, "Metis_1467");
				break;
			case 25350:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105725350));
				orderActorToFactory(1105728350, EnemyMetis, "Metis_1468");
				break;
			case 25370:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105725370));
				orderActorToFactory(1105728370, EnemyMetis, "Metis_1469");
				break;
			case 25390:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105725390));
				orderActorToFactory(1105728390, EnemyMetis, "Metis_1470");
				break;
			case 25410:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105725410));
				orderActorToFactory(1105728410, EnemyMetis, "Metis_1471");
				break;
			case 25430:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105725430));
				orderActorToFactory(1105728430, EnemyMetis, "Metis_1472");
				break;
			case 25450:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105725450));
				orderActorToFactory(1105728450, EnemyMetis, "Metis_1473");
				break;
			case 25470:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105725470));
				orderActorToFactory(1105728470, EnemyMetis, "Metis_1474");
				break;
			case 25490:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105725490));
				orderActorToFactory(1105728490, EnemyMetis, "Metis_1475");
				break;
			case 25510:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105725510));
				orderActorToFactory(1105728510, EnemyMetis, "Metis_1476");
				break;
			case 25530:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105725530));
				orderActorToFactory(1105728530, EnemyMetis, "Metis_1477");
				break;
			case 25550:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105725550));
				orderActorToFactory(1105728550, EnemyMetis, "Metis_1478");
				break;
			case 25570:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105725570));
				orderActorToFactory(1105728570, EnemyMetis, "Metis_1479");
				break;
			case 25590:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105725590));
				orderActorToFactory(1105728590, EnemyMetis, "Metis_1480");
				break;
			case 25610:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105725610));
				orderActorToFactory(1105728610, EnemyMetis, "Metis_1481");
				break;
			case 25630:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105725630));
				orderActorToFactory(1105728630, EnemyMetis, "Metis_1482");
				break;
			case 25650:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105725650));
				orderActorToFactory(1105728650, EnemyMetis, "Metis_1483");
				break;
			case 25670:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105725670));
				orderActorToFactory(1105728670, EnemyMetis, "Metis_1484");
				break;
			case 25690:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105725690));
				orderActorToFactory(1105728690, EnemyMetis, "Metis_1485");
				break;
			case 25710:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105725710));
				orderActorToFactory(1105728710, EnemyMetis, "Metis_1486");
				break;
			case 25730:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105725730));
				orderActorToFactory(1105728730, EnemyMetis, "Metis_1487");
				break;
			case 25750:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105725750));
				orderActorToFactory(1105728750, EnemyMetis, "Metis_1488");
				break;
			case 25770:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105725770));
				orderActorToFactory(1105728770, EnemyMetis, "Metis_1489");
				break;
			case 25790:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105725790));
				orderActorToFactory(1105728790, EnemyMetis, "Metis_1490");
				break;
			case 25810:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105725810));
				orderActorToFactory(1105728810, EnemyMetis, "Metis_1491");
				break;
			case 25830:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105725830));
				orderActorToFactory(1105728830, EnemyMetis, "Metis_1492");
				break;
			case 25850:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105725850));
				orderActorToFactory(1105728850, EnemyMetis, "Metis_1493");
				break;
			case 25870:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105725870));
				orderActorToFactory(1105728870, EnemyMetis, "Metis_1494");
				break;
			case 25890:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105725890));
				orderActorToFactory(1105728890, EnemyMetis, "Metis_1495");
				break;
			case 25910:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105725910));
				orderActorToFactory(1105728910, EnemyMetis, "Metis_1496");
				break;
			case 25930:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105725930));
				orderActorToFactory(1105728930, EnemyMetis, "Metis_1497");
				break;
			case 25950:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105725950));
				orderActorToFactory(1105728950, EnemyMetis, "Metis_1498");
				break;
			case 25970:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105725970));
				orderActorToFactory(1105728970, EnemyMetis, "Metis_1499");
				break;
			case 25990:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105725990));
				orderActorToFactory(1105728990, EnemyMetis, "Metis_1500");
				break;
			case 26010:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105726010));
				orderActorToFactory(1105729010, EnemyMetis, "Metis_1501");
				break;
			case 26030:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105726030));
				orderActorToFactory(1105729030, EnemyMetis, "Metis_1502");
				break;
			case 26050:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105726050));
				orderActorToFactory(1105729050, EnemyMetis, "Metis_1503");
				break;
			case 26070:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105726070));
				orderActorToFactory(1105729070, EnemyMetis, "Metis_1504");
				break;
			case 26090:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105726090));
				orderActorToFactory(1105729090, EnemyMetis, "Metis_1505");
				break;
			case 26110:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105726110));
				orderActorToFactory(1105729110, EnemyMetis, "Metis_1506");
				break;
			case 26130:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105726130));
				orderActorToFactory(1105729130, EnemyMetis, "Metis_1507");
				break;
			case 26150:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105726150));
				orderActorToFactory(1105729150, EnemyMetis, "Metis_1508");
				break;
			case 26170:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105726170));
				orderActorToFactory(1105729170, EnemyMetis, "Metis_1509");
				break;
			case 26190:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105726190));
				orderActorToFactory(1105729190, EnemyMetis, "Metis_1510");
				break;
			case 26210:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105726210));
				orderActorToFactory(1105729210, EnemyMetis, "Metis_1511");
				break;
			case 26230:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105726230));
				orderActorToFactory(1105729230, EnemyMetis, "Metis_1512");
				break;
			case 26250:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105726250));
				orderActorToFactory(1105729250, EnemyMetis, "Metis_1513");
				break;
			case 26270:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105726270));
				orderActorToFactory(1105729270, EnemyMetis, "Metis_1514");
				break;
			case 26290:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105726290));
				orderActorToFactory(1105729290, EnemyMetis, "Metis_1515");
				break;
			case 26310:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105726310));
				orderActorToFactory(1105729310, EnemyMetis, "Metis_1516");
				break;
			case 26330:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105726330));
				orderActorToFactory(1105729330, EnemyMetis, "Metis_1517");
				break;
			case 26350:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105726350));
				orderActorToFactory(1105729350, EnemyMetis, "Metis_1518");
				break;
			case 26370:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105726370));
				orderActorToFactory(1105729370, EnemyMetis, "Metis_1519");
				break;
			case 26390:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105726390));
				orderActorToFactory(1105729390, EnemyMetis, "Metis_1520");
				break;
			case 26410:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105726410));
				orderActorToFactory(1105729410, EnemyMetis, "Metis_1521");
				break;
			case 26430:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105726430));
				orderActorToFactory(1105729430, EnemyMetis, "Metis_1522");
				break;
			case 26450:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105726450));
				orderActorToFactory(1105729450, EnemyMetis, "Metis_1523");
				break;
			case 26470:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105726470));
				orderActorToFactory(1105729470, EnemyMetis, "Metis_1524");
				break;
			case 26490:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105726490));
				orderActorToFactory(1105729490, EnemyMetis, "Metis_1525");
				break;
			case 26510:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105726510));
				orderActorToFactory(1105729510, EnemyMetis, "Metis_1526");
				break;
			case 26530:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105726530));
				orderActorToFactory(1105729530, EnemyMetis, "Metis_1527");
				break;
			case 26550:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105726550));
				orderActorToFactory(1105729550, EnemyMetis, "Metis_1528");
				break;
			case 26570:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105726570));
				orderActorToFactory(1105729570, EnemyMetis, "Metis_1529");
				break;
			case 26590:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105726590));
				orderActorToFactory(1105729590, EnemyMetis, "Metis_1530");
				break;
			case 26610:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105726610));
				orderActorToFactory(1105729610, EnemyMetis, "Metis_1531");
				break;
			case 26630:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105726630));
				orderActorToFactory(1105729630, EnemyMetis, "Metis_1532");
				break;
			case 26650:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105726650));
				orderActorToFactory(1105729650, EnemyMetis, "Metis_1533");
				break;
			case 26670:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105726670));
				orderActorToFactory(1105729670, EnemyMetis, "Metis_1534");
				break;
			case 26690:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105726690));
				orderActorToFactory(1105729690, EnemyMetis, "Metis_1535");
				break;
			case 26710:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105726710));
				orderActorToFactory(1105729710, EnemyMetis, "Metis_1536");
				break;
			case 26730:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105726730));
				orderActorToFactory(1105729730, EnemyMetis, "Metis_1537");
				break;
			case 26750:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105726750));
				orderActorToFactory(1105729750, EnemyMetis, "Metis_1538");
				break;
			case 26770:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105726770));
				orderActorToFactory(1105729770, EnemyMetis, "Metis_1539");
				break;
			case 26790:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105726790));
				orderActorToFactory(1105729790, EnemyMetis, "Metis_1540");
				break;
			case 26810:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105726810));
				orderActorToFactory(1105729810, EnemyMetis, "Metis_1541");
				break;
			case 26830:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105726830));
				orderActorToFactory(1105729830, EnemyMetis, "Metis_1542");
				break;
			case 26850:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105726850));
				orderActorToFactory(1105729850, EnemyMetis, "Metis_1543");
				break;
			case 26870:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105726870));
				orderActorToFactory(1105729870, EnemyMetis, "Metis_1544");
				break;
			case 26890:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105726890));
				orderActorToFactory(1105729890, EnemyMetis, "Metis_1545");
				break;
			case 26910:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105726910));
				orderActorToFactory(1105729910, EnemyMetis, "Metis_1546");
				break;
			case 26930:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105726930));
				orderActorToFactory(1105729930, EnemyMetis, "Metis_1547");
				break;
			case 26950:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105726950));
				orderActorToFactory(1105729950, EnemyMetis, "Metis_1548");
				break;
			case 26970:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105726970));
				orderActorToFactory(1105729970, EnemyMetis, "Metis_1549");
				break;
			case 26990:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105726990));
				orderActorToFactory(1105729990, EnemyMetis, "Metis_1550");
				break;
			case 27010:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105727010));
				orderActorToFactory(1105730010, EnemyMetis, "Metis_1551");
				break;
			case 27030:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105727030));
				orderActorToFactory(1105730030, EnemyMetis, "Metis_1552");
				break;
			case 27050:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105727050));
				orderActorToFactory(1105730050, EnemyMetis, "Metis_1553");
				break;
			case 27070:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105727070));
				orderActorToFactory(1105730070, EnemyMetis, "Metis_1554");
				break;
			case 27090:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105727090));
				orderActorToFactory(1105730090, EnemyMetis, "Metis_1555");
				break;
			case 27110:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105727110));
				orderActorToFactory(1105730110, EnemyMetis, "Metis_1556");
				break;
			case 27130:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105727130));
				orderActorToFactory(1105730130, EnemyMetis, "Metis_1557");
				break;
			case 27150:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105727150));
				orderActorToFactory(1105730150, EnemyMetis, "Metis_1558");
				break;
			case 27170:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105727170));
				orderActorToFactory(1105730170, EnemyMetis, "Metis_1559");
				break;
			case 27190:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105727190));
				orderActorToFactory(1105730190, EnemyMetis, "Metis_1560");
				break;
			case 27210:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105727210));
				orderActorToFactory(1105730210, EnemyMetis, "Metis_1561");
				break;
			case 27230:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105727230));
				orderActorToFactory(1105730230, EnemyMetis, "Metis_1562");
				break;
			case 27250:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105727250));
				orderActorToFactory(1105730250, EnemyMetis, "Metis_1563");
				break;
			case 27270:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105727270));
				orderActorToFactory(1105730270, EnemyMetis, "Metis_1564");
				break;
			case 27290:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105727290));
				orderActorToFactory(1105730290, EnemyMetis, "Metis_1565");
				break;
			case 27310:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105727310));
				orderActorToFactory(1105730310, EnemyMetis, "Metis_1566");
				break;
			case 27330:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105727330));
				orderActorToFactory(1105730330, EnemyMetis, "Metis_1567");
				break;
			case 27350:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105727350));
				orderActorToFactory(1105730350, EnemyMetis, "Metis_1568");
				break;
			case 27370:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105727370));
				orderActorToFactory(1105730370, EnemyMetis, "Metis_1569");
				break;
			case 27390:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105727390));
				orderActorToFactory(1105730390, EnemyMetis, "Metis_1570");
				break;
			case 27410:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105727410));
				orderActorToFactory(1105730410, EnemyMetis, "Metis_1571");
				break;
			case 27430:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105727430));
				orderActorToFactory(1105730430, EnemyMetis, "Metis_1572");
				break;
			case 27450:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105727450));
				orderActorToFactory(1105730450, EnemyMetis, "Metis_1573");
				break;
			case 27470:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105727470));
				orderActorToFactory(1105730470, EnemyMetis, "Metis_1574");
				break;
			case 27490:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105727490));
				orderActorToFactory(1105730490, EnemyMetis, "Metis_1575");
				break;
			case 27510:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105727510));
				orderActorToFactory(1105730510, EnemyMetis, "Metis_1576");
				break;
			case 27530:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105727530));
				orderActorToFactory(1105730530, EnemyMetis, "Metis_1577");
				break;
			case 27550:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105727550));
				orderActorToFactory(1105730550, EnemyMetis, "Metis_1578");
				break;
			case 27570:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105727570));
				orderActorToFactory(1105730570, EnemyMetis, "Metis_1579");
				break;
			case 27590:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105727590));
				orderActorToFactory(1105730590, EnemyMetis, "Metis_1580");
				break;
			case 27610:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105727610));
				orderActorToFactory(1105730610, EnemyMetis, "Metis_1581");
				break;
			case 27630:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105727630));
				orderActorToFactory(1105730630, EnemyMetis, "Metis_1582");
				break;
			case 27650:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105727650));
				orderActorToFactory(1105730650, EnemyMetis, "Metis_1583");
				break;
			case 27670:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105727670));
				orderActorToFactory(1105730670, EnemyMetis, "Metis_1584");
				break;
			case 27690:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105727690));
				orderActorToFactory(1105730690, EnemyMetis, "Metis_1585");
				break;
			case 27710:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105727710));
				orderActorToFactory(1105730710, EnemyMetis, "Metis_1586");
				break;
			case 27730:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105727730));
				orderActorToFactory(1105730730, EnemyMetis, "Metis_1587");
				break;
			case 27750:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105727750));
				orderActorToFactory(1105730750, EnemyMetis, "Metis_1588");
				break;
			case 27770:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105727770));
				orderActorToFactory(1105730770, EnemyMetis, "Metis_1589");
				break;
			case 27790:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105727790));
				orderActorToFactory(1105730790, EnemyMetis, "Metis_1590");
				break;
			case 27810:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105727810));
				orderActorToFactory(1105730810, EnemyMetis, "Metis_1591");
				break;
			case 27830:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105727830));
				orderActorToFactory(1105730830, EnemyMetis, "Metis_1592");
				break;
			case 27850:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105727850));
				orderActorToFactory(1105730850, EnemyMetis, "Metis_1593");
				break;
			case 27870:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105727870));
				orderActorToFactory(1105730870, EnemyMetis, "Metis_1594");
				break;
			case 27890:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105727890));
				orderActorToFactory(1105730890, EnemyMetis, "Metis_1595");
				break;
			case 27910:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105727910));
				orderActorToFactory(1105730910, EnemyMetis, "Metis_1596");
				break;
			case 27930:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105727930));
				orderActorToFactory(1105730930, EnemyMetis, "Metis_1597");
				break;
			case 27950:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105727950));
				orderActorToFactory(1105730950, EnemyMetis, "Metis_1598");
				break;
			case 27970:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105727970));
				orderActorToFactory(1105730970, EnemyMetis, "Metis_1599");
				break;
			case 27990:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105727990));
				orderActorToFactory(1105730990, EnemyMetis, "Metis_1600");
				break;
			case 28010:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105728010));
				orderActorToFactory(1105731010, EnemyMetis, "Metis_1601");
				break;
			case 28030:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105728030));
				orderActorToFactory(1105731030, EnemyMetis, "Metis_1602");
				break;
			case 28050:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105728050));
				orderActorToFactory(1105731050, EnemyMetis, "Metis_1603");
				break;
			case 28070:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105728070));
				orderActorToFactory(1105731070, EnemyMetis, "Metis_1604");
				break;
			case 28090:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105728090));
				orderActorToFactory(1105731090, EnemyMetis, "Metis_1605");
				break;
			case 28110:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105728110));
				orderActorToFactory(1105731110, EnemyMetis, "Metis_1606");
				break;
			case 28130:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105728130));
				orderActorToFactory(1105731130, EnemyMetis, "Metis_1607");
				break;
			case 28150:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105728150));
				orderActorToFactory(1105731150, EnemyMetis, "Metis_1608");
				break;
			case 28170:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105728170));
				orderActorToFactory(1105731170, EnemyMetis, "Metis_1609");
				break;
			case 28190:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105728190));
				orderActorToFactory(1105731190, EnemyMetis, "Metis_1610");
				break;
			case 28210:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105728210));
				orderActorToFactory(1105731210, EnemyMetis, "Metis_1611");
				break;
			case 28230:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105728230));
				orderActorToFactory(1105731230, EnemyMetis, "Metis_1612");
				break;
			case 28250:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105728250));
				orderActorToFactory(1105731250, EnemyMetis, "Metis_1613");
				break;
			case 28270:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105728270));
				orderActorToFactory(1105731270, EnemyMetis, "Metis_1614");
				break;
			case 28290:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105728290));
				orderActorToFactory(1105731290, EnemyMetis, "Metis_1615");
				break;
			case 28310:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105728310));
				orderActorToFactory(1105731310, EnemyMetis, "Metis_1616");
				break;
			case 28330:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105728330));
				orderActorToFactory(1105731330, EnemyMetis, "Metis_1617");
				break;
			case 28350:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105728350));
				orderActorToFactory(1105731350, EnemyMetis, "Metis_1618");
				break;
			case 28370:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105728370));
				orderActorToFactory(1105731370, EnemyMetis, "Metis_1619");
				break;
			case 28390:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105728390));
				orderActorToFactory(1105731390, EnemyMetis, "Metis_1620");
				break;
			case 28410:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105728410));
				orderActorToFactory(1105731410, EnemyMetis, "Metis_1621");
				break;
			case 28430:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105728430));
				orderActorToFactory(1105731430, EnemyMetis, "Metis_1622");
				break;
			case 28450:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105728450));
				orderActorToFactory(1105731450, EnemyMetis, "Metis_1623");
				break;
			case 28470:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105728470));
				orderActorToFactory(1105731470, EnemyMetis, "Metis_1624");
				break;
			case 28490:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105728490));
				orderActorToFactory(1105731490, EnemyMetis, "Metis_1625");
				break;
			case 28510:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105728510));
				orderActorToFactory(1105731510, EnemyMetis, "Metis_1626");
				break;
			case 28530:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105728530));
				orderActorToFactory(1105731530, EnemyMetis, "Metis_1627");
				break;
			case 28550:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105728550));
				orderActorToFactory(1105731550, EnemyMetis, "Metis_1628");
				break;
			case 28570:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105728570));
				orderActorToFactory(1105731570, EnemyMetis, "Metis_1629");
				break;
			case 28590:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105728590));
				orderActorToFactory(1105731590, EnemyMetis, "Metis_1630");
				break;
			case 28610:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105728610));
				orderActorToFactory(1105731610, EnemyMetis, "Metis_1631");
				break;
			case 28630:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105728630));
				orderActorToFactory(1105731630, EnemyMetis, "Metis_1632");
				break;
			case 28650:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105728650));
				orderActorToFactory(1105731650, EnemyMetis, "Metis_1633");
				break;
			case 28670:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105728670));
				orderActorToFactory(1105731670, EnemyMetis, "Metis_1634");
				break;
			case 28690:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105728690));
				orderActorToFactory(1105731690, EnemyMetis, "Metis_1635");
				break;
			case 28710:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105728710));
				orderActorToFactory(1105731710, EnemyMetis, "Metis_1636");
				break;
			case 28730:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105728730));
				orderActorToFactory(1105731730, EnemyMetis, "Metis_1637");
				break;
			case 28750:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105728750));
				orderActorToFactory(1105731750, EnemyMetis, "Metis_1638");
				break;
			case 28770:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105728770));
				orderActorToFactory(1105731770, EnemyMetis, "Metis_1639");
				break;
			case 28790:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105728790));
				orderActorToFactory(1105731790, EnemyMetis, "Metis_1640");
				break;
			case 28810:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105728810));
				orderActorToFactory(1105731810, EnemyMetis, "Metis_1641");
				break;
			case 28830:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105728830));
				orderActorToFactory(1105731830, EnemyMetis, "Metis_1642");
				break;
			case 28850:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105728850));
				orderActorToFactory(1105731850, EnemyMetis, "Metis_1643");
				break;
			case 28870:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105728870));
				orderActorToFactory(1105731870, EnemyMetis, "Metis_1644");
				break;
			case 28890:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105728890));
				orderActorToFactory(1105731890, EnemyMetis, "Metis_1645");
				break;
			case 28910:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105728910));
				orderActorToFactory(1105731910, EnemyMetis, "Metis_1646");
				break;
			case 28930:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105728930));
				orderActorToFactory(1105731930, EnemyMetis, "Metis_1647");
				break;
			case 28950:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105728950));
				orderActorToFactory(1105731950, EnemyMetis, "Metis_1648");
				break;
			case 28970:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105728970));
				orderActorToFactory(1105731970, EnemyMetis, "Metis_1649");
				break;
			case 28990:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105728990));
				orderActorToFactory(1105731990, EnemyMetis, "Metis_1650");
				break;
			case 29010:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105729010));
				break;
			case 29030:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105729030));
				break;
			case 29050:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105729050));
				break;
			case 29070:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105729070));
				break;
			case 29090:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105729090));
				break;
			case 29110:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105729110));
				break;
			case 29130:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105729130));
				break;
			case 29150:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105729150));
				break;
			case 29170:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105729170));
				break;
			case 29190:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105729190));
				break;
			case 29210:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105729210));
				break;
			case 29230:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105729230));
				break;
			case 29250:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105729250));
				break;
			case 29270:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105729270));
				break;
			case 29290:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105729290));
				break;
			case 29310:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105729310));
				break;
			case 29330:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105729330));
				break;
			case 29350:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105729350));
				break;
			case 29370:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105729370));
				break;
			case 29390:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105729390));
				break;
			case 29410:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105729410));
				break;
			case 29430:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105729430));
				break;
			case 29450:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105729450));
				break;
			case 29470:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105729470));
				break;
			case 29490:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105729490));
				break;
			case 29510:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105729510));
				break;
			case 29530:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105729530));
				break;
			case 29550:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105729550));
				break;
			case 29570:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105729570));
				break;
			case 29590:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105729590));
				break;
			case 29610:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105729610));
				break;
			case 29630:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105729630));
				break;
			case 29650:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105729650));
				break;
			case 29670:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105729670));
				break;
			case 29690:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105729690));
				break;
			case 29710:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105729710));
				break;
			case 29730:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105729730));
				break;
			case 29750:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105729750));
				break;
			case 29770:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105729770));
				break;
			case 29790:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105729790));
				break;
			case 29810:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105729810));
				break;
			case 29830:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105729830));
				break;
			case 29850:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105729850));
				break;
			case 29870:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105729870));
				break;
			case 29890:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105729890));
				break;
			case 29910:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105729910));
				break;
			case 29930:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105729930));
				break;
			case 29950:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105729950));
				break;
			case 29970:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105729970));
				break;
			case 29990:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105729990));
				break;
			case 30010:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105730010));
				break;
			case 30030:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105730030));
				break;
			case 30050:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105730050));
				break;
			case 30070:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105730070));
				break;
			case 30090:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105730090));
				break;
			case 30110:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105730110));
				break;
			case 30130:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105730130));
				break;
			case 30150:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105730150));
				break;
			case 30170:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105730170));
				break;
			case 30190:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105730190));
				break;
			case 30210:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105730210));
				break;
			case 30230:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105730230));
				break;
			case 30250:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105730250));
				break;
			case 30270:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105730270));
				break;
			case 30290:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105730290));
				break;
			case 30310:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105730310));
				break;
			case 30330:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105730330));
				break;
			case 30350:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105730350));
				break;
			case 30370:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105730370));
				break;
			case 30390:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105730390));
				break;
			case 30410:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105730410));
				break;
			case 30430:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105730430));
				break;
			case 30450:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105730450));
				break;
			case 30470:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105730470));
				break;
			case 30490:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105730490));
				break;
			case 30510:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105730510));
				break;
			case 30530:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105730530));
				break;
			case 30550:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105730550));
				break;
			case 30570:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105730570));
				break;
			case 30590:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105730590));
				break;
			case 30610:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105730610));
				break;
			case 30630:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105730630));
				break;
			case 30650:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105730650));
				break;
			case 30670:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105730670));
				break;
			case 30690:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105730690));
				break;
			case 30710:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105730710));
				break;
			case 30730:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105730730));
				break;
			case 30750:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105730750));
				break;
			case 30770:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105730770));
				break;
			case 30790:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105730790));
				break;
			case 30810:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105730810));
				break;
			case 30830:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105730830));
				break;
			case 30850:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105730850));
				break;
			case 30870:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105730870));
				break;
			case 30890:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105730890));
				break;
			case 30910:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105730910));
				break;
			case 30930:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105730930));
				break;
			case 30950:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105730950));
				break;
			case 30970:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105730970));
				break;
			case 30990:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105730990));
				break;
			case 31010:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105731010));
				break;
			case 31030:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105731030));
				break;
			case 31050:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105731050));
				break;
			case 31070:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105731070));
				break;
			case 31090:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105731090));
				break;
			case 31110:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105731110));
				break;
			case 31130:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105731130));
				break;
			case 31150:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105731150));
				break;
			case 31170:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105731170));
				break;
			case 31190:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105731190));
				break;
			case 31210:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105731210));
				break;
			case 31230:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105731230));
				break;
			case 31250:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105731250));
				break;
			case 31270:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105731270));
				break;
			case 31290:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105731290));
				break;
			case 31310:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105731310));
				break;
			case 31330:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105731330));
				break;
			case 31350:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105731350));
				break;
			case 31370:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105731370));
				break;
			case 31390:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105731390));
				break;
			case 31410:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105731410));
				break;
			case 31430:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105731430));
				break;
			case 31450:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105731450));
				break;
			case 31470:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105731470));
				break;
			case 31490:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105731490));
				break;
			case 31510:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105731510));
				break;
			case 31530:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105731530));
				break;
			case 31550:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105731550));
				break;
			case 31570:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105731570));
				break;
			case 31590:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105731590));
				break;
			case 31610:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105731610));
				break;
			case 31630:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105731630));
				break;
			case 31650:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105731650));
				break;
			case 31670:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105731670));
				break;
			case 31690:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105731690));
				break;
			case 31710:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105731710));
				break;
			case 31730:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105731730));
				break;
			case 31750:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105731750));
				break;
			case 31770:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105731770));
				break;
			case 31790:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105731790));
				break;
			case 31810:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105731810));
				break;
			case 31830:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105731830));
				break;
			case 31850:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105731850));
				break;
			case 31870:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105731870));
				break;
			case 31890:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105731890));
				break;
			case 31910:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105731910));
				break;
			case 31930:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105731930));
				break;
			case 31950:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105731950));
				break;
			case 31970:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105731970));
				break;
			case 31990:
				getLordActor()->addSubGroup(obtainActorFromFactory(1105731990));
				break;
			default :
				break;
		}
		_iCnt_Event = (_iCnt_Event < 1646-1 ? _iCnt_Event+1 : _iCnt_Event);
	}
    // gen02 end

    if (getBehaveingFrame() == 2) {

        _TRACE_("Stage01MainScene::processBehavior はいはいDemoさんありがとう、私も起動しましたよ");
        // 共通シーンを配下に移動
        addSubLast(GameGlobal::_pSceneCommon->extract());

    }

}

void Stage01MainScene::processFinal() {
    //	if (getBehaveingFrame() == 1) {
    //		_TRACE_("Stage01MainScene::processFinally 私はいきなり停止します。GameMainSceneが解除してくれるはずー");
    //		this->inactivateTree(); //GameMainSceneが解除してくれる
    //	}
}

Stage01MainScene::~Stage01MainScene() {
    //NEWからprocessBehaviorまでの間に強制終了された場合、
    //_pDispatcherはどのツリーにも所属していない。
    if (_pDispatcher->getParent() == NULL) {
        _TRACE_("_pDispatcherが未所属のため独自delete");
        DELETE_IMPOSSIBLE_NULL(_pDispatcher);
    }
}
