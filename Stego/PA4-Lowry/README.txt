To use my program just follow the command instructions that are specified in the requirements. One can encypt using -e and have file one encypted into file two with the input text of any txt.
Also, if you don't put a txt file you can just type a line into stdin. In addition you can decyprt using -d and have the file read either to a txt file or if nothing is passed then it just
goes to stdout. 

Examples using my pictures and files
./PA4.exe -e dolphin.png proxy2.png shakespear.txt 
	-Here shakespear.txt is encoded in dolphin.png and stored in proxy2.png
./PA4.exe -d proxy2.png output.txt
	-Here proxy2.png is decoded into output.txt
./PA4.exe -e dolphin.png proxy2.png
	-Here stdin is encoded in dolphin.png and stored in proxy2.png
./PA4.exe -d proxy2.png
	-Here proxy2.png is decoded into stdout