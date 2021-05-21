10 rem adapted from main_ssc.c
11 rem steve lewis - 2021
12 rem  a = work distance ft
15 rem  b = number of planets to model
20 rem  c = distance percentage
25 rem  d = distance proportion ft
30 rem  e = distance int
35 rem  f = distance frac
40 rem i,j = counters

500 print "work distance ft (7-1000)"
510 input a
515 rem range checks to keep the output report reasonable length
520 if (a < 7) goto 5000
530 if (a > 1000) goto 5000

600 print "num planets (1-9)";:input b
605 rem range checks  valid number of planets relative to the available data
610 if (b < 1) goto 5000
620 if (b > 9) goto 5000

990 rem get data for b,th planet specified (used to set the scale of the model)
1000 for i = 1 to b
1005   rem nearest
1010   read m(1), m(2), m(3)
1015   rem farthest
1020   read m(4), m(5), m(6)  
1025   rem average
1030   read m(7), m(8), m(9)  
1040 next i
1050 rem  m now holds the max conditions

1055 rem  go back to beginning of the data
1060 restore

1070 print "first ";:print b;:print " planets"
1080 print "scaled to ";:print a;:print " ft"

1100 for i = 1 to b
1105   rem nearest
1110   read p(1), p(2), p(3)
1115   rem farthest
1120   read p(4), p(5), p(6)
1125   rem average
1130   read p(7), p(8), p(9)
1140   if i=1 then print "mercury ";:goto 1230
1150   if i=2 then print "venus   ";:goto 1230
1160   if i=3 then print "earth   ";:goto 1230
1170   if i=4 then print "mars    ";:goto 1230
1180   if i=5 then print "jupiter ";:goto 1230
1190   if i=6 then print "saturn  ";:goto 1230
1200   if i=7 then print "uranus  ";:goto 1230
1210   if i=8 then print "neptune ";:goto 1230
1220   if i=9 then print "pluto   ";:goto 1230
1230   for j = 2 to 8 step 3
1240     c = p(j) / m(5)
1250     d = c * a
1260     e = int(d)
1270     f = int((d - e) * 12.0)
1280     if (f=12) then e=e+1:f=0
1290     print e;:print "'";
1292     print f;:print chr$(34);
1300   next j
1310   print
1320 next i

4000 end

5000 print "invalid"
5010 goto 500

8990 rem mercury
9000 data 46, 29, 0.307
9010 data 70, 43, 0.466
9020 data 57, 35, 0.387
9025 rem venus
9030 data 107, 66, 0.718
9040 data 109, 68, 0.728
9050 data 108, 67, 0.722
9065 rem earth
9060 data 147, 91, 0.980
9070 data 152, 94, 1.010
9080 data 150, 93, 1.000
9095 rem mars
9090 data 205, 127, 1.380
9100 data 249, 155, 1.660
9110 data 228, 142, 1.520
9125 rem jupiter
9120 data 741, 460, 4.950  
9130 data 817, 508, 5.460
9140 data 779, 484, 5.200
9155 rem saturn
9150 data 1350, 839, 9.05  
9160 data 1510, 938, 10.120
9170 data 1430, 889, 9.58
9185 rem uranus
9180 data 2750, 1710, 18.4  
9190 data 3000, 1860, 20.1
9200 data 2880, 1790, 19.2
9215 rem neptune
9210 data 4450, 2770, 29.8  
9220 data 4550, 2830, 30.4
9230 data 4500, 2800, 30.1
9245 rem pluto
9240 data 4440, 2760, 29.7  
9250 data 7380, 4590, 49.3
9260 data 5910, 3670, 39.5
