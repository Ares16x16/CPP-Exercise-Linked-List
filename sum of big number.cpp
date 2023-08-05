//description: program to add 2 big numbers using linked list method

#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include <string> 
#include <cstdlib>

using namespace std;

struct Node
{
    int value;
    Node* next;
};

//create a new node
struct Node* newNode(int value)
{
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->value = value;
    node->next = NULL;
    return node;
}

// output the linked list
void print_list(Node* head)
{
    Node* current = head;
    while (current != NULL)
    {
        // process the current node, e.g., print the content
        cout << current->value << " -> ";
        current = current->next;
    }
    cout << "NULL\n";
}

// output the large number stored in the linked list
void print_num(Node* head)
{
    Node* current = head;
    while (current != NULL)
    {
        if (current == head)
            cout << current->value;
        else
            cout << setw(5) << setfill('0') << current->value;
        current = current->next;
    }
}

void push(struct Node** head, int data)
{
    // create a new linked list node from the heap
    struct Node* node = newNode(data);
    node->next = *head;
    *head = node;
}

//loop through the whole list and push in the beginning
void reverse(struct Node** head)
{
    struct Node* out = NULL;
    struct Node* current = *head;

    // traverse the list
    while (current)
    {
        struct Node* next = current->next;

        current->next = out;
        out = current;

        // continue
        current = next;
    }
    //ptr arrangment
    *head = out;
}

//add 2 linked list
void add(struct Node* first, struct Node* second, struct Node** head)
{
    struct Node* previous_node = NULL;
    // initialize
    int carry = 0;

    // run until all are empty
    while (first || second)
    {
        // add the data in same index and see if there are any carry bit
        int sum = 0;
        if (first) {
            sum += first->value;
        }
        if (second) {
            sum += second->value;
        }
        sum += carry;

        // if 2 digit, then reduce it to single digit and update the carry bit
        carry = sum / 10;
        sum = sum % 10;

        struct Node* node = newNode(sum);

        if (*head == NULL)
        {
            previous_node = node;
            *head = node;
        }
        else 
        {
            previous_node->next = node;
            previous_node = node;
        }

        if (first) 
        {
            first = first->next;
        }

        if (second) 
        {
            second = second->next;
        }
    }

    if (carry != 0) {
        push(&(previous_node->next), carry);
    }
}

struct Node* addition(struct Node* first, struct Node* second)
{
    struct Node* out = NULL;

    //reverse the 2 nodes
    reverse(&first);
    reverse(&second);
    add(first, second, &out); //add tgt
    reverse(&out);
    return out;
}

// insert a value as a node to the head of a linked list
void head_insert(Node*& head, int v)
{
    Node* p = new Node;
    p->value = v;
    p->next = head;
    head = p;
}

// delete the head node from a linked list
void delete_head(Node*& head)
{
    if (head != NULL) {
        Node* p = head;
        head = head->next;
        delete p;
    }
}


// free an entire linked list
void delete_list(Node*& head)
{
    while (head != NULL)
    {
        delete_head(head);
    }
}

// double the capacity of an array
// array: input array
// size: original size of array, updated to new size of array
void grow_array(char*& array, int& size)
{
    if (array == NULL)
        return;

    int newSize = size * 2;

    // doubled the size of the array;
    char* tmp = new char[newSize];
    // copy original contents
    for (int i = 0; i < size; ++i)
        tmp[i] = array[i];

    delete[] array;

    array = tmp;
    size = newSize;
}

// get a number from a user
// by reading character by character until a space is hit
// use dynamic array to store the digits
// digits:  character array that stores the digits of the number
// numDigits: number of digits read from input
void input_num(char*& digits, int& numDigits)
{
    int arraysize = 32;
    digits = new char[arraysize];
    char c;
    int numRead = 0;

    // read each digit as a character until a white space is hit
    c = cin.get();
    while (!isspace(c))
    {
        if (numRead >= arraysize)
            grow_array(digits, arraysize);

        digits[numRead] = c;
        numRead++;
        
        c = cin.get();
    }

    numDigits = numRead;

}

int reversDigits(int num)
{
    int rev_num = 0;
    while (num > 0) {
        rev_num = rev_num * 10 + num % 10;
        num = num / 10;
    }
    return rev_num;
}

void input_num_output(char*& digits, int& numDigits, string a)
{
    int arraysize = 32;
    digits = new char[arraysize];
    char c;
    int numRead = 0;


    for (int i = 0; i < a.length(); i++)
    {
        c = a[i];
        if (numRead >= arraysize)
            grow_array(digits, arraysize);

        digits[numRead] = c;
        numRead++;
    }

    numDigits = numRead;

}

Node* create_num_list()
{
    // TASK 1a: declare a pointer pointing to the head of the link list
    Node* head = NULL;

    string str;
    char* digits = NULL;  // a dynamic array for storing an input number
    int numDigits;
    int val;

    // get a number from the user
    input_num(digits, numDigits);

    str.clear();
    for (int i = numDigits - 1; i >= 0; --i) {
        str = digits[i] + str;
        if (str.length() == 1) {
            val = atoi(str.c_str());

            // TASK 1b: insert a value as a node to the head of the linked list
            head_insert(head, val);

            str.clear();
        }
    }
    // the digits array is scanned and there are still digits
    // stored in str that are not inserted into the list yet
    if (!str.empty()) {
        val = atoi(str.c_str());

        // TASK 1c: insert a value as a node to the head of the linked list
        head_insert(head, val);
    }

    if (digits != NULL) {
        delete[] digits;
    }

    // TASK 1d: return the pointer to the linked list
    return head;
}

Node* create_num_list_output(string a)
{
    // TASK 1a: declare a pointer pointing to the head of the link list
    Node* head = NULL;

    string str;
    char* digits = NULL;  // a dynamic array for storing an input number
    int numDigits;
    int val;
    bool first_time = true;

    // get a number from the user
    //input_num(digits, numDigits);

    input_num_output(digits, numDigits, a);

    str.clear();
    for (int i = 0; i < numDigits; ++i) {
        str = digits[i] + str;
        if (numDigits % 3 == 2 and first_time)
        {
            if (str.length() == 2) {
                first_time = false;
                val = atoi(str.c_str());
                val = reversDigits(val);

                head_insert(head, val);

                str.clear();
            }
        }
        else if (numDigits % 3 == 1 and first_time)
        {
            if (str.length() == 1) {
                first_time = false;
                val = atoi(str.c_str());
                val = reversDigits(val);

                head_insert(head, val);

                str.clear();
            }
        }
        else
        {
            if (str.length() == 3) {
                val = atoi(str.c_str());
                val = reversDigits(val);

                head_insert(head, val);

                str.clear();
            }
        }
    }
    // the digits array is scanned and there are still digits
    // stored in str that are not inserted into the list yet
    if (!str.empty()) {
        val = atoi(str.c_str());
        val = reversDigits(val);
        // TASK 1c: insert a value as a node to the head of the linked list
        head_insert(head, val);
    }

    if (digits != NULL) {
        delete[] digits;

    }

    // TASK 1d: return the pointer to the linked list
    return head;
}

// return the length of a linked list
int list_length(Node* head)
{
    // TASK 3: Modify this print function to one that
    // count the number of nodes in a linked list

    int num = 0;

    Node* current = head;
    while (current != NULL)
    {
        // process the current node, e.g., print the content
        ++num;
        current = current->next;
    }

    return num;
}

void print_ans(Node* head)
{
    Node* current = head;
    while (current != NULL)
    {
        // process the current node, e.g., print the content
        cout << current->value;
        current = current->next;
    }
}

string convert_list(Node* head)
{
    string conversion = "";

    Node* temp = head;
    while (temp != NULL)
    {
        conversion += to_string(temp->value);
        temp = temp->next;
    }
    return conversion;
}

int main()
{
    Node* n1, * n2, * output1, * output2, * output3;
    char* cal1 = NULL;
    int cal2;
    string str1, str2, str3;

    n1 = create_num_list();
    cin.get();       // skip the '>' sign
    cin.get();       // the space after the '>' sign
    n2 = create_num_list();

    str1 = convert_list(n1);
    str2 = convert_list(n2);
    output1 = create_num_list_output(str1);
    output2 = create_num_list_output(str2);
    

    // TASK 2: call print_list() on n1 and n2 for checking
    print_list(output1);
    print_list(output2);

    Node *ans = addition(n1, n2);
    str3 = convert_list(ans);
    output3 = create_num_list_output(str3);
    print_list(output3);
    print_ans(ans);

    // TASK 5: free the linked lists
    delete_list(n1);
    delete_list(n2);
    delete_list(ans);
    delete_list(output1);
    delete_list(output2);
    delete_list(output3);

    return 0;
}
