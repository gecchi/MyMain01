
require './ExteriorArea'
#http://download.aptana.com/tools/radrails/plugin/install/radrails-bundle





xfile= ARGV[0] #"STAGE3_2.X"
max_x_colliwall_num = ARGV[1].to_i
#�ǂݍ���
f = open(xfile)


while line = f.gets
  if line =~ /^\s*Mesh/
    break;
  end
end

line = f.gets

i = 0
vtx = Array.new
while line = f.gets
  data = line.split(/\s*;\s*/)
  if data.length < 3 then
    break
  end
  vtx[i] = Veartex.new
      #print "data[12]=",data[12]," data[12].to_f.round   =",(data[12].to_f.round   )," \n"
  vtx[i].X = data[0].to_f.round     #int �Ɋۂ�
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

  for v in 0..11 #6��*2
    line = f.gets

    if line.length < 3 then
      break_flg = true
      break
    end
    data = line.split(/\s*;\s*/)
    vtx_index = data[1].split(/\s*,\s*/)
    for fv in 0..2 #
      x = vtx[vtx_index[fv].to_i].X
      y = vtx[vtx_index[fv].to_i].Y
      z = vtx[vtx_index[fv].to_i].Z
      if v == 0 && fv == 0 then
        max_x = x;
        max_y = y;
        max_z = z;
        min_x = x;
        min_y = y;
        min_z = z;
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

  box[box_index] = Box.new
  #BOX�̒��S�_����
  box[box_index].X = (min_x+((max_x-min_x) / 2)).round
  box[box_index].Y = (min_y+((max_y-min_y) / 2)).round
  box[box_index].Z = (min_z+((max_z-min_z) / 2)).round

  box_index += 1
end

f.close

$box_dep = max_x-min_x
$box_width = max_y-min_y
$box_height = max_z-min_z





#�\�[�g
box = box.sort{|e1, e2|  (e1.X <=> e2.X).nonzero? or   #X����
                         (e1.Y <=> e2.Y).nonzero? or   #Y����
                          e1.Z <=> e2.Z                #Z����
                         }

#for bbb in 0..box_index-1
#  print "[",bbb,"]=(",box[bbb].X,",",box[bbb].Y,",",box[bbb].Z,")\n"
#end


#�I�u�W�F�N�g�\�z


$area_len = ((box[box_index-1].X - ($box_dep/2))/$box_dep)+1
$area_height = 34
$area_width = 34

area = Array.new( $area_len, 0 )
area.each_index { |x|
  area[x] = Array.new( $area_height, 0 )
  area[x].each_index { |y|
      area[x][y] = Array.new( $area_width, 0 )
  }
}

#BOX�ݒ�
exArea = ExteriorArea.new($area_len, $area_height, $area_width)

for idx in 0..box_index-1
    iX = (box[idx].X - ($box_dep/2))/$box_dep
    iY = ((box[idx].Y-($box_height/2))/$box_height) + ($area_height/2)
    iZ = ((box[idx].Z-($box_width/2))/$box_width)  + ($area_width/2)
    #print idx,",(",iX,",",iY,",",iZ,") box[idx].X=",box[idx].X,"\n"
    exArea.area[iX][iY][iZ] = ExteriorArea::KABE_VAL
end
#exArea.dump
#�O�h��Ԃ�
exArea.fullfull
r01_exArea = exArea.getAnalyze01
#print "r01_exArea.dump01---------------\n"
#r01_exArea.dump01
#r01_exArea.dump02

r02_exArea = r01_exArea.getAnalyze02
#print "r02_exArea.dump02---------------\n"
#r02_exArea.dump02


r03_exArea = r02_exArea.getAnalyze03
#print "r03_exArea.dump02---------------\n"
#r03_exArea.dump02
r03_2_exArea = r03_exArea.getAnalyze03 #Z�����A�����s�����߂������getAnalyze03




r04_exArea = r03_2_exArea.getAnalyze04(max_x_colliwall_num)
#print "r04_exArea.dump02---------------\n"
#r04_exArea.dump02

#�f�[�^�o�͊J�n
#print "data---------------\n"
print $area_len," ",$area_height," ",$area_width

print "\n"
print "\n"

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
  print box_info_len[l]," "
end
print "\n"
print "\n"
for l in 0..$area_len-1
  for h in 0..$area_height-1
     for w in 0..$area_width-1
       if r01_exArea.area[l][h][w] >= 0 then
         print h," ",w," ",r01_exArea.area[l][h][w]," "
         print r04_exArea.area[l][h][w][0]," ",
               r04_exArea.area[l][h][w][1]," ",
               r04_exArea.area[l][h][w][2]," ",
               r04_exArea.area[l][h][w][3]," ",
               r04_exArea.area[l][h][w][4]," ",
               r04_exArea.area[l][h][w][5]
         print "\t"
       end
    end #w
  end #h
  print "\n"
end
