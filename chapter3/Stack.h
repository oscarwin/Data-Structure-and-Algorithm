/************************************************************************/
/*��stack��ʵ�� ��ʹ��vectorʵ��*/
/************************************************************************/
#include <vector>
#ifndef STACK_H
#define  STACK_H

namespace stl
{
	template <typename Object>
	class Stack
	{
	public:
		Stack()
			:topOfStack(0)
			,obj(0) {}

		~Stack() {}

		//����Ĭ�ϵĿ������캯�������������

		void push(const Object & rth)
		{
			obj.push_back(rth);
			++topOfStack;
		}

		const Object & pop() const
		{
			if (topOfStack == 0)
			{
				throw();
			}
			Object temp = obj[topOfStack];
			obj.pop_back();
			return temp;
		}

		bool empty() const
		{
			return topOfStack == 0;
		}
	private:
		std::vector<Object> obj;
		int topOfStack;
	};
}
#endif // !STACK_H
