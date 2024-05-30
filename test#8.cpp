/*
PHASYA VIGO KHALIL 235150300111004
GILANG SHIDO FAIZALHAQ 235150300111011
ADIKA RIZKY PRIMANTORO 235150301111011
MUHAMMAD SYAUQI FADILLAH 235150307111007
MUHAMMAD RAKA NAUFAL 235150307111004
*/
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

struct followNode {
    string name;
    followNode* next;
    followNode(string newUser) : name(newUser), next(nullptr) {}
};

class User {
public:
    string username;
    string minat[3];
    User* nextMember;
    followNode* headFollower;
    followNode* headFollowing;
    int followerCount, followingCount;

    User(stringstream &ss, string name) {
        username = name;
        ss >> minat[0] >> minat[1] >> minat[2];
        nextMember = nullptr;
        headFollower = nullptr;
        headFollowing = nullptr;
        followerCount = 0;
        followingCount = 0;
    }

    void addFollower(string newUser) {
        followNode* newFollower = new followNode(newUser);
        newFollower->next = headFollower;
        headFollower = newFollower;
        followerCount++;
    }

    void addFollowing(string newUser) {
        followNode* newFollowing = new followNode(newUser);
        newFollowing->next = headFollowing;
        headFollowing = newFollowing;
        followingCount++;
    }
};

class Group {
public:
    User* headMember;
    User* tailMember;
    Group* nextGroup;
    int group_id;

    Group() : headMember(nullptr), tailMember(nullptr), nextGroup(nullptr), group_id(0) {}

    Group(User* newUser, int id) : headMember(newUser), tailMember(newUser), nextGroup(nullptr), group_id(id) {}

    void addMember(User* newUser) {
        if (tailMember) {
            tailMember->nextMember = newUser;
        } else {
            headMember = newUser;
        }
        tailMember = newUser;
    }
};

class nodeKata {
public:
    string data;
    nodeKata* next;
    int rankMinat;

    nodeKata(string newData) : data(newData), next(nullptr), rankMinat(1) {}
};

class textOutputContainer {
public:
    nodeKata* headData;
    nodeKata* tailData;
    nodeKata* headMinat;

    textOutputContainer() : headData(nullptr), tailData(nullptr), headMinat(nullptr) {}

    ~textOutputContainer() {
        while (headData != nullptr) {
            nodeKata* temp = headData;
            headData = headData->next;
            delete temp;
        }
    }

    void addString(string newData, int type) {
        switch (type) {
            case 1: {
                nodeKata* newKata1 = new nodeKata(newData);
                if (headData == nullptr) {
                    headData = newKata1;
                    tailData = newKata1;
                } else {
                    tailData->next = newKata1;
                    tailData = newKata1;
                }
                break;
            }
            case 2: {
                nodeKata* current = headData;
                while (current != nullptr) {
                    if (current->data == newData) {
                        return;
                    }
                    current = current->next;
                }

                nodeKata* newKata2 = new nodeKata(newData);
                if (headData == nullptr) {
                    headData = tailData = newKata2;
                } else {
                    tailData->next = newKata2;
                    tailData = newKata2;
                }
                break;
            }
            case 3: {
                nodeKata* current = headMinat;
                while (current != nullptr) {
                    if (current->data == newData) {
                        current->rankMinat += 1;
                        return;
                    }
                    current = current->next;
                }

                nodeKata* newKata3 = new nodeKata(newData);
                if (headMinat == nullptr) {
                    headMinat = newKata3;
                } else {
                    newKata3->next = headMinat;
                    headMinat = newKata3;
                }
                break;
            }
            default:
                break;
        }
    }

    nodeKata* merge(nodeKata* left, nodeKata* right) {
        nodeKata dummyHead("dummy");
        nodeKata* tail = &dummyHead;

        while (left != nullptr && right != nullptr) {
            if (left->data <= right->data) {
                tail->next = left;
                left = left->next;
            } else {
                tail->next = right;
                right = right->next;
            }
            tail = tail->next;
        }

        tail->next = (left != nullptr) ? left : right;
        return dummyHead.next;
    }

    nodeKata* mergeSort(nodeKata* head) {
        if (head == nullptr || head->next == nullptr)
            return head;

        nodeKata* slow = head;
        nodeKata* fast = head->next;

        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        nodeKata* mid = slow->next;
        slow->next = nullptr;

        return merge(mergeSort(head), mergeSort(mid));
    }

    void sortText() {
        headData = mergeSort(headData);
    }

    void addMinat(nodeKata*& minat) {
        if (headMinat == nullptr) {
            headMinat = minat;
        } else {
            minat->next = headMinat;
            headMinat = minat;
        }
    }
    void removeException(string username) {
        if (headData == nullptr) return;

        
        if (headData->data == username) {
            nodeKata* temp = headData;
            headData = headData->next;
            delete temp;
            return;
        }

        nodeKata* prev = headData;
        nodeKata* current = headData->next;

        while (current != nullptr) {
            if (current->data == username) {
                prev->next = current->next;
                if (current == tailData) {
                    tailData = prev;
                }
                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }
    }

    void sortMinat() {
        int highestMinat = -1;
        nodeKata* temp = headMinat;
        while (temp) {
            if (highestMinat < temp->rankMinat) {
                highestMinat = temp->rankMinat;
                headData = nullptr;
                addString(temp->data, 1);
            } else if (highestMinat == temp->rankMinat) {
                addString(temp->data, 1);
            }
            temp = temp->next;
        }
    }

    string printText() {
        string text;
        nodeKata* current = headData;
        while (current != nullptr) {
            text += current->data;
            if (current->next != nullptr) {
                text += ",";
            }
            current = current->next;
        }
        text += '\n';
        return text;
    }

    void printGroupTopic(){
        nodeKata* current = headData;
        while (current != nullptr){
            cout << current->data;
            current = current->next;
        }
    }
};

class App {
private:
    Group* headGroup;
    Group* tailGroup;
    int groupCounter;
    int numberOfGroup;

    void dfs(User* currentUser, const string& targetUser, textOutputContainer &visited, int currentDepth, int& minEdges) {
        if (currentUser->username == targetUser) {
            if (currentDepth < minEdges) {
                minEdges = currentDepth;
            }
            return;
        }
       
        visited.addString(currentUser->username, 2);

        followNode* currentFollowing = currentUser->headFollowing;
        while (currentFollowing != nullptr) {
            bool isVisited = false;
            nodeKata* temp = visited.headData;
            while (temp != nullptr) {
                if (temp->data == currentFollowing->name) {
                    isVisited = true;
                    break;
                }
                temp = temp->next;
            }

            if (!isVisited) {
                User* nextUser = findUser(currentFollowing->name);
                if (nextUser != nullptr) {
                    dfs(nextUser, targetUser, visited, currentDepth + 1, minEdges);
                }
            }
            currentFollowing = currentFollowing->next;
        }
        visited.removeException(currentUser->username);
    }

public:
    App() : headGroup(nullptr), tailGroup(nullptr), groupCounter(0), numberOfGroup(0) {}

    void insert(stringstream &ss, string name) {
        groupCounter++;
        User* newUser = new User(ss, name);
        Group* newGroup = new Group(newUser, groupCounter);
        if (headGroup == nullptr) {
            headGroup = tailGroup = newGroup;
        } else {
            tailGroup->nextGroup = newGroup;
            tailGroup = newGroup;
        }
        numberOfGroup++;
    }

    Group* findGroup(string username) {
        Group* currentGroup = headGroup;
        while (currentGroup) {
            User* currentUser = currentGroup->headMember;
            while (currentUser) {
                if (currentUser->username == username) {
                    return currentGroup;
                }
                currentUser = currentUser->nextMember;
            }
            currentGroup = currentGroup->nextGroup;
        }
        return nullptr;
    }

    User* findUser(string username) {
        Group* currentGroup = headGroup;
        while (currentGroup) {
            User* currentUser = currentGroup->headMember;
            while (currentUser) {
                if (currentUser->username == username) {
                    return currentUser;
                }
                currentUser = currentUser->nextMember;
            }
            currentGroup = currentGroup->nextGroup;
        }
        return nullptr;
    }

    void connect(string user1, string user2) {
        Group* yangFollow_Group = findGroup(user1);
        Group* diFollow_Group = findGroup(user2);

        if (!yangFollow_Group || !diFollow_Group) return;

        User* yangFollow = findUser(user1);
        User* diFollow = findUser(user2);

        if (!yangFollow || !diFollow) return;

        yangFollow->addFollowing(user2);
        diFollow->addFollower(user1);

        if (diFollow_Group->group_id == yangFollow_Group->group_id) {
            return;
        } else {
            User* pindahGroup = diFollow_Group->headMember;
            while (pindahGroup) {
                User* nextMember = pindahGroup->nextMember;
                yangFollow_Group->addMember(pindahGroup);
                pindahGroup = nextMember;
            }

            if (headGroup == diFollow_Group) {
                headGroup = diFollow_Group->nextGroup;
            } else {
                Group* prevGroup = headGroup;
                while (prevGroup && prevGroup->nextGroup != diFollow_Group) {
                    prevGroup = prevGroup->nextGroup;
                }

                if (prevGroup) {
                    prevGroup->nextGroup = diFollow_Group->nextGroup;
                }

                if (tailGroup == diFollow_Group) {
                    tailGroup = nullptr;
                    tailGroup = prevGroup;
                }
            }


            delete diFollow_Group;
            numberOfGroup--;
        }
    }

    void numgroup() const {
        cout << numberOfGroup << endl;
    }

    void mostfollowed() const {
        int highestFollower = -1;
        textOutputContainer obj;

        Group* currentGroup = headGroup;
        while (currentGroup) {
            User* currentUser = currentGroup->headMember;
            while (currentUser) {
                if (highestFollower < currentUser->followerCount) {
                    highestFollower = currentUser->followerCount;
                    obj.headData = nullptr;
                    obj.addString(currentUser->username, 1);
                } else if (highestFollower == currentUser->followerCount) {
                    obj.addString(currentUser->username, 1);
                }
                currentUser = currentUser->nextMember;
            }
            currentGroup = currentGroup->nextGroup;
        }

        obj.sortText();
        cout << obj.printText();
    }

    void suggestfriend(string username) {
        textOutputContainer obj;
    
        User* user1 = findUser(username);
        if (!user1) return;
    
    
        followNode* currentFollowing = user1->headFollowing;
        while (currentFollowing) {
            obj.addString(currentFollowing->name, 1);
            currentFollowing = currentFollowing->next;
        }
    
    
        currentFollowing = user1->headFollowing;
        while (currentFollowing) {
            User* friendUser = findUser(currentFollowing->name);
            if (friendUser) {
                
                followNode* followerOfFriend = friendUser->headFollower;
                while (followerOfFriend) {
                    if (followerOfFriend->name != username) {
                        obj.addString(followerOfFriend->name, 2);
                    }
                    followerOfFriend = followerOfFriend->next;
                }
    
                
                followNode* followingOfFriend = friendUser->headFollowing;
                while (followingOfFriend) {
                    if (followingOfFriend->name != username) {
                        obj.addString(followingOfFriend->name, 2);
                    }
                    followingOfFriend = followingOfFriend->next;
                }
            }
            currentFollowing = currentFollowing->next;
        }
    
        
        currentFollowing = user1->headFollowing;
        while (currentFollowing) {
            obj.removeException(currentFollowing->name);
            currentFollowing = currentFollowing->next;
        }
    
        obj.removeException(username);
    
        obj.sortText();
        cout << obj.printText();
        }

    void grouptopic() {
        textOutputContainer out;
        Group* currentGroup = headGroup;
        while (currentGroup) {
            textOutputContainer obj;
            User* currentUser = currentGroup->headMember;
            while (currentUser) {
                for (int i = 0; i < 3; i++) {
                    obj.addString(currentUser->minat[i], 3);
                }
                currentUser = currentUser->nextMember;
            }
            obj.sortMinat();
            obj.sortText();
            out.addString(obj.printText(),1);
            currentGroup = currentGroup->nextGroup;
        }
        out.sortText();
        out.printGroupTopic();

    }

    int mincuit(string user1, string user2) {
        User* startUser = findUser(user1);
        if (startUser == nullptr || findUser(user2) == nullptr) {
            return -1;
        }

        textOutputContainer visited; 
        int minEdges = INT_MAX;

        dfs(startUser, user2, visited, -1, minEdges);

        return (minEdges == INT_MAX) ? -1 : minEdges;
    }
};

class Node {
public:
    string data;
    Node* next;

    Node(const string &data) : data(data), next(nullptr) {}
};

// Kelas Queue untuk mengelola operasi antrian
class Queue {
private:
    Node* front;
    Node* rear;

public:
    Queue() : front(nullptr), rear(nullptr) {}

    void enqueue(const string &data) {
        Node* newNode = new Node(data);
        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    string dequeue() {
        if (front == nullptr) {
            return "";
        }

        Node* temp = front;
        string data = temp->data;
        front = front->next;

        if (front == nullptr) {
            rear = nullptr;
        }

        delete temp;
        return data;
    }

    bool isEmpty() const {
        return front == nullptr;
    }
};

int main() {
    App cuitcuit;
    string line;
    Queue iq;
    int n, m;

    cin >> n >> m;
    cin.ignore();

    for (int i = 0; i < n; i++) {
        string name;
        getline(cin, line);
        stringstream currLine(line);
        currLine >> name;
        cuitcuit.insert(currLine, name);
    }

    for (int i = 0; i < m; i++) {
        string user1, user2;
        getline(cin, line);
        stringstream currLine(line);
        currLine >> user1 >> user2;
        cuitcuit.connect(user1, user2);
    }

    while (getline(cin, line) && !line.empty()) {
        iq.enqueue(line);
    }

    while (!iq.isEmpty()) {
        string token = iq.dequeue();
        stringstream currLine(token);
        string command;
        currLine >> command;

        if (command == "insert") {
            string name;
            currLine >> name;
            cuitcuit.insert(currLine, name);
            cout << name << " inserted" << endl;
        } else if (command == "connect") {
            string user1, user2;
            currLine >> user1 >> user2;
            cuitcuit.connect(user1, user2);
            cout << "connect " << user1 << ' ' << user2 << " success" << endl;
        } else if (command == "mostfollowed") {
            cuitcuit.mostfollowed();
        } else if (command == "numgroup") {
            cuitcuit.numgroup();
        } else if (command == "grouptopic") {
            cuitcuit.grouptopic();
        } else if (command == "suggestfriend") {
            string user1;
            currLine >> user1;
            cuitcuit.suggestfriend(user1);
        } else if (command == "mincuit") {
            string user1, user2;
            currLine >> user1 >> user2;
            cout << cuitcuit.mincuit(user1, user2) << endl;
        }
    }

    return 0;
}
