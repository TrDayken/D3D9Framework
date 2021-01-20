// readfile map

/*
  <grid cellwidth, cellheight, width, height>
    <data>
        <group id , name>
            <object id, cellx, celly, spanx, spany />
            <object id, cellx, celly, spanx, spany />
        </group>
    </data>
  </grid>

*/

// create file xml accordingly 

#include <iostream>
#include <string>

#include "tinyXML/tinyxml/tinyxml.h"
#include "tinyXML/tinyxml/tinystr.h"
#include "Utils.h"
#include "ObjectGroup.h"

void LoadXML(std::string filepath)
{
    TiXmlDocument doc(filepath.c_str());


    if (!doc.LoadFile())
    {
        printf("%s", doc.ErrorDesc());
    }
    else
    {

    }
}

void CreateXML()
{
}



int main()
{
    std::string filepath;

    int cellwidth, cellheight;

    std::cout << "Enter FilePath\n";
    std::cin >> filepath;

    std::cout << "Enter Cell Width \n";
    std::cin >> cellwidth;

    std::cout << "Enter Cell Height \n";
    std::cin >> cellheight;
  
    LoadXML(filepath);


}



