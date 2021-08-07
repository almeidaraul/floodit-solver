make fabiano
echo "ENTRADA PEQUENA"
cat entradas/in1.txt entradas/saida.txt | ./fabiano/verifica
if [ "$?" -eq 0 ]
	then
		echo ok
	else
		echo fail
fi

echo "ENTRADA GRANDE"
time ./main < entradas/100x100-20c.txt
