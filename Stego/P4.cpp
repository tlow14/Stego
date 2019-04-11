#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "LodePNG.h"

using namespace std;


bool check_path(string path) {
	fstream myfile;
	myfile.open(path.c_str());
	if (myfile.is_open()){
		myfile.close();
		return true;
	}
	else {
		return false;
	}
	
}

int input_error(string arguement) {
	cerr << "Does not recognize " << arguement << "\n"
		<< "steg -e <original image name> <modified image name> [input ASCII text file name] \n"
		<< "or \n"
		<< "steg -d <modified image name> [output ASCII text file name] \n" << endl;
	return -1;
}

//This reads in the file line by line and puts it into a vector of unsigned chars
vector<unsigned char> readTextFile(string path) {
	string message;
	ifstream file(path.c_str());
	while (getline(file, message));
	vector<unsigned char> charMessage (message.begin(), message.end());
	return charMessage;
}

//This encodes the message into the picture by changing the last bit
void encodeMessage(vector<unsigned char> &image, vector<unsigned char> message){
	unsigned char bit[8];
	for(int i = 0; i < image.size(); i++){
		image[i] &= 0xFE; 
	}
	for(int i = 0; i < message.size(); i++){
		//This makes 8 bits to put at the end
		for(int j = 0; j < 8; j++){
			bit[j] = ((message[i]>>j) & 0x01);
		}
		//This makes sure the bits get put in the right order
		for(int j = 0; j < 8; j++){
			image[(i*8) + (j)] |= (bit[7-j]);
		}
	}

	return;
}

//This decodes the message in the picture
//TODO
string decodeMessage(vector <unsigned char> image){
	string message;
	unsigned char byte = 0x00;
	for(int i = 0; i < image.size(); i++){
		byte |= (image[i] & 0x01);
		byte =  byte << 1;

		if(i%8 == 0 || i != 0){
			cout << byte << endl;
			message += byte;
			byte = 0x00;
		}
	}
	cout << message << endl;
	return message;
}

int main(int argc, char* argv[]) {
	//Error checking to make sure file there is the corrrect amount of arguements
	//cout << argv[1] << " " << argv[2] << " " << argv[3] << " " << argv[4] << endl;
	/*if (argc > 5 || argc < 4) {
		cerr << "Please eneter the correct amount of inputs! Examples below\n"
			<< "steg -e <original image name> <modified image name> [input ASCII text file name] \n"
			<< "or \n"
			<< "steg -d <modified image name> [output ASCII text file name] \n" << endl;
		return -1;
	}*/
	//Checks that the rest of the inputs are valid files 
	for (int i = 2; i < (argc); ++i) {
		// if (!check_path(argv[i])) {
		// 	return input_error(argv[i]);
		// }
	}

	//This deals with all the encoding
	if (string(argv[1]) == "-e") {
		vector<unsigned char> text = readTextFile(argv[4]);
		//This reads in the image
		vector<unsigned char> image;
		unsigned width, height;
		cout << "Reads the first file" << endl;
		unsigned error = lodepng::decode(image, width, height, argv[2]);
		//if there's an error, display it
		if (error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
		
		//This decodes the message in the image
		encodeMessage(image, text);

		//Encode the image
		error = lodepng::encode(argv[3], image, width, height);

		//if there's an error, display it
		if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;

	}
	//This deals with the decoding
	else if(string(argv[1]) == "-d"){
		//This reads in the image
		vector<unsigned char> image;
		unsigned width, height;
		cout << "Reads the first file" << endl;
		unsigned error = lodepng::decode(image, width, height, argv[2]);

		cout << argv[2] << endl;
		//if there's an error, display it
		if (error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
		string hiddenMessage = decodeMessage(image);
		cout << hiddenMessage << endl;
		

	//This deals if the first arguement is wrong.
	}else if(string(argv[1]) == "-t"){
		string s = argv[2];
		vector<unsigned char> image;
		vector<unsigned char> charMessage (s.begin(), s.end());
		for(int i = 0; i < 16; i++){
			image.push_back('A');
		}
		encodeMessage(image, charMessage);
		for(int i = 0; i < 16; i++){
			cout << image[i];
		}
		
		cout <<endl;
		ofstream file;
		file.open(argv[3]);

		file << decodeMessage(image);
		file.close();

	}else {
		return input_error(argv[1]);
	}
	string s;
	cout << "end of program" << endl;
	cin >> s;
	return 0;
}