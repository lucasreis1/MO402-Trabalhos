out_file='total_times.txt'
rm $out_file
for file in times/*times.txt
do
	NO_TXT=${file#times/}
	NO_TXT=${NO_TXT%-times*}
	time=$(sed '3q;d' $file)
	echo $NO_TXT ": " $time >> $out_file
done
