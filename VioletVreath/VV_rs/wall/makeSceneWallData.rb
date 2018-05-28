################################################################
#  外壁情報データ作成スクリプト
#                                    since 2010/10/19 by Gecchi
#
# 【書式】
# $ ruby makeSceneWallData.rb <入力Xファイル> <Y軸方向AAB数> <Z軸方向AAB数> <当たり判定AABのX方向最大連結数> <FULLFULLモード>
# FULLFULLモード "Yes":FULLFULLを行う（内部塗りつぶし） "Yes"以外:FULLFULLしない
# (※AAB とは 軸並行直方体：Axis-Aligned Box の省略)
#
# 【使用例】
# $ ruby makeSceneWallData.rb scene3_2_wall.X 34 36 4
# 実行すると
# scene3_2_wall_0.dat, scene3_2_wall_1.dat, ・・・ , scene3_2_wall_[N].dat が作成される
################################################################

require './ExteriorArea'

xfile= ARGV[0]
max_x_colliwall_num = ARGV[3].to_i

outputfiles = Array.new
outputfile_index = 0

#読み込み
f = open(xfile)
while true

  while line = f.gets
    if line == nil then
      break
    end
    if line =~ /^Frame / then   #Xファイルの 行頭"Frame " という文字列を頼りにしている
      #"Frame _200_8 {"
      break
    end
  end
  if line == nil then
    finishflg = true
    break
  end

  #"Frame _200_8 {" の "200" と "8" を取り出す
  no_loop = line.sub(/^[^0-9]+/,'').sub(/[^0-9]+$/,'').split(/_/)
  seq_no = no_loop[0]
  loop_num = no_loop[1]

  if loop_num.nil? then
    loop_num = "1"
    p "Warning: Force loop 1."
  end

  while line = f.gets
    if line =~ /^\s*Mesh/ then   #Xファイルの 行頭"Mesh" という文字列を頼りにしている
      break;
    end
  end

  line = f.gets #頂点数読み飛ばし

  #頂点情報をVeartex配列に貯めこむ
  i = 0
  vtx = Array.new
  while line = f.gets
    #"50.000000;0.000002;-20.000004;," を
    #50.000000 と 0.000002 と -20.000004 に分割
    data = line.split(/\s*;\s*/)
    if data.length < 3 then
      break  #  1248;  の頂点インデックス数の列で読み飛ばし
    end
    vtx[i] = Veartex.new
        #print "data[12]=",data[12]," data[12].to_f.round   =",(data[12].to_f.round   )," \n"
    vtx[i].X = data[0].to_f.round     #int に丸め
    vtx[i].Y = data[1].to_f.round
    vtx[i].Z = data[2].to_f.round
    i += 1
  end


  box_index = 0
  box = Array.new
  break_flg = false

  max_x = 0;
  max_y = 0;
  max_z = 0;
  min_x = 0;
  min_y = 0;
  min_z = 0;


  while break_flg == false
    boxvtx = Array.new
    for vidx in 0..35
      boxvtx[vidx] = Veartex.new
    end
    for v in 0..11 #AABのモデル頂点数インデックスは12個としている。6面*2
      #3;0,1,2;,
      #3;1,0,3;,
      #3;4,5,6;,
      #3;5,4,7;,
      #3;8,9,10;,
      line = f.gets

      if line.length < 3 then
        break_flg = true
        break
      end
      data = line.split(/\s*;\s*/)
      vtx_index = data[1].split(/\s*,\s*/)
      for fv in 0..2 #
        #頂点インデックスの頂点情報
        x = vtx[vtx_index[fv].to_i].X
        y = vtx[vtx_index[fv].to_i].Y
        z = vtx[vtx_index[fv].to_i].Z

        #頂点情報保持
        boxvtx[v*3+fv].X = x
        boxvtx[v*3+fv].Y = y
        boxvtx[v*3+fv].Z = z

        if v == 0 && fv == 0 then
          #初回は代入
          max_x = x
          max_y = y
          max_z = z
          min_x = x
          min_y = y
          min_z = z
        else
          if x > max_x then
            max_x = x
          end
          if x < min_x then
            min_x = x
          end

          if y > max_y then
            max_y = y
          end
          if y < min_y then
            min_y = y
          end

          if z > max_z then
            max_z = z
          end
          if z < min_z then
            min_z = z
          end
        end
      end

    end

    if break_flg == false then

      box[box_index] = Box.new
      #AABの中心点を代入
      box[box_index].X = (min_x+((max_x-min_x) / 2)).round
      box[box_index].Y = (min_y+((max_y-min_y) / 2)).round
      box[box_index].Z = (min_z+((max_z-min_z) / 2)).round


      #どういうプリズムか調査
      counter = [0,0,0,0,0,0,0,0]
      for vidx in 0..35
        x = boxvtx[vidx].X
        y = boxvtx[vidx].Y
        z = boxvtx[vidx].Z
        if    x > box[box_index].X && y > box[box_index].Y && z > box[box_index].Z then  #0
          counter[0] += 1
        elsif x > box[box_index].X && y > box[box_index].Y && z < box[box_index].Z then  #1
          counter[1] += 1
        elsif x > box[box_index].X && y < box[box_index].Y && z > box[box_index].Z then  #2
          counter[2] += 1
        elsif x > box[box_index].X && y < box[box_index].Y && z < box[box_index].Z then  #3
          counter[3] += 1
        elsif x < box[box_index].X && y > box[box_index].Y && z > box[box_index].Z then  #4
          counter[4] += 1
        elsif x < box[box_index].X && y > box[box_index].Y && z < box[box_index].Z then  #5
          counter[5] += 1
        elsif x < box[box_index].X && y < box[box_index].Y && z > box[box_index].Z then  #6
          counter[6] += 1
        elsif x < box[box_index].X && y < box[box_index].Y && z < box[box_index].Z then  #7
          counter[7] += 1
        end
      end

      #BOXの中心座標から見て８方向の各頂点座標に向かって全て伸びているかをチェック
      #８個全ての頂点に伸びている場合は、BOX
      #伸びてない頂点が２個の場合、プリズム
      #伸びてない頂点が４の場合、ピラミッド（実装予定）
      counter_sum = 0
      if counter[0] > 0 then
        counter_sum += 1
      end
      if counter[1] > 0 then
        counter_sum += 1
      end
      if counter[2] > 0 then
        counter_sum += 1
      end
      if counter[3] > 0 then
        counter_sum += 1
      end
      if counter[4] > 0 then
        counter_sum += 1
      end
      if counter[5] > 0 then
        counter_sum += 1
      end
      if counter[6] > 0 then
        counter_sum += 1
      end
      if counter[7] > 0 then
        counter_sum += 1
      end

      if counter_sum == 8 then

        #BOX
        box[box_index].pos_info = 0

      elsif counter_sum == 6 then
        #プリズム

        if counter[0] == 0 && counter[1] == 0 then
          box[box_index].pos_info = POS_PRISM_XY_NN
        elsif counter[2] == 0 && counter[3] == 0 then
          box[box_index].pos_info = POS_PRISM_XY_NP
        elsif counter[4] == 0 && counter[5] == 0 then
          box[box_index].pos_info = POS_PRISM_XY_PN
        elsif counter[6] == 0 && counter[7] == 0 then
          box[box_index].pos_info = POS_PRISM_XY_PP

        elsif counter[0] == 0 && counter[4] == 0 then
          box[box_index].pos_info = POS_PRISM_YZ_NN
        elsif counter[5] == 0 && counter[1] == 0 then
          box[box_index].pos_info = POS_PRISM_YZ_NP
        elsif counter[2] == 0 && counter[6] == 0 then
          box[box_index].pos_info = POS_PRISM_YZ_PN
        elsif counter[3] == 0 && counter[7] == 0 then
          box[box_index].pos_info = POS_PRISM_YZ_PP

        elsif counter[0] == 0 && counter[2] == 0 then
          box[box_index].pos_info = POS_PRISM_ZX_NN
        elsif counter[4] == 0 && counter[6] == 0 then
          box[box_index].pos_info = POS_PRISM_ZX_NP
        elsif counter[1] == 0 && counter[3] == 0 then
          box[box_index].pos_info = POS_PRISM_ZX_PN
        elsif counter[5] == 0 && counter[7] == 0 then
          box[box_index].pos_info = POS_PRISM_ZX_PP
        else
          #ありえない
          puts "Illigal prism!!!"
          p "counter=",counter
          p "boxvtx=",boxvtx
          exit(1)
        end

      elsif counter_sum == 4 then
        #ピラミッド

        if counter[7] > 0 && counter[5] > 0 && counter[6] > 0 && counter[3] > 0 then
          box[box_index].pos_info = POS_PYRAMID_NNN
        elsif counter[6] > 0 && counter[4] > 0 && counter[7] > 0 && counter[2] > 0 then
          box[box_index].pos_info = POS_PYRAMID_NNP
        elsif counter[5] > 0 && counter[1] > 0 && counter[4] > 0 && counter[7] > 0 then
          box[box_index].pos_info = POS_PYRAMID_NPN
        elsif counter[4] > 0 && counter[0] > 0 && counter[6] > 0 && counter[5] > 0 then
          box[box_index].pos_info = POS_PYRAMID_NPP
        elsif counter[3] > 0 && counter[1] > 0 && counter[2] > 0 && counter[7] > 0 then
          box[box_index].pos_info = POS_PYRAMID_PNN
        elsif counter[2] > 0 && counter[0] > 0 && counter[3] > 0 && counter[6] > 0 then
          box[box_index].pos_info = POS_PYRAMID_PNP
        elsif counter[1] > 0 && counter[0] > 0 && counter[5] > 0 && counter[3] > 0 then
          box[box_index].pos_info = POS_PYRAMID_PPN
        elsif counter[0] > 0 && counter[1] > 0 && counter[2] > 0 && counter[4] > 0 then
          box[box_index].pos_info = POS_PYRAMID_PPP
        else
          puts "Illigal Pyramid!!!"
          p "counter=",counter
          p "boxvtx=",boxvtx
          exit(1)
        end

      end


#        #プリズムと判定された要素表示
#      if box[box_index].pos_info != 0 then
#        p counter
#        p "boxvtx=",boxvtx
#      end
      box_index += 1
    end

  end


  $box_dep = max_x-min_x
  $box_width = max_y-min_y
  $box_height = max_z-min_z

  #ソート
  box = box.sort{|e1, e2|  (e1.X <=> e2.X).nonzero? or   #X昇順
                           (e1.Y <=> e2.Y).nonzero? or   #Y昇順
                            e1.Z <=> e2.Z                #Z昇順
                           }

  #X=0合わせ
  offsetX = box[0].X - ($box_dep/2);
  for idx in 0..box_index-1
    box[idx].X -= offsetX;
  end


  #オブジェクト構築
  $area_len = ((box[box_index-1].X - ($box_dep/2))/$box_dep)+1
  $area_height = ARGV[1].to_i
  $area_width = ARGV[2].to_i

  area = Array.new( $area_len, 0 )
  area.each_index { |x|
    area[x] = Array.new( $area_height, 0 )
    area[x].each_index { |y|
        area[x][y] = Array.new( $area_width, 0 )
    }
  }

  #BOX設定&当たり判定AAB最適化解析
  exArea = ExteriorArea.new($area_len, $area_height, $area_width)
  #BOX設定
  for idx in 0..box_index-1
      iX = (box[idx].X - ($box_dep/2))/$box_dep
      iY = ((box[idx].Y-($box_height/2))/$box_height) + ($area_height/2)
      iZ = ((box[idx].Z-($box_width/2))/$box_width)  + ($area_width/2)
      #print idx,",(",iX,",",iY,",",iZ,") box[idx].X=",box[idx].X,"\n"
      exArea.area[iX][iY][iZ] = box[idx].pos_info  #ExteriorArea::KABE_BOX_VAL
  end

  #exArea.dump01

  if ARGV[4] == "Yes" || ARGV[4] == "yes" then
    exArea.fullfull #外塗りつぶし
    exArea.fullfull #２回以上でほとんどの場合は大丈夫だが・・
  end

  #各BOXの6面の内、最低限描画しなければいけない面を解析
  r01_exArea = exArea.getAnalyze01

  #print "r01_exArea.dump01---------------\n"
  #r01_exArea.dump01
  #r01_exArea.dump02

  r02_exArea = r01_exArea.getAnalyze02(exArea)

  #r02_exArea.dump02

  r03_exArea = r02_exArea.getAnalyze03(exArea)
  r03_2_exArea = r03_exArea.getAnalyze03(exArea) #Z方向連結を行うためもう一回getAnalyze03

  #  #r03_2_exArea.dump02

  r04_exArea = r03_2_exArea.getAnalyze04(max_x_colliwall_num, exArea)


  #データ出力開始
  outputfiles[outputfile_index] = seq_no.to_s + "." + xfile +".dat"
  fw = File.open(outputfiles[outputfile_index],'w')



  fw.print loop_num

  fw.print "\n"
  fw.print "\n"

  fw.print $area_len," ",$area_height," ",$area_width

  fw.print "\n"
  fw.print "\n"


  box_info_len = Array.new
  for l in 0..$area_len-1
    len = 0
    for h in 0..$area_height-1
      for w in 0..$area_width-1
        if r01_exArea.area[l][h][w] >= 0 then
          len += 1;
        end
      end #w
    end #h
    box_info_len[l] = len
  end

  for l in 0..$area_len-1
    fw.print box_info_len[l]," "
  end
  fw.print "\n"
  fw.print "\n"
  for l in 0..$area_len-1
    for h in 0..$area_height-1
       for w in 0..$area_width-1
         if r01_exArea.area[l][h][w] >= 0 then
           fw.print exArea.area[l][h][w]," "
           fw.print h," ",w," ",r01_exArea.area[l][h][w]," "
           fw.print r04_exArea.area[l][h][w][0]," ",
                     r04_exArea.area[l][h][w][1]," ",
                     r04_exArea.area[l][h][w][2]," ",
                     r04_exArea.area[l][h][w][3]," ",
                     r04_exArea.area[l][h][w][4]," ",
                     r04_exArea.area[l][h][w][5]
           fw.print "\t"
         end
      end #w
    end #h
    fw.print "\n"
  end
  fw.close
  outputfile_index += 1
end #while true
f.close

outputfiles = outputfiles.sort
p outputfiles
for i in 0..outputfiles.length-1
  partstr = outputfiles[i].split(/\./)
  new_filenemae = partstr[1] + "_" + i.to_s + ".dat"
  File.rename(outputfiles[i], new_filenemae)

end


