input="./valid_input_asc"
while read -r line
do
	./push_swap "$line" | wc -l
	./push_swap "$line" | ./checker "$line"
done < "$input"