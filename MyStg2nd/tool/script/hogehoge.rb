require 'tool/script/ExteriorBox'

xfile_dir = "C:\\cygwin\\workspace\\MyStgResource\\_STAGE_"
xfile= "STAGE3.X"
f = open(xfile_dir+"\\"+xfile)
i = 0
box = Array.new
while line = f.gets
  if line =~ /1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,/
    data = line.split(/\s*,\s*/)
    box[i] = ExteriorBox.new
    box[i].X = data[12].to_f.prec_i  #int Ç…ä€Çﬂ
    box[i].Y = data[13].to_f.prec_i
    box[i].Z = data[14].to_f.prec_i
    i += 1
  end
end
f.close


box = box.sort{|e1, e2|  (e1.X <=> e2.X).nonzero? or   #Xè∏èá
                         (e1.Y <=> e2.Y).nonzero? or   #Yè∏èá
                          e1.Z <=> e2.Z                #Zè∏èá
                         }


for b in box
  print  b.X,"\t",b.Y,"\t",b.Z
  print  "\n"
end

