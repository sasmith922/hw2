#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
    std::set<T> intersection;
    typename std::set<T>::iterator iter1 = s1.begin();
    typename std::set<T>::iterator iter2 = s2.begin();

    while(iter1 != s1.end() && iter2 != s2.end())
    {
        if(*iter1 < *iter2)
            ++iter1;
        else if (*iter2 < *iter1)
            ++iter2;
        else // both iters point to same value
        {
            intersection.insert(*iter1); // add to intersection
            ++iter1;
            ++iter2;
        }
    }
    return intersection;
}
template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{

    std::set<T> result = s1; // gets all elements from s1
    result.insert(s2.begin(), s2.end()); // adds all elements from s2
    return result; // because of set properties does not count duplicates

}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
