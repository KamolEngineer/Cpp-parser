#include <iostream>
#include <fstream>
#include <regex>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::fstream;
using std::getline;
using std::regex;
using std::vector;


struct nodeCoeffs
{
    float coeffs;
    regex &regForNode;
};


class fileHandler
{
    private:
        fstream file;
        string fileContent;

        void gatherFileContent()
        {
            string oneTextLine;

            while(getline(file, oneTextLine))
            {
                fileContent+=oneTextLine+"\n";
            }
        }
  
    public:

        fileHandler(){}
        fileHandler(const string fileName, std::ios_base::openmode opMode): file(fileName, opMode)
        {
            if(true == fileIsOpen())
            {
                gatherFileContent();
            }
        }

        bool fileIsOpen()
        {
            return file.is_open();
        }
        
        ~fileHandler()
        {
            if(true == fileIsOpen())
            {
                file.close();
            }
            
            cout << "File has been closed:\n";
        }
};

int main(void)
{
    fstream inputHtml("Tekst.html", std::ios::in);

    fileHandler inputFile, outputFile;

    if(false == inputHtml.is_open())
    {
        cout << "File cannot be opended\n";
    }
    else
    {
        string textFromFile, oneTextLine;
        std::smatch match;

        while(getline(inputHtml, oneTextLine))
        {
            textFromFile+=oneTextLine+"\n";
        }
        
        cout << textFromFile << endl;

        regex regex1(R"((("itemWidth"|"xOffset")><int>)(\d+))");
        regex regex2(R"((("itemHeight"|"yOffset")><int>)(\d+))");
        regex regex3(R"((("fontSize"|"titleFontSize")><int>)(\d+))");

        vector<nodeCoeffs> allRegsAndCoeffs{{1.5, regex1},
                                            {1.78, regex2}, //1.78~16/9 
                                            {2.35, regex3}
                                           };   
        
        for(auto oneElemnt:allRegsAndCoeffs)
        {
            std::regex_search(textFromFile, match, oneElemnt.regForNode);

            //Convert number to int and recalculate
            int newValue = stoi(match[3])*oneElemnt.coeffs;

            //Setting new value
            string newNode = match[1].str() + std::to_string(newValue);
            textFromFile = std::regex_replace(textFromFile, oneElemnt.regForNode, newNode);
        }

        cout << textFromFile << endl;

        fstream outputHtml("Tekst_out.html", std::ios::out);

        //Write to new file
        outputHtml << textFromFile;
        outputHtml.close();
    }

    inputHtml.close();

    return 0;
}

