#ifndef OOP_EXERCISE_06_LIST_H
#define OOP_EXERCISE_06_LIST_H

#include <memory>
#include <iostream>
#include <exception>
#include <iterator>

template<class T>
class TList {
    private:
        struct TListNode {
            T data;
            std::shared_ptr<TListNode> next;

            T& Get(size_t index) {
                if (index == 0) return(data);
                if (next) return(next->Get(--index));
                throw std::logic_error("Ошибка. Выход за границу списка\n");
            }

            void PushBack(T& elem) {
                if(next) next->PushBack(elem);
                else next = std::shared_ptr<TListNode>(new TListNode{elem, std::shared_ptr<TListNode>()});
            }

            void Insert(TListNode& pred, size_t index, const T& elem) {
                if (index == 0) {
                    pred.next = std::shared_ptr<TListNode>(new TListNode{elem, std::move(pred.next)});
                }
                else if (next) {
                    next->Insert(*this, --index, elem);
                }
                else throw std::logic_error("Ошибка. Попытка вставить элемент на несуществующую позицию списка\n");
            }

            void Erase(TListNode& pred, size_t index) {
                if (index == 0) {
                    pred.next = std::move(next);
                }
                else if (next) {
                    next->Erase(*this, --index);
                }
                else throw std::logic_error("Ошибка. Попытка удалить элемент на несуществующей позиции списка\n");
            }

            size_t Size() {
                if (!next) {
                    return 1;
                }
                else return(1 + next->Size());
            }
        };

        std::shared_ptr<TListNode> head;

    public:
        using value_type = T;
        class TLIterator {
            private:
                TList& list;
                size_t index;
                friend class TList;
            public:
                using difference_type = ptrdiff_t;
                using value_type = TList::value_type;
                using reference = TList::value_type&;
                using pointer = TList::value_type*;
                using iterator_category = std::forward_iterator_tag;

            TLIterator(TList& l, int i) : list(l), index(i) {}

            reference operator*() {
                return(list[index]);
            }

            pointer operator->() {
                return(&list[index]);
            }

            TLIterator& operator++() {
                ++index;
                return *this;
            }

            bool operator==(const TLIterator& itr) {
                if (&list == &itr.list) {
                    if (index == itr.index) return(true);
                    else return(false);
                }
                throw std::logic_error("Ошибка. Попытка сравнения итераторов разных списков\n");
            }

            bool operator!=(const TLIterator& itr) {
                if (&list == &itr.list) {
                    if (index != itr.index) return(true);
                    else return(false);
                }
                throw std::logic_error("Ошибка. Попытка сравнения итераторов разных списков\n");
            }
        };

        TList() : head(std::shared_ptr<TListNode>()) {}

        size_t Size() {
            if (head) {
                return (head->Size());
            }
            else return((size_t)0);
        }

        value_type& operator[](size_t i) {
            if (!head) throw std::logic_error("Ошибка. Попытка доступа к несуществующему элементу\n");
            return(head->Get(i));
        }

        void PushBack(value_type& elem) {
            if (!head) {
                head = std::shared_ptr<TListNode>(new TListNode{elem, std::shared_ptr<TListNode>()});
            }
            else {
                head->PushBack(elem);
            }
        }

        void PushBack(value_type&& elem) {
            if (!head) {
                head = std::shared_ptr<TListNode>(new TListNode{elem, std::shared_ptr<TListNode>()});
            }
            else {
                head->PushBack(elem);
            }
        }
        TLIterator Erase(TLIterator itr) {
            if (itr.index == 0) {
                if (head) {
                head = std::move(head->next);
                }
                else throw std::logic_error("Ошибка. Попытка удалить элемент на несуществующей позиции списка\n");
            }
            else if (head->next) {
                try {
                    head->next->Erase(*head, --itr.index);
                }
                catch(std::logic_error& error) {
                    throw error;
                }
            } 
            else throw std::logic_error("Ошибка. Попытка удалить элемент на несуществующей позиции списка\n");
            if (itr.index < Size()) return(itr);
            else return(TLIterator(*this, Size()));
        }

        TLIterator Insert(TLIterator itr, const value_type& elem) {
            if (itr.index == 0) {
                if (head) {
                    head->Insert(*head, itr.index, elem);
                }
                else throw std::logic_error("Ошибка. Попытка вставить элемент на несуществующую позицию списка\n");
            }
            else if (head->next) {
                try {
                    head->next->Insert(*head, --itr.index, elem);
                }
                catch(std::logic_error& error) {
                    throw error;
                }
            
            }
            else throw std::logic_error("Ошибка. Попытка вставить элемент на несуществующую позицию списка\n"); 
            return(itr);
        } 

        void InsertToHead(const value_type& elem) {
            head = std::shared_ptr<TListNode>(new TListNode{elem, std::move(head)});
        }

        TLIterator Begin() {
            return(TLIterator(*this, 0));
        }

        TLIterator End() {
            return(TLIterator(*this, Size()));
        }
};


#endif //OOP_EXERCISE_06_LIST_H