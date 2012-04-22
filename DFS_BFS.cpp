

#include <cstdlib>
#include <iostream>
#include <vector>
#include <set>
using namespace std;

class Tree
{
private:
    enum color{ white, grey, black };
    int number_of_vertexes;
    struct Vertex 
    {
        int parent;
        set<int> children;
        color color_of_vertex;
        Vertex(int _parent, const set<int>& _children, color _color) {
            parent = _parent;
            children = _children;
            color_of_vertex = _color;
        }
        bool operator == (const Vertex& _vertex) {
            return (parent == _vertex.parent && children == _vertex.children && color_of_vertex == _vertex.color_of_vertex); 
        }
        bool operator != (const Vertex& _vertex) {
            return  !((*this) == _vertex);
        }
        ~Vertex() {
            children.clear();
        }
    };
    vector<Vertex> vertexes;
    class DFS_Iterator {
    private:
        int current;
		Tree* tree;
    public:
	DFS_Iterator(Tree* _tree, int index) {
			current = index;
			tree = _tree;
	}
        int get_current() const {
            return current;
        }
		Tree* const getTree() const {
			return tree;
		}
        DFS_Iterator& operator = (const DFS_Iterator& iterator) {
            current = iterator.get_current();
			tree = iterator.getTree();
            return *this;
        }
        bool operator == (const DFS_Iterator& iterator) {
            return (current == iterator.get_current() && tree == iterator.getTree());
        }
        bool operator != (const DFS_Iterator& iterator) {
            return (current != iterator.get_current() || !(tree == iterator.getTree()));
        }
        DFS_Iterator& operator ++ () {
            if(!((tree->getVertexes())[current].children.empty())) {    
                return ((*this) = DFS_Iterator(this->tree, *(((this->tree)->getVertexes())[current].children.begin())));
            }
            else {
                int _current = current;
                int parent_of_current = (tree->getVertexes())[_current].parent;
                set<int> parents_children;
                while(parent_of_current != -1) {
                    parents_children = (tree->getVertexes())[parent_of_current].children;
                    set<int> :: iterator elder_brother = parents_children.find(_current);
                    ++elder_brother;
                    if(elder_brother != parents_children.end()) {
                        return ((*this) = DFS_Iterator((this->tree),*elder_brother));
                    }
                    else {
                        _current = parent_of_current;
                        parent_of_current = (tree->getVertexes())[_current].parent;
                    }
                    return ((*this) = DFS_Iterator(this->tree, -10));
                }
            }
        }
        const Vertex& operator * () const {
            return (tree->getVertexes())[current];
        }
        Vertex& operator * () {
            return (tree->getVertexes())[current];
        }
     };
public: 
    typedef DFS_Iterator iterator;
    int getNumberOfVertexes() const {
        return number_of_vertexes;
    }
    const vector<Vertex>& getVertexes() const {
        return vertexes;
    }
    vector<Vertex>& getVertexes() {
        return vertexes;
    }
    Tree() {
        number_of_vertexes = 1;
        vertexes.push_back(Vertex(-1, set<int>(),white));
    }
    Tree(const vector<Vertex>& _vertexes) {
        number_of_vertexes = _vertexes.size();
        vertexes = _vertexes;
    }
    Tree(const Tree& _tree) {
        number_of_vertexes = _tree.getNumberOfVertexes();
        vector<Vertex> :: const_iterator it;
        for(it = _tree.getVertexes().begin(); it != _tree.getVertexes().end(); it++) {
            vertexes.push_back(*it);
        }
    }
    iterator begin() {
        return iterator(this, 0);
    }
    iterator end() {
        return iterator(this, -10);
    }
    void ErasePaint() {
        vector<Vertex> :: iterator it;
        for(it = vertexes.begin(); it != vertexes.end(); it++) {
            (*it).color_of_vertex = white;
        } 
    } 
    Tree& operator = (const Tree& _tree) {
        number_of_vertexes = _tree.getNumberOfVertexes();
        vector<Vertex> :: const_iterator it;
        vertexes.clear();
        for(it = _tree.getVertexes().begin(); it != _tree.getVertexes().end(); it++) {
            vertexes.push_back(*it);
        }
        return *this;
    }
    bool operator == (const Tree& _tree) {
        if(number_of_vertexes != _tree.getNumberOfVertexes()) {
            return false;
        }
        else {
            int i = 0;
            while(i < number_of_vertexes && vertexes[i] == _tree.getVertexes()[i]) {
                i++;
            }
            return (i == number_of_vertexes);
        }
    }
    bool operator != (const Tree& _tree) {
            return !((*this) == _tree);
    }
    ~Tree() {
        vertexes.clear();
    }
};

    /*Colors[startV] = grey;
    for(int i=0; i<Ribs[startV].size(); i++)
    {
        if(Ribs[startV][i]>0 && Colors[i] == white)
        {
            DFS(i, bypass);
        }
    }
    Colors[startV] = black;
    bypass.push_back(startV);
    return; */
    
int main() {

    return 0;
}

