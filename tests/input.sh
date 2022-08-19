#first parameter is filename for randomized number lists 
#just put them on one line
linenbr=1
while read -r line
do
	echo "line $linenbr :"
	let "linenbr"++
	./push_swap "$line" | wc -l
	./push_swap "$line" | ./checker "$line"
done < "$1"