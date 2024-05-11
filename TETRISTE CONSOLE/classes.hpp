#ifndef CLASSES

#define CLASSES

#include <string>

void print_wcharstring(wchar_t *_string);

// Utilities lines

using namespace std;

const int _BLACK = 0;
const int _BLUE = 1;
const int _GREEN = 2;
const int _CYAN = 3;
const int _RED = 4;
const int _MAGENTA = 5;
const int _YELLOW = 6;
const int ANSI_RESET = 7;
const int _INTENSITY = 8;

/*
\u25A0: BLACK SQUARE (■)
\u2666: BLACK DIAMOND SUIT (♦)
\u25CF: BLACK CIRCLE (●)
\u25B2: BLACK UP-POINTING TRIANGLE (▲)
*/

wchar_t ListForms[][100] = {L"\u25A0", L"\u2666", L"\u25CF", L"\u25B2"};

const string shapesList[] = {"Carrer", "Cercle", "Losange", "Triangle"};

const int colorsList[] = {_RED, _YELLOW, _GREEN, _BLUE};

// Class for the shape form

class Form
{
public:
    string shape;
    const int color;

    Form(string init_Shape, int init_col) : shape(init_Shape), color(init_col) {}

    static Form *CreateRandom()
    {
        return new Form(shapesList[rand() % 4], colorsList[rand() % 4]);
    }

    // Copy constructor for deep copy
    Form(Form &other) : shape(other.shape), color(other.color) {}

    // this function set the text of  console Windows to color
    void textcolor(int color)
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, color);
    }

    wchar_t *GetShape()
    {
        if (this->shape == "Carrer")
        {
            return ListForms[1];
        }
        else if (this->shape == "Cercle")
        {
            return ListForms[2];
        }
        else if (this->shape == "Losange")
        {
            return ListForms[0];
        }
        else if (this->shape == "Triangle")
        {
            return ListForms[3];
        }
    }

    // this show he Form
    void toString()
    {
        textcolor(this->color);
        print_wcharstring(this->GetShape());
        textcolor(ANSI_RESET);
    }

    ~Form() {}
};

// Class for the lists Nodes
class Node
{
public:
    void *item;
    // the main list
    Node *Next;
    Node *Prev;
    // the color list
    Node *NextColor;
    Node *PrevColor;
    // the shape list
    Node *NextShape;
    Node *PrevShape;

    Node() : item(nullptr), Next(nullptr), Prev(nullptr), NextColor(nullptr), PrevColor(nullptr), NextShape(nullptr), PrevShape(nullptr) {}

    Node(Node &other) : Next(nullptr), Prev(nullptr), NextColor(nullptr), PrevColor(nullptr), NextShape(nullptr), PrevShape(nullptr)
    {
        Form *newForm = new Form(*((Form *)other.item));
        this->item = (void *)newForm;
    }

    Node *getNext()
    {
        return Next;
    }

    Node *getPrev()
    {
        return Prev;
    }

    void setNext(Node *e)
    {
        this->Next = e;
    }

    void setPrev(Node *e)
    {
        this->Prev = e;
    }

    ~Node()
    {
        if(!item){
            free(item);
        }
    }
};

// for Linked list abstract class

// Class abstract ListChaine. For common data to all the lists.
class ListChaine
{
    // Insert First the item
    void InsertMainFirst(Node *item)
    {
        if (item != nullptr)
        {
            if (size == 0)
            {
                item->Next = item;
                item->Prev = item;
                Head = item;
                Tail = item;
            }
            else
            {
                item->Next = Head;
                Head->Prev = item;
                item->Prev = Tail;
                Tail->Next = item;
                Head = item;
                // loop
            }
            this->size++;
        }
    }

    // Insert Last the item
    void InsertMainLast(Node *item)
    {
        if (item != nullptr)
        {
            if (size == 0)
            {
                item->Next = item;
                item->Prev = item;
                Head = item;
                Tail = item;
            }
            else
            {
                item->Prev = Tail;
                Tail->Next = item;
                Head->Prev = item;
                Tail = item;
                item->Next = Head;
            }
            this->size++;
        }
    }

    // Insert First the item depend on the Color condition
    void InsertColorFirst(Node *item)
    {
        Node *currentNode = Head;
        for (int i = 0; i < size; i++)
        {
            if (((Form *)currentNode->item)->color == ((Form *)item->item)->color)
            {
                // do somthing
                item->NextColor = currentNode;
                currentNode->PrevColor->NextColor = item;
                item->PrevColor = currentNode->PrevColor;
                currentNode->PrevColor = item;
                break;
            }
            currentNode = currentNode->Next;
        }
        if (item->NextColor == nullptr)
        {
            item->NextColor = item;
            item->PrevColor = item;
        }
        HeadColors[((Form *)item->item)->color] = item;
    }

    // Insert Last the item depend on the Color condition
    void InsertColorLast(Node *item)
    {
        Node *currentNode = Tail;
        for (int i = 0; i < size; i++)
        {
            if (((Form *)currentNode->item)->color == ((Form *)item->item)->color)
            {
                // do somthing
                item->PrevColor = currentNode;
                currentNode->NextColor->PrevColor = item;
                item->NextColor = currentNode->NextColor;
                currentNode->NextColor = item;
                break;
            }
            currentNode = currentNode->Prev;
        }
        if (item->NextColor == nullptr)
        {
            item->NextColor = item;
            item->PrevColor = item;
        }
        if (HeadColors[((Form *)item->item)->color] == nullptr)
            HeadColors[((Form *)item->item)->color] = item;
    }

    // Insert First the item depend on the Shape condition
    void InsertShapeFirst(Node *item)
    {
        Node *currentNode = Head;
        for (int i = 0; i < size; i++)
        {
            if (((Form *)currentNode->item)->shape == ((Form *)item->item)->shape)
            {
                // do somthing
                item->NextShape = currentNode;
                currentNode->PrevShape->NextShape = item;
                item->PrevShape = currentNode->PrevShape;
                currentNode->PrevShape = item;
                break;
            }
            currentNode = currentNode->Next;
        }
        if (item->NextShape == nullptr)
        {
            item->NextShape = item;
            item->PrevShape = item;
        }
        HeadShapes[((Form *)item->item)->shape] = item;
    }

    // Insert Last the item depend on the Shape condition
    void InsertShapeLast(Node *item)
    {
        Node *currentNode = Tail;
        for (int i = 0; i < size; i++)
        {
            if (((Form *)currentNode->item)->shape == ((Form *)item->item)->shape)
            {
                // do somthing
                item->PrevShape = currentNode;
                currentNode->NextShape->PrevShape = item;
                item->NextShape = currentNode->NextShape;
                currentNode->NextShape = item;
                break;
            }
            currentNode = currentNode->Prev;
        }
        if (item->NextShape == nullptr)
        {
            item->NextShape = item;
            item->PrevShape = item;
        }
        if (HeadShapes[((Form *)item->item)->shape] == nullptr)
            HeadShapes[((Form *)item->item)->shape] = item;
    }

protected:
    int size;
    int score = 0;

    // Function that delet the node form node to other node
    void DeletFromNodeToNode(Node *StartNode, Node *EndNode)
    {
        if (this->size == 0)
        {
            cout << "hello world";
        }
        else
        {
            Node *currentNode = StartNode;
            for (int i = 0;; i++)
            {
                bool theBreakCon = (currentNode == EndNode);
                Node *deletedItem = currentNode;
                currentNode = currentNode->Next;
                this->DeleteNode(deletedItem);
                if (theBreakCon)
                    break;
            }
        }
    }

    // Function that gere a eruer case in decalage
    void PreparColorListAfterDecalage(int color)
    {
        Node *currentNode = Head;
        // save the Head of teh color in the loop , nd save the last color node to do cercularity
        Node *ColorHead = nullptr, *LastColor = nullptr;
        // counter in case we have only one node
        int countColor = 0;
        for (int i = 0; i <= size; i++)
        {
            // we find a Node in the main list have the same color as parametrecolor
            if (((Form *)currentNode->item)->color == color)
            {
                // do somthing
                ++countColor;
                // in case it first color do cercularity on ur-self and continue
                if (countColor == 1)
                {
                    ColorHead = currentNode;
                    LastColor = currentNode;
                    currentNode->NextColor = currentNode;
                    currentNode->PrevColor = currentNode;
                    continue;
                }
                // else in case ther more than one i want u to applycerularity
                LastColor->NextColor->PrevColor = currentNode;
                currentNode->NextColor = LastColor->NextColor;
                LastColor->NextColor = currentNode;
                currentNode->PrevColor = LastColor;
                // save current node as last node befor going to next
                LastColor = currentNode;
            }
            currentNode = currentNode->Next;
        }
        // save the header of color in the list
        HeadColors[color] = ColorHead;
    }

    // Function that gere a eruer case in decalage
    void PreparShapeListAfterDecalage(string shape)
    {
        Node *currentNode = Head;
        Node *ShapeHead = nullptr, *LastShape = nullptr;
        int countShape = 0;
        for (int i = 0; i <= size; i++)
        {
            if (((Form *)currentNode->item)->shape == shape)
            {
                // do somthing
                ++countShape;
                if (countShape == 1)
                {
                    ShapeHead = currentNode;
                    LastShape = currentNode;
                    currentNode->NextShape = currentNode;
                    currentNode->PrevShape = currentNode;
                    continue;
                }
                LastShape->NextShape->PrevShape = currentNode;
                currentNode->NextShape = LastShape->NextShape;
                LastShape->NextShape = currentNode;
                currentNode->PrevShape = LastShape;

                LastShape = currentNode;
            }
            currentNode = currentNode->Next;
        }
        HeadShapes[shape] = ShapeHead;
    }

public:
    // Delete a node in mainlist and color shpa lists
    void DeleteNode(Node *myNode)
    {
        if (!myNode)
        {
            cout << "Error : Node is Empty" << endl;
        }
        else
        {
            Node *NextElement = myNode->Next;
            Node *PrevElement = myNode->Prev;

            Node *NextElementColor = myNode->NextColor;
            Node *PrevElementColor = myNode->PrevColor;

            Node *NextElementShape = myNode->NextShape;
            Node *PrevElementShape = myNode->PrevShape;

            // if my myNode is the Head of Colors
            if (myNode == myNode->NextColor)
            {
                HeadColors[((Form *)myNode->item)->color] = nullptr;
            }
            else
            {
                if (HeadColors[((Form *)myNode->item)->color] == myNode)
                {
                    HeadColors[((Form *)myNode->item)->color] = myNode->NextColor;
                }
                PrevElementColor->NextColor = NextElementColor;
                NextElementColor->PrevColor = PrevElementColor;
            }

            // if my myNode is the Head of Shape
            if (myNode == myNode->NextShape)
            {
                HeadShapes[((Form *)myNode->item)->shape] = nullptr;
            }
            else
            {
                if (HeadShapes[((Form *)myNode->item)->shape] == myNode)
                {
                    HeadShapes[((Form *)myNode->item)->shape] = myNode->NextShape;
                }
                PrevElementShape->NextShape = NextElementShape;
                NextElementShape->PrevShape = PrevElementShape;
            }

            // if my myNode is the Head of Main list
            if (Head == Tail)
            {
                Head = Tail = nullptr;
            }
            else
            {
                if (Head == myNode)
                {
                    Head = myNode->Next;
                }
                else if (Tail == myNode)
                {
                    Tail = myNode->Prev;
                }
                PrevElement->Next = NextElement;
                NextElement->Prev = PrevElement;
            }
            delete myNode;
            this->size--;
        }
    }
    // Head and the tail of the list
    Node *Head;
    Node *Tail;
    // arrray of headers of the color and shapes
    map<int, Node *> HeadColors;
    map<string, Node *> HeadShapes;

    // Constructeur
    ListChaine() : Head(nullptr), Tail(nullptr), size(0)
    {
        for (int i = 0; i < HeadColors.size(); i++)
        {
            HeadColors[colorsList[i]] = nullptr;
            HeadShapes[shapesList[i]] = nullptr;
        }
    }

    // return sixe of the list
    int getSize()
    {
        return this->size;
    }

    bool isEmpty()
    {
        return (size == 0);
    }

    // Insert the Node at the begeninng of the list
    void InsertFirst(Node *item)
    {
        this->InsertColorFirst(item);
        this->InsertShapeFirst(item);
        // call color and shap inserting first so they wont effect by the main insert because of the chae of the size
        this->InsertMainFirst(item);
    }

    // Insert the Node at the begeninng of the list
    void InsertLast(Node *item)
    {
        this->InsertColorLast(item);
        this->InsertShapeLast(item);
        // call color and shap inserting first so they wont effect by the main insert because of the chae of the size
        this->InsertMainLast(item);
    }

    void removeFirst()
    {
        if (!this->isEmpty())
        {
            Node *removed = Head;
            Head = removed->Next;
            Head->Prev = nullptr;
            delete removed;
        }
    }

    void removeLast()
    {
        if (!this->isEmpty())
        {
            Node *removed = Tail;
            Tail = removed->Prev;
            Tail->Next = nullptr;
            delete removed;
        }
    }

    Node *getFirst()
    {
        Node *MyItem = nullptr;
        if (!this->isEmpty())
        {
            MyItem = Head;
        }
        return MyItem;
    }

    Node *getLast()
    {
        Node *MyItem = nullptr;
        if (!this->isEmpty())
        {
            MyItem = Tail;
        }
        return MyItem;
    }


    void print_size_score()
    {
        cout << "Taille actuel: " << this->size << endl;
        cout << "score: " << this->score;
    }

    void setScore(int value)
    {
        this->score = value;
    }

    int getScore()
    {
        return score;
    }

    // Destricteur
    ~ListChaine()
    {
        Node *currentNode = Head;
        Node *nextNode;

        for (int i = 0; i < size; i++)
        {
            if (!currentNode)
            {
                nextNode = currentNode->Next;
                delete currentNode;
                currentNode = nextNode;
            }
        }
    }
};


// for linked FormList for according to the game necessities.

// Class abstract FormList. The implementation with necessary functions to the game.
class FormList : public ListChaine
{
private:
    // function return if the 2 node have the same color
    bool NodesHaveSameColor(Node *item1, Node *item2)
    {
        return ((Form *)item1->item)->color == ((Form *)item2->item)->color;
    }

    // function return if the 2 node have the same shapes
    bool NodesHaveSameShape(Node *item1, Node *item2)
    {
        return ((Form *)item1->item)->shape == ((Form *)item2->item)->shape;
    }

    // swape 2 node in teh list => [saces o main list only]
    void SwapNodes(Node *itemNbr1, Node *itemNbr2)
    {
        // Handle if either of the nodes is NULL or if they are the same node
        if (!itemNbr1 || !itemNbr2 || itemNbr1 == itemNbr2)
            return;

        // Swap next pointers
        Node *tempNext = itemNbr1->Next;
        itemNbr1->Next = itemNbr2->Next;
        itemNbr2->Next = tempNext;

        if (itemNbr1->Next)
            itemNbr1->Next->Prev = itemNbr1;
        if (itemNbr2->Next)
            itemNbr2->Next->Prev = itemNbr2;

        if (itemNbr1->Prev == itemNbr2)
        { // Handling adjacent nodes
            itemNbr2->Prev = itemNbr1->Prev;
            itemNbr1->Prev = itemNbr2;
        }
        else
        {
            Node *tempPrev = itemNbr1->Prev;
            itemNbr1->Prev = itemNbr2->Prev;
            itemNbr2->Prev = tempPrev;
        }

        if (itemNbr1->Prev)
            itemNbr1->Prev->Next = itemNbr1;
        if (itemNbr2->Prev)
            itemNbr2->Prev->Next = itemNbr2;

        // Update head if necessary
        if (itemNbr1 == Head)
            Head = itemNbr2;
        else if (itemNbr2 == Head)
            Head = itemNbr1;

        // Update tail if necessary
        if (itemNbr1 == Tail)
            Tail = itemNbr2;
        else if (itemNbr2 == Tail)
            Tail = itemNbr1;
    }

    // Function to find the longest sequence of nodes with the same color
    int DeleteTheLongestSameColorOrSameShapeSequence()
    {
        // |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
        // |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
        // Traitement of the Same Colors
        // |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
        // |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

        // get the first element of the list
        Node *currentNode = Head;
        // declar the start and end of the nodes i need to delete
        Node *startNodeColor = nullptr;
        Node *endNodeColor = nullptr;
        // 2 varibale to do comaperesent of the "newLenght" and the "oldLongestLenght" of the sequnce of the nodes have same color
        int maxSequenceLengthColor = 0;
        int currentSequenceLength = 1;

        // loop go trought all the list
        for (int i = 0; i < this->size - 2; i++)
        {
            // Save the next of the current node ->next
            Node *nextNode = currentNode->Next;
            // loop fromt the start of the node and calculate the lenght of the longest sequnce
            for (int i = 0; nextNode->Prev != Tail && NodesHaveSameColor(currentNode, nextNode); i++)
            {
                // increase the lenght      > this value after this loop will store the current lenght of the Start to End of the longest sequnece of node
                currentSequenceLength++;
                nextNode = nextNode->Next;
            }
            // check if the current and the old lenght is diffrent or not   >to get the longest sequnace of the list have same colore
            if (currentSequenceLength > maxSequenceLengthColor)
            {
                // SAVE the value and the old longest , to calculate the new longest
                maxSequenceLengthColor = currentSequenceLength;
                startNodeColor = currentNode;
                endNodeColor = nextNode->Prev;
            }
            // chnage currentSequenceLength to calculate new lenght of colors
            currentSequenceLength = 1;
            // here instead of getting the next by the next we just get the next of the last node we read i  longest sequnce
            currentNode = nextNode;
        }
        // |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
        // |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
        // Traitement of the Same Colors
        // |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
        // |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
        currentNode = Head;
        // declar the start and end of the nodes i need to delete
        Node *startNodeShape = nullptr;
        Node *endNodeShape = nullptr;
        // 2 varibale to do comaperesent of the "newLenght" and the "oldLongestLenght" of the sequnce of the nodes have same color
        int maxSequenceLengthShape = 0;
        currentSequenceLength = 1;

        // loop go trought all the list
        for (int i = 0; i < this->size - 2; i++)
        {
            // Save the next of the current node ->next
            Node *nextNode = currentNode->Next;
            // loop fromt the start of the node and calculate the lenght of the longest sequnce
            for (int i = 0; nextNode->Prev != Tail && NodesHaveSameShape(currentNode, nextNode); i++)
            {
                // increase the lenght      > this value after this loop will store the current lenght of the Start to End of the longest sequnece of node
                currentSequenceLength++;
                nextNode = nextNode->Next;
            }
            // check if the current and the old lenght is diffrent or not   >to get the longest sequnace of the list have same colore
            if (currentSequenceLength > maxSequenceLengthShape)
            {
                // SAVE the value and the old longest , to calculate the new longest
                maxSequenceLengthShape = currentSequenceLength;
                startNodeShape = currentNode;
                endNodeShape = nextNode->Prev;
            }
            // chnage currentSequenceLength to calculate new lenght of colors
            currentSequenceLength = 1;
            // here instead of getting the next by the next we just get the next of the last node we read i  longest sequnce
            currentNode = nextNode;
        }

        //  NOW DEETINg the longest seconse , check if there bigger than color or shape and delet the biggest one
        if (maxSequenceLengthShape >= 3 && maxSequenceLengthColor >= 3)
        {
            if (maxSequenceLengthColor >= maxSequenceLengthShape)
            {
                this->DeletFromNodeToNode(startNodeColor, endNodeColor);
                this->score += ((maxSequenceLengthColor*5)-5);
                return maxSequenceLengthColor;
            }
            else
            {
                this->DeletFromNodeToNode(startNodeShape, endNodeShape);
                this->score += ((maxSequenceLengthShape*5)-5);
                return maxSequenceLengthShape;
            }
        }
        else
        {
            if (maxSequenceLengthShape >= 3)
            {
                this->DeletFromNodeToNode(startNodeShape, endNodeShape);
                this->score += ((maxSequenceLengthShape*5)-5);
                return maxSequenceLengthShape;
            }
            else if (maxSequenceLengthColor >= 3)
            {
                this->DeletFromNodeToNode(startNodeColor, endNodeColor);
                this->score += ((maxSequenceLengthColor*5)-5);
                return maxSequenceLengthColor;
            }
        }
        return -1;
    }

public:
    bool isEqualTo(FormList *otherList)
    {
        if (this->size != otherList->size || !this->NodesHaveSameColor(this->Head, otherList->Head) || !this->NodesHaveSameColor(this->Tail, otherList->Tail) || !this->NodesHaveSameShape(this->Head, otherList->Head) || !this->NodesHaveSameShape(this->Tail, otherList->Tail))
            return false;
        Node *List1CurrentNode = this->Head, *List2CurrentNode = otherList->Head;
        for (int i = 0; i < this->size; i++)
        {
            if (!(this->NodesHaveSameColor(List1CurrentNode, List2CurrentNode) && this->NodesHaveSameColor(List1CurrentNode, List2CurrentNode)))
            {
                return false;
            }
            List1CurrentNode = List1CurrentNode->Next;
            List2CurrentNode = List2CurrentNode->Next;
        }
        return true;
    }

    FormList *clone()
    {
        FormList *newList = new FormList();
        Node *currentNode = this->Head;
        for (int i = 0; i < this->size; i++)
        {
            // Create a new node with a copy of the data
            Form *newNode = new Form(*((Form *)currentNode->item));
            newList->InsertFormLast(newNode);
            currentNode = currentNode->Next;
        }
        return newList;
    }

    //  Fucntion Correct all the shapes and colors headers & the list cerculair
    void CorrectCollorHeadsAndShapes()
    {
        // THE MAIN FUNCTION THAT HAVE THE MAIN CORRECTON of list header and shapes
        for (int i = 0; i < HeadColors.size(); i++)
        {
            this->PreparColorListAfterDecalage(colorsList[i]);
            this->PreparShapeListAfterDecalage(shapesList[i]);
        }
    }

    // Function Delete Element an Return the Totale element Deleted !! call it after decalage and before affichage
    int DeleteSimilarElementsGetNumberOfDeletedElements()
    {
        // start couting from 0
        int TotaleDeleted = 0;
        // function return the elemnt deleted one time , and keep deleting after one delting let say TSSSTT the SSS deleted so the output is TTT so the TTT should be delted also and totale is = 6
        while (int theoutput = DeleteTheLongestSameColorOrSameShapeSequence())
        {
            // DeleteTheLongestSameColorOrSameShapeSequence retrun -1 if no element deleted . it can change to return 0
            if (theoutput == -1)
                break;
            // calcul some
            TotaleDeleted += theoutput;
        }
        return TotaleDeleted;
    }

    // ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
    // |||||||||||||||||||||||||||||||||||||| Errer : I didnt gere case of decalage in the header of color and shapes  ||||||||||||||||||||||||||||||||||||||||
    // ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
    // decalage the node to LEFT from the starting Node as argument
    void DecalageColorToLeft(Node *theColoHead)
    {
        if (theColoHead == nullptr || theColoHead->PrevColor == nullptr)
            return;

        Node *currentNode = theColoHead;
        do
        {
            Node *tmpNodeStoreData = currentNode->PrevColor;
            SwapNodes(currentNode->PrevColor, currentNode);
            currentNode = tmpNodeStoreData;
        } while (currentNode != nullptr && !(theColoHead->NextColor == currentNode));
        this->PreparColorListAfterDecalage(((Form *)theColoHead->item)->color);
    }

    // decalage the node to RIGHT from the starting Node as argument
    void DecalageColorToRight(Node *theColoHead)
    {
        if (theColoHead == nullptr || theColoHead->NextColor == nullptr)
            return;

        Node *currentNode = theColoHead;
        do
        {
            SwapNodes(currentNode->PrevColor, currentNode);
            currentNode = currentNode->NextColor;
        } while (currentNode != nullptr && !(theColoHead->PrevColor == currentNode));
        this->PreparColorListAfterDecalage(((Form *)theColoHead->item)->color);
    }

    // decalage the node to LEFT from the starting Node as argument
    void DecalageShapeToLeft(Node *theColoHead)
    {
        if (theColoHead == nullptr || theColoHead->PrevShape == nullptr)
            return;

        Node *currentNode = theColoHead;
        do
        {
            Node *tmpNodeStoreData = currentNode->PrevShape;
            SwapNodes(currentNode->PrevShape, currentNode);
            currentNode = tmpNodeStoreData;
        } while (currentNode != nullptr && !(theColoHead->NextShape == currentNode));
        this->PreparShapeListAfterDecalage(((Form *)theColoHead->item)->shape);
    }

    // decalage the node to RIGHT from the starting Node as argument
    void DecalageShapeToRight(Node *theColoHead)
    {
        if (theColoHead == nullptr || theColoHead->NextShape == nullptr)
            return;

        Node *currentNode = theColoHead;
        do
        {
            SwapNodes(currentNode->PrevShape, currentNode);
            currentNode = currentNode->NextShape;
        } while (currentNode != nullptr && !(theColoHead->PrevShape == currentNode));
        this->PreparShapeListAfterDecalage(((Form *)theColoHead->item)->shape);
    }
    // ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
    // ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

    // Insert Randome element in the list
    void InsertRandomForms(int size)
    {
        for (int i = 0; i < size; i++)
        {
            Node *newNode = new Node();
            Form *newForm = Form::CreateRandom();
            newNode->item = (void *)newForm;
            this->InsertFirst(newNode);
        }
    }

    // Insert Form to LEFT
    void InsertFormFirst(Form *maform)
    {
        Node *newitem = new Node();
        newitem->item = (void *)maform;
        this->InsertFirst(newitem);
    }

    // Insert Form to RIGHT
    void InsertFormLast(Form *maform)
    {
        Node *newitem = new Node();
        newitem->item = (void *)maform;
        this->InsertLast(newitem);
    }

    // string show the main list
    void toString()
    {
        Node *currentNoed = Head;
        if (Head == nullptr || size == 0)
        {
            cout << "Empty List here . . . " << endl;
        }
        else
        {
            for (int i = 0; i < this->size; i++)
            {

                cout << "( ";
                ((Form *)currentNoed->item)->toString();
                if(currentNoed !=this->Tail) cout << " )->";
                else cout << " )";
                currentNoed = currentNoed->Next;
            }
        }
    }

    // string show the color map list
    void toStringColors()
    {
        cout << "\n\t\tThe Color list size is : " << this->size << endl;
        for (int i = 0; i < HeadColors.size(); i++)
        {
            Node *item = HeadColors[colorsList[i]];
            cout << "\t > ";
            while (HeadColors[colorsList[i]])
            {
                ((Form *)item->item)->toString();
                item = item->NextColor;
                if (item == HeadColors[colorsList[i]])
                    break;
            }
            cout << endl;
        }
    }

    // string show the shape map list
    void toStringShapes()
    {
        cout << "\n\t\tThe Shape list size is : " << this->size << endl;
        for (int i = 0; i < HeadColors.size(); i++)
        {
            Node *item = HeadShapes[shapesList[i]];
            cout << "\t > ";
            while (HeadShapes[shapesList[i]])
            {
                ((Form *)item->item)->toString();
                item = item->NextShape;
                if (item == HeadShapes[shapesList[i]])
                    break;
            }
            cout << endl;
        }
    }

    // Functiom that delete the last element and insert a random one in the tail
    Form *DeleteAndGetLastForm()
    {
        if (Head != nullptr)
        {
            Form *newItem = new Form(((Form *)Head->item)->shape, ((Form *)Head->item)->color);
            this->DeleteNode(Head);
            this->InsertFormLast(Form::CreateRandom());
            return newItem;
        }
        return nullptr;
    }
};


// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// ||||||||||||||||||||||||||||||||||||||||||||||||||||AI SECTION|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

string intToColorString(int color)
{
    switch (color)
    {
    case _RED:
        return "Red";
        break;
    case _GREEN:
        return "Green";
        break;
    case _INTENSITY:
        return "Yellow";
        break;
    case _BLUE:
        return "Blue";
        break;
    default:
        return "Yellow";
        break;
    }
}

class TreeNode
{
public:
    string actionsName;
    int ChildCount;
    int score;
    int actionIndex;
    vector<TreeNode *> *children;
    FormList *List;
    FormList *NextElements;

    TreeNode(FormList *listPointer, FormList *NextItem, int layer, string actionsName, int score = 0, int actionIndex = -1)
        : NextElements(NextItem), score(score), actionIndex(actionIndex), children(nullptr), List(listPointer), actionsName(actionsName)
    {

        try
        {
            try
            {
                children = new vector<TreeNode *>();
                ChildCount = 0;
            }
            catch (...)
            {
                cout << "\n\t\t -> Somthing happened Making the Vectore Children!!";
                getchar();
            }
            FormList *newList;
            FormList *newNextElement;
            //     // Iterate over possible actions
            for (int i = 0; i < (2 + sizeof(colorsList) / sizeof(colorsList[0]) + sizeof(shapesList) / sizeof(shapesList[0])); i++)
            {
                newList = listPointer->clone();
                newNextElement = NextItem->clone();
                string newactionName = "None";
                TreeNode *newNode = nullptr;
                int score = DoAction(i, newList, newNextElement, &newactionName);
                // Check if newList is different from original List
                if (!List->isEqualTo(newList))
                {
                    // Check if layer is less than or equal to 0
                    if (layer <= 0)
                    {
                        // Check if score is valid
                        if (score != 0 && score != -1)
                        {
                            try
                            {
                                newNode = new TreeNode(newactionName, this->score + score, i);
                            }
                            catch (std::bad_alloc &e)
                            {
                                std::cout << "Error occurred while creating Tree object: " << std::endl;
                            }
                            catch (...)
                            {
                                std::cout << "Error occurred while creating Tree object: " << std::endl;
                            }
                            children->push_back(newNode);
                            ChildCount++;
                        }
                    }
                    else
                    {
                        newNode = new TreeNode(newList, newNextElement, layer - 1, newactionName, this->score + score, i);
                        children->push_back(newNode);
                        ChildCount++;
                    }
                }
                try
                {
                    delete newList;
                    delete newNextElement;
                }
                catch (...)
                {
                    cout << "\n\t\t -> Somthing happened whiw deleting the 2 liste of the node!!";
                    getchar();
                }
            }
        }
        catch (std::bad_alloc &e)
        {
            std::cout << "Error occurred while allocating memory for children vector: " << e.what() << std::endl;
            getchar();
        }
        catch (...)
        {
            std::cout << "Unknown error occurred in TreeNode constructor" << std::endl;
            getchar();
        }
    }

    // Destructor
    ~TreeNode()
    {
        if (!List)
            delete List;
        if (!NextElements)
            delete NextElements;
        if (!children)
        {
            for (int i = 0; i < ChildCount; ++i)
            {
                if ((*children)[i] != nullptr)
                {
                    delete (*children)[i];    // Recursively delete child nodes
                    (*children)[i] = nullptr; // Set child pointer to nullptr after deletion
                }
            }
            delete children; // Delete the children vector
        }
    }

    // Default Constructor
    TreeNode(string actionsName, int score = 0, int actionIndex = -1) : ChildCount(0), score(score), actionsName(actionsName), actionIndex(actionIndex), children(nullptr), List(nullptr), NextElements(nullptr) {}

    int DoAction(int index, FormList *mylist, FormList *newNextElement, string *action)
    {
        try
        {
            //     // Check if either myList or newNextElement is nullptr
            if (mylist == nullptr || newNextElement == nullptr)
            {
                // Handle the case where either myList or newNextElement is nullptr
                cout << "Error: myList or newNextElement is nullptr\n";
                return 0;
            }

            // Continue with the action based on the index
            if (newNextElement->getSize() != 0)
            {
                if (index == 0 && mylist->getSize() <= 15)
                {
                    // Insert Left
                    if (newNextElement->Head != nullptr)
                    {
                        Node *nextItemToInsert = new Node(*newNextElement->Head);
                        newNextElement->DeleteNode(newNextElement->Head);
                        mylist->InsertFirst(nextItemToInsert);
                        *action = "Insertion a gauche";
                        return mylist->DeleteSimilarElementsGetNumberOfDeletedElements();
                    }
                }
                else if (index == 1 && mylist->getSize() <= 15)
                {
                    // Insert Right (Corrected typo)
                    if (newNextElement->Head != nullptr)
                    {
                        Node *nextItemToInsert = new Node(*newNextElement->Head);
                        newNextElement->DeleteNode(newNextElement->Head);
                        mylist->InsertLast(nextItemToInsert);
                        *action = "Insertion a droite";
                        return mylist->DeleteSimilarElementsGetNumberOfDeletedElements();
                    }
                }
            }
            if (mylist->getSize() != 0)
            {
                for (int i = 0; i < 4; i++)
                {
                    if ((i + 2) == index && mylist->HeadColors[colorsList[i]] != nullptr)
                    {
                        mylist->DecalageColorToLeft(mylist->HeadColors[colorsList[i]]);
                        *action = "Decalage Couleur : " + intToColorString(colorsList[i]);
                        return mylist->DeleteSimilarElementsGetNumberOfDeletedElements();
                    }
                    continue;
                }
                for (int i = 0; i < 4; i++)
                {
                    if ((i + 4 + 2) == index && mylist->HeadShapes[shapesList[i]] != nullptr)
                    {
                        mylist->DecalageShapeToLeft(mylist->HeadShapes[shapesList[i]]);
                        *action = "Decalage Forme : " + shapesList[i];
                        return mylist->DeleteSimilarElementsGetNumberOfDeletedElements();
                    }
                }
            }
        }
        catch (std::exception &e)
        {
            std::cout << "Error occurred in DoAction function: " << e.what() << std::endl;
        }
        catch (...)
        {
            std::cout << "Unknown error occurred in DoAction function" << std::endl;
        }
        return 0; // Return 0 if no action was performed
    }

    string toString()
    {
        return "Node :{ Nbr of children :" + to_string(this->ChildCount) + " ,Score: " + to_string(this->score) + ", Action Index: \"" + this->actionsName + "\" , The Action Index is : " + to_string(this->actionIndex) + " }\n";
    }
};

class Tree
{
public:
    TreeNode *root;

    Tree(FormList *myList, FormList *myNextElementList, int nbrLayers)
    {
        root = nullptr; // Explicitly initialize root to nullptr
        try
        {
            if (myList != nullptr && myNextElementList != nullptr && nbrLayers >= 0)
            {
                bool LocatedInSucce = true;
                while (LocatedInSucce)
                {
                    try
                    {
                        root = new TreeNode(myList->clone(), myNextElementList->clone(), nbrLayers, "");
                        LocatedInSucce = false;
                    }
                    catch (std::bad_alloc &e)
                    {
                        LocatedInSucce = true;
                    }
                    catch (...)
                    {
                        std::cout << "Error occurred while creating Tree object: " << std::endl;
                        getchar();
                    }
                }
            }
        }
        catch (std::bad_alloc &e)
        {
            std::cout << "Error occurred while allocating memory for tree node: " << e.what() << std::endl;
            getchar();
        }
        catch (...)
        {
            std::cout << "Unknown error occurred in Tree constructor" << std::endl;
            getchar();
        }
    }

    void printTree()
    {
        if (!root)
        {
            printTreeNode(root, 0);
        }
    }

    // Helper function to print tree nodes recursively
    void printTreeNode(TreeNode *node, int level)
    {
        if (node != nullptr)
        {
            // Print current node
            cout << string(level, '\t') << node->toString() << endl;

            // Print children recursively
            if (node->children != nullptr)
            {
                for (size_t i = 0; i < node->children->size(); ++i)
                {
                    if ((*node->children)[i] != nullptr)
                    {
                        printTreeNode((*node->children)[i], level + 1);
                    }
                }
            }
        }
    }

    vector<string> GetBestPath(int &highscore)
    {
        vector<string> bestPath;
        vector<string> currentPath;
        int maxScore = 1;
        BackTracking(root, maxScore, currentPath, bestPath);
        highscore = maxScore;
        return bestPath;
    }

    vector<int> GetBestPathIndexs()
    {
        vector<int> bestPath;
        vector<int> currentPath;
        int maxScore = 1;
        BackTracking(root, maxScore, currentPath, bestPath);
        return bestPath;
    }

    void BackTracking(TreeNode *node, int &maxScore, vector<string> &currentPath, vector<string> &bestPath)
    {
        if (node == nullptr)
            return;

        // save the path the highest score found
        if (maxScore < node->score)
        {
            maxScore = node->score;
            bestPath = currentPath;
        }

        if (maxScore == node->score && bestPath.size() > currentPath.size())
        {
            bestPath = currentPath;
        }

        if (node->children != nullptr)
        {
            for (int i = 0; i < node->ChildCount; i++)
            {
                if ((*node->children)[i] != nullptr)
                {
                    currentPath.push_back((*node->children)[i]->actionsName);
                    BackTracking((*node->children)[i], maxScore, currentPath, bestPath);
                    currentPath.pop_back();
                }
            }
        }
    }

    void BackTracking(TreeNode *node, int &maxScore, vector<int> &currentPath, vector<int> &bestPath)
    {
        if (node == nullptr)
            return;

        // save the path the highest score found
        if (maxScore < node->score)
        {
            maxScore = node->score;
            bestPath = currentPath;
        }

        if (maxScore == node->score && bestPath.size() > currentPath.size())
        {
            bestPath = currentPath;
        }

        if (node->children != nullptr)
        {
            for (int i = 0; i < node->ChildCount; i++)
            {
                if ((*node->children)[i] != nullptr)
                {
                    currentPath.push_back((*node->children)[i]->actionIndex);
                    BackTracking((*node->children)[i], maxScore, currentPath, bestPath);
                    currentPath.pop_back();
                }
            }
        }
    }
    // Destructor
    ~Tree()
    {
        try
        {
            if (!root)
            {
                delete root;    // This will recursively delete all nodes in the tree
                root = nullptr; // Set root to nullptr after deletion
            }
        }
        catch (std::exception &e)
        {
            std::cout << "Error occurred in Tree destructor: " << e.what() << std::endl;
        }
        catch (...)
        {
            std::cout << "Unknown error occurred in Tree destructor" << std::endl;
        }
    }
};

#endif // CLASSES
