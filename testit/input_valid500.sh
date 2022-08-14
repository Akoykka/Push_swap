input="./valid_500"
linenbr=1
while read -r line
do
	echo "line $linenbr :"
	let "linenbr"++
	valgrind --leak-check=full ./push_swap "$line" | valgrind --leak-check=full ./checker "$line"
done < "$input"