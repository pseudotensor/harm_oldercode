mov	3	#
		pl $1 $2
		do i=$2+1,$3,1 {\
			rd $i
			pla $1
		}
		#
pl	2	#
		#
		rd $2
		pla $1
pla	1	#
		#
		set i=1,$nr*$nh
		#
		set r=(int((i-0.5)/$nh) + 0.5)*$dr + $rin
                set th=(int(i-0.5 - $nh*int((i-0.5)/$nh)) + 0.5)*$dh
		#
		image($nr,$nh) $rin $rout 0 3.14159
		#
		set ir = int((r - $rin - 0.4*$dr)/$dr)
		set ih = int((th - 0.4*$dh)/$dh)
		#
		set image[ir,ih] = $1[i-1]
		#
		limits $rin $rout 0 3.14159
		erase
		box
		minmax min max echo $min $max
		if($min*$max < 0.) {\
			#define delta (($max-$min)/10.)
			#set lev=$min,-$delta,$delta
			#levels lev
			#ltype 2
			#contour
			#
			#set lev=$delta,$max,$delta
			#levels lev
			#ltype 0
			#contour
	                #
                        define delta ((-$min)/10.)
                        set lev=$min,-$delta,$delta
                        levels lev
                        ltype 2
                        contour
                        #
                        define delta ($max/10.)
                        set lev=$delta,$max,$delta
			#set lev=0,0.5,0.01
                        levels lev
                        ltype 0
                        contour
                        #
                        #ctype cyan
                        #set lev = 0
                        #levels lev
                        #contour
                        #ctype white
                        #
		} \
		else {\
			set lev=$min,$max,($max-$min)/10.
			#set lev=0,0.5,0.01
			levels lev
			ltype 0
			contour
		}
		#
rd	1	#
		if($1 < 10) {define num <00$1>} \
                else {if($1 < 100) {define num <0$1>} \
                else {define num <$1>}}
                echo $num
		rdp dump$num
rdp	1	#
		#
		da dumps/$1
		lines 1 1
		read {_nr 1 _nh 2 _rin 3 _rout 4 _t 5}
		define nr (_nr)
		define nh (_nh)
		define rin (_rin)
		define rout (_rout)
		define dr ((_rout - _rin)/_nr)
		define dh (pi/$nh)
		lines 2 1000000
		#
		#
		read {r 1 h 2 rho 3 u 4 ur 5 uh 6 up 7 br 8 bh 9 bp 10}
		read {divb 11}
		read {ibeta 12}
		#read {frd 11 fru 12 frur 13 fruh 14}
		set g = 5./3.
		#
		# auxiliary info.
		set p = (g - 1.)*u
		set K = p*rho**(-g)
		set cs = sqrt(g*p/rho)
		set ma = ur/cs
		#
		set pr = rho*ur
		set pp = rho*up
		set ph = rho*uh
		#
		set lrho = lg(rho)
		set luh = lg(abs(uh) + 1.e-20)
		set lu = lg(u)
		set ldivb = lg(abs(divb) + 1.e-20)
		#
