

declare str="";

for files in *.h.gch
do
	rm $files
done

for files in *.cpp;
do
	str="$str $files"
done

for files in *.h;
do
	str="$str $files"
done

g++ $str -o tmp

./tmp.exe