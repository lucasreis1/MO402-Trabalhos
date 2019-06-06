out_folder="times/"

for file in out/*.txt
do
	NO_TXT=${file%.txt}
	NO_TXT=${NO_TXT#out/}
	echo "Computando tres versoes do kruskal para " $file
	./main kruskal 0 $file times/"$NO_TXT-k0.txt" >> times/"$NO_TXT-k0-times.txt"
	./main kruskal 1 $file times/"$NO_TXT-k1.txt" >> times/"$NO_TXT-k1-times.txt"
	./main kruskal 2 $file times/"$NO_TXT-k2.txt" >> times/"$NO_TXT-k2-times.txt"
	echo "Computando duas versoes do prim para " $file
	./main prim 0 $file times/"$NO_TXT-k0.txt" >> times/"$NO_TXT-k0-times.txt"
	./main prim 1 $file times/"$NO_TXT-k1.txt" >> times/"$NO_TXT-k1-times.txt"
done