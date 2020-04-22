#include "dictionary.h"

Dictionary::Dictionary()
{
    nombre_diccionario = "";
    qty_words_calculated = 0;
    limit_of_words = 0;
    word_lenght = 0;
    charset = nullptr;
    word = nullptr;
    nodeNumber = 1;
}

size_t Dictionary::findChar(const char &caracter){
    for(size_t i = 0; i < 20; i++){
        if( caracter == charset[i]  ){
            return i;
        }
    }
    return (size_t) - 1;
}
void Dictionary::calculateInitialWord(){

}
void Dictionary::calculateLimitOfWords(){
    // Numero Total de Combinaciones = (Longitud de Charset) ^ (Longitud del Password)
    numeroTotalDeCombinaciones = pow(charset_lenght, word_lenght);
    cout << "Potencia: "<< charset_lenght <<" al " << word_lenght << endl;
    // Limite de combinaciones = (Numero Total de Combinaciones) / (Numero de Nodos)
    limit_of_words = numeroTotalDeCombinaciones / nodeNumber;
    cout << "Numero de Combinaciones: " << numeroTotalDeCombinaciones << endl;
    cout << "Limite de Palabras: " << limit_of_words << endl;
}

// Getters
char * Dictionary::getCharset(){ return charset; }
char * Dictionary::getInitialWord(){ return word; }
unsigned long long Dictionary::getLimitOfWords(){ return limit_of_words; }
unsigned short int Dictionary::getNodeNumber(){ return nodeNumber; }
size_t Dictionary::getPasswordLenght(){ return word_lenght; }

// Setters
void Dictionary::setPasswordLenght( size_t lenght){ (word_lenght == 0) ? lenght: word_lenght; }
void Dictionary::setNodeNumber(unsigned short int number){(number == 0) ? 1 : this->nodeNumber = number; }
void Dictionary::setLimitOfWords( unsigned long long limit){ this->limit_of_words = limit; }

void Dictionary::setCharset(const string &charset){
    this->charset_lenght = charset.size();                  // Definimos la longitud del charset
    this->charset = (char *) malloc( charset.size() );      // Internamente se usa un array char
    strcpy(this->charset, charset.c_str() );                // Copiamos los caracteres en nuestro array
}

bool Dictionary::setInitialWord(const string &word){
    // Paso 1: Validar que la palabra incial tenga los caracteres del charset
    //PENDIENTE COMPLETAR EL CODIGO
//    for(auto charInWord = word.begin(); charInWord != word.end(); charInWord++){
//        for(size_t i = 0; i < charset_lenght; i++){
//            if(*charInWord == charset[i]){
//            }
//        }
//    }
    this->word = (char *) malloc( word.size() );
    word_lenght = word.size();
    strcpy(this->word, word.c_str() );
    this->Position = this->word_lenght - 1;

    // Recorremos la palabra para rellenar el array de posiciones
    for(size_t i = 0; i < word_lenght; i++){
        charsetPos[i] = findChar( word.at(i) );
    }
    return true;
}

int Dictionary::createDictionary(){
    if(word_lenght == 0)
        return EXIT_FAILURE;

    if(word == nullptr)                                 // Si no se ha definido la palabra incial
        calculateInitialWord();                         // la calculamos en funcion del numero de nodo

    if(limit_of_words == 0)                             // Si no se ha definido el limite de palabras
        calculateLimitOfWords();                        // Calulamos el limite en funcion del numero de nodoq

    if(charset != nullptr ){
        //fichero.open(nombre_diccionario.c_str());
        //Inicializamos todos los valores a 0
        /*
        for(size_t i = 0; i < word_lenght; i++){
            charsetPos[i] = 0;
        }
        */
        while( qty_words_calculated < limit_of_words){

            anidado:    // Si el caracter apuntado no ha llegado al final del charset

            if(Position == ((size_t)-1 )){  //Si se alcanzo el limite de posibles passwords con la longitud actual se acaba el bucle
                break;
            }
            //apuntamos al sig caracter del charset
            charsetPos[Position]++;
            //Si no se ha llegado al final de charset
            if( charsetPos[Position] < charset_lenght ){
                // se le asigna a word el caracter (es la nueva conbinacion del password)
                word[ Position ] = charset[ charsetPos[Position] ];
            }else {
                // sino reiniciamos el contador para que apunte al primer char de nuevo
                charsetPos[Position] = 0;
                // se le asigna a word el caracter (es la nueva conbinacion del password)
                word[ Position ] = charset[ charsetPos[Position] ];
                //Cambiamos la posicion del nivel de profundidad (apuntamos a un caracter mas atras)
                Position--;
                //Hacemos lo mismo de manera recursiva
                goto anidado;
            }
            //imprimimos o escribimos la palabra en el stream deseado
            cout << word << endl;
            //fichero << word << endl;

            //contabilizamos la cantidad de passwords escritos para tener un limite exacto
            qty_words_calculated++;
            if(Position < word_lenght -1){
                Position = word_lenght -1;
            }
        }
        //fichero.close();
    }
    return EXIT_SUCCESS;
}

Dictionary::~Dictionary()
{
    delete this->charset;
    delete this->word;
}
