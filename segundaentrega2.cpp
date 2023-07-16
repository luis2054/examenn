#include <iostream>
#include <string>

using namespace std;

// Clase LStack
template <typename T>
class LStack {
private:
    struct Node {
        T value;
        Node* next;
    };

    Node* topNode;

public:
    LStack() : topNode(nullptr) {}

    ~LStack() {
        while (!isEmpty()) {
            Pop();
        }
    }

    void Push(T value) {
        Node* newNode = new Node;
        newNode->value = value;
        newNode->next = topNode;
        topNode = newNode;
    }

    void Pop() {
        if (!isEmpty()) {
            Node* temp = topNode;
            topNode = topNode->next;
            delete temp;
        }
    }

    T Top() {
        if (!isEmpty()) {
            return topNode->value;
        }
        // Aquí puedes lanzar una excepción o devolver un valor predeterminado en caso de que la stack esté vacía.
       
        return T();
    }

    bool isEmpty() {
        return topNode == nullptr;
    }
};

// Clase LQueue
template <typename T>
class LQueue {
private:
    struct Node {
        T value;
        Node* next;
    };

    Node* frontNode;
    Node* backNode;

public:
    LQueue() : frontNode(nullptr), backNode(nullptr) {}

    ~LQueue() {
        while (!isEmpty()) {
            Dequeue();
        }
    }

    void Enqueue(T value) {
        Node* newNode = new Node;
        newNode->value = value;
        newNode->next = nullptr;

        if (isEmpty()) {
            frontNode = newNode;
            backNode = newNode;
        }
        else {
            backNode->next = newNode;
            backNode = newNode;
        }
    }

    void Dequeue() {
        if (!isEmpty()) {
            Node* temp = frontNode;
            frontNode = frontNode->next;
            delete temp;

            if (frontNode == nullptr) {
                backNode = nullptr;
            }
        }
    }

    T Front() {
        if (!isEmpty()) {
            return frontNode->value;
        }
        // Para simplificar, devolveré un valor predeterminado (puede ser modificado según las necesidades).
        return T();
    }

    T Back() {
        if (!isEmpty()) {
            return backNode->value;
        }

        return T();
    }

    bool isEmpty() {
        return frontNode == nullptr;
    }
};

// Clase Triage
class Triage {
private:
    static const int NUM_LEVELS = 5;
    LQueue<string> patientQueues[NUM_LEVELS];

public:
    void AddPatient(int urgency, string patient_name) {
        if (urgency >= 1 && urgency <= NUM_LEVELS) {
            patientQueues[urgency - 1].Enqueue(patient_name);
        }
    }

    void PassPatient() {
        for (int i = 0; i < NUM_LEVELS; ++i) {
            if (!patientQueues[i].isEmpty()) {
                patientQueues[i].Dequeue();
                return;
            }
        }
    }

    void Print() {
        for (int i = 0; i < NUM_LEVELS; ++i) {
            cout << i + 1 << "-> ";
            if (patientQueues[i].isEmpty()) {
                cout << "\n";
            }
            else {
                LQueue<string> tempQueue = patientQueues[i];
                while (!tempQueue.isEmpty()) {
                    cout << tempQueue.Front();
                    tempQueue.Dequeue();
                    if (!tempQueue.isEmpty()) {
                        cout << ", ";
                    }
                }
                cout << "\n";
            }
        }
    }
};

int main() {
    // Punto 1
    LStack<int> stack;
    stack.Push(10);
    stack.Push(20);
    stack.Push(30);
    cout << "Top: " << stack.Top() << endl;  // Output: 30
    stack.Pop();
    cout << "Top: " << stack.Top() << endl;  // Output: 20

    // Punto 2
    LQueue<string> queue;
    queue.Enqueue("PATRICIO");
    queue.Enqueue("BOB ESPONJA");
    cout << "Front: " << queue.Front() << endl;  // Output: Alice
    cout << "Back: " << queue.Back() << endl;    // Output: Bob
    queue.Dequeue();
    cout << "Front: " << queue.Front() << endl;  // Output: Bob

    // Punto 3
    Triage myTriage = Triage();
    myTriage.AddPatient(1, "luis");
    myTriage.AddPatient(5, "sorriana");
    myTriage.AddPatient(3, "LALA");
    myTriage.AddPatient(2, "Sofia");
    myTriage.AddPatient(1, "chaparro");
    myTriage.AddPatient(4, "Olivia");
    myTriage.AddPatient(5, "guero");
    myTriage.AddPatient(1, "Emiliano");

    myTriage.PassPatient();
    myTriage.PassPatient();

    myTriage.Print();

    return 0;
}








