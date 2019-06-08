out_folder="times/"

for file in out/*.txt
do
	NO_TXT=${file%.txt}
	NO_TXT=${NO_TXT#out/}
	#echo Computando Ford-Fulkerson para $file
	#./main ford-fulkerson $file times/"$NO_TXT-ff.txt" >> times/"$NO_TXT-ff-times.txt"
	echo Computando Edmonds-Karp para $file
	./main edmonds-karp $file times/$NO_TXT-ek.txt >> times/$NO_TXT-ek-times.txt
	echo Computando Dinitz para $file
	./main dinitz $file times/$NO_TXT-d.txt >> times/$NO_TXT-d-times.txt
done
