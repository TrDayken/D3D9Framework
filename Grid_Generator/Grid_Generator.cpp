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

std::vector<ObjectGroup*> objectgroups;

void LoadXML(std::string filepath, int cellwidth, int cellheight)
{
    TiXmlDocument doc(filepath.c_str());


    if (!doc.LoadFile())
    {
        printf("%s", doc.ErrorDesc());
    }
    else
    {
        TiXmlElement* root = doc.RootElement();

        for (TiXmlElement* XMLobjectgroup = root->FirstChildElement("objectgroup"); XMLobjectgroup != NULL; XMLobjectgroup = XMLobjectgroup->NextSiblingElement("objectgroup"))
        {
            objectgroups.push_back(new ObjectGroup(XMLobjectgroup,  cellwidth,  cellheight));
        }
    }

    DebugOut(L"[INFO] Read file complete");
}

void CreateXML(std::string filepath, int cellwidth, int cellheight)
{
    auto node = split(filepath, "\\");

    TiXmlDocument doc;

    //XML declaration
    TiXmlDeclaration* dec = new TiXmlDeclaration("1.0", "utf-8", "");
    doc.LinkEndChild(dec);

    //root node
    TiXmlElement* root = new TiXmlElement("grid");
    doc.LinkEndChild(root);

    TiXmlElement* config = new TiXmlElement("config");
    config->SetAttribute("cellwidth", cellwidth);
    config->SetAttribute("cellheight", cellheight);

    root->LinkEndChild(config);

    for (int i = 0; i < objectgroups.size(); i++)
    {
        TiXmlElement* group = new TiXmlElement("group");
        group->SetAttribute("id", objectgroups[i]->getID());
        group->SetAttribute("name", objectgroups[i]->getName().c_str());

        auto objects = objectgroups[i]->getObject();

        for (auto o : objects)
        {
            TiXmlElement* object = new TiXmlElement("object");

            object->SetAttribute("id", o->getID());
            object->SetAttribute("cellx", o->getCellx());
            object->SetAttribute("celly", o->getCelly());
            object->SetAttribute("spanx", o->getSpanx());
            object->SetAttribute("spany", o->getSpany());

            group->LinkEndChild(object);
        }

        root->LinkEndChild(group);
    }

    std::string filename = "grid\\grid-" + node[1];

    doc.SaveFile(filename.c_str());

    DebugOut(L"[INFO] Create file complete");
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
  
    LoadXML(filepath, cellwidth, cellheight);

    CreateXML(filepath, cellwidth, cellheight);
}



