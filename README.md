  Author:  Atzamis Iosif 
  Purpose: C Shell Implementation
  E-mail: iwsifa@gmail.com
  Language:  C
 
 H upoloihsh akolouthei kata gramma tis odhghies kai tis apaithseis thn ekfwnhshs ths askhshs. 
 O kwdikas ulopoihei to 1 pipe dhladh den upostirizontai pollapla piepes kathws sumfwna me thn ekfwnhsh mas zhththike monaxa to aplo pipe.
Se periptwsh pou mou ksefuge kapoia allh diaforopoihsh eite apo e-mail - epe3hghseis pou eginan , uparxoun arketa sxolia sxedon se olo ton kwdika gia epipleon epekshghseis.

Parakatw deixnw duo paradeigmata xrhshs tou redirection , pisteuw pws oti mproei na grapsei o kathenas se ena shell apotelei paradeigma kati pou den tha xorouse na to grapsw se ena tetoio ReadME :) 

scenario 1 : " < "
 Will output the word count and file name for each of its arguments. 
	$ wc -w < test1.txt
	$ cat myfile.txt | wc -w


scenario 2 : " > "

	$ cat me.txt
		Iosif atzamis
	$ wc -l me.txt > out /* metraei tis grammes tou arxeiou */
	$ cat out
		1 me.txt
