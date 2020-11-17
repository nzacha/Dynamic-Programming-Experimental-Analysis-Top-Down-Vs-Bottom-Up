#include <stdlib.h>
#include "../helper/problem.h"

using namespace std;

#define MIN_WEIGHT 1
#define MAX_WEIGHT 3
#define MIN_VALUE 1
#define MAX_VALUE 30

class Item {
    public:
        int weight = 0, value = 0; 

        Item(int weight, int value){
            this->weight = weight;
            this->value = value;
        }

        operator string() const { 
            return std::string("[Weight: "+ to_string(weight) +", value: "+ to_string(value) +"]\n");
        }
};

/*
class Sack {
    list <Item> items;

    public:
        int capacity, weight, value = -1; 

        Sack(int capacity){
            this->capacity = capacity;
        }

        bool fitsItem(Item* item){
            return capacity >= weight + item->weight;
        }

        void addItem(Item* item){
            if(!fitsItem(item))
                return;
            items.push_back(*item);
            weight += item->weight;
            value += item->value;
        }

        void showItems(){
            cout << "Printing sack items:\n" << endl;
        	for (auto it = items.cbegin(); it != items.cend(); it++){
                cout << (string)(*it) << endl;
            }
        }

        void print(){
            cout << "[Value: " << value << ", Capacity: " << weight << "/" << capacity << "]" << endl;
        }
};
*/
struct ItemComparator { 
    bool operator ()(const Item & item1, const Item & item2){
        return item1.weight <= item2.weight;
    }
};
