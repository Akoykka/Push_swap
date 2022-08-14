input="./three_to_five"
linenbr=1
while read -r line
do
	echo "line $linenbr :"
	let "linenbr"++
	./push_swap "$line" | wc -l
	./push_swap "$line" | ./checker "$line"
done < "$input"