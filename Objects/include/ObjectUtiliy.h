#ifndef RTX_OBJECTUTILIY_H
#define RTX_OBJECTUTILIY_H

#include <string>
#include <vector>
#include "InstantiableObject.h"

class ObjectUtility 
{
    public:
        static std::vector<InstantiableObject*> createObjectsFromFile(const std::string& filename);
};


#endif //RTX_OBJECTUTILIY_H
