#include<iostream>
using namespace std;

class Shopping
{
    private:
        string productName;
        int productCode;
        float productPrice;
        float discount;
    public:
        void mainMenu(); // Main function that will Hold all Project;
        void administrator();// person will access about projects for modifications
        void buyer(); // Person who will buy product
        void addProduct(); // to add a product
        void editProduct(); // to edit a product
        void removeProduct(); // to remove a product
        void listItems(); // to list all products items
        void receipt(); // to get the receipt bill for payment
        void loginProcess(); // check about user Authioenticatn
};
