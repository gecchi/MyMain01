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
	frame f[] = {1,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,210,220,230,240,250,260,270,280,290,300,310,320,330,340,350,360,370,380,390,400,410,420,430,440,450,460,470,480,490,500,510,520,530,540,550,560,570,580,590,600,610,620,630,640,650,660,670,680,690,700,710,720,730,740,750,760,770,780,790,800,810,820,830,840,850,860,870,880,890,900,910,920,930,940,950,960,970,980,990,1000,1010,1020,1030,1040,1050,1060,1070,1080,1090,1100,1110,1120,1130,1140,1150,1160,1170,1180,1190,1200,1210,1220,1230,1240,1250,1260,1270,1280,1290,1300,1310,1320,1330,1340,1350,1360,1370,1380,1390,1400,1410,1420,1430,1440,1450,1460,1470,1480,1490,1500,1510,1520,1530,1540,1550,1560,1570,1580,1590,1600,1610,1620,1630,1640,1650,1660,1670,1680,1690,1700,1710,1720,1730,1740,1750,1760,1770,1780,1790,1800,1810,1820,1830,1840,1850,1860,1870,1880,1890,1900,1910,1920,1930,1940,1950,1960,1970,1980,1990,2000,2010,2020,2030,2040,2050,2060,2070,2080,2090,2100,2110,2120,2130,2140,2150,2160,2170,2180,2190,2200,2210,2220,2230,2240,2250,2260,2270,2280,2290,2300,2310,2320,2330,2340,2350,2360,2370,2380,2390,2400,2410,2420,2430,2440,2450,2460,2470,2480,2490,2500,2510,2520,2530,2540,2550,2560,2570,2580,2590,2600,2610,2620,2630,2640,2650,2660,2670,2680,2690,2700,2710,2720,2730,2740,2750,2760,2770,2780,2790,2800,2810,2820,2830,2840,2850,2860,2870,2880,2890,2900,2910,2920,2930,2940,2950,2960,2970,2980,2990,3000,3010,3020,3030,3040,3050,3060,3070,3080,3090,3100,3110,3120,3130,3140,3150,3160,3170,3180,3190,3200,3210,3220,3230,3240,3250,3260,3270,3280,3290,3300,3310,3320,3330,3340,3350,3360,3370,3380,3390,3400,3410,3420,3430,3440,3450,3460,3470,3480,3490,3500,3510,3520,3530,3540,3550,3560,3570,3580,3590,3600,3610,3620,3630,3640,3650,3660,3670,3680,3690,3700,3710,3720,3730,3740,3750,3760,3770,3780,3790,3800,3810,3820,3830,3840,3850,3860,3870,3880,3890,3900,3910,3920,3930,3940,3950,3960,3970,3980,3990,4000,4010,4020,4030,4040,4050,4060,4070,4080,4090,4100,4110,4120,4130,4140,4150,4160,4170,4180,4190,4200,4210,4220,4230,4240,4250,4260,4270,4280,4290,4300,4310,4320,4330,4340,4350,4360,4370,4380,4390,4400,4410,4420,4430,4440,4450,4460,4470,4480,4490,4500,4510,4520,4530,4540,4550,4560,4570,4580,4590,4600,4610,4620,4630,4640,4650,4660,4670,4680,4690,4700,4710,4720,4730,4740,4750,4760,4770,4780,4790,4800,4810,4820,4830,4840,4850,4860,4870,4880,4890,4900,4910,4920,4930,4940,4950,4960,4970,4980,4990,5000,5010,5020,5030,5040,5050,5060,5070,5080,5090,5100,5110,5120,5130,5140,5150,5160,5170,5180,5190,5200,5210,5220,5230,5240,5250,5260,5270,5280,5290,5300,5310,5320,5330,5340,5350,5360,5370,5380,5390,5400,5410,5420,5430,5440,5450,5460,5470,5480,5490,5500,5510,5520,5530,5540,5550,5560,5570,5580,5590,5600,5610,5620,5630,5640,5650,5660,5670,5680,5690,5700,5710,5720,5730,5740,5750,5760,5770,5780,5790,5800,5810,5820,5830,5840,5850,5860,5870,5880,5890,5900,5910,5920,5930,5940,5950,5960,5970,5980,5990,6000,6010,6020,6030,6040,6050,6060,6070,6080,6090,6100,6110,6120,6130,6140,6150,6160,6170,6180,6190,6200,6210,6220,6230,6240,6250,6260,6270,6280,6290,6300,6310,6320,6330,6340,6350,6360,6370,6380,6390,6400,6410,6420,6430,6440,6450,6460,6470,6480,6490,6500,6510,6520,6530,6540,6550,6560,6570,6580,6590,6600,6610,6620,6630,6640,6650,6660,6670,6680,6690,6700,6710,6720,6730,6740,6750,6760,6770,6780,6790,6800,6810,6820,6830,6840,6850,6860,6870,6880,6890,6900,6910,6920,6930,6940,6950,6960,6970,6980,6990,7000,7010,7020,7030,7040,7050,7060,7070,7080,7090,7100,7110,7120,7130,7140,7150,7160,7170,7180,7190,7200,7210,7220,7230,7240,7250,7260,7270,7280,7290,7300,7310,7320,7330,7340,7350,7360,7370,7380,7390,7400,7410,7420,7430,7440,7450,7460,7470,7480,7490,7500,7510,7520,7530,7540,7550,7560,7570,7580,7590,7600,7610,7620,7630,7640,7650,7660,7670,7680,7690,7700,7710,7720,7730,7740,7750,7760,7770,7780,7790,7800,7810,7820,7830,7840,7850,7860,7870,7880,7890,7900,7910,7920,7930,7940,7950,7960,7970,7980,7990,8000,8010,8020,8030,8040,8050,8060,8070,8080,8090,8100,8110,8120,8130,8140,8150,8160,8170,8180,8190,8200,8210,8220,8230,8240,8250,8260,8270,8280,8290,8300,8310,8320,8330,8340,8350,8360,8370,8380,8390,8400,8410,8420,8430,8440,8450,8460,8470,8480,8490,8500,8510,8520,8530,8540,8550,8560,8570,8580,8590,8600,8610,8620,8630,8640,8650,8660,8670,8680,8690,8700,8710,8720,8730,8740,8750,8760,8770,8780,8790,8800,8810,8820,8830,8840,8850,8860,8870,8880,8890,8900,8910,8920,8930,8940,8950,8960,8970,8980,8990,9000,9010,9020,9030,9040,9050,9060,9070,9080,9090,9100,9110,9120,9130,9140,9150,9160,9170,9180,9190,9200,9210,9220,9230,9240,9250,9260,9270,9280,9290,9300,9310,9320,9330,9340,9350,9360,9370,9380,9390,9400,9410,9420,9430,9440,9450,9460,9470,9480,9490,9500,9510,9520,9530,9540,9550,9560,9570,9580,9590,9600,9610,9620,9630,9640,9650,9660,9670,9680,9690,9700,9710,9720,9730,9740,9750,9760,9770,9780,9790,9800,9810,9820,9830,9840,9850,9860,9870,9880,9890,9900,9910,9920,9930,9940,9950,9960,9970,9980,9990,10000,10010,10020,10030,10040,10050,10060,10070,10080,10090,10100,10110,10120,10130,10140,10150,10160,10170,10180,10190,10200,10210,10220,10230,10240,10250,10260,10270,10280,10290,10300,10310,10320,10330,10340,10350,10360,10370,10380,10390,10400,10410,10420,10430,10440,10450,10460,10470,10480,10490,10500,10510,10520,10530,10540,10550,10560,10570,10580,10590,10600,10610,10620,10630,10640,10650,10660,10670,10680,10690,10700,10710,10720,10730,10740,10750,10760,10770,10780,10790,10800,10810,10820,10830,10840,10850,10860,10870,10880,10890,10900,10910,10920,10930,10940,10950,10960,10970,10980,10990,11000,11010,11020,11030,11040,11050,11060,11070,11080,11090,11100,11110,11120,11130,11140,11150,11160,11170,11180,11190,11200,11210,11220,11230,11240,11250,11260,11270,11280,11290,11300,11310,11320,11330,11340,11350,11360,11370,11380,11390,11400,11410,11420,11430,11440,11450,11460,11470,11480,11490,11500,11510,11520,11530,11540,11550,11560,11570,11580,11590,11600,11610,11620,11630,11640,11650,11660,11670,11680,11690,11700,11710,11720,11730,11740,11750,11760,11770,11780,11790,11800,11810,11820,11830,11840,11850,11860,11870,11880,11890,11900,11910,11920,11930,11940,11950,11960,11970,11980,11990,12000,12010,12020,12030,12040,12050,12060,12070,12080,12090,12100,12110,12120,12130,12140,12150,12160,12170,12180,12190,12200,12210,12220,12230,12240,12250,12260,12270,12280,12290,12300,12310,12320,12330,12340,12350,12360,12370,12380,12390,12400,12410,12420,12430,12440,12450,12460,12470,12480,12490,12500,12510,12520,12530,12540,12550,12560,12570,12580,12590,12600,12610,12620,12630,12640,12650,12660,12670,12680,12690,12700,12710,12720,12730,12740,12750,12760,12770,12780,12790,12800,12810,12820,12830,12840,12850,12860,12870,12880,12890,12900,12910,12920,12930,12940,12950,12960,12970,12980,12990,13000,13010,13020,13030,13040,13050,13060,13070,13080,13090,13100,13110,13120,13130,13140,13150,13160,13170,13180,13190,13200,13210,13220,13230,13240,13250,13260,13270,13280,13290,13300,13310,13320,13330,13340,13350,13360,13370,13380,13390,13400,13410,13420,13430,13440,13450,13460,13470,13480,13490,13500,13510,13520,13530,13540,13550,13560,13570,13580,13590,13600,13610,13620,13630,13640,13650,13660,13670,13680,13690,13700,13710,13720,13730,13740,13750,13760,13770,13780,13790,13800,13810,13820,13830,13840,13850,13860,13870,13880,13890,13900,13910,13920,13930,13940,13950,13960,13970,13980,13990,14000,14010,14020,14030,14040,14050,14060,14070,14080,14090,14100,14110,14120,14130,14140,14150,14160,14170,14180,14190,14200,14210,14220,14230,14240,14250,14260,14270,14280,14290,14300,14310,14320,14330,14340,14350,14360,14370,14380,14390,14400,14410,14420,14430,14440,14450,14460,14470,14480,14490,14500,14510,14520,14530,14540,14550,14560,14570,14580,14590,14600,14610,14620,14630,14640,14650,14660,14670,14680,14690,14700,14710,14720,14730,14740,14750,14760,14770,14780,14790,14800,14810,14820,14830,14840,14850,14860,14870,14880,14890,14900,14910,14920,14930,14940,14950,14960,14970,14980,14990,15000,15010,15020,15030,15040,15050,15060,15070,15080,15090,15100,15110,15120,15130,15140,15150,15160,15170,15180,15190,15200,15210,15220,15230,15240,15250,15260,15270,15280,15290,15300,15310,15320,15330,15340,15350,15360,15370,15380,15390,15400,15410,15420,15430,15440,15450,15460,15470,15480,15490,15500,15510,15520,15530,15540,15550,15560,15570,15580,15590,15600,15610,15620,15630,15640,15650,15660,15670,15680,15690,15700,15710,15720,15730,15740,15750,15760,15770,15780,15790,15800,15810,15820,15830,15840,15850,15860,15870,15880,15890,15900,15910,15920,15930,15940,15950,15960,15970,15980,15990,16000,16010,16020,16030,16040,16050,16060,16070,16080,16090,16100,16110,16120,16130,16140,16150,16160,16170,16180,16190,16200,16210,16220,16230,16240,16250,16260,16270,16280,16290,16300,16310,16320,16330,16340,16350,16360,16370,16380,16390,16400,16410,16420,16430,16440,16450,16460,16470,16480,16490,16500,16510,16520,16530,16540,16550,16560,16570,16580,16590,16600,16610,16620,16630,16640,16650,16660,16670,16680,16690,16700,16710,16720,16730,16740,16750,16760,16770,16780,16790,16800,16810,16820,16830,16840,16850,16860,16870,16880,16890,16900,16910,16920,16930,16940,16950,16960,16970,16980,16990,17000,17010,17020,17030,17040,17050,17060,17070,17080,17090,17100,17110,17120,17130,17140,17150,17160,17170,17180,17190,17200,17210,17220,17230,17240,17250,17260,17270,17280,17290,17300,17310,17320,17330,17340,17350,17360,17370,17380,17390,17400,17410,17420,17430,17440,17450,17460,17470,17480,17490,17500,17510,17520,17530,17540,17550,17560,17570,17580,17590,17600,17610,17620,17630,17640,17650,17660,17670,17680,17690,17700,17710,17720,17730,17740,17750,17760,17770,17780,17790,17800,17810,17820,17830,17840,17850,17860,17870,17880,17890,17900,17910,17920,17930,17940,17950,17960,17970,17980,17990,18000,18010,18020,18030,18040,18050,18060,18070,18080,18090,18100,18110,18120,18130,18140,18150,18160,18170,18180,18190,18200,18210,18220,18230,18240,18250,18260,18270,18280,18290,18300,18310,18320,18330,18340,18350,18360,18370,18380,18390,18400,18410,18420,18430,18440,18450,18460,18470,18480,18490,18500,18510,18520,18530,18540,18550,18560,18570,18580,18590,18600,18610,18620,18630,18640,18650,18660,18670,18680,18690,18700,18710,18720,18730,18740,18750,18760,18770,18780,18790,18800,18810,18820,18830,18840,18850,18860,18870,18880,18890,18900,18910,18920,18930,18940,18950,18960,18970,18980,18990,19000,19010,19020,19030,19040,19050,19060,19070,19080,19090,19100,19110,19120,19130,19140,19150,19160,19170,19180,19190,19200,19210,19220,19230,19240,19250,19260,19270,19280,19290,19300,19310,19320,19330,19340,19350,19360,19370,19380,19390,19400,19410,19420,19430,19440,19450,19460,19470,19480,19490,19500,19510,19520,19530,19540,19550,19560,19570,19580,19590,19600,19610,19620,19630,19640,19650,19660,19670,19680,19690,19700,19710,19720,19730,19740,19750,19760,19770,19780,19790,19800,19810,19820,19830,19840,19850,19860,19870,19880,19890,19900,19910,19920,19930,19940,19950,19960,19970,19980,19990,20000,20010,20020,20030,20040,20050,20060,20070,20080,20090,20100,20110,20120,20130,20140,20150,20160,20170,20180,20190,20200,20210,20220,20230,20240,20250,20260,20270,20280,20290,20300,20310,20320,20330,20340,20350,20360,20370,20380,20390,20400,20410,20420,20430,20440,20450,20460,20470,20480,20490,20500,20510,20520,20530,20540,20550,20560,20570,20580,20590,20600,20610,20620,20630,20640,20650,20660,20670,20680,20690,20700,20710,20720,20730,20740,20750,20760,20770,20780,20790,20800,20810,20820,20830,20840,20850,20860,20870,20880,20890,20900,20910,20920,20930,20940,20950,20960,20970,20980,20990,21000,21010,21020,21030,21040,21050,21060,21070,21080,21090,21100,21110,21120,21130,21140,21150,21160,21170,21180,21190,21200,21210,21220,21230,21240,21250,21260,21270,21280,21290,21300,21310,21320,21330,21340,21350,21360,21370,21380,21390,21400,21410,21420,21430,21440,21450,21460,21470,21480,21490,21500,21510,21520,21530,21540,21550,21560,21570,21580,21590,21600,21610,21620,21630,21640,21650,21660,21670,21680,21690,21700,21710,21720,21730,21740,21750,21760,21770,21780,21790,21800,21810,21820,21830,21840,21850,21860,21870,21880,21890,21900,21910,21920,21930,21940,21950,21960,21970,21980,21990,22000,22010,22020,22030,22040,22050,22060,22070,22080,22090,22100,22110,22120,22130,22140,22150,22160,22170,22180,22190,22200,22210,22220,22230,22240,22250,22260,22270,22280,22290,22300,22310,22320,22330,22340,22350,22360,22370,22380,22390,22400,22410,22420,22430,22440,22450,22460,22470,22480,22490,22500,22510,22520,22530,22540,22550,22560,22570,22580,22590,22600,22610,22620,22630,22640,22650,22660,22670,22680,22690,22700,22710,22720,22730,22740,22750,22760,22770,22780,22790,22800,22810,22820,22830,22840,22850,22860,22870,22880,22890,22900,22910,22920,22930,22940,22950,22960,22970,22980,22990,23000,23010,23020,23030,23040,23050,23060,23070,23080,23090,23100,23110,23120,23130,23140,23150,23160,23170,23180,23190,23200,23210,23220,23230,23240,23250,23260,23270,23280,23290,23300,23310,23320,23330,23340,23350,23360,23370,23380,23390,23400,23410,23420,23430,23440,23450,23460,23470,23480,23490,23500,23510,23520,23530,23540,23550,23560,23570,23580,23590,23600,23610,23620,23630,23640,23650,23660,23670,23680,23690,23700,23710,23720,23730,23740,23750,23760,23770,23780,23790,23800,23810,23820,23830,23840,23850,23860,23870,23880,23890,23900,23910,23920,23930,23940,23950,23960,23970,23980,23990,24000,24010,24020,24030,24040,24050,24060,24070,24080,24090,24100,24110,24120,24130,24140,24150,24160,24170,24180,24190,24200,24210,24220,24230,24240,24250,24260,24270,24280,24290,24300,24310,24320,24330,24340,24350,24360,24370,24380,24390,24400,24410,24420,24430,24440,24450,24460,24470,24480,24490,24500,24510,24520,24530,24540,24550,24560,24570,24580,24590,24600,24610,24620,24630,24640,24650,24660,24670,24680,24690,24700,24710,24720,24730,24740,24750,24760,24770,24780,24790,24800,24810,24820,24830,24840,24850,24860,24870,24880,24890,24900,24910,24920,24930,24940,24950,24960,24970,24980,24990,25000,25010,25020,25030,25040,25050,25060,25070,25080,25090,25100,25110,25120,25130,25140,25150,25160,25170,25180,25190,25200,25210,25220,25230,25240,25250,25260,25270,25280,25290,25300,25310,25320,25330,25340,25350,25360,25370,25380,25390,25400,25410,25420,25430,25440,25450,25460,25470,25480,25490,25500,25510,25520,25530,25540,25550,25560,25570,25580,25590,25600,25610,25620,25630,25640,25650,25660,25670,25680,25690,25700,25710,25720,25730,25740,25750,25760,25770,25780,25790,25800,25810,25820,25830,25840,25850,25860,25870,25880,25890,25900,25910,25920,25930,25940,25950,25960,25970,25980,25990,26000,26010,26020,26030,26040,26050,26060,26070,26080,26090,26100,26110,26120,26130,26140,26150,26160,26170,26180,26190,26200,26210,26220,26230,26240,26250,26260,26270,26280,26290,26300,26310,26320,26330,26340,26350,26360,26370,26380,26390,26400,26410,26420,26430,26440,26450,26460,26470,26480,26490,26500,26510,26520,26530,26540,26550,26560,26570,26580,26590,26600,26610,26620,26630,26640,26650,26660,26670,26680,26690,26700,26710,26720,26730,26740,26750,26760,26770,26780,26790,26800,26810,26820,26830,26840,26850,26860,26870,26880,26890,26900,26910,26920,26930,26940,26950,26960,26970,26980,26990,27000,27010,27020,27030,27040,27050,27060,27070,27080,27090,27100,27110,27120,27130,27140,27150,27160,27170,27180,27190,27200,27210,27220,27230,27240,27250,27260,27270,27280,27290,27300,27310,27320,27330,27340,27350,27360,27370,27380,27390,27400,27410,27420,27430,27440,27450,27460,27470,27480,27490,27500,27510,27520,27530,27540,27550,27560,27570,27580,27590,27600,27610,27620,27630,27640,27650,27660,27670,27680,27690,27700,27710,27720,27730,27740,27750,27760,27770,27780,27790,27800,27810,27820,27830,27840,27850,27860,27870,27880,27890,27900,27910,27920,27930,27940,27950,27960,27970,27980,27990,28000,28010,28020,28030,28040,28050,28060,28070,28080,28090,28100,28110,28120,28130,28140,28150,28160,28170,28180,28190,28200,28210,28220,28230,28240,28250,28260,28270,28280,28290,28300,28310,28320,28330,28340,28350,28360,28370,28380,28390,28400,28410,28420,28430,28440,28450,28460,28470,28480,28490,28500,28510,28520,28530,28540,28550,28560,28570,28580,28590,28600,28610,28620,28630,28640,28650,28660,28670,28680,28690,28700,28710,28720,28730,28740,28750,28760,28770,28780,28790,28800,28810,28820,28830,28840,28850,28860,28870,28880,28890,28900,28910,28920,28930,28940,28950,28960,28970,28980,28990,29000,29010,29020,29030,29040,29050,29060,29070,29080,29090,29100,29110,29120,29130,29140,29150,29160,29170,29180,29190,29200,29210,29220,29230,29240,29250,29260,29270,29280,29290,29300,29310,29320,29330,29340,29350,29360,29370,29380,29390,29400,29410,29420,29430,29440,29450,29460,29470,29480,29490,29500,29510,29520,29530,29540,29550,29560,29570,29580,29590,29600,29610,29620,29630,29640,29650,29660,29670,29680,29690,29700,29710,29720,29730,29740,29750,29760,29770,29780,29790,29800,29810,29820,29830,29840,29850,29860,29870,29880,29890,29900,29910,29920,29930,29940,29950,29960,29970,29980,29990,30000};
	_paFrame_NextEvent = new frame[3001];
	for (int i = 0; i < 3001; i++) {
		_paFrame_NextEvent[i] = f[i];
	}
	
	orderActorToFactory(21047100, FormationPallas001a, "F001a_Pallas_1");
	orderActorToFactory(21057100, FormationPallas001d, "F001d_Pallas_2");
	orderActorToFactory(21067100, FormationPallas001b, "F001b_Pallas_3");
	orderActorToFactory(21077100, FormationPallas001c, "F001c_Pallas_4");
	orderActorToFactory(21087100, FormationPallas001a, "F001a_Pallas_5");
	orderActorToFactory(21097100, FormationPallas001d, "F001d_Pallas_6");
	orderActorToFactory(21107100, FormationPallas001b, "F001b_Pallas_7");
	orderActorToFactory(21117100, FormationPallas001c, "F001c_Pallas_8");
	orderActorToFactory(21127100, FormationPallas001a, "F001a_Pallas_9");
	orderActorToFactory(21137100, FormationPallas001d, "F001d_Pallas_10");
	orderActorToFactory(21147100, FormationPallas001b, "F001b_Pallas_11");
	orderActorToFactory(21157100, FormationPallas001c, "F001c_Pallas_12");
	orderActorToFactory(21177100, EnemyMetis, "Metis_13");
	orderActorToFactory(21177110, EnemyMetis, "Metis_14");
	orderActorToFactory(21177120, EnemyMetis, "Metis_15");
	orderActorToFactory(21177130, EnemyMetis, "Metis_16");
	orderActorToFactory(21177140, EnemyMetis, "Metis_17");
	orderActorToFactory(21177150, EnemyMetis, "Metis_18");
	orderActorToFactory(21177160, EnemyMetis, "Metis_19");
	orderActorToFactory(21177170, EnemyMetis, "Metis_20");
	orderActorToFactory(21177180, EnemyMetis, "Metis_21");
	orderActorToFactory(21177190, EnemyMetis, "Metis_22");
	orderActorToFactory(21177200, EnemyMetis, "Metis_23");
	orderActorToFactory(21177210, EnemyMetis, "Metis_24");
	orderActorToFactory(21177220, EnemyMetis, "Metis_25");
	orderActorToFactory(21177230, EnemyMetis, "Metis_26");
	orderActorToFactory(21177240, EnemyMetis, "Metis_27");
	orderActorToFactory(21177250, EnemyMetis, "Metis_28");
	orderActorToFactory(21177260, EnemyMetis, "Metis_29");
	orderActorToFactory(21177270, EnemyMetis, "Metis_30");
	orderActorToFactory(21177280, EnemyMetis, "Metis_31");
	orderActorToFactory(21177290, EnemyMetis, "Metis_32");
	orderActorToFactory(21177300, EnemyMetis, "Metis_33");
	orderActorToFactory(21177310, EnemyMetis, "Metis_34");
	orderActorToFactory(21177320, EnemyMetis, "Metis_35");
	orderActorToFactory(21177330, EnemyMetis, "Metis_36");
	orderActorToFactory(21177340, EnemyMetis, "Metis_37");
	orderActorToFactory(21177350, EnemyMetis, "Metis_38");
	orderActorToFactory(21177360, EnemyMetis, "Metis_39");
	orderActorToFactory(21177370, EnemyMetis, "Metis_40");
	orderActorToFactory(21177380, EnemyMetis, "Metis_41");
	orderActorToFactory(21177390, EnemyMetis, "Metis_42");
	orderActorToFactory(21177400, EnemyMetis, "Metis_43");
	orderActorToFactory(21177410, EnemyMetis, "Metis_44");
	orderActorToFactory(21177420, EnemyMetis, "Metis_45");
	orderActorToFactory(21177430, EnemyMetis, "Metis_46");
	orderActorToFactory(21177440, EnemyMetis, "Metis_47");
	orderActorToFactory(21177450, EnemyMetis, "Metis_48");
	orderActorToFactory(21177460, EnemyMetis, "Metis_49");
	orderActorToFactory(21177470, EnemyMetis, "Metis_50");
	orderActorToFactory(21177480, EnemyMetis, "Metis_51");
	orderActorToFactory(21177490, EnemyMetis, "Metis_52");
	orderActorToFactory(21177500, EnemyMetis, "Metis_53");
	orderActorToFactory(21177510, EnemyMetis, "Metis_54");
	orderActorToFactory(21177520, EnemyMetis, "Metis_55");
	orderActorToFactory(21177530, EnemyMetis, "Metis_56");
	orderActorToFactory(21177540, EnemyMetis, "Metis_57");
	orderActorToFactory(21177550, EnemyMetis, "Metis_58");
	orderActorToFactory(21177560, EnemyMetis, "Metis_59");
	orderActorToFactory(21177570, EnemyMetis, "Metis_60");
	orderActorToFactory(21177580, EnemyMetis, "Metis_61");
	orderActorToFactory(21177590, EnemyMetis, "Metis_62");
	orderActorToFactory(21177600, EnemyMetis, "Metis_63");
	orderActorToFactory(21177610, EnemyMetis, "Metis_64");
	orderActorToFactory(21177620, EnemyMetis, "Metis_65");
	orderActorToFactory(21177630, EnemyMetis, "Metis_66");
	orderActorToFactory(21177640, EnemyMetis, "Metis_67");
	orderActorToFactory(21177650, EnemyMetis, "Metis_68");
	orderActorToFactory(21177660, EnemyMetis, "Metis_69");
	orderActorToFactory(21177670, EnemyMetis, "Metis_70");
	orderActorToFactory(21177680, EnemyMetis, "Metis_71");
	orderActorToFactory(21177690, EnemyMetis, "Metis_72");
	orderActorToFactory(21177700, EnemyMetis, "Metis_73");
	orderActorToFactory(21177710, EnemyMetis, "Metis_74");
	orderActorToFactory(21177720, EnemyMetis, "Metis_75");
	orderActorToFactory(21177730, EnemyMetis, "Metis_76");
	orderActorToFactory(21177740, EnemyMetis, "Metis_77");
	orderActorToFactory(21177750, EnemyMetis, "Metis_78");
	orderActorToFactory(21177760, EnemyMetis, "Metis_79");
	orderActorToFactory(21177770, EnemyMetis, "Metis_80");
	orderActorToFactory(21177780, EnemyMetis, "Metis_81");
	orderActorToFactory(21177790, EnemyMetis, "Metis_82");
	orderActorToFactory(21177800, EnemyMetis, "Metis_83");
	orderActorToFactory(21177810, EnemyMetis, "Metis_84");
	orderActorToFactory(21177820, EnemyMetis, "Metis_85");
	orderActorToFactory(21177830, EnemyMetis, "Metis_86");
	orderActorToFactory(21177840, EnemyMetis, "Metis_87");
	orderActorToFactory(21177850, EnemyMetis, "Metis_88");
	orderActorToFactory(21177860, EnemyMetis, "Metis_89");
	orderActorToFactory(21177870, EnemyMetis, "Metis_90");
	orderActorToFactory(21177880, EnemyMetis, "Metis_91");
	orderActorToFactory(21177890, EnemyMetis, "Metis_92");
	orderActorToFactory(21177900, EnemyMetis, "Metis_93");
	orderActorToFactory(21177910, EnemyMetis, "Metis_94");
	orderActorToFactory(21177920, EnemyMetis, "Metis_95");
	orderActorToFactory(21177930, EnemyMetis, "Metis_96");
	orderActorToFactory(21177940, EnemyMetis, "Metis_97");
	orderActorToFactory(21177950, EnemyMetis, "Metis_98");
	orderActorToFactory(21177960, EnemyMetis, "Metis_99");
	orderActorToFactory(21177970, EnemyMetis, "Metis_100");
	orderActorToFactory(21177980, EnemyMetis, "Metis_101");
	orderActorToFactory(21177990, EnemyMetis, "Metis_102");
	orderActorToFactory(211771000, EnemyMetis, "Metis_103");
	orderActorToFactory(211771010, EnemyMetis, "Metis_104");
	orderActorToFactory(211771020, EnemyMetis, "Metis_105");
	orderActorToFactory(211771030, EnemyMetis, "Metis_106");
	orderActorToFactory(211771040, EnemyMetis, "Metis_107");
	orderActorToFactory(211771050, EnemyMetis, "Metis_108");
	orderActorToFactory(211771060, EnemyMetis, "Metis_109");
	orderActorToFactory(211771070, EnemyMetis, "Metis_110");
	orderActorToFactory(211771080, EnemyMetis, "Metis_111");
	orderActorToFactory(211771090, EnemyMetis, "Metis_112");
	orderActorToFactory(211771100, EnemyMetis, "Metis_113");
	orderActorToFactory(211771110, EnemyMetis, "Metis_114");
	orderActorToFactory(211771120, EnemyMetis, "Metis_115");
	orderActorToFactory(211771130, EnemyMetis, "Metis_116");
	orderActorToFactory(211771140, EnemyMetis, "Metis_117");
	orderActorToFactory(211771150, EnemyMetis, "Metis_118");
	orderActorToFactory(211771160, EnemyMetis, "Metis_119");
	orderActorToFactory(211771170, EnemyMetis, "Metis_120");
	orderActorToFactory(211771180, EnemyMetis, "Metis_121");
	orderActorToFactory(211771190, EnemyMetis, "Metis_122");
	orderActorToFactory(211771200, EnemyMetis, "Metis_123");
	orderActorToFactory(211771210, EnemyMetis, "Metis_124");
	orderActorToFactory(211771220, EnemyMetis, "Metis_125");
	orderActorToFactory(211771230, EnemyMetis, "Metis_126");
	orderActorToFactory(211771240, EnemyMetis, "Metis_127");
	orderActorToFactory(211771250, EnemyMetis, "Metis_128");
	orderActorToFactory(211771260, EnemyMetis, "Metis_129");
	orderActorToFactory(211771270, EnemyMetis, "Metis_130");
	orderActorToFactory(211771280, EnemyMetis, "Metis_131");
	orderActorToFactory(211771290, EnemyMetis, "Metis_132");
	orderActorToFactory(211771300, EnemyMetis, "Metis_133");
	orderActorToFactory(211771310, EnemyMetis, "Metis_134");
	orderActorToFactory(211771320, EnemyMetis, "Metis_135");
	orderActorToFactory(211771330, EnemyMetis, "Metis_136");
	orderActorToFactory(211771340, EnemyMetis, "Metis_137");
	orderActorToFactory(211771350, EnemyMetis, "Metis_138");
	orderActorToFactory(211771360, EnemyMetis, "Metis_139");
	orderActorToFactory(211771370, EnemyMetis, "Metis_140");
	orderActorToFactory(211771380, EnemyMetis, "Metis_141");
	orderActorToFactory(211771390, EnemyMetis, "Metis_142");
	orderActorToFactory(211771400, EnemyMetis, "Metis_143");
	orderActorToFactory(211771410, EnemyMetis, "Metis_144");
	orderActorToFactory(211771420, EnemyMetis, "Metis_145");
	orderActorToFactory(211771430, EnemyMetis, "Metis_146");
	orderActorToFactory(211771440, EnemyMetis, "Metis_147");
	orderActorToFactory(211771450, EnemyMetis, "Metis_148");
	orderActorToFactory(211771460, EnemyMetis, "Metis_149");
	orderActorToFactory(211771470, EnemyMetis, "Metis_150");
	orderActorToFactory(211771480, EnemyMetis, "Metis_151");
	orderActorToFactory(211771490, EnemyMetis, "Metis_152");
	orderActorToFactory(211771500, EnemyMetis, "Metis_153");
	orderActorToFactory(211771510, EnemyMetis, "Metis_154");
	orderActorToFactory(211771520, EnemyMetis, "Metis_155");
	orderActorToFactory(211771530, EnemyMetis, "Metis_156");
	orderActorToFactory(211771540, EnemyMetis, "Metis_157");
	orderActorToFactory(211771550, EnemyMetis, "Metis_158");
	orderActorToFactory(211771560, EnemyMetis, "Metis_159");
	orderActorToFactory(211771570, EnemyMetis, "Metis_160");
	orderActorToFactory(211771580, EnemyMetis, "Metis_161");
	orderActorToFactory(211771590, EnemyMetis, "Metis_162");
	orderActorToFactory(211771600, EnemyMetis, "Metis_163");
	orderActorToFactory(211771610, EnemyMetis, "Metis_164");
	orderActorToFactory(211771620, EnemyMetis, "Metis_165");
	orderActorToFactory(211771630, EnemyMetis, "Metis_166");
	orderActorToFactory(211771640, EnemyMetis, "Metis_167");
	orderActorToFactory(211771650, EnemyMetis, "Metis_168");
	orderActorToFactory(211771660, EnemyMetis, "Metis_169");
	orderActorToFactory(211771670, EnemyMetis, "Metis_170");
	orderActorToFactory(211771680, EnemyMetis, "Metis_171");
	orderActorToFactory(211771690, EnemyMetis, "Metis_172");
	orderActorToFactory(211771700, EnemyMetis, "Metis_173");
	orderActorToFactory(211771710, EnemyMetis, "Metis_174");
	orderActorToFactory(211771720, EnemyMetis, "Metis_175");
	orderActorToFactory(211771730, EnemyMetis, "Metis_176");
	orderActorToFactory(211771740, EnemyMetis, "Metis_177");
	orderActorToFactory(211771750, EnemyMetis, "Metis_178");
	orderActorToFactory(211771760, EnemyMetis, "Metis_179");
	orderActorToFactory(211771770, EnemyMetis, "Metis_180");
	orderActorToFactory(211771780, EnemyMetis, "Metis_181");
	orderActorToFactory(211771790, EnemyMetis, "Metis_182");
	orderActorToFactory(211771800, EnemyMetis, "Metis_183");
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
			case 10:
				orderActorToFactory(211771810, EnemyMetis, "Metis_184");
				break;
			case 20:
				orderActorToFactory(211771820, EnemyMetis, "Metis_185");
				break;
			case 30:
				orderActorToFactory(211771830, EnemyMetis, "Metis_186");
				break;
			case 40:
				orderActorToFactory(211771840, EnemyMetis, "Metis_187");
				break;
			case 50:
				orderActorToFactory(211771850, EnemyMetis, "Metis_188");
				break;
			case 60:
				orderActorToFactory(211771860, EnemyMetis, "Metis_189");
				break;
			case 70:
				orderActorToFactory(211771870, EnemyMetis, "Metis_190");
				break;
			case 80:
				orderActorToFactory(211771880, EnemyMetis, "Metis_191");
				break;
			case 90:
				orderActorToFactory(211771890, EnemyMetis, "Metis_192");
				break;
			case 100:
				{
				ActorTableScene* ta = NEW ActorTableScene("TableScene_193");
				ta->setMaxPerformFrame(2000);
				addSubLast(ta);
				ta->addToTable(((FormationPallas001a*)obtainActorFromFactory(21047100)), 1);
				ta->addToTable(((FormationPallas001d*)obtainActorFromFactory(21057100)), 1);
				ta->addToTable(((FormationPallas001b*)obtainActorFromFactory(21067100)), 1);
				ta->addToTable(((FormationPallas001c*)obtainActorFromFactory(21077100)), 400);
				ta->addToTable(((FormationPallas001a*)obtainActorFromFactory(21087100)), 1);
				ta->addToTable(((FormationPallas001d*)obtainActorFromFactory(21097100)), 1);
				ta->addToTable(((FormationPallas001b*)obtainActorFromFactory(21107100)), 1);
				ta->addToTable(((FormationPallas001c*)obtainActorFromFactory(21117100)), 400);
				ta->addToTable(((FormationPallas001a*)obtainActorFromFactory(21127100)), 1);
				ta->addToTable(((FormationPallas001d*)obtainActorFromFactory(21137100)), 1);
				ta->addToTable(((FormationPallas001b*)obtainActorFromFactory(21147100)), 1);
				ta->addToTable(((FormationPallas001c*)obtainActorFromFactory(21157100)), 400);
				}
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177100);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211771900, EnemyMetis, "Metis_194");
				break;
			case 110:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177110);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211771910, EnemyMetis, "Metis_195");
				break;
			case 120:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177120);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211771920, EnemyMetis, "Metis_196");
				break;
			case 130:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177130);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211771930, EnemyMetis, "Metis_197");
				break;
			case 140:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177140);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211771940, EnemyMetis, "Metis_198");
				break;
			case 150:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177150);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211771950, EnemyMetis, "Metis_199");
				break;
			case 160:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177160);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211771960, EnemyMetis, "Metis_200");
				break;
			case 170:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177170);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211771970, EnemyMetis, "Metis_201");
				break;
			case 180:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177180);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211771980, EnemyMetis, "Metis_202");
				break;
			case 190:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177190);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211771990, EnemyMetis, "Metis_203");
				break;
			case 200:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177200);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772000, EnemyMetis, "Metis_204");
				break;
			case 210:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177210);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772010, EnemyMetis, "Metis_205");
				break;
			case 220:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177220);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772020, EnemyMetis, "Metis_206");
				break;
			case 230:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177230);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772030, EnemyMetis, "Metis_207");
				break;
			case 240:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177240);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772040, EnemyMetis, "Metis_208");
				break;
			case 250:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177250);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772050, EnemyMetis, "Metis_209");
				break;
			case 260:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177260);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772060, EnemyMetis, "Metis_210");
				break;
			case 270:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177270);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772070, EnemyMetis, "Metis_211");
				break;
			case 280:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177280);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772080, EnemyMetis, "Metis_212");
				break;
			case 290:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177290);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772090, EnemyMetis, "Metis_213");
				break;
			case 300:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177300);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772100, EnemyMetis, "Metis_214");
				break;
			case 310:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177310);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772110, EnemyMetis, "Metis_215");
				break;
			case 320:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177320);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772120, EnemyMetis, "Metis_216");
				break;
			case 330:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177330);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772130, EnemyMetis, "Metis_217");
				break;
			case 340:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177340);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772140, EnemyMetis, "Metis_218");
				break;
			case 350:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177350);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772150, EnemyMetis, "Metis_219");
				break;
			case 360:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177360);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772160, EnemyMetis, "Metis_220");
				break;
			case 370:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177370);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772170, EnemyMetis, "Metis_221");
				break;
			case 380:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177380);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772180, EnemyMetis, "Metis_222");
				break;
			case 390:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177390);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772190, EnemyMetis, "Metis_223");
				break;
			case 400:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177400);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772200, EnemyMetis, "Metis_224");
				break;
			case 410:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177410);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772210, EnemyMetis, "Metis_225");
				break;
			case 420:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177420);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772220, EnemyMetis, "Metis_226");
				break;
			case 430:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177430);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772230, EnemyMetis, "Metis_227");
				break;
			case 440:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177440);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772240, EnemyMetis, "Metis_228");
				break;
			case 450:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177450);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772250, EnemyMetis, "Metis_229");
				break;
			case 460:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177460);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772260, EnemyMetis, "Metis_230");
				break;
			case 470:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177470);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772270, EnemyMetis, "Metis_231");
				break;
			case 480:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177480);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772280, EnemyMetis, "Metis_232");
				break;
			case 490:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177490);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772290, EnemyMetis, "Metis_233");
				break;
			case 500:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177500);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772300, EnemyMetis, "Metis_234");
				break;
			case 510:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177510);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772310, EnemyMetis, "Metis_235");
				break;
			case 520:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177520);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772320, EnemyMetis, "Metis_236");
				break;
			case 530:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177530);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772330, EnemyMetis, "Metis_237");
				break;
			case 540:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177540);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772340, EnemyMetis, "Metis_238");
				break;
			case 550:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177550);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772350, EnemyMetis, "Metis_239");
				break;
			case 560:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177560);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772360, EnemyMetis, "Metis_240");
				break;
			case 570:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177570);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772370, EnemyMetis, "Metis_241");
				break;
			case 580:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177580);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772380, EnemyMetis, "Metis_242");
				break;
			case 590:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177590);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772390, EnemyMetis, "Metis_243");
				break;
			case 600:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177600);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772400, EnemyMetis, "Metis_244");
				break;
			case 610:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177610);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772410, EnemyMetis, "Metis_245");
				break;
			case 620:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177620);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772420, EnemyMetis, "Metis_246");
				break;
			case 630:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177630);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772430, EnemyMetis, "Metis_247");
				break;
			case 640:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177640);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772440, EnemyMetis, "Metis_248");
				break;
			case 650:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177650);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772450, EnemyMetis, "Metis_249");
				break;
			case 660:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177660);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772460, EnemyMetis, "Metis_250");
				break;
			case 670:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177670);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772470, EnemyMetis, "Metis_251");
				break;
			case 680:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177680);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772480, EnemyMetis, "Metis_252");
				break;
			case 690:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177690);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772490, EnemyMetis, "Metis_253");
				break;
			case 700:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177700);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772500, EnemyMetis, "Metis_254");
				break;
			case 710:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177710);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772510, EnemyMetis, "Metis_255");
				break;
			case 720:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177720);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772520, EnemyMetis, "Metis_256");
				break;
			case 730:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177730);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772530, EnemyMetis, "Metis_257");
				break;
			case 740:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177740);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772540, EnemyMetis, "Metis_258");
				break;
			case 750:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177750);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772550, EnemyMetis, "Metis_259");
				break;
			case 760:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177760);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772560, EnemyMetis, "Metis_260");
				break;
			case 770:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177770);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772570, EnemyMetis, "Metis_261");
				break;
			case 780:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177780);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772580, EnemyMetis, "Metis_262");
				break;
			case 790:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177790);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772590, EnemyMetis, "Metis_263");
				break;
			case 800:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177800);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772600, EnemyMetis, "Metis_264");
				break;
			case 810:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177810);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772610, EnemyMetis, "Metis_265");
				break;
			case 820:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177820);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772620, EnemyMetis, "Metis_266");
				break;
			case 830:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177830);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772630, EnemyMetis, "Metis_267");
				break;
			case 840:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177840);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772640, EnemyMetis, "Metis_268");
				break;
			case 850:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177850);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772650, EnemyMetis, "Metis_269");
				break;
			case 860:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177860);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772660, EnemyMetis, "Metis_270");
				break;
			case 870:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177870);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772670, EnemyMetis, "Metis_271");
				break;
			case 880:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177880);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772680, EnemyMetis, "Metis_272");
				break;
			case 890:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177890);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772690, EnemyMetis, "Metis_273");
				break;
			case 900:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177900);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772700, EnemyMetis, "Metis_274");
				break;
			case 910:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177910);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772710, EnemyMetis, "Metis_275");
				break;
			case 920:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177920);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772720, EnemyMetis, "Metis_276");
				break;
			case 930:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177930);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772730, EnemyMetis, "Metis_277");
				break;
			case 940:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177940);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772740, EnemyMetis, "Metis_278");
				break;
			case 950:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177950);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772750, EnemyMetis, "Metis_279");
				break;
			case 960:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177960);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772760, EnemyMetis, "Metis_280");
				break;
			case 970:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177970);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772770, EnemyMetis, "Metis_281");
				break;
			case 980:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177980);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772780, EnemyMetis, "Metis_282");
				break;
			case 990:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177990);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772790, EnemyMetis, "Metis_283");
				break;
			case 1000:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771000);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772800, EnemyMetis, "Metis_284");
				break;
			case 1010:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771010);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772810, EnemyMetis, "Metis_285");
				break;
			case 1020:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771020);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772820, EnemyMetis, "Metis_286");
				break;
			case 1030:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771030);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772830, EnemyMetis, "Metis_287");
				break;
			case 1040:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771040);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772840, EnemyMetis, "Metis_288");
				break;
			case 1050:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771050);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772850, EnemyMetis, "Metis_289");
				break;
			case 1060:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771060);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772860, EnemyMetis, "Metis_290");
				break;
			case 1070:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771070);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772870, EnemyMetis, "Metis_291");
				break;
			case 1080:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771080);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772880, EnemyMetis, "Metis_292");
				break;
			case 1090:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771090);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772890, EnemyMetis, "Metis_293");
				break;
			case 1100:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771100);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772900, EnemyMetis, "Metis_294");
				break;
			case 1110:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771110);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772910, EnemyMetis, "Metis_295");
				break;
			case 1120:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771120);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772920, EnemyMetis, "Metis_296");
				break;
			case 1130:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771130);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772930, EnemyMetis, "Metis_297");
				break;
			case 1140:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771140);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772940, EnemyMetis, "Metis_298");
				break;
			case 1150:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771150);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772950, EnemyMetis, "Metis_299");
				break;
			case 1160:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771160);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772960, EnemyMetis, "Metis_300");
				break;
			case 1170:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771170);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772970, EnemyMetis, "Metis_301");
				break;
			case 1180:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771180);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772980, EnemyMetis, "Metis_302");
				break;
			case 1190:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771190);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772990, EnemyMetis, "Metis_303");
				break;
			case 1200:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771200);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773000, EnemyMetis, "Metis_304");
				break;
			case 1210:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771210);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773010, EnemyMetis, "Metis_305");
				break;
			case 1220:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771220);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773020, EnemyMetis, "Metis_306");
				break;
			case 1230:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771230);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773030, EnemyMetis, "Metis_307");
				break;
			case 1240:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771240);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773040, EnemyMetis, "Metis_308");
				break;
			case 1250:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771250);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773050, EnemyMetis, "Metis_309");
				break;
			case 1260:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771260);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773060, EnemyMetis, "Metis_310");
				break;
			case 1270:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771270);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773070, EnemyMetis, "Metis_311");
				break;
			case 1280:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771280);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773080, EnemyMetis, "Metis_312");
				break;
			case 1290:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771290);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773090, EnemyMetis, "Metis_313");
				break;
			case 1300:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771300);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773100, EnemyMetis, "Metis_314");
				break;
			case 1310:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771310);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773110, EnemyMetis, "Metis_315");
				break;
			case 1320:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771320);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773120, EnemyMetis, "Metis_316");
				break;
			case 1330:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771330);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773130, EnemyMetis, "Metis_317");
				break;
			case 1340:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771340);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773140, EnemyMetis, "Metis_318");
				break;
			case 1350:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771350);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773150, EnemyMetis, "Metis_319");
				break;
			case 1360:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771360);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773160, EnemyMetis, "Metis_320");
				break;
			case 1370:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771370);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773170, EnemyMetis, "Metis_321");
				break;
			case 1380:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771380);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773180, EnemyMetis, "Metis_322");
				break;
			case 1390:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771390);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773190, EnemyMetis, "Metis_323");
				break;
			case 1400:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771400);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773200, EnemyMetis, "Metis_324");
				break;
			case 1410:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771410);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773210, EnemyMetis, "Metis_325");
				break;
			case 1420:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771420);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773220, EnemyMetis, "Metis_326");
				break;
			case 1430:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771430);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773230, EnemyMetis, "Metis_327");
				break;
			case 1440:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771440);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773240, EnemyMetis, "Metis_328");
				break;
			case 1450:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771450);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773250, EnemyMetis, "Metis_329");
				break;
			case 1460:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771460);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773260, EnemyMetis, "Metis_330");
				break;
			case 1470:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771470);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773270, EnemyMetis, "Metis_331");
				break;
			case 1480:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771480);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773280, EnemyMetis, "Metis_332");
				break;
			case 1490:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771490);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773290, EnemyMetis, "Metis_333");
				break;
			case 1500:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771500);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773300, EnemyMetis, "Metis_334");
				break;
			case 1510:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771510);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773310, EnemyMetis, "Metis_335");
				break;
			case 1520:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771520);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773320, EnemyMetis, "Metis_336");
				break;
			case 1530:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771530);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773330, EnemyMetis, "Metis_337");
				break;
			case 1540:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771540);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773340, EnemyMetis, "Metis_338");
				break;
			case 1550:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771550);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773350, EnemyMetis, "Metis_339");
				break;
			case 1560:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771560);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773360, EnemyMetis, "Metis_340");
				break;
			case 1570:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771570);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773370, EnemyMetis, "Metis_341");
				break;
			case 1580:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771580);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773380, EnemyMetis, "Metis_342");
				break;
			case 1590:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771590);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773390, EnemyMetis, "Metis_343");
				break;
			case 1600:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771600);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773400, EnemyMetis, "Metis_344");
				break;
			case 1610:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771610);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773410, EnemyMetis, "Metis_345");
				break;
			case 1620:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771620);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773420, EnemyMetis, "Metis_346");
				break;
			case 1630:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771630);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773430, EnemyMetis, "Metis_347");
				break;
			case 1640:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771640);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773440, EnemyMetis, "Metis_348");
				break;
			case 1650:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771650);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773450, EnemyMetis, "Metis_349");
				break;
			case 1660:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771660);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773460, EnemyMetis, "Metis_350");
				break;
			case 1670:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771670);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773470, EnemyMetis, "Metis_351");
				break;
			case 1680:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771680);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773480, EnemyMetis, "Metis_352");
				break;
			case 1690:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771690);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773490, EnemyMetis, "Metis_353");
				break;
			case 1700:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771700);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773500, EnemyMetis, "Metis_354");
				break;
			case 1710:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771710);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773510, EnemyMetis, "Metis_355");
				break;
			case 1720:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771720);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773520, EnemyMetis, "Metis_356");
				break;
			case 1730:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771730);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773530, EnemyMetis, "Metis_357");
				break;
			case 1740:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771740);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773540, EnemyMetis, "Metis_358");
				break;
			case 1750:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771750);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773550, EnemyMetis, "Metis_359");
				break;
			case 1760:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771760);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773560, EnemyMetis, "Metis_360");
				break;
			case 1770:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771770);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773570, EnemyMetis, "Metis_361");
				break;
			case 1780:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771780);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773580, EnemyMetis, "Metis_362");
				break;
			case 1790:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771790);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773590, EnemyMetis, "Metis_363");
				break;
			case 1800:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771800);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773600, EnemyMetis, "Metis_364");
				break;
			case 1810:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771810);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773610, EnemyMetis, "Metis_365");
				break;
			case 1820:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771820);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773620, EnemyMetis, "Metis_366");
				break;
			case 1830:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771830);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773630, EnemyMetis, "Metis_367");
				break;
			case 1840:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771840);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773640, EnemyMetis, "Metis_368");
				break;
			case 1850:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771850);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773650, EnemyMetis, "Metis_369");
				break;
			case 1860:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771860);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773660, EnemyMetis, "Metis_370");
				break;
			case 1870:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771870);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773670, EnemyMetis, "Metis_371");
				break;
			case 1880:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771880);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773680, EnemyMetis, "Metis_372");
				break;
			case 1890:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771890);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773690, EnemyMetis, "Metis_373");
				break;
			case 1900:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771900);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773700, EnemyMetis, "Metis_374");
				break;
			case 1910:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771910);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773710, EnemyMetis, "Metis_375");
				break;
			case 1920:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771920);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773720, EnemyMetis, "Metis_376");
				break;
			case 1930:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771930);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773730, EnemyMetis, "Metis_377");
				break;
			case 1940:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771940);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773740, EnemyMetis, "Metis_378");
				break;
			case 1950:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771950);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773750, EnemyMetis, "Metis_379");
				break;
			case 1960:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771960);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773760, EnemyMetis, "Metis_380");
				break;
			case 1970:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771970);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773770, EnemyMetis, "Metis_381");
				break;
			case 1980:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771980);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773780, EnemyMetis, "Metis_382");
				break;
			case 1990:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771990);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773790, EnemyMetis, "Metis_383");
				break;
			case 2000:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772000);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773800, EnemyMetis, "Metis_384");
				break;
			case 2010:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772010);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773810, EnemyMetis, "Metis_385");
				break;
			case 2020:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772020);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773820, EnemyMetis, "Metis_386");
				break;
			case 2030:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772030);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773830, EnemyMetis, "Metis_387");
				break;
			case 2040:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772040);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773840, EnemyMetis, "Metis_388");
				break;
			case 2050:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772050);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773850, EnemyMetis, "Metis_389");
				break;
			case 2060:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772060);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773860, EnemyMetis, "Metis_390");
				break;
			case 2070:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772070);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773870, EnemyMetis, "Metis_391");
				break;
			case 2080:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772080);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773880, EnemyMetis, "Metis_392");
				break;
			case 2090:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772090);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773890, EnemyMetis, "Metis_393");
				break;
			case 2100:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772100);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773900, EnemyMetis, "Metis_394");
				break;
			case 2110:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772110);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773910, EnemyMetis, "Metis_395");
				break;
			case 2120:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772120);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773920, EnemyMetis, "Metis_396");
				break;
			case 2130:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772130);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773930, EnemyMetis, "Metis_397");
				break;
			case 2140:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772140);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773940, EnemyMetis, "Metis_398");
				break;
			case 2150:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772150);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773950, EnemyMetis, "Metis_399");
				break;
			case 2160:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772160);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773960, EnemyMetis, "Metis_400");
				break;
			case 2170:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772170);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773970, EnemyMetis, "Metis_401");
				break;
			case 2180:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772180);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773980, EnemyMetis, "Metis_402");
				break;
			case 2190:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772190);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773990, EnemyMetis, "Metis_403");
				break;
			case 2200:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772200);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774000, EnemyMetis, "Metis_404");
				break;
			case 2210:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772210);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774010, EnemyMetis, "Metis_405");
				break;
			case 2220:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772220);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774020, EnemyMetis, "Metis_406");
				break;
			case 2230:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772230);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774030, EnemyMetis, "Metis_407");
				break;
			case 2240:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772240);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774040, EnemyMetis, "Metis_408");
				break;
			case 2250:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772250);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774050, EnemyMetis, "Metis_409");
				break;
			case 2260:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772260);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774060, EnemyMetis, "Metis_410");
				break;
			case 2270:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772270);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774070, EnemyMetis, "Metis_411");
				break;
			case 2280:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772280);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774080, EnemyMetis, "Metis_412");
				break;
			case 2290:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772290);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774090, EnemyMetis, "Metis_413");
				break;
			case 2300:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772300);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774100, EnemyMetis, "Metis_414");
				break;
			case 2310:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772310);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774110, EnemyMetis, "Metis_415");
				break;
			case 2320:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772320);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774120, EnemyMetis, "Metis_416");
				break;
			case 2330:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772330);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774130, EnemyMetis, "Metis_417");
				break;
			case 2340:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772340);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774140, EnemyMetis, "Metis_418");
				break;
			case 2350:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772350);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774150, EnemyMetis, "Metis_419");
				break;
			case 2360:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772360);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774160, EnemyMetis, "Metis_420");
				break;
			case 2370:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772370);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774170, EnemyMetis, "Metis_421");
				break;
			case 2380:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772380);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774180, EnemyMetis, "Metis_422");
				break;
			case 2390:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772390);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774190, EnemyMetis, "Metis_423");
				break;
			case 2400:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772400);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774200, EnemyMetis, "Metis_424");
				break;
			case 2410:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772410);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774210, EnemyMetis, "Metis_425");
				break;
			case 2420:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772420);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774220, EnemyMetis, "Metis_426");
				break;
			case 2430:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772430);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774230, EnemyMetis, "Metis_427");
				break;
			case 2440:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772440);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774240, EnemyMetis, "Metis_428");
				break;
			case 2450:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772450);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774250, EnemyMetis, "Metis_429");
				break;
			case 2460:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772460);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774260, EnemyMetis, "Metis_430");
				break;
			case 2470:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772470);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774270, EnemyMetis, "Metis_431");
				break;
			case 2480:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772480);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774280, EnemyMetis, "Metis_432");
				break;
			case 2490:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772490);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774290, EnemyMetis, "Metis_433");
				break;
			case 2500:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772500);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774300, EnemyMetis, "Metis_434");
				break;
			case 2510:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772510);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774310, EnemyMetis, "Metis_435");
				break;
			case 2520:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772520);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774320, EnemyMetis, "Metis_436");
				break;
			case 2530:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772530);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774330, EnemyMetis, "Metis_437");
				break;
			case 2540:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772540);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774340, EnemyMetis, "Metis_438");
				break;
			case 2550:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772550);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774350, EnemyMetis, "Metis_439");
				break;
			case 2560:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772560);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774360, EnemyMetis, "Metis_440");
				break;
			case 2570:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772570);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774370, EnemyMetis, "Metis_441");
				break;
			case 2580:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772580);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774380, EnemyMetis, "Metis_442");
				break;
			case 2590:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772590);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774390, EnemyMetis, "Metis_443");
				break;
			case 2600:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772600);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774400, EnemyMetis, "Metis_444");
				break;
			case 2610:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772610);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774410, EnemyMetis, "Metis_445");
				break;
			case 2620:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772620);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774420, EnemyMetis, "Metis_446");
				break;
			case 2630:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772630);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774430, EnemyMetis, "Metis_447");
				break;
			case 2640:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772640);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774440, EnemyMetis, "Metis_448");
				break;
			case 2650:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772650);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774450, EnemyMetis, "Metis_449");
				break;
			case 2660:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772660);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774460, EnemyMetis, "Metis_450");
				break;
			case 2670:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772670);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774470, EnemyMetis, "Metis_451");
				break;
			case 2680:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772680);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774480, EnemyMetis, "Metis_452");
				break;
			case 2690:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772690);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774490, EnemyMetis, "Metis_453");
				break;
			case 2700:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772700);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774500, EnemyMetis, "Metis_454");
				break;
			case 2710:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772710);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774510, EnemyMetis, "Metis_455");
				break;
			case 2720:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772720);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774520, EnemyMetis, "Metis_456");
				break;
			case 2730:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772730);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774530, EnemyMetis, "Metis_457");
				break;
			case 2740:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772740);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774540, EnemyMetis, "Metis_458");
				break;
			case 2750:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772750);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774550, EnemyMetis, "Metis_459");
				break;
			case 2760:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772760);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774560, EnemyMetis, "Metis_460");
				break;
			case 2770:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772770);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774570, EnemyMetis, "Metis_461");
				break;
			case 2780:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772780);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774580, EnemyMetis, "Metis_462");
				break;
			case 2790:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772790);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774590, EnemyMetis, "Metis_463");
				break;
			case 2800:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772800);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774600, EnemyMetis, "Metis_464");
				break;
			case 2810:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772810);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774610, EnemyMetis, "Metis_465");
				break;
			case 2820:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772820);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774620, EnemyMetis, "Metis_466");
				break;
			case 2830:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772830);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774630, EnemyMetis, "Metis_467");
				break;
			case 2840:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772840);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774640, EnemyMetis, "Metis_468");
				break;
			case 2850:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772850);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774650, EnemyMetis, "Metis_469");
				break;
			case 2860:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772860);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774660, EnemyMetis, "Metis_470");
				break;
			case 2870:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772870);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774670, EnemyMetis, "Metis_471");
				break;
			case 2880:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772880);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774680, EnemyMetis, "Metis_472");
				break;
			case 2890:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772890);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774690, EnemyMetis, "Metis_473");
				break;
			case 2900:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772900);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774700, EnemyMetis, "Metis_474");
				break;
			case 2910:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772910);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774710, EnemyMetis, "Metis_475");
				break;
			case 2920:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772920);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774720, EnemyMetis, "Metis_476");
				break;
			case 2930:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772930);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774730, EnemyMetis, "Metis_477");
				break;
			case 2940:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772940);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774740, EnemyMetis, "Metis_478");
				break;
			case 2950:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772950);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774750, EnemyMetis, "Metis_479");
				break;
			case 2960:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772960);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774760, EnemyMetis, "Metis_480");
				break;
			case 2970:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772970);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774770, EnemyMetis, "Metis_481");
				break;
			case 2980:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772980);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774780, EnemyMetis, "Metis_482");
				break;
			case 2990:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772990);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774790, EnemyMetis, "Metis_483");
				break;
			case 3000:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773000);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774800, EnemyMetis, "Metis_484");
				break;
			case 3010:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773010);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774810, EnemyMetis, "Metis_485");
				break;
			case 3020:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773020);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774820, EnemyMetis, "Metis_486");
				break;
			case 3030:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773030);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774830, EnemyMetis, "Metis_487");
				break;
			case 3040:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773040);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774840, EnemyMetis, "Metis_488");
				break;
			case 3050:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773050);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774850, EnemyMetis, "Metis_489");
				break;
			case 3060:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773060);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774860, EnemyMetis, "Metis_490");
				break;
			case 3070:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773070);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774870, EnemyMetis, "Metis_491");
				break;
			case 3080:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773080);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774880, EnemyMetis, "Metis_492");
				break;
			case 3090:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773090);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774890, EnemyMetis, "Metis_493");
				break;
			case 3100:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773100);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774900, EnemyMetis, "Metis_494");
				break;
			case 3110:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773110);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774910, EnemyMetis, "Metis_495");
				break;
			case 3120:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773120);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774920, EnemyMetis, "Metis_496");
				break;
			case 3130:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773130);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774930, EnemyMetis, "Metis_497");
				break;
			case 3140:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773140);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774940, EnemyMetis, "Metis_498");
				break;
			case 3150:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773150);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774950, EnemyMetis, "Metis_499");
				break;
			case 3160:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773160);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774960, EnemyMetis, "Metis_500");
				break;
			case 3170:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773170);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774970, EnemyMetis, "Metis_501");
				break;
			case 3180:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773180);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774980, EnemyMetis, "Metis_502");
				break;
			case 3190:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773190);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774990, EnemyMetis, "Metis_503");
				break;
			case 3200:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773200);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775000, EnemyMetis, "Metis_504");
				break;
			case 3210:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773210);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775010, EnemyMetis, "Metis_505");
				break;
			case 3220:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773220);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775020, EnemyMetis, "Metis_506");
				break;
			case 3230:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773230);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775030, EnemyMetis, "Metis_507");
				break;
			case 3240:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773240);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775040, EnemyMetis, "Metis_508");
				break;
			case 3250:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773250);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775050, EnemyMetis, "Metis_509");
				break;
			case 3260:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773260);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775060, EnemyMetis, "Metis_510");
				break;
			case 3270:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773270);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775070, EnemyMetis, "Metis_511");
				break;
			case 3280:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773280);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775080, EnemyMetis, "Metis_512");
				break;
			case 3290:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773290);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775090, EnemyMetis, "Metis_513");
				break;
			case 3300:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773300);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775100, EnemyMetis, "Metis_514");
				break;
			case 3310:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773310);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775110, EnemyMetis, "Metis_515");
				break;
			case 3320:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773320);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775120, EnemyMetis, "Metis_516");
				break;
			case 3330:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773330);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775130, EnemyMetis, "Metis_517");
				break;
			case 3340:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773340);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775140, EnemyMetis, "Metis_518");
				break;
			case 3350:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773350);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775150, EnemyMetis, "Metis_519");
				break;
			case 3360:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773360);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775160, EnemyMetis, "Metis_520");
				break;
			case 3370:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773370);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775170, EnemyMetis, "Metis_521");
				break;
			case 3380:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773380);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775180, EnemyMetis, "Metis_522");
				break;
			case 3390:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773390);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775190, EnemyMetis, "Metis_523");
				break;
			case 3400:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773400);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775200, EnemyMetis, "Metis_524");
				break;
			case 3410:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773410);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775210, EnemyMetis, "Metis_525");
				break;
			case 3420:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773420);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775220, EnemyMetis, "Metis_526");
				break;
			case 3430:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773430);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775230, EnemyMetis, "Metis_527");
				break;
			case 3440:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773440);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775240, EnemyMetis, "Metis_528");
				break;
			case 3450:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773450);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775250, EnemyMetis, "Metis_529");
				break;
			case 3460:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773460);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775260, EnemyMetis, "Metis_530");
				break;
			case 3470:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773470);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775270, EnemyMetis, "Metis_531");
				break;
			case 3480:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773480);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775280, EnemyMetis, "Metis_532");
				break;
			case 3490:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773490);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775290, EnemyMetis, "Metis_533");
				break;
			case 3500:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773500);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775300, EnemyMetis, "Metis_534");
				break;
			case 3510:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773510);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775310, EnemyMetis, "Metis_535");
				break;
			case 3520:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773520);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775320, EnemyMetis, "Metis_536");
				break;
			case 3530:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773530);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775330, EnemyMetis, "Metis_537");
				break;
			case 3540:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773540);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775340, EnemyMetis, "Metis_538");
				break;
			case 3550:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773550);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775350, EnemyMetis, "Metis_539");
				break;
			case 3560:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773560);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775360, EnemyMetis, "Metis_540");
				break;
			case 3570:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773570);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775370, EnemyMetis, "Metis_541");
				break;
			case 3580:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773580);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775380, EnemyMetis, "Metis_542");
				break;
			case 3590:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773590);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775390, EnemyMetis, "Metis_543");
				break;
			case 3600:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773600);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775400, EnemyMetis, "Metis_544");
				break;
			case 3610:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773610);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775410, EnemyMetis, "Metis_545");
				break;
			case 3620:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773620);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775420, EnemyMetis, "Metis_546");
				break;
			case 3630:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773630);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775430, EnemyMetis, "Metis_547");
				break;
			case 3640:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773640);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775440, EnemyMetis, "Metis_548");
				break;
			case 3650:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773650);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775450, EnemyMetis, "Metis_549");
				break;
			case 3660:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773660);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775460, EnemyMetis, "Metis_550");
				break;
			case 3670:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773670);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775470, EnemyMetis, "Metis_551");
				break;
			case 3680:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773680);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775480, EnemyMetis, "Metis_552");
				break;
			case 3690:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773690);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775490, EnemyMetis, "Metis_553");
				break;
			case 3700:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773700);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775500, EnemyMetis, "Metis_554");
				break;
			case 3710:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773710);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775510, EnemyMetis, "Metis_555");
				break;
			case 3720:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773720);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775520, EnemyMetis, "Metis_556");
				break;
			case 3730:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773730);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775530, EnemyMetis, "Metis_557");
				break;
			case 3740:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773740);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775540, EnemyMetis, "Metis_558");
				break;
			case 3750:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773750);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775550, EnemyMetis, "Metis_559");
				break;
			case 3760:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773760);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775560, EnemyMetis, "Metis_560");
				break;
			case 3770:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773770);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775570, EnemyMetis, "Metis_561");
				break;
			case 3780:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773780);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775580, EnemyMetis, "Metis_562");
				break;
			case 3790:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773790);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775590, EnemyMetis, "Metis_563");
				break;
			case 3800:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773800);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775600, EnemyMetis, "Metis_564");
				break;
			case 3810:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773810);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775610, EnemyMetis, "Metis_565");
				break;
			case 3820:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773820);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775620, EnemyMetis, "Metis_566");
				break;
			case 3830:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773830);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775630, EnemyMetis, "Metis_567");
				break;
			case 3840:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773840);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775640, EnemyMetis, "Metis_568");
				break;
			case 3850:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773850);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775650, EnemyMetis, "Metis_569");
				break;
			case 3860:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773860);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775660, EnemyMetis, "Metis_570");
				break;
			case 3870:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773870);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775670, EnemyMetis, "Metis_571");
				break;
			case 3880:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773880);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775680, EnemyMetis, "Metis_572");
				break;
			case 3890:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773890);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775690, EnemyMetis, "Metis_573");
				break;
			case 3900:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773900);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775700, EnemyMetis, "Metis_574");
				break;
			case 3910:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773910);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775710, EnemyMetis, "Metis_575");
				break;
			case 3920:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773920);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775720, EnemyMetis, "Metis_576");
				break;
			case 3930:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773930);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775730, EnemyMetis, "Metis_577");
				break;
			case 3940:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773940);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775740, EnemyMetis, "Metis_578");
				break;
			case 3950:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773950);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775750, EnemyMetis, "Metis_579");
				break;
			case 3960:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773960);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775760, EnemyMetis, "Metis_580");
				break;
			case 3970:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773970);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775770, EnemyMetis, "Metis_581");
				break;
			case 3980:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773980);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775780, EnemyMetis, "Metis_582");
				break;
			case 3990:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773990);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775790, EnemyMetis, "Metis_583");
				break;
			case 4000:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774000);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775800, EnemyMetis, "Metis_584");
				break;
			case 4010:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774010);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775810, EnemyMetis, "Metis_585");
				break;
			case 4020:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774020);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775820, EnemyMetis, "Metis_586");
				break;
			case 4030:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774030);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775830, EnemyMetis, "Metis_587");
				break;
			case 4040:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774040);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775840, EnemyMetis, "Metis_588");
				break;
			case 4050:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774050);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775850, EnemyMetis, "Metis_589");
				break;
			case 4060:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774060);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775860, EnemyMetis, "Metis_590");
				break;
			case 4070:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774070);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775870, EnemyMetis, "Metis_591");
				break;
			case 4080:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774080);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775880, EnemyMetis, "Metis_592");
				break;
			case 4090:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774090);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775890, EnemyMetis, "Metis_593");
				break;
			case 4100:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774100);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775900, EnemyMetis, "Metis_594");
				break;
			case 4110:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774110);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775910, EnemyMetis, "Metis_595");
				break;
			case 4120:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774120);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775920, EnemyMetis, "Metis_596");
				break;
			case 4130:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774130);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775930, EnemyMetis, "Metis_597");
				break;
			case 4140:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774140);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775940, EnemyMetis, "Metis_598");
				break;
			case 4150:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774150);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775950, EnemyMetis, "Metis_599");
				break;
			case 4160:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774160);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775960, EnemyMetis, "Metis_600");
				break;
			case 4170:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774170);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775970, EnemyMetis, "Metis_601");
				break;
			case 4180:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774180);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775980, EnemyMetis, "Metis_602");
				break;
			case 4190:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774190);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775990, EnemyMetis, "Metis_603");
				break;
			case 4200:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774200);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776000, EnemyMetis, "Metis_604");
				break;
			case 4210:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774210);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776010, EnemyMetis, "Metis_605");
				break;
			case 4220:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774220);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776020, EnemyMetis, "Metis_606");
				break;
			case 4230:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774230);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776030, EnemyMetis, "Metis_607");
				break;
			case 4240:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774240);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776040, EnemyMetis, "Metis_608");
				break;
			case 4250:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774250);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776050, EnemyMetis, "Metis_609");
				break;
			case 4260:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774260);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776060, EnemyMetis, "Metis_610");
				break;
			case 4270:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774270);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776070, EnemyMetis, "Metis_611");
				break;
			case 4280:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774280);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776080, EnemyMetis, "Metis_612");
				break;
			case 4290:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774290);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776090, EnemyMetis, "Metis_613");
				break;
			case 4300:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774300);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776100, EnemyMetis, "Metis_614");
				break;
			case 4310:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774310);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776110, EnemyMetis, "Metis_615");
				break;
			case 4320:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774320);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776120, EnemyMetis, "Metis_616");
				break;
			case 4330:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774330);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776130, EnemyMetis, "Metis_617");
				break;
			case 4340:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774340);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776140, EnemyMetis, "Metis_618");
				break;
			case 4350:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774350);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776150, EnemyMetis, "Metis_619");
				break;
			case 4360:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774360);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776160, EnemyMetis, "Metis_620");
				break;
			case 4370:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774370);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776170, EnemyMetis, "Metis_621");
				break;
			case 4380:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774380);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776180, EnemyMetis, "Metis_622");
				break;
			case 4390:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774390);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776190, EnemyMetis, "Metis_623");
				break;
			case 4400:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774400);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776200, EnemyMetis, "Metis_624");
				break;
			case 4410:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774410);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776210, EnemyMetis, "Metis_625");
				break;
			case 4420:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774420);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776220, EnemyMetis, "Metis_626");
				break;
			case 4430:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774430);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776230, EnemyMetis, "Metis_627");
				break;
			case 4440:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774440);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776240, EnemyMetis, "Metis_628");
				break;
			case 4450:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774450);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776250, EnemyMetis, "Metis_629");
				break;
			case 4460:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774460);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776260, EnemyMetis, "Metis_630");
				break;
			case 4470:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774470);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776270, EnemyMetis, "Metis_631");
				break;
			case 4480:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774480);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776280, EnemyMetis, "Metis_632");
				break;
			case 4490:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774490);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776290, EnemyMetis, "Metis_633");
				break;
			case 4500:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774500);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776300, EnemyMetis, "Metis_634");
				break;
			case 4510:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774510);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776310, EnemyMetis, "Metis_635");
				break;
			case 4520:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774520);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776320, EnemyMetis, "Metis_636");
				break;
			case 4530:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774530);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776330, EnemyMetis, "Metis_637");
				break;
			case 4540:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774540);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776340, EnemyMetis, "Metis_638");
				break;
			case 4550:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774550);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776350, EnemyMetis, "Metis_639");
				break;
			case 4560:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774560);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776360, EnemyMetis, "Metis_640");
				break;
			case 4570:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774570);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776370, EnemyMetis, "Metis_641");
				break;
			case 4580:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774580);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776380, EnemyMetis, "Metis_642");
				break;
			case 4590:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774590);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776390, EnemyMetis, "Metis_643");
				break;
			case 4600:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774600);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776400, EnemyMetis, "Metis_644");
				break;
			case 4610:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774610);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776410, EnemyMetis, "Metis_645");
				break;
			case 4620:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774620);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776420, EnemyMetis, "Metis_646");
				break;
			case 4630:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774630);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776430, EnemyMetis, "Metis_647");
				break;
			case 4640:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774640);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776440, EnemyMetis, "Metis_648");
				break;
			case 4650:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774650);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776450, EnemyMetis, "Metis_649");
				break;
			case 4660:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774660);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776460, EnemyMetis, "Metis_650");
				break;
			case 4670:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774670);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776470, EnemyMetis, "Metis_651");
				break;
			case 4680:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774680);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776480, EnemyMetis, "Metis_652");
				break;
			case 4690:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774690);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776490, EnemyMetis, "Metis_653");
				break;
			case 4700:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774700);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776500, EnemyMetis, "Metis_654");
				break;
			case 4710:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774710);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776510, EnemyMetis, "Metis_655");
				break;
			case 4720:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774720);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776520, EnemyMetis, "Metis_656");
				break;
			case 4730:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774730);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776530, EnemyMetis, "Metis_657");
				break;
			case 4740:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774740);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776540, EnemyMetis, "Metis_658");
				break;
			case 4750:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774750);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776550, EnemyMetis, "Metis_659");
				break;
			case 4760:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774760);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776560, EnemyMetis, "Metis_660");
				break;
			case 4770:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774770);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776570, EnemyMetis, "Metis_661");
				break;
			case 4780:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774780);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776580, EnemyMetis, "Metis_662");
				break;
			case 4790:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774790);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776590, EnemyMetis, "Metis_663");
				break;
			case 4800:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774800);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776600, EnemyMetis, "Metis_664");
				break;
			case 4810:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774810);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776610, EnemyMetis, "Metis_665");
				break;
			case 4820:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774820);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776620, EnemyMetis, "Metis_666");
				break;
			case 4830:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774830);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776630, EnemyMetis, "Metis_667");
				break;
			case 4840:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774840);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776640, EnemyMetis, "Metis_668");
				break;
			case 4850:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774850);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776650, EnemyMetis, "Metis_669");
				break;
			case 4860:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774860);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776660, EnemyMetis, "Metis_670");
				break;
			case 4870:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774870);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776670, EnemyMetis, "Metis_671");
				break;
			case 4880:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774880);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776680, EnemyMetis, "Metis_672");
				break;
			case 4890:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774890);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776690, EnemyMetis, "Metis_673");
				break;
			case 4900:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774900);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776700, EnemyMetis, "Metis_674");
				break;
			case 4910:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774910);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776710, EnemyMetis, "Metis_675");
				break;
			case 4920:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774920);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776720, EnemyMetis, "Metis_676");
				break;
			case 4930:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774930);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776730, EnemyMetis, "Metis_677");
				break;
			case 4940:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774940);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776740, EnemyMetis, "Metis_678");
				break;
			case 4950:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774950);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776750, EnemyMetis, "Metis_679");
				break;
			case 4960:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774960);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776760, EnemyMetis, "Metis_680");
				break;
			case 4970:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774970);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776770, EnemyMetis, "Metis_681");
				break;
			case 4980:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774980);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776780, EnemyMetis, "Metis_682");
				break;
			case 4990:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774990);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776790, EnemyMetis, "Metis_683");
				break;
			case 5000:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775000);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776800, EnemyMetis, "Metis_684");
				break;
			case 5010:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775010);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776810, EnemyMetis, "Metis_685");
				break;
			case 5020:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775020);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776820, EnemyMetis, "Metis_686");
				break;
			case 5030:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775030);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776830, EnemyMetis, "Metis_687");
				break;
			case 5040:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775040);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776840, EnemyMetis, "Metis_688");
				break;
			case 5050:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775050);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776850, EnemyMetis, "Metis_689");
				break;
			case 5060:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775060);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776860, EnemyMetis, "Metis_690");
				break;
			case 5070:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775070);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776870, EnemyMetis, "Metis_691");
				break;
			case 5080:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775080);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776880, EnemyMetis, "Metis_692");
				break;
			case 5090:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775090);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776890, EnemyMetis, "Metis_693");
				break;
			case 5100:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775100);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776900, EnemyMetis, "Metis_694");
				break;
			case 5110:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775110);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776910, EnemyMetis, "Metis_695");
				break;
			case 5120:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775120);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776920, EnemyMetis, "Metis_696");
				break;
			case 5130:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775130);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776930, EnemyMetis, "Metis_697");
				break;
			case 5140:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775140);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776940, EnemyMetis, "Metis_698");
				break;
			case 5150:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775150);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776950, EnemyMetis, "Metis_699");
				break;
			case 5160:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775160);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776960, EnemyMetis, "Metis_700");
				break;
			case 5170:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775170);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776970, EnemyMetis, "Metis_701");
				break;
			case 5180:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775180);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776980, EnemyMetis, "Metis_702");
				break;
			case 5190:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775190);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776990, EnemyMetis, "Metis_703");
				break;
			case 5200:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775200);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777000, EnemyMetis, "Metis_704");
				break;
			case 5210:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775210);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777010, EnemyMetis, "Metis_705");
				break;
			case 5220:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775220);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777020, EnemyMetis, "Metis_706");
				break;
			case 5230:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775230);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777030, EnemyMetis, "Metis_707");
				break;
			case 5240:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775240);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777040, EnemyMetis, "Metis_708");
				break;
			case 5250:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775250);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777050, EnemyMetis, "Metis_709");
				break;
			case 5260:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775260);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777060, EnemyMetis, "Metis_710");
				break;
			case 5270:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775270);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777070, EnemyMetis, "Metis_711");
				break;
			case 5280:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775280);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777080, EnemyMetis, "Metis_712");
				break;
			case 5290:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775290);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777090, EnemyMetis, "Metis_713");
				break;
			case 5300:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775300);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777100, EnemyMetis, "Metis_714");
				break;
			case 5310:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775310);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777110, EnemyMetis, "Metis_715");
				break;
			case 5320:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775320);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777120, EnemyMetis, "Metis_716");
				break;
			case 5330:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775330);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777130, EnemyMetis, "Metis_717");
				break;
			case 5340:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775340);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777140, EnemyMetis, "Metis_718");
				break;
			case 5350:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775350);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777150, EnemyMetis, "Metis_719");
				break;
			case 5360:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775360);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777160, EnemyMetis, "Metis_720");
				break;
			case 5370:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775370);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777170, EnemyMetis, "Metis_721");
				break;
			case 5380:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775380);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777180, EnemyMetis, "Metis_722");
				break;
			case 5390:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775390);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777190, EnemyMetis, "Metis_723");
				break;
			case 5400:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775400);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777200, EnemyMetis, "Metis_724");
				break;
			case 5410:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775410);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777210, EnemyMetis, "Metis_725");
				break;
			case 5420:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775420);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777220, EnemyMetis, "Metis_726");
				break;
			case 5430:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775430);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777230, EnemyMetis, "Metis_727");
				break;
			case 5440:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775440);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777240, EnemyMetis, "Metis_728");
				break;
			case 5450:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775450);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777250, EnemyMetis, "Metis_729");
				break;
			case 5460:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775460);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777260, EnemyMetis, "Metis_730");
				break;
			case 5470:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775470);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777270, EnemyMetis, "Metis_731");
				break;
			case 5480:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775480);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777280, EnemyMetis, "Metis_732");
				break;
			case 5490:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775490);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777290, EnemyMetis, "Metis_733");
				break;
			case 5500:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775500);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777300, EnemyMetis, "Metis_734");
				break;
			case 5510:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775510);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777310, EnemyMetis, "Metis_735");
				break;
			case 5520:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775520);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777320, EnemyMetis, "Metis_736");
				break;
			case 5530:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775530);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777330, EnemyMetis, "Metis_737");
				break;
			case 5540:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775540);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777340, EnemyMetis, "Metis_738");
				break;
			case 5550:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775550);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777350, EnemyMetis, "Metis_739");
				break;
			case 5560:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775560);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777360, EnemyMetis, "Metis_740");
				break;
			case 5570:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775570);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777370, EnemyMetis, "Metis_741");
				break;
			case 5580:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775580);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777380, EnemyMetis, "Metis_742");
				break;
			case 5590:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775590);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777390, EnemyMetis, "Metis_743");
				break;
			case 5600:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775600);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777400, EnemyMetis, "Metis_744");
				break;
			case 5610:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775610);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777410, EnemyMetis, "Metis_745");
				break;
			case 5620:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775620);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777420, EnemyMetis, "Metis_746");
				break;
			case 5630:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775630);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777430, EnemyMetis, "Metis_747");
				break;
			case 5640:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775640);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777440, EnemyMetis, "Metis_748");
				break;
			case 5650:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775650);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777450, EnemyMetis, "Metis_749");
				break;
			case 5660:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775660);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777460, EnemyMetis, "Metis_750");
				break;
			case 5670:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775670);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777470, EnemyMetis, "Metis_751");
				break;
			case 5680:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775680);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777480, EnemyMetis, "Metis_752");
				break;
			case 5690:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775690);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777490, EnemyMetis, "Metis_753");
				break;
			case 5700:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775700);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777500, EnemyMetis, "Metis_754");
				break;
			case 5710:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775710);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777510, EnemyMetis, "Metis_755");
				break;
			case 5720:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775720);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777520, EnemyMetis, "Metis_756");
				break;
			case 5730:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775730);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777530, EnemyMetis, "Metis_757");
				break;
			case 5740:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775740);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777540, EnemyMetis, "Metis_758");
				break;
			case 5750:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775750);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777550, EnemyMetis, "Metis_759");
				break;
			case 5760:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775760);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777560, EnemyMetis, "Metis_760");
				break;
			case 5770:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775770);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777570, EnemyMetis, "Metis_761");
				break;
			case 5780:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775780);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777580, EnemyMetis, "Metis_762");
				break;
			case 5790:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775790);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777590, EnemyMetis, "Metis_763");
				break;
			case 5800:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775800);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777600, EnemyMetis, "Metis_764");
				break;
			case 5810:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775810);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777610, EnemyMetis, "Metis_765");
				break;
			case 5820:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775820);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777620, EnemyMetis, "Metis_766");
				break;
			case 5830:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775830);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777630, EnemyMetis, "Metis_767");
				break;
			case 5840:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775840);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777640, EnemyMetis, "Metis_768");
				break;
			case 5850:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775850);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777650, EnemyMetis, "Metis_769");
				break;
			case 5860:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775860);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777660, EnemyMetis, "Metis_770");
				break;
			case 5870:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775870);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777670, EnemyMetis, "Metis_771");
				break;
			case 5880:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775880);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777680, EnemyMetis, "Metis_772");
				break;
			case 5890:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775890);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777690, EnemyMetis, "Metis_773");
				break;
			case 5900:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775900);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777700, EnemyMetis, "Metis_774");
				break;
			case 5910:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775910);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777710, EnemyMetis, "Metis_775");
				break;
			case 5920:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775920);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777720, EnemyMetis, "Metis_776");
				break;
			case 5930:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775930);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777730, EnemyMetis, "Metis_777");
				break;
			case 5940:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775940);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777740, EnemyMetis, "Metis_778");
				break;
			case 5950:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775950);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777750, EnemyMetis, "Metis_779");
				break;
			case 5960:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775960);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777760, EnemyMetis, "Metis_780");
				break;
			case 5970:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775970);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777770, EnemyMetis, "Metis_781");
				break;
			case 5980:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775980);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777780, EnemyMetis, "Metis_782");
				break;
			case 5990:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775990);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777790, EnemyMetis, "Metis_783");
				break;
			case 6000:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776000);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777800, EnemyMetis, "Metis_784");
				break;
			case 6010:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776010);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777810, EnemyMetis, "Metis_785");
				break;
			case 6020:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776020);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777820, EnemyMetis, "Metis_786");
				break;
			case 6030:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776030);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777830, EnemyMetis, "Metis_787");
				break;
			case 6040:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776040);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777840, EnemyMetis, "Metis_788");
				break;
			case 6050:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776050);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777850, EnemyMetis, "Metis_789");
				break;
			case 6060:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776060);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777860, EnemyMetis, "Metis_790");
				break;
			case 6070:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776070);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777870, EnemyMetis, "Metis_791");
				break;
			case 6080:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776080);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777880, EnemyMetis, "Metis_792");
				break;
			case 6090:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776090);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777890, EnemyMetis, "Metis_793");
				break;
			case 6100:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776100);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777900, EnemyMetis, "Metis_794");
				break;
			case 6110:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776110);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777910, EnemyMetis, "Metis_795");
				break;
			case 6120:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776120);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777920, EnemyMetis, "Metis_796");
				break;
			case 6130:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776130);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777930, EnemyMetis, "Metis_797");
				break;
			case 6140:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776140);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777940, EnemyMetis, "Metis_798");
				break;
			case 6150:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776150);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777950, EnemyMetis, "Metis_799");
				break;
			case 6160:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776160);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777960, EnemyMetis, "Metis_800");
				break;
			case 6170:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776170);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777970, EnemyMetis, "Metis_801");
				break;
			case 6180:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776180);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777980, EnemyMetis, "Metis_802");
				break;
			case 6190:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776190);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777990, EnemyMetis, "Metis_803");
				break;
			case 6200:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776200);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778000, EnemyMetis, "Metis_804");
				break;
			case 6210:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776210);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778010, EnemyMetis, "Metis_805");
				break;
			case 6220:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776220);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778020, EnemyMetis, "Metis_806");
				break;
			case 6230:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776230);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778030, EnemyMetis, "Metis_807");
				break;
			case 6240:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776240);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778040, EnemyMetis, "Metis_808");
				break;
			case 6250:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776250);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778050, EnemyMetis, "Metis_809");
				break;
			case 6260:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776260);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778060, EnemyMetis, "Metis_810");
				break;
			case 6270:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776270);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778070, EnemyMetis, "Metis_811");
				break;
			case 6280:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776280);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778080, EnemyMetis, "Metis_812");
				break;
			case 6290:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776290);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778090, EnemyMetis, "Metis_813");
				break;
			case 6300:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776300);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778100, EnemyMetis, "Metis_814");
				break;
			case 6310:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776310);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778110, EnemyMetis, "Metis_815");
				break;
			case 6320:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776320);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778120, EnemyMetis, "Metis_816");
				break;
			case 6330:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776330);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778130, EnemyMetis, "Metis_817");
				break;
			case 6340:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776340);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778140, EnemyMetis, "Metis_818");
				break;
			case 6350:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776350);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778150, EnemyMetis, "Metis_819");
				break;
			case 6360:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776360);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778160, EnemyMetis, "Metis_820");
				break;
			case 6370:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776370);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778170, EnemyMetis, "Metis_821");
				break;
			case 6380:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776380);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778180, EnemyMetis, "Metis_822");
				break;
			case 6390:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776390);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778190, EnemyMetis, "Metis_823");
				break;
			case 6400:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776400);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778200, EnemyMetis, "Metis_824");
				break;
			case 6410:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776410);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778210, EnemyMetis, "Metis_825");
				break;
			case 6420:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776420);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778220, EnemyMetis, "Metis_826");
				break;
			case 6430:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776430);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778230, EnemyMetis, "Metis_827");
				break;
			case 6440:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776440);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778240, EnemyMetis, "Metis_828");
				break;
			case 6450:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776450);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778250, EnemyMetis, "Metis_829");
				break;
			case 6460:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776460);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778260, EnemyMetis, "Metis_830");
				break;
			case 6470:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776470);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778270, EnemyMetis, "Metis_831");
				break;
			case 6480:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776480);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778280, EnemyMetis, "Metis_832");
				break;
			case 6490:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776490);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778290, EnemyMetis, "Metis_833");
				break;
			case 6500:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776500);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778300, EnemyMetis, "Metis_834");
				break;
			case 6510:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776510);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778310, EnemyMetis, "Metis_835");
				break;
			case 6520:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776520);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778320, EnemyMetis, "Metis_836");
				break;
			case 6530:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776530);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778330, EnemyMetis, "Metis_837");
				break;
			case 6540:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776540);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778340, EnemyMetis, "Metis_838");
				break;
			case 6550:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776550);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778350, EnemyMetis, "Metis_839");
				break;
			case 6560:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776560);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778360, EnemyMetis, "Metis_840");
				break;
			case 6570:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776570);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778370, EnemyMetis, "Metis_841");
				break;
			case 6580:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776580);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778380, EnemyMetis, "Metis_842");
				break;
			case 6590:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776590);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778390, EnemyMetis, "Metis_843");
				break;
			case 6600:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776600);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778400, EnemyMetis, "Metis_844");
				break;
			case 6610:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776610);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778410, EnemyMetis, "Metis_845");
				break;
			case 6620:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776620);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778420, EnemyMetis, "Metis_846");
				break;
			case 6630:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776630);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778430, EnemyMetis, "Metis_847");
				break;
			case 6640:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776640);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778440, EnemyMetis, "Metis_848");
				break;
			case 6650:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776650);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778450, EnemyMetis, "Metis_849");
				break;
			case 6660:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776660);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778460, EnemyMetis, "Metis_850");
				break;
			case 6670:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776670);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778470, EnemyMetis, "Metis_851");
				break;
			case 6680:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776680);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778480, EnemyMetis, "Metis_852");
				break;
			case 6690:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776690);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778490, EnemyMetis, "Metis_853");
				break;
			case 6700:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776700);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778500, EnemyMetis, "Metis_854");
				break;
			case 6710:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776710);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778510, EnemyMetis, "Metis_855");
				break;
			case 6720:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776720);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778520, EnemyMetis, "Metis_856");
				break;
			case 6730:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776730);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778530, EnemyMetis, "Metis_857");
				break;
			case 6740:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776740);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778540, EnemyMetis, "Metis_858");
				break;
			case 6750:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776750);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778550, EnemyMetis, "Metis_859");
				break;
			case 6760:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776760);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778560, EnemyMetis, "Metis_860");
				break;
			case 6770:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776770);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778570, EnemyMetis, "Metis_861");
				break;
			case 6780:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776780);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778580, EnemyMetis, "Metis_862");
				break;
			case 6790:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776790);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778590, EnemyMetis, "Metis_863");
				break;
			case 6800:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776800);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778600, EnemyMetis, "Metis_864");
				break;
			case 6810:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776810);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778610, EnemyMetis, "Metis_865");
				break;
			case 6820:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776820);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778620, EnemyMetis, "Metis_866");
				break;
			case 6830:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776830);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778630, EnemyMetis, "Metis_867");
				break;
			case 6840:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776840);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778640, EnemyMetis, "Metis_868");
				break;
			case 6850:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776850);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778650, EnemyMetis, "Metis_869");
				break;
			case 6860:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776860);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778660, EnemyMetis, "Metis_870");
				break;
			case 6870:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776870);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778670, EnemyMetis, "Metis_871");
				break;
			case 6880:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776880);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778680, EnemyMetis, "Metis_872");
				break;
			case 6890:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776890);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778690, EnemyMetis, "Metis_873");
				break;
			case 6900:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776900);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778700, EnemyMetis, "Metis_874");
				break;
			case 6910:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776910);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778710, EnemyMetis, "Metis_875");
				break;
			case 6920:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776920);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778720, EnemyMetis, "Metis_876");
				break;
			case 6930:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776930);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778730, EnemyMetis, "Metis_877");
				break;
			case 6940:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776940);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778740, EnemyMetis, "Metis_878");
				break;
			case 6950:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776950);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778750, EnemyMetis, "Metis_879");
				break;
			case 6960:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776960);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778760, EnemyMetis, "Metis_880");
				break;
			case 6970:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776970);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778770, EnemyMetis, "Metis_881");
				break;
			case 6980:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776980);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778780, EnemyMetis, "Metis_882");
				break;
			case 6990:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776990);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778790, EnemyMetis, "Metis_883");
				break;
			case 7000:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777000);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778800, EnemyMetis, "Metis_884");
				break;
			case 7010:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777010);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778810, EnemyMetis, "Metis_885");
				break;
			case 7020:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777020);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778820, EnemyMetis, "Metis_886");
				break;
			case 7030:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777030);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778830, EnemyMetis, "Metis_887");
				break;
			case 7040:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777040);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778840, EnemyMetis, "Metis_888");
				break;
			case 7050:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777050);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778850, EnemyMetis, "Metis_889");
				break;
			case 7060:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777060);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778860, EnemyMetis, "Metis_890");
				break;
			case 7070:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777070);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778870, EnemyMetis, "Metis_891");
				break;
			case 7080:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777080);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778880, EnemyMetis, "Metis_892");
				break;
			case 7090:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777090);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778890, EnemyMetis, "Metis_893");
				break;
			case 7100:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777100);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778900, EnemyMetis, "Metis_894");
				break;
			case 7110:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777110);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778910, EnemyMetis, "Metis_895");
				break;
			case 7120:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777120);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778920, EnemyMetis, "Metis_896");
				break;
			case 7130:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777130);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778930, EnemyMetis, "Metis_897");
				break;
			case 7140:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777140);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778940, EnemyMetis, "Metis_898");
				break;
			case 7150:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777150);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778950, EnemyMetis, "Metis_899");
				break;
			case 7160:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777160);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778960, EnemyMetis, "Metis_900");
				break;
			case 7170:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777170);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778970, EnemyMetis, "Metis_901");
				break;
			case 7180:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777180);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778980, EnemyMetis, "Metis_902");
				break;
			case 7190:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777190);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778990, EnemyMetis, "Metis_903");
				break;
			case 7200:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777200);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779000, EnemyMetis, "Metis_904");
				break;
			case 7210:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777210);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779010, EnemyMetis, "Metis_905");
				break;
			case 7220:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777220);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779020, EnemyMetis, "Metis_906");
				break;
			case 7230:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777230);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779030, EnemyMetis, "Metis_907");
				break;
			case 7240:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777240);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779040, EnemyMetis, "Metis_908");
				break;
			case 7250:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777250);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779050, EnemyMetis, "Metis_909");
				break;
			case 7260:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777260);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779060, EnemyMetis, "Metis_910");
				break;
			case 7270:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777270);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779070, EnemyMetis, "Metis_911");
				break;
			case 7280:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777280);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779080, EnemyMetis, "Metis_912");
				break;
			case 7290:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777290);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779090, EnemyMetis, "Metis_913");
				break;
			case 7300:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777300);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779100, EnemyMetis, "Metis_914");
				break;
			case 7310:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777310);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779110, EnemyMetis, "Metis_915");
				break;
			case 7320:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777320);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779120, EnemyMetis, "Metis_916");
				break;
			case 7330:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777330);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779130, EnemyMetis, "Metis_917");
				break;
			case 7340:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777340);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779140, EnemyMetis, "Metis_918");
				break;
			case 7350:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777350);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779150, EnemyMetis, "Metis_919");
				break;
			case 7360:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777360);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779160, EnemyMetis, "Metis_920");
				break;
			case 7370:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777370);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779170, EnemyMetis, "Metis_921");
				break;
			case 7380:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777380);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779180, EnemyMetis, "Metis_922");
				break;
			case 7390:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777390);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779190, EnemyMetis, "Metis_923");
				break;
			case 7400:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777400);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779200, EnemyMetis, "Metis_924");
				break;
			case 7410:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777410);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779210, EnemyMetis, "Metis_925");
				break;
			case 7420:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777420);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779220, EnemyMetis, "Metis_926");
				break;
			case 7430:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777430);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779230, EnemyMetis, "Metis_927");
				break;
			case 7440:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777440);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779240, EnemyMetis, "Metis_928");
				break;
			case 7450:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777450);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779250, EnemyMetis, "Metis_929");
				break;
			case 7460:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777460);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779260, EnemyMetis, "Metis_930");
				break;
			case 7470:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777470);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779270, EnemyMetis, "Metis_931");
				break;
			case 7480:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777480);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779280, EnemyMetis, "Metis_932");
				break;
			case 7490:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777490);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779290, EnemyMetis, "Metis_933");
				break;
			case 7500:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777500);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779300, EnemyMetis, "Metis_934");
				break;
			case 7510:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777510);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779310, EnemyMetis, "Metis_935");
				break;
			case 7520:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777520);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779320, EnemyMetis, "Metis_936");
				break;
			case 7530:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777530);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779330, EnemyMetis, "Metis_937");
				break;
			case 7540:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777540);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779340, EnemyMetis, "Metis_938");
				break;
			case 7550:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777550);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779350, EnemyMetis, "Metis_939");
				break;
			case 7560:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777560);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779360, EnemyMetis, "Metis_940");
				break;
			case 7570:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777570);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779370, EnemyMetis, "Metis_941");
				break;
			case 7580:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777580);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779380, EnemyMetis, "Metis_942");
				break;
			case 7590:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777590);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779390, EnemyMetis, "Metis_943");
				break;
			case 7600:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777600);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779400, EnemyMetis, "Metis_944");
				break;
			case 7610:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777610);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779410, EnemyMetis, "Metis_945");
				break;
			case 7620:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777620);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779420, EnemyMetis, "Metis_946");
				break;
			case 7630:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777630);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779430, EnemyMetis, "Metis_947");
				break;
			case 7640:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777640);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779440, EnemyMetis, "Metis_948");
				break;
			case 7650:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777650);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779450, EnemyMetis, "Metis_949");
				break;
			case 7660:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777660);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779460, EnemyMetis, "Metis_950");
				break;
			case 7670:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777670);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779470, EnemyMetis, "Metis_951");
				break;
			case 7680:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777680);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779480, EnemyMetis, "Metis_952");
				break;
			case 7690:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777690);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779490, EnemyMetis, "Metis_953");
				break;
			case 7700:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777700);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779500, EnemyMetis, "Metis_954");
				break;
			case 7710:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777710);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779510, EnemyMetis, "Metis_955");
				break;
			case 7720:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777720);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779520, EnemyMetis, "Metis_956");
				break;
			case 7730:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777730);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779530, EnemyMetis, "Metis_957");
				break;
			case 7740:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777740);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779540, EnemyMetis, "Metis_958");
				break;
			case 7750:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777750);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779550, EnemyMetis, "Metis_959");
				break;
			case 7760:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777760);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779560, EnemyMetis, "Metis_960");
				break;
			case 7770:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777770);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779570, EnemyMetis, "Metis_961");
				break;
			case 7780:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777780);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779580, EnemyMetis, "Metis_962");
				break;
			case 7790:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777790);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779590, EnemyMetis, "Metis_963");
				break;
			case 7800:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777800);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779600, EnemyMetis, "Metis_964");
				break;
			case 7810:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777810);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779610, EnemyMetis, "Metis_965");
				break;
			case 7820:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777820);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779620, EnemyMetis, "Metis_966");
				break;
			case 7830:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777830);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779630, EnemyMetis, "Metis_967");
				break;
			case 7840:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777840);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779640, EnemyMetis, "Metis_968");
				break;
			case 7850:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777850);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779650, EnemyMetis, "Metis_969");
				break;
			case 7860:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777860);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779660, EnemyMetis, "Metis_970");
				break;
			case 7870:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777870);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779670, EnemyMetis, "Metis_971");
				break;
			case 7880:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777880);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779680, EnemyMetis, "Metis_972");
				break;
			case 7890:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777890);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779690, EnemyMetis, "Metis_973");
				break;
			case 7900:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777900);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779700, EnemyMetis, "Metis_974");
				break;
			case 7910:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777910);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779710, EnemyMetis, "Metis_975");
				break;
			case 7920:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777920);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779720, EnemyMetis, "Metis_976");
				break;
			case 7930:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777930);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779730, EnemyMetis, "Metis_977");
				break;
			case 7940:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777940);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779740, EnemyMetis, "Metis_978");
				break;
			case 7950:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777950);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779750, EnemyMetis, "Metis_979");
				break;
			case 7960:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777960);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779760, EnemyMetis, "Metis_980");
				break;
			case 7970:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777970);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779770, EnemyMetis, "Metis_981");
				break;
			case 7980:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777980);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779780, EnemyMetis, "Metis_982");
				break;
			case 7990:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777990);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779790, EnemyMetis, "Metis_983");
				break;
			case 8000:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778000);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779800, EnemyMetis, "Metis_984");
				break;
			case 8010:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778010);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779810, EnemyMetis, "Metis_985");
				break;
			case 8020:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778020);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779820, EnemyMetis, "Metis_986");
				break;
			case 8030:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778030);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779830, EnemyMetis, "Metis_987");
				break;
			case 8040:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778040);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779840, EnemyMetis, "Metis_988");
				break;
			case 8050:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778050);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779850, EnemyMetis, "Metis_989");
				break;
			case 8060:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778060);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779860, EnemyMetis, "Metis_990");
				break;
			case 8070:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778070);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779870, EnemyMetis, "Metis_991");
				break;
			case 8080:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778080);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779880, EnemyMetis, "Metis_992");
				break;
			case 8090:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778090);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779890, EnemyMetis, "Metis_993");
				break;
			case 8100:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778100);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779900, EnemyMetis, "Metis_994");
				break;
			case 8110:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778110);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779910, EnemyMetis, "Metis_995");
				break;
			case 8120:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778120);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779920, EnemyMetis, "Metis_996");
				break;
			case 8130:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778130);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779930, EnemyMetis, "Metis_997");
				break;
			case 8140:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778140);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779940, EnemyMetis, "Metis_998");
				break;
			case 8150:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778150);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779950, EnemyMetis, "Metis_999");
				break;
			case 8160:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778160);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779960, EnemyMetis, "Metis_1000");
				break;
			case 8170:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778170);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779970, EnemyMetis, "Metis_1001");
				break;
			case 8180:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778180);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779980, EnemyMetis, "Metis_1002");
				break;
			case 8190:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778190);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779990, EnemyMetis, "Metis_1003");
				break;
			case 8200:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778200);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710000, EnemyMetis, "Metis_1004");
				orderActorToFactory(2122610000, EnemyAstraea, "Astraea_1005");
				break;
			case 8210:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778210);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710010, EnemyMetis, "Metis_1006");
				break;
			case 8220:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778220);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710020, EnemyMetis, "Metis_1007");
				break;
			case 8230:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778230);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710030, EnemyMetis, "Metis_1008");
				break;
			case 8240:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778240);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710040, EnemyMetis, "Metis_1009");
				break;
			case 8250:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778250);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710050, EnemyMetis, "Metis_1010");
				break;
			case 8260:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778260);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710060, EnemyMetis, "Metis_1011");
				break;
			case 8270:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778270);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710070, EnemyMetis, "Metis_1012");
				break;
			case 8280:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778280);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710080, EnemyMetis, "Metis_1013");
				break;
			case 8290:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778290);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710090, EnemyMetis, "Metis_1014");
				break;
			case 8300:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778300);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710100, EnemyMetis, "Metis_1015");
				break;
			case 8310:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778310);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710110, EnemyMetis, "Metis_1016");
				break;
			case 8320:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778320);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710120, EnemyMetis, "Metis_1017");
				break;
			case 8330:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778330);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710130, EnemyMetis, "Metis_1018");
				break;
			case 8340:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778340);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710140, EnemyMetis, "Metis_1019");
				break;
			case 8350:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778350);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710150, EnemyMetis, "Metis_1020");
				break;
			case 8360:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778360);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710160, EnemyMetis, "Metis_1021");
				break;
			case 8370:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778370);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710170, EnemyMetis, "Metis_1022");
				break;
			case 8380:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778380);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710180, EnemyMetis, "Metis_1023");
				break;
			case 8390:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778390);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710190, EnemyMetis, "Metis_1024");
				break;
			case 8400:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778400);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710200, EnemyMetis, "Metis_1025");
				break;
			case 8410:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778410);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710210, EnemyMetis, "Metis_1026");
				break;
			case 8420:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778420);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710220, EnemyMetis, "Metis_1027");
				break;
			case 8430:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778430);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710230, EnemyMetis, "Metis_1028");
				break;
			case 8440:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778440);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710240, EnemyMetis, "Metis_1029");
				break;
			case 8450:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778450);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710250, EnemyMetis, "Metis_1030");
				break;
			case 8460:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778460);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710260, EnemyMetis, "Metis_1031");
				break;
			case 8470:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778470);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710270, EnemyMetis, "Metis_1032");
				break;
			case 8480:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778480);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710280, EnemyMetis, "Metis_1033");
				break;
			case 8490:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778490);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710290, EnemyMetis, "Metis_1034");
				break;
			case 8500:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778500);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710300, EnemyMetis, "Metis_1035");
				break;
			case 8510:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778510);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710310, EnemyMetis, "Metis_1036");
				break;
			case 8520:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778520);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710320, EnemyMetis, "Metis_1037");
				break;
			case 8530:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778530);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710330, EnemyMetis, "Metis_1038");
				break;
			case 8540:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778540);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710340, EnemyMetis, "Metis_1039");
				break;
			case 8550:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778550);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710350, EnemyMetis, "Metis_1040");
				break;
			case 8560:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778560);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710360, EnemyMetis, "Metis_1041");
				break;
			case 8570:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778570);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710370, EnemyMetis, "Metis_1042");
				break;
			case 8580:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778580);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710380, EnemyMetis, "Metis_1043");
				break;
			case 8590:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778590);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710390, EnemyMetis, "Metis_1044");
				break;
			case 8600:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778600);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710400, EnemyMetis, "Metis_1045");
				break;
			case 8610:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778610);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710410, EnemyMetis, "Metis_1046");
				break;
			case 8620:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778620);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710420, EnemyMetis, "Metis_1047");
				break;
			case 8630:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778630);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710430, EnemyMetis, "Metis_1048");
				break;
			case 8640:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778640);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710440, EnemyMetis, "Metis_1049");
				break;
			case 8650:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778650);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710450, EnemyMetis, "Metis_1050");
				break;
			case 8660:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778660);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710460, EnemyMetis, "Metis_1051");
				break;
			case 8670:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778670);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710470, EnemyMetis, "Metis_1052");
				break;
			case 8680:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778680);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710480, EnemyMetis, "Metis_1053");
				break;
			case 8690:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778690);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710490, EnemyMetis, "Metis_1054");
				break;
			case 8700:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778700);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710500, EnemyMetis, "Metis_1055");
				break;
			case 8710:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778710);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710510, EnemyMetis, "Metis_1056");
				break;
			case 8720:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778720);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710520, EnemyMetis, "Metis_1057");
				break;
			case 8730:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778730);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710530, EnemyMetis, "Metis_1058");
				break;
			case 8740:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778740);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710540, EnemyMetis, "Metis_1059");
				break;
			case 8750:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778750);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710550, EnemyMetis, "Metis_1060");
				break;
			case 8760:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778760);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710560, EnemyMetis, "Metis_1061");
				break;
			case 8770:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778770);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710570, EnemyMetis, "Metis_1062");
				break;
			case 8780:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778780);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710580, EnemyMetis, "Metis_1063");
				break;
			case 8790:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778790);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710590, EnemyMetis, "Metis_1064");
				break;
			case 8800:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778800);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710600, EnemyMetis, "Metis_1065");
				break;
			case 8810:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778810);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710610, EnemyMetis, "Metis_1066");
				break;
			case 8820:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778820);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710620, EnemyMetis, "Metis_1067");
				break;
			case 8830:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778830);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710630, EnemyMetis, "Metis_1068");
				break;
			case 8840:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778840);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710640, EnemyMetis, "Metis_1069");
				break;
			case 8850:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778850);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710650, EnemyMetis, "Metis_1070");
				break;
			case 8860:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778860);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710660, EnemyMetis, "Metis_1071");
				break;
			case 8870:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778870);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710670, EnemyMetis, "Metis_1072");
				break;
			case 8880:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778880);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710680, EnemyMetis, "Metis_1073");
				break;
			case 8890:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778890);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710690, EnemyMetis, "Metis_1074");
				break;
			case 8900:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778900);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710700, EnemyMetis, "Metis_1075");
				break;
			case 8910:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778910);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710710, EnemyMetis, "Metis_1076");
				break;
			case 8920:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778920);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710720, EnemyMetis, "Metis_1077");
				break;
			case 8930:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778930);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710730, EnemyMetis, "Metis_1078");
				break;
			case 8940:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778940);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710740, EnemyMetis, "Metis_1079");
				break;
			case 8950:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778950);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710750, EnemyMetis, "Metis_1080");
				break;
			case 8960:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778960);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710760, EnemyMetis, "Metis_1081");
				break;
			case 8970:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778970);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710770, EnemyMetis, "Metis_1082");
				break;
			case 8980:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778980);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710780, EnemyMetis, "Metis_1083");
				break;
			case 8990:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778990);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710790, EnemyMetis, "Metis_1084");
				break;
			case 9000:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779000);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710800, EnemyMetis, "Metis_1085");
				break;
			case 9010:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779010);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710810, EnemyMetis, "Metis_1086");
				break;
			case 9020:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779020);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710820, EnemyMetis, "Metis_1087");
				break;
			case 9030:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779030);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710830, EnemyMetis, "Metis_1088");
				break;
			case 9040:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779040);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710840, EnemyMetis, "Metis_1089");
				break;
			case 9050:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779050);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710850, EnemyMetis, "Metis_1090");
				break;
			case 9060:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779060);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710860, EnemyMetis, "Metis_1091");
				break;
			case 9070:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779070);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710870, EnemyMetis, "Metis_1092");
				break;
			case 9080:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779080);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710880, EnemyMetis, "Metis_1093");
				break;
			case 9090:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779090);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710890, EnemyMetis, "Metis_1094");
				break;
			case 9100:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779100);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710900, EnemyMetis, "Metis_1095");
				break;
			case 9110:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779110);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710910, EnemyMetis, "Metis_1096");
				break;
			case 9120:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779120);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710920, EnemyMetis, "Metis_1097");
				break;
			case 9130:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779130);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710930, EnemyMetis, "Metis_1098");
				break;
			case 9140:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779140);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710940, EnemyMetis, "Metis_1099");
				break;
			case 9150:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779150);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710950, EnemyMetis, "Metis_1100");
				break;
			case 9160:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779160);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710960, EnemyMetis, "Metis_1101");
				break;
			case 9170:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779170);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710970, EnemyMetis, "Metis_1102");
				break;
			case 9180:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779180);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710980, EnemyMetis, "Metis_1103");
				break;
			case 9190:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779190);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710990, EnemyMetis, "Metis_1104");
				break;
			case 9200:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779200);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711000, EnemyMetis, "Metis_1105");
				break;
			case 9210:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779210);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711010, EnemyMetis, "Metis_1106");
				break;
			case 9220:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779220);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711020, EnemyMetis, "Metis_1107");
				break;
			case 9230:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779230);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711030, EnemyMetis, "Metis_1108");
				break;
			case 9240:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779240);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711040, EnemyMetis, "Metis_1109");
				break;
			case 9250:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779250);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711050, EnemyMetis, "Metis_1110");
				break;
			case 9260:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779260);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711060, EnemyMetis, "Metis_1111");
				break;
			case 9270:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779270);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711070, EnemyMetis, "Metis_1112");
				break;
			case 9280:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779280);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711080, EnemyMetis, "Metis_1113");
				break;
			case 9290:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779290);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711090, EnemyMetis, "Metis_1114");
				break;
			case 9300:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779300);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711100, EnemyMetis, "Metis_1115");
				break;
			case 9310:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779310);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711110, EnemyMetis, "Metis_1116");
				break;
			case 9320:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779320);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711120, EnemyMetis, "Metis_1117");
				break;
			case 9330:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779330);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711130, EnemyMetis, "Metis_1118");
				break;
			case 9340:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779340);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711140, EnemyMetis, "Metis_1119");
				break;
			case 9350:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779350);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711150, EnemyMetis, "Metis_1120");
				break;
			case 9360:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779360);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711160, EnemyMetis, "Metis_1121");
				break;
			case 9370:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779370);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711170, EnemyMetis, "Metis_1122");
				break;
			case 9380:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779380);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711180, EnemyMetis, "Metis_1123");
				break;
			case 9390:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779390);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711190, EnemyMetis, "Metis_1124");
				break;
			case 9400:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779400);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711200, EnemyMetis, "Metis_1125");
				break;
			case 9410:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779410);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711210, EnemyMetis, "Metis_1126");
				break;
			case 9420:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779420);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711220, EnemyMetis, "Metis_1127");
				break;
			case 9430:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779430);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711230, EnemyMetis, "Metis_1128");
				break;
			case 9440:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779440);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711240, EnemyMetis, "Metis_1129");
				break;
			case 9450:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779450);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711250, EnemyMetis, "Metis_1130");
				break;
			case 9460:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779460);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711260, EnemyMetis, "Metis_1131");
				break;
			case 9470:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779470);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711270, EnemyMetis, "Metis_1132");
				break;
			case 9480:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779480);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711280, EnemyMetis, "Metis_1133");
				break;
			case 9490:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779490);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711290, EnemyMetis, "Metis_1134");
				break;
			case 9500:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779500);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711300, EnemyMetis, "Metis_1135");
				break;
			case 9510:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779510);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711310, EnemyMetis, "Metis_1136");
				break;
			case 9520:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779520);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711320, EnemyMetis, "Metis_1137");
				break;
			case 9530:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779530);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711330, EnemyMetis, "Metis_1138");
				break;
			case 9540:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779540);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711340, EnemyMetis, "Metis_1139");
				break;
			case 9550:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779550);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711350, EnemyMetis, "Metis_1140");
				break;
			case 9560:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779560);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711360, EnemyMetis, "Metis_1141");
				break;
			case 9570:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779570);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711370, EnemyMetis, "Metis_1142");
				break;
			case 9580:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779580);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711380, EnemyMetis, "Metis_1143");
				break;
			case 9590:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779590);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711390, EnemyMetis, "Metis_1144");
				break;
			case 9600:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779600);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711400, EnemyMetis, "Metis_1145");
				break;
			case 9610:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779610);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711410, EnemyMetis, "Metis_1146");
				break;
			case 9620:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779620);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711420, EnemyMetis, "Metis_1147");
				break;
			case 9630:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779630);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711430, EnemyMetis, "Metis_1148");
				break;
			case 9640:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779640);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711440, EnemyMetis, "Metis_1149");
				break;
			case 9650:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779650);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711450, EnemyMetis, "Metis_1150");
				break;
			case 9660:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779660);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711460, EnemyMetis, "Metis_1151");
				break;
			case 9670:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779670);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711470, EnemyMetis, "Metis_1152");
				break;
			case 9680:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779680);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711480, EnemyMetis, "Metis_1153");
				break;
			case 9690:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779690);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711490, EnemyMetis, "Metis_1154");
				break;
			case 9700:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779700);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711500, EnemyMetis, "Metis_1155");
				break;
			case 9710:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779710);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711510, EnemyMetis, "Metis_1156");
				break;
			case 9720:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779720);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711520, EnemyMetis, "Metis_1157");
				break;
			case 9730:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779730);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711530, EnemyMetis, "Metis_1158");
				break;
			case 9740:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779740);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711540, EnemyMetis, "Metis_1159");
				break;
			case 9750:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779750);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711550, EnemyMetis, "Metis_1160");
				break;
			case 9760:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779760);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711560, EnemyMetis, "Metis_1161");
				break;
			case 9770:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779770);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711570, EnemyMetis, "Metis_1162");
				break;
			case 9780:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779780);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711580, EnemyMetis, "Metis_1163");
				break;
			case 9790:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779790);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711590, EnemyMetis, "Metis_1164");
				break;
			case 9800:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779800);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711600, EnemyMetis, "Metis_1165");
				break;
			case 9810:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779810);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711610, EnemyMetis, "Metis_1166");
				break;
			case 9820:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779820);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711620, EnemyMetis, "Metis_1167");
				break;
			case 9830:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779830);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711630, EnemyMetis, "Metis_1168");
				break;
			case 9840:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779840);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711640, EnemyMetis, "Metis_1169");
				break;
			case 9850:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779850);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711650, EnemyMetis, "Metis_1170");
				break;
			case 9860:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779860);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711660, EnemyMetis, "Metis_1171");
				break;
			case 9870:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779870);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711670, EnemyMetis, "Metis_1172");
				break;
			case 9880:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779880);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711680, EnemyMetis, "Metis_1173");
				break;
			case 9890:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779890);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711690, EnemyMetis, "Metis_1174");
				break;
			case 9900:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779900);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711700, EnemyMetis, "Metis_1175");
				break;
			case 9910:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779910);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711710, EnemyMetis, "Metis_1176");
				break;
			case 9920:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779920);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711720, EnemyMetis, "Metis_1177");
				break;
			case 9930:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779930);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711730, EnemyMetis, "Metis_1178");
				break;
			case 9940:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779940);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711740, EnemyMetis, "Metis_1179");
				break;
			case 9950:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779950);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711750, EnemyMetis, "Metis_1180");
				break;
			case 9960:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779960);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711760, EnemyMetis, "Metis_1181");
				break;
			case 9970:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779970);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711770, EnemyMetis, "Metis_1182");
				break;
			case 9980:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779980);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711780, EnemyMetis, "Metis_1183");
				break;
			case 9990:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779990);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711790, EnemyMetis, "Metis_1184");
				break;
			case 10000:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710000);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711800, EnemyMetis, "Metis_1185");
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(2122610000);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1800000;
				pActor->_Y = -100000;
				}
				break;
			case 10010:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710010);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711810, EnemyMetis, "Metis_1186");
				break;
			case 10020:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710020);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711820, EnemyMetis, "Metis_1187");
				break;
			case 10030:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710030);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711830, EnemyMetis, "Metis_1188");
				break;
			case 10040:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710040);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711840, EnemyMetis, "Metis_1189");
				break;
			case 10050:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710050);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711850, EnemyMetis, "Metis_1190");
				break;
			case 10060:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710060);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711860, EnemyMetis, "Metis_1191");
				break;
			case 10070:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710070);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711870, EnemyMetis, "Metis_1192");
				break;
			case 10080:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710080);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711880, EnemyMetis, "Metis_1193");
				break;
			case 10090:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710090);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711890, EnemyMetis, "Metis_1194");
				break;
			case 10100:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710100);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711900, EnemyMetis, "Metis_1195");
				break;
			case 10110:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710110);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711910, EnemyMetis, "Metis_1196");
				break;
			case 10120:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710120);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711920, EnemyMetis, "Metis_1197");
				break;
			case 10130:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710130);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711930, EnemyMetis, "Metis_1198");
				break;
			case 10140:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710140);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711940, EnemyMetis, "Metis_1199");
				break;
			case 10150:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710150);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711950, EnemyMetis, "Metis_1200");
				break;
			case 10160:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710160);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711960, EnemyMetis, "Metis_1201");
				break;
			case 10170:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710170);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711970, EnemyMetis, "Metis_1202");
				break;
			case 10180:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710180);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711980, EnemyMetis, "Metis_1203");
				break;
			case 10190:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710190);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711990, EnemyMetis, "Metis_1204");
				break;
			case 10200:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710200);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712000, EnemyMetis, "Metis_1205");
				break;
			case 10210:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710210);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712010, EnemyMetis, "Metis_1206");
				break;
			case 10220:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710220);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712020, EnemyMetis, "Metis_1207");
				break;
			case 10230:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710230);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712030, EnemyMetis, "Metis_1208");
				break;
			case 10240:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710240);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712040, EnemyMetis, "Metis_1209");
				break;
			case 10250:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710250);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712050, EnemyMetis, "Metis_1210");
				break;
			case 10260:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710260);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712060, EnemyMetis, "Metis_1211");
				break;
			case 10270:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710270);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712070, EnemyMetis, "Metis_1212");
				break;
			case 10280:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710280);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712080, EnemyMetis, "Metis_1213");
				break;
			case 10290:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710290);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712090, EnemyMetis, "Metis_1214");
				break;
			case 10300:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710300);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712100, EnemyMetis, "Metis_1215");
				break;
			case 10310:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710310);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712110, EnemyMetis, "Metis_1216");
				break;
			case 10320:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710320);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712120, EnemyMetis, "Metis_1217");
				break;
			case 10330:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710330);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712130, EnemyMetis, "Metis_1218");
				break;
			case 10340:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710340);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712140, EnemyMetis, "Metis_1219");
				break;
			case 10350:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710350);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712150, EnemyMetis, "Metis_1220");
				break;
			case 10360:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710360);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712160, EnemyMetis, "Metis_1221");
				break;
			case 10370:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710370);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712170, EnemyMetis, "Metis_1222");
				break;
			case 10380:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710380);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712180, EnemyMetis, "Metis_1223");
				break;
			case 10390:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710390);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712190, EnemyMetis, "Metis_1224");
				break;
			case 10400:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710400);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712200, EnemyMetis, "Metis_1225");
				break;
			case 10410:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710410);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712210, EnemyMetis, "Metis_1226");
				break;
			case 10420:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710420);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712220, EnemyMetis, "Metis_1227");
				break;
			case 10430:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710430);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712230, EnemyMetis, "Metis_1228");
				break;
			case 10440:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710440);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712240, EnemyMetis, "Metis_1229");
				break;
			case 10450:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710450);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712250, EnemyMetis, "Metis_1230");
				break;
			case 10460:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710460);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712260, EnemyMetis, "Metis_1231");
				break;
			case 10470:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710470);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712270, EnemyMetis, "Metis_1232");
				break;
			case 10480:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710480);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712280, EnemyMetis, "Metis_1233");
				break;
			case 10490:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710490);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712290, EnemyMetis, "Metis_1234");
				break;
			case 10500:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710500);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712300, EnemyMetis, "Metis_1235");
				break;
			case 10510:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710510);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712310, EnemyMetis, "Metis_1236");
				break;
			case 10520:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710520);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712320, EnemyMetis, "Metis_1237");
				break;
			case 10530:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710530);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712330, EnemyMetis, "Metis_1238");
				break;
			case 10540:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710540);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712340, EnemyMetis, "Metis_1239");
				break;
			case 10550:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710550);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712350, EnemyMetis, "Metis_1240");
				break;
			case 10560:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710560);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712360, EnemyMetis, "Metis_1241");
				break;
			case 10570:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710570);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712370, EnemyMetis, "Metis_1242");
				break;
			case 10580:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710580);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712380, EnemyMetis, "Metis_1243");
				break;
			case 10590:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710590);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712390, EnemyMetis, "Metis_1244");
				break;
			case 10600:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710600);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712400, EnemyMetis, "Metis_1245");
				break;
			case 10610:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710610);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712410, EnemyMetis, "Metis_1246");
				break;
			case 10620:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710620);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712420, EnemyMetis, "Metis_1247");
				break;
			case 10630:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710630);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712430, EnemyMetis, "Metis_1248");
				break;
			case 10640:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710640);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712440, EnemyMetis, "Metis_1249");
				break;
			case 10650:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710650);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712450, EnemyMetis, "Metis_1250");
				break;
			case 10660:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710660);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712460, EnemyMetis, "Metis_1251");
				break;
			case 10670:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710670);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712470, EnemyMetis, "Metis_1252");
				break;
			case 10680:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710680);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712480, EnemyMetis, "Metis_1253");
				break;
			case 10690:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710690);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712490, EnemyMetis, "Metis_1254");
				break;
			case 10700:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710700);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712500, EnemyMetis, "Metis_1255");
				break;
			case 10710:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710710);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712510, EnemyMetis, "Metis_1256");
				break;
			case 10720:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710720);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712520, EnemyMetis, "Metis_1257");
				break;
			case 10730:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710730);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712530, EnemyMetis, "Metis_1258");
				break;
			case 10740:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710740);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712540, EnemyMetis, "Metis_1259");
				break;
			case 10750:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710750);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712550, EnemyMetis, "Metis_1260");
				break;
			case 10760:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710760);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712560, EnemyMetis, "Metis_1261");
				break;
			case 10770:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710770);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712570, EnemyMetis, "Metis_1262");
				break;
			case 10780:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710780);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712580, EnemyMetis, "Metis_1263");
				break;
			case 10790:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710790);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712590, EnemyMetis, "Metis_1264");
				break;
			case 10800:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710800);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712600, EnemyMetis, "Metis_1265");
				break;
			case 10810:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710810);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712610, EnemyMetis, "Metis_1266");
				break;
			case 10820:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710820);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712620, EnemyMetis, "Metis_1267");
				break;
			case 10830:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710830);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712630, EnemyMetis, "Metis_1268");
				break;
			case 10840:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710840);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712640, EnemyMetis, "Metis_1269");
				break;
			case 10850:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710850);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712650, EnemyMetis, "Metis_1270");
				break;
			case 10860:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710860);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712660, EnemyMetis, "Metis_1271");
				break;
			case 10870:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710870);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712670, EnemyMetis, "Metis_1272");
				break;
			case 10880:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710880);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712680, EnemyMetis, "Metis_1273");
				break;
			case 10890:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710890);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712690, EnemyMetis, "Metis_1274");
				break;
			case 10900:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710900);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712700, EnemyMetis, "Metis_1275");
				break;
			case 10910:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710910);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712710, EnemyMetis, "Metis_1276");
				break;
			case 10920:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710920);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712720, EnemyMetis, "Metis_1277");
				break;
			case 10930:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710930);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712730, EnemyMetis, "Metis_1278");
				break;
			case 10940:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710940);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712740, EnemyMetis, "Metis_1279");
				break;
			case 10950:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710950);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712750, EnemyMetis, "Metis_1280");
				break;
			case 10960:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710960);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712760, EnemyMetis, "Metis_1281");
				break;
			case 10970:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710970);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712770, EnemyMetis, "Metis_1282");
				break;
			case 10980:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710980);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712780, EnemyMetis, "Metis_1283");
				break;
			case 10990:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710990);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712790, EnemyMetis, "Metis_1284");
				break;
			case 11000:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711000);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712800, EnemyMetis, "Metis_1285");
				break;
			case 11010:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711010);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712810, EnemyMetis, "Metis_1286");
				break;
			case 11020:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711020);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712820, EnemyMetis, "Metis_1287");
				break;
			case 11030:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711030);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712830, EnemyMetis, "Metis_1288");
				break;
			case 11040:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711040);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712840, EnemyMetis, "Metis_1289");
				break;
			case 11050:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711050);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712850, EnemyMetis, "Metis_1290");
				break;
			case 11060:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711060);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712860, EnemyMetis, "Metis_1291");
				break;
			case 11070:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711070);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712870, EnemyMetis, "Metis_1292");
				break;
			case 11080:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711080);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712880, EnemyMetis, "Metis_1293");
				break;
			case 11090:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711090);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712890, EnemyMetis, "Metis_1294");
				break;
			case 11100:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711100);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712900, EnemyMetis, "Metis_1295");
				break;
			case 11110:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711110);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712910, EnemyMetis, "Metis_1296");
				break;
			case 11120:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711120);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712920, EnemyMetis, "Metis_1297");
				break;
			case 11130:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711130);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712930, EnemyMetis, "Metis_1298");
				break;
			case 11140:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711140);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712940, EnemyMetis, "Metis_1299");
				break;
			case 11150:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711150);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712950, EnemyMetis, "Metis_1300");
				break;
			case 11160:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711160);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712960, EnemyMetis, "Metis_1301");
				break;
			case 11170:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711170);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712970, EnemyMetis, "Metis_1302");
				break;
			case 11180:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711180);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712980, EnemyMetis, "Metis_1303");
				break;
			case 11190:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711190);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712990, EnemyMetis, "Metis_1304");
				break;
			case 11200:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711200);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713000, EnemyMetis, "Metis_1305");
				break;
			case 11210:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711210);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713010, EnemyMetis, "Metis_1306");
				break;
			case 11220:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711220);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713020, EnemyMetis, "Metis_1307");
				break;
			case 11230:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711230);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713030, EnemyMetis, "Metis_1308");
				break;
			case 11240:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711240);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713040, EnemyMetis, "Metis_1309");
				break;
			case 11250:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711250);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713050, EnemyMetis, "Metis_1310");
				break;
			case 11260:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711260);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713060, EnemyMetis, "Metis_1311");
				break;
			case 11270:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711270);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713070, EnemyMetis, "Metis_1312");
				break;
			case 11280:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711280);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713080, EnemyMetis, "Metis_1313");
				break;
			case 11290:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711290);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713090, EnemyMetis, "Metis_1314");
				break;
			case 11300:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711300);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713100, EnemyMetis, "Metis_1315");
				break;
			case 11310:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711310);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713110, EnemyMetis, "Metis_1316");
				break;
			case 11320:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711320);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713120, EnemyMetis, "Metis_1317");
				break;
			case 11330:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711330);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713130, EnemyMetis, "Metis_1318");
				break;
			case 11340:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711340);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713140, EnemyMetis, "Metis_1319");
				break;
			case 11350:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711350);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713150, EnemyMetis, "Metis_1320");
				break;
			case 11360:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711360);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713160, EnemyMetis, "Metis_1321");
				break;
			case 11370:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711370);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713170, EnemyMetis, "Metis_1322");
				break;
			case 11380:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711380);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713180, EnemyMetis, "Metis_1323");
				break;
			case 11390:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711390);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713190, EnemyMetis, "Metis_1324");
				break;
			case 11400:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711400);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713200, EnemyMetis, "Metis_1325");
				break;
			case 11410:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711410);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713210, EnemyMetis, "Metis_1326");
				break;
			case 11420:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711420);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713220, EnemyMetis, "Metis_1327");
				break;
			case 11430:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711430);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713230, EnemyMetis, "Metis_1328");
				break;
			case 11440:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711440);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713240, EnemyMetis, "Metis_1329");
				break;
			case 11450:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711450);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713250, EnemyMetis, "Metis_1330");
				break;
			case 11460:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711460);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713260, EnemyMetis, "Metis_1331");
				break;
			case 11470:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711470);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713270, EnemyMetis, "Metis_1332");
				break;
			case 11480:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711480);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713280, EnemyMetis, "Metis_1333");
				break;
			case 11490:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711490);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713290, EnemyMetis, "Metis_1334");
				break;
			case 11500:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711500);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713300, EnemyMetis, "Metis_1335");
				break;
			case 11510:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711510);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713310, EnemyMetis, "Metis_1336");
				break;
			case 11520:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711520);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713320, EnemyMetis, "Metis_1337");
				break;
			case 11530:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711530);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713330, EnemyMetis, "Metis_1338");
				break;
			case 11540:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711540);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713340, EnemyMetis, "Metis_1339");
				break;
			case 11550:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711550);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713350, EnemyMetis, "Metis_1340");
				break;
			case 11560:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711560);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713360, EnemyMetis, "Metis_1341");
				break;
			case 11570:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711570);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713370, EnemyMetis, "Metis_1342");
				break;
			case 11580:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711580);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713380, EnemyMetis, "Metis_1343");
				break;
			case 11590:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711590);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713390, EnemyMetis, "Metis_1344");
				break;
			case 11600:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711600);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713400, EnemyMetis, "Metis_1345");
				break;
			case 11610:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711610);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713410, EnemyMetis, "Metis_1346");
				break;
			case 11620:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711620);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713420, EnemyMetis, "Metis_1347");
				break;
			case 11630:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711630);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713430, EnemyMetis, "Metis_1348");
				break;
			case 11640:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711640);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713440, EnemyMetis, "Metis_1349");
				break;
			case 11650:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711650);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713450, EnemyMetis, "Metis_1350");
				break;
			case 11660:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711660);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713460, EnemyMetis, "Metis_1351");
				break;
			case 11670:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711670);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713470, EnemyMetis, "Metis_1352");
				break;
			case 11680:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711680);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713480, EnemyMetis, "Metis_1353");
				break;
			case 11690:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711690);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713490, EnemyMetis, "Metis_1354");
				break;
			case 11700:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711700);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713500, EnemyMetis, "Metis_1355");
				break;
			case 11710:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711710);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713510, EnemyMetis, "Metis_1356");
				break;
			case 11720:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711720);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713520, EnemyMetis, "Metis_1357");
				break;
			case 11730:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711730);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713530, EnemyMetis, "Metis_1358");
				break;
			case 11740:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711740);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713540, EnemyMetis, "Metis_1359");
				break;
			case 11750:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711750);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713550, EnemyMetis, "Metis_1360");
				break;
			case 11760:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711760);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713560, EnemyMetis, "Metis_1361");
				break;
			case 11770:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711770);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713570, EnemyMetis, "Metis_1362");
				break;
			case 11780:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711780);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713580, EnemyMetis, "Metis_1363");
				break;
			case 11790:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711790);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713590, EnemyMetis, "Metis_1364");
				break;
			case 11800:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711800);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713600, EnemyMetis, "Metis_1365");
				break;
			case 11810:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711810);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713610, EnemyMetis, "Metis_1366");
				break;
			case 11820:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711820);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713620, EnemyMetis, "Metis_1367");
				break;
			case 11830:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711830);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713630, EnemyMetis, "Metis_1368");
				break;
			case 11840:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711840);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713640, EnemyMetis, "Metis_1369");
				break;
			case 11850:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711850);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713650, EnemyMetis, "Metis_1370");
				break;
			case 11860:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711860);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713660, EnemyMetis, "Metis_1371");
				break;
			case 11870:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711870);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713670, EnemyMetis, "Metis_1372");
				break;
			case 11880:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711880);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713680, EnemyMetis, "Metis_1373");
				break;
			case 11890:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711890);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713690, EnemyMetis, "Metis_1374");
				break;
			case 11900:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711900);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713700, EnemyMetis, "Metis_1375");
				break;
			case 11910:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711910);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713710, EnemyMetis, "Metis_1376");
				break;
			case 11920:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711920);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713720, EnemyMetis, "Metis_1377");
				break;
			case 11930:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711930);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713730, EnemyMetis, "Metis_1378");
				break;
			case 11940:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711940);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713740, EnemyMetis, "Metis_1379");
				break;
			case 11950:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711950);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713750, EnemyMetis, "Metis_1380");
				break;
			case 11960:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711960);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713760, EnemyMetis, "Metis_1381");
				break;
			case 11970:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711970);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713770, EnemyMetis, "Metis_1382");
				break;
			case 11980:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711980);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713780, EnemyMetis, "Metis_1383");
				break;
			case 11990:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711990);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713790, EnemyMetis, "Metis_1384");
				break;
			case 12000:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712000);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713800, EnemyMetis, "Metis_1385");
				break;
			case 12010:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712010);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713810, EnemyMetis, "Metis_1386");
				break;
			case 12020:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712020);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713820, EnemyMetis, "Metis_1387");
				break;
			case 12030:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712030);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713830, EnemyMetis, "Metis_1388");
				break;
			case 12040:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712040);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713840, EnemyMetis, "Metis_1389");
				break;
			case 12050:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712050);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713850, EnemyMetis, "Metis_1390");
				break;
			case 12060:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712060);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713860, EnemyMetis, "Metis_1391");
				break;
			case 12070:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712070);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713870, EnemyMetis, "Metis_1392");
				break;
			case 12080:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712080);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713880, EnemyMetis, "Metis_1393");
				break;
			case 12090:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712090);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713890, EnemyMetis, "Metis_1394");
				break;
			case 12100:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712100);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713900, EnemyMetis, "Metis_1395");
				break;
			case 12110:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712110);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713910, EnemyMetis, "Metis_1396");
				break;
			case 12120:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712120);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713920, EnemyMetis, "Metis_1397");
				break;
			case 12130:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712130);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713930, EnemyMetis, "Metis_1398");
				break;
			case 12140:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712140);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713940, EnemyMetis, "Metis_1399");
				break;
			case 12150:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712150);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713950, EnemyMetis, "Metis_1400");
				break;
			case 12160:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712160);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713960, EnemyMetis, "Metis_1401");
				break;
			case 12170:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712170);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713970, EnemyMetis, "Metis_1402");
				break;
			case 12180:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712180);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713980, EnemyMetis, "Metis_1403");
				break;
			case 12190:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712190);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713990, EnemyMetis, "Metis_1404");
				break;
			case 12200:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712200);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714000, EnemyMetis, "Metis_1405");
				break;
			case 12210:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712210);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714010, EnemyMetis, "Metis_1406");
				break;
			case 12220:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712220);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714020, EnemyMetis, "Metis_1407");
				break;
			case 12230:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712230);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714030, EnemyMetis, "Metis_1408");
				break;
			case 12240:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712240);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714040, EnemyMetis, "Metis_1409");
				break;
			case 12250:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712250);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714050, EnemyMetis, "Metis_1410");
				break;
			case 12260:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712260);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714060, EnemyMetis, "Metis_1411");
				break;
			case 12270:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712270);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714070, EnemyMetis, "Metis_1412");
				break;
			case 12280:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712280);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714080, EnemyMetis, "Metis_1413");
				break;
			case 12290:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712290);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714090, EnemyMetis, "Metis_1414");
				break;
			case 12300:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712300);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714100, EnemyMetis, "Metis_1415");
				break;
			case 12310:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712310);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714110, EnemyMetis, "Metis_1416");
				break;
			case 12320:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712320);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714120, EnemyMetis, "Metis_1417");
				break;
			case 12330:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712330);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714130, EnemyMetis, "Metis_1418");
				break;
			case 12340:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712340);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714140, EnemyMetis, "Metis_1419");
				break;
			case 12350:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712350);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714150, EnemyMetis, "Metis_1420");
				break;
			case 12360:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712360);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714160, EnemyMetis, "Metis_1421");
				break;
			case 12370:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712370);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714170, EnemyMetis, "Metis_1422");
				break;
			case 12380:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712380);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714180, EnemyMetis, "Metis_1423");
				break;
			case 12390:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712390);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714190, EnemyMetis, "Metis_1424");
				break;
			case 12400:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712400);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714200, EnemyMetis, "Metis_1425");
				break;
			case 12410:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712410);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714210, EnemyMetis, "Metis_1426");
				break;
			case 12420:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712420);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714220, EnemyMetis, "Metis_1427");
				break;
			case 12430:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712430);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714230, EnemyMetis, "Metis_1428");
				break;
			case 12440:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712440);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714240, EnemyMetis, "Metis_1429");
				break;
			case 12450:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712450);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714250, EnemyMetis, "Metis_1430");
				break;
			case 12460:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712460);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714260, EnemyMetis, "Metis_1431");
				break;
			case 12470:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712470);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714270, EnemyMetis, "Metis_1432");
				break;
			case 12480:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712480);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714280, EnemyMetis, "Metis_1433");
				break;
			case 12490:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712490);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714290, EnemyMetis, "Metis_1434");
				break;
			case 12500:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712500);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714300, EnemyMetis, "Metis_1435");
				break;
			case 12510:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712510);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714310, EnemyMetis, "Metis_1436");
				break;
			case 12520:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712520);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714320, EnemyMetis, "Metis_1437");
				break;
			case 12530:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712530);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714330, EnemyMetis, "Metis_1438");
				break;
			case 12540:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712540);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714340, EnemyMetis, "Metis_1439");
				break;
			case 12550:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712550);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714350, EnemyMetis, "Metis_1440");
				break;
			case 12560:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712560);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714360, EnemyMetis, "Metis_1441");
				break;
			case 12570:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712570);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714370, EnemyMetis, "Metis_1442");
				break;
			case 12580:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712580);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714380, EnemyMetis, "Metis_1443");
				break;
			case 12590:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712590);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714390, EnemyMetis, "Metis_1444");
				break;
			case 12600:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712600);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714400, EnemyMetis, "Metis_1445");
				break;
			case 12610:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712610);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714410, EnemyMetis, "Metis_1446");
				break;
			case 12620:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712620);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714420, EnemyMetis, "Metis_1447");
				break;
			case 12630:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712630);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714430, EnemyMetis, "Metis_1448");
				break;
			case 12640:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712640);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714440, EnemyMetis, "Metis_1449");
				break;
			case 12650:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712650);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714450, EnemyMetis, "Metis_1450");
				break;
			case 12660:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712660);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714460, EnemyMetis, "Metis_1451");
				break;
			case 12670:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712670);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714470, EnemyMetis, "Metis_1452");
				break;
			case 12680:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712680);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714480, EnemyMetis, "Metis_1453");
				break;
			case 12690:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712690);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714490, EnemyMetis, "Metis_1454");
				break;
			case 12700:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712700);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714500, EnemyMetis, "Metis_1455");
				break;
			case 12710:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712710);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714510, EnemyMetis, "Metis_1456");
				break;
			case 12720:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712720);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714520, EnemyMetis, "Metis_1457");
				break;
			case 12730:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712730);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714530, EnemyMetis, "Metis_1458");
				break;
			case 12740:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712740);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714540, EnemyMetis, "Metis_1459");
				break;
			case 12750:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712750);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714550, EnemyMetis, "Metis_1460");
				break;
			case 12760:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712760);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714560, EnemyMetis, "Metis_1461");
				break;
			case 12770:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712770);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714570, EnemyMetis, "Metis_1462");
				break;
			case 12780:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712780);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714580, EnemyMetis, "Metis_1463");
				break;
			case 12790:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712790);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714590, EnemyMetis, "Metis_1464");
				break;
			case 12800:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712800);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714600, EnemyMetis, "Metis_1465");
				break;
			case 12810:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712810);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714610, EnemyMetis, "Metis_1466");
				break;
			case 12820:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712820);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714620, EnemyMetis, "Metis_1467");
				break;
			case 12830:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712830);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714630, EnemyMetis, "Metis_1468");
				break;
			case 12840:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712840);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714640, EnemyMetis, "Metis_1469");
				break;
			case 12850:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712850);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714650, EnemyMetis, "Metis_1470");
				break;
			case 12860:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712860);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714660, EnemyMetis, "Metis_1471");
				break;
			case 12870:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712870);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714670, EnemyMetis, "Metis_1472");
				break;
			case 12880:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712880);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714680, EnemyMetis, "Metis_1473");
				break;
			case 12890:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712890);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714690, EnemyMetis, "Metis_1474");
				break;
			case 12900:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712900);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714700, EnemyMetis, "Metis_1475");
				break;
			case 12910:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712910);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714710, EnemyMetis, "Metis_1476");
				break;
			case 12920:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712920);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714720, EnemyMetis, "Metis_1477");
				break;
			case 12930:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712930);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714730, EnemyMetis, "Metis_1478");
				break;
			case 12940:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712940);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714740, EnemyMetis, "Metis_1479");
				break;
			case 12950:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712950);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714750, EnemyMetis, "Metis_1480");
				break;
			case 12960:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712960);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714760, EnemyMetis, "Metis_1481");
				break;
			case 12970:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712970);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714770, EnemyMetis, "Metis_1482");
				break;
			case 12980:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712980);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714780, EnemyMetis, "Metis_1483");
				break;
			case 12990:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712990);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714790, EnemyMetis, "Metis_1484");
				break;
			case 13000:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713000);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714800, EnemyMetis, "Metis_1485");
				break;
			case 13010:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713010);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714810, EnemyMetis, "Metis_1486");
				break;
			case 13020:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713020);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714820, EnemyMetis, "Metis_1487");
				break;
			case 13030:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713030);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714830, EnemyMetis, "Metis_1488");
				break;
			case 13040:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713040);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714840, EnemyMetis, "Metis_1489");
				break;
			case 13050:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713050);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714850, EnemyMetis, "Metis_1490");
				break;
			case 13060:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713060);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714860, EnemyMetis, "Metis_1491");
				break;
			case 13070:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713070);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714870, EnemyMetis, "Metis_1492");
				break;
			case 13080:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713080);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714880, EnemyMetis, "Metis_1493");
				break;
			case 13090:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713090);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714890, EnemyMetis, "Metis_1494");
				break;
			case 13100:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713100);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714900, EnemyMetis, "Metis_1495");
				break;
			case 13110:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713110);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714910, EnemyMetis, "Metis_1496");
				break;
			case 13120:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713120);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714920, EnemyMetis, "Metis_1497");
				break;
			case 13130:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713130);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714930, EnemyMetis, "Metis_1498");
				break;
			case 13140:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713140);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714940, EnemyMetis, "Metis_1499");
				break;
			case 13150:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713150);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714950, EnemyMetis, "Metis_1500");
				break;
			case 13160:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713160);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714960, EnemyMetis, "Metis_1501");
				break;
			case 13170:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713170);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714970, EnemyMetis, "Metis_1502");
				break;
			case 13180:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713180);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714980, EnemyMetis, "Metis_1503");
				break;
			case 13190:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713190);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714990, EnemyMetis, "Metis_1504");
				break;
			case 13200:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713200);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715000, EnemyMetis, "Metis_1505");
				break;
			case 13210:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713210);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715010, EnemyMetis, "Metis_1506");
				break;
			case 13220:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713220);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715020, EnemyMetis, "Metis_1507");
				break;
			case 13230:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713230);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715030, EnemyMetis, "Metis_1508");
				break;
			case 13240:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713240);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715040, EnemyMetis, "Metis_1509");
				break;
			case 13250:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713250);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715050, EnemyMetis, "Metis_1510");
				break;
			case 13260:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713260);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715060, EnemyMetis, "Metis_1511");
				break;
			case 13270:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713270);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715070, EnemyMetis, "Metis_1512");
				break;
			case 13280:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713280);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715080, EnemyMetis, "Metis_1513");
				break;
			case 13290:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713290);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715090, EnemyMetis, "Metis_1514");
				break;
			case 13300:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713300);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715100, EnemyMetis, "Metis_1515");
				break;
			case 13310:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713310);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715110, EnemyMetis, "Metis_1516");
				break;
			case 13320:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713320);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715120, EnemyMetis, "Metis_1517");
				break;
			case 13330:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713330);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715130, EnemyMetis, "Metis_1518");
				break;
			case 13340:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713340);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715140, EnemyMetis, "Metis_1519");
				break;
			case 13350:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713350);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715150, EnemyMetis, "Metis_1520");
				break;
			case 13360:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713360);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715160, EnemyMetis, "Metis_1521");
				break;
			case 13370:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713370);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715170, EnemyMetis, "Metis_1522");
				break;
			case 13380:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713380);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715180, EnemyMetis, "Metis_1523");
				break;
			case 13390:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713390);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715190, EnemyMetis, "Metis_1524");
				break;
			case 13400:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713400);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715200, EnemyMetis, "Metis_1525");
				break;
			case 13410:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713410);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715210, EnemyMetis, "Metis_1526");
				break;
			case 13420:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713420);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715220, EnemyMetis, "Metis_1527");
				break;
			case 13430:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713430);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715230, EnemyMetis, "Metis_1528");
				break;
			case 13440:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713440);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715240, EnemyMetis, "Metis_1529");
				break;
			case 13450:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713450);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715250, EnemyMetis, "Metis_1530");
				break;
			case 13460:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713460);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715260, EnemyMetis, "Metis_1531");
				break;
			case 13470:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713470);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715270, EnemyMetis, "Metis_1532");
				break;
			case 13480:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713480);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715280, EnemyMetis, "Metis_1533");
				break;
			case 13490:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713490);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715290, EnemyMetis, "Metis_1534");
				break;
			case 13500:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713500);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715300, EnemyMetis, "Metis_1535");
				break;
			case 13510:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713510);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715310, EnemyMetis, "Metis_1536");
				break;
			case 13520:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713520);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715320, EnemyMetis, "Metis_1537");
				break;
			case 13530:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713530);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715330, EnemyMetis, "Metis_1538");
				break;
			case 13540:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713540);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715340, EnemyMetis, "Metis_1539");
				break;
			case 13550:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713550);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715350, EnemyMetis, "Metis_1540");
				break;
			case 13560:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713560);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715360, EnemyMetis, "Metis_1541");
				break;
			case 13570:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713570);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715370, EnemyMetis, "Metis_1542");
				break;
			case 13580:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713580);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715380, EnemyMetis, "Metis_1543");
				break;
			case 13590:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713590);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715390, EnemyMetis, "Metis_1544");
				break;
			case 13600:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713600);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715400, EnemyMetis, "Metis_1545");
				break;
			case 13610:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713610);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715410, EnemyMetis, "Metis_1546");
				break;
			case 13620:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713620);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715420, EnemyMetis, "Metis_1547");
				break;
			case 13630:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713630);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715430, EnemyMetis, "Metis_1548");
				break;
			case 13640:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713640);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715440, EnemyMetis, "Metis_1549");
				break;
			case 13650:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713650);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715450, EnemyMetis, "Metis_1550");
				break;
			case 13660:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713660);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715460, EnemyMetis, "Metis_1551");
				break;
			case 13670:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713670);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715470, EnemyMetis, "Metis_1552");
				break;
			case 13680:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713680);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715480, EnemyMetis, "Metis_1553");
				break;
			case 13690:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713690);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715490, EnemyMetis, "Metis_1554");
				break;
			case 13700:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713700);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715500, EnemyMetis, "Metis_1555");
				break;
			case 13710:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713710);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715510, EnemyMetis, "Metis_1556");
				break;
			case 13720:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713720);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715520, EnemyMetis, "Metis_1557");
				break;
			case 13730:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713730);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715530, EnemyMetis, "Metis_1558");
				break;
			case 13740:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713740);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715540, EnemyMetis, "Metis_1559");
				break;
			case 13750:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713750);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715550, EnemyMetis, "Metis_1560");
				break;
			case 13760:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713760);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715560, EnemyMetis, "Metis_1561");
				break;
			case 13770:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713770);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715570, EnemyMetis, "Metis_1562");
				break;
			case 13780:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713780);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715580, EnemyMetis, "Metis_1563");
				break;
			case 13790:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713790);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715590, EnemyMetis, "Metis_1564");
				break;
			case 13800:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713800);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715600, EnemyMetis, "Metis_1565");
				break;
			case 13810:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713810);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715610, EnemyMetis, "Metis_1566");
				break;
			case 13820:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713820);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715620, EnemyMetis, "Metis_1567");
				break;
			case 13830:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713830);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715630, EnemyMetis, "Metis_1568");
				break;
			case 13840:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713840);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715640, EnemyMetis, "Metis_1569");
				break;
			case 13850:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713850);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715650, EnemyMetis, "Metis_1570");
				break;
			case 13860:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713860);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715660, EnemyMetis, "Metis_1571");
				break;
			case 13870:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713870);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715670, EnemyMetis, "Metis_1572");
				break;
			case 13880:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713880);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715680, EnemyMetis, "Metis_1573");
				break;
			case 13890:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713890);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715690, EnemyMetis, "Metis_1574");
				break;
			case 13900:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713900);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715700, EnemyMetis, "Metis_1575");
				break;
			case 13910:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713910);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715710, EnemyMetis, "Metis_1576");
				break;
			case 13920:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713920);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715720, EnemyMetis, "Metis_1577");
				break;
			case 13930:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713930);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715730, EnemyMetis, "Metis_1578");
				break;
			case 13940:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713940);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715740, EnemyMetis, "Metis_1579");
				break;
			case 13950:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713950);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715750, EnemyMetis, "Metis_1580");
				break;
			case 13960:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713960);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715760, EnemyMetis, "Metis_1581");
				break;
			case 13970:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713970);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715770, EnemyMetis, "Metis_1582");
				break;
			case 13980:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713980);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715780, EnemyMetis, "Metis_1583");
				break;
			case 13990:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713990);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715790, EnemyMetis, "Metis_1584");
				break;
			case 14000:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714000);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715800, EnemyMetis, "Metis_1585");
				break;
			case 14010:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714010);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715810, EnemyMetis, "Metis_1586");
				break;
			case 14020:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714020);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715820, EnemyMetis, "Metis_1587");
				break;
			case 14030:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714030);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715830, EnemyMetis, "Metis_1588");
				break;
			case 14040:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714040);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715840, EnemyMetis, "Metis_1589");
				break;
			case 14050:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714050);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715850, EnemyMetis, "Metis_1590");
				break;
			case 14060:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714060);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715860, EnemyMetis, "Metis_1591");
				break;
			case 14070:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714070);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715870, EnemyMetis, "Metis_1592");
				break;
			case 14080:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714080);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715880, EnemyMetis, "Metis_1593");
				break;
			case 14090:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714090);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715890, EnemyMetis, "Metis_1594");
				break;
			case 14100:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714100);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715900, EnemyMetis, "Metis_1595");
				break;
			case 14110:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714110);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715910, EnemyMetis, "Metis_1596");
				break;
			case 14120:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714120);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715920, EnemyMetis, "Metis_1597");
				break;
			case 14130:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714130);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715930, EnemyMetis, "Metis_1598");
				break;
			case 14140:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714140);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715940, EnemyMetis, "Metis_1599");
				break;
			case 14150:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714150);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715950, EnemyMetis, "Metis_1600");
				break;
			case 14160:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714160);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715960, EnemyMetis, "Metis_1601");
				break;
			case 14170:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714170);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715970, EnemyMetis, "Metis_1602");
				break;
			case 14180:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714180);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715980, EnemyMetis, "Metis_1603");
				break;
			case 14190:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714190);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715990, EnemyMetis, "Metis_1604");
				break;
			case 14200:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714200);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716000, EnemyMetis, "Metis_1605");
				break;
			case 14210:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714210);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716010, EnemyMetis, "Metis_1606");
				break;
			case 14220:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714220);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716020, EnemyMetis, "Metis_1607");
				break;
			case 14230:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714230);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716030, EnemyMetis, "Metis_1608");
				break;
			case 14240:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714240);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716040, EnemyMetis, "Metis_1609");
				break;
			case 14250:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714250);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716050, EnemyMetis, "Metis_1610");
				break;
			case 14260:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714260);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716060, EnemyMetis, "Metis_1611");
				break;
			case 14270:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714270);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716070, EnemyMetis, "Metis_1612");
				break;
			case 14280:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714280);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716080, EnemyMetis, "Metis_1613");
				break;
			case 14290:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714290);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716090, EnemyMetis, "Metis_1614");
				break;
			case 14300:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714300);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716100, EnemyMetis, "Metis_1615");
				break;
			case 14310:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714310);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716110, EnemyMetis, "Metis_1616");
				break;
			case 14320:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714320);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716120, EnemyMetis, "Metis_1617");
				break;
			case 14330:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714330);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716130, EnemyMetis, "Metis_1618");
				break;
			case 14340:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714340);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716140, EnemyMetis, "Metis_1619");
				break;
			case 14350:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714350);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716150, EnemyMetis, "Metis_1620");
				break;
			case 14360:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714360);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716160, EnemyMetis, "Metis_1621");
				break;
			case 14370:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714370);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716170, EnemyMetis, "Metis_1622");
				break;
			case 14380:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714380);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716180, EnemyMetis, "Metis_1623");
				break;
			case 14390:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714390);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716190, EnemyMetis, "Metis_1624");
				break;
			case 14400:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714400);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716200, EnemyMetis, "Metis_1625");
				break;
			case 14410:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714410);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716210, EnemyMetis, "Metis_1626");
				break;
			case 14420:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714420);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716220, EnemyMetis, "Metis_1627");
				break;
			case 14430:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714430);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716230, EnemyMetis, "Metis_1628");
				break;
			case 14440:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714440);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716240, EnemyMetis, "Metis_1629");
				break;
			case 14450:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714450);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716250, EnemyMetis, "Metis_1630");
				break;
			case 14460:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714460);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716260, EnemyMetis, "Metis_1631");
				break;
			case 14470:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714470);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716270, EnemyMetis, "Metis_1632");
				break;
			case 14480:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714480);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716280, EnemyMetis, "Metis_1633");
				break;
			case 14490:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714490);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716290, EnemyMetis, "Metis_1634");
				break;
			case 14500:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714500);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716300, EnemyMetis, "Metis_1635");
				break;
			case 14510:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714510);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716310, EnemyMetis, "Metis_1636");
				break;
			case 14520:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714520);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716320, EnemyMetis, "Metis_1637");
				break;
			case 14530:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714530);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716330, EnemyMetis, "Metis_1638");
				break;
			case 14540:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714540);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716340, EnemyMetis, "Metis_1639");
				break;
			case 14550:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714550);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716350, EnemyMetis, "Metis_1640");
				break;
			case 14560:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714560);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716360, EnemyMetis, "Metis_1641");
				break;
			case 14570:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714570);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716370, EnemyMetis, "Metis_1642");
				break;
			case 14580:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714580);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716380, EnemyMetis, "Metis_1643");
				break;
			case 14590:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714590);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716390, EnemyMetis, "Metis_1644");
				break;
			case 14600:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714600);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716400, EnemyMetis, "Metis_1645");
				break;
			case 14610:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714610);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716410, EnemyMetis, "Metis_1646");
				break;
			case 14620:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714620);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716420, EnemyMetis, "Metis_1647");
				break;
			case 14630:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714630);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716430, EnemyMetis, "Metis_1648");
				break;
			case 14640:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714640);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716440, EnemyMetis, "Metis_1649");
				break;
			case 14650:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714650);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716450, EnemyMetis, "Metis_1650");
				break;
			case 14660:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714660);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716460, EnemyMetis, "Metis_1651");
				break;
			case 14670:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714670);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716470, EnemyMetis, "Metis_1652");
				break;
			case 14680:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714680);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716480, EnemyMetis, "Metis_1653");
				break;
			case 14690:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714690);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716490, EnemyMetis, "Metis_1654");
				break;
			case 14700:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714700);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716500, EnemyMetis, "Metis_1655");
				break;
			case 14710:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714710);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716510, EnemyMetis, "Metis_1656");
				break;
			case 14720:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714720);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716520, EnemyMetis, "Metis_1657");
				break;
			case 14730:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714730);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716530, EnemyMetis, "Metis_1658");
				break;
			case 14740:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714740);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716540, EnemyMetis, "Metis_1659");
				break;
			case 14750:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714750);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716550, EnemyMetis, "Metis_1660");
				break;
			case 14760:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714760);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716560, EnemyMetis, "Metis_1661");
				break;
			case 14770:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714770);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716570, EnemyMetis, "Metis_1662");
				break;
			case 14780:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714780);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716580, EnemyMetis, "Metis_1663");
				break;
			case 14790:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714790);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716590, EnemyMetis, "Metis_1664");
				break;
			case 14800:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714800);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716600, EnemyMetis, "Metis_1665");
				break;
			case 14810:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714810);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716610, EnemyMetis, "Metis_1666");
				break;
			case 14820:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714820);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716620, EnemyMetis, "Metis_1667");
				break;
			case 14830:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714830);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716630, EnemyMetis, "Metis_1668");
				break;
			case 14840:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714840);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716640, EnemyMetis, "Metis_1669");
				break;
			case 14850:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714850);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716650, EnemyMetis, "Metis_1670");
				break;
			case 14860:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714860);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716660, EnemyMetis, "Metis_1671");
				break;
			case 14870:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714870);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716670, EnemyMetis, "Metis_1672");
				break;
			case 14880:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714880);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716680, EnemyMetis, "Metis_1673");
				break;
			case 14890:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714890);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716690, EnemyMetis, "Metis_1674");
				break;
			case 14900:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714900);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716700, EnemyMetis, "Metis_1675");
				break;
			case 14910:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714910);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716710, EnemyMetis, "Metis_1676");
				break;
			case 14920:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714920);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716720, EnemyMetis, "Metis_1677");
				break;
			case 14930:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714930);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716730, EnemyMetis, "Metis_1678");
				break;
			case 14940:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714940);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716740, EnemyMetis, "Metis_1679");
				break;
			case 14950:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714950);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716750, EnemyMetis, "Metis_1680");
				break;
			case 14960:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714960);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716760, EnemyMetis, "Metis_1681");
				break;
			case 14970:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714970);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716770, EnemyMetis, "Metis_1682");
				break;
			case 14980:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714980);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716780, EnemyMetis, "Metis_1683");
				break;
			case 14990:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714990);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716790, EnemyMetis, "Metis_1684");
				break;
			case 15000:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715000);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716800, EnemyMetis, "Metis_1685");
				break;
			case 15010:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715010);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716810, EnemyMetis, "Metis_1686");
				break;
			case 15020:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715020);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716820, EnemyMetis, "Metis_1687");
				break;
			case 15030:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715030);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716830, EnemyMetis, "Metis_1688");
				break;
			case 15040:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715040);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716840, EnemyMetis, "Metis_1689");
				break;
			case 15050:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715050);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716850, EnemyMetis, "Metis_1690");
				break;
			case 15060:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715060);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716860, EnemyMetis, "Metis_1691");
				break;
			case 15070:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715070);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716870, EnemyMetis, "Metis_1692");
				break;
			case 15080:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715080);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716880, EnemyMetis, "Metis_1693");
				break;
			case 15090:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715090);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716890, EnemyMetis, "Metis_1694");
				break;
			case 15100:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715100);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716900, EnemyMetis, "Metis_1695");
				break;
			case 15110:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715110);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716910, EnemyMetis, "Metis_1696");
				break;
			case 15120:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715120);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716920, EnemyMetis, "Metis_1697");
				break;
			case 15130:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715130);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716930, EnemyMetis, "Metis_1698");
				break;
			case 15140:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715140);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716940, EnemyMetis, "Metis_1699");
				break;
			case 15150:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715150);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716950, EnemyMetis, "Metis_1700");
				break;
			case 15160:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715160);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716960, EnemyMetis, "Metis_1701");
				break;
			case 15170:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715170);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716970, EnemyMetis, "Metis_1702");
				break;
			case 15180:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715180);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716980, EnemyMetis, "Metis_1703");
				break;
			case 15190:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715190);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716990, EnemyMetis, "Metis_1704");
				break;
			case 15200:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715200);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717000, EnemyMetis, "Metis_1705");
				break;
			case 15210:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715210);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717010, EnemyMetis, "Metis_1706");
				break;
			case 15220:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715220);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717020, EnemyMetis, "Metis_1707");
				break;
			case 15230:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715230);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717030, EnemyMetis, "Metis_1708");
				break;
			case 15240:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715240);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717040, EnemyMetis, "Metis_1709");
				break;
			case 15250:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715250);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717050, EnemyMetis, "Metis_1710");
				break;
			case 15260:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715260);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717060, EnemyMetis, "Metis_1711");
				break;
			case 15270:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715270);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717070, EnemyMetis, "Metis_1712");
				break;
			case 15280:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715280);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717080, EnemyMetis, "Metis_1713");
				break;
			case 15290:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715290);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717090, EnemyMetis, "Metis_1714");
				break;
			case 15300:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715300);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717100, EnemyMetis, "Metis_1715");
				break;
			case 15310:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715310);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717110, EnemyMetis, "Metis_1716");
				break;
			case 15320:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715320);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717120, EnemyMetis, "Metis_1717");
				break;
			case 15330:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715330);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717130, EnemyMetis, "Metis_1718");
				break;
			case 15340:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715340);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717140, EnemyMetis, "Metis_1719");
				break;
			case 15350:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715350);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717150, EnemyMetis, "Metis_1720");
				break;
			case 15360:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715360);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717160, EnemyMetis, "Metis_1721");
				break;
			case 15370:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715370);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717170, EnemyMetis, "Metis_1722");
				break;
			case 15380:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715380);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717180, EnemyMetis, "Metis_1723");
				break;
			case 15390:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715390);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717190, EnemyMetis, "Metis_1724");
				break;
			case 15400:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715400);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717200, EnemyMetis, "Metis_1725");
				break;
			case 15410:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715410);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717210, EnemyMetis, "Metis_1726");
				break;
			case 15420:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715420);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717220, EnemyMetis, "Metis_1727");
				break;
			case 15430:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715430);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717230, EnemyMetis, "Metis_1728");
				break;
			case 15440:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715440);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717240, EnemyMetis, "Metis_1729");
				break;
			case 15450:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715450);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717250, EnemyMetis, "Metis_1730");
				break;
			case 15460:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715460);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717260, EnemyMetis, "Metis_1731");
				break;
			case 15470:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715470);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717270, EnemyMetis, "Metis_1732");
				break;
			case 15480:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715480);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717280, EnemyMetis, "Metis_1733");
				break;
			case 15490:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715490);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717290, EnemyMetis, "Metis_1734");
				break;
			case 15500:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715500);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717300, EnemyMetis, "Metis_1735");
				break;
			case 15510:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715510);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717310, EnemyMetis, "Metis_1736");
				break;
			case 15520:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715520);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717320, EnemyMetis, "Metis_1737");
				break;
			case 15530:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715530);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717330, EnemyMetis, "Metis_1738");
				break;
			case 15540:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715540);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717340, EnemyMetis, "Metis_1739");
				break;
			case 15550:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715550);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717350, EnemyMetis, "Metis_1740");
				break;
			case 15560:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715560);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717360, EnemyMetis, "Metis_1741");
				break;
			case 15570:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715570);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717370, EnemyMetis, "Metis_1742");
				break;
			case 15580:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715580);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717380, EnemyMetis, "Metis_1743");
				break;
			case 15590:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715590);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717390, EnemyMetis, "Metis_1744");
				break;
			case 15600:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715600);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717400, EnemyMetis, "Metis_1745");
				break;
			case 15610:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715610);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717410, EnemyMetis, "Metis_1746");
				break;
			case 15620:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715620);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717420, EnemyMetis, "Metis_1747");
				break;
			case 15630:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715630);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717430, EnemyMetis, "Metis_1748");
				break;
			case 15640:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715640);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717440, EnemyMetis, "Metis_1749");
				break;
			case 15650:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715650);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717450, EnemyMetis, "Metis_1750");
				break;
			case 15660:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715660);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717460, EnemyMetis, "Metis_1751");
				break;
			case 15670:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715670);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717470, EnemyMetis, "Metis_1752");
				break;
			case 15680:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715680);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717480, EnemyMetis, "Metis_1753");
				break;
			case 15690:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715690);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717490, EnemyMetis, "Metis_1754");
				break;
			case 15700:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715700);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717500, EnemyMetis, "Metis_1755");
				break;
			case 15710:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715710);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717510, EnemyMetis, "Metis_1756");
				break;
			case 15720:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715720);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717520, EnemyMetis, "Metis_1757");
				break;
			case 15730:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715730);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717530, EnemyMetis, "Metis_1758");
				break;
			case 15740:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715740);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717540, EnemyMetis, "Metis_1759");
				break;
			case 15750:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715750);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717550, EnemyMetis, "Metis_1760");
				break;
			case 15760:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715760);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717560, EnemyMetis, "Metis_1761");
				break;
			case 15770:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715770);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717570, EnemyMetis, "Metis_1762");
				break;
			case 15780:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715780);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717580, EnemyMetis, "Metis_1763");
				break;
			case 15790:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715790);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717590, EnemyMetis, "Metis_1764");
				break;
			case 15800:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715800);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717600, EnemyMetis, "Metis_1765");
				break;
			case 15810:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715810);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717610, EnemyMetis, "Metis_1766");
				break;
			case 15820:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715820);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717620, EnemyMetis, "Metis_1767");
				break;
			case 15830:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715830);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717630, EnemyMetis, "Metis_1768");
				break;
			case 15840:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715840);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717640, EnemyMetis, "Metis_1769");
				break;
			case 15850:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715850);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717650, EnemyMetis, "Metis_1770");
				break;
			case 15860:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715860);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717660, EnemyMetis, "Metis_1771");
				break;
			case 15870:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715870);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717670, EnemyMetis, "Metis_1772");
				break;
			case 15880:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715880);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717680, EnemyMetis, "Metis_1773");
				break;
			case 15890:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715890);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717690, EnemyMetis, "Metis_1774");
				break;
			case 15900:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715900);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717700, EnemyMetis, "Metis_1775");
				break;
			case 15910:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715910);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717710, EnemyMetis, "Metis_1776");
				break;
			case 15920:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715920);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717720, EnemyMetis, "Metis_1777");
				break;
			case 15930:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715930);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717730, EnemyMetis, "Metis_1778");
				break;
			case 15940:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715940);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717740, EnemyMetis, "Metis_1779");
				break;
			case 15950:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715950);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717750, EnemyMetis, "Metis_1780");
				break;
			case 15960:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715960);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717760, EnemyMetis, "Metis_1781");
				break;
			case 15970:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715970);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717770, EnemyMetis, "Metis_1782");
				break;
			case 15980:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715980);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717780, EnemyMetis, "Metis_1783");
				break;
			case 15990:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715990);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717790, EnemyMetis, "Metis_1784");
				break;
			case 16000:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716000);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717800, EnemyMetis, "Metis_1785");
				break;
			case 16010:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716010);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717810, EnemyMetis, "Metis_1786");
				break;
			case 16020:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716020);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717820, EnemyMetis, "Metis_1787");
				break;
			case 16030:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716030);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717830, EnemyMetis, "Metis_1788");
				break;
			case 16040:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716040);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717840, EnemyMetis, "Metis_1789");
				break;
			case 16050:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716050);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717850, EnemyMetis, "Metis_1790");
				break;
			case 16060:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716060);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717860, EnemyMetis, "Metis_1791");
				break;
			case 16070:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716070);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717870, EnemyMetis, "Metis_1792");
				break;
			case 16080:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716080);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717880, EnemyMetis, "Metis_1793");
				break;
			case 16090:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716090);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717890, EnemyMetis, "Metis_1794");
				break;
			case 16100:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716100);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717900, EnemyMetis, "Metis_1795");
				break;
			case 16110:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716110);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717910, EnemyMetis, "Metis_1796");
				break;
			case 16120:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716120);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717920, EnemyMetis, "Metis_1797");
				break;
			case 16130:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716130);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717930, EnemyMetis, "Metis_1798");
				break;
			case 16140:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716140);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717940, EnemyMetis, "Metis_1799");
				break;
			case 16150:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716150);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717950, EnemyMetis, "Metis_1800");
				break;
			case 16160:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716160);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717960, EnemyMetis, "Metis_1801");
				break;
			case 16170:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716170);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717970, EnemyMetis, "Metis_1802");
				break;
			case 16180:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716180);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717980, EnemyMetis, "Metis_1803");
				break;
			case 16190:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716190);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717990, EnemyMetis, "Metis_1804");
				break;
			case 16200:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716200);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718000, EnemyMetis, "Metis_1805");
				break;
			case 16210:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716210);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718010, EnemyMetis, "Metis_1806");
				break;
			case 16220:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716220);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718020, EnemyMetis, "Metis_1807");
				break;
			case 16230:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716230);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718030, EnemyMetis, "Metis_1808");
				break;
			case 16240:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716240);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718040, EnemyMetis, "Metis_1809");
				break;
			case 16250:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716250);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718050, EnemyMetis, "Metis_1810");
				break;
			case 16260:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716260);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718060, EnemyMetis, "Metis_1811");
				break;
			case 16270:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716270);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718070, EnemyMetis, "Metis_1812");
				break;
			case 16280:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716280);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718080, EnemyMetis, "Metis_1813");
				break;
			case 16290:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716290);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718090, EnemyMetis, "Metis_1814");
				break;
			case 16300:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716300);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718100, EnemyMetis, "Metis_1815");
				break;
			case 16310:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716310);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718110, EnemyMetis, "Metis_1816");
				break;
			case 16320:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716320);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718120, EnemyMetis, "Metis_1817");
				break;
			case 16330:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716330);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718130, EnemyMetis, "Metis_1818");
				break;
			case 16340:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716340);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718140, EnemyMetis, "Metis_1819");
				break;
			case 16350:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716350);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718150, EnemyMetis, "Metis_1820");
				break;
			case 16360:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716360);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718160, EnemyMetis, "Metis_1821");
				break;
			case 16370:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716370);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718170, EnemyMetis, "Metis_1822");
				break;
			case 16380:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716380);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718180, EnemyMetis, "Metis_1823");
				break;
			case 16390:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716390);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718190, EnemyMetis, "Metis_1824");
				break;
			case 16400:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716400);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718200, EnemyMetis, "Metis_1825");
				break;
			case 16410:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716410);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718210, EnemyMetis, "Metis_1826");
				break;
			case 16420:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716420);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718220, EnemyMetis, "Metis_1827");
				break;
			case 16430:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716430);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718230, EnemyMetis, "Metis_1828");
				break;
			case 16440:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716440);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718240, EnemyMetis, "Metis_1829");
				break;
			case 16450:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716450);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718250, EnemyMetis, "Metis_1830");
				break;
			case 16460:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716460);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718260, EnemyMetis, "Metis_1831");
				break;
			case 16470:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716470);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718270, EnemyMetis, "Metis_1832");
				break;
			case 16480:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716480);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718280, EnemyMetis, "Metis_1833");
				break;
			case 16490:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716490);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718290, EnemyMetis, "Metis_1834");
				break;
			case 16500:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716500);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718300, EnemyMetis, "Metis_1835");
				break;
			case 16510:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716510);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718310, EnemyMetis, "Metis_1836");
				break;
			case 16520:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716520);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718320, EnemyMetis, "Metis_1837");
				break;
			case 16530:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716530);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718330, EnemyMetis, "Metis_1838");
				break;
			case 16540:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716540);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718340, EnemyMetis, "Metis_1839");
				break;
			case 16550:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716550);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718350, EnemyMetis, "Metis_1840");
				break;
			case 16560:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716560);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718360, EnemyMetis, "Metis_1841");
				break;
			case 16570:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716570);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718370, EnemyMetis, "Metis_1842");
				break;
			case 16580:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716580);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718380, EnemyMetis, "Metis_1843");
				break;
			case 16590:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716590);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718390, EnemyMetis, "Metis_1844");
				break;
			case 16600:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716600);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718400, EnemyMetis, "Metis_1845");
				break;
			case 16610:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716610);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718410, EnemyMetis, "Metis_1846");
				break;
			case 16620:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716620);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718420, EnemyMetis, "Metis_1847");
				break;
			case 16630:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716630);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718430, EnemyMetis, "Metis_1848");
				break;
			case 16640:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716640);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718440, EnemyMetis, "Metis_1849");
				break;
			case 16650:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716650);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718450, EnemyMetis, "Metis_1850");
				break;
			case 16660:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716660);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718460, EnemyMetis, "Metis_1851");
				break;
			case 16670:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716670);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718470, EnemyMetis, "Metis_1852");
				break;
			case 16680:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716680);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718480, EnemyMetis, "Metis_1853");
				break;
			case 16690:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716690);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718490, EnemyMetis, "Metis_1854");
				break;
			case 16700:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716700);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718500, EnemyMetis, "Metis_1855");
				break;
			case 16710:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716710);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718510, EnemyMetis, "Metis_1856");
				break;
			case 16720:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716720);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718520, EnemyMetis, "Metis_1857");
				break;
			case 16730:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716730);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718530, EnemyMetis, "Metis_1858");
				break;
			case 16740:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716740);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718540, EnemyMetis, "Metis_1859");
				break;
			case 16750:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716750);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718550, EnemyMetis, "Metis_1860");
				break;
			case 16760:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716760);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718560, EnemyMetis, "Metis_1861");
				break;
			case 16770:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716770);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718570, EnemyMetis, "Metis_1862");
				break;
			case 16780:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716780);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718580, EnemyMetis, "Metis_1863");
				break;
			case 16790:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716790);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718590, EnemyMetis, "Metis_1864");
				break;
			case 16800:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716800);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718600, EnemyMetis, "Metis_1865");
				break;
			case 16810:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716810);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718610, EnemyMetis, "Metis_1866");
				break;
			case 16820:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716820);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718620, EnemyMetis, "Metis_1867");
				break;
			case 16830:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716830);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718630, EnemyMetis, "Metis_1868");
				break;
			case 16840:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716840);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718640, EnemyMetis, "Metis_1869");
				break;
			case 16850:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716850);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718650, EnemyMetis, "Metis_1870");
				break;
			case 16860:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716860);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718660, EnemyMetis, "Metis_1871");
				break;
			case 16870:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716870);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718670, EnemyMetis, "Metis_1872");
				break;
			case 16880:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716880);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718680, EnemyMetis, "Metis_1873");
				break;
			case 16890:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716890);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718690, EnemyMetis, "Metis_1874");
				break;
			case 16900:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716900);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718700, EnemyMetis, "Metis_1875");
				break;
			case 16910:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716910);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718710, EnemyMetis, "Metis_1876");
				break;
			case 16920:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716920);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718720, EnemyMetis, "Metis_1877");
				break;
			case 16930:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716930);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718730, EnemyMetis, "Metis_1878");
				break;
			case 16940:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716940);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718740, EnemyMetis, "Metis_1879");
				break;
			case 16950:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716950);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718750, EnemyMetis, "Metis_1880");
				break;
			case 16960:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716960);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718760, EnemyMetis, "Metis_1881");
				break;
			case 16970:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716970);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718770, EnemyMetis, "Metis_1882");
				break;
			case 16980:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716980);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718780, EnemyMetis, "Metis_1883");
				break;
			case 16990:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716990);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718790, EnemyMetis, "Metis_1884");
				break;
			case 17000:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717000);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718800, EnemyMetis, "Metis_1885");
				break;
			case 17010:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717010);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718810, EnemyMetis, "Metis_1886");
				break;
			case 17020:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717020);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718820, EnemyMetis, "Metis_1887");
				break;
			case 17030:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717030);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718830, EnemyMetis, "Metis_1888");
				break;
			case 17040:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717040);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718840, EnemyMetis, "Metis_1889");
				break;
			case 17050:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717050);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718850, EnemyMetis, "Metis_1890");
				break;
			case 17060:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717060);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718860, EnemyMetis, "Metis_1891");
				break;
			case 17070:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717070);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718870, EnemyMetis, "Metis_1892");
				break;
			case 17080:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717080);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718880, EnemyMetis, "Metis_1893");
				break;
			case 17090:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717090);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718890, EnemyMetis, "Metis_1894");
				break;
			case 17100:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717100);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718900, EnemyMetis, "Metis_1895");
				break;
			case 17110:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717110);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718910, EnemyMetis, "Metis_1896");
				break;
			case 17120:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717120);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718920, EnemyMetis, "Metis_1897");
				break;
			case 17130:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717130);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718930, EnemyMetis, "Metis_1898");
				break;
			case 17140:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717140);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718940, EnemyMetis, "Metis_1899");
				break;
			case 17150:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717150);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718950, EnemyMetis, "Metis_1900");
				break;
			case 17160:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717160);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718960, EnemyMetis, "Metis_1901");
				break;
			case 17170:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717170);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718970, EnemyMetis, "Metis_1902");
				break;
			case 17180:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717180);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718980, EnemyMetis, "Metis_1903");
				break;
			case 17190:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717190);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718990, EnemyMetis, "Metis_1904");
				break;
			case 17200:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717200);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719000, EnemyMetis, "Metis_1905");
				break;
			case 17210:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717210);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719010, EnemyMetis, "Metis_1906");
				break;
			case 17220:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717220);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719020, EnemyMetis, "Metis_1907");
				break;
			case 17230:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717230);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719030, EnemyMetis, "Metis_1908");
				break;
			case 17240:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717240);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719040, EnemyMetis, "Metis_1909");
				break;
			case 17250:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717250);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719050, EnemyMetis, "Metis_1910");
				break;
			case 17260:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717260);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719060, EnemyMetis, "Metis_1911");
				break;
			case 17270:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717270);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719070, EnemyMetis, "Metis_1912");
				break;
			case 17280:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717280);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719080, EnemyMetis, "Metis_1913");
				break;
			case 17290:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717290);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719090, EnemyMetis, "Metis_1914");
				break;
			case 17300:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717300);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719100, EnemyMetis, "Metis_1915");
				break;
			case 17310:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717310);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719110, EnemyMetis, "Metis_1916");
				break;
			case 17320:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717320);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719120, EnemyMetis, "Metis_1917");
				break;
			case 17330:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717330);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719130, EnemyMetis, "Metis_1918");
				break;
			case 17340:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717340);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719140, EnemyMetis, "Metis_1919");
				break;
			case 17350:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717350);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719150, EnemyMetis, "Metis_1920");
				break;
			case 17360:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717360);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719160, EnemyMetis, "Metis_1921");
				break;
			case 17370:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717370);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719170, EnemyMetis, "Metis_1922");
				break;
			case 17380:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717380);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719180, EnemyMetis, "Metis_1923");
				break;
			case 17390:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717390);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719190, EnemyMetis, "Metis_1924");
				break;
			case 17400:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717400);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719200, EnemyMetis, "Metis_1925");
				break;
			case 17410:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717410);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719210, EnemyMetis, "Metis_1926");
				break;
			case 17420:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717420);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719220, EnemyMetis, "Metis_1927");
				break;
			case 17430:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717430);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719230, EnemyMetis, "Metis_1928");
				break;
			case 17440:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717440);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719240, EnemyMetis, "Metis_1929");
				break;
			case 17450:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717450);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719250, EnemyMetis, "Metis_1930");
				break;
			case 17460:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717460);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719260, EnemyMetis, "Metis_1931");
				break;
			case 17470:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717470);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719270, EnemyMetis, "Metis_1932");
				break;
			case 17480:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717480);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719280, EnemyMetis, "Metis_1933");
				break;
			case 17490:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717490);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719290, EnemyMetis, "Metis_1934");
				break;
			case 17500:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717500);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719300, EnemyMetis, "Metis_1935");
				break;
			case 17510:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717510);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719310, EnemyMetis, "Metis_1936");
				break;
			case 17520:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717520);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719320, EnemyMetis, "Metis_1937");
				break;
			case 17530:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717530);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719330, EnemyMetis, "Metis_1938");
				break;
			case 17540:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717540);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719340, EnemyMetis, "Metis_1939");
				break;
			case 17550:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717550);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719350, EnemyMetis, "Metis_1940");
				break;
			case 17560:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717560);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719360, EnemyMetis, "Metis_1941");
				break;
			case 17570:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717570);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719370, EnemyMetis, "Metis_1942");
				break;
			case 17580:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717580);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719380, EnemyMetis, "Metis_1943");
				break;
			case 17590:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717590);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719390, EnemyMetis, "Metis_1944");
				break;
			case 17600:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717600);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719400, EnemyMetis, "Metis_1945");
				break;
			case 17610:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717610);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719410, EnemyMetis, "Metis_1946");
				break;
			case 17620:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717620);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719420, EnemyMetis, "Metis_1947");
				break;
			case 17630:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717630);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719430, EnemyMetis, "Metis_1948");
				break;
			case 17640:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717640);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719440, EnemyMetis, "Metis_1949");
				break;
			case 17650:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717650);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719450, EnemyMetis, "Metis_1950");
				break;
			case 17660:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717660);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719460, EnemyMetis, "Metis_1951");
				break;
			case 17670:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717670);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719470, EnemyMetis, "Metis_1952");
				break;
			case 17680:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717680);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719480, EnemyMetis, "Metis_1953");
				break;
			case 17690:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717690);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719490, EnemyMetis, "Metis_1954");
				break;
			case 17700:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717700);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719500, EnemyMetis, "Metis_1955");
				break;
			case 17710:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717710);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719510, EnemyMetis, "Metis_1956");
				break;
			case 17720:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717720);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719520, EnemyMetis, "Metis_1957");
				break;
			case 17730:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717730);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719530, EnemyMetis, "Metis_1958");
				break;
			case 17740:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717740);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719540, EnemyMetis, "Metis_1959");
				break;
			case 17750:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717750);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719550, EnemyMetis, "Metis_1960");
				break;
			case 17760:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717760);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719560, EnemyMetis, "Metis_1961");
				break;
			case 17770:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717770);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719570, EnemyMetis, "Metis_1962");
				break;
			case 17780:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717780);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719580, EnemyMetis, "Metis_1963");
				break;
			case 17790:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717790);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719590, EnemyMetis, "Metis_1964");
				break;
			case 17800:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717800);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719600, EnemyMetis, "Metis_1965");
				break;
			case 17810:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717810);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719610, EnemyMetis, "Metis_1966");
				break;
			case 17820:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717820);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719620, EnemyMetis, "Metis_1967");
				break;
			case 17830:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717830);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719630, EnemyMetis, "Metis_1968");
				break;
			case 17840:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717840);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719640, EnemyMetis, "Metis_1969");
				break;
			case 17850:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717850);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719650, EnemyMetis, "Metis_1970");
				break;
			case 17860:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717860);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719660, EnemyMetis, "Metis_1971");
				break;
			case 17870:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717870);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719670, EnemyMetis, "Metis_1972");
				break;
			case 17880:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717880);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719680, EnemyMetis, "Metis_1973");
				break;
			case 17890:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717890);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719690, EnemyMetis, "Metis_1974");
				break;
			case 17900:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717900);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719700, EnemyMetis, "Metis_1975");
				break;
			case 17910:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717910);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719710, EnemyMetis, "Metis_1976");
				break;
			case 17920:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717920);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719720, EnemyMetis, "Metis_1977");
				break;
			case 17930:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717930);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719730, EnemyMetis, "Metis_1978");
				break;
			case 17940:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717940);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719740, EnemyMetis, "Metis_1979");
				break;
			case 17950:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717950);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719750, EnemyMetis, "Metis_1980");
				break;
			case 17960:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717960);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719760, EnemyMetis, "Metis_1981");
				break;
			case 17970:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717970);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719770, EnemyMetis, "Metis_1982");
				break;
			case 17980:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717980);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719780, EnemyMetis, "Metis_1983");
				break;
			case 17990:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717990);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719790, EnemyMetis, "Metis_1984");
				break;
			case 18000:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718000);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719800, EnemyMetis, "Metis_1985");
				break;
			case 18010:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718010);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719810, EnemyMetis, "Metis_1986");
				break;
			case 18020:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718020);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719820, EnemyMetis, "Metis_1987");
				break;
			case 18030:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718030);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719830, EnemyMetis, "Metis_1988");
				break;
			case 18040:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718040);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719840, EnemyMetis, "Metis_1989");
				break;
			case 18050:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718050);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719850, EnemyMetis, "Metis_1990");
				break;
			case 18060:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718060);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719860, EnemyMetis, "Metis_1991");
				break;
			case 18070:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718070);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719870, EnemyMetis, "Metis_1992");
				break;
			case 18080:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718080);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719880, EnemyMetis, "Metis_1993");
				break;
			case 18090:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718090);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719890, EnemyMetis, "Metis_1994");
				break;
			case 18100:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718100);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719900, EnemyMetis, "Metis_1995");
				break;
			case 18110:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718110);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719910, EnemyMetis, "Metis_1996");
				break;
			case 18120:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718120);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719920, EnemyMetis, "Metis_1997");
				break;
			case 18130:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718130);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719930, EnemyMetis, "Metis_1998");
				break;
			case 18140:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718140);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719940, EnemyMetis, "Metis_1999");
				break;
			case 18150:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718150);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719950, EnemyMetis, "Metis_2000");
				break;
			case 18160:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718160);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719960, EnemyMetis, "Metis_2001");
				break;
			case 18170:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718170);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719970, EnemyMetis, "Metis_2002");
				break;
			case 18180:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718180);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719980, EnemyMetis, "Metis_2003");
				break;
			case 18190:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718190);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719990, EnemyMetis, "Metis_2004");
				break;
			case 18200:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718200);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720000, EnemyMetis, "Metis_2005");
				break;
			case 18210:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718210);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720010, EnemyMetis, "Metis_2006");
				break;
			case 18220:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718220);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720020, EnemyMetis, "Metis_2007");
				break;
			case 18230:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718230);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720030, EnemyMetis, "Metis_2008");
				break;
			case 18240:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718240);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720040, EnemyMetis, "Metis_2009");
				break;
			case 18250:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718250);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720050, EnemyMetis, "Metis_2010");
				break;
			case 18260:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718260);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720060, EnemyMetis, "Metis_2011");
				break;
			case 18270:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718270);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720070, EnemyMetis, "Metis_2012");
				break;
			case 18280:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718280);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720080, EnemyMetis, "Metis_2013");
				break;
			case 18290:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718290);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720090, EnemyMetis, "Metis_2014");
				break;
			case 18300:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718300);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720100, EnemyMetis, "Metis_2015");
				break;
			case 18310:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718310);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720110, EnemyMetis, "Metis_2016");
				break;
			case 18320:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718320);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720120, EnemyMetis, "Metis_2017");
				break;
			case 18330:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718330);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720130, EnemyMetis, "Metis_2018");
				break;
			case 18340:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718340);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720140, EnemyMetis, "Metis_2019");
				break;
			case 18350:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718350);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720150, EnemyMetis, "Metis_2020");
				break;
			case 18360:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718360);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720160, EnemyMetis, "Metis_2021");
				break;
			case 18370:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718370);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720170, EnemyMetis, "Metis_2022");
				break;
			case 18380:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718380);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720180, EnemyMetis, "Metis_2023");
				break;
			case 18390:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718390);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720190, EnemyMetis, "Metis_2024");
				break;
			case 18400:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718400);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720200, EnemyMetis, "Metis_2025");
				break;
			case 18410:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718410);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720210, EnemyMetis, "Metis_2026");
				break;
			case 18420:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718420);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720220, EnemyMetis, "Metis_2027");
				break;
			case 18430:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718430);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720230, EnemyMetis, "Metis_2028");
				break;
			case 18440:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718440);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720240, EnemyMetis, "Metis_2029");
				break;
			case 18450:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718450);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720250, EnemyMetis, "Metis_2030");
				break;
			case 18460:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718460);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720260, EnemyMetis, "Metis_2031");
				break;
			case 18470:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718470);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720270, EnemyMetis, "Metis_2032");
				break;
			case 18480:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718480);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720280, EnemyMetis, "Metis_2033");
				break;
			case 18490:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718490);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720290, EnemyMetis, "Metis_2034");
				break;
			case 18500:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718500);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720300, EnemyMetis, "Metis_2035");
				break;
			case 18510:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718510);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720310, EnemyMetis, "Metis_2036");
				break;
			case 18520:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718520);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720320, EnemyMetis, "Metis_2037");
				break;
			case 18530:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718530);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720330, EnemyMetis, "Metis_2038");
				break;
			case 18540:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718540);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720340, EnemyMetis, "Metis_2039");
				break;
			case 18550:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718550);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720350, EnemyMetis, "Metis_2040");
				break;
			case 18560:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718560);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720360, EnemyMetis, "Metis_2041");
				break;
			case 18570:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718570);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720370, EnemyMetis, "Metis_2042");
				break;
			case 18580:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718580);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720380, EnemyMetis, "Metis_2043");
				break;
			case 18590:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718590);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720390, EnemyMetis, "Metis_2044");
				break;
			case 18600:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718600);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720400, EnemyMetis, "Metis_2045");
				break;
			case 18610:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718610);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720410, EnemyMetis, "Metis_2046");
				break;
			case 18620:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718620);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720420, EnemyMetis, "Metis_2047");
				break;
			case 18630:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718630);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720430, EnemyMetis, "Metis_2048");
				break;
			case 18640:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718640);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720440, EnemyMetis, "Metis_2049");
				break;
			case 18650:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718650);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720450, EnemyMetis, "Metis_2050");
				break;
			case 18660:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718660);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720460, EnemyMetis, "Metis_2051");
				break;
			case 18670:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718670);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720470, EnemyMetis, "Metis_2052");
				break;
			case 18680:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718680);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720480, EnemyMetis, "Metis_2053");
				break;
			case 18690:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718690);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720490, EnemyMetis, "Metis_2054");
				break;
			case 18700:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718700);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720500, EnemyMetis, "Metis_2055");
				break;
			case 18710:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718710);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720510, EnemyMetis, "Metis_2056");
				break;
			case 18720:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718720);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720520, EnemyMetis, "Metis_2057");
				break;
			case 18730:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718730);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720530, EnemyMetis, "Metis_2058");
				break;
			case 18740:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718740);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720540, EnemyMetis, "Metis_2059");
				break;
			case 18750:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718750);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720550, EnemyMetis, "Metis_2060");
				break;
			case 18760:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718760);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720560, EnemyMetis, "Metis_2061");
				break;
			case 18770:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718770);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720570, EnemyMetis, "Metis_2062");
				break;
			case 18780:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718780);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720580, EnemyMetis, "Metis_2063");
				break;
			case 18790:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718790);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720590, EnemyMetis, "Metis_2064");
				break;
			case 18800:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718800);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720600, EnemyMetis, "Metis_2065");
				break;
			case 18810:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718810);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720610, EnemyMetis, "Metis_2066");
				break;
			case 18820:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718820);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720620, EnemyMetis, "Metis_2067");
				break;
			case 18830:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718830);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720630, EnemyMetis, "Metis_2068");
				break;
			case 18840:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718840);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720640, EnemyMetis, "Metis_2069");
				break;
			case 18850:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718850);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720650, EnemyMetis, "Metis_2070");
				break;
			case 18860:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718860);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720660, EnemyMetis, "Metis_2071");
				break;
			case 18870:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718870);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720670, EnemyMetis, "Metis_2072");
				break;
			case 18880:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718880);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720680, EnemyMetis, "Metis_2073");
				break;
			case 18890:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718890);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720690, EnemyMetis, "Metis_2074");
				break;
			case 18900:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718900);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720700, EnemyMetis, "Metis_2075");
				break;
			case 18910:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718910);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720710, EnemyMetis, "Metis_2076");
				break;
			case 18920:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718920);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720720, EnemyMetis, "Metis_2077");
				break;
			case 18930:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718930);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720730, EnemyMetis, "Metis_2078");
				break;
			case 18940:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718940);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720740, EnemyMetis, "Metis_2079");
				break;
			case 18950:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718950);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720750, EnemyMetis, "Metis_2080");
				break;
			case 18960:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718960);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720760, EnemyMetis, "Metis_2081");
				break;
			case 18970:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718970);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720770, EnemyMetis, "Metis_2082");
				break;
			case 18980:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718980);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720780, EnemyMetis, "Metis_2083");
				break;
			case 18990:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718990);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720790, EnemyMetis, "Metis_2084");
				break;
			case 19000:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719000);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720800, EnemyMetis, "Metis_2085");
				break;
			case 19010:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719010);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720810, EnemyMetis, "Metis_2086");
				break;
			case 19020:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719020);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720820, EnemyMetis, "Metis_2087");
				break;
			case 19030:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719030);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720830, EnemyMetis, "Metis_2088");
				break;
			case 19040:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719040);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720840, EnemyMetis, "Metis_2089");
				break;
			case 19050:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719050);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720850, EnemyMetis, "Metis_2090");
				break;
			case 19060:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719060);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720860, EnemyMetis, "Metis_2091");
				break;
			case 19070:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719070);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720870, EnemyMetis, "Metis_2092");
				break;
			case 19080:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719080);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720880, EnemyMetis, "Metis_2093");
				break;
			case 19090:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719090);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720890, EnemyMetis, "Metis_2094");
				break;
			case 19100:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719100);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720900, EnemyMetis, "Metis_2095");
				break;
			case 19110:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719110);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720910, EnemyMetis, "Metis_2096");
				break;
			case 19120:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719120);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720920, EnemyMetis, "Metis_2097");
				break;
			case 19130:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719130);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720930, EnemyMetis, "Metis_2098");
				break;
			case 19140:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719140);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720940, EnemyMetis, "Metis_2099");
				break;
			case 19150:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719150);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720950, EnemyMetis, "Metis_2100");
				break;
			case 19160:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719160);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720960, EnemyMetis, "Metis_2101");
				break;
			case 19170:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719170);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720970, EnemyMetis, "Metis_2102");
				break;
			case 19180:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719180);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720980, EnemyMetis, "Metis_2103");
				break;
			case 19190:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719190);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720990, EnemyMetis, "Metis_2104");
				break;
			case 19200:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719200);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721000, EnemyMetis, "Metis_2105");
				break;
			case 19210:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719210);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721010, EnemyMetis, "Metis_2106");
				break;
			case 19220:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719220);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721020, EnemyMetis, "Metis_2107");
				break;
			case 19230:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719230);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721030, EnemyMetis, "Metis_2108");
				break;
			case 19240:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719240);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721040, EnemyMetis, "Metis_2109");
				break;
			case 19250:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719250);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721050, EnemyMetis, "Metis_2110");
				break;
			case 19260:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719260);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721060, EnemyMetis, "Metis_2111");
				break;
			case 19270:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719270);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721070, EnemyMetis, "Metis_2112");
				break;
			case 19280:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719280);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721080, EnemyMetis, "Metis_2113");
				break;
			case 19290:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719290);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721090, EnemyMetis, "Metis_2114");
				break;
			case 19300:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719300);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721100, EnemyMetis, "Metis_2115");
				break;
			case 19310:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719310);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721110, EnemyMetis, "Metis_2116");
				break;
			case 19320:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719320);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721120, EnemyMetis, "Metis_2117");
				break;
			case 19330:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719330);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721130, EnemyMetis, "Metis_2118");
				break;
			case 19340:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719340);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721140, EnemyMetis, "Metis_2119");
				break;
			case 19350:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719350);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721150, EnemyMetis, "Metis_2120");
				break;
			case 19360:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719360);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721160, EnemyMetis, "Metis_2121");
				break;
			case 19370:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719370);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721170, EnemyMetis, "Metis_2122");
				break;
			case 19380:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719380);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721180, EnemyMetis, "Metis_2123");
				break;
			case 19390:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719390);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721190, EnemyMetis, "Metis_2124");
				break;
			case 19400:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719400);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721200, EnemyMetis, "Metis_2125");
				break;
			case 19410:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719410);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721210, EnemyMetis, "Metis_2126");
				break;
			case 19420:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719420);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721220, EnemyMetis, "Metis_2127");
				break;
			case 19430:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719430);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721230, EnemyMetis, "Metis_2128");
				break;
			case 19440:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719440);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721240, EnemyMetis, "Metis_2129");
				break;
			case 19450:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719450);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721250, EnemyMetis, "Metis_2130");
				break;
			case 19460:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719460);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721260, EnemyMetis, "Metis_2131");
				break;
			case 19470:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719470);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721270, EnemyMetis, "Metis_2132");
				break;
			case 19480:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719480);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721280, EnemyMetis, "Metis_2133");
				break;
			case 19490:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719490);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721290, EnemyMetis, "Metis_2134");
				break;
			case 19500:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719500);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721300, EnemyMetis, "Metis_2135");
				break;
			case 19510:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719510);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721310, EnemyMetis, "Metis_2136");
				break;
			case 19520:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719520);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721320, EnemyMetis, "Metis_2137");
				break;
			case 19530:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719530);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721330, EnemyMetis, "Metis_2138");
				break;
			case 19540:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719540);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721340, EnemyMetis, "Metis_2139");
				break;
			case 19550:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719550);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721350, EnemyMetis, "Metis_2140");
				break;
			case 19560:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719560);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721360, EnemyMetis, "Metis_2141");
				break;
			case 19570:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719570);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721370, EnemyMetis, "Metis_2142");
				break;
			case 19580:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719580);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721380, EnemyMetis, "Metis_2143");
				break;
			case 19590:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719590);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721390, EnemyMetis, "Metis_2144");
				break;
			case 19600:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719600);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721400, EnemyMetis, "Metis_2145");
				break;
			case 19610:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719610);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721410, EnemyMetis, "Metis_2146");
				break;
			case 19620:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719620);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721420, EnemyMetis, "Metis_2147");
				break;
			case 19630:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719630);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721430, EnemyMetis, "Metis_2148");
				break;
			case 19640:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719640);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721440, EnemyMetis, "Metis_2149");
				break;
			case 19650:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719650);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721450, EnemyMetis, "Metis_2150");
				break;
			case 19660:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719660);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721460, EnemyMetis, "Metis_2151");
				break;
			case 19670:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719670);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721470, EnemyMetis, "Metis_2152");
				break;
			case 19680:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719680);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721480, EnemyMetis, "Metis_2153");
				break;
			case 19690:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719690);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721490, EnemyMetis, "Metis_2154");
				break;
			case 19700:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719700);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721500, EnemyMetis, "Metis_2155");
				break;
			case 19710:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719710);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721510, EnemyMetis, "Metis_2156");
				break;
			case 19720:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719720);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721520, EnemyMetis, "Metis_2157");
				break;
			case 19730:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719730);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721530, EnemyMetis, "Metis_2158");
				break;
			case 19740:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719740);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721540, EnemyMetis, "Metis_2159");
				break;
			case 19750:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719750);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721550, EnemyMetis, "Metis_2160");
				break;
			case 19760:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719760);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721560, EnemyMetis, "Metis_2161");
				break;
			case 19770:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719770);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721570, EnemyMetis, "Metis_2162");
				break;
			case 19780:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719780);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721580, EnemyMetis, "Metis_2163");
				break;
			case 19790:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719790);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721590, EnemyMetis, "Metis_2164");
				break;
			case 19800:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719800);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721600, EnemyMetis, "Metis_2165");
				break;
			case 19810:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719810);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721610, EnemyMetis, "Metis_2166");
				break;
			case 19820:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719820);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721620, EnemyMetis, "Metis_2167");
				break;
			case 19830:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719830);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721630, EnemyMetis, "Metis_2168");
				break;
			case 19840:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719840);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721640, EnemyMetis, "Metis_2169");
				break;
			case 19850:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719850);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721650, EnemyMetis, "Metis_2170");
				break;
			case 19860:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719860);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721660, EnemyMetis, "Metis_2171");
				break;
			case 19870:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719870);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721670, EnemyMetis, "Metis_2172");
				break;
			case 19880:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719880);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721680, EnemyMetis, "Metis_2173");
				break;
			case 19890:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719890);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721690, EnemyMetis, "Metis_2174");
				break;
			case 19900:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719900);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721700, EnemyMetis, "Metis_2175");
				break;
			case 19910:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719910);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721710, EnemyMetis, "Metis_2176");
				break;
			case 19920:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719920);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721720, EnemyMetis, "Metis_2177");
				break;
			case 19930:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719930);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721730, EnemyMetis, "Metis_2178");
				break;
			case 19940:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719940);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721740, EnemyMetis, "Metis_2179");
				break;
			case 19950:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719950);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721750, EnemyMetis, "Metis_2180");
				break;
			case 19960:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719960);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721760, EnemyMetis, "Metis_2181");
				break;
			case 19970:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719970);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721770, EnemyMetis, "Metis_2182");
				break;
			case 19980:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719980);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721780, EnemyMetis, "Metis_2183");
				break;
			case 19990:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719990);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721790, EnemyMetis, "Metis_2184");
				break;
			case 20000:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720000);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721800, EnemyMetis, "Metis_2185");
				break;
			case 20010:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720010);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721810, EnemyMetis, "Metis_2186");
				break;
			case 20020:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720020);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721820, EnemyMetis, "Metis_2187");
				break;
			case 20030:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720030);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721830, EnemyMetis, "Metis_2188");
				break;
			case 20040:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720040);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721840, EnemyMetis, "Metis_2189");
				break;
			case 20050:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720050);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721850, EnemyMetis, "Metis_2190");
				break;
			case 20060:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720060);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721860, EnemyMetis, "Metis_2191");
				break;
			case 20070:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720070);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721870, EnemyMetis, "Metis_2192");
				break;
			case 20080:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720080);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721880, EnemyMetis, "Metis_2193");
				break;
			case 20090:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720090);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721890, EnemyMetis, "Metis_2194");
				break;
			case 20100:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720100);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721900, EnemyMetis, "Metis_2195");
				break;
			case 20110:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720110);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721910, EnemyMetis, "Metis_2196");
				break;
			case 20120:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720120);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721920, EnemyMetis, "Metis_2197");
				break;
			case 20130:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720130);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721930, EnemyMetis, "Metis_2198");
				break;
			case 20140:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720140);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721940, EnemyMetis, "Metis_2199");
				break;
			case 20150:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720150);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721950, EnemyMetis, "Metis_2200");
				break;
			case 20160:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720160);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721960, EnemyMetis, "Metis_2201");
				break;
			case 20170:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720170);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721970, EnemyMetis, "Metis_2202");
				break;
			case 20180:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720180);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721980, EnemyMetis, "Metis_2203");
				break;
			case 20190:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720190);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721990, EnemyMetis, "Metis_2204");
				break;
			case 20200:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720200);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722000, EnemyMetis, "Metis_2205");
				break;
			case 20210:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720210);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722010, EnemyMetis, "Metis_2206");
				break;
			case 20220:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720220);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722020, EnemyMetis, "Metis_2207");
				break;
			case 20230:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720230);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722030, EnemyMetis, "Metis_2208");
				break;
			case 20240:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720240);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722040, EnemyMetis, "Metis_2209");
				break;
			case 20250:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720250);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722050, EnemyMetis, "Metis_2210");
				break;
			case 20260:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720260);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722060, EnemyMetis, "Metis_2211");
				break;
			case 20270:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720270);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722070, EnemyMetis, "Metis_2212");
				break;
			case 20280:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720280);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722080, EnemyMetis, "Metis_2213");
				break;
			case 20290:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720290);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722090, EnemyMetis, "Metis_2214");
				break;
			case 20300:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720300);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722100, EnemyMetis, "Metis_2215");
				break;
			case 20310:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720310);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722110, EnemyMetis, "Metis_2216");
				break;
			case 20320:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720320);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722120, EnemyMetis, "Metis_2217");
				break;
			case 20330:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720330);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722130, EnemyMetis, "Metis_2218");
				break;
			case 20340:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720340);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722140, EnemyMetis, "Metis_2219");
				break;
			case 20350:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720350);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722150, EnemyMetis, "Metis_2220");
				break;
			case 20360:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720360);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722160, EnemyMetis, "Metis_2221");
				break;
			case 20370:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720370);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722170, EnemyMetis, "Metis_2222");
				break;
			case 20380:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720380);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722180, EnemyMetis, "Metis_2223");
				break;
			case 20390:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720390);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722190, EnemyMetis, "Metis_2224");
				break;
			case 20400:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720400);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722200, EnemyMetis, "Metis_2225");
				break;
			case 20410:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720410);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722210, EnemyMetis, "Metis_2226");
				break;
			case 20420:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720420);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722220, EnemyMetis, "Metis_2227");
				break;
			case 20430:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720430);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722230, EnemyMetis, "Metis_2228");
				break;
			case 20440:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720440);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722240, EnemyMetis, "Metis_2229");
				break;
			case 20450:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720450);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722250, EnemyMetis, "Metis_2230");
				break;
			case 20460:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720460);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722260, EnemyMetis, "Metis_2231");
				break;
			case 20470:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720470);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722270, EnemyMetis, "Metis_2232");
				break;
			case 20480:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720480);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722280, EnemyMetis, "Metis_2233");
				break;
			case 20490:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720490);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722290, EnemyMetis, "Metis_2234");
				break;
			case 20500:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720500);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722300, EnemyMetis, "Metis_2235");
				break;
			case 20510:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720510);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722310, EnemyMetis, "Metis_2236");
				break;
			case 20520:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720520);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722320, EnemyMetis, "Metis_2237");
				break;
			case 20530:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720530);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722330, EnemyMetis, "Metis_2238");
				break;
			case 20540:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720540);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722340, EnemyMetis, "Metis_2239");
				break;
			case 20550:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720550);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722350, EnemyMetis, "Metis_2240");
				break;
			case 20560:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720560);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722360, EnemyMetis, "Metis_2241");
				break;
			case 20570:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720570);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722370, EnemyMetis, "Metis_2242");
				break;
			case 20580:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720580);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722380, EnemyMetis, "Metis_2243");
				break;
			case 20590:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720590);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722390, EnemyMetis, "Metis_2244");
				break;
			case 20600:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720600);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722400, EnemyMetis, "Metis_2245");
				break;
			case 20610:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720610);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722410, EnemyMetis, "Metis_2246");
				break;
			case 20620:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720620);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722420, EnemyMetis, "Metis_2247");
				break;
			case 20630:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720630);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722430, EnemyMetis, "Metis_2248");
				break;
			case 20640:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720640);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722440, EnemyMetis, "Metis_2249");
				break;
			case 20650:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720650);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722450, EnemyMetis, "Metis_2250");
				break;
			case 20660:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720660);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722460, EnemyMetis, "Metis_2251");
				break;
			case 20670:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720670);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722470, EnemyMetis, "Metis_2252");
				break;
			case 20680:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720680);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722480, EnemyMetis, "Metis_2253");
				break;
			case 20690:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720690);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722490, EnemyMetis, "Metis_2254");
				break;
			case 20700:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720700);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722500, EnemyMetis, "Metis_2255");
				break;
			case 20710:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720710);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722510, EnemyMetis, "Metis_2256");
				break;
			case 20720:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720720);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722520, EnemyMetis, "Metis_2257");
				break;
			case 20730:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720730);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722530, EnemyMetis, "Metis_2258");
				break;
			case 20740:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720740);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722540, EnemyMetis, "Metis_2259");
				break;
			case 20750:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720750);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722550, EnemyMetis, "Metis_2260");
				break;
			case 20760:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720760);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722560, EnemyMetis, "Metis_2261");
				break;
			case 20770:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720770);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722570, EnemyMetis, "Metis_2262");
				break;
			case 20780:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720780);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722580, EnemyMetis, "Metis_2263");
				break;
			case 20790:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720790);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722590, EnemyMetis, "Metis_2264");
				break;
			case 20800:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720800);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722600, EnemyMetis, "Metis_2265");
				break;
			case 20810:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720810);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722610, EnemyMetis, "Metis_2266");
				break;
			case 20820:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720820);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722620, EnemyMetis, "Metis_2267");
				break;
			case 20830:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720830);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722630, EnemyMetis, "Metis_2268");
				break;
			case 20840:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720840);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722640, EnemyMetis, "Metis_2269");
				break;
			case 20850:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720850);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722650, EnemyMetis, "Metis_2270");
				break;
			case 20860:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720860);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722660, EnemyMetis, "Metis_2271");
				break;
			case 20870:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720870);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722670, EnemyMetis, "Metis_2272");
				break;
			case 20880:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720880);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722680, EnemyMetis, "Metis_2273");
				break;
			case 20890:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720890);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722690, EnemyMetis, "Metis_2274");
				break;
			case 20900:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720900);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722700, EnemyMetis, "Metis_2275");
				break;
			case 20910:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720910);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722710, EnemyMetis, "Metis_2276");
				break;
			case 20920:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720920);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722720, EnemyMetis, "Metis_2277");
				break;
			case 20930:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720930);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722730, EnemyMetis, "Metis_2278");
				break;
			case 20940:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720940);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722740, EnemyMetis, "Metis_2279");
				break;
			case 20950:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720950);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722750, EnemyMetis, "Metis_2280");
				break;
			case 20960:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720960);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722760, EnemyMetis, "Metis_2281");
				break;
			case 20970:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720970);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722770, EnemyMetis, "Metis_2282");
				break;
			case 20980:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720980);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722780, EnemyMetis, "Metis_2283");
				break;
			case 20990:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720990);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722790, EnemyMetis, "Metis_2284");
				break;
			case 21000:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721000);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722800, EnemyMetis, "Metis_2285");
				break;
			case 21010:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721010);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722810, EnemyMetis, "Metis_2286");
				break;
			case 21020:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721020);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722820, EnemyMetis, "Metis_2287");
				break;
			case 21030:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721030);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722830, EnemyMetis, "Metis_2288");
				break;
			case 21040:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721040);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722840, EnemyMetis, "Metis_2289");
				break;
			case 21050:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721050);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722850, EnemyMetis, "Metis_2290");
				break;
			case 21060:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721060);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722860, EnemyMetis, "Metis_2291");
				break;
			case 21070:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721070);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722870, EnemyMetis, "Metis_2292");
				break;
			case 21080:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721080);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722880, EnemyMetis, "Metis_2293");
				break;
			case 21090:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721090);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722890, EnemyMetis, "Metis_2294");
				break;
			case 21100:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721100);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722900, EnemyMetis, "Metis_2295");
				break;
			case 21110:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721110);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722910, EnemyMetis, "Metis_2296");
				break;
			case 21120:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721120);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722920, EnemyMetis, "Metis_2297");
				break;
			case 21130:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721130);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722930, EnemyMetis, "Metis_2298");
				break;
			case 21140:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721140);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722940, EnemyMetis, "Metis_2299");
				break;
			case 21150:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721150);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722950, EnemyMetis, "Metis_2300");
				break;
			case 21160:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721160);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722960, EnemyMetis, "Metis_2301");
				break;
			case 21170:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721170);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722970, EnemyMetis, "Metis_2302");
				break;
			case 21180:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721180);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722980, EnemyMetis, "Metis_2303");
				break;
			case 21190:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721190);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722990, EnemyMetis, "Metis_2304");
				break;
			case 21200:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721200);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723000, EnemyMetis, "Metis_2305");
				break;
			case 21210:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721210);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723010, EnemyMetis, "Metis_2306");
				break;
			case 21220:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721220);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723020, EnemyMetis, "Metis_2307");
				break;
			case 21230:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721230);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723030, EnemyMetis, "Metis_2308");
				break;
			case 21240:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721240);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723040, EnemyMetis, "Metis_2309");
				break;
			case 21250:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721250);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723050, EnemyMetis, "Metis_2310");
				break;
			case 21260:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721260);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723060, EnemyMetis, "Metis_2311");
				break;
			case 21270:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721270);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723070, EnemyMetis, "Metis_2312");
				break;
			case 21280:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721280);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723080, EnemyMetis, "Metis_2313");
				break;
			case 21290:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721290);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723090, EnemyMetis, "Metis_2314");
				break;
			case 21300:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721300);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723100, EnemyMetis, "Metis_2315");
				break;
			case 21310:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721310);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723110, EnemyMetis, "Metis_2316");
				break;
			case 21320:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721320);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723120, EnemyMetis, "Metis_2317");
				break;
			case 21330:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721330);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723130, EnemyMetis, "Metis_2318");
				break;
			case 21340:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721340);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723140, EnemyMetis, "Metis_2319");
				break;
			case 21350:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721350);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723150, EnemyMetis, "Metis_2320");
				break;
			case 21360:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721360);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723160, EnemyMetis, "Metis_2321");
				break;
			case 21370:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721370);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723170, EnemyMetis, "Metis_2322");
				break;
			case 21380:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721380);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723180, EnemyMetis, "Metis_2323");
				break;
			case 21390:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721390);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723190, EnemyMetis, "Metis_2324");
				break;
			case 21400:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721400);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723200, EnemyMetis, "Metis_2325");
				break;
			case 21410:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721410);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723210, EnemyMetis, "Metis_2326");
				break;
			case 21420:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721420);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723220, EnemyMetis, "Metis_2327");
				break;
			case 21430:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721430);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723230, EnemyMetis, "Metis_2328");
				break;
			case 21440:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721440);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723240, EnemyMetis, "Metis_2329");
				break;
			case 21450:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721450);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723250, EnemyMetis, "Metis_2330");
				break;
			case 21460:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721460);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723260, EnemyMetis, "Metis_2331");
				break;
			case 21470:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721470);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723270, EnemyMetis, "Metis_2332");
				break;
			case 21480:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721480);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723280, EnemyMetis, "Metis_2333");
				break;
			case 21490:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721490);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723290, EnemyMetis, "Metis_2334");
				break;
			case 21500:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721500);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723300, EnemyMetis, "Metis_2335");
				break;
			case 21510:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721510);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723310, EnemyMetis, "Metis_2336");
				break;
			case 21520:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721520);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723320, EnemyMetis, "Metis_2337");
				break;
			case 21530:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721530);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723330, EnemyMetis, "Metis_2338");
				break;
			case 21540:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721540);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723340, EnemyMetis, "Metis_2339");
				break;
			case 21550:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721550);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723350, EnemyMetis, "Metis_2340");
				break;
			case 21560:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721560);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723360, EnemyMetis, "Metis_2341");
				break;
			case 21570:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721570);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723370, EnemyMetis, "Metis_2342");
				break;
			case 21580:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721580);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723380, EnemyMetis, "Metis_2343");
				break;
			case 21590:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721590);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723390, EnemyMetis, "Metis_2344");
				break;
			case 21600:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721600);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723400, EnemyMetis, "Metis_2345");
				break;
			case 21610:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721610);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723410, EnemyMetis, "Metis_2346");
				break;
			case 21620:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721620);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723420, EnemyMetis, "Metis_2347");
				break;
			case 21630:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721630);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723430, EnemyMetis, "Metis_2348");
				break;
			case 21640:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721640);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723440, EnemyMetis, "Metis_2349");
				break;
			case 21650:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721650);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723450, EnemyMetis, "Metis_2350");
				break;
			case 21660:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721660);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723460, EnemyMetis, "Metis_2351");
				break;
			case 21670:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721670);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723470, EnemyMetis, "Metis_2352");
				break;
			case 21680:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721680);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723480, EnemyMetis, "Metis_2353");
				break;
			case 21690:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721690);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723490, EnemyMetis, "Metis_2354");
				break;
			case 21700:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721700);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723500, EnemyMetis, "Metis_2355");
				break;
			case 21710:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721710);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723510, EnemyMetis, "Metis_2356");
				break;
			case 21720:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721720);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723520, EnemyMetis, "Metis_2357");
				break;
			case 21730:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721730);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723530, EnemyMetis, "Metis_2358");
				break;
			case 21740:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721740);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723540, EnemyMetis, "Metis_2359");
				break;
			case 21750:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721750);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723550, EnemyMetis, "Metis_2360");
				break;
			case 21760:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721760);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723560, EnemyMetis, "Metis_2361");
				break;
			case 21770:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721770);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723570, EnemyMetis, "Metis_2362");
				break;
			case 21780:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721780);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723580, EnemyMetis, "Metis_2363");
				break;
			case 21790:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721790);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723590, EnemyMetis, "Metis_2364");
				break;
			case 21800:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721800);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723600, EnemyMetis, "Metis_2365");
				break;
			case 21810:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721810);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723610, EnemyMetis, "Metis_2366");
				break;
			case 21820:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721820);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723620, EnemyMetis, "Metis_2367");
				break;
			case 21830:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721830);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723630, EnemyMetis, "Metis_2368");
				break;
			case 21840:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721840);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723640, EnemyMetis, "Metis_2369");
				break;
			case 21850:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721850);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723650, EnemyMetis, "Metis_2370");
				break;
			case 21860:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721860);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723660, EnemyMetis, "Metis_2371");
				break;
			case 21870:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721870);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723670, EnemyMetis, "Metis_2372");
				break;
			case 21880:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721880);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723680, EnemyMetis, "Metis_2373");
				break;
			case 21890:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721890);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723690, EnemyMetis, "Metis_2374");
				break;
			case 21900:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721900);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723700, EnemyMetis, "Metis_2375");
				break;
			case 21910:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721910);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723710, EnemyMetis, "Metis_2376");
				break;
			case 21920:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721920);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723720, EnemyMetis, "Metis_2377");
				break;
			case 21930:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721930);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723730, EnemyMetis, "Metis_2378");
				break;
			case 21940:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721940);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723740, EnemyMetis, "Metis_2379");
				break;
			case 21950:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721950);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723750, EnemyMetis, "Metis_2380");
				break;
			case 21960:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721960);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723760, EnemyMetis, "Metis_2381");
				break;
			case 21970:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721970);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723770, EnemyMetis, "Metis_2382");
				break;
			case 21980:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721980);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723780, EnemyMetis, "Metis_2383");
				break;
			case 21990:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721990);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723790, EnemyMetis, "Metis_2384");
				break;
			case 22000:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722000);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723800, EnemyMetis, "Metis_2385");
				break;
			case 22010:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722010);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723810, EnemyMetis, "Metis_2386");
				break;
			case 22020:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722020);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723820, EnemyMetis, "Metis_2387");
				break;
			case 22030:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722030);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723830, EnemyMetis, "Metis_2388");
				break;
			case 22040:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722040);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723840, EnemyMetis, "Metis_2389");
				break;
			case 22050:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722050);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723850, EnemyMetis, "Metis_2390");
				break;
			case 22060:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722060);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723860, EnemyMetis, "Metis_2391");
				break;
			case 22070:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722070);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723870, EnemyMetis, "Metis_2392");
				break;
			case 22080:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722080);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723880, EnemyMetis, "Metis_2393");
				break;
			case 22090:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722090);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723890, EnemyMetis, "Metis_2394");
				break;
			case 22100:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722100);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723900, EnemyMetis, "Metis_2395");
				break;
			case 22110:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722110);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723910, EnemyMetis, "Metis_2396");
				break;
			case 22120:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722120);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723920, EnemyMetis, "Metis_2397");
				break;
			case 22130:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722130);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723930, EnemyMetis, "Metis_2398");
				break;
			case 22140:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722140);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723940, EnemyMetis, "Metis_2399");
				break;
			case 22150:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722150);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723950, EnemyMetis, "Metis_2400");
				break;
			case 22160:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722160);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723960, EnemyMetis, "Metis_2401");
				break;
			case 22170:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722170);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723970, EnemyMetis, "Metis_2402");
				break;
			case 22180:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722180);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723980, EnemyMetis, "Metis_2403");
				break;
			case 22190:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722190);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723990, EnemyMetis, "Metis_2404");
				break;
			case 22200:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722200);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724000, EnemyMetis, "Metis_2405");
				break;
			case 22210:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722210);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724010, EnemyMetis, "Metis_2406");
				break;
			case 22220:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722220);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724020, EnemyMetis, "Metis_2407");
				break;
			case 22230:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722230);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724030, EnemyMetis, "Metis_2408");
				break;
			case 22240:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722240);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724040, EnemyMetis, "Metis_2409");
				break;
			case 22250:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722250);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724050, EnemyMetis, "Metis_2410");
				break;
			case 22260:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722260);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724060, EnemyMetis, "Metis_2411");
				break;
			case 22270:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722270);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724070, EnemyMetis, "Metis_2412");
				break;
			case 22280:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722280);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724080, EnemyMetis, "Metis_2413");
				break;
			case 22290:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722290);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724090, EnemyMetis, "Metis_2414");
				break;
			case 22300:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722300);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724100, EnemyMetis, "Metis_2415");
				break;
			case 22310:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722310);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724110, EnemyMetis, "Metis_2416");
				break;
			case 22320:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722320);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724120, EnemyMetis, "Metis_2417");
				break;
			case 22330:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722330);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724130, EnemyMetis, "Metis_2418");
				break;
			case 22340:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722340);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724140, EnemyMetis, "Metis_2419");
				break;
			case 22350:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722350);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724150, EnemyMetis, "Metis_2420");
				break;
			case 22360:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722360);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724160, EnemyMetis, "Metis_2421");
				break;
			case 22370:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722370);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724170, EnemyMetis, "Metis_2422");
				break;
			case 22380:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722380);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724180, EnemyMetis, "Metis_2423");
				break;
			case 22390:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722390);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724190, EnemyMetis, "Metis_2424");
				break;
			case 22400:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722400);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724200, EnemyMetis, "Metis_2425");
				break;
			case 22410:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722410);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724210, EnemyMetis, "Metis_2426");
				break;
			case 22420:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722420);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724220, EnemyMetis, "Metis_2427");
				break;
			case 22430:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722430);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724230, EnemyMetis, "Metis_2428");
				break;
			case 22440:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722440);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724240, EnemyMetis, "Metis_2429");
				break;
			case 22450:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722450);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724250, EnemyMetis, "Metis_2430");
				break;
			case 22460:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722460);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724260, EnemyMetis, "Metis_2431");
				break;
			case 22470:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722470);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724270, EnemyMetis, "Metis_2432");
				break;
			case 22480:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722480);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724280, EnemyMetis, "Metis_2433");
				break;
			case 22490:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722490);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724290, EnemyMetis, "Metis_2434");
				break;
			case 22500:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722500);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724300, EnemyMetis, "Metis_2435");
				break;
			case 22510:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722510);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724310, EnemyMetis, "Metis_2436");
				break;
			case 22520:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722520);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724320, EnemyMetis, "Metis_2437");
				break;
			case 22530:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722530);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724330, EnemyMetis, "Metis_2438");
				break;
			case 22540:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722540);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724340, EnemyMetis, "Metis_2439");
				break;
			case 22550:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722550);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724350, EnemyMetis, "Metis_2440");
				break;
			case 22560:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722560);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724360, EnemyMetis, "Metis_2441");
				break;
			case 22570:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722570);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724370, EnemyMetis, "Metis_2442");
				break;
			case 22580:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722580);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724380, EnemyMetis, "Metis_2443");
				break;
			case 22590:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722590);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724390, EnemyMetis, "Metis_2444");
				break;
			case 22600:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722600);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724400, EnemyMetis, "Metis_2445");
				break;
			case 22610:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722610);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724410, EnemyMetis, "Metis_2446");
				break;
			case 22620:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722620);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724420, EnemyMetis, "Metis_2447");
				break;
			case 22630:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722630);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724430, EnemyMetis, "Metis_2448");
				break;
			case 22640:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722640);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724440, EnemyMetis, "Metis_2449");
				break;
			case 22650:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722650);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724450, EnemyMetis, "Metis_2450");
				break;
			case 22660:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722660);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724460, EnemyMetis, "Metis_2451");
				break;
			case 22670:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722670);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724470, EnemyMetis, "Metis_2452");
				break;
			case 22680:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722680);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724480, EnemyMetis, "Metis_2453");
				break;
			case 22690:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722690);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724490, EnemyMetis, "Metis_2454");
				break;
			case 22700:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722700);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724500, EnemyMetis, "Metis_2455");
				break;
			case 22710:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722710);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724510, EnemyMetis, "Metis_2456");
				break;
			case 22720:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722720);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724520, EnemyMetis, "Metis_2457");
				break;
			case 22730:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722730);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724530, EnemyMetis, "Metis_2458");
				break;
			case 22740:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722740);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724540, EnemyMetis, "Metis_2459");
				break;
			case 22750:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722750);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724550, EnemyMetis, "Metis_2460");
				break;
			case 22760:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722760);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724560, EnemyMetis, "Metis_2461");
				break;
			case 22770:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722770);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724570, EnemyMetis, "Metis_2462");
				break;
			case 22780:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722780);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724580, EnemyMetis, "Metis_2463");
				break;
			case 22790:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722790);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724590, EnemyMetis, "Metis_2464");
				break;
			case 22800:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722800);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724600, EnemyMetis, "Metis_2465");
				break;
			case 22810:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722810);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724610, EnemyMetis, "Metis_2466");
				break;
			case 22820:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722820);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724620, EnemyMetis, "Metis_2467");
				break;
			case 22830:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722830);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724630, EnemyMetis, "Metis_2468");
				break;
			case 22840:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722840);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724640, EnemyMetis, "Metis_2469");
				break;
			case 22850:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722850);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724650, EnemyMetis, "Metis_2470");
				break;
			case 22860:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722860);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724660, EnemyMetis, "Metis_2471");
				break;
			case 22870:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722870);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724670, EnemyMetis, "Metis_2472");
				break;
			case 22880:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722880);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724680, EnemyMetis, "Metis_2473");
				break;
			case 22890:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722890);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724690, EnemyMetis, "Metis_2474");
				break;
			case 22900:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722900);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724700, EnemyMetis, "Metis_2475");
				break;
			case 22910:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722910);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724710, EnemyMetis, "Metis_2476");
				break;
			case 22920:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722920);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724720, EnemyMetis, "Metis_2477");
				break;
			case 22930:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722930);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724730, EnemyMetis, "Metis_2478");
				break;
			case 22940:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722940);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724740, EnemyMetis, "Metis_2479");
				break;
			case 22950:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722950);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724750, EnemyMetis, "Metis_2480");
				break;
			case 22960:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722960);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724760, EnemyMetis, "Metis_2481");
				break;
			case 22970:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722970);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724770, EnemyMetis, "Metis_2482");
				break;
			case 22980:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722980);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724780, EnemyMetis, "Metis_2483");
				break;
			case 22990:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722990);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724790, EnemyMetis, "Metis_2484");
				break;
			case 23000:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723000);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724800, EnemyMetis, "Metis_2485");
				break;
			case 23010:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723010);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724810, EnemyMetis, "Metis_2486");
				break;
			case 23020:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723020);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724820, EnemyMetis, "Metis_2487");
				break;
			case 23030:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723030);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724830, EnemyMetis, "Metis_2488");
				break;
			case 23040:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723040);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724840, EnemyMetis, "Metis_2489");
				break;
			case 23050:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723050);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724850, EnemyMetis, "Metis_2490");
				break;
			case 23060:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723060);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724860, EnemyMetis, "Metis_2491");
				break;
			case 23070:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723070);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724870, EnemyMetis, "Metis_2492");
				break;
			case 23080:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723080);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724880, EnemyMetis, "Metis_2493");
				break;
			case 23090:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723090);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724890, EnemyMetis, "Metis_2494");
				break;
			case 23100:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723100);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724900, EnemyMetis, "Metis_2495");
				break;
			case 23110:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723110);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724910, EnemyMetis, "Metis_2496");
				break;
			case 23120:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723120);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724920, EnemyMetis, "Metis_2497");
				break;
			case 23130:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723130);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724930, EnemyMetis, "Metis_2498");
				break;
			case 23140:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723140);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724940, EnemyMetis, "Metis_2499");
				break;
			case 23150:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723150);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724950, EnemyMetis, "Metis_2500");
				break;
			case 23160:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723160);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724960, EnemyMetis, "Metis_2501");
				break;
			case 23170:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723170);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724970, EnemyMetis, "Metis_2502");
				break;
			case 23180:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723180);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724980, EnemyMetis, "Metis_2503");
				break;
			case 23190:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723190);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724990, EnemyMetis, "Metis_2504");
				break;
			case 23200:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723200);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725000, EnemyMetis, "Metis_2505");
				break;
			case 23210:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723210);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725010, EnemyMetis, "Metis_2506");
				break;
			case 23220:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723220);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725020, EnemyMetis, "Metis_2507");
				break;
			case 23230:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723230);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725030, EnemyMetis, "Metis_2508");
				break;
			case 23240:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723240);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725040, EnemyMetis, "Metis_2509");
				break;
			case 23250:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723250);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725050, EnemyMetis, "Metis_2510");
				break;
			case 23260:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723260);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725060, EnemyMetis, "Metis_2511");
				break;
			case 23270:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723270);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725070, EnemyMetis, "Metis_2512");
				break;
			case 23280:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723280);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725080, EnemyMetis, "Metis_2513");
				break;
			case 23290:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723290);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725090, EnemyMetis, "Metis_2514");
				break;
			case 23300:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723300);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725100, EnemyMetis, "Metis_2515");
				break;
			case 23310:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723310);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725110, EnemyMetis, "Metis_2516");
				break;
			case 23320:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723320);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725120, EnemyMetis, "Metis_2517");
				break;
			case 23330:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723330);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725130, EnemyMetis, "Metis_2518");
				break;
			case 23340:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723340);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725140, EnemyMetis, "Metis_2519");
				break;
			case 23350:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723350);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725150, EnemyMetis, "Metis_2520");
				break;
			case 23360:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723360);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725160, EnemyMetis, "Metis_2521");
				break;
			case 23370:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723370);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725170, EnemyMetis, "Metis_2522");
				break;
			case 23380:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723380);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725180, EnemyMetis, "Metis_2523");
				break;
			case 23390:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723390);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725190, EnemyMetis, "Metis_2524");
				break;
			case 23400:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723400);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725200, EnemyMetis, "Metis_2525");
				break;
			case 23410:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723410);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725210, EnemyMetis, "Metis_2526");
				break;
			case 23420:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723420);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725220, EnemyMetis, "Metis_2527");
				break;
			case 23430:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723430);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725230, EnemyMetis, "Metis_2528");
				break;
			case 23440:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723440);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725240, EnemyMetis, "Metis_2529");
				break;
			case 23450:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723450);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725250, EnemyMetis, "Metis_2530");
				break;
			case 23460:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723460);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725260, EnemyMetis, "Metis_2531");
				break;
			case 23470:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723470);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725270, EnemyMetis, "Metis_2532");
				break;
			case 23480:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723480);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725280, EnemyMetis, "Metis_2533");
				break;
			case 23490:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723490);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725290, EnemyMetis, "Metis_2534");
				break;
			case 23500:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723500);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725300, EnemyMetis, "Metis_2535");
				break;
			case 23510:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723510);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725310, EnemyMetis, "Metis_2536");
				break;
			case 23520:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723520);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725320, EnemyMetis, "Metis_2537");
				break;
			case 23530:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723530);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725330, EnemyMetis, "Metis_2538");
				break;
			case 23540:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723540);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725340, EnemyMetis, "Metis_2539");
				break;
			case 23550:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723550);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725350, EnemyMetis, "Metis_2540");
				break;
			case 23560:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723560);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725360, EnemyMetis, "Metis_2541");
				break;
			case 23570:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723570);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725370, EnemyMetis, "Metis_2542");
				break;
			case 23580:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723580);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725380, EnemyMetis, "Metis_2543");
				break;
			case 23590:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723590);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725390, EnemyMetis, "Metis_2544");
				break;
			case 23600:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723600);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725400, EnemyMetis, "Metis_2545");
				break;
			case 23610:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723610);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725410, EnemyMetis, "Metis_2546");
				break;
			case 23620:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723620);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725420, EnemyMetis, "Metis_2547");
				break;
			case 23630:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723630);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725430, EnemyMetis, "Metis_2548");
				break;
			case 23640:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723640);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725440, EnemyMetis, "Metis_2549");
				break;
			case 23650:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723650);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725450, EnemyMetis, "Metis_2550");
				break;
			case 23660:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723660);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725460, EnemyMetis, "Metis_2551");
				break;
			case 23670:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723670);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725470, EnemyMetis, "Metis_2552");
				break;
			case 23680:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723680);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725480, EnemyMetis, "Metis_2553");
				break;
			case 23690:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723690);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725490, EnemyMetis, "Metis_2554");
				break;
			case 23700:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723700);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725500, EnemyMetis, "Metis_2555");
				break;
			case 23710:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723710);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725510, EnemyMetis, "Metis_2556");
				break;
			case 23720:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723720);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725520, EnemyMetis, "Metis_2557");
				break;
			case 23730:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723730);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725530, EnemyMetis, "Metis_2558");
				break;
			case 23740:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723740);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725540, EnemyMetis, "Metis_2559");
				break;
			case 23750:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723750);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725550, EnemyMetis, "Metis_2560");
				break;
			case 23760:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723760);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725560, EnemyMetis, "Metis_2561");
				break;
			case 23770:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723770);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725570, EnemyMetis, "Metis_2562");
				break;
			case 23780:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723780);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725580, EnemyMetis, "Metis_2563");
				break;
			case 23790:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723790);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725590, EnemyMetis, "Metis_2564");
				break;
			case 23800:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723800);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725600, EnemyMetis, "Metis_2565");
				break;
			case 23810:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723810);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725610, EnemyMetis, "Metis_2566");
				break;
			case 23820:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723820);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725620, EnemyMetis, "Metis_2567");
				break;
			case 23830:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723830);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725630, EnemyMetis, "Metis_2568");
				break;
			case 23840:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723840);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725640, EnemyMetis, "Metis_2569");
				break;
			case 23850:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723850);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725650, EnemyMetis, "Metis_2570");
				break;
			case 23860:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723860);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725660, EnemyMetis, "Metis_2571");
				break;
			case 23870:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723870);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725670, EnemyMetis, "Metis_2572");
				break;
			case 23880:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723880);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725680, EnemyMetis, "Metis_2573");
				break;
			case 23890:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723890);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725690, EnemyMetis, "Metis_2574");
				break;
			case 23900:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723900);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725700, EnemyMetis, "Metis_2575");
				break;
			case 23910:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723910);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725710, EnemyMetis, "Metis_2576");
				break;
			case 23920:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723920);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725720, EnemyMetis, "Metis_2577");
				break;
			case 23930:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723930);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725730, EnemyMetis, "Metis_2578");
				break;
			case 23940:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723940);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725740, EnemyMetis, "Metis_2579");
				break;
			case 23950:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723950);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725750, EnemyMetis, "Metis_2580");
				break;
			case 23960:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723960);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725760, EnemyMetis, "Metis_2581");
				break;
			case 23970:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723970);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725770, EnemyMetis, "Metis_2582");
				break;
			case 23980:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723980);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725780, EnemyMetis, "Metis_2583");
				break;
			case 23990:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723990);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725790, EnemyMetis, "Metis_2584");
				break;
			case 24000:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724000);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725800, EnemyMetis, "Metis_2585");
				break;
			case 24010:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724010);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725810, EnemyMetis, "Metis_2586");
				break;
			case 24020:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724020);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725820, EnemyMetis, "Metis_2587");
				break;
			case 24030:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724030);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725830, EnemyMetis, "Metis_2588");
				break;
			case 24040:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724040);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725840, EnemyMetis, "Metis_2589");
				break;
			case 24050:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724050);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725850, EnemyMetis, "Metis_2590");
				break;
			case 24060:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724060);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725860, EnemyMetis, "Metis_2591");
				break;
			case 24070:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724070);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725870, EnemyMetis, "Metis_2592");
				break;
			case 24080:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724080);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725880, EnemyMetis, "Metis_2593");
				break;
			case 24090:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724090);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725890, EnemyMetis, "Metis_2594");
				break;
			case 24100:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724100);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725900, EnemyMetis, "Metis_2595");
				break;
			case 24110:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724110);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725910, EnemyMetis, "Metis_2596");
				break;
			case 24120:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724120);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725920, EnemyMetis, "Metis_2597");
				break;
			case 24130:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724130);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725930, EnemyMetis, "Metis_2598");
				break;
			case 24140:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724140);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725940, EnemyMetis, "Metis_2599");
				break;
			case 24150:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724150);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725950, EnemyMetis, "Metis_2600");
				break;
			case 24160:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724160);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725960, EnemyMetis, "Metis_2601");
				break;
			case 24170:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724170);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725970, EnemyMetis, "Metis_2602");
				break;
			case 24180:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724180);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725980, EnemyMetis, "Metis_2603");
				break;
			case 24190:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724190);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725990, EnemyMetis, "Metis_2604");
				break;
			case 24200:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724200);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726000, EnemyMetis, "Metis_2605");
				break;
			case 24210:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724210);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726010, EnemyMetis, "Metis_2606");
				break;
			case 24220:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724220);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726020, EnemyMetis, "Metis_2607");
				break;
			case 24230:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724230);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726030, EnemyMetis, "Metis_2608");
				break;
			case 24240:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724240);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726040, EnemyMetis, "Metis_2609");
				break;
			case 24250:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724250);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726050, EnemyMetis, "Metis_2610");
				break;
			case 24260:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724260);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726060, EnemyMetis, "Metis_2611");
				break;
			case 24270:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724270);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726070, EnemyMetis, "Metis_2612");
				break;
			case 24280:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724280);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726080, EnemyMetis, "Metis_2613");
				break;
			case 24290:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724290);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726090, EnemyMetis, "Metis_2614");
				break;
			case 24300:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724300);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726100, EnemyMetis, "Metis_2615");
				break;
			case 24310:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724310);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726110, EnemyMetis, "Metis_2616");
				break;
			case 24320:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724320);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726120, EnemyMetis, "Metis_2617");
				break;
			case 24330:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724330);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726130, EnemyMetis, "Metis_2618");
				break;
			case 24340:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724340);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726140, EnemyMetis, "Metis_2619");
				break;
			case 24350:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724350);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726150, EnemyMetis, "Metis_2620");
				break;
			case 24360:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724360);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726160, EnemyMetis, "Metis_2621");
				break;
			case 24370:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724370);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726170, EnemyMetis, "Metis_2622");
				break;
			case 24380:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724380);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726180, EnemyMetis, "Metis_2623");
				break;
			case 24390:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724390);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726190, EnemyMetis, "Metis_2624");
				break;
			case 24400:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724400);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726200, EnemyMetis, "Metis_2625");
				break;
			case 24410:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724410);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726210, EnemyMetis, "Metis_2626");
				break;
			case 24420:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724420);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726220, EnemyMetis, "Metis_2627");
				break;
			case 24430:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724430);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726230, EnemyMetis, "Metis_2628");
				break;
			case 24440:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724440);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726240, EnemyMetis, "Metis_2629");
				break;
			case 24450:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724450);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726250, EnemyMetis, "Metis_2630");
				break;
			case 24460:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724460);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726260, EnemyMetis, "Metis_2631");
				break;
			case 24470:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724470);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726270, EnemyMetis, "Metis_2632");
				break;
			case 24480:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724480);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726280, EnemyMetis, "Metis_2633");
				break;
			case 24490:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724490);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726290, EnemyMetis, "Metis_2634");
				break;
			case 24500:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724500);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726300, EnemyMetis, "Metis_2635");
				break;
			case 24510:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724510);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726310, EnemyMetis, "Metis_2636");
				break;
			case 24520:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724520);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726320, EnemyMetis, "Metis_2637");
				break;
			case 24530:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724530);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726330, EnemyMetis, "Metis_2638");
				break;
			case 24540:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724540);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726340, EnemyMetis, "Metis_2639");
				break;
			case 24550:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724550);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726350, EnemyMetis, "Metis_2640");
				break;
			case 24560:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724560);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726360, EnemyMetis, "Metis_2641");
				break;
			case 24570:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724570);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726370, EnemyMetis, "Metis_2642");
				break;
			case 24580:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724580);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726380, EnemyMetis, "Metis_2643");
				break;
			case 24590:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724590);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726390, EnemyMetis, "Metis_2644");
				break;
			case 24600:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724600);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726400, EnemyMetis, "Metis_2645");
				break;
			case 24610:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724610);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726410, EnemyMetis, "Metis_2646");
				break;
			case 24620:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724620);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726420, EnemyMetis, "Metis_2647");
				break;
			case 24630:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724630);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726430, EnemyMetis, "Metis_2648");
				break;
			case 24640:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724640);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726440, EnemyMetis, "Metis_2649");
				break;
			case 24650:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724650);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726450, EnemyMetis, "Metis_2650");
				break;
			case 24660:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724660);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726460, EnemyMetis, "Metis_2651");
				break;
			case 24670:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724670);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726470, EnemyMetis, "Metis_2652");
				break;
			case 24680:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724680);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726480, EnemyMetis, "Metis_2653");
				break;
			case 24690:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724690);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726490, EnemyMetis, "Metis_2654");
				break;
			case 24700:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724700);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726500, EnemyMetis, "Metis_2655");
				break;
			case 24710:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724710);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726510, EnemyMetis, "Metis_2656");
				break;
			case 24720:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724720);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726520, EnemyMetis, "Metis_2657");
				break;
			case 24730:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724730);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726530, EnemyMetis, "Metis_2658");
				break;
			case 24740:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724740);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726540, EnemyMetis, "Metis_2659");
				break;
			case 24750:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724750);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726550, EnemyMetis, "Metis_2660");
				break;
			case 24760:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724760);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726560, EnemyMetis, "Metis_2661");
				break;
			case 24770:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724770);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726570, EnemyMetis, "Metis_2662");
				break;
			case 24780:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724780);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726580, EnemyMetis, "Metis_2663");
				break;
			case 24790:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724790);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726590, EnemyMetis, "Metis_2664");
				break;
			case 24800:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724800);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726600, EnemyMetis, "Metis_2665");
				break;
			case 24810:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724810);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726610, EnemyMetis, "Metis_2666");
				break;
			case 24820:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724820);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726620, EnemyMetis, "Metis_2667");
				break;
			case 24830:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724830);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726630, EnemyMetis, "Metis_2668");
				break;
			case 24840:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724840);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726640, EnemyMetis, "Metis_2669");
				break;
			case 24850:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724850);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726650, EnemyMetis, "Metis_2670");
				break;
			case 24860:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724860);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726660, EnemyMetis, "Metis_2671");
				break;
			case 24870:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724870);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726670, EnemyMetis, "Metis_2672");
				break;
			case 24880:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724880);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726680, EnemyMetis, "Metis_2673");
				break;
			case 24890:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724890);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726690, EnemyMetis, "Metis_2674");
				break;
			case 24900:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724900);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726700, EnemyMetis, "Metis_2675");
				break;
			case 24910:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724910);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726710, EnemyMetis, "Metis_2676");
				break;
			case 24920:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724920);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726720, EnemyMetis, "Metis_2677");
				break;
			case 24930:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724930);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726730, EnemyMetis, "Metis_2678");
				break;
			case 24940:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724940);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726740, EnemyMetis, "Metis_2679");
				break;
			case 24950:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724950);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726750, EnemyMetis, "Metis_2680");
				break;
			case 24960:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724960);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726760, EnemyMetis, "Metis_2681");
				break;
			case 24970:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724970);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726770, EnemyMetis, "Metis_2682");
				break;
			case 24980:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724980);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726780, EnemyMetis, "Metis_2683");
				break;
			case 24990:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724990);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726790, EnemyMetis, "Metis_2684");
				break;
			case 25000:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725000);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726800, EnemyMetis, "Metis_2685");
				break;
			case 25010:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725010);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726810, EnemyMetis, "Metis_2686");
				break;
			case 25020:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725020);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726820, EnemyMetis, "Metis_2687");
				break;
			case 25030:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725030);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726830, EnemyMetis, "Metis_2688");
				break;
			case 25040:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725040);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726840, EnemyMetis, "Metis_2689");
				break;
			case 25050:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725050);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726850, EnemyMetis, "Metis_2690");
				break;
			case 25060:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725060);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726860, EnemyMetis, "Metis_2691");
				break;
			case 25070:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725070);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726870, EnemyMetis, "Metis_2692");
				break;
			case 25080:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725080);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726880, EnemyMetis, "Metis_2693");
				break;
			case 25090:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725090);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726890, EnemyMetis, "Metis_2694");
				break;
			case 25100:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725100);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726900, EnemyMetis, "Metis_2695");
				break;
			case 25110:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725110);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726910, EnemyMetis, "Metis_2696");
				break;
			case 25120:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725120);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726920, EnemyMetis, "Metis_2697");
				break;
			case 25130:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725130);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726930, EnemyMetis, "Metis_2698");
				break;
			case 25140:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725140);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726940, EnemyMetis, "Metis_2699");
				break;
			case 25150:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725150);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726950, EnemyMetis, "Metis_2700");
				break;
			case 25160:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725160);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726960, EnemyMetis, "Metis_2701");
				break;
			case 25170:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725170);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726970, EnemyMetis, "Metis_2702");
				break;
			case 25180:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725180);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726980, EnemyMetis, "Metis_2703");
				break;
			case 25190:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725190);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726990, EnemyMetis, "Metis_2704");
				break;
			case 25200:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725200);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727000, EnemyMetis, "Metis_2705");
				break;
			case 25210:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725210);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727010, EnemyMetis, "Metis_2706");
				break;
			case 25220:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725220);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727020, EnemyMetis, "Metis_2707");
				break;
			case 25230:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725230);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727030, EnemyMetis, "Metis_2708");
				break;
			case 25240:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725240);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727040, EnemyMetis, "Metis_2709");
				break;
			case 25250:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725250);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727050, EnemyMetis, "Metis_2710");
				break;
			case 25260:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725260);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727060, EnemyMetis, "Metis_2711");
				break;
			case 25270:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725270);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727070, EnemyMetis, "Metis_2712");
				break;
			case 25280:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725280);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727080, EnemyMetis, "Metis_2713");
				break;
			case 25290:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725290);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727090, EnemyMetis, "Metis_2714");
				break;
			case 25300:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725300);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727100, EnemyMetis, "Metis_2715");
				break;
			case 25310:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725310);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727110, EnemyMetis, "Metis_2716");
				break;
			case 25320:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725320);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727120, EnemyMetis, "Metis_2717");
				break;
			case 25330:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725330);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727130, EnemyMetis, "Metis_2718");
				break;
			case 25340:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725340);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727140, EnemyMetis, "Metis_2719");
				break;
			case 25350:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725350);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727150, EnemyMetis, "Metis_2720");
				break;
			case 25360:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725360);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727160, EnemyMetis, "Metis_2721");
				break;
			case 25370:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725370);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727170, EnemyMetis, "Metis_2722");
				break;
			case 25380:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725380);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727180, EnemyMetis, "Metis_2723");
				break;
			case 25390:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725390);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727190, EnemyMetis, "Metis_2724");
				break;
			case 25400:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725400);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727200, EnemyMetis, "Metis_2725");
				break;
			case 25410:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725410);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727210, EnemyMetis, "Metis_2726");
				break;
			case 25420:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725420);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727220, EnemyMetis, "Metis_2727");
				break;
			case 25430:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725430);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727230, EnemyMetis, "Metis_2728");
				break;
			case 25440:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725440);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727240, EnemyMetis, "Metis_2729");
				break;
			case 25450:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725450);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727250, EnemyMetis, "Metis_2730");
				break;
			case 25460:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725460);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727260, EnemyMetis, "Metis_2731");
				break;
			case 25470:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725470);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727270, EnemyMetis, "Metis_2732");
				break;
			case 25480:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725480);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727280, EnemyMetis, "Metis_2733");
				break;
			case 25490:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725490);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727290, EnemyMetis, "Metis_2734");
				break;
			case 25500:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725500);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727300, EnemyMetis, "Metis_2735");
				break;
			case 25510:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725510);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727310, EnemyMetis, "Metis_2736");
				break;
			case 25520:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725520);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727320, EnemyMetis, "Metis_2737");
				break;
			case 25530:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725530);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727330, EnemyMetis, "Metis_2738");
				break;
			case 25540:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725540);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727340, EnemyMetis, "Metis_2739");
				break;
			case 25550:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725550);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727350, EnemyMetis, "Metis_2740");
				break;
			case 25560:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725560);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727360, EnemyMetis, "Metis_2741");
				break;
			case 25570:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725570);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727370, EnemyMetis, "Metis_2742");
				break;
			case 25580:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725580);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727380, EnemyMetis, "Metis_2743");
				break;
			case 25590:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725590);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727390, EnemyMetis, "Metis_2744");
				break;
			case 25600:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725600);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727400, EnemyMetis, "Metis_2745");
				break;
			case 25610:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725610);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727410, EnemyMetis, "Metis_2746");
				break;
			case 25620:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725620);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727420, EnemyMetis, "Metis_2747");
				break;
			case 25630:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725630);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727430, EnemyMetis, "Metis_2748");
				break;
			case 25640:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725640);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727440, EnemyMetis, "Metis_2749");
				break;
			case 25650:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725650);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727450, EnemyMetis, "Metis_2750");
				break;
			case 25660:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725660);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727460, EnemyMetis, "Metis_2751");
				break;
			case 25670:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725670);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727470, EnemyMetis, "Metis_2752");
				break;
			case 25680:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725680);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727480, EnemyMetis, "Metis_2753");
				break;
			case 25690:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725690);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727490, EnemyMetis, "Metis_2754");
				break;
			case 25700:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725700);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727500, EnemyMetis, "Metis_2755");
				break;
			case 25710:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725710);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727510, EnemyMetis, "Metis_2756");
				break;
			case 25720:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725720);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727520, EnemyMetis, "Metis_2757");
				break;
			case 25730:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725730);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727530, EnemyMetis, "Metis_2758");
				break;
			case 25740:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725740);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727540, EnemyMetis, "Metis_2759");
				break;
			case 25750:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725750);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727550, EnemyMetis, "Metis_2760");
				break;
			case 25760:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725760);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727560, EnemyMetis, "Metis_2761");
				break;
			case 25770:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725770);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727570, EnemyMetis, "Metis_2762");
				break;
			case 25780:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725780);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727580, EnemyMetis, "Metis_2763");
				break;
			case 25790:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725790);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727590, EnemyMetis, "Metis_2764");
				break;
			case 25800:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725800);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727600, EnemyMetis, "Metis_2765");
				break;
			case 25810:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725810);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727610, EnemyMetis, "Metis_2766");
				break;
			case 25820:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725820);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727620, EnemyMetis, "Metis_2767");
				break;
			case 25830:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725830);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727630, EnemyMetis, "Metis_2768");
				break;
			case 25840:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725840);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727640, EnemyMetis, "Metis_2769");
				break;
			case 25850:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725850);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727650, EnemyMetis, "Metis_2770");
				break;
			case 25860:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725860);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727660, EnemyMetis, "Metis_2771");
				break;
			case 25870:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725870);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727670, EnemyMetis, "Metis_2772");
				break;
			case 25880:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725880);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727680, EnemyMetis, "Metis_2773");
				break;
			case 25890:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725890);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727690, EnemyMetis, "Metis_2774");
				break;
			case 25900:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725900);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727700, EnemyMetis, "Metis_2775");
				break;
			case 25910:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725910);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727710, EnemyMetis, "Metis_2776");
				break;
			case 25920:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725920);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727720, EnemyMetis, "Metis_2777");
				break;
			case 25930:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725930);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727730, EnemyMetis, "Metis_2778");
				break;
			case 25940:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725940);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727740, EnemyMetis, "Metis_2779");
				break;
			case 25950:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725950);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727750, EnemyMetis, "Metis_2780");
				break;
			case 25960:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725960);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727760, EnemyMetis, "Metis_2781");
				break;
			case 25970:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725970);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727770, EnemyMetis, "Metis_2782");
				break;
			case 25980:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725980);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727780, EnemyMetis, "Metis_2783");
				break;
			case 25990:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725990);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727790, EnemyMetis, "Metis_2784");
				break;
			case 26000:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726000);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727800, EnemyMetis, "Metis_2785");
				break;
			case 26010:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726010);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727810, EnemyMetis, "Metis_2786");
				break;
			case 26020:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726020);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727820, EnemyMetis, "Metis_2787");
				break;
			case 26030:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726030);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727830, EnemyMetis, "Metis_2788");
				break;
			case 26040:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726040);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727840, EnemyMetis, "Metis_2789");
				break;
			case 26050:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726050);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727850, EnemyMetis, "Metis_2790");
				break;
			case 26060:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726060);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727860, EnemyMetis, "Metis_2791");
				break;
			case 26070:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726070);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727870, EnemyMetis, "Metis_2792");
				break;
			case 26080:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726080);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727880, EnemyMetis, "Metis_2793");
				break;
			case 26090:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726090);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727890, EnemyMetis, "Metis_2794");
				break;
			case 26100:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726100);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727900, EnemyMetis, "Metis_2795");
				break;
			case 26110:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726110);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727910, EnemyMetis, "Metis_2796");
				break;
			case 26120:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726120);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727920, EnemyMetis, "Metis_2797");
				break;
			case 26130:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726130);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727930, EnemyMetis, "Metis_2798");
				break;
			case 26140:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726140);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727940, EnemyMetis, "Metis_2799");
				break;
			case 26150:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726150);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727950, EnemyMetis, "Metis_2800");
				break;
			case 26160:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726160);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727960, EnemyMetis, "Metis_2801");
				break;
			case 26170:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726170);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727970, EnemyMetis, "Metis_2802");
				break;
			case 26180:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726180);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727980, EnemyMetis, "Metis_2803");
				break;
			case 26190:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726190);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727990, EnemyMetis, "Metis_2804");
				break;
			case 26200:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726200);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728000, EnemyMetis, "Metis_2805");
				break;
			case 26210:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726210);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728010, EnemyMetis, "Metis_2806");
				break;
			case 26220:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726220);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728020, EnemyMetis, "Metis_2807");
				break;
			case 26230:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726230);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728030, EnemyMetis, "Metis_2808");
				break;
			case 26240:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726240);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728040, EnemyMetis, "Metis_2809");
				break;
			case 26250:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726250);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728050, EnemyMetis, "Metis_2810");
				break;
			case 26260:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726260);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728060, EnemyMetis, "Metis_2811");
				break;
			case 26270:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726270);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728070, EnemyMetis, "Metis_2812");
				break;
			case 26280:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726280);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728080, EnemyMetis, "Metis_2813");
				break;
			case 26290:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726290);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728090, EnemyMetis, "Metis_2814");
				break;
			case 26300:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726300);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728100, EnemyMetis, "Metis_2815");
				break;
			case 26310:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726310);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728110, EnemyMetis, "Metis_2816");
				break;
			case 26320:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726320);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728120, EnemyMetis, "Metis_2817");
				break;
			case 26330:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726330);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728130, EnemyMetis, "Metis_2818");
				break;
			case 26340:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726340);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728140, EnemyMetis, "Metis_2819");
				break;
			case 26350:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726350);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728150, EnemyMetis, "Metis_2820");
				break;
			case 26360:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726360);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728160, EnemyMetis, "Metis_2821");
				break;
			case 26370:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726370);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728170, EnemyMetis, "Metis_2822");
				break;
			case 26380:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726380);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728180, EnemyMetis, "Metis_2823");
				break;
			case 26390:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726390);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728190, EnemyMetis, "Metis_2824");
				break;
			case 26400:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726400);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728200, EnemyMetis, "Metis_2825");
				break;
			case 26410:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726410);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728210, EnemyMetis, "Metis_2826");
				break;
			case 26420:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726420);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728220, EnemyMetis, "Metis_2827");
				break;
			case 26430:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726430);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728230, EnemyMetis, "Metis_2828");
				break;
			case 26440:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726440);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728240, EnemyMetis, "Metis_2829");
				break;
			case 26450:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726450);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728250, EnemyMetis, "Metis_2830");
				break;
			case 26460:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726460);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728260, EnemyMetis, "Metis_2831");
				break;
			case 26470:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726470);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728270, EnemyMetis, "Metis_2832");
				break;
			case 26480:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726480);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728280, EnemyMetis, "Metis_2833");
				break;
			case 26490:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726490);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728290, EnemyMetis, "Metis_2834");
				break;
			case 26500:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726500);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728300, EnemyMetis, "Metis_2835");
				break;
			case 26510:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726510);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728310, EnemyMetis, "Metis_2836");
				break;
			case 26520:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726520);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728320, EnemyMetis, "Metis_2837");
				break;
			case 26530:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726530);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728330, EnemyMetis, "Metis_2838");
				break;
			case 26540:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726540);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728340, EnemyMetis, "Metis_2839");
				break;
			case 26550:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726550);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728350, EnemyMetis, "Metis_2840");
				break;
			case 26560:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726560);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728360, EnemyMetis, "Metis_2841");
				break;
			case 26570:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726570);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728370, EnemyMetis, "Metis_2842");
				break;
			case 26580:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726580);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728380, EnemyMetis, "Metis_2843");
				break;
			case 26590:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726590);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728390, EnemyMetis, "Metis_2844");
				break;
			case 26600:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726600);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728400, EnemyMetis, "Metis_2845");
				break;
			case 26610:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726610);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728410, EnemyMetis, "Metis_2846");
				break;
			case 26620:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726620);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728420, EnemyMetis, "Metis_2847");
				break;
			case 26630:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726630);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728430, EnemyMetis, "Metis_2848");
				break;
			case 26640:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726640);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728440, EnemyMetis, "Metis_2849");
				break;
			case 26650:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726650);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728450, EnemyMetis, "Metis_2850");
				break;
			case 26660:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726660);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728460, EnemyMetis, "Metis_2851");
				break;
			case 26670:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726670);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728470, EnemyMetis, "Metis_2852");
				break;
			case 26680:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726680);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728480, EnemyMetis, "Metis_2853");
				break;
			case 26690:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726690);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728490, EnemyMetis, "Metis_2854");
				break;
			case 26700:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726700);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728500, EnemyMetis, "Metis_2855");
				break;
			case 26710:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726710);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728510, EnemyMetis, "Metis_2856");
				break;
			case 26720:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726720);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728520, EnemyMetis, "Metis_2857");
				break;
			case 26730:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726730);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728530, EnemyMetis, "Metis_2858");
				break;
			case 26740:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726740);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728540, EnemyMetis, "Metis_2859");
				break;
			case 26750:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726750);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728550, EnemyMetis, "Metis_2860");
				break;
			case 26760:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726760);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728560, EnemyMetis, "Metis_2861");
				break;
			case 26770:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726770);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728570, EnemyMetis, "Metis_2862");
				break;
			case 26780:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726780);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728580, EnemyMetis, "Metis_2863");
				break;
			case 26790:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726790);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728590, EnemyMetis, "Metis_2864");
				break;
			case 26800:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726800);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728600, EnemyMetis, "Metis_2865");
				break;
			case 26810:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726810);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728610, EnemyMetis, "Metis_2866");
				break;
			case 26820:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726820);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728620, EnemyMetis, "Metis_2867");
				break;
			case 26830:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726830);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728630, EnemyMetis, "Metis_2868");
				break;
			case 26840:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726840);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728640, EnemyMetis, "Metis_2869");
				break;
			case 26850:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726850);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728650, EnemyMetis, "Metis_2870");
				break;
			case 26860:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726860);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728660, EnemyMetis, "Metis_2871");
				break;
			case 26870:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726870);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728670, EnemyMetis, "Metis_2872");
				break;
			case 26880:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726880);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728680, EnemyMetis, "Metis_2873");
				break;
			case 26890:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726890);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728690, EnemyMetis, "Metis_2874");
				break;
			case 26900:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726900);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728700, EnemyMetis, "Metis_2875");
				break;
			case 26910:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726910);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728710, EnemyMetis, "Metis_2876");
				break;
			case 26920:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726920);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728720, EnemyMetis, "Metis_2877");
				break;
			case 26930:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726930);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728730, EnemyMetis, "Metis_2878");
				break;
			case 26940:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726940);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728740, EnemyMetis, "Metis_2879");
				break;
			case 26950:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726950);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728750, EnemyMetis, "Metis_2880");
				break;
			case 26960:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726960);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728760, EnemyMetis, "Metis_2881");
				break;
			case 26970:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726970);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728770, EnemyMetis, "Metis_2882");
				break;
			case 26980:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726980);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728780, EnemyMetis, "Metis_2883");
				break;
			case 26990:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726990);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728790, EnemyMetis, "Metis_2884");
				break;
			case 27000:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727000);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728800, EnemyMetis, "Metis_2885");
				break;
			case 27010:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727010);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728810, EnemyMetis, "Metis_2886");
				break;
			case 27020:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727020);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728820, EnemyMetis, "Metis_2887");
				break;
			case 27030:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727030);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728830, EnemyMetis, "Metis_2888");
				break;
			case 27040:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727040);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728840, EnemyMetis, "Metis_2889");
				break;
			case 27050:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727050);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728850, EnemyMetis, "Metis_2890");
				break;
			case 27060:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727060);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728860, EnemyMetis, "Metis_2891");
				break;
			case 27070:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727070);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728870, EnemyMetis, "Metis_2892");
				break;
			case 27080:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727080);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728880, EnemyMetis, "Metis_2893");
				break;
			case 27090:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727090);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728890, EnemyMetis, "Metis_2894");
				break;
			case 27100:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727100);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728900, EnemyMetis, "Metis_2895");
				break;
			case 27110:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727110);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728910, EnemyMetis, "Metis_2896");
				break;
			case 27120:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727120);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728920, EnemyMetis, "Metis_2897");
				break;
			case 27130:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727130);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728930, EnemyMetis, "Metis_2898");
				break;
			case 27140:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727140);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728940, EnemyMetis, "Metis_2899");
				break;
			case 27150:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727150);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728950, EnemyMetis, "Metis_2900");
				break;
			case 27160:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727160);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728960, EnemyMetis, "Metis_2901");
				break;
			case 27170:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727170);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728970, EnemyMetis, "Metis_2902");
				break;
			case 27180:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727180);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728980, EnemyMetis, "Metis_2903");
				break;
			case 27190:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727190);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728990, EnemyMetis, "Metis_2904");
				break;
			case 27200:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727200);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729000, EnemyMetis, "Metis_2905");
				break;
			case 27210:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727210);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729010, EnemyMetis, "Metis_2906");
				break;
			case 27220:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727220);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729020, EnemyMetis, "Metis_2907");
				break;
			case 27230:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727230);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729030, EnemyMetis, "Metis_2908");
				break;
			case 27240:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727240);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729040, EnemyMetis, "Metis_2909");
				break;
			case 27250:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727250);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729050, EnemyMetis, "Metis_2910");
				break;
			case 27260:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727260);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729060, EnemyMetis, "Metis_2911");
				break;
			case 27270:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727270);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729070, EnemyMetis, "Metis_2912");
				break;
			case 27280:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727280);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729080, EnemyMetis, "Metis_2913");
				break;
			case 27290:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727290);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729090, EnemyMetis, "Metis_2914");
				break;
			case 27300:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727300);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729100, EnemyMetis, "Metis_2915");
				break;
			case 27310:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727310);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729110, EnemyMetis, "Metis_2916");
				break;
			case 27320:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727320);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729120, EnemyMetis, "Metis_2917");
				break;
			case 27330:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727330);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729130, EnemyMetis, "Metis_2918");
				break;
			case 27340:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727340);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729140, EnemyMetis, "Metis_2919");
				break;
			case 27350:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727350);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729150, EnemyMetis, "Metis_2920");
				break;
			case 27360:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727360);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729160, EnemyMetis, "Metis_2921");
				break;
			case 27370:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727370);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729170, EnemyMetis, "Metis_2922");
				break;
			case 27380:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727380);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729180, EnemyMetis, "Metis_2923");
				break;
			case 27390:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727390);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729190, EnemyMetis, "Metis_2924");
				break;
			case 27400:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727400);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729200, EnemyMetis, "Metis_2925");
				break;
			case 27410:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727410);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729210, EnemyMetis, "Metis_2926");
				break;
			case 27420:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727420);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729220, EnemyMetis, "Metis_2927");
				break;
			case 27430:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727430);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729230, EnemyMetis, "Metis_2928");
				break;
			case 27440:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727440);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729240, EnemyMetis, "Metis_2929");
				break;
			case 27450:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727450);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729250, EnemyMetis, "Metis_2930");
				break;
			case 27460:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727460);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729260, EnemyMetis, "Metis_2931");
				break;
			case 27470:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727470);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729270, EnemyMetis, "Metis_2932");
				break;
			case 27480:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727480);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729280, EnemyMetis, "Metis_2933");
				break;
			case 27490:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727490);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729290, EnemyMetis, "Metis_2934");
				break;
			case 27500:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727500);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729300, EnemyMetis, "Metis_2935");
				break;
			case 27510:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727510);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729310, EnemyMetis, "Metis_2936");
				break;
			case 27520:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727520);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729320, EnemyMetis, "Metis_2937");
				break;
			case 27530:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727530);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729330, EnemyMetis, "Metis_2938");
				break;
			case 27540:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727540);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729340, EnemyMetis, "Metis_2939");
				break;
			case 27550:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727550);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729350, EnemyMetis, "Metis_2940");
				break;
			case 27560:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727560);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729360, EnemyMetis, "Metis_2941");
				break;
			case 27570:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727570);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729370, EnemyMetis, "Metis_2942");
				break;
			case 27580:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727580);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729380, EnemyMetis, "Metis_2943");
				break;
			case 27590:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727590);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729390, EnemyMetis, "Metis_2944");
				break;
			case 27600:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727600);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729400, EnemyMetis, "Metis_2945");
				break;
			case 27610:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727610);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729410, EnemyMetis, "Metis_2946");
				break;
			case 27620:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727620);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729420, EnemyMetis, "Metis_2947");
				break;
			case 27630:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727630);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729430, EnemyMetis, "Metis_2948");
				break;
			case 27640:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727640);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729440, EnemyMetis, "Metis_2949");
				break;
			case 27650:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727650);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729450, EnemyMetis, "Metis_2950");
				break;
			case 27660:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727660);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729460, EnemyMetis, "Metis_2951");
				break;
			case 27670:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727670);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729470, EnemyMetis, "Metis_2952");
				break;
			case 27680:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727680);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729480, EnemyMetis, "Metis_2953");
				break;
			case 27690:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727690);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729490, EnemyMetis, "Metis_2954");
				break;
			case 27700:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727700);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729500, EnemyMetis, "Metis_2955");
				break;
			case 27710:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727710);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729510, EnemyMetis, "Metis_2956");
				break;
			case 27720:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727720);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729520, EnemyMetis, "Metis_2957");
				break;
			case 27730:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727730);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729530, EnemyMetis, "Metis_2958");
				break;
			case 27740:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727740);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729540, EnemyMetis, "Metis_2959");
				break;
			case 27750:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727750);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729550, EnemyMetis, "Metis_2960");
				break;
			case 27760:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727760);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729560, EnemyMetis, "Metis_2961");
				break;
			case 27770:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727770);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729570, EnemyMetis, "Metis_2962");
				break;
			case 27780:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727780);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729580, EnemyMetis, "Metis_2963");
				break;
			case 27790:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727790);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729590, EnemyMetis, "Metis_2964");
				break;
			case 27800:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727800);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729600, EnemyMetis, "Metis_2965");
				break;
			case 27810:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727810);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729610, EnemyMetis, "Metis_2966");
				break;
			case 27820:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727820);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729620, EnemyMetis, "Metis_2967");
				break;
			case 27830:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727830);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729630, EnemyMetis, "Metis_2968");
				break;
			case 27840:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727840);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729640, EnemyMetis, "Metis_2969");
				break;
			case 27850:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727850);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729650, EnemyMetis, "Metis_2970");
				break;
			case 27860:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727860);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729660, EnemyMetis, "Metis_2971");
				break;
			case 27870:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727870);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729670, EnemyMetis, "Metis_2972");
				break;
			case 27880:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727880);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729680, EnemyMetis, "Metis_2973");
				break;
			case 27890:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727890);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729690, EnemyMetis, "Metis_2974");
				break;
			case 27900:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727900);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729700, EnemyMetis, "Metis_2975");
				break;
			case 27910:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727910);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729710, EnemyMetis, "Metis_2976");
				break;
			case 27920:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727920);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729720, EnemyMetis, "Metis_2977");
				break;
			case 27930:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727930);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729730, EnemyMetis, "Metis_2978");
				break;
			case 27940:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727940);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729740, EnemyMetis, "Metis_2979");
				break;
			case 27950:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727950);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729750, EnemyMetis, "Metis_2980");
				break;
			case 27960:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727960);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729760, EnemyMetis, "Metis_2981");
				break;
			case 27970:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727970);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729770, EnemyMetis, "Metis_2982");
				break;
			case 27980:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727980);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729780, EnemyMetis, "Metis_2983");
				break;
			case 27990:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727990);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729790, EnemyMetis, "Metis_2984");
				break;
			case 28000:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728000);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729800, EnemyMetis, "Metis_2985");
				break;
			case 28010:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728010);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729810, EnemyMetis, "Metis_2986");
				break;
			case 28020:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728020);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729820, EnemyMetis, "Metis_2987");
				break;
			case 28030:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728030);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729830, EnemyMetis, "Metis_2988");
				break;
			case 28040:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728040);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729840, EnemyMetis, "Metis_2989");
				break;
			case 28050:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728050);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729850, EnemyMetis, "Metis_2990");
				break;
			case 28060:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728060);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729860, EnemyMetis, "Metis_2991");
				break;
			case 28070:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728070);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729870, EnemyMetis, "Metis_2992");
				break;
			case 28080:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728080);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729880, EnemyMetis, "Metis_2993");
				break;
			case 28090:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728090);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729890, EnemyMetis, "Metis_2994");
				break;
			case 28100:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728100);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729900, EnemyMetis, "Metis_2995");
				break;
			case 28110:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728110);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729910, EnemyMetis, "Metis_2996");
				break;
			case 28120:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728120);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729920, EnemyMetis, "Metis_2997");
				break;
			case 28130:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728130);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729930, EnemyMetis, "Metis_2998");
				break;
			case 28140:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728140);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729940, EnemyMetis, "Metis_2999");
				break;
			case 28150:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728150);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729950, EnemyMetis, "Metis_3000");
				break;
			case 28160:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728160);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729960, EnemyMetis, "Metis_3001");
				break;
			case 28170:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728170);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729970, EnemyMetis, "Metis_3002");
				break;
			case 28180:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728180);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729980, EnemyMetis, "Metis_3003");
				break;
			case 28190:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728190);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729990, EnemyMetis, "Metis_3004");
				break;
			case 28200:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728200);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117730000, EnemyMetis, "Metis_3005");
				break;
			case 28210:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728210);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28220:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728220);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28230:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728230);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28240:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728240);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28250:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728250);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28260:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728260);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28270:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728270);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28280:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728280);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28290:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728290);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28300:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728300);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28310:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728310);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28320:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728320);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28330:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728330);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28340:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728340);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28350:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728350);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28360:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728360);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28370:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728370);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28380:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728380);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28390:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728390);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28400:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728400);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28410:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728410);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28420:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728420);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28430:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728430);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28440:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728440);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28450:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728450);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28460:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728460);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28470:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728470);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28480:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728480);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28490:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728490);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28500:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728500);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28510:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728510);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28520:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728520);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28530:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728530);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28540:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728540);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28550:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728550);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28560:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728560);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28570:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728570);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28580:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728580);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28590:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728590);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28600:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728600);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28610:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728610);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28620:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728620);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28630:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728630);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28640:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728640);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28650:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728650);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28660:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728660);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28670:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728670);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28680:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728680);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28690:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728690);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28700:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728700);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28710:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728710);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28720:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728720);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28730:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728730);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28740:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728740);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28750:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728750);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28760:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728760);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28770:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728770);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28780:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728780);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28790:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728790);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28800:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728800);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28810:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728810);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28820:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728820);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28830:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728830);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28840:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728840);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28850:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728850);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28860:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728860);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28870:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728870);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28880:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728880);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28890:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728890);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28900:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728900);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28910:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728910);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28920:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728920);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28930:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728930);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28940:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728940);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28950:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728950);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28960:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728960);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28970:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728970);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28980:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728980);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28990:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728990);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29000:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729000);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29010:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729010);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29020:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729020);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29030:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729030);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29040:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729040);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29050:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729050);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29060:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729060);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29070:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729070);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29080:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729080);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29090:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729090);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29100:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729100);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29110:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729110);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29120:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729120);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29130:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729130);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29140:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729140);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29150:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729150);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29160:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729160);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29170:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729170);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29180:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729180);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29190:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729190);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29200:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729200);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29210:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729210);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29220:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729220);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29230:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729230);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29240:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729240);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29250:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729250);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29260:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729260);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29270:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729270);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29280:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729280);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29290:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729290);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29300:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729300);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29310:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729310);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29320:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729320);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29330:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729330);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29340:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729340);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29350:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729350);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29360:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729360);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29370:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729370);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29380:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729380);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29390:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729390);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29400:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729400);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29410:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729410);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29420:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729420);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29430:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729430);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29440:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729440);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29450:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729450);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29460:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729460);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29470:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729470);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29480:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729480);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29490:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729490);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29500:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729500);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29510:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729510);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29520:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729520);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29530:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729530);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29540:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729540);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29550:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729550);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29560:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729560);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29570:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729570);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29580:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729580);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29590:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729590);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29600:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729600);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29610:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729610);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29620:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729620);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29630:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729630);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29640:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729640);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29650:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729650);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29660:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729660);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29670:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729670);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29680:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729680);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29690:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729690);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29700:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729700);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29710:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729710);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29720:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729720);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29730:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729730);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29740:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729740);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29750:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729750);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29760:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729760);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29770:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729770);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29780:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729780);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29790:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729790);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29800:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729800);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29810:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729810);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29820:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729820);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29830:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729830);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29840:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729840);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29850:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729850);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29860:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729860);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29870:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729870);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29880:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729880);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29890:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729890);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29900:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729900);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29910:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729910);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29920:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729920);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29930:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729930);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29940:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729940);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29950:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729950);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29960:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729960);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29970:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729970);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29980:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729980);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29990:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729990);
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
		_iCnt_Event = (_iCnt_Event < 3001-1 ? _iCnt_Event+1 : _iCnt_Event);
	}
    // gen02 end

}

void Stage01_01::processFinal() {
}

Stage01_01::~Stage01_01() {

}
