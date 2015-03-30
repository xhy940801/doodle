#ifndef _ARRAYBLOCKINGQUEUE_H
#define _ARRAYBLOCKINGQUEUE_H

#include <condition_variable>
#include <atomic>
#include <mutex>
#include <thread>

/**
 * @author xiao.hy
 */
template <typename T>
class ArrayBlockingQueue
{
	T* buffer;
	size_t qmod;
	std::atomic<size_t> head, tail, claimg, claimp;
	std::condition_variable waitForEpt, waitForFll;
	std::mutex emtx, fmtx;
	std::atomic<size_t> popWaitCount, pushWaitCount;
private:
	size_t i2p(size_t i) const;
public:
	ArrayBlockingQueue(size_t minSize);
	~ArrayBlockingQueue();

	void pop(T& data);
	void push(const T& data);

	size_t getCapacity() const;
	bool isEmpty() const;
	bool isFull() const;
};

template <typename T>
inline size_t ArrayBlockingQueue<T>::i2p(size_t i) const
{
	return i & qmod;
}

template <typename T>
ArrayBlockingQueue<T>::ArrayBlockingQueue(size_t minSize)
	: head(0), tail(0), claimg(0), claimp(0), popWaitCount(0), pushWaitCount(0)
{
	size_t capacity = 1;
	while(minSize != 0)
	{
		capacity <<= 1;
		minSize >>= 1;
	}
	
	buffer = new T[capacity];
	qmod = capacity - 1;
}

template <typename T>
ArrayBlockingQueue<T>::~ArrayBlockingQueue()
{
	delete[] buffer;
}

template <typename T>
void ArrayBlockingQueue<T>::pop(T& data)
{
	size_t cg, tn;
	do
	{
		++popWaitCount;
		while((cg = claimg.load()) == (tn = i2p(tail.load())))
		{
			std::unique_lock<std::mutex> lck(emtx);
			waitForEpt.wait(lck);
		}
		--popWaitCount;
	} while(!claimg.compare_exchange_weak(cg, i2p(cg + 1)));

	data = buffer[cg];
	
	size_t oh = cg, nh = i2p(cg + 1);
	while(!head.compare_exchange_weak(oh, nh))
	{
		std::this_thread::yield();
		oh = cg;
	}

	size_t odwc = pushWaitCount.load();
	while(odwc > 0 && odwc <= pushWaitCount.load() && !isEmpty())
	{
		odwc = pushWaitCount.load();
		waitForFll.notify_all();
		std::this_thread::yield();
	}
}

template <typename T>
void ArrayBlockingQueue<T>::push(const T& data)
{
	size_t cp, h;
	do
	{
		++pushWaitCount;
		while(i2p((cp = claimp.load()) + 1) == (h = head.load()))
		{
				std::unique_lock<std::mutex> lck(fmtx);
			waitForFll.wait(lck);
		}
		--pushWaitCount;
	} while(!claimp.compare_exchange_weak(cp, i2p(cp + 1)));

	buffer[cp] = data;

	size_t ot = cp, nt = i2p(cp + 1);
	while(!tail.compare_exchange_weak(ot, nt))
	{
		std::this_thread::yield();
		ot = cp;
	}

	size_t odwc = popWaitCount.load();
	while(odwc > 0 && odwc <= popWaitCount.load() && !isFull())
	{
		odwc = popWaitCount.load();
		waitForEpt.notify_all();
		std::this_thread::yield();
	}
}

template <typename T>
inline size_t ArrayBlockingQueue<T>::getCapacity() const
{
	return qmod + 1;
}

template <typename T>
inline bool ArrayBlockingQueue<T>::isEmpty() const
{
	return head.load() == tail.load();
}

template <typename T>
inline bool ArrayBlockingQueue<T>::isFull() const
{
	return head.load() == i2p(tail.load() + 1);
}

#endif