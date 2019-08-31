#include <map>
#include <limits>
#include <bits/stdc++.h>
template<typename K, typename V>
class interval_map {
	std::map<K,V> m_map;

public:
    // constructor associates whole range of K with val by inserting (K_min, val)
    // into the map
    interval_map( V const& val) {
        m_map.insert(m_map.end(),std::make_pair(std::numeric_limits<K>::lowest(),val));
    }

    // Assign value val to interval [keyBegin, keyEnd).
    // Overwrite previous values in this interval.
    // Conforming to the C++ Standard Library conventions, the interval
    // includes keyBegin, but excludes keyEnd.
    // If !( keyBegin < keyEnd ), this designates an empty interval,
    // and assign must do nothing.
    void assign( K const& keyBegin, K const& keyEnd, V const& val ) {
        if(!(keyBegin < std::numeric_limits<K>::lowest())){
            if(keyBegin>=keyEnd) return;
            auto lastItr = --m_map.upper_bound(keyEnd);
            auto startItr = --m_map.upper_bound(keyBegin);
            auto lastVal = lastItr->second;

            lastItr = m_map.insert(lastItr,std::make_pair(keyEnd,lastItr->second));
            startItr = m_map.insert(startItr,std::make_pair(keyBegin,val));

            lastItr->second = lastVal;
            startItr->second= val;
            auto prevItr = std::prev(startItr);

            while(startItr!=m_map.begin() && prevItr->second == val){
                --startItr;
                --prevItr;
            }
            while(lastItr!=m_map.end() && startItr->second == lastItr->second){
                ++lastItr;
            }
            m_map.erase(++startItr,lastItr);    
        }
        
    }

    // look-up of the value associated with key
    V const& operator[]( K const& key ) const {
        return ( --m_map.upper_bound(key) )->second;
    }
    
    void show() {
		std::cout << "show" << std::endl;
		for(auto entry : m_map) {
			std::cout << entry.first << entry.second << std::endl;
		}
	}
};

int main(int argc, char* argv[])
{
    interval_map<unsigned int, char> m('A');
    m.assign(6, 7, 'd');
    m.assign(8, 12, 'd');
    m.assign(11, 14, 'm');
    m.show();
    return 0;
}