#include <iostream>
#include <string>
#include <string.h>
#include <dictionary.h>

using namespace std;

int main()
{
    Dictionary dic;
    dic.setCharset("0123456789");   // Indicamos los caracteres que queremos usar para generar las combinaciones
    dic.setInitialWord("000000");
//    dic.setPasswordLenght(4);       // Indicamos la longitud de las palabras generadas por el diccionario

    cout << "Charset: " << dic.getCharset() << endl;
    cout << "Word: " << dic.getInitialWord() << endl;

    dic.createDictionary();         // Creamos el diccionario
    return 0;
}
