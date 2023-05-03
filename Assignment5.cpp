// ASU CSE310 Assignment #5 Fall 2022
// Name of Author: Race Musgrave
// ASU ID: 1215151093
// Description: this is the main program that reads input from a text file,
// it then call hash functions to execute hash commands given in the input.


/*****************************************************************************
1.    For my hash function, I followed a basic hashing by muliplication. The key used in the general
      hashing by multiplication formula was the sum of all ASCII values in the make and model of the
      given vehicle.
2.    With my original hash function, as the number of vehicles increased, so did the performance ratio,
      but as I applied the more concrete hashing by multiplication, as the number of cars increased,
      the performance ratio decreased. Although the first case performance ratio(PR) was 2.5, this did 
      not concern me since the input size was only 17, small enough that it would never make a difference
      in speed. Since the PR decreases as the size increases, I would say the hash function works well 
      since we are most worried about large cases
      case 1:     PR: 2.50       Longest list: 8
      case 2:     PR: 2.21       Longest list: 12
      case 3:     PR: 2.12       Longest list: 10
      case 4:     PR: 1.50       Longest list: 26
3.    If I were going to implament anything, I might try applying a similar idea from quadratic linear
      hashing. Using a second function to run parts of the key through to red an even more randomized value.
*/
#include "Hash.h"
#include <sstream>

using namespace std;

int main()
{
   int size = 0 ;
   int numOfCommand = 0;
   int carCount = 0;
   string model, make;
   int vin, idx;
   double price;
   string line, command, newStr, stringVin, stringPrice;
   string delim = ",";

   cout << "Enter the size of the hash table:";
   cin >> size;
   cin.ignore(20, '\n');

   Hash hash = Hash(size);          //hash is the hash table(array) that we will be adding values to

   do{
         getline(cin,line);
         if(line == "InsertionEnd" || line == "InsertionEnd\n"|| line == "InsertionEnd\r"){
            break;
         }

         //this array will contain the model at index 0,
         //the make at index 1 and the vin at index 2
         //the price will be stored in what is left of "line"
         string arr[3];
         for(int i = 0; i < 3; i++){
            idx = line.find(delim);
            arr[i] = line.substr(0,idx);
            line.erase(0, idx+delim.length());
         }
         model = arr[0];
         make = arr[1];
         vin = stoi(arr[2]);
         price = stod(line);

         hash.hashInsert(model, make, vin, price);          //puts the new vehicle into the hash table

         carCount++;
   }while(true);

   //cout << "\nEnter number of commands: ";
   cin >> numOfCommand;
   cin.ignore(20, '\n');
   //cout << "\nyou entered: " << numOfCommand;

   for(int i= 0; i < numOfCommand; i++)
   {
      getline(cin,line);               //read user input

      //if the command is hashdisplay
      if(line == "hashDisplay" || line == "hashDisplay\n"|| line == "hashDisplay\r"){
         hash.hashDisplay();
      }
      //if the command is hashLoadFactor
      else if(line == "hashLoadFactor" || line == "hashLoadFactor\n"|| line == "hashLoadFactor\r"){
         double LF = (double)hash.hashLoadFactor();            //LF = load factor
         double ILF = carCount / (double)hash.getm();          //ILF = ideal load factor
         double PR = LF / ILF;                                 //PR = performance ratio
         cout << "\nThe ideal load factor is: " << setprecision(2) << fixed << ILF << "\n";
         cout << "My hash table real load factor is: " << setprecision(2) << fixed << LF << "\n";
         cout << "My hash table performance ratio is: " << setprecision(2) << fixed << PR << "\n";
      }
      else{ //more than one token, check the command name, extract the remaining tokens

         int len = line.length();
         int idx = line.find(",");
         command = line.substr(0,idx);
         newStr = line.substr(idx+1, len);

         //get the model
         len = newStr.length();
         idx = newStr.find(",");
         model = newStr.substr(0,idx);
         newStr = newStr.substr(idx+1, len);

         //finally get the make and vin
         len = newStr.length();
         idx = newStr.find(",");
         make = newStr.substr(0,idx);
         stringVin = newStr.substr(idx+1, len);
         vin = stoi(stringVin);

         //finds a given car from given information
         if(command.compare("hashSearch")==0){
            hash.hashSearch(model, make, vin);
         }

         //deletes a car based on given information
         else  if(command.compare("hashDelete")==0){
            hash.hashDelete(model, make, vin);
         }
         else
            cout<<"Invalid command"<<endl;
      }
   } //end for loop
   return 0;
}