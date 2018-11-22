N=100

rm -f tests.txt

for ((i=1; i<=$N ; i++))
do
    ./2.exe 0 s >> tests.txt
    echo -n $i \ 
done

echo Стандартный: 
cat tests.txt | awk 'BEGIN { coun=0; sum=0 } { coun++; sum+=$1 } END { print sum/coun }'

rm -f tests.txt

for ((i=1; i<=$N ; i++))
do
    ./2.exe 1 s >> tests.txt
    echo -n $i \ 
done

echo Виноград:
cat tests.txt | awk 'BEGIN { coun=0; sum=0 } { coun++; sum+=$1 } END { print sum/coun }'

rm -f tests.txt

for ((i=1; i<=$N ; i++))
do
    ./2.exe 2 s >> tests.txt
    echo -n $i \ 
done

echo Виноград2: 
cat tests.txt | awk 'BEGIN { coun=0; sum=0 } { coun++; sum+=$1 } END { print sum/coun }'