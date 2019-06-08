out_folder="out/"
for file in ../general_in/*
do
	number=$(echo $file | sed -e 's/.*[^0-9]\([0-9]\+\)[^0-9]*$/\1/')
	text=$(echo ${file%.tsp} | cut -d'/' -f 3)
	counter=5
	while [ $counter -lt 100 ]
		do
			if [ $number -gt 20000 ] && [ $counter -gt 40 ];then
				break
			fi
			echo Tratando dados do arquivo $file com $counter% de arestas
			R1=$(($RANDOM%$number))
			R2=$(($RANDOM%$number))		
			tratamento_tsp/tdd s $file $R1 $R2 $counter
			counter=$(( $counter + 5 ))
	done
	if [ $number -lt 20001 ];then
		R1=$(($RANDOM%$number))
		R2=$(($RANDOM%$number))
		echo Tratando dados do arquivo $file com full edges
		tratamento_tsp/tdd f $file $R1 $R2
	fi
	mv *.txt $out_folder
done
