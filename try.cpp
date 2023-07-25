#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <cstring>

using namespace std;
const string INDEX_FILE = "index.txt";
const string EMPLOYEE_FILE = "employee.txt";
vector<string> splitString(string str, char delim) {
    vector<string> tokens;
    stringstream ss(str);
    string token;
    while (getline(ss, token, delim)) {
        tokens.push_back(token);
    }
    return tokens;
}
const int TABLE_SIZE = 10;

// Structure to hold credit card details
struct CreditCard {
    string creditCardNumber;
    string pin;
    double availableBalance;
};

// Hash Table class
class HashTable {
private:
    CreditCard* table[TABLE_SIZE];

    // Hash function
    int hashFunction(const string& creditCardNumber) {
        int sum = 0;
        for (char ch : creditCardNumber) {
            sum += ch;
        }
        return sum % TABLE_SIZE;
    }

public:
    // Constructor
    HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = nullptr;
        }
    }

    // Destructor
    ~HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (table[i] != nullptr) {
                delete table[i];
            }
        }
    }

    // Insert a credit card
    // Insert a credit card
// Insert a credit card
void insertCreditCard(const string& creditCardNumber, const string& pin, double availableBalance) {
    int index = hashFunction(creditCardNumber);
    int count = 0;

    // Linear probing collision handling
    while (table[index] != nullptr && count < TABLE_SIZE) {
        if (table[index]->creditCardNumber == creditCardNumber) {
            cout << "Collision occurred for credit card number: " << creditCardNumber << endl;
           
    }
    cout << "Collision occurred for credit card number: " << creditCardNumber << endl;
        index = (index + 1) % TABLE_SIZE;
        count++;
    }

    if (count == TABLE_SIZE) {
        cout << "Hash table is full. Unable to insert credit card." << endl;
        return;
    }

    CreditCard* newCard = new CreditCard;
    newCard->creditCardNumber = creditCardNumber;
    newCard->pin = pin;
    newCard->availableBalance = availableBalance;

    table[index] = newCard;

    cout << "Credit card inserted at index " << index << endl;
}


    // Find a credit card by credit card number
    CreditCard* findCreditCard(const string& creditCardNumber) {
        int index = hashFunction(creditCardNumber);
        int count = 0;

        while (table[index] != nullptr && count < TABLE_SIZE) {
            if (table[index]->creditCardNumber == creditCardNumber) {
                return table[index];
            }
            index = (index + 1) % TABLE_SIZE;
            count++;
        }

        return nullptr; // Credit card not found
    }

    // Display all credit card details
    // Display all credit card details
void displayAllCreditCards() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table[i] != nullptr) {
            cout << "Index: " << i << endl;
            cout << "Credit Card Number: " << table[i]->creditCardNumber << endl;
            cout << "PIN: " << table[i]->pin << endl;
            cout << "Available Balance: " << table[i]->availableBalance << endl;
            cout << endl;
        }
    }
}


    // Save the hash table to a file
    void saveHashTableToFile(const string& filename) {
        ofstream file(filename);

        if (file.is_open()) {
            for (int i = 0; i < TABLE_SIZE; i++) {
                if (table[i] != nullptr) {
                    file << table[i]->creditCardNumber << "|" << table[i]->pin << "|" << table[i]->availableBalance << endl;
                }
            }
            file.close();
            cout << "Hash table saved to " << filename << endl;
        }
        else {
            cout << "Unable to open file." << endl;
        }
    }

    // Load the hash table from a file
    void loadHashTableFromFile(const string& filename) {
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (table[i] != nullptr) {
                delete table[i];
                table[i] = nullptr;
            }
        }

        ifstream file(filename);
        string line;

        if (file.is_open()) {
            while (getline(file, line)) {
                stringstream ss(line);
                string token;
                getline(ss, token, '|');
                string creditCardNumber = token;
                getline(ss, token, '|');
                string pin = token;
                getline(ss, token, '|');
                double availableBalance = stod(token);

                insertCreditCard(creditCardNumber, pin, availableBalance);
            }

            file.close();
            cout << "Hash table loaded from " << filename << endl;
        }
        else {
            cout << "Unable to open file." << endl;
        }
    }
};

struct Item {
    string itemName,itemQuantity;
    float itemValue;
    int stocksLeft,Item_id;
};
struct Employee {
    int employeeId;
    string employeeName;
    string address;
    string emailAddress;
};
vector<string> splitString12(string str, char delimiter) {
    vector<string> tokens1;
    string token1;
    for (char c : str) {
        if (c == delimiter) {
            tokens1.push_back(token1);
            token1 = "";
        } else {
            token1 += c;
        }
    }
    tokens1.push_back(token1);
    return tokens1;
}
vector<Item> readItemsFromFile(string fileName) {
    vector<Item> items;
    ifstream inFile(fileName);

    if (!inFile) {
        cerr << "Failed to open file: " << fileName << endl;
        return items;
    }

    string line;
    while (getline(inFile, line)) {
        string delimiter = "|";
        size_t pos = 0;
        vector<string> tokens;
        while ((pos = line.find(delimiter)) != string::npos) {
            string token = line.substr(0, pos);
            tokens.push_back(token);
            line.erase(0, pos + delimiter.length());
        }
        tokens.push_back(line);

        Item item;
        item.itemName = tokens[0];
        item.itemQuantity = tokens[1];
        item.itemValue = stof(tokens[2]);
        item.Item_id = stoi(tokens[3]);
        item.stocksLeft = stoi(tokens[4]);

        items.push_back(item);
    }

    inFile.close();

    return items;
}

void writeItemsToFile(string fileName, vector<Item> items) {
    ofstream outFile(fileName);

    if (!outFile) {
        cerr << "Failed to open file: " << fileName << endl;
        return;
    }

    for (int i = 0; i < items.size(); i++) {
        Item item = items[i];
        outFile << item.itemName << "|" << item.itemQuantity << "|" << item.itemValue << "|" << item.Item_id << "|" << item.stocksLeft << endl;
    }

    outFile.close();
}

void addItems(string fileName) {
    vector<Item> items = readItemsFromFile(fileName);

    string itemName;
    cout << "Enter the name of the item: ";
    cin>>itemName;

    bool itemFound = false;
    for (int i = 0; i < items.size(); i++) {
        if (items[i].itemName == itemName) {
            itemFound = true;
            float price;
            int stocks;
            string value;
            cout << "Enter the stocks to be added: ";
            cin >> stocks;
            items[i].stocksLeft += stocks;

            break;
        }
    }

    if (!itemFound) {
        float price;
        int id, stocks;
        string value;

        cout << "Enter the item value: ";
        cin >> value;
        cout << "Enter the item price: ";
        cin >> price;
        cout << "Enter the item id: ";
        cin >> id;
        cout << "Enter the stocks: ";
        cin >> stocks;

        Item item;
        item.itemName = itemName;
        item.itemQuantity = value;
        item.itemValue = price;
        item.Item_id = id;
        item.stocksLeft = stocks;

        items.push_back(item);
    }

    writeItemsToFile(fileName, items);

    cout << "Items updated successfully!" << endl;
}
void removeDuplicateEntries(vector<string>& items) {
    // Create a vector to store the indices of the items with each unique name
    vector<int> nameIndices(items.size(), -1);
    for (int i = 0; i < items.size(); i++) {
        vector<string> tokens1 = splitString12(items[i], '|');
        string itemName = tokens1[0];
        int j = 0;
        while (j < i && nameIndices[j] != -1 && splitString12(items[nameIndices[j]], '|')[0] != itemName) {
            j++;
        }
        if (j == i || nameIndices[j] == -1) {
            // If this is the first occurrence of this name, store its index in the vector
            nameIndices[i] = i;
        } else {
            // If this is not the first occurrence of this name, update the value and price of the first occurrence
            vector<string> firstTokens = splitString12(items[nameIndices[j]], '|');
            int firstValue = stoi(firstTokens[1]);
            int firstPrice = stoi(firstTokens[3]);
            int currValue = stoi(tokens1[1]);
            int currPrice = stoi(tokens1[3]);
            firstValue += currValue;
            firstPrice += currPrice;
            firstTokens[1] = to_string(firstValue);
            firstTokens[3] = to_string(firstPrice);
            items[nameIndices[j]] = "";
            items[nameIndices[j]] = firstTokens[0] + "|" + firstTokens[1] + "|" + firstTokens[2] + "|" + firstTokens[3];
            // Remove the current item from the vector
            items[i] = "";
        }
    }

    // Remove the empty strings from the vector
   // items.erase(remove(items.begin(), items.end(), ""), items.end());
}
void printItemList1(string tako) {
    string line;
    ifstream infile(tako);
    if (infile.is_open()) {
        // Print the header row
        cout <<  setw(30) << left << "Item Name" << setw(15) << left << "Quantity" << setw(10) << left << "Value" << setw(10) << left << "Item-ID" << endl;
        cout << setfill('-') << setw(60) << "" << endl;
        cout << setfill(' ');
        // Print each item in a row
        while (getline(infile, line)) {
            size_t pos = line.find("|");
            string itemName = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find("|");
            string itemQuantity = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find("|");
            string itemValue = line.substr(0, pos);
            line.erase(0, pos + 1);
            int item_id = stoi(line);
            cout <<setw(30) << left << itemName << setw(15) << left << itemQuantity << setw(10) << left << itemValue<< setw(10) << left << item_id << endl;
        }
        infile.close();
    } else {
        cout << "Error opening file." << endl;
    }
}
double displayBill(string taco) {
    // Open the file
    ifstream inFile(taco);

    // Variables to store data from file
    string line, itemName;
    int itemQuantity;
    double itemValue, totalPrice;

    // Variable to store the total calculated price
    double totalCalculatedPrice = 0;

    // Output the table headers
    cout << left << setw(25) << "Item ID" << setw(25) << "Item Name" << setw(25) << "Item Quantity" << setw(25) << "Total Price" << endl;
    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;

    // Loop through each line in the file
    while (getline(inFile, line)) {
        // Create a stringstream from the line
        stringstream ss(line);

        // Use the '|' delimiter to separate the fields
        getline(ss, itemName, '|');
        ss >> itemQuantity;
        ss.ignore();
        ss >> itemValue;
        ss.ignore();
        ss >> totalPrice;

        // Add the total price to the running total
        totalCalculatedPrice += totalPrice;

        // Output the data in a formatted table row
        cout << left << setw(25) << itemValue << setw(25) << itemName << setw(25) << itemQuantity << setw(25) << totalPrice << endl;
    }

    // Close the file
    inFile.close();

    // Output the total calculated price
    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << left << setw(75) << "Total Calculated Price: " << setw(25) << totalCalculatedPrice << endl;
    return totalCalculatedPrice;
}
void deletelast(const std::string& filename) {
  // Open the input file in read mode.
  std::ifstream input_file(filename);

  // Open the output file in write mode.
  std::ofstream output_file("Customerlist2.txt");

  // Copy all the lines from the input file to the output file,
  // except for the last one if it's empty.
  std::string line;
  while (std::getline(input_file, line)) {
    if (!line.empty() || input_file.peek() != std::ifstream::traits_type::eof()) {
      output_file << line << std::endl;
    }
  }
  string taco="Customerlist2.txt";
  double value=displayBill(taco);

  // Close both files.
  input_file.close();
  output_file.close();

  // Replace the input file with the output file.
 
}
void checkingfunction()
{
    ifstream inputFile("Customerlist.txt");
    if (!inputFile) {
        cout << "Ur Total Bill was:- 0" << endl;
        exit(0);
    }

    // Read the input file into a vector of strings
    vector<string> items;
    string line;
    while (getline(inputFile, line)) {
        items.push_back(line);
    }

    // Close the input file
    inputFile.close();

    // Remove duplicate entries from the vector
    removeDuplicateEntries(items);

    // Open the output file
    ofstream outputFile("Customerlist1.txt");
    if (!outputFile) {
        cout << "Error: Unable to open output file." << endl;
        return ;
    }

    // Write the cleaned items to the output file
    for (string item : items) {
        outputFile << item << endl;
    }
    // Close the output file
    outputFile.close();
    string taco="Customerlist1.txt";
    std::string filename = taco;
    deletelast(taco);


}
void customerclaculation(string taco)
{
    
    ifstream inFile(taco);
    if (!inFile.is_open()) {
        cout << "Error opening file." << endl;
        return;
    }

    // Read the contents of the file into a vector of strings
    vector<string> items;
    string line;
    while (getline(inFile, line)) {
        items.push_back(line);
    }
    inFile.close();

    // Prompt the user for an item_id and quantity
    string itemId;
    int quantity;
    cout << "Enter an item ID: ";
    cin >> itemId;
    cout << "Enter the quantity: ";
    cin >> quantity;
    
    // Find the item with the given item_id
    bool foundItem = false;
    string itemName;
    float itemPrice;
    int stocksLeft;
    for (auto& item : items) {
        vector<string> tokens = splitString(item, '|');
        if (tokens[3] == itemId) {
            itemName = tokens[0];
            itemPrice = stof(tokens[2]);
            stocksLeft = stoi(tokens[4]);
            foundItem = true;
            if (quantity > stocksLeft) {
            cout << "Out of stock." << endl;
            return;
            }
            else{
            // Update the stocks_left value
            stocksLeft -= quantity;
            }
            // Update the item string with the new stocks_left value
            item = tokens[0] + "|" + tokens[1] + "|" + tokens[2] + "|" + tokens[3] + "|" + to_string(stocksLeft);
            break;
        }
    }

    // If the item was not found, print an error message and exit
    if (!foundItem) {
        cout << "Item not found." << endl;
        return;
    }

    // Check if there is enough stock of the item
    

    // Calculate the total price and write to the Customerlist.txt file
    float totalPrice = quantity * itemPrice;
    ofstream outFile("Customerlist.txt", ios_base::app);
    outFile << itemName << "|" << quantity << "|" << itemId << "|" << totalPrice << endl;
    outFile.close();

    // Write the updated item information back to the "item.txt" file
    ofstream itemFile(taco);
    if (!itemFile.is_open()) {
        cout << "Error opening file." << endl;
        return;
    }
    for (auto& item : items) {
        itemFile << item << endl;
    }
    itemFile.close();

}

void maintainace()
{
    char num;
    string taco;
    cout<<"HI!!! Which Department U want to enter?:-"<<endl;
    cout<<" 1) Grocery store"<<endl;
    cout<<" 2) Electronics store"<<endl;
    cout<<" 3) Eatables"<<endl;
    cout<<" 4) Fashion"<<endl;
    cout<<" 5) Bathroom Products"<<endl;
    cout<<" 6) EXIT"<<endl;
    cout<<" Choose Department"<<endl;
    cin>>num;
    if(num == '1')
    {   int numbers;
    do{
        taco="itemlist.txt";
        printItemList1(taco);
        customerclaculation(taco);
        cout<<"Continue Shopping?(1/0)"<<endl;
        cin>>numbers;
    }while(numbers!=0);
    }
    else if(num == '2')
    {   int numbers;
    do{
        taco="itemlist1.txt";
        printItemList1(taco);
        customerclaculation(taco);
        cout<<"Continue Shopping?(1/0)"<<endl;
        cin>>numbers;
    }while(numbers!=0);
    }
    else if(num == '3')
    {   int numbers;
    do{
        taco="itemlist2.txt";
        printItemList1(taco);
        customerclaculation(taco);
        cout<<"Continue Shopping?(1/0)"<<endl;
        cin>>numbers;
    }while(numbers!=0);
    }
    else if(num == '4')
    {   int numbers;
    do{
        taco="itemlist3.txt";
        printItemList1(taco);
        customerclaculation(taco);
        cout<<"Continue Shopping?(1/0)"<<endl;
        cin>>numbers;
    }while(numbers!=0);
    }
    else if(num == '5')
    {   int numbers;
    do{
        taco="itemlist4.txt";
        printItemList1(taco);
        customerclaculation(taco);
        cout<<"Continue Shopping?(1/0)"<<endl;
        cin>>numbers;
    }while(numbers!=0);
    }
    else{
        cout<<"Invalid Department"<<endl;
        return;
    }

}
void mnya()
{  int mine;
    HashTable hashTable;
    string filename = "credit.txt";

    hashTable.loadHashTableFromFile(filename);
    int chum;
     do{
    cout<<"SO SOON!!!"<<endl;
        cout<<"THINK AGAIN?(1/0)"<<endl;
        
        cin>>mine;
        switch(mine)
        {
            case 0:maintainace();
            
                    do{
                        cout<<" 1)Check other Departments?"<<endl;
                        cout<<" 2)EXIT Towards BILLING?"<<endl;
                        cout<<" 3)Enter ur Choice:-"<<endl;
                        cin>>chum;
                        switch(chum)
                        {
                            case 1:maintainace();
                                    break;
                            case 2:mnya();
                                     break;
                            default:break;
                        }
                        break;
                    }while(chum<3);
                    break;
            default:cout<<"THANKYOU!!! BELOW IS THE BILL DISPLAYED"<<endl;
                    string taco="Customerlist.txt";
                    double value=displayBill(taco);
                    checkingfunction();
                    int result = remove("Customerlist.txt");
                    if (result != 0) {
                         cout << "Error deleting file." << endl;
                    }
                    int result1 = remove("Customerlist1.txt");
                    if (result1 != 0) {
                         cout << "Error deleting file." << endl;
                    }
                    int result2 = remove("Customerlist2.txt");
                    if (result != 0) {
                         cout << "Error deleting file." << endl;
                    }

                     
                    cout<<"Payment via cash or card?(1/0)"<<endl;
                    int rum;
                    cin>>rum;
                    if(rum==1)
                    {
                            cout<<"Payment must me made at the Counter and the Items can be collected from there.Thank You"<<endl;
                            cout<<"Amount to be paid is:- "+ to_string(value)<<endl;
                            cout<<endl;
                            exit(0);
                    }
                    else
                     {  
                     string creditCardNumber;
                     cout << "Enter credit card number: ";
                    cin >> creditCardNumber;
                    CreditCard* card = hashTable.findCreditCard(creditCardNumber);
                    if (card != nullptr) {
                    cout << "Credit Card Number: " << card->creditCardNumber << endl;
                    cout << "Available Balance: " << card->availableBalance << endl;
                    cout<<"Thankyou Transaction was Successfull,Please Collect ur items at the nearby desk"<<endl;
                            exit(0);
                }
                else {
                    cout << "Credit card not found." << endl;
                    exit(0);
                }
                        
                        
                            
                    }
        }
        }while(mine!=0);
}
void CUSTOMER()
{
    int chum;
    maintainace();
    
    do{
    cout<<" 1)Check other Departments?"<<endl;
    cout<<" 2)EXIT Towards BILLING?"<<endl;
    cout<<" 3)Enter ur Choice:-"<<endl;
    cin>>chum;
    switch(chum)
    {
        case 1:maintainace();
                break;
        case 2:mnya();
                break;
        default:break;
    }
    }while(chum<3);
    

}
void createEmployeeFile() {
    ofstream employeeFile(EMPLOYEE_FILE);
    employeeFile.close();
}

// Function to create an index file
void createIndexFile() {
    ofstream indexFile(INDEX_FILE);
    indexFile.close();
}

// Function to insert employee information
// Function to insert employee information
void insertEmployee(const Employee& employee) {
    ofstream employeeFile(EMPLOYEE_FILE, ios::app);
    employeeFile << employee.employeeId << "|" << employee.employeeName << "|"
                 << employee.address << "|" << employee.emailAddress << endl;
    employeeFile.close();
}

// Function to insert into index file
void insertIndex(int employeeId, int filePosition) {
    ofstream indexFile(INDEX_FILE, ios::app);
    indexFile << employeeId << "|" << filePosition << endl;
    indexFile.close();
}

// Function to insert employee and update index
// Function to insert employee and update index
void insertEmployeeAndUpdateIndex(const Employee& employee) {
    ofstream employeeFile(EMPLOYEE_FILE, ios::app | ios::binary);
    employeeFile.seekp(0, ios::end); // Seek to the end of the employee file
    int filePosition = employeeFile.tellp(); // Get the current position in the employee file
    employeeFile << employee.employeeId << "|" << employee.employeeName << "|"
                 << employee.address << "|" << employee.emailAddress << endl;
    employeeFile.close();

    insertIndex(employee.employeeId, filePosition);
}




// Function to find a particular employee
void findEmployee(int employeeId) {
    ifstream indexFile(INDEX_FILE);
    string indexLine;
    bool found = false;

    while (getline(indexFile, indexLine)) {
        stringstream ss(indexLine);
        string eId, filePos;
        getline(ss, eId, '|');
        getline(ss, filePos, '|');

        if (stoi(eId) == employeeId) {
            ifstream employeeFile(EMPLOYEE_FILE);
            employeeFile.seekg(stoi(filePos), ios::beg);

            string empLine;
            getline(employeeFile, empLine);

            cout << "Employee Details:" << endl;
            cout << empLine << endl;

            employeeFile.close();
            found = true;
            break;
        }
    }

    indexFile.close();

    if (!found) {
        cout << "Employee not found." << endl;
    }
}

// Function to delete an employee information


// Function to display information for all employees
void displayAllEmployees() {
    ifstream employeeFile(EMPLOYEE_FILE);
    string empLine;

    cout << "All Employees:" << endl;

    while (getline(employeeFile, empLine)) {
        cout << empLine << endl;
    }

    employeeFile.close();
}



// Function to delete an employee
void deleteEmployee() {
    string name, password, department, line;
    bool found_employee = false;
    // Open the file for reading and writing
    ifstream infile("employees.txt");
    ofstream outfile("temp.txt");
    if (infile.is_open() && outfile.is_open()) {
        cout << "Enter employee name to delete: ";
        getline(cin, name);
        cout << "Enter department number: ";
        getline(cin, department);

        // Search for the employee's data in the file
        while (getline(infile, line)) {
            // Split the line into its components
            size_t pos1 = line.find("|");
            if (pos1 == string::npos) {
                continue;  // Invalid line, skip it
            }
            size_t pos2 = line.find("|", pos1+1);
            if (pos2 == string::npos) {
                continue;  // Invalid line, skip it
            }
            string emp_name = line.substr(0, pos1);
            string emp_password = line.substr(pos1+1, pos2-pos1-1);
            string emp_department = line.substr(pos2+1);

            // Check if the employee matches
            if (emp_name == name && emp_department == department) {
                found_employee = true;
                continue;
            }

            // Write the line to the output file
            outfile << emp_name << "|" << emp_password << "|" << emp_department << endl;
        }
        infile.close();
        outfile.close();
        if (found_employee) {
            // Delete the original file and rename the temporary file
            remove("employees.txt");
            rename("temp.txt", "employees.txt");
            cout << "Employee deleted successfully." << endl;
        } else {
            remove("temp.txt");
            cout << "Invalid operation: Employee name and department number do not match." << endl;
        }
    } else {
        cout << "Error occurred while deleting employee." << endl;
    }
}
void printItemList(string tako) {
    string line;
    ifstream infile(tako);
    if (infile.is_open()) {
        // Print the header row
        cout <<  setw(30) << left << "Item Name" << setw(15) << left << "Quantity" << setw(10) << left << "Price" << setw(10) << left <<"Item-ID" << setw(10) << left << "Stocks_left" << endl;
        cout << setfill('-') << setw(80) << "" << endl;
        cout << setfill(' ');
        // Print each item in a row
        while (getline(infile, line)) {
            size_t pos = line.find("|");
            string itemName = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find("|");
            string itemQuantity = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find("|");
            string itemValue = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find("|");
            string item_id = line.substr(0, pos);
            line.erase(0, pos + 1);
            string stocks_left = line;
            cout <<setw(30) << left << itemName << setw(15) << left << itemQuantity << setw(10) << left << itemValue<< setw(10) << setw(10) << left << item_id<< setw(10) << left <<stocks_left << endl;
        }
        infile.close();
    } else {
        cout << "Error opening file." << endl;
    }
}
void displayItemsofDepartment(){
    int choice,value;
    string taco;
    do{
    cout<<"enter the department number: (Enter 6 for Exit)"<<endl;
    cin>>choice;
    if(choice == 1)
    {
        taco="itemlist.txt";
        cout<<"DEPARTMENT-General Groceries"<<endl;
        printItemList(taco);
        cout<<endl;
    }
    else if(choice ==2)
    {
        taco="itemlist1.txt";
        cout<<"DEPARTMENT-Electronics"<<endl;
        printItemList(taco);
        cout<<endl;
    }
     else if(choice ==3)
    {
        taco="itemlist2.txt";
        cout<<"DEPARTMENT-Eatables"<<endl;
        printItemList(taco);
        cout<<endl;
    }
     else if(choice ==4)
    {
        taco="itemlist3.txt";
        cout<<"DEPARTMENT-Fashion"<<endl;
        printItemList(taco);
        cout<<endl;
    }
     else if(choice ==5)
    {
        taco="itemlist4.txt";
        cout<<"DEPARTMENT-Bathroom Products"<<endl;
        printItemList(taco);
        cout<<endl;
    }
    }while(choice<6);
    cout<<"DO YOU WISH TO DISPLAY ALL ITEMS OF ALL DEPARTMENTS?(1/0)"<<endl;
    cin>>value;
    if(value == 1)
    {
        taco="itemlist.txt";
        cout<<"DEPARTMENT-General Groceries"<<endl;
        printItemList(taco);
        cout<<endl;
        taco="itemlist1.txt";
        cout<<"DEPARTMENT-Electronics"<<endl;
        printItemList(taco);
        cout<<endl;
        taco="itemlist2.txt";
        cout<<"DEPARTMENT-Eatables"<<endl;
        printItemList(taco);
        cout<<endl;
         taco="itemlist3.txt";
        cout<<"DEPARTMENT-Fashion"<<endl;
        printItemList(taco);
        cout<<endl;
        taco="itemlist4.txt";
        cout<<"DEPARTMENT-Bathroom Products"<<endl;
        printItemList(taco);
        cout<<endl;
    }

}



void admin_options(){
    int choice;
      Employee employee;
      HashTable hashTable;
    string filename = "credit.txt";
    string creditCardNumber, pin;

    hashTable.loadHashTableFromFile(filename);

    ofstream employeeFile(EMPLOYEE_FILE, ios::app);
        do
        {
        cout<<"----- ADMIN OPERATIONS-----"<<endl;
        
        cout << "1. Show employee details"<<endl;
        cout<<  "2. Search for a Particular Employee"<<endl;
        cout << "3. Display all the items of a particular department"<<endl;
        cout<<  "4. Add a new employee recruit" << endl;
        cout << "5. Delete employee username and password" << endl;
        cout<< "6. Enter the credit-card details"<<endl;
        cout<<  "7. EXIT" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // To ignore the newline character in the input buffer
        switch (choice) {
            case 1: displayAllEmployees();
                cout<<"\n";
                break;
            break;
            case 3:cout<<endl;
            displayItemsofDepartment();
            break;
            case 2:int employeeId;
                cout << "Enter Employee ID: ";
                cin >> employeeId;
                findEmployee(employeeId);
                cout<<"\n";
                break;
            case 4:
              
                cout << "Enter Employee ID: ";
                cin >> employee.employeeId;
                cout << "Enter Employee Name: ";
                cin.ignore();
                getline(cin, employee.employeeName);
                cout << "Enter Address: ";
                getline(cin, employee.address);
                cout << "Enter Email Address: ";
                getline(cin, employee.emailAddress);

                 insertEmployeeAndUpdateIndex(employee);

                cout << "Employee inserted successfully." << endl;
                cout<<endl;
                break;
            case 5:
            deleteEmployee();          
            break;
            case 6:
                
                double availableBalance;
                cout << "Enter credit card number: ";
                cin >> creditCardNumber;
                cout << "Enter pin: ";
                cin >> pin;
                cout << "Enter available balance: ";
                cin >> availableBalance;
                hashTable.insertCreditCard(creditCardNumber, pin, availableBalance);
                cout << " Save hash table to? (1/0)" << endl;
                int aaa;
                cin>>aaa;
                if(aaa==1)
                {
                hashTable.saveHashTableToFile(filename);
                }
                else
                {
                
                }
                break;
            default:
            system("cls");
            cout<<"Logging out Successfully and jumping to the main Screen"<<endl;
            cout<<endl;
            break;
            }
            } while (choice<5);
}
void ADMIN(){
    string admin_username, admin_password, admin_stored_username, admin_stored_password;
    ifstream infile("admin.txt");
    if (infile.is_open()) {
        // Read the stored username and password from the file
        getline(infile, admin_stored_username);
        getline(infile, admin_stored_password);
        infile.close();
        // Get input from the user for the username and password
        cout << "Enter username: ";
        cin>>admin_username;
        cout << "Enter password: ";
        cin>>admin_password;
        // Compare the input username and password to the stored values
        if (admin_username == admin_stored_username && admin_password == admin_stored_password) {
            cout << "You have access." << endl;
            admin_options();
        } else {
            cout << "You don't have access." << endl;
            cout<<endl;
        }
    } else {
        cout << "Unable to open file." << endl;
        
    }
}
void addEmployee12() {
    string name, password, department, line;
    int departmentnum;
    cout << "Enter employee name: ";
    cin>>name;
    cout << "Enter password: ";
    cin>>password;
    do{
        cout << "Enter department number: ";
        cin>>departmentnum;
        if(departmentnum<5)
        {
            department=to_string(departmentnum);
            break;
        }
        else{
            cout<<"Invalid Department"<<endl;
        }
    }while(departmentnum>5);
    // Append the employee data to the file
    ofstream outfile("employees.txt", ios::app);
    if (outfile.is_open()) {
        line = name + "|" + password + "|" + department + "\n";
        outfile << line; // Add a newline character after the employee data
        outfile.close();
        cout << "Employee details updated successfully." << endl;
    } else {
        cout << "Error occurred while updating employee details." << endl;
    }
}
void search_item(string itemName, string tako) {
    string line;
    ifstream infile(tako);
    if (infile.is_open()) {
        // Create an index vector to store the positions of the item names in the file
        vector<long> index;
        // Read each line and search for the item name
        long pos = 0;
        while (getline(infile, line)) {
            if (line.find(itemName) != string::npos) {
                // Store the position of the matching item in the index vector
                cout<<"Successful Search"<<endl;
                cout<<endl;
                index.push_back(pos);
            }
            pos = infile.tellg();
        }
        // If no items were found, output an error message and return to main function
        if (index.empty()) {
            cout << "Unsuccessful search." << endl;
            return;
        }
        // Print the header row for the table
        cout << setw(25) << left << "Item Name" << setw(15) << left << "Quantity" << setw(10) << left << "Price" << setw(10) << left << "Item_id" << setw(10) << left<< "Stocks_left" << endl;
        cout << setfill('-') << setw(80) << "" << endl;
        cout << setfill(' ');
        // Read the details of the matching items using the index vector
        infile.clear();
        infile.seekg(0);
        for (long idx : index) {
            infile.seekg(idx);
            getline(infile, line);
            // Extract the item details from the line using string manipulation functions
            size_t pos = line.find("|");
            string itemQuantity = line.substr(pos + 1);
            pos = itemQuantity.find("|");
            string itemValue = itemQuantity.substr(pos + 1);
            itemQuantity = itemQuantity.substr(0, pos);
            pos = itemValue.find("|");
            string Item_id = itemValue.substr(pos + 1);
            itemValue = itemValue.substr(0, pos);
            pos = Item_id.find("|");
            string stocks_left = Item_id.substr(pos+1);
            Item_id =Item_id.substr(0,pos);
            // Print the item details in tabular format
            cout << setw(25) << left << itemName << setw(15) << left << itemQuantity << setw(10) << left << itemValue << setw(10) << left << Item_id << setw(10) << left << stocks_left << endl;
        }
        infile.close();
    } else {
        cout << "Error opening file." << endl;
    }
}

void addItem(string taco) {
     addItems(taco);
}
// Function to print the items list in tabular format

void delete_items(string taco) {
    string item_name, line;
    bool found = false;
    ifstream infile(taco);
    ofstream temp("temp.txt");
    cout << "Enter the name of item to delete: ";
    cin >> item_name;
    while (getline(infile, line)) {
        if (line.find(item_name) != string::npos) {
            found = true;
            continue;
        }
        temp << line << "\n";
    }
    infile.close();
    temp.close();
    remove(taco.c_str());
    rename("temp.txt", taco.c_str());
    if (found) {
        cout << "Item deleted successfully." << endl;
    } else {
        cout << "Item not found." << endl;
    }
}
void Search_items(string tako)
{
    string itemName;
    cout << "Enter item name: ";
    cin>>itemName;
    cout<<endl;
    search_item(itemName,tako);
    cout<<endl;
}
void employeeChecking() {
    string employee_name, line;
    bool found_employee = false;
    // Get the employee name from the user
    cout << "Enter the name of the employee to check: ";
    cin>>employee_name;
    // Open the employees file for reading
    ifstream infile("employees.txt");
    if (infile.is_open()) {
        // Check each line in the file for the employee name
        while (getline(infile, line)) {
            size_t pos = line.find("|");
            if (pos != string::npos && line.substr(0, pos) == employee_name) {
                found_employee = true;
                break;
            }
        }
        infile.close();
        // Output the result
        if (found_employee) {
            cout << "Employee " << employee_name << " exists in the file." << endl;
            string name, password, stored_name, stored_password, stored_department;
        bool found_employee = false;
        cout<<"enter the UserID: ";
        cin>>name;
         // Open the file
        ifstream infile("employees.txt");
        if (infile.is_open()) {
        // Search for the employee's username in the file
        while (getline(infile, stored_name, '|')) {
            getline(infile, stored_password, '|');
            getline(infile, stored_department);
        // Remove any whitespace from stored_name
            stored_name.erase(0, stored_name.find_first_not_of(" \t\r\n"));
            if (name == stored_name) {
                found_employee = true;
                break;
            }
            }

        infile.close();
        if (found_employee) {
            // Prompt for the employee's password
            for (int i = 0; i < 3; i++) {
                cout << "Enter password: ";
                cin>>password;
                if (password == stored_password) {
                    string tako;
                    int choice;
                    cout << "Hello, " << stored_name << " of department " << stored_department << "!" << endl;
                    if(stoi(stored_department) == 1)
                    {
                        tako="itemlist.txt";
                    }
                    else if(stoi(stored_department) == 2)
                    {
                        tako="itemlist1.txt";
                    }
                    else if(stoi(stored_department) == 3)
                    {
                        tako="itemlist2.txt";

                    }
                    else if(stoi(stored_department) == 4)
                    {
                        tako="itemlist3.txt";
                    }
                    else {
                        tako="itemlist4.txt";
                    }
                    do{
                    cout<< "----EMPLOYEE OPERATIONS----"<<endl;
                    cout << "1. Add item" << endl;
                    cout << "2. Delete item" <<endl;
                    cout << "3. Search a particular item"<<endl;
                    cout << "4. Display items" << endl;
                    cout << "5. Exit" << endl;
                    cout << "Enter your choice: ";
                    cout<<endl;
                    cin >> choice;
                    switch (choice) {
                                    case 1:
                                        addItem(tako);
                                        break;
                                    case 2:
                                        delete_items(tako);
                                         break;
                                    case 3:
                                        Search_items(tako);
                                        break;
                                     case 4:
                                        printItemList(tako);
                                        cout<<endl;
                                        break;
                                     default:
                                        system("cls");
                                        cout << "Going to the main Screen and Logging Out!!!" << endl;
                                        cout<<endl;
                                         break;
                                        }
                    }while(choice<5);
                    return;
                    
                } else {
                    cout << "Incorrect password. Please try again." << endl;
                    
                }
                
            }
            system("cls");
            cout << "Too many incorrect attempts. Access denied." << endl;
            return;
            
                 
                 
        } else {
            cout << "employee password generation not done." << endl;
            cout<< "Want to generate password?(1/0):" <<endl;
            int num;
            cin>>num;
            if(num==1)
            {
                    addEmployee12();
            }
            else{
                cout<<"Contact ur admin for more information..."<<endl;
            }            
        }
    } else {
        cout << "Unable to open file." << endl;
       
    }
        } else {
            cout << "U are not an Employee,Register yourself with Admin" << endl;
            return;
        }
    } else {
        cout << "Error: could not open employees file." << endl;
    }
}
void EMPLOYEE123(){
    employeeChecking();
}
int main() {
    int choice;
    do{
    cout<<"HELLO WELCOME TO THE GROCERY SHOPPING SYSTEM"<<endl;
    cout<<"PLEASE SELECT THE BELOW OPTIONS"<<endl;
    cout<<"1)ADMIN LOGIN"<<endl;
    cout<<"2)EMPLOYEE LOGIN"<<endl;
    cout<<"3)CUSTOMER LOGIN"<<endl;
    cout<<"4)EXIT"<<endl;
    cout<<"ENTER UR CHOICE:"<<endl;
    cin>>choice;
    switch(choice)
    {
        case 1:ADMIN();
                break;
        case 2:EMPLOYEE123();
                break;
        case 3:CUSTOMER();
                break;
        default:cout<<"THANK YOU VISIT AGAIN!!!"<<endl;
        break;
    }
    }while(choice<4);
    return 0;
}

