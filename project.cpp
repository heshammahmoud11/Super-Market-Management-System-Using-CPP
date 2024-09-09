#include<iostream>
#include"project.h"
#include<fstream>
using namespace std;
// -------------- SuperMarket Management System ---------------
void Shopping::loginProcess()
{

    string email;
    string password;
    cout << "Please Login For Enter to Administration Form\n";
    cout << "Enter Your Email: ";
    cin >> email;
    cout << "Enter Your Password: ";
    cin >> password;
    if (email == "admin@gmail.com" && password == "admin0000")
    {
        administrator(); // it will call administrator function to enable user to access(add-edit-remove) about all products
    }
    else{
        cout << "Invalid Email or Passwrod\n";
    }
}


//--------- Main function -> that will Hold All Projects ------------
void Shopping::mainMenu()
{
    int choice;
    do
    {
        cout << "------ Welcome in Suparmarket Management System ---------\n";
        cout << "\t----------------   Main Product  -------------\n";
        cout << "1- Administration\n";
        cout << "2- Buyer\n";
        cout << "3- Exit\n";
        cout << "Enter Your Choice Please...";
        cin >> choice;
        switch(choice)
        {
            case 1:
                loginProcess(); // check about user Authioenticatn
                break;
            case 2:
                buyer();
                break;
            case 3:
                exit(0);
                break;
            default:
                cout << "Enter A Valid Number\n";
        }
    }while(choice != 3);
}

//----------- Administration function ----------------------
// it function will executa only when login info (email & password) is Correct
void Shopping::administrator()
{
    int choice;
    cout <<"------------- Access Administration Menu ---------------\n";
    cout <<"\t1- Add Product\n";
    cout <<"\t2- Modiffy Prodcut\n";
    cout <<"\t3- Remove Product\n";
    cout <<"\t4- Back To Main Menu\n";
    cout << "Please Enter Your Choice...";
    cin >> choice;
    switch(choice)
    {
        case 1:
            addProduct();
            break;
        case 2:
            editProduct();
            break;
        case 3:
            removeProduct();
            break;
        case 4:
            mainMenu();
            break;
        default:
            cout <<"Enter a Valid Number\n";
    }

}
//------ First Administration function => for Adding Products ----------
void Shopping::addProduct() // public
{
    start:
    string name;
    float price;
    float dis;
    int code;
    int token = 0;


    cout << "Enter Your Porduct Name: ";
    cin >> productName;
    cout << "Enter Product Code: ";
    cin >> productCode;
    cout << "Enter Price of the Product: ";
    cin >> productPrice;
    cout << "Enter Dscount on Product: ";
    cin >> discount;
    
    //--------Read & Write Product info in the File ---------

    fstream file;
    file.open("database.txt", ios::in); // Read from the file

    if (!file) // that means if the File Dosen't Exist
    {
        // we create new file and write the product info on it.
        file.open("database.txt", ios::app | ios::out); // Open/Create File to Write Product info
        file << "Product Name is: " << productName << endl;
        file << "Product Code is: " << productCode << endl;
        file << "Product Price is: " << productPrice << endl;
        file << "Product Discount is: " << discount << endl;
        file.close();
    }
    else
    {
        // Read Product info from the file
        file >> name >> code >> price >> dis;
        while(!file.eof()) // this will help us to iterate to the end of file
        {
            if(code == productCode) // if the product with same code exist, not add it again.
            {
                token++;
            }
            file >> name >> code >> price >> dis;
        }
        file.close();

        if(token == 1) // that means product exist in file, i doesen't add it again.
        {
            goto start;
        }
        else // that means product dosen't exist in file, i will add it in file.
        {
            file.open("database.txt", ios::app | ios::out);
            file << "Name: " << productName << ", Code: "<< productCode << ", Price: " << productPrice << ", Dis: " << discount << "\n";
            file.close();
        }
    }

}

//------ Second Administration function => for Editing Products ----------
void Shopping::editProduct()
{
    int pkey; // to get the product code from  the administrator
    int token = 0;
    string name;
    int code;
    float price;
    float dis;

    cout << "--- Modify The Product ---\n";
    cout << "Enter The Product Code: ";
    cin >> pkey;

    fstream fileOne, fileTwo;
    fileOne.open("database.txt", ios::in);

    if(!fileOne)// if the file dosen't exist
    {
        cout << "File Dosen't Exist\n";
    }
    else
    {
        //we will write the updated value in the database1 file, and then we will update its name to database after we make the changes 
        fileTwo.open("database1.txt", ios::app | ios::out); // Open the new file
        fileOne >> productName >> productCode >> productPrice >> discount;
        while (!fileOne.eof())
        {
            if(pkey == productCode)
            {// in this case product is exist, administrator can edit on the product info
                cout << "Enter New Name: ";
                cin >> name;
                cout << "Enter New Code: ";
                cin >> code;
                cout << "Enter New Price: ";
                cin >> price;
                cout << "Enter New Discount: ";
                cin >> dis;
                // write these new product info in new file;
                fileTwo << "New Name: " << name << " New Code: " << code
                        << "New Price: " << price <<" New Discount: " << dis;
                token++; // increment token because we find the user code match the product code
            }
            else
            {
                // if user code dosen't match the product code in file, i will add(write) these product information to the new file
                fileTwo << "Product Name: " << productName << " Product Code: " << productCode
                        << " Product Price" << productPrice << "Product Discount: " << discount << "\n";
            }
            fileOne >> productName >> productCode >> productPrice >> discount;
            // it help us to iterating again and again inside while loop
        }

        // Closing Files
        fileOne.close();
        fileTwo.close();
        
        // We will Remove The old file, then will rename the new file (database1 => database);
        remove("database.txt");
        rename("database1.txt", "database.txt");

        if(token == 0)
        {
            cout << "Sorry!! Product Record Not Found\n";
        }
    }

}

//------ Third Administration function => for Removing Products ----------
void Shopping::removeProduct()
{
    int pkey;
    int token = 0;

    fstream file1, file2;

    file1.open("database.txt", ios::in);
    cout << "Enter The Product Key To delete it...";
    cin >> pkey;

    if(!file1)// file not exist
    {
        cout << "The File doesn't Exist\n";
    }
    else
    {
        file2.open("database1.txt", ios::app | ios::out);
        file1 >> productName >> productCode >> productPrice >> discount;

        while(!file1.eof())
        {
            if(pkey == productCode)
            {
                cout << "Item Deleted Successfuly..\n";
                token++; // to know that we found the product;
            }
            else
            {
                // if user code doesn't match product code, write these info in new file
                file2   << "Product Name: " << productName << " Product Code: " << productCode
                        << " Product Price: " << productPrice << " Discount: " << discount << "\n";
            }
            file1 >> productName >> productCode >> productPrice >> discount; // to help us to iterating again and again
        }
        file1.close();
        file2.close();

        remove("database.txt");
        rename("database1.txt", "database.txt");

        if(token == 0)
        {
            cout << "==>> Product Code Not Found <==\n";
        }
    }
}

// ----------------------- Buyer Function -------------------------
void Shopping::buyer()
{
    start:
    int choice;
    cout << "--------- Buyer Menu ------------\n";
    cout << "1- Buy Product\n";
    cout << "2- Go Bacck\n";
    cout << "Enter Your Choice...";
    cin >> choice;
    
    switch (choice)
    {
    case 1:
        receipt();
        break;
    case 2:
        mainMenu();
        break;
    default:
        cout << "Invalid Number, Please Try Again" << endl;
        break;
    }
    goto start;
}

//------ First Customer function => for Lists All Products ----------

void Shopping::listItems()
{

    fstream file;
    file.open("database.txt", ios::in); // Reading From file

    cout << "----------------------------------------------\n";
    cout << "----- Product NO, Name, Price, Discount ------\n";
    cout << "----------------------------------------------\n";
    file >> productName >> productCode >> productPrice >> discount;

    while (!file.eof())
    {
        cout << "Product Name: " << productName << endl;
        cout << "Product Code: " << productCode << endl;
        cout << "Product Price: " << productPrice << endl;
        cout << "Product Discount: " << discount << endl;
        file >> productName >> productCode >> productPrice >> discount; // For iteration Purpose
    }

    file.close();
}

//------ Second Customer function => for Show Products Receipt ----------
void Shopping::receipt()
{
    start:
    fstream data;
    
    int productArr[100];  //we are taking a array to hold the code of the various product
    int QuantityArr[100]; //we are taking a array to hold the quantity of each product

    char choice;

    int cnt = 0;
    float amount = 0;
    float dis = 0;
    float total = 0;

    cout << "\t\t--------- Receipt ------------\n";
    data.open("database.txt", ios::in);

    if(!data)  //if the file doesn't exists
    {
        cout << "\tEmpty Database File\n";
        return;
    }
    else
    {
        data.close();
        listItems();  //if the file exists then we will show its content to the user

        
        cout<<"\n\t\t\t\t\t\t__________________________________________________\n";
        cout<<"\n\t\t\t\t\t\t|                                                 |\n";
        cout<<"\n\t\t\t\t\t\t|            Please place your order              |\n";
        cout<<"\n\t\t\t\t\t\t|                                                 |\n";
        cout<<"\n\t\t\t\t\t\t__________________________________________________\n";


        do
        {
            cout << "\tEnter Product Code: ";
            cin >> productArr[cnt];
            cout << "\tEnter Product Quantity: ";
            cin >> QuantityArr[cnt];

            // checking if we ordering dublicate items or not
            for (int i = 0; i < cnt; i++) 
            {
                if(productArr[cnt] == productArr[i])
                {
                    cout << "Dublicate Product Code, Please Try Again\n";
                    goto start;
                }
            }
            //if it is not a duplicate product code then we are going to increase the count of product
            cnt++;
            cout<<"\n\n\t\t\t\t\t\t  Do you want to Buy another Product ? If yes then Press 'y' else 'n' ";
            cin>>choice;
        }while(choice == 'y' || choice == 'Y');
        
        cout<<"\n\n\t\t\t\t\t\t_________________________________RECEIPT________________________\n";
        cout<<"\n\t\t\t\t\t\t Product No.\t Product Name\t Product quantity\t Price\t Amount\t Amount with Discount\n";

            //iterating over the file to get the products and generate the prices and receipt
            
            for(int i = 0; i < cnt; i++)
            {
                data.open("database.txt", ios::in);
                data >> productName >> productCode >> productPrice >> discount;

                while(!data.eof())
                {
                    if(productCode == productArr[i])
                    {
                        amount = productPrice * QuantityArr[i];
                        dis = amount - (amount * dis/100);
                        total = total + dis;
                    cout<<"\n\t\t\t\t\t\t  "<<productName<<"\t\t  "<<productCode<<"\t\t"<<QuantityArr[i]<<"\t\t"<<productPrice<<"\t"<<amount<<"\t\t"<<dis;
                    }
                    data >> productName >> productCode >> productPrice >> discount;
                    i++;
                }
            }
            
            data.close();
    }
    cout<<"t___________________________________\n";
    cout<<"\t  Total Amount :  "<< total <<endl;
}
