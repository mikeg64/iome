#ifndef _IOVLIST_H_
#define _IOVLIST_H_

#include <deque>
#include "vec.h"

typedef std::list<vec> listv;


class vlist
{
public:
	vlist();
	virtual ~vlist();
	
	listv m_vlist;
	
	push_front(vec &v);
	push_back(vec &v);
	pop_front();
	pop_back();
};

#endif //_IOVLIST_H_
