#
    #By : Fayssal Chokri <fayssalchokri@symantec.com>
    #2021-2022 MIT Licence
#
convert=./fontconvert
inpath=~/Desktop/freefont/
outpath=../Fonts/
fonts=(FreeMono FreeSans FreeSerif)
styles=("" Bold Italic BoldItalic Oblique BoldOblique)
sizes=(9 12 18 24)

for f in ${fonts[*]}
do
	for index in ${!styles[*]}
	do
		st=${styles[$index]}
		for si in ${sizes[*]}
		do
			infile=$inpath$f$st".ttf"
			if [ -f $infile ] # Does source combination exist?
			  then
				outfile=$outpath$f$st$si"pt7b.h"
#				printf "%s %s %s > %s\n" $convert $infile $si $outfile
				$convert $infile $si > $outfile
			fi
		done
	done
done
