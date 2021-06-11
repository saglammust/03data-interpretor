/* @Author 
* Student Name: Mustafa Saðlam 
* Student ID: 150140129
* Date: 24.12.2016
*/
#include "ipop.h"

using namespace std;

typedef major thestruct;
thestruct qs;

int main(int argc, char* argv[]){
	qs.begin();

	if(argc == 2){ //if there is a file
		FILE* fileP;

		if(!(fileP = fopen(argv[1], "r+"))){
			if(!(fileP = fopen(argv[1], "w+"))){
				cerr << "File couldn't opened, terminating!..." << endl;
				exit(1);
			}
		}
		cout << endl;
		while(!feof(fileP)){
			fgets(qs.prefix, SIZE_STR, fileP);
			qs.postfixer(true);
		}
		cout << "Answer queue : " << qs.q.dequeue();
		while(!qs.q.isQempty())
			cout << " -> " << qs.q.dequeue();
		cout << endl << endl;

		qs.terminate();
		cout << "Terminating..." << endl;
	}
	else if(argc > 2){// if there is a syntax error about arguments
		cerr << "ERROR!!! Argument count can not be greater than two..." << endl;
		cout << "Please run the program wthout an argument or with just a name of a file containing appropriate mathematical operations" << endl;
		return EXIT_SUCCESS;
	}

	else{
		cout << "Initializing interpreter... " << endl << endl;
		do{
			cout << ">> ";
			cin.getline(qs.prefix, SIZE_STR);

			if(strcmp(qs.prefix, "exit") == 0){
				cout << endl << "Terminating the interpreter..." ;

				if(!qs.q.isQempty())
					cout << endl << "Answer queue : " << qs.q.dequeue();
				while(!qs.q.isQempty()){
					cout << " -> " << qs.q.dequeue();
				}

				cout << endl;
				return EXIT_SUCCESS;
			}

			qs.postfixer(false);
		}while(1);
	}

	qs.terminate();
	return EXIT_SUCCESS;
}
