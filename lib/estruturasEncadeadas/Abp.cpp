#include "Abp.hpp"

Abp::Abp(bool avl)
{
    this->root = NULL;
    this->avl = avl;
    this->size = 0;
}

Abp::~Abp()
{
    reset();
}

bool Abp::isEmpty()
{
    return this->root == NULL;
}

void Abp::reset(Node *node)
{
    if (node != NULL)
    {
        reset(node->right);
        reset(node->left);
        delete[] node;
    }
}

void Abp::reset()
{
    reset(this->root);
    this->root = NULL;
}

int Abp::getSize()
{
    return size;
}

void Abp::insert(int value, string text)
{
    this->root = insert(value, this->root, text);
    this->size++;
}

Abp::Node *Abp::insert(int value, Node *root, string text)
{
    if (root == NULL)
    {
        root = new Node;
        root->value = value;
        root->text = new char[text.length() + 1];
        strcpy(root->text, text.c_str());
        root->left = NULL;
        root->right = NULL;
        return root;
    }
    else if (value < root->value)
    {
        root->left = insert(value, root->left, text);
        if (avl)
        {
            root = balance(root);
        }
    }
    else if (value >= root->value)
    {
        root->right = insert(value, root->right, text);
        if (avl)
        {
            root = balance(root);
        }
    }
    return root;
}

void Abp::remove(int value)
{
    this->root = remove(this->root, value);
}

Abp::Node *Abp::remove(Node *t, int x)
{
    Node *temp;
    if (t == NULL)
        return NULL;
    else if (x < t->value)
        t->left = remove(t->left, x);
    else if (x > t->value)
        t->right = remove(t->right, x);
    else if (t->left && t->right)
    {
        temp = findMin(t->right);
        t->value = temp->value;
        t->right = remove(t->right, t->value);
    }
    else
    {
        temp = t;
        if (t->left == NULL)
            t = t->right;
        else if (t->right == NULL)
            t = t->left;
        delete temp;
        this->size--;
    }
    if (t == NULL)
        return t;
    if (avl)
    {
        t = balance(t);
    }
    return t;
}

string Abp::get(int value)
{
    Node *root = this->root;
    while (root != NULL)
    {
        if (value == root->value)
        {
            return string(root->text);
        }
        else if (value > root->value)
        {
            root = root->right;
        }
        else
        {
            root = root->left;
        }
    }
    return NULL;
}

void Abp::display()
{
    display(this->root);
    cout << endl;
}

void Abp::display(Node *ptr, int level)
{
    int i;
    if (ptr != NULL)
    {
        display(ptr->right, level + 1);
        printf("\n");
        if (ptr == root)
            cout << "Raiz -> ";
        for (i = 0; i < level && ptr != root; i++)
            cout << "        ";
        cout << ptr->value;
        display(ptr->left, level + 1);
    }
}

void Abp::showBalance()
{
    showBalance(this->root);
    cout << endl;
}

void Abp::showBalance(Node *root)
{
    if (root == NULL)
        return;
    showBalance(root->left);
    cout << root->value << ":" << diff(root) << " ";
    showBalance(root->right);
}

Abp::Node *Abp::balance(Node *temp)
{
    int bal_factor = diff(temp);

    if (bal_factor > 1)
    {
        if (diff(temp->left) > 0)
            temp = rotateLL(temp);
        else
            temp = rotateLR(temp);
    }
    else if (bal_factor < -1)
    {
        if (diff(temp->right) > 0)
            temp = rotateRL(temp);
        else
            temp = rotateRR(temp);
    }
    return temp;
}

int Abp::height(Node *temp)
{
    int h = 0;
    if (temp != NULL)
    {
        int l_height = height(temp->left);
        int r_height = height(temp->right);
        int max_height = max(l_height, r_height);
        h = max_height + 1;
    }
    return h;
}

Abp::Node *Abp::findMin(Node *t)
{
    if (t == NULL)
        return NULL;
    else if (t->left == NULL)
        return t;
    else
        return findMin(t->left);
}

int Abp::diff(Node *temp)
{
    int l_height = height(temp->left);
    int r_height = height(temp->right);
    int b_factor = l_height - r_height;
    return b_factor;
}

Abp::Node *Abp::rotateRR(Node *parent)
{
    Node *temp;
    temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    return temp;
}

Abp::Node *Abp::rotateLL(Node *parent)
{
    Node *temp;
    temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    return temp;
}

Abp::Node *Abp::rotateLR(Node *parent)
{
    Node *temp;
    temp = parent->left;
    parent->left = rotateRR(temp);
    return rotateLL(parent);
}

Abp::Node *Abp::rotateRL(Node *parent)
{
    Node *temp;
    temp = parent->right;
    parent->right = rotateLL(temp);
    return rotateRR(parent);
}
