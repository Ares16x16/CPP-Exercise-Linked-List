//description: program to print the most popular pages and users record

#include<iostream>
#include<algorithm>
#include<string>
#include<map>
#include<vector>

using namespace std;

struct Page {
    int id;
    string path;
    int counter;
    Page(int id, string path) {
        this->id = id;
        this->path = path;
        counter = 0;
    };
};

// This function can facilitate sorting
bool operator<(const Page& a, const Page& b) {
    return (a.id < b.id);
}

vector<Page> pages;

struct User {
    int id;
    vector<string> visits;
    User(int id) {
        this->id = id;
    };
    void add_visit(int page_id) {
        Page p(page_id, "");
        vector<Page>::iterator iter = lower_bound(pages.begin(), pages.end(), p);
        if (iter->id == page_id)
            visits.push_back(iter->path);
    };
    int size() const {
        return visits.size();
    };
    void print_visits() {
        sort(visits.begin(), visits.end());
        vector<string>::iterator iter;
        for (iter = visits.begin(); iter != visits.end(); iter++) {
            cout << "- " << *iter << endl;
        }
    }
};

vector<User> users;

// Please implement the following function to facilitate the sorting of users
bool operator<(const User& a, const User& b) { //compare the size of users
    if (a.size() == b.size())
        return (a.id > b.id);
    else
        return (a.size() < b.size());
}

// Please implement the following function
void add_page(const Page& p) {
    pages.push_back(p);   //add into pages
    sort(pages.begin(), pages.end());
}

// Please implement the following function
bool cmp_page_count(const Page& a, const Page& b) {
    return (a.counter < b.counter);  //compare counter value
}

// Please implement the following function
void print_pages(int number) {
    for (int i = number - 1 ; i >= 0; i--) {
      cout << pages.back().counter  << ":" << pages.back().path << endl;  //print the last element and pop back
      pages.pop_back();
      
    }
}

// Please implement the following function
void add_user(User u) {
    users.push_back(u); //add a user to the vector
}

// Please implement the following function
void add_visit(int page_id) {
    users.back().add_visit(page_id); //add visit to the last user
}

// Please implement the following function
void print_users(int number) {
    for (int i = number -1 ; i >= 0; i--) {
      cout  << users.back().size() << ":" << users.back().id << endl; //print the last element and pop back
      users.back().print_visits();
      users.pop_back();
    }
}

int main() {

    string type;
    while (cin >> type) {
        if (type == "USER") {
            int user_id;
            cin >> user_id;
            User u(user_id);
            add_user(u);
        }
        else if (type == "PAGE") {
            int page_id;
            string page_path;
            cin >> page_id;
            cin >> page_path;
            Page p(page_id, page_path);
            add_page(p);
        }
        else if (type == "VISIT") {
            int page_id;
            cin >> page_id;
            Page p(page_id, "");

            vector<Page>::iterator iter = lower_bound(pages.begin(), pages.end(), p);
            if (iter->id == p.id) {
                iter->counter++;
            }
            add_visit(page_id);
        }
    }
    sort(pages.begin(), pages.end(), cmp_page_count);
    cout << "*** 5 most popular pages ***" << endl;
    print_pages(5);
    sort(pages.begin(), pages.end());

    sort(users.begin(), users.end());
    cout << "*** 5 most active users ***" << endl;
    print_users(5);

    return 0;

}
