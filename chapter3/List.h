/************************************************************************/
/*��list��ʵ�֣����õ���˫������C++��׼����ʹ�õ�Ҳ��˫������ */
/************************************************************************/

#ifndef LIST_H
#define  LIST_H

namespace stl
{
	template <typename Object> 
	class List
	{
	//public members
	public:
		//���캯��
		List() : theSize(0)
		{
			init();
		}

		//�������캯��
		List(const List & L)
		{
			//��Ҫ���εĿ���
			init();
			this->operator=(L);
		}

		//���ظ�ֵ�����
		const List & operator = (const List & L)
		{
			if (this == &L)
			{
				return *this;
			}
		    //�β�List��const���͵ģ����ֻ�ܵ���const�汾�ĺ���
			//��Ԫ��һ�����������������ڵ㣬�ڵ���init������
			for (const_iterator from = L.begin(); from != L.cend(); ++from)
			{
				push_back(*L);
			}
			return *this;
		}

		bool operator == (const List & L)
		{
			return head == L.head && tail == L.tail && theSize == L.theSize;
		}

		//��������
		~List()
		{
			//ɾ��Ԫ��
			Node* temp = head->next;
			Node* tempNext = temp->next;
			while (temp != tail)
			{
				delete temp;
				temp = tempNext;
			}
			//ɾ��ͷ����β�ڵ�
			delete head;
			delete tail;
		}

		void init()
		{
			head = new Node;
			tail = new Node;
			head->next = tail;
			tail->prev = head;
		}

	public:
		/************************************************************************/
		/* ˵   ������������Ķ���
		/* ʱ   �䣺2016.10.27
		/************************************************************************/
		class const_iterator
		{
		public:
			//���캯������Ĭ��ֵΪNULL
			const_iterator(Node* n = NULL)
				:current(n){ }

			//����ȡ���ò������������ò��������޲ε�
			const Object& operator * () const
			{
				retrieve();
			}

			//����++�����صĻ��ǵ�������current�����˸ı䣬��������Ϊconst
			//�������Ӻ������
			const_iterator & operator ++ ()
			{
				current = current->next;
				return *this;
			}

			//���ã�Ϊ�����ڲ�����һ�£�����֮ǰ��ֵ
			const_iterator & operator ++ (int)
			{
				const_iterator ret = *this;
				++*this;
				return ret;
			}

			bool operator == (const const_iterator & iter) const
			{
				return current == iter.current;
			}

			bool operator != (const const_iterator & iter) const
			{
				return ! (this->operator== (iter));
			}
		protected:
			//����һ��Node*�ı����������������λ�ã�����Ϊprotected��Ϊ���������ܷ��ʵ�
			Node* current;

			//���ص�������ָ�ڵ����ݶ��������,���ı�const_iterator���κ����ݣ�����Ϊconst
			//�ú���ֻ���ڲ�ʹ�ã�����ΪprotectedΪ����������ʹ��
			const Object & retrieve() const
			{
				return current->data;
			}
			const_iterator( Node* p ) : current(p) { }

			//Ϊ���ܷ���List<Object>�ĳ�Ա��������������Ϊconst_iterator����Ԫ
			friend class List<Object>;
		};


		//��const_iterator�̳й���
		class iterator : public const_iterator
		{
		public:
			iterator();
			~iterator();
			//����ȡ���ò������������ò��������޲ε�
			Object& operator * () const
			{
				retrieve();
			}

			iterator & operator ++ ()
			{
				current = current->next;
				return *this;
			}

			//���ã�Ϊ�����ڲ�����һ�£�����֮ǰ��ֵ
			iterator & operator ++ (int)
			{
				const_iterator ret = *this;
				++*this;
				return ret;
			}
		protected:
			iterator(Node* p) : const_iterator (p) { }
		};

		/************************************************************************/
		/* ��������begin end��Ա
		/* ʱ   �䣺2016.10.27
		/************************************************************************/
		iterator begin()
		{
			return iterator(head->next);
		}

		iterator end()
		{
			return iterator(tail);
		}

		const_iterator cbegin() const
		{
			return const_iterator(head->next);
		}

		const_iterator cend() const
		{
			return const_iterator(tail);
		}


		/************************************************************************/
		/* ˵   ������ֵ��swap
		/* ʱ   �䣺2016.10.27
		/************************************************************************/

		/************************************************************************/
		/* ˵   ����������С����
		/* ʱ   �䣺2016.10.27
		/************************************************************************/
		//size����
		int Size() const
		{
			return theSize;
		}

		bool Empty() const
		{
			return Size() == 0;
		}



		/************************************************************************/
		/* ˵   �������������Ԫ��
		/* ʱ   �䣺2016.10.27
		/************************************************************************/
		void push_back(const Object& obj)
		{
			insert(end(), obj);
		}


		void push_front(Object obj)
		{
			insert(begin(), obj);
		}

		iterator insert(iterator it, const Object &  obj)
		{
			Node* p = it.current;
			Node* node = new Node(obj, p->prev, p);
			p->prev->next = node;
			p->prev = node;
			//��С��һ
			++theSize;
			return iterator(node);
			//ţ��д����return iterator(p->prev = p->prev->next = new Node(obj, p->prev, p));
		}

		/************************************************************************/
		/* ˵   ��������Ԫ��
		/* ʱ   �䣺2016.10.27
		/************************************************************************/
		Object & front() const
		{
			return head->next->data;
		}

		const Object & front() const
		{
			return head->next->data;
		}

		Object & back() const
		{
            return tail->prev->data;
		}

		const Object & back() const
		{
			return tail->prev->data;
		}

		/************************************************************************/
		/* ˵   ����ɾ��Ԫ��
		/* ʱ   �䣺2016.10.27
		/************************************************************************/
		void pop_front()
		{
			Node* temp = head->next;
			temp->next->prev = head;
			head->next = temp->next;
			delete temp;
			theSize--;
		}

		void pop_back()
		{
			erase(--end());
		}

		iterator erase(iterator itr)
		{
			Node* temp = itr.current;
			iterator ret = ++itr;
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
			delete temp;
			theSize--;
			return ret;
		}

		iterator erase(iterator itr1, iterator itr2)
		{
			iterator to  = ++itr2;
			for (iterator i = itr1; i != to; )
			{
				i = erase( i );
			}
			return i;
		}

	private:
		//����ڵ�
		struct  Node
		{
			Object data;
			Node* prev;
			Node* next;
			//�ṹ��Ĺ��캯��
			Node(Object obj = Object(), Node* p = NULL, Node* n = NULL)
				:data(obj), prev(p), next(n){ }
		};
		Node* head;   //ͷ���
		Node* tail;      //β�ڵ�
		int theSize;
	};
}
#endif