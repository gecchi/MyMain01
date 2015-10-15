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
	frame f[] = {1,20,40,60,80,100,120,140,160,180,200,220,240,260,280,300,320,340,360,380,400,420,440,460,480,500,520,540,560,580,600,620,640,660,680,700,720,740,760,780,800,820,840,860,880,900,920,940,960,980,1000,1020,1040,1060,1080,1100,1120,1140,1160,1180,1200,1220,1240,1260,1280,1300,1320,1340,1360,1380,1400,1420,1440,1460,1480,1500,1520,1540,1560,1580,1600,1620,1640,1660,1680,1700,1720,1740,1760,1780,1800,1820,1840,1860,1880,1900,1920,1940,1960,1980,2000,2020,2040,2060,2080,2100,2120,2140,2160,2180,2200,2220,2240,2260,2280,2300,2320,2340,2360,2380,2400,2420,2440,2460,2480,2500,2520,2540,2560,2580,2600,2620,2640,2660,2680,2700,2720,2740,2760,2780,2800,2820,2840,2860,2880,2900,2920,2940,2960,2980,3000,3020,3040,3060,3080,3100,3120,3140,3160,3180,3200,3220,3240,3260,3280,3300,3320,3340,3360,3380,3400,3420,3440,3460,3480,3500,3520,3540,3560,3580,3600,3620,3640,3660,3680,3700,3720,3740,3760,3780,3800,3820,3840,3860,3880,3900,3920,3940,3960,3980,4000,4020,4040,4060,4080,4100,4120,4140,4160,4180,4200,4220,4240,4260,4280,4300,4320,4340,4360,4380,4400,4420,4440,4460,4480,4500,4520,4540,4560,4580,4600,4620,4640,4660,4680,4700,4720,4740,4760,4780,4800,4820,4840,4860,4880,4900,4920,4940,4960,4980,5000,5020,5040,5060,5080,5100,5120,5140,5160,5180,5200,5220,5240,5260,5280,5300,5320,5340,5360,5380,5400,5420,5440,5460,5480,5500,5520,5540,5560,5580,5600,5620,5640,5660,5680,5700,5720,5740,5760,5780,5800,5820,5840,5860,5880,5900,5920,5940,5960,5980,6000,6020,6040,6060,6080,6100,6120,6140,6160,6180,6200,6220,6240,6260,6280,6300,6320,6340,6360,6380,6400,6420,6440,6460,6480,6500,6520,6540,6560,6580,6600,6620,6640,6660,6680,6700,6720,6740,6760,6780,6800,6820,6840,6860,6880,6900,6920,6940,6960,6980,7000,7020,7040,7060,7080,7100,7120,7140,7160,7180,7200,7220,7240,7260,7280,7300,7320,7340,7360,7380,7400,7420,7440,7460,7480,7500,7520,7540,7560,7580,7600,7620,7640,7660,7680,7700,7720,7740,7760,7780,7800,7820,7840,7860,7880,7900,7920,7940,7960,7980,8000,8020,8040,8060,8080,8100,8120,8140,8160,8180,8200,8220,8240,8260,8280,8300,8320,8340,8360,8380,8400,8420,8440,8460,8480,8500,8520,8540,8560,8580,8600,8620,8640,8660,8680,8700,8720,8740,8760,8780,8800,8820,8840,8860,8880,8900,8920,8940,8960,8980,9000,9020,9040,9060,9080,9100,9120,9140,9160,9180,9200,9220,9240,9260,9280,9300,9320,9340,9360,9380,9400,9420,9440,9460,9480,9500,9520,9540,9560,9580,9600,9620,9640,9660,9680,9700,9720,9740,9760,9780,9800,9820,9840,9860,9880,9900,9920,9940,9960,9980,10000,10020,10040,10060,10080,10100,10120,10140,10160,10180,10200,10220,10240,10260,10280,10300,10320,10340,10360,10380,10400,10420,10440,10460,10480,10500,10520,10540,10560,10580,10600,10620,10640,10660,10680,10700,10720,10740,10760,10780,10800,10820,10840,10860,10880,10900,10920,10940,10960,10980,11000,11020,11040,11060,11080,11100,11120,11140,11160,11180,11200,11220,11240,11260,11280,11300,11320,11340,11360,11380,11400,11420,11440,11460,11480,11500,11520,11540,11560,11580,11600,11620,11640,11660,11680,11700,11720,11740,11760,11780,11800,11820,11840,11860,11880,11900,11920,11940,11960,11980,12000,12020,12040,12060,12080,12100,12120,12140,12160,12180,12200,12220,12240,12260,12280,12300,12320,12340,12360,12380,12400,12420,12440,12460,12480,12500,12520,12540,12560,12580,12600,12620,12640,12660,12680,12700,12720,12740,12760,12780,12800,12820,12840,12860,12880,12900,12920,12940,12960,12980,13000,13020,13040,13060,13080,13100,13120,13140,13160,13180,13200,13220,13240,13260,13280,13300,13320,13340,13360,13380,13400,13420,13440,13460,13480,13500,13520,13540,13560,13580,13600,13620,13640,13660,13680,13700,13720,13740,13760,13780,13800,13820,13840,13860,13880,13900,13920,13940,13960,13980,14000,14020,14040,14060,14080,14100,14120,14140,14160,14180,14200,14220,14240,14260,14280,14300,14320,14340,14360,14380,14400,14420,14440,14460,14480,14500,14520,14540,14560,14580,14600,14620,14640,14660,14680,14700,14720,14740,14760,14780,14800,14820,14840,14860,14880,14900,14920,14940,14960,14980,15000,15020,15040,15060,15080,15100,15120,15140,15160,15180,15200,15220,15240,15260,15280,15300,15320,15340,15360,15380,15400,15420,15440,15460,15480,15500,15520,15540,15560,15580,15600,15620,15640,15660,15680,15700,15720,15740,15760,15780,15800,15820,15840,15860,15880,15900,15920,15940,15960,15980,16000,16020,16040,16060,16080,16100,16120,16140,16160,16180,16200,16220,16240,16260,16280,16300,16320,16340,16360,16380,16400,16420,16440,16460,16480,16500,16520,16540,16560,16580,16600,16620,16640,16660,16680,16700,16720,16740,16760,16780,16800,16820,16840,16860,16880,16900,16920,16940,16960,16980,17000,17020,17040,17060,17080,17100,17120,17140,17160,17180,17200,17220,17240,17260,17280,17300,17320,17340,17360,17380,17400,17420,17440,17460,17480,17500,17520,17540,17560,17580,17600,17620,17640,17660,17680,17700,17720,17740,17760,17780,17800,17820,17840,17860,17880,17900,17920,17940,17960,17980,18000,18020,18040,18060,18080,18100,18120,18140,18160,18180,18200,18220,18240,18260,18280,18300,18320,18340,18360,18380,18400,18420,18440,18460,18480,18500,18520,18540,18560,18580,18600,18620,18640,18660,18680,18700,18720,18740,18760,18780,18800,18820,18840,18860,18880,18900,18920,18940,18960,18980,19000,19020,19040,19060,19080,19100,19120,19140,19160,19180,19200,19220,19240,19260,19280,19300,19320,19340,19360,19380,19400,19420,19440,19460,19480,19500,19520,19540,19560,19580,19600,19620,19640,19660,19680,19700,19720,19740,19760,19780,19800,19820,19840,19860,19880,19900,19920,19940,19960,19980,20000,20020,20040,20060,20080,20100,20120,20140,20160,20180,20200,20220,20240,20260,20280,20300,20320,20340,20360,20380,20400,20420,20440,20460,20480,20500,20520,20540,20560,20580,20600,20620,20640,20660,20680,20700,20720,20740,20760,20780,20800,20820,20840,20860,20880,20900,20920,20940,20960,20980,21000,21020,21040,21060,21080,21100,21120,21140,21160,21180,21200,21220,21240,21260,21280,21300,21320,21340,21360,21380,21400,21420,21440,21460,21480,21500,21520,21540,21560,21580,21600,21620,21640,21660,21680,21700,21720,21740,21760,21780,21800,21820,21840,21860,21880,21900,21920,21940,21960,21980,22000,22020,22040,22060,22080,22100,22120,22140,22160,22180,22200,22220,22240,22260,22280,22300,22320,22340,22360,22380,22400,22420,22440,22460,22480,22500,22520,22540,22560,22580,22600,22620,22640,22660,22680,22700,22720,22740,22760,22780,22800,22820,22840,22860,22880,22900,22920,22940,22960,22980,23000,23020,23040,23060,23080,23100,23120,23140,23160,23180,23200,23220,23240,23260,23280,23300,23320,23340,23360,23380,23400,23420,23440,23460,23480,23500,23520,23540,23560,23580,23600,23620,23640,23660,23680,23700,23720,23740,23760,23780,23800,23820,23840,23860,23880,23900,23920,23940,23960,23980,24000,24020,24040,24060,24080,24100,24120,24140,24160,24180,24200,24220,24240,24260,24280,24300,24320,24340,24360,24380,24400,24420,24440,24460,24480,24500,24520,24540,24560,24580,24600,24620,24640,24660,24680,24700,24720,24740,24760,24780,24800,24820,24840,24860,24880,24900,24920,24940,24960,24980,25000,25020,25040,25060,25080,25100,25120,25140,25160,25180,25200,25220,25240,25260,25280,25300,25320,25340,25360,25380,25400,25420,25440,25460,25480,25500,25520,25540,25560,25580,25600,25620,25640,25660,25680,25700,25720,25740,25760,25780,25800,25820,25840,25860,25880,25900,25920,25940,25960,25980,26000,26020,26040,26060,26080,26100,26120,26140,26160,26180,26200,26220,26240,26260,26280,26300,26320,26340,26360,26380,26400,26420,26440,26460,26480,26500,26520,26540,26560,26580,26600,26620,26640,26660,26680,26700,26720,26740,26760,26780,26800,26820,26840,26860,26880,26900,26920,26940,26960,26980,27000,27020,27040,27060,27080,27100,27120,27140,27160,27180,27200,27220,27240,27260,27280,27300,27320,27340,27360,27380,27400,27420,27440,27460,27480,27500,27520,27540,27560,27580,27600,27620,27640,27660,27680,27700,27720,27740,27760,27780,27800,27820,27840,27860,27880,27900,27920,27940,27960,27980,28000,28020,28040,28060,28080,28100,28120,28140,28160,28180,28200,28220,28240,28260,28280,28300,28320,28340,28360,28380,28400,28420,28440,28460,28480,28500,28520,28540,28560,28580,28600,28620,28640,28660,28680,28700,28720,28740,28760,28780,28800,28820,28840,28860,28880,28900,28920,28940,28960,28980,29000,29020,29040,29060,29080,29100,29120,29140,29160,29180,29200,29220,29240,29260,29280,29300,29320,29340,29360,29380,29400,29420,29440,29460,29480,29500,29520,29540,29560,29580,29600,29620,29640,29660,29680,29700,29720,29740,29760,29780,29800,29820,29840,29860,29880,29900,29920,29940,29960,29980,30000,30020,30040,30060,30080,30100,30120,30140,30160,30180,30200,30220,30240,30260,30280,30300,30320,30340,30360,30380,30400,30420,30440,30460,30480,30500,30520,30540,30560,30580,30600,30620,30640,30660,30680,30700,30720,30740,30760,30780,30800,30820,30840,30860,30880,30900,30920,30940,30960,30980,31000,31020,31040,31060,31080,31100,31120,31140,31160,31180,31200,31220,31240,31260,31280,31300,31320,31340,31360,31380,31400,31420,31440,31460,31480,31500,31520,31540,31560,31580,31600,31620,31640,31660,31680,31700,31720,31740,31760,31780,31800,31820,31840,31860,31880,31900,31920,31940,31960,31980,32000,32020,32040,32060,32080,32100,32120,32140,32160,32180,32200,32220,32240,32260,32280,32300,32320,32340,32360,32380,32400,32420,32440,32460,32480,32500,32520,32540,32560,32580,32600,32620,32640,32660,32680,32700,32720,32740,32760,32780,32800,32820,32840,32860,32880,32900,32920,32940,32960,32980,33000,33020,33040,33060,33080,33100,33120,33140,33160,33180,33200,33220,33240,33260,33280,33300,33320,33340,33360,33380,33400,33420,33440,33460,33480,33500,33520,33540,33560,33580,33600,33620,33640,33660,33680,33700,33720,33740,33760,33780,33800,33820,33840,33860,33880,33900,33920,33940,33960,33980,34000,34020,34040,34060,34080,34100,34120,34140,34160,34180,34200,34220,34240,34260,34280,34300,34320,34340,34360,34380,34400,34420,34440,34460,34480,34500,34520,34540,34560,34580,34600,34620,34640,34660,34680,34700,34720,34740,34760,34780,34800,34820,34840,34860,34880,34900,34920,34940,34960,34980,35000,35020,35040,35060,35080,35100,35120,35140,35160,35180,35200,35220,35240,35260,35280,35300,35320,35340,35360,35380,35400,35420,35440,35460,35480,35500,35520,35540,35560,35580,35600,35620,35640,35660,35680,35700,35720,35740,35760,35780,35800,35820,35840,35860,35880,35900,35920,35940,35960,35980,36000,36020,36040,36060,36080,36100,36120,36140,36160,36180,36200,36220,36240,36260,36280,36300,36320,36340,36360,36380,36400,36420,36440,36460,36480,36500,36520,36540,36560,36580,36600,36620,36640,36660,36680,36700,36720,36740,36760,36780,36800,36820,36840,36860,36880,36900,36920,36940,36960,36980,37000,37020,37040,37060,37080,37100,37120,37140,37160,37180,37200,37220,37240,37260,37280,37300,37320,37340,37360,37380,37400,37420,37440,37460,37480,37500,37520,37540,37560,37580,37600,37620,37640,37660,37680,37700,37720,37740,37760,37780,37800,37820,37840,37860,37880,37900,37920,37940,37960,37980,38000,38020,38040,38060,38080,38100,38120,38140,38160,38180,38200,38220,38240,38260,38280,38300,38320,38340,38360,38380,38400,38420,38440,38460,38480,38500,38520,38540,38560,38580,38600,38620,38640,38660,38680,38700,38720,38740,38760,38780,38800,38820,38840,38860,38880,38900,38920,38940,38960,38980,39000,39020,39040,39060,39080,39100,39120,39140,39160,39180,39200,39220,39240,39260,39280,39300,39320,39340,39360,39380,39400,39420,39440,39460,39480,39500,39520,39540,39560,39580,39600,39620,39640,39660,39680,39700,39720,39740,39760,39780,39800,39820,39840,39860,39880,39900,39920,39940,39960,39980,40000,40020,40040,40060,40080,40100,40120,40140,40160,40180,40200,40220,40240,40260,40280,40300,40320,40340,40360,40380,40400,40420,40440,40460,40480,40500,40520,40540,40560,40580,40600,40620,40640,40660,40680,40700,40720,40740,40760,40780,40800,40820,40840,40860,40880,40900,40920,40940,40960,40980,41000,41020,41040,41060,41080,41100,41120,41140,41160,41180,41200,41220,41240,41260,41280,41300,41320,41340,41360,41380,41400,41420,41440,41460,41480,41500,41520,41540,41560,41580,41600,41620,41640,41660,41680,41700,41720,41740,41760,41780,41800,41820,41840,41860,41880,41900,41920,41940,41960,41980,42000,42020,42040,42060,42080,42100,42120,42140,42160,42180,42200,42220,42240,42260,42280,42300,42320,42340,42360,42380,42400,42420,42440,42460,42480,42500,42520,42540,42560,42580,42600,42620,42640,42660,42680,42700,42720,42740,42760,42780,42800,42820,42840,42860,42880,42900,42920,42940,42960,42980,43000,43020,43040,43060,43080,43100,43120,43140,43160,43180,43200,43220,43240,43260,43280,43300,43320,43340,43360,43380,43400,43420,43440,43460,43480,43500,43520,43540,43560,43580,43600,43620,43640,43660,43680,43700,43720,43740,43760,43780,43800,43820,43840,43860,43880,43900,43920,43940,43960,43980,44000,44020,44040,44060,44080,44100,44120,44140,44160,44180,44200,44220,44240,44260,44280,44300,44320,44340,44360,44380,44400,44420,44440,44460,44480,44500,44520,44540,44560,44580,44600,44620,44640,44660,44680,44700,44720,44740,44760,44780,44800,44820,44840,44860,44880,44900,44920,44940,44960,44980,45000,45020,45040,45060,45080,45100,45120,45140,45160,45180,45200,45220,45240,45260,45280,45300,45320,45340,45360,45380,45400,45420,45440,45460,45480,45500,45520,45540,45560,45580,45600,45620,45640,45660,45680,45700,45720,45740,45760,45780,45800,45820,45840,45860,45880,45900,45920,45940,45960,45980,46000,46020,46040,46060,46080,46100,46120,46140,46160,46180,46200,46220,46240,46260,46280,46300,46320,46340,46360,46380,46400,46420,46440,46460,46480,46500,46520,46540,46560,46580,46600,46620,46640,46660,46680,46700,46720,46740,46760,46780,46800,46820,46840,46860,46880,46900,46920,46940,46960,46980,47000,47020,47040,47060,47080,47100,47120,47140,47160,47180,47200,47220,47240,47260,47280,47300,47320,47340,47360,47380,47400,47420,47440,47460,47480,47500,47520,47540,47560,47580,47600,47620,47640,47660,47680,47700,47720,47740,47760,47780,47800,47820,47840,47860,47880,47900,47920,47940,47960,47980,48000,48020,48040,48060,48080,48100,48120,48140,48160,48180,48200,48220,48240,48260,48280,48300,48320,48340,48360,48380,48400,48420,48440,48460,48480,48500,48520,48540,48560,48580,48600,48620,48640,48660,48680,48700,48720,48740,48760,48780,48800,48820,48840,48860,48880,48900,48920,48940,48960,48980,49000,49020,49040,49060,49080,49100,49120,49140,49160,49180,49200,49220,49240,49260,49280,49300,49320,49340,49360,49380,49400,49420,49440,49460,49480,49500,49520,49540,49560,49580,49600,49620,49640,49660,49680,49700,49720,49740,49760,49780,49800,49820,49840,49860,49880,49900,49920,49940,49960,49980,50000};
	_paFrame_NextEvent = new frame[2501];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 2501;
	orderActorToFactory(10000000, EnemyOebiusController001, "EnemyOebiusController001-1");
	orderActorToFactory(10000002, EnemyEtis, "EnemyEtis-2");
	orderActorToFactory(10000003, EnemyEtis, "EnemyEtis-3");
	orderActorToFactory(10000004, EnemyEtis, "EnemyEtis-4");
	orderActorToFactory(10000005, EnemyEtis, "EnemyEtis-5");
	orderActorToFactory(10000006, EnemyEtis, "EnemyEtis-6");
	orderActorToFactory(10000007, EnemyEtis, "EnemyEtis-7");
	orderActorToFactory(10000008, EnemyEtis, "EnemyEtis-8");
	orderActorToFactory(10000009, EnemyEtis, "EnemyEtis-9");
	orderActorToFactory(10000010, EnemyEtis, "EnemyEtis-10");
	orderActorToFactory(10000011, EnemyEtis, "EnemyEtis-11");
	orderActorToFactory(10000012, EnemyEtis, "EnemyEtis-12");
	orderActorToFactory(10000013, EnemyEtis, "EnemyEtis-13");
	orderActorToFactory(10000014, EnemyEtis, "EnemyEtis-14");
	orderActorToFactory(10000015, EnemyEtis, "EnemyEtis-15");
	orderActorToFactory(10000016, EnemyEtis, "EnemyEtis-16");
	orderActorToFactory(10000017, EnemyEtis, "EnemyEtis-17");
	orderActorToFactory(10000018, EnemyEtis, "EnemyEtis-18");
	orderActorToFactory(10000019, EnemyEtis, "EnemyEtis-19");
	orderActorToFactory(10000020, EnemyEtis, "EnemyEtis-20");
	orderActorToFactory(10000021, EnemyEtis, "EnemyEtis-21");
	orderActorToFactory(10000022, EnemyEtis, "EnemyEtis-22");
	orderActorToFactory(10000023, EnemyEtis, "EnemyEtis-23");
	orderActorToFactory(10000024, EnemyEtis, "EnemyEtis-24");
	orderActorToFactory(10000025, EnemyEtis, "EnemyEtis-25");
	orderActorToFactory(10000026, EnemyEtis, "EnemyEtis-26");
	orderActorToFactory(10000027, EnemyEtis, "EnemyEtis-27");
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
			case 20: {
				orderActorToFactory(10000001, EnemyOebiusController002, "EnemyOebiusController002-28");
				orderActorToFactory(10000028, EnemyEtis, "EnemyEtis-29");
				break;
			}
			case 40: {
				orderActorToFactory(10000029, EnemyEtis, "EnemyEtis-30");
				break;
			}
			case 60: {
				orderActorToFactory(10000030, EnemyEtis, "EnemyEtis-31");
				break;
			}
			case 80: {
				orderActorToFactory(10000031, EnemyEtis, "EnemyEtis-32");
				break;
			}
			case 100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000002);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000032, EnemyEtis, "EnemyEtis-33");
				break;
			}
			case 120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000003);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000033, EnemyEtis, "EnemyEtis-34");
				break;
			}
			case 140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000004);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000034, EnemyEtis, "EnemyEtis-35");
				break;
			}
			case 160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000005);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000035, EnemyEtis, "EnemyEtis-36");
				break;
			}
			case 180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000006);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000036, EnemyEtis, "EnemyEtis-37");
				break;
			}
			case 200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000007);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000037, EnemyEtis, "EnemyEtis-38");
				break;
			}
			case 220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000008);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000038, EnemyEtis, "EnemyEtis-39");
				break;
			}
			case 240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000009);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000039, EnemyEtis, "EnemyEtis-40");
				break;
			}
			case 260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000010);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000040, EnemyEtis, "EnemyEtis-41");
				break;
			}
			case 280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000011);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000041, EnemyEtis, "EnemyEtis-42");
				break;
			}
			case 300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000012);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000042, EnemyEtis, "EnemyEtis-43");
				break;
			}
			case 320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000013);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000043, EnemyEtis, "EnemyEtis-44");
				break;
			}
			case 340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000014);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000044, EnemyEtis, "EnemyEtis-45");
				break;
			}
			case 360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000015);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000045, EnemyEtis, "EnemyEtis-46");
				break;
			}
			case 380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000016);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000046, EnemyEtis, "EnemyEtis-47");
				break;
			}
			case 400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000017);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000047, EnemyEtis, "EnemyEtis-48");
				break;
			}
			case 420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000018);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000048, EnemyEtis, "EnemyEtis-49");
				break;
			}
			case 440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000019);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000049, EnemyEtis, "EnemyEtis-50");
				break;
			}
			case 460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000020);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000050, EnemyEtis, "EnemyEtis-51");
				break;
			}
			case 480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000021);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000051, EnemyEtis, "EnemyEtis-52");
				break;
			}
			case 500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000022);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000052, EnemyEtis, "EnemyEtis-53");
				break;
			}
			case 520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000023);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000053, EnemyEtis, "EnemyEtis-54");
				break;
			}
			case 540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000024);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000054, EnemyEtis, "EnemyEtis-55");
				break;
			}
			case 560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000025);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000055, EnemyEtis, "EnemyEtis-56");
				break;
			}
			case 580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000026);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000056, EnemyEtis, "EnemyEtis-57");
				break;
			}
			case 600: {
				EnemyOebiusController001* p1 = (EnemyOebiusController001*)obtainActorFromFactory(10000000);
				bringDirector()->addSubGroup(p1);
				p1->position(PX_C(800), PX_C(100), PX_C(400) );
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000027);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000057, EnemyEtis, "EnemyEtis-58");
				break;
			}
			case 620: {
				EnemyOebiusController002* p2 = (EnemyOebiusController002*)obtainActorFromFactory(10000001);
				bringDirector()->addSubGroup(p2);
				p2->position(PX_C(800), PX_C(400), PX_C(100) );
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000028);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000058, EnemyEtis, "EnemyEtis-59");
				break;
			}
			case 640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000029);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000059, EnemyEtis, "EnemyEtis-60");
				break;
			}
			case 660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000030);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000060, EnemyEtis, "EnemyEtis-61");
				break;
			}
			case 680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000031);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000061, EnemyEtis, "EnemyEtis-62");
				break;
			}
			case 700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000032);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000062, EnemyEtis, "EnemyEtis-63");
				break;
			}
			case 720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000033);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000063, EnemyEtis, "EnemyEtis-64");
				break;
			}
			case 740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000034);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000064, EnemyEtis, "EnemyEtis-65");
				break;
			}
			case 760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000035);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000065, EnemyEtis, "EnemyEtis-66");
				break;
			}
			case 780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000036);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000066, EnemyEtis, "EnemyEtis-67");
				break;
			}
			case 800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000037);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000067, EnemyEtis, "EnemyEtis-68");
				break;
			}
			case 820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000038);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000068, EnemyEtis, "EnemyEtis-69");
				break;
			}
			case 840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000039);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000069, EnemyEtis, "EnemyEtis-70");
				break;
			}
			case 860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000040);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000070, EnemyEtis, "EnemyEtis-71");
				break;
			}
			case 880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000041);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000071, EnemyEtis, "EnemyEtis-72");
				break;
			}
			case 900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000042);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000072, EnemyEtis, "EnemyEtis-73");
				break;
			}
			case 920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000043);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000073, EnemyEtis, "EnemyEtis-74");
				break;
			}
			case 940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000044);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000074, EnemyEtis, "EnemyEtis-75");
				break;
			}
			case 960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000045);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000075, EnemyEtis, "EnemyEtis-76");
				break;
			}
			case 980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000046);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000076, EnemyEtis, "EnemyEtis-77");
				break;
			}
			case 1000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000047);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000077, EnemyEtis, "EnemyEtis-78");
				break;
			}
			case 1020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000048);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000078, EnemyEtis, "EnemyEtis-79");
				break;
			}
			case 1040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000049);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000079, EnemyEtis, "EnemyEtis-80");
				break;
			}
			case 1060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000050);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000080, EnemyEtis, "EnemyEtis-81");
				break;
			}
			case 1080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000051);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000081, EnemyEtis, "EnemyEtis-82");
				break;
			}
			case 1100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000052);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000082, EnemyEtis, "EnemyEtis-83");
				break;
			}
			case 1120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000053);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000083, EnemyEtis, "EnemyEtis-84");
				break;
			}
			case 1140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000054);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000084, EnemyEtis, "EnemyEtis-85");
				break;
			}
			case 1160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000055);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000085, EnemyEtis, "EnemyEtis-86");
				break;
			}
			case 1180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000056);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000086, EnemyEtis, "EnemyEtis-87");
				break;
			}
			case 1200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000057);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000087, EnemyEtis, "EnemyEtis-88");
				break;
			}
			case 1220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000058);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000088, EnemyEtis, "EnemyEtis-89");
				break;
			}
			case 1240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000059);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000089, EnemyEtis, "EnemyEtis-90");
				break;
			}
			case 1260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000060);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000090, EnemyEtis, "EnemyEtis-91");
				break;
			}
			case 1280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000061);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000091, EnemyEtis, "EnemyEtis-92");
				break;
			}
			case 1300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000062);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000092, EnemyEtis, "EnemyEtis-93");
				break;
			}
			case 1320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000063);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000093, EnemyEtis, "EnemyEtis-94");
				break;
			}
			case 1340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000064);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000094, EnemyEtis, "EnemyEtis-95");
				break;
			}
			case 1360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000065);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000095, EnemyEtis, "EnemyEtis-96");
				break;
			}
			case 1380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000066);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000096, EnemyEtis, "EnemyEtis-97");
				break;
			}
			case 1400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000067);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000097, EnemyEtis, "EnemyEtis-98");
				break;
			}
			case 1420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000068);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000098, EnemyEtis, "EnemyEtis-99");
				break;
			}
			case 1440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000069);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000099, EnemyEtis, "EnemyEtis-100");
				break;
			}
			case 1460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000070);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000100, EnemyEtis, "EnemyEtis-101");
				break;
			}
			case 1480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000071);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000101, EnemyEtis, "EnemyEtis-102");
				break;
			}
			case 1500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000072);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000102, EnemyEtis, "EnemyEtis-103");
				break;
			}
			case 1520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000073);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000103, EnemyEtis, "EnemyEtis-104");
				break;
			}
			case 1540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000074);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000104, EnemyEtis, "EnemyEtis-105");
				break;
			}
			case 1560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000075);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000105, EnemyEtis, "EnemyEtis-106");
				break;
			}
			case 1580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000076);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000106, EnemyEtis, "EnemyEtis-107");
				break;
			}
			case 1600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000077);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000107, EnemyEtis, "EnemyEtis-108");
				break;
			}
			case 1620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000078);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000108, EnemyEtis, "EnemyEtis-109");
				break;
			}
			case 1640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000079);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000109, EnemyEtis, "EnemyEtis-110");
				break;
			}
			case 1660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000080);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000110, EnemyEtis, "EnemyEtis-111");
				break;
			}
			case 1680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000081);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000111, EnemyEtis, "EnemyEtis-112");
				break;
			}
			case 1700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000082);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000112, EnemyEtis, "EnemyEtis-113");
				break;
			}
			case 1720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000083);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000113, EnemyEtis, "EnemyEtis-114");
				break;
			}
			case 1740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000084);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000114, EnemyEtis, "EnemyEtis-115");
				break;
			}
			case 1760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000085);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000115, EnemyEtis, "EnemyEtis-116");
				break;
			}
			case 1780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000086);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000116, EnemyEtis, "EnemyEtis-117");
				break;
			}
			case 1800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000087);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000117, EnemyEtis, "EnemyEtis-118");
				break;
			}
			case 1820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000088);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000118, EnemyEtis, "EnemyEtis-119");
				break;
			}
			case 1840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000089);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000119, EnemyEtis, "EnemyEtis-120");
				break;
			}
			case 1860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000090);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000120, EnemyEtis, "EnemyEtis-121");
				break;
			}
			case 1880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000091);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000121, EnemyEtis, "EnemyEtis-122");
				break;
			}
			case 1900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000092);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000122, EnemyEtis, "EnemyEtis-123");
				break;
			}
			case 1920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000093);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000123, EnemyEtis, "EnemyEtis-124");
				break;
			}
			case 1940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000094);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000124, EnemyEtis, "EnemyEtis-125");
				break;
			}
			case 1960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000095);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000125, EnemyEtis, "EnemyEtis-126");
				break;
			}
			case 1980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000096);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000126, EnemyEtis, "EnemyEtis-127");
				break;
			}
			case 2000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000097);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000127, EnemyEtis, "EnemyEtis-128");
				break;
			}
			case 2020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000098);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000128, EnemyEtis, "EnemyEtis-129");
				break;
			}
			case 2040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000099);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000129, EnemyEtis, "EnemyEtis-130");
				break;
			}
			case 2060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000100);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000130, EnemyEtis, "EnemyEtis-131");
				break;
			}
			case 2080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000101);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000131, EnemyEtis, "EnemyEtis-132");
				break;
			}
			case 2100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000102);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000132, EnemyEtis, "EnemyEtis-133");
				break;
			}
			case 2120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000103);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000133, EnemyEtis, "EnemyEtis-134");
				break;
			}
			case 2140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000104);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000134, EnemyEtis, "EnemyEtis-135");
				break;
			}
			case 2160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000105);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000135, EnemyEtis, "EnemyEtis-136");
				break;
			}
			case 2180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000106);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000136, EnemyEtis, "EnemyEtis-137");
				break;
			}
			case 2200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000107);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000137, EnemyEtis, "EnemyEtis-138");
				break;
			}
			case 2220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000108);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000138, EnemyEtis, "EnemyEtis-139");
				break;
			}
			case 2240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000109);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000139, EnemyEtis, "EnemyEtis-140");
				break;
			}
			case 2260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000110);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000140, EnemyEtis, "EnemyEtis-141");
				break;
			}
			case 2280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000111);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000141, EnemyEtis, "EnemyEtis-142");
				break;
			}
			case 2300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000112);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000142, EnemyEtis, "EnemyEtis-143");
				break;
			}
			case 2320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000113);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000143, EnemyEtis, "EnemyEtis-144");
				break;
			}
			case 2340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000114);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000144, EnemyEtis, "EnemyEtis-145");
				break;
			}
			case 2360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000115);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000145, EnemyEtis, "EnemyEtis-146");
				break;
			}
			case 2380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000116);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000146, EnemyEtis, "EnemyEtis-147");
				break;
			}
			case 2400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000117);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000147, EnemyEtis, "EnemyEtis-148");
				break;
			}
			case 2420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000118);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000148, EnemyEtis, "EnemyEtis-149");
				break;
			}
			case 2440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000119);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000149, EnemyEtis, "EnemyEtis-150");
				break;
			}
			case 2460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000120);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000150, EnemyEtis, "EnemyEtis-151");
				break;
			}
			case 2480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000121);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000151, EnemyEtis, "EnemyEtis-152");
				break;
			}
			case 2500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000122);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000152, EnemyEtis, "EnemyEtis-153");
				break;
			}
			case 2520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000123);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000153, EnemyEtis, "EnemyEtis-154");
				break;
			}
			case 2540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000124);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000154, EnemyEtis, "EnemyEtis-155");
				break;
			}
			case 2560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000125);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000155, EnemyEtis, "EnemyEtis-156");
				break;
			}
			case 2580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000126);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000156, EnemyEtis, "EnemyEtis-157");
				break;
			}
			case 2600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000127);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000157, EnemyEtis, "EnemyEtis-158");
				break;
			}
			case 2620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000128);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000158, EnemyEtis, "EnemyEtis-159");
				break;
			}
			case 2640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000129);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000159, EnemyEtis, "EnemyEtis-160");
				break;
			}
			case 2660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000130);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000160, EnemyEtis, "EnemyEtis-161");
				break;
			}
			case 2680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000131);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000161, EnemyEtis, "EnemyEtis-162");
				break;
			}
			case 2700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000132);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000162, EnemyEtis, "EnemyEtis-163");
				break;
			}
			case 2720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000133);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000163, EnemyEtis, "EnemyEtis-164");
				break;
			}
			case 2740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000134);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000164, EnemyEtis, "EnemyEtis-165");
				break;
			}
			case 2760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000135);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000165, EnemyEtis, "EnemyEtis-166");
				break;
			}
			case 2780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000136);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000166, EnemyEtis, "EnemyEtis-167");
				break;
			}
			case 2800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000137);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000167, EnemyEtis, "EnemyEtis-168");
				break;
			}
			case 2820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000138);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000168, EnemyEtis, "EnemyEtis-169");
				break;
			}
			case 2840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000139);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000169, EnemyEtis, "EnemyEtis-170");
				break;
			}
			case 2860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000140);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000170, EnemyEtis, "EnemyEtis-171");
				break;
			}
			case 2880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000141);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000171, EnemyEtis, "EnemyEtis-172");
				break;
			}
			case 2900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000142);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000172, EnemyEtis, "EnemyEtis-173");
				break;
			}
			case 2920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000143);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000173, EnemyEtis, "EnemyEtis-174");
				break;
			}
			case 2940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000144);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000174, EnemyEtis, "EnemyEtis-175");
				break;
			}
			case 2960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000145);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000175, EnemyEtis, "EnemyEtis-176");
				break;
			}
			case 2980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000146);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000176, EnemyEtis, "EnemyEtis-177");
				break;
			}
			case 3000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000147);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000177, EnemyEtis, "EnemyEtis-178");
				break;
			}
			case 3020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000148);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000178, EnemyEtis, "EnemyEtis-179");
				break;
			}
			case 3040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000149);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000179, EnemyEtis, "EnemyEtis-180");
				break;
			}
			case 3060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000150);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000180, EnemyEtis, "EnemyEtis-181");
				break;
			}
			case 3080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000151);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000181, EnemyEtis, "EnemyEtis-182");
				break;
			}
			case 3100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000152);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000182, EnemyEtis, "EnemyEtis-183");
				break;
			}
			case 3120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000153);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000183, EnemyEtis, "EnemyEtis-184");
				break;
			}
			case 3140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000154);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000184, EnemyEtis, "EnemyEtis-185");
				break;
			}
			case 3160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000155);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000185, EnemyEtis, "EnemyEtis-186");
				break;
			}
			case 3180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000156);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000186, EnemyEtis, "EnemyEtis-187");
				break;
			}
			case 3200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000157);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000187, EnemyEtis, "EnemyEtis-188");
				break;
			}
			case 3220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000158);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000188, EnemyEtis, "EnemyEtis-189");
				break;
			}
			case 3240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000159);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000189, EnemyEtis, "EnemyEtis-190");
				break;
			}
			case 3260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000160);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000190, EnemyEtis, "EnemyEtis-191");
				break;
			}
			case 3280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000161);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000191, EnemyEtis, "EnemyEtis-192");
				break;
			}
			case 3300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000162);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000192, EnemyEtis, "EnemyEtis-193");
				break;
			}
			case 3320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000163);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000193, EnemyEtis, "EnemyEtis-194");
				break;
			}
			case 3340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000164);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000194, EnemyEtis, "EnemyEtis-195");
				break;
			}
			case 3360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000165);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000195, EnemyEtis, "EnemyEtis-196");
				break;
			}
			case 3380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000166);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000196, EnemyEtis, "EnemyEtis-197");
				break;
			}
			case 3400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000167);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000197, EnemyEtis, "EnemyEtis-198");
				break;
			}
			case 3420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000168);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000198, EnemyEtis, "EnemyEtis-199");
				break;
			}
			case 3440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000169);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000199, EnemyEtis, "EnemyEtis-200");
				break;
			}
			case 3460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000170);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000200, EnemyEtis, "EnemyEtis-201");
				break;
			}
			case 3480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000171);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000201, EnemyEtis, "EnemyEtis-202");
				break;
			}
			case 3500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000172);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000202, EnemyEtis, "EnemyEtis-203");
				break;
			}
			case 3520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000173);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000203, EnemyEtis, "EnemyEtis-204");
				break;
			}
			case 3540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000174);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000204, EnemyEtis, "EnemyEtis-205");
				break;
			}
			case 3560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000175);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000205, EnemyEtis, "EnemyEtis-206");
				break;
			}
			case 3580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000176);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000206, EnemyEtis, "EnemyEtis-207");
				break;
			}
			case 3600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000177);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000207, EnemyEtis, "EnemyEtis-208");
				break;
			}
			case 3620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000178);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000208, EnemyEtis, "EnemyEtis-209");
				break;
			}
			case 3640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000179);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000209, EnemyEtis, "EnemyEtis-210");
				break;
			}
			case 3660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000180);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000210, EnemyEtis, "EnemyEtis-211");
				break;
			}
			case 3680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000181);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000211, EnemyEtis, "EnemyEtis-212");
				break;
			}
			case 3700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000182);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000212, EnemyEtis, "EnemyEtis-213");
				break;
			}
			case 3720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000183);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000213, EnemyEtis, "EnemyEtis-214");
				break;
			}
			case 3740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000184);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000214, EnemyEtis, "EnemyEtis-215");
				break;
			}
			case 3760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000185);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000215, EnemyEtis, "EnemyEtis-216");
				break;
			}
			case 3780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000186);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000216, EnemyEtis, "EnemyEtis-217");
				break;
			}
			case 3800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000187);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000217, EnemyEtis, "EnemyEtis-218");
				break;
			}
			case 3820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000188);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000218, EnemyEtis, "EnemyEtis-219");
				break;
			}
			case 3840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000189);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000219, EnemyEtis, "EnemyEtis-220");
				break;
			}
			case 3860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000190);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000220, EnemyEtis, "EnemyEtis-221");
				break;
			}
			case 3880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000191);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000221, EnemyEtis, "EnemyEtis-222");
				break;
			}
			case 3900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000192);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000222, EnemyEtis, "EnemyEtis-223");
				break;
			}
			case 3920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000193);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000223, EnemyEtis, "EnemyEtis-224");
				break;
			}
			case 3940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000194);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000224, EnemyEtis, "EnemyEtis-225");
				break;
			}
			case 3960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000195);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000225, EnemyEtis, "EnemyEtis-226");
				break;
			}
			case 3980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000196);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000226, EnemyEtis, "EnemyEtis-227");
				break;
			}
			case 4000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000197);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000227, EnemyEtis, "EnemyEtis-228");
				break;
			}
			case 4020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000198);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000228, EnemyEtis, "EnemyEtis-229");
				break;
			}
			case 4040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000199);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000229, EnemyEtis, "EnemyEtis-230");
				break;
			}
			case 4060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000200);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000230, EnemyEtis, "EnemyEtis-231");
				break;
			}
			case 4080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000201);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000231, EnemyEtis, "EnemyEtis-232");
				break;
			}
			case 4100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000202);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000232, EnemyEtis, "EnemyEtis-233");
				break;
			}
			case 4120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000203);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000233, EnemyEtis, "EnemyEtis-234");
				break;
			}
			case 4140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000204);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000234, EnemyEtis, "EnemyEtis-235");
				break;
			}
			case 4160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000205);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000235, EnemyEtis, "EnemyEtis-236");
				break;
			}
			case 4180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000206);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000236, EnemyEtis, "EnemyEtis-237");
				break;
			}
			case 4200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000207);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000237, EnemyEtis, "EnemyEtis-238");
				break;
			}
			case 4220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000208);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000238, EnemyEtis, "EnemyEtis-239");
				break;
			}
			case 4240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000209);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000239, EnemyEtis, "EnemyEtis-240");
				break;
			}
			case 4260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000210);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000240, EnemyEtis, "EnemyEtis-241");
				break;
			}
			case 4280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000211);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000241, EnemyEtis, "EnemyEtis-242");
				break;
			}
			case 4300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000212);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000242, EnemyEtis, "EnemyEtis-243");
				break;
			}
			case 4320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000213);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000243, EnemyEtis, "EnemyEtis-244");
				break;
			}
			case 4340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000214);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000244, EnemyEtis, "EnemyEtis-245");
				break;
			}
			case 4360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000215);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000245, EnemyEtis, "EnemyEtis-246");
				break;
			}
			case 4380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000216);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000246, EnemyEtis, "EnemyEtis-247");
				break;
			}
			case 4400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000217);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000247, EnemyEtis, "EnemyEtis-248");
				break;
			}
			case 4420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000218);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000248, EnemyEtis, "EnemyEtis-249");
				break;
			}
			case 4440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000219);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000249, EnemyEtis, "EnemyEtis-250");
				break;
			}
			case 4460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000220);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000250, EnemyEtis, "EnemyEtis-251");
				break;
			}
			case 4480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000221);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000251, EnemyEtis, "EnemyEtis-252");
				break;
			}
			case 4500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000222);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000252, EnemyEtis, "EnemyEtis-253");
				break;
			}
			case 4520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000223);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000253, EnemyEtis, "EnemyEtis-254");
				break;
			}
			case 4540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000224);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000254, EnemyEtis, "EnemyEtis-255");
				break;
			}
			case 4560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000225);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000255, EnemyEtis, "EnemyEtis-256");
				break;
			}
			case 4580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000226);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000256, EnemyEtis, "EnemyEtis-257");
				break;
			}
			case 4600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000227);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000257, EnemyEtis, "EnemyEtis-258");
				break;
			}
			case 4620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000228);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000258, EnemyEtis, "EnemyEtis-259");
				break;
			}
			case 4640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000229);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000259, EnemyEtis, "EnemyEtis-260");
				break;
			}
			case 4660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000230);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000260, EnemyEtis, "EnemyEtis-261");
				break;
			}
			case 4680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000231);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000261, EnemyEtis, "EnemyEtis-262");
				break;
			}
			case 4700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000232);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000262, EnemyEtis, "EnemyEtis-263");
				break;
			}
			case 4720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000233);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000263, EnemyEtis, "EnemyEtis-264");
				break;
			}
			case 4740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000234);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000264, EnemyEtis, "EnemyEtis-265");
				break;
			}
			case 4760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000235);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000265, EnemyEtis, "EnemyEtis-266");
				break;
			}
			case 4780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000236);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000266, EnemyEtis, "EnemyEtis-267");
				break;
			}
			case 4800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000237);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000267, EnemyEtis, "EnemyEtis-268");
				break;
			}
			case 4820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000238);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000268, EnemyEtis, "EnemyEtis-269");
				break;
			}
			case 4840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000239);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000269, EnemyEtis, "EnemyEtis-270");
				break;
			}
			case 4860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000240);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000270, EnemyEtis, "EnemyEtis-271");
				break;
			}
			case 4880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000241);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000271, EnemyEtis, "EnemyEtis-272");
				break;
			}
			case 4900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000242);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000272, EnemyEtis, "EnemyEtis-273");
				break;
			}
			case 4920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000243);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000273, EnemyEtis, "EnemyEtis-274");
				break;
			}
			case 4940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000244);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000274, EnemyEtis, "EnemyEtis-275");
				break;
			}
			case 4960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000245);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000275, EnemyEtis, "EnemyEtis-276");
				break;
			}
			case 4980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000246);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000276, EnemyEtis, "EnemyEtis-277");
				break;
			}
			case 5000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000247);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000277, EnemyEtis, "EnemyEtis-278");
				break;
			}
			case 5020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000248);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000278, EnemyEtis, "EnemyEtis-279");
				break;
			}
			case 5040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000249);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000279, EnemyEtis, "EnemyEtis-280");
				break;
			}
			case 5060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000250);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000280, EnemyEtis, "EnemyEtis-281");
				break;
			}
			case 5080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000251);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000281, EnemyEtis, "EnemyEtis-282");
				break;
			}
			case 5100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000252);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000282, EnemyEtis, "EnemyEtis-283");
				break;
			}
			case 5120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000253);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000283, EnemyEtis, "EnemyEtis-284");
				break;
			}
			case 5140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000254);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000284, EnemyEtis, "EnemyEtis-285");
				break;
			}
			case 5160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000255);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000285, EnemyEtis, "EnemyEtis-286");
				break;
			}
			case 5180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000256);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000286, EnemyEtis, "EnemyEtis-287");
				break;
			}
			case 5200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000257);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000287, EnemyEtis, "EnemyEtis-288");
				break;
			}
			case 5220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000258);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000288, EnemyEtis, "EnemyEtis-289");
				break;
			}
			case 5240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000259);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000289, EnemyEtis, "EnemyEtis-290");
				break;
			}
			case 5260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000260);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000290, EnemyEtis, "EnemyEtis-291");
				break;
			}
			case 5280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000261);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000291, EnemyEtis, "EnemyEtis-292");
				break;
			}
			case 5300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000262);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000292, EnemyEtis, "EnemyEtis-293");
				break;
			}
			case 5320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000263);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000293, EnemyEtis, "EnemyEtis-294");
				break;
			}
			case 5340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000264);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000294, EnemyEtis, "EnemyEtis-295");
				break;
			}
			case 5360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000265);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000295, EnemyEtis, "EnemyEtis-296");
				break;
			}
			case 5380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000266);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000296, EnemyEtis, "EnemyEtis-297");
				break;
			}
			case 5400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000267);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000297, EnemyEtis, "EnemyEtis-298");
				break;
			}
			case 5420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000268);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000298, EnemyEtis, "EnemyEtis-299");
				break;
			}
			case 5440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000269);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000299, EnemyEtis, "EnemyEtis-300");
				break;
			}
			case 5460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000270);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000300, EnemyEtis, "EnemyEtis-301");
				break;
			}
			case 5480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000271);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000301, EnemyEtis, "EnemyEtis-302");
				break;
			}
			case 5500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000272);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000302, EnemyEtis, "EnemyEtis-303");
				break;
			}
			case 5520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000273);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000303, EnemyEtis, "EnemyEtis-304");
				break;
			}
			case 5540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000274);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000304, EnemyEtis, "EnemyEtis-305");
				break;
			}
			case 5560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000275);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000305, EnemyEtis, "EnemyEtis-306");
				break;
			}
			case 5580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000276);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000306, EnemyEtis, "EnemyEtis-307");
				break;
			}
			case 5600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000277);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000307, EnemyEtis, "EnemyEtis-308");
				break;
			}
			case 5620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000278);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000308, EnemyEtis, "EnemyEtis-309");
				break;
			}
			case 5640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000279);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000309, EnemyEtis, "EnemyEtis-310");
				break;
			}
			case 5660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000280);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000310, EnemyEtis, "EnemyEtis-311");
				break;
			}
			case 5680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000281);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000311, EnemyEtis, "EnemyEtis-312");
				break;
			}
			case 5700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000282);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000312, EnemyEtis, "EnemyEtis-313");
				break;
			}
			case 5720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000283);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000313, EnemyEtis, "EnemyEtis-314");
				break;
			}
			case 5740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000284);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000314, EnemyEtis, "EnemyEtis-315");
				break;
			}
			case 5760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000285);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000315, EnemyEtis, "EnemyEtis-316");
				break;
			}
			case 5780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000286);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000316, EnemyEtis, "EnemyEtis-317");
				break;
			}
			case 5800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000287);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000317, EnemyEtis, "EnemyEtis-318");
				break;
			}
			case 5820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000288);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000318, EnemyEtis, "EnemyEtis-319");
				break;
			}
			case 5840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000289);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000319, EnemyEtis, "EnemyEtis-320");
				break;
			}
			case 5860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000290);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000320, EnemyEtis, "EnemyEtis-321");
				break;
			}
			case 5880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000291);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000321, EnemyEtis, "EnemyEtis-322");
				break;
			}
			case 5900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000292);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000322, EnemyEtis, "EnemyEtis-323");
				break;
			}
			case 5920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000293);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000323, EnemyEtis, "EnemyEtis-324");
				break;
			}
			case 5940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000294);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000324, EnemyEtis, "EnemyEtis-325");
				break;
			}
			case 5960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000295);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000325, EnemyEtis, "EnemyEtis-326");
				break;
			}
			case 5980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000296);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000326, EnemyEtis, "EnemyEtis-327");
				break;
			}
			case 6000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000297);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000327, EnemyEtis, "EnemyEtis-328");
				break;
			}
			case 6020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000298);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000328, EnemyEtis, "EnemyEtis-329");
				break;
			}
			case 6040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000299);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000329, EnemyEtis, "EnemyEtis-330");
				break;
			}
			case 6060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000300);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000330, EnemyEtis, "EnemyEtis-331");
				break;
			}
			case 6080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000301);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000331, EnemyEtis, "EnemyEtis-332");
				break;
			}
			case 6100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000302);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000332, EnemyEtis, "EnemyEtis-333");
				break;
			}
			case 6120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000303);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000333, EnemyEtis, "EnemyEtis-334");
				break;
			}
			case 6140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000304);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000334, EnemyEtis, "EnemyEtis-335");
				break;
			}
			case 6160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000305);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000335, EnemyEtis, "EnemyEtis-336");
				break;
			}
			case 6180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000306);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000336, EnemyEtis, "EnemyEtis-337");
				break;
			}
			case 6200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000307);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000337, EnemyEtis, "EnemyEtis-338");
				break;
			}
			case 6220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000308);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000338, EnemyEtis, "EnemyEtis-339");
				break;
			}
			case 6240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000309);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000339, EnemyEtis, "EnemyEtis-340");
				break;
			}
			case 6260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000310);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000340, EnemyEtis, "EnemyEtis-341");
				break;
			}
			case 6280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000311);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000341, EnemyEtis, "EnemyEtis-342");
				break;
			}
			case 6300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000312);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000342, EnemyEtis, "EnemyEtis-343");
				break;
			}
			case 6320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000313);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000343, EnemyEtis, "EnemyEtis-344");
				break;
			}
			case 6340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000314);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000344, EnemyEtis, "EnemyEtis-345");
				break;
			}
			case 6360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000315);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000345, EnemyEtis, "EnemyEtis-346");
				break;
			}
			case 6380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000316);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000346, EnemyEtis, "EnemyEtis-347");
				break;
			}
			case 6400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000317);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000347, EnemyEtis, "EnemyEtis-348");
				break;
			}
			case 6420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000318);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000348, EnemyEtis, "EnemyEtis-349");
				break;
			}
			case 6440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000319);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000349, EnemyEtis, "EnemyEtis-350");
				break;
			}
			case 6460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000320);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000350, EnemyEtis, "EnemyEtis-351");
				break;
			}
			case 6480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000321);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000351, EnemyEtis, "EnemyEtis-352");
				break;
			}
			case 6500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000322);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000352, EnemyEtis, "EnemyEtis-353");
				break;
			}
			case 6520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000323);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000353, EnemyEtis, "EnemyEtis-354");
				break;
			}
			case 6540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000324);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000354, EnemyEtis, "EnemyEtis-355");
				break;
			}
			case 6560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000325);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000355, EnemyEtis, "EnemyEtis-356");
				break;
			}
			case 6580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000326);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000356, EnemyEtis, "EnemyEtis-357");
				break;
			}
			case 6600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000327);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000357, EnemyEtis, "EnemyEtis-358");
				break;
			}
			case 6620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000328);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000358, EnemyEtis, "EnemyEtis-359");
				break;
			}
			case 6640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000329);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000359, EnemyEtis, "EnemyEtis-360");
				break;
			}
			case 6660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000330);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000360, EnemyEtis, "EnemyEtis-361");
				break;
			}
			case 6680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000331);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000361, EnemyEtis, "EnemyEtis-362");
				break;
			}
			case 6700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000332);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000362, EnemyEtis, "EnemyEtis-363");
				break;
			}
			case 6720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000333);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000363, EnemyEtis, "EnemyEtis-364");
				break;
			}
			case 6740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000334);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000364, EnemyEtis, "EnemyEtis-365");
				break;
			}
			case 6760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000335);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000365, EnemyEtis, "EnemyEtis-366");
				break;
			}
			case 6780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000336);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000366, EnemyEtis, "EnemyEtis-367");
				break;
			}
			case 6800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000337);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000367, EnemyEtis, "EnemyEtis-368");
				break;
			}
			case 6820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000338);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000368, EnemyEtis, "EnemyEtis-369");
				break;
			}
			case 6840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000339);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000369, EnemyEtis, "EnemyEtis-370");
				break;
			}
			case 6860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000340);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000370, EnemyEtis, "EnemyEtis-371");
				break;
			}
			case 6880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000341);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000371, EnemyEtis, "EnemyEtis-372");
				break;
			}
			case 6900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000342);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000372, EnemyEtis, "EnemyEtis-373");
				break;
			}
			case 6920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000343);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000373, EnemyEtis, "EnemyEtis-374");
				break;
			}
			case 6940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000344);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000374, EnemyEtis, "EnemyEtis-375");
				break;
			}
			case 6960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000345);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000375, EnemyEtis, "EnemyEtis-376");
				break;
			}
			case 6980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000346);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000376, EnemyEtis, "EnemyEtis-377");
				break;
			}
			case 7000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000347);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000377, EnemyEtis, "EnemyEtis-378");
				break;
			}
			case 7020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000348);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000378, EnemyEtis, "EnemyEtis-379");
				break;
			}
			case 7040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000349);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000379, EnemyEtis, "EnemyEtis-380");
				break;
			}
			case 7060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000350);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000380, EnemyEtis, "EnemyEtis-381");
				break;
			}
			case 7080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000351);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000381, EnemyEtis, "EnemyEtis-382");
				break;
			}
			case 7100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000352);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000382, EnemyEtis, "EnemyEtis-383");
				break;
			}
			case 7120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000353);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000383, EnemyEtis, "EnemyEtis-384");
				break;
			}
			case 7140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000354);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000384, EnemyEtis, "EnemyEtis-385");
				break;
			}
			case 7160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000355);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000385, EnemyEtis, "EnemyEtis-386");
				break;
			}
			case 7180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000356);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000386, EnemyEtis, "EnemyEtis-387");
				break;
			}
			case 7200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000357);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000387, EnemyEtis, "EnemyEtis-388");
				break;
			}
			case 7220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000358);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000388, EnemyEtis, "EnemyEtis-389");
				break;
			}
			case 7240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000359);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000389, EnemyEtis, "EnemyEtis-390");
				break;
			}
			case 7260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000360);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000390, EnemyEtis, "EnemyEtis-391");
				break;
			}
			case 7280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000361);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000391, EnemyEtis, "EnemyEtis-392");
				break;
			}
			case 7300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000362);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000392, EnemyEtis, "EnemyEtis-393");
				break;
			}
			case 7320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000363);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000393, EnemyEtis, "EnemyEtis-394");
				break;
			}
			case 7340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000364);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000394, EnemyEtis, "EnemyEtis-395");
				break;
			}
			case 7360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000365);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000395, EnemyEtis, "EnemyEtis-396");
				break;
			}
			case 7380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000366);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000396, EnemyEtis, "EnemyEtis-397");
				break;
			}
			case 7400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000367);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000397, EnemyEtis, "EnemyEtis-398");
				break;
			}
			case 7420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000368);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000398, EnemyEtis, "EnemyEtis-399");
				break;
			}
			case 7440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000369);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000399, EnemyEtis, "EnemyEtis-400");
				break;
			}
			case 7460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000370);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000400, EnemyEtis, "EnemyEtis-401");
				break;
			}
			case 7480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000371);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000401, EnemyEtis, "EnemyEtis-402");
				break;
			}
			case 7500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000372);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000402, EnemyEtis, "EnemyEtis-403");
				break;
			}
			case 7520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000373);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000403, EnemyEtis, "EnemyEtis-404");
				break;
			}
			case 7540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000374);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000404, EnemyEtis, "EnemyEtis-405");
				break;
			}
			case 7560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000375);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000405, EnemyEtis, "EnemyEtis-406");
				break;
			}
			case 7580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000376);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000406, EnemyEtis, "EnemyEtis-407");
				break;
			}
			case 7600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000377);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000407, EnemyEtis, "EnemyEtis-408");
				break;
			}
			case 7620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000378);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000408, EnemyEtis, "EnemyEtis-409");
				break;
			}
			case 7640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000379);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000409, EnemyEtis, "EnemyEtis-410");
				break;
			}
			case 7660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000380);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000410, EnemyEtis, "EnemyEtis-411");
				break;
			}
			case 7680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000381);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000411, EnemyEtis, "EnemyEtis-412");
				break;
			}
			case 7700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000382);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000412, EnemyEtis, "EnemyEtis-413");
				break;
			}
			case 7720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000383);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000413, EnemyEtis, "EnemyEtis-414");
				break;
			}
			case 7740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000384);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000414, EnemyEtis, "EnemyEtis-415");
				break;
			}
			case 7760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000385);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000415, EnemyEtis, "EnemyEtis-416");
				break;
			}
			case 7780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000386);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000416, EnemyEtis, "EnemyEtis-417");
				break;
			}
			case 7800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000387);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000417, EnemyEtis, "EnemyEtis-418");
				break;
			}
			case 7820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000388);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000418, EnemyEtis, "EnemyEtis-419");
				break;
			}
			case 7840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000389);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000419, EnemyEtis, "EnemyEtis-420");
				break;
			}
			case 7860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000390);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000420, EnemyEtis, "EnemyEtis-421");
				break;
			}
			case 7880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000391);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000421, EnemyEtis, "EnemyEtis-422");
				break;
			}
			case 7900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000392);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000422, EnemyEtis, "EnemyEtis-423");
				break;
			}
			case 7920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000393);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000423, EnemyEtis, "EnemyEtis-424");
				break;
			}
			case 7940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000394);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000424, EnemyEtis, "EnemyEtis-425");
				break;
			}
			case 7960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000395);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000425, EnemyEtis, "EnemyEtis-426");
				break;
			}
			case 7980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000396);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000426, EnemyEtis, "EnemyEtis-427");
				break;
			}
			case 8000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000397);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000427, EnemyEtis, "EnemyEtis-428");
				break;
			}
			case 8020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000398);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000428, EnemyEtis, "EnemyEtis-429");
				break;
			}
			case 8040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000399);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000429, EnemyEtis, "EnemyEtis-430");
				break;
			}
			case 8060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000400);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000430, EnemyEtis, "EnemyEtis-431");
				break;
			}
			case 8080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000401);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000431, EnemyEtis, "EnemyEtis-432");
				break;
			}
			case 8100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000402);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000432, EnemyEtis, "EnemyEtis-433");
				break;
			}
			case 8120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000403);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000433, EnemyEtis, "EnemyEtis-434");
				break;
			}
			case 8140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000404);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000434, EnemyEtis, "EnemyEtis-435");
				break;
			}
			case 8160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000405);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000435, EnemyEtis, "EnemyEtis-436");
				break;
			}
			case 8180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000406);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000436, EnemyEtis, "EnemyEtis-437");
				break;
			}
			case 8200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000407);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000437, EnemyEtis, "EnemyEtis-438");
				break;
			}
			case 8220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000408);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000438, EnemyEtis, "EnemyEtis-439");
				break;
			}
			case 8240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000409);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000439, EnemyEtis, "EnemyEtis-440");
				break;
			}
			case 8260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000410);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000440, EnemyEtis, "EnemyEtis-441");
				break;
			}
			case 8280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000411);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000441, EnemyEtis, "EnemyEtis-442");
				break;
			}
			case 8300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000412);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000442, EnemyEtis, "EnemyEtis-443");
				break;
			}
			case 8320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000413);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000443, EnemyEtis, "EnemyEtis-444");
				break;
			}
			case 8340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000414);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000444, EnemyEtis, "EnemyEtis-445");
				break;
			}
			case 8360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000415);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000445, EnemyEtis, "EnemyEtis-446");
				break;
			}
			case 8380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000416);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000446, EnemyEtis, "EnemyEtis-447");
				break;
			}
			case 8400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000417);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000447, EnemyEtis, "EnemyEtis-448");
				break;
			}
			case 8420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000418);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000448, EnemyEtis, "EnemyEtis-449");
				break;
			}
			case 8440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000419);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000449, EnemyEtis, "EnemyEtis-450");
				break;
			}
			case 8460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000420);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000450, EnemyEtis, "EnemyEtis-451");
				break;
			}
			case 8480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000421);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000451, EnemyEtis, "EnemyEtis-452");
				break;
			}
			case 8500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000422);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000452, EnemyEtis, "EnemyEtis-453");
				break;
			}
			case 8520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000423);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000453, EnemyEtis, "EnemyEtis-454");
				break;
			}
			case 8540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000424);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000454, EnemyEtis, "EnemyEtis-455");
				break;
			}
			case 8560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000425);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000455, EnemyEtis, "EnemyEtis-456");
				break;
			}
			case 8580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000426);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000456, EnemyEtis, "EnemyEtis-457");
				break;
			}
			case 8600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000427);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000457, EnemyEtis, "EnemyEtis-458");
				break;
			}
			case 8620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000428);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000458, EnemyEtis, "EnemyEtis-459");
				break;
			}
			case 8640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000429);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000459, EnemyEtis, "EnemyEtis-460");
				break;
			}
			case 8660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000430);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000460, EnemyEtis, "EnemyEtis-461");
				break;
			}
			case 8680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000431);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000461, EnemyEtis, "EnemyEtis-462");
				break;
			}
			case 8700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000432);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000462, EnemyEtis, "EnemyEtis-463");
				break;
			}
			case 8720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000433);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000463, EnemyEtis, "EnemyEtis-464");
				break;
			}
			case 8740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000434);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000464, EnemyEtis, "EnemyEtis-465");
				break;
			}
			case 8760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000435);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000465, EnemyEtis, "EnemyEtis-466");
				break;
			}
			case 8780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000436);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000466, EnemyEtis, "EnemyEtis-467");
				break;
			}
			case 8800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000437);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000467, EnemyEtis, "EnemyEtis-468");
				break;
			}
			case 8820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000438);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000468, EnemyEtis, "EnemyEtis-469");
				break;
			}
			case 8840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000439);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000469, EnemyEtis, "EnemyEtis-470");
				break;
			}
			case 8860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000440);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000470, EnemyEtis, "EnemyEtis-471");
				break;
			}
			case 8880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000441);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000471, EnemyEtis, "EnemyEtis-472");
				break;
			}
			case 8900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000442);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000472, EnemyEtis, "EnemyEtis-473");
				break;
			}
			case 8920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000443);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000473, EnemyEtis, "EnemyEtis-474");
				break;
			}
			case 8940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000444);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000474, EnemyEtis, "EnemyEtis-475");
				break;
			}
			case 8960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000445);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000475, EnemyEtis, "EnemyEtis-476");
				break;
			}
			case 8980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000446);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000476, EnemyEtis, "EnemyEtis-477");
				break;
			}
			case 9000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000447);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000477, EnemyEtis, "EnemyEtis-478");
				break;
			}
			case 9020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000448);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000478, EnemyEtis, "EnemyEtis-479");
				break;
			}
			case 9040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000449);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000479, EnemyEtis, "EnemyEtis-480");
				break;
			}
			case 9060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000450);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000480, EnemyEtis, "EnemyEtis-481");
				break;
			}
			case 9080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000451);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000481, EnemyEtis, "EnemyEtis-482");
				break;
			}
			case 9100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000452);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000482, EnemyEtis, "EnemyEtis-483");
				break;
			}
			case 9120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000453);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000483, EnemyEtis, "EnemyEtis-484");
				break;
			}
			case 9140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000454);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000484, EnemyEtis, "EnemyEtis-485");
				break;
			}
			case 9160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000455);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000485, EnemyEtis, "EnemyEtis-486");
				break;
			}
			case 9180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000456);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000486, EnemyEtis, "EnemyEtis-487");
				break;
			}
			case 9200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000457);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000487, EnemyEtis, "EnemyEtis-488");
				break;
			}
			case 9220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000458);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000488, EnemyEtis, "EnemyEtis-489");
				break;
			}
			case 9240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000459);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000489, EnemyEtis, "EnemyEtis-490");
				break;
			}
			case 9260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000460);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000490, EnemyEtis, "EnemyEtis-491");
				break;
			}
			case 9280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000461);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000491, EnemyEtis, "EnemyEtis-492");
				break;
			}
			case 9300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000462);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000492, EnemyEtis, "EnemyEtis-493");
				break;
			}
			case 9320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000463);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000493, EnemyEtis, "EnemyEtis-494");
				break;
			}
			case 9340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000464);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000494, EnemyEtis, "EnemyEtis-495");
				break;
			}
			case 9360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000465);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000495, EnemyEtis, "EnemyEtis-496");
				break;
			}
			case 9380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000466);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000496, EnemyEtis, "EnemyEtis-497");
				break;
			}
			case 9400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000467);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000497, EnemyEtis, "EnemyEtis-498");
				break;
			}
			case 9420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000468);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000498, EnemyEtis, "EnemyEtis-499");
				break;
			}
			case 9440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000469);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000499, EnemyEtis, "EnemyEtis-500");
				break;
			}
			case 9460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000470);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000500, EnemyEtis, "EnemyEtis-501");
				break;
			}
			case 9480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000471);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000501, EnemyEtis, "EnemyEtis-502");
				break;
			}
			case 9500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000472);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000502, EnemyEtis, "EnemyEtis-503");
				break;
			}
			case 9520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000473);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000503, EnemyEtis, "EnemyEtis-504");
				break;
			}
			case 9540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000474);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000504, EnemyEtis, "EnemyEtis-505");
				break;
			}
			case 9560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000475);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000505, EnemyEtis, "EnemyEtis-506");
				break;
			}
			case 9580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000476);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000506, EnemyEtis, "EnemyEtis-507");
				break;
			}
			case 9600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000477);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000507, EnemyEtis, "EnemyEtis-508");
				break;
			}
			case 9620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000478);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000508, EnemyEtis, "EnemyEtis-509");
				break;
			}
			case 9640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000479);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000509, EnemyEtis, "EnemyEtis-510");
				break;
			}
			case 9660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000480);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000510, EnemyEtis, "EnemyEtis-511");
				break;
			}
			case 9680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000481);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000511, EnemyEtis, "EnemyEtis-512");
				break;
			}
			case 9700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000482);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000512, EnemyEtis, "EnemyEtis-513");
				break;
			}
			case 9720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000483);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000513, EnemyEtis, "EnemyEtis-514");
				break;
			}
			case 9740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000484);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000514, EnemyEtis, "EnemyEtis-515");
				break;
			}
			case 9760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000485);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000515, EnemyEtis, "EnemyEtis-516");
				break;
			}
			case 9780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000486);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000516, EnemyEtis, "EnemyEtis-517");
				break;
			}
			case 9800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000487);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000517, EnemyEtis, "EnemyEtis-518");
				break;
			}
			case 9820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000488);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000518, EnemyEtis, "EnemyEtis-519");
				break;
			}
			case 9840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000489);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000519, EnemyEtis, "EnemyEtis-520");
				break;
			}
			case 9860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000490);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000520, EnemyEtis, "EnemyEtis-521");
				break;
			}
			case 9880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000491);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000521, EnemyEtis, "EnemyEtis-522");
				break;
			}
			case 9900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000492);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000522, EnemyEtis, "EnemyEtis-523");
				break;
			}
			case 9920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000493);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000523, EnemyEtis, "EnemyEtis-524");
				break;
			}
			case 9940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000494);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000524, EnemyEtis, "EnemyEtis-525");
				break;
			}
			case 9960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000495);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000525, EnemyEtis, "EnemyEtis-526");
				break;
			}
			case 9980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000496);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000526, EnemyEtis, "EnemyEtis-527");
				break;
			}
			case 10000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000497);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000527, EnemyEtis, "EnemyEtis-528");
				break;
			}
			case 10020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000498);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000528, EnemyEtis, "EnemyEtis-529");
				break;
			}
			case 10040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000499);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000529, EnemyEtis, "EnemyEtis-530");
				break;
			}
			case 10060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000500);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000530, EnemyEtis, "EnemyEtis-531");
				break;
			}
			case 10080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000501);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000531, EnemyEtis, "EnemyEtis-532");
				break;
			}
			case 10100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000502);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000532, EnemyEtis, "EnemyEtis-533");
				break;
			}
			case 10120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000503);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000533, EnemyEtis, "EnemyEtis-534");
				break;
			}
			case 10140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000504);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000534, EnemyEtis, "EnemyEtis-535");
				break;
			}
			case 10160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000505);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000535, EnemyEtis, "EnemyEtis-536");
				break;
			}
			case 10180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000506);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000536, EnemyEtis, "EnemyEtis-537");
				break;
			}
			case 10200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000507);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000537, EnemyEtis, "EnemyEtis-538");
				break;
			}
			case 10220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000508);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000538, EnemyEtis, "EnemyEtis-539");
				break;
			}
			case 10240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000509);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000539, EnemyEtis, "EnemyEtis-540");
				break;
			}
			case 10260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000510);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000540, EnemyEtis, "EnemyEtis-541");
				break;
			}
			case 10280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000511);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000541, EnemyEtis, "EnemyEtis-542");
				break;
			}
			case 10300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000512);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000542, EnemyEtis, "EnemyEtis-543");
				break;
			}
			case 10320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000513);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000543, EnemyEtis, "EnemyEtis-544");
				break;
			}
			case 10340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000514);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000544, EnemyEtis, "EnemyEtis-545");
				break;
			}
			case 10360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000515);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000545, EnemyEtis, "EnemyEtis-546");
				break;
			}
			case 10380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000516);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000546, EnemyEtis, "EnemyEtis-547");
				break;
			}
			case 10400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000517);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000547, EnemyEtis, "EnemyEtis-548");
				break;
			}
			case 10420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000518);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000548, EnemyEtis, "EnemyEtis-549");
				break;
			}
			case 10440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000519);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000549, EnemyEtis, "EnemyEtis-550");
				break;
			}
			case 10460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000520);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000550, EnemyEtis, "EnemyEtis-551");
				break;
			}
			case 10480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000521);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000551, EnemyEtis, "EnemyEtis-552");
				break;
			}
			case 10500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000522);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000552, EnemyEtis, "EnemyEtis-553");
				break;
			}
			case 10520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000523);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000553, EnemyEtis, "EnemyEtis-554");
				break;
			}
			case 10540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000524);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000554, EnemyEtis, "EnemyEtis-555");
				break;
			}
			case 10560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000525);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000555, EnemyEtis, "EnemyEtis-556");
				break;
			}
			case 10580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000526);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000556, EnemyEtis, "EnemyEtis-557");
				break;
			}
			case 10600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000527);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000557, EnemyEtis, "EnemyEtis-558");
				break;
			}
			case 10620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000528);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000558, EnemyEtis, "EnemyEtis-559");
				break;
			}
			case 10640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000529);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000559, EnemyEtis, "EnemyEtis-560");
				break;
			}
			case 10660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000530);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000560, EnemyEtis, "EnemyEtis-561");
				break;
			}
			case 10680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000531);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000561, EnemyEtis, "EnemyEtis-562");
				break;
			}
			case 10700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000532);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000562, EnemyEtis, "EnemyEtis-563");
				break;
			}
			case 10720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000533);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000563, EnemyEtis, "EnemyEtis-564");
				break;
			}
			case 10740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000534);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000564, EnemyEtis, "EnemyEtis-565");
				break;
			}
			case 10760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000535);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000565, EnemyEtis, "EnemyEtis-566");
				break;
			}
			case 10780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000536);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000566, EnemyEtis, "EnemyEtis-567");
				break;
			}
			case 10800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000537);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000567, EnemyEtis, "EnemyEtis-568");
				break;
			}
			case 10820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000538);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000568, EnemyEtis, "EnemyEtis-569");
				break;
			}
			case 10840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000539);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000569, EnemyEtis, "EnemyEtis-570");
				break;
			}
			case 10860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000540);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000570, EnemyEtis, "EnemyEtis-571");
				break;
			}
			case 10880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000541);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000571, EnemyEtis, "EnemyEtis-572");
				break;
			}
			case 10900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000542);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000572, EnemyEtis, "EnemyEtis-573");
				break;
			}
			case 10920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000543);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000573, EnemyEtis, "EnemyEtis-574");
				break;
			}
			case 10940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000544);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000574, EnemyEtis, "EnemyEtis-575");
				break;
			}
			case 10960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000545);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000575, EnemyEtis, "EnemyEtis-576");
				break;
			}
			case 10980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000546);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000576, EnemyEtis, "EnemyEtis-577");
				break;
			}
			case 11000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000547);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000577, EnemyEtis, "EnemyEtis-578");
				break;
			}
			case 11020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000548);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000578, EnemyEtis, "EnemyEtis-579");
				break;
			}
			case 11040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000549);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000579, EnemyEtis, "EnemyEtis-580");
				break;
			}
			case 11060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000550);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000580, EnemyEtis, "EnemyEtis-581");
				break;
			}
			case 11080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000551);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000581, EnemyEtis, "EnemyEtis-582");
				break;
			}
			case 11100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000552);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000582, EnemyEtis, "EnemyEtis-583");
				break;
			}
			case 11120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000553);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000583, EnemyEtis, "EnemyEtis-584");
				break;
			}
			case 11140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000554);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000584, EnemyEtis, "EnemyEtis-585");
				break;
			}
			case 11160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000555);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000585, EnemyEtis, "EnemyEtis-586");
				break;
			}
			case 11180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000556);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000586, EnemyEtis, "EnemyEtis-587");
				break;
			}
			case 11200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000557);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000587, EnemyEtis, "EnemyEtis-588");
				break;
			}
			case 11220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000558);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000588, EnemyEtis, "EnemyEtis-589");
				break;
			}
			case 11240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000559);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000589, EnemyEtis, "EnemyEtis-590");
				break;
			}
			case 11260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000560);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000590, EnemyEtis, "EnemyEtis-591");
				break;
			}
			case 11280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000561);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000591, EnemyEtis, "EnemyEtis-592");
				break;
			}
			case 11300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000562);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000592, EnemyEtis, "EnemyEtis-593");
				break;
			}
			case 11320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000563);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000593, EnemyEtis, "EnemyEtis-594");
				break;
			}
			case 11340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000564);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000594, EnemyEtis, "EnemyEtis-595");
				break;
			}
			case 11360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000565);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000595, EnemyEtis, "EnemyEtis-596");
				break;
			}
			case 11380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000566);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000596, EnemyEtis, "EnemyEtis-597");
				break;
			}
			case 11400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000567);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000597, EnemyEtis, "EnemyEtis-598");
				break;
			}
			case 11420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000568);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000598, EnemyEtis, "EnemyEtis-599");
				break;
			}
			case 11440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000569);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000599, EnemyEtis, "EnemyEtis-600");
				break;
			}
			case 11460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000570);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000600, EnemyEtis, "EnemyEtis-601");
				break;
			}
			case 11480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000571);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000601, EnemyEtis, "EnemyEtis-602");
				break;
			}
			case 11500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000572);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000602, EnemyEtis, "EnemyEtis-603");
				break;
			}
			case 11520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000573);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000603, EnemyEtis, "EnemyEtis-604");
				break;
			}
			case 11540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000574);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000604, EnemyEtis, "EnemyEtis-605");
				break;
			}
			case 11560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000575);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000605, EnemyEtis, "EnemyEtis-606");
				break;
			}
			case 11580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000576);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000606, EnemyEtis, "EnemyEtis-607");
				break;
			}
			case 11600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000577);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000607, EnemyEtis, "EnemyEtis-608");
				break;
			}
			case 11620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000578);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000608, EnemyEtis, "EnemyEtis-609");
				break;
			}
			case 11640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000579);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000609, EnemyEtis, "EnemyEtis-610");
				break;
			}
			case 11660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000580);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000610, EnemyEtis, "EnemyEtis-611");
				break;
			}
			case 11680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000581);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000611, EnemyEtis, "EnemyEtis-612");
				break;
			}
			case 11700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000582);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000612, EnemyEtis, "EnemyEtis-613");
				break;
			}
			case 11720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000583);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000613, EnemyEtis, "EnemyEtis-614");
				break;
			}
			case 11740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000584);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000614, EnemyEtis, "EnemyEtis-615");
				break;
			}
			case 11760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000585);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000615, EnemyEtis, "EnemyEtis-616");
				break;
			}
			case 11780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000586);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000616, EnemyEtis, "EnemyEtis-617");
				break;
			}
			case 11800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000587);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000617, EnemyEtis, "EnemyEtis-618");
				break;
			}
			case 11820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000588);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000618, EnemyEtis, "EnemyEtis-619");
				break;
			}
			case 11840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000589);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000619, EnemyEtis, "EnemyEtis-620");
				break;
			}
			case 11860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000590);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000620, EnemyEtis, "EnemyEtis-621");
				break;
			}
			case 11880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000591);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000621, EnemyEtis, "EnemyEtis-622");
				break;
			}
			case 11900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000592);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000622, EnemyEtis, "EnemyEtis-623");
				break;
			}
			case 11920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000593);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000623, EnemyEtis, "EnemyEtis-624");
				break;
			}
			case 11940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000594);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000624, EnemyEtis, "EnemyEtis-625");
				break;
			}
			case 11960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000595);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000625, EnemyEtis, "EnemyEtis-626");
				break;
			}
			case 11980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000596);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000626, EnemyEtis, "EnemyEtis-627");
				break;
			}
			case 12000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000597);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000627, EnemyEtis, "EnemyEtis-628");
				break;
			}
			case 12020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000598);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000628, EnemyEtis, "EnemyEtis-629");
				break;
			}
			case 12040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000599);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000629, EnemyEtis, "EnemyEtis-630");
				break;
			}
			case 12060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000600);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000630, EnemyEtis, "EnemyEtis-631");
				break;
			}
			case 12080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000601);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000631, EnemyEtis, "EnemyEtis-632");
				break;
			}
			case 12100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000602);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000632, EnemyEtis, "EnemyEtis-633");
				break;
			}
			case 12120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000603);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000633, EnemyEtis, "EnemyEtis-634");
				break;
			}
			case 12140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000604);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000634, EnemyEtis, "EnemyEtis-635");
				break;
			}
			case 12160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000605);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000635, EnemyEtis, "EnemyEtis-636");
				break;
			}
			case 12180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000606);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000636, EnemyEtis, "EnemyEtis-637");
				break;
			}
			case 12200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000607);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000637, EnemyEtis, "EnemyEtis-638");
				break;
			}
			case 12220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000608);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000638, EnemyEtis, "EnemyEtis-639");
				break;
			}
			case 12240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000609);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000639, EnemyEtis, "EnemyEtis-640");
				break;
			}
			case 12260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000610);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000640, EnemyEtis, "EnemyEtis-641");
				break;
			}
			case 12280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000611);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000641, EnemyEtis, "EnemyEtis-642");
				break;
			}
			case 12300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000612);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000642, EnemyEtis, "EnemyEtis-643");
				break;
			}
			case 12320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000613);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000643, EnemyEtis, "EnemyEtis-644");
				break;
			}
			case 12340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000614);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000644, EnemyEtis, "EnemyEtis-645");
				break;
			}
			case 12360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000615);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000645, EnemyEtis, "EnemyEtis-646");
				break;
			}
			case 12380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000616);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000646, EnemyEtis, "EnemyEtis-647");
				break;
			}
			case 12400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000617);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000647, EnemyEtis, "EnemyEtis-648");
				break;
			}
			case 12420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000618);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000648, EnemyEtis, "EnemyEtis-649");
				break;
			}
			case 12440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000619);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000649, EnemyEtis, "EnemyEtis-650");
				break;
			}
			case 12460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000620);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000650, EnemyEtis, "EnemyEtis-651");
				break;
			}
			case 12480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000621);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000651, EnemyEtis, "EnemyEtis-652");
				break;
			}
			case 12500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000622);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000652, EnemyEtis, "EnemyEtis-653");
				break;
			}
			case 12520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000623);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000653, EnemyEtis, "EnemyEtis-654");
				break;
			}
			case 12540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000624);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000654, EnemyEtis, "EnemyEtis-655");
				break;
			}
			case 12560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000625);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000655, EnemyEtis, "EnemyEtis-656");
				break;
			}
			case 12580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000626);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000656, EnemyEtis, "EnemyEtis-657");
				break;
			}
			case 12600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000627);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000657, EnemyEtis, "EnemyEtis-658");
				break;
			}
			case 12620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000628);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000658, EnemyEtis, "EnemyEtis-659");
				break;
			}
			case 12640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000629);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000659, EnemyEtis, "EnemyEtis-660");
				break;
			}
			case 12660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000630);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000660, EnemyEtis, "EnemyEtis-661");
				break;
			}
			case 12680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000631);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000661, EnemyEtis, "EnemyEtis-662");
				break;
			}
			case 12700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000632);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000662, EnemyEtis, "EnemyEtis-663");
				break;
			}
			case 12720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000633);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000663, EnemyEtis, "EnemyEtis-664");
				break;
			}
			case 12740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000634);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000664, EnemyEtis, "EnemyEtis-665");
				break;
			}
			case 12760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000635);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000665, EnemyEtis, "EnemyEtis-666");
				break;
			}
			case 12780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000636);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000666, EnemyEtis, "EnemyEtis-667");
				break;
			}
			case 12800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000637);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000667, EnemyEtis, "EnemyEtis-668");
				break;
			}
			case 12820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000638);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000668, EnemyEtis, "EnemyEtis-669");
				break;
			}
			case 12840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000639);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000669, EnemyEtis, "EnemyEtis-670");
				break;
			}
			case 12860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000640);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000670, EnemyEtis, "EnemyEtis-671");
				break;
			}
			case 12880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000641);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000671, EnemyEtis, "EnemyEtis-672");
				break;
			}
			case 12900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000642);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000672, EnemyEtis, "EnemyEtis-673");
				break;
			}
			case 12920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000643);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000673, EnemyEtis, "EnemyEtis-674");
				break;
			}
			case 12940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000644);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000674, EnemyEtis, "EnemyEtis-675");
				break;
			}
			case 12960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000645);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000675, EnemyEtis, "EnemyEtis-676");
				break;
			}
			case 12980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000646);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000676, EnemyEtis, "EnemyEtis-677");
				break;
			}
			case 13000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000647);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000677, EnemyEtis, "EnemyEtis-678");
				break;
			}
			case 13020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000648);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000678, EnemyEtis, "EnemyEtis-679");
				break;
			}
			case 13040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000649);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000679, EnemyEtis, "EnemyEtis-680");
				break;
			}
			case 13060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000650);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000680, EnemyEtis, "EnemyEtis-681");
				break;
			}
			case 13080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000651);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000681, EnemyEtis, "EnemyEtis-682");
				break;
			}
			case 13100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000652);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000682, EnemyEtis, "EnemyEtis-683");
				break;
			}
			case 13120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000653);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000683, EnemyEtis, "EnemyEtis-684");
				break;
			}
			case 13140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000654);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000684, EnemyEtis, "EnemyEtis-685");
				break;
			}
			case 13160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000655);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000685, EnemyEtis, "EnemyEtis-686");
				break;
			}
			case 13180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000656);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000686, EnemyEtis, "EnemyEtis-687");
				break;
			}
			case 13200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000657);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000687, EnemyEtis, "EnemyEtis-688");
				break;
			}
			case 13220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000658);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000688, EnemyEtis, "EnemyEtis-689");
				break;
			}
			case 13240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000659);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000689, EnemyEtis, "EnemyEtis-690");
				break;
			}
			case 13260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000660);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000690, EnemyEtis, "EnemyEtis-691");
				break;
			}
			case 13280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000661);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000691, EnemyEtis, "EnemyEtis-692");
				break;
			}
			case 13300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000662);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000692, EnemyEtis, "EnemyEtis-693");
				break;
			}
			case 13320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000663);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000693, EnemyEtis, "EnemyEtis-694");
				break;
			}
			case 13340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000664);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000694, EnemyEtis, "EnemyEtis-695");
				break;
			}
			case 13360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000665);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000695, EnemyEtis, "EnemyEtis-696");
				break;
			}
			case 13380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000666);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000696, EnemyEtis, "EnemyEtis-697");
				break;
			}
			case 13400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000667);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000697, EnemyEtis, "EnemyEtis-698");
				break;
			}
			case 13420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000668);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000698, EnemyEtis, "EnemyEtis-699");
				break;
			}
			case 13440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000669);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000699, EnemyEtis, "EnemyEtis-700");
				break;
			}
			case 13460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000670);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000700, EnemyEtis, "EnemyEtis-701");
				break;
			}
			case 13480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000671);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000701, EnemyEtis, "EnemyEtis-702");
				break;
			}
			case 13500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000672);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000702, EnemyEtis, "EnemyEtis-703");
				break;
			}
			case 13520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000673);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000703, EnemyEtis, "EnemyEtis-704");
				break;
			}
			case 13540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000674);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000704, EnemyEtis, "EnemyEtis-705");
				break;
			}
			case 13560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000675);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000705, EnemyEtis, "EnemyEtis-706");
				break;
			}
			case 13580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000676);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000706, EnemyEtis, "EnemyEtis-707");
				break;
			}
			case 13600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000677);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000707, EnemyEtis, "EnemyEtis-708");
				break;
			}
			case 13620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000678);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000708, EnemyEtis, "EnemyEtis-709");
				break;
			}
			case 13640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000679);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000709, EnemyEtis, "EnemyEtis-710");
				break;
			}
			case 13660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000680);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000710, EnemyEtis, "EnemyEtis-711");
				break;
			}
			case 13680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000681);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000711, EnemyEtis, "EnemyEtis-712");
				break;
			}
			case 13700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000682);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000712, EnemyEtis, "EnemyEtis-713");
				break;
			}
			case 13720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000683);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000713, EnemyEtis, "EnemyEtis-714");
				break;
			}
			case 13740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000684);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000714, EnemyEtis, "EnemyEtis-715");
				break;
			}
			case 13760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000685);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000715, EnemyEtis, "EnemyEtis-716");
				break;
			}
			case 13780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000686);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000716, EnemyEtis, "EnemyEtis-717");
				break;
			}
			case 13800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000687);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000717, EnemyEtis, "EnemyEtis-718");
				break;
			}
			case 13820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000688);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000718, EnemyEtis, "EnemyEtis-719");
				break;
			}
			case 13840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000689);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000719, EnemyEtis, "EnemyEtis-720");
				break;
			}
			case 13860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000690);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000720, EnemyEtis, "EnemyEtis-721");
				break;
			}
			case 13880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000691);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000721, EnemyEtis, "EnemyEtis-722");
				break;
			}
			case 13900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000692);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000722, EnemyEtis, "EnemyEtis-723");
				break;
			}
			case 13920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000693);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000723, EnemyEtis, "EnemyEtis-724");
				break;
			}
			case 13940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000694);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000724, EnemyEtis, "EnemyEtis-725");
				break;
			}
			case 13960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000695);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000725, EnemyEtis, "EnemyEtis-726");
				break;
			}
			case 13980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000696);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000726, EnemyEtis, "EnemyEtis-727");
				break;
			}
			case 14000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000697);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000727, EnemyEtis, "EnemyEtis-728");
				break;
			}
			case 14020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000698);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000728, EnemyEtis, "EnemyEtis-729");
				break;
			}
			case 14040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000699);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000729, EnemyEtis, "EnemyEtis-730");
				break;
			}
			case 14060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000700);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000730, EnemyEtis, "EnemyEtis-731");
				break;
			}
			case 14080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000701);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000731, EnemyEtis, "EnemyEtis-732");
				break;
			}
			case 14100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000702);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000732, EnemyEtis, "EnemyEtis-733");
				break;
			}
			case 14120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000703);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000733, EnemyEtis, "EnemyEtis-734");
				break;
			}
			case 14140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000704);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000734, EnemyEtis, "EnemyEtis-735");
				break;
			}
			case 14160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000705);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000735, EnemyEtis, "EnemyEtis-736");
				break;
			}
			case 14180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000706);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000736, EnemyEtis, "EnemyEtis-737");
				break;
			}
			case 14200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000707);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000737, EnemyEtis, "EnemyEtis-738");
				break;
			}
			case 14220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000708);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000738, EnemyEtis, "EnemyEtis-739");
				break;
			}
			case 14240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000709);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000739, EnemyEtis, "EnemyEtis-740");
				break;
			}
			case 14260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000710);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000740, EnemyEtis, "EnemyEtis-741");
				break;
			}
			case 14280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000711);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000741, EnemyEtis, "EnemyEtis-742");
				break;
			}
			case 14300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000712);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000742, EnemyEtis, "EnemyEtis-743");
				break;
			}
			case 14320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000713);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000743, EnemyEtis, "EnemyEtis-744");
				break;
			}
			case 14340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000714);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000744, EnemyEtis, "EnemyEtis-745");
				break;
			}
			case 14360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000715);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000745, EnemyEtis, "EnemyEtis-746");
				break;
			}
			case 14380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000716);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000746, EnemyEtis, "EnemyEtis-747");
				break;
			}
			case 14400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000717);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000747, EnemyEtis, "EnemyEtis-748");
				break;
			}
			case 14420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000718);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000748, EnemyEtis, "EnemyEtis-749");
				break;
			}
			case 14440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000719);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000749, EnemyEtis, "EnemyEtis-750");
				break;
			}
			case 14460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000720);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000750, EnemyEtis, "EnemyEtis-751");
				break;
			}
			case 14480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000721);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000751, EnemyEtis, "EnemyEtis-752");
				break;
			}
			case 14500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000722);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000752, EnemyEtis, "EnemyEtis-753");
				break;
			}
			case 14520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000723);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000753, EnemyEtis, "EnemyEtis-754");
				break;
			}
			case 14540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000724);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000754, EnemyEtis, "EnemyEtis-755");
				break;
			}
			case 14560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000725);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000755, EnemyEtis, "EnemyEtis-756");
				break;
			}
			case 14580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000726);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000756, EnemyEtis, "EnemyEtis-757");
				break;
			}
			case 14600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000727);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000757, EnemyEtis, "EnemyEtis-758");
				break;
			}
			case 14620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000728);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000758, EnemyEtis, "EnemyEtis-759");
				break;
			}
			case 14640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000729);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000759, EnemyEtis, "EnemyEtis-760");
				break;
			}
			case 14660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000730);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000760, EnemyEtis, "EnemyEtis-761");
				break;
			}
			case 14680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000731);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000761, EnemyEtis, "EnemyEtis-762");
				break;
			}
			case 14700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000732);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000762, EnemyEtis, "EnemyEtis-763");
				break;
			}
			case 14720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000733);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000763, EnemyEtis, "EnemyEtis-764");
				break;
			}
			case 14740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000734);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000764, EnemyEtis, "EnemyEtis-765");
				break;
			}
			case 14760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000735);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000765, EnemyEtis, "EnemyEtis-766");
				break;
			}
			case 14780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000736);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000766, EnemyEtis, "EnemyEtis-767");
				break;
			}
			case 14800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000737);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000767, EnemyEtis, "EnemyEtis-768");
				break;
			}
			case 14820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000738);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000768, EnemyEtis, "EnemyEtis-769");
				break;
			}
			case 14840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000739);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000769, EnemyEtis, "EnemyEtis-770");
				break;
			}
			case 14860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000740);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000770, EnemyEtis, "EnemyEtis-771");
				break;
			}
			case 14880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000741);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000771, EnemyEtis, "EnemyEtis-772");
				break;
			}
			case 14900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000742);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000772, EnemyEtis, "EnemyEtis-773");
				break;
			}
			case 14920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000743);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000773, EnemyEtis, "EnemyEtis-774");
				break;
			}
			case 14940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000744);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000774, EnemyEtis, "EnemyEtis-775");
				break;
			}
			case 14960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000745);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000775, EnemyEtis, "EnemyEtis-776");
				break;
			}
			case 14980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000746);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000776, EnemyEtis, "EnemyEtis-777");
				break;
			}
			case 15000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000747);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000777, EnemyEtis, "EnemyEtis-778");
				break;
			}
			case 15020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000748);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000778, EnemyEtis, "EnemyEtis-779");
				break;
			}
			case 15040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000749);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000779, EnemyEtis, "EnemyEtis-780");
				break;
			}
			case 15060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000750);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000780, EnemyEtis, "EnemyEtis-781");
				break;
			}
			case 15080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000751);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000781, EnemyEtis, "EnemyEtis-782");
				break;
			}
			case 15100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000752);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000782, EnemyEtis, "EnemyEtis-783");
				break;
			}
			case 15120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000753);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000783, EnemyEtis, "EnemyEtis-784");
				break;
			}
			case 15140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000754);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000784, EnemyEtis, "EnemyEtis-785");
				break;
			}
			case 15160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000755);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000785, EnemyEtis, "EnemyEtis-786");
				break;
			}
			case 15180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000756);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000786, EnemyEtis, "EnemyEtis-787");
				break;
			}
			case 15200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000757);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000787, EnemyEtis, "EnemyEtis-788");
				break;
			}
			case 15220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000758);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000788, EnemyEtis, "EnemyEtis-789");
				break;
			}
			case 15240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000759);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000789, EnemyEtis, "EnemyEtis-790");
				break;
			}
			case 15260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000760);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000790, EnemyEtis, "EnemyEtis-791");
				break;
			}
			case 15280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000761);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000791, EnemyEtis, "EnemyEtis-792");
				break;
			}
			case 15300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000762);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000792, EnemyEtis, "EnemyEtis-793");
				break;
			}
			case 15320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000763);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000793, EnemyEtis, "EnemyEtis-794");
				break;
			}
			case 15340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000764);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000794, EnemyEtis, "EnemyEtis-795");
				break;
			}
			case 15360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000765);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000795, EnemyEtis, "EnemyEtis-796");
				break;
			}
			case 15380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000766);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000796, EnemyEtis, "EnemyEtis-797");
				break;
			}
			case 15400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000767);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000797, EnemyEtis, "EnemyEtis-798");
				break;
			}
			case 15420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000768);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000798, EnemyEtis, "EnemyEtis-799");
				break;
			}
			case 15440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000769);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000799, EnemyEtis, "EnemyEtis-800");
				break;
			}
			case 15460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000770);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000800, EnemyEtis, "EnemyEtis-801");
				break;
			}
			case 15480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000771);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000801, EnemyEtis, "EnemyEtis-802");
				break;
			}
			case 15500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000772);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000802, EnemyEtis, "EnemyEtis-803");
				break;
			}
			case 15520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000773);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000803, EnemyEtis, "EnemyEtis-804");
				break;
			}
			case 15540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000774);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000804, EnemyEtis, "EnemyEtis-805");
				break;
			}
			case 15560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000775);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000805, EnemyEtis, "EnemyEtis-806");
				break;
			}
			case 15580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000776);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000806, EnemyEtis, "EnemyEtis-807");
				break;
			}
			case 15600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000777);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000807, EnemyEtis, "EnemyEtis-808");
				break;
			}
			case 15620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000778);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000808, EnemyEtis, "EnemyEtis-809");
				break;
			}
			case 15640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000779);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000809, EnemyEtis, "EnemyEtis-810");
				break;
			}
			case 15660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000780);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000810, EnemyEtis, "EnemyEtis-811");
				break;
			}
			case 15680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000781);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000811, EnemyEtis, "EnemyEtis-812");
				break;
			}
			case 15700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000782);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000812, EnemyEtis, "EnemyEtis-813");
				break;
			}
			case 15720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000783);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000813, EnemyEtis, "EnemyEtis-814");
				break;
			}
			case 15740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000784);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000814, EnemyEtis, "EnemyEtis-815");
				break;
			}
			case 15760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000785);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000815, EnemyEtis, "EnemyEtis-816");
				break;
			}
			case 15780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000786);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000816, EnemyEtis, "EnemyEtis-817");
				break;
			}
			case 15800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000787);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000817, EnemyEtis, "EnemyEtis-818");
				break;
			}
			case 15820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000788);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000818, EnemyEtis, "EnemyEtis-819");
				break;
			}
			case 15840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000789);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000819, EnemyEtis, "EnemyEtis-820");
				break;
			}
			case 15860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000790);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000820, EnemyEtis, "EnemyEtis-821");
				break;
			}
			case 15880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000791);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000821, EnemyEtis, "EnemyEtis-822");
				break;
			}
			case 15900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000792);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000822, EnemyEtis, "EnemyEtis-823");
				break;
			}
			case 15920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000793);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000823, EnemyEtis, "EnemyEtis-824");
				break;
			}
			case 15940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000794);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000824, EnemyEtis, "EnemyEtis-825");
				break;
			}
			case 15960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000795);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000825, EnemyEtis, "EnemyEtis-826");
				break;
			}
			case 15980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000796);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000826, EnemyEtis, "EnemyEtis-827");
				break;
			}
			case 16000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000797);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000827, EnemyEtis, "EnemyEtis-828");
				break;
			}
			case 16020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000798);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000828, EnemyEtis, "EnemyEtis-829");
				break;
			}
			case 16040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000799);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000829, EnemyEtis, "EnemyEtis-830");
				break;
			}
			case 16060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000800);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000830, EnemyEtis, "EnemyEtis-831");
				break;
			}
			case 16080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000801);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000831, EnemyEtis, "EnemyEtis-832");
				break;
			}
			case 16100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000802);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000832, EnemyEtis, "EnemyEtis-833");
				break;
			}
			case 16120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000803);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000833, EnemyEtis, "EnemyEtis-834");
				break;
			}
			case 16140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000804);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000834, EnemyEtis, "EnemyEtis-835");
				break;
			}
			case 16160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000805);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000835, EnemyEtis, "EnemyEtis-836");
				break;
			}
			case 16180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000806);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000836, EnemyEtis, "EnemyEtis-837");
				break;
			}
			case 16200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000807);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000837, EnemyEtis, "EnemyEtis-838");
				break;
			}
			case 16220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000808);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000838, EnemyEtis, "EnemyEtis-839");
				break;
			}
			case 16240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000809);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000839, EnemyEtis, "EnemyEtis-840");
				break;
			}
			case 16260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000810);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000840, EnemyEtis, "EnemyEtis-841");
				break;
			}
			case 16280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000811);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000841, EnemyEtis, "EnemyEtis-842");
				break;
			}
			case 16300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000812);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000842, EnemyEtis, "EnemyEtis-843");
				break;
			}
			case 16320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000813);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000843, EnemyEtis, "EnemyEtis-844");
				break;
			}
			case 16340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000814);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000844, EnemyEtis, "EnemyEtis-845");
				break;
			}
			case 16360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000815);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000845, EnemyEtis, "EnemyEtis-846");
				break;
			}
			case 16380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000816);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000846, EnemyEtis, "EnemyEtis-847");
				break;
			}
			case 16400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000817);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000847, EnemyEtis, "EnemyEtis-848");
				break;
			}
			case 16420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000818);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000848, EnemyEtis, "EnemyEtis-849");
				break;
			}
			case 16440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000819);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000849, EnemyEtis, "EnemyEtis-850");
				break;
			}
			case 16460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000820);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000850, EnemyEtis, "EnemyEtis-851");
				break;
			}
			case 16480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000821);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000851, EnemyEtis, "EnemyEtis-852");
				break;
			}
			case 16500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000822);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000852, EnemyEtis, "EnemyEtis-853");
				break;
			}
			case 16520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000823);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000853, EnemyEtis, "EnemyEtis-854");
				break;
			}
			case 16540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000824);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000854, EnemyEtis, "EnemyEtis-855");
				break;
			}
			case 16560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000825);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000855, EnemyEtis, "EnemyEtis-856");
				break;
			}
			case 16580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000826);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000856, EnemyEtis, "EnemyEtis-857");
				break;
			}
			case 16600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000827);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000857, EnemyEtis, "EnemyEtis-858");
				break;
			}
			case 16620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000828);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000858, EnemyEtis, "EnemyEtis-859");
				break;
			}
			case 16640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000829);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000859, EnemyEtis, "EnemyEtis-860");
				break;
			}
			case 16660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000830);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000860, EnemyEtis, "EnemyEtis-861");
				break;
			}
			case 16680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000831);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000861, EnemyEtis, "EnemyEtis-862");
				break;
			}
			case 16700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000832);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000862, EnemyEtis, "EnemyEtis-863");
				break;
			}
			case 16720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000833);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000863, EnemyEtis, "EnemyEtis-864");
				break;
			}
			case 16740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000834);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000864, EnemyEtis, "EnemyEtis-865");
				break;
			}
			case 16760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000835);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000865, EnemyEtis, "EnemyEtis-866");
				break;
			}
			case 16780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000836);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000866, EnemyEtis, "EnemyEtis-867");
				break;
			}
			case 16800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000837);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000867, EnemyEtis, "EnemyEtis-868");
				break;
			}
			case 16820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000838);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000868, EnemyEtis, "EnemyEtis-869");
				break;
			}
			case 16840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000839);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000869, EnemyEtis, "EnemyEtis-870");
				break;
			}
			case 16860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000840);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000870, EnemyEtis, "EnemyEtis-871");
				break;
			}
			case 16880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000841);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000871, EnemyEtis, "EnemyEtis-872");
				break;
			}
			case 16900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000842);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000872, EnemyEtis, "EnemyEtis-873");
				break;
			}
			case 16920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000843);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000873, EnemyEtis, "EnemyEtis-874");
				break;
			}
			case 16940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000844);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000874, EnemyEtis, "EnemyEtis-875");
				break;
			}
			case 16960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000845);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000875, EnemyEtis, "EnemyEtis-876");
				break;
			}
			case 16980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000846);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000876, EnemyEtis, "EnemyEtis-877");
				break;
			}
			case 17000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000847);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000877, EnemyEtis, "EnemyEtis-878");
				break;
			}
			case 17020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000848);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000878, EnemyEtis, "EnemyEtis-879");
				break;
			}
			case 17040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000849);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000879, EnemyEtis, "EnemyEtis-880");
				break;
			}
			case 17060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000850);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000880, EnemyEtis, "EnemyEtis-881");
				break;
			}
			case 17080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000851);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000881, EnemyEtis, "EnemyEtis-882");
				break;
			}
			case 17100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000852);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000882, EnemyEtis, "EnemyEtis-883");
				break;
			}
			case 17120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000853);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000883, EnemyEtis, "EnemyEtis-884");
				break;
			}
			case 17140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000854);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000884, EnemyEtis, "EnemyEtis-885");
				break;
			}
			case 17160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000855);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000885, EnemyEtis, "EnemyEtis-886");
				break;
			}
			case 17180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000856);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000886, EnemyEtis, "EnemyEtis-887");
				break;
			}
			case 17200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000857);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000887, EnemyEtis, "EnemyEtis-888");
				break;
			}
			case 17220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000858);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000888, EnemyEtis, "EnemyEtis-889");
				break;
			}
			case 17240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000859);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000889, EnemyEtis, "EnemyEtis-890");
				break;
			}
			case 17260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000860);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000890, EnemyEtis, "EnemyEtis-891");
				break;
			}
			case 17280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000861);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000891, EnemyEtis, "EnemyEtis-892");
				break;
			}
			case 17300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000862);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000892, EnemyEtis, "EnemyEtis-893");
				break;
			}
			case 17320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000863);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000893, EnemyEtis, "EnemyEtis-894");
				break;
			}
			case 17340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000864);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000894, EnemyEtis, "EnemyEtis-895");
				break;
			}
			case 17360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000865);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000895, EnemyEtis, "EnemyEtis-896");
				break;
			}
			case 17380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000866);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000896, EnemyEtis, "EnemyEtis-897");
				break;
			}
			case 17400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000867);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000897, EnemyEtis, "EnemyEtis-898");
				break;
			}
			case 17420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000868);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000898, EnemyEtis, "EnemyEtis-899");
				break;
			}
			case 17440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000869);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000899, EnemyEtis, "EnemyEtis-900");
				break;
			}
			case 17460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000870);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000900, EnemyEtis, "EnemyEtis-901");
				break;
			}
			case 17480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000871);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000901, EnemyEtis, "EnemyEtis-902");
				break;
			}
			case 17500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000872);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000902, EnemyEtis, "EnemyEtis-903");
				break;
			}
			case 17520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000873);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000903, EnemyEtis, "EnemyEtis-904");
				break;
			}
			case 17540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000874);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000904, EnemyEtis, "EnemyEtis-905");
				break;
			}
			case 17560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000875);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000905, EnemyEtis, "EnemyEtis-906");
				break;
			}
			case 17580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000876);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000906, EnemyEtis, "EnemyEtis-907");
				break;
			}
			case 17600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000877);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000907, EnemyEtis, "EnemyEtis-908");
				break;
			}
			case 17620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000878);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000908, EnemyEtis, "EnemyEtis-909");
				break;
			}
			case 17640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000879);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000909, EnemyEtis, "EnemyEtis-910");
				break;
			}
			case 17660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000880);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000910, EnemyEtis, "EnemyEtis-911");
				break;
			}
			case 17680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000881);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000911, EnemyEtis, "EnemyEtis-912");
				break;
			}
			case 17700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000882);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000912, EnemyEtis, "EnemyEtis-913");
				break;
			}
			case 17720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000883);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000913, EnemyEtis, "EnemyEtis-914");
				break;
			}
			case 17740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000884);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000914, EnemyEtis, "EnemyEtis-915");
				break;
			}
			case 17760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000885);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000915, EnemyEtis, "EnemyEtis-916");
				break;
			}
			case 17780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000886);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000916, EnemyEtis, "EnemyEtis-917");
				break;
			}
			case 17800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000887);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000917, EnemyEtis, "EnemyEtis-918");
				break;
			}
			case 17820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000888);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000918, EnemyEtis, "EnemyEtis-919");
				break;
			}
			case 17840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000889);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000919, EnemyEtis, "EnemyEtis-920");
				break;
			}
			case 17860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000890);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000920, EnemyEtis, "EnemyEtis-921");
				break;
			}
			case 17880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000891);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000921, EnemyEtis, "EnemyEtis-922");
				break;
			}
			case 17900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000892);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000922, EnemyEtis, "EnemyEtis-923");
				break;
			}
			case 17920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000893);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000923, EnemyEtis, "EnemyEtis-924");
				break;
			}
			case 17940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000894);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000924, EnemyEtis, "EnemyEtis-925");
				break;
			}
			case 17960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000895);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000925, EnemyEtis, "EnemyEtis-926");
				break;
			}
			case 17980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000896);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000926, EnemyEtis, "EnemyEtis-927");
				break;
			}
			case 18000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000897);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000927, EnemyEtis, "EnemyEtis-928");
				break;
			}
			case 18020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000898);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000928, EnemyEtis, "EnemyEtis-929");
				break;
			}
			case 18040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000899);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000929, EnemyEtis, "EnemyEtis-930");
				break;
			}
			case 18060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000900);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000930, EnemyEtis, "EnemyEtis-931");
				break;
			}
			case 18080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000901);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000931, EnemyEtis, "EnemyEtis-932");
				break;
			}
			case 18100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000902);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000932, EnemyEtis, "EnemyEtis-933");
				break;
			}
			case 18120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000903);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000933, EnemyEtis, "EnemyEtis-934");
				break;
			}
			case 18140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000904);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000934, EnemyEtis, "EnemyEtis-935");
				break;
			}
			case 18160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000905);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000935, EnemyEtis, "EnemyEtis-936");
				break;
			}
			case 18180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000906);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000936, EnemyEtis, "EnemyEtis-937");
				break;
			}
			case 18200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000907);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000937, EnemyEtis, "EnemyEtis-938");
				break;
			}
			case 18220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000908);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000938, EnemyEtis, "EnemyEtis-939");
				break;
			}
			case 18240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000909);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000939, EnemyEtis, "EnemyEtis-940");
				break;
			}
			case 18260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000910);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000940, EnemyEtis, "EnemyEtis-941");
				break;
			}
			case 18280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000911);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000941, EnemyEtis, "EnemyEtis-942");
				break;
			}
			case 18300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000912);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000942, EnemyEtis, "EnemyEtis-943");
				break;
			}
			case 18320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000913);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000943, EnemyEtis, "EnemyEtis-944");
				break;
			}
			case 18340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000914);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000944, EnemyEtis, "EnemyEtis-945");
				break;
			}
			case 18360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000915);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000945, EnemyEtis, "EnemyEtis-946");
				break;
			}
			case 18380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000916);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000946, EnemyEtis, "EnemyEtis-947");
				break;
			}
			case 18400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000917);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000947, EnemyEtis, "EnemyEtis-948");
				break;
			}
			case 18420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000918);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000948, EnemyEtis, "EnemyEtis-949");
				break;
			}
			case 18440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000919);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000949, EnemyEtis, "EnemyEtis-950");
				break;
			}
			case 18460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000920);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000950, EnemyEtis, "EnemyEtis-951");
				break;
			}
			case 18480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000921);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000951, EnemyEtis, "EnemyEtis-952");
				break;
			}
			case 18500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000922);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000952, EnemyEtis, "EnemyEtis-953");
				break;
			}
			case 18520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000923);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000953, EnemyEtis, "EnemyEtis-954");
				break;
			}
			case 18540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000924);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000954, EnemyEtis, "EnemyEtis-955");
				break;
			}
			case 18560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000925);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000955, EnemyEtis, "EnemyEtis-956");
				break;
			}
			case 18580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000926);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000956, EnemyEtis, "EnemyEtis-957");
				break;
			}
			case 18600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000927);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000957, EnemyEtis, "EnemyEtis-958");
				break;
			}
			case 18620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000928);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000958, EnemyEtis, "EnemyEtis-959");
				break;
			}
			case 18640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000929);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000959, EnemyEtis, "EnemyEtis-960");
				break;
			}
			case 18660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000930);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000960, EnemyEtis, "EnemyEtis-961");
				break;
			}
			case 18680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000931);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000961, EnemyEtis, "EnemyEtis-962");
				break;
			}
			case 18700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000932);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000962, EnemyEtis, "EnemyEtis-963");
				break;
			}
			case 18720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000933);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000963, EnemyEtis, "EnemyEtis-964");
				break;
			}
			case 18740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000934);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000964, EnemyEtis, "EnemyEtis-965");
				break;
			}
			case 18760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000935);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000965, EnemyEtis, "EnemyEtis-966");
				break;
			}
			case 18780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000936);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000966, EnemyEtis, "EnemyEtis-967");
				break;
			}
			case 18800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000937);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000967, EnemyEtis, "EnemyEtis-968");
				break;
			}
			case 18820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000938);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000968, EnemyEtis, "EnemyEtis-969");
				break;
			}
			case 18840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000939);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000969, EnemyEtis, "EnemyEtis-970");
				break;
			}
			case 18860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000940);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000970, EnemyEtis, "EnemyEtis-971");
				break;
			}
			case 18880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000941);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000971, EnemyEtis, "EnemyEtis-972");
				break;
			}
			case 18900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000942);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000972, EnemyEtis, "EnemyEtis-973");
				break;
			}
			case 18920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000943);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000973, EnemyEtis, "EnemyEtis-974");
				break;
			}
			case 18940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000944);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000974, EnemyEtis, "EnemyEtis-975");
				break;
			}
			case 18960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000945);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000975, EnemyEtis, "EnemyEtis-976");
				break;
			}
			case 18980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000946);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000976, EnemyEtis, "EnemyEtis-977");
				break;
			}
			case 19000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000947);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000977, EnemyEtis, "EnemyEtis-978");
				break;
			}
			case 19020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000948);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000978, EnemyEtis, "EnemyEtis-979");
				break;
			}
			case 19040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000949);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000979, EnemyEtis, "EnemyEtis-980");
				break;
			}
			case 19060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000950);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000980, EnemyEtis, "EnemyEtis-981");
				break;
			}
			case 19080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000951);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000981, EnemyEtis, "EnemyEtis-982");
				break;
			}
			case 19100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000952);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000982, EnemyEtis, "EnemyEtis-983");
				break;
			}
			case 19120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000953);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000983, EnemyEtis, "EnemyEtis-984");
				break;
			}
			case 19140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000954);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000984, EnemyEtis, "EnemyEtis-985");
				break;
			}
			case 19160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000955);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000985, EnemyEtis, "EnemyEtis-986");
				break;
			}
			case 19180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000956);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000986, EnemyEtis, "EnemyEtis-987");
				break;
			}
			case 19200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000957);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000987, EnemyEtis, "EnemyEtis-988");
				break;
			}
			case 19220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000958);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000988, EnemyEtis, "EnemyEtis-989");
				break;
			}
			case 19240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000959);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000989, EnemyEtis, "EnemyEtis-990");
				break;
			}
			case 19260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000960);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000990, EnemyEtis, "EnemyEtis-991");
				break;
			}
			case 19280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000961);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000991, EnemyEtis, "EnemyEtis-992");
				break;
			}
			case 19300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000962);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000992, EnemyEtis, "EnemyEtis-993");
				break;
			}
			case 19320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000963);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000993, EnemyEtis, "EnemyEtis-994");
				break;
			}
			case 19340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000964);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000994, EnemyEtis, "EnemyEtis-995");
				break;
			}
			case 19360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000965);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000995, EnemyEtis, "EnemyEtis-996");
				break;
			}
			case 19380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000966);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000996, EnemyEtis, "EnemyEtis-997");
				break;
			}
			case 19400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000967);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000997, EnemyEtis, "EnemyEtis-998");
				break;
			}
			case 19420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000968);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000998, EnemyEtis, "EnemyEtis-999");
				break;
			}
			case 19440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000969);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000999, EnemyEtis, "EnemyEtis-1000");
				break;
			}
			case 19460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000970);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001000, EnemyEtis, "EnemyEtis-1001");
				break;
			}
			case 19480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000971);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001001, EnemyEtis, "EnemyEtis-1002");
				break;
			}
			case 19500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000972);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001002, EnemyEtis, "EnemyEtis-1003");
				break;
			}
			case 19520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000973);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001003, EnemyEtis, "EnemyEtis-1004");
				break;
			}
			case 19540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000974);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001004, EnemyEtis, "EnemyEtis-1005");
				break;
			}
			case 19560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000975);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001005, EnemyEtis, "EnemyEtis-1006");
				break;
			}
			case 19580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000976);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001006, EnemyEtis, "EnemyEtis-1007");
				break;
			}
			case 19600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000977);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001007, EnemyEtis, "EnemyEtis-1008");
				break;
			}
			case 19620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000978);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001008, EnemyEtis, "EnemyEtis-1009");
				break;
			}
			case 19640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000979);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001009, EnemyEtis, "EnemyEtis-1010");
				break;
			}
			case 19660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000980);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001010, EnemyEtis, "EnemyEtis-1011");
				break;
			}
			case 19680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000981);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001011, EnemyEtis, "EnemyEtis-1012");
				break;
			}
			case 19700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000982);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001012, EnemyEtis, "EnemyEtis-1013");
				break;
			}
			case 19720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000983);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001013, EnemyEtis, "EnemyEtis-1014");
				break;
			}
			case 19740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000984);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001014, EnemyEtis, "EnemyEtis-1015");
				break;
			}
			case 19760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000985);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001015, EnemyEtis, "EnemyEtis-1016");
				break;
			}
			case 19780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000986);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001016, EnemyEtis, "EnemyEtis-1017");
				break;
			}
			case 19800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000987);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001017, EnemyEtis, "EnemyEtis-1018");
				break;
			}
			case 19820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000988);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001018, EnemyEtis, "EnemyEtis-1019");
				break;
			}
			case 19840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000989);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001019, EnemyEtis, "EnemyEtis-1020");
				break;
			}
			case 19860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000990);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001020, EnemyEtis, "EnemyEtis-1021");
				break;
			}
			case 19880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000991);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001021, EnemyEtis, "EnemyEtis-1022");
				break;
			}
			case 19900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000992);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001022, EnemyEtis, "EnemyEtis-1023");
				break;
			}
			case 19920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000993);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001023, EnemyEtis, "EnemyEtis-1024");
				break;
			}
			case 19940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000994);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001024, EnemyEtis, "EnemyEtis-1025");
				break;
			}
			case 19960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000995);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001025, EnemyEtis, "EnemyEtis-1026");
				break;
			}
			case 19980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000996);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001026, EnemyEtis, "EnemyEtis-1027");
				break;
			}
			case 20000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000997);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001027, EnemyEtis, "EnemyEtis-1028");
				break;
			}
			case 20020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000998);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001028, EnemyEtis, "EnemyEtis-1029");
				break;
			}
			case 20040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000999);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001029, EnemyEtis, "EnemyEtis-1030");
				break;
			}
			case 20060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001000);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001030, EnemyEtis, "EnemyEtis-1031");
				break;
			}
			case 20080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001001);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001031, EnemyEtis, "EnemyEtis-1032");
				break;
			}
			case 20100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001002);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001032, EnemyEtis, "EnemyEtis-1033");
				break;
			}
			case 20120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001003);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001033, EnemyEtis, "EnemyEtis-1034");
				break;
			}
			case 20140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001004);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001034, EnemyEtis, "EnemyEtis-1035");
				break;
			}
			case 20160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001005);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001035, EnemyEtis, "EnemyEtis-1036");
				break;
			}
			case 20180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001006);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001036, EnemyEtis, "EnemyEtis-1037");
				break;
			}
			case 20200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001007);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001037, EnemyEtis, "EnemyEtis-1038");
				break;
			}
			case 20220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001008);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001038, EnemyEtis, "EnemyEtis-1039");
				break;
			}
			case 20240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001009);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001039, EnemyEtis, "EnemyEtis-1040");
				break;
			}
			case 20260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001010);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001040, EnemyEtis, "EnemyEtis-1041");
				break;
			}
			case 20280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001011);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001041, EnemyEtis, "EnemyEtis-1042");
				break;
			}
			case 20300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001012);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001042, EnemyEtis, "EnemyEtis-1043");
				break;
			}
			case 20320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001013);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001043, EnemyEtis, "EnemyEtis-1044");
				break;
			}
			case 20340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001014);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001044, EnemyEtis, "EnemyEtis-1045");
				break;
			}
			case 20360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001015);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001045, EnemyEtis, "EnemyEtis-1046");
				break;
			}
			case 20380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001016);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001046, EnemyEtis, "EnemyEtis-1047");
				break;
			}
			case 20400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001017);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001047, EnemyEtis, "EnemyEtis-1048");
				break;
			}
			case 20420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001018);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001048, EnemyEtis, "EnemyEtis-1049");
				break;
			}
			case 20440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001019);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001049, EnemyEtis, "EnemyEtis-1050");
				break;
			}
			case 20460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001020);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001050, EnemyEtis, "EnemyEtis-1051");
				break;
			}
			case 20480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001021);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001051, EnemyEtis, "EnemyEtis-1052");
				break;
			}
			case 20500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001022);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001052, EnemyEtis, "EnemyEtis-1053");
				break;
			}
			case 20520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001023);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001053, EnemyEtis, "EnemyEtis-1054");
				break;
			}
			case 20540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001024);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001054, EnemyEtis, "EnemyEtis-1055");
				break;
			}
			case 20560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001025);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001055, EnemyEtis, "EnemyEtis-1056");
				break;
			}
			case 20580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001026);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001056, EnemyEtis, "EnemyEtis-1057");
				break;
			}
			case 20600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001027);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001057, EnemyEtis, "EnemyEtis-1058");
				break;
			}
			case 20620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001028);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001058, EnemyEtis, "EnemyEtis-1059");
				break;
			}
			case 20640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001029);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001059, EnemyEtis, "EnemyEtis-1060");
				break;
			}
			case 20660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001030);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001060, EnemyEtis, "EnemyEtis-1061");
				break;
			}
			case 20680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001031);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001061, EnemyEtis, "EnemyEtis-1062");
				break;
			}
			case 20700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001032);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001062, EnemyEtis, "EnemyEtis-1063");
				break;
			}
			case 20720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001033);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001063, EnemyEtis, "EnemyEtis-1064");
				break;
			}
			case 20740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001034);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001064, EnemyEtis, "EnemyEtis-1065");
				break;
			}
			case 20760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001035);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001065, EnemyEtis, "EnemyEtis-1066");
				break;
			}
			case 20780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001036);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001066, EnemyEtis, "EnemyEtis-1067");
				break;
			}
			case 20800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001037);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001067, EnemyEtis, "EnemyEtis-1068");
				break;
			}
			case 20820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001038);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001068, EnemyEtis, "EnemyEtis-1069");
				break;
			}
			case 20840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001039);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001069, EnemyEtis, "EnemyEtis-1070");
				break;
			}
			case 20860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001040);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001070, EnemyEtis, "EnemyEtis-1071");
				break;
			}
			case 20880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001041);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001071, EnemyEtis, "EnemyEtis-1072");
				break;
			}
			case 20900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001042);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001072, EnemyEtis, "EnemyEtis-1073");
				break;
			}
			case 20920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001043);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001073, EnemyEtis, "EnemyEtis-1074");
				break;
			}
			case 20940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001044);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001074, EnemyEtis, "EnemyEtis-1075");
				break;
			}
			case 20960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001045);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001075, EnemyEtis, "EnemyEtis-1076");
				break;
			}
			case 20980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001046);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001076, EnemyEtis, "EnemyEtis-1077");
				break;
			}
			case 21000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001047);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001077, EnemyEtis, "EnemyEtis-1078");
				break;
			}
			case 21020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001048);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001078, EnemyEtis, "EnemyEtis-1079");
				break;
			}
			case 21040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001049);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001079, EnemyEtis, "EnemyEtis-1080");
				break;
			}
			case 21060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001050);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001080, EnemyEtis, "EnemyEtis-1081");
				break;
			}
			case 21080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001051);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001081, EnemyEtis, "EnemyEtis-1082");
				break;
			}
			case 21100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001052);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001082, EnemyEtis, "EnemyEtis-1083");
				break;
			}
			case 21120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001053);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001083, EnemyEtis, "EnemyEtis-1084");
				break;
			}
			case 21140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001054);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001084, EnemyEtis, "EnemyEtis-1085");
				break;
			}
			case 21160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001055);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001085, EnemyEtis, "EnemyEtis-1086");
				break;
			}
			case 21180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001056);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001086, EnemyEtis, "EnemyEtis-1087");
				break;
			}
			case 21200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001057);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001087, EnemyEtis, "EnemyEtis-1088");
				break;
			}
			case 21220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001058);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001088, EnemyEtis, "EnemyEtis-1089");
				break;
			}
			case 21240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001059);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001089, EnemyEtis, "EnemyEtis-1090");
				break;
			}
			case 21260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001060);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001090, EnemyEtis, "EnemyEtis-1091");
				break;
			}
			case 21280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001061);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001091, EnemyEtis, "EnemyEtis-1092");
				break;
			}
			case 21300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001062);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001092, EnemyEtis, "EnemyEtis-1093");
				break;
			}
			case 21320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001063);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001093, EnemyEtis, "EnemyEtis-1094");
				break;
			}
			case 21340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001064);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001094, EnemyEtis, "EnemyEtis-1095");
				break;
			}
			case 21360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001065);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001095, EnemyEtis, "EnemyEtis-1096");
				break;
			}
			case 21380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001066);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001096, EnemyEtis, "EnemyEtis-1097");
				break;
			}
			case 21400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001067);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001097, EnemyEtis, "EnemyEtis-1098");
				break;
			}
			case 21420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001068);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001098, EnemyEtis, "EnemyEtis-1099");
				break;
			}
			case 21440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001069);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001099, EnemyEtis, "EnemyEtis-1100");
				break;
			}
			case 21460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001070);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001100, EnemyEtis, "EnemyEtis-1101");
				break;
			}
			case 21480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001071);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001101, EnemyEtis, "EnemyEtis-1102");
				break;
			}
			case 21500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001072);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001102, EnemyEtis, "EnemyEtis-1103");
				break;
			}
			case 21520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001073);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001103, EnemyEtis, "EnemyEtis-1104");
				break;
			}
			case 21540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001074);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001104, EnemyEtis, "EnemyEtis-1105");
				break;
			}
			case 21560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001075);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001105, EnemyEtis, "EnemyEtis-1106");
				break;
			}
			case 21580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001076);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001106, EnemyEtis, "EnemyEtis-1107");
				break;
			}
			case 21600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001077);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001107, EnemyEtis, "EnemyEtis-1108");
				break;
			}
			case 21620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001078);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001108, EnemyEtis, "EnemyEtis-1109");
				break;
			}
			case 21640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001079);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001109, EnemyEtis, "EnemyEtis-1110");
				break;
			}
			case 21660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001080);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001110, EnemyEtis, "EnemyEtis-1111");
				break;
			}
			case 21680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001081);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001111, EnemyEtis, "EnemyEtis-1112");
				break;
			}
			case 21700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001082);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001112, EnemyEtis, "EnemyEtis-1113");
				break;
			}
			case 21720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001083);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001113, EnemyEtis, "EnemyEtis-1114");
				break;
			}
			case 21740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001084);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001114, EnemyEtis, "EnemyEtis-1115");
				break;
			}
			case 21760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001085);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001115, EnemyEtis, "EnemyEtis-1116");
				break;
			}
			case 21780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001086);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001116, EnemyEtis, "EnemyEtis-1117");
				break;
			}
			case 21800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001087);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001117, EnemyEtis, "EnemyEtis-1118");
				break;
			}
			case 21820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001088);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001118, EnemyEtis, "EnemyEtis-1119");
				break;
			}
			case 21840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001089);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001119, EnemyEtis, "EnemyEtis-1120");
				break;
			}
			case 21860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001090);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001120, EnemyEtis, "EnemyEtis-1121");
				break;
			}
			case 21880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001091);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001121, EnemyEtis, "EnemyEtis-1122");
				break;
			}
			case 21900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001092);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001122, EnemyEtis, "EnemyEtis-1123");
				break;
			}
			case 21920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001093);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001123, EnemyEtis, "EnemyEtis-1124");
				break;
			}
			case 21940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001094);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001124, EnemyEtis, "EnemyEtis-1125");
				break;
			}
			case 21960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001095);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001125, EnemyEtis, "EnemyEtis-1126");
				break;
			}
			case 21980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001096);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001126, EnemyEtis, "EnemyEtis-1127");
				break;
			}
			case 22000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001097);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001127, EnemyEtis, "EnemyEtis-1128");
				break;
			}
			case 22020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001098);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001128, EnemyEtis, "EnemyEtis-1129");
				break;
			}
			case 22040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001099);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001129, EnemyEtis, "EnemyEtis-1130");
				break;
			}
			case 22060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001100);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001130, EnemyEtis, "EnemyEtis-1131");
				break;
			}
			case 22080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001101);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001131, EnemyEtis, "EnemyEtis-1132");
				break;
			}
			case 22100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001102);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001132, EnemyEtis, "EnemyEtis-1133");
				break;
			}
			case 22120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001103);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001133, EnemyEtis, "EnemyEtis-1134");
				break;
			}
			case 22140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001104);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001134, EnemyEtis, "EnemyEtis-1135");
				break;
			}
			case 22160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001105);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001135, EnemyEtis, "EnemyEtis-1136");
				break;
			}
			case 22180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001106);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001136, EnemyEtis, "EnemyEtis-1137");
				break;
			}
			case 22200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001107);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001137, EnemyEtis, "EnemyEtis-1138");
				break;
			}
			case 22220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001108);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001138, EnemyEtis, "EnemyEtis-1139");
				break;
			}
			case 22240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001109);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001139, EnemyEtis, "EnemyEtis-1140");
				break;
			}
			case 22260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001110);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001140, EnemyEtis, "EnemyEtis-1141");
				break;
			}
			case 22280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001111);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001141, EnemyEtis, "EnemyEtis-1142");
				break;
			}
			case 22300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001112);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001142, EnemyEtis, "EnemyEtis-1143");
				break;
			}
			case 22320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001113);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001143, EnemyEtis, "EnemyEtis-1144");
				break;
			}
			case 22340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001114);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001144, EnemyEtis, "EnemyEtis-1145");
				break;
			}
			case 22360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001115);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001145, EnemyEtis, "EnemyEtis-1146");
				break;
			}
			case 22380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001116);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001146, EnemyEtis, "EnemyEtis-1147");
				break;
			}
			case 22400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001117);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001147, EnemyEtis, "EnemyEtis-1148");
				break;
			}
			case 22420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001118);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001148, EnemyEtis, "EnemyEtis-1149");
				break;
			}
			case 22440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001119);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001149, EnemyEtis, "EnemyEtis-1150");
				break;
			}
			case 22460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001120);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001150, EnemyEtis, "EnemyEtis-1151");
				break;
			}
			case 22480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001121);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001151, EnemyEtis, "EnemyEtis-1152");
				break;
			}
			case 22500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001122);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001152, EnemyEtis, "EnemyEtis-1153");
				break;
			}
			case 22520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001123);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001153, EnemyEtis, "EnemyEtis-1154");
				break;
			}
			case 22540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001124);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001154, EnemyEtis, "EnemyEtis-1155");
				break;
			}
			case 22560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001125);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001155, EnemyEtis, "EnemyEtis-1156");
				break;
			}
			case 22580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001126);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001156, EnemyEtis, "EnemyEtis-1157");
				break;
			}
			case 22600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001127);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001157, EnemyEtis, "EnemyEtis-1158");
				break;
			}
			case 22620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001128);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001158, EnemyEtis, "EnemyEtis-1159");
				break;
			}
			case 22640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001129);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001159, EnemyEtis, "EnemyEtis-1160");
				break;
			}
			case 22660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001130);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001160, EnemyEtis, "EnemyEtis-1161");
				break;
			}
			case 22680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001131);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001161, EnemyEtis, "EnemyEtis-1162");
				break;
			}
			case 22700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001132);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001162, EnemyEtis, "EnemyEtis-1163");
				break;
			}
			case 22720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001133);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001163, EnemyEtis, "EnemyEtis-1164");
				break;
			}
			case 22740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001134);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001164, EnemyEtis, "EnemyEtis-1165");
				break;
			}
			case 22760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001135);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001165, EnemyEtis, "EnemyEtis-1166");
				break;
			}
			case 22780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001136);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001166, EnemyEtis, "EnemyEtis-1167");
				break;
			}
			case 22800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001137);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001167, EnemyEtis, "EnemyEtis-1168");
				break;
			}
			case 22820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001138);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001168, EnemyEtis, "EnemyEtis-1169");
				break;
			}
			case 22840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001139);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001169, EnemyEtis, "EnemyEtis-1170");
				break;
			}
			case 22860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001140);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001170, EnemyEtis, "EnemyEtis-1171");
				break;
			}
			case 22880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001141);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001171, EnemyEtis, "EnemyEtis-1172");
				break;
			}
			case 22900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001142);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001172, EnemyEtis, "EnemyEtis-1173");
				break;
			}
			case 22920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001143);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001173, EnemyEtis, "EnemyEtis-1174");
				break;
			}
			case 22940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001144);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001174, EnemyEtis, "EnemyEtis-1175");
				break;
			}
			case 22960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001145);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001175, EnemyEtis, "EnemyEtis-1176");
				break;
			}
			case 22980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001146);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001176, EnemyEtis, "EnemyEtis-1177");
				break;
			}
			case 23000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001147);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001177, EnemyEtis, "EnemyEtis-1178");
				break;
			}
			case 23020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001148);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001178, EnemyEtis, "EnemyEtis-1179");
				break;
			}
			case 23040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001149);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001179, EnemyEtis, "EnemyEtis-1180");
				break;
			}
			case 23060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001150);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001180, EnemyEtis, "EnemyEtis-1181");
				break;
			}
			case 23080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001151);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001181, EnemyEtis, "EnemyEtis-1182");
				break;
			}
			case 23100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001152);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001182, EnemyEtis, "EnemyEtis-1183");
				break;
			}
			case 23120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001153);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001183, EnemyEtis, "EnemyEtis-1184");
				break;
			}
			case 23140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001154);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001184, EnemyEtis, "EnemyEtis-1185");
				break;
			}
			case 23160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001155);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001185, EnemyEtis, "EnemyEtis-1186");
				break;
			}
			case 23180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001156);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001186, EnemyEtis, "EnemyEtis-1187");
				break;
			}
			case 23200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001157);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001187, EnemyEtis, "EnemyEtis-1188");
				break;
			}
			case 23220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001158);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001188, EnemyEtis, "EnemyEtis-1189");
				break;
			}
			case 23240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001159);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001189, EnemyEtis, "EnemyEtis-1190");
				break;
			}
			case 23260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001160);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001190, EnemyEtis, "EnemyEtis-1191");
				break;
			}
			case 23280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001161);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001191, EnemyEtis, "EnemyEtis-1192");
				break;
			}
			case 23300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001162);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001192, EnemyEtis, "EnemyEtis-1193");
				break;
			}
			case 23320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001163);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001193, EnemyEtis, "EnemyEtis-1194");
				break;
			}
			case 23340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001164);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001194, EnemyEtis, "EnemyEtis-1195");
				break;
			}
			case 23360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001165);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001195, EnemyEtis, "EnemyEtis-1196");
				break;
			}
			case 23380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001166);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001196, EnemyEtis, "EnemyEtis-1197");
				break;
			}
			case 23400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001167);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001197, EnemyEtis, "EnemyEtis-1198");
				break;
			}
			case 23420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001168);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001198, EnemyEtis, "EnemyEtis-1199");
				break;
			}
			case 23440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001169);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001199, EnemyEtis, "EnemyEtis-1200");
				break;
			}
			case 23460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001170);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001200, EnemyEtis, "EnemyEtis-1201");
				break;
			}
			case 23480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001171);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001201, EnemyEtis, "EnemyEtis-1202");
				break;
			}
			case 23500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001172);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001202, EnemyEtis, "EnemyEtis-1203");
				break;
			}
			case 23520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001173);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001203, EnemyEtis, "EnemyEtis-1204");
				break;
			}
			case 23540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001174);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001204, EnemyEtis, "EnemyEtis-1205");
				break;
			}
			case 23560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001175);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001205, EnemyEtis, "EnemyEtis-1206");
				break;
			}
			case 23580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001176);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001206, EnemyEtis, "EnemyEtis-1207");
				break;
			}
			case 23600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001177);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001207, EnemyEtis, "EnemyEtis-1208");
				break;
			}
			case 23620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001178);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001208, EnemyEtis, "EnemyEtis-1209");
				break;
			}
			case 23640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001179);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001209, EnemyEtis, "EnemyEtis-1210");
				break;
			}
			case 23660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001180);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001210, EnemyEtis, "EnemyEtis-1211");
				break;
			}
			case 23680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001181);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001211, EnemyEtis, "EnemyEtis-1212");
				break;
			}
			case 23700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001182);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001212, EnemyEtis, "EnemyEtis-1213");
				break;
			}
			case 23720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001183);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001213, EnemyEtis, "EnemyEtis-1214");
				break;
			}
			case 23740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001184);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001214, EnemyEtis, "EnemyEtis-1215");
				break;
			}
			case 23760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001185);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001215, EnemyEtis, "EnemyEtis-1216");
				break;
			}
			case 23780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001186);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001216, EnemyEtis, "EnemyEtis-1217");
				break;
			}
			case 23800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001187);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001217, EnemyEtis, "EnemyEtis-1218");
				break;
			}
			case 23820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001188);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001218, EnemyEtis, "EnemyEtis-1219");
				break;
			}
			case 23840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001189);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001219, EnemyEtis, "EnemyEtis-1220");
				break;
			}
			case 23860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001190);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001220, EnemyEtis, "EnemyEtis-1221");
				break;
			}
			case 23880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001191);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001221, EnemyEtis, "EnemyEtis-1222");
				break;
			}
			case 23900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001192);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001222, EnemyEtis, "EnemyEtis-1223");
				break;
			}
			case 23920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001193);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001223, EnemyEtis, "EnemyEtis-1224");
				break;
			}
			case 23940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001194);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001224, EnemyEtis, "EnemyEtis-1225");
				break;
			}
			case 23960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001195);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001225, EnemyEtis, "EnemyEtis-1226");
				break;
			}
			case 23980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001196);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001226, EnemyEtis, "EnemyEtis-1227");
				break;
			}
			case 24000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001197);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001227, EnemyEtis, "EnemyEtis-1228");
				break;
			}
			case 24020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001198);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001228, EnemyEtis, "EnemyEtis-1229");
				break;
			}
			case 24040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001199);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001229, EnemyEtis, "EnemyEtis-1230");
				break;
			}
			case 24060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001200);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001230, EnemyEtis, "EnemyEtis-1231");
				break;
			}
			case 24080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001201);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001231, EnemyEtis, "EnemyEtis-1232");
				break;
			}
			case 24100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001202);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001232, EnemyEtis, "EnemyEtis-1233");
				break;
			}
			case 24120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001203);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001233, EnemyEtis, "EnemyEtis-1234");
				break;
			}
			case 24140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001204);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001234, EnemyEtis, "EnemyEtis-1235");
				break;
			}
			case 24160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001205);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001235, EnemyEtis, "EnemyEtis-1236");
				break;
			}
			case 24180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001206);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001236, EnemyEtis, "EnemyEtis-1237");
				break;
			}
			case 24200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001207);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001237, EnemyEtis, "EnemyEtis-1238");
				break;
			}
			case 24220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001208);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001238, EnemyEtis, "EnemyEtis-1239");
				break;
			}
			case 24240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001209);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001239, EnemyEtis, "EnemyEtis-1240");
				break;
			}
			case 24260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001210);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001240, EnemyEtis, "EnemyEtis-1241");
				break;
			}
			case 24280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001211);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001241, EnemyEtis, "EnemyEtis-1242");
				break;
			}
			case 24300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001212);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001242, EnemyEtis, "EnemyEtis-1243");
				break;
			}
			case 24320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001213);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001243, EnemyEtis, "EnemyEtis-1244");
				break;
			}
			case 24340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001214);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001244, EnemyEtis, "EnemyEtis-1245");
				break;
			}
			case 24360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001215);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001245, EnemyEtis, "EnemyEtis-1246");
				break;
			}
			case 24380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001216);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001246, EnemyEtis, "EnemyEtis-1247");
				break;
			}
			case 24400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001217);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001247, EnemyEtis, "EnemyEtis-1248");
				break;
			}
			case 24420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001218);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001248, EnemyEtis, "EnemyEtis-1249");
				break;
			}
			case 24440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001219);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001249, EnemyEtis, "EnemyEtis-1250");
				break;
			}
			case 24460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001220);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001250, EnemyEtis, "EnemyEtis-1251");
				break;
			}
			case 24480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001221);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001251, EnemyEtis, "EnemyEtis-1252");
				break;
			}
			case 24500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001222);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001252, EnemyEtis, "EnemyEtis-1253");
				break;
			}
			case 24520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001223);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001253, EnemyEtis, "EnemyEtis-1254");
				break;
			}
			case 24540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001224);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001254, EnemyEtis, "EnemyEtis-1255");
				break;
			}
			case 24560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001225);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001255, EnemyEtis, "EnemyEtis-1256");
				break;
			}
			case 24580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001226);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001256, EnemyEtis, "EnemyEtis-1257");
				break;
			}
			case 24600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001227);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001257, EnemyEtis, "EnemyEtis-1258");
				break;
			}
			case 24620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001228);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001258, EnemyEtis, "EnemyEtis-1259");
				break;
			}
			case 24640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001229);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001259, EnemyEtis, "EnemyEtis-1260");
				break;
			}
			case 24660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001230);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001260, EnemyEtis, "EnemyEtis-1261");
				break;
			}
			case 24680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001231);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001261, EnemyEtis, "EnemyEtis-1262");
				break;
			}
			case 24700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001232);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001262, EnemyEtis, "EnemyEtis-1263");
				break;
			}
			case 24720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001233);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001263, EnemyEtis, "EnemyEtis-1264");
				break;
			}
			case 24740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001234);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001264, EnemyEtis, "EnemyEtis-1265");
				break;
			}
			case 24760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001235);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001265, EnemyEtis, "EnemyEtis-1266");
				break;
			}
			case 24780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001236);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001266, EnemyEtis, "EnemyEtis-1267");
				break;
			}
			case 24800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001237);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001267, EnemyEtis, "EnemyEtis-1268");
				break;
			}
			case 24820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001238);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001268, EnemyEtis, "EnemyEtis-1269");
				break;
			}
			case 24840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001239);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001269, EnemyEtis, "EnemyEtis-1270");
				break;
			}
			case 24860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001240);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001270, EnemyEtis, "EnemyEtis-1271");
				break;
			}
			case 24880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001241);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001271, EnemyEtis, "EnemyEtis-1272");
				break;
			}
			case 24900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001242);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001272, EnemyEtis, "EnemyEtis-1273");
				break;
			}
			case 24920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001243);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001273, EnemyEtis, "EnemyEtis-1274");
				break;
			}
			case 24940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001244);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001274, EnemyEtis, "EnemyEtis-1275");
				break;
			}
			case 24960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001245);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001275, EnemyEtis, "EnemyEtis-1276");
				break;
			}
			case 24980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001246);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001276, EnemyEtis, "EnemyEtis-1277");
				break;
			}
			case 25000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001247);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001277, EnemyEtis, "EnemyEtis-1278");
				break;
			}
			case 25020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001248);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001278, EnemyEtis, "EnemyEtis-1279");
				break;
			}
			case 25040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001249);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001279, EnemyEtis, "EnemyEtis-1280");
				break;
			}
			case 25060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001250);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001280, EnemyEtis, "EnemyEtis-1281");
				break;
			}
			case 25080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001251);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001281, EnemyEtis, "EnemyEtis-1282");
				break;
			}
			case 25100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001252);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001282, EnemyEtis, "EnemyEtis-1283");
				break;
			}
			case 25120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001253);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001283, EnemyEtis, "EnemyEtis-1284");
				break;
			}
			case 25140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001254);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001284, EnemyEtis, "EnemyEtis-1285");
				break;
			}
			case 25160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001255);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001285, EnemyEtis, "EnemyEtis-1286");
				break;
			}
			case 25180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001256);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001286, EnemyEtis, "EnemyEtis-1287");
				break;
			}
			case 25200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001257);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001287, EnemyEtis, "EnemyEtis-1288");
				break;
			}
			case 25220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001258);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001288, EnemyEtis, "EnemyEtis-1289");
				break;
			}
			case 25240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001259);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001289, EnemyEtis, "EnemyEtis-1290");
				break;
			}
			case 25260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001260);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001290, EnemyEtis, "EnemyEtis-1291");
				break;
			}
			case 25280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001261);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001291, EnemyEtis, "EnemyEtis-1292");
				break;
			}
			case 25300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001262);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001292, EnemyEtis, "EnemyEtis-1293");
				break;
			}
			case 25320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001263);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001293, EnemyEtis, "EnemyEtis-1294");
				break;
			}
			case 25340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001264);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001294, EnemyEtis, "EnemyEtis-1295");
				break;
			}
			case 25360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001265);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001295, EnemyEtis, "EnemyEtis-1296");
				break;
			}
			case 25380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001266);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001296, EnemyEtis, "EnemyEtis-1297");
				break;
			}
			case 25400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001267);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001297, EnemyEtis, "EnemyEtis-1298");
				break;
			}
			case 25420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001268);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001298, EnemyEtis, "EnemyEtis-1299");
				break;
			}
			case 25440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001269);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001299, EnemyEtis, "EnemyEtis-1300");
				break;
			}
			case 25460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001270);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001300, EnemyEtis, "EnemyEtis-1301");
				break;
			}
			case 25480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001271);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001301, EnemyEtis, "EnemyEtis-1302");
				break;
			}
			case 25500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001272);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001302, EnemyEtis, "EnemyEtis-1303");
				break;
			}
			case 25520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001273);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001303, EnemyEtis, "EnemyEtis-1304");
				break;
			}
			case 25540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001274);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001304, EnemyEtis, "EnemyEtis-1305");
				break;
			}
			case 25560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001275);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001305, EnemyEtis, "EnemyEtis-1306");
				break;
			}
			case 25580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001276);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001306, EnemyEtis, "EnemyEtis-1307");
				break;
			}
			case 25600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001277);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001307, EnemyEtis, "EnemyEtis-1308");
				break;
			}
			case 25620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001278);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001308, EnemyEtis, "EnemyEtis-1309");
				break;
			}
			case 25640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001279);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001309, EnemyEtis, "EnemyEtis-1310");
				break;
			}
			case 25660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001280);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001310, EnemyEtis, "EnemyEtis-1311");
				break;
			}
			case 25680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001281);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001311, EnemyEtis, "EnemyEtis-1312");
				break;
			}
			case 25700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001282);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001312, EnemyEtis, "EnemyEtis-1313");
				break;
			}
			case 25720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001283);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001313, EnemyEtis, "EnemyEtis-1314");
				break;
			}
			case 25740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001284);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001314, EnemyEtis, "EnemyEtis-1315");
				break;
			}
			case 25760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001285);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001315, EnemyEtis, "EnemyEtis-1316");
				break;
			}
			case 25780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001286);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001316, EnemyEtis, "EnemyEtis-1317");
				break;
			}
			case 25800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001287);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001317, EnemyEtis, "EnemyEtis-1318");
				break;
			}
			case 25820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001288);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001318, EnemyEtis, "EnemyEtis-1319");
				break;
			}
			case 25840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001289);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001319, EnemyEtis, "EnemyEtis-1320");
				break;
			}
			case 25860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001290);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001320, EnemyEtis, "EnemyEtis-1321");
				break;
			}
			case 25880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001291);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001321, EnemyEtis, "EnemyEtis-1322");
				break;
			}
			case 25900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001292);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001322, EnemyEtis, "EnemyEtis-1323");
				break;
			}
			case 25920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001293);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001323, EnemyEtis, "EnemyEtis-1324");
				break;
			}
			case 25940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001294);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001324, EnemyEtis, "EnemyEtis-1325");
				break;
			}
			case 25960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001295);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001325, EnemyEtis, "EnemyEtis-1326");
				break;
			}
			case 25980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001296);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001326, EnemyEtis, "EnemyEtis-1327");
				break;
			}
			case 26000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001297);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001327, EnemyEtis, "EnemyEtis-1328");
				break;
			}
			case 26020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001298);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001328, EnemyEtis, "EnemyEtis-1329");
				break;
			}
			case 26040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001299);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001329, EnemyEtis, "EnemyEtis-1330");
				break;
			}
			case 26060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001300);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001330, EnemyEtis, "EnemyEtis-1331");
				break;
			}
			case 26080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001301);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001331, EnemyEtis, "EnemyEtis-1332");
				break;
			}
			case 26100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001302);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001332, EnemyEtis, "EnemyEtis-1333");
				break;
			}
			case 26120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001303);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001333, EnemyEtis, "EnemyEtis-1334");
				break;
			}
			case 26140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001304);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001334, EnemyEtis, "EnemyEtis-1335");
				break;
			}
			case 26160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001305);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001335, EnemyEtis, "EnemyEtis-1336");
				break;
			}
			case 26180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001306);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001336, EnemyEtis, "EnemyEtis-1337");
				break;
			}
			case 26200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001307);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001337, EnemyEtis, "EnemyEtis-1338");
				break;
			}
			case 26220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001308);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001338, EnemyEtis, "EnemyEtis-1339");
				break;
			}
			case 26240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001309);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001339, EnemyEtis, "EnemyEtis-1340");
				break;
			}
			case 26260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001310);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001340, EnemyEtis, "EnemyEtis-1341");
				break;
			}
			case 26280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001311);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001341, EnemyEtis, "EnemyEtis-1342");
				break;
			}
			case 26300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001312);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001342, EnemyEtis, "EnemyEtis-1343");
				break;
			}
			case 26320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001313);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001343, EnemyEtis, "EnemyEtis-1344");
				break;
			}
			case 26340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001314);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001344, EnemyEtis, "EnemyEtis-1345");
				break;
			}
			case 26360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001315);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001345, EnemyEtis, "EnemyEtis-1346");
				break;
			}
			case 26380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001316);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001346, EnemyEtis, "EnemyEtis-1347");
				break;
			}
			case 26400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001317);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001347, EnemyEtis, "EnemyEtis-1348");
				break;
			}
			case 26420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001318);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001348, EnemyEtis, "EnemyEtis-1349");
				break;
			}
			case 26440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001319);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001349, EnemyEtis, "EnemyEtis-1350");
				break;
			}
			case 26460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001320);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001350, EnemyEtis, "EnemyEtis-1351");
				break;
			}
			case 26480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001321);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001351, EnemyEtis, "EnemyEtis-1352");
				break;
			}
			case 26500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001322);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001352, EnemyEtis, "EnemyEtis-1353");
				break;
			}
			case 26520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001323);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001353, EnemyEtis, "EnemyEtis-1354");
				break;
			}
			case 26540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001324);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001354, EnemyEtis, "EnemyEtis-1355");
				break;
			}
			case 26560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001325);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001355, EnemyEtis, "EnemyEtis-1356");
				break;
			}
			case 26580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001326);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001356, EnemyEtis, "EnemyEtis-1357");
				break;
			}
			case 26600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001327);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001357, EnemyEtis, "EnemyEtis-1358");
				break;
			}
			case 26620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001328);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001358, EnemyEtis, "EnemyEtis-1359");
				break;
			}
			case 26640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001329);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001359, EnemyEtis, "EnemyEtis-1360");
				break;
			}
			case 26660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001330);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001360, EnemyEtis, "EnemyEtis-1361");
				break;
			}
			case 26680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001331);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001361, EnemyEtis, "EnemyEtis-1362");
				break;
			}
			case 26700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001332);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001362, EnemyEtis, "EnemyEtis-1363");
				break;
			}
			case 26720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001333);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001363, EnemyEtis, "EnemyEtis-1364");
				break;
			}
			case 26740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001334);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001364, EnemyEtis, "EnemyEtis-1365");
				break;
			}
			case 26760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001335);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001365, EnemyEtis, "EnemyEtis-1366");
				break;
			}
			case 26780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001336);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001366, EnemyEtis, "EnemyEtis-1367");
				break;
			}
			case 26800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001337);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001367, EnemyEtis, "EnemyEtis-1368");
				break;
			}
			case 26820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001338);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001368, EnemyEtis, "EnemyEtis-1369");
				break;
			}
			case 26840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001339);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001369, EnemyEtis, "EnemyEtis-1370");
				break;
			}
			case 26860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001340);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001370, EnemyEtis, "EnemyEtis-1371");
				break;
			}
			case 26880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001341);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001371, EnemyEtis, "EnemyEtis-1372");
				break;
			}
			case 26900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001342);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001372, EnemyEtis, "EnemyEtis-1373");
				break;
			}
			case 26920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001343);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001373, EnemyEtis, "EnemyEtis-1374");
				break;
			}
			case 26940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001344);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001374, EnemyEtis, "EnemyEtis-1375");
				break;
			}
			case 26960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001345);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001375, EnemyEtis, "EnemyEtis-1376");
				break;
			}
			case 26980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001346);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001376, EnemyEtis, "EnemyEtis-1377");
				break;
			}
			case 27000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001347);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001377, EnemyEtis, "EnemyEtis-1378");
				break;
			}
			case 27020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001348);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001378, EnemyEtis, "EnemyEtis-1379");
				break;
			}
			case 27040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001349);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001379, EnemyEtis, "EnemyEtis-1380");
				break;
			}
			case 27060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001350);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001380, EnemyEtis, "EnemyEtis-1381");
				break;
			}
			case 27080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001351);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001381, EnemyEtis, "EnemyEtis-1382");
				break;
			}
			case 27100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001352);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001382, EnemyEtis, "EnemyEtis-1383");
				break;
			}
			case 27120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001353);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001383, EnemyEtis, "EnemyEtis-1384");
				break;
			}
			case 27140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001354);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001384, EnemyEtis, "EnemyEtis-1385");
				break;
			}
			case 27160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001355);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001385, EnemyEtis, "EnemyEtis-1386");
				break;
			}
			case 27180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001356);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001386, EnemyEtis, "EnemyEtis-1387");
				break;
			}
			case 27200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001357);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001387, EnemyEtis, "EnemyEtis-1388");
				break;
			}
			case 27220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001358);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001388, EnemyEtis, "EnemyEtis-1389");
				break;
			}
			case 27240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001359);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001389, EnemyEtis, "EnemyEtis-1390");
				break;
			}
			case 27260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001360);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001390, EnemyEtis, "EnemyEtis-1391");
				break;
			}
			case 27280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001361);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001391, EnemyEtis, "EnemyEtis-1392");
				break;
			}
			case 27300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001362);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001392, EnemyEtis, "EnemyEtis-1393");
				break;
			}
			case 27320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001363);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001393, EnemyEtis, "EnemyEtis-1394");
				break;
			}
			case 27340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001364);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001394, EnemyEtis, "EnemyEtis-1395");
				break;
			}
			case 27360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001365);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001395, EnemyEtis, "EnemyEtis-1396");
				break;
			}
			case 27380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001366);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001396, EnemyEtis, "EnemyEtis-1397");
				break;
			}
			case 27400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001367);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001397, EnemyEtis, "EnemyEtis-1398");
				break;
			}
			case 27420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001368);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001398, EnemyEtis, "EnemyEtis-1399");
				break;
			}
			case 27440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001369);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001399, EnemyEtis, "EnemyEtis-1400");
				break;
			}
			case 27460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001370);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001400, EnemyEtis, "EnemyEtis-1401");
				break;
			}
			case 27480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001371);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001401, EnemyEtis, "EnemyEtis-1402");
				break;
			}
			case 27500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001372);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001402, EnemyEtis, "EnemyEtis-1403");
				break;
			}
			case 27520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001373);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001403, EnemyEtis, "EnemyEtis-1404");
				break;
			}
			case 27540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001374);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001404, EnemyEtis, "EnemyEtis-1405");
				break;
			}
			case 27560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001375);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001405, EnemyEtis, "EnemyEtis-1406");
				break;
			}
			case 27580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001376);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001406, EnemyEtis, "EnemyEtis-1407");
				break;
			}
			case 27600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001377);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001407, EnemyEtis, "EnemyEtis-1408");
				break;
			}
			case 27620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001378);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001408, EnemyEtis, "EnemyEtis-1409");
				break;
			}
			case 27640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001379);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001409, EnemyEtis, "EnemyEtis-1410");
				break;
			}
			case 27660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001380);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001410, EnemyEtis, "EnemyEtis-1411");
				break;
			}
			case 27680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001381);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001411, EnemyEtis, "EnemyEtis-1412");
				break;
			}
			case 27700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001382);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001412, EnemyEtis, "EnemyEtis-1413");
				break;
			}
			case 27720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001383);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001413, EnemyEtis, "EnemyEtis-1414");
				break;
			}
			case 27740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001384);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001414, EnemyEtis, "EnemyEtis-1415");
				break;
			}
			case 27760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001385);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001415, EnemyEtis, "EnemyEtis-1416");
				break;
			}
			case 27780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001386);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001416, EnemyEtis, "EnemyEtis-1417");
				break;
			}
			case 27800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001387);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001417, EnemyEtis, "EnemyEtis-1418");
				break;
			}
			case 27820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001388);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001418, EnemyEtis, "EnemyEtis-1419");
				break;
			}
			case 27840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001389);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001419, EnemyEtis, "EnemyEtis-1420");
				break;
			}
			case 27860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001390);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001420, EnemyEtis, "EnemyEtis-1421");
				break;
			}
			case 27880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001391);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001421, EnemyEtis, "EnemyEtis-1422");
				break;
			}
			case 27900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001392);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001422, EnemyEtis, "EnemyEtis-1423");
				break;
			}
			case 27920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001393);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001423, EnemyEtis, "EnemyEtis-1424");
				break;
			}
			case 27940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001394);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001424, EnemyEtis, "EnemyEtis-1425");
				break;
			}
			case 27960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001395);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001425, EnemyEtis, "EnemyEtis-1426");
				break;
			}
			case 27980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001396);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001426, EnemyEtis, "EnemyEtis-1427");
				break;
			}
			case 28000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001397);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001427, EnemyEtis, "EnemyEtis-1428");
				break;
			}
			case 28020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001398);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001428, EnemyEtis, "EnemyEtis-1429");
				break;
			}
			case 28040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001399);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001429, EnemyEtis, "EnemyEtis-1430");
				break;
			}
			case 28060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001400);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001430, EnemyEtis, "EnemyEtis-1431");
				break;
			}
			case 28080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001401);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001431, EnemyEtis, "EnemyEtis-1432");
				break;
			}
			case 28100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001402);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001432, EnemyEtis, "EnemyEtis-1433");
				break;
			}
			case 28120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001403);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001433, EnemyEtis, "EnemyEtis-1434");
				break;
			}
			case 28140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001404);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001434, EnemyEtis, "EnemyEtis-1435");
				break;
			}
			case 28160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001405);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001435, EnemyEtis, "EnemyEtis-1436");
				break;
			}
			case 28180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001406);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001436, EnemyEtis, "EnemyEtis-1437");
				break;
			}
			case 28200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001407);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001437, EnemyEtis, "EnemyEtis-1438");
				break;
			}
			case 28220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001408);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001438, EnemyEtis, "EnemyEtis-1439");
				break;
			}
			case 28240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001409);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001439, EnemyEtis, "EnemyEtis-1440");
				break;
			}
			case 28260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001410);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001440, EnemyEtis, "EnemyEtis-1441");
				break;
			}
			case 28280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001411);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001441, EnemyEtis, "EnemyEtis-1442");
				break;
			}
			case 28300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001412);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001442, EnemyEtis, "EnemyEtis-1443");
				break;
			}
			case 28320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001413);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001443, EnemyEtis, "EnemyEtis-1444");
				break;
			}
			case 28340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001414);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001444, EnemyEtis, "EnemyEtis-1445");
				break;
			}
			case 28360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001415);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001445, EnemyEtis, "EnemyEtis-1446");
				break;
			}
			case 28380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001416);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001446, EnemyEtis, "EnemyEtis-1447");
				break;
			}
			case 28400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001417);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001447, EnemyEtis, "EnemyEtis-1448");
				break;
			}
			case 28420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001418);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001448, EnemyEtis, "EnemyEtis-1449");
				break;
			}
			case 28440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001419);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001449, EnemyEtis, "EnemyEtis-1450");
				break;
			}
			case 28460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001420);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001450, EnemyEtis, "EnemyEtis-1451");
				break;
			}
			case 28480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001421);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001451, EnemyEtis, "EnemyEtis-1452");
				break;
			}
			case 28500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001422);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001452, EnemyEtis, "EnemyEtis-1453");
				break;
			}
			case 28520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001423);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001453, EnemyEtis, "EnemyEtis-1454");
				break;
			}
			case 28540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001424);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001454, EnemyEtis, "EnemyEtis-1455");
				break;
			}
			case 28560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001425);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001455, EnemyEtis, "EnemyEtis-1456");
				break;
			}
			case 28580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001426);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001456, EnemyEtis, "EnemyEtis-1457");
				break;
			}
			case 28600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001427);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001457, EnemyEtis, "EnemyEtis-1458");
				break;
			}
			case 28620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001428);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001458, EnemyEtis, "EnemyEtis-1459");
				break;
			}
			case 28640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001429);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001459, EnemyEtis, "EnemyEtis-1460");
				break;
			}
			case 28660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001430);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001460, EnemyEtis, "EnemyEtis-1461");
				break;
			}
			case 28680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001431);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001461, EnemyEtis, "EnemyEtis-1462");
				break;
			}
			case 28700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001432);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001462, EnemyEtis, "EnemyEtis-1463");
				break;
			}
			case 28720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001433);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001463, EnemyEtis, "EnemyEtis-1464");
				break;
			}
			case 28740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001434);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001464, EnemyEtis, "EnemyEtis-1465");
				break;
			}
			case 28760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001435);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001465, EnemyEtis, "EnemyEtis-1466");
				break;
			}
			case 28780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001436);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001466, EnemyEtis, "EnemyEtis-1467");
				break;
			}
			case 28800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001437);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001467, EnemyEtis, "EnemyEtis-1468");
				break;
			}
			case 28820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001438);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001468, EnemyEtis, "EnemyEtis-1469");
				break;
			}
			case 28840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001439);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001469, EnemyEtis, "EnemyEtis-1470");
				break;
			}
			case 28860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001440);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001470, EnemyEtis, "EnemyEtis-1471");
				break;
			}
			case 28880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001441);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001471, EnemyEtis, "EnemyEtis-1472");
				break;
			}
			case 28900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001442);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001472, EnemyEtis, "EnemyEtis-1473");
				break;
			}
			case 28920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001443);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001473, EnemyEtis, "EnemyEtis-1474");
				break;
			}
			case 28940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001444);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001474, EnemyEtis, "EnemyEtis-1475");
				break;
			}
			case 28960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001445);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001475, EnemyEtis, "EnemyEtis-1476");
				break;
			}
			case 28980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001446);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001476, EnemyEtis, "EnemyEtis-1477");
				break;
			}
			case 29000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001447);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001477, EnemyEtis, "EnemyEtis-1478");
				break;
			}
			case 29020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001448);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001478, EnemyEtis, "EnemyEtis-1479");
				break;
			}
			case 29040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001449);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001479, EnemyEtis, "EnemyEtis-1480");
				break;
			}
			case 29060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001450);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001480, EnemyEtis, "EnemyEtis-1481");
				break;
			}
			case 29080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001451);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001481, EnemyEtis, "EnemyEtis-1482");
				break;
			}
			case 29100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001452);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001482, EnemyEtis, "EnemyEtis-1483");
				break;
			}
			case 29120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001453);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001483, EnemyEtis, "EnemyEtis-1484");
				break;
			}
			case 29140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001454);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001484, EnemyEtis, "EnemyEtis-1485");
				break;
			}
			case 29160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001455);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001485, EnemyEtis, "EnemyEtis-1486");
				break;
			}
			case 29180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001456);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001486, EnemyEtis, "EnemyEtis-1487");
				break;
			}
			case 29200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001457);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001487, EnemyEtis, "EnemyEtis-1488");
				break;
			}
			case 29220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001458);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001488, EnemyEtis, "EnemyEtis-1489");
				break;
			}
			case 29240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001459);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001489, EnemyEtis, "EnemyEtis-1490");
				break;
			}
			case 29260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001460);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001490, EnemyEtis, "EnemyEtis-1491");
				break;
			}
			case 29280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001461);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001491, EnemyEtis, "EnemyEtis-1492");
				break;
			}
			case 29300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001462);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001492, EnemyEtis, "EnemyEtis-1493");
				break;
			}
			case 29320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001463);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001493, EnemyEtis, "EnemyEtis-1494");
				break;
			}
			case 29340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001464);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001494, EnemyEtis, "EnemyEtis-1495");
				break;
			}
			case 29360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001465);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001495, EnemyEtis, "EnemyEtis-1496");
				break;
			}
			case 29380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001466);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001496, EnemyEtis, "EnemyEtis-1497");
				break;
			}
			case 29400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001467);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001497, EnemyEtis, "EnemyEtis-1498");
				break;
			}
			case 29420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001468);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001498, EnemyEtis, "EnemyEtis-1499");
				break;
			}
			case 29440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001469);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001499, EnemyEtis, "EnemyEtis-1500");
				break;
			}
			case 29460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001470);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001500, EnemyEtis, "EnemyEtis-1501");
				break;
			}
			case 29480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001471);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001501, EnemyEtis, "EnemyEtis-1502");
				break;
			}
			case 29500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001472);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001502, EnemyEtis, "EnemyEtis-1503");
				break;
			}
			case 29520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001473);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001503, EnemyEtis, "EnemyEtis-1504");
				break;
			}
			case 29540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001474);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001504, EnemyEtis, "EnemyEtis-1505");
				break;
			}
			case 29560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001475);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001505, EnemyEtis, "EnemyEtis-1506");
				break;
			}
			case 29580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001476);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001506, EnemyEtis, "EnemyEtis-1507");
				break;
			}
			case 29600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001477);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001507, EnemyEtis, "EnemyEtis-1508");
				break;
			}
			case 29620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001478);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001508, EnemyEtis, "EnemyEtis-1509");
				break;
			}
			case 29640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001479);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001509, EnemyEtis, "EnemyEtis-1510");
				break;
			}
			case 29660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001480);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001510, EnemyEtis, "EnemyEtis-1511");
				break;
			}
			case 29680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001481);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001511, EnemyEtis, "EnemyEtis-1512");
				break;
			}
			case 29700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001482);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001512, EnemyEtis, "EnemyEtis-1513");
				break;
			}
			case 29720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001483);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001513, EnemyEtis, "EnemyEtis-1514");
				break;
			}
			case 29740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001484);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001514, EnemyEtis, "EnemyEtis-1515");
				break;
			}
			case 29760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001485);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001515, EnemyEtis, "EnemyEtis-1516");
				break;
			}
			case 29780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001486);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001516, EnemyEtis, "EnemyEtis-1517");
				break;
			}
			case 29800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001487);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001517, EnemyEtis, "EnemyEtis-1518");
				break;
			}
			case 29820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001488);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001518, EnemyEtis, "EnemyEtis-1519");
				break;
			}
			case 29840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001489);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001519, EnemyEtis, "EnemyEtis-1520");
				break;
			}
			case 29860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001490);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001520, EnemyEtis, "EnemyEtis-1521");
				break;
			}
			case 29880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001491);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001521, EnemyEtis, "EnemyEtis-1522");
				break;
			}
			case 29900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001492);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001522, EnemyEtis, "EnemyEtis-1523");
				break;
			}
			case 29920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001493);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001523, EnemyEtis, "EnemyEtis-1524");
				break;
			}
			case 29940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001494);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001524, EnemyEtis, "EnemyEtis-1525");
				break;
			}
			case 29960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001495);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001525, EnemyEtis, "EnemyEtis-1526");
				break;
			}
			case 29980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001496);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001526, EnemyEtis, "EnemyEtis-1527");
				break;
			}
			case 30000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001497);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001527, EnemyEtis, "EnemyEtis-1528");
				break;
			}
			case 30020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001498);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001528, EnemyEtis, "EnemyEtis-1529");
				break;
			}
			case 30040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001499);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001529, EnemyEtis, "EnemyEtis-1530");
				break;
			}
			case 30060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001500);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001530, EnemyEtis, "EnemyEtis-1531");
				break;
			}
			case 30080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001501);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001531, EnemyEtis, "EnemyEtis-1532");
				break;
			}
			case 30100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001502);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001532, EnemyEtis, "EnemyEtis-1533");
				break;
			}
			case 30120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001503);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001533, EnemyEtis, "EnemyEtis-1534");
				break;
			}
			case 30140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001504);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001534, EnemyEtis, "EnemyEtis-1535");
				break;
			}
			case 30160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001505);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001535, EnemyEtis, "EnemyEtis-1536");
				break;
			}
			case 30180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001506);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001536, EnemyEtis, "EnemyEtis-1537");
				break;
			}
			case 30200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001507);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001537, EnemyEtis, "EnemyEtis-1538");
				break;
			}
			case 30220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001508);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001538, EnemyEtis, "EnemyEtis-1539");
				break;
			}
			case 30240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001509);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001539, EnemyEtis, "EnemyEtis-1540");
				break;
			}
			case 30260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001510);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001540, EnemyEtis, "EnemyEtis-1541");
				break;
			}
			case 30280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001511);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001541, EnemyEtis, "EnemyEtis-1542");
				break;
			}
			case 30300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001512);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001542, EnemyEtis, "EnemyEtis-1543");
				break;
			}
			case 30320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001513);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001543, EnemyEtis, "EnemyEtis-1544");
				break;
			}
			case 30340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001514);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001544, EnemyEtis, "EnemyEtis-1545");
				break;
			}
			case 30360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001515);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001545, EnemyEtis, "EnemyEtis-1546");
				break;
			}
			case 30380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001516);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001546, EnemyEtis, "EnemyEtis-1547");
				break;
			}
			case 30400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001517);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001547, EnemyEtis, "EnemyEtis-1548");
				break;
			}
			case 30420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001518);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001548, EnemyEtis, "EnemyEtis-1549");
				break;
			}
			case 30440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001519);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001549, EnemyEtis, "EnemyEtis-1550");
				break;
			}
			case 30460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001520);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001550, EnemyEtis, "EnemyEtis-1551");
				break;
			}
			case 30480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001521);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001551, EnemyEtis, "EnemyEtis-1552");
				break;
			}
			case 30500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001522);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001552, EnemyEtis, "EnemyEtis-1553");
				break;
			}
			case 30520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001523);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001553, EnemyEtis, "EnemyEtis-1554");
				break;
			}
			case 30540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001524);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001554, EnemyEtis, "EnemyEtis-1555");
				break;
			}
			case 30560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001525);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001555, EnemyEtis, "EnemyEtis-1556");
				break;
			}
			case 30580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001526);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001556, EnemyEtis, "EnemyEtis-1557");
				break;
			}
			case 30600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001527);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001557, EnemyEtis, "EnemyEtis-1558");
				break;
			}
			case 30620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001528);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001558, EnemyEtis, "EnemyEtis-1559");
				break;
			}
			case 30640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001529);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001559, EnemyEtis, "EnemyEtis-1560");
				break;
			}
			case 30660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001530);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001560, EnemyEtis, "EnemyEtis-1561");
				break;
			}
			case 30680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001531);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001561, EnemyEtis, "EnemyEtis-1562");
				break;
			}
			case 30700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001532);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001562, EnemyEtis, "EnemyEtis-1563");
				break;
			}
			case 30720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001533);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001563, EnemyEtis, "EnemyEtis-1564");
				break;
			}
			case 30740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001534);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001564, EnemyEtis, "EnemyEtis-1565");
				break;
			}
			case 30760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001535);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001565, EnemyEtis, "EnemyEtis-1566");
				break;
			}
			case 30780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001536);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001566, EnemyEtis, "EnemyEtis-1567");
				break;
			}
			case 30800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001537);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001567, EnemyEtis, "EnemyEtis-1568");
				break;
			}
			case 30820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001538);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001568, EnemyEtis, "EnemyEtis-1569");
				break;
			}
			case 30840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001539);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001569, EnemyEtis, "EnemyEtis-1570");
				break;
			}
			case 30860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001540);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001570, EnemyEtis, "EnemyEtis-1571");
				break;
			}
			case 30880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001541);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001571, EnemyEtis, "EnemyEtis-1572");
				break;
			}
			case 30900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001542);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001572, EnemyEtis, "EnemyEtis-1573");
				break;
			}
			case 30920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001543);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001573, EnemyEtis, "EnemyEtis-1574");
				break;
			}
			case 30940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001544);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001574, EnemyEtis, "EnemyEtis-1575");
				break;
			}
			case 30960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001545);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001575, EnemyEtis, "EnemyEtis-1576");
				break;
			}
			case 30980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001546);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001576, EnemyEtis, "EnemyEtis-1577");
				break;
			}
			case 31000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001547);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001577, EnemyEtis, "EnemyEtis-1578");
				break;
			}
			case 31020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001548);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001578, EnemyEtis, "EnemyEtis-1579");
				break;
			}
			case 31040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001549);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001579, EnemyEtis, "EnemyEtis-1580");
				break;
			}
			case 31060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001550);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001580, EnemyEtis, "EnemyEtis-1581");
				break;
			}
			case 31080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001551);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001581, EnemyEtis, "EnemyEtis-1582");
				break;
			}
			case 31100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001552);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001582, EnemyEtis, "EnemyEtis-1583");
				break;
			}
			case 31120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001553);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001583, EnemyEtis, "EnemyEtis-1584");
				break;
			}
			case 31140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001554);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001584, EnemyEtis, "EnemyEtis-1585");
				break;
			}
			case 31160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001555);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001585, EnemyEtis, "EnemyEtis-1586");
				break;
			}
			case 31180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001556);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001586, EnemyEtis, "EnemyEtis-1587");
				break;
			}
			case 31200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001557);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001587, EnemyEtis, "EnemyEtis-1588");
				break;
			}
			case 31220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001558);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001588, EnemyEtis, "EnemyEtis-1589");
				break;
			}
			case 31240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001559);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001589, EnemyEtis, "EnemyEtis-1590");
				break;
			}
			case 31260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001560);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001590, EnemyEtis, "EnemyEtis-1591");
				break;
			}
			case 31280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001561);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001591, EnemyEtis, "EnemyEtis-1592");
				break;
			}
			case 31300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001562);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001592, EnemyEtis, "EnemyEtis-1593");
				break;
			}
			case 31320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001563);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001593, EnemyEtis, "EnemyEtis-1594");
				break;
			}
			case 31340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001564);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001594, EnemyEtis, "EnemyEtis-1595");
				break;
			}
			case 31360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001565);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001595, EnemyEtis, "EnemyEtis-1596");
				break;
			}
			case 31380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001566);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001596, EnemyEtis, "EnemyEtis-1597");
				break;
			}
			case 31400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001567);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001597, EnemyEtis, "EnemyEtis-1598");
				break;
			}
			case 31420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001568);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001598, EnemyEtis, "EnemyEtis-1599");
				break;
			}
			case 31440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001569);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001599, EnemyEtis, "EnemyEtis-1600");
				break;
			}
			case 31460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001570);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001600, EnemyEtis, "EnemyEtis-1601");
				break;
			}
			case 31480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001571);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001601, EnemyEtis, "EnemyEtis-1602");
				break;
			}
			case 31500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001572);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001602, EnemyEtis, "EnemyEtis-1603");
				break;
			}
			case 31520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001573);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001603, EnemyEtis, "EnemyEtis-1604");
				break;
			}
			case 31540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001574);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001604, EnemyEtis, "EnemyEtis-1605");
				break;
			}
			case 31560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001575);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001605, EnemyEtis, "EnemyEtis-1606");
				break;
			}
			case 31580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001576);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001606, EnemyEtis, "EnemyEtis-1607");
				break;
			}
			case 31600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001577);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001607, EnemyEtis, "EnemyEtis-1608");
				break;
			}
			case 31620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001578);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001608, EnemyEtis, "EnemyEtis-1609");
				break;
			}
			case 31640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001579);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001609, EnemyEtis, "EnemyEtis-1610");
				break;
			}
			case 31660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001580);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001610, EnemyEtis, "EnemyEtis-1611");
				break;
			}
			case 31680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001581);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001611, EnemyEtis, "EnemyEtis-1612");
				break;
			}
			case 31700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001582);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001612, EnemyEtis, "EnemyEtis-1613");
				break;
			}
			case 31720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001583);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001613, EnemyEtis, "EnemyEtis-1614");
				break;
			}
			case 31740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001584);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001614, EnemyEtis, "EnemyEtis-1615");
				break;
			}
			case 31760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001585);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001615, EnemyEtis, "EnemyEtis-1616");
				break;
			}
			case 31780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001586);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001616, EnemyEtis, "EnemyEtis-1617");
				break;
			}
			case 31800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001587);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001617, EnemyEtis, "EnemyEtis-1618");
				break;
			}
			case 31820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001588);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001618, EnemyEtis, "EnemyEtis-1619");
				break;
			}
			case 31840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001589);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001619, EnemyEtis, "EnemyEtis-1620");
				break;
			}
			case 31860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001590);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001620, EnemyEtis, "EnemyEtis-1621");
				break;
			}
			case 31880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001591);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001621, EnemyEtis, "EnemyEtis-1622");
				break;
			}
			case 31900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001592);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001622, EnemyEtis, "EnemyEtis-1623");
				break;
			}
			case 31920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001593);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001623, EnemyEtis, "EnemyEtis-1624");
				break;
			}
			case 31940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001594);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001624, EnemyEtis, "EnemyEtis-1625");
				break;
			}
			case 31960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001595);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001625, EnemyEtis, "EnemyEtis-1626");
				break;
			}
			case 31980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001596);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001626, EnemyEtis, "EnemyEtis-1627");
				break;
			}
			case 32000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001597);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001627, EnemyEtis, "EnemyEtis-1628");
				break;
			}
			case 32020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001598);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001628, EnemyEtis, "EnemyEtis-1629");
				break;
			}
			case 32040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001599);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001629, EnemyEtis, "EnemyEtis-1630");
				break;
			}
			case 32060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001600);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001630, EnemyEtis, "EnemyEtis-1631");
				break;
			}
			case 32080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001601);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001631, EnemyEtis, "EnemyEtis-1632");
				break;
			}
			case 32100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001602);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001632, EnemyEtis, "EnemyEtis-1633");
				break;
			}
			case 32120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001603);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001633, EnemyEtis, "EnemyEtis-1634");
				break;
			}
			case 32140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001604);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001634, EnemyEtis, "EnemyEtis-1635");
				break;
			}
			case 32160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001605);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001635, EnemyEtis, "EnemyEtis-1636");
				break;
			}
			case 32180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001606);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001636, EnemyEtis, "EnemyEtis-1637");
				break;
			}
			case 32200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001607);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001637, EnemyEtis, "EnemyEtis-1638");
				break;
			}
			case 32220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001608);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001638, EnemyEtis, "EnemyEtis-1639");
				break;
			}
			case 32240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001609);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001639, EnemyEtis, "EnemyEtis-1640");
				break;
			}
			case 32260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001610);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001640, EnemyEtis, "EnemyEtis-1641");
				break;
			}
			case 32280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001611);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001641, EnemyEtis, "EnemyEtis-1642");
				break;
			}
			case 32300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001612);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001642, EnemyEtis, "EnemyEtis-1643");
				break;
			}
			case 32320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001613);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001643, EnemyEtis, "EnemyEtis-1644");
				break;
			}
			case 32340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001614);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001644, EnemyEtis, "EnemyEtis-1645");
				break;
			}
			case 32360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001615);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001645, EnemyEtis, "EnemyEtis-1646");
				break;
			}
			case 32380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001616);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001646, EnemyEtis, "EnemyEtis-1647");
				break;
			}
			case 32400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001617);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001647, EnemyEtis, "EnemyEtis-1648");
				break;
			}
			case 32420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001618);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001648, EnemyEtis, "EnemyEtis-1649");
				break;
			}
			case 32440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001619);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001649, EnemyEtis, "EnemyEtis-1650");
				break;
			}
			case 32460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001620);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001650, EnemyEtis, "EnemyEtis-1651");
				break;
			}
			case 32480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001621);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001651, EnemyEtis, "EnemyEtis-1652");
				break;
			}
			case 32500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001622);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001652, EnemyEtis, "EnemyEtis-1653");
				break;
			}
			case 32520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001623);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001653, EnemyEtis, "EnemyEtis-1654");
				break;
			}
			case 32540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001624);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001654, EnemyEtis, "EnemyEtis-1655");
				break;
			}
			case 32560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001625);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001655, EnemyEtis, "EnemyEtis-1656");
				break;
			}
			case 32580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001626);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001656, EnemyEtis, "EnemyEtis-1657");
				break;
			}
			case 32600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001627);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001657, EnemyEtis, "EnemyEtis-1658");
				break;
			}
			case 32620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001628);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001658, EnemyEtis, "EnemyEtis-1659");
				break;
			}
			case 32640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001629);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001659, EnemyEtis, "EnemyEtis-1660");
				break;
			}
			case 32660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001630);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001660, EnemyEtis, "EnemyEtis-1661");
				break;
			}
			case 32680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001631);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001661, EnemyEtis, "EnemyEtis-1662");
				break;
			}
			case 32700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001632);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001662, EnemyEtis, "EnemyEtis-1663");
				break;
			}
			case 32720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001633);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001663, EnemyEtis, "EnemyEtis-1664");
				break;
			}
			case 32740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001634);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001664, EnemyEtis, "EnemyEtis-1665");
				break;
			}
			case 32760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001635);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001665, EnemyEtis, "EnemyEtis-1666");
				break;
			}
			case 32780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001636);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001666, EnemyEtis, "EnemyEtis-1667");
				break;
			}
			case 32800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001637);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001667, EnemyEtis, "EnemyEtis-1668");
				break;
			}
			case 32820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001638);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001668, EnemyEtis, "EnemyEtis-1669");
				break;
			}
			case 32840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001639);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001669, EnemyEtis, "EnemyEtis-1670");
				break;
			}
			case 32860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001640);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001670, EnemyEtis, "EnemyEtis-1671");
				break;
			}
			case 32880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001641);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001671, EnemyEtis, "EnemyEtis-1672");
				break;
			}
			case 32900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001642);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001672, EnemyEtis, "EnemyEtis-1673");
				break;
			}
			case 32920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001643);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001673, EnemyEtis, "EnemyEtis-1674");
				break;
			}
			case 32940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001644);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001674, EnemyEtis, "EnemyEtis-1675");
				break;
			}
			case 32960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001645);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001675, EnemyEtis, "EnemyEtis-1676");
				break;
			}
			case 32980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001646);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001676, EnemyEtis, "EnemyEtis-1677");
				break;
			}
			case 33000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001647);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001677, EnemyEtis, "EnemyEtis-1678");
				break;
			}
			case 33020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001648);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001678, EnemyEtis, "EnemyEtis-1679");
				break;
			}
			case 33040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001649);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001679, EnemyEtis, "EnemyEtis-1680");
				break;
			}
			case 33060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001650);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001680, EnemyEtis, "EnemyEtis-1681");
				break;
			}
			case 33080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001651);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001681, EnemyEtis, "EnemyEtis-1682");
				break;
			}
			case 33100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001652);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001682, EnemyEtis, "EnemyEtis-1683");
				break;
			}
			case 33120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001653);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001683, EnemyEtis, "EnemyEtis-1684");
				break;
			}
			case 33140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001654);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001684, EnemyEtis, "EnemyEtis-1685");
				break;
			}
			case 33160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001655);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001685, EnemyEtis, "EnemyEtis-1686");
				break;
			}
			case 33180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001656);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001686, EnemyEtis, "EnemyEtis-1687");
				break;
			}
			case 33200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001657);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001687, EnemyEtis, "EnemyEtis-1688");
				break;
			}
			case 33220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001658);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001688, EnemyEtis, "EnemyEtis-1689");
				break;
			}
			case 33240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001659);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001689, EnemyEtis, "EnemyEtis-1690");
				break;
			}
			case 33260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001660);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001690, EnemyEtis, "EnemyEtis-1691");
				break;
			}
			case 33280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001661);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001691, EnemyEtis, "EnemyEtis-1692");
				break;
			}
			case 33300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001662);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001692, EnemyEtis, "EnemyEtis-1693");
				break;
			}
			case 33320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001663);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001693, EnemyEtis, "EnemyEtis-1694");
				break;
			}
			case 33340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001664);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001694, EnemyEtis, "EnemyEtis-1695");
				break;
			}
			case 33360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001665);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001695, EnemyEtis, "EnemyEtis-1696");
				break;
			}
			case 33380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001666);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001696, EnemyEtis, "EnemyEtis-1697");
				break;
			}
			case 33400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001667);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001697, EnemyEtis, "EnemyEtis-1698");
				break;
			}
			case 33420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001668);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001698, EnemyEtis, "EnemyEtis-1699");
				break;
			}
			case 33440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001669);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001699, EnemyEtis, "EnemyEtis-1700");
				break;
			}
			case 33460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001670);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001700, EnemyEtis, "EnemyEtis-1701");
				break;
			}
			case 33480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001671);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001701, EnemyEtis, "EnemyEtis-1702");
				break;
			}
			case 33500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001672);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001702, EnemyEtis, "EnemyEtis-1703");
				break;
			}
			case 33520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001673);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001703, EnemyEtis, "EnemyEtis-1704");
				break;
			}
			case 33540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001674);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001704, EnemyEtis, "EnemyEtis-1705");
				break;
			}
			case 33560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001675);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001705, EnemyEtis, "EnemyEtis-1706");
				break;
			}
			case 33580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001676);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001706, EnemyEtis, "EnemyEtis-1707");
				break;
			}
			case 33600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001677);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001707, EnemyEtis, "EnemyEtis-1708");
				break;
			}
			case 33620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001678);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001708, EnemyEtis, "EnemyEtis-1709");
				break;
			}
			case 33640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001679);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001709, EnemyEtis, "EnemyEtis-1710");
				break;
			}
			case 33660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001680);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001710, EnemyEtis, "EnemyEtis-1711");
				break;
			}
			case 33680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001681);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001711, EnemyEtis, "EnemyEtis-1712");
				break;
			}
			case 33700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001682);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001712, EnemyEtis, "EnemyEtis-1713");
				break;
			}
			case 33720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001683);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001713, EnemyEtis, "EnemyEtis-1714");
				break;
			}
			case 33740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001684);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001714, EnemyEtis, "EnemyEtis-1715");
				break;
			}
			case 33760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001685);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001715, EnemyEtis, "EnemyEtis-1716");
				break;
			}
			case 33780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001686);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001716, EnemyEtis, "EnemyEtis-1717");
				break;
			}
			case 33800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001687);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001717, EnemyEtis, "EnemyEtis-1718");
				break;
			}
			case 33820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001688);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001718, EnemyEtis, "EnemyEtis-1719");
				break;
			}
			case 33840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001689);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001719, EnemyEtis, "EnemyEtis-1720");
				break;
			}
			case 33860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001690);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001720, EnemyEtis, "EnemyEtis-1721");
				break;
			}
			case 33880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001691);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001721, EnemyEtis, "EnemyEtis-1722");
				break;
			}
			case 33900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001692);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001722, EnemyEtis, "EnemyEtis-1723");
				break;
			}
			case 33920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001693);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001723, EnemyEtis, "EnemyEtis-1724");
				break;
			}
			case 33940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001694);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001724, EnemyEtis, "EnemyEtis-1725");
				break;
			}
			case 33960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001695);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001725, EnemyEtis, "EnemyEtis-1726");
				break;
			}
			case 33980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001696);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001726, EnemyEtis, "EnemyEtis-1727");
				break;
			}
			case 34000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001697);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001727, EnemyEtis, "EnemyEtis-1728");
				break;
			}
			case 34020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001698);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001728, EnemyEtis, "EnemyEtis-1729");
				break;
			}
			case 34040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001699);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001729, EnemyEtis, "EnemyEtis-1730");
				break;
			}
			case 34060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001700);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001730, EnemyEtis, "EnemyEtis-1731");
				break;
			}
			case 34080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001701);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001731, EnemyEtis, "EnemyEtis-1732");
				break;
			}
			case 34100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001702);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001732, EnemyEtis, "EnemyEtis-1733");
				break;
			}
			case 34120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001703);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001733, EnemyEtis, "EnemyEtis-1734");
				break;
			}
			case 34140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001704);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001734, EnemyEtis, "EnemyEtis-1735");
				break;
			}
			case 34160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001705);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001735, EnemyEtis, "EnemyEtis-1736");
				break;
			}
			case 34180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001706);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001736, EnemyEtis, "EnemyEtis-1737");
				break;
			}
			case 34200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001707);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001737, EnemyEtis, "EnemyEtis-1738");
				break;
			}
			case 34220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001708);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001738, EnemyEtis, "EnemyEtis-1739");
				break;
			}
			case 34240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001709);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001739, EnemyEtis, "EnemyEtis-1740");
				break;
			}
			case 34260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001710);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001740, EnemyEtis, "EnemyEtis-1741");
				break;
			}
			case 34280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001711);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001741, EnemyEtis, "EnemyEtis-1742");
				break;
			}
			case 34300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001712);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001742, EnemyEtis, "EnemyEtis-1743");
				break;
			}
			case 34320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001713);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001743, EnemyEtis, "EnemyEtis-1744");
				break;
			}
			case 34340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001714);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001744, EnemyEtis, "EnemyEtis-1745");
				break;
			}
			case 34360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001715);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001745, EnemyEtis, "EnemyEtis-1746");
				break;
			}
			case 34380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001716);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001746, EnemyEtis, "EnemyEtis-1747");
				break;
			}
			case 34400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001717);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001747, EnemyEtis, "EnemyEtis-1748");
				break;
			}
			case 34420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001718);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001748, EnemyEtis, "EnemyEtis-1749");
				break;
			}
			case 34440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001719);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001749, EnemyEtis, "EnemyEtis-1750");
				break;
			}
			case 34460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001720);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001750, EnemyEtis, "EnemyEtis-1751");
				break;
			}
			case 34480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001721);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001751, EnemyEtis, "EnemyEtis-1752");
				break;
			}
			case 34500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001722);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001752, EnemyEtis, "EnemyEtis-1753");
				break;
			}
			case 34520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001723);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001753, EnemyEtis, "EnemyEtis-1754");
				break;
			}
			case 34540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001724);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001754, EnemyEtis, "EnemyEtis-1755");
				break;
			}
			case 34560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001725);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001755, EnemyEtis, "EnemyEtis-1756");
				break;
			}
			case 34580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001726);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001756, EnemyEtis, "EnemyEtis-1757");
				break;
			}
			case 34600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001727);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001757, EnemyEtis, "EnemyEtis-1758");
				break;
			}
			case 34620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001728);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001758, EnemyEtis, "EnemyEtis-1759");
				break;
			}
			case 34640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001729);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001759, EnemyEtis, "EnemyEtis-1760");
				break;
			}
			case 34660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001730);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001760, EnemyEtis, "EnemyEtis-1761");
				break;
			}
			case 34680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001731);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001761, EnemyEtis, "EnemyEtis-1762");
				break;
			}
			case 34700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001732);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001762, EnemyEtis, "EnemyEtis-1763");
				break;
			}
			case 34720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001733);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001763, EnemyEtis, "EnemyEtis-1764");
				break;
			}
			case 34740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001734);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001764, EnemyEtis, "EnemyEtis-1765");
				break;
			}
			case 34760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001735);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001765, EnemyEtis, "EnemyEtis-1766");
				break;
			}
			case 34780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001736);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001766, EnemyEtis, "EnemyEtis-1767");
				break;
			}
			case 34800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001737);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001767, EnemyEtis, "EnemyEtis-1768");
				break;
			}
			case 34820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001738);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001768, EnemyEtis, "EnemyEtis-1769");
				break;
			}
			case 34840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001739);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001769, EnemyEtis, "EnemyEtis-1770");
				break;
			}
			case 34860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001740);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001770, EnemyEtis, "EnemyEtis-1771");
				break;
			}
			case 34880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001741);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001771, EnemyEtis, "EnemyEtis-1772");
				break;
			}
			case 34900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001742);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001772, EnemyEtis, "EnemyEtis-1773");
				break;
			}
			case 34920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001743);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001773, EnemyEtis, "EnemyEtis-1774");
				break;
			}
			case 34940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001744);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001774, EnemyEtis, "EnemyEtis-1775");
				break;
			}
			case 34960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001745);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001775, EnemyEtis, "EnemyEtis-1776");
				break;
			}
			case 34980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001746);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001776, EnemyEtis, "EnemyEtis-1777");
				break;
			}
			case 35000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001747);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001777, EnemyEtis, "EnemyEtis-1778");
				break;
			}
			case 35020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001748);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001778, EnemyEtis, "EnemyEtis-1779");
				break;
			}
			case 35040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001749);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001779, EnemyEtis, "EnemyEtis-1780");
				break;
			}
			case 35060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001750);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001780, EnemyEtis, "EnemyEtis-1781");
				break;
			}
			case 35080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001751);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001781, EnemyEtis, "EnemyEtis-1782");
				break;
			}
			case 35100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001752);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001782, EnemyEtis, "EnemyEtis-1783");
				break;
			}
			case 35120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001753);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001783, EnemyEtis, "EnemyEtis-1784");
				break;
			}
			case 35140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001754);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001784, EnemyEtis, "EnemyEtis-1785");
				break;
			}
			case 35160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001755);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001785, EnemyEtis, "EnemyEtis-1786");
				break;
			}
			case 35180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001756);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001786, EnemyEtis, "EnemyEtis-1787");
				break;
			}
			case 35200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001757);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001787, EnemyEtis, "EnemyEtis-1788");
				break;
			}
			case 35220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001758);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001788, EnemyEtis, "EnemyEtis-1789");
				break;
			}
			case 35240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001759);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001789, EnemyEtis, "EnemyEtis-1790");
				break;
			}
			case 35260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001760);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001790, EnemyEtis, "EnemyEtis-1791");
				break;
			}
			case 35280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001761);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001791, EnemyEtis, "EnemyEtis-1792");
				break;
			}
			case 35300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001762);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001792, EnemyEtis, "EnemyEtis-1793");
				break;
			}
			case 35320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001763);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001793, EnemyEtis, "EnemyEtis-1794");
				break;
			}
			case 35340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001764);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001794, EnemyEtis, "EnemyEtis-1795");
				break;
			}
			case 35360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001765);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001795, EnemyEtis, "EnemyEtis-1796");
				break;
			}
			case 35380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001766);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001796, EnemyEtis, "EnemyEtis-1797");
				break;
			}
			case 35400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001767);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001797, EnemyEtis, "EnemyEtis-1798");
				break;
			}
			case 35420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001768);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001798, EnemyEtis, "EnemyEtis-1799");
				break;
			}
			case 35440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001769);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001799, EnemyEtis, "EnemyEtis-1800");
				break;
			}
			case 35460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001770);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001800, EnemyEtis, "EnemyEtis-1801");
				break;
			}
			case 35480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001771);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001801, EnemyEtis, "EnemyEtis-1802");
				break;
			}
			case 35500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001772);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001802, EnemyEtis, "EnemyEtis-1803");
				break;
			}
			case 35520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001773);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001803, EnemyEtis, "EnemyEtis-1804");
				break;
			}
			case 35540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001774);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001804, EnemyEtis, "EnemyEtis-1805");
				break;
			}
			case 35560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001775);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001805, EnemyEtis, "EnemyEtis-1806");
				break;
			}
			case 35580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001776);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001806, EnemyEtis, "EnemyEtis-1807");
				break;
			}
			case 35600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001777);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001807, EnemyEtis, "EnemyEtis-1808");
				break;
			}
			case 35620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001778);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001808, EnemyEtis, "EnemyEtis-1809");
				break;
			}
			case 35640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001779);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001809, EnemyEtis, "EnemyEtis-1810");
				break;
			}
			case 35660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001780);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001810, EnemyEtis, "EnemyEtis-1811");
				break;
			}
			case 35680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001781);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001811, EnemyEtis, "EnemyEtis-1812");
				break;
			}
			case 35700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001782);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001812, EnemyEtis, "EnemyEtis-1813");
				break;
			}
			case 35720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001783);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001813, EnemyEtis, "EnemyEtis-1814");
				break;
			}
			case 35740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001784);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001814, EnemyEtis, "EnemyEtis-1815");
				break;
			}
			case 35760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001785);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001815, EnemyEtis, "EnemyEtis-1816");
				break;
			}
			case 35780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001786);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001816, EnemyEtis, "EnemyEtis-1817");
				break;
			}
			case 35800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001787);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001817, EnemyEtis, "EnemyEtis-1818");
				break;
			}
			case 35820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001788);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001818, EnemyEtis, "EnemyEtis-1819");
				break;
			}
			case 35840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001789);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001819, EnemyEtis, "EnemyEtis-1820");
				break;
			}
			case 35860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001790);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001820, EnemyEtis, "EnemyEtis-1821");
				break;
			}
			case 35880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001791);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001821, EnemyEtis, "EnemyEtis-1822");
				break;
			}
			case 35900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001792);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001822, EnemyEtis, "EnemyEtis-1823");
				break;
			}
			case 35920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001793);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001823, EnemyEtis, "EnemyEtis-1824");
				break;
			}
			case 35940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001794);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001824, EnemyEtis, "EnemyEtis-1825");
				break;
			}
			case 35960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001795);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001825, EnemyEtis, "EnemyEtis-1826");
				break;
			}
			case 35980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001796);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001826, EnemyEtis, "EnemyEtis-1827");
				break;
			}
			case 36000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001797);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001827, EnemyEtis, "EnemyEtis-1828");
				break;
			}
			case 36020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001798);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001828, EnemyEtis, "EnemyEtis-1829");
				break;
			}
			case 36040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001799);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001829, EnemyEtis, "EnemyEtis-1830");
				break;
			}
			case 36060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001800);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001830, EnemyEtis, "EnemyEtis-1831");
				break;
			}
			case 36080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001801);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001831, EnemyEtis, "EnemyEtis-1832");
				break;
			}
			case 36100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001802);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001832, EnemyEtis, "EnemyEtis-1833");
				break;
			}
			case 36120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001803);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001833, EnemyEtis, "EnemyEtis-1834");
				break;
			}
			case 36140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001804);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001834, EnemyEtis, "EnemyEtis-1835");
				break;
			}
			case 36160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001805);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001835, EnemyEtis, "EnemyEtis-1836");
				break;
			}
			case 36180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001806);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001836, EnemyEtis, "EnemyEtis-1837");
				break;
			}
			case 36200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001807);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001837, EnemyEtis, "EnemyEtis-1838");
				break;
			}
			case 36220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001808);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001838, EnemyEtis, "EnemyEtis-1839");
				break;
			}
			case 36240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001809);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001839, EnemyEtis, "EnemyEtis-1840");
				break;
			}
			case 36260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001810);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001840, EnemyEtis, "EnemyEtis-1841");
				break;
			}
			case 36280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001811);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001841, EnemyEtis, "EnemyEtis-1842");
				break;
			}
			case 36300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001812);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001842, EnemyEtis, "EnemyEtis-1843");
				break;
			}
			case 36320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001813);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001843, EnemyEtis, "EnemyEtis-1844");
				break;
			}
			case 36340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001814);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001844, EnemyEtis, "EnemyEtis-1845");
				break;
			}
			case 36360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001815);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001845, EnemyEtis, "EnemyEtis-1846");
				break;
			}
			case 36380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001816);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001846, EnemyEtis, "EnemyEtis-1847");
				break;
			}
			case 36400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001817);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001847, EnemyEtis, "EnemyEtis-1848");
				break;
			}
			case 36420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001818);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001848, EnemyEtis, "EnemyEtis-1849");
				break;
			}
			case 36440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001819);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001849, EnemyEtis, "EnemyEtis-1850");
				break;
			}
			case 36460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001820);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001850, EnemyEtis, "EnemyEtis-1851");
				break;
			}
			case 36480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001821);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001851, EnemyEtis, "EnemyEtis-1852");
				break;
			}
			case 36500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001822);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001852, EnemyEtis, "EnemyEtis-1853");
				break;
			}
			case 36520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001823);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001853, EnemyEtis, "EnemyEtis-1854");
				break;
			}
			case 36540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001824);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001854, EnemyEtis, "EnemyEtis-1855");
				break;
			}
			case 36560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001825);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001855, EnemyEtis, "EnemyEtis-1856");
				break;
			}
			case 36580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001826);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001856, EnemyEtis, "EnemyEtis-1857");
				break;
			}
			case 36600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001827);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001857, EnemyEtis, "EnemyEtis-1858");
				break;
			}
			case 36620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001828);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001858, EnemyEtis, "EnemyEtis-1859");
				break;
			}
			case 36640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001829);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001859, EnemyEtis, "EnemyEtis-1860");
				break;
			}
			case 36660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001830);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001860, EnemyEtis, "EnemyEtis-1861");
				break;
			}
			case 36680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001831);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001861, EnemyEtis, "EnemyEtis-1862");
				break;
			}
			case 36700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001832);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001862, EnemyEtis, "EnemyEtis-1863");
				break;
			}
			case 36720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001833);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001863, EnemyEtis, "EnemyEtis-1864");
				break;
			}
			case 36740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001834);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001864, EnemyEtis, "EnemyEtis-1865");
				break;
			}
			case 36760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001835);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001865, EnemyEtis, "EnemyEtis-1866");
				break;
			}
			case 36780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001836);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001866, EnemyEtis, "EnemyEtis-1867");
				break;
			}
			case 36800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001837);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001867, EnemyEtis, "EnemyEtis-1868");
				break;
			}
			case 36820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001838);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001868, EnemyEtis, "EnemyEtis-1869");
				break;
			}
			case 36840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001839);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001869, EnemyEtis, "EnemyEtis-1870");
				break;
			}
			case 36860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001840);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001870, EnemyEtis, "EnemyEtis-1871");
				break;
			}
			case 36880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001841);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001871, EnemyEtis, "EnemyEtis-1872");
				break;
			}
			case 36900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001842);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001872, EnemyEtis, "EnemyEtis-1873");
				break;
			}
			case 36920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001843);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001873, EnemyEtis, "EnemyEtis-1874");
				break;
			}
			case 36940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001844);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001874, EnemyEtis, "EnemyEtis-1875");
				break;
			}
			case 36960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001845);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001875, EnemyEtis, "EnemyEtis-1876");
				break;
			}
			case 36980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001846);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001876, EnemyEtis, "EnemyEtis-1877");
				break;
			}
			case 37000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001847);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001877, EnemyEtis, "EnemyEtis-1878");
				break;
			}
			case 37020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001848);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001878, EnemyEtis, "EnemyEtis-1879");
				break;
			}
			case 37040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001849);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001879, EnemyEtis, "EnemyEtis-1880");
				break;
			}
			case 37060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001850);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001880, EnemyEtis, "EnemyEtis-1881");
				break;
			}
			case 37080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001851);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001881, EnemyEtis, "EnemyEtis-1882");
				break;
			}
			case 37100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001852);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001882, EnemyEtis, "EnemyEtis-1883");
				break;
			}
			case 37120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001853);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001883, EnemyEtis, "EnemyEtis-1884");
				break;
			}
			case 37140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001854);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001884, EnemyEtis, "EnemyEtis-1885");
				break;
			}
			case 37160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001855);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001885, EnemyEtis, "EnemyEtis-1886");
				break;
			}
			case 37180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001856);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001886, EnemyEtis, "EnemyEtis-1887");
				break;
			}
			case 37200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001857);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001887, EnemyEtis, "EnemyEtis-1888");
				break;
			}
			case 37220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001858);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001888, EnemyEtis, "EnemyEtis-1889");
				break;
			}
			case 37240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001859);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001889, EnemyEtis, "EnemyEtis-1890");
				break;
			}
			case 37260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001860);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001890, EnemyEtis, "EnemyEtis-1891");
				break;
			}
			case 37280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001861);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001891, EnemyEtis, "EnemyEtis-1892");
				break;
			}
			case 37300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001862);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001892, EnemyEtis, "EnemyEtis-1893");
				break;
			}
			case 37320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001863);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001893, EnemyEtis, "EnemyEtis-1894");
				break;
			}
			case 37340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001864);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001894, EnemyEtis, "EnemyEtis-1895");
				break;
			}
			case 37360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001865);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001895, EnemyEtis, "EnemyEtis-1896");
				break;
			}
			case 37380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001866);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001896, EnemyEtis, "EnemyEtis-1897");
				break;
			}
			case 37400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001867);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001897, EnemyEtis, "EnemyEtis-1898");
				break;
			}
			case 37420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001868);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001898, EnemyEtis, "EnemyEtis-1899");
				break;
			}
			case 37440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001869);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001899, EnemyEtis, "EnemyEtis-1900");
				break;
			}
			case 37460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001870);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001900, EnemyEtis, "EnemyEtis-1901");
				break;
			}
			case 37480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001871);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001901, EnemyEtis, "EnemyEtis-1902");
				break;
			}
			case 37500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001872);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001902, EnemyEtis, "EnemyEtis-1903");
				break;
			}
			case 37520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001873);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001903, EnemyEtis, "EnemyEtis-1904");
				break;
			}
			case 37540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001874);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001904, EnemyEtis, "EnemyEtis-1905");
				break;
			}
			case 37560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001875);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001905, EnemyEtis, "EnemyEtis-1906");
				break;
			}
			case 37580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001876);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001906, EnemyEtis, "EnemyEtis-1907");
				break;
			}
			case 37600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001877);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001907, EnemyEtis, "EnemyEtis-1908");
				break;
			}
			case 37620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001878);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001908, EnemyEtis, "EnemyEtis-1909");
				break;
			}
			case 37640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001879);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001909, EnemyEtis, "EnemyEtis-1910");
				break;
			}
			case 37660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001880);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001910, EnemyEtis, "EnemyEtis-1911");
				break;
			}
			case 37680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001881);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001911, EnemyEtis, "EnemyEtis-1912");
				break;
			}
			case 37700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001882);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001912, EnemyEtis, "EnemyEtis-1913");
				break;
			}
			case 37720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001883);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001913, EnemyEtis, "EnemyEtis-1914");
				break;
			}
			case 37740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001884);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001914, EnemyEtis, "EnemyEtis-1915");
				break;
			}
			case 37760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001885);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001915, EnemyEtis, "EnemyEtis-1916");
				break;
			}
			case 37780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001886);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001916, EnemyEtis, "EnemyEtis-1917");
				break;
			}
			case 37800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001887);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001917, EnemyEtis, "EnemyEtis-1918");
				break;
			}
			case 37820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001888);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001918, EnemyEtis, "EnemyEtis-1919");
				break;
			}
			case 37840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001889);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001919, EnemyEtis, "EnemyEtis-1920");
				break;
			}
			case 37860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001890);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001920, EnemyEtis, "EnemyEtis-1921");
				break;
			}
			case 37880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001891);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001921, EnemyEtis, "EnemyEtis-1922");
				break;
			}
			case 37900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001892);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001922, EnemyEtis, "EnemyEtis-1923");
				break;
			}
			case 37920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001893);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001923, EnemyEtis, "EnemyEtis-1924");
				break;
			}
			case 37940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001894);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001924, EnemyEtis, "EnemyEtis-1925");
				break;
			}
			case 37960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001895);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001925, EnemyEtis, "EnemyEtis-1926");
				break;
			}
			case 37980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001896);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001926, EnemyEtis, "EnemyEtis-1927");
				break;
			}
			case 38000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001897);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001927, EnemyEtis, "EnemyEtis-1928");
				break;
			}
			case 38020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001898);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001928, EnemyEtis, "EnemyEtis-1929");
				break;
			}
			case 38040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001899);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001929, EnemyEtis, "EnemyEtis-1930");
				break;
			}
			case 38060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001900);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001930, EnemyEtis, "EnemyEtis-1931");
				break;
			}
			case 38080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001901);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001931, EnemyEtis, "EnemyEtis-1932");
				break;
			}
			case 38100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001902);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001932, EnemyEtis, "EnemyEtis-1933");
				break;
			}
			case 38120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001903);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001933, EnemyEtis, "EnemyEtis-1934");
				break;
			}
			case 38140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001904);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001934, EnemyEtis, "EnemyEtis-1935");
				break;
			}
			case 38160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001905);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001935, EnemyEtis, "EnemyEtis-1936");
				break;
			}
			case 38180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001906);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001936, EnemyEtis, "EnemyEtis-1937");
				break;
			}
			case 38200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001907);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001937, EnemyEtis, "EnemyEtis-1938");
				break;
			}
			case 38220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001908);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001938, EnemyEtis, "EnemyEtis-1939");
				break;
			}
			case 38240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001909);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001939, EnemyEtis, "EnemyEtis-1940");
				break;
			}
			case 38260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001910);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001940, EnemyEtis, "EnemyEtis-1941");
				break;
			}
			case 38280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001911);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001941, EnemyEtis, "EnemyEtis-1942");
				break;
			}
			case 38300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001912);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001942, EnemyEtis, "EnemyEtis-1943");
				break;
			}
			case 38320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001913);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001943, EnemyEtis, "EnemyEtis-1944");
				break;
			}
			case 38340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001914);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001944, EnemyEtis, "EnemyEtis-1945");
				break;
			}
			case 38360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001915);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001945, EnemyEtis, "EnemyEtis-1946");
				break;
			}
			case 38380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001916);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001946, EnemyEtis, "EnemyEtis-1947");
				break;
			}
			case 38400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001917);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001947, EnemyEtis, "EnemyEtis-1948");
				break;
			}
			case 38420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001918);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001948, EnemyEtis, "EnemyEtis-1949");
				break;
			}
			case 38440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001919);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001949, EnemyEtis, "EnemyEtis-1950");
				break;
			}
			case 38460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001920);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001950, EnemyEtis, "EnemyEtis-1951");
				break;
			}
			case 38480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001921);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001951, EnemyEtis, "EnemyEtis-1952");
				break;
			}
			case 38500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001922);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001952, EnemyEtis, "EnemyEtis-1953");
				break;
			}
			case 38520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001923);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001953, EnemyEtis, "EnemyEtis-1954");
				break;
			}
			case 38540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001924);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001954, EnemyEtis, "EnemyEtis-1955");
				break;
			}
			case 38560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001925);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001955, EnemyEtis, "EnemyEtis-1956");
				break;
			}
			case 38580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001926);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001956, EnemyEtis, "EnemyEtis-1957");
				break;
			}
			case 38600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001927);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001957, EnemyEtis, "EnemyEtis-1958");
				break;
			}
			case 38620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001928);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001958, EnemyEtis, "EnemyEtis-1959");
				break;
			}
			case 38640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001929);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001959, EnemyEtis, "EnemyEtis-1960");
				break;
			}
			case 38660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001930);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001960, EnemyEtis, "EnemyEtis-1961");
				break;
			}
			case 38680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001931);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001961, EnemyEtis, "EnemyEtis-1962");
				break;
			}
			case 38700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001932);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001962, EnemyEtis, "EnemyEtis-1963");
				break;
			}
			case 38720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001933);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001963, EnemyEtis, "EnemyEtis-1964");
				break;
			}
			case 38740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001934);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001964, EnemyEtis, "EnemyEtis-1965");
				break;
			}
			case 38760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001935);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001965, EnemyEtis, "EnemyEtis-1966");
				break;
			}
			case 38780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001936);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001966, EnemyEtis, "EnemyEtis-1967");
				break;
			}
			case 38800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001937);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001967, EnemyEtis, "EnemyEtis-1968");
				break;
			}
			case 38820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001938);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001968, EnemyEtis, "EnemyEtis-1969");
				break;
			}
			case 38840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001939);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001969, EnemyEtis, "EnemyEtis-1970");
				break;
			}
			case 38860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001940);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001970, EnemyEtis, "EnemyEtis-1971");
				break;
			}
			case 38880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001941);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001971, EnemyEtis, "EnemyEtis-1972");
				break;
			}
			case 38900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001942);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001972, EnemyEtis, "EnemyEtis-1973");
				break;
			}
			case 38920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001943);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001973, EnemyEtis, "EnemyEtis-1974");
				break;
			}
			case 38940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001944);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001974, EnemyEtis, "EnemyEtis-1975");
				break;
			}
			case 38960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001945);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001975, EnemyEtis, "EnemyEtis-1976");
				break;
			}
			case 38980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001946);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001976, EnemyEtis, "EnemyEtis-1977");
				break;
			}
			case 39000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001947);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001977, EnemyEtis, "EnemyEtis-1978");
				break;
			}
			case 39020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001948);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001978, EnemyEtis, "EnemyEtis-1979");
				break;
			}
			case 39040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001949);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001979, EnemyEtis, "EnemyEtis-1980");
				break;
			}
			case 39060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001950);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001980, EnemyEtis, "EnemyEtis-1981");
				break;
			}
			case 39080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001951);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001981, EnemyEtis, "EnemyEtis-1982");
				break;
			}
			case 39100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001952);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001982, EnemyEtis, "EnemyEtis-1983");
				break;
			}
			case 39120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001953);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001983, EnemyEtis, "EnemyEtis-1984");
				break;
			}
			case 39140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001954);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001984, EnemyEtis, "EnemyEtis-1985");
				break;
			}
			case 39160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001955);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001985, EnemyEtis, "EnemyEtis-1986");
				break;
			}
			case 39180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001956);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001986, EnemyEtis, "EnemyEtis-1987");
				break;
			}
			case 39200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001957);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001987, EnemyEtis, "EnemyEtis-1988");
				break;
			}
			case 39220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001958);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001988, EnemyEtis, "EnemyEtis-1989");
				break;
			}
			case 39240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001959);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001989, EnemyEtis, "EnemyEtis-1990");
				break;
			}
			case 39260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001960);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001990, EnemyEtis, "EnemyEtis-1991");
				break;
			}
			case 39280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001961);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001991, EnemyEtis, "EnemyEtis-1992");
				break;
			}
			case 39300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001962);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001992, EnemyEtis, "EnemyEtis-1993");
				break;
			}
			case 39320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001963);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001993, EnemyEtis, "EnemyEtis-1994");
				break;
			}
			case 39340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001964);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001994, EnemyEtis, "EnemyEtis-1995");
				break;
			}
			case 39360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001965);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001995, EnemyEtis, "EnemyEtis-1996");
				break;
			}
			case 39380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001966);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001996, EnemyEtis, "EnemyEtis-1997");
				break;
			}
			case 39400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001967);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001997, EnemyEtis, "EnemyEtis-1998");
				break;
			}
			case 39420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001968);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001998, EnemyEtis, "EnemyEtis-1999");
				break;
			}
			case 39440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001969);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001999, EnemyEtis, "EnemyEtis-2000");
				break;
			}
			case 39460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001970);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002000, EnemyEtis, "EnemyEtis-2001");
				break;
			}
			case 39480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001971);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002001, EnemyEtis, "EnemyEtis-2002");
				break;
			}
			case 39500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001972);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002002, EnemyEtis, "EnemyEtis-2003");
				break;
			}
			case 39520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001973);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002003, EnemyEtis, "EnemyEtis-2004");
				break;
			}
			case 39540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001974);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002004, EnemyEtis, "EnemyEtis-2005");
				break;
			}
			case 39560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001975);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002005, EnemyEtis, "EnemyEtis-2006");
				break;
			}
			case 39580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001976);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002006, EnemyEtis, "EnemyEtis-2007");
				break;
			}
			case 39600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001977);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002007, EnemyEtis, "EnemyEtis-2008");
				break;
			}
			case 39620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001978);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002008, EnemyEtis, "EnemyEtis-2009");
				break;
			}
			case 39640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001979);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002009, EnemyEtis, "EnemyEtis-2010");
				break;
			}
			case 39660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001980);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002010, EnemyEtis, "EnemyEtis-2011");
				break;
			}
			case 39680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001981);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002011, EnemyEtis, "EnemyEtis-2012");
				break;
			}
			case 39700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001982);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002012, EnemyEtis, "EnemyEtis-2013");
				break;
			}
			case 39720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001983);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002013, EnemyEtis, "EnemyEtis-2014");
				break;
			}
			case 39740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001984);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002014, EnemyEtis, "EnemyEtis-2015");
				break;
			}
			case 39760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001985);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002015, EnemyEtis, "EnemyEtis-2016");
				break;
			}
			case 39780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001986);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002016, EnemyEtis, "EnemyEtis-2017");
				break;
			}
			case 39800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001987);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002017, EnemyEtis, "EnemyEtis-2018");
				break;
			}
			case 39820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001988);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002018, EnemyEtis, "EnemyEtis-2019");
				break;
			}
			case 39840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001989);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002019, EnemyEtis, "EnemyEtis-2020");
				break;
			}
			case 39860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001990);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002020, EnemyEtis, "EnemyEtis-2021");
				break;
			}
			case 39880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001991);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002021, EnemyEtis, "EnemyEtis-2022");
				break;
			}
			case 39900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001992);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002022, EnemyEtis, "EnemyEtis-2023");
				break;
			}
			case 39920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001993);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002023, EnemyEtis, "EnemyEtis-2024");
				break;
			}
			case 39940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001994);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002024, EnemyEtis, "EnemyEtis-2025");
				break;
			}
			case 39960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001995);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002025, EnemyEtis, "EnemyEtis-2026");
				break;
			}
			case 39980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001996);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002026, EnemyEtis, "EnemyEtis-2027");
				break;
			}
			case 40000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001997);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002027, EnemyEtis, "EnemyEtis-2028");
				break;
			}
			case 40020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001998);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002028, EnemyEtis, "EnemyEtis-2029");
				break;
			}
			case 40040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001999);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002029, EnemyEtis, "EnemyEtis-2030");
				break;
			}
			case 40060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002000);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002030, EnemyEtis, "EnemyEtis-2031");
				break;
			}
			case 40080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002001);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002031, EnemyEtis, "EnemyEtis-2032");
				break;
			}
			case 40100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002002);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002032, EnemyEtis, "EnemyEtis-2033");
				break;
			}
			case 40120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002003);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002033, EnemyEtis, "EnemyEtis-2034");
				break;
			}
			case 40140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002004);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002034, EnemyEtis, "EnemyEtis-2035");
				break;
			}
			case 40160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002005);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002035, EnemyEtis, "EnemyEtis-2036");
				break;
			}
			case 40180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002006);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002036, EnemyEtis, "EnemyEtis-2037");
				break;
			}
			case 40200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002007);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002037, EnemyEtis, "EnemyEtis-2038");
				break;
			}
			case 40220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002008);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002038, EnemyEtis, "EnemyEtis-2039");
				break;
			}
			case 40240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002009);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002039, EnemyEtis, "EnemyEtis-2040");
				break;
			}
			case 40260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002010);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002040, EnemyEtis, "EnemyEtis-2041");
				break;
			}
			case 40280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002011);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002041, EnemyEtis, "EnemyEtis-2042");
				break;
			}
			case 40300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002012);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002042, EnemyEtis, "EnemyEtis-2043");
				break;
			}
			case 40320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002013);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002043, EnemyEtis, "EnemyEtis-2044");
				break;
			}
			case 40340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002014);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002044, EnemyEtis, "EnemyEtis-2045");
				break;
			}
			case 40360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002015);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002045, EnemyEtis, "EnemyEtis-2046");
				break;
			}
			case 40380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002016);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002046, EnemyEtis, "EnemyEtis-2047");
				break;
			}
			case 40400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002017);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002047, EnemyEtis, "EnemyEtis-2048");
				break;
			}
			case 40420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002018);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002048, EnemyEtis, "EnemyEtis-2049");
				break;
			}
			case 40440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002019);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002049, EnemyEtis, "EnemyEtis-2050");
				break;
			}
			case 40460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002020);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002050, EnemyEtis, "EnemyEtis-2051");
				break;
			}
			case 40480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002021);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002051, EnemyEtis, "EnemyEtis-2052");
				break;
			}
			case 40500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002022);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002052, EnemyEtis, "EnemyEtis-2053");
				break;
			}
			case 40520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002023);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002053, EnemyEtis, "EnemyEtis-2054");
				break;
			}
			case 40540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002024);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002054, EnemyEtis, "EnemyEtis-2055");
				break;
			}
			case 40560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002025);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002055, EnemyEtis, "EnemyEtis-2056");
				break;
			}
			case 40580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002026);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002056, EnemyEtis, "EnemyEtis-2057");
				break;
			}
			case 40600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002027);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002057, EnemyEtis, "EnemyEtis-2058");
				break;
			}
			case 40620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002028);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002058, EnemyEtis, "EnemyEtis-2059");
				break;
			}
			case 40640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002029);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002059, EnemyEtis, "EnemyEtis-2060");
				break;
			}
			case 40660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002030);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002060, EnemyEtis, "EnemyEtis-2061");
				break;
			}
			case 40680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002031);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002061, EnemyEtis, "EnemyEtis-2062");
				break;
			}
			case 40700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002032);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002062, EnemyEtis, "EnemyEtis-2063");
				break;
			}
			case 40720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002033);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002063, EnemyEtis, "EnemyEtis-2064");
				break;
			}
			case 40740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002034);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002064, EnemyEtis, "EnemyEtis-2065");
				break;
			}
			case 40760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002035);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002065, EnemyEtis, "EnemyEtis-2066");
				break;
			}
			case 40780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002036);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002066, EnemyEtis, "EnemyEtis-2067");
				break;
			}
			case 40800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002037);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002067, EnemyEtis, "EnemyEtis-2068");
				break;
			}
			case 40820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002038);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002068, EnemyEtis, "EnemyEtis-2069");
				break;
			}
			case 40840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002039);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002069, EnemyEtis, "EnemyEtis-2070");
				break;
			}
			case 40860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002040);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002070, EnemyEtis, "EnemyEtis-2071");
				break;
			}
			case 40880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002041);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002071, EnemyEtis, "EnemyEtis-2072");
				break;
			}
			case 40900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002042);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002072, EnemyEtis, "EnemyEtis-2073");
				break;
			}
			case 40920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002043);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002073, EnemyEtis, "EnemyEtis-2074");
				break;
			}
			case 40940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002044);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002074, EnemyEtis, "EnemyEtis-2075");
				break;
			}
			case 40960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002045);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002075, EnemyEtis, "EnemyEtis-2076");
				break;
			}
			case 40980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002046);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002076, EnemyEtis, "EnemyEtis-2077");
				break;
			}
			case 41000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002047);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002077, EnemyEtis, "EnemyEtis-2078");
				break;
			}
			case 41020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002048);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002078, EnemyEtis, "EnemyEtis-2079");
				break;
			}
			case 41040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002049);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002079, EnemyEtis, "EnemyEtis-2080");
				break;
			}
			case 41060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002050);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002080, EnemyEtis, "EnemyEtis-2081");
				break;
			}
			case 41080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002051);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002081, EnemyEtis, "EnemyEtis-2082");
				break;
			}
			case 41100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002052);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002082, EnemyEtis, "EnemyEtis-2083");
				break;
			}
			case 41120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002053);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002083, EnemyEtis, "EnemyEtis-2084");
				break;
			}
			case 41140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002054);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002084, EnemyEtis, "EnemyEtis-2085");
				break;
			}
			case 41160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002055);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002085, EnemyEtis, "EnemyEtis-2086");
				break;
			}
			case 41180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002056);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002086, EnemyEtis, "EnemyEtis-2087");
				break;
			}
			case 41200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002057);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002087, EnemyEtis, "EnemyEtis-2088");
				break;
			}
			case 41220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002058);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002088, EnemyEtis, "EnemyEtis-2089");
				break;
			}
			case 41240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002059);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002089, EnemyEtis, "EnemyEtis-2090");
				break;
			}
			case 41260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002060);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002090, EnemyEtis, "EnemyEtis-2091");
				break;
			}
			case 41280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002061);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002091, EnemyEtis, "EnemyEtis-2092");
				break;
			}
			case 41300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002062);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002092, EnemyEtis, "EnemyEtis-2093");
				break;
			}
			case 41320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002063);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002093, EnemyEtis, "EnemyEtis-2094");
				break;
			}
			case 41340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002064);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002094, EnemyEtis, "EnemyEtis-2095");
				break;
			}
			case 41360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002065);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002095, EnemyEtis, "EnemyEtis-2096");
				break;
			}
			case 41380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002066);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002096, EnemyEtis, "EnemyEtis-2097");
				break;
			}
			case 41400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002067);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002097, EnemyEtis, "EnemyEtis-2098");
				break;
			}
			case 41420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002068);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002098, EnemyEtis, "EnemyEtis-2099");
				break;
			}
			case 41440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002069);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002099, EnemyEtis, "EnemyEtis-2100");
				break;
			}
			case 41460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002070);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002100, EnemyEtis, "EnemyEtis-2101");
				break;
			}
			case 41480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002071);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002101, EnemyEtis, "EnemyEtis-2102");
				break;
			}
			case 41500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002072);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002102, EnemyEtis, "EnemyEtis-2103");
				break;
			}
			case 41520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002073);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002103, EnemyEtis, "EnemyEtis-2104");
				break;
			}
			case 41540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002074);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002104, EnemyEtis, "EnemyEtis-2105");
				break;
			}
			case 41560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002075);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002105, EnemyEtis, "EnemyEtis-2106");
				break;
			}
			case 41580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002076);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002106, EnemyEtis, "EnemyEtis-2107");
				break;
			}
			case 41600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002077);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002107, EnemyEtis, "EnemyEtis-2108");
				break;
			}
			case 41620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002078);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002108, EnemyEtis, "EnemyEtis-2109");
				break;
			}
			case 41640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002079);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002109, EnemyEtis, "EnemyEtis-2110");
				break;
			}
			case 41660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002080);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002110, EnemyEtis, "EnemyEtis-2111");
				break;
			}
			case 41680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002081);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002111, EnemyEtis, "EnemyEtis-2112");
				break;
			}
			case 41700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002082);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002112, EnemyEtis, "EnemyEtis-2113");
				break;
			}
			case 41720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002083);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002113, EnemyEtis, "EnemyEtis-2114");
				break;
			}
			case 41740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002084);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002114, EnemyEtis, "EnemyEtis-2115");
				break;
			}
			case 41760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002085);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002115, EnemyEtis, "EnemyEtis-2116");
				break;
			}
			case 41780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002086);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002116, EnemyEtis, "EnemyEtis-2117");
				break;
			}
			case 41800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002087);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002117, EnemyEtis, "EnemyEtis-2118");
				break;
			}
			case 41820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002088);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002118, EnemyEtis, "EnemyEtis-2119");
				break;
			}
			case 41840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002089);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002119, EnemyEtis, "EnemyEtis-2120");
				break;
			}
			case 41860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002090);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002120, EnemyEtis, "EnemyEtis-2121");
				break;
			}
			case 41880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002091);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002121, EnemyEtis, "EnemyEtis-2122");
				break;
			}
			case 41900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002092);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002122, EnemyEtis, "EnemyEtis-2123");
				break;
			}
			case 41920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002093);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002123, EnemyEtis, "EnemyEtis-2124");
				break;
			}
			case 41940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002094);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002124, EnemyEtis, "EnemyEtis-2125");
				break;
			}
			case 41960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002095);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002125, EnemyEtis, "EnemyEtis-2126");
				break;
			}
			case 41980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002096);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002126, EnemyEtis, "EnemyEtis-2127");
				break;
			}
			case 42000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002097);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002127, EnemyEtis, "EnemyEtis-2128");
				break;
			}
			case 42020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002098);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002128, EnemyEtis, "EnemyEtis-2129");
				break;
			}
			case 42040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002099);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002129, EnemyEtis, "EnemyEtis-2130");
				break;
			}
			case 42060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002100);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002130, EnemyEtis, "EnemyEtis-2131");
				break;
			}
			case 42080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002101);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002131, EnemyEtis, "EnemyEtis-2132");
				break;
			}
			case 42100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002102);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002132, EnemyEtis, "EnemyEtis-2133");
				break;
			}
			case 42120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002103);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002133, EnemyEtis, "EnemyEtis-2134");
				break;
			}
			case 42140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002104);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002134, EnemyEtis, "EnemyEtis-2135");
				break;
			}
			case 42160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002105);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002135, EnemyEtis, "EnemyEtis-2136");
				break;
			}
			case 42180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002106);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002136, EnemyEtis, "EnemyEtis-2137");
				break;
			}
			case 42200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002107);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002137, EnemyEtis, "EnemyEtis-2138");
				break;
			}
			case 42220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002108);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002138, EnemyEtis, "EnemyEtis-2139");
				break;
			}
			case 42240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002109);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002139, EnemyEtis, "EnemyEtis-2140");
				break;
			}
			case 42260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002110);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002140, EnemyEtis, "EnemyEtis-2141");
				break;
			}
			case 42280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002111);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002141, EnemyEtis, "EnemyEtis-2142");
				break;
			}
			case 42300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002112);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002142, EnemyEtis, "EnemyEtis-2143");
				break;
			}
			case 42320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002113);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002143, EnemyEtis, "EnemyEtis-2144");
				break;
			}
			case 42340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002114);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002144, EnemyEtis, "EnemyEtis-2145");
				break;
			}
			case 42360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002115);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002145, EnemyEtis, "EnemyEtis-2146");
				break;
			}
			case 42380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002116);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002146, EnemyEtis, "EnemyEtis-2147");
				break;
			}
			case 42400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002117);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002147, EnemyEtis, "EnemyEtis-2148");
				break;
			}
			case 42420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002118);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002148, EnemyEtis, "EnemyEtis-2149");
				break;
			}
			case 42440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002119);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002149, EnemyEtis, "EnemyEtis-2150");
				break;
			}
			case 42460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002120);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002150, EnemyEtis, "EnemyEtis-2151");
				break;
			}
			case 42480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002121);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002151, EnemyEtis, "EnemyEtis-2152");
				break;
			}
			case 42500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002122);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002152, EnemyEtis, "EnemyEtis-2153");
				break;
			}
			case 42520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002123);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002153, EnemyEtis, "EnemyEtis-2154");
				break;
			}
			case 42540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002124);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002154, EnemyEtis, "EnemyEtis-2155");
				break;
			}
			case 42560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002125);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002155, EnemyEtis, "EnemyEtis-2156");
				break;
			}
			case 42580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002126);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002156, EnemyEtis, "EnemyEtis-2157");
				break;
			}
			case 42600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002127);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002157, EnemyEtis, "EnemyEtis-2158");
				break;
			}
			case 42620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002128);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002158, EnemyEtis, "EnemyEtis-2159");
				break;
			}
			case 42640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002129);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002159, EnemyEtis, "EnemyEtis-2160");
				break;
			}
			case 42660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002130);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002160, EnemyEtis, "EnemyEtis-2161");
				break;
			}
			case 42680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002131);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002161, EnemyEtis, "EnemyEtis-2162");
				break;
			}
			case 42700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002132);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002162, EnemyEtis, "EnemyEtis-2163");
				break;
			}
			case 42720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002133);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002163, EnemyEtis, "EnemyEtis-2164");
				break;
			}
			case 42740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002134);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002164, EnemyEtis, "EnemyEtis-2165");
				break;
			}
			case 42760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002135);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002165, EnemyEtis, "EnemyEtis-2166");
				break;
			}
			case 42780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002136);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002166, EnemyEtis, "EnemyEtis-2167");
				break;
			}
			case 42800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002137);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002167, EnemyEtis, "EnemyEtis-2168");
				break;
			}
			case 42820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002138);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002168, EnemyEtis, "EnemyEtis-2169");
				break;
			}
			case 42840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002139);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002169, EnemyEtis, "EnemyEtis-2170");
				break;
			}
			case 42860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002140);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002170, EnemyEtis, "EnemyEtis-2171");
				break;
			}
			case 42880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002141);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002171, EnemyEtis, "EnemyEtis-2172");
				break;
			}
			case 42900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002142);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002172, EnemyEtis, "EnemyEtis-2173");
				break;
			}
			case 42920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002143);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002173, EnemyEtis, "EnemyEtis-2174");
				break;
			}
			case 42940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002144);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002174, EnemyEtis, "EnemyEtis-2175");
				break;
			}
			case 42960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002145);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002175, EnemyEtis, "EnemyEtis-2176");
				break;
			}
			case 42980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002146);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002176, EnemyEtis, "EnemyEtis-2177");
				break;
			}
			case 43000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002147);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002177, EnemyEtis, "EnemyEtis-2178");
				break;
			}
			case 43020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002148);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002178, EnemyEtis, "EnemyEtis-2179");
				break;
			}
			case 43040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002149);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002179, EnemyEtis, "EnemyEtis-2180");
				break;
			}
			case 43060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002150);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002180, EnemyEtis, "EnemyEtis-2181");
				break;
			}
			case 43080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002151);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002181, EnemyEtis, "EnemyEtis-2182");
				break;
			}
			case 43100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002152);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002182, EnemyEtis, "EnemyEtis-2183");
				break;
			}
			case 43120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002153);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002183, EnemyEtis, "EnemyEtis-2184");
				break;
			}
			case 43140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002154);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002184, EnemyEtis, "EnemyEtis-2185");
				break;
			}
			case 43160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002155);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002185, EnemyEtis, "EnemyEtis-2186");
				break;
			}
			case 43180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002156);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002186, EnemyEtis, "EnemyEtis-2187");
				break;
			}
			case 43200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002157);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002187, EnemyEtis, "EnemyEtis-2188");
				break;
			}
			case 43220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002158);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002188, EnemyEtis, "EnemyEtis-2189");
				break;
			}
			case 43240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002159);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002189, EnemyEtis, "EnemyEtis-2190");
				break;
			}
			case 43260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002160);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002190, EnemyEtis, "EnemyEtis-2191");
				break;
			}
			case 43280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002161);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002191, EnemyEtis, "EnemyEtis-2192");
				break;
			}
			case 43300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002162);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002192, EnemyEtis, "EnemyEtis-2193");
				break;
			}
			case 43320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002163);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002193, EnemyEtis, "EnemyEtis-2194");
				break;
			}
			case 43340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002164);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002194, EnemyEtis, "EnemyEtis-2195");
				break;
			}
			case 43360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002165);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002195, EnemyEtis, "EnemyEtis-2196");
				break;
			}
			case 43380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002166);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002196, EnemyEtis, "EnemyEtis-2197");
				break;
			}
			case 43400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002167);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002197, EnemyEtis, "EnemyEtis-2198");
				break;
			}
			case 43420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002168);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002198, EnemyEtis, "EnemyEtis-2199");
				break;
			}
			case 43440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002169);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002199, EnemyEtis, "EnemyEtis-2200");
				break;
			}
			case 43460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002170);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002200, EnemyEtis, "EnemyEtis-2201");
				break;
			}
			case 43480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002171);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002201, EnemyEtis, "EnemyEtis-2202");
				break;
			}
			case 43500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002172);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002202, EnemyEtis, "EnemyEtis-2203");
				break;
			}
			case 43520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002173);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002203, EnemyEtis, "EnemyEtis-2204");
				break;
			}
			case 43540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002174);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002204, EnemyEtis, "EnemyEtis-2205");
				break;
			}
			case 43560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002175);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002205, EnemyEtis, "EnemyEtis-2206");
				break;
			}
			case 43580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002176);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002206, EnemyEtis, "EnemyEtis-2207");
				break;
			}
			case 43600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002177);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002207, EnemyEtis, "EnemyEtis-2208");
				break;
			}
			case 43620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002178);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002208, EnemyEtis, "EnemyEtis-2209");
				break;
			}
			case 43640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002179);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002209, EnemyEtis, "EnemyEtis-2210");
				break;
			}
			case 43660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002180);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002210, EnemyEtis, "EnemyEtis-2211");
				break;
			}
			case 43680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002181);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002211, EnemyEtis, "EnemyEtis-2212");
				break;
			}
			case 43700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002182);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002212, EnemyEtis, "EnemyEtis-2213");
				break;
			}
			case 43720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002183);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002213, EnemyEtis, "EnemyEtis-2214");
				break;
			}
			case 43740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002184);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002214, EnemyEtis, "EnemyEtis-2215");
				break;
			}
			case 43760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002185);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002215, EnemyEtis, "EnemyEtis-2216");
				break;
			}
			case 43780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002186);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002216, EnemyEtis, "EnemyEtis-2217");
				break;
			}
			case 43800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002187);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002217, EnemyEtis, "EnemyEtis-2218");
				break;
			}
			case 43820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002188);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002218, EnemyEtis, "EnemyEtis-2219");
				break;
			}
			case 43840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002189);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002219, EnemyEtis, "EnemyEtis-2220");
				break;
			}
			case 43860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002190);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002220, EnemyEtis, "EnemyEtis-2221");
				break;
			}
			case 43880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002191);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002221, EnemyEtis, "EnemyEtis-2222");
				break;
			}
			case 43900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002192);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002222, EnemyEtis, "EnemyEtis-2223");
				break;
			}
			case 43920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002193);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002223, EnemyEtis, "EnemyEtis-2224");
				break;
			}
			case 43940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002194);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002224, EnemyEtis, "EnemyEtis-2225");
				break;
			}
			case 43960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002195);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002225, EnemyEtis, "EnemyEtis-2226");
				break;
			}
			case 43980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002196);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002226, EnemyEtis, "EnemyEtis-2227");
				break;
			}
			case 44000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002197);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002227, EnemyEtis, "EnemyEtis-2228");
				break;
			}
			case 44020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002198);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002228, EnemyEtis, "EnemyEtis-2229");
				break;
			}
			case 44040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002199);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002229, EnemyEtis, "EnemyEtis-2230");
				break;
			}
			case 44060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002200);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002230, EnemyEtis, "EnemyEtis-2231");
				break;
			}
			case 44080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002201);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002231, EnemyEtis, "EnemyEtis-2232");
				break;
			}
			case 44100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002202);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002232, EnemyEtis, "EnemyEtis-2233");
				break;
			}
			case 44120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002203);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002233, EnemyEtis, "EnemyEtis-2234");
				break;
			}
			case 44140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002204);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002234, EnemyEtis, "EnemyEtis-2235");
				break;
			}
			case 44160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002205);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002235, EnemyEtis, "EnemyEtis-2236");
				break;
			}
			case 44180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002206);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002236, EnemyEtis, "EnemyEtis-2237");
				break;
			}
			case 44200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002207);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002237, EnemyEtis, "EnemyEtis-2238");
				break;
			}
			case 44220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002208);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002238, EnemyEtis, "EnemyEtis-2239");
				break;
			}
			case 44240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002209);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002239, EnemyEtis, "EnemyEtis-2240");
				break;
			}
			case 44260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002210);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002240, EnemyEtis, "EnemyEtis-2241");
				break;
			}
			case 44280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002211);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002241, EnemyEtis, "EnemyEtis-2242");
				break;
			}
			case 44300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002212);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002242, EnemyEtis, "EnemyEtis-2243");
				break;
			}
			case 44320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002213);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002243, EnemyEtis, "EnemyEtis-2244");
				break;
			}
			case 44340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002214);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002244, EnemyEtis, "EnemyEtis-2245");
				break;
			}
			case 44360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002215);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002245, EnemyEtis, "EnemyEtis-2246");
				break;
			}
			case 44380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002216);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002246, EnemyEtis, "EnemyEtis-2247");
				break;
			}
			case 44400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002217);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002247, EnemyEtis, "EnemyEtis-2248");
				break;
			}
			case 44420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002218);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002248, EnemyEtis, "EnemyEtis-2249");
				break;
			}
			case 44440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002219);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002249, EnemyEtis, "EnemyEtis-2250");
				break;
			}
			case 44460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002220);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002250, EnemyEtis, "EnemyEtis-2251");
				break;
			}
			case 44480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002221);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002251, EnemyEtis, "EnemyEtis-2252");
				break;
			}
			case 44500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002222);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002252, EnemyEtis, "EnemyEtis-2253");
				break;
			}
			case 44520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002223);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002253, EnemyEtis, "EnemyEtis-2254");
				break;
			}
			case 44540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002224);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002254, EnemyEtis, "EnemyEtis-2255");
				break;
			}
			case 44560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002225);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002255, EnemyEtis, "EnemyEtis-2256");
				break;
			}
			case 44580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002226);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002256, EnemyEtis, "EnemyEtis-2257");
				break;
			}
			case 44600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002227);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002257, EnemyEtis, "EnemyEtis-2258");
				break;
			}
			case 44620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002228);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002258, EnemyEtis, "EnemyEtis-2259");
				break;
			}
			case 44640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002229);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002259, EnemyEtis, "EnemyEtis-2260");
				break;
			}
			case 44660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002230);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002260, EnemyEtis, "EnemyEtis-2261");
				break;
			}
			case 44680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002231);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002261, EnemyEtis, "EnemyEtis-2262");
				break;
			}
			case 44700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002232);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002262, EnemyEtis, "EnemyEtis-2263");
				break;
			}
			case 44720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002233);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002263, EnemyEtis, "EnemyEtis-2264");
				break;
			}
			case 44740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002234);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002264, EnemyEtis, "EnemyEtis-2265");
				break;
			}
			case 44760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002235);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002265, EnemyEtis, "EnemyEtis-2266");
				break;
			}
			case 44780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002236);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002266, EnemyEtis, "EnemyEtis-2267");
				break;
			}
			case 44800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002237);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002267, EnemyEtis, "EnemyEtis-2268");
				break;
			}
			case 44820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002238);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002268, EnemyEtis, "EnemyEtis-2269");
				break;
			}
			case 44840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002239);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002269, EnemyEtis, "EnemyEtis-2270");
				break;
			}
			case 44860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002240);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002270, EnemyEtis, "EnemyEtis-2271");
				break;
			}
			case 44880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002241);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002271, EnemyEtis, "EnemyEtis-2272");
				break;
			}
			case 44900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002242);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002272, EnemyEtis, "EnemyEtis-2273");
				break;
			}
			case 44920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002243);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002273, EnemyEtis, "EnemyEtis-2274");
				break;
			}
			case 44940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002244);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002274, EnemyEtis, "EnemyEtis-2275");
				break;
			}
			case 44960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002245);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002275, EnemyEtis, "EnemyEtis-2276");
				break;
			}
			case 44980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002246);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002276, EnemyEtis, "EnemyEtis-2277");
				break;
			}
			case 45000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002247);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002277, EnemyEtis, "EnemyEtis-2278");
				break;
			}
			case 45020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002248);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002278, EnemyEtis, "EnemyEtis-2279");
				break;
			}
			case 45040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002249);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002279, EnemyEtis, "EnemyEtis-2280");
				break;
			}
			case 45060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002250);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002280, EnemyEtis, "EnemyEtis-2281");
				break;
			}
			case 45080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002251);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002281, EnemyEtis, "EnemyEtis-2282");
				break;
			}
			case 45100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002252);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002282, EnemyEtis, "EnemyEtis-2283");
				break;
			}
			case 45120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002253);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002283, EnemyEtis, "EnemyEtis-2284");
				break;
			}
			case 45140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002254);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002284, EnemyEtis, "EnemyEtis-2285");
				break;
			}
			case 45160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002255);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002285, EnemyEtis, "EnemyEtis-2286");
				break;
			}
			case 45180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002256);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002286, EnemyEtis, "EnemyEtis-2287");
				break;
			}
			case 45200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002257);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002287, EnemyEtis, "EnemyEtis-2288");
				break;
			}
			case 45220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002258);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002288, EnemyEtis, "EnemyEtis-2289");
				break;
			}
			case 45240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002259);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002289, EnemyEtis, "EnemyEtis-2290");
				break;
			}
			case 45260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002260);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002290, EnemyEtis, "EnemyEtis-2291");
				break;
			}
			case 45280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002261);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002291, EnemyEtis, "EnemyEtis-2292");
				break;
			}
			case 45300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002262);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002292, EnemyEtis, "EnemyEtis-2293");
				break;
			}
			case 45320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002263);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002293, EnemyEtis, "EnemyEtis-2294");
				break;
			}
			case 45340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002264);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002294, EnemyEtis, "EnemyEtis-2295");
				break;
			}
			case 45360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002265);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002295, EnemyEtis, "EnemyEtis-2296");
				break;
			}
			case 45380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002266);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002296, EnemyEtis, "EnemyEtis-2297");
				break;
			}
			case 45400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002267);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002297, EnemyEtis, "EnemyEtis-2298");
				break;
			}
			case 45420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002268);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002298, EnemyEtis, "EnemyEtis-2299");
				break;
			}
			case 45440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002269);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002299, EnemyEtis, "EnemyEtis-2300");
				break;
			}
			case 45460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002270);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002300, EnemyEtis, "EnemyEtis-2301");
				break;
			}
			case 45480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002271);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002301, EnemyEtis, "EnemyEtis-2302");
				break;
			}
			case 45500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002272);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002302, EnemyEtis, "EnemyEtis-2303");
				break;
			}
			case 45520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002273);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002303, EnemyEtis, "EnemyEtis-2304");
				break;
			}
			case 45540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002274);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002304, EnemyEtis, "EnemyEtis-2305");
				break;
			}
			case 45560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002275);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002305, EnemyEtis, "EnemyEtis-2306");
				break;
			}
			case 45580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002276);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002306, EnemyEtis, "EnemyEtis-2307");
				break;
			}
			case 45600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002277);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002307, EnemyEtis, "EnemyEtis-2308");
				break;
			}
			case 45620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002278);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002308, EnemyEtis, "EnemyEtis-2309");
				break;
			}
			case 45640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002279);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002309, EnemyEtis, "EnemyEtis-2310");
				break;
			}
			case 45660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002280);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002310, EnemyEtis, "EnemyEtis-2311");
				break;
			}
			case 45680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002281);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002311, EnemyEtis, "EnemyEtis-2312");
				break;
			}
			case 45700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002282);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002312, EnemyEtis, "EnemyEtis-2313");
				break;
			}
			case 45720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002283);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002313, EnemyEtis, "EnemyEtis-2314");
				break;
			}
			case 45740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002284);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002314, EnemyEtis, "EnemyEtis-2315");
				break;
			}
			case 45760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002285);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002315, EnemyEtis, "EnemyEtis-2316");
				break;
			}
			case 45780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002286);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002316, EnemyEtis, "EnemyEtis-2317");
				break;
			}
			case 45800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002287);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002317, EnemyEtis, "EnemyEtis-2318");
				break;
			}
			case 45820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002288);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002318, EnemyEtis, "EnemyEtis-2319");
				break;
			}
			case 45840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002289);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002319, EnemyEtis, "EnemyEtis-2320");
				break;
			}
			case 45860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002290);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002320, EnemyEtis, "EnemyEtis-2321");
				break;
			}
			case 45880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002291);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002321, EnemyEtis, "EnemyEtis-2322");
				break;
			}
			case 45900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002292);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002322, EnemyEtis, "EnemyEtis-2323");
				break;
			}
			case 45920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002293);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002323, EnemyEtis, "EnemyEtis-2324");
				break;
			}
			case 45940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002294);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002324, EnemyEtis, "EnemyEtis-2325");
				break;
			}
			case 45960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002295);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002325, EnemyEtis, "EnemyEtis-2326");
				break;
			}
			case 45980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002296);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002326, EnemyEtis, "EnemyEtis-2327");
				break;
			}
			case 46000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002297);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002327, EnemyEtis, "EnemyEtis-2328");
				break;
			}
			case 46020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002298);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002328, EnemyEtis, "EnemyEtis-2329");
				break;
			}
			case 46040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002299);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002329, EnemyEtis, "EnemyEtis-2330");
				break;
			}
			case 46060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002300);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002330, EnemyEtis, "EnemyEtis-2331");
				break;
			}
			case 46080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002301);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002331, EnemyEtis, "EnemyEtis-2332");
				break;
			}
			case 46100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002302);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002332, EnemyEtis, "EnemyEtis-2333");
				break;
			}
			case 46120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002303);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002333, EnemyEtis, "EnemyEtis-2334");
				break;
			}
			case 46140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002304);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002334, EnemyEtis, "EnemyEtis-2335");
				break;
			}
			case 46160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002305);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002335, EnemyEtis, "EnemyEtis-2336");
				break;
			}
			case 46180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002306);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002336, EnemyEtis, "EnemyEtis-2337");
				break;
			}
			case 46200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002307);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002337, EnemyEtis, "EnemyEtis-2338");
				break;
			}
			case 46220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002308);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002338, EnemyEtis, "EnemyEtis-2339");
				break;
			}
			case 46240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002309);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002339, EnemyEtis, "EnemyEtis-2340");
				break;
			}
			case 46260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002310);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002340, EnemyEtis, "EnemyEtis-2341");
				break;
			}
			case 46280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002311);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002341, EnemyEtis, "EnemyEtis-2342");
				break;
			}
			case 46300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002312);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002342, EnemyEtis, "EnemyEtis-2343");
				break;
			}
			case 46320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002313);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002343, EnemyEtis, "EnemyEtis-2344");
				break;
			}
			case 46340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002314);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002344, EnemyEtis, "EnemyEtis-2345");
				break;
			}
			case 46360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002315);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002345, EnemyEtis, "EnemyEtis-2346");
				break;
			}
			case 46380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002316);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002346, EnemyEtis, "EnemyEtis-2347");
				break;
			}
			case 46400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002317);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002347, EnemyEtis, "EnemyEtis-2348");
				break;
			}
			case 46420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002318);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002348, EnemyEtis, "EnemyEtis-2349");
				break;
			}
			case 46440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002319);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002349, EnemyEtis, "EnemyEtis-2350");
				break;
			}
			case 46460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002320);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002350, EnemyEtis, "EnemyEtis-2351");
				break;
			}
			case 46480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002321);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002351, EnemyEtis, "EnemyEtis-2352");
				break;
			}
			case 46500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002322);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002352, EnemyEtis, "EnemyEtis-2353");
				break;
			}
			case 46520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002323);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002353, EnemyEtis, "EnemyEtis-2354");
				break;
			}
			case 46540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002324);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002354, EnemyEtis, "EnemyEtis-2355");
				break;
			}
			case 46560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002325);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002355, EnemyEtis, "EnemyEtis-2356");
				break;
			}
			case 46580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002326);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002356, EnemyEtis, "EnemyEtis-2357");
				break;
			}
			case 46600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002327);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002357, EnemyEtis, "EnemyEtis-2358");
				break;
			}
			case 46620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002328);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002358, EnemyEtis, "EnemyEtis-2359");
				break;
			}
			case 46640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002329);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002359, EnemyEtis, "EnemyEtis-2360");
				break;
			}
			case 46660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002330);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002360, EnemyEtis, "EnemyEtis-2361");
				break;
			}
			case 46680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002331);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002361, EnemyEtis, "EnemyEtis-2362");
				break;
			}
			case 46700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002332);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002362, EnemyEtis, "EnemyEtis-2363");
				break;
			}
			case 46720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002333);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002363, EnemyEtis, "EnemyEtis-2364");
				break;
			}
			case 46740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002334);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002364, EnemyEtis, "EnemyEtis-2365");
				break;
			}
			case 46760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002335);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002365, EnemyEtis, "EnemyEtis-2366");
				break;
			}
			case 46780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002336);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002366, EnemyEtis, "EnemyEtis-2367");
				break;
			}
			case 46800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002337);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002367, EnemyEtis, "EnemyEtis-2368");
				break;
			}
			case 46820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002338);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002368, EnemyEtis, "EnemyEtis-2369");
				break;
			}
			case 46840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002339);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002369, EnemyEtis, "EnemyEtis-2370");
				break;
			}
			case 46860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002340);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002370, EnemyEtis, "EnemyEtis-2371");
				break;
			}
			case 46880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002341);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002371, EnemyEtis, "EnemyEtis-2372");
				break;
			}
			case 46900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002342);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002372, EnemyEtis, "EnemyEtis-2373");
				break;
			}
			case 46920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002343);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002373, EnemyEtis, "EnemyEtis-2374");
				break;
			}
			case 46940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002344);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002374, EnemyEtis, "EnemyEtis-2375");
				break;
			}
			case 46960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002345);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002375, EnemyEtis, "EnemyEtis-2376");
				break;
			}
			case 46980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002346);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002376, EnemyEtis, "EnemyEtis-2377");
				break;
			}
			case 47000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002347);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002377, EnemyEtis, "EnemyEtis-2378");
				break;
			}
			case 47020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002348);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002378, EnemyEtis, "EnemyEtis-2379");
				break;
			}
			case 47040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002349);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002379, EnemyEtis, "EnemyEtis-2380");
				break;
			}
			case 47060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002350);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002380, EnemyEtis, "EnemyEtis-2381");
				break;
			}
			case 47080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002351);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002381, EnemyEtis, "EnemyEtis-2382");
				break;
			}
			case 47100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002352);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002382, EnemyEtis, "EnemyEtis-2383");
				break;
			}
			case 47120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002353);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002383, EnemyEtis, "EnemyEtis-2384");
				break;
			}
			case 47140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002354);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002384, EnemyEtis, "EnemyEtis-2385");
				break;
			}
			case 47160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002355);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002385, EnemyEtis, "EnemyEtis-2386");
				break;
			}
			case 47180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002356);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002386, EnemyEtis, "EnemyEtis-2387");
				break;
			}
			case 47200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002357);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002387, EnemyEtis, "EnemyEtis-2388");
				break;
			}
			case 47220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002358);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002388, EnemyEtis, "EnemyEtis-2389");
				break;
			}
			case 47240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002359);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002389, EnemyEtis, "EnemyEtis-2390");
				break;
			}
			case 47260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002360);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002390, EnemyEtis, "EnemyEtis-2391");
				break;
			}
			case 47280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002361);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002391, EnemyEtis, "EnemyEtis-2392");
				break;
			}
			case 47300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002362);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002392, EnemyEtis, "EnemyEtis-2393");
				break;
			}
			case 47320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002363);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002393, EnemyEtis, "EnemyEtis-2394");
				break;
			}
			case 47340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002364);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002394, EnemyEtis, "EnemyEtis-2395");
				break;
			}
			case 47360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002365);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002395, EnemyEtis, "EnemyEtis-2396");
				break;
			}
			case 47380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002366);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002396, EnemyEtis, "EnemyEtis-2397");
				break;
			}
			case 47400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002367);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002397, EnemyEtis, "EnemyEtis-2398");
				break;
			}
			case 47420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002368);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002398, EnemyEtis, "EnemyEtis-2399");
				break;
			}
			case 47440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002369);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002399, EnemyEtis, "EnemyEtis-2400");
				break;
			}
			case 47460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002370);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002400, EnemyEtis, "EnemyEtis-2401");
				break;
			}
			case 47480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002371);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002401, EnemyEtis, "EnemyEtis-2402");
				break;
			}
			case 47500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002372);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002402, EnemyEtis, "EnemyEtis-2403");
				break;
			}
			case 47520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002373);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002403, EnemyEtis, "EnemyEtis-2404");
				break;
			}
			case 47540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002374);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002404, EnemyEtis, "EnemyEtis-2405");
				break;
			}
			case 47560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002375);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002405, EnemyEtis, "EnemyEtis-2406");
				break;
			}
			case 47580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002376);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002406, EnemyEtis, "EnemyEtis-2407");
				break;
			}
			case 47600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002377);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002407, EnemyEtis, "EnemyEtis-2408");
				break;
			}
			case 47620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002378);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002408, EnemyEtis, "EnemyEtis-2409");
				break;
			}
			case 47640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002379);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002409, EnemyEtis, "EnemyEtis-2410");
				break;
			}
			case 47660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002380);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002410, EnemyEtis, "EnemyEtis-2411");
				break;
			}
			case 47680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002381);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002411, EnemyEtis, "EnemyEtis-2412");
				break;
			}
			case 47700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002382);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002412, EnemyEtis, "EnemyEtis-2413");
				break;
			}
			case 47720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002383);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002413, EnemyEtis, "EnemyEtis-2414");
				break;
			}
			case 47740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002384);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002414, EnemyEtis, "EnemyEtis-2415");
				break;
			}
			case 47760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002385);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002415, EnemyEtis, "EnemyEtis-2416");
				break;
			}
			case 47780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002386);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002416, EnemyEtis, "EnemyEtis-2417");
				break;
			}
			case 47800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002387);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002417, EnemyEtis, "EnemyEtis-2418");
				break;
			}
			case 47820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002388);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002418, EnemyEtis, "EnemyEtis-2419");
				break;
			}
			case 47840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002389);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002419, EnemyEtis, "EnemyEtis-2420");
				break;
			}
			case 47860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002390);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002420, EnemyEtis, "EnemyEtis-2421");
				break;
			}
			case 47880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002391);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002421, EnemyEtis, "EnemyEtis-2422");
				break;
			}
			case 47900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002392);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002422, EnemyEtis, "EnemyEtis-2423");
				break;
			}
			case 47920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002393);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002423, EnemyEtis, "EnemyEtis-2424");
				break;
			}
			case 47940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002394);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002424, EnemyEtis, "EnemyEtis-2425");
				break;
			}
			case 47960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002395);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002425, EnemyEtis, "EnemyEtis-2426");
				break;
			}
			case 47980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002396);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002426, EnemyEtis, "EnemyEtis-2427");
				break;
			}
			case 48000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002397);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002427, EnemyEtis, "EnemyEtis-2428");
				break;
			}
			case 48020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002398);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002428, EnemyEtis, "EnemyEtis-2429");
				break;
			}
			case 48040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002399);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002429, EnemyEtis, "EnemyEtis-2430");
				break;
			}
			case 48060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002400);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002430, EnemyEtis, "EnemyEtis-2431");
				break;
			}
			case 48080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002401);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002431, EnemyEtis, "EnemyEtis-2432");
				break;
			}
			case 48100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002402);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002432, EnemyEtis, "EnemyEtis-2433");
				break;
			}
			case 48120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002403);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002433, EnemyEtis, "EnemyEtis-2434");
				break;
			}
			case 48140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002404);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002434, EnemyEtis, "EnemyEtis-2435");
				break;
			}
			case 48160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002405);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002435, EnemyEtis, "EnemyEtis-2436");
				break;
			}
			case 48180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002406);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002436, EnemyEtis, "EnemyEtis-2437");
				break;
			}
			case 48200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002407);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002437, EnemyEtis, "EnemyEtis-2438");
				break;
			}
			case 48220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002408);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002438, EnemyEtis, "EnemyEtis-2439");
				break;
			}
			case 48240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002409);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002439, EnemyEtis, "EnemyEtis-2440");
				break;
			}
			case 48260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002410);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002440, EnemyEtis, "EnemyEtis-2441");
				break;
			}
			case 48280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002411);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002441, EnemyEtis, "EnemyEtis-2442");
				break;
			}
			case 48300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002412);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002442, EnemyEtis, "EnemyEtis-2443");
				break;
			}
			case 48320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002413);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002443, EnemyEtis, "EnemyEtis-2444");
				break;
			}
			case 48340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002414);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002444, EnemyEtis, "EnemyEtis-2445");
				break;
			}
			case 48360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002415);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002445, EnemyEtis, "EnemyEtis-2446");
				break;
			}
			case 48380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002416);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002446, EnemyEtis, "EnemyEtis-2447");
				break;
			}
			case 48400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002417);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002447, EnemyEtis, "EnemyEtis-2448");
				break;
			}
			case 48420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002418);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002448, EnemyEtis, "EnemyEtis-2449");
				break;
			}
			case 48440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002419);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002449, EnemyEtis, "EnemyEtis-2450");
				break;
			}
			case 48460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002420);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002450, EnemyEtis, "EnemyEtis-2451");
				break;
			}
			case 48480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002421);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002451, EnemyEtis, "EnemyEtis-2452");
				break;
			}
			case 48500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002422);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002452, EnemyEtis, "EnemyEtis-2453");
				break;
			}
			case 48520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002423);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002453, EnemyEtis, "EnemyEtis-2454");
				break;
			}
			case 48540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002424);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002454, EnemyEtis, "EnemyEtis-2455");
				break;
			}
			case 48560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002425);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002455, EnemyEtis, "EnemyEtis-2456");
				break;
			}
			case 48580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002426);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002456, EnemyEtis, "EnemyEtis-2457");
				break;
			}
			case 48600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002427);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002457, EnemyEtis, "EnemyEtis-2458");
				break;
			}
			case 48620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002428);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002458, EnemyEtis, "EnemyEtis-2459");
				break;
			}
			case 48640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002429);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002459, EnemyEtis, "EnemyEtis-2460");
				break;
			}
			case 48660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002430);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002460, EnemyEtis, "EnemyEtis-2461");
				break;
			}
			case 48680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002431);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002461, EnemyEtis, "EnemyEtis-2462");
				break;
			}
			case 48700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002432);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002462, EnemyEtis, "EnemyEtis-2463");
				break;
			}
			case 48720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002433);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002463, EnemyEtis, "EnemyEtis-2464");
				break;
			}
			case 48740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002434);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002464, EnemyEtis, "EnemyEtis-2465");
				break;
			}
			case 48760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002435);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002465, EnemyEtis, "EnemyEtis-2466");
				break;
			}
			case 48780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002436);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002466, EnemyEtis, "EnemyEtis-2467");
				break;
			}
			case 48800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002437);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002467, EnemyEtis, "EnemyEtis-2468");
				break;
			}
			case 48820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002438);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002468, EnemyEtis, "EnemyEtis-2469");
				break;
			}
			case 48840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002439);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002469, EnemyEtis, "EnemyEtis-2470");
				break;
			}
			case 48860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002440);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002470, EnemyEtis, "EnemyEtis-2471");
				break;
			}
			case 48880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002441);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002471, EnemyEtis, "EnemyEtis-2472");
				break;
			}
			case 48900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002442);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002472, EnemyEtis, "EnemyEtis-2473");
				break;
			}
			case 48920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002443);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002473, EnemyEtis, "EnemyEtis-2474");
				break;
			}
			case 48940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002444);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002474, EnemyEtis, "EnemyEtis-2475");
				break;
			}
			case 48960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002445);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002475, EnemyEtis, "EnemyEtis-2476");
				break;
			}
			case 48980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002446);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002476, EnemyEtis, "EnemyEtis-2477");
				break;
			}
			case 49000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002447);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002477, EnemyEtis, "EnemyEtis-2478");
				break;
			}
			case 49020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002448);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002478, EnemyEtis, "EnemyEtis-2479");
				break;
			}
			case 49040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002449);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002479, EnemyEtis, "EnemyEtis-2480");
				break;
			}
			case 49060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002450);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002480, EnemyEtis, "EnemyEtis-2481");
				break;
			}
			case 49080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002451);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002481, EnemyEtis, "EnemyEtis-2482");
				break;
			}
			case 49100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002452);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002482, EnemyEtis, "EnemyEtis-2483");
				break;
			}
			case 49120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002453);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002483, EnemyEtis, "EnemyEtis-2484");
				break;
			}
			case 49140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002454);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002484, EnemyEtis, "EnemyEtis-2485");
				break;
			}
			case 49160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002455);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002485, EnemyEtis, "EnemyEtis-2486");
				break;
			}
			case 49180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002456);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002486, EnemyEtis, "EnemyEtis-2487");
				break;
			}
			case 49200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002457);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002487, EnemyEtis, "EnemyEtis-2488");
				break;
			}
			case 49220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002458);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002488, EnemyEtis, "EnemyEtis-2489");
				break;
			}
			case 49240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002459);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002489, EnemyEtis, "EnemyEtis-2490");
				break;
			}
			case 49260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002460);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002490, EnemyEtis, "EnemyEtis-2491");
				break;
			}
			case 49280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002461);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002491, EnemyEtis, "EnemyEtis-2492");
				break;
			}
			case 49300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002462);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002492, EnemyEtis, "EnemyEtis-2493");
				break;
			}
			case 49320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002463);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002493, EnemyEtis, "EnemyEtis-2494");
				break;
			}
			case 49340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002464);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002494, EnemyEtis, "EnemyEtis-2495");
				break;
			}
			case 49360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002465);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002495, EnemyEtis, "EnemyEtis-2496");
				break;
			}
			case 49380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002466);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002496, EnemyEtis, "EnemyEtis-2497");
				break;
			}
			case 49400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002467);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10002497, EnemyEtis, "EnemyEtis-2498");
				break;
			}
			case 49420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002468);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 49440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002469);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 49460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002470);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 49480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002471);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 49500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002472);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 49520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002473);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 49540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002474);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 49560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002475);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 49580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002476);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 49600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002477);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 49620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002478);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 49640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002479);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 49660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002480);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 49680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002481);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 49700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002482);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 49720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002483);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 49740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002484);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 49760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002485);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 49780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002486);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 49800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002487);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 49820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002488);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 49840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002489);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 49860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002490);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 49880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002491);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 49900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002492);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 49920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002493);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 49940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002494);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 49960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002495);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 49980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002496);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 50000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10002497);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 2501-1 ? _cnt_event+1 : _cnt_event);
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
