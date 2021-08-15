make
echo "ENTRADA PEQUENA"
./aquarela < entradas/in1.txt > entradas/saida.txt
cat entradas/in1.txt entradas/saida.txt | ./fabiano/verifica
if [ "$?" -eq 0 ]
	then
		echo ok
	else
		echo fail
fi

echo "ENTRADA GRANDE"
time ./aquarela < entradas/100x100-20c.txt
