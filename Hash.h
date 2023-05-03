// ASU CSE310 Assignment #5 Fall 2022
// Name of Author: Race Musgrave
// ASU ID: 1215151093
// Description: this is where I designed functions on Hash hashTable,
// such as hashInsert, hashDelete, hashSearch and hashDisplay.
// I also crated some helper functinos such as getKey() which
// creates a hash key based on a cars info


#include "LinkedList.h"

using namespace std;

class Hash{
   private:
      LinkedList* hashTable;     //hashTable is a one-dimensional array of LinkedList
      int m;                     //slots number of the hash table
	public:
      Hash(int size);
      ~Hash();
      bool hashSearch(string model, string make, int vin);
      bool hashInsert(string model, string make, int vin, double price);
      bool hashDelete(string model, string make, int vin);
      int hashLoadFactor();
      void hashDisplay();
      int hashFunction(string key);
      int getStringInt(string str);
      int getm();
      string getKey(string, string, int);
};

//constructor
Hash::Hash(int size){
   hashTable =  new LinkedList[size];
   m = size;
}

//Destructor
Hash::~Hash(){
   for(int i = 0; i < getm(); i++){
      hashTable[i].~LinkedList();
   }
   delete[] hashTable;
}

//returns the size of the hash table
int Hash::getm(){
   return m;
}

//This function searches for a key inside the hash table and
//return true if it is found and false otherwise
//Note: key is the combination of model, make and vin
bool Hash::hashSearch(string model, string make, int vin){
   bool found = false;
   string newKey = getKey(model,make,vin);

   //gets the index and then checks if it is found
   int index = hashFunction(newKey);
   found = hashTable[index].searchCar(vin);

   //if the car is found at the key, then we print and return true
   if (found == true){
      cout << "\n" << left
          << setw(18) << model
          << setw(18) << make
          << setw(8)  << vin
          << " is found inside the hash table." << endl;
      return true;
   }

   //if the car is not found, then we print and return false
   cout << "\n" << left
        << setw(18) << model
        << setw(18) << make
        << setw(8)  << vin
        << " is NOT found inside the hash table." << endl;
   return false;     
}

//hashInsert inserts a Car with the relevant info. into the hashTable.
//it returns true if the data is inserted successfully and false otherwise
bool Hash::hashInsert(string model, string make, int vin, double price){
   string newKey = getKey(model,make,vin);
   int index = hashFunction(newKey);
   hashTable[index].insertCar(model, make, vin, price);
   if(hashTable[index].searchCar(vin) == true){
      return true;
   }
   return false;
}

//hashDelete deletes a Car with the relevant key from the hashTable.
//it returns true if it is deleted successfully and false otherwise
//Note: key is the combination of model, make and vin
bool Hash::hashDelete(string model, string make, int vin){
   if(hashSearch(model,make,vin)){
      //setting the key
      string newKey = getKey(model,make,vin);

      //finding the index
      int index = hashFunction(newKey);

      //if the car is found at the index, then we delete and display the message
      bool check = hashTable[index].deleteCar(vin);
      cout << "\n";
      cout << setw(18) << model
         << setw(18) << make
         << setw(8)  << vin
         << " is deleted from hash table." << endl;
      return check;
   }

   //if the car is not found or does not delete, then we display this message and return false
   cout << "\n";
   cout << setw(18) << model
        << setw(18) << make
        << setw(8)  << vin
        << " is NOT deleted from hash table." << endl;
   
   return false;
}

//This function computes your hash table real load factor
//it is the longest linked list size
int Hash::hashLoadFactor(){
   int LF = 0;                               //LF stands for Load factor
   for(int i = 0; i < getm(); i++){
      int LLsize = hashTable[i].getSize();   //LLsize stands for LinkedListsize
      if(LLsize > LF){
         LF = LLsize;
      }
   }
   return LF;
}

//This function prints all elements from the hashTable.
void Hash::hashDisplay(){
   for(int i = 0; i < getm(); i++){
      int LLsize = hashTable[i].getSize();
      if(LLsize == 0){
         cout << "\nHashTable[" << i << "] is empty, size = 0\n";
      }
      else{
         cout << "\nHashTable[" << i << "], size = " << LLsize << "\n";
         hashTable[i].displayList();
      }
   }
}

//This is the hash function you need to design. Given a
//string key, the function should return the slot number
//where we will hash the key to
int Hash::hashFunction(string key){

   //the followingline split the given key into two parts:
   int start = key.find(",");
   int end = key.length();
   string Svin = key.substr(start+1,end-start+1);     //the vin
   string modelAndMake = key.substr(0,start);         //the make and model
   int titleValue = getStringInt(modelAndMake);
   int vinValue = stoi(Svin);                         //the string vin is converted into an int vin
   
   //this is all the computations for my hash function, the basis is hashing by multiplication
   double GR = 0.618033989; 
   double k = (double)titleValue + (double)vinValue;
   double val = fmod(k*GR,1.0);
   int hash = getm() * val;

   return hash;
}

//just a helper function to convert a string into a int value
int Hash::getStringInt(string str){
   int total = 0;
   int length = str.length();
   for(int i = 0; i < length; i++){    //this for loop adds all the ASCII values 
      total += str[i];                 //from the make and model into a total sum
   }
   return total;
}

//a helper function to convert model, make, and vin info into a single string
string Hash::getKey(string model, string make, int vin){
   string vinStr = to_string(vin);
   string newKey = model + make + "," + vinStr;
   return newKey;
}

