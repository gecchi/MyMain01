
require 'tool/script/ExteriorArea'
#http://download.aptana.com/tools/radrails/plugin/install/radrails-bundle





xfile_dir = "../MyStgResource/_STAGE_"
xfile= "STAGE3.X"
#読み込み
f = open(xfile_dir+"/"+xfile)
i = 0
box = Array.new
while line = f.gets
  if line =~ /1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,/
    data = line.split(/\s*,\s*/)
    box[i] = ExteriorBox.new
        #print "data[12]=",data[12]," data[12].to_f.round   =",(data[12].to_f.round   )," \n"
    box[i].X = data[12].to_f.round     #int に丸め
    box[i].Y = data[13].to_f.round
    box[i].Z = data[14].to_f.round
    i += 1
  end
end
f.close

#ソート
box = box.sort{|e1, e2|  (e1.X <=> e2.X).nonzero? or   #X昇順
                         (e1.Y <=> e2.Y).nonzero? or   #Y昇順
                          e1.Z <=> e2.Z                #Z昇順
                         }

#オブジェクト構築
$box_dep = 40
$box_width = 10
$box_height = 10

$area_len = ((box[i-1].X - ($box_dep/2))/$box_dep)+1
$area_height = 32
$area_width = 42

area = Array.new( $area_len, 0 )
area.each_index { |x|
  area[x] = Array.new( $area_height, 0 )
  area[x].each_index { |y|
      area[x][y] = Array.new( $area_width, 0 )
  }
}

#BOX設定
exArea = ExteriorArea.new($area_len, $area_height, $area_width)

for idx in 0..i-1
    iX = (box[idx].X - ($box_dep/2))/$box_dep
    iY = ((box[idx].Y-($box_height/2))/$box_height) + ($area_height/2)
    iZ = ((box[idx].Z-($box_width/2))/$box_width)  + ($area_width/2)
    #print idx,",(",iX,",",iY,",",iZ,") box[idx].X=",box[idx].X,"\n"
    exArea.area[iX][iY][iZ] = ExteriorArea::KABE_VAL
end

#外塗りつぶし
exArea.fullfull

r_exArea = exArea.getAnalyze



r_exArea.dump


