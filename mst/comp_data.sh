out_folder="out/"
for file in ../general_in/*
do
	number=$(echo $file | sed -e 's/.*[^0-9]\([0-9]\+\)[^0-9]*$/\1/')
	text=$(echo ${file%.tsp} | cut -d'/' -f 3)
	counter=1
	cmp=0
	while [ $counter -lt $number ]
		do
			if [ $number -gt 20000 ] && [ $counter -gt 100 ];then
				break
			fi
			echo "Tratando dados do arquivo" $file com $counter "vizinhos"
			tratamento_tsp/tratamento_de_dados s $file $counter
			if [ $cmp -eq 0 ]; then
				counter=$(($counter*5))
				cmp=1
			else
				counter=$((counter*2))
				cmp=0
			fi
	done
	echo "Computando grafo cheio para" $file
	if [ $number -lt  50000 ]; then
		tratamento_tsp/tratamento_de_dados f $file
	fi
	mv *.txt $out_folder
done
