
#ifndef __LIST__
#define __LIST__

template <class T>
class List
{
public:
	List<T> * prev;
	List<T> * next;
	T         data;

	List() : prev(this), next(this) {}
	List(T data) : data(data) {}

	List<T> * add(T data)
	{
		List<T> * list = new List<T>(data);

		list->prev = prev;
		list->next = this;
		prev->next = list;
		prev       = list;

		return list;
	}

	// remove self from the list, but won't be deleted
	void remove()
	{
		prev->next = next;
		next->prev = prev;
	}

	void iterBegin() { iter = this->next; }
	T iterGet() { return (iter = iter->next)->prev->data; }
	bool iterDone() { return (iter == this); }

	unsigned int size()
	{
		unsigned int cnt = 0;
		iter = this;
		while ((iter = iter->next) != this)
			cnt++;
		return cnt;
	}
private:
	List<T> * iter;
};

#endif

