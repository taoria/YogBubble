#include<functional>
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

#ifdef _DEBUG
#define OUTPUT(info) cout<<info <<endl<<endl;
#else
#define OUTPUT(info)
#endif

namespace YogTools
{
	template<class C, typename R, typename ...Args>
	class DelegateClass
	{
	public:
		typedef R(C::*class_func_type)(Args...);

		DelegateClass(class_func_type fun, C* class_ptr) :_fun(fun), _class_ptr(class_ptr) {}

		R operator()(Args&&...args)
		{
			return (_class_ptr->*_fun)(args...);
		}


		bool operator== (const DelegateClass<C, R, Args...>&other) const
		{
			if (_class_ptr == other._class_ptr && _fun == other._fun)
				return true;
			return false;
		}

		template<typename T>
		bool operator==(const T&&)const
		{
			return false;
		}

	private:
		C*  _class_ptr;
		class_func_type _fun;

	};


	template<typename ...T>
	class delegate { };


	template<typename R, typename ...Args>
	class delegate<R(Args...)>
	{
	public:
		typedef std::function<R(Args...)> dele_func;
		typedef std::list<dele_func> function_list;
		typedef R(*func_type)(Args...);
		typedef delegate<R(Args...)>  this_type;


		delegate()
		{
			OUTPUT("function type:" << typeid(R(Args...)).name())
				OUTPUT("args count:" << sizeof...(Args))
		};

		~delegate()
		{
			func_list.clear();
		}


		this_type& operator -=(func_type fun)
		{
			auto itr = std::find_if(func_list.begin(), func_list.end(),
				[&](dele_func&f)->bool
			{
				auto _fun = f.target<R(*)(Args...)>();
				if (_fun && *_fun == fun)
				{
					return true;
				}
				return false;
			});

			if (itr != func_list.end())
				func_list.erase(itr);

			return *this;
		}

		template<class C>
		this_type& operator -=(DelegateClass<C, R, Args...>&& class_mem_h)
		{
			auto itr = std::find_if(func_list.begin(), func_list.end(),
				[&](dele_func&f)->bool
			{
				auto _fun = f.target<DelegateClass<C, R, Args...>>();
				if (_fun && *_fun == class_mem_h)
				{
					return true;
				}
				return false;
			});


			if (itr != func_list.end())
			{
				func_list.erase(itr);
			}
			return *this;
		}


		this_type& operator +=(func_type fun)
		{
			func_list.push_back(fun);
			return *this;
		}

		template<class C>
		this_type& operator +=(DelegateClass<C, R, Args...>&& class_mem_h)
		{
			func_list.push_back(class_mem_h);
			return *this;
		}

		void operator()(Args&&...args)
		{
			for (auto itr = func_list.begin(); itr != func_list.end(); itr++)
			{
				try
				{
					(*itr)(args...);
				}
				catch (exception ex)
				{
					//do something...
				}
			}
		}


	private:
		function_list func_list;
	};


	template<typename C, typename R, typename ...Args>
	auto makeDelegateClassHelper(R(C::*class_func_type)(Args...), C* class_ptr) ->DelegateClass<C, R, Args...>
	{
		return DelegateClass<C, R, Args...>(class_func_type, class_ptr);
	}

};
