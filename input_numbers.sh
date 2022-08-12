input="./valid_input"
while read -r line
do
	echo "$line"
	read -r line
	./push_swap "$line" | ./checker "$line"
done < "$input"