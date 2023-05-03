// ASU CSE310 Assignment #5 Fall 2022
// Name of Author: Race Musgrave
// ASU ID: 1215151093
// Description: A simple linked list that implements a list of Car objects. A user can
//              perform searching, insertion or deletion on the linked list.

#include <iostream>
#include <iomanip>
#include <string>
#include <math.h>

using namespace std;

struct Car{
   string model, make;
   int vin;
   double price;
   struct Car* next;
};

class LinkedList{
   private:
     struct Car* head;      //pointer always pointing to the head of the list
     int size;              //a variable represents number of Cars inside the list
   public:
     LinkedList();
     ~LinkedList();
     Car* getHead();
     int getSize();
     bool searchCar(int carVIN);
     bool insertCar(string model, string make, int vin, double price);
     bool deleteCar(int carVIN);
     void displayList();
};

//Constructor
LinkedList::LinkedList(){
    head = NULL;
}

//Destructor
LinkedList::~LinkedList(){
    int carCount = 0;
    Car * curr = head;
    while(curr != NULL){
        head = head->next;
        delete curr;
        curr = head;
        ++carCount;
    }
    head = NULL;
    curr = NULL;
}

//just returns the head pointer
Car* LinkedList::getHead(){
    return head;
}


//Return number of Cars inside the Linked list
int LinkedList::getSize(){
    Car * curr = head;
    int count = 0;
    while(curr != NULL){
        curr = curr->next;
        ++count;
    }
    return count;
}

//This function does a linear search on the Car list with the given Car VIN
//it returns true if the corresponding Car is found, otherwise it returns false.
bool LinkedList::searchCar(int carVIN){
    Car * curr = head;
    while(curr != NULL){
        if(curr->vin == carVIN){
            return true;
        }
        curr = curr->next;
    }
    return false;
}

//Insert the parameter Car at the head of the linked list.
//return true if it is inserted successfully and false otherwise
bool LinkedList::insertCar(string model, string make, int vin, double price){
    Car * newCar = new Car;
    newCar->model = model;
    newCar->make = make;
    newCar->vin = vin;
    newCar->price = price;
    newCar->next = head;
    head = newCar;
    if(newCar->vin == head->vin){
        return true;
    }
    return false;
}

//Delete the Car with the given Car VIN from the linked list.
//Return true if it is deleted successfully and false otherwise
bool LinkedList::deleteCar(int carVIN){
    Car * curr = head;
    Car * prev = NULL;

    if(searchCar(carVIN) != true){
        return false;
    }

    if(curr->next == NULL ){
        delete curr;
        head = NULL;
        return true;
    }
    while(curr != NULL){
        //removes from the front
        if(prev == NULL && curr->vin == carVIN){
            head = head->next;
            delete curr;
            curr = head;
            return true;
        }
        //removes from the middle or end
        if(curr->vin == carVIN){
            prev->next = curr->next;
            delete curr;
            curr = prev->next;
            return true;
        }
        prev = curr;
        curr = curr->next;
    }
    return false;
}

//This function displays the content of the linked list.
void LinkedList::displayList(){
   struct Car *temp = head;
   if(head == NULL){
   	//empty linked list, print nothing here
   }
   else{
      while(temp != NULL)
      {
         cout << left    << setw(18) << temp->model
              << left    << setw(18) << temp->make
              << right   << setw(8)  << temp->vin
              << setw(10) << fixed << setprecision(2) << temp->price << "\n";
         temp = temp->next;
      }
   }
}