#include <stdio.h>

typedef struct {
    char firstName[8];
    char lastName[8];
    float age;
} Person;


typedef union {
    Person data;
    char pos[sizeof(Person)];
} SER;


void writeToFile(FILE* filePtr, SER ser) {
    int bytesWritten = 0;
    while(bytesWritten <= sizeof(Person)) {        
        fputc(ser.pos[bytesWritten++], filePtr);
    }

    fputc('\n', filePtr);
}


SER readFromFile(FILE* filePtr) {
    SER deSer;
    int byteRead = 0;
    int counter = 0;
    
    while(byteRead != EOF) {
        byteRead = fgetc(filePtr);
        deSer.pos[counter++] = byteRead;
    }
    
    return deSer;
}


int main() {
    FILE* serFilePtr = fopen("ser.txt", "w+");
    
    Person briBri = {"Brian", "Fister", 2};
    SER ser;
    ser.data = briBri;

    writeToFile(serFilePtr, ser);
    rewind(serFilePtr);
    SER deSer = readFromFile(serFilePtr);
    fclose(serFilePtr);



    FILE* deSerFilePtr = fopen("deSer.txt", "w+");
    writeToFile(deSerFilePtr, deSer);
    fclose(deSerFilePtr);

    return 0;
}
