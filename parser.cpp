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
        std::ios_base::openmode operationMode;

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
        fileHandler(const string fileName, std::ios_base::openmode opMode): file(fileName, opMode), operationMode(opMode)
        {
            if(true == fileIsOpen())
            {
                if(operationMode == std::ios::in)
                {
                    gatherFileContent();
                }
            }
        }

        bool fileIsOpen()
        {
            return file.is_open();
        }

        string & getFileContent()
        {
            return fileContent;
        }

        void fillTheFile(const string text2Write)
        {
            if(operationMode == std::ios::out)
            {
                fileContent = text2Write;
                file << fileContent;
            }
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
    fileHandler inputFile("Tekst.html", std::ios::in);

    if(false == inputFile.fileIsOpen())
    {
        cout << "File cannot be opended\n";
    }
    else
    {
        std::smatch match;

        regex regex1(R"((("itemWidth"|"xOffset")><int>)(\d+))");
        regex regex2(R"((("itemHeight"|"yOffset")><int>)(\d+))");
        regex regex3(R"((("fontSize"|"titleFontSize")><int>)(\d+))");

        vector<nodeCoeffs> allRegsAndCoeffs{{1.5, regex1},
                                            {1.78, regex2}, //1.78~16/9 
                                            {2.35, regex3}
                                           };   
        
        for(auto oneElemnt:allRegsAndCoeffs)
        {
            std::regex_search(inputFile.getFileContent(), match, oneElemnt.regForNode);

            //Convert number to int and recalculate
            int newValue = stoi(match[3])*oneElemnt.coeffs;

            //Setting new value
            string newNode = match[1].str() + std::to_string(newValue);
            inputFile.getFileContent() = std::regex_replace(inputFile.getFileContent(), oneElemnt.regForNode, newNode);
        }

        fileHandler outputFile("Tekst_out.html", std::ios::out);

        outputFile.fillTheFile(inputFile.getFileContent());
    }

    return 0;
}

