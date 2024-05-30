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
                    headData = newKata2;
                    tailData = newKata2;
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

    void printText() {
        nodeKata* current = headData;
        while (current != nullptr) {
            cout << current->data;
            if (current->next != nullptr) {
                cout << ',';
            }
            current = current->next;
        }
        cout << endl;
    }
};

class App {
private:
    Group* headGroup;
    Group* tailGroup;
    int groupCounter;
    int numberOfGroup;

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
            }

            if (tailGroup == diFollow_Group) {
                tailGroup = nullptr;
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
        obj.printText();
    }

    void suggestfriend(string username) {
        textOutputContainer obj;
        User* user1 = findUser(username);
        followNode* currentFollowing = user1->headFollowing;
        while (currentFollowing) {
            User* friends = findUser(currentFollowing->name);
            followNode* followerFriends = friends->headFollower;
            while (followerFriends) {
                obj.addString(followerFriends->name, 2);
                followerFriends = followerFriends->next;
            }
            followNode* followingFriends = friends->headFollowing;
            while (followingFriends) {
                obj.addString(followingFriends->name, 2);
                followingFriends = followingFriends->next;
            }
            currentFollowing = currentFollowing->next;
        }
        obj.sortText();
        obj.printText();
    }

    void grouptopic() {
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
            obj.printText();
            currentGroup = currentGroup->nextGroup;
        }
    }
};


int main() {
    App app;

    // Example user data
    stringstream user1Data("music sports coding");
    stringstream user2Data("reading music movies");
    stringstream user3Data("coding sports reading");
    stringstream user4Data("music movies sports");
    stringstream user5Data("cooking travel music");
    stringstream user6Data("sports travel coding");
    stringstream user7Data("reading cooking travel");

    // Insert users into the app
    app.insert(user1Data, "Alice");
    app.insert(user2Data, "Bob");
    app.insert(user3Data, "Charlie");
    app.insert(user4Data, "Diana");
    app.insert(user5Data, "Eve");
    app.insert(user6Data, "Frank");
    app.insert(user7Data, "Grace");

    // Connect users (following relationships)
    app.connect("Alice", "Bob");
    app.connect("Bob", "Charlie");
    app.connect("Alice", "Charlie");
    app.connect("Charlie", "Diana");
    app.connect("Eve", "Frank");
    app.connect("Frank", "Grace");
    app.connect("Alice", "Eve");
    app.connect("Bob", "Frank");

    // Display the number of groups
    cout << "Number of groups: ";
    app.numgroup();

    // Display the most followed users
    cout << "Most followed users: ";
    app.mostfollowed();

    // Suggest friends for a user
    cout << "Friend suggestions for Alice: ";
    app.suggestfriend("Alice");

    // Display group topics
    cout << "Group topics: " << endl;
    app.grouptopic();

    return 0;
}
