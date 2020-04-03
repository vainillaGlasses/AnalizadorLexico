#include "scanner.h"
#include "parser.h"


int main(int argc, char *argv[]){
    // Parámetros incorrectos
    if (argc != 3) {
        printf("Invalid arguments count"); // Cambiarlo a Usage: micro input_file
        return 1;
    } else {
	source_file = fopen(argv[1], "r+");
	text_file = fopen("text.txt", "w+");
    data_file = fopen(argv[2], "w+");
	
        
	if (source_file == 0) {
            printf("Could not open source file, exiting\n");
            return 1;
        } else {
        	system_goal();
            fclose(source_file);
            fclose(text_file);
            fclose(data_file);
            remove("text.txt");
        }
    }
}





