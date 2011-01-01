################################################################
#  �O�Ǐ��f�[�^�쐬�X�N���v�g
#                                    since 2010/10/19 by Gecchi
#
# �y�����z
# $ ruby makeSceneWallData.rb <����X�t�@�C��> <Y������AAB��> <Z������AAB��> <�����蔻��AAB��X�����ő�A����>
# (��AAB �Ƃ� �����s�����́FAxis-Aligned Box �̏ȗ�)
#
# �y�g�p��z
# $ ruby makeSceneWallData.rb scene3_2_wall.X 34 36 4 > scene3_2_wall.dat
################################################################

require './ExteriorArea'

xfile= ARGV[0]
max_x_colliwall_num = ARGV[3].to_i
outputfiles = Array.new
outputfile_index = 0

#�ǂݍ���
f = open(xfile)
while true

  while line = f.gets
    if line == nil then
      break
    end
    if line =~ /^Frame / then   #X�t�@�C���� �s��"Frame " �Ƃ���������𗊂�ɂ��Ă���
      #"Frame _200_8 {"
      break
    end
  end
  if line == nil then
    finishflg = true
    break
  end

  #"Frame _200_8 {" �� "200" �� "8" �����o��
  no_loop = line.sub(/^[^0-9]+/,'').sub(/[^0-9]+$/,'').split(/_/)
  seq_no = no_loop[0]
  loop_num = no_loop[1]

  while line = f.gets
    if line =~ /^\s*Mesh/ then   #X�t�@�C���� �s��"Mesh" �Ƃ���������𗊂�ɂ��Ă���
      break;
    end
  end

  line = f.gets #���_���ǂݔ�΂�

  #���_����Veartex�z��ɒ��߂���
  i = 0
  vtx = Array.new
  while line = f.gets
    #"50.000000;0.000002;-20.000004;," ��
    #50.000000 �� 0.000002 �� -20.000004 �ɕ���
    data = line.split(/\s*;\s*/)
    if data.length < 3 then
      break  #  1248;  �̒��_�C���f�b�N�X���̗�œǂݔ�΂�
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

    for v in 0..11 #AAB�̃��f�����_���C���f�b�N�X��12�Ƃ��Ă���B6��*2
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
        #���_�C���f�b�N�X�̒��_���
        x = vtx[vtx_index[fv].to_i].X
        y = vtx[vtx_index[fv].to_i].Y
        z = vtx[vtx_index[fv].to_i].Z
        if v == 0 && fv == 0 then
          #����͑��
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

    box[box_index] = Box.new
    #AAB�̒��S�_����
    box[box_index].X = (min_x+((max_x-min_x) / 2)).round
    box[box_index].Y = (min_y+((max_y-min_y) / 2)).round
    box[box_index].Z = (min_z+((max_z-min_z) / 2)).round

    box_index += 1
  end


  $box_dep = max_x-min_x
  $box_width = max_y-min_y
  $box_height = max_z-min_z

  #�\�[�g
  box = box.sort{|e1, e2|  (e1.X <=> e2.X).nonzero? or   #X����
                           (e1.Y <=> e2.Y).nonzero? or   #Y����
                            e1.Z <=> e2.Z                #Z����
                           }

  #X=0���킹
  offsetX = box[0].X - ($box_dep/2);
  for idx in 0..box_index-1
    box[idx].X -= offsetX;
  end


  #�I�u�W�F�N�g�\�z
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

  #BOX�ݒ�&�����蔻��AAB�œK�����
  exArea = ExteriorArea.new($area_len, $area_height, $area_width)
  #BOX�ݒ�
  for idx in 0..box_index-1
      iX = (box[idx].X - ($box_dep/2))/$box_dep
      iY = ((box[idx].Y-($box_height/2))/$box_height) + ($area_height/2)
      iZ = ((box[idx].Z-($box_width/2))/$box_width)  + ($area_width/2)
      #print idx,",(",iX,",",iY,",",iZ,") box[idx].X=",box[idx].X,"\n"
      exArea.area[iX][iY][iZ] = ExteriorArea::KABE_VAL
  end

  #exArea.dump01
  exArea.fullfull #�O�h��Ԃ�
  exArea.fullfull #�Q��ȏ�łقƂ�ǂ̏ꍇ�͑��v�����E�E

  r01_exArea = exArea.getAnalyze01

  #print "r01_exArea.dump01---------------\n"
  #r01_exArea.dump01
  #r01_exArea.dump02

  r02_exArea = r01_exArea.getAnalyze02

  #r02_exArea.dump02

  r03_exArea = r02_exArea.getAnalyze03
  r03_2_exArea = r03_exArea.getAnalyze03 #Z�����A�����s�����߂������getAnalyze03
  r04_exArea = r03_2_exArea.getAnalyze04(max_x_colliwall_num)


  #�f�[�^�o�͊J�n
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


