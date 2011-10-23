
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

	void iterBegin() { iter = this->next; }
	T iterGet() { return (iter = iter->next)->prev->data; }
	bool iterDone() { return (iter == this); }

	// remove self from the list, but won't be deleted
	void remove()
	{
		prev->next = next;
		next->prev = prev;
	}

	// remove a node from the list, and deleted that node(but not data).
	void remove(T data)
	{
		iterBegin();
		while (!iterDone())
			if (iterGet() == data) {
				iter->remove();
				delete iter;
				break;
			}
	}

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

