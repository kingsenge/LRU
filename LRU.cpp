#include<unordered_map>
#include<list>
using namespace std;

typedef struct stElement
{
	int	nKey;
	int	nValue;
	list<int>::iterator oIter;
}STELEMENT;

class LRUCache {
public:
    LRUCache(int capacity);
public:
    int		get(int key);
    void	put(int key, int value);
public:
	void	delNode();
	void	updateNode(list<int>::iterator &oIter);
	void	insertNode(list<int>::iterator &oIter,int nIndex);
private:
	int		m_nLeft;
	int		m_nTotalSize;
private:
	list<int>	m_pList;
	unordered_map<int,STELEMENT> m_Hash;
};

LRUCache::LRUCache(int capacity)
{
	m_nLeft = capacity;
	m_nTotalSize = capacity;
}

void LRUCache::delNode()
{
	list<int>::iterator oIter = m_pList.begin();
	m_Hash[*oIter].nKey =-1;

	m_pList.pop_front();
}

void LRUCache::updateNode(list<int>::iterator &oIter)
{
	int nIndex = *oIter;

	m_pList.erase(oIter);
	m_pList.push_back(nIndex);

	oIter = m_pList.end();
	oIter--;
}

void LRUCache::insertNode(list<int>::iterator &oIter,int nIndex)
{
	m_pList.push_back(nIndex);
	oIter = m_pList.end();
	oIter--;
}

void LRUCache::put(int key, int value)
{
	unordered_map<int,STELEMENT>::iterator oIter = m_Hash.find(key);

	if(oIter != m_Hash.end())
	{
		oIter->second.nValue = value;
		if(oIter->second.nKey!=-1)
			updateNode(oIter->second.oIter);
		else
		{
			insertNode(oIter->second.oIter,key);
			if(m_nLeft==0)
				delNode();
		}
		oIter->second.nKey = key;

		return ;
	}

	STELEMENT stElemt;
	stElemt.nKey = key;
	stElemt.nValue = value;
	
	insertNode(stElemt.oIter,key);
	m_Hash[key] = stElemt;

	if(m_nLeft ==0)
		delNode();

	if(m_nLeft>0)
		m_nLeft--;
}

int	LRUCache::get(int key)
{
	unordered_map<int,STELEMENT>::iterator oIter = m_Hash.find(key);
	if(oIter==m_Hash.end())
		return -1;

	if(oIter->second.nKey==-1)
		return -1;
	int nValue = oIter->second.nValue;

	updateNode(oIter->second.oIter);

	return nValue;
}