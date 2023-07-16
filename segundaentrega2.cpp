#include <iostream>  
#include <string>   

using namespace std;

// Implementación de una pila utilizando una lista enlazada
template <typename T>
class LStack {
private:
    struct Node {  // Estructura de nodo para almacenar los elementos de la pila
        T value;    // Valor del nodo
        Node* next; // Puntero al siguiente nodo
    };

    Node* topNode;

public:
    LStack() : topNode(nullptr) {}  // Constructor: inicializa la pila vacía

    ~LStack() {  // Destructor: libera la memoria de todos los nodos de la pila
        while (!isEmpty()) {
            Pop();
        }
    }

    void Push(T value) {  // Agrega un elemento a la pila
        Node* newNode = new Node;   // Crea un nuevo nodo
        newNode->value = value;     // Asigna el valor al nuevo nodo
        newNode->next = topNode;    // Establece el siguiente nodo como el nodo superior actual
        topNode = newNode;          // Actualiza el nodo superior con el nuevo nodo
    }

    void Pop() {  // Elimina el elemento superior de la pila
        if (!isEmpty()) {
            Node* temp = topNode;      // Guarda el nodo superior actual
            topNode = topNode->next;   // Actualiza el nodo superior con el siguiente nodo
            delete temp;               // Libera la memoria del nodo eliminado
        }
    }

    T Top() {  // Obtiene el valor del elemento superior de la pila
        if (!isEmpty()) {
            return topNode->value;
        }
        // Aquí puedes lanzar una excepción o devolver un valor predeterminado en caso de que la pila esté vacía.
        return T();  // Devuelve un valor predeterminado (0 para tipos numéricos, cadena vacía para std::string, etc.)
    }

    bool isEmpty() {  // Verifica si la pila está vacía
        return topNode == nullptr;
    }
};

// Clase LQueue - Implementación de una cola utilizando una lista enlazada
template <typename T>
class LQueue {
private:
    struct Node {  // Estructura de nodo para almacenar los elementos de la cola
        T value;    // Valor del nodo
        Node* next; // Puntero al siguiente nodo
    };

    Node* frontNode;  // Puntero al nodo del frente de la cola
    Node* backNode;   // Puntero al nodo de la parte posterior de la cola

public:
    LQueue() : frontNode(nullptr), backNode(nullptr) {}  // Constructor: inicializa la cola vacía

    ~LQueue() {  // Destructor: libera la memoria de todos los nodos de la cola
        while (!isEmpty()) {
            Dequeue();
        }
    }

    void Enqueue(T value) {  // Agrega un elemento al final de la cola
        Node* newNode = new Node;  // Crea un nuevo nodo
        newNode->value = value;    // Asigna el valor al nuevo nodo
        newNode->next = nullptr;

        if (isEmpty()) {           // Si la cola está vacía, el nuevo nodo se convierte en el frente y la parte posterior
            frontNode = newNode;
            backNode = newNode;
        }
        else {                   // Si la cola no está vacía, se agrega el nuevo nodo después del último nodo
            backNode->next = newNode;
            backNode = newNode;
        }
    }

    void Dequeue() {  // Elimina el elemento del frente de la cola
        if (!isEmpty()) {
            Node* temp = frontNode;    // Guarda el nodo del frente actual
            frontNode = frontNode->next;  // Actualiza el frente con el siguiente nodo
            delete temp;               // Libera la memoria del nodo eliminado

            if (frontNode == nullptr) {  // Si el frente se convierte en nullptr, la cola está vacía
                backNode = nullptr;     // Por lo tanto, la parte posterior también se establece en nullptr
            }
        }
    }

    T Front() {  // Obtiene el valor del elemento del frente de la cola
        if (!isEmpty()) {
            return frontNode->value;
        }
        // Para simplificar, devolveré un valor predeterminado (puede ser modificado según las necesidades).
        return T();  // Devuelve un valor predeterminado (0 para tipos numéricos, cadena vacía para std::string, etc.)
    }

    T Back() {  // Obtiene el valor del elemento de la parte posterior de la cola
        if (!isEmpty()) {
            return backNode->value;
        }
        return T();
    }

    bool isEmpty() {  // Verifica si la cola está vacía
        return frontNode == nullptr;
    }
};

// Clase Triage - Implementación de un sistema de triaje utilizando colas
class Triage {
private:
    static const int NUM_LEVELS = 5;  // Número de niveles de urgencia
    LQueue<string> patientQueues[NUM_LEVELS];  // Arreglo de colas para cada nivel de urgencia

public:
    void AddPatient(int urgency, string patient_name) {  // Agrega un paciente al nivel de urgencia especificado
        if (urgency >= 1 && urgency <= NUM_LEVELS) {
            patientQueues[urgency - 1].Enqueue(patient_name);
        }
    }

    void PassPatient() {  // Pasa al siguiente paciente en orden de prioridad
        for (int i = 0; i < NUM_LEVELS; ++i) {
            if (!patientQueues[i].isEmpty()) {
                patientQueues[i].Dequeue();
                return;
            }
        }
    }

    void Print() {  // Imprime el estado actual de las colas de pacientes
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

    LStack<int> stack;
    stack.Push(10);
    stack.Push(20);
    stack.Push(30);
    cout << "Top: " << stack.Top() << endl;  // Output: 30
    stack.Pop();
    cout << "Top: " << stack.Top() << endl;  // Output: 20

    LQueue<string> queue;
    queue.Enqueue("PATRICIO");
    queue.Enqueue("BOB ESPONJA");
    cout << "Front: " << queue.Front() << endl;  // Output: PATRICIO
    cout << "Back: " << queue.Back() << endl;    // Output: BOB ESPONJA
    queue.Dequeue();
    cout << "Front: " << queue.Front() << endl;  // Output: BOB ESPONJA

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








