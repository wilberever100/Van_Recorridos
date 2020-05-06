#ifndef SOURCE_DIRECTEDGRAPH_HPP_
#define SOURCE_DIRECTEDGRAPH_HPP_

#include <cstddef>
#include <iostream>
#include <utility>
#include <list>
#include <bits/stdc++.h>
using namespace std;

namespace ADE {

    template <typename Type>
    class Node {
    public:
        typedef Type data_type;

        Node(data_type data, std::size_t const& out_ptrs_size)
            : data_(new data_type(data)),
            out_ptrs_size_(out_ptrs_size),
            forward_(new Node<Type>* [out_ptrs_size]()) {}

        virtual ~Node() {}

        /**
         *  \brief Access specified element
         *
         *  Returns a reference to the element at specified location position. If id
         * is not within the range of the container an exception of type
         * std::out_of_range is thrown. If no node exist at the location
         * std::logic_error is thrown.
         *
         */
        Node& operator[](std::size_t id) const {
            if (out_ptrs_size_ < id) {
                throw std::out_of_range("Index out of node edges range.");
            }
            if (!forward_[id]) {
                throw std::logic_error("Access to null reference.");
            }
            return *forward_[id];
        }   
        data_type* data_;
        Node** forward_;
        std::size_t out_ptrs_size_;
    };

    template <typename Type, typename Node = Node<Type>>
    class DirectedGraph {
    public:
        typedef Type data_type;

        DirectedGraph(data_type const data, std::size_t const& out_ptrs_size)
            : root_ptr_(new Node(data, out_ptrs_size)),
            out_ptrs_size_(out_ptrs_size) {}

        virtual ~DirectedGraph() {}

        Node* get_root_ptr() { return root_ptr_; }

        /**
         *  \brief Inserts element
         *
         *  Inserts elements at the specified node in the container at location id and
         * returns the vertex pointer for the new vertex.
         *
         */
        Node* insert_vertex(data_type const data, Node* u, std::size_t position) {
            if (u->out_ptrs_size_ != out_ptrs_size_) {
                throw std::logic_error("Node with different number of out pointers.");
            }
            if (out_ptrs_size_ < position) {
                throw std::out_of_range("Insert position out of node edges range.");
            }
            Node* next_node_ptr = dynamic_cast<Node*>(u->forward_[position]);
            Node* new_node = new Node(data, out_ptrs_size_);
            new_node->forward_[position] = next_node_ptr;
            u->forward_[position] = new_node;
            return dynamic_cast<Node*>(u->forward_[position]);
        }

        /**
         *  \brief Attachs two nodes
         *
         *  Adds edge from u to v and throws and exception oof type std::out_of_range
         * if position is not within the range of u. nodes,
         *
         */
        void add_edge(Node* u, Node* v, std::size_t position) {
            if (u->out_ptrs_size_ < position) {
                throw std::out_of_range("Position out of first argument node.");
            }
            u->forward_[position] = v;
        }

        int retornar(int blocks, int B) {
            if (blocks % B > 0) {
                return (blocks / B) + 1;
            }
            else {
                return blocks / B;
            }
        }

        int VanDaBose(int B, data_type value) {

            list<pair<Node*,bool>> S;
            S.push_back(make_pair(root_ptr_, 0));
            int blocks=0; //cantidad de bloques recorridos

            while (!S.empty()) {
                blocks++;
                Node* u=S.front().first;
                bool altura = S.front().second;     //indica si es par o no

                

                if (u && *(u->data_) == value) {
                    return retornar(blocks, B);
                }
                S.pop_front();

                for (int i = 0; i <2; i++) {
                    if (altura) {
                        if (u->forward_[i]) {
                            S.push_back(make_pair(u->forward_[i], 0));
                            
                        }
                    }
                    else {
                        if (u->forward_[1-i]) {
                            S.push_front(make_pair(u->forward_[1-i], 1));
                        }

                    }
                }
                

            }
            

            return retornar(blocks, B);

        }
        
        int DFS(int B, data_type value) {
            stack<Node*> S;
            S.push(root_ptr_);
            int blocks=0;
            while(!S.empty()) {
                blocks++;
                Node* u = S.top();
                S.pop();
                if (*(u->data_) == value) {
                    return retornar(blocks, B);
                }

                for (int i = 1; i >= 0; i--) {
                    if (u->forward_[i]) {
                        S.push(u->forward_[i]);
                    }
                }
                
            }
            return retornar(blocks, B);
        }
        int BFS(int B, data_type value) {
            list<Node*> S;
            S.push_back(root_ptr_);
            int blocks = 0;
            while (!S.empty()) {
                blocks++;
                Node* u = S.front();
                S.pop_front();
                if (*(u->data_) == value) {
                    return retornar(blocks, B);
                }
                for (int i = 0; i < 2; i++) {
                    if (u->forward_[i]) {
                        S.push_back(u->forward_[i]);
                    }
                }

            }
            return retornar(blocks, B);
        }

        int look_for(int index,int B, data_type value) {
            int res;
            switch (index) {
            case 1 :
                res = BFS(B, value);
                break;
            case 2:
                res= DFS(B, value);
                break;
            case 3:
                res=VanDaBose(B, value);
                break;
            default:
                cout << "No ingresó un algoritmo correcto" << endl;
                return -1;
                break;
            }
            
            cout << "La cantidad de bloques recorridos es: "<<res << endl;
            return res;
            

        }



    private:
        Node* root_ptr_;
        std::size_t out_ptrs_size_;
    };

}  // namespace ADE

#endif  // SOURCE_DIRECTEDGRAPH_HPP_