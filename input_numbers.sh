input="./valid_500"
while read -r line
do
	./push_swap "$line" | wc -l
	./push_swap "$line" | ./checker "$line"
done < "$input"