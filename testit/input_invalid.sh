input="./invalid"
linenbr=1
clear
while read -r line
do
	echo "line $linenbr :"
	let "linenbr"++
	valgrind --leak-check=full ./push_swap "$line" | valgrind --leak-check=full ./checker "$line" 
	valgrind --leak-check=full ./push_swap "$line" | valgrind --leak-check=full ./checker "$line" | grep -A "LEAK SUMMARY"=6 >>invalid_output
done < "$input"


#howto grep this with grep -A --SUMMARY:=6